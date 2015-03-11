

#ifndef __UTIL_H_

char *ChangTextToUtf8(LPCTSTR szText,char* szTemp);				//改变文本格式为UTf8
TCHAR *ChangUtf8ToText(const char* szText,TCHAR *szTemp);				//改变文本格式由UTf8转回

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

void WriteErrorLogString(LPCTSTR lpcszSec,LPCTSTR lpcszKey,LPCTSTR lpcszValue);	//写日志文件



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
int ReadConfigDefaultInt(LPCTSTR lpcszSec, LPCTSTR lpcszKey, int nDefValue);	//读取 Config.ini 文件里的默认值

//  音视频调节向导的高级选项设置
int  ReadEchoClearIntensity();
void ReadAudioAdvancedSetting(int &nBefore, int &nAfter, int &nNoiseSuppession);
void WriteAudioAdvancedSetting(int nBefore, int nAfter, int nNoiseSuppession, int nEchoClearIntensity);
// End Add

/*提供的函数原型为：BOOL BlurFindStr(CString &strSource,CString &strFindCell)，模糊查找函数。
功能：判断子字符串strFindCel在查找目标字符串strSource中是否存在，若存在返回TRUE，否则返回FALSE。
说明：strSource为任意字符串，可以包含中文或英文字母，而strFindCell也可为中文或英文字母。strFindCell中可以用
汉字的声母的第一个字母表示，例如“劳动局”可以用“ldj”代替。“戴军民”可以用“djm”代替，当然，汉字也可
不用声母第一个字母代替，直接为该汉字，例如“劳动局”可以用“劳动j”。另外，若字符串strSource中本来就包含这个
英文字符串，则函数也会返回TRUE，或者如上面例子“劳动局”，若还有其他三个连续的汉字声母也是“ldj”，则也返回
TRUE。*/
BOOL IsBlur(BYTE c1,BYTE c2,char c);
BOOL BlurFindStr(CString &strSource1,CString &strFindCell1);

int STRCMPVersion(CString strCMP1,CString strCMP2);			//比较版本大小 1:strCMP1>strCMP2 0:strCMP1==strCMP2 -1:strCMP1<strCMP2
void FindNuber(CString str, int fn[]);						//将数据取出放到数组里去

// 日志处理 Add HHJ 2009/08/05
CString GetLocalLogPath(DWORD dwFlag);	// 得到日志的路径 dwFlag: 日志标识 0:系统 1: 会议
void WriteLocalLogDate(CString strDate, DWORD dwFlag);	// 写日志 dwFlag: 日志标识 0:系统 1: 会议

BOOL GetRecordFlag();
void SetRecordFlag(BOOL bRecordFlag);

bool LogToFile(TCHAR *fn, const char *data, size_t len);
int GetXPE();

#endif

