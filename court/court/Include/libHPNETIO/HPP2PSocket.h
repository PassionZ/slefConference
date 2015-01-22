#ifndef __HPP2PSOCKET_H__
#define __HPP2PSOCKET_H__

#include <map>
#include "HPP2PConnection.h"
#include "../libHPBaseclass/AVAutoLock.h"

typedef std::map<void*,HPP2PConnection*>	ListHPP2PConnection;

class HPP2PSocket
{
public:
	HPP2PSocket(unsigned long ulP2PID);
	virtual ~HPP2PSocket(void);
public:
	virtual void ReleaseConnections(void);
	virtual bool AddConnection(HPP2PConnection*pHPP2PConnection);
	virtual void RemoveConnection(HPP2PConnection*pHPP2PConnection);
	
	virtual int SendData(const void*pData,int nLen);
	virtual int SendRawData(const void*pData,int nLen);
	virtual void OnReceivedData(const void*pData,int nLen);
	virtual void OnConnectionStateChanged(HPP2PConnection*pHPP2PConnection,bool bWritable);
	virtual void OnConnected(void){}
	
	virtual bool IsExpired(void);
	virtual bool IsWritable(void);
	
	virtual void SwitchBestConnection(void);
	
	virtual void DoRTT(unsigned long ulTimestamp);
	virtual void DoSTT(unsigned long ulTimestamp);
	virtual void DoSTTAck(unsigned long ulTimestamp);
	
	virtual void OnReceivedSTTAck(unsigned short usSTTID,unsigned long ulCID);
	virtual void OnReceivedSTT(void)=0;
protected:
	ListHPP2PConnection		m_ListHPP2PConnection;
	AVCritSec				m_csListHPP2PConnection;

	HPP2PConnection*		m_pBestConnection;
	unsigned long			m_ulP2PID;
	unsigned short			m_usSTTID;
	bool					m_bExpired;
};

#endif