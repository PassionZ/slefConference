#ifndef VIDEOSESSIONCLIENTTCP_H_
#define VIDEOSESSIONCLIENTTCP_H_

#include "VideoSession.h"
#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"
#include "../DataDefine/AVMTMCUClient.h"

#include "HMTConnectTCP.h"


class CVideoSessionClientTcp 
	: public CVideoSession
	//, public AVMTConnectTCPNotify
	, public AVMTSocketClientNotify
	, public AVMTTCPClientNotify
	, public IVideoSessionClient

	, public HMTConnectTCPNotify
{
public:
	CVideoSessionClientTcp(IVideoSessionClientNotify&rNotify, CVideoChannel&rChannel);
	virtual ~CVideoSessionClientTcp(void);

public:
	virtual bool Connect(const std::string&/*unsigned long*/ ulPeerMCUIP0,unsigned short usPeerMCUPort);
	virtual void ReleaseConnections(void);

	virtual void OnAVMTConnectTCPNotifyConnected(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	virtual void OnAVMTConnectTCPNotifyFailed(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP);

	virtual bool OnAVMTSocketClientNotifyConnected(AVMTSocketClient*pAVMTSocketClient,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	virtual void OnAVMTSocketClientNotifyFailed(AVMTSocketClient*pAVMTSocketClient,unsigned long ulType);

	virtual void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen); // inout data
	virtual void OnAVMTTCPClientNotifyDisconnected(void);

	virtual void OnReceivedDataFromChannel(bool bTcp,const char*pData,int nLen); // outin data
	virtual void OnReceivedDataFromChannelDirection(bool bTcp,const char*pData,int nLen);
	virtual void OnReceivedDataFromChannelEnable(bool bTcp,const char*pData,int nLen);
	virtual bool IsDisconnected(void);
	virtual void ProcessDisable() {
	}
	virtual unsigned long GetBufferingFrameCount(void);

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool IsEnable(void);
	//bool IsRequestKeyFrame(void);

	//////////////////////////////////////////////////////////////////////////

	// source
	void OnEnable(void);
	void OnDisable(void);
	void OnRequestKeyFrame(void);

	bool WantReading(void);

	// udp interface
	virtual void OnReceivedFrame(const char*pData,int nLen) {};

	void Reset();
	void CopyStatus(CVideoSessionClientTcp* pSession);
	void ReverseDirection();

protected:
	IVideoSessionClientNotify&	m_rNotify;
	/*AVMTConnectTCP*/HMTConnectTCP*				m_pAVMTConnectTCP;
	AVMTSocketClient*			m_pAVMTSocketClient;
	AVCritSec					m_AVCritSecAVMTTCPClient;
	AVMTTCPClient*				m_pAVMTTCPClient;

	//unsigned long				m_ulPeerMCUIP0;
	//unsigned short				m_usPeerMCUPort;

	bool						m_bDisconnected;

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool						m_bEnable;
	//bool						m_bRequestKeyFrame;

	//////////////////////////////////////////////////////////////////////////
	// source
	//bool						m_bIsEnable;

	unsigned long			m_ulUserSessionID;
};

#endif
