#include "controller.h"
#include "logger/log.h"
#include <firebase/auth.h>

#include <memory>
#include "authentication/firebase/auth_state_listener.h"
#include "authentication/FacebookDelegate.h"
#include "authentication/GoogleDelegate.h"
#include "authentication/controller/apple_login_delegate.h"

using namespace firebase::auth;

typedef firebase::Future<firebase::auth::User*> UserFuture;
typedef firebase::Future<void> VoidFuture;
typedef firebase::Future<firebase::auth::SignInResult> LinkResultFuture;

namespace authentication
{
    bool isGGToken(const std::string &tokenStr)
    {
        return tokenStr[0] == 'G' && tokenStr[1] == 'G';
    }
    void handleSuccess(AuthenticationController *controller)
    {
        auto loginDelegate = controller->getLoginDelegate();
        loginDelegate->OnSuccess();
    }

    void onAuthResult(const UserFuture &result, void *user_data)
    {
        if (result.status() != firebase::kFutureStatusComplete)
        {
            return;
        }
        // TODO: handle fb link failure
        auto controller = static_cast<AuthenticationController *>(user_data);
        auto loginDelegate = controller->getLoginDelegate();
        if (result.error() == firebase::auth::kAuthErrorNone)
        {
            handleSuccess(controller);
            return;
        }
        logger::log("Created user failed with error '%s'\n", result.error_message());
        logger::log("onAuthResult: Something went wrong: %d", result.status());

        loginDelegate->OnFailure(result.error(), result.error_message());
    }

    void onReAuthResult(const VoidFuture &result, void *user_data)
    {
        if (result.status() != firebase::kFutureStatusComplete)
        {
            return;
        }
        auto controller = static_cast<AuthenticationController *>(user_data);
        if (result.error() == firebase::auth::kAuthErrorNone)
        {
            handleSuccess(controller);
            return;
        }
        controller->SignInApple(false);
        logger::log("onReAuthResult: Something went wrong: %d", result.error());
        logger::log("onReAuthResult failed with error '%s'\n", result.error_message());
    }

    void onAuthResultOnLinkFail(const UserFuture &result, void *user_data)
    {
        if (result.status() != firebase::kFutureStatusComplete)
        {
            return;
        }
        // TODO: handle fb link failure
        auto controller = static_cast<AuthenticationController *>(user_data);
        auto loginDelegate = controller->getLoginDelegate();
        if (result.error() == firebase::auth::kAuthErrorNone)
        {
            handleSuccess(controller);
            return;
        }
        logger::log("Created user failed with error '%s'\n", result.error_message());
        logger::log("onAuthResult: Something went wrong: %d", result.status());
        loginDelegate->OnFailure(result.error(), result.error_message());
    }

    void onLinkResult(const UserFuture &result, void *user_data)
    {
        if (result.status() != firebase::kFutureStatusComplete)
        {
            return;
        }
        auto controller = static_cast<AuthenticationController *>(user_data);
        auto loginDelegate = controller->getLoginDelegate();
        if (result.error() == firebase::auth::kAuthErrorNone)
        {
            handleSuccess(controller);
            return;
        }
        if (result.error() == firebase::auth::kAuthErrorProviderAlreadyLinked ||
            result.error() == firebase::auth::kAuthErrorCredentialAlreadyInUse ||
            result.error() == firebase::auth::kAuthErrorAccountExistsWithDifferentCredentials ||
            result.error() == firebase::auth::kAuthErrorEmailAlreadyInUse)
        {
            loginDelegate->OnLinkAccountFail(result.error(), result.error_message());
        }
        else
        {
            loginDelegate->OnFailure(result.error(), result.error_message());
        }
    }

    void onAppleLinkResult(const LinkResultFuture &result, void *user_data)
    {
        if (result.status() != firebase::kFutureStatusComplete)
        {
            return;
        }
        auto controller = static_cast<AuthenticationController *>(user_data);
        auto loginDelegate = controller->getLoginDelegate();
        if (result.error() == firebase::auth::kAuthErrorNone)
        {
            handleSuccess(controller);
            return;
        }
        if (result.error() == firebase::auth::kAuthErrorCredentialAlreadyInUse &&
            result.result()->info.updated_credential.is_valid())
        {
            controller->onAppleCredentialsUpdated(result.result());
        } else if (result.error() == firebase::auth::kAuthErrorProviderAlreadyLinked ||
                 result.error() == firebase::auth::kAuthErrorAccountExistsWithDifferentCredentials ||
                 result.error() == firebase::auth::kAuthErrorEmailAlreadyInUse)
        {
            loginDelegate->OnLinkAccountFail(result.error(), result.error_message());
        }
        else
        {
            loginDelegate->OnFailure(result.error(), result.error_message());
        }
    }

    void AuthenticationController::tryInit() {
        if (isReady()) {
            return;
        }
        if (!_app) {
            return;
        }
        firebase::InitResult initResult;
        _auth = firebase::auth::Auth::GetAuth(_app, &initResult);
        _isReady = initResult == firebase::kInitResultSuccess;
    }

    AuthenticationController::AuthenticationController(wrapper::jsbhelper::IFirebaseAppGetter* getter,
                                                       FacebookDelegate *fbDelegate,
                                                       GoogleDelegate *googleDelegate,
                                                       AppleLoginDelegate *appleDelegate)
    {
        _auth = nullptr;
        _isReady = false;
        _authListener = std::make_unique<AuthStateListener>();
        _fbDelegate.reset(fbDelegate);
        _googleDelegate.reset(googleDelegate);
        _appleDelegate.reset(appleDelegate);
        _app = getter->getApp();
        tryInit();
        if (_auth)
        {
            _auth->AddAuthStateListener(_authListener.get());
        }
        else
        {
            logger::log("Auth object is null, auth failed\n");
        }
    }

    void AuthenticationController::SignInAnonymously(bool autoSignIn)
    {
        if (!_auth)
        {
            return;
        }
        _autoSignIn = autoSignIn;
        auto result = _auth->SignInAnonymously();
        result.OnCompletion(onAuthResult, this);
    }

    void AuthenticationController::SignInOnLinkFail(int type)
    {
        if (!_auth)
        {
            return;
        }
        Credential credential;
        if (type == (int)LoginType::FACEBOOK)
        {
            credential = FacebookAuthProvider::GetCredential(_fbDelegate->GetAuthToken(false).c_str());
            auto result = _auth->SignInWithCredential(credential);
            result.OnCompletion(onAuthResultOnLinkFail, this);
        }
        else if (type == (int)LoginType::GOOGLE)
        {
            signInGoogleOnLinkFailure();
        }
        else
        {
            // NOTE: It shouldn't come here, as for apple, it will have been handled before
            logger::log("SignInOnLinkFail: uknown link type %d", type);
        }
    }
    void AuthenticationController::signInGoogleOnLinkFailure()
    {
        auto token = _googleDelegate->GetAuthToken();
        if (token.size() == 0)
        {
            auto lambda = [this](LoginState state,
                                 const std::string &token,
                                 const std::string &errorMsg,
                                 int errorCode)
            {
                if (state == LoginState::SUCCESS)
                {
                    auto credential = _googleDelegate->getCredential(token);
                    auto result = _auth->SignInWithCredential(credential);
                    result.OnCompletion(onAuthResultOnLinkFail, this);
                }
                else if (state == LoginState::CANCELLED)
                {
                    _loginDelegate->OnCancel();
                }
                else
                {
                    _loginDelegate->OnFailure(errorCode, errorMsg);
                }
            };
            _googleDelegate->SignIn(true, lambda);
        }
        else
        {
            auto credential = _googleDelegate->getCredential(token);
            auto result = _auth->SignInWithCredential(credential);
            result.OnCompletion(onAuthResultOnLinkFail, this);
        }
    }

    void AuthenticationController::SignInFacebook(bool autoSignIn, const std::vector<std::string> permissions)
    {
        _autoSignIn = autoSignIn;
        _fbPermissions = permissions;
        auto token = _fbDelegate->GetAuthToken(true);
        if (token.size() == 0)
        {
            _fbDelegate->FetchAuthToken([this](LoginState state,
                                               const std::string &token,
                                               const std::string &errorMsg,
                                               int errorCode)
                                        {
                if (state == LoginState::SUCCESS) {
                    processGGToken(token);
                } else if (state == LoginState::CANCELLED) {
                    _loginDelegate->OnCancel();
                } else {
                    _loginDelegate->OnFailure(errorCode, errorMsg);
                } },
                                        permissions);
        }
        else
        {
            processGGToken(token);
        }
    }

    void AuthenticationController::processGGToken(const std::string& tokenStr)
    {
        if (isGGToken(tokenStr))
        {
            std::string userIdToConnect;
            if (_userIdToConnect.size() > 0)
            {
                userIdToConnect = _userIdToConnect;
                _userIdToConnect = "";
            }
            else if (!_autoSignIn)
            {
                userIdToConnect = getUserID();
            }
            _loginDelegate->OnFbGamingLogin(tokenStr,
                                            userIdToConnect);
            _fbDelegate->FetchUserName();
        }
        else
        {
            // NOTE: This will happen on app update, where user is signed in to nongg fb
            _userIdToConnect = getUserID();
            signOut();
            _fbDelegate->LogOut();
            SignInFacebook(false, _fbPermissions);
        }
    }

    void AuthenticationController::OnGGFirebaseTokenReceived(std::string ggFirebaseToken)
    {
        auto result = _auth->SignInWithCustomToken(ggFirebaseToken.c_str());
        result.OnCompletion(onAuthResult, this);
    }

    void AuthenticationController::SignInGoogle(bool autoSignIn)
    {
        _autoSignIn = autoSignIn;
        auto token = _googleDelegate->GetAuthToken();
        if (token.size() == 0)
        {
            auto lambda = [this](LoginState state,
                                 const std::string &token,
                                 const std::string &errorMsg,
                                 int errorCode)
            {
                if (state == LoginState::SUCCESS)
                {
                    auto credential = _googleDelegate->getCredential(token);
                    linkOrSignInGoogle(credential);
                }
                else if (state == LoginState::CANCELLED)
                {
                    _loginDelegate->OnCancel();
                }
                else
                {
                    _loginDelegate->OnFailure(errorCode, errorMsg);
                }
            };
            _googleDelegate->SignIn(autoSignIn, lambda);
        }
        else
        {
            auto credential = _googleDelegate->getCredential(token);
            linkOrSignInGoogle(credential);
        }
    }

    void AuthenticationController::SignInApple(bool autoSignIn)
    {
        _autoSignIn = autoSignIn;
        auto lambda = [this](LoginState state,
                             const std::string &token,
                             const std::string &nonce,
                             const std::string &errorMsg,
                             int errorCode)
        {
            if (state == LoginState::SUCCESS)
            {
                auto credential = OAuthProvider::GetCredential("apple.com", token.c_str(), nonce.c_str(), nullptr);
                linkOrSignInApple(credential);
            }
            else if (state == LoginState::CANCELLED)
            {
                _loginDelegate->OnCancel();
            }
            else
            {
                _loginDelegate->OnFailure(errorCode, errorMsg);
            }
        };
        _appleDelegate->SignIn(autoSignIn, lambda);
    }

    void AuthenticationController::linkOrSignInFB(Credential credential)
    {
        if (!_auth)
        {
            return;
        }
        auto user = _auth->current_user();
        if (isLoggedInGoogle() || isLoggedInApple() || isLoggedInAnonymous())
        {
            logger::log("Link between accounts\n");
            auto result = user->LinkWithCredential(credential);
            result.OnCompletion(onLinkResult, this);
        }
        else
        {
            logger::log("No anon user, log in to facebook");
            auto result = _auth->SignInWithCredential(credential);
            result.OnCompletion(onAuthResult, this);
        }
    }

    void AuthenticationController::linkOrSignInGoogle(Credential credential)
    {
        if (!_auth)
        {
            return;
        }
        auto user = _auth->current_user();
        if (isLoggedInFB() || isLoggedInApple() || isLoggedInAnonymous())
        {
            logger::log("Link between accounts\n");
            auto result = user->LinkWithCredential(credential);
            result.OnCompletion(onLinkResult, this);
        }
        else
        {
            logger::log("No anon user, log in to google");
            auto result = _auth->SignInWithCredential(credential);
            result.OnCompletion(onAuthResult, this);
        }
    }

    void AuthenticationController::linkOrSignInApple(Credential credential)
    {
        if (!_auth)
        {
            return;
        }
        auto user = _auth->current_user();
        if (isLoggedInFB() || isLoggedInGoogle() || isLoggedInAnonymous())
        {
            logger::log("Apple login Link between accounts\n");
            auto result = user->LinkAndRetrieveDataWithCredential(credential);
            result.OnCompletion(onAppleLinkResult, this);
        }
        else
        {
            logger::log("No anon user, log in to Apple");
            auto result = _auth->SignInWithCredential(credential);
            result.OnCompletion(onAuthResult, this);
        }
    }

    void AuthenticationController::onAppleCredentialsUpdated(const firebase::auth::SignInResult* result)
    {
        auto credential =  result->info.updated_credential;
        auto response = _auth->SignInWithCredential(credential);
        response.OnCompletion(onAuthResultOnLinkFail, this);
    }

    bool AuthenticationController::isLoggedInAnonymous()
    {
        if (!_auth)
        {
            return false;
        }
        auto user = _auth->current_user();
        return user && user->is_anonymous();
    }

    bool AuthenticationController::isLoggedInFB()
    {
        if (!_auth)
        {
            return false;
        }
        auto user = _auth->current_user();
        return user && !user->is_anonymous() && _fbDelegate->IsTokenActive();
    }
    bool AuthenticationController::isLoggedInFBGaming()
    {
        if (isLoggedInFB())
        {
            return isGGToken(_fbDelegate->GetAuthToken(false));
        }
        return false;
    }

    bool AuthenticationController::canLogOut()
    {
        return !this->isLoggedInAnonymous();
    }

    bool AuthenticationController::isGuestEnabled()
    {
        return true;
    }

    bool AuthenticationController::canSendEmail()
    {
        return true;
    }

    bool AuthenticationController::canManuallySignin()
    {
        return true;
    }

    bool AuthenticationController::isLoggedInGoogle()
    {
        if (!_auth)
        {
            return false;
        }
        auto user = _auth->current_user();
        return user && !user->is_anonymous() && _googleDelegate->HasLoggedIn();
    }

    bool AuthenticationController::isLoggedInApple()
    {
        if (!_auth)
        {
            return false;
        }
        auto user = _auth->current_user();
        return user && !user->is_anonymous() && _appleDelegate->HasLoggedIn();
    }

    void AuthenticationController::fetchToken()
    {
        auto user = _auth->current_user();
        if (user != nullptr)
        {
            user->GetToken(true).OnCompletion([this](const firebase::Future<std::string> result)
                                              {
                if (result.status() == firebase::kFutureStatusComplete) {
                    _idToken = *result.result();
                } else {
                    logger::log("Failed fetching token %d", result.status());
                } });
        }
    }
    const std::string AuthenticationController::getToken()
    {
        return _idToken;
    }

    std::string AuthenticationController::getUserID()
    {
        if (!_auth)
        {
            return "";
        }
        auto user = _auth->current_user();
        if (user)
        {
            return user->uid();
        }
        return "";
    }

    std::string AuthenticationController::getUserDisplayName()
    {
        if (!_auth)
        {
            return "";
        }
        UserInfoInterface *profile = nullptr;
        if (isLoggedInGoogle())
        {
            profile = this->getGoogleProfile();
        }
        else if (isLoggedInFBGaming())
        {
            return _fbDelegate->GetUserName();
        }
        else if (isLoggedInFB())
        {
            profile = this->getFacebookProfile();
        }
        else if (isLoggedInApple())
        {
            profile = this->getAppleProfile();
        }
        if (profile != nullptr)
        {
            return profile->display_name();
        }
        auto user = _auth->current_user();
        if (user)
        {
            return user->display_name();
        }
        return "";
    }

    std::string AuthenticationController::getUserPhotoUrl()
    {
        if (!_auth)
        {
            return "";
        }
        auto user = _auth->current_user();
        std::string url = "";
        if (user)
        {
            UserInfoInterface *profile = nullptr;
            if (isLoggedInGoogle())
            {
                profile = getGoogleProfile();
                if (profile != nullptr && profile->photo_url().size() > 0)
                {
                    return profile->photo_url();
                }
                return user->photo_url();
            }
            if (isLoggedInApple())
            {
                profile = getAppleProfile();
                if (profile != nullptr && profile->photo_url().size() > 0)
                {
                    return profile->photo_url();
                }
                return user->photo_url();
            }
            if (isLoggedInFB())
            {
                profile = getFacebookProfile();
            }
            if (profile != nullptr)
            {
                url += "https://graph.fb.gg/v11.0/me/picture?access_token=";
                url += _fbDelegate->GetAuthToken(false).c_str();
                logger::log("--->>>> getUserPhotoUrl() url from facebook profile: %s", url.c_str());
                return url;
            }
            else
            {
                logger::log("--->>>> getUserPhotoUrl() no facebook profile associated with user!");
                return user->photo_url();
            }
        }
        else
        {
            logger::log("--->>>> getUserPhotoUrl() no user in auth!!!");
        }
        return url;
    }

    UserInfoInterface *AuthenticationController::getProviderProfile(const std::string &providerId)
    {
        if (!_auth)
        {
            return nullptr;
        }
        auto user = _auth->current_user();
        if (user)
        {
            logger::log("getProviderProfile provider_id: %s", user->provider_id().c_str());
            auto profiles = user->provider_data();
            for (auto iter = profiles.begin(); iter != profiles.end(); ++iter)
            {
                logger::log("--->>>> Provider id: %s", (*iter)->provider_id().c_str());
                if ((*iter)->provider_id() == providerId)
                {
                    return *iter;
                }
            }
        }
        return nullptr;
    }

    UserInfoInterface *AuthenticationController::getFacebookProfile()
    {
        return this->getProviderProfile("oidc.fb_gg");
    }

    UserInfoInterface *AuthenticationController::getGoogleProfile()
    {
        return this->getProviderProfile("google.com");
    }

    UserInfoInterface *AuthenticationController::getAppleProfile()
    {
        return this->getProviderProfile("apple.com");
    }
    void AuthenticationController::logOutFB() {
        auto user = _auth->current_user();
        _fbDelegate->LogOut();
        logger::log("LogOutFB()");
    }

    void AuthenticationController::logOutGoogle() {
        auto user = _auth->current_user();
        _googleDelegate->LogOut();
        logger::log("LogOutGoogle()");
    }
    std::string AuthenticationController::getFacebookAccessToken() {
        return _fbDelegate->GetAuthToken(false);
    }
    bool AuthenticationController::isAppleSignInSupported() {
        return _appleDelegate->IsSupported();
    }
    void AuthenticationController::logOutApple() {
        _appleDelegate->LogOut();
    }
    AuthenticationController::~AuthenticationController() {}
}
