#ifndef __WBSESSION_H__
#define __WBSESSION_H__

#include "../DataDefine/AVMTMCUClient.h"


class AFX_EXT_CLASS CWbChannel;
class AFX_EXT_CLASS CWbSession
{
public:
	CWbSession(CWbChannel&rChannel);
	virtual ~CWbSession(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen)=0;
	virtual bool IsDisconnected(void)=0;

	virtual void SendDataToChannel(const char*pData,int nLen);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);

	CWbChannel& GetChannel() {
		return m_rChannel;
	}

protected:
	CWbChannel&					m_rChannel;
	unsigned long				m_ulSessionID;

};

#endif
