#include "stdafx.h"
#include "BMPfile.h"
#include "stdio.h"
BMPFile::BMPFile()
{
    file=NULL;
    memset(&fileheader,0,sizeof(fileheader));
    memset(&infoheader,0,sizeof(infoheader));
	filesize=0;
    totalpixeldata=0;
	pixeldataoffset=0;
    bmpformat=0;
    width=0;
    height=0;
    filebuffer=NULL;
}

BMPFile::~BMPFile()
{
	memset(&fileheader,0,sizeof(fileheader));
	memset(&infoheader,0,sizeof(infoheader));
	filesize=0;
    totalpixeldata=0;
	pixeldataoffset=0;
    bmpformat=0;
    width=0;
    height=0;
	if(file!=NULL)
	{
		close();
	}
    if(filebuffer!=NULL)
    {
		delete filebuffer;
		filebuffer=NULL;
    }
}

bool BMPFile::open(char *filename)
{
    file=fopen(filename,"rb");
	if(file==NULL)
    {
        return false;
    }
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
	if(filesize>MAXFILESIZE)
	{
		close();
		return false;
	}
	return true;
}

bool BMPFile::check()
{
	if(file==NULL)
	{
		return false;
	}
	if(filesize<=56)
	{
		return false;
	}
	unsigned char head[56];
	fseek(file, 0, SEEK_SET);
    if(!fread(head,1,56,file))
	{
		return false;
	}
    memcpy(&fileheader,head,sizeof(fileheader));
    memcpy(&infoheader,head+14,sizeof(infoheader));
	if(fileheader.bfType!=19778) return false;
	if(fileheader.bfSize!=filesize) return false;
	pixeldataoffset=fileheader.bfOffBits;//54

	if(infoheader.biCompression!=0) return false; 
	if(infoheader.biBitCount!=24&&infoheader.biBitCount!=32) return false;
	
	pixeldataoffset=54;
	
	totalpixeldata=(filesize-54);
	bmpformat=(infoheader.biBitCount==24?BMP24:BMP32);
	totalusefulpixeldata=bmpformat==BMP24?totalpixeldata:totalpixeldata;
	width=infoheader.biWidth;
	height=infoheader.biHeight;
	return true;
}

bool BMPFile::close()
{
	memset(&fileheader,0,sizeof(fileheader));
	memset(&infoheader,0,sizeof(infoheader));
	filesize=0;
    totalpixeldata=0;
	pixeldataoffset=0;
    bmpformat=0;
    width=0;
    height=0;
	if(file!=NULL)
	{
		fclose(file);
		file=NULL;
	}
    if(filebuffer!=NULL)
    {
		delete filebuffer;
		filebuffer=NULL;
    }
	return true;
}

bool BMPFile::readAllToBuffer()
{
	if(file==NULL)
    {
		return false;
	}
	if(filebuffer!=NULL)
	{
		delete filebuffer;
		filebuffer=NULL;
	}
	try
	{
		filebuffer=new unsigned char[filesize];
		fseek(file, 0, SEEK_SET);
        if(fread(filebuffer,1,filesize,file))
		{
			return true;
		}
		return false;
	}
	catch (...)
	{
		filebuffer=NULL;
		return false;
	}
}

bool BMPFile::readPixelBitsFromBuffer(unsigned int pixelIndex, unsigned int* value,unsigned int mask)
{
    if(pixelIndex<0||pixelIndex>=totalpixeldata)
	{
		return false;
	}
	else
	{
		*value=filebuffer[pixeldataoffset+pixelIndex]&mask;
		return true;
	}
}

bool BMPFile::writePixelBitsToBuffer(unsigned int pixelIndex, unsigned int value,unsigned int mask)
{
	if(pixelIndex<0||pixelIndex>=totalpixeldata)
	{
		return false;
	}
	else
	{
		filebuffer[pixeldataoffset+pixelIndex]&=~mask;
		filebuffer[pixeldataoffset+pixelIndex]|=value&mask;
		return true;
	}
}

bool BMPFile::saveBufferToFile(char *filename)
{
	if(filebuffer==NULL) return false;
	FILE *wfile=fopen(filename,"w+");
	if(wfile==NULL) 
	{
		return false;
	}
	else
	{
		fwrite(filebuffer,1,filesize,wfile);
		fclose(wfile);
		return true;
	}
}