#include "stdafx.h"
#include "bytebit.h"
#include "stdio.h"

Bits::Bits()
{
	bytes=NULL;
	totalbytes=0;
	totalbits=0;
}

Bits::Bits(void*data,int size)
{
	bytes=(unsigned char*)data;
	totalbytes=size;
	totalbits=size*8;
}

void Bits::init(void*data,int size)
{
	bytes=(unsigned char*)data;
	totalbytes=size;
	totalbits=size*8;
}

Bits::~Bits()
{
	bytes=NULL;
	totalbytes=0;
	totalbits=0;
}

int Bits::readBit(int index)
{
	return bytes[index/8]&(1<<(index&7))?1:0;
}

void Bits::writeBit(int index, int bitvalue)
{
	if(bitvalue)
		bytes[index/8]|=(1<<(index&7));
	else
		bytes[index/8]&=~(1<<(index&7));
}