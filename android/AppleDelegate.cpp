#include "authentication/AppleDelegate.h"
#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
#else
#include "platform/android/jni/JniHelper.h"
#endif
#include <vector>
static AppleDelegate* sInstance = nullptr;
static authentication::TokenCallback sCallback = nullptr;

AppleDelegate::AppleDelegate() {
    sInstance = this;
}

bool AppleDelegate::IsSupported() {
    return false;
}

void AppleDelegate::OnSignIn(authentication::LoginState loginState,
                              const std::string &token,
                              const std::string& nonce,
                              const std::string& errorMsg,
                              int errorCode)
{
    // NOTE: Do nothing, this is for ios only
}

void AppleDelegate::SignIn(bool autoLogin, authentication::TokenNonceCallback)
{
    // NOTE: Do nothing, this is for ios only
}

void AppleDelegate::CheckAndGetAuthToken(authentication::AuthTokenCheckCallback callback)
{
    // NOTE: Do nothing, this is for ios only
}

const std::string AppleDelegate::GetAuthToken()
{
    return "";
}

const std::string AppleDelegate::GetNonce()
{
    return "";
}

bool AppleDelegate::HasLoggedIn()
{
    return false;
}

void AppleDelegate::LogOut()
{
    // NOTE: Do nothing, this is for ios only
}

