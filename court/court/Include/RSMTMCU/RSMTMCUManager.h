// RSMTMCUManager.h: interface for the RSMTMCUManager class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __RSMTMCUMANAGER_H__
#define __RSMTMCUMANAGER_H__

#define USE_DB
//#define MULTITHREAD
//#define TEST
//#define TEST_TEST

#define USEMAP
#define OPTIMIZE
//#define VIEW_CHANNEL


//#define NETTVANDBROADCAST 
////#define VIDEOCAST
//#define NETTV

#ifdef NETTVANDBROADCAST
#include "./DataDefine/RSMsgdefine.h"
#else
#include "../DataDefine/RSMsgdefine.h"
#endif

#define YOUHUA

#include "../libHPNETIO/libHPNETIO.h"
#include "McuAudio.h"
#include "McuVideo.h"
#include "McuWb.h"
#include "McuDesktop.h"
#include "McuFile.h"
#include "RSMTMCUMsg.h"
#include "IRSTcpClientMsgNotify.h"
#include "RSTcpClient.h"
#ifdef USE_DB
#include "DbManager.h"
#endif
#ifdef WIN32
#include <typeinfo.h>
#else
#include <ctype.h>
#endif
#include <assert.h>
#include <map>
#include "Log.h"


class CRSTcpClient;
class AFX_EXT_CLASS RSMTMCUManager  
	: public IHPTCPIONotify
	, public IHPUDPIONotify
#ifdef MULTITHREAD
	, public AVThread
#endif
{
public:
	RSMTMCUManager(IRSTcpClientMsgNotify& rNotify);
	virtual ~RSMTMCUManager(void);

public:
	static RSMTMCUManager*Instance(void);

public:
	virtual bool Connect(const std::string &/*unsigned long*/ ulIP, unsigned short usTCPPort, bool bAnyPort, bool bTcp);
	virtual void ReleaseConnections(void);
	virtual unsigned short GetTCPPort(void);
	virtual unsigned short GetUDPPort(void);
	virtual SOCKET GetSocketHandle(unsigned long ulIP);
	virtual void OnIHPUDPIONotifyReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);

	bool		 DoCheck(void);

	unsigned long m_ulLastCheckTimestamp;
	unsigned long m_ulLastCheckTimestampDb;

protected:
#ifdef MULTITHREAD
	void		 ThreadProcMain(void);
#else
#endif
	virtual bool OnIHPTCPIONotifyConnected(SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);

protected:
#ifdef MULTITHREAD
	bool						m_bWantToStop;
#endif

	CMcuAudio*					m_pAVMTMCUAudio;
	CMcuVideo*					m_pAVMTMCUVideo;
	CMcuWb*						m_pAVMTMCUWB;
	CMcuDesktop*				m_pAVMTMCUDesktop;
	CMcuFile*					m_pAVMTMCUFile;

	IHPTCPIO*					m_pAVMTManagerTCPNormal;
	IHPUDPIO*					m_pAVMTManagerUDP;

	AVBufferPool				m_BufferPool;
#ifdef USE_DB
	CDbManager*					m_pDbManager;
#endif

	friend class RSMTMCUMsg;	
	friend class CRSTcpClient;
	bool						m_bDbFirst;

	std::string					m_strPort;			// test 保存本机端口，作为请求mcuID的基准
	//std::string					m_strMcuName;
	bool						m_bReady;

	EInfoType					m_eInfoType;
	UINT32						m_iSelfMcuID;
	UINT32						m_iUpMcuID;
	UINT32						m_iTopMcuID;

	/*UINT32*/std::string						m_iServerIp;
	UINT16						m_iServerPort;
	/*UINT32*/std::string						m_iInterface;

public:
	IRSTcpClientMsgNotify&		m_rNotify;
	CRSTcpClient*				m_pMsgClientTcp;
	RSMTMCUMsg*					m_pMcuMsg;
	CDataStore*					m_pDataStore; 

	bool						m_bTcp;
	unsigned char				m_ucTos;

	bool		RSTcpClientConnect(const std::string &/*unsigned long*/ ulIP,unsigned short usPort,const std::string &/*unsigned long*/ ulInterface);
	int			SendData(const void*pData,int nLen);
	int			SendDataToDown(const void*pData,int nLen);

	UINT32		GetMcuIDOfPort() { return (UINT32)atoi(m_strPort.c_str()); } // test
	void		SetReady(bool bReady);
	
	bool		InitMcuInfo(const char* host=NULL, const char* name=NULL);
	UINT32		GetSelfMcuID() { return m_iSelfMcuID; }
	void		SetSelfMcuID(UINT32 iMcuID) { m_iSelfMcuID = iMcuID; }
	UINT32		GetUpMcuID() { return m_iUpMcuID;}
	void		SetUpMcuID(UINT32 iMcuID) { m_iUpMcuID = iMcuID; }
	UINT32      GetTopMcuID() { return m_iTopMcuID;}
	void		SetTopMcuID(UINT32 iTopMcuID) { m_iTopMcuID = iTopMcuID;}
	void		SetInfoType(EInfoType eInfoType) { m_eInfoType = eInfoType; }
	EInfoType	GetInfoType() { return m_eInfoType; }
	//std::string		GetSelfMcuName() { return m_strMcuName; }
	//void		SetSelfMcuName(std::string strMcuName) { m_strMcuName = strMcuName; }

	/*UINT32*/std::string		GetServerIp() { return m_iServerIp; }
	UINT16		GetServerPort() { return m_iServerPort; }
	UINT16		GetServerPortUdp() { return m_iServerPort+1; }
	/*UINT32*/std::string		GetInterface() { return m_iInterface; }

	byte		GetTempletInfoWinNumber(tTempletInfo *pInfo);

	void		AddNewAudioChannel(UINT16 nCount);
	void		AddNewVideoChannel(UINT16 nCount);
	void		AddNewWbChannel(UINT16 nCount);
	void		AddNewDesktopChannel(UINT16 nCount);
	void		AddNewFileChannel(UINT16 nCount);
	void		SendFileHistory(UINT32 iConferenceID, RSMTMsgTCP* pRSMTMCUMsg);

	bool		IsTcp() {return m_bTcp == true;}
	void		SetTos(unsigned char ucTos);

	void		SetClientCount(UINT16 iCount) { if (m_pMcuMsg != NULL) m_pMcuMsg->SetClientCount(iCount); }
	bool 		CompareIpAddress(const char * cIpAddr);
	bool 		CompareMACAddress(const char * cMACAddr);

	bool		ReSendConnectHand();

	void		SendPacket(unsigned char* pData,int nLen);

	void		SetDbFirst(bool bDbFirst) { m_bDbFirst = bDbFirst; }
	bool		GetDbFirst() { return m_bDbFirst; }

#ifdef YOUHUA
	void		DeleteAudioChannel(UINT32 ulChannelID);
	void		DeleteVideoChannel(UINT32 ulChannelID);
	void		DeleteDesktopChannel(UINT32 ulChannelID);
	void		DeleteFileChannel(UINT32 ulChannelID);
	void		DeleteWbChannel(UINT32 ulChannelID);
#endif

protected:
	void		DeleteMcu(UINT32 iMcuID);
	void		UpdateMcu(tMCUInfo *ptMCUInfo);
	void		InsertMcu(tMCUInfo *ptMCUInfo);

	void		DeleteConference(UINT32 iConferenceID);
	void		UpdateConference(tConferenceInfo *ptConferenceInfo);
	void		InsertConference(tConferenceInfo *ptConferenceInfo);

	void		DeleteConferenceUser(UINT32 iConferenceID, UINT32 iSessionID);
	void		UpdateConferenceUser(tConferenceUserInfo *ptConferenceUserInfo);
	void		InsertConferenceUser(tConferenceUserInfo *ptConferenceUserInfo);

	void		DeleteTemplet(tTempletInfo *ptInfo);
	void		UpdateTemplet(tTempletInfo *ptInfo);
	void		InsertTemplet(tTempletInfo *ptInfo);

#ifdef NETTVANDBROADCAST
	void		DeleteChannel(tChannelInfo *ptInfo);
	void		UpdateChannel(tChannelInfo *ptInfo);
	void		InsertChannel(tChannelInfo *ptInfo);
#endif

	void		DisconnectedMcu();

	//////////////////////////////////////////////////////////////////////////

	bool		DoCheckDb();
	void		OnDispatchReceivedData(char* pData,int nLen);

	void		OnDispatchUserLoginRep(AVDataInPacket& in);
	void		OnDispatchChangeNameRep(AVDataInPacket& in);
	void		OnDispatchChangePassRep(AVDataInPacket& in);

	void		OnDispatchDeleteMcu(AVDataInPacket& in);
	void		OnDispatchUpdateMcu(AVDataInPacket& in);
	void		OnDispatchInsertMcu(AVDataInPacket& in);

	void		OnDispatchDeleteConference(AVDataInPacket& in);
	void		OnDispatchUpdateConference(AVDataInPacket& in);
	void		OnDispatchInsertConference(AVDataInPacket& in);

	void		OnDispatchDeleteConferenceUser(AVDataInPacket& in);
	void		OnDispatchUpdateConferenceUser(AVDataInPacket& in);
	void		OnDispatchInsertConferenceUser(AVDataInPacket& in);

	void		OnDispatchDeleteTemplet(AVDataInPacket& in);
	void		OnDispatchUpdateTemplet(AVDataInPacket& in);
	void		OnDispatchInsertTemplet(AVDataInPacket& in);

	void		OnDispatchGetTos(AVDataInPacket& in);

	void		OnDispatchGenOrderListTMCUInfo(AVDataInPacket& in);
	void		OnDispatchGenMapListSessionIDofMcuID(AVDataInPacket& in);
	void		OnDispatchGenMapListtConferenceBaseInfo(AVDataInPacket& in);

#ifdef NETTVANDBROADCAST
	void		OnDispatchDeleteChannel(AVDataInPacket& in);
	void		OnDispatchUpdateChannel(AVDataInPacket& in);
	void		OnDispatchInsertChannel(AVDataInPacket& in);
#endif

	void		OnDispatchUpdateConferenceAll(AVDataInPacket& in);

};

#endif
