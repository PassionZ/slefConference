// HPNetIOQueuePoll.h: interface for the HPNetIOQueuePoll class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __HPNETIOQUEUEPOLL_H__
#define __HPNETIOQUEUEPOLL_H__

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

#include "HPNetIOQueueOperator.h"

class HPNetIOQueuePoll 
	: public HPNetIOQueueOperator  
{
public:
	HPNetIOQueuePoll(HPNetIOQueue&rHPNetIOQueue);
	virtual ~HPNetIOQueuePoll(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool RemoveEvent(SOCKET hSocket);
	bool ModifyEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool PollingEvents(void);
protected:
	struct pollfd *		m_event_set;
	int					m_num_fds;
	int					m_event_count;
};

#endif

#endif 
