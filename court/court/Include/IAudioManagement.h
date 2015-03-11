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
	//输出音频数据包的回调
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

	virtual void	InitAudioCapture(int nDevice, int AudioType)=0;	//设置音频采集
	virtual void	EncodeAudioFrame(void*pFrameData, int nFrameSize, double dSamples)=0;
	//设置静音
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
	//解码后的输出音频数据包的回调
	virtual void OnIOAudioPlayDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)=0;
};

class AFX_EXT_CLASS IOAudioPlay
{
public:
	IOAudioPlay(){};
	virtual ~IOAudioPlay(){};

	virtual void ReleaseAudio(void)=0;

	//放入音频数据包
	virtual void SetAudioPacket(unsigned char*pPacketData,int nPacketLen,BOOL bPlay=TRUE)=0;

	//设置静音
	virtual void SetMute(BOOL bMute)=0;
	//设置音量
	virtual void SetVolume(int nNewVolume)=0;

	//得到音量
	virtual int GetVolume(void)=0;
	virtual int	GetOutVolume(void)=0;

	// 启用/禁用 唇音同步
	virtual void EnableSyn( BOOL SynEnable)=0;
};

//创建音频采集对象
DllExport_AUDIOMANAGEMENT IOAudioCapture* IOCreateAudioCapture(IOAudioCaptureNotify *hFuncAudioCaptureNotify);
//创建音频播放对象
DllExport_AUDIOMANAGEMENT IOAudioPlay* IOCreateAudioPlay(IOAudioPlayNotify *hFuncAudioPlayNotify);

//音频库创建
DllExport_AUDIOMANAGEMENT void AudioCreate();
//音频库释放
DllExport_AUDIOMANAGEMENT void AudioRelease();

//设置音频附加信息
DllExport_AUDIOMANAGEMENT void SetAudioInfo(int nInfoType,int nInfoValue);

/// 对音频输入或输出设备进行计数
/**
* @param bInputDevice [IN] 设备类型。若本参数为真，则对音频输入设备进行计数，否则对音频输出设备进行计数
* @return 指定类型的音频设备的数目
*/
DllExport_AUDIOMANAGEMENT UINT GetAudioCount(BOOL bInputDevice);

/// 取得指定音频输入或输出设备的描述信息
/**
* @param nIndex [IN] 指定设备的索引值
* @param bInputDevice [IN] 设备类型。若本参数为真，则指定设备为音频输入设备，否则为音频输出设备
* @return 指定设备的描述信息
*/
DllExport_AUDIOMANAGEMENT const char* GetAudioDesc(UINT nIndex, BOOL bInputDevice);

/// 得到MIC输入音量大小
/**
* @return 音量大小值为0到100
*/
DllExport_AUDIOMANAGEMENT UINT GetMICInVolume();

/// 得到音响输出音量大小
/**
* @return 音量大小值为0到100
*/
DllExport_AUDIOMANAGEMENT UINT GetSpeakerOutVolume();

//静音优化
DllExport_AUDIOMANAGEMENT void SilenceOptimize();
#endif