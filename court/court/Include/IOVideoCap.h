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
	int width;	//�ɼ�ͼ���
	int height;//�ɼ�ͼ���

}VIDEO_CAP_SIZE;

typedef enum VIDEO_CAP_TYPE{
	VIDEO_CAP_TYPE_NON=-1,
	VIDEO_CAP_TYPE_YV12=0,	//�ɼ��õ�yuv���ݣ� YV12��ʽ
	VIDEO_CAP_TYPE_YUYV,	//�ɼ��õ�yuv���ݣ�YUYV�����ʽ�� Ŀǰ��֧��
	VIDEO_CAP_TYPE_RGB16,	//�ɼ��õ�RGB16���ݣ�Ŀǰ��֧��
	VIDEO_CAP_TYPE_RGB24,	//�ɼ��õ�RGB24����
	VIDEO_CAP_TYPE_H263RAW,	//Ŀǰ��֧��
	VIDEO_CAP_TYPE_H263PRAW,//Ŀǰ��֧��
	VIDEO_CAP_TYPE_H263PPRAW,//Ŀǰ��֧��
	VIDEO_CAP_TYPE_H264RAW,	//�ɼ��õ�RGB24����
	VIDEO_CAP_TYPE_H264RTP,//Ŀǰ��֧��
	VIDEO_CAP_TYPE_H264UDP,//Ŀǰ��֧��
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
	//�����Ƶ���ݰ��Ļص�
	virtual void OnIOAudioCapNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)=0;		//pass
	virtual void OnIOAudioEncNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;	//pass
	//�����Ƶ���ݰ��Ļص�
	virtual void OnIOVideoCapNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;		//pass
	virtual void OnIOVideoEncNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;	//pass
	virtual void OnIOVideoEncNotifyRTPPacket(unsigned char*pPacketData,int nPacketLen)=0;	//current not used
	//�����Ƶ�������ݰ��Ļص�
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
	//�õ���Ƶ���ڵĿ��
	virtual int GetWidth(void)=0;	//pass
	//�õ���Ƶ���ڵĸ߶�
	virtual int GetHeight(void)=0;	//pass

	// ��ʾ/���� ��Ƶ����
	virtual void ShowWindow(BOOL bShow)=0;	//pass
	//��Ƶ�����Ƿ�ɼ�
	virtual BOOL IsWindowVisible(void)=0;	//pass
	//������Ƶ���ڵ�λ��
	virtual void SetWindowPosition(int x,int y,int cx,int cy)=0;	//pass

	// ����/����͸��������
	virtual void EnableTitle(BOOL bEnable)=0;	//to be done...
	//�Ƿ�������͸��������
	virtual BOOL IsTitleEnable(void)=0;
	//����͸�������������ֺͷ���
	virtual void SetTitleText(const TCHAR*cszText,int nAlign=0)=0;//Align==0 TOP_LEFT 1:BOTOM_LEFT	//to be done...

	//�õ���Ƶ���ڵľ��
	virtual HWND GetHWnd(void)=0;	//pass

	//���ñ���������,�ֵ���ɫ�ͱ���ɫ
	virtual void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255))=0;	//to be done...
};

class IOVideoCap:public VideoWndCap
{
public:
	IOVideoCap(void){};
	virtual ~IOVideoCap(void){};

public:

	virtual void CloseAll(void)=0;	//�رղɼ�	//pass
	virtual void CloseVideoCapture(void)=0;	//�ر���Ƶ�ɼ�	//pass

	virtual VIDEO_CAP_TYPE GetVideoType(void)=0;	//pass
	virtual void GetVideoSize(VIDEO_CAP_SIZE *VideoSize)=0;	//pass
	virtual int  GetVideoFrameRate(void)=0;	//pass

	virtual int OpenVideoCapture(int nDevice, VIDEO_CAP_TYPE VideoType, VIDEO_CAP_SIZE VideoSize, int nFrameRate,int nBitrate, int Cbr)=0;	//pass
	virtual int ReSetVideoCapture(int nDevice, VIDEO_CAP_TYPE VideoType, VIDEO_CAP_SIZE VideoSize, int nFrameRate,int nBitrate, int Cbr)=0;	//������Ƶ�ɼ��Ĳ���    //pass
	virtual int EncodeVideoFrame(void*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;

	virtual void RequestVideoKeyFrame(bool KeyFrame)=0;	//�ɼ���Ƶ�ؼ�֡
	virtual double GetVideoBitrate(void)=0;//����ÿ��2000�������һ��	//pass
	
	virtual bool HasVideoCapture(void)=0;		//pass
	virtual void StartVideoCapture(void)=0;		//pass
	virtual bool IsStopVideoCapture(void)=0;
	virtual void StopVideoCapture(void)=0;		//pass
	virtual void ReStartVideoCapture(void)=0;	//pass


////////////////////////////////////////////////////
		
	virtual bool HasVideoInputWindow(void)=0;//�Ƿ���Խ�����Ƶ�������	
	virtual void ShowVideoInputWindow(void)=0;//��ʾ��Ƶ�����������
	virtual bool HasVideoAdjustWindow(void)=0;//�Ƿ���Խ�����Ƶ�߼�����
	virtual void ShowAdjustVideoWnd(void)=0;	//��ʾ��Ƶ�߼���������
	virtual void EnableShowVideoPreView(bool bVideoPreView)=0;	//pass
	virtual bool IsShowVideoPreView(void)=0;	//pass

	virtual void Invert(bool bInverted)=0;	//��Ƶ�ߵ�			//pass
	virtual bool IsInverted(void)=0;	//�Ƿ��Ѿ���Ƶ�ߵ�		//pass

	virtual bool IsDeinterlaceEnable(void)=0;	//pass
	virtual void EnableDeinterlace(bool bDeinterlace)=0;	//pass
	virtual bool IsDenoiseEnable(void)=0;	//pass
	virtual void EnableDenoise(bool bDenoise)=0;	//pass
	virtual bool CaptureToJPGFile(const char*cszJPGFile)=0;

	virtual bool CanSetVideoParam(void)=0;//�Ƿ����������Ƶ����
	virtual void SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/)=0;	//������Ƶ����


///////////////////////////////////////////////////////////////
	virtual void CloseAudioCapture(void)=0;	//�ر���Ƶ�ɼ�

	virtual int		OpenAudioCapture(int nDevice, AUDIO_CAP_TYPE AudioType, bool bBroadBand=0, bool bStereo=0)=0;	//����Ƶ�ɼ�
	virtual int		ReSetAudioCapture(int nDevice, AUDIO_CAP_TYPE AudioType, bool bBroadBand=0, bool bStereo=0)=0;	//������Ƶ�ɼ��Ĳ���
	virtual int		EncodeAudioFrame(void*pFrameData, int nFrameSize, double dSamples)=0;

	virtual AUDIO_CAP_TYPE GetAudioType(void)=0;
	virtual double	GetAudioBitrate(void)=0;//����ÿ��2000�������һ��
	virtual int		GetInVolume(void)=0;
	virtual int		GetOutVolume(void)=0;

	virtual bool	HasAudioCapture(void)=0;
	virtual void	StartAudioCapture(void)=0;
	virtual bool	IsStopAudioCapture(void)=0;
	virtual void	StopAudioCapture(void)=0;
	virtual void	RestartAudioCapture(void)=0;
};

//������Ƶ�ɼ�����
AFX_EXT_API IOVideoCap* IOCreateVideoCap(void* hWndParentWindow, IOVideoCapNotify *hFuncVideoCapNotify);//pass

//video device API
//ȡ����ֵ��Χ
AFX_EXT_API int GetBrightessRange(int&nMin,int&nMax);
//ȡ����ֵ��ȱʡֵ
AFX_EXT_API int GetDefaultBrightness(void);

//ȡ�Աȶȷ�Χ
AFX_EXT_API int GetContrastRange(int&nMin,int&nMax);
//ȡ�Աȶȵ�ȱʡֵ
AFX_EXT_API int GetDefaultContrast(void);

//ȡ���Ͷȷ�Χ
AFX_EXT_API int GetSaturationRange(int&nMin,int&nMax);
//ȡ���Ͷȵ�ȱʡֵ
AFX_EXT_API int GetDefaultSaturation(void);

//ȡɫ����Χ
AFX_EXT_API int GetHueRange(int&nMin,int&nMax);
//ȡɫ����ȱʡֵ
AFX_EXT_API int GetDefaultHue(void);

//ȡ٤��Χ
AFX_EXT_API int GetGammaRange(int&nMin,int&nMax);
//ȡ٤���ȱʡֵ
AFX_EXT_API int GetDefaultGamma(void);

//ȡ�񻯷�Χ
AFX_EXT_API int GetSharpenRange(int&nMin,int&nMax);
//ȡ�񻯵�ȱʡֵ
AFX_EXT_API int GetDefaultSharpen(void);

AFX_EXT_CLASS bool GetVideoCaptureDevice(void *hwComboBox);	//pass
//�õ���Ƶ�ɼ��豸������
AFX_EXT_CLASS int GetVideoCaptureDeviceCount(void);	//pass

//������Ƶ�ɼ��豸�ŵõ�����
AFX_EXT_CLASS bool GetVideoCaptureDeviceName(int nDevice,char*szDeviceName);	//pass

//for video capture
//�õ���Ƶ�ɼ��豸������
AFX_EXT_CLASS int GetAudioCaptureDeviceCount(void);	//pass

//������Ƶ�ɼ��豸�ŵõ�����
AFX_EXT_CLASS bool GetAudioCaptureDeviceName(int nDevice,char*szDeviceName);	//pass



AFX_EXT_CLASS void EnableAudioAEC(bool bEnable);
AFX_EXT_CLASS bool IsEnableAudioAEC(void);
AFX_EXT_CLASS void EnableAudioAGC(bool bEnable);
AFX_EXT_CLASS bool IsEnableAudioAGC(void);

//�ж��Ǹ����豸
AFX_EXT_CLASS bool IsHDDevice(int nDevID);

AFX_EXT_CLASS int SD_GetFormatCount(void);
AFX_EXT_CLASS bool SD_GetFormatName(int nIndex,char*szName);
AFX_EXT_CLASS bool SD_GetFormatSize(int nIndex,int&nWidth,int&nHeight);

AFX_EXT_CLASS int HD_GetFormatCount(void);
AFX_EXT_CLASS bool HD_GetFormatName(int nIndex,char*szName);
AFX_EXT_CLASS bool HD_GetFormatSize(int nIndex,int&nWidth,int&nHeight);


#endif
