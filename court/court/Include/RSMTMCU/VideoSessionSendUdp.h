#ifndef VIDEOSESSIONSENDUDP_H_
#define VIDEOSESSIONSENDUDP_H_

#include "../libHPBaseclass/AVUtil.h"
#include "../DataDefine/AVMTMCUClient.h"
#include "../libHPNETIO/AVMTSocketUDP.h"

#ifdef MAINTAINUDPPACKET
#include "../libHPNETIO/AVSCTPSession.h"
#endif


class AFX_EXT_CLASS CVideoSessionSendUdp
	: public IAVVideoSender

#ifdef MAINTAINUDPPACKET
	, public AVSCTPSessionNotify
	, public AVBufferPool
#endif

{
public:
	CVideoSessionSendUdp(IAVVideoSenderNotify&rNotify,unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, UINT32 iMcuID,unsigned long ulUserSessionID,unsigned short usCardNo);
	virtual ~CVideoSessionSendUdp(void);

public:
	bool Connect(void);
	virtual void ReleaseConnections(void);

	void OnReceivedConnectACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort); // client
	//void OnReceivedFrame(const char*pData,int nLen); // inout data
	void SendVideoFrame(const char*pData,int nLen);

	virtual void EnableSend(bool bEnable);
	virtual bool IsEnableSend(void);
	virtual bool IsDisconnected(void);
	virtual unsigned long GetSentLostPackets(void);
	//virtual unsigned long GetTotalPackets(void);

	bool IsEnable(void);
	void OnReceivedEnable(void);
	void OnReceivedDisable(void);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);
	unsigned long GetPeerSessionID(void);

	virtual bool IsMatch(unsigned long ulChannelID) {
		return m_ulChannelID == ulChannelID;
	}
	virtual bool IsReceived() {
		return m_bPeerEnableReceive;
	}

	// tcp interface
	virtual unsigned long GetBufferingFrameCount(void) {return 0;}

#ifdef MAINTAINUDPPACKET
	void OnReceivedFrameACK(const char*pData,int nLen);
	//void OnRequestKeyFrame(void);

	void OnAVSCTPSessionNotifyReceivedFrame(const char*pData,int nLen);
	void OnAVSCTPSessionNotifySendData(const char*pData,int nLen);
	bool DoSendData(void);
	//bool HasSendData(void);
#endif

	SOCKET GetSocketHandle(void) { return (SOCKET)m_AVMTSocketUDP;}
	void OnReceivedDirectionAck(void);

protected:
	IAVVideoSenderNotify&	m_rNotify;
	unsigned long			m_ulSessionID;

	AVMTSocketUDP			m_AVMTSocketUDP;
	unsigned long			m_ulIP;
	unsigned short			m_usPort;
	struct sockaddr_in		m_sa;

	unsigned long			m_ulTimestamp;
	unsigned long			m_ulPeerSessionID;
	unsigned char			m_ucKeepAliveCount;

	//unsigned char			m_ucKeepAliveCount;
	bool					m_bDisconnected;

	bool					m_bEnableSend;
	bool					m_bPeerEnableReceive;

	unsigned long			m_ulLostPackets;

	unsigned long			m_ulChannelID;

	//char					m_pCMD[MAX_VIDEOUDPPACKET_LEN];

	bool					m_bDirectionAck;

#ifdef MAINTAINUDPPACKET
	AVSCTPSession*			m_pAVSCTPSession;

	//bool					m_bSource;
	//bool					m_bRequestKeyFrame;
#endif

	bool	m_bConnected;
	UINT32  m_iMcuID;

	unsigned long			m_ulUserSessionID;
	unsigned short			m_usCardNo;

};

#endif