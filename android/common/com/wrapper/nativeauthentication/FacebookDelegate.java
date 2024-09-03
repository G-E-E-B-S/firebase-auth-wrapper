package com.wrapper.nativeauthentication;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import com.facebook.AccessToken;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;

import org.json.JSONObject;

import java.util.Arrays;
import java.util.List;

public class FacebookDelegate implements FacebookCallback<LoginResult> {

    enum LoginState {
        SUCCESS,
        CANCELLED,
        ERROR
    }

    private static String CLASS_TAG = "FacebookDelegate";
    private static Activity sActivity;
    private static IThreadHelper sThreadHelper;
    private String mUserName = "";
    private boolean mNameFetchSuccess = false;
    private static FacebookDelegate sInstance;

    public FacebookDelegate(Activity activity, IThreadHelper threadHelper) {
        sActivity = activity;
        sThreadHelper = threadHelper;
        sInstance = this;
    }

    public static void fetchAuthToken(String[] permissions) {
        AccessToken token = AccessToken.getCurrentAccessToken();
        if (token != null && token.isDataAccessExpired()) {
            sThreadHelper.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.d("FacebookDelegate", "reauthorizeDataAccess()");
                    LoginManager.getInstance().reauthorizeDataAccess(sActivity);
                }
            });
        } else {
            final List<String> permissionsList = Arrays.asList(permissions);
            sThreadHelper.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    LoginManager.getInstance().logInWithReadPermissions(sActivity, permissionsList);
                }
            });
        }
    }

    public static void fetchUserName() {
        if (!sInstance.mNameFetchSuccess) {
            sThreadHelper.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    AccessToken currentAccessToken = AccessToken.getCurrentAccessToken();
                    GraphRequest request = GraphRequest.newMeRequest(
                            currentAccessToken,
                            new GraphRequest.GraphJSONObjectCallback() {
                                @Override
                                public void onCompleted(
                                        JSONObject object,
                                        GraphResponse response) {
                                    sInstance.updateName(object);
                                }
                            });
                    Bundle parameters = new Bundle();
                    parameters.putString("fields", "name");
                    request.setParameters(parameters);
                    request.executeAsync();
                }
            });

        }
    }

    public static String getAuthToken(boolean checkValidity) {
        AccessToken currentAccessToken = AccessToken.getCurrentAccessToken();
        if (currentAccessToken == null) {
            return "";
        }
        if (!checkValidity) {
            return currentAccessToken.getToken();
        }
        if (!currentAccessToken.isExpired() && !currentAccessToken.isDataAccessExpired()) {
            return currentAccessToken.getToken();
        }
        return "";
    }

    public static String getUserName() {
        return sInstance.mUserName;
    }

    public static boolean isTokenActive() {
        AccessToken token = AccessToken.getCurrentAccessToken();
        if (token == null) {
            return false;
        }
        return AccessToken.isCurrentAccessTokenActive();
    }

    public static void logOut() {
        sInstance.mNameFetchSuccess = false;
        sThreadHelper.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                LoginManager.getInstance().logOut();
            }
        });
    }

    @Override
    public void onSuccess(LoginResult loginResult) {
        Log.d(CLASS_TAG, "Successfully logged in");
        final LoginResult result = loginResult;
        sThreadHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                String token = result.getAccessToken().getToken();
                onComplete(LoginState.SUCCESS.ordinal(),
                        token,
                        "",
                        0);
            }
        });
    }

    @Override
    public void onCancel() {
        Log.d(CLASS_TAG, "Cancelled logged in");
        sThreadHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                onComplete(LoginState.CANCELLED.ordinal(),
                        "",
                        "cancelled",
                        0);
            }
        });
    }

    @Override
    public void onError(final FacebookException error) {
        Log.d(CLASS_TAG, "Error logged in", error);
        final FacebookException exception = error;
        sThreadHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                onComplete(LoginState.ERROR.ordinal(),
                        "",
                        error.toString(),
                        error.hashCode());
            }
        });
    }

    private void updateName(JSONObject object) {
        sThreadHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                try {
                    mUserName = object.getString("name");
                    mNameFetchSuccess = true;
                } catch (Exception e) {
                }
            }
        });

    }

    private native void onComplete(int loginState,
                                   String string,
                                   String errorMsg,
                                   int errorCode);
}
