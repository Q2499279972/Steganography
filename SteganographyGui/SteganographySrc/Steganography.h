#ifndef _STEGANOGRAPHY_H_
#define _STEGANOGRAPHY_H_

class Steganography
{
public:
	static const unsigned int MAGICNUM=123;
	struct SteganographyHead
    {
        unsigned int head;
        unsigned int crc;
        unsigned int type;
        unsigned int totalbytes;
        unsigned int firstoffset;
		unsigned int havefilename;
		unsigned int originalfilesize;
		unsigned int reserve;
		unsigned char Props[8];
		unsigned char filename[1];//...
    };
	Steganography();
	~Steganography();
	int LzmaOriginalFile(char *filename,unsigned char** outdata,int *outdatalen,unsigned char *props,unsigned int* orisize,int method);
    int SteganographyTo(char *srcfile, char *bmpfile, char* outfile);
    int SteganographyFrom(char *srcfile, char* outfile);
};

#endif
