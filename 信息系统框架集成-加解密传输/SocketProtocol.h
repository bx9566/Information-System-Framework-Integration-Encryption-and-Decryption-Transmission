#pragma once
class CSocketProtocol
{
public:
	CSocketProtocol()
	{ 
		;
	}
	virtual ~CSocketProtocol()//虚析构函数---》delete sp;
	{
		;
	}
public:
	virtual int cltSocketInit() = 0;//客户端初始化 获取handle
	virtual int cltSocketSend(unsigned char *buf,int buflen) = 0;//客户端发报文
	virtual int cltSocketRev(unsigned char *buf,int *buflen) = 0;//客户端收报文
	virtual int cltSocketDestory() = 0;//释放资源
};

