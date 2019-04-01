#pragma once
#include<iostream>
using namespace std;
#include "CEncDesProtocol.h"
#include "des加密解密.h"
class HwEncDes : public CEncDesProtocol,public des
{
public:
	// 加密 明文--》密文
	virtual int EncData(unsigned char *plain, int plainlen, unsigned char *cryptdata, int *cryptdatalen);
	// 解密 密文-->>明文
	virtual int DecData(unsigned char *cryptdata, int cryptdatalen, unsigned char *plain, int *plainlen);
};


