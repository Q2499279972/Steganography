#ifndef _BMPFILE_H_
#define _BMPFILE_H_

#if 0
#ifdef _WIN32 

#pragma pack(push)
#pragma pack(1)
//rewrite this
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;        //2B
    unsigned int   bfSize;       //4B
    unsigned short bfReserved1;   //2B
    unsigned short bfReserved2;   //2B
    unsigned int   bfOffBits;    //4B
}BITMAPFILEHEADER;//14Bytes

typedef struct tagBITMAPINFOHEADER{
    int biSize;              //4B
    int biWidth;             //4B
    int biHeight;            //4B 
    short biPlanes;          //2B
    short biBitCount;        //2B
    int biCompression;       //4B
    int biSizeImage;         //4B
    int biXPelsPerMeter;     //4B
    int biYPelsPerMeter;     //4B 
    int biClrUsed;           //4B
    int biClrImportant;      //4B
}BITMAPINFOHEADER;//40Bytes

#pragma pack(pop)

#endif
#endif 

class BMPFile
{
	enum BMPTYPE
	{	
		BMP24=1,
		BMP32=2,
		BMPOTHER=3,
	};
public:   
    static const int MAXFILESIZE=1024*1024*50;//WILL NOT HANDLE FILE LARGER THAN THIS VALUE
	FILE *file;
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
	long filesize;
    unsigned int totalpixeldata;
	unsigned int totalusefulpixeldata;
	unsigned int pixeldataoffset;
    unsigned int       bmpformat;// I ONLY USE 24BITS or 32BITS(BUT NOT USE ALPHA CHANNEL)
    int width,height;
    unsigned char* filebuffer;

private:

public:
    BMPFile();
    ~BMPFile();
    bool open(char *filename);
	bool check();
    bool close();
    bool readAllToBuffer();
    bool readPixelBitsFromBuffer(unsigned int pixelIndex, unsigned int *value,unsigned int mask);
    bool writePixelBitsToBuffer(unsigned int pixelIndex, unsigned int value,unsigned int mask);
    bool saveBufferToFile(char *filename);
};

#endif