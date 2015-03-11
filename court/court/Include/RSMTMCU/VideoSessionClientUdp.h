#ifndef VIDEOSESSIONCLIENTUDP_H_
#define VIDEOSESSIONCLIENTUDP_H_

#include "VideoSession.h"
//#include "../libHPBaseclass/AVBufferPool.h"

#ifdef MAINTAINUDPPACKET
#include "../libHPNETIO/AVSCTPSession.h"
#endif


class AFX_EXT_CLASS CVideoSessionClientUdp 
	: public CVideoSession
//	, public AVBufferPool

#ifdef MAINTAINUDPPACKET
	, public AVSCTPSessionNotify
	, public AVBufferPool
#endif

{
public:
	CVideoSessionClientUdp(CVideoChannel&rChannel,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID , UINT32 iMcuID);
	virtual ~CVideoSessionClientUdp(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	void OnReceivedConnectACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort); // client

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
	void OnReceivedEnableACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort);
	void OnReceivedDisableACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort);
	virtual void ProcessDisable();

	void OnReceivedNull(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort);

	void OnReceivedDirectionAck(void);

	void Reset();
	void CopyStatus(CVideoSessionClientUdp* pSession);
	void ReverseDirection();
	void OnReverseDirectionAck();

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

protected:
	void OnEnable(void);
	void OnDisable(void);

#ifdef MAINTAINUDPPACKET
	AVSCTPSession*		m_pAVSCTPSession;
#endif

	bool	m_bConnected;
	UINT32  m_iMcuID;

	bool	m_bReverseDirectionAck;

};

AFX_EXT_CLASS /*IAudiioSessionClient*/CVideoSessionClientUdp* CreateIVideoSessionClientUdp(/*IVideoSessionClientNotify&rNotify,*/unsigned long ulChannelID/*, unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

#endif