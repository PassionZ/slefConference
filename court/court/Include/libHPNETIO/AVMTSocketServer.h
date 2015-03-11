// AVMTSocketServer.h: interface for the AVMTSocketServer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVMTSOCKETSERVER_H__
#define __AVMTSOCKETSERVER_H__

#include "AVMTSocketTCP.h"
#include "../libHPBaseclass/AVUtil.h"
#include "AVIOEvent.h"

class AFX_EXT_CLASS AVMTSocketServer;
class AFX_EXT_CLASS AVMTSocketServerNotify
{
public:
	AVMTSocketServerNotify(void){};
	virtual~AVMTSocketServerNotify(void){};
public:
	virtual bool OnAVMTSocketServerNotifyConnected(AVMTSocketServer*pAVMTSocketServer,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen)=0;
	virtual void OnAVMTSocketServerNotifyFailed(AVMTSocketServer*pAVMTSocketServer)=0;
};

class AFX_EXT_CLASS AVMTSocketServer  
	: public AVIOEvent
{
public:
	AVMTSocketServer(AVMTSocketServerNotify&rNotify);
	virtual ~AVMTSocketServer(void);
public:
	bool Connect(SOCKET hSocket);
	void ReleaseConnections(void);
	bool IsExpired(void);
	
	bool OnRead(void);
	bool OnWrite(void);
	void OnError(void);
	bool WantReading(void);
	bool WantWriting(void);
protected:
	AVMTSocketServerNotify&			m_rNotify;
	AVMTSocketTCP					m_AVMTSocketTCP;
	unsigned long					m_ulType;
	void*							m_pData;
	int								m_nLen;
	int								m_nBytes;
	unsigned long					m_ulStartTimestamp;

	char							m_pHeaderData[8];
	int								m_nHeaderLen;
};

#endif 
