// AVMTTCPListener.h: interface for the AVMTTCPListener class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVMTTCPLISTENER_H__
#define __AVMTTCPLISTENER_H__

#include "AVMTSocketTCP.h"
#include "AVIOEvent.h"

class AVMTTCPListenerNotify
{
public:
	AVMTTCPListenerNotify(void){};
	virtual~AVMTTCPListenerNotify(void){};
public:
	virtual void OnAVMTTCPListenerNotifyAccpted(SOCKET hSocket)=0;
};

class AVMTTCPListener  
	: public AVIOEvent
{
public:
	AVMTTCPListener(AVMTTCPListenerNotify&rNotify);
	virtual ~AVMTTCPListener(void);
public:
	bool Connect(unsigned short usPort);
	void ReleaseConnections(void);
	unsigned short GetPort(void);
	
	bool OnRead(void);
	bool OnWrite(void);
	bool WantWriting(void){return false;};
	bool WantReading(void){return true;};
	void OnError(void){return;};
protected:
	AVMTTCPListenerNotify&	m_rNotify;
	AVMTSocketTCP			m_AVMTSocketTCP;
};

#endif 