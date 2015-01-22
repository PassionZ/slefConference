#ifndef __IHPEVENTSPUMP_H__
#define __IHPEVENTSPUMP_H__

class AFX_EXT_CLASS IHPEventsQueue
{
public:
	IHPEventsQueue(void){};
	virtual~IHPEventsQueue(void){};
public:
	virtual bool PumpEvents(void)=0;
};

class AFX_EXT_CLASS IHPEventsPump
{
public:
	IHPEventsPump(void){};
	virtual ~IHPEventsPump(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual void AddIHPEventsQueue(IHPEventsQueue*pIHPEventsQueue)=0;
	virtual void RemoveIHPEventsQueue(IHPEventsQueue*pIHPEventsQueue)=0;
	virtual bool PumpEvents(void)=0;
};

AFX_EXT_CLASS IHPEventsPump*CreateIHPEventsPump(bool bConsole=false);

#endif