// HMTSocketTCP.h: interface for the HMTSocketTCP class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __HMTSOCKETTCP_H__
#define __HMTSOCKETTCP_H__

#include "HMTSocket.h"

class AFX_EXT_CLASS HMTSocketTCP 
	: public HMTSocket  
{
public:
	HMTSocketTCP(void);
	virtual ~HMTSocketTCP(void);
public:
	bool Bind(unsigned long ulIP,unsigned short usPort);
	bool Connect(unsigned long ulIP,unsigned short usPort,unsigned long ulInterface);
	int Receive(char*pBuffer,int nLen);
	int Send(const char*pData,int nLen);
	SOCKET Accept(void);
};

#endif 
