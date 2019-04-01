#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "SocketProtocol.h"
#include "SckFactoryImp1.h"
#include "SckFactoryImp2.h"
#include "CEncDesProtocol.h"
#include "HwEncDes.h"
#include "des加密解密.h"
//面对抽象类编程，框架实现
int SckSendAndRev02(CSocketProtocol *sp, unsigned char *in, int inlen, unsigned char *out, int *outlen)
//int SckSendAndRev(CSocketProtocol *sp, unsigned char *in, int inlen, unsigned char *out, int *outlen)
{
	int ret = 0;
	ret = sp->cltSocketInit();
	if (ret != 0)
	{
		goto End;
	}
	ret = sp->cltSocketSend(in, inlen);
	if (ret != 0)
	{
		goto End;
	}
	//cout << "第一个厂商socket产品发送内容" << in << endl;
	ret = sp->cltSocketRev(out, outlen);
	if (ret != 0)
	{
		goto End;
	}
	//cout << "第一个厂商socket产品接收的内容" << out << endl;
End:
	ret = sp->cltSocketDestory();
	return 0;
}
//该框架式一个函数 要改为类的形式 见mainclass03_框架类.cpp
int SckSendAndRecDecEn03(CSocketProtocol *sp, CEncDesProtocol *ed, unsigned char *in, int inlen, unsigned char *out, int *outlen)
{
	int ret = 0;
	unsigned char data[4096];
	int datalen = 0;
	ret = sp->cltSocketInit();
	if (ret != 0)
	{
		goto End;
	}

	ret = ed->EncData(in, inlen, data, &datalen);// 数据发送之前要加密，发送的是密文
	if (ret != 0)
	{
		goto End;
	}

	ret = sp->cltSocketSend(data, datalen);// 发送密文
	if (ret != 0)
	{
		goto End;
	}

	ret = sp->cltSocketRev(data, &datalen);// 收到的是密文，要进行解密
	if (ret != 0)
	{
		goto End;
	}

	ret = ed->DecData(data, datalen, out, outlen);//解密
	if (ret != 0)
	{
		goto End;
	}
End:
	ret = sp->cltSocketDestory();
	return 0;
}
//框架 
int main02()
{
	int ret = 0;
	unsigned char in[4096];
	int inlen;
	unsigned char out[4096];
	int outlen = 0;
	//strcpy((char*)in, "a");
	inlen = 9;
	CSocketProtocol *sp = NULL;
	//第一个厂商socket收发产品测试
	sp = new CSckFactoryImp1;
	/*ret = SckSendAndRev02(sp, in, inlen, out, outlen);
	if (ret != 0)
	{
		printf("func SckSendAndRev() err:%d\n", ret);
		return ret;
	}

	delete sp;//想通过父类指针，释放所有的子类对象的资源，应使用虚析构函数*/
	CSocketProtocol *sp2 = NULL;
	//第二个厂商socket收发产品测试
	sp2 = new CSckFactoryImp2;
	/*ret = SckSendAndRev02(sp2, in, inlen, out, outlen);
	if (ret != 0)
	{
		printf("func SckSendAndRev() err:%d\n", ret);
		return ret;
	}

	//delete sp2;*/
	// 加解密

	CEncDesProtocol *ed = NULL;
	ed = new HwEncDes;
	ret = SckSendAndRecDecEn03(sp2, ed, in, inlen, out, &outlen);//SckSendAndRecDecEn03
	if (ret != 0)
	{
		cout << "func SckSendAndRecDecEnc() err:" << ret << endl;
		return ret;
	}
	delete ed;
	system("pause");
	return ret;
}
