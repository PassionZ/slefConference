#ifndef VIDEOSERVERUDP_H_
#define VIDEOSERVERUDP_H_

#include "VideoSession.h"
//#include "../libHPBaseclass/AVBufferPool.h"

#ifdef MAINTAINUDPPACKET
#include "../libHPNETIO/AVSCTPSession.h"
#endif


class AFX_EXT_CLASS CVideoSessionServerUdp :
	public CVideoSession
//	, public AVBufferPool

#ifdef MAINTAINUDPPACKET
	, public AVSCTPSessionNotify
	, public AVBufferPool
#endif

{
public:
	CVideoSessionServerUdp(CVideoChannel&rChannel,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, UINT32 iMcuID);
	virtual ~CVideoSessionServerUdp(void);

public:
	void OnReceivedConnect(void); // server

	void OnReceivedDirection(const char*pData,int nLen);
	virtual void OnReceivedFrame(const char*pData,int nLen); // inout data
	virtual void OnReceivedDataFromChannel(bool bTcp,const char*pData,int nLen); // outin data
	virtual void OnReceivedDataFromChannelDirection(bool bTcp,const char*pData,int nLen);
	virtual void OnReceivedDataFromChannelEnable(bool bTcp,const char*pData,int nLen);
	virtual bool IsDisconnected(void);

	// sink
	void OnReceivedEnable(void);
	void OnReceivedDisable(void);

	// source
	void OnReceivedEnableACK(void);
	void OnReceivedDisableACK(void);
	virtual void ProcessDisable();

	void OnReceivedNull(void);

	void OnReceivedDirectionAck(void);

	void Reset();
	void OnReverseDirection(bool bSource);

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

	UINT32 GetMcuID() { return m_iMcuID; }

	void SetClientServer(bool bServer)
	{
		m_bClientServer = bServer;
	}

	void SetUserSessionCard(unsigned long ulUserSessionID, unsigned short usCardNo)
	{
		m_ulUserSessionID = ulUserSessionID;
		m_usCardNo = usCardNo;
	}

protected:
	void OnEnable(void);
	void OnDisable(void);

#ifdef MAINTAINUDPPACKET
	AVSCTPSession*		m_pAVSCTPSession;
#endif

	UINT32  m_iMcuID;

	bool	m_bClientServer;

	unsigned long			m_ulUserSessionID;
	unsigned short			m_usCardNo;

	bool	m_bDisConnected;

};

#endif
