//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IOVideoCap.h: interface for the IOVideoCap class.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __IOVIDEOCAP_H__
#define __IOVIDEOCAP_H__

//#define AFX_EXT_CLASS  __declspec(dllexport)
//#define AFX_EXT_CLASS __declspec(dllimport)

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

typedef enum VIDEO_SIZE_NICK_NAME{
	SIZE_DEFAULT=-1,
	SIZE_176X144=0,	//
	SIZE_320X240,	//
	SIZE_352X288,	//
	SIZE_640X480,	//
	SIZE_704X576,	//
	SIZE_800X600,	//
	SIZE_1024X768,	//
	SIZE_1280X720,	//
	SIZE_1280X800,	//
	SIZE_1920X1080,	//
}VIDEO_SIZE_NICK_NAME;

typedef enum VIDEO_BIT_RATE_NICK_NAME{
	BR_DEFAULT=-1,	//
	BR_32KBPS=0,	//
	BR_64KBPS,		//
	BR_128KBPS,		//
	BR_256KBPS,		//
	BR_512KBPS,		//
	BR_768KBPS,		//
	BR_1MBPS,		//
	BR_1D5MBPS,		//
	BR_2MBPS,		//
	BR_4MKBPS,		//
	BR_8MBPS,		//
}VIDEO_BIT_RATE_NICK_NAME;



typedef struct VIDEO_CAP_SIZE
{
	int width;	//采集图像宽
	int height;//采集图像高

}VIDEO_CAP_SIZE;

typedef enum VIDEO_CAP_TYPE{
	VIDEO_CAP_TYPE_NON=-1,
	VIDEO_CAP_TYPE_YV12=0,	//采集得到yuv数据， YV12格式
	VIDEO_CAP_TYPE_YUYV,	//采集得到yuv数据，YUYV交错格式， 目前不支持
	VIDEO_CAP_TYPE_RGB16,	//采集得到RGB16数据，目前不支持
	VIDEO_CAP_TYPE_RGB24,	//采集得到RGB24数据
	VIDEO_CAP_TYPE_H263RAW,	//目前不支持
	VIDEO_CAP_TYPE_H263PRAW,//目前不支持
	VIDEO_CAP_TYPE_H263PPRAW,//目前不支持
	VIDEO_CAP_TYPE_H264RAW,	//采集得到RGB24数据
	VIDEO_CAP_TYPE_H264RTP,//目前不支持
	VIDEO_CAP_TYPE_H264UDP,//目前不支持
}VIDEO_CAP_TYPE;

#ifndef	AUDIO_CAP_TYPE_DEFINE
#define	AUDIO_CAP_TYPE_DEFINE

typedef enum AUDIO_CAP_TYPE{
	AUDIO_CAP_TYPE_NON=-1,
	AUDIO_CAP_TYPE_WAVE=0,
	AUDIO_CAP_TYPE_G711,
	AUDIO_CAP_TYPE_G722,
	AUDIO_CAP_TYPE_G729,
	AUDIO_CAP_TYPE_MP3,
	AUDIO_CAP_TYPE_AAC,
}AUDIO_CAP_TYPE;
#endif	//#ifndef	AUDIO_CAP_TYPE

class AFX_EXT_CLASS IOVideoCapNotify
{
public:
	IOVideoCapNotify(void){};
	virtual~IOVideoCapNotify(void){};
public:
	//输出音频数据包的回调
	virtual void OnIOAudioCapNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)=0;		//pass
	virtual void OnIOAudioEncNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;	//pass
	//输出视频数据包的回调
	virtual void OnIOVideoCapNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;		//pass
	virtual void OnIOVideoEncNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;	//pass
	virtual void OnIOVideoEncNotifyRTPPacket(unsigned char*pPacketData,int nPacketLen)=0;	//current not used
	//输出视频子流数据包的回调
	virtual void OnIOVideoSubCapNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;			//current not used
	virtual void OnIOVideoSubEncNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;	//current not used
	virtual void OnIOVideoSubEncNotifyRTPPacket(unsigned char*pPacketData,int nPacketLen)=0;	//current not used
};

class VideoWndCap
{
public:
	VideoWndCap(void){};
	virtual~VideoWndCap(void){};
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

class IOVideoCap:public VideoWndCap
{
public:
	IOVideoCap(void){};
	virtual ~IOVideoCap(void){};

public:

	virtual void CloseAll(void)=0;	//关闭采集	//pass
	virtual void CloseVideoCapture(void)=0;	//关闭视频采集	//pass

	virtual VIDEO_CAP_TYPE GetVideoType(void)=0;	//pass
	virtual void GetVideoSize(VIDEO_CAP_SIZE *VideoSize)=0;	//pass
	virtual int  GetVideoFrameRate(void)=0;	//pass

	virtual int OpenVideoCapture(int nDevice, VIDEO_CAP_TYPE VideoType, VIDEO_CAP_SIZE VideoSize, int nFrameRate,int nBitrate, int Cbr)=0;	//pass
	virtual int ReSetVideoCapture(int nDevice, VIDEO_CAP_TYPE VideoType, VIDEO_CAP_SIZE VideoSize, int nFrameRate,int nBitrate, int Cbr)=0;	//重设视频采集的参数    //pass
	virtual int EncodeVideoFrame(void*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;

	virtual void RequestVideoKeyFrame(bool KeyFrame)=0;	//采集视频关键帧
	virtual double GetVideoBitrate(void)=0;//建议每隔2000毫秒调用一次	//pass
	
	virtual bool HasVideoCapture(void)=0;		//pass
	virtual void StartVideoCapture(void)=0;		//pass
	virtual bool IsStopVideoCapture(void)=0;
	virtual void StopVideoCapture(void)=0;		//pass
	virtual void ReStartVideoCapture(void)=0;	//pass


////////////////////////////////////////////////////
		
	virtual bool HasVideoInputWindow(void)=0;//是否可以进行视频输入调整	
	virtual void ShowVideoInputWindow(void)=0;//显示视频输入调整窗口
	virtual bool HasVideoAdjustWindow(void)=0;//是否可以进行视频高级调整
	virtual void ShowAdjustVideoWnd(void)=0;	//显示视频高级调整窗口
	virtual void EnableShowVideoPreView(bool bVideoPreView)=0;	//pass
	virtual bool IsShowVideoPreView(void)=0;	//pass

	virtual void Invert(bool bInverted)=0;	//视频颠倒			//pass
	virtual bool IsInverted(void)=0;	//是否已经视频颠倒		//pass

	virtual bool IsDeinterlaceEnable(void)=0;	//pass
	virtual void EnableDeinterlace(bool bDeinterlace)=0;	//pass
	virtual bool IsDenoiseEnable(void)=0;	//pass
	virtual void EnableDenoise(bool bDenoise)=0;	//pass
	virtual bool CaptureToJPGFile(const char*cszJPGFile)=0;

	virtual bool CanSetVideoParam(void)=0;//是否可以设置视频参数
	virtual void SetVideoParam(int nBrightness=128/*亮度值0-255*/, int nContrast=64/*对比度0-127*/, int nSaturation=64/*饱和度0-127*/, int nHue=0/*色调0-255*/,int nGamma=100/*伽马1-400*/,int nSharpen=0/*锐化0-127*/)=0;	//设置视频参数


///////////////////////////////////////////////////////////////
	virtual void CloseAudioCapture(void)=0;	//关闭音频采集

	virtual int		OpenAudioCapture(int nDevice, AUDIO_CAP_TYPE AudioType, bool bBroadBand=0, bool bStereo=0)=0;	//打开音频采集
	virtual int		ReSetAudioCapture(int nDevice, AUDIO_CAP_TYPE AudioType, bool bBroadBand=0, bool bStereo=0)=0;	//重设视频采集的参数
	virtual int		EncodeAudioFrame(void*pFrameData, int nFrameSize, double dSamples)=0;

	virtual AUDIO_CAP_TYPE GetAudioType(void)=0;
	virtual double	GetAudioBitrate(void)=0;//建议每隔2000毫秒调用一次
	virtual int		GetInVolume(void)=0;
	virtual int		GetOutVolume(void)=0;

	virtual bool	HasAudioCapture(void)=0;
	virtual void	StartAudioCapture(void)=0;
	virtual bool	IsStopAudioCapture(void)=0;
	virtual void	StopAudioCapture(void)=0;
	virtual void	RestartAudioCapture(void)=0;
};

//创建视频采集对象
AFX_EXT_API IOVideoCap* IOCreateVideoCap(void* hWndParentWindow, IOVideoCapNotify *hFuncVideoCapNotify);//pass

//video device API
//取亮度值范围
AFX_EXT_API int GetBrightessRange(int&nMin,int&nMax);
//取亮度值的缺省值
AFX_EXT_API int GetDefaultBrightness(void);

//取对比度范围
AFX_EXT_API int GetContrastRange(int&nMin,int&nMax);
//取对比度的缺省值
AFX_EXT_API int GetDefaultContrast(void);

//取饱和度范围
AFX_EXT_API int GetSaturationRange(int&nMin,int&nMax);
//取饱和度的缺省值
AFX_EXT_API int GetDefaultSaturation(void);

//取色调范围
AFX_EXT_API int GetHueRange(int&nMin,int&nMax);
//取色调的缺省值
AFX_EXT_API int GetDefaultHue(void);

//取伽马范围
AFX_EXT_API int GetGammaRange(int&nMin,int&nMax);
//取伽马的缺省值
AFX_EXT_API int GetDefaultGamma(void);

//取锐化范围
AFX_EXT_API int GetSharpenRange(int&nMin,int&nMax);
//取锐化的缺省值
AFX_EXT_API int GetDefaultSharpen(void);

AFX_EXT_CLASS bool GetVideoCaptureDevice(void *hwComboBox);	//pass
//得到视频采集设备的数量
AFX_EXT_CLASS int GetVideoCaptureDeviceCount(void);	//pass

//根据视频采集设备号得到名称
AFX_EXT_CLASS bool GetVideoCaptureDeviceName(int nDevice,char*szDeviceName);	//pass

//for video capture
//得到视频采集设备的数量
AFX_EXT_CLASS int GetAudioCaptureDeviceCount(void);	//pass

//根据视频采集设备号得到名称
AFX_EXT_CLASS bool GetAudioCaptureDeviceName(int nDevice,char*szDeviceName);	//pass



AFX_EXT_CLASS void EnableAudioAEC(bool bEnable);
AFX_EXT_CLASS bool IsEnableAudioAEC(void);
AFX_EXT_CLASS void EnableAudioAGC(bool bEnable);
AFX_EXT_CLASS bool IsEnableAudioAGC(void);

//判断是高清设备
AFX_EXT_CLASS bool IsHDDevice(int nDevID);

AFX_EXT_CLASS int SD_GetFormatCount(void);
AFX_EXT_CLASS bool SD_GetFormatName(int nIndex,char*szName);
AFX_EXT_CLASS bool SD_GetFormatSize(int nIndex,int&nWidth,int&nHeight);

AFX_EXT_CLASS int HD_GetFormatCount(void);
AFX_EXT_CLASS bool HD_GetFormatName(int nIndex,char*szName);
AFX_EXT_CLASS bool HD_GetFormatSize(int nIndex,int&nWidth,int&nHeight);


#endif
