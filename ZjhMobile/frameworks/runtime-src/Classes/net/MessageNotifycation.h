//
//  MessageNotifycation.h
//  ZjhMobile
//
//  Created by gongxun on 15/9/18.
//
//

#ifndef __ZjhMobile__MessageNotifycation__
#define __ZjhMobile__MessageNotifycation__

#include <string>
#include <mutex>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

struct MessageStruct
{
    string base64;
    int msgId;
};

class MessageNotifycation
{
public:
    static MessageNotifycation *singleton();
    
    void stratSendCB();
    
    //读取msg 储存msg
    MessageStruct getMsg();
    void setMsg(MessageStruct msg);
private:
    list<MessageStruct> mMsgs;
    mutex mMutex;
    
    static MessageNotifycation *mMessageNotifycation;
    MessageNotifycation();
    ~MessageNotifycation();
    class CGarbo
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (mMessageNotifycation)
            {
                delete mMessageNotifycation;
            }
        }
    };
    static CGarbo mGarobo;
};

#endif /* defined(__ZjhMobile__MessageNotifycation__) */
