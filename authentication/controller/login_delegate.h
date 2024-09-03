#ifndef AUTHENTICATION_LOGIN_DELEGATE_H
#define AUTHENTICATION_LOGIN_DELEGATE_H

#include <string>

namespace authentication {
    enum class LoginState {
        SUCCESS,
        CANCELLED,
        ERROR
    };
    typedef std::function<void(LoginState state,
                               const std::string& token,
                               const std::string& errorMsg,
                               int errorCode)> TokenCallback;
    typedef std::function<void(LoginState state,
                            const std::string& token,
                            const std::string& nonce,
                            const std::string& errorMsg,
                            int errorCode)> TokenNonceCallback;
    typedef std::function<void(
            const std::string& token,
            const std::string& nonce)> AuthTokenCheckCallback;
    class LoginDelegate
    {
    public:
        virtual bool OnSuccess() = 0;
        virtual bool OnCancel() = 0;
        virtual bool OnFailure(int error_code, std::string error_msg) = 0;
        virtual bool OnLinkAccountFail(int error_code, std::string error_msg) = 0;
        virtual bool OnFbGamingLogin(std::string ggToken, std::string userIdToConnectTo) = 0;
        virtual ~LoginDelegate() {};
    };
}

#endif // AUTHENTICATION_LOGIN_DELEGATE_H
