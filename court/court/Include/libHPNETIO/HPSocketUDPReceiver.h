#ifndef __HPSOCKETUDPRECEIVER_H__
#define __HPSOCKETUDPRECEIVER_H__

#include "AVMTSocketUDP.h"
#include "HPThreadPool.h"

class HPSocketUDPReceiverNotify
{
public:
	HPSocketUDPReceiverNotify(void){};
	virtual~HPSocketUDPReceiverNotify(void){};
public:
	virtual void OnHPSocketUDPReceiverNotifyReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort)=0;
};

class HPSocketUDPReceiver 
	: public HPThreadPool
{
public:
	HPSocketUDPReceiver(HPSocketUDPReceiverNotify&rHPSocketUDPReceiverNotify);
	virtual ~HPSocketUDPReceiver(void);
public:
	bool Connect(unsigned long ulIP,unsigned short usPort);
	void ReleaseConnections(void);
	operator SOCKET(void){return m_AVMTSocketUDP;};
	unsigned long GetIP(void){return m_ulIP;};
	unsigned short GetPort(void);
	
	bool OnRunOnce(void);
protected:
	HPSocketUDPReceiverNotify&	m_rHPSocketUDPReceiverNotify;
	AVMTSocketUDP				m_AVMTSocketUDP;
	unsigned long				m_ulIP;
};

#endif