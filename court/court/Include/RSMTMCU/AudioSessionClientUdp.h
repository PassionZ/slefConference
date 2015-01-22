#ifndef AUDIOSESSIONCLIENTUDP_H_
#define AUDIOSESSIONCLIENTUDP_H_

#include "AudioSession.h"


class AFX_EXT_CLASS CAudioSessionClientUdp :
	public CAudioSession
{
public:
	CAudioSessionClientUdp(CAudioChannel&rChannel,SOCKET hSocket,unsigned long ulIP,unsigned short usPort,unsigned long ulPeerSessionID, UINT32 iMcuID);
	virtual ~CAudioSessionClientUdp(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	void OnReceivedConnectACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort,unsigned long ulChannelID); // client

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
	void OnReceivedEnableACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort);
	void OnReceivedDisableACK(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort);
	virtual void ProcessDisable();

	void OnReceivedNull(unsigned long ulPeerSessionID,unsigned long ulIP,unsigned short usPort);

	void OnReceivedDirectionAck(void);

	void Reset();
	void CopyStatus(CAudioSessionClientUdp* pSession);
	void ReverseDirection();
	void OnReverseDirectionAck();

protected:
	void OnEnable(void);
	void OnDisable(void);

	bool	m_bConnected;
	UINT32  m_iMcuID;

	UINT32  m_ucKeepAliveCount;

	bool	m_bReverseDirectionAck;
};

AFX_EXT_CLASS /*IAudiioSessionClient*/CAudioSessionClientUdp* CreateIAudioSessionClientUdp(/*IAudioSessionClientNotify&rNotify,*/unsigned long ulChannelID/*, unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

#endif