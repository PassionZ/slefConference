#ifndef __HPEVENTSPUMP_H__
#define __HPEVENTSPUMP_H__

#include "IHPEventsPump.h"
#include "../libHPBaseclass/AVThread.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>

typedef std::map<void*,IHPEventsQueue*>	MapIHPEventsQueue;
//
//#ifdef _WIN32
//class HPEventsPump;
//class HPEventsPumpWnd
//	: public CWnd
//{
//	DECLARE_DYNAMIC(HPEventsPumpWnd)
//protected:
//	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnTimer(UINT nIDEvent);
//public:
//	HPEventsPumpWnd(HPEventsPump&rHPEventsPump);
//	virtual~HPEventsPumpWnd(void);
//public:
//	bool Connect(void);
//	void ReleaseConnections(void);
//protected:
//	bool			m_bWantToStop;
//	HPEventsPump&	m_rHPEventsPump;
//};
//#endif

class HPEventsPump 
	: public IHPEventsPump
#ifdef _WIN32
	, public AVThread
#endif
{
public:
	HPEventsPump(bool bConsole);
	virtual ~HPEventsPump(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	void AddIHPEventsQueue(IHPEventsQueue*pIHPEventsQueue);
	void RemoveIHPEventsQueue(IHPEventsQueue*pIHPEventsQueue);
	bool PumpEvents(void);
protected:
#ifdef _WIN32
	//HPEventsPumpWnd*		m_pHPEventsPumpWnd;
	void ThreadProcMain(void);
	bool					m_bWantToStop;
#endif
	AVCritSec				m_csMapIHPEventsQueue;
	MapIHPEventsQueue		m_MapIHPEventsQueue;
	bool					m_bConsole;
};

#endif