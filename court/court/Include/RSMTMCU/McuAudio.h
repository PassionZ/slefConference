#ifndef MCUAUDIO_H_
#define MCUAUDIO_H_

#include "AudioChannel.h"
#include "AudioSessionServerUdp.h"
#include "AudioSessionClientUdp.h"
#include "AudioSessionSendUdp.h"
#include "AudioSessionReceiverUdp.h"
#include <list>
#include "../libHPBaseclass/ListPtr.h"

#ifdef YOUHUA
#define FREEAUDIOCHANNELSIZE 5
#else
#define FREEAUDIOCHANNELSIZE 10
#endif

typedef std::map<unsigned long,CAudioChannel*>					MapAudioChannel;

typedef std::map<unsigned long,CAudioSessionServerUdp*>			MapAudioSessionServerUdp;
typedef std::map<unsigned long,CAudioSessionClientUdp*>			MapAudioSessionClientUdp;
//////////////////////////////////////////////////////////////////////////
typedef std::map<unsigned long,CAudioSessionSendUdp*>			MapAudioSessionSendUdp;
typedef std::map<unsigned long,CAudioSessionReceiverUdp*>		MapAudioSessionReceiverUdp;
//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CMcuAudio
{
public:
	CMcuAudio(void);
	virtual ~CMcuAudio(void);

public:
	static CMcuAudio* Instance(void);

public:
	void ReleaseConnections(void);
	void OnAVMTManagerUDPReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);

	//void AddAudioChannel(CAudioChannel*pChannel);
	//void RemoveAudioChannel(CAudioChannel*pChannel);

	void AddAudioSessionServerUdp(CAudioSessionServerUdp*pSessionServerUdp);
	void RemoveAudioSessionServerUdp(CAudioSessionServerUdp*pSessionServerUdp);
	void AddAudioSessionClientUdp(CAudioSessionClientUdp*pSessionClientUdp);
	void RemoveAudioSessionClientUdp(CAudioSessionClientUdp*pSessionClientUdp);
	//////////////////////////////////////////////////////////////////////////
	void AddAudioSessionSendUdp(CAudioSessionSendUdp*pSessionSendUdp);
	void RemoveAudioSessionSendUdp(CAudioSessionSendUdp*pSessionSendUdp);
	void AddAudioSessionReceiverUdp(CAudioSessionReceiverUdp*pSessionReceiverUdp);
	void RemoveAudioSessionReceiverUdp(CAudioSessionReceiverUdp*pSessionReceiverUdp);
	//////////////////////////////////////////////////////////////////////////

	void DoCheck(void);

	//void ClearAudioSession(unsigned long ulChannelID);
	CAudioSessionClientUdp* CreateAudioSessionClientUdp(/*IAudioSessionClientNotify&rNotify,*/unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort, UINT32 iMcuID);
	//////////////////////////////////////////////////////////////////////////
	CAudioSessionSendUdp* CreateAudioSessionSendUdp(/*IAudioSessionClientNotify&rNotify,*/unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);
	CAudioSessionReceiverUdp* CreateAudioSessionReceiverUdp(/*IAudioSessionClientNotify&rNotify,*/unsigned long ulChannelID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);
	//////////////////////////////////////////////////////////////////////////
	
	//bool DoSendData(void); //

	CAudioChannel* GetChannel(unsigned long ulChannelID);
	CAudioChannel* GetChannelOfSession(unsigned long ulSessionID, unsigned short usCardNo);
	CAudioChannel* NewChannel(unsigned long ulChannelID = 0);
	CAudioChannel* GetFreeChannel(unsigned long ulSessionID, unsigned short usCardNo, bool& bMatch);
	void FreeChannel(unsigned long ulChannelID);
	void FreeChannelOfSession(unsigned long ulSessionID);
	void FreeChannelOfSession(unsigned long ulSessionID, unsigned short usCardNo);

	void GetListChannelID(/*std::list<unsigned long>*/ListPtr& listChannelID);

	void SetTos(unsigned char ucTos);

	void ReleaseServerUdp(UINT32 iMcuID);

	void DeleteChannel(UINT32 ulChannelID);

	bool FindClientUdpSessionID(UINT32 ulSessionID);

protected:
	//void CheckAudioChannel(void); //
	void ClearAudioChannel(void);

	void CheckAudioSessionServerUdp(void);
	//void ClearAudioSessionServerUdp(void);
	void CheckAudioSessionClientUdp(void);
	//void ClearAudioSessionClientUdp(void);
	//////////////////////////////////////////////////////////////////////////
	void CheckAudioSessionSendUdp(void);
	void ClearAudioSessionSendUdp(void);
	void CheckAudioSessionReceiverUdp(void);
	void ClearAudioSessionReceiverUdp(void);
	//////////////////////////////////////////////////////////////////////////

protected:
	MapAudioChannel				m_MapAudioChannel;
	AVCritSec					m_AVCritSecMapAudioChannel;

	MapAudioSessionServerUdp	m_MapAudioSessionServerUdp;
	AVCritSec					m_AVCritSecMapAudioSessionServerUdp;
	MapAudioSessionClientUdp	m_MapAudioSessionClientUdp;
	AVCritSec					m_AVCritSecMapAudioSessionClientUdp;
	//////////////////////////////////////////////////////////////////////////
	MapAudioSessionSendUdp		m_MapAudioSessionSendUdp;
	AVCritSec					m_AVCritSecMapAudioSessionSendUdp;
	MapAudioSessionReceiverUdp	m_MapAudioSessionReceiverUdp;
	AVCritSec					m_AVCritSecMapAudioSessionReceiverUdp;
	//////////////////////////////////////////////////////////////////////////

	unsigned short				m_usFreeChannelCount;
};

#endif
