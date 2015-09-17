//  ShareUtil.cpp
//  ZjhMobile
//  Created by LiuXueCheng on 15/9/16

#ifndef _ShareUtil_h_
#define _ShareUtil_h_

#include "C2DXShareSDK.h"

class ShareUtil
{
public:
    static ShareUtil* GetSingleton();
    ShareUtil();
    virtual ~ShareUtil();
};

#endif
