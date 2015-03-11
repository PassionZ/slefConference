// AVIOEventOperator.h: interface for the AVIOEventOperator class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVIOEVENTOPERATOR_H__
#define __AVIOEVENTOPERATOR_H__

class AFX_EXT_CLASS AVIOEventManager;
class AFX_EXT_CLASS AVIOEventOperator  
{
public:
	AVIOEventOperator(AVIOEventManager&rAVIOEventManager);
	virtual ~AVIOEventOperator(void);
public:
	virtual bool Connect(void)=0;
	virtual void ReleaseConnections(void)=0;
	virtual bool AddEvent(SOCKET hSocket,bool bRead,bool bWrite)=0;
	virtual bool PollingEvents(void)=0;
	virtual void Reset(void)=0;
protected:
	void OnReadEvent(SOCKET hSocket);
	void OnWriteEvent(SOCKET hSocket);
	void OnErrorEvent(SOCKET hSocket);
protected:
	AVIOEventManager&	m_rAVIOEventManager;
};

#endif 