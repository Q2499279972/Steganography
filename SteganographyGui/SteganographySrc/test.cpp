// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Steganography.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Steganography S;
	S.SteganographyTo("ori.txt","ori.bmp","out.bmp");
	S.SteganographyFrom("out.bmp","out.txt");
	return 0;
}

