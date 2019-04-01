#include<iostream>
using namespace std;

#include "SckFactoryImp2.h"
//第一个厂商产品入围 系统框架
int CSckFactoryImp2::cltSocketInit()
{
	p = NULL;
	len = 0;
	cout << "第二个厂商socket产品初始化" << endl;
	return 0;
}
//客户端初始化 获取handle
int CSckFactoryImp2::cltSocketSend(unsigned char *in, int inlen)
{
	//unsigned char *p = new unsigned char(sizeof(buf));

	p = (unsigned char *)malloc(sizeof(unsigned char)*inlen);
	if (p == NULL)
	{
		cout << "发送分配内存失败" << endl;
		return -1;
	}
	//cin >> in;
	memcpy(p, in, inlen);
	len = inlen;
	cout << "第二个厂商socket产品发送" << endl;
	cout << "输出发送值" << *in << endl;
	return 0;
}//客户端发报文
int CSckFactoryImp2::cltSocketRev(unsigned char *out, int *outlen)
{
	if (outlen == 0 || out == NULL)
	{
		return -1;
	}
	*outlen = this->len;
	memcpy(out, this->p, this->len);
	cout << "第二个厂商socket产品接收" << endl;
	cout << "输出接受值" << *out << endl;
	return 0;
}//客户端收报文 从服务器端缓存数据
int CSckFactoryImp2::cltSocketDestory()
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
		len = 0;
	}
	cout << "第二个厂商socket产品释放资源" << endl;
	return 0;
}//释放资源
