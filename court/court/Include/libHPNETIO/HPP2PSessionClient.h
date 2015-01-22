#ifndef __HPP2PSESSIONCLIENT_H__
#define __HPP2PSESSIONCLIENT_H__

#include "HPP2PSession.h"
#include "IHPP2PSessionClient.h"


class HPP2PSessionClient
	: public IHPP2PSessionClient
{
public:
	HPP2PSessionClient(IHPP2PSessionClientNotify&rIHPP2PSessionClientNotify,IHPNetIOQueue&rIHPNetIOQueue,IHPMsgQueue&rIHPMsgQueue,unsigned long ulP2PID,const std::string strStunServer[],int nCount,unsigned short usStunPort,bool bHost);
	virtual ~HPP2PSessionClient(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	unsigned long GetP2PID(void);
	unsigned long GetSessionID(void);
	bool IsReadable(void);
	bool IsWritale(void);
	int SendData(const void*pData,int nLen);
	void AddPeerAddress(const std::string&strIP,unsigned short usPort,int nPreference,bool bFirst);
protected:
	void SwitchBest(void);
protected:
	IHPP2PSessionClientNotify&	m_rIHPP2PSessionClientNotify;
	IHPNetIOQueue&				m_rIHPNetIOQueue;
	IHPMsgQueue&				m_rIHPMsgQueue;
	unsigned long				m_ulP2PID;
	unsigned long				m_ulSessionID;

	ListString					m_ListStringStunServer;
	unsigned short				m_usStunPort;
	bool						m_bHost;

	HPP2PSession*				m_pHPP2PSessionFirst;
	HPP2PSession*				m_pHPP2PSessionSecond;

	HPP2PSocket*				m_pHPP2PSocketBest;

	friend class HPP2PSession;
};

#endif