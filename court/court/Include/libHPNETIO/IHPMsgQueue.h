#ifndef __IHPMSGPUMP_H__
#define __IHPMSGPUMP_H__

#include "IHPEventsPump.h"

class AFX_EXT_CLASS IHPMsgData
{
public:
	IHPMsgData(void){};
	virtual~IHPMsgData(void){};
};

class AFX_EXT_CLASS IHPMsgHandle
{
public:
	IHPMsgHandle(void){};
	virtual~IHPMsgHandle(void){};
public:
	virtual void HandleMsg(unsigned long ulMsgID,IHPMsgData*pIHPMsgData)=0;
};

class AFX_EXT_CLASS  IHPMsgQueue
	: public IHPEventsQueue
{
public:
	IHPMsgQueue(void){};
	virtual ~IHPMsgQueue(void){};
public:
	virtual void PostMsg(IHPMsgHandle*pIHPMsgHandle,unsigned long ulMsgID,IHPMsgData*pIHPMsgData=NULL,bool bOnce=true,unsigned long ulDelay=0)=0;
	virtual void ClearMsg(IHPMsgHandle*pIHPMsgHandle)=0;
	virtual void RemoveMsg(IHPMsgHandle*pIHPMsgHandle,unsigned long ulMsgID)=0;
};

AFX_EXT_CLASS IHPMsgQueue*CreateIHPMsgQueue(void);

#endif