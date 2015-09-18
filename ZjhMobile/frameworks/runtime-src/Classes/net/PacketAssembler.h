//
//  PacketAssembler.h
//  ZjhMobile
//
//  Created by gongxun on 15/9/17.
//
//

#ifndef __ZjhMobile__PacketAssembler__
#define __ZjhMobile__PacketAssembler__

#include <stdio.h>
#include "CRingBuf.h"
#include <vector>
#include <functional>

class PacketAssembler
{
public:
    static string gMagic;
    static PacketAssembler *singleton();
    
    void setMsgCallBack(function<void (string, int)> msgCallBack);
    
    //解析消息 
    bool assemble(char *data, int datalen);
    //^加密
    string codeData( string data );
private:
    CRingBuf mRingBuf;
    vector<int> mMsgIds;
    function<void (string, int)> mMsgCallBack;
    
    /**
     *  给js发送未解析的消息
     *
     *  @param piece 数据
     *  @param used  使用了数据的长度
     *
     *  @return 是否需要清空缓冲区 false就清空
     */
    bool toMessage( string piece, int &used);
    
    //...
    static PacketAssembler *mPacketAssembler;
    PacketAssembler();
    ~PacketAssembler();
    class CGarbo
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (mPacketAssembler)
            {
                delete mPacketAssembler;
            }
        }
    };
    static CGarbo mGarobo;
};


#endif /* defined(__ZjhMobile__PacketAssembler__) */
