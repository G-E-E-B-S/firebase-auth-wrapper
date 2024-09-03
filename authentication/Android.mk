LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
FIREBASE_SDK_PATH := $(LOCAL_PATH)/../../../cpp/libs/firebase_sdk

LOCAL_MODULE := authentication

LOCAL_MODULE_FILENAME := libauthentication

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := ../bindings/manual/AuthJsHelper.cpp \
	../bindings/manual/login_delegate_impl.cpp \
	../bindings/auto/2.x/jsb_authentication_auto.cpp \
	controller/controller.cpp \
	firebase/auth_state_listener.cpp \
	../android/FacebookDelegate.cpp \
	../android/GoogleDelegate.cpp \
	../android/AppleDelegate.cpp \
	../android/PersistentAppData.cpp

LOCAL_CFLAGS    += -DTARGET_PLATFORM=1

LOCAL_STATIC_LIBRARIES := logging
LOCAL_STATIC_LIBRARIES += firebase-auth
LOCAL_STATIC_LIBRARIES += cocos2dx_static
LOCAL_STATIC_LIBRARIES += jsbhelper

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/..
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

include $(BUILD_STATIC_LIBRARY)

$(call import-module, logging)
$(call import-module, firebase)
$(call import-module, cocos)
$(call import-module, jsb-helper)