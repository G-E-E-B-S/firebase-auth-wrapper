#include "authentication/GoogleDelegate.h"
#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif
 #include "logger/log.h"
#include <vector>

#define NATIVE_AUTH_GOOGLE_SIGNIN_CLASSIC 0
#define NATIVE_AUTH_GOOGLE_SIGNIN_PLAY 1

using namespace firebase::auth;

static GoogleDelegate *sInstance = nullptr;
static authentication::TokenCallback sCallback = nullptr;

GoogleDelegate::GoogleDelegate()
{
    sInstance = this;
}

void GoogleDelegate::OnSignIn(authentication::LoginState loginState,
                              const std::string &token,
                              const std::string &errorMsg,
                              int errorCode)
{
    // NOTE: Do nothing, this is for ios only
}

void GoogleDelegate::SignIn(bool autoLogin, authentication::TokenCallback callback)
{
    sCallback = callback;
#if (NATIVE_AUTH_GOOGLE_SIGNIN == NATIVE_AUTH_GOOGLE_SIGNIN_PLAY)
    JniHelper::callStaticVoidMethod("com/wrapper/nativeauthentication/GooglePlayDelegate", "signIn");
#else
    if (autoLogin)
    {
        cocos2d::JniHelper::callStaticVoidMethod("com/wrapper/nativeauthentication/GoogleDelegate", "signInSilently");
    }
    else
    {
        cocos2d::JniHelper::callStaticVoidMethod("com/wrapper/nativeauthentication/GoogleDelegate", "signIn");
    }
#endif
}

const std::string GoogleDelegate::GetAuthToken()
{
#if (NATIVE_AUTH_GOOGLE_SIGNIN == NATIVE_AUTH_GOOGLE_SIGNIN_PLAY)
    return JniHelper::callStaticStringMethod("com/wrapper/nativeauthentication/GooglePlayDelegate", "getAuthToken");
#else
    return JniHelper::callStaticStringMethod("com/wrapper/nativeauthentication/GoogleDelegate", "getAuthToken");
#endif
}

bool GoogleDelegate::HasLoggedIn()
{
#if (NATIVE_AUTH_GOOGLE_SIGNIN == NATIVE_AUTH_GOOGLE_SIGNIN_PLAY)
    return JniHelper::callStaticBooleanMethod("com/wrapper/nativeauthentication/GooglePlayDelegate", "hasLoggedIn");
#else
    return GetAuthToken() != "";
#endif
}

void GoogleDelegate::LogOut()
{
#if (NATIVE_AUTH_GOOGLE_SIGNIN == NATIVE_AUTH_GOOGLE_SIGNIN_PLAY)
// no-op
#else
    cocos2d::JniHelper::callStaticVoidMethod("com/wrapper/nativeauthentication/GoogleDelegate", "logOut");
#endif
}

extern "C"
{
#if (NATIVE_AUTH_GOOGLE_SIGNIN == NATIVE_AUTH_GOOGLE_SIGNIN_PLAY)
    JNIEXPORT void JNICALL Java_com_wrapper_nativeauthentication_GooglePlayDelegate_onComplete(
#else
    JNIEXPORT void JNICALL Java_com_wrapper_nativeauthentication_GoogleDelegate_onComplete(
#endif
        JNIEnv *env,
        jobject obj,
        int j_state,
        jstring token,
        jstring errorMsg,
        jint errorCode)
    {
        logger::log("GoogleDelegate OnComplete with state %d\n", j_state);
        if (sCallback)
        {
            auto state = static_cast<authentication::LoginState>(j_state);
            sCallback(state,
                      JniHelper::jstring2string(token),
                      JniHelper::jstring2string(errorMsg),
                      errorCode);
        }
    }
}
