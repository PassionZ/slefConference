#ifndef __HPSOCKETUDPRECEIVER_H__
#define __HPSOCKETUDPRECEIVER_H__

#include "AVMTSocketUDP.h"
#include "../libHPBaseclass/AVUtil.h"
#include "../libHPBaseclass/AVThread.h"

class AVMTUDPReceiverNotify
{
public:
	AVMTUDPReceiverNotify(void){};
	virtual~AVMTUDPReceiverNotify(void){};
public:
	virtual void OnAVMTUDPReceiverNotifyReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort)=0;
};

class AVMTUDPReceiver 
	: public AVThread
{
public:
	AVMTUDPReceiver(AVMTUDPReceiverNotify&rAVMTUDPReceiverNotify);
	virtual ~AVMTUDPReceiver(void);
public:
	bool Connect(unsigned long ulIP,unsigned short usPort);
	void ReleaseConnections(void);
	operator SOCKET(void){return m_AVMTSocketUDP;};
	unsigned long GetIP(void){return m_ulIP;};
	unsigned short GetPort(void);
	
protected:
	void ThreadProcMain(void);
protected:
	AVMTUDPReceiverNotify&		m_rAVMTUDPReceiverNotify;
	bool						m_bRunning;
	AVMTSocketUDP				m_AVMTSocketUDP;
	unsigned long				m_ulIP;
};

#endif