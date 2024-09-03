#ifndef AUTHENTICATION_USER_CONTROLLER_H
#define AUTHENTICATION_USER_CONTROLLER_H

#include "firebase/auth.h"
#include "authentication/controller/login_delegate.h"
#include "include/firebase_app_getter.h"
#include "authentication/models/user_info.h"
#include <memory>
#include <string>
#include <vector>


class FacebookDelegate;
class GoogleDelegate;
namespace firebase {
    class App;
}
namespace authentication
{
    class AppleLoginDelegate;
    class AuthStateListener;

    enum LoginType {
        NONE,
        ANONYMOUS,
        FACEBOOK,
        FACEBOOK_GAMING,
        GOOGLE,
        APPLE
    };
    class AuthenticationController {
    public:
        AuthenticationController(wrapper::jsbhelper::IFirebaseAppGetter* getter,
                                 FacebookDelegate* fbDelegate,
                                 GoogleDelegate* googleDelegate,
                                 AppleLoginDelegate* appleDelegate);
        UserInfo* getUserInfo() {
            return &_userInfo;
        }

        std::shared_ptr<LoginDelegate> getLoginDelegate() {
            return _loginDelegate;
        }
        void setLoginDelegate(LoginDelegate* delegate) {
            _loginDelegate.reset(delegate);
        }

        bool isAppleSignInSupported();

        /**
         * @param autoSignIn true if this is called automatically
         * on login.
         */
        void SignInAnonymously(bool autoSignIn);
        /**
         * @param autoSignIn true if this is called automatically
         * on login.
         */
        void SignInFacebook(bool autoSignIn, const std::vector<std::string> permissions);
        
        void OnGGFirebaseTokenReceived(std::string ggFirebaseToken);
        
        void SignInGoogle(bool autoSignIn);

        void SignInApple(bool autoSignIn);
        void onAppleCredentialsUpdated(const firebase::auth::SignInResult* result);

        void SignInOnLinkFail(int type);

        bool isAutoSignIn() {
            return _autoSignIn;
        }

        bool isLoggedInAnonymous();

        bool isLoggedInFB();
        bool isLoggedInFBGaming();
        
        bool isLoggedInGoogle();

        bool isLoggedInApple();

        void fetchToken();
        const std::string getToken();

        std::string getUserID();

        std::string getUserDisplayName();
        
        std::string getUserPhotoUrl();
        
        firebase::auth::UserInfoInterface* getFacebookProfile();
        
        std::string getFacebookAccessToken();
        
        std::string getFacebookUserId() {
            auto fbProfile = this->getFacebookProfile();
            if (fbProfile) {
                return fbProfile->uid();
            }
            return "";
        }
        
        std::string getGoogleUserId() {
            auto googleProfile = this->getGoogleProfile();
            if (googleProfile) {
                return googleProfile->uid();
            }
            return "";
        }

        void tryInit();

        bool canLogOut();

        bool isGuestEnabled();
        
        bool canSendEmail();

        bool canManuallySignin();

        void signOut() {
            if (isLoggedInFB()) {
                logOutFB();
            } else  if (isLoggedInGoogle()) {
                logOutGoogle();
            } else if (isLoggedInApple()) {
                logOutApple();
            }
            _auth->SignOut();
        }
        
        void logOutFB();
        
        void logOutGoogle();

        void logOutApple();
        
        bool isReady() {
            return _isReady;
        }
        ~AuthenticationController();
    private:
        void linkOrSignInFB(firebase::auth::Credential);
        void linkOrSignInGoogle(firebase::auth::Credential);
        void linkOrSignInApple(firebase::auth::Credential);
        void signInGoogleOnLinkFailure();
        void processGGToken(const std::string& token);
        firebase::auth::UserInfoInterface* getProviderProfile(const std::string &providerId);
        firebase::auth::UserInfoInterface* getGoogleProfile();
        firebase::auth::UserInfoInterface* getAppleProfile();
        bool _autoSignIn;
        std::unique_ptr<AuthStateListener> _authListener;
        UserInfo _userInfo;
        firebase::auth::Auth* _auth;
        std::shared_ptr<LoginDelegate> _loginDelegate;
        std::shared_ptr<FacebookDelegate> _fbDelegate;
        std::shared_ptr<GoogleDelegate> _googleDelegate;
        std::shared_ptr<AppleLoginDelegate> _appleDelegate;
        bool _isReady;
        firebase::App* _app;
        std::vector<std::string> _fbPermissions;
        std::string _idToken;
        std::string _userIdToConnect;
    };
}
#endif // AUTHENTICATION_USER_CONTROLLER_H
