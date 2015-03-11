#ifndef __HPP2PSESSION_H__
#define __HPP2PSESSION_H__

#include <vector>

#include "HPP2PSocket.h"
#include "AVMTSocketUDPAsyn.h"
#include "AVMTNetInterface.h"
#include "IHPMsgQueue.h"

typedef std::list<std::string>	ListString;

struct HPADDR
{
	HPADDR(unsigned long ulIP,unsigned short usPort)
		:m_ulIP(ulIP)
		,m_usPort(usPort)
	{
	}
	HPADDR(void)
		:m_ulIP(0)
		,m_usPort(0)
	{
	}

	HPADDR&operator=(const HPADDR&tHPAddr)
	{
		m_ulIP=tHPAddr.m_ulIP;
		m_usPort=tHPAddr.m_usPort;
		return *this;
	}

	bool operator==(const HPADDR&tHPAddr)
	{
		return (m_ulIP==tHPAddr.m_ulIP && m_usPort==tHPAddr.m_usPort);
	}
	unsigned long	m_ulIP;
	unsigned short	m_usPort;
};

typedef std::vector<HPADDR>	ListHPAddr;

class HPP2PSessionClient;
class HPP2PSession 
	: public HPP2PSocket
	, public AVMTSocketUDPAsynNotify
	, public IHPMsgHandle
{
public:
	HPP2PSession(HPP2PSessionClient&rHPP2PSessionClient,unsigned long ulP2PID,bool bFirst);
	virtual ~HPP2PSession(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);

	bool AddPeerAddress(unsigned long ulIP,unsigned short usPort,unsigned char nPreference);//1-10
	void OnReceivedDataFrom(const void*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);

	void HandleMsg(unsigned long ulMsgID,IHPMsgData*pIHPMsgData);

	void OnReceivedData(const void*pData,int nLen);
	void OnReceivedSTT(void);
	void OnConnected(void);
protected:
	void DoStun(void);
	void SendStun(unsigned long ulIP,unsigned short usPort);
protected:
	HPP2PSessionClient&		m_rHPP2PSessionClient;
	MapAVMTSocketUDPAsyn	m_MapAVMTSocketUDPAsyn;
	MapHPP2PConnection		m_MapHPP2PConnection;
	ListHPAddr				m_ListHPAddr;
	int						m_nStunCount;
	bool					m_bPreparingDoSTTAck;
	bool					m_bFirst;
};

#endif