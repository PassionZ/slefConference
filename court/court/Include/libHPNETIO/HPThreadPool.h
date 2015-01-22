#ifndef __HPTHREADPOOL_H__
#define __HPTHREADPOOL_H__

#include "../libHPBaseclass/AVThread.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include "../libHPBaseclass/AVUtil.h"
#include <list>

class HPThreadPool;
class HPThread
	: public AVThread
{
public:
	HPThread(HPThreadPool&rHPThreadPool);
	virtual ~HPThread(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
protected:
	void ThreadProcMain(void);
protected:
	HPThreadPool&	m_rHPThreadPool;
	bool			m_bWantToStop;
};

typedef std::list<HPThread*>	ListHPThread;

class HPThreadPool
{
public:
	HPThreadPool(void);
	virtual~HPThreadPool(void);
public:
	virtual bool Connect(int nThreadCount);
	virtual void ReleaseConnections(void);
	virtual bool OnRunOnce(void)=0;
protected:
	bool OnRunOnceCallback(void);
protected:
	ListHPThread	m_ListHPThread;
	AVCritSec		m_csRunOnce;

	friend class HPThread;
};


#endif