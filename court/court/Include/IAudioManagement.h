// IAUDIOMANAGEMENT.h

#if !defined(_AUDIOMANAGEMENT_H_)
#define _AUDIOMANAGEMENT_H_

#ifdef _AUDIOMANAGEMENT_
#define DllExport_AUDIOMANAGEMENT __declspec(dllexport)
#else
#define DllExport_AUDIOMANAGEMENT __declspec(dllimport) 
#endif

// AudioInfo Type
typedef enum _eAudioInfoType {ntAGC,ntAEC,ntNOISE_REDUCTION,ntMIC_REINFORCE} AudioInfoType;

class AFX_EXT_CLASS IOAudioCaptureNotify
{
public:
	IOAudioCaptureNotify(void){};
	virtual~IOAudioCaptureNotify(void){};
public:
	//�����Ƶ���ݰ��Ļص�
	virtual void OnIOAudioCaptureNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)=0;
	virtual void OnIOAudioCaptureEncNotifyFrame(unsigned char*pPacketData,int nPacketLen)=0;
};

class AFX_EXT_CLASS IOAudioCapture
{
public:
	IOAudioCapture(void){};
	virtual ~IOAudioCapture(void){};

public:
	virtual void	ReleaseAudio(void)=0;

	virtual void	InitAudioCapture(int nDevice, int AudioType)=0;	//������Ƶ�ɼ�
	virtual void	EncodeAudioFrame(void*pFrameData, int nFrameSize, double dSamples)=0;
	//���þ���
	virtual void SetMute(BOOL bMute)=0;

	virtual int		GetInVolume(void)=0;
	virtual int		GetOutVolume(void)=0;
};

class AFX_EXT_CLASS IOAudioPlayNotify
{
public:
	IOAudioPlayNotify(void){};
	virtual~IOAudioPlayNotify(void){};
public:
	//�����������Ƶ���ݰ��Ļص�
	virtual void OnIOAudioPlayDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)=0;
};

class AFX_EXT_CLASS IOAudioPlay
{
public:
	IOAudioPlay(){};
	virtual ~IOAudioPlay(){};

	virtual void ReleaseAudio(void)=0;

	//������Ƶ���ݰ�
	virtual void SetAudioPacket(unsigned char*pPacketData,int nPacketLen,BOOL bPlay=TRUE)=0;

	//���þ���
	virtual void SetMute(BOOL bMute)=0;
	//��������
	virtual void SetVolume(int nNewVolume)=0;

	//�õ�����
	virtual int GetVolume(void)=0;
	virtual int	GetOutVolume(void)=0;

	// ����/���� ����ͬ��
	virtual void EnableSyn( BOOL SynEnable)=0;
};

//������Ƶ�ɼ�����
DllExport_AUDIOMANAGEMENT IOAudioCapture* IOCreateAudioCapture(IOAudioCaptureNotify *hFuncAudioCaptureNotify);
//������Ƶ���Ŷ���
DllExport_AUDIOMANAGEMENT IOAudioPlay* IOCreateAudioPlay(IOAudioPlayNotify *hFuncAudioPlayNotify);

//��Ƶ�ⴴ��
DllExport_AUDIOMANAGEMENT void AudioCreate();
//��Ƶ���ͷ�
DllExport_AUDIOMANAGEMENT void AudioRelease();

//������Ƶ������Ϣ
DllExport_AUDIOMANAGEMENT void SetAudioInfo(int nInfoType,int nInfoValue);

/// ����Ƶ���������豸���м���
/**
* @param bInputDevice [IN] �豸���͡���������Ϊ�棬�����Ƶ�����豸���м������������Ƶ����豸���м���
* @return ָ�����͵���Ƶ�豸����Ŀ
*/
DllExport_AUDIOMANAGEMENT UINT GetAudioCount(BOOL bInputDevice);

/// ȡ��ָ����Ƶ���������豸��������Ϣ
/**
* @param nIndex [IN] ָ���豸������ֵ
* @param bInputDevice [IN] �豸���͡���������Ϊ�棬��ָ���豸Ϊ��Ƶ�����豸������Ϊ��Ƶ����豸
* @return ָ���豸��������Ϣ
*/
DllExport_AUDIOMANAGEMENT const char* GetAudioDesc(UINT nIndex, BOOL bInputDevice);

/// �õ�MIC����������С
/**
* @return ������СֵΪ0��100
*/
DllExport_AUDIOMANAGEMENT UINT GetMICInVolume();

/// �õ��������������С
/**
* @return ������СֵΪ0��100
*/
DllExport_AUDIOMANAGEMENT UINT GetSpeakerOutVolume();

//�����Ż�
DllExport_AUDIOMANAGEMENT void SilenceOptimize();
#endif