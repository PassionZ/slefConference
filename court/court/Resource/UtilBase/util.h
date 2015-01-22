

#ifndef __UTIL_H_

char *ChangTextToUtf8(LPCTSTR szText,char* szTemp);				//�ı��ı���ʽΪUTf8
TCHAR *ChangUtf8ToText(const char* szText,TCHAR *szTemp);				//�ı��ı���ʽ��UTf8ת��

void ReadAudioSetting(byte &nAudioDevice, byte &nAudioCodec, bool &bAudioAEC, bool &bAudioAGC,bool &bNoiseReduction,bool &bMICReinforce);
void WriteAudioSetting(int nAudioDevice, byte nAudioCodec);
void ReadVideoSetting(
					  byte iUserCardNo,	 				 
					  byte&iUserCodeType,
					  byte&iUserDisplayType,
					  byte&iUserFrame,
					  bool&bUserPreventInterleaved,
					  byte&iUserMaxStream,
					  byte&iUserPicQuality,
					  byte&iVideoDriverIndex,
					  bool &denoise);

void WriteVideoSetting(
									byte iUserCardNo,	 				 
									byte iUserCodeType,
									byte iUserDisplayType,
									byte iUserFrame,
									bool bUserPreventInterleaved,
									byte iUserMaxStream,
									byte iUserPicQuality,
									byte iVideoDriverIndex,
									bool bdenoise);

void WriteErrorLogString(LPCTSTR lpcszSec,LPCTSTR lpcszKey,LPCTSTR lpcszValue);	//д��־�ļ�



HRGN BitmapToRegion (HBITMAP hBmp, COLORREF cTransparentColor);
CString GetFormatTime(unsigned long ulTime);
BOOL IsParmarter(const char *pBuffer, int len);
BOOL IsControlParmarter(const char *pBuffer, int len);
BOOL ReturnControlParmarter(const char *pBuffer, int len);
BOOL GetControlParmarter(const char *pBuffer, int len);
BOOL IsSetParameter(const char *pBuffer, int len);
BOOL IsAskParamter(const char *pBuffer, int len);
CString GetExePath();
BOOL IsP2PDataByType(const char *pBuffer, int len,const char *pType);

// Add Han Hua jie 2007/12/18  
int ReadSetupIniInt(LPCTSTR lpcszSec,LPCTSTR lpcszKey,int nDefValue);
void ReadSetupIniString(LPCTSTR lpcszSec,LPCTSTR lpcszKey,LPCTSTR lpcszDefValue,TCHAR* lpValue,int nMax);
int ReadConfigDefaultInt(LPCTSTR lpcszSec, LPCTSTR lpcszKey, int nDefValue);	//��ȡ Config.ini �ļ����Ĭ��ֵ

//  ����Ƶ�����򵼵ĸ߼�ѡ������
int  ReadEchoClearIntensity();
void ReadAudioAdvancedSetting(int &nBefore, int &nAfter, int &nNoiseSuppession);
void WriteAudioAdvancedSetting(int nBefore, int nAfter, int nNoiseSuppession, int nEchoClearIntensity);
// End Add

/*�ṩ�ĺ���ԭ��Ϊ��BOOL BlurFindStr(CString &strSource,CString &strFindCell)��ģ�����Һ�����
���ܣ��ж����ַ���strFindCel�ڲ���Ŀ���ַ���strSource���Ƿ���ڣ������ڷ���TRUE�����򷵻�FALSE��
˵����strSourceΪ�����ַ��������԰������Ļ�Ӣ����ĸ����strFindCellҲ��Ϊ���Ļ�Ӣ����ĸ��strFindCell�п�����
���ֵ���ĸ�ĵ�һ����ĸ��ʾ�����硰�Ͷ��֡������á�ldj�����档�������񡱿����á�djm�����棬��Ȼ������Ҳ��
������ĸ��һ����ĸ���棬ֱ��Ϊ�ú��֣����硰�Ͷ��֡������á��Ͷ�j�������⣬���ַ���strSource�б����Ͱ������
Ӣ���ַ���������Ҳ�᷵��TRUE���������������ӡ��Ͷ��֡����������������������ĺ�����ĸҲ�ǡ�ldj������Ҳ����
TRUE��*/
BOOL IsBlur(BYTE c1,BYTE c2,char c);
BOOL BlurFindStr(CString &strSource1,CString &strFindCell1);

int STRCMPVersion(CString strCMP1,CString strCMP2);			//�Ƚϰ汾��С 1:strCMP1>strCMP2 0:strCMP1==strCMP2 -1:strCMP1<strCMP2
void FindNuber(CString str, int fn[]);						//������ȡ���ŵ�������ȥ

// ��־���� Add HHJ 2009/08/05
CString GetLocalLogPath(DWORD dwFlag);	// �õ���־��·�� dwFlag: ��־��ʶ 0:ϵͳ 1: ����
void WriteLocalLogDate(CString strDate, DWORD dwFlag);	// д��־ dwFlag: ��־��ʶ 0:ϵͳ 1: ����

BOOL GetRecordFlag();
void SetRecordFlag(BOOL bRecordFlag);

bool LogToFile(TCHAR *fn, const char *data, size_t len);
int GetXPE();

#endif

