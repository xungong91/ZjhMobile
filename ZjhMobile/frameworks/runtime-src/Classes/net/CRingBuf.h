#ifndef _C_RING_BUF_H_
#define _C_RING_BUF_H_

#include <string>
using namespace std;

class CRingBuf
{
public:
	int testFun(int a,int b);
	void createBuf();
	void releaseBuf();
	void readBuf(string *&piece);
    
    //保存数据
	void writeBuf(char* data,int len);
	void movepos(int size);
//	static const int mRingLen = 10240;
    static const int mRingLen = 51200;
	char buffer[mRingLen];
	int getvalielen();
private:
    //环形缓冲区等待解析的索引
	int mPos;
    
    //等待解析的长度
	int mValielen;
    
    //返回环形缓冲区的索引
	int mGetnewpos(int pos);
};
#endif