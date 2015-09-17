//  GameSocket.h
//  ZjhMobile
//  Created by LiuXueCheng on 15/9/16

#ifndef _GameSocket_h_
#define _GameSocket_h_

#include "ODSocket.h"
#include <string>
#include <thread>

using namespace std;

class GameSocket
{
public:
    static GameSocket* GetSingleton();
    GameSocket();
    virtual ~GameSocket();
    
    void testSend(string buffer);
    void testSend1(const char *data);
    string codeData( string data );
    
    //关闭连接
    void Close();
    //连接
    bool Connect(string host, unsigned short port);
    //向服务器发消息
    bool SendMsg(const char* msg, int msgLength, int flags = 0);
    
private:
    //接收服务器消息
    void ReceiveData();
    
private:
    ODSocket mODSocket;
    bool mbConnected;
};

#endif
