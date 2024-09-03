#import "authentication/GoogleDelegate.h"
#import <GoogleSignIn/GoogleSignIn.h>
#import <Firebase/Firebase.h>

namespace GlDelegate {
authentication::TokenCallback s_authCallback;
GIDConfiguration *signInConfig;
}

GoogleDelegate::GoogleDelegate() {
    GlDelegate::signInConfig = [[GIDConfiguration alloc] initWithClientID:[FIRApp defaultApp].options.clientID];
}

void GoogleDelegate::OnSignIn(authentication::LoginState loginState,
                              const std::string &token,
                              const std::string &errorMSg,
                              int errorCode)
{
    GlDelegate::s_authCallback(loginState,
                               token,
                               errorMSg,
                               errorCode);
}

void GoogleDelegate::SignIn(bool autoSignIn, authentication::TokenCallback callback)
{
    // TODO: handle errors or auto sign in
    GlDelegate::s_authCallback = callback;
    if (autoSignIn) {
        [GIDSignIn.sharedInstance restorePreviousSignInWithCompletion:^(GIDGoogleUser * _Nullable user, NSError * _Nullable error) {
            if (error) {
                OnSignIn(authentication::LoginState::ERROR, "", [error.localizedDescription UTF8String], (int)error.code);
                return;
            }
            OnSignIn(authentication::LoginState::SUCCESS, [[user accessToken].tokenString UTF8String], "", 0);
        }];
    } else {
        [GIDSignIn.sharedInstance signInWithPresentingViewController:[UIApplication sharedApplication].keyWindow.rootViewController completion:^(GIDSignInResult * result, NSError *error) {
            if (error) {
                OnSignIn(authentication::LoginState::ERROR, "", [error.localizedDescription UTF8String], (int)error.code);
                return;
            }
            OnSignIn(authentication::LoginState::SUCCESS, [[result serverAuthCode] UTF8String], "", 0);
        }];
    }
}

const std::string GoogleDelegate::GetAuthToken()
{
    // no-op
    return "";
}

bool GoogleDelegate::HasLoggedIn()
{
    return [GIDSignIn.sharedInstance hasPreviousSignIn];
}

void GoogleDelegate::LogOut()
{
    //    NSLog(@"Google LogOut()");
    [GIDSignIn.sharedInstance signOut];
}

