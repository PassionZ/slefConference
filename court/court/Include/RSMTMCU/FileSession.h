#ifndef __FileSESSION_H__
#define __FileSESSION_H__

#include "../DataDefine/AVMTMCUClient.h"


class AFX_EXT_CLASS CFileChannel;
class AFX_EXT_CLASS CFileSession
{
public:
	CFileSession(CFileChannel&rChannel);
	virtual ~CFileSession(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen)=0;
	virtual bool IsDisconnected(void)=0;

	virtual void SendDataToChannel(const char*pData,int nLen);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);

	CFileChannel& GetChannel() {
		return m_rChannel;
	}

protected:
	CFileChannel&					m_rChannel;
	unsigned long				m_ulSessionID;

};

#endif
