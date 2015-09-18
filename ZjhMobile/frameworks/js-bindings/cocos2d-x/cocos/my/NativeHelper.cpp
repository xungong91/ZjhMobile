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
//    vector<int> a = {1, 2, 3, 4, 5, 6};
//    setMsg(a);
    
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

MessageStruct NativeHelper::getMsg()
{
    MessageStruct temp = mMsgs.front();
    mMsgs.pop_front();
    return temp;
}

void NativeHelper::setMsg(MessageStruct msg)
{
    mMsgs.push_back(msg);
}

void NativeHelper::startSendMsg()
{
    Director::getInstance()->getRunningScene()->schedule
    ([this](float dt)
    {
        if (mMsgCallBack && mMsgs.size() > 0)
        {
//            mMsgCallBack();
            MessageStruct msg = getMsg();
            mMsgCallBack(msg.base64, msg.msgId);
        }
    }, 0.1f, "startSendMsg");
}

bool NativeHelper::sendJsMsg(string msg, int msgId)
{
    return GameSocket::GetSingleton()->sendJsMsg(msg, msgId);
}












