#ifndef VIDEOSESSIONRECEIVERUDP_H_
#define VIDEOSESSIONRECEIVERUDP_H_

#include "../libHPBaseclass/AVUtil.h"
#include "../DataDefine/AVMTMCUClient.h"
#include "../libHPNETIO/AVMTSocketUDP.h"

#ifdef MAINTAINUDPPACKET
#include "../libHPNETIO/AVSCTPSession.h"
#endif

class AFX_EXT_CLASS CVideoSessionReceiverUdp
	: public IAVVideoReceiver

#ifdef MAINTAINUDPPACKET
	, public AVSCTPSessionNotify
	//, public AVBufferPool
#endif

{
public:
	CVideoSessionReceiverUdp(IAVVideoReceiverNotify&rNotify,unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, UINT32 iMcuID);
	virtual ~CVideoSessionReceiverUdp(void);

public:
	bool Connect(void);
	virtual void ReleaseConnections(void);

	void OnReceivedConnectACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort); // client
	void OnReceivedFrame(unsigned long ulVideoSinkID,const char*pData,int nLen,unsigned long ulIP,unsigned short usPort); // inout data

	virtual void EnableReceive(bool bEnable);
	virtual bool IsEnableReceive(void);
	virtual bool IsDisconnected(void);

	void EnableReceive(void);
	void DisableReceive(void);
	void OnReceivedEnableACK(unsigned long ulVideoSinkID,unsigned long ulIP,unsigned short usPort);
	void OnReceivedDisableACK(unsigned long ulVideoSinkID,unsigned long ulIP,unsigned short usPort);

	void OnReceivedDirection(const char*pData,int nLen);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);
	unsigned long GetPeerSessionID(void);

	virtual bool IsMatch(unsigned long ulChannelID) {
		return m_ulChannelID == ulChannelID;
	}

	//virtual bool IsSession(unsigned long ulSessionID) {
	//	return (m_ulSelfSessionID == ulSessionID);
	//}
	//virtual void SetSessionCard(unsigned long ulSessionID) {
	//	m_ulSelfSessionID = ulSessionID;
	//}

	// tcp interface
	virtual unsigned long GetBufferingFrameCount(void) {return 0;}

	// client interface
	virtual void SetSessionCard(unsigned long ulSessionID, unsigned char iCardNo) {
		m_ulUserSessionID = ulSessionID;
		m_iCardNo = iCardNo;
	}
	virtual bool IsSessionCard(unsigned long ulSessionID, unsigned char iCardNo) {
		return (m_ulUserSessionID == ulSessionID && m_iCardNo == iCardNo);
	}

#ifdef MAINTAINUDPPACKET
	void OnReceivedFrameACK(const char*pData,int nLen);
	//void OnRequestKeyFrame(void);

	void OnAVSCTPSessionNotifyReceivedFrame(const char*pData,int nLen);
	void OnAVSCTPSessionNotifySendData(const char*pData,int nLen);
	bool DoSendData(void);
	//bool HasSendData(void);
#endif

	SOCKET GetSocketHandle(void) { return (SOCKET)m_AVMTSocketUDP;}

	virtual int SendFrame(const char*pData,int nLen){return 0;};//tiger add
protected:
	IAVVideoReceiverNotify&	m_rNotify;
	unsigned long			m_ulSessionID;
	// client interface
	unsigned long			m_ulUserSessionID;
	unsigned char			m_iCardNo;

	AVMTSocketUDP			m_AVMTSocketUDP;
	unsigned long			m_ulIP;
	unsigned short			m_usPort;
	struct sockaddr_in		m_sa;

	unsigned long			m_ulTimestamp;
	unsigned long			m_ulPeerSessionID;
	unsigned char			m_ucKeepAliveCount;

	bool					m_bEnableReceive;

	unsigned long			m_ulChannelID;

	unsigned long			m_ulSelfSessionID; // user sessionID

	bool					m_bInited;

#ifdef MAINTAINUDPPACKET
	AVSCTPSession*		m_pAVSCTPSession;
#endif

	bool	m_bConnected;
	UINT32  m_iMcuID;

};

#endif