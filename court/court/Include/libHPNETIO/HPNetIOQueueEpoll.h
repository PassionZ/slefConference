// HPNetIOQueueEpoll.h: interface for the HPNetIOQueueEpoll class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __HPNETIOQUEUEEPOLL_H__
#define __HPNETIOQUEUEEPOLL_H__

#ifndef _WIN32

#include <stdint.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <sys/epoll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "HPNetIOQueueOperator.h"

class HPNetIOQueueEpoll 
	: public HPNetIOQueueOperator  
{
public:
	HPNetIOQueueEpoll(HPNetIOQueue&rHPNetIOQueue);
	virtual ~HPNetIOQueueEpoll(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool RemoveEvent(SOCKET hSocket);
	bool ModifyEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool PollingEvents(void);
protected:
	int						m_epfd;
	struct epoll_event *	m_event_set;
	int						m_event_count;
};

#endif

#endif 