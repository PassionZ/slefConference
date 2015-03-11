// AVIOEventEpoll.h: interface for the AVIOEventEpoll class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVIOEVENTEPOLL_H__
#define __AVIOEVENTEPOLL_H__

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

#include "AVIOEventOperator.h"

class AVIOEventEpoll 
	: public AVIOEventOperator  
{
public:
	AVIOEventEpoll(AVIOEventManager&rAVIOEventManager);
	virtual ~AVIOEventEpoll(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool PollingEvents(void);
	void Reset(void);
protected:
	int						m_epfd;
	int*					m_fdset;
	int						m_fd_count;
	int						m_num_fds;
	struct epoll_event *	m_event_set;
	int						m_event_count;
};

#endif

#endif 