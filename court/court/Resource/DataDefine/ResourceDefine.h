            // ResourceDefine.h: interface for the CResourceDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEDEFINE_H__9ACA1E49_32C3_439B_BF25_3A372B7C5A38__INCLUDED_)
#define AFX_RESOURCEDEFINE_H__9ACA1E49_32C3_439B_BF25_3A372B7C5A38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define CONFERENCE_WIN_NUMBER 4

//////////////////////////////////////////////////////////////////////
// Enums
const int nSeperateWidth = 5;
// 屏幕号	Add Hhj		2008/01/17	 
typedef enum _eScreenNOType { ntSCREEN_ONE = 0, ntSCREEN_TWO, ntSCREEN_THREE, ntSCREEN_FOUR} ScreenNOType;

// 屏幕共享的选择状态  Add Hhj  2008/07/17
typedef enum ScreenNoteStatus {pointer, pen, middlepen, bigpen, erase} ScreenNoteStatus;	

// VideoShowMode Type		0:视觉比例切割显示 1:视觉比例填补显示 2:视频全景显示
typedef enum _eVideoShowModeType { ntVideoShowModeCut,ntVideoShowModeFill,ntVideoShowModeFull} VideoShowModeType;

// Screen Type
typedef enum _eScreenType { ntScreen4x3,ntScreen16x9,ntScreen16x10} ScreenType;

// Operate Type 0:按会议创建排序  1:按会议名称排序
typedef enum _eConfOperateType { ntOperateConfCreate = 0, ntOperateConfName } ConfOperateType;

// Operate Type 	1:按登陆排序 2:按名称排序 3:按帐号排序 
typedef enum _eOperateType { ntOperateLogin=1,ntOperateName,ntOperateAccounts} OperateType;

// FrameInfo Type
typedef enum _eFrameInfoType { ntFrameNull,ntVideoSound,ntWhiteBoard,ntScreen,ntTalkOver,ntMedio,ntFloatWin } FrameInfoType;

// Info Type
typedef enum _eInfoType { ntNull,ntMCU,ntUser } InfoType;

// Template Type
typedef enum _eTemplateType { ntTemplateNull,ntFree,ntNormal,nt16x9 } TemplateType;	

// StatusFlag Type		0:没登陆，1：已登陆，2：主持人，3：与会者，4：监控人员 
//5+0输入单元 5+1是输出单元 5+2是解码器 5+3拼接服务器PAD 5+4 法官 pad 5+5法官PC 5+6书记员PC 5+7被告与原告(公诉人和辩护人) 5+8法院合议庭
typedef enum _eStatusFlagType { ntStatusFlageNull,ntLogin,ntPresideLogin,ntConferenceUser,ntWatchUser,ntIM , } StatusFlagType;

// Popedom Type
typedef enum _ePopedomType { ntAllowKinescope,ntAllowControl,ntSetTalk,ntAllowUseWhiteBoard,ntAllowFloatDrag,ntAllowAskTalk, nScreenControl } PopedomType;

//////////////////////////////////////////////////////////////////////
// Struct
//Info
typedef struct _TInfo
{
	InfoType	_InfoType;				//信息类型	0:空 1:MCU 2:User
} TInfo;		//本机中

//User Info
typedef struct _TUserInfo  :public TInfo
{
	TCHAR		_strUserName[51];				//用户名
	TCHAR		_iUserID[21];					//用户ID
	unsigned __int32		_iSessionID;				//会话ID
	unsigned __int32			_iConferenceID;				//会议ID
	bool		_bPresentFlag;				//缺席标志 0:缺席1:在会
	byte		_iOnlineFlag;				//在线标志	0:不在线
														//1:在线无视音频
														//2:在线有视频无音频
														//3:在线无视频有音频
														//4:在线有视音频
	unsigned __int32			_iMCUID;				//登陆的MCU的id
	TCHAR		_strOnlineTime[15];						//登陆时间 格式：yyyymmddhhmmss
	byte		_iUserStatus;							//同StatusFlagType
	HTREEITEM	*_phRoot;
} TUserInfo;		//在与会者和非顶层MCU中的用户列表

// Video Card Info
typedef struct _TVideoCardInfo
{
	//本用户、主持人和在顶层MCU中记录
	byte			_iUserCardNo;				//用户视频卡号	0~12  199路卡为高清晰卡
	byte			_iUserCodeType;				//用户视频编码类型	4:X264 VBR(HP_VIDEO_CODEC_WMVA),
												//						3:X264 CBR(HP_VIDEO_CODEC_H264_VBR_HARDWARE),
												//						1:H263++ VBR(HP_VIDEO_CODEC_H263P)

	byte			_iUserDisplayType;			//用户分辨率	0:176*144
												//				1:242*176
												//				2:320*240
												//				3:352*288
												//				4:640*480
												//				5:704*576

	byte			_iUserFrame;				//用户帧率
	bool			_bUserPreventInterleaved;	//图象质量自动控制
	bool			_bUserRemoveConfusion;		//用户视频去噪							
	byte			_iUserMaxStream;			//用户视频模式 已没用
	byte			_iUserPicQuality;			//用户图像质量
	byte			_iVideoDriverIndex;			//视频设备号
	unsigned __int32	_iLockSessionID;		//被谁锁定视音频
} TVideoCardInfo;
typedef CTypedPtrArray<CPtrArray, TVideoCardInfo*> CTVideoCardInfoArray;

// Video Driver Info
typedef struct _TVideoDriverInfo
{
	//本用户、主持人和在顶层MCU中记录
	TCHAR			_strDriverName[256];				//设备名称
	bool			_bVideo_HDDevice;					//是否是高清卡
	bool			_bAcquisitionCardHaveSound;			//采集卡有声音采集
} TVideoDriverInfo;
typedef CTypedPtrArray<CPtrArray, TVideoDriverInfo*> CTVideoDriverInfoArray;

// Sound Driver Info
typedef struct _TSoundDriverInfo
{
	//本用户、主持人和在顶层MCU中记录
	TCHAR			_strDriverName[256];				//设备名称
} TSoundDriverInfo;
typedef CTypedPtrArray<CPtrArray, TSoundDriverInfo*> CTSoundDriverInfoArray;

// Media Info
typedef struct _TMediaInfo				//媒体格式结构
{
	byte		_iCodeType;				//编码类型
	byte		_iDisplayType;			//分辨率
	byte		_iFrame;				//帧率
	byte		_iMaxStream;			//最大码流
	byte		_iPicQuality;			//图像质量
	bool		_bAutoQuality;			//图象质量自动控制
}TMediaInfo;

//Conference User Info
typedef struct _TConferenceUserInfo	: public TUserInfo
{
	//本用户、主持人和在顶层MCU中记录
	byte			_iUserMicType;				//用户音频编码类型	0:MS G.723.1,2:WB,255:无音频
	bool			_bAllowKinescope;			//允许录像
	bool			_bAllowControl;				//允许云台控制
	byte			_iTalkControl;				//讨论控制	0:禁止讨论,1:允许讨论,2:向主持人讨论,3:向组讨论,4:向组和主持人讨论
	bool			_bAllowUseWhiteBoard;		//允许使用白板
	bool			_bAllowFloatDrag;			//允许浮动窗口拖动
	bool			_bAllowAskTalk;				//允许请求发言
	bool			_bAllowAskScreenControl;	//允许申请屏幕控制
	byte			_iSoundDriverIndex;			//音频设备号
	TCHAR			_strMediaFile[256];			//媒体文件路径
	TMediaInfo		*_ptMediaInfo;				//媒体格式结构
	byte			_iFrameResource;			//资源号	0:1屏资源，1:2屏资源

	CTVideoCardInfoArray _aVideoCardInfo;		//视频卡数据
	CTSoundDriverInfoArray _aSoundDriverInfo;	//声音驱动信息
	CTVideoDriverInfoArray _aVideoDriverInfo;	//视频驱动信息

	//本机内存
	bool		_bControl;					//是否显示控制栏	(不同步)
} TConferenceUserInfo;		//主持人和顶层MCU的用户列表，本用户

typedef struct _TConferenceUserADDInfo	: public TUserInfo
{
	//TConferenceUserInfo userinfo;
	
		bool bControl ;
		 int nPart ;
		 int nAll ;
		 int ndefValue ;
		 int nPersonType ;


} TConferenceUserAddInfo;		//主持人和顶层MCU的用户列表，本用户

// Conference Base Info
typedef struct _TConferenceBaseInfo
{
	unsigned __int32			_iConferenceID;	//会议ID				
	TCHAR		_strConferenceName[61];			//会议名称
	TCHAR		_strConferenceTopic[255];		//会议主题
} TConferenceBaseInfo;

//会议提醒状态
typedef struct _TConferenceNotifyState
{
    TConferenceBaseInfo *pInfo;
    unsigned nNotifyCount;
}TConferenceNotifyState;

// VideoSound Info
typedef struct _TVideoSoundInfo
{
	byte			_iUserCardNo;				//用户视频卡号	0~12
	bool			_bSound;					//是否广播音频
	bool			_bVideo;					//是否广播视频
} TVideoSoundInfo;		//在MCU中记录

// Win Info
typedef struct _TWinInfo
{
	FrameInfoType			_iFrameInfoType;	//框上显示的是哪种信息
	unsigned __int32		_iSessionID;		//会话ID
	TVideoSoundInfo*		_ptVideoSoundInfo;	//框上显示的是视音频，有视音频信息
	
	//在本机中有
	CWnd*				_pdDialogInf;		//对话框指针
	CRect					_rcScreen;			//窗口的坐标
} TWinInfo;		//在MCU中记录
typedef CTypedPtrArray<CPtrArray, TWinInfo*> CTWinInfoArray;

//// WhiteBoard Info
//typedef struct _TWhiteBoardInfo
//{
//	byte			_iWinNo;					//屏号
//	byte			_iFrameNo;					//第几个框
//} TWhiteBoardInfo;		//在MCU中记录

//Screen Info
//typedef struct _TScreenInfo
//{
//	unsigned __int32		_iSessionID;		//会话ID
//	byte			_iWinNo;					//屏号
//	byte			_iFrameNo;					//第几个框
//} TScreenInfo;			//在MCU中记录

//TalkOver Info
//typedef struct _TTalkOverInfo
//{
//	byte			_iWinNo;					//屏号
//	byte			_iFrameNo;					//第几个框
//} TTalkOverInfo;			//在MCU中记录

//Medio Info
//typedef struct _TMedioInfo
//{
//	unsigned __int32		_iSessionID;		//会话ID
//	byte			_iWinNo;					//屏号
//	byte			_iFrameNo;					//第几个框
//} TMedioInfo;			//在MCU中记录


//Prolocutor Info
//在本机中记录
typedef struct _TProlocutorInfo
{
	TConferenceUserInfo	*_pConferenceUserInfo;	//发言人信息
	BOOL			_bIsProlocutor;				//是否是发言人
} TProlocutorInfo;
typedef CTypedPtrArray<CPtrArray, TProlocutorInfo*> CTProlocutorInfoArray;

// Conference Info
typedef struct _TConferenceInfo : public TConferenceBaseInfo
{
	unsigned __int16			_iBandwidth;	//限制的带宽
	byte			_iOneWinClass;				//1号屏种类	1，2，3第几个种类 按TemplateType
	bool			_bOneWinTemplate;			//1号屏模板模式	0：不显示所有,1：为显示所有
	byte			_iOneWinNumber;				//1号屏数量	
	byte			_iOneWinType;				//1号屏类型
	byte			_iTwoWinClass;				//2号屏种类	1，2，3第几个种类 按TemplateType
	bool			_bTwoWinTemplate;			//2号屏模板模式	0：不显示所有,1：为显示所有
	byte			_iTwoWinNumber;				//2号屏数量
	byte			_iTwoWinType;				//2号屏类型

	//在MCU中记录
	unsigned __int32			_iSpokesmanID;				//演讲人ID	0：无演讲人
	byte		_iFrameNo;					//显示几号屏
	bool		_bAllowKinescope;			//允许录像
	bool		_bAllowControl;				//允许控制
	byte		_iTalkControl;				//讨论控制	0:禁止讨论,1:允许讨论,2:向主持人讨论,4:向组和主持人讨论
	bool		_bAllowUseWhiteBoard;		//允许使用白板
	bool		_bAllowFloatDrag;			//允许浮动窗口拖动
	bool		_bAllowAskTalk;				//允许请求发言
	bool		_bAllowAskScreenControl;	//允许申请屏幕控制
	TCHAR		_strAfficheSet[30 + 8 + 256];		//字幕设置(字体 + 颜色 + 文本信息)
	bool		_bAfficheFlag;				//字幕发布
	CTWinInfoArray	*_aWinInfo[CONFERENCE_WIN_NUMBER];				//会议窗口信息
	bool		_bConferenceTopicFlag;		//会议标题发布
	unsigned __int32		_iFloatWinUserSessionID;				//浮动窗用户会话ID 0：无浮动窗
	byte		_iUserCardNo;					//浮动窗用户卡号
	unsigned __int16		_iFloatWinRect[6];		//浮动窗坐标
	bool		_bWatchUserControl;			//监控人员控制权限		监控人员才有
	unsigned __int32 _iFullScreenSessionID;		//共享屏幕全屏人员ID
	bool		_bIsAllowInConference;			//是否允许不在线人员进入会议
	bool		_bCalling;						//点名
	byte		_iLinkage;						//屏幕联动	0:不联动 1:联动

	unsigned __int32 _iPresentCount;			//会议在线人数
	unsigned __int32 _iConferenceUserCount;		//会议总人数

	byte			_iWinClass[CONFERENCE_WIN_NUMBER];				//屏种类	1，2，3第几个种类 按TemplateType
	bool			_bWinTemplate[CONFERENCE_WIN_NUMBER];			//屏模板模式	0：不显示所有,1：为显示所有
	byte			_iWinNumber[CONFERENCE_WIN_NUMBER];				//屏数量	
	byte			_iWinType[CONFERENCE_WIN_NUMBER];				//屏类型
	//主持人本地
//	CTProlocutorInfoArray	_aAskSpeakUserInfo;	//请求发言的信息
} TConferenceInfo;

// MCU Info
typedef struct _TMCUInfo:public TInfo
{
	unsigned __int32			_iMCUID;					//MCUID
	TCHAR		_strMCUName[31];				//MCU名称
	TCHAR		_strMCUIPAddress[15];			//IP地址
	unsigned __int32			_iUPMCUid;					//上级MCUid
	HTREEITEM	*_phRoot;
} TMCUInfo;

//Repetition User Info
//typedef struct _TRepetitionUserInfo
//{
//	TConferenceUserInfo	*_pConferenceUserInfo;	//被轮循的用户指针
//	bool		_bRepetitionDegree;			//本次已被轮循过
//} TRepetitionUserInfo;			//主持人本地

//  PreSetting Info
typedef struct _TPreSettingInfo
{
	bool		_bUseFlag;			//是否启用
	byte		_iCodeType;			//编码类型
	byte		_iDisplayType;		//标清分辨率
	byte		_iFrame;			//帧率
	byte		_iVideoMode;		//视频模式
	byte		_iPicQuality;		//视频码流
	byte		_iHDDisplayType;	//高清分辨率
	bool		_bAutoPicQuality;	//图像质量自动控制	//modified by lzl,2008.10.29
}TPreSettingInfo;
typedef CTypedPtrArray<CPtrArray, TPreSettingInfo*> CTPreSettingInfoArray;	

// Preside User Info
typedef struct _TPresideUserInfo
{
	//在本地保存的数据
	byte			_iRepetitionUserNumber;		//轮循用户数
	byte			_iRepetitionTime;			//轮循时间
	byte			_iWhatWinRepetition;		//轮循的屏幕号
	bool			_bRepetitionSoundFlag;		//轮循时静音标志
	byte			_iBroadcast;				//轮循标志 0: 不轮循 1: 轮循时广播 2: 轮循时单接(不广播)

	bool			_bConferenceSynchronizationFlag;	//会议同步
	bool			_bVASynchronizationFlag;			//视音频同步
	bool			_bWinLayoutSynchronizationFlag;		//窗口布局同步
//	bool			_bConferencePreSettingFlag;	//是否使用会议预设置

    bool        _bVoiceInspirit;            //声控切换
	byte		_iInspiritTimeSegment;		//每隔几秒为一个声控切换时间段
	byte		_iInspiritTimeSpeak;		//每个声控切换时几秒决定谁发言
	
	//bool		_bBigWinFlag;				//大窗口设置标志
	//bool		_bLittleWinFlag;			//小画面设置标志
	bool		_bUp9WinFlag;				//大于9画面设置标志
	bool		_bDown9WinFlag;				//小于9画面设置标志
	//byte		_iBigWinCodeType;			//大窗口编码类型
	//byte		_iBigWinDisplayType;		//大窗口分辨率
	//byte		_iBigWinFrame;				//大窗口帧率
	//bool		_bBigWinPreventInterleaved;	//大窗口防止隔行扫描
	//byte		_iBigWinMaxStream;			//大窗口最大码流
	//byte		_iBigWinPicQuality;			//大窗口图像质量
	//byte		_iLittleWinCodeType;		//小窗口编码类型
	//byte		_iLittleWinDisplayType;		//小窗口分辨率
	//byte		_iLittleWinFrame;			//小窗口帧率
	//bool		_bLittleWinPreventInterleaved;	//小窗口防止隔行扫描
	//byte		_iLittleWinMaxStream;		//小窗口最大码流
    //byte		_iLittleWinPicQuality;		//小窗口图像质量
	byte		_iDown9WinCodeType;			//小于9窗口编码类型
	byte		_iDown9WinDisplayType;		//小于9窗口分辨率
	byte		_iDown9WinFrame;			//小于9窗口帧率
	bool		_bDown9WinPreventInterleaved;	//小于9窗口防止隔行扫描
	byte		_iDown9WinMaxStream;		//小于9窗口最大码流
	byte		_iDown9WinPicQuality;		//小于9窗口图像质量
	byte		_iUp9WinCodeType;			//大于9窗口编码类型
	byte		_iUp9WinDisplayType;		//大于9窗口分辨率
	byte		_iUp9WinFrame;				//大于9窗口帧率
	bool		_bUp9WinPreventInterleaved;	//大于9窗口防止隔行扫描
	byte		_iUp9WinMaxStream;			//大于9窗口最大码流
	byte		_iUp9WinPicQuality;			//大于9窗口图像质量

	bool		_bAutoPicQuality;			//图象质量自动控制 lzl add 2008.10.29

	CTPreSettingInfoArray	_aPreSettingInfoArray;		//预设置参数数组
	CTWinInfoArray	_aVideoInfoArray;		//记录本地接收窗口的信息

} TPresideUserInfo;


// Local User Info
typedef struct _TLocalUserInfo
{
	////在本地保存的数据	
//	bool		_bShowMainWin;				//当登录时，显示主窗口
//	TCHAR		_strPicDir;					//图像路径
	BOOL		_bConferenceNotify;			//是否会议提醒
	int			_iConferenceMin;			//每个会议每隔几分钟提醒一次
	int			_iConferenceAwakeNumber;	//每个会议提醒几次
	BOOL		_bLogAwake;					//在每次登录时提醒
	int			_iConferenceInviteFlag;		//会议邀请方式:
											// 0: 拒绝所有邀请
											// 1: 弹出对话框提示
											// 2: 自动进入会议
	BOOL		_bExitAndJoinNewMeet;		//退出当前会议, 并进入新的会议.
	int			_iCallingCloseSecond;       //点名结束时间限制秒钟
	BOOL		_bAutoCalling;				//是否启动会议自动点名
	int			_iAutoCallingMinSect;		//自动点名时间段分钟
	unsigned __int32		_iCallingSessionID;	//点名者会话ID
	BOOL		_bRunControlerHook;			//运行控制器
	BOOL		_bUseVideoSoundSynchronization;		//启用唇音同步
	int			_iVideoSoundSynchronizationTime;	//视音频唇音同步缓冲池时间的大小，最小10秒，最大5分钟 单位秒
	BOOL		_bToAllConferenceUserFullScreen;	//视频窗口最大化通知所有成员
	ScreenType	_iScreenType[CONFERENCE_WIN_NUMBER];					//屏的类型
	OperateType	_iOperateType;				//按什么方法排序 
	VideoShowModeType _iVideoShowMode;		//视频显示模式
	BOOL		_bScreenShowMode[CONFERENCE_WIN_NUMBER];			//屏幕显示模式
	int			_iShowUserState;			//显示的人员状态  0:显示所有人员 1:只显示在线人员 2:只显示在会人员
	
	//本机内存临时数据
	BOOL		_bShowTitleBar;				//为定制，在“操作”菜单中增加“显示标题栏”，且默认选中
											//add by lzl,2008.10.20

	BOOL		_bShowCodeFlow;				//显示码流
	CString		_strPassword;				//密码
	TCHAR		_strMCUIPAddress[256];		//IP地址
	unsigned __int16 _iMCUPort;				//使用的端口
	int			_iStatusFlag;				//身份标志	0:没登陆，1：已登陆，2：主持人，3：与会者，4监控人员
	BOOL		_bVideoOrder;				//视频预置
	BOOL		_bVideoTCPorUDP;			//视频传输方式TCP/UDP  1:TCP 0:UDP
	BOOL		_bShowHaveUserMCU;			//显示有人的MCU节点
	CString		_strSearchUser;				//查找的人的字段
	TConferenceUserInfo	*_pUserInfo;		//本用户指针
	TConferenceInfo		*_pConferenceInfo;	//进入的会议
	TPresideUserInfo	*_pPresideUserInfo;	//主持人有此连接
} TLocalUserInfo;

//TalkOver Data Info
typedef struct _TTalkOverDataInfo
{
	unsigned __int32		_iSessionID;	//用户ID
	TCHAR		_cTalkOver_Data[256];			//讨论的信息
} TTalkOverDataInfo;			//在MCU中记录

//视频COM参数
struct ComParameter
{
	int nType;
	int nComPort;
	int nSerialNumber;
};

// VOD Info
typedef struct _TVODInfo
{
	TCHAR		_strVODName[90];									//VOD名称
	TCHAR		_strVODIPAddress[45];								//IP地址
} TVODInfo;


typedef CTypedPtrArray<CPtrArray, TTalkOverDataInfo*> CTTalkOverDataInfoArray;

typedef CTypedPtrArray<CPtrArray, TConferenceBaseInfo*> CTConferenceBaseInfoArray;
typedef CTypedPtrArray<CPtrArray, TConferenceInfo*> CTConferenceInfoArray;
typedef CTypedPtrArray<CPtrArray, TMCUInfo*> CTMCUInfoArray;
typedef CTypedPtrArray<CPtrArray, TUserInfo*> CTUserInfoArray;
typedef CTypedPtrArray<CPtrArray, TConferenceUserInfo*> CTConferenceUserInfoArray;
typedef CTypedPtrArray<CPtrArray, TConferenceNotifyState *> CTConferenceNotifyStateArray;
typedef CTypedPtrArray<CPtrArray, TVODInfo *> CTVODInfoArray;

//
TVideoCardInfo *GetVideoCardSetting(CTVideoCardInfoArray &array, int nCardNo);

typedef struct _TSelectedUserInfo
{
	TConferenceUserInfo*	_ptConferenceUserInfo;		// 选中的人员信息				
	byte					_iSeleCardNo;				// 选中的人员信息的卡号	
} TSelectedUserInfo;
typedef CTypedPtrArray<CPtrArray, TSelectedUserInfo*> CTSelectedUserInfoArray;


//视频窗口透明标题栏位置枚举类型声明 add lzl 2008-9-26
typedef enum _ETitleBarPos { TOP_LEFT=0,BOTOM_LEFT} ETitleBarPos;

#endif // !defined(AFX_RESOURCEDEFINE_H__9ACA1E49_32C3_439B_BF25_3A372B7C5A38__INCLUDED_)
