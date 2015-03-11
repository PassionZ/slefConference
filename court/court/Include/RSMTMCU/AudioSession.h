#ifndef AUDIOSESSION_H_
#define AUDIOSESSION_H_

#include "../libHPBaseclass/AVUtil.h"
#include "../libHPNETIO/AVMTSocketUDP.h"
#include "../DataDefine/AVMTMCUClient.h"


class AFX_EXT_CLASS CAudioChannel;
class AFX_EXT_CLASS CAudioSession
{
public:
	CAudioSession(CAudioChannel&rChannel,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, bool bClient);
	virtual ~CAudioSession(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);
	unsigned long GetPeerSessionID(void);

	SOCKET GetSocketHandle(void);
	unsigned long GetIP(void);
	unsigned short GetPort(void);

	virtual void OnReceivedFrame(const char*pData,int nLen)=0;
	virtual void OnReceivedDataFromChannel(const char*pData,int nLen)=0;
	virtual void OnReceivedDataFromChannelDirection(const char*pData,int nLen)=0;
	virtual void OnReceivedDataFromChannelEnable(const char*pData,int nLen)=0;
	virtual bool IsDisconnected(void)=0;
	virtual void ProcessDisable()=0;

	virtual void SendDataToChannel(const char*pData,int nLen);
	virtual void SendDataToChannelDirection(const char*pData,int nLen);
	virtual void SendDataToChannelEnable(const char*pData,int nLen);

	bool IsClient() { return m_bClient; }
	bool IsSource() { return m_bSource; }
	void SetSource(bool bSource) { m_bSource = bSource; }

	// sink
	bool IsEnable(void) { return m_bEnable; }
	void OnReceivedDirectionAck(void);

	virtual void Reset() = 0;
	bool GetSource() {
		return m_bSource;
	}
	bool GetDirectionAck() {
		return m_bDirectionAck;
	}
	bool GetEnable() {
		return m_bEnable;
	}

	CAudioChannel& GetChannel() {
		return m_rChannel;
	}

protected:
	CAudioChannel&		m_rChannel;
	unsigned long		m_ulSessionID;

	AVMTSocketUDP		m_AVMTSocketUDP;
	unsigned long		m_ulIP;
	unsigned short		m_usPort;
	struct sockaddr_in	m_sa;

	unsigned long		m_ulTimestamp;
	unsigned long		m_ulPeerSessionID;

	bool				m_bClient; //
	bool				m_bSource; // true is source,or is sink

	// sink
	bool				m_bEnable;
	bool				m_bDirectionAck;

	// source
	unsigned char		m_ucKeepAliveCount;
	//bool				m_bIsEnable;
	unsigned long		m_ulLostPackets;
	unsigned short		m_usSequence;

	//char				m_pCMD[MAX_AUDIOUDPPACKET_LEN];
	
};

#endif
