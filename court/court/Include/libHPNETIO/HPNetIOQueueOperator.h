// HPNetIOQueueOperator.h: interface for the HPNetIOQueueOperator class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __HPNETIOQUEUEOPERATOR_H__
#define __HPNETIOQUEUEOPERATOR_H__

class HPNetIOQueue;
class HPNetIOQueueOperator  
{
public:
	HPNetIOQueueOperator(HPNetIOQueue&rHPNetIOQueue);
	virtual ~HPNetIOQueueOperator(void);
public:
	virtual bool Connect(void)=0;
	virtual void ReleaseConnections(void)=0;
	virtual bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite)=0;
	virtual bool RemoveEvent(SOCKET hSocket)=0;
	virtual bool ModifyEvent(SOCKET hSocket,bool bRead,bool bWrite)=0;
	virtual bool PollingEvents(void)=0;
protected:
	void OnReadEvent(SOCKET hSocket);
	void OnWriteEvent(SOCKET hSocket);
	void OnErrorEvent(SOCKET hSocket);
protected:
	HPNetIOQueue&	m_rHPNetIOQueue;
};

#endif 