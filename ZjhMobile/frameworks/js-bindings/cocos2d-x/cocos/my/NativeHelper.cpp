//
//  NativeHelper.cpp
//  ZjhMobile
//
//  Created by gongxun on 15/9/14.
//
//

#include "NativeHelper.h"
#include "GameSocket.h"

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
    
    GameSocket::GetSingleton()->Connect("192.168.2.21", 7999);
    
    return "test msg";
}

void NativeHelper::testSend(string buffer)
{
    GameSocket::GetSingleton()->testSend(buffer);
}

void NativeHelper::testSend1(const char *data)
{
    GameSocket::GetSingleton()->testSend1(data);
}

void NativeHelper::setCallFunc(function<void (string)> callFunc)
{
    mCallFunc = callFunc;
}














