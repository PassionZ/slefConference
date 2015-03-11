#ifndef __MCUDESKTOP_H__
#define __MCUDESKTOP_H__

#include "DesktopChannel.h"
#include "DesktopSessionServerTcp.h"
#include "DesktopSessionClientTcp.h"
#include <list>
#include "../libHPBaseclass/ListPtr.h"

#ifdef YOUHUA
#define FREEDESKTOPCHANNELSIZE 4
#else
#define FREEDESKTOPCHANNELSIZE 4
#endif

typedef std::map<unsigned long,CDesktopChannel*>					MapDesktopChannel;
typedef std::map<unsigned long,CDesktopSessionServerTcp*>			MapDesktopSessionServerTCP;
//typedef std::map<unsigned long,AVMTWBSessionServerUDP*>		MapAVMTWBSessionServerUDP;
//typedef std::map<unsigned long,AVMTWBSessionClientUDP*>		MapAVMTWBSessionClientUDP;
//////////////////////////////////////////////////////////////////////////
typedef std::map<unsigned long,CDesktopSessionClientTcp*>			MapDesktopSessionClientTCP;
//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CMcuDesktop
	: public IDesktopSessionClientNotify
{
public:
	CMcuDesktop(void);
	virtual ~CMcuDesktop(void);

public:
	static CMcuDesktop* Instance(void);

public:
	void ReleaseConnections(void);
	bool OnAVMTManagerTCPNotifyConnected(SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	void AddDesktopChannel(CDesktopChannel*pChannel);
	void RemoveDesktopChannel(CDesktopChannel*pChannel);
	void AddDesktopSessionServerTCP(CDesktopSessionServerTcp*pSessionServerTCP);
	void RemoveDesktopSessionServerTCP(CDesktopSessionServerTcp*pSessionServerTCP);
	//void AddAVMTWBSessionServerUDP(AVMTWBSessionServerUDP*pAVMTWBSessionServerUDP);
	//void RemoveAVMTWBSessionServerUDP(AVMTWBSessionServerUDP*pAVMTWBSessionServerUDP);
	//void AddAVMTWBSessionClientUDP(AVMTWBSessionClientUDP*pAVMTWBSessionClientUDP);
	//void RemoveAVMTWBSessionClientUDP(AVMTWBSessionClientUDP*pAVMTWBSessionClientUDP);
	void DoCheck(void);

	//void OnAVMTManagerUDPReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);

	void ClearDesktopSession(unsigned long ulChannelID);
	CDesktopSessionClientTcp* CreateDesktopSessionClientTCP(IDesktopSessionClientNotify&rNotify,unsigned long ulChannelID);
	//AVMTWBSessionClientUDP*CreateAVMTWBSessionClientUDP(IDesktopSessionClientNotify&rNotify,unsigned long ulChannelID);
	
	//bool DoSendData(void);

	//////////////////////////////////////////////////////////////////////////
	virtual void OnIDesktopSessionClientNotifyConnected(); //

	void AddDesktopSessionClientTCP(CDesktopSessionClientTcp*pSessionClientTCP);
	void RemoveDesktopSessionClientTCP(CDesktopSessionClientTcp*pSessionClientTCP);

	CDesktopChannel* GetChannel(unsigned long ulChannelID=0);
	CDesktopChannel* GetChannelOfSession(unsigned long ulSessionID);
	CDesktopChannel* NewChannel(unsigned long ulChannelID = 0);
	CDesktopChannel* GetFreeChannel(unsigned long ulSessionID, bool& bMatch);
	void FreeChannel(unsigned long ulChannelID);
	void FreeChannelOfSession(unsigned long ulSessionID);
	void GetListChannelID(/*std::list<unsigned long>*/ListPtr& listChannelID);
	//////////////////////////////////////////////////////////////////////////

	void DeleteChannel(UINT32 ulChannelID);

	bool FindClientTcpSessionID(UINT32 ulSessionID);

protected:
	void CheckDesktopChannel(void); //
	void ClearDesktopChannel(void);
	void CheckDesktopSessionServerTCP(void);
	void ClearDesktopSessionServerTCP(void);
	//void CheckAVMTWBSessionServerUDP(void);
	//void ClearAVMTWBSessionServerUDP(void);
	////void CheckAVMTWBSessionClientUDP(void);
	////void ClearAVMTWBSessionClientUDP(void);

	//////////////////////////////////////////////////////////////////////////
	void CheckDesktopSessionClientTCP(void);
	void ClearDesktopSessionClientTCP(void);
	//////////////////////////////////////////////////////////////////////////

protected:
	MapDesktopChannel			m_MapDesktopChannel;
	AVCritSec					m_AVCritSecMapDesktopChannel;
	MapDesktopSessionServerTCP	m_MapDesktopSessionServerTCP;
	AVCritSec					m_AVCritSecMapDesktopSessionServerTCP;
	//MapAVMTWBSessionServerUDP	m_MapAVMTWBSessionServerUDP;
	//AVCritSec					m_AVCritSecMapAVMTWBSessionServerUDP;
	//MapAVMTWBSessionClientUDP	m_MapAVMTWBSessionClientUDP;
	//AVCritSec					m_AVCritSecMapAVMTWBSessionClientUDP;

	//////////////////////////////////////////////////////////////////////////
	MapDesktopSessionClientTCP	m_MapDesktopSessionClientTCP;
	AVCritSec					m_AVCritSecMapDesktopSessionClientTCP;
	unsigned short				m_usFreeChannelCount;
	//////////////////////////////////////////////////////////////////////////

};

#endif
