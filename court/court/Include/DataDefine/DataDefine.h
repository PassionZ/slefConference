#ifndef __DATADEFINE_H
#define __DATADEFINE_H


#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "../libHPBaseclass/ListPtr.h"

using namespace std;

#define SYSTEM32
//#define SYSTEM16
//#define SYSTEM64

//#define NETTVANDBROADCAST 

#ifdef SYSTEM32							// 32位系统
typedef unsigned short	UINT16;			// 16位无符号整数（短整形）
typedef unsigned int	UINT32;			// 32位无符号整数（整形）
typedef unsigned long	UNLONG32;		// 32位无符号整数, 有些机器可能是64位（长整形）

#else //if SYSTEM16						// 16位系统
typedef unsigned short	UINT8;			// 8位无符号整数（短整形）
typedef unsigned int	UINT16;			// 16位无符号整数（整形）
typedef unsigned long	UINT32;			// 32位无符号整数, 有些机器可能是64位（长整形）

//#else if SYSTEM64						// 64位系统
//typedef unsigned short	UINT32;		// 32位无符号整数（短整形）？
//typedef unsigned int		UINT64;		// 64位无符号整数（整形）
//typedef unsigned long		ULONG64;	// 64位无符号整数, 有些机器可能是64位（长整形）？

#endif

//#ifndef WIN32
//typedef UINT32 /*unsigned __int32*/UINT32;
typedef unsigned char byte;

//#endif

typedef UINT32* UINT32PTR;
typedef std::string STRING;
//typedef std::list<void*> LISTPTR;
typedef std::map<UINT32,void*> UINT32MAPPTR;

//////////////////////////////////////////////////////////////////////////
// add by davy 2006-1-4

// FrameInfo Type
typedef enum _EFrameInfoType { _eFrameNull=0,_eFrameAudioVideo,_eFrameWhiteBoard,_eFrameDesktop,_eFrameTalkOver,_eFrameFile,_eFrameMedio } EFrameInfoType;

typedef enum _EInfoType { _eInfoNull=0,_eTopMcu,_eSonMcu, _eUser, _eServerDog } EInfoType;

typedef enum _ETalkType { _eTalkNull=0,_eTalkPublic,_eTalkPresider,_eTalkGroup, _eTalkPresiderGroup} ETalkType;


//Info
typedef struct _tInfo
{
	EInfoType	_InfoType;				//信息类型	0:空 1:TOPMCU 2:SONMCU 3:User
} tInfo;		

//User Info
typedef struct _tUserInfo  :public tInfo
{
	//在与会者和非顶层MCU中的用户列表
	char		_strUserName[150];						//用户名
	char		_iUserID[60];							//用户ID
	/*unsigned __int32*/UINT32			_iSessionID;	//会话ID
	/*unsigned __int32*/UINT32			_iConferenceID;	//会议ID
	bool		_bPresentFlag;							//缺席标志  0:缺席1:在会
	byte		_iOnlineFlag;							//在线标志	
														//0:不在线
														//1:在线无视音频
														//2:在线有视频无音频
														//3:在线无视频有音频
														//4:在线有视音频
	/*unsigned __int32*/UINT32			_iMCUID;		//登陆的MCU的id
	char		_strOnlineTime[42];						//登陆时间 格式：yyyymmddhhmmss
//	HTREEITEM	*_phRoot;

	//bool operator < (const _tUserInfo &m)const {
	//	return atol(_strOnlineTime)< atol(m._strOnlineTime);
	//}

	byte		_iDegreeFlag;							//用户身份标志 0:xxx 1:xxx 2:主持人 3:与会者 4:监控人员
	bool		_bAllowEnterConference;					//是否允许进入会议

#ifdef NETTVANDBROADCAST
	//网络电视
	byte		_iLevel;
#endif
} tUserInfo;		

// Video Card Info
typedef struct _tVideoCardInfo
{
	//本用户、主持人和在顶层MCU中记录
	byte			_iUserCardNo;				//用户视频卡号	1~13
	byte			_iUserCodeType;				//用户视频编码类型	
												//4:X264 VBR(AVVIDEO_CODEC_WMVA),
												//3:X264 CBR(AVVIDEO_CODEC_WMV9),
												//1:H263++ VBR(AVVIDEO_CODEC_H263P)
	byte			_iUserDisplayType;			//用户分辨率	0:176*144
												//				1:242*176
												//				2:320*240
												//				3:352*288
												//				4:640*480
												//				5:704*576
	byte			_iUserFrame;				//用户帧率	5，10，15，20，25，30
	bool			_bUserPreventInterleaved;	//用户防止隔行扫描	
	byte			_iUserMaxStream;			//用户最大码流	0:0,1:64,2:128,3:384, 4:512,5:768,6:1024,7:2048
	byte			_iUserPicQuality;			//用户图像质量	0:64,1:128,2:256,3:512,4:1024,5:2048

	// add
	//////////////////////////////////////////////////////////////////////////
	byte			_iVideoDriverIndex;			//视频设备号
	//////////////////////////////////////////////////////////////////////////

	bool			_bUserRemoveConfusion;		//用户视频去噪
	
} tVideoCardInfo;
//typedef CTypedPtrArray<CPtrArray, tVideoCardInfo*> CTVideoCardInfoArray;
typedef /*list<tVideoCardInfo*>*/ListPtr ListtVideoCardInfo;

// add
//////////////////////////////////////////////////////////////////////////
// Video Driver Info
typedef struct _tVideoDriverInfo
{
	//本用户、主持人和在顶层MCU中记录
	char			_strDriverName[1024];				//设备名称
	bool			_bHDVideo;							//是否高清设备
	bool			_bHaveSound;						//采集卡有声音采集
} tVideoDriverInfo;
//typedef CTypedPtrArray<CPtrArray, TVideoDriverInfo*> CTVideoDriverInfoArray;
typedef /*list<tVideoDriverInfo*>*/ListPtr ListtVideoDriverInfo;

// Sound Driver Info
typedef struct _tSoundDriverInfo
{
	//本用户、主持人和在顶层MCU中记录
	char			_strDriverName[1024];				//设备名称
} tSoundDriverInfo;
//typedef CTypedPtrArray<CPtrArray, TSoundDriverInfo*> CTSoundDriverInfoArray;
typedef /*list<tSoundDriverInfo*>*/ListPtr ListtSoundDriverInfo;
//////////////////////////////////////////////////////////////////////////

//Conference User Info
typedef struct _tConferenceUserInfo	: public tUserInfo
{
	//本用户、主持人和在顶层MCU中记录
	byte			_iUserMicType;									//用户音频编码类型	0:MS G.723.1,2:WB,255:无音频
	bool			_bAllowKinescope;								//允许录像
	bool			_bAllowControl;									//允许控制
	byte			_iTalkControl;									//讨论控制	0:禁止讨论,1:允许讨论,2:向主持人讨论,3:向组内成员讨论
	//byte			_iUserCardNumber;								//用户有几个视频卡	0：无视频
	/*CTVideoCardInfoArray*/ListtVideoCardInfo _aVideoCardInfo;		//视频卡数据

	// add
	//////////////////////////////////////////////////////////////////////////
	byte			_iSoundDriverIndex;			//音频设备号
	bool			_bAllowUseWhiteBoard;		//允许使用白板
	/*CTSoundDriverInfoArray*/ListtSoundDriverInfo _aSoundDriverInfo;	//视频驱动信息
	/*CTVideoDriverInfoArray*/ListtVideoDriverInfo _aVideoDriverInfo;	//声音驱动信息
	//////////////////////////////////////////////////////////////////////////

	//bool operator < (const _tConferenceUserInfo &m)const {
	//	return atol(_strOnlineTime)< atol(m._strOnlineTime);
	//}

	bool		_bAllowEnterConference;										//是否允许进入会议

	bool		_bAskToProlocutor;											//是否显示申请发言人
	bool		_bFloatWin;													//是否拉申浮动窗口
	//add by davy 20071218
	bool		_bScreenControl;											//是否允许屏幕控制
				
} tConferenceUserInfo;		//主持人和顶层MCU的用户列表，本用户

// Conference Base Info
typedef struct _tConferenceBaseInfo
{
	/*unsigned __int32*/UINT32			_iConferenceID;	//会议ID				
	char		_strConferenceName[180];				//会议名称
	char		_strConferenceTopic[765];				//会议主题

#ifdef NETTVANDBROADCAST
	//网络电视及视频直播
	byte		_iAnonymous;							//是否允许匿名（0不允许，1允许）
	byte		_iActivate;
#endif

} tConferenceBaseInfo;

//add by davy 2008-2-22
typedef struct _tConferenceCount
{
	UINT32			_iConferenceID;	//会议ID		
	UINT16			_iCount;		//在线会议成员人数
	UINT16			_iTotalCount;	//会议成员人数
} tConferenceCount;
typedef ListPtr ListtConferenceCount;

// VideoSound Info
typedef struct _tVideoSoundInfo
{
	//在MCU中记录
	byte			_iUserCardNo;				//用户视频卡号	1~13
	bool			_bSound;					//是否有音频
	bool			_bVideo;					//是否有视频

	// add
	//////////////////////////////////////////////////////////////////////////
	/*unsigned __int32*/UINT32		_iSoundChannelID;		//音频通道号
	/*unsigned __int32*/UINT32		_iVideoChannelID;		//视频通道号
	//////////////////////////////////////////////////////////////////////////
	
} tVideoSoundInfo;		

// Win Info
typedef struct _tWinInfo
{
	//在MCU中记录
	EFrameInfoType			_iFrameInfoType;			//框上显示的是哪种信息
	/*unsigned __int32*/UINT32		_iSessionID;		//会话ID
	tVideoSoundInfo*		_ptVideoSoundInfo;			//框上显示的是视音频，有视音频信息

	// add
	//////////////////////////////////////////////////////////////////////////
	/*unsigned __int32*/UINT32		_iChannelID;		//通道号
	//////////////////////////////////////////////////////////////////////////

	//屏幕资源
	byte	_iScreenResourceID;
} tWinInfo;		
//typedef CTypedPtrArray<CPtrArray, tWinInfo*> CTWinInfoArray;
typedef /*list<tWinInfo*>*/ListPtr ListtWinInfo;

//Ask Speak User Info
//在MCU中记录
//typedef CTypedPtrArray<CPtrArray, tConferenceUserInfo*> CTAskSpeakUserInfoArray;
//typedef /*list<tConferenceUserInfo*>*/ListPtr ListtConferenceUserInfo;

typedef struct _tProlocutorInfo
{
	UINT32 _iSessionID; // 申请发言人
	byte   _iStatus;	// 发言人状态 0：取消发言，2：设为发言
} tProlocutorInfo;
typedef /*list<tProlocutorInfo*>*/ListPtr ListtProlocutorInfo;

//屏幕资源
typedef struct _tScreenResourceInfo
{
	byte			_iWinClass;						//种类	1，2，3第几个种类 按TemplateType
	bool			_bWinTemplate;					//模板模式	0：不显示所有,1：为显示所有
	byte			_iWinNumber;					//数量	
	byte			_iWinType;						//类型

	ListtWinInfo    _aWinInfo;						//窗口信息
} tScreenResourceInfo;
typedef ListPtr ListtScreenResourceInfo;

typedef struct _tScreenResource
{
	byte			_iFrameNo;						//显示几号屏
	bool			_bInterLock;					//是否与其他屏幕资源联动
	ListtScreenResourceInfo _aScreenResourceInfo;	//屏幕资源详细信息
} tScreenResource;
typedef ListPtr ListtScreenResource;

// Conference Info
typedef struct _tConferenceInfo : public tConferenceBaseInfo
{
	/*unsigned __int16*/UINT16			_iBandwidth;	//限制的带宽
	byte			_iOneWinClass;						//1号屏种类	1，2，3第几个种类 按TemplateType
	bool			_bOneWinTemplate;					//1号屏模板模式	0：不显示所有,1：为显示所有
	byte			_iOneWinNumber;						//1号屏数量	
	byte			_iOneWinType;						//1号屏类型
	byte			_iTwoWinClass;						//2号屏种类	1，2第几个种类	按TemplateType
	bool			_bTwoWinTemplate;					//2号屏模板模式	0：不显示所有,1：为显示所有
	byte			_iTwoWinNumber;						//2号屏数量
	byte			_iTwoWinType;						//2号屏类型

	//在MCU中记录
	/*unsigned __int32*/UINT32			_iSpokesmanID;			//发言人ID	0：无演讲人
	bool		_bAllowKinescope;								//允许录像
	bool		_bAllowControl;									//允许控制
//	bool		_bBeginRepetition;								//开始轮循
	byte		_iTalkControl;									//讨论控制	0:禁止讨论,1:允许讨论,2:向主持人讨论
	char		_strAfficheSet[768];							//公告设置
	bool		_bAfficheFlag;									//公告发布
//	bool		_bWhiteBoard;									//会议白板标志
	/*CTWinInfoArray*/ListtWinInfo	_aOneWinInfo;				//会议1窗口信息
	/*CTWinInfoArray*/ListtWinInfo	_aTwoWinInfo;				//会议2窗口信息
//	byte		_iAskSpeakUserNumber;							//有几个人请求发言
//	/*CTAskSpeakUserInfoArray*/ListtConferenceUserInfo	_aAskSpeakUserInfo;	//请求发言的信息

	// add
	//////////////////////////////////////////////////////////////////////////
	byte		_iFrameNo;					//显示几号屏
	bool		_bAllowUseWhiteBoard;		//允许使用白板
	//////////////////////////////////////////////////////////////////////////

	/*unsigned __int32*/UINT32		_iFloatWinUserSessionID;				//浮动窗用户会话ID 0：无浮动窗
	byte		_iUserCardNo;												//浮动窗用户卡号
	/*unsigned __int32*/UINT16		_iFloatWinRect[6];						//浮动窗坐标

	/*unsigned __int32*/UINT32		_iWatchUserID;							//监控人员ID
	bool		_bWatchUserControl;											//监控人员控制权限		监控人员才有

	/*unsigned __int32*/UINT32 _iFullScreenSessionID;						//共享屏幕全屏人员ID

	bool		_bConferenceTopic;											//是否显示会议标题

	bool		_bAllowEnterConference;										//是否允许进入会议

	bool		_bAskToProlocutor;											//是否显示申请发言人
	bool		_bFloatWin;													//是否拉申浮动窗口
	//add by davy 20071218
	bool		_bScreenControl;											//是否允许屏幕控制
	
	ListtProlocutorInfo	_aProlocutorInfo;									//申请发言人列表

	//add by davy 2007-06-18
	UINT32			_iCallID;												//点名人ID

#ifdef NETTVANDBROADCAST 
	byte		_iLevel;		//网络电视
	UINT32		_iSessionID;	//电视机

	byte		_iChannelID;	//电视频道
#endif

	//屏幕资源
	ListtScreenResource _aScreenResource;

} tConferenceInfo;

// MCU Info
typedef struct _tMCUInfo:public tInfo
{
	/*unsigned __int32*/UINT32			_iMCUID;					//MCUID
	char		_strMCUName[90];									//MCU名称
	char		_strMCUIPAddress[45];								//IP地址
	/*unsigned __int32*/UINT32			_iUPMCUid;					//上级MCUid
//	HTREEITEM	*_phRoot;

	byte		_ucStatus;
} tMCUInfo;

// VOD Info
typedef struct _tVODInfo
{
	char		_strVODName[90];									//VOD名称
	char		_strVODIPAddress[45];								//IP地址
} tVODInfo;

//TalkOver Data Info
typedef struct _tTalkOverDataInfo
{
	/*unsigned __int32*/UINT32		_iSessionID;	//用户ID
	char		_cTalkOver_Data[768];				//讨论的信息
} tTalkOverDataInfo;			//在MCU中记录
//typedef CTypedPtrArray<CPtrArray, TTalkOverDataInfo*> CTTalkOverDataInfoArray;
//
//typedef CTypedPtrArray<CPtrArray, TConferenceBaseInfo*> CTConferenceBaseInfoArray;
//typedef CTypedPtrArray<CPtrArray, TConferenceInfo*> CTConferenceInfoArray;
////typedef CTypedPtrArray<CPtrArray, TRepetitionUserInfo*> CTRepetitionUserInfoArray;
//typedef CTypedPtrArray<CPtrArray, TMCUInfo*> CTMCUInfoArray;
//typedef CTypedPtrArray<CPtrArray, TUserInfo*> CTUserInfoArray;
//typedef CTypedPtrArray<CPtrArray, TConferenceUserInfo*> CTConferenceUserInfoArray;

typedef /*list<tTalkOverDataInfo*>*/ListPtr ListtTalkOverDataInfo;
typedef /*list<tConferenceBaseInfo*>*/ListPtr ListtConferenceBaseInfo;
typedef /*list<tConferenceInfo*>*/ListPtr ListtConferenceInfo;
typedef /*list<tMCUInfo*>*/ListPtr ListtMCUInfo;
typedef /*list<tUserInfo*>*/ListPtr ListtUserInfo;
typedef /*list<tConferenceUserInfo*>*/ListPtr ListtConferenceUserInfo;


typedef struct _tTempletInfo 
{
	byte			_iTempletClass;						//模板种类	1，2，3第几个种类 按TemplateType
	//bool			_bTempletTemplate;					//模板模式	0：不显示所有,1：为显示所有
	byte			_iTempletNumber;					//模板数量	
	byte			_iTempletType;						//模板类型
	byte			_iTempletWinNumber;					//模板窗口数量
} tTempletInfo;
typedef /*list<tTempletInfo*>*/ListPtr ListtTempletInfo;

// rsftp
typedef struct _tFileInfo 
{
	UINT32	_iFileHandle;			// file IO handle
	std::string	_strFileName;		// file name
	UINT32	_iFileTotalLength;		// file total length
	bool	_bCompleted;			// is completed? is equal _iFileTotalLength = filelen(_iFileHandle)
	UINT32	_iCurFileLength;		// file current length
	UINT32	_iConferenceID;			
} tFileInfo;
typedef /*list<tFileInfo*>*/ListPtr ListtFileInfo;

// Channel Info
typedef struct _tChannelInfo:public tInfo
{
	UINT32		_iTelevisionID;			//电视ID
	UINT32		_iChannelID;			//电视频道ID
	char		_cChannelName[20];		//电视频道名称
	char		_cChannelMark[50];		//电视频道描述
	byte		_iActiveStatus;			//频道当前状态 
} tChannelInfo;
typedef /*list<tChannelInfo*>*/ListPtr ListtChannelInfo;

#endif

