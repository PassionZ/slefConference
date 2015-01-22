#ifndef __AVMTSOCKETUDPASYN_H__
#define __AVMTSOCKETUDPASYN_H__

#include "IHPNetIOQueue.h"
#include "AVMTSocketUDP.h"
#include <list>
#include <map>

class AVMTSocketUDPAsynNotify
{
public:
	AVMTSocketUDPAsynNotify(void){};
	virtual~AVMTSocketUDPAsynNotify(void){};
public:
	virtual void OnReceivedDataFrom(const void*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort)=0;
};

class AVMTSocketUDPAsyn 
	: public IHPNetIOEvent
	, public AVMTSocketUDP
{
public:
	AVMTSocketUDPAsyn(IHPNetIOQueue&rIHPNetIOQueue,AVMTSocketUDPAsynNotify&rAVMTSocketUDPAsynNotify);
	virtual ~AVMTSocketUDPAsyn(void);
public:
	virtual bool Bind(unsigned long ulIP,unsigned short usPort,bool bReuseAddr=true,bool bNB=true);
	virtual bool ConnectTo(unsigned long ulIP,unsigned short usPort);
	virtual void Close(void);

	operator SOCKET(void){return AVMTSocketUDP::operator SOCKET();}
	void OnRead(void);
	void OnWrite(void);
	void OnError(void);
protected:
	AVMTSocketUDPAsynNotify&	m_rAVMTSocketUDPAsynNotify;
};

typedef std::list<AVMTSocketUDPAsyn*>						ListAVMTSocketUDPAsyn;
typedef std::map<unsigned long,AVMTSocketUDPAsyn*>			MapAVMTSocketUDPAsyn;

#endif