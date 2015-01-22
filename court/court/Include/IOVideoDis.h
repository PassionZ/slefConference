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
	//�����Ƶ���ݰ��Ļص�
	virtual void OnIOAudioDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)=0;	//pass
	//�����Ƶ���ݰ��Ļص�
	virtual void OnIOVideoDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;	//pass
	virtual void OnIOVideoDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;		//current not used
	//�����Ƶ�������ݰ��Ļص�
	virtual void OnIOVideoSubDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)=0;			//current not used
	virtual void OnIOVideoSubDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen)=0;	//current not used
};

class VideoWndDis
{
public:
	VideoWndDis(void){};
	virtual~VideoWndDis(void){};
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

	//������Ƶ���ݰ�
	virtual void SetVideoPacket(unsigned char*pPacketData,int nPacketLen)=0;//pass

////////////////////////////////////////////////////
		
	virtual void Invert(bool bInverted)=0;	//��Ƶ�ߵ�			//pass
	virtual bool IsInverted(void)=0;	//�Ƿ��Ѿ���Ƶ�ߵ�		//pass

	virtual bool IsDeinterlaceEnable(void)=0;	//pass
	virtual void EnableDeinterlace(bool bDeinterlace)=0;	//pass
	virtual bool IsDenoiseEnable(void)=0;	//pass
	virtual void EnableDenoise(bool bDenoise)=0;	//pass
	virtual bool CaptureToJPGFile(const char*cszJPGFile)=0;

	//������Ƶ����
	virtual void SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/)=0;


///////////////////////////////////////////////////////////////
	virtual void CloseAudioDisplay(void)=0;	//�ر���Ƶ����

	virtual int OpenAudioDisplay(AUDIO_DIS_TYPE AudioType)=0;
	virtual int ReSetAudioDisplay(AUDIO_DIS_TYPE AudioType)=0;	//������Ƶ�ɼ��Ĳ���
	
	virtual AUDIO_DIS_TYPE GetAudioType(void)=0;
	//�õ���Ƶ����
	virtual double GetAudioBitrate(void)=0;	//pass
	//�õ�����Ƶ���Ŵ��ڵ���Ƶ������
	virtual unsigned long GetAudioLostCount(void)=0;

	virtual void  StartAudioDisplay(void)=0;
	virtual bool  IsStopAudioDisplay(void)=0;
	virtual void  StopAudioDisplay(void)=0;
	virtual void  ReStartAudioDisplay(void)=0;

	//������Ƶ���ݰ�
	virtual void SetAudioPacket(unsigned char*pPacketData,int nPacketLen)=0;


	//����Ƶ���Ŵ����Ƿ�����Ƶ
	virtual BOOL HasAudio(void)=0;
	//���ñ���Ƶ���Ŵ��ھ���
	//virtual void Mute(BOOL bMute)=0;
	////���ñ���Ƶ���Ŵ��ڵ�����
	virtual void SetVolume(int nNewVolume)=0;
	//�õ�����Ƶ���Ŵ��ڵ�����
	virtual int GetVolume(void)=0;

	//�õ�����Ƶ���Ŵ��ڵ�����
	virtual int GetAudioLevel(void)=0;//����ÿ��200�������һ��


	// ����/���� ����ͬ��
	virtual void EnableSyn( BOOL SynEnable)=0;
};


AFX_EXT_API IOVideoDis* IOCreateVideoDis(void* hWndParentWindow, IOVideoDisNotify *hFuncVideoDisNotify);	//pass

#endif
