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
            bResult = true;
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
        if(len > 0)
        {
            //接收消息
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
            break;
        }
    }
}





