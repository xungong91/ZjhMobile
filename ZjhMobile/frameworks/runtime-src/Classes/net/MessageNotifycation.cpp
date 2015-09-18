//
//  MessageNotifycation.cpp
//  ZjhMobile
//
//  Created by gongxun on 15/9/18.
//
//

#include "MessageNotifycation.h"
#include "NativeHelper.h"

MessageNotifycation *MessageNotifycation::mMessageNotifycation = nullptr;

MessageNotifycation::CGarbo MessageNotifycation::mGarobo;

MessageNotifycation::MessageNotifycation()
{
    
}

MessageNotifycation::~MessageNotifycation()
{
    mMessageNotifycation = nullptr;
}

MessageNotifycation *MessageNotifycation::singleton()
{
    if (!mMessageNotifycation)
    {
        mMessageNotifycation = new MessageNotifycation();
    }
    return mMessageNotifycation;
}

void MessageNotifycation::stratSendCB()
{
    Director::getInstance()->getRunningScene()->schedule
    ([this](float dt)
     {
         if (mMsgs.size() > 0)
         {
             MessageStruct msg = getMsg();
             NativeHelper::singleton()->recvJsMsg(msg.base64, msg.msgId);
         }
     }, 0.1f, "startSendMsg");
}

MessageStruct MessageNotifycation::getMsg()
{
    mMutex.lock();
    MessageStruct temp;
    if (mMsgs.size() != 0)
    {
        temp = mMsgs.front();
        mMsgs.pop_front();
    }
    mMutex.unlock();
    return temp;
}

void MessageNotifycation::setMsg(MessageStruct msg)
{
    mMutex.lock();
    mMsgs.push_back(msg);
    mMutex.unlock();
}
























