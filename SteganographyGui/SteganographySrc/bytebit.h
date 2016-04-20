#ifndef _BYTEBIT_H_
#define _BYTEBIT_H_

class Bits
{
public:
	unsigned char* bytes;
	int totalbytes;
	int totalbits;
	Bits();
	Bits(void *data,int size);
	~Bits();
	void init(void*data,int size);
	int readBit(int index);
	void writeBit(int index,int bitvalue);

};
#endif