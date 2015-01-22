//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IOVideoDis.h: interface for the IOVideoDis class.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __IOVIDEODIS_H__
#define __IOVIDEODIS_H__

#include "VideoHeader.h"

#ifndef	VIDEO_FRAME_TYPE_DEFINE
#define	VIDEO_FRAME_TYPE_DEFINE
typedef enum VIDEO_FRAME_TYPE{
	VT_RGB24=0,	//
	VT_RGB16,		//
	VT_YV12,		//
	VT_YUYV,
}VIDEO_FRAME_TYPE;
#endif

typedef struct VIDEO_DIS_SIZE
{
	int width;
	int height;

}VIDEO_DIS_SIZE;

typedef enum VIDEO_DIS_TYPE{
	VIDEO_DIS_TYPE_ANY=-1,
	VIDEO_DIS_TYPE_YV12=0,
	VIDEO_DIS_TYPE_YUYV,
	VIDEO_DIS_TYPE_RGB16,
	VIDEO_DIS_TYPE_RGB24,
	VIDEO_DIS_TYPE_H263RAW,
	VIDEO_DIS_TYPE_H264RAW,
	VIDEO_DIS_TYPE_H264RTP,
}VIDEO_DIS_TYPE;

#ifndef	AUDIO_DIS_TYPE_DEFINE
#define	AUDIO_DIS_TYPE_DEFINE

typedef enum AUDIO_DIS_TYPE{
	AUDIO_DIS_TYPE_ANY=-1,
	AUDIO_DIS_TYPE_WAVE=0,
	AUDIO_DIS_TYPE_G711,
	AUDIO_DIS_TYPE_G722,
	AUDIO_DIS_TYPE_G729,
	AUDIO_DIS_TYPE_MP3,
	AUDIO_DIS_TYPE_AAC,
}AUDIO_DIS_TYPE;
#endif	//#ifndef	AUDIO_DIS_TYPE_DEFINE

class AFX_EXT_CLASS IOVideoDisNotify
{
public:
	IOVideoDisNotify(void){};
	virtual~IOVideoDisNotify(void){};
public:
	//输出音频数据包的回调
	virtual void OnIOAudioDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)=0;	//pass
	//输出视频数据包的回调
	virtual void OnIOVideoDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;	//pass
	virtual void OnIOVideoDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;		//current not used
	//输出视频子流数据包的回调
	virtual void OnIOVideoSubDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;			//current not used
	virtual void OnIOVideoSubDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;	//current not used
};

class VideoWndDis
{
public:
	VideoWndDis(void){};
	virtual~VideoWndDis(void){};
public:
	//得到视频窗口的宽度
	virtual int GetWidth(void)=0;	//pass
	//得到视频窗口的高度
	virtual int GetHeight(void)=0;	//pass

	// 显示/隐藏 视频窗口
	virtual void ShowWindow(BOOL bShow)=0;	//pass
	//视频窗口是否可见
	virtual BOOL IsWindowVisible(void)=0;	//pass
	//设置视频窗口的位置
	virtual void SetWindowPosition(int x,int y,int cx,int cy)=0;	//pass

	// 启用/禁用透明标题栏
	virtual void EnableTitle(BOOL bEnable)=0;	//to be done...
	//是否启用了透明标题栏
	virtual BOOL IsTitleEnable(void)=0;
	//设置透明标题栏的文字和方向
	virtual void SetTitleText(const TCHAR*cszText,int nAlign=0)=0;//Align==0 TOP_LEFT 1:BOTOM_LEFT	//to be done...

	//得到视频窗口的句柄
	virtual HWND GetHWnd(void)=0;	//pass

	//设置标题栏字体,字的颜色和背景色
	virtual void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255))=0;	//to be done...
};

class AFX_EXT_CLASS IOVideoDis :public VideoWndDis
{
public:
	IOVideoDis(void){};
	virtual ~IOVideoDis(){};

public:

	virtual void CloseAll(void)=0;
	virtual void CloseVideoDisplay(void)=0;	//pass

	virtual void GetVideoSize(VIDEO_DIS_SIZE *VideoSize)=0;	//pass
	virtual VIDEO_DIS_TYPE GetVideoType(void)=0;	//pass

	virtual void SetVideoFrameRate(int FrameRate)=0;
	virtual int  GetVideoFrameRate(void)=0;			//pass
	virtual double GetVideoBitrate(void)=0;	//pass

	virtual int  OpenVideoDisplay(VIDEO_DIS_TYPE VideoType, VIDEO_DIS_SIZE VideoSize)=0;	//pass
	virtual int  ReSetVideoDisplay(VIDEO_DIS_TYPE VideoType, VIDEO_DIS_SIZE VideoSize)=0;//pass

	virtual bool HasVideo(void)=0;		//pass
	virtual void StartVideoDisplay(void)=0;	//pass
	virtual bool IsStopVideoDisplay(void)=0;	//pass
	virtual void StopVideoDisplay(void)=0;	//pass
	virtual void ReStartVideoDisplay(void)=0;	//pass

	//放入视频数据包
	virtual void SetVideoPacket(unsigned char*pPacketData,int nPacketLen)=0;//pass

////////////////////////////////////////////////////
		
	virtual void Invert(bool bInverted)=0;	//视频颠倒			//pass
	virtual bool IsInverted(void)=0;	//是否已经视频颠倒		//pass

	virtual bool IsDeinterlaceEnable(void)=0;	//pass
	virtual void EnableDeinterlace(bool bDeinterlace)=0;	//pass
	virtual bool IsDenoiseEnable(void)=0;	//pass
	virtual void EnableDenoise(bool bDenoise)=0;	//pass
	virtual bool CaptureToJPGFile(const char*cszJPGFile)=0;

	//设置视频参数
	virtual void SetVideoParam(int nBrightness=128/*亮度值0-255*/, int nContrast=64/*对比度0-127*/, int nSaturation=64/*饱和度0-127*/, int nHue=0/*色调0-255*/,int nGamma=100/*伽马1-400*/,int nSharpen=0/*锐化0-127*/)=0;


///////////////////////////////////////////////////////////////
	virtual void CloseAudioDisplay(void)=0;	//关闭音频播放

	virtual int OpenAudioDisplay(AUDIO_DIS_TYPE AudioType)=0;
	virtual int ReSetAudioDisplay(AUDIO_DIS_TYPE AudioType)=0;	//重设音频采集的参数
	
	virtual AUDIO_DIS_TYPE GetAudioType(void)=0;
	//得到音频码流
	virtual double GetAudioBitrate(void)=0;	//pass
	//得到本视频播放窗口的音频丢包数
	virtual unsigned long GetAudioLostCount(void)=0;

	virtual void  StartAudioDisplay(void)=0;
	virtual bool  IsStopAudioDisplay(void)=0;
	virtual void  StopAudioDisplay(void)=0;
	virtual void  ReStartAudioDisplay(void)=0;

	//放入音频数据包
	virtual void SetAudioPacket(unsigned char*pPacketData,int nPacketLen)=0;


	//本视频播放窗口是否有音频
	virtual BOOL HasAudio(void)=0;
	//设置本视频播放窗口静音
	//virtual void Mute(BOOL bMute)=0;
	////设置本视频播放窗口的音量
	virtual void SetVolume(int nNewVolume)=0;
	//得到本视频播放窗口的音量
	virtual int GetVolume(void)=0;

	//得到本视频播放窗口的音量
	virtual int GetAudioLevel(void)=0;//建议每隔200毫秒调用一次


	// 启用/禁用 唇音同步
	virtual void EnableSyn( BOOL SynEnable)=0;
};


AFX_EXT_API IOVideoDis* IOCreateVideoDis(void* hWndParentWindow, IOVideoDisNotify *hFuncVideoDisNotify);	//pass

#endif
