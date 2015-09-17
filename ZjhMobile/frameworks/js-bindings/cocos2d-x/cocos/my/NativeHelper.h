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

using namespace std;

namespace cocos2d
{
    class NativeHelper
    {
    public:
        static NativeHelper *singleton();
        
        string test();
        void testSend(string buffer);
        void testSend1(const char *data);
        
        void setCallFunc(function<void (string)> callFunc);
    private:
        function<void (string)> mCallFunc;
        
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
