#ifndef __VIDEOSESSION_H__
#define __VIDEOSESSION_H__

//////////////////////////////////////////////////////////////////////////
// udp
#include "../libHPBaseclass/AVUtil.h"
#include "../libHPNETIO/AVMTSocketUDP.h"
//////////////////////////////////////////////////////////////////////////
#include "../DataDefine/AVMTMCUClient.h"


class AFX_EXT_CLASS CVideoChannel;
class AFX_EXT_CLASS CVideoSession
{
public:
	CVideoSession(CVideoChannel&rChannel, bool bClient);
	//////////////////////////////////////////////////////////////////////////
	// udp
	CVideoSession(CVideoChannel&rChannel,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, bool bClient);
	//////////////////////////////////////////////////////////////////////////
	virtual ~CVideoSession(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	virtual void OnReceivedDataFromChannel(bool bTcp,const char*pData,int nLen)=0;
	virtual void OnReceivedDataFromChannelDirection(bool bTcp,const char*pData,int nLen)=0;
	virtual void OnReceivedDataFromChannelEnable(bool bTcp,const char*pData,int nLen)=0;
	virtual bool IsDisconnected(void)=0;
	virtual void ProcessDisable()=0;
	virtual unsigned long GetBufferingFrameCount(void)=0;

	virtual void SendDataToChannel(bool bTcp,const char*pData,int nLen);
	virtual void SendDataToChannelDirection(bool bTcp,const char*pData,int nLen);
	virtual void SendDataToChannelEnable(bool bTcp,const char*pData,int nLen);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);
	//////////////////////////////////////////////////////////////////////////
	// udp
	unsigned long GetPeerSessionID(void);

	SOCKET GetSocketHandle(void);
	unsigned long GetIP(void);
	unsigned short GetPort(void);

	virtual void OnReceivedFrame(const char*pData,int nLen)=0;
	//////////////////////////////////////////////////////////////////////////

	bool IsClient() { return m_bClient; }
	bool IsSource() { return m_bSource; }
	void SetSource(bool bSource) { m_bSource = bSource; }

	// sink
	bool IsEnable(void);
	void OnReceivedDirectionAck(void);
	bool IsRequestKeyFrame(void);

	bool IsTcp() {return m_bTcp == true;}
	void SetTcp(bool bTcp) {m_bTcp = bTcp;}

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

	//unsigned long GetBufferingFrameCount(void);

//#ifdef MAINTAINUDPPACKET
//	virtual void OnRequestKeyFrame(void)=0;
//#endif

	CVideoChannel& GetChannel() {
		return m_rChannel;
	}

protected:
	CVideoChannel&		m_rChannel;
	unsigned long		m_ulSessionID;

	//////////////////////////////////////////////////////////////////////////
	// udp
	AVMTSocketUDP		m_AVMTSocketUDP;
	unsigned long		m_ulIP;
	unsigned short		m_usPort;
	struct sockaddr_in	m_sa;

	unsigned long		m_ulTimestamp;
	unsigned long		m_ulPeerSessionID;

	unsigned long		m_ulLostPackets;
	unsigned short		m_usSequence;
	//////////////////////////////////////////////////////////////////////////

	bool				m_bClient; //
	bool				m_bSource; // true is source,or is sink

	unsigned char		m_ucKeepAliveCount;

	// sink
	bool				m_bEnable;
	bool				m_bDirectionAck;
	bool				m_bRequestKeyFrame;

	// source
	//bool				m_bIsEnable; // instead of by m_bEnable

	bool				m_bTcp;
	//char				m_pCMD[MAX_VIDEOUDPPACKET_LEN];
};

#endif
