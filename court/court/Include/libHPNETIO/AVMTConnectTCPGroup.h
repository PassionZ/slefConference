// AVMTConnectTCPGroup.h: interface for the AVMTConnectTCPGroup class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVMTCONNECTTCPGROUP_H__
#define __AVMTCONNECTTCPGROUP_H__

#include "AVMTConnectTCP.h"
#include "../libHPBaseclass/AVUtil.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <list>

typedef std::list<AVMTConnectTCP*>		ListAVMTConnectTCP;

class AFX_EXT_CLASS AVMTConnectTCPGroupNotify
{
public:
	AVMTConnectTCPGroupNotify(void){};
	virtual~AVMTConnectTCPGroupNotify(void){};
public:
	virtual void OnAVMTConnectTCPGroupNotifyConnected(SOCKET hSocket,unsigned long ulIP,unsigned short usPort)=0;
	virtual void OnAVMTConnectTCPGroupNotifyFailed(void)=0;
};

class AFX_EXT_CLASS AVMTConnectTCPGroup  
	: public AVMTConnectTCPNotify
	, public AVThread
{
public:
	AVMTConnectTCPGroup(AVMTConnectTCPGroupNotify&rNotify);
	virtual ~AVMTConnectTCPGroup(void);
public:
	bool Connect(void);
	void ReleasConnections(void);
	void AddConnect(unsigned long ulIP,unsigned short usPort,unsigned long ulInterface=0);
	void AddConnectHTTPProxy(unsigned long ulIP,unsigned short usPort,const char*cszProxyHost,unsigned short usProxyPort,const char*cszUser,const char*cszPassword);
	void AddConnectSOCKS5(unsigned long ulIP,unsigned short usPort,const char*cszProxyHost,unsigned short usProxyPort,const char*cszUser,const char*cszPassword);
protected:
	void ThreadProcMain(void);
	void OnAVMTConnectTCPNotifyConnected(AVMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	void OnAVMTConnectTCPNotifyFailed(AVMTConnectTCP*pAVMTConnectTCP);
	void ClearConnecting(void);
	void ClearDone(void);
protected:
	AVMTConnectTCPGroupNotify&	m_rNotify;
	bool						m_bWantToStop;
	bool						m_bInitialized;
	AVCritSec					m_AVCritSecListAVMTConnectTCP;
	ListAVMTConnectTCP			m_ListAVMTConnectTCPConnecting;
	ListAVMTConnectTCP			m_ListAVMTConnectTCPDone;
	bool						m_bConnected;
};

#endif 
