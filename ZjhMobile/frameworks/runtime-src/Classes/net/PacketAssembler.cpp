//
//  PacketAssembler.cpp
//  ZjhMobile
//
//  Created by gongxun on 15/9/17.
//
//

#include "PacketAssembler.h"
#include "MessageNotifycation.h"

PacketAssembler *PacketAssembler::mPacketAssembler = nullptr;

PacketAssembler::CGarbo PacketAssembler::mGarobo;

string PacketAssembler::gMagic = "WGP1";

PacketAssembler::PacketAssembler()
: mMsgCallBack(nullptr)
{
    mMsgIds = {2, 22};
    mRingBuf.createBuf();
}

PacketAssembler::~PacketAssembler()
{
    mPacketAssembler = nullptr;
}

PacketAssembler *PacketAssembler::singleton()
{
    if (!mPacketAssembler)
    {
        mPacketAssembler = new PacketAssembler();
    }
    return mPacketAssembler;
}

void PacketAssembler::setMsgCallBack(function<void (string, int)> msgCallBack)
{
    mMsgCallBack = msgCallBack;
}

bool PacketAssembler::assemble(char *data, int datalen)
{
    mRingBuf.writeBuf(data, datalen);
    string *piece = nullptr;
    mRingBuf.readBuf(piece);
    
    if (piece->length()<8)
    {
        //不够一个包的长度
        delete piece;
        return false;
    }
    //是否需要重置缓冲区
    bool valid;
    //消耗的缓冲区长度
    int used;
    
    valid = toMessage(*piece, used);
    
    delete piece;
    if (!valid)
    {
        //不是一个正确的包
        mRingBuf.releaseBuf();
        return false;
    }
    if (used > 0 && used <= mRingBuf.getvalielen())
    {
        mRingBuf.movepos(used);
        return true;
    }
    return false;
}

bool PacketAssembler::toMessage( string piece, int &used)
{
    int len = piece.length();
    
    if (len < 8)
    {
        //可以继续接收
        used = 0;
        return true;
    }
    
    //头
    char aBytes[5];
    for (int i=0; i<4; i++)
    {
        aBytes[i] = piece[i];
    }
    aBytes[4] = '\0';
    string magic = aBytes;
    if (magic != gMagic)
    {
        //需要重置缓冲区
        used = 0;
        return false;
    }
    
    //类型
    int pkyType= ((unsigned char)piece[4] << 8) + (unsigned char)piece[5];
    if (find(mMsgIds.begin(), mMsgIds.end(), pkyType) == mMsgIds.end())
    {
        //需要重置缓冲区
        used = 0;
        return false;
    }
    
    //长度
    int msglen = ((unsigned char)piece[6] << 8) + (unsigned char)piece[7];
    if (msglen < 0)
    {
        //需要重置缓冲区
        used = 0;
        return false;
    }
    
    if (msglen + 8 > len)
    {
        //可以继续接收
        used = 0;
        return true;
    }
    
    //可以转成msg的string
    string strmsg = piece.substr(8 , msglen);
    //string strmsg=data+8;
    strmsg = codeData(strmsg);
    used = msglen + 8;
    
    char *buffer;
    cocos2d::base64Encode((unsigned char*)strmsg.c_str(), (unsigned int)strmsg.size(), &buffer);
    string s(buffer);
    MessageStruct msgStruct = {s, pkyType};
    MessageNotifycation::singleton()->setMsg(msgStruct);
    
    return true;
}

string PacketAssembler::codeData( string data )
{
    int key[] = {71, 113, 127, 103, 67, 97, 73, 79, 107, 131, 61, 109, 59, 101, 89, 83};
    int keylenght = sizeof(key)/sizeof(int);
    size_t datalenght = data.length();
    for (size_t i = 0; i< datalenght; i++)
    {
        data[i]^= key[(i) % keylenght];
    }
    return data;
}






