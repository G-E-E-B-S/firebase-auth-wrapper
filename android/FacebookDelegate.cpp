#include "authentication/FacebookDelegate.h"
#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif
#include "logger/log.h"
#include <vector>
static FacebookDelegate* sInstance = nullptr;
static authentication::TokenCallback sCallback = nullptr;
#define  LOG_TAG    "FacebookDelegate"

namespace {
    void fetchAuthToken(const std::string& className, const std::string& methodName, const std::string& signature,const std::vector<std::string> persmissions) {
        auto env = JniHelper::getEnv();
        jobjectArray params = env->NewObjectArray(persmissions.size(), env->FindClass("java/lang/String"), 0);
        for (auto idx = 0; idx < persmissions.size(); idx++) {
            auto elem = env->NewStringUTF(persmissions[idx].c_str());
            env->SetObjectArrayElement(params,idx, elem);
        }
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, params);
            t.env->DeleteLocalRef(t.classID);
            env->DeleteLocalRef(params);
        } else {
            logger::log("Failed to find static java method. Class name: %s, method name: %s, signature: %s ",  className.c_str(), methodName.c_str(), signature.c_str());
        }
    }
    const std::string getAuthToken(const std::string& className, const std::string& methodName, const std::string& signature,const std::vector<std::string> persmissions, bool  checkValidity) {
        auto env = JniHelper::getEnv();
        jobjectArray params = env->NewObjectArray(persmissions.size(), env->FindClass("java/lang/String"), 0);
        for (auto idx = 0; idx < persmissions.size(); idx++) {
            auto elem = env->NewStringUTF(persmissions[idx].c_str());
            env->SetObjectArrayElement(params,idx, elem);
        }
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, params, checkValidity);
            auto ret = JniHelper::jstring2string(jret);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jret);
            env->DeleteLocalRef(params);
            return ret;
        } else {
            logger::log("Failed to find static java method. Class name: %s, method name: %s, signature: %s ",  className.c_str(), methodName.c_str(), signature.c_str());
            return "";
        }
    }
}
FacebookDelegate::FacebookDelegate() {
    sInstance = this;
}

void FacebookDelegate::FetchAuthToken(authentication::TokenCallback callback, const std::vector<std::string> persmissions)
{

    sCallback = callback;
    fetchAuthToken("com/wrapper/FacebookDelegate", "fetchAuthToken", "([Ljava/lang/String;)V", persmissions);
}

const std::string FacebookDelegate::GetAuthToken(bool checkValidity)
{
    return JniHelper::callStaticStringMethod("com/wrapper/nativeauthentication/FacebookDelegate", "getAuthToken", checkValidity);
}

void FacebookDelegate::FetchUserName()
{
    JniHelper::callStaticVoidMethod("com/wrapper/nativeauthentication/FacebookDelegate", "fetchUserName");
}

const std::string FacebookDelegate::GetUserName()
{
    return JniHelper::callStaticStringMethod("com/wrapper/nativeauthentication/FacebookDelegate", "getUserName");
}

const bool FacebookDelegate::IsTokenActive()
{
    return JniHelper::callStaticBooleanMethod("com/wrapper/nativeauthentication/FacebookDelegate", "isTokenActive");
}

void FacebookDelegate::LogOut()
{
    JniHelper::callStaticVoidMethod("com/wrapper/nativeauthentication/FacebookDelegate", "logOut");
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_wrapper_nativeauthentication_FacebookDelegate_onComplete(JNIEnv *env, jobject obj,
                                                                     int j_state,
                                                                     jstring token,
                                                                     jstring errorMsg,
                                                                     int errorCode)
    {
        logger::log("OnComplete with state %d\n", j_state);
        if (sCallback) {
            auto state = static_cast<authentication::LoginState>(j_state);
            sCallback(state,
                      JniHelper::jstring2string(token),
                      JniHelper::jstring2string(errorMsg),
                      errorCode);
        }
    }
}
