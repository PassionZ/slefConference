// HMTConnectTCP.h: interface for the HMTConnectTCP class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __HMTCONNECTTCP_H__
#define __HMTCONNECTTCP_H__

#include "HMTSocketTCP.h"
#include "HThread.h"
#include <string>

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS HMTConnectTCP;

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS HMTConnectTCPNotify
{
public:
	HMTConnectTCPNotify(void){};
	virtual~HMTConnectTCPNotify(void){};

	virtual void OnAVMTConnectTCPNotifyConnected(HMTConnectTCP* pAVMTConnectTCP,SOCKET hSocket)=0;
	virtual void OnAVMTConnectTCPNotifyFailed(HMTConnectTCP* pAVMTConnectTCP)=0;
};

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS HMTConnectTCP : public HThread
{
public:
	HMTConnectTCP(HMTConnectTCPNotify& rNotify);
	virtual~HMTConnectTCP(void);

public:
	virtual bool Connect(const std::string& serveraddr,unsigned short serverport,const std::string& interfaceaddr);
	virtual void ReleaseConnections(void);
	virtual unsigned long GetIP(void);
	virtual unsigned short GetPort(void);

protected:
	HMTConnectTCPNotify&	m_rNotify;
	HMTSocketTCP			m_AVMTSocketTCP;
	std::string				m_serveraddr;
	unsigned short			m_serverport;
	std::string				m_interfaceaddr;

	virtual void ThreadProcMain(void);
};

////---------------------------------------------------------------------------------------
//class AFX_EXT_CLASS AVMTConnectHTTPProxy : public HMTConnectTCP
//{
//public:
//	AVMTConnectHTTPProxy(HMTConnectTCPNotify& rNotify,const std::string& proxyhost,unsigned short proxyport,const std::string& proxyuser,const std::string& proxypassword);
//	virtual~AVMTConnectHTTPProxy(void);
//	virtual bool Connect(const std::string& serveraddr,unsigned short serverport,const std::string& interfaceaddr);
//
//protected:
//	std::string			m_proxyhost;
//	unsigned short		m_proxyport;
//	std::string			m_proxyuser;
//	std::string			m_proxypassword;
//
//	virtual void ThreadProcMain(void);
//};
//
////---------------------------------------------------------------------------------------
//class AFX_EXT_CLASS AVMTConnectSOCKS5 : public HMTConnectTCP
//{
//public:
//	AVMTConnectSOCKS5(HMTConnectTCPNotify& rNotify,const std::string& proxyhost,unsigned short proxyport,const std::string& proxyuser,const std::string& proxypassword);
//	virtual~AVMTConnectSOCKS5(void);
//
//protected:
//	std::string			m_proxyhost;
//	unsigned short		m_proxyport;
//	std::string			m_proxyuser;
//	std::string			m_proxypassword;
//
//	virtual void ThreadProcMain(void);
//};

#endif 
