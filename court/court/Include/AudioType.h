//
// Constants
//
/// 音频编解码器支持的编码方式
typedef enum AUDIOTYPE
{
	AUDIOTYPE_G711a = 0,	///0< G.711   8kHz  A律编码方式
	AUDIOTYPE_G723,			///1< G.723.1 8kHz  6.3kbps编码方式
	AUDIOTYPE_G711plus,		///2< 高带宽冗余编码方式：G.711 + G.723.1 x 2
	AUDIOTYPE_G723plus,		///3< 低带宽冗余编码方式：G.723.1 x 2
	AUDIOTYPE_CELP,		    ///4< Celp   16kHz 高带宽MPEG-4 celp语音编码方式
	AUDIOTYPE_CELPplus,     ///5< Celp   16kHz 高带宽MPEG-4 celp语音编码方式：Celp x 2
	AUDIOTYPE_SPEEX,		///6< 保留
	AUDIOTYPE_PCM,			///7< PCM码
	AUDIOTYPE_G711u ,		///8< G.711  8kHz  u律编码方式
	AUDIOTYPE_SPEEX_NB,		///9< Speex  8kHz  采样 编码方式
	AUDIOTYPE_SPEEX_WB,		///10< Speex 16kHz 采样 编码方式
	AUDIOTYPE_SPEEX_UWB,	///11< Speex 32kHz 采样 编码方式
	AUDIOTYPE_G729,			///12< G729  8kHz  采样 编码方式
	AUDIOTYPE_G729a,		///13< G729a 8kHz  采样 编码方式
	AUDIOTYPE_G729plus,		///14< G729  8kHz  采样  冗余编码方式 G729  x 2
	AUDIOTYPE_G729aplus,	///15< G729a 8kHz  采样  冗余编码方式 G729a x 2
	AUDIOTYPE_ILBC,			///16< iLBC  8kHz  采样  30ms模式 编码方式
	AUDIOTYPE_AMR_WB,       ///17< iLBC  16kHz 采样
	AUDIOTYPE_NONE			///< 未定义的编码方式
} AUDIOTYPE;