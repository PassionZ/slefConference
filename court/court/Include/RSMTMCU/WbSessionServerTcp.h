#ifndef WBSESSIONSERVERTCP_H_
#define WBSESSIONSERVERTCP_H_

#include "WbSession.h"
#include "../libHPNETIO/AVMTSConnection.h"


class CWbSessionServerTcp 
	: public CWbSession
	, public AVMTSConnection
{
public:
	CWbSessionServerTcp(CWbChannel&rChannel, SOCKET hSocket);
	virtual ~CWbSessionServerTcp(void);

public:
	virtual void ReleaseConnections(void);
	
	virtual void OnReceivedFrame(const char*pFrameData,int nLen);  // inout data

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen); // outin data
	virtual bool IsDisconnected(void);

protected:
	unsigned char	m_ucBufferEmptyCount;
};

#endif
