#ifndef __AVMTMANAGERUDP_H__
#define __AVMTMANAGERUDP_H__

#include <map>
#include "libHPNETIO.h"
#include "AVMTUDPReceiver.h"
#include "../libHPBaseclass/AVAutoLock.h"

typedef std::map<unsigned long,AVMTUDPReceiver*>	MapAVMTUDPReceiver;

class AVMTManagerUDP 
	: public AVMTUDPReceiverNotify
	, public IHPUDPIO
{
public:
	AVMTManagerUDP(IHPUDPIONotify&rIHPUDPIONotify);
	virtual~AVMTManagerUDP(void);
public:
	static AVMTManagerUDP*Instance(void);
public:
	virtual bool Connect(unsigned short usPort,unsigned char nTos);
	virtual void ReleaseConnections(void);
	virtual bool IsLocalIP(unsigned long ulIP);
	virtual SOCKET GetSocketHandle(unsigned long ulIP);
	virtual unsigned short GetUDPPort(void);
protected:
	void OnAVMTUDPReceiverNotifyReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);
protected:
	IHPUDPIONotify&					m_rIHPUDPIONotify;
	MapAVMTUDPReceiver				m_MapAVMTUDPReceiver;
	unsigned short					m_usPort;
};

#endif