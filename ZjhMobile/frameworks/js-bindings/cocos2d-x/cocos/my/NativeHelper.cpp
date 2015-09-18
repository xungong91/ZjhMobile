//
//  NativeHelper.cpp
//  ZjhMobile
//
//  Created by gongxun on 15/9/14.
//
//

#include "NativeHelper.h"
#include "GameSocket.h"
#include "PacketAssembler.h"
#include "MessageNotifycation.h"

USING_NS_CC;

NativeHelper::CGarbo NativeHelper::mGarbo;

NativeHelper *NativeHelper::mNativeHelper = nullptr;

NativeHelper::NativeHelper()
: mMsgCallBack(nullptr)
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
    GameSocket::GetSingleton()->test();
    
    return "test msg";
}

void NativeHelper::setPacketAssembler(function<void (string, int)> msgCallBack)
{
    mMsgCallBack = msgCallBack;
}

void NativeHelper::setCallBack(function<void ()> callBack)
{
    mCallBack = callBack;
}

void NativeHelper::startSendMsg()
{
    MessageNotifycation::singleton()->stratSendCB();
}

bool NativeHelper::sendJsMsg(string msg, int msgId)
{
    return GameSocket::GetSingleton()->sendJsMsg(msg, msgId);
}

bool NativeHelper::recvJsMsg(string base64, int msgId)
{
    if (mMsgCallBack)
    {
        mMsgCallBack(base64, msgId);
        return true;
    }
    return false;
}












