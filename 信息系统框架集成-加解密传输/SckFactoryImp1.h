#pragma once
#include<iostream>
using namespace std;
#include "SocketProtocol.h"
class CSckFactoryImp1 :public CSocketProtocol
{
public:
	CSckFactoryImp1()
	{
		;
	}
	virtual ~CSckFactoryImp1()
	{
		;
	}
public:
	virtual int cltSocketInit();//客户端初始化 获取handle
	virtual int cltSocketSend(unsigned char *buf, int buflen);//客户端发报文
	virtual int cltSocketRev(unsigned char *buf, int *buflen);//客户端收报文
	virtual int cltSocketDestory();//释放资源
private:
	unsigned char *p;
	int len;
};

