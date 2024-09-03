#ifndef GoogleDelegate_h
#define GoogleDelegate_h

#include <string>
#include "firebase/auth.h"
#include "controller/login_delegate.h"

class GoogleDelegate
{
public:
    GoogleDelegate();
    void SignIn(bool autoLogin, authentication::TokenCallback);
    const std::string GetAuthToken();
    bool HasLoggedIn();
    void LogOut();
    const firebase::auth::Credential getCredential(const std::string& token) {
    #if (NATIVE_AUTH_GOOGLE_SIGNIN == NATIVE_AUTH_GOOGLE_SIGNIN_CLASSIC)
        return firebase::auth::GoogleAuthProvider::GetCredential(token.c_str(), nullptr);
    #else
        return firebase::auth::PlayGamesAuthProvider::GetCredential(token.c_str());
    #endif // (NATIVE_AUTH_GOOGLE_SIGNIN == NATIVE_AUTH_GOOGLE_SIGNIN_CLASSIC)
    }
    static void OnSignIn(authentication::LoginState loginState,
                         const std::string& token,
                         const std::string& errorMsg,
                         int errorCode);
private:
};

#endif /* GoogleDelegate_h */

