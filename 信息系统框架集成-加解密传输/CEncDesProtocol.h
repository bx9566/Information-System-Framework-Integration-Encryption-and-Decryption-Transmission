#pragma once

// 加密 解密  抽象类协议

class CEncDesProtocol
{
public:
	CEncDesProtocol()
	{

	}
	virtual~CEncDesProtocol()
	{

	}
	// 加密 明文--》密文
	virtual int EncData(unsigned char *plain, int plainlen, unsigned char *cryptdata, int *cryptdatalen) = 0;
	// 解密 密文-->>明文
	virtual int DecData(unsigned char *cryptdata, int cryptdatalen, unsigned char *plain, int *plainlen) = 0;
};