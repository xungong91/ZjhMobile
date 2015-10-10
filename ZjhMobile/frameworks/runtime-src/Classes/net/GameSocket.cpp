//  GameSocket.h
//  ZjhMobile
//  Created by LiuXueCheng on 15/9/16

#include "GameSocket.h"
#include "PacketAssembler.h"

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
    Connect("192.168.2.21", 6999);
}

bool GameSocket::sendJsMsg(string msg, int msgId)
{
    //长度
    int lenght;
    //抑或加密
    string loads = PacketAssembler::singleton()->codeData(msg);
    //发送的指针
    char* result;
    
    int Magiclenght = (int)PacketAssembler::gMagic.length();
    short loadslenght=loads.length();
    lenght = Magiclenght + 2 + 2 + loadslenght;
    
    result = new char[lenght];
    memcpy(result, PacketAssembler::gMagic.c_str() , Magiclenght);
    char twochar[2];
    twochar[0] = (char)(msgId>>8);
    twochar[1] = (char)(msgId>>0);
    memcpy(result+Magiclenght , twochar,2);
    twochar[0] = (char)(loadslenght>>8);
    twochar[1] = (char)(loadslenght>>0);
    memcpy(result + Magiclenght + 2, twochar , 2);
    memcpy(result + Magiclenght + 2 + 2, loads.c_str() , loadslenght);
    
    return SendMsg(result, lenght);
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
        CCLOG("收到消息：%s", msg);

        if(len > 0)
        {
            //接收消息
            CCLOG("收到消息");
            //解析消息 存储recvBuf  成功返回 pkyType 和 msg
            bool valid = PacketAssembler::singleton()->assemble(receiveBuf, len);
            if (valid)
            {
                int iTest = 0;
                while (valid)
                {
                    //继续解析
                    valid = PacketAssembler::singleton()->assemble(NULL, 0);
                    if (!valid)
                    {
                        //数据不准确需要继续recv
                        break;
                    }
                    ++iTest;
                    
                    //防止当前循环使cup过高
                    this_thread::sleep_for(chrono::milliseconds(1));
                }
            }
            else
            {
                // 数据包不够解析 需要继续recv
            }
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





