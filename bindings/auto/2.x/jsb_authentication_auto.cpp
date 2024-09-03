#include "bindings/auto/2.x/jsb_authentication_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "authentication/controller/controller.h"
#include "authentication/PersistentAppData.h"

se::Object* __jsb_authentication_AuthenticationController_proto = nullptr;
se::Class* __jsb_authentication_AuthenticationController_class = nullptr;

static bool js_authentication_AuthenticationController_isReady(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isReady : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isReady();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isReady : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isReady)

static bool js_authentication_AuthenticationController_logOutApple(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_logOutApple : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->logOutApple();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_logOutApple)

static bool js_authentication_AuthenticationController_isLoggedInGoogle(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isLoggedInGoogle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isLoggedInGoogle();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isLoggedInGoogle : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isLoggedInGoogle)

static bool js_authentication_AuthenticationController_canSendEmail(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_canSendEmail : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->canSendEmail();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_canSendEmail : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_canSendEmail)

static bool js_authentication_AuthenticationController_isGuestEnabled(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isGuestEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isGuestEnabled();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isGuestEnabled : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isGuestEnabled)

static bool js_authentication_AuthenticationController_SignInGoogle(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_SignInGoogle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_SignInGoogle : Error processing arguments");
        cobj->SignInGoogle(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_SignInGoogle)

static bool js_authentication_AuthenticationController_getUserPhotoUrl(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getUserPhotoUrl : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getUserPhotoUrl();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getUserPhotoUrl : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getUserPhotoUrl)

static bool js_authentication_AuthenticationController_isAutoSignIn(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isAutoSignIn : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isAutoSignIn();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isAutoSignIn : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isAutoSignIn)

static bool js_authentication_AuthenticationController_tryInit(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_tryInit : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->tryInit();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_tryInit)

static bool js_authentication_AuthenticationController_SignInFacebook(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_SignInFacebook : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        bool arg0;
        std::vector<std::string> arg1;
        ok &= seval_to_boolean(args[0], &arg0);
        ok &= seval_to_std_vector_string(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_SignInFacebook : Error processing arguments");
        cobj->SignInFacebook(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_SignInFacebook)

static bool js_authentication_AuthenticationController_isLoggedInAnonymous(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isLoggedInAnonymous : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isLoggedInAnonymous();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isLoggedInAnonymous : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isLoggedInAnonymous)

static bool js_authentication_AuthenticationController_getUserDisplayName(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getUserDisplayName : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getUserDisplayName();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getUserDisplayName : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getUserDisplayName)

static bool js_authentication_AuthenticationController_SignInAnonymously(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_SignInAnonymously : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_SignInAnonymously : Error processing arguments");
        cobj->SignInAnonymously(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_SignInAnonymously)

static bool js_authentication_AuthenticationController_isLoggedInFB(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isLoggedInFB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isLoggedInFB();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isLoggedInFB : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isLoggedInFB)

static bool js_authentication_AuthenticationController_logOutFB(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_logOutFB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->logOutFB();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_logOutFB)

static bool js_authentication_AuthenticationController_getGoogleUserId(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getGoogleUserId : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getGoogleUserId();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getGoogleUserId : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getGoogleUserId)

static bool js_authentication_AuthenticationController_SignInOnLinkFail(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_SignInOnLinkFail : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= seval_to_int32(args[0], (int32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_SignInOnLinkFail : Error processing arguments");
        cobj->SignInOnLinkFail(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_SignInOnLinkFail)

static bool js_authentication_AuthenticationController_getFacebookAccessToken(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getFacebookAccessToken : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getFacebookAccessToken();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getFacebookAccessToken : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getFacebookAccessToken)

static bool js_authentication_AuthenticationController_fetchToken(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_fetchToken : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->fetchToken();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_fetchToken)

static bool js_authentication_AuthenticationController_isAppleSignInSupported(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isAppleSignInSupported : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isAppleSignInSupported();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isAppleSignInSupported : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isAppleSignInSupported)

static bool js_authentication_AuthenticationController_isLoggedInFBGaming(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isLoggedInFBGaming : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isLoggedInFBGaming();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isLoggedInFBGaming : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isLoggedInFBGaming)

static bool js_authentication_AuthenticationController_signOut(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_signOut : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->signOut();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_signOut)

static bool js_authentication_AuthenticationController_SignInApple(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_SignInApple : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_SignInApple : Error processing arguments");
        cobj->SignInApple(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_SignInApple)

static bool js_authentication_AuthenticationController_getToken(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getToken : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::string result = cobj->getToken();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getToken : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getToken)

static bool js_authentication_AuthenticationController_canManuallySignin(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_canManuallySignin : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->canManuallySignin();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_canManuallySignin : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_canManuallySignin)

static bool js_authentication_AuthenticationController_getUserInfo(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getUserInfo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        authentication::UserInfo* result = cobj->getUserInfo();
        ok &= native_ptr_to_seval<authentication::UserInfo>((authentication::UserInfo*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getUserInfo : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getUserInfo)

static bool js_authentication_AuthenticationController_logOutGoogle(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_logOutGoogle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->logOutGoogle();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_logOutGoogle)

static bool js_authentication_AuthenticationController_OnGGFirebaseTokenReceived(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_OnGGFirebaseTokenReceived : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_OnGGFirebaseTokenReceived : Error processing arguments");
        cobj->OnGGFirebaseTokenReceived(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_OnGGFirebaseTokenReceived)

static bool js_authentication_AuthenticationController_isLoggedInApple(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_isLoggedInApple : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isLoggedInApple();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_isLoggedInApple : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_isLoggedInApple)

static bool js_authentication_AuthenticationController_canLogOut(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_canLogOut : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->canLogOut();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_canLogOut : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_canLogOut)

static bool js_authentication_AuthenticationController_getUserID(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getUserID : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getUserID();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getUserID : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getUserID)

static bool js_authentication_AuthenticationController_getFacebookProfile(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getFacebookProfile : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        firebase::auth::UserInfoInterface* result = cobj->getFacebookProfile();
        ok &= native_ptr_to_seval<firebase::auth::UserInfoInterface>((firebase::auth::UserInfoInterface*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getFacebookProfile : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getFacebookProfile)

static bool js_authentication_AuthenticationController_getFacebookUserId(se::State& s)
{
    authentication::AuthenticationController* cobj = (authentication::AuthenticationController*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_AuthenticationController_getFacebookUserId : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::string result = cobj->getFacebookUserId();
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_AuthenticationController_getFacebookUserId : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_AuthenticationController_getFacebookUserId)




bool js_register_authentication_AuthenticationController(se::Object* obj)
{
    auto cls = se::Class::create("AuthenticationController", obj, nullptr, nullptr);

    cls->defineFunction("isReady", _SE(js_authentication_AuthenticationController_isReady));
    cls->defineFunction("logOutApple", _SE(js_authentication_AuthenticationController_logOutApple));
    cls->defineFunction("isLoggedInGoogle", _SE(js_authentication_AuthenticationController_isLoggedInGoogle));
    cls->defineFunction("canSendEmail", _SE(js_authentication_AuthenticationController_canSendEmail));
    cls->defineFunction("isGuestEnabled", _SE(js_authentication_AuthenticationController_isGuestEnabled));
    cls->defineFunction("SignInGoogle", _SE(js_authentication_AuthenticationController_SignInGoogle));
    cls->defineFunction("getUserPhotoUrl", _SE(js_authentication_AuthenticationController_getUserPhotoUrl));
    cls->defineFunction("isAutoSignIn", _SE(js_authentication_AuthenticationController_isAutoSignIn));
    cls->defineFunction("tryInit", _SE(js_authentication_AuthenticationController_tryInit));
    cls->defineFunction("SignInFacebook", _SE(js_authentication_AuthenticationController_SignInFacebook));
    cls->defineFunction("isLoggedInAnonymous", _SE(js_authentication_AuthenticationController_isLoggedInAnonymous));
    cls->defineFunction("getUserDisplayName", _SE(js_authentication_AuthenticationController_getUserDisplayName));
    cls->defineFunction("SignInAnonymously", _SE(js_authentication_AuthenticationController_SignInAnonymously));
    cls->defineFunction("isLoggedInFB", _SE(js_authentication_AuthenticationController_isLoggedInFB));
    cls->defineFunction("logOutFB", _SE(js_authentication_AuthenticationController_logOutFB));
    cls->defineFunction("getGoogleUserId", _SE(js_authentication_AuthenticationController_getGoogleUserId));
    cls->defineFunction("SignInOnLinkFail", _SE(js_authentication_AuthenticationController_SignInOnLinkFail));
    cls->defineFunction("getFacebookAccessToken", _SE(js_authentication_AuthenticationController_getFacebookAccessToken));
    cls->defineFunction("fetchToken", _SE(js_authentication_AuthenticationController_fetchToken));
    cls->defineFunction("isAppleSignInSupported", _SE(js_authentication_AuthenticationController_isAppleSignInSupported));
    cls->defineFunction("isLoggedInFBGaming", _SE(js_authentication_AuthenticationController_isLoggedInFBGaming));
    cls->defineFunction("signOut", _SE(js_authentication_AuthenticationController_signOut));
    cls->defineFunction("SignInApple", _SE(js_authentication_AuthenticationController_SignInApple));
    cls->defineFunction("getToken", _SE(js_authentication_AuthenticationController_getToken));
    cls->defineFunction("canManuallySignin", _SE(js_authentication_AuthenticationController_canManuallySignin));
    cls->defineFunction("getUserInfo", _SE(js_authentication_AuthenticationController_getUserInfo));
    cls->defineFunction("logOutGoogle", _SE(js_authentication_AuthenticationController_logOutGoogle));
    cls->defineFunction("OnGGFirebaseTokenReceived", _SE(js_authentication_AuthenticationController_OnGGFirebaseTokenReceived));
    cls->defineFunction("isLoggedInApple", _SE(js_authentication_AuthenticationController_isLoggedInApple));
    cls->defineFunction("canLogOut", _SE(js_authentication_AuthenticationController_canLogOut));
    cls->defineFunction("getUserID", _SE(js_authentication_AuthenticationController_getUserID));
    cls->defineFunction("getFacebookProfile", _SE(js_authentication_AuthenticationController_getFacebookProfile));
    cls->defineFunction("getFacebookUserId", _SE(js_authentication_AuthenticationController_getFacebookUserId));
    cls->install();
    JSBClassType::registerClass<authentication::AuthenticationController>(cls);

    __jsb_authentication_AuthenticationController_proto = cls->getProto();
    __jsb_authentication_AuthenticationController_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_authentication_PersistentAppData_proto = nullptr;
se::Class* __jsb_authentication_PersistentAppData_class = nullptr;

static bool js_authentication_PersistentAppData_getData(se::State& s)
{
    authentication::PersistentAppData* cobj = (authentication::PersistentAppData*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_PersistentAppData_getData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_authentication_PersistentAppData_getData : Error processing arguments");
        const std::string result = cobj->getData(arg0);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_PersistentAppData_getData : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_authentication_PersistentAppData_getData)

static bool js_authentication_PersistentAppData_saveData(se::State& s)
{
    authentication::PersistentAppData* cobj = (authentication::PersistentAppData*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_authentication_PersistentAppData_saveData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_authentication_PersistentAppData_saveData : Error processing arguments");
        cobj->saveData(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_authentication_PersistentAppData_saveData)

static bool js_authentication_PersistentAppData_getInstance(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        authentication::PersistentAppData* result = authentication::PersistentAppData::getInstance();
        ok &= native_ptr_to_seval<authentication::PersistentAppData>((authentication::PersistentAppData*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_PersistentAppData_getInstance : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_authentication_PersistentAppData_getInstance)



static bool js_authentication_PersistentAppData_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (authentication::PersistentAppData)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        authentication::PersistentAppData* cobj = (authentication::PersistentAppData*)s.nativeThisObject();
        delete cobj;
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_authentication_PersistentAppData_finalize)

bool js_register_authentication_PersistentAppData(se::Object* obj)
{
    auto cls = se::Class::create("PersistentAppData", obj, nullptr, nullptr);

    cls->defineFunction("getData", _SE(js_authentication_PersistentAppData_getData));
    cls->defineFunction("saveData", _SE(js_authentication_PersistentAppData_saveData));
    cls->defineStaticFunction("getInstance", _SE(js_authentication_PersistentAppData_getInstance));
    cls->defineFinalizeFunction(_SE(js_authentication_PersistentAppData_finalize));
    cls->install();
    JSBClassType::registerClass<authentication::PersistentAppData>(cls);

    __jsb_authentication_PersistentAppData_proto = cls->getProto();
    __jsb_authentication_PersistentAppData_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_authentication(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("authentication", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("authentication", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_authentication_AuthenticationController(ns);
    js_register_authentication_PersistentAppData(ns);
    return true;
}

