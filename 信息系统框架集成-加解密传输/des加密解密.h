#pragma once

class des
{
public://加密解密的接口
	//用户使用的函数 加密
	virtual int DesEnc(unsigned char *pInData,int nInDataLen,unsigned char *poutData,int *poutDataLen);
	// 用户使用函数 des 解密
	virtual int DesDec(unsigned char *pInData, int nInDataLen, unsigned char *poutData, int *poutDataLen);
};

