cmake_minimum_required(VERSION 3.8)

set(AUTH_JS_BINDING_SRC
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/AuthJsHelper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/AuthJsHelper.h
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/login_delegate_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/login_delegate_impl.h)

if (COCOS_3_7_PLUS)
    list(APPEND AUTH_JS_BINDING_SRC
        ${CMAKE_CURRENT_LIST_DIR}/../bindings/auto/3.7.x/jsb_authentication_auto.cpp
    )
elseif(COCOS_3_X_PLUS)
    list(APPEND AUTH_JS_BINDING_SRC
        ${CMAKE_CURRENT_LIST_DIR}/../bindings/auto/3.x.x_3.6.x/jsb_authentication_auto.cpp
    )
else()
    list(APPEND AUTH_JS_BINDING_SRC
        ${CMAKE_CURRENT_LIST_DIR}/../bindings/auto/2.x/jsb_authentication_auto.cpp
    )
endif()

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/../bindings PREFIX "js-bindings/auth-sdk" FILES ${AUTH_JS_BINDING_SRC})

list(APPEND CC_ALL_SOURCES ${AUTH_JS_BINDING_SRC})