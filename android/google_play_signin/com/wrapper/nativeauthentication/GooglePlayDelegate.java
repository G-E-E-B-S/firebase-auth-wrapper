package com.wrapper.nativeauthentication;

import android.app.Activity;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.games.AuthenticationResult;
import com.google.android.gms.games.GamesSignInClient;
import com.google.android.gms.games.PlayGames;
import com.google.android.gms.games.PlayGamesSdk;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

enum LoginState {
    SUCCESS,
    CANCELLED,
    ERROR
}
public class GooglePlayDelegate implements OnCompleteListener<AuthenticationResult> {
    private static String TAG = "GooglePlayDelegate";
    private static IThreadHelper sThreadHelper;
    private static Activity sActivity;
    private static String sWebClientId;
    private static String sAuthToken = "";
    private static GooglePlayDelegate sIntance;
    private static boolean sLoggedIn = false;
    private static boolean initialised = false;
    public GooglePlayDelegate(Activity activity, IThreadHelper threadHelper, String webClientId) {
        sIntance = this;
        sActivity = activity;
        sThreadHelper = threadHelper;
        sWebClientId = webClientId;
    }
    public static void signIn()
    {
        sThreadHelper.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (!initialised) {
                    PlayGamesSdk.initialize(sActivity);
                    initialised = true;
                }
                GamesSignInClient gamesSignInClient = PlayGames.getGamesSignInClient(sActivity);
                gamesSignInClient.requestServerSideAccess(sWebClientId, false).addOnCompleteListener(new OnCompleteListener<String>() {
                    @Override
                    public void onComplete(@NonNull Task<String> task) {
                        if (task.isSuccessful()) {
                            sLoggedIn = true;
                            sAuthToken = task.getResult();
                            sIntance.onResponse(LoginState.SUCCESS.ordinal(), sAuthToken, "", LoginState.SUCCESS.ordinal());
                        } else if (task.isCanceled()) {
                            sIntance.onResponse(LoginState.CANCELLED.ordinal(), "", "", LoginState.CANCELLED.ordinal());
                        } else {
                            sIntance.onResponse(LoginState.ERROR.ordinal(), "", task.getException().getLocalizedMessage(), -1);
                        }
                    }
                });
            }
        });
    }
    public static String getAuthToken() {
        return "";
    }
    public static boolean hasLoggedIn() {
        return sLoggedIn;
    }
    public static void logOut() {
        // no -op sdk handles logout itself
    }
    private void onResponse(int loginState, String token, String errorMsg, int errorCode) {
        sThreadHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                onComplete(loginState, token, errorMsg, errorCode);
            }
        });
    }
    private native void onComplete(int loginState, String token, String errorMsg, int errorCode);

    @Override
    public void onComplete(@NonNull Task<AuthenticationResult> task) {
        if (task.isSuccessful() && task.getResult().isAuthenticated()) {
            Log.d(TAG, "onComplete");
        }
    }
}
