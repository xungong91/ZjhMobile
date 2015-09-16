#include "ODSocket.h"
#include <stdio.h>
#ifdef WIN32
	#pragma comment(lib, "wsock32")
#endif

ODSocket::ODSocket(SOCKET sock)
{
	m_sock = sock;
}

ODSocket::~ODSocket()
{
}

//this is just for windows
int ODSocket::Init()
{
#ifdef WIN32
	//http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret )
		return -1;//Initilize winsock error
#endif
	return 0;
}

//this is just for windows
int ODSocket::Clean()
{
#ifdef WIN32
		return (WSACleanup());
#endif
		return 0;
}

ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

ODSocket::operator SOCKET ()
{
	return m_sock;
}

//create a socket object win/lin is the same
bool ODSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET )
		return false;
    
    if(type == SOCK_DGRAM)//udp
    {
        int opt = 1;
        //设置该套接字为广播类型，
        setsockopt(m_sock,SOL_SOCKET,SO_BROADCAST,(char *)&opt,sizeof(opt));
        //设置接收超时
        struct timeval recv_timeout;
        recv_timeout.tv_sec = 2;
        recv_timeout.tv_usec = 0;
        setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&recv_timeout, sizeof(recv_timeout));
    }
    else if(type == SOCK_STREAM)//tcp
    {
        struct timeval recv_timeout;
        struct timeval send_timeout;
        recv_timeout.tv_sec = 0;
        recv_timeout.tv_usec = 500000;
        send_timeout.tv_sec = 0;
        send_timeout.tv_usec = 500000;
        
        setsockopt(m_sock,SOL_SOCKET,SO_SNDTIMEO,(void *)&send_timeout, sizeof(send_timeout));
        setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&recv_timeout, sizeof(recv_timeout));
    }
    return true;
}

bool ODSocket::Connect(const char* ip, unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR )
		return false;
	return true;
}

//for server
bool ODSocket::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);

	int opt =  1;
	if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0 ) 
		return false;

	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR )
		return false;
	
	return true;
}

//for server
bool ODSocket::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR )
		return false;

	return true;
}

//for server
bool ODSocket::Accept(ODSocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR )
		return false;

	s = sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

int ODSocket::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;

	while ( count < len )
    {
		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	}
    
	return count;
}

int ODSocket::SendTo(const char* buf, int len, const struct sockaddr *to, int tolen, int flags)
{
	int bytes;
	int count = 0;

	while ( count < len )
    {
		bytes = sendto(m_sock, buf + count, len - count, flags, to, tolen);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	} 

	return count;
}

int ODSocket::SendBroadcast(const char* buf, int len, unsigned short port)
{
    struct sockaddr_in addrto;
    socklen_t addrlen = sizeof(addrto);
    addrto.sin_family=AF_INET;
    addrto.sin_addr.s_addr=INADDR_BROADCAST;
    addrto.sin_port=htons(port);
    
    int bytes = sendto(m_sock, buf, len, 0, (struct sockaddr*)&addrto, addrlen);
    if(SOCKET_ERROR == bytes)
        return -1;
    
    return bytes;
}

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
int ODSocket::RecvFrom(char* buf, int len, struct sockaddr * to, unsigned int tolen, int flags)
{
	int bytes;
	bytes= recvfrom(m_sock, buf, len, flags, to, &tolen);
	if(bytes==-1||bytes==0)
		return -1;
	else
		return bytes;
}
#else
int ODSocket::RecvFrom(char* buf, int len, struct sockaddr * to, int tolen, int flags)
{
    int bytes;
    bytes= recvfrom(m_sock, buf, len, flags, to, &tolen);
    if(bytes==-1||bytes==0)
        return -1;
    else
        return bytes;
}
#endif

int ODSocket::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}


int ODSocket::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int ODSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool ODSocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
		
	sprintf(ip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	
	return true;
}
