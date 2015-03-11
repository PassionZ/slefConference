#ifndef DESKTOPSESSIONCLIENTTCP_H_
#define DESKTOPSESSIONCLIENTTCP_H_

#include "DesktopSession.h"
#include "../DataDefine/AVMTMCUClient.h"
#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"

#include "HMTConnectTCP.h"


class CDesktopSessionClientTcp 
	: public CDesktopSession
	//, public AVMTConnectTCPNotify
	, public AVMTSocketClientNotify
	, public AVMTTCPClientNotify
	, public IDesktopSessionClient

	, public HMTConnectTCPNotify
{
public:
	CDesktopSessionClientTcp(IDesktopSessionClientNotify&rNotify, CDesktopChannel&rChannel);
	virtual ~CDesktopSessionClientTcp(void);

public:
	virtual bool Connect(const std::string&/*unsigned long*/ ulPeerMCUIP0,unsigned short usPeerMCUPort);
	virtual void ReleaseConnections(void);

	virtual void OnAVMTConnectTCPNotifyConnected(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	virtual void OnAVMTConnectTCPNotifyFailed(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP);

	virtual bool OnAVMTSocketClientNotifyConnected(AVMTSocketClient*pAVMTSocketClient,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	virtual void OnAVMTSocketClientNotifyFailed(AVMTSocketClient*pAVMTSocketClient,unsigned long ulType);

	virtual void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen); // inout data
	virtual void OnAVMTTCPClientNotifyDisconnected(void);

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen); // outin data
	virtual bool IsDisconnected(void);
	virtual unsigned long GetBufferingFrameCount(void);

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool IsEnable(void);
	//bool IsRequestKeyFrame(void);

	//////////////////////////////////////////////////////////////////////////
	// source
	void OnEnable(void);
	void OnDisable(void);
	//void OnRequestKeyFrame(void);

	bool WantReading(void);

	void Reset();
	void CopyStatus(CDesktopSessionClientTcp* pSession);
	void ReverseDirection();

protected:
	IDesktopSessionClientNotify&	m_rNotify;
	/*AVMTConnectTCP*/HMTConnectTCP*					m_pAVMTConnectTCP;
	AVMTSocketClient*				m_pAVMTSocketClient;
	AVCritSec						m_AVCritSecAVMTTCPClient;
	AVMTTCPClient*					m_pAVMTTCPClient;

	//unsigned long					m_ulPeerMCUIP0;
	//unsigned short					m_usPeerMCUPort;

	bool							m_bDisconnected;

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool							m_bEnable;
	//bool							m_bRequestKeyFrame;

	//////////////////////////////////////////////////////////////////////////
	// source
	//bool							m_bIsEnable;
};

#endif
