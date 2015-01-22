 #ifndef __RSMTMCUMSG_H__
#define __RSMTMCUMSG_H__

#include "AVDataPacket.h"
#include "TopMcuDataStore.h"
#include "SonMcuDataStore.h"
#include "RSMTMsgTcp.h"
#include "FileIO.h"
#include <map>


typedef std::map<void*,RSMTMsgTCP*>		MapRSMTMsgTCPPending;
typedef std::map<UINT32,RSMTMsgTCP*>	MapRSMTMsgTCP;
typedef std::map<UINT32,CFileIO*>	    MapFileIO;
typedef std::map<std::string,ListMcuID*> MapListInceptAV;


class AFX_EXT_CLASS RSMTMCUManager;
class AFX_EXT_CLASS RSMTMCUMsg  
{
public:
	RSMTMCUMsg(RSMTMCUManager&rAVMTMCUManager);
	virtual ~RSMTMCUMsg(void);

public:
	static RSMTMCUMsg*Instance(void);

public:
	virtual void ReleaseConnections(void);
	virtual bool OnAVMTManagerTCPNotifyConnected(SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);

	virtual void AddFileSource(UINT32 ulFileSourceID,RSMTMsgTCP*pAVMTFileSource);
	virtual void RemoveFileSource(UINT32 ulFileSourceID);
	virtual void CheckFileSource(void);
	virtual void ClearFileSource(void);

	virtual void AddFileSourcePending(RSMTMsgTCP*pAVMTFileSource);
	virtual void RemoveFileSourcePending(RSMTMsgTCP*pAVMTFileSource);
	virtual void CheckFileSourcePending(void);
	virtual void ClearFileSourcePending(void);

	virtual void AddFileIO(UINT32 ulFileSourceID,CFileIO*pAVMTFileSource);
	virtual void RemoveFileIO(UINT32 ulFileSourceID);
	virtual void ClearFileIO(void);

	virtual int	 OnRecvInMsg(RSMTMsgTCP* pMsgTcp,const void*pData,int nLen);
	virtual void DoCheck(void);
	virtual void OnRSMTMsgTCPNotifyDisconnected(RSMTMsgTCP *pRSMTMsgTCP);

	void SetSendInitEnd(bool bValue) { m_bSendInitEnd = bValue; }
	bool GetSendInitEnd() { return m_bSendInitEnd; }
	void SetClientCount(UINT16 iCount) { m_iClientCount = iCount; }

	CSonMcuDataStore*		m_pSonMcuDataStore;
	CTopMcuDataStore*		m_pTopMcuDataStore;

protected:
	RSMTMCUManager&			m_rAVMTMCUManager;
	bool					m_bSendInitEnd;

	AVCritSec				m_AVCritSecMapMsgServerTcp;
	MapRSMTMsgTCPPending	m_MapMsgServerTcpPending;
	MapRSMTMsgTCP			m_MapMsgServerTcp;

	AVCritSec				m_AVCritSecMapFileIO;
	MapFileIO				m_MapFileIO;

	UINT16					m_iClientCount;

	AVCritSec				m_AVCritSecMapListInceptVideo;
	MapListInceptAV			m_MapListInceptVideo;

	AVCritSec				m_AVCritSecMapListInceptAudio;
	MapListInceptAV			m_MapListInceptAudio;

	friend class			RSMTMsgTCP;

protected:
	void	SendInitMsg(RSMTMsgTCP *pRSMTMsgTCP);
	void	SendInitMcuInfo(RSMTMsgTCP *pRSMTMsgTCP);
	void	SendInitConferenceBaseInfo(RSMTMsgTCP *pRSMTMsgTCP, UINT32 iSessionID);
#ifdef NETTVANDBROADCAST
	void	SendInitChannelInfo(RSMTMsgTCP *pRSMTMsgTCP, UINT32 iTelevisionID);
#endif
	void	BroadcastMcuLogin(RSMTMsgTCP *pRSMTMsgTCP, UINT32 iMcuID);

	void	ProcessFromDownMsg(UINT32 iCmdID, const void* pData, int nLen);
	UINT16	ProcessFromUpMsg(UINT32 iCmdID, AVDataInPacket *pInPacket, const void* pData, int nLen);
	void	TopMcuProcessMsg(UINT32 iCmdID, UINT32 iMcuID, AVDataInPacket *pInPacket, const void* pData, int nLen, RSMTMsgTCP* pMsgTcp);
	void	ProcessBroadMsg(UINT32 iCmdID, UINT32 iMcuID, AVDataInPacket *pInPacket, const void* pData, int nLen, RSMTMsgTCP *pRSMTMsgTCP = NULL);
	
	void	SendConferenceInitMsg(UINT32 iConferenceID, RSMTMsgTCP* pAVMTFileSource);
	void    SendConferenceSynchronizationInitMsg(UINT32 iConferenceID, RSMTMsgTCP* pAVMTFileSource);
	void    SendConferenceMsg(UINT32 iConferenceID, RSMTMsgTCP* pAVMTFileSource, tConferenceInfo* pCurtConferenceInfo);
	
	void	OnBroadcastUserLogin(UINT32 iSessionID, byte iOnlineFlag, UINT32 iMcuID, const char* strOnlineTime);
	void	OnBroadcastUserLogout(UINT32 iSessionID);
	void	OnBroadcastConferenceLogin(UINT32 iSessionID, UINT32 iConferenceID);
	void	OnBroadcastConferenceLogout(UINT32 iSessionID, UINT32 iConferenceID, RSMTMsgTCP *pRSMTMsgTCP);
	void	OnBroadcastChangeConferenceTemplet(UINT32 iConferenceID,byte WinNo, byte iWinClass, byte bWinTemplate, byte iWinNumber, byte iWinType);
	void	OnBroadcastChangeName(UINT32 uiSessionID, const char* cName);

	void	ConferenceControlProcess(UINT32 iCmdID, UINT32 iMcuID, AVDataInPacket *pInPacket/*, UINT32 iSessionID, UINT32 iConferenceID*/, UINT32& iUpConferenceID, UINT32& iUpSessionID);
	void	ConferenceUserControlProcess(UINT32 iCmdID, UINT32 iConferenceID, byte bValue);

	void	OnBroadcastDeleteMcu(UINT32 iMcuID);
	void	OnBroadcastUpdateMcu(tMCUInfo *pInfo);
	void	OnBroadcastInsertMcu(tMCUInfo *pInfo);

	void	OnBroadcastDeleteConference(UINT32 iConferenceID);
	void	OnBroadcastUpdateConference(tConferenceInfo *pInfo);
	void	OnBroadcastInsertConference(tConferenceInfo *pInfo);

	void	OnBroadcastDeleteConferenceUser(UINT32 iConferenceID, UINT32 iSessionID);
	void	OnBroadcastUpdateConferenceUser(tConferenceUserInfo *pInfo);
	void	OnBroadcastInsertConferenceUser(tConferenceUserInfo *pInfo);

	void	OnBroadcastDeleteTemplet(tTempletInfo *pInfo);
	void	OnBroadcastUpdateTemplet(tTempletInfo *pInfo);
	void	OnBroadcastInsertTemplet(tTempletInfo *pInfo);

#ifdef NETTVANDBROADCAST
	void	OnBroadcastDeleteChannel(tChannelInfo *pInfo);
	void	OnBroadcastUpdateChannel(tChannelInfo *pInfo);
	void	OnBroadcastInsertChannel(tChannelInfo *pInfo);
#endif

	void	OnAddNewWbChannel(UINT32 iChannelID);
	void	OnAddNewFileChannel(UINT32 iChannelID);
	void	OnAddNewDesktopChannel(UINT32 iChannelID);
	void	OnAddNewAudioChannel(UINT32 iChannelID);
	void	OnAddNewVideoChannel(UINT32 iChannelID);
	

	// get the route path of the sessionID
	bool	GetSessionIDPath(UINT32 iSessionID, UINT32 iCmdID, AVDataOutPacket& outPacket, UINT32& iNextMcuID);
	// send msg to the sessionID
	UINT16	SendMsgToSessionID(AVDataOutPacket& outPacket, UINT32 iNextMcuID);
	// send msg to the all presiders(option to filtrate the sessionID)
	void	SendMsgToPresiders(UINT32 iSessionID, UINT32 iConferenceID, AVDataOutPacket& outPacket, bool bFiltrate);
	// enable the RSMTMsgTCP
	void	EnableRSMTMsgTCP(UINT32 iMcuID, UINT32 iConferenceID);
	// find the RSMTMsgTCP
	RSMTMsgTCP*	FindRSMTMsgTCP(UINT32 iMcuID);
	void OnDisconnectedNortify(RSMTMsgTCP* pRSMTMsgTCP);

	//////////////////////////////////////////////////////////////////////////
	// common
	CDataStore* GetDataStore();

	// video
	bool BroadcastVideoChannel(UINT32 iSessionID, byte ucVideoCardNo, UINT32& iChannelID);
	bool SearchVideoInfo(ListtWinInfo* pListInfo, byte ucFrameNo, UINT32 iSessionID, byte ucVideoCardNo, byte ucWnd, byte ucFrame, tWinInfo*& pInfoOld, tWinInfo*& pInfoNull, tWinInfo*& pInfoAim, UINT32& iChannelID);
	bool ProcessBroadcastVideo(UINT32 iConferenceID, UINT32 iSessionID, byte ucVideoCardNo, byte ucWnd, byte ucFrame, UINT32& iChannelID);

	bool BroadcastVideoChannelClose(UINT32 iChannelID);
	bool FindVideoInfo(ListtWinInfo* pListInfo, UINT32 iSessionID, byte ucVideoCardNo, UINT32& iChannelID);
	bool ProcessBroadcastVideoClose(UINT32 iConferenceID, UINT32 iSessionID, byte ucVideoCardNo, UINT32& iChannelID);

	// audio
	bool BroadcastAudioChannel(UINT32 iSessionID, byte ucVideoCardNo, UINT32& iChannelID);
	bool SearchAudioInfo(ListtWinInfo* pListInfo, byte ucFrameNo, UINT32 iSessionID, byte ucVideoCardNo, byte ucWnd, byte ucFrame, tWinInfo*& pInfoOld, tWinInfo*& pInfoNull, tWinInfo*& pInfoAim, UINT32& iChannelID);
	bool ProcessBroadcastAudio(UINT32 iConferenceID, UINT32 iSessionID, byte ucVideoCardNo,byte ucWnd, byte ucFrame, UINT32& iChannelID);

	bool BroadcastAudioChannelClose(UINT32 iChannelID);
	bool FindAudioInfo(ListtWinInfo* pListInfo, UINT32 iSessionID, byte ucVideoCardNo, UINT32& iChannelID);
	bool ProcessBroadcastAudioClose(UINT32 iConferenceID, UINT32 iSessionID, byte ucVideoCardNo, UINT32& iChannelID);

	// wb
	bool BroadcastWbChannel(UINT32 iConferenceID, UINT32& iChannelID);
	bool SearchWbInfo(ListtWinInfo* pListInfo, byte ucFrameNo, UINT32 iConferenceID, byte ucWnd, byte ucFrame, tWinInfo*& pInfoOld, tWinInfo*& pInfoNull, tWinInfo*& pInfoAim, UINT32& iChannelID);
	bool ProcessBroadcastWb(UINT32 iConferenceID, byte ucWnd, byte ucFrame, UINT32& iChannelID);

	bool BroadcastWbChannelClose(UINT32 iChannelID);
	bool FindWbInfo(ListtWinInfo* pListInfo, UINT32 iConferenceID, UINT32& iChannelID);
	bool ProcessBroadcastWbClose(UINT32 iConferenceID, UINT32& iChannelID);

	// file
	bool BroadcastFileChannel(UINT32 iConferenceID, const char* cFileName, UINT32& iChannelID);
	bool ProcessBroadcastStartFile(UINT32 iConferenceID, const char* cFileName, UINT32& iChannelID);
	bool ProcessBroadcastFileClose(UINT32 iConferenceID, const char* cFileName, UINT32& iChannelID);

	// desktop
	bool BroadcastDesktopChannel(UINT32 iSessionID, UINT32& iChannelID);
	bool SearchDesktopInfo(ListtWinInfo* pListInfo, byte ucFrameNo, UINT32 iSessionID, byte ucWnd, byte ucFrame, tWinInfo*& pInfoOld, tWinInfo*& pInfoNull, tWinInfo*& pInfoAim, UINT32& iChannelID);
	bool ProcessBroadcastDesktop(UINT32 iConferenceID, UINT32 iSessionID, byte ucWnd, byte ucFrame, UINT32& iChannelID);

	bool BroadcastDesktopChannelClose(UINT32 iChannelID);
	bool FindDesktopInfo(ListtWinInfo* pListInfo, UINT32 iSessionID, UINT32& iChannelID);
	bool ProcessBroadcastDesktopClose(UINT32 iConferenceID, UINT32 iSessionID, UINT32& iChannelID);

	// talkover
	//bool BroadcastTalkoverChannel(UINT32 iSessionID, UINT32& iChannelID);
	bool SearchTalkoverInfo(ListtWinInfo* pListInfo, byte ucFrameNo, UINT32 iConferenceID, byte ucWnd, byte ucFrame, tWinInfo*& pInfoOld, tWinInfo*& pInfoNull, tWinInfo*& pInfoAim, UINT32& iChannelID);
	bool ProcessBroadcastTalkover(UINT32 iConferenceID, byte ucWnd, byte ucFrame, UINT32& iChannelID);

	//bool BroadcastTalkoverChannelClose(UINT32 iChannelID);
	bool FindTalkoverInfo(ListtWinInfo* pListInfo, UINT32 iConferenceID, UINT32& iChannelID);
	bool ProcessBroadcastTalkoverClose(UINT32 iConferenceID, UINT32& iChannelID);

	// swap position
	bool SearchSwapPosition(ListtWinInfo* pListInfo, byte ucFrameNo, EFrameInfoType eFrameType, UINT32 iSessionID, byte ucVideoCardNo, byte ucWnd, byte ucFrame, tWinInfo*& pInfoOld, tWinInfo*& pInfoAim);
	bool ProcessSwapPosition(UINT32 iConferenceID, EFrameInfoType eFrameType, UINT32 iSessionID, byte ucVideoCardNo, byte ucWnd, byte ucFrame);
	//////////////////////////////////////////////////////////////////////////

	bool FreeAudioChannel(UINT32 iChannelID);
	bool FreeVideoChannel(UINT32 iChannelID);
	bool FreeWbChannel(UINT32 iChannelID);
	bool FreeFileChannel(UINT32 iChannelID);
	bool FreeFileChannelOfSessionID(UINT32 iSessionID);
	bool FreeDesktopChannel(UINT32 iChannelID);

	void SearchAllChannelClose(ListtWinInfo* pListInfo, UINT32 iSessionID, UINT32 iConferenceID, RSMTMsgTCP *pRSMTMsgTCP);
	void ProcessAllChannelClose(UINT32 iConferenceID, UINT32 iSessionID, RSMTMsgTCP *pRSMTMsgTCP);

	void OnBroadcastSaveTalkoverData(UINT32 iSessionID, UINT32 iConferenceID, UINT32 iTalkType, const char* cTalkoverData);
	void SendConferenceTalkoverData(UINT32 iConferenceID, RSMTMsgTCP* pAVMTFileSource);

	void IsAllowEnterConferenceUser(UINT32 iConferenceID, byte bValue);

	void ProcessBroadcastDisconnectedMcuTest(UINT32 iMcuID, RSMTMsgTCP* pRSMTMsgTCP);

	int BroadMsg(UINT32 iSessionID, RSMTMsgTCP* pAVMTFileSource, const void* pData, int nLen);

	// 视频单接用户列表
	void AddMapListInceptVideo(std::string iMcuID, UINT32 iSessionID);
	void DelMapListInceptVideo(std::string iMcuID, UINT32 iSessionID);
	void ClearMapListInceptVideo();
	AVCritSec* GetAVCritSecMapListInceptVideo() { return &m_AVCritSecMapListInceptVideo; }
	ListMcuID* GetMapListInceptVideo(std::string iMcuID) { return m_MapListInceptVideo[iMcuID]; }

	// 音频单接用户列表
	void AddMapListInceptAudio(std::string iMcuID, UINT32 iSessionID);
	void DelMapListInceptAudio(std::string iMcuID, UINT32 iSessionID);
	void ClearMapListInceptAudio();
	AVCritSec* GetAVCritSecMapListInceptAudio() { return &m_AVCritSecMapListInceptAudio; }
	ListMcuID* GetMapListInceptAudio(std::string iMcuID) { return m_MapListInceptAudio[iMcuID]; }

	void ProcessInceptAV(UINT32 iSessionID);
	void SendCloseIncept(std::string strKey, UINT32 iCmd);

	void SendVideoSoundInfoToSpokeMan(UINT32 iSessionID, UINT32 iConferenceID, UINT32 iMcuID);
	void GetMcuIDofUser(UINT32 iSessionID, UINT32& iMcuID);
	bool GetConferenceSpokeMan(UINT32 iConferenceID, UINT32& iSessionID);
	void FetchConferenceInitMsgSpokeMan(UINT32 iConferenceID, UINT32 iSessionID);

public:
	void	SetMcuDataStore(CDataStore* pDataStore, EInfoType eType);
	int		OnMsgFromUpMcu(const void*pData, int nLen);
	char*   GetUserName(UINT32 iSessionID);
	UINT32  GetConferenceID(UINT32 iSessionID);
	byte  GetUserDegreeFlag(UINT32 iSessionID, UINT32 iConferenceID);

	//////////////////////////////////////////////////////////////////////////

	void OnDispatchUserLoginRep(UINT16 iRet, UINT32 iSessionID, UINT32 iPMsgTcp, UINT32 iUpMcuID, const char* cUser, byte iOnlineFlag, unsigned char* pData, int nLen);
	void OnDispatchChangeNameRep(UINT16 iRet, UINT32 iSessionID, UINT32 iPMsgTcp,const char* cName);
	void OnDispatchChangePassRep(UINT16 iRet, UINT32 iSessionID, UINT32 iPMsgTcp);
};

#endif
