set (PROJ_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/android/FacebookDelegate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/android/GoogleDelegate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/android/AppleDelegate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/android/PersistentAppData.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bindings/manual/AuthJsHelper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bindings/manual/login_delegate_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/authentication/controller/controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/authentication/firebase/auth_state_listener.cpp
)

if (GOOGLE_PLAY_SIGN_IN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNATIVE_AUTH_GOOGLE_SIGNIN=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNATIVE_AUTH_GOOGLE_SIGNIN=1")
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNATIVE_AUTH_GOOGLE_SIGNIN=0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNATIVE_AUTH_GOOGLE_SIGNIN=0")
endif()
if (COCOS_3_7_PLUS)
    list(APPEND PROJ_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/bindings/auto/3.7.x/jsb_authentication_auto.cpp
    )
elseif(COCOS_3_X_PLUS)
    list(APPEND PROJ_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/bindings/auto/3.x.x_3.6.x/jsb_authentication_auto.cpp
    )
else()
    list(APPEND PROJ_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/bindings/auto/2.x/jsb_authentication_auto.cpp
    )
endif()

set(AUTH_SDK_INCLUDE_LIST
    ${CMAKE_CURRENT_LIST_DIR}
)

add_library(native_auth STATIC ${PROJ_SOURCES})    

target_include_directories(native_auth PUBLIC 
    ${COCOS_X_PATH}
    ${COCOS_X_PATH}/cocos
    ${COCOS_X_PATH}/cocos/renderer
    ${platform_spec_path}/include/v8
    ${FIREBASE_CPP_DIR}/include
    ${JSB_HELPER_INCLUDE_DIR}
    ${LOG_WRAPPER_INCLUDE_DIR}
    ${AUTH_SDK_INCLUDE_LIST}
)

target_link_libraries(native_auth
    PRIVATE log-wrapper
    PRIVATE jsb-helper
    PRIVATE ${FIREBASE_CPP_DIR}/libs/android/${ANDROID_ABI}/libfirebase_auth.a)