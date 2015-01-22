#ifndef __MCUWB_H__
#define __MCUWB_H__

#include "WbChannel.h"
#include "WbSessionServerTcp.h"
#include "WbSessionClientTcp.h"
#include <list>
#include "../libHPBaseclass/ListPtr.h"

#ifdef YOUHUA
#define FREEWBCHANNELSIZE 2
#else
#define FREEWBCHANNELSIZE 4
#endif

typedef std::map<unsigned long,CWbChannel*>						MapWbChannel;
typedef std::map<unsigned long,CWbSessionServerTcp*>			MapWbSessionServerTCP;
//typedef std::map<unsigned long,AVMTWBSessionServerUDP*>		MapAVMTWBSessionServerUDP;
//typedef std::map<unsigned long,AVMTWBSessionClientUDP*>		MapAVMTWBSessionClientUDP;
//////////////////////////////////////////////////////////////////////////
typedef std::map<unsigned long,CWbSessionClientTcp*>			MapWbSessionClientTCP;
//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CMcuWb
	: public IWbSessionClientNotify
{
public:
	CMcuWb(void);
	virtual ~CMcuWb(void);

public:
	static CMcuWb* Instance(void);

public:
	void ReleaseConnections(void);
	bool OnAVMTManagerTCPNotifyConnected(SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	void AddWbChannel(CWbChannel*pChannel);
	void RemoveWbChannel(CWbChannel*pChannel);
	void AddWbSessionServerTCP(CWbSessionServerTcp*pSessionServerTCP);
	void RemoveWbSessionServerTCP(CWbSessionServerTcp*pSessionServerTCP);
	//void AddAVMTWBSessionServerUDP(AVMTWBSessionServerUDP*pAVMTWBSessionServerUDP);
	//void RemoveAVMTWBSessionServerUDP(AVMTWBSessionServerUDP*pAVMTWBSessionServerUDP);
	//void AddAVMTWBSessionClientUDP(AVMTWBSessionClientUDP*pAVMTWBSessionClientUDP);
	//void RemoveAVMTWBSessionClientUDP(AVMTWBSessionClientUDP*pAVMTWBSessionClientUDP);
	void DoCheck(void);

	//void OnAVMTManagerUDPReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);

	void ClearWbSession(unsigned long ulChannelID);
	CWbSessionClientTcp* CreateWbSessionClientTCP(IWbSessionClientNotify&rNotify,unsigned long ulChannelID);
	//AVMTWBSessionClientUDP*CreateAVMTWBSessionClientUDP(IWbSessionClientNotify&rNotify,unsigned long ulChannelID);
	
	//bool DoSendData(void);

	//////////////////////////////////////////////////////////////////////////
	virtual void OnIWbSessionClientNotifyConnected(); //
	virtual void OnReceivedFrame(const char*pFrameData,int nLen);

	void AddWbSessionClientTCP(CWbSessionClientTcp*pSessionClientTCP);
	void RemoveWbSessionClientTCP(CWbSessionClientTcp*pSessionClientTCP);

	CWbChannel* GetChannelOfConference(unsigned long ulConferenceID);
	CWbChannel* GetChannel(unsigned long ulChannelID = 0);
	CWbChannel* NewChannel(unsigned long ulChannelID = 0);
	CWbChannel* GetFreeChannel(unsigned long ulConferenceID, bool& bMatch);
	void FreeChannel(unsigned long ulChannelID);
	void FreeChannelOfConference(unsigned long ulConferenceID);
	void GetListChannelID(/*std::list<unsigned long>*/ListPtr& listChannelID);
	//////////////////////////////////////////////////////////////////////////

	void DeleteChannel(UINT32 ulChannelID);

	bool FindClientTcpSessionID(UINT32 ulSessionID);

protected:
	void CheckWbChannel(void); //
	void ClearWbChannel(void);
	void CheckWbSessionServerTCP(void);
	void ClearWbSessionServerTCP(void);
	//void CheckAVMTWBSessionServerUDP(void);
	//void ClearAVMTWBSessionServerUDP(void);
	////void CheckAVMTWBSessionClientUDP(void);
	////void ClearAVMTWBSessionClientUDP(void);

	//////////////////////////////////////////////////////////////////////////
	void CheckWbSessionClientTCP(void);
	void ClearWbSessionClientTCP(void);
	//////////////////////////////////////////////////////////////////////////

protected:
	MapWbChannel				m_MapWbChannel;
	AVCritSec					m_AVCritSecMapWbChannel;
	MapWbSessionServerTCP		m_MapWbSessionServerTCP;
	AVCritSec					m_AVCritSecMapWbSessionServerTCP;
	//MapAVMTWBSessionServerUDP	m_MapAVMTWBSessionServerUDP;
	//AVCritSec					m_AVCritSecMapAVMTWBSessionServerUDP;
	//MapAVMTWBSessionClientUDP	m_MapAVMTWBSessionClientUDP;
	//AVCritSec					m_AVCritSecMapAVMTWBSessionClientUDP;

	//////////////////////////////////////////////////////////////////////////
	MapWbSessionClientTCP		m_MapWbSessionClientTCP;
	AVCritSec					m_AVCritSecMapWbSessionClientTCP;
	unsigned short				m_usFreeChannelCount;
	//////////////////////////////////////////////////////////////////////////

};

#endif
