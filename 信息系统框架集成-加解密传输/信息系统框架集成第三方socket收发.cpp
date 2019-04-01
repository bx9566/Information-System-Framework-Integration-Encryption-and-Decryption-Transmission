#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "SocketProtocol.h"
#include "SckFactoryImp1.h"
#include "SckFactoryImp2.h"
//面对抽象类编程，框架实现
int SckSendAndRev01(CSocketProtocol *sp, unsigned char *in, int inlen, unsigned char *out, int *outlen)
//int SckSendAndRev(CSocketProtocol *sp, unsigned char *in, int inlen, unsigned char *out, int *outlen)
{
	int ret = 0;
	ret = sp->cltSocketInit();
	if (ret != 0)
	{
		goto End;
	}
	ret = sp->cltSocketSend(in,inlen);
	if (ret != 0)
	{
		goto End;
	}
	//cout << "第一个厂商socket产品发送内容" << in << endl;
	ret = sp->cltSocketRev(out,outlen);
	if (ret != 0)
	{
		goto End;
	}
	//cout << "第一个厂商socket产品接收的内容" << out << endl;
	End:
	ret = sp->cltSocketDestory();
	return 0;
}
//框架 
int main01()
{
	int ret = 0;
	unsigned char in[4096];
	int inlen;
	unsigned char out[4096];
	int outlen=0;
	strcpy((char*)in, "aaaaaaaaaaa");
	inlen = 9;
    CSocketProtocol *sp = NULL;
	//第一个厂商socket收发产品测试
	sp = new CSckFactoryImp1;
	ret = SckSendAndRev01(sp, in, inlen, out, &outlen);
	if (ret != 0)
	{
		printf("func SckSendAndRev() err:%d\n",ret);
		return ret;
	}
	
	delete sp;
	CSocketProtocol *sp2 = NULL;
	//第一个厂商socket收发产品测试
	sp2 = new CSckFactoryImp2;
	ret = SckSendAndRev01(sp2, in, inlen, out, &outlen);
	if (ret != 0)
	{
		printf("func SckSendAndRev() err:%d\n", ret);
		return ret;
	}

	delete sp2;
	system("pause");
	return ret;
}
 