#ifndef AUDIOSERVERUDP_H_
#define AUDIOSERVERUDP_H_

#include "AudioSession.h"


class AFX_EXT_CLASS CAudioSessionServerUdp :
	public CAudioSession
{
public:
	CAudioSessionServerUdp(CAudioChannel&rChannel,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, UINT32 iMcuID);
	virtual ~CAudioSessionServerUdp(void);

public:
	void OnReceivedConnect(void); // server

	void OnReceivedDirection(const char*pData,int nLen/*,unsigned long ulPeerSessionID,unsigned long ulChannelID*/);
	virtual void OnReceivedFrame(const char*pData,int nLen); // inout data
	virtual void OnReceivedDataFromChannel(const char*pData,int nLen); // outin data
	virtual void OnReceivedDataFromChannelDirection(const char*pData,int nLen);
	virtual void OnReceivedDataFromChannelEnable(const char*pData,int nLen);
	virtual bool IsDisconnected(void);

	// sink
	void OnReceivedEnable(void);
	void OnReceivedDisable(void);

	// source
	void OnReceivedEnableACK(void);
	void OnReceivedDisableACK(void);
	virtual void ProcessDisable();

	void OnReceivedNull(void);

	UINT32 GetMcuID() { return m_iMcuID; }

	void OnReceivedDirectionAck(void);

	void Reset();
	void OnReverseDirection(bool bSource);

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

	UINT32  m_iMcuID;

	UINT32  m_ucKeepAliveCount;

	bool	m_bClientServer;

	unsigned long			m_ulUserSessionID;
	unsigned short			m_usCardNo;

	bool	m_bDisConnected;
};

#endif
