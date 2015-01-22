#ifndef VIDEOSESSIONSERVERTCP_H_
#define VIDEOSESSIONSERVERTCP_H_

#include "VideoSession.h"
#include "../libHPNETIO/AVMTSConnection.h"


class CVideoSessionServerTcp 
	: public CVideoSession
	, public AVMTSConnection
{
public:
	CVideoSessionServerTcp(CVideoChannel&rChannel, SOCKET hSocket);
	virtual ~CVideoSessionServerTcp(void);

public:
	virtual void ReleaseConnections(void);
	
	virtual void OnReceivedFrame(const char*pFrameData,int nLen);  // inout data

	virtual void OnReceivedDataFromChannel(bool bTcp,const char*pData,int nLen); // outin data
	virtual void OnReceivedDataFromChannelDirection(bool bTcp,const char*pData,int nLen);
	virtual void OnReceivedDataFromChannelEnable(bool bTcp,const char*pData,int nLen);
	virtual bool IsDisconnected(void);
	virtual void ProcessDisable() {
	}
	virtual unsigned long GetBufferingFrameCount(void);

	//////////////////////////////////////////////////////////////////////////
	// source
	void OnEnable(void);
	void OnDisable(void);
	void OnRequestKeyFrame(void);

	bool WantReading(void);

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool IsEnable(void);
	//bool IsRequestKeyFrame(void);

	// udp interface
	//virtual void OnReceivedFrame(const char*pData,int nLen) {};

	void Reset();
	void OnReverseDirection(bool bSource);

	void SetClientServer(bool bServer)
	{
		m_bClientServer = bServer;
	}

protected:
	//////////////////////////////////////////////////////////////////////////
	// source
	//bool						m_bIsEnable;

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool						m_bEnable;
	//bool						m_bRequestKeyFrame;

	bool	m_bClientServer;

	unsigned long			m_ulUserSessionID;
	unsigned short			m_usCardNo;

//public:
//	virtual void OnError(void)
//	{
//		AVMTSConnection::OnError();
//		printf("CVideoSessionServerTcp OnError\n");
//	}
//	virtual void OnDisconnected(void)
//	{
//		AVMTSConnection::OnDisconnected();
//		printf("CVideoSessionServerTcp OnDisconnected\n");
//	}
};

#endif
