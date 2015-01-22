// IVideoSystem.h

#if !defined(_VIDEOSYSTEM_H__20091124_092009__INCLUDED_HHJ_)
#define _VIDEOSYSTEM_H__20091124_092009__INCLUDED_HHJ_

// **************************************************************
//  VideoSystem Interface   version:  1.0   ·  date: 11/24/2009
//  -------------------------------------------------------------
//  视频会议系统对外接口
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
//                                                 By:    HHJ
// ***************************************************************


#define  MY_VIDEO_CONFERENCE_SYSTEM_MSG   WM_USER + 14678
typedef enum _ewParamDate {enSystemQuit = 0/*系统退出*/, enExitConf} eWPARAM_DATE;


#ifdef _VIDEOSYSTEM_CONFERENCE_HHJ_
#define DllExport_VIDEO_CONF_SYSTEM __declspec(dllexport)
#else
#define DllExport_VIDEO_CONF_SYSTEM __declspec(dllimport) 
#endif



//////////////////////////////////////////////////////////////////////////
//    视频会议系统回调通知接口， 需继承
//////////////////////////////////////////////////////////////////////////
interface IVideoConfSystemNotify
{
public:
	IVideoConfSystemNotify(){};
	virtual ~IVideoConfSystemNotify(){};

	// 得到用户登录MCU的信息
	// nMcuLevel     MCU 级别，目前只有0
	// pszServerIP   服务器的IP地址
	// pszUserID     用户登录的ID（用户登录帐号）
	// pszPassword	 登陆密码
	virtual void GetLoginMCUInfo(int &nMcuLevel, CString &strServerIP, CString &strUserID, CString &strPassword) = 0;
	// 得到要进入会议室的ID
	virtual int GetLoginConferenceID() = 0;
	//得到录像文件路径名称
	virtual CString GetFilePathName() = 0;
};



//////////////////////////////////////////////////////////////////////////
//    视频会议系统调用接口
//////////////////////////////////////////////////////////////////////////
interface IVideoConfSystem
{
public:
	IVideoConfSystem(){};
	virtual ~IVideoConfSystem(){};

public:
	// 释放视频会议系统
	virtual void ReleaseVideoConfSystem(IVideoConfSystem* pISystem) = 0;
	virtual void SendDlgMessage(MSG* pMsg) = 0;
};


// 创建视频会议系统调用接口
DllExport_VIDEO_CONF_SYSTEM IVideoConfSystem* CreateIVideoConferenceSystem(IVideoConfSystemNotify* pINotify,	// 视频会议系统回调通知接口
																		   HWND hWnd,							// 回调消息的接受窗口句柄
																		   BOOL bStartFromOcx,					// 启动是否从 OCX 启动
																		   int  nFlage);						// 调用标识 0: 启动会议调用 1: 会议录像调用
#endif