#include "des加密解密.h"
#include<iostream>
using namespace std;
// 用户使用函数 desenc 加密
int des::DesEnc(unsigned char *pInData, int nInDataLen, unsigned char *poutData, int *poutDataLen)
{
	cin >> *pInData;
	if ('b' == *pInData)
	{ 
		*poutData = 'x';
	}
	if ('x' == *pInData)
	{
		*poutData = 'm';
	}
	cout << "加密后的暗文" << *poutData << endl;
	
	return 0;
}
// 用户使用函数 desdec 解密
int des::DesDec(unsigned char *poutData, int poutDataLen,unsigned char *pInData, int *nInDataLen )
{
	if ('x' == *poutData)
	{
		*pInData = 'b';//(unsigned char)
	}
	if ('m' == *poutData)
	{
		*pInData = 'x';
	}
	cout << "解密后的明文" << *pInData << endl;
	
	return 0;
}