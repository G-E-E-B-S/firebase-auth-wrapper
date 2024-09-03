#ifndef AUTHENTICATION_APPLE_LOGIN_DELEGATE_H
#define AUTHENTICATION_APPLE_LOGIN_DELEGATE_H

#include <functional>
#include <string>
#include <vector>
#include "login_delegate.h"

namespace authentication {
    class AppleLoginDelegate {
    public:
        virtual ~AppleLoginDelegate() {};
        virtual bool IsSupported() = 0;
        virtual const std::string GetAuthToken() = 0;
        virtual const std::string GetNonce() = 0;
        virtual void CheckAndGetAuthToken(authentication::AuthTokenCheckCallback callback) = 0;
        virtual void SignIn(bool, TokenNonceCallback) = 0;
        virtual bool HasLoggedIn() = 0;
        virtual void LogOut() = 0;
    };
} // authentication

#endif // AUTHENTICATION_APPLE_LOGIN_DELEGATE_H

