//  ShareUtil.cpp
//  ZjhMobile
//  Created by LiuXueCheng on 15/9/16

#include "ShareUtil.h"

static ShareUtil *sShareUtil = nullptr;

ShareUtil* ShareUtil::GetSingleton()
{
    if(!sShareUtil)
        sShareUtil = new (std::nothrow)ShareUtil();
    
    return sShareUtil;
}

ShareUtil::ShareUtil()
{
}

ShareUtil::~ShareUtil()
{
}
