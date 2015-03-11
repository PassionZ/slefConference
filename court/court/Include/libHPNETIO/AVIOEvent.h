// AVIOEvent.h: interface for the AVIOEvent class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVIOEVENT_H__
#define __AVIOEVENT_H__


class AFX_EXT_CLASS AVIOEvent  
{
public:
	AVIOEvent(void);
	virtual ~AVIOEvent(void);
public:
	virtual bool WantReading(void)=0;
	virtual bool WantWriting(void)=0;
	virtual bool OnRead(void)=0;
	virtual bool OnWrite(void)=0;
	virtual void OnError(void)=0;
};

#endif 