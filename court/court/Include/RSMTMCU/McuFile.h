#ifndef __MCUFile_H__
#define __MCUFile_H__

#include "FileChannel.h"
#include "FileSessionServerTcp.h"
#include "FileSessionClientTcp.h"
#include <list>
#include "../libHPBaseclass/ListPtr.h"

#ifdef YOUHUA
#define FREEFILECHANNELSIZE 2
#else
#define FREEFILECHANNELSIZE 4
#endif

typedef std::map<unsigned long,CFileChannel*>					MapFileChannel;
typedef std::map<unsigned long,CFileSessionServerTcp*>			MapFileSessionServerTCP;
//typedef std::map<unsigned long,AVMTFileSessionServerUDP*>		MapAVMTFileSessionServerUDP;
//typedef std::map<unsigned long,AVMTFileSessionClientUDP*>		MapAVMTFileSessionClientUDP;
//////////////////////////////////////////////////////////////////////////
typedef std::map<unsigned long,CFileSessionClientTcp*>			MapFileSessionClientTCP;
//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CMcuFile
	: public ILocalFileNotify
{
public:
	CMcuFile(void);
	virtual ~CMcuFile(void);

public:
	static CMcuFile* Instance(void);

public:
	void ReleaseConnections(void);
	bool OnAVMTManagerTCPNotifyConnected(SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	void AddFileChannel(CFileChannel*pChannel);
	void RemoveFileChannel(CFileChannel*pChannel);
	void AddFileSessionServerTCP(CFileSessionServerTcp*pSessionServerTCP);
	void RemoveFileSessionServerTCP(CFileSessionServerTcp*pSessionServerTCP);
	//void AddAVMTFileSessionServerUDP(AVMTFileSessionServerUDP*pAVMTFileSessionServerUDP);
	//void RemoveAVMTFileSessionServerUDP(AVMTFileSessionServerUDP*pAVMTFileSessionServerUDP);
	//void AddAVMTFileSessionClientUDP(AVMTFileSessionClientUDP*pAVMTFileSessionClientUDP);
	//void RemoveAVMTFileSessionClientUDP(AVMTFileSessionClientUDP*pAVMTFileSessionClientUDP);
	void DoCheck(void);

	//void OnAVMTManagerUDPReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);

	void ClearFileSession(unsigned long ulChannelID);
	CFileSessionClientTcp* CreateFileSessionClientTCP(ILocalFileNotify&rNotify,unsigned long ulChannelID);
	//AVMTFileSessionClientUDP*CreateAVMTFileSessionClientUDP(ILocalFileNotify&rNotify,unsigned long ulChannelID);
	
	//bool DoSendData(void);

	//////////////////////////////////////////////////////////////////////////
	virtual void OnIFileSessionClientNotifyConnected(); //
	virtual void OnReceivedFrame(const char*pFrameData,int nLen);

	void AddFileSessionClientTCP(CFileSessionClientTcp*pSessionClientTCP);
	void RemoveFileSessionClientTCP(CFileSessionClientTcp*pSessionClientTCP);

	CFileChannel* GetChannelOfConference(unsigned long ulConferenceID, const char* cFileName);
	CFileChannel* GetChannel(unsigned long ulChannelID = 0);
	CFileChannel* NewChannel(unsigned long ulChannelID = 0);
	CFileChannel* GetFreeChannel(unsigned long ulConferenceID, const char* cFileName, bool& bMatch);
	void FreeChannel(unsigned long ulChannelID);
	void FreeChannelOfSession(unsigned long ulSessionID, const char* cFileName = "");
	void GetListChannelID(/*std::list<unsigned long>*/ListPtr& listChannelID);
	//////////////////////////////////////////////////////////////////////////

	AVCritSec* GetAVCritSecMapFileChannel() { return &m_AVCritSecMapFileChannel; }
	MapFileChannel* GetMapFileChannel() { return &m_MapFileChannel; };
	void DelFileOfConference(UINT32 iConferenceID);

	void onFileEnd(const char* cFileName) {}
	void onFileProcess(double iProcess) {}

	void DeleteChannel(UINT32 ulChannelID);

	bool FindClientTcpSessionID(UINT32 ulSessionID);

protected:
	void CheckFileChannel(void); //
	void ClearFileChannel(void);
	void CheckFileSessionServerTCP(void);
	void ClearFileSessionServerTCP(void);
	//void CheckAVMTFileSessionServerUDP(void);
	//void ClearAVMTFileSessionServerUDP(void);
	////void CheckAVMTFileSessionClientUDP(void);
	////void ClearAVMTFileSessionClientUDP(void);

	//////////////////////////////////////////////////////////////////////////
	void CheckFileSessionClientTCP(void);
	void ClearFileSessionClientTCP(void);
	//////////////////////////////////////////////////////////////////////////

protected:
	MapFileChannel				m_MapFileChannel;
	AVCritSec					m_AVCritSecMapFileChannel;
	MapFileSessionServerTCP		m_MapFileSessionServerTCP;
	AVCritSec					m_AVCritSecMapFileSessionServerTCP;
	//MapAVMTFileSessionServerUDP	m_MapAVMTFileSessionServerUDP;
	//AVCritSec					m_AVCritSecMapAVMTFileSessionServerUDP;
	//MapAVMTFileSessionClientUDP	m_MapAVMTFileSessionClientUDP;
	//AVCritSec					m_AVCritSecMapAVMTFileSessionClientUDP;

	//////////////////////////////////////////////////////////////////////////
	MapFileSessionClientTCP		m_MapFileSessionClientTCP;
	AVCritSec					m_AVCritSecMapFileSessionClientTCP;
	unsigned short				m_usFreeChannelCount;
	//////////////////////////////////////////////////////////////////////////

};

#endif
