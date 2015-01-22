#ifndef WBCHANNELCLIENT_H_
#define WBCHANNELCLIENT_H_

#include "WbChannel.h"
#include "../DataDefine/AVMTMCUClient.h"
#include "WbSessionClientTcp.h"


class CWbChannelClient :
	public CWbChannel
	, public IWbSessionClient
{
public:
	CWbChannelClient(IWbSessionClientNotify&rNotify, unsigned long ulChannelID);
	virtual ~CWbChannelClient(void);

	virtual bool Connect(void);
	virtual void ReleaseConnections(void);
	virtual void onWbData(unsigned long ulSessionID,char* data,int len);
	virtual void SendFrame(const char*pData,int nLen);
	virtual bool IsDisconnected(void);

	virtual void onDTSUIDataNotify(const char* pData,int nLen);

protected:
	IWbSessionClientNotify&	m_rNotify;

	CWbSessionClientTcp*	m_pWbSessionClientTcp;
};

#endif
