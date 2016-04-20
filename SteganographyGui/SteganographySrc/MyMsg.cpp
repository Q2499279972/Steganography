#include "stdafx.h"
#include "MyMsg.h"

void MYMSG::MSGSend(int type,char* msg,...)
{
	switch (type)
	{
		case 1:
		{
			va_list argptr;
			va_start(argptr,msg);
			vprintf(msg,argptr);
			va_end(argptr);
			break;
		}
		case 2:
		{
			va_list argptr;
			va_start(argptr,msg);
			char buf[1024];
			vsnprintf(buf,1024,msg,argptr);
			printf(buf);
			va_end(argptr);
			break;
		}
		default:
		{
			break;
		}
	}
	return;
}


void MYMSG::MSGSend(char* msg,...)
{
	va_list argptr;
	va_start(argptr,msg);
	vprintf(msg,argptr);
	va_end(argptr);
	return;
}
