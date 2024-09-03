#ifndef AUTHENTICATION_SDK_AUTH_JS_HELPER_H
#define AUTHENTICATION_SDK_AUTH_JS_HELPER_H

#if CC_VERSION_3_X
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#else
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#endif

namespace se {
    class Object;
}

bool register_all_authentication_JS_helper(se::Object* obj);
#endif // AUTHENTICATION_SDK_AUTH_JS_HELPER_H