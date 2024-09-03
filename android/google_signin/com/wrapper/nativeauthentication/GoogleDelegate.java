package com.wrapper.nativeauthentication;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentSender;
import androidx.annotation.NonNull;
import android.util.Log;

import com.cocos.lib.CocosHelper;
import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInStatusCodes;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailability;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.ResolvableApiException;
import com.google.android.gms.common.api.Scope;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

import com.cocos.lib.CocosActivity;

public class GoogleDelegate {
    private static String TAG = "GoogleDelegate";
    private static CocosActivity sActivity;
    private static GoogleSignInClient sSignInClient;
    private static GoogleDelegate sInstance;
    private static int RC_SIGN_IN = 100;
    private static int RC_RESOLVE = 101;

    enum LoginState {
        SUCCESS,
        CANCELLED,
        ERROR
    }
    public GoogleDelegate(CocosActivity activity, String webClientId) {
        sActivity = activity;
        sInstance = this;
        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestIdToken(webClientId)
                .requestEmail()
                .build();
        sSignInClient = GoogleSignIn.getClient(sActivity, gso);
    }

    public static void signInSilently()
    {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Task<GoogleSignInAccount> task = sSignInClient.silentSignIn();
                if (task.isSuccessful()) {
                    sInstance.handleSignInResult(task);
                } else {
                    task.addOnCompleteListener(new OnCompleteListener<GoogleSignInAccount>() {
                        @Override
                        public void onComplete(@NonNull Task task) {
                            sInstance.handleSignInResult(task);
                        }
                    });
                }
            }
        });
    }

    public static void signIn()
    {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Intent signInIntent = sSignInClient.getSignInIntent();
                sActivity.startActivityForResult(signInIntent, RC_SIGN_IN);
            }
        });
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (requestCode == RC_RESOLVE) {
            if (resultCode == Activity.RESULT_OK) {
                GoogleDelegate.SignIn();
            } else {
                onSignInFailure(LoginState.ERROR.ordinal(), "resolutionerror", "resolutionerror", resultCode);
            }
        }
        if (requestCode == RC_SIGN_IN) {
            Task<GoogleSignInAccount> task = GoogleSignIn.getSignedInAccountFromIntent(data);
            handleSignInResult(task);
        }
    }

    public static void logOut()
    {
        Log.d(TAG, "Google LogOut()");
        sSignInClient.signOut();
    }

    public static String getAuthToken()
    {
        GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(sActivity);
        if (isSignedIn(account)) {
            return account.getIdToken();
        }
        return "";
    }

    private static boolean isSignedIn(GoogleSignInAccount account) {
        return account != null &&
                account.getIdToken() != null &&
                !account.isExpired() &&
                GoogleSignIn.hasPermissions(account, account.getRequestedScopes().toArray(new Scope[account.getRequestedScopes().size()]));
    }

    private void handleSignInResult(Task<GoogleSignInAccount> completedTask) {
        try {
            final GoogleSignInAccount account = completedTask.getResult(ApiException.class);
            onSignInComplete(account);
        } catch (final ResolvableApiException e) {
            sActivity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    try {
                        e.startResolutionForResult(sActivity, RC_RESOLVE);
                    } catch (final IntentSender.SendIntentException ie) {
                        onSignInFailure(LoginState.ERROR.ordinal(), "SendIntentException", ie.getLocalizedMessage(), -1);
                    }
                }
            });
        } catch (final ApiException e) {
            // The ApiException status code indicates the detailed failure reason.
            // Please refer to the GoogleSignInStatusCodes class reference for more information.
            int loginStatus = 0;

            if (e.getStatusCode() == GoogleSignInStatusCodes.SIGN_IN_CURRENTLY_IN_PROGRESS) {
                SignIn();
                return;
            }
            if (e.getStatusCode() == GoogleSignInStatusCodes.CANCELED || e.getStatusCode() == GoogleSignInStatusCodes.SIGN_IN_CANCELLED) {
                loginStatus = LoginState.CANCELLED.ordinal();
            } else {
                checkPlayServices();
                loginStatus = LoginState.ERROR.ordinal();
            }
            final int lStatus = loginStatus;
            Log.w(TAG, "signInResult:failed code=" + e.getStatusCode());
            onSignInFailure(lStatus, "", e.getLocalizedMessage(), e.getStatusCode());
        }

    }
    private void checkPlayServices(){
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GoogleApiAvailability gaa = GoogleApiAvailability.getInstance();
                int result = gaa.isGooglePlayServicesAvailable(sActivity);
                Log.d(TAG, "isGooglePlayServicesAvailable returned " + result);
                if (result != ConnectionResult.SUCCESS) {
                    if (gaa.isUserResolvableError(result)) {
                        gaa.getErrorDialog(sActivity, result, RC_RESOLVE).show();
                    }
                }
            }
        });
    }

    private void onSignInComplete(final GoogleSignInAccount account) {
        CocosHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                onComplete(LoginState.SUCCESS.ordinal(), account.getIdToken(), "", GoogleSignInStatusCodes.SUCCESS);
            }
        });
    }
    private void onSignInFailure(final int status, final String error, final String errorMessage, final int errorCode) {
        CocosHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                onComplete(status,error, errorMessage, errorCode);
            }
        });
    }

    private native void onComplete(int loginState, String string, String errorMsg, int errorCode);
}
