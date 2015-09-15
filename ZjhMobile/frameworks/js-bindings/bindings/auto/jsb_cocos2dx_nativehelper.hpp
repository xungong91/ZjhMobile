#ifndef __cocos2dx_nativehelper_h__
#define __cocos2dx_nativehelper_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_cocos2d_NativeHelper_class;
extern JSObject *jsb_cocos2d_NativeHelper_prototype;

bool js_cocos2dx_nativehelper_NativeHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_nativehelper_NativeHelper_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_nativehelper_NativeHelper(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_nativehelper(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_nativehelper_NativeHelper_test(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_nativehelper_NativeHelper_setCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_nativehelper_NativeHelper_singleton(JSContext *cx, uint32_t argc, jsval *vp);
#endif

