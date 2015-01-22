#ifndef __RSMSGDEFINE_H
#define __RSMSGDEFINE_H

#include "../DataDefine/DataDefine.h"

#define		COUNTOFONCE		400
// 命令ID定义（部分）

// 只上传到上层MCU（即拉数据）
#define 	CONF_COMMAND_FETCHMCUINFO						0x0001	// 取得MCU信息
#define 	CONF_COMMAND_FETCHMCUINFOEND					0x0002	// 取得MCU信息结束
#define     CONF_COMMAND_FETCHCONFERENCEBASEINFO			0x0003  // 取得会议基本信息
#define     CONF_COMMAND_FETCHCONFERENCEBASEINFOEND			0x0004  // 取得会议基本信息结束
// 上传到顶层MCU
#define 	CONF_COMMAND_USERLOGIN							0x0005	// 用户登录
#define     CONF_COMMAND_FETCHCONFERENCEUSERINFO			0x0006  // 取得会议用户信息					// temp

#define 	CONF_COMMAND_CHANGENAME							0x0007	// 改变用户名称（待用）
#define 	CONF_COMMAND_CHANGEPASSWORD						0x0008	// 改变用户密码（待用）

#define 	CONF_COMMAND_CHANGECONFERENCETEMPLET			0x0009	// 改变会议模板（会议）
#define 	CONF_COMMAND_ALLOWKINESCOPE						0x000A	// 允许录像（会议和个人）
#define 	CONF_COMMAND_FORBIDKINESCOPE					0x000B	// 不允许录像（会议和个人）
#define 	CONF_COMMAND_ALLOWCONTROL						0x000C	// 允许控制（会议和个人）
#define 	CONF_COMMAND_FORBIDCONTROL						0x000D	// 不允许控制（会议和个人）
#define 	CONF_COMMAND_SETTALK							0x000E	// 讨论设置（会议和个人）
#define 	CONF_COMMAND_ISSUEBULL							0x000F	// 打开公告（会议）
#define 	CONF_COMMAND_CLOSEBULL							0x0010	// 关闭公告（会议）
#define 	CONF_COMMAND_SETBULL							0x0011	// 设置公告内容（会议）

#define 	CONF_COMMAND_ALLOWSPEAK							0x0012	// 允许演讲
#define 	CONF_COMMAND_CLOSESPEAK							0x0013	// 关闭演讲
#define 	CONF_COMMAND_ASKSPEAK							0x0014	// 请求演讲

#define 	CONF_COMMAND_CHANGUSERMICVIDEOINFO				0x0015	// 改变视音频格式（个人）

#define		CONF_COMMAND_INCEPTVIDEO						0x0016  // 接收视频
#define		CONF_COMMAND_CLOSEVIDEO							0x0017  // 关闭视频
#define		CONF_COMMAND_SETBROADCASTVIDEO					0x0018  // 广播视频
#define		CONF_COMMAND_CLOSEBROADCASTVIDEO				0x0019  // 关闭广播视频
#define		CONF_COMMAND_INCEPTSOUND						0x001A  // 接收音频
#define		CONF_COMMAND_CLOSEINCEPTSOUND					0x001B  // 关闭音频
#define		CONF_COMMAND_SETBROADCASTSOUND					0x001C  // 广播音频
#define		CONF_COMMAND_CLOSEBROADCASTSOUND				0x001D  // 关闭广播音频

#define		CONF_COMMAND_SOUNDDRIVERITEM					0x001E  // 音频设备项（个人）
#define		CONF_COMMAND_VIDEODRIVERITEM					0x001F  // 视频设备项（个人）

#define		CONF_COMMAND_FRAMENO							0x0020	// 显示几号屏（会议）

#define		CONF_COMMAND_OPENTALKOVER						0x0021	// 打开讨论
#define		CONF_COMMAND_CLOSETALKOVER						0x0022	// 关闭讨论
#define		CONF_COMMAND_BROADCASTWB						0x0023  // 广播白板
#define		CONF_COMMAND_CLOSEWB							0x0024  // 关闭白板
#define		CONF_COMMAND_BROADCASTDESKTOP					0x0025  // 广播桌面
#define		CONF_COMMAND_CLOSEDESKTOP						0x0026  // 关闭桌面

#define		CONF_COMMAND_FULLWIN							0x0027  // 窗口已满
#define		CONF_COMMAND_CONTROLCOMMAND						0x0028	// 云台控制
#define		CONF_COMMAND_CONTROLSPEED						0x0029	// 云台速度
#define		CONF_COMMAND_SWAPPOSITION						0x002A	// 交换屏窗
#define		CONF_COMMAND_VIDEOORDER							0x002B	// 视频预置
#define		CONF_COMMAND_ASKTOPROLOCUTOR					0x002C	// 申请成为发言人
#define		CONF_COMMAND_INVITEUSER							0x002D	// 邀请已登陆的人员参会

#define 	CONF_COMMAND_ALLOWUSEWHITEBOARD					0x002E	// 允许使用白板（会议和个人）
#define 	CONF_COMMAND_FORBIDUSEWHITEBOARD				0x002F	// 不允许使用白板（会议和个人）
 
#define 	CONF_COMMAND_OPENFLOATWIN						0x0030	// 打开浮动窗（会议）
#define 	CONF_COMMAND_CLOSEFLOATWIN						0x0031	// 关闭浮动窗（会议）
#define 	CONF_COMMAND_SETFLOATWINRECT					0x0032	// 设置浮动窗位置（会议）

#define 	CONF_COMMAND_SETBANDWIDTH						0x0033	// 限制的带宽（会议）

#define     CONF_COMMAND_FETCHCONFERENCESYNCHRONIZATION		0x0034  // 取得会议同步信息，只上传到上层MCU（即拉数据）

#define 	CONF_COMMAND_SETWATCHUSER						0x0035	// 设监控人员（会议）
#define 	CONF_COMMAND_CLOSEWATCHUSER						0x0036	// 关闭监控人员（会议）
#define		CONF_COMMAND_ALLOWWATCHUSERCONTROL				0x0037	// 允许监控员控制（会议）
#define		CONF_COMMAND_FORBIDWATCHUSERCONTROL				0x0038	// 不允许监控员控制（会议）

#define 	CONF_COMMAND_SETFULLSCREEN						0x0039	// 设共享屏幕全屏（会议）
#define 	CONF_COMMAND_CLOSEFULLSCREEN					0x003A	// 关闭全屏屏幕（会议）

#define 	CONF_COMMAND_TESTMCUBANDWIDTHSTART				0x003B	// 测试网络带宽开始
#define 	CONF_COMMAND_TESTMCUBANDWIDTHDATA				0x003C	// 测试网络带宽数据
#define 	CONF_COMMAND_TESTMCUBANDWIDTHEND				0x003D	// 测试网络带宽结束

#define 	CONF_COMMAND_SPURNSOMEBODY						0x003E	// 踢人
#define		CONF_COMMAND_ISENABLECONFERENCETOPIC			0x003F	// 是否显示会议标题
#define		CONF_COMMAND_ISALLOWENTERCONFERENCE				0x0040	// 是否允许进入会议
#define		CONF_COMMAND_ISENABLEASKTOPROLOCUTOR			0x0041	// 是否显示申请发言人
#define		CONF_COMMAND_ISENABLEFLOATWIN					0x0042	// 是否拉申浮动窗口
#define		CONF_COMMAND_ISSETPROLOCUTOR					0x0043	// 是否设置发言人
#define		CONF_COMMAND_DELPROLOCUTOR						0x0044	// 删除发言人

#define		CONF_COMMAND_P2PDATA							0x0048	// 发送点对点数据
#define		CONF_COMMAND_ISSCREENCONTROL					0x0049	// 是否允许申请屏幕控制

#define 	CONF_COMMAND_CONFERENCEINITMSGSPOKEMAN			0x0055	// 取得演讲人进入会议初始化信息

// 用户进入会议的初始化信息传递
#define     CONF_COMMAND_SENDCONFERENCETEMPLET				0x1001  // 发送会议模板
#define     CONF_COMMAND_SENDCONFERENCEMEMBER				0x1002  // 发送会议成员（某会议）
#define     CONF_COMMAND_SENDCONFERENCEMEMBERPRESENCE		0x1003  // 发送在线会议成员
#define     CONF_COMMAND_SENDCONFERENCEMEMBERENTER			0x1004  // 发送进入会议成员   
#define		CONF_COMMAND_SENDTALKOVER						0x1005	// 发送讨论设置
#define		CONF_COMMAND_SENDTALKOVERDATA					0x1006	// 发送讨论历史数据
#define		CONF_COMMAND_SENDASKTOPROLOCUTORLIST			0x1007	// 发送申请发言人列表


// MCU之间的初始化信息传递
#define     CONF_COMMAND_SENDINITCONFERENCETEMPLET			0x2001  // 发送初始化会议模板
#define     CONF_COMMAND_SENDINITCONFERENCEMEMBER			0x2002  // 发送初始化会议成员（全部会议）
#define		CONF_COMMAND_SENDINITVIDEOCHANNELID				0x2003  // 发送初始化视频通道ID
#define		CONF_COMMAND_SENDINITAUDIOCHANNELID				0x2004  // 发送初始化音频通道ID
#define		CONF_COMMAND_SENDINITWBCHANNELID				0x2005  // 发送初始化音频通道ID
#define		CONF_COMMAND_SENDINITDESKTOPCHANNELID			0x2006  // 发送初始化桌面通道ID
#define		CONF_COMMAND_SENDINITTEMPLETDICTIONARY			0x2007  // 发送初始化模板字典表

#define		CONF_COMMAND_DISCONNECTEDMCU					0x2008  // 某mcu断开连接
#define		CONF_COMMAND_SENDINITEND						0x2009  // 发送初始化数据结束


// 广播
#define     CONF_COMMAND_BROADCAST_MCULOGIN					0x3001  // MCU登陆状态广播		
#define     CONF_COMMAND_BROADCAST_MCULOGOUT				0x3002  // MCU登陆状态广播						
#define 	CONF_COMMAND_BROADCAST_USERLOGIN				0x3003	// 用户登录状态广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_USERLOGOUT				0x3004	// 用户退出状态广播（上下发散）
#define 	CONF_COMMAND_BROADCAST_CONFERENCELOGIN			0x3005	// 用户登录会议状态广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_CONFERENCELOGOUT			0x3006	// 用户退出会议状态广播（上下发散）

#define		CONF_COMMAND_BROADCAST_P2PDATA					0x3007	// 发送点对点广播数据

#define 	CONF_COMMAND_BROADCAST_OPENTALKOVER				0x4001	// 打开会议讨论广播					
#define 	CONF_COMMAND_BROADCAST_CLOSETALKOVER			0x4002	// 关闭会议讨论广播						
#define 	CONF_COMMAND_BROADCAST_TALKOVERDATA				0x4003	// 会议讨论数据广播（上下发散）

#define 	CONF_COMMAND_BROADCAST_CHANGECONFERENCETEMPLET	0x4004	// 改变会议模板广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_CHANGENAME				0x4005	// 改变用户名广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_ALLOWKINESCOPE			0x4006	// 允许录像广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_FORBIDKINESCOPE			0x4007	// 不允许录像广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_ALLOWCONTROL				0x4008	// 允许控制广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_FORBIDCONTROL			0x4009	// 不允许控制广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_SETTALK					0x400A	// 讨论设置广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_ISSUEBULL				0x400B	// 打开公告广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_CLOSEBULL				0x400C	// 关闭公告广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_SETBULL					0x400D	// 设置公告内容广播（自顶而下）

#define 	CONF_COMMAND_BROADCAST_ALLOWSPEAK				0x400E	// 允许演讲广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_CLOSESPEAK				0x400F	// 关闭演讲广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_ASKSPEAK					0x4010	// 请求演讲广播（只给主持人）

#define 	CONF_COMMAND_BROADCAST_CHANGUSERMICVIDEOINFO	0x4011	// 改变视音频格式广播（只给主持人）

#define		CONF_COMMAND_BROADCAST_SETBROADCASTVIDEO		0x4012  // 视频广播
#define		CONF_COMMAND_BROADCAST_CLOSEBROADCASTVIDEO		0x4013  // 关闭视频广播
#define		CONF_COMMAND_BROADCAST_SETBROADCASTSOUND		0x4014  // 音频广播
#define		CONF_COMMAND_BROADCAST_CLOSEBROADCASTSOUND		0x4015  // 关闭音频广播

#define		CONF_COMMAND_BROADCAST_SOUNDDRIVERITEM			0x4016  // 音频设备项广播
#define		CONF_COMMAND_BROADCAST_VIDEODRIVERITEM			0x4017  // 视频设备项广播

#define		CONF_COMMAND_BROADCAST_FRAMENO					0x4018	// 显示几号屏广播
#define		CONF_COMMAND_BROADCAST_WB						0x4019	// 打开白板广播
#define		CONF_COMMAND_BROADCAST_CLOSEWB					0x401A  // 关闭白板广播
#define		CONF_COMMAND_BROADCAST_DESKTOP					0x401B	// 打开桌面广播
#define		CONF_COMMAND_BROADCAST_CLOSEDESKTOP				0x401C  // 关闭桌面广播

#define		CONF_COMMAND_BROADCAST_FULLWIN					0x401D  // 窗口已满广播							
#define		CONF_COMMAND_BROADCAST_SWAPPOSITION				0x401E  // 交换屏窗广播

//////////////////////////////////////////////////////////////////////////
#define		CONF_COMMAND_BROADCAST_DELETEMCU				0x401F  // MCU删除广播
#define		CONF_COMMAND_BROADCAST_UPDATEMCU				0x4020  // MCU更新广播
#define		CONF_COMMAND_BROADCAST_INSERTMCU				0x4021  // MCU插入广播
#define		CONF_COMMAND_BROADCAST_DELETECONFERENCE			0x4022  // 会议删除广播
#define		CONF_COMMAND_BROADCAST_UPDATECONFERENCE			0x4023  // 会议更新广播
#define		CONF_COMMAND_BROADCAST_INSERTCONFERENCE			0x4024  // 会议插入广播
#define		CONF_COMMAND_BROADCAST_DELETECONFERENCEUSER		0x4025  // 会议成员删除广播
#define		CONF_COMMAND_BROADCAST_UPDATECONFERENCEUSER		0x4026  // 会议成员更新广播
#define		CONF_COMMAND_BROADCAST_INSERTCONFERENCEUSER		0x4027  // 会议成员插入广播
#define		CONF_COMMAND_BROADCAST_DELETETEMPLET			0x4028  // 会议模板删除广播
#define		CONF_COMMAND_BROADCAST_UPDATETEMPLET			0x4029  // 会议模板更新广播
#define		CONF_COMMAND_BROADCAST_INSERTTEMPLET			0x402A  // 会议模板插入广播
//////////////////////////////////////////////////////////////////////////

#define		CONF_COMMAND_BROADCAST_FREEVIDEOCHANNEL			0x402B	// 关闭视频通道
#define		CONF_COMMAND_BROADCAST_FREEAUDIOCHANNEL			0x402C	// 关闭音频通道

#define 	CONF_COMMAND_BROADCAST_VIDEOORDER				0x402D	// 视频预置广播（只给主持人）
#define 	CONF_COMMAND_BROADCAST_ASKTOPROLOCUTOR			0x402E	// 申请成为发言人广播

#define 	CONF_COMMAND_BROADCAST_ALLOWUSEWHITEBOARD		0x402F	// 允许使用白板广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_FORBIDUSEWHITEBOARD		0x4030	// 不允许使用白板广播（自顶而下）

#define		CONF_COMMAND_BROADCAST_ADDNEWAUDIOCHANNEL		0x4031  // 新增音频通道广播
#define		CONF_COMMAND_BROADCAST_ADDNEWVIDEOCHANNEL		0x4032  // 新增视频通道广播
#define		CONF_COMMAND_BROADCAST_ADDNEWWBCHANNEL			0x4033  // 新增白板通道广播
#define		CONF_COMMAND_BROADCAST_ADDNEWDESKTOPCHANNEL		0x4034  // 新增桌面通道广播

#define		CONF_COMMAND_BROADCAST_OPENFLOATWIN				0x4035  // 打开浮动窗广播（自顶而下，给所有人）
#define		CONF_COMMAND_BROADCAST_CLOSEFLOATWIN			0x4036  // 关闭浮动窗广播（自顶而下，给所有人）
#define		CONF_COMMAND_BROADCAST_SETFLOATWINRECT			0x4037  // 设置浮动窗位置广播（自顶而下，给所有人）

#define		CONF_COMMAND_BROADCAST_SETBANDWIDTH				0x4038  // 限制的带宽广播（只给主持人）

#define 	CONF_COMMAND_BROADCAST_SETWATCHUSER				0x4039	// 设监控人员广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_CLOSEWATCHUSER			0x403A  // 关闭监控人员广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_ALLOWWATCHUSERCONTROL	0x403B	// 允许监控员控制广播（自顶而下）
#define 	CONF_COMMAND_BROADCAST_FORBIDWATCHUSERCONTROL	0x403C	// 不允许监控员控制广播（自顶而下）

#define		CONF_COMMAND_BROADCAST_SETFULLSCREEN			0x403D  // 设共享屏幕全屏广播（自顶而下，给所有人）
#define		CONF_COMMAND_BROADCAST_CLOSEFULLSCREEN			0x403E  // 关闭全屏屏幕广播（自顶而下，给所有人）

#define		CONF_COMMAND_BROADCAST_FREEWBCHANNEL			0x403F	// 关闭白板通道
#define		CONF_COMMAND_BROADCAST_FREEDESKTOPCHANNEL		0x4040	// 关闭桌面通道
#define		CONF_COMMAND_BROADCAST_FREEFILECHANNEL			0x4041	// 关闭文件通道

#define		CONF_COMMAND_BROADCAST_ISENABLECONFERENCETOPIC	0x4042	// 是否显示会议标题
#define		CONF_COMMAND_BROADCAST_ISALLOWENTERCONFERENCE	0x4043	// 是否允许进入会议
#define		CONF_COMMAND_BROADCAST_ISENABLEASKTOPROLOCUTOR	0x4044	// 是否显示申请发言人
#define		CONF_COMMAND_BROADCAST_ISENABLEFLOATWIN			0x4045	// 是否拉申浮动窗口
#define		CONF_COMMAND_BROADCAST_ISSETPROLOCUTOR			0x4046	// 是否设置发言人
#define		CONF_COMMAND_BROADCAST_DELPROLOCUTOR			0x4047	// 删除发言人

#define		CONF_COMMAND_BROADCAST_TOS						0x4048	// QOS

#define		CONF_COMMAND_BROADCAST_DISCONNECTEDMCU			0x4049  // 某mcu断开连接(优化版)

#define     CONF_COMMAND_BROADCAST_UPDATECONFERENCEALL      0x404A

#define		CONF_COMMAND_BROADCAST_DELETEAUDIOCHANNEL		0x404B
#define		CONF_COMMAND_BROADCAST_DELETEVIDEOCHANNEL		0x404C
#define		CONF_COMMAND_BROADCAST_DELETEDESKTOPCHANNEL		0x404D
#define		CONF_COMMAND_BROADCAST_DELETEFILECHANNEL		0x404E
#define		CONF_COMMAND_BROADCAST_DELETEWBCHANNEL			0x404F

#define		CONF_COMMAND_BROADCAST_ISSCREENCONTROL			0x4052	// 是否允许申请屏幕控制


// 响应返回
#define 	CONF_COMMAND_CHANGENAME_REP						0x5001	// 改变用户名称返回
#define 	CONF_COMMAND_CHANGEPASSWORD_REP					0x5002	// 改变用户密码返回
#define 	CONF_COMMAND_ALLOWKINESCOPE_REP					0x5003	// 允许录像返回（个人）
#define 	CONF_COMMAND_FORBIDKINESCOPE_REP				0x5004	// 不允许录像返回（个人）
#define 	CONF_COMMAND_ALLOWCONTROL_REP					0x5005	// 允许控制返回（个人）
#define 	CONF_COMMAND_FORBIDCONTROL_REP					0x5006	// 不允许控制返回（个人）
#define 	CONF_COMMAND_SETTALK_REP						0x5007	// 讨论设置返回（个人）

#define 	CONF_COMMAND_CHANGUSERMICVIDEOINFO_REP			0x5008	// 改变视音频格式返回

#define		CONF_COMMAND_INCEPTVIDEO_REP					0x5009  // 接收视频返回对方
#define		CONF_COMMAND_CLOSEVIDEO_REP						0x500A  // 关闭视频返回对方
#define		CONF_COMMAND_INCEPTSOUND_REP					0x500B  // 接收音频返回对方
#define		CONF_COMMAND_CLOSEINCEPTSOUND_REP				0x500C  // 关闭音频返回对方

#define		CONF_COMMAND_INCEPTVIDEO_SELFREP				0x500D  // 接收视频返回自己
#define		CONF_COMMAND_INCEPTSOUND_SELFREP				0x500E  // 接收音频返回自己

#define		CONF_COMMAND_FULLWIN_REP						0x500F  // 窗口已满返回
#define		CONF_COMMAND_CONTROLCOMMAND_REP					0x5010	// 云台控制返回
#define		CONF_COMMAND_CONTROLSPEED_REP					0x5011	// 云台速度返回

#define		CONF_COMMAND_INVITEUSER_REP 					0x5012	// 邀请已登陆的人员参会返回

#define 	CONF_COMMAND_ALLOWUSEWHITEBOARD_REP				0x5013	// 允许使用白板返回（个人）
#define 	CONF_COMMAND_FORBIDUSEWHITEBOARD_REP			0x5014	// 不允许使用白板返回（个人）

#define 	CONF_COMMAND_TESTMCUBANDWIDTH_REP				0x5015	// 测试网络带宽返回

#define 	CONF_COMMAND_SPURNSOMEBODY_REP					0x5016	// 踢人返回

#define		CONF_COMMAND_P2PDATA_REP						0x5017	//	点对点数据回调

#define		CONF_COMMAND_CHANGUSERMICVIDEOINFO_SPOKEMAN		0x5018
#define		CONF_COMMAND_SOUNDDRIVERITEM_SPOKEMAN			0x5019
#define		CONF_COMMAND_VIDEODRIVERITEM_SPOKEMAN			0x5020


// 文件分发
#define		CONF_COMMAND_STARTFILE							0x6000  // 开始文件分发
#define		CONF_COMMAND_CLOSEFILE							0x6001  // 关闭文件分发
#define		CONF_COMMAND_SENDINITFILECHANNELID				0x6002  // 发送初始化文件分发通道ID
#define		CONF_COMMAND_BROADCAST_STARTFILE				0x6003	// 分发文件广播
#define		CONF_COMMAND_BROADCAST_CLOSEFILE				0x6004  // 关闭文件分发广播
#define		CONF_COMMAND_BROADCAST_ADDNEWFILECHANNEL		0x6005  // 新增文件分发通道广播
#define		CONF_COMMAND_FILEEXIST_REP						0x6005  // 文件已存在

//////////////////////////////////////////////////////////////////////////
//#ifdef NETTVANDBROADCAST
#define     CONF_COMMAND_FETCHCHANNELINFO					0x7001  // 取得频道基本信息
#define     CONF_COMMAND_FETCHCHANNELINFOEND				0x7002  // 取得频道基本信息结束
#define		CONF_COMMAND_SETTVCHANNEL						0x7003  // 设置电视机频道

#define		CONF_COMMAND_BROADCAST_DELETECHANNEL			0x7004  // 会议频道删除广播
#define		CONF_COMMAND_BROADCAST_UPDATECHANNEL			0x7005  // 会议频道更新广播
#define		CONF_COMMAND_BROADCAST_INSERTCHANNEL			0x7006  // 会议频道插入广播

#define		CONF_COMMAND_BROADCAST_SETTVCHANNEL				0x7007  // 设置电视机频道广播
#define		CONF_COMMAND_BROADCAST_CHANNELCHARGER			0x7008  // 设置电视机频道广播
//#endif
//////////////////////////////////////////////////////////////////////////


// 信令分类
typedef enum SignalType {
	_eMessage,		// 消息
	_eVideo		// 视频
	//_eAudio,		// 音频
	//_eDesktop,		// 桌面
	//_eWhiteboard,	// 白板
	//_eFile			// 文件
} ESignalType;

// 方向分类
typedef enum DirectionType {
	_eSingle,		// 单一
	_eBroadcast		// 广播
} EDirectionType;

// 信令头（保持向下兼容）
typedef struct SignalHeader {
	ESignalType 	_eSignalType;		// 信令类型
	UINT32			_iSignalBodyLength;	// 信令体字长
} _tSignalHeader;

// 信令体（未定义）
typedef struct SignalBody {
} _tSignalBody;

// 信令头字长
const UINT16 c_tSignalHeaderLen = sizeof(SignalHeader);

// 消息头
typedef struct MessageHeader {
	EDirectionType	_eDirectionType;	// 方向类型
	UINT32			_iCommandID;		// 命令ID，参考文件：ComDefine.h，网络部分参考本文	
	UINT32			_iMcuID;			// 上行命令：_iMcuID为发起地mcuID；下行命令：表示当前搜索路径级数，每一跳加1（初始值为0）
//  以下消息体：_lMcuID1..._lMcuIDn为mcuID搜索路径序列，即由mcuID序列组成，包括目的地（最后一个）
//	UINT32	_lMcuID1;					// 第一级mcuID（即顶层mcu的下一级mcu）
//	...
//	UINT32	_lMcuIDn;					// 目的mcuID（即sessionID，这里的mcuID和sessionID是一回事，注意数据库的分配）
} _tMessageHeader;

// 消息头字长
const UINT16 c_tMessageHeaderLen = sizeof(MessageHeader);

// 消息体（未定义）
// 参考文件：DataDefine.h

// 通道数据头（白板无此头，数据流总是先到顶层mcu再广播到所有在线会议人员）
typedef struct ChannelHeader {
	EDirectionType	_eDirectionType;	// 方向类型
	UINT32			_cMcuIDCount;		// mcu数量，若_eDirectionType为_eSingle，则为要组播的数量，若为_eBroadcast，则为不要组播的数量
	//  以下消息体：_lMcuID1..._lMcuIDn为mcuID组播集合，即由mcuID组成
	//	UINT32	_lMcuID1;					// 第一个mcuID
	//	...
	//	UINT32	_lMcuIDn;					// 第n个mcuID（即sessionID，这里的mcuID和sessionID是一回事，注意数据库的分配）
} _tChannelHeader;


#endif 
