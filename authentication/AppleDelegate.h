#ifndef AppleDelegate_h
#define AppleDelegate_h

#include "controller/apple_login_delegate.h"
#include <string>

class AppleDelegate : public authentication::AppleLoginDelegate
{
public:
    AppleDelegate();
    virtual void SignIn(bool autoLogin, authentication::TokenNonceCallback) override;
    virtual bool IsSupported() override;
    virtual void CheckAndGetAuthToken(authentication::AuthTokenCheckCallback callback) override;
    virtual const std::string GetAuthToken() override;
    virtual const std::string GetNonce() override;
    virtual bool HasLoggedIn() override;
    virtual void LogOut() override;
    static void OnSignIn(authentication::LoginState loginState,
                         const std::string& token,
                         const std::string& nonce,
                         const std::string& errorMsg,
                         int errorCode);
};

#endif /* AppleDelegate_h */

