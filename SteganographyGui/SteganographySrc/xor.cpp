#include "stdafx.h"
#include "xor.h"
#include "stdio.h"
int XOR(unsigned char *src, int srcLen, unsigned char *mask, int maskLen)
{
	if(maskLen==0) return 0;
	int srcIndex=0;
	int maskIndex=0;
	while(srcIndex<srcLen)
	{
		src[srcIndex]^=mask[maskIndex];
		maskIndex++;
		if(maskIndex>=maskLen) maskIndex=0;
		srcIndex++;
	}
	return 0;
}
