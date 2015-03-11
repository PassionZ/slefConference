#ifndef VIDEOSESSIONSENDTCP_H_
#define VIDEOSESSIONSENDTCP_H_

#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"
#include "../DataDefine/AVMTMCUClient.h"

#include "HMTConnectTCP.h"


class CVideoSessionSendTcp 
	//: public AVMTConnectTCPNotify
	: public AVMTSocketClientNotify
	, public AVMTTCPClientNotify
	, public IAVVideoSender

	, public HMTConnectTCPNotify
{
public:
	CVideoSessionSendTcp(IAVVideoSenderNotify&rNotify,/*CVideoChannel&rVideoChannel*/unsigned long ulChannelID,unsigned long ulUserSessionID,unsigned short usCardNo);
	virtual ~CVideoSessionSendTcp(void);

public:
	bool Connect(const std::string &/*unsigned long*/ ulPeerMCUIP0,unsigned short usPeerMCUPort);
	void ReleaseConnections(void);

	void OnAVMTConnectTCPNotifyConnected(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	void OnAVMTConnectTCPNotifyFailed(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP);

	bool OnAVMTSocketClientNotifyConnected(AVMTSocketClient*pAVMTSocketClient,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	void OnAVMTSocketClientNotifyFailed(AVMTSocketClient*pAVMTSocketClient,unsigned long ulType);

	void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen);
	void OnAVMTTCPClientNotifyDisconnected(void);

	void EnableSend(bool bEnable);
	bool IsEnableSend(void);
	void OnReceivedEnable(void);
	void OnReceivedDisable(void);

	bool IsEnable(void);
	bool IsDisconnected(void);
	virtual void SendVideoFrame(const char*pData,int nLen);
	unsigned long GetSentLostPackets(void);

	unsigned long GetBufferingFrameCount(void);

	virtual bool IsMatch(unsigned long ulChannelID) {
		return m_ulChannelID == ulChannelID;
	}
	virtual bool IsReceived() {
		return m_bPeerEnableReceive;
	}

	// udp interface
	virtual void OnReceivedFrame(const char*pData,int nLen) {};

protected:
	IAVVideoSenderNotify&	m_rNotify;
	/*AVMTConnectTCP*/HMTConnectTCP*			m_pAVMTConnectTCP;
	AVMTSocketClient*		m_pAVMTSocketClient;
	AVCritSec				m_AVCritSecAVMTTCPClient;
	AVMTTCPClient*			m_pAVMTTCPClient;
	unsigned char			m_ucKeepAliveCount;
	bool					m_bDisconnected;

	//unsigned long			m_ulPeerMCUIP0;
	//unsigned short			m_usPeerMCUPort;

	bool					m_bEnableSend;
	bool					m_bPeerEnableReceive;

	unsigned long			m_ulLostPackets;
	//unsigned char			m_ucBufferEmptyCount;

	unsigned long			m_ulChannelID;

	unsigned long			m_ulUserSessionID;
	unsigned short			m_usCardNo;
};

#endif
