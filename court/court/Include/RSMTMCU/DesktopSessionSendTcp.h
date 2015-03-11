#ifndef DESKTOPSESSIONSENDTCP_H_
#define DESKTOPSESSIONSENDTCP_H_

#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"
#include "../DataDefine/AVMTMCUClient.h"

#include "HMTConnectTCP.h"


class CDesktopSessionSendTcp 
	//: public AVMTConnectTCPNotify
	: public AVMTSocketClientNotify
	, public AVMTTCPClientNotify
	, public IAVDesktopSender

	, public HMTConnectTCPNotify
{
public:
	CDesktopSessionSendTcp(IAVDesktopSenderNotify&rNotify,/*CDesktopChannel&rDesktopChannel*/unsigned long ulChannelID);
	virtual ~CDesktopSessionSendTcp(void);

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
	virtual void SendDesktopFrame(const char*pData,int nLen);
	unsigned long GetSentLostPackets(void);

	unsigned long GetBufferingFrameCount(void);

	virtual bool IsMatch(unsigned long ulChannelID) {
		return m_ulChannelID == ulChannelID;
	}

protected:
	IAVDesktopSenderNotify&	m_rNotify;
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
};

#endif
