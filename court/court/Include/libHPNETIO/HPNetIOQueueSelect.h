// HPNetIOQueueSelect.h: interface for the HPNetIOQueueSelect class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __HPNETIOQUEUESELECT_H__
#define __HPNETIOQUEUESELECT_H__

#ifdef _WIN32
#include "HPNetIOQueueOperator.h"

struct win_fd_set {
	u_int fd_count;
	SOCKET fd_array[1];
};

class HPNetIOQueueSelect 
	: public HPNetIOQueueOperator  
{
public:
	HPNetIOQueueSelect(HPNetIOQueue&rHPNetIOQueue);
	virtual ~HPNetIOQueueSelect(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool RemoveEvent(SOCKET hSocket);
	bool ModifyEvent(SOCKET hSocket,bool bRead,bool bWrite);
	bool PollingEvents(void);
protected:
	int realloc_fd_sets(size_t new_size);
	int do_fd_set(struct win_fd_set *set, SOCKET s);
	void do_fd_unset(struct win_fd_set *set, SOCKET s);
	void fd_set_copy(struct win_fd_set *out, const struct win_fd_set *in);
protected:
	u_int			m_fd_size;
	win_fd_set*		m_readset_in;
	win_fd_set*		m_writeset_in;
	win_fd_set*		m_readset_out;
	win_fd_set*		m_writeset_out;
	win_fd_set*		m_exset_out;
};

#endif
#endif 