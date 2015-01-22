
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include "resource.h"



#define  __MORE_DROG__  //是否启动多人拖拽功能
//#undef   __MORE_DROG__

//是否有IM
#define HAVE_IM_FLAG       0	

//是否使用ChatUI.dll（如果不使用注释掉下面的define）
//#define USES_CHATUI				1

//版本标志
#define RS_FLAG      0
//系列颜色设置
//#define RS_COLOR_FLAG       0				

#ifdef RS_COLOR_FLAG
//主窗口的颜色设置
#define COLOR_BACK_GROUND       RGB(233,254,209)
#define COLOR_BACK_GROUND2      RGB(242,253,210)
#define COLOR_TEXT				RGB(0,0,0)
#define BUTTON_BACK_COLOR		RGB(167,219,9)
#define MENU_BACK_COLOR			RGB(243,243,243)
#define COLOR_TEXT_NORMAL		RGB(10,113,191)
#define COLOR_TEXT_SELECT		RGB(255,0,0)//RGB(255, 255, 0)
#define COLOR_TEXT_ACTIVE		RGB(7,80,135)
#define COLOR_BUTTON_NORMAL_BOTTOM		RGB(124,186,80)
#define COLOR_BUTTON_FRAME		RGB(156, 156, 156)

//IDD_USER_DIALOG的颜色设置
#define COLOR_WIN_BACK_DLG		RGB(236, 233, 216)
#define COLOR_USER_BACK_DLG		RGB(166, 182, 255)
#define COLOR_HAVE_USER_BACK_DLG		RGB(57,125,243)
#define COLOR_USER_FRAME_DLG	RGB(255, 255, 255)
#define COLOR_USER_FRAME_INDEX_DLG	RGB(255, 255, 255)
#define COLOR_SCREEN_FRAME_DLG	RGB(255, 0, 0)

//IDD_PRESIDE_CONTROL_DIALOG的button颜色设置
#define COLOR_BUTTON_FRAME_ACTIVE_PRESIDE_CONTROL_DIALOG		RGB(255, 255, 255)
#define COLOR_BUTTON_NORMAL_BOTTOM_PRESIDE_CONTROL_DIALOG		RGB(172, 172, 172)

//IDD_LOCAL_USER_DIALOG的颜色设置
#define COLOR_CPU_TEXT RGB(0, 255, 0)
#define COLOR_CPU_LOW RGB(0,255,0)
#define COLOR_CPU_HIGH RGB(255,0,0)

//IDD_REPETITION_LIST_DIALOG的颜色设置
#define COLOR_NO_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_BKCOLOR RGB(161,216,122)
#else
//主窗口的颜色设置
#define COLOR_BACK_GROUND       RGB(208,214,226)	//RGB(210,210,210)
#define COLOR_BACK_GROUND2		RGB(255,255,255)	//RGB(210,210,210)
#define COLOR_TEXT				RGB(0,0,0)
#define BUTTON_BACK_COLOR		RGB(167,219,9)
#define MENU_BACK_COLOR			RGB(243,243,243)
#define COLOR_TEXT_NORMAL		RGB(10,113,191)
#define COLOR_TEXT_SELECT		RGB(255,0,0)//RGB(255, 255, 0)
#define COLOR_TEXT_ACTIVE		RGB(7,80,135)
#define COLOR_BUTTON_NORMAL_BOTTOM		RGB(101,170,211)//RGB(124,186,80)
#define COLOR_BUTTON_FRAME		RGB(156, 156, 156)

//IDD_USER_DIALOG的颜色设置
#define COLOR_WIN_BACK_DLG		RGB(236, 233, 216)
#define COLOR_USER_BACK_DLG		RGB(255,255,255)	//RGB(208,214,226)	//RGB(166, 182, 255)
#define COLOR_HAVE_USER_BACK_DLG		RGB(57,125,243)
#define COLOR_USER_FRAME_DLG	RGB(201,201,201)	//RGB(255, 255, 255)
#define COLOR_USER_FRAME_INDEX_DLG	RGB(255, 255, 255)
#define COLOR_SCREEN_FRAME_DLG	RGB(255, 0, 0)

//IDD_PRESIDE_CONTROL_DIALOG的button颜色设置
#define COLOR_BUTTON_FRAME_ACTIVE_PRESIDE_CONTROL_DIALOG		RGB(255, 255, 255)
#define COLOR_BUTTON_NORMAL_BOTTOM_PRESIDE_CONTROL_DIALOG		RGB(172, 172, 172)

//IDD_LOCAL_USER_DIALOG的颜色设置
#define COLOR_CPU_TEXT RGB(0, 255, 0)
#define COLOR_CPU_LOW RGB(0,255,0)
#define COLOR_CPU_HIGH RGB(255,0,0)

//IDD_REPETITION_LIST_DIALOG的颜色设置
#define COLOR_NO_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_BKCOLOR RGB(161,216,122)
#endif

// 视频切割填充的颜色
#define COLOR_VIDEO_BKCOLOR RGB(0, 0, 0)	// Add Han Huajie 2008/01/15


//对话筐边上空出的宽度
#define SIDE_WIDTH				3

//是否强制更新
#define HP_UPDATE_FLAG			1

// 使用新的自动更新程序
#define NEW_HPLIVEUPDATE		1		// 0 用原来的自动更新程序   1  新的自动更新程序

//小图标消息
#define WM_MYMESSAGE (WM_USER+1)

//屏幕共享边框宽度
#define SCREEN_BORDER_WIDTH	3

//转化临时字符串的长度
#define SZTEMP_LENTH 1024 

#define CONFERENCE_WIN_NUMBER 4

//IP Camera对应卡号
#define IP_CAMERA_NO 100
//屏幕共享对应卡号
#define SCREEN_IS_VIDEO_NO 198
//高清对应卡号
#define RGB_IS_VIDEO_NO 199
//共享媒体对应卡号
#define MEDIA_IS_VIDEO_NO 200
//H323对应的卡号
#define H323_IS_VIDEO_NO 240


#define	 SEPERATE                        (_T("<_|||_>"))


//{{add by tiger,2009.06.18
const int TITALBAR_HEIGHT = 72;	//标题栏高度
const int TOOLBAR_HEIGHT = 43;	//工具栏高度
const int STATUS_HEIGHT = 44;	//状态栏高度
const int TALKDLG_HEIGHT = 100;	//讨论区高度（未广播时）
const int AFFICHE_HEIGHT = 30;	//字幕区高度
const int MENU_HEIGHT = 29;		//菜单栏高度
const int MAIN_FRAME_WIDTH = 3;	//主程序边框宽度
const int MENU_BMP_HEIGHT = 20;	//菜单栏图片高度	Add HHJ 2009/10/12
//}}

//
//自定义消息------------------------------------------------
//

#define WM_ACCEPT_CONFERENCE WM_USER+0x12+13000		//参加会议消息, WPARAM = ConferenceID, LPARAM = TRUE | FALSE
#define WM_OPEN_REMOTE_VIDEO WM_USER+0x13+13000		//打开远程用户视频 WPARAM=SessionID, LPARAM=MAKELONG(CardNo, WndIndex)
#define WM_OPEN_REMOTE_AUDIO WM_USER+0x14+13000		//打开远程用户音频 WPARAM=SessionID, LPARAM=LPARAM=MAKELONG(CardNo, WndIndex)
#define WM_CLOSE_REMOTE_VIDEO WM_USER+0x15+13000		//关闭远程用户视频 WPARAM=SessionID, LPARAM=CardNo
#define WM_CLOSE_REMOTE_AUDIO WM_USER+0x16+13000		//关闭远程用户音频 WPARAM=SessionID, LPARAM=CardNo
#define WM_APPLY_VIDEO_FORMAT_PRESETTING WM_USER+0x17+13000	//应用视频格式预设置 WPARAM = 用户数, LPARAM = 参数指针,具体参数见程序部分
#define WM_VIDEO_FULL_SCREEN WM_USER+0x18+13000 //最大化视频 WPARAM=MAKELONG(x,y), LPARAM=MAKELONG(cx,cy)
#define WM_VIDEO_RESTORE_SCREEN WM_USER+0x19+13000 //恢复视频 WPARAM=MAKELONG(x,y), LPARAM=MAKELONG(cx,cy)
#define WM_RESIZE_ALL_WND WM_USER+0x1a+13000      //修改所有窗口的大小, 放在屏幕共享区内, 
#define WM_CAPTURE_FULL_SCREEN WM_USER+0x1b+13000 //屏幕共享 => 全屏
//WPARAM = IsFullScreen(TRUE|FALSE)
//LPARAM = TRUE|FALSE (send this message to other window)
//

#define WM_CAPTURE_ONCE WM_USER+0x1c+13000    //屏幕共享 => 刷新
#define WM_SCREEN_VIDEO_BMP_QUALITY WM_USER+0x1d+13000    //屏幕共享 => 图像质量
//0: stop
//1: slowly
//2: slow
//3: normal
#define WM_SCREEN_VIDEO_FRAME_RATE WM_USER+0x1e+13000 //屏幕共享 => 图像帧率(L)
//4: 4 bit color 
//8: 8 bit color
//16: 16 bit color 
#define WM_CONFERENCE_SYNC WM_USER+0x1f+13000 //会议同步, WPARAM=IsSync

#define WM_OPEN_FLOAT_WIN WM_USER+0x20+13000  //打开浮动窗口, WPARAM= SessionID, LPARAM=UerCardNo.
#define WM_CLOSE_FLOAT_WIN WM_USER+0x22+13000  //关闭浮动窗口
#define WM_WAVEOUT_MUTE WM_USER+0x24+13000    //设置本地静音 WPARAM=TRUE|FALSE
#define WM_CAPTURE_FULL_SCREEN_REQUEST WM_USER+0x25+13000 //通知主窗口屏幕全屏
//WPARAM = nScreenIndex, LPARAM = IsFullScreen(TRUE | FALSE)
#define WM_CLOSE_CAPTURE_SCREEN_REQUEST WM_USER+0x26+13000    //通知主窗口关闭屏幕共享
#define WM_RELOAD_YUTAI_PARAMETER WM_USER+0x27+13000  //重新加载云台参数
#define WM_AUTO_LOGIN_CONFERENCE WM_USER+0x28+13000  //自动进入会议(自动登录) WPARAM = ConferenceID, LPARAM = TRUE | FALSE
#define WM_SET_WAVEOUT_VOLUME WM_USER+0x29+13000 //设置本地音量
#define WM_YUTAI_ACTION WM_USER+0x2B+13000 //云台命令提醒,WPARAM = command
#define WM_SCREEN_SWITCH_STATE WM_USER+0x2C+13000 //设置屏幕切换工具条状态, WPARAM = Screen Index[0,1]
#define WM_CONFERENCE_CLSOE WM_USER+0x2d+13000    //退出会议消息
#define WM_SYSTEM_OFF_LINE  WM_USER+0x2e+13000    //注销消息
#define WM_RECIRCLE_SHOW    WM_USER+0x2f+13000    //重新轮循
//------------------------------------------------------------

#define WM_VIDEO_SETTING_ITEMER_MSG    WM_USER + 265482    //选项设置单项选择消息
// 释放 视频会议系统 模块消息处理
#define WM_RELEASE_DATAINFOMANAGE_MSG		24860

#define COMPONENTTYPE_DST_SPEAKERS    4
#define COMPONENTTYPE_DST_WAVEIN      7

#ifndef	 _VIDEOSYSTEM_CONFERENCE_HHJ_
	#define  _VIDEOSYSTEM_CONFERENCE_HHJ_
#endif

#ifndef _H323DATAINFO_HHJ_
	#define _H323DATAINFO_HHJ_
#endif

#ifndef _AVIDEO_TEST_HHJ_200912021041_
	#define _AVIDEO_TEST_HHJ_200912021041_
#endif

// H323 网关启动标识宏定义	Add HHJ 20091211
//#ifndef _H323_GATEWAY_MARK_
//	#define _H323_GATEWAY_MARK_
//#endif

//远程定损标志
//#ifndef _REMOTE_SET_LOSS_			
//	#define _REMOTE_SET_LOSS_
//#endif

//#ifndef _IPCAMERA_
//	#define _IPCAMERA_
//#endif

//#ifndef _IFREECOMM_
//	#define _IFREECOMM_
//#endif

//#ifndef _IFREECOMM_
//#ifdef _DEBUG
//#pragma comment(lib,"../../lib/Debug/IPCamera.lib")
//#else
//#pragma comment(lib,"../../lib/release/IPCamera.lib")
//#endif
//#endif


char *ChangTextToUtf8(LPCTSTR szText,char* szTemp);				//改变文本格式为UTf8
TCHAR *ChangUtf8ToText(const char* szText,TCHAR *szTemp);				//改变文本格式由UTf8转回
CString GetExePath();


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


