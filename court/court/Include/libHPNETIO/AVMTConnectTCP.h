// AVMTConnectTCP.h: interface for the AVMTConnectTCP class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVMTCONNECTTCP_H__
#define __AVMTCONNECTTCP_H__

#include "AVMTSocketTCP.h"
#include "../libHPBaseclass/AVThread.h"
#include <string>

class AFX_EXT_CLASS AVMTConnectTCP;
class AFX_EXT_CLASS AVMTConnectTCPNotify
{
public:
	AVMTConnectTCPNotify(void){};
	virtual~AVMTConnectTCPNotify(void){};
public:
	virtual void OnAVMTConnectTCPNotifyConnected(AVMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket)=0;
	virtual void OnAVMTConnectTCPNotifyFailed(AVMTConnectTCP*pAVMTConnectTCP)=0;
};

class AFX_EXT_CLASS AVMTConnectTCP  
	: public AVThread
{
public:
	AVMTConnectTCP(AVMTConnectTCPNotify&rNotify);
	virtual~AVMTConnectTCP(void);
public:
	virtual bool Connect(unsigned long ulIP,unsigned short usPort,unsigned long ulInterface);
	virtual void ReleaseConnections(void);
	virtual unsigned long GetIP(void);
	virtual unsigned short GetPort(void);
protected:
	virtual void ThreadProcMain(void);
protected:
	AVMTConnectTCPNotify&	m_rNotify;
	AVMTSocketTCP			m_AVMTSocketTCP;
	unsigned long			m_ulIP;
	unsigned short			m_usPort;
	unsigned long			m_ulInterface;
};

class AFX_EXT_CLASS AVMTConnectHTTPProxy
	: public AVMTConnectTCP
{
public:
	AVMTConnectHTTPProxy(AVMTConnectTCPNotify&rNotify,const char*cszProxyHost,unsigned short usProxyPort,const char*cszUser,const char*cszPassword);
	virtual~AVMTConnectHTTPProxy(void);
protected:
	virtual void ThreadProcMain(void);
protected:
	std::string			m_strProxyHost;
	unsigned short		m_usProxyPort;
	std::string			m_strUser;
	std::string			m_strPassword;
};

class AFX_EXT_CLASS AVMTConnectSOCKS5
	: public AVMTConnectTCP
{
public:
	AVMTConnectSOCKS5(AVMTConnectTCPNotify&rNotify,const char*cszProxyHost,unsigned short usProxyPort,const char*cszUser,const char*cszPassword);
	virtual~AVMTConnectSOCKS5(void);
protected:
	virtual void ThreadProcMain(void);
protected:
	std::string			m_strProxyHost;
	unsigned short		m_usProxyPort;
	std::string			m_strUser;
	std::string			m_strPassword;
};

#endif 
