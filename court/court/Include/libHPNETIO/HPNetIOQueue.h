// HPNetIOQueue.h: interface for the HPNetIOQueue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __HPNETIOQUEUE_H__
#define __HPNETIOQUEUE_H__

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif
#include <map>
#include "IHPNetIOQueue.h"
#include "HPNetIOQueueOperator.h"

typedef std::map<SOCKET,IHPNetIOEvent*>	MapIHPNetIOEvent;

class HPNetIOQueue 
	: public IHPNetIOQueue
{
public:
	HPNetIOQueue(void);
	virtual ~HPNetIOQueue(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);

	void AddEvent(IHPNetIOEvent*pIHPNetIOEvent);
	void RemoveEvent(IHPNetIOEvent*pIHPNetIOEvent);
	void ModifyEvent(IHPNetIOEvent*pIHPNetIOEvent);
	bool PumpEvents(void);

	void OnReadEvent(SOCKET hSocket);
	void OnWriteEvent(SOCKET hSocket);
	void OnErrorEvent(SOCKET hSocket);
protected:
	MapIHPNetIOEvent		m_MapIHPNetIOEvent;
	HPNetIOQueueOperator*	m_pHPNetIOQueueOperator;
};

#endif 
