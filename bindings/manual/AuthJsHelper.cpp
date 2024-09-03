#include "bindings/manual/AuthJSHelper.h"
#include "bindings/manual/login_delegate_impl.h"
#include "authentication/controller/controller.h"
#include "authentication/FacebookDelegate.h"
#include "authentication/GoogleDelegate.h"
#include "authentication/AppleDelegate.h"
#include "authentication/PersistentAppData.h"

namespace {
    authentication::AuthenticationController* s_controller = nullptr;
}

static bool js_authentication_JS_setListener(se::State& s)
{
    const auto& args = s.args();
    auto expected = 1;
    int argc = (int)args.size();
    if (argc == expected)
    {
        static LoginDelegateImpl* listener = nullptr;
        if (!listener) {
            listener = new (std::nothrow) LoginDelegateImpl();
            s_controller->setLoginDelegate(listener);
        }
        listener->setJSDelegate(args[0]);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, expected);
    return false;
}
SE_BIND_FUNC(js_authentication_JS_setListener)
static bool js_authentication_JS_getController(se::State& s)
{
    const auto& args = s.args();
    int argc = (int)args.size();
    auto expected = 1;
    if (argc == expected)
    {
        if (s_controller == nullptr) {
            wrapper::jsbhelper::IFirebaseAppGetter* getter = nullptr;
            seval_to_native_ptr(args[0], &getter);

            s_controller = new authentication::AuthenticationController(getter,
                                                                          new FacebookDelegate(),
                                                                          new GoogleDelegate(),
                                                                          new AppleDelegate());
        }
        auto ok = native_ptr_to_seval<authentication::AuthenticationController>((authentication::AuthenticationController*)s_controller, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_JS_getController : Error processing arguments");
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, expected);
    return false;
}
SE_BIND_FUNC(js_authentication_JS_getController)

static bool js_authentication_JS_getPersistentDataHelper(se::State& s)
{

    const auto& args = s.args();
    int argc = (int)args.size();
    auto expected = 0;
    if (argc == expected)
    {
        static authentication::PersistentAppData* persistentAppDataHelper = nullptr;
        if (!persistentAppDataHelper) {
            persistentAppDataHelper = new authentication::PersistentAppData();
        }
        auto ok = native_ptr_to_seval<authentication::PersistentAppData>((authentication::PersistentAppData*)persistentAppDataHelper, &s.rval());
        SE_PRECONDITION2(ok, false, "js_authentication_JS_getPersistentDataHelper : Error processing arguments");
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, expected);
    return false;
}
SE_BIND_FUNC(js_authentication_JS_getPersistentDataHelper)
bool register_all_authentication_JS_helper(se::Object* obj)
{
    auto pluginValue = wrapper::jsbhelper::getPluginValue(obj, "authentication");
    auto plugin = pluginValue.toObject();
    plugin->defineFunction("setListener", _SE(js_authentication_JS_setListener));
    plugin->defineFunction("getController", _SE(js_authentication_JS_getController));
    plugin->defineFunction("getPersistentDataHelper", _SE(js_authentication_JS_getPersistentDataHelper));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

