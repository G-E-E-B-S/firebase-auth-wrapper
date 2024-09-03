#include "login_delegate_impl.h"
#include "logger/log.h"
#include <map>
#include <string>
#include <sstream>

bool LoginDelegateImpl::OnSuccess()
{
    logger::log("OnLoginSuccess\n");
    RUN_ON_MAIN_THREAD_BEGIN
    MAKE_V8_HAPPY

    se::ValueArray args;
    invokeJSFun(funcName, args);

    RUN_ON_MAIN_THREAD_END

    // just return true, now
    return true;
}

bool LoginDelegateImpl::OnCancel()
{
    logger::log("OnCancel\n");
    RUN_ON_MAIN_THREAD_BEGIN
    MAKE_V8_HAPPY

    se::ValueArray args;
    invokeJSFun(funcName, args);

    RUN_ON_MAIN_THREAD_END

    // just return true, now
    return true;
}

bool LoginDelegateImpl::OnFailure(int error_code, std::string error_msg)
{
    std::ostringstream os;
    os << error_code;
    auto error_code_str = os.str();
    std::map<std::string, std::string> params;
    params["error_code"] = error_code_str;
    params["error_msg"] = error_msg;
    logger::log("OnLoginFailure: %s", error_msg.c_str());

    RUN_ON_MAIN_THREAD_BEGIN
    MAKE_V8_HAPPY

    se::ValueArray args;
    args.push_back(se::Value(error_code));
    invokeJSFun(funcName, args);

    RUN_ON_MAIN_THREAD_END

    // just return true, now
    return true;
}
bool LoginDelegateImpl::OnLinkAccountFail(int error_code, std::string error_msg)
{
    std::ostringstream os;
    os << error_code;
    auto error_code_str = os.str();
    std::map<std::string, std::string> params;
    params["error_code"] = error_code_str;
    params["error_msg"] = error_msg;
    logger::log("OnLinkAccountFail\n");
    RUN_ON_MAIN_THREAD_BEGIN
    MAKE_V8_HAPPY

    se::ValueArray args;
    args.push_back(se::Value(error_code));
    invokeJSFun(funcName, args);

    RUN_ON_MAIN_THREAD_END

    // just return true, now
    return true;
}

bool LoginDelegateImpl::OnFbGamingLogin(std::string gamingLoginToken, std::string userIdToConnectTo)
{
    logger::log("OnLinkAccountFail\n");
    RUN_ON_MAIN_THREAD_BEGIN
    MAKE_V8_HAPPY

    se::ValueArray args;
    args.push_back(se::Value(gamingLoginToken));
    invokeJSFun(funcName, args);

    RUN_ON_MAIN_THREAD_END

    // just return true, now
    return true;
}
