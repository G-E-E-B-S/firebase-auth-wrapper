#ifndef UNO_LOGIN_DELEGATE_IMPL_H
#define UNO_LOGIN_DELEGATE_IMPL_H

#include "authentication/controller/controller.h"
#include "authentication/controller/login_delegate.h"

#if CC_VERSION_3_X
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#else
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#endif

#define MAKE_V8_HAPPY \
se::ScriptEngine::getInstance()->clearException(); \
se::AutoHandleScope hs;

#if CC_VERSION_3_X
#include "cocos.h"
#else
#include "cocos2d.h"
#include "base/CCScheduler.h"
#include "platform/CCApplication.h"
#endif

#if CC_VERSION_3_X
#define RUN_ON_MAIN_THREAD_BEGIN \
auto funcName = __FUNCTION__;    \
auto scheduler = CC_CURRENT_ENGINE()->getScheduler(); \
scheduler->performFunctionInCocosThread([=](){

#define RUN_ON_MAIN_THREAD_END });
#else
#define RUN_ON_MAIN_THREAD_BEGIN \
auto funcName = __FUNCTION__; \
auto scheduler = cocos2d::Application::getInstance()->getScheduler(); \
scheduler->performFunctionInCocosThread([=](){

#define RUN_ON_MAIN_THREAD_END });
#endif

#include <atomic>
#include "include/JSListenerBase.h"

class LoginDelegateImpl : public authentication::LoginDelegate, public wrapper::jsbhelper::JSListenerBase
{
    enum class CallBackEvents {
        NONE,
        LOGIN_SUCCESS,
        LOGIN_FAILURE,
        LOGIN_LINK_FAIL,
        DATA_LOAD_SUCCESS,
        DATA_LOAD_FAILURE
    };
    using AuthenticationController = authentication::AuthenticationController;
public:    
    LoginDelegateImpl() {};
    virtual bool OnSuccess() override;
    virtual bool OnCancel() override;
    virtual bool OnFailure(int error_code, std::string error_msg) override;
    virtual bool OnLinkAccountFail(int error_code, std::string error_msg) override;
    virtual bool OnFbGamingLogin(std::string ggToken, std::string userIdToConnectTo) override;
    virtual ~LoginDelegateImpl() {};
private:
    std::shared_ptr<AuthenticationController> _controller;
};
#endif // UNO_LOGIN_DELEGATE_IMPL_H
