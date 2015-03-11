#ifndef DESKTOPSESSIONSERVERTCP_H_
#define DESKTOPSESSIONSERVERTCP_H_

#include "DesktopSession.h"
#include "../libHPNETIO/AVMTSConnection.h"


class CDesktopSessionServerTcp 
	: public CDesktopSession
	, public AVMTSConnection
{
public:
	CDesktopSessionServerTcp(CDesktopChannel&rChannel, SOCKET hSocket);
	virtual ~CDesktopSessionServerTcp(void);

public:
	virtual void ReleaseConnections(void);
	
	virtual void OnReceivedFrame(const char*pFrameData,int nLen);  // inout data

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen); // outin data
	virtual bool IsDisconnected(void);
	virtual unsigned long GetBufferingFrameCount(void);

	//////////////////////////////////////////////////////////////////////////
	// source
	void OnEnable(void);
	void OnDisable(void);
	//void OnRequestKeyFrame(void);

	bool WantReading(void);

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool IsEnable(void);
	//bool IsRequestKeyFrame(void);

	void Reset();
	void OnReverseDirection(bool bSource);

protected:
	//////////////////////////////////////////////////////////////////////////
	// source
	//bool						m_bIsEnable;

	//////////////////////////////////////////////////////////////////////////
	// sink
	//bool						m_bEnable;
	//bool						m_bRequestKeyFrame;
};

#endif
