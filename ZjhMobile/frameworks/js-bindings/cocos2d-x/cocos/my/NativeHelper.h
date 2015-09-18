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
    class NativeHelper
    {
    public:
        static NativeHelper *singleton();
        
        string test();
        
        void setCallBack(function<void ()> callBack);
        
        /**
         *  c++传递收到的消息到js
         *
         *  @param string base64编码的message
         *  @param int    messageId
         */
        void setPacketAssembler(function<void (string, int)> msgCallBack);
        
        /**
         *  启动消息发送器
         */
        void startSendMsg();
        
        /**
         *  发送socket消息
         *
         *  @param msg   message二进制
         *  @param msgId messageid
         *
         *  @return 是否发送成功
         */
        bool sendJsMsg(string msg, int msgId);
        
        /**
         *  接受到了消息交给js解析
         *
         *  @param base64 string
         *  @param msgId  id
         *
         *  @return 是否发送成功
         */
        bool recvJsMsg(string base64, int msgId);
        
    private:
        function<void (string, int)> mMsgCallBack;
        function<void ()> mCallBack;
        
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
