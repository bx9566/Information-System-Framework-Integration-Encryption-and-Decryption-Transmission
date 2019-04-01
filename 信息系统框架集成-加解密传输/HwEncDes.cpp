#include "HwEncDes.h"
#include "des加密解密.h"


// 加密 明文--》密文
int HwEncDes::EncData(unsigned char *plain, int plainlen, unsigned char *cryptdata, int *cryptdatalen)
{
	int ret = 0;
	//用户使用的函数 加密
	cout << "华为加密" << endl;
	ret = des::DesEnc(plain, plainlen, cryptdata, cryptdatalen);
	if (ret != 0)
	{
		printf("func DesEnc() err:%d\n", ret);
	}
	
	
	return ret;
}
// 解密 密文-->>明文
int  HwEncDes::DecData(unsigned char *cryptdata, int cryptdatalen, unsigned char *plain, int *plainlen)
{
	int ret = 0;
	// 用户使用函数 des 解密
	cout << "华为解密" << endl;
	ret = des::DesDec(cryptdata, cryptdatalen, plain, plainlen);
	if (ret != 0)
	{
		printf("func DesDec() err:%d\n", ret);
	}

	
	return ret;
}