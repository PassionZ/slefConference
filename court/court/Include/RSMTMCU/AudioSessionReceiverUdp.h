#ifndef AUDIOSESSIONRECEIVERUDP_H_
#define AUDIOSESSIONRECEIVERUDP_H_

#include "../libHPBaseclass/AVUtil.h"
#include "../DataDefine/AVMTMCUClient.h"
#include "../libHPNETIO/AVMTSocketUDP.h"


class AFX_EXT_CLASS CAudioSessionReceiverUdp
	: public IAVAudioReceiver
{
public:
	CAudioSessionReceiverUdp(IAVAudioReceiverNotify&rNotify,unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, UINT32 iMcuID);
	virtual ~CAudioSessionReceiverUdp(void);

public:
	bool Connect(void);
	virtual void ReleaseConnections(void);

	void OnReceivedConnectACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort,unsigned long ulChannelID); // client
	void OnReceivedFrame(unsigned long ulAudioSinkID,const char*pData,int nLen,unsigned long ulIP,unsigned short usPort); // inout data

	virtual void EnableReceive(bool bEnable);
	virtual bool IsEnableReceive(void);
	virtual bool IsDisconnected(void);

	void EnableReceive(void);
	void DisableReceive(void);
	void OnReceivedEnableACK(unsigned long ulAudioSinkID,unsigned long ulIP,unsigned short usPort);
	void OnReceivedDisableACK(unsigned long ulAudioSinkID,unsigned long ulIP,unsigned short usPort);

	void OnReceivedDirection(const char*pData,int nLen/*,unsigned long ulPeerSessionID,unsigned long ulChannelID*/);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);
	unsigned long GetPeerSessionID(void);

	virtual bool IsMatch(unsigned long ulChannelID) {
		return m_ulChannelID == ulChannelID;
	}

	virtual bool IsSession(unsigned long ulSessionID) {
		return (m_ulSelfSessionID == ulSessionID);
	}
	virtual void SetSessionCard(unsigned long ulSessionID) {
		m_ulSelfSessionID = ulSessionID;
	}

	SOCKET GetSocketHandle(void) { return (SOCKET)m_AVMTSocketUDP;}

protected:
	IAVAudioReceiverNotify&	m_rNotify;
	unsigned long			m_ulSessionID;

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

	bool	m_bConnected;
	UINT32  m_iMcuID;
};

#endif