// AVIOEventPoll.h: interface for the AVIOEventPoll class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVIOEVENTPOLL_H__
#define __AVIOEVENTPOLL_H__

#ifndef _WIN32
#include <sys/types.h>
#include <sys/time.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "AVIOEventOperator.h"

class AVIOEventPoll 
	: public AVIOEventOperator  
{
public:
	AVIOEventPoll(AVIOEventManager&rAVIOEventManager);
	virtual ~AVIOEventPoll(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool PollingEvents(void);
	void Reset(void);
protected:
	struct pollfd *		m_event_set;
	int					m_num_fds;
	int					m_event_count;
};

#endif

#endif 
