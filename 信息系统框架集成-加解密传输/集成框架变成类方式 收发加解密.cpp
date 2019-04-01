#define _CRT_SECURE_NO_WARNINGS
#include "iostream"

using namespace std;

#include "SocketProtocol.h"
#include "SckFactoryImp1.h"
#include "SckFactoryImp2.h"
#include "CEncDesProtocol.h"
#include "HwEncDes.h"
#include "des加密解密.h"

// 抽象类在多继承中的应用
//class MainOp : public CSocketProtocol,public CEncDesProtocol
//{
//public:
//
//protected:
//
//private:
//
//};

class MainOp
{
public:
	MainOp()
	{
		this->ed = NULL;
		this->sp = NULL;
	}
	MainOp(CSocketProtocol *sp,CEncDesProtocol *ed)
	{
		this->ed = ed;
		this->sp = sp;
	}
	void setSp(CSocketProtocol *sp)
	{
		this->sp = sp;
	}
	void setEd(CEncDesProtocol *ed)
	{
		this->ed = ed;
	}

public:
	int SckSendAndRec(unsigned char *in,int inlen,unsigned char *out,int *outlen)
	{ 
		int ret = 0;
		ret = this->sp->cltSocketInit();
		if ( ret != 0)
		{
			goto End;
		}
		ret = sp->cltSocketSend(in,inlen);
		if ( ret != 0)
		{
			goto End;
		}
		ret = sp->cltSocketRev(out,outlen);
		if ( ret != 0)
		{
			goto End;
		}
	End:
		ret = this->sp->cltSocketDestory();
		return 0;
	}

	//该框架式一个函数 改为类的形式 
	int SckSendAndRecDecEnc(unsigned char *in,int inlen,unsigned char *out,int *outlen)
	{ 
		int ret = 0;
		unsigned char data[4096];
		int datalen = 0;
		ret = this->sp->cltSocketInit();
		if ( ret != 0)
		{
			goto End;
		}

		ret = this->ed->EncData(in,inlen,data,&datalen);// 数据发送之前要加密，发送的是密文
		if ( ret != 0)
		{
			goto End;
		}

		ret = this->sp->cltSocketSend(data,datalen);// 发送密文
		if ( ret != 0)
		{
			goto End;
		}

		ret = sp->cltSocketRev(data,&datalen);// 收到的是密文，要进行解密
		if ( ret != 0)
		{
			goto End;
		}

		ret = ed->DecData(data,datalen,out,outlen);//解密
		if ( ret != 0)
		{
			goto End;
		}
	End:
		ret = sp->cltSocketDestory();
		return 0;
	}
protected:

private:
	CSocketProtocol *sp;
	CEncDesProtocol *ed;
};

//写一个框架
int main()
{
	int ret = 0;
	unsigned char in[4096];
	int inlen;
	unsigned char out[4096];
	int outlen = 0;

	strcpy((char *)in,"aaaaaabbbbbbbdddd");
	inlen = 9;

	CSocketProtocol *sp = NULL;
	CSocketProtocol *sp2 = NULL;
	sp = new CSckFactoryImp1;
	sp2 = new CSckFactoryImp2;

	CEncDesProtocol *ed = NULL;
	ed = new HwEncDes;
	
	MainOp *myMainOp = new MainOp;//此时调用无参构造函数MainOp()，需要设置，如下
	myMainOp->setSp(sp);
	myMainOp->setEd(ed);

	// 第二个厂商
	myMainOp->SckSendAndRec(in,inlen,out,&outlen);
	if ( ret != 0)
	{
		cout << "func SckSendAndRec() err:" << ret << endl;
		return ret;
	}

	//加解密
	ret = myMainOp->SckSendAndRecDecEnc(in,inlen,out,&outlen);
	if ( ret != 0)
	{
		cout << "func SckSendAndRecDecEnc() err:" << ret << endl;
		return ret;
	}

	MainOp *m2 = new MainOp(sp,ed);//此时调用有参构造函数，MainOp(CSocketProtocol *sp,CEncDesProtocol *ed）不需要设置
	m2->SckSendAndRecDecEnc(in,inlen,out,&outlen);
	if ( ret != 0)
	{
		cout << "func SckSendAndRecDecEnc() err:" << ret << endl;
		return ret;
	}

	delete sp;
	delete ed;
	delete myMainOp;
	delete sp2;
	delete m2;

	cout << "hello..."<< endl;

	system("pause");

}