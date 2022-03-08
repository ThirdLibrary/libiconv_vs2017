#include <iostream>
#include <string>
#include <fstream>
#include "iconv.h"
extern "C" {
#include <stdio.h>
}
using namespace std;


int ChangeCode(const char* pFromCode,
	const char* pToCode,
	const char* pInBuf,
	size_t* iInLen,
	char* pOutBuf,
	size_t* iOutLen);

int main(int argc, char* argv[])
{
	char sInBuf[100];
	char sOutBuf[100];
	size_t iInLen = 0;
	size_t iOutLen = 100;
	int iRet;
	strcpy_s(sInBuf, "��������.ini");
	memset(sOutBuf, 0x00, 100);
	iInLen = strlen(sInBuf);
	iRet = ChangeCode("GBK", "UTF-8", sInBuf, &iInLen, sOutBuf, &iOutLen);
	wofstream fp("./text.txt", ios::out | ios::app);
	fp << sOutBuf;
	fp.close();
	return 0;
}

int ChangeCode(const char* pFromCode,
	const char* pToCode,
	const char* pInBuf,
	size_t* iInLen,
	char* pOutBuf,
	size_t* iOutLen)
{
	int iRet;
	//���ַ���ת��
	iconv_t hIconv = iconv_open(pToCode, pFromCode);
	if (-1 == (int)hIconv)
	{
		return -1;//��ʧ�ܣ����ܲ�֧�ֵ��ַ���
	}
	//��ʼת��
	iRet = iconv(hIconv, (const char**)(&pInBuf), iInLen, (char**)(&pOutBuf), iOutLen);
	//�ر��ַ���ת��
	iconv_close(hIconv);
	return iRet;
}

































