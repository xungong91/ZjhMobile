//  GameSocket.h
//  ZjhMobile
//  Created by LiuXueCheng on 15/9/16

#include "GameSocket.h"

static GameSocket *sGameSocket = nullptr;

GameSocket* GameSocket::GetSingleton()
{
    if(!sGameSocket)
        sGameSocket = new (std::nothrow)GameSocket();
    
    return sGameSocket;
}

GameSocket::GameSocket()
:mbConnected(false)
{
}

GameSocket::~GameSocket()
{
    mbConnected = false;
    sGameSocket = nullptr;
    mODSocket.Close();
}

void GameSocket::test()
{
    Connect("192.168.2.21", 7999);
}

void GameSocket::testSend(string buffer)
{
    string mMagic = "WGP1";
    int lenght;
    int msgId = 7;
    
    CCLOG(buffer.c_str());
//    string loads = codeData(buffer);
    string loads = buffer;
    char* result;
    //º”√‹
    //◊º±∏∫œ≥…
    int Magiclenght = mMagic.length();
    //short messagemappings=getTypeForMessage(message);      3.17
    short loadslenght=loads.length();
    lenght = Magiclenght + 2 + 2 + loadslenght;
    
    result = new char[lenght];
    memcpy(result,mMagic.c_str() , Magiclenght);
    char twochar[2];
    twochar[0] = (char)(msgId>>8);
    twochar[1] = (char)(msgId>>0);
    memcpy(result+Magiclenght , twochar,2);
    //twochar[0] = (char)(messagemappings>>8);				 3.17
    //twochar[1] = (char)(messagemappings>>0);				 3.17
    //memcpy(result+Magiclenght , twochar,2);				 3.17
    twochar[0] = (char)(loadslenght>>8);
    twochar[1] = (char)(loadslenght>>0);
    memcpy(result + Magiclenght + 2, twochar , 2);
    memcpy(result + Magiclenght + 2 + 2, loads.c_str() , loadslenght);
    
    SendMsg(result, lenght);
}

string GameSocket::codeData( string data )
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

void GameSocket::testSend1(const char *data)
{
    CCLOG(data);
}

//关闭连接
void GameSocket::Close()
{
    mbConnected = false;
    mODSocket.Close();
}

//连接
bool GameSocket::Connect(string host, unsigned short port)
{
    mODSocket.Init();
    mODSocket.Create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    mbConnected = mODSocket.Connect(host.c_str(), port);
    if(mbConnected)
    {
        //创建接收服务器消息的线程
        thread receiveThread = thread(bind(&GameSocket::ReceiveData, this));
        receiveThread.detach();
        CCLOG("连接服务器成功");
    }
    else
    {
        CCLOG("连接服务器失败");
    }
    
    return mbConnected;
}

//向服务器发消息
bool GameSocket::SendMsg(const char *msg, int msgLength, int flags)
{
    bool bResult = false;
    
    if(mbConnected)
    {
        int count = mODSocket.Send(msg, msgLength, flags);
        if(count > 0)
        {
            bResult = true;
            CCLOG("发送消息成功");
        }
        else
        {
            CCLOG("发送消息失败");
        }
    }
    
    return bResult;
}

//接收服务器消息
void GameSocket::ReceiveData()
{
    const size_t receiveCount = 10240;
    char receiveBuf[receiveCount];
    
    while(mbConnected)
    {
        memset(receiveBuf, 0x00, receiveCount);
        int len = mODSocket.Recv(receiveBuf, receiveCount, 0);
        
        char msg[100];
        sprintf(msg, "收到消息长度是:%d", len);
        CCLOG(msg);

        if(len > 0)
        {
            //接收消息
            CCLOG("收到消息");
            CCLOG(receiveBuf);
        }
        else if(len == 0)
        {
            //网络断开
            mbConnected = false;
            mODSocket.Close();
            break;
        }
        else if(len < 0)
        {
            continue;
        }
    }
    
    CCLOG("断开了");
}





