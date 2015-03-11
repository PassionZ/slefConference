#ifndef __IAVMTMCUCLIENT_H__
#define __IAVMTMCUCLIENT_H__

#include <string>

#define MAX_AUDIOUDPPACKET_LEN 1666
#define MAX_VIDEOUDPPACKET_LEN 65536

//#define MAINTAINUDPPACKET 1

// video tcp&udp
class IAVVideoReceiverNotify
{
public:
	IAVVideoReceiverNotify(void){};
	virtual~IAVVideoReceiverNotify(void){};
public:
	virtual void OnIAVVideoReceiverNotifyReceivedVideoFrame(const char*pData,int nLen)=0;
	virtual void OnIAVVideoReceiverNotifyConnected(/*unsigned long ulIP*/)=0;
};

class IAVVideoReceiver
{
public:
	IAVVideoReceiver(void){};
	virtual ~IAVVideoReceiver(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual void EnableReceive(bool bEnable)=0;
	virtual bool IsEnableReceive(void)=0;
	virtual bool IsDisconnected(void)=0;

	//virtual void GetWndFrame(byte iWnd, byte iFrame) = 0;
	//virtual bool IsWndFrame(byte iWnd, byte iFrame) = 0;

	virtual unsigned long GetChannelID()=0;
	virtual void SetSessionCard(unsigned long ulSessionID, unsigned char iCardNo)=0;
	virtual bool IsSessionCard(unsigned long ulSessionID, unsigned char iCardNo)=0;

	virtual bool IsMatch(unsigned long ulChannelID)=0;
	
	//发送屏幕控制数据
	virtual int SendFrame(const char*pData,int nLen) = 0;
};

AFX_EXT_CLASS IAVVideoReceiver*CreateIAVVideoReceiverTCP(IAVVideoReceiverNotify&rIAVVideoReceiverNotify,unsigned long ulVideoChannelID/*,unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

AFX_EXT_CLASS IAVVideoReceiver*CreateIAVVideoReceiverUDP(IAVVideoReceiverNotify&rIAVVideoReceiverNotify,unsigned long ulVideoChannelID/*,unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

class IAVVideoSenderNotify
{
public:
	IAVVideoSenderNotify(void){};
	virtual~IAVVideoSenderNotify(void){};
public:
	virtual void OnIAVVideoSenderNotifyConnected(/*unsigned long ulIP*/)=0;
	virtual void OnIAVVideoSenderNotifyRequestKeyFrame(void)=0;
	virtual void OnIAVVideoSenderNotifyClose(unsigned long iChannelID)=0;

	//收到屏幕控制数据
	virtual void OnReceivedFrame(const char*pFrameData,int nLen) = 0;
};

class IAVVideoSender
{
public:
	IAVVideoSender(void){};
	virtual ~IAVVideoSender(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual void EnableSend(bool bEnable)=0;
	virtual bool IsEnableSend(void)=0;
	virtual void OnReceivedEnable(void)=0;
	virtual void OnReceivedDisable(void)=0;
	virtual bool IsDisconnected(void)=0;
	virtual unsigned long GetSentLostPackets(void)=0;

	virtual void SendVideoFrame(const char*pData,int nLen)=0;
	//virtual void GetWndFrame(byte iWnd, byte iFrame) = 0;
	//virtual bool IsWndFrame(byte iWnd, byte iFrame) = 0;

	virtual bool IsMatch(unsigned long ulChannelID)=0;
	virtual bool IsReceived()=0;
};

AFX_EXT_CLASS IAVVideoSender*CreateIAVVideoSenderTCP(IAVVideoSenderNotify&rIAVVideoSenderNotify,unsigned long ulVideoChannelID/*,unsigned long ulMCUIP0,unsigned short usMCUPort*/,unsigned long ulUserSessionID,unsigned short usCardNo);

AFX_EXT_CLASS IAVVideoSender*CreateIAVVideoSenderUDP(IAVVideoSenderNotify&rIAVVideoSenderNotify,unsigned long ulVideoChannelID/*,unsigned long ulMCUIP0,unsigned short usMCUPort*/,unsigned long ulUserSessionID,unsigned short usCardNo);

// audio udp
class IAVAudioReceiverNotify
{ 
public:
	IAVAudioReceiverNotify(void){};
	virtual~IAVAudioReceiverNotify(void){};
public:
	virtual void OnIAVAudioReceiverNotifyReceivedAudioFrame(const char*pData,int nLen)=0;
	virtual void OnIAVAudioReceiverNotifyConnected(/*unsigned long ulIP*/)=0;
};

class IAVAudioReceiver
{
public:
	IAVAudioReceiver(void){};
	virtual ~IAVAudioReceiver(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual void EnableReceive(bool bEnable)=0;
	virtual bool IsEnableReceive(void)=0;
	virtual bool IsDisconnected(void)=0;

	virtual bool IsMatch(unsigned long ulChannelID)=0;
	virtual bool IsSession(unsigned long ulSessionID)=0;
	virtual void SetSessionCard(unsigned long ulSessionID)=0;
};

AFX_EXT_CLASS IAVAudioReceiver*CreateIAVAudioReceiverUDP(IAVAudioReceiverNotify&rIAVAudioReceiverNotify,unsigned long ulAudioChannelID/*,unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);


class IAVAudioSenderNotify
{
public:
	IAVAudioSenderNotify(void){};
	virtual~IAVAudioSenderNotify(void){};
public:
	virtual void OnIAVAudioSenderNotifyConnected(/*unsigned long ulIP*/)=0;
	virtual void OnIAVAudioSenderNotifyClose(unsigned long iChannelID)=0;
};

class IAVAudioSender
{
public:
	IAVAudioSender(void){};
	virtual ~IAVAudioSender(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual void EnableSend(bool bEnable)=0;
	virtual bool IsEnableSend(void)=0;
	virtual bool IsDisconnected(void)=0;
	virtual unsigned long GetSentLostPackets(void)=0;
	//virtual unsigned long GetTotalPackets(void)=0;

	virtual void SendAudioFrame(const char*pData,int nLen)=0;
	virtual bool IsMatch(unsigned long ulChannelID)=0;
	virtual bool IsReceived()=0;
};
AFX_EXT_CLASS IAVAudioSender*CreateIAVAudioSenderUDP(IAVAudioSenderNotify&rIAVAudioSenderNotify,unsigned long ulAudioChannelID/*,unsigned long ulMCUIP0,unsigned short usMCUPort*/,unsigned long ulUserSessionID,unsigned short usCardNo);


//////////////////////////////////////////////////////////////////////////
class IVideoSessionClientNotify
{
public:
	IVideoSessionClientNotify(void){};
	virtual~IVideoSessionClientNotify(void){};
public:
	virtual void OnIVideoSessionClientNotifyConnected()=0;
};

class IVideoSessionClient
{
public:
	IVideoSessionClient(void){};
	virtual~IVideoSessionClient(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual bool IsDisconnected(void)=0;
};

AFX_EXT_CLASS IVideoSessionClient* CreateIVideoSessionClientTCP(IVideoSessionClientNotify&rNotify,unsigned long ulChannelID, const std::string & ulPeerMCUIP0,unsigned short usPeerMCUPort);

//////////////////////////////////////////////////////////////////////////

class IWbSessionClientNotify
{
public:
	IWbSessionClientNotify(void){};
	virtual~IWbSessionClientNotify(void){};
public:
	virtual void OnIWbSessionClientNotifyConnected()=0;
	virtual void OnReceivedFrame(const char*pFrameData,int nLen) = 0;
};

class IWbSessionClient
{
public:
	IWbSessionClient(void){};
	virtual~IWbSessionClient(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual bool IsDisconnected(void)=0;
	virtual void SendFrame(const char*pData,int nLen)=0;
};

AFX_EXT_CLASS IWbSessionClient* CreateIWbChannelClientTCP(IWbSessionClientNotify&rNotify,unsigned long ulChannelID/*, unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

//AFX_EXT_CLASS IWbSessionClient* CreateIWbSessionEndPointTCP(IWbSessionClientNotify&rNotify,unsigned long ulChannelID/*, unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

AFX_EXT_CLASS IWbSessionClient* CreateIWbSessionClientTCP(IWbSessionClientNotify&rNotify,unsigned long ulChannelID/*, unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

//////////////////////////////////////////////////////////////////////////

class IAVDesktopReceiverNotify
{
public:
	IAVDesktopReceiverNotify(void){};
	virtual~IAVDesktopReceiverNotify(void){};
public:
	virtual void OnIAVDesktopReceiverNotifyReceivedDesktopFrame(const char*pData,int nLen)=0;
	virtual void OnIAVDesktopReceiverNotifyConnected(/*unsigned long ulIP*/)=0;
};

class IAVDesktopReceiver
{
public:
	IAVDesktopReceiver(void){};
	virtual ~IAVDesktopReceiver(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual void EnableReceive(bool bEnable)=0;
	virtual bool IsEnableReceive(void)=0;
	virtual bool IsDisconnected(void)=0;

	//virtual void GetWndFrame(byte iWnd, byte iFrame) = 0;
	//virtual bool IsWndFrame(byte iWnd, byte iFrame) = 0;

	virtual unsigned long GetChannelID()=0;
	//virtual void SetSessionCard(unsigned long ulSessionID, unsigned char iCardNo)=0;
	//virtual bool IsSessionCard(unsigned long ulSessionID, unsigned char iCardNo)=0;

	virtual bool IsMatch(unsigned long ulChannelID)=0;

	virtual int SendFrame(const char*pData,int nLen) = 0;
};

AFX_EXT_CLASS IAVDesktopReceiver*CreateIAVDesktopReceiverTCP(IAVDesktopReceiverNotify&rIAVDesktopReceiverNotify,unsigned long ulDesktopChannelID/*,unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);


class IAVDesktopSenderNotify
{
public:
	IAVDesktopSenderNotify(void){};
	virtual~IAVDesktopSenderNotify(void){};
public:
	virtual void OnIAVDesktopSenderNotifyConnected(/*unsigned long ulIP*/)=0;
	//virtual void OnIAVDesktopSenderNotifyRequestKeyFrame(void)=0;
	virtual void OnReceivedFrame(const char*pFrameData,int nLen) = 0;

};

class IAVDesktopSender
{
public:
	IAVDesktopSender(void){};
	virtual ~IAVDesktopSender(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual void EnableSend(bool bEnable)=0;
	virtual bool IsEnableSend(void)=0;
	virtual void OnReceivedEnable(void)=0;
	virtual void OnReceivedDisable(void)=0;
	virtual bool IsDisconnected(void)=0;
	virtual unsigned long GetSentLostPackets(void)=0;

	virtual void SendDesktopFrame(const char*pData,int nLen)=0;
	//virtual void GetWndFrame(byte iWnd, byte iFrame) = 0;
	//virtual bool IsWndFrame(byte iWnd, byte iFrame) = 0;

	virtual bool IsMatch(unsigned long ulChannelID)=0;
};

AFX_EXT_CLASS IAVDesktopSender*CreateIAVDesktopSenderTCP(IAVDesktopSenderNotify&rIAVDesktopSenderNotify,unsigned long ulDesktopChannelID/*,unsigned long ulMCUIP0,unsigned short usMCUPort*/);

class IDesktopSessionClientNotify
{
public:
	IDesktopSessionClientNotify(void){};
	virtual~IDesktopSessionClientNotify(void){};
public:
	virtual void OnIDesktopSessionClientNotifyConnected()=0;
};

class IDesktopSessionClient
{
public:
	IDesktopSessionClient(void){};
	virtual~IDesktopSessionClient(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual bool IsDisconnected(void)=0;
};

AFX_EXT_CLASS IDesktopSessionClient* CreateIDesktopSessionClientTCP(IDesktopSessionClientNotify&rNotify,unsigned long ulChannelID/*, unsigned long ulPeerMCUIP0,unsigned short usPeerMCUPort*/);

//////////////////////////////////////////////////////////////////////////
class ILocalFileNotify
{
public:
	ILocalFileNotify(void){};
	virtual~ILocalFileNotify(void){};
	//virtual void onFileDataOut(char* pData,long nLen)=0;
	virtual void OnIFileSessionClientNotifyConnected()=0;

	virtual void onFileEnd(const char* cFileName)=0;
	virtual void onFileProcess(double iProcess)=0;
};

class ILocalFile
{ 
public:
	ILocalFile(void){};
	virtual~ILocalFile(void){};
	virtual void SetSendFilePath(std::string sFilePath)=0;//测试使用
	//virtual void processFileData(char * pData,long nLen)=0;

	virtual void ReleaseConnections(void)=0;
	virtual bool IsDisconnected(void)=0;
};

ILocalFile * CreateLocalFile(ILocalFileNotify& pNotify);

AFX_EXT_CLASS ILocalFile* CreateIFileChannelClientTCP(ILocalFileNotify&rNotify,unsigned long ulChannelID);

//////////////////////////////////////////////////////////////////////////

enum {
	AVMT_VIDEO_NULL=0,
	AVMT_VIDEO_DIRECTION,
	AVMT_VIDEO_ENABLE,
	AVMT_VIDEO_DISABLE,
	AVMT_VIDEO_KEYFRAME,
	AVMT_VIDEO_REVERSEDIRECTION,
	AVMT_VIDEO_USERSESSIONID
};

enum {
	AVMT_DESKTOP_NULL=0,
	AVMT_DESKTOP_DIRECTION,
	AVMT_DESKTOP_ENABLE,
	AVMT_DESKTOP_DISABLE,
	//AVMT_DESKTOP_KEYFRAME
	AVMT_DESKTOP_REVERSEDIRECTION,
};

enum {
	// upload channel(mcu)
	AVMT_FILE_NULL=0,
	AVMT_FILE_DIRECTION,
	//AVMT_FILE_ENABLE,
	//AVMT_FILE_DISABLE,
	//AVMT_FILE_KEYFRAME,		
	AVMT_FILE_UPLOAD_PIECE,			// pdu:file piece start position
	//AVMT_FILE_UPLOAD_EXCEPTION,
	AVMT_FILE_UPLOAD_OVER,			// pdu:filelength
	//AVMT_FILE_UPLOAD_OVER_ACK,		

	// client interface
	AVMT_FILE_LIST_REQ,
	AVMT_FILE_LIST_ACK,				// pdu:filename list
	AVMT_FILE_DEL,					// pdu:filename

	AVMT_FILE_UPLOAD_REQ,			// pdu:filename,filelength
	AVMT_FILE_UPLOAD_ACK,			// pdu:if same filename exist,then return false,or true(and return channelid)
	AVMT_FILE_UPLOAD_CANCEL,		// pdu:channelid

	AVMT_FILE_DOWNLOAD_REQ,			// pdu:filename
	AVMT_FILE_DOWNLOAD_ACK,			// pdu:filename,filelength

	// download channel(client)
	AVMT_FILE_DOWNLOAD_PIECE_REQ,	// pdu:filename,file piece start position
	AVMT_FILE_DOWNLOAD_PIECE_ACK,	// pdu:filename,file piece start position
	AVMT_FILE_DOWNLOAD_EXCEPTION	// pdu:filename
};

enum{
	AVMT_UDP_P2P=0,
	AVMT_UDP_P2P_ACK,
	AVMT_UDP_AUDIO,
	AVMT_UDP_VIDEO,
	AVMT_UDP_FILE,
	AVMT_UDP_DESKTOP,
	AVMT_UDP_WB
};

enum{
	AVMT_UDP_AUDIO_SESSION_CONNECT=0,
	AVMT_UDP_AUDIO_SESSION_CONNECT_ACK,									//1
	AVMT_UDP_AUDIO_SESSION_DISCONNECT,									//2
	AVMT_UDP_AUDIO_SESSION_ENABLE,										//3
	AVMT_UDP_AUDIO_SESSION_ENABLE_ACK,									//4
	AVMT_UDP_AUDIO_SESSION_DISABLE,										//5
	AVMT_UDP_AUDIO_SESSION_DISABLE_ACK,									//6
	AVMT_UDP_AUDIO_SESSION_FRAME,										//7
	AVMT_UDP_AUDIO_SESSION_DIRECTION,									//8
	AVMT_UDP_AUDIO_SESSION_NULL,				// mcu之间				//9
	AVMT_UDP_AUDIO_SESSION_DIRECTION_ACK,								//10
	AVMT_UDP_AUDIO_SESSION_REVERSEDIRECTION,							//11
	AVMT_UDP_AUDIO_SESSION_REVERSEDIRECTION_ACK,						//12
};

enum{
	AVMT_UDP_VIDEO_SESSION_CONNECT=0,
	AVMT_UDP_VIDEO_SESSION_CONNECT_ACK,
	AVMT_UDP_VIDEO_SESSION_DISCONNECT,
	AVMT_UDP_VIDEO_SESSION_ENABLE,
	AVMT_UDP_VIDEO_SESSION_ENABLE_ACK,
	AVMT_UDP_VIDEO_SESSION_DISABLE,
	AVMT_UDP_VIDEO_SESSION_DISABLE_ACK,
	AVMT_UDP_VIDEO_SESSION_FRAME,
	AVMT_UDP_VIDEO_SESSION_FRAME_ACK,
	AVMT_UDP_VIDEO_SESSION_DIRECTION,
	AVMT_UDP_VIDEO_SESSION_NULL,				// mcu之间
	AVMT_UDP_VIDEO_SESSION_DIRECTION_ACK,
	AVMT_UDP_VIDEO_SESSION_REVERSEDIRECTION,
	AVMT_UDP_VIDEO_SESSION_REVERSEDIRECTION_ACK,
};

#endif

