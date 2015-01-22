#ifndef _IAVFPLAYER_H
#define _IAVFPLAYER_H

#define		PLAY_EVENT_MESSAGE			WM_USER+100	//WPARAM=PLAY_EVENT_XXXX, LPARAM=parameter
enum {
	PLAY_EVENT_TIMESTAMP=1,
	PLAY_EVENT_OVER,
	PLAY_EVENT_START_BUFFER,
	PLAY_EVENT_STOP_BUFFER,
	PLAY_EVENT_START_SEEK,
	PLAY_EVENT_STOP_SEEK,
	PLAY_EVENT_PAUSE,
	PLAY_EVENT_TIMEOSD,
	PLAY_EVENT_MUTE,
	PLAY_EVENT_VOLUME,
	PLAY_EVENT_MODECHANGED,
	PLAY_EVENT_SELECTED,
	PLAY_EVENT_MENU,		//菜单
	PLAY_EVENT_FULLSCREEN, //TRUE 全屏模式， FALSE 退出全屏模式 //PLAY_EVENT_RESTORE,
	PLAY_EVENT_DOUBLESIZE,
	PLAY_EVENT_STREAM,
	PLAY_EVENT_VIDEO_CHANGED,
	PLAY_EVENT_NEWSTREAM
};

//播放模式
enum {
	PLAY_MODE_NORMAL=0,		//正常播放
	PLAY_MODE_FRAME,		//单帧进
	PLAY_MODE_X,			//慢进	（1/2X）
	PLAY_MODE_2X,			//快进	（2X）
	PLAY_MODE_4X,			//快进	（4X）
	PLAY_MODE_8X,			//快进	（8X）
	PLAY_MODE_16X,			//快进	（16X）
	PLAY_MODE_NULL=15,		//进退间隔
	PLAY_MODE_FRAME_REVERSE,//单帧退
	PLAY_MODE_X_REVERSE,	//慢退	（1/2X）
	PLAY_MODE_2X_REVERSE,	//快退	（2X）
	PLAY_MODE_4X_REVERSE,	//快退	（4X）
	PLAY_MODE_8X_REVERSE,	//快退	（8X）
	PLAY_MODE_16X_REVERSE	//快退	（16X）
};
enum {
	PLAY_STYLE_FILE_INFO=1,
	PLAY_STYLE_FILE_LIST=2,
	PLAY_STYLE_OSD_TIME=4,
	PLAY_STYLE_OSD_CHANNEL=8,
	PLAY_STYLE_OSD_STATUS=0x0010,
	PLAY_STYLE_MENU=0x0020,//禁用内置右键菜单,发送WM_NOTIFY::NM_RCLICK通知
	PLAY_SYTLE_FIXEDRATIO=0x00C0,
	PLAY_SYTLE_FULLSCREEN=0x0100
};
enum {
	PLAY_ERR_SUCCESS=0//
};

enum 
{
	TM_1X1	= 0x0001,
	TM_2X2	= 0x0004,
	TM_3X3	= 0x0009,
	TM_4X4	= 0x0010,
	TM_5X5	= 0x0019,
	TM_6X6	= 0x0024,
	TM_7X7	= 0x0031,
	TM_8X8	= 0x0040,
	TM_9X9	= 0x0051,
	TM_RL5	= 0x0005,
	TM_RL6	= 0x0006,
	TM_RL8	= 0x0008,
	TM_RL10	= 0x000A,
	TM_RL12	= 12,
	TM_RL14 = 14,
	TM_RL18 = 18,
	TM_ALL  = 0xFFFF
};
class IDVRPlayer
{
public:
	virtual bool Connect(HWND hNotifyWnd, HWND hParentWnd)=0;
	virtual void ReleaseConnections(void)=0;

	virtual int OpenAVFPlayFile(const char * cszFile, bool bAdd=false, int nCh=0)=0;
	virtual void CloseAVFPlayFile(int nCh=0)=0;	 

	virtual unsigned long GetDuration()=0;
	virtual unsigned long GetPos()=0;
	virtual void Seek(unsigned long ulSeekTime)=0;

	virtual void Pause(bool bPause)=0;
	virtual bool IsPaused(void)=0;
	virtual bool IsOpen()=0;
	virtual bool IsStop()=0;

	virtual unsigned short GetWidth(void)=0;
	virtual unsigned short GetHeight(void)=0;
	virtual void SetFullScreen(bool bFullScreen, int nCh=0)=0;
	virtual bool IsFullScreen(void)=0;

	virtual void SetMute(bool bMute)=0;
	virtual bool IsMute(void)=0;
	virtual void SetVolume(int nAudioVolume)=0;

	virtual void SetPlayMode(int nMode)=0;
	virtual int GetPlayMode()=0;
	virtual int  Info(void *buffer, unsigned int dwFlag, int nCh=0)=0;

	virtual bool SetStyle(unsigned __int64 dwStyle)=0;
	virtual unsigned __int64 GetStyle()=0;
	virtual HWND GetHwnd()=0;

	virtual void SetTM(int nSize, DWORD dwType=0)=0;					//nSize=-1时不改变当前模板，自动扩张模板
	//SetTmAllocator

	// 20071025
	virtual void InputPacket(unsigned char* data, int length, int nCh=0)=0;
	virtual bool CaptureToFile(const char *fullpath, int nCh=0)=0;

	// 20080110
	//virtual bool RegisterNotifyMessage(DWORD dwMsg);
	virtual void SetSkipVideo(unsigned long ulMS)=0;
	virtual unsigned long GetSkipVideo()=0;
};
class AVSingleStreamPlayer
{
public:
	virtual bool Connect(HWND hNotifyWnd, HWND hParentWnd)=0;
	virtual void ReleaseConnections(void)=0;

	/*************************************
	bAdd
	   false	关闭
	   true		不关闭之前打开的文件
    nPlayId		使用指定播放器
		0		自动寻找
		>0		指定播放器,值为[1-nSize]
	返回值
		0		打开文件失败
		>0		当前文件使用的播放器
	*************************************/
	virtual int OpenAVFPlayFile(const char * cszFile, bool bAdd=false)=0;

	/*************************************
	nPlayId
		0		关闭所有播放器
		>0		关闭指定播放器
	*************************************/
	virtual void CloseAVFPlayFile()=0;	 
	virtual void SetTM(int nSize, DWORD dwType=0)=0;					//dwTM=-1时不改变当前模板，自动扩张模板

	virtual unsigned long GetDuration()=0;
	virtual unsigned long GetPos()=0;
	virtual void Seek(unsigned long ulSeekTime)=0;

	virtual void Pause(bool bPause)=0;
	virtual bool IsPaused(void)=0;
	virtual bool IsOpen()=0;
	virtual bool IsStop()=0;

	virtual unsigned short GetWidth(void)=0;
	virtual unsigned short GetHeight(void)=0;
	virtual void SetFullScreen(bool bFullScreen)=0;
	virtual bool IsFullScreen(void)=0;

	virtual void SetMute(bool bMute)=0;
	virtual bool IsMute(void)=0;
	virtual void SetVolume(int nAudioVolume)=0;
	virtual void SetPlayMode(int nMode)=0;
	virtual int GetPlayMode()=0;
	virtual int  Info(void *buffer, unsigned int dwFlag)=0;

	virtual bool SetStyle(unsigned __int64 dwStyle)=0;
	virtual unsigned __int64 GetStyle()=0;
	virtual HWND GetHwnd()=0;

	// 20071025
	virtual void InputPacket(unsigned char* data, int length)=0;
	virtual bool CaptureToFile(const char *fullpath)=0;

	// 20080110
	//virtual bool RegisterNotifyMessage(DWORD dwMsg);
	virtual void SetSkipVideo(unsigned long ulMS)=0;
	virtual unsigned long GetSkipVideo()=0;
	// Add 20080626
	virtual void RegisterCallbackMsg(unsigned long uMsg)=0;
	virtual bool IsSupportMode(int nMode)=0;
	// + [9/10/2008] Jee	
	virtual void SetVideoParam(int nBrightness=128/*亮度值0-255*/, int nContrast=64/*对比度0-127*/, int nSaturation=64/*饱和度0-127*/, int nHue=0/*色调0-255*/,int nGamma=100/*伽马1-400*/,int nSharpen=0/*锐化0-127*/)=0;
	//
};

// 音量控制回调接口
class IMixerVolumeCallback
{
public: // 回调
	virtual HWND GetHwnd(void) = 0;
	// Volume改变时通知
	virtual void OnMixerNotify_VolumeValueChanged(DWORD dwVal) = 0;
	// Mute改变时通知
	virtual void OnMixerNotify_VolumeMuteChanged(BOOL bVal) = 0;
	// Mic select改变时通知
	virtual void OnMixerNotify_MicValueChanged(DWORD bVal) = 0;
	// Mic Mute改变时通知
	virtual void OnMixerNotify_MicMuteChanged(BOOL bVal) = 0;
};

// 音量控制器接口
class IMixerVolume
{
public:
	// 初始化
	virtual BOOL InitConnection(void)=0;
	// 释放
	virtual void ReleaseConnections(void)=0;

	// Volume control
	virtual BOOL GetMute()=0;
	virtual void SetMute(BOOL bVal)=0;
	virtual DWORD GetVolume()=0;
	virtual void SetVolume(DWORD dwVal)=0;

	// Mic control
	virtual BOOL GetMicMute(void)=0;
	virtual void SetMicMute(BOOL bVal)=0;
	virtual DWORD GetMicValue()=0;
	virtual void SetMicValue(DWORD lVal)=0;
};
#ifdef __cplusplus
extern "C" 
{ 
#endif
	void AVFPlayerInit();
	IMixerVolume* CreateIMixerVolume(IMixerVolumeCallback* pDVDVolumeCallback);
	AVSingleStreamPlayer* CreateAVFPlayer(HWND hNotifyWnd, HWND hParentWnd);
	IDVRPlayer* CreateDVRPlayer(HWND hNotifyWnd, HWND hParentWnd);
	LPCTSTR GetSaveFileNameEx(LPTSTR pszFile, int nBufSize, LPCTSTR pszFilter, LPCTSTR pszDefaultExt, DWORD dwFlag=OFN_NOREADONLYRETURN | OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT);	
	void AVFPlayerUninit();
#ifdef __cplusplus
}
#endif
#endif