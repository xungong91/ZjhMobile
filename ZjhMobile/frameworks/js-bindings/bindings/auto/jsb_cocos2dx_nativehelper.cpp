#include "jsb_cocos2dx_nativehelper.hpp"
#include "cocos2d_specifics.hpp"
#include "NativeHelper.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_cocos2d_NativeHelper_class;
JSObject *jsb_cocos2d_NativeHelper_prototype;

bool js_cocos2dx_nativehelper_NativeHelper_startSendMsg(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NativeHelper* cobj = (cocos2d::NativeHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_nativehelper_NativeHelper_startSendMsg : Invalid Native Object");
    if (argc == 0) {
        cobj->startSendMsg();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_startSendMsg : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_nativehelper_NativeHelper_setPacketAssembler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NativeHelper* cobj = (cocos2d::NativeHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_nativehelper_NativeHelper_setPacketAssembler : Invalid Native Object");
    if (argc == 1) {
        std::function<void (std::basic_string<char>, int)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](std::basic_string<char> larg0, int larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            largv[0] = std_string_to_jsval(cx, larg0);
		            largv[1] = int32_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(2, &largv[0], &rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_nativehelper_NativeHelper_setPacketAssembler : Error processing arguments");
        cobj->setPacketAssembler(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_setPacketAssembler : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_nativehelper_NativeHelper_getMsg(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NativeHelper* cobj = (cocos2d::NativeHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_nativehelper_NativeHelper_getMsg : Invalid Native Object");
    if (argc == 0) {
        cocos2d::MessageStruct ret = cobj->getMsg();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR MessageStruct;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_getMsg : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_nativehelper_NativeHelper_setCallBack(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NativeHelper* cobj = (cocos2d::NativeHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_nativehelper_NativeHelper_setCallBack : Invalid Native Object");
    if (argc == 1) {
        std::function<void ()> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(0, nullptr, &rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_nativehelper_NativeHelper_setCallBack : Error processing arguments");
        cobj->setCallBack(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_setCallBack : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_nativehelper_NativeHelper_sendJsMsg(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NativeHelper* cobj = (cocos2d::NativeHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_nativehelper_NativeHelper_sendJsMsg : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_nativehelper_NativeHelper_sendJsMsg : Error processing arguments");
        bool ret = cobj->sendJsMsg(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_sendJsMsg : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_nativehelper_NativeHelper_test(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NativeHelper* cobj = (cocos2d::NativeHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_nativehelper_NativeHelper_test : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->test();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_test : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_nativehelper_NativeHelper_setMsg(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NativeHelper* cobj = (cocos2d::NativeHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_nativehelper_NativeHelper_setMsg : Invalid Native Object");
    if (argc == 1) {
        cocos2d::MessageStruct arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR MessageStruct
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_nativehelper_NativeHelper_setMsg : Error processing arguments");
        cobj->setMsg(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_setMsg : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_nativehelper_NativeHelper_singleton(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::NativeHelper* ret = cocos2d::NativeHelper::singleton();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::NativeHelper>(cx, (cocos2d::NativeHelper*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_nativehelper_NativeHelper_singleton : wrong number of arguments");
    return false;
}



void js_cocos2d_NativeHelper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (NativeHelper)", obj);
}

void js_register_cocos2dx_nativehelper_NativeHelper(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_NativeHelper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_NativeHelper_class->name = "NativeHelper";
    jsb_cocos2d_NativeHelper_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_NativeHelper_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_NativeHelper_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_NativeHelper_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_NativeHelper_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_NativeHelper_class->resolve = JS_ResolveStub;
    jsb_cocos2d_NativeHelper_class->convert = JS_ConvertStub;
    jsb_cocos2d_NativeHelper_class->finalize = js_cocos2d_NativeHelper_finalize;
    jsb_cocos2d_NativeHelper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("startSendMsg", js_cocos2dx_nativehelper_NativeHelper_startSendMsg, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPacketAssembler", js_cocos2dx_nativehelper_NativeHelper_setPacketAssembler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMsg", js_cocos2dx_nativehelper_NativeHelper_getMsg, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCallBack", js_cocos2dx_nativehelper_NativeHelper_setCallBack, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendJsMsg", js_cocos2dx_nativehelper_NativeHelper_sendJsMsg, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("test", js_cocos2dx_nativehelper_NativeHelper_test, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMsg", js_cocos2dx_nativehelper_NativeHelper_setMsg, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("singleton", js_cocos2dx_nativehelper_NativeHelper_singleton, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_NativeHelper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_NativeHelper_class,
        dummy_constructor<cocos2d::NativeHelper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "NativeHelper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::NativeHelper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_NativeHelper_class;
        p->proto = jsb_cocos2d_NativeHelper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_nativehelper(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);

    js_register_cocos2dx_nativehelper_NativeHelper(cx, ns);
}

