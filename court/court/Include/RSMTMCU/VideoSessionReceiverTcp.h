#ifndef VIDEOSESSIONRECEIVERTCP_H_
#define VIDEOSESSIONRECEIVERTCP_H_

#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"
#include "../DataDefine/AVMTMCUClient.h"

#include "HMTConnectTCP.h"


class CVideoSessionReceiverTcp
	//: public AVMTConnectTCPNotify
	: public AVMTSocketClientNotify
	, public AVMTTCPClientNotify
	, public IAVVideoReceiver

	, public HMTConnectTCPNotify
{
public:
	CVideoSessionReceiverTcp(IAVVideoReceiverNotify&rNotify,/*CVideoChannel&rVideoChannel*/unsigned long ulChannelID);
	virtual ~CVideoSessionReceiverTcp(void);

public:
	bool Connect(const std::string&/*unsigned long*/ ulPeerMCUIP0,unsigned short usPeerMCUPort);
	void ReleaseConnections(void);

	void OnAVMTConnectTCPNotifyConnected(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	void OnAVMTConnectTCPNotifyFailed(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP);

	bool OnAVMTSocketClientNotifyConnected(AVMTSocketClient*pAVMTSocketClient,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	void OnAVMTSocketClientNotifyFailed(AVMTSocketClient*pAVMTSocketClient,unsigned long ulType);

	void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen);
	void OnAVMTTCPClientNotifyDisconnected(void);

	//void OnReceivedDataFromChannel(const char*pData,int nLen);
	bool IsDisconnected(void);

	void EnableReceive(bool bEnable);
	virtual bool IsEnableReceive(void);

	virtual unsigned long GetChannelID() {
		return m_ulChannelID;
	}
	virtual bool IsMatch(unsigned long ulChannelID) {
		return m_ulChannelID == ulChannelID;
	}
	virtual void SetSessionCard(unsigned long ulSessionID, unsigned char iCardNo) {
		m_ulSessionID = ulSessionID;
		m_iCardNo = iCardNo;
	}
	virtual bool IsSessionCard(unsigned long ulSessionID, unsigned char iCardNo) {
		return (m_ulSessionID == ulSessionID && m_iCardNo == iCardNo);
	}

	// udp interface
	virtual void OnReceivedFrame(const char*pData,int nLen) {};

	virtual int SendFrame(const char*pData,int nLen){return 0;};//tiger add
protected:
	IAVVideoReceiverNotify&	m_rNotify;
	/*AVMTConnectTCP*/HMTConnectTCP*			m_pAVMTConnectTCP;
	AVMTSocketClient*		m_pAVMTSocketClient;
	AVCritSec				m_AVCritSecAVMTTCPClient;
	AVMTTCPClient*			m_pAVMTTCPClient;
	unsigned char			m_ucKeepAliveCount;
	bool					m_bDisconnected;

	//unsigned long			m_ulPeerMCUIP0;
	//unsigned short			m_usPeerMCUPort;

	bool					m_bEnableReceive;

	unsigned long			m_ulChannelID;

	unsigned long			m_ulSessionID;
	unsigned char			m_iCardNo;

	bool					m_bInited;

	unsigned long			m_ulUserSessionID;
};

#endif
