#ifndef __AVUDPRECEIVER_H__
#define __AVUDPRECEIVER_H__

#include "../libHPBaseclass/AVThread.h"
#include "AVMTSocketUDP.h"

class AVUDPReceiverNotify
{
public:
	AVUDPReceiverNotify(void){};
	virtual~AVUDPReceiverNotify(void){};
public:
	virtual void OnAVUDPReceiverNotifyReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort)=0;
};

class AVUDPReceiver 
	: public AVThread
{
public:
	AVUDPReceiver(AVUDPReceiverNotify&rNotify);
	~AVUDPReceiver(void);
public:
	bool Connect(unsigned long ulIP,unsigned short usPort);
	void ReleaseConnections(void);
	operator SOCKET(void){return m_AVMTSocketUDP;};
	unsigned long GetIP(void){return m_ulIP;};
	unsigned short GetPort(void);
protected:
	void ThreadProcMain(void);
protected:
	AVUDPReceiverNotify&	m_rNotify;
	bool					m_bWantToStop;
	AVMTSocketUDP			m_AVMTSocketUDP;
	unsigned long			m_ulIP;
};

#endif