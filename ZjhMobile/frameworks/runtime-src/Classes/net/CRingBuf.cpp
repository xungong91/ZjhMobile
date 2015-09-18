#include "CRingBuf.h"

void CRingBuf::createBuf()
{
	mPos = 0;
	mValielen = 0;
}
void CRingBuf::releaseBuf()
{
	mPos = 0;
	mValielen = 0;
}
void CRingBuf::readBuf(string *&piece)
{
	piece = new string(mValielen,'\0');
	for (int i = 0 ; i<mValielen ; i++)
	{
		(*piece)[i] = buffer[mGetnewpos(mPos+i)];
	}
}
void CRingBuf::movepos( int size )
{
	mPos = mGetnewpos(mPos + size);
	mValielen -= size;
}

void CRingBuf::writeBuf(char* data , int len )
{
	int endnum = mValielen + mPos;
	for (int i = 0; i<len; i++)
	{
		buffer[mGetnewpos(i+endnum)] = data[i];
	}
	mValielen += len;
}

int CRingBuf::mGetnewpos( int num )
{
	if (num >= mRingLen)
	{
		num  = num - mRingLen;
	}
	return num;
}

int CRingBuf::getvalielen()
{
	return mValielen;
}

int CRingBuf::testFun( int a , int b )
{
	return a+b;
}

