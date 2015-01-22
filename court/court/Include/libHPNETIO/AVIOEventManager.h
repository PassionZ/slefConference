// AVIOEventManager.h: interface for the AVIOEventManager class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVIOEVENTMANAGER_H__
#define __AVIOEVENTMANAGER_H__

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif
#include <map>
#include "AVIOEvent.h"
#include "AVIOEventOperator.h"
#include "../libHPBaseclass/AVThread.h"
#include "../libHPBaseclass/AVAutoLock.h"

typedef std::map<SOCKET,AVIOEvent*>	MapAVIOEvent;

class AFX_EXT_CLASS AVIOEventManager 
	: public AVThread
{
public:
	AVIOEventManager(void);
	virtual ~AVIOEventManager(void);
public:
	static AVIOEventManager*Instance(void);
	static bool StartInstance(void);
	static void FreeInstance(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	void AddAVIOEvent(SOCKET hSocket,AVIOEvent*pAVIOEvent);
	void RemoveAVIOEvent(SOCKET hSocket);
	void OnReadEvent(SOCKET hSocket);
	void OnWriteEvent(SOCKET hSocket);
	void OnErrorEvent(SOCKET hSocket);
protected:
	void ThreadProcMain(void);
	bool PendingEvents(void);
	bool PollingEvents(void);
protected:
	bool				m_bWantToStop;
	AVCritSec			m_AVCritSecMapAVIOEvent;
	MapAVIOEvent		m_MapAVIOEvent;
	AVIOEventOperator*	m_pAVIOEventOperator;
};

#endif 
