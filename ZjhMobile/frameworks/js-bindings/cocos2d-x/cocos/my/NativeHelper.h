//
//  NativeHelper.h
//  ZjhMobile
//
//  Created by gongxun on 15/9/14.
//
//

#ifndef __ZjhMobile__NativeHelper__
#define __ZjhMobile__NativeHelper__

#include "cocos2d.h"
#include <functional>
#include <vector>
#include <list>

using namespace std;

namespace cocos2d
{
    struct MessageStruct
    {
        string base64;
        int msgId;
    };
    
    class NativeHelper
    {
    public:
        static NativeHelper *singleton();
        
        string test();
        
        void setPacketAssembler(function<void (string, int)> msgCallBack);
        
        void setCallBack(function<void ()> callBack);
        
        //start
        void startSendMsg();
        
        //发送
        bool sendJsMsg(string msg, int msgId);
        
        //读取msg
        MessageStruct getMsg();
        void setMsg(MessageStruct msg);
    private:
        function<void (string, int)> mMsgCallBack;
        function<void ()> mCallBack;
        list<MessageStruct> mMsgs;
        
        static NativeHelper *mNativeHelper;
        NativeHelper();
        ~NativeHelper();
        class CGarbo
        {
        public:
            CGarbo() {}
            ~CGarbo()
            {
                if (mNativeHelper)
                {
                    delete mNativeHelper;
                }
            }
        };
        static CGarbo mGarbo;
    };
}



#endif /* defined(__ZjhMobile__NativeHelper__) */
