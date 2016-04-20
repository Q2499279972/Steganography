#include "stdafx.h"
#include "BMPfile.h"
#include "Steganography.h"
#include "LzmaLib.h"
#include "bytebit.h"
#include "xor.h"
#pragma comment(lib,"..\\lib\\LZMA.lib") 
Steganography::Steganography()
{
}
Steganography::~Steganography()
{
}

int Steganography::LzmaOriginalFile(char *filename,unsigned char** outdata,int *outdatalen,unsigned char *props,unsigned int *orisize,int method)
{
	FILE* file=fopen(filename,"rb");
	if(file==NULL) return false;
	fseek(file, 0, SEEK_END);

    unsigned int filesize=ftell(file);
	unsigned int filesize2=2*filesize+2048;
	unsigned char* filedata;
	unsigned char* filedata2;
	*orisize=filesize;
	try
	{
		filedata=new unsigned char[filesize];
	}
	catch(...)
	{
		return false;
	}

	try
	{
		filedata2=new unsigned char[filesize2];
	}
	catch(...)
	{
		delete filedata;
		return false;
	}

	fseek(file, 0, SEEK_SET);
	if(!fread(filedata,1,filesize,file))
	{
		delete filedata;
		delete filedata2;
		return false;
	}

	unsigned char outProps[6]={0};
	unsigned int  outPropsSize=5;
	if(		SZ_OK!=
			LzmaCompress(
			filedata2,&filesize2, 
			filedata, filesize,
			outProps, &outPropsSize, /* *outPropsSize must be = 5 */
			9,      /* 0 <= level <= 9, default = 5 */
			1<<24,  /* default = (1 << 24) */
			3,        /* 0 <= lc <= 8, default = 3  */
			0,        /* 0 <= lp <= 4, default = 0  */
			2,        /* 0 <= pb <= 4, default = 2  */
			32,        /* 5 <= fb <= 273, default = 32 */
			1 /* 1 or 2, default = 2 */
			))
	{
		delete filedata;
		delete filedata2;
		return false;	
	};

	delete filedata;
	//realloc the memory ???
	*outdata=filedata2;
	*outdatalen=filesize2;
	props[0]=outProps[0];
	props[1]=outProps[1];
	props[2]=outProps[2];
	props[3]=outProps[3];
	props[4]=outProps[4];

	return true;
}
int Steganography::SteganographyTo(char *srcfile, char *bmpfile, char* outfile)
{
	BMPFile oriBMP;
	if(!oriBMP.open(bmpfile)) return false;
	if(!oriBMP.check()) return false;
	unsigned char* srcfiledatalzma=NULL;
    int srcfiledatalzmasize;
	unsigned char lzmaprops[6];

	unsigned int filesize=0;
	
    if(LzmaOriginalFile(srcfile,&srcfiledatalzma,&srcfiledatalzmasize,lzmaprops,&filesize,NULL)==0) return false;

	XOR(srcfiledatalzma,srcfiledatalzmasize,(unsigned char *)"this is test",12);//bad ,just test
	
	SteganographyHead head;
	memset(&head,0,sizeof(head));
	head.crc=0;//not use now
	head.filename[0]=0;//not use now
	head.firstoffset=sizeof(head)*8+0;//no filename,so add zero
	head.havefilename=0;
	head.head=MAGICNUM;
	head.Props[0]=lzmaprops[0];//put it here first...
	head.Props[1]=lzmaprops[1];
	head.Props[2]=lzmaprops[2];
	head.Props[3]=lzmaprops[3];
	head.Props[4]=lzmaprops[4];
	head.originalfilesize=filesize;
	head.reserve=0;
	head.totalbytes=srcfiledatalzmasize;
	head.type=0;//not use now

	//check bmp space is avaliable ??
	unsigned int totalbytes=sizeof(head)+srcfiledatalzmasize;
	if(totalbytes*8>=oriBMP.totalusefulpixeldata) 
	{
		delete srcfiledatalzma;
		return false;
	}
	if(!oriBMP.readAllToBuffer())
	{
		delete srcfiledatalzma;
		return false;
	}
	
	int i;
	Bits bits;
	bits.init(&head,sizeof(head));
	for(i=0;i<bits.totalbits;i++)
	{
		oriBMP.writePixelBitsToBuffer(i,bits.readBit(i),0x01);
	}
	bits.init(srcfiledatalzma,srcfiledatalzmasize);
	for(i=0;i<bits.totalbits;i++)
	{
		oriBMP.writePixelBitsToBuffer(i+head.firstoffset,bits.readBit(i),0x01);
	}
	delete srcfiledatalzma;
	if(	oriBMP.saveBufferToFile(outfile))
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned char buffer2[1024*1024*20];//20M
unsigned int buffer2len=1024*1024*20;
int Steganography::SteganographyFrom(char *srcfile, char* outfile)
{
	BMPFile oriBMP;
	if(!oriBMP.open(srcfile)) 
	{	
		return false;
	}
	if(!oriBMP.check()) 
	{
		return false;
	}
	if(!oriBMP.readAllToBuffer()) 
	{
		return false;
	}
	SteganographyHead head;
	memset(&head,0,sizeof(head));
	Bits bits;
	bits.init(&head,sizeof(head));
	int i;
	for(i=0;i<bits.totalbits;i++)
	{
		unsigned int bitvalue;
		oriBMP.readPixelBitsFromBuffer(i,&bitvalue,0x01);
		bits.writeBit(i,bitvalue);
	}
	if(head.head!=MAGICNUM)
	{
		return false;//TOO SIMPLE !!
	}
	if(head.firstoffset+head.totalbytes*8>oriBMP.totalusefulpixeldata)
	{
		return false;
	}
	
	unsigned char *buffer;
	buffer=new unsigned char[head.totalbytes];
	bits.init(buffer,head.totalbytes);
	for(i=0;i<bits.totalbits;i++)
	{
		unsigned int bitvalue;
		oriBMP.readPixelBitsFromBuffer(i+head.firstoffset,&bitvalue,0x01);
		bits.writeBit(i,bitvalue);
	}

	buffer2len=head.originalfilesize;
	
	XOR(buffer,head.totalbytes,(unsigned char *)"this is test",12);

	if(SZ_OK!=LzmaUncompress(buffer2, &buffer2len, buffer, &head.totalbytes, head.Props, 5))
	{
		delete buffer;
		return false;
	}

	FILE *file=fopen(outfile,"wb+");
	fwrite(buffer2,1,buffer2len,file);
	fclose(file);
	delete buffer;
	return true;
}


