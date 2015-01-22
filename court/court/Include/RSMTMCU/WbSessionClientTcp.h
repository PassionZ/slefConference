#ifndef	WBSESSIONCLIENTTCP_H_
#define WBSESSIONCLIENTTCP_H_

#include "WbSession.h"
#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"
#include "../DataDefine/AVMTMCUClient.h"

#include "HMTConnectTCP.h"


class CWbSessionClientTcp 
	: public CWbSession
	//, public AVMTConnectTCPNotify
	, public AVMTSocketClientNotify
	, public AVMTTCPClientNotify
	, public IWbSessionClient

	, public HMTConnectTCPNotify
{
public:
	CWbSessionClientTcp(IWbSessionClientNotify&rNotify, CWbChannel&rChannel);
	virtual ~CWbSessionClientTcp(void);

public:
	virtual bool Connect(const std::string &/*unsigned long*/ ulPeerMCUIP0,unsigned short usPeerMCUPort);
	virtual void ReleaseConnections(void);

	virtual void OnAVMTConnectTCPNotifyConnected(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	virtual void OnAVMTConnectTCPNotifyFailed(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP);

	virtual bool OnAVMTSocketClientNotifyConnected(AVMTSocketClient*pAVMTSocketClient,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	virtual void OnAVMTSocketClientNotifyFailed(AVMTSocketClient*pAVMTSocketClient,unsigned long ulType);

	virtual void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen); // inout data
	virtual void OnAVMTTCPClientNotifyDisconnected(void);

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen); // outin data
	virtual bool IsDisconnected(void);

	virtual void SendFrame(const char*pData,int nLen) {};

	bool IsNoConnected() {return m_bNoConnected;}
	void SetNoConnected(bool bNoConnected) {m_bNoConnected = bNoConnected;}

protected:
	IWbSessionClientNotify&		m_rNotify;
	/*AVMTConnectTCP*/HMTConnectTCP*				m_pAVMTConnectTCP;
	AVMTSocketClient*			m_pAVMTSocketClient;
	AVCritSec					m_AVCritSecAVMTTCPClient;
	AVMTTCPClient*				m_pAVMTTCPClient;

	bool						m_bDisconnected;
	bool						m_bNoConnected;

	unsigned char				m_ucKeepAliveCount;
};

#endif
