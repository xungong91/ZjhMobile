//
//  NativeHelper.cpp
//  ZjhMobile
//
//  Created by gongxun on 15/9/14.
//
//

#include "NativeHelper.h"

USING_NS_CC;

NativeHelper::CGarbo NativeHelper::mGarbo;

NativeHelper *NativeHelper::mNativeHelper = nullptr;

NativeHelper::NativeHelper()
: mCallFunc(nullptr)
{
    
}

NativeHelper::~NativeHelper()
{
    mNativeHelper = nullptr;
}

NativeHelper *NativeHelper::singleton()
{
    if (!mNativeHelper)
    {
        mNativeHelper = new NativeHelper();
    }
    return mNativeHelper;
}

std::string NativeHelper::test()
{
    if (mCallFunc)
    {
        mCallFunc("setCallFunc hehe");
    }
    
    return "test msg";
}

void NativeHelper::setCallFunc(function<void (string)> callFunc)
{
    mCallFunc = callFunc;
}