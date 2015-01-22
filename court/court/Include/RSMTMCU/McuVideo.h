#ifndef __MCUVIDEO_H__
#define __MCUVIDEO_H__

#include "VideoChannel.h"
#include "VideoSessionServerTcp.h"
#include "VideoSessionClientTcp.h"
//////////////////////////////////////////////////////////////////////////
#include "VideoSessionServerUdp.h"
#include "VideoSessionClientUdp.h"
#include "VideoSessionSendUdp.h"
#include "VideoSessionReceiverUdp.h"
//////////////////////////////////////////////////////////////////////////
#include <list>
#include "../libHPBaseclass/ListPtr.h"

#ifdef YOUHUA
#define FREEVIDEOCHANNELSIZE 5
#else
#define FREEVIDEOCHANNELSIZE 10
#endif

typedef std::map<unsigned long,CVideoChannel*>					MapVideoChannel;

typedef std::map<unsigned long,CVideoSessionServerTcp*>			MapVideoSessionServerTCP;
typedef std::map<unsigned long,CVideoSessionClientTcp*>			MapVideoSessionClientTCP;
//////////////////////////////////////////////////////////////////////////
typedef std::map<unsigned long,CVideoSessionServerUdp*>			MapVideoSessionServerUdp;
typedef std::map<unsigned long,CVideoSessionClientUdp*>			MapVideoSessionClientUdp;
typedef std::map<unsigned long,CVideoSessionSendUdp*>			MapVideoSessionSendUdp;
typedef std::map<unsigned long,CVideoSessionReceiverUdp*>		MapVideoSessionReceiverUdp;
//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CMcuVideo
	: public IVideoSessionClientNotify
{
public:
	CMcuVideo();
	virtual ~CMcuVideo(void);

public:
	static CMcuVideo* Instance(void);

public:
	void ReleaseConnections(void);
	bool OnAVMTManagerTCPNotifyConnected(SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	//////////////////////////////////////////////////////////////////////////
	void OnAVMTManagerUDPReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);
	//////////////////////////////////////////////////////////////////////////

	//void AddVideoChannel(CVideoChannel*pChannel);
	//void RemoveVideoChannel(CVideoChannel*pChannel);

	void AddVideoSessionServerTCP(CVideoSessionServerTcp*pSessionServerTCP);
	void RemoveVideoSessionServerTCP(CVideoSessionServerTcp*pSessionServerTCP);
	void AddVideoSessionClientTCP(CVideoSessionClientTcp*pSessionClientTCP);
	void RemoveVideoSessionClientTCP(CVideoSessionClientTcp*pSessionClientTCP);
	//////////////////////////////////////////////////////////////////////////
	void AddVideoSessionServerUdp(CVideoSessionServerUdp*pSessionServerUdp);
	void RemoveVideoSessionServerUdp(CVideoSessionServerUdp*pSessionServerUdp);
	void AddVideoSessionClientUdp(CVideoSessionClientUdp*pSessionClientUdp);
	void RemoveVideoSessionClientUdp(CVideoSessionClientUdp*pSessionClientUdp);
	void AddVideoSessionSendUdp(CVideoSessionSendUdp*pSessionSendUdp);
	void RemoveVideoSessionSendUdp(CVideoSessionSendUdp*pSessionSendUdp);
	void AddVideoSessionReceiverUdp(CVideoSessionReceiverUdp*pSessionReceiverUdp);
	void RemoveVideoSessionReceiverUdp(CVideoSessionReceiverUdp*pSessionReceiverUdp);
	//////////////////////////////////////////////////////////////////////////

	void DoCheck(void);

	//void ClearVideoSession(unsigned long ulChannelID);
	CVideoSessionClientTcp* CreateVideoSessionClientTCP(IVideoSessionClientNotify&rNotify,unsigned long ulChannelID);
	//////////////////////////////////////////////////////////////////////////
	CVideoSessionClientUdp* CreateVideoSessionClientUdp(/*IVideoSessionClientNotify&rNotify,*/unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort, UINT32 iMcuID);
	CVideoSessionSendUdp* CreateVideoSessionSendUdp(/*IVideoSessionClientNotify&rNotify,*/unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);
	CVideoSessionReceiverUdp* CreateVideoSessionReceiverUdp(/*IVideoSessionClientNotify&rNotify,*/unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);
	//////////////////////////////////////////////////////////////////////////
	
	//bool DoSendData(void);

	virtual void OnIVideoSessionClientNotifyConnected(); //

	CVideoChannel* GetChannel(unsigned long ulChannelID);
	CVideoChannel* GetChannelOfSession(unsigned long ulSessionID, unsigned short usCardNo);
	CVideoChannel* NewChannel(unsigned long ulChannelID = 0);
	CVideoChannel* GetFreeChannel(unsigned long ulSessionID, unsigned short usCardNo, bool& bMatch);
	void FreeChannel(unsigned long ulChannelID);
	void FreeChannelOfSession(unsigned long ulSessionID);
	void FreeChannelOfSession(unsigned long ulSessionID, unsigned short usCardNo);

	void GetListChannelID(/*std::list<unsigned long>*/ListPtr& listChannelID);

	void SetTos(unsigned char ucTos);

#ifdef MAINTAINUDPPACKET
	bool DoSendData(void);
#endif

	void ReleaseServerUdp(UINT32 iMcuID);

	void DeleteChannel(UINT32 ulChannelID);

	bool FindClientUdpSessionID(UINT32 ulSessionID);
	bool FindClientTcpSessionID(UINT32 ulSessionID);

protected:
	//void CheckVideoChannel(void); //
	void ClearVideoChannel(void);

	void CheckVideoSessionServerTCP(void);
	void ClearVideoSessionServerTCP(void);
	void CheckVideoSessionClientTCP(void);
	void ClearVideoSessionClientTCP(void);
	//////////////////////////////////////////////////////////////////////////
	void CheckVideoSessionServerUdp(void);
	//void ClearVideoSessionServerUdp(void);
	void CheckVideoSessionClientUdp(void);
	//void ClearVideoSessionClientUdp(void);
	void CheckVideoSessionSendUdp(void);
	void ClearVideoSessionSendUdp(void);
	void CheckVideoSessionReceiverUdp(void);
	void ClearVideoSessionReceiverUdp(void);
	//////////////////////////////////////////////////////////////////////////

protected:
	MapVideoChannel				m_MapVideoChannel;
	AVCritSec					m_AVCritSecMapVideoChannel;

	MapVideoSessionServerTCP	m_MapVideoSessionServerTCP;
	AVCritSec					m_AVCritSecMapVideoSessionServerTCP;
	MapVideoSessionClientTCP	m_MapVideoSessionClientTCP;
	AVCritSec					m_AVCritSecMapVideoSessionClientTCP;
	//////////////////////////////////////////////////////////////////////////
	MapVideoSessionServerUdp	m_MapVideoSessionServerUdp;
	AVCritSec					m_AVCritSecMapVideoSessionServerUdp;
	MapVideoSessionClientUdp	m_MapVideoSessionClientUdp;
	AVCritSec					m_AVCritSecMapVideoSessionClientUdp;
	MapVideoSessionSendUdp		m_MapVideoSessionSendUdp;
	AVCritSec					m_AVCritSecMapVideoSessionSendUdp;
	MapVideoSessionReceiverUdp	m_MapVideoSessionReceiverUdp;
	AVCritSec					m_AVCritSecMapVideoSessionReceiverUdp;
	//////////////////////////////////////////////////////////////////////////

	unsigned short				m_usFreeChannelCount;
};

#endif
