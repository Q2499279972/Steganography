#ifndef _MYMSG_H_
#define _MYMSG_H_
#include <stdarg.h> 

class MYMSG
{
public:	
	MYMSG(){}
	~MYMSG(){}
	void MSGSend(int type,char* msg,...);
	void MSGSend(char* msg,...);
};
#endif
