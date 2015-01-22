#ifndef AUDIOSESSIONSENDUDP_H_
#define AUDIOSESSIONSENDUDP_H_

#include "../libHPBaseclass/AVUtil.h"
#include "../DataDefine/AVMTMCUClient.h"
#include "../libHPNETIO/AVMTSocketUDP.h"


class AFX_EXT_CLASS CAudioSessionSendUdp
	: public IAVAudioSender
{
public:
	CAudioSessionSendUdp(IAVAudioSenderNotify&rNotify,unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, UINT32 iMcuID,unsigned long ulUserSessionID,unsigned short usCardNo);
	virtual ~CAudioSessionSendUdp(void);

public:
	bool Connect(void);
	virtual void ReleaseConnections(void);

	void OnReceivedConnectACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort,unsigned long ulChannelID); // client
	//void OnReceivedFrame(const char*pData,int nLen); // inout data
	void SendAudioFrame(const char*pData,int nLen);

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

	SOCKET GetSocketHandle(void) { return (SOCKET)m_AVMTSocketUDP;}
	void OnReceivedDirectionAck(void);

protected:
	IAVAudioSenderNotify&	m_rNotify;
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

	//char					m_pCMD[MAX_AUDIOUDPPACKET_LEN];

	bool					m_bDirectionAck;

	bool	m_bConnected;
	UINT32  m_iMcuID;

	unsigned long			m_ulUserSessionID;
	unsigned short			m_usCardNo;
};

#endif