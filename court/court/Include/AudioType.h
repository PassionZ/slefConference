//
// Constants
//
/// ��Ƶ�������֧�ֵı��뷽ʽ
typedef enum AUDIOTYPE
{
	AUDIOTYPE_G711a = 0,	///0< G.711   8kHz  A�ɱ��뷽ʽ
	AUDIOTYPE_G723,			///1< G.723.1 8kHz  6.3kbps���뷽ʽ
	AUDIOTYPE_G711plus,		///2< �ߴ���������뷽ʽ��G.711 + G.723.1 x 2
	AUDIOTYPE_G723plus,		///3< �ʹ���������뷽ʽ��G.723.1 x 2
	AUDIOTYPE_CELP,		    ///4< Celp   16kHz �ߴ���MPEG-4 celp�������뷽ʽ
	AUDIOTYPE_CELPplus,     ///5< Celp   16kHz �ߴ���MPEG-4 celp�������뷽ʽ��Celp x 2
	AUDIOTYPE_SPEEX,		///6< ����
	AUDIOTYPE_PCM,			///7< PCM��
	AUDIOTYPE_G711u ,		///8< G.711  8kHz  u�ɱ��뷽ʽ
	AUDIOTYPE_SPEEX_NB,		///9< Speex  8kHz  ���� ���뷽ʽ
	AUDIOTYPE_SPEEX_WB,		///10< Speex 16kHz ���� ���뷽ʽ
	AUDIOTYPE_SPEEX_UWB,	///11< Speex 32kHz ���� ���뷽ʽ
	AUDIOTYPE_G729,			///12< G729  8kHz  ���� ���뷽ʽ
	AUDIOTYPE_G729a,		///13< G729a 8kHz  ���� ���뷽ʽ
	AUDIOTYPE_G729plus,		///14< G729  8kHz  ����  ������뷽ʽ G729  x 2
	AUDIOTYPE_G729aplus,	///15< G729a 8kHz  ����  ������뷽ʽ G729a x 2
	AUDIOTYPE_ILBC,			///16< iLBC  8kHz  ����  30msģʽ ���뷽ʽ
	AUDIOTYPE_AMR_WB,       ///17< iLBC  16kHz ����
	AUDIOTYPE_NONE			///< δ����ı��뷽ʽ
} AUDIOTYPE;