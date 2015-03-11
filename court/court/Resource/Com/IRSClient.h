// IRSClient.h: interface for the IRSClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRSCLIENT_H__8C758EE0_772E_494B_912E_3FF6C720A601__INCLUDED_)
#define AFX_IRSCLIENT_H__8C758EE0_772E_494B_912E_3FF6C720A601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DataDefine/ResourceDefine.h"

class IRSClient  
{
public:
	IRSClient(){};
	virtual ~IRSClient(){};

	public:
	virtual bool Connect(const char*cszMCUHost,unsigned __int16 iMCUPort)=0;//连接MCU
	virtual bool SendLogin(const char*cszUserID,const char*cszPassword,byte iOnlineFlag)=0;	//发登陆信息
	virtual bool FecthMCU(void)=0;			//请求MCU
	virtual bool SendLoginConference(unsigned __int32 iConferenceID,byte iFrameResource=1)=0;	//登陆会议	

	virtual void SoundDriverArray(CTSoundDriverInfoArray *paTSoundDriverInfoArray)=0;		//声卡驱动
	virtual void VideoDriverArray(CTVideoDriverInfoArray *paTVideoDriverInfoArray)=0;		//视频驱动

	virtual void ChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray)=0;			//改变视音频格式
	
	virtual bool FetchConferenceList(void)=0;		//请求会议列表
	virtual void FetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray)=0;		//请求会议人员数
	virtual void LogoutConference(void)=0;		//退出会议
	virtual void LogoutSystem(void)=0;			//退出系统
	virtual void ChangeConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType)=0; //改变模板

	virtual void ChangeName(const char *cszName)=0; //改变用户名
	virtual void ChangePassword(const char*cszUserID,const char*cszPassword)=0; //改变用户密码
	
	virtual void AskSpeak()=0;	//演讲请求
	virtual void AllowSpeak(unsigned __int32 iSessionID)=0;	//广播允许谁演讲
	virtual void CloseSpeak(unsigned __int32 iSessionID)=0;	//广播关闭谁演讲
	virtual void AllowKinescope()=0;	//允许录像
	virtual void ForbidKinescope()=0;	//不允许录像
	virtual void AllowControl()=0;	//允许控制
	virtual void ForbidControl()=0;	//不允许控制
	virtual void SetTalk(byte iTalkControl)=0;	//讨论设置
	virtual void AllowUseWhiteBoard()=0;			//允许使用白板
	virtual void ForbidUseWhiteBoard()=0;			//不允许使用白板
	virtual void AllowFloatDrag()=0;			//允许改变浮动窗口
	virtual void ForbidFloatDrag()=0;			//不允许改变浮动窗口
	virtual void AllowAskTalk()=0;				//允许请求发言
	virtual void ForbidAskTalk()=0;				//不允许请求发言
	virtual void AllowAskScreenControl()=0;				//允许屏幕共享控制
	virtual void ForbidAskScreenControl()=0;				//不允许屏幕共享控制

	virtual void AllowKinescope(unsigned __int32 iSessionID)=0;	//允许谁录像
	virtual void ForbidKinescope(unsigned __int32 iSessionID)=0;	//不允许谁录像
	virtual void AllowControl(unsigned __int32 iSessionID)=0;	//允许谁控制
	virtual void ForbidControl(unsigned __int32 iSessionID)=0;	//不允许谁控制
	virtual void SetTalk(unsigned __int32 iSessionID,byte iTalkControl)=0;	//谁的讨论设置
	virtual void AllowUseWhiteBoard(unsigned __int32 iSessionID)=0;			//允许谁使用白板
	virtual void ForbidUseWhiteBoard(unsigned __int32 iSessionID)=0;			//不允许谁使用白板
	virtual void AllowFloatDrag(unsigned __int32 iSessionID)=0;			//允许浮动窗口拖动
	virtual void ForbidFloatDrag(unsigned __int32 iSessionID)=0;			//不允许浮动窗口拖动
	virtual void AllowAskTalk(unsigned __int32 iSessionID)=0;				//允许请求发言
	virtual void ForbidAskTalk(unsigned __int32 iSessionID)=0;				//不允许请求发言
	virtual void AllowAskScreenControl(unsigned __int32 iSessionID)=0;				//允许请求屏幕控制
	virtual void ForbidAskScreenControl(unsigned __int32 iSessionID)=0;				//不允许屏幕控制
	
	virtual void SetBull(const char* cszBullData)=0;	//设置字幕内容
	virtual void IssueBull()=0;	//广播打开字幕
	virtual void CloseBull()=0;	//广播关闭字幕
	virtual void OpenTalkOver(byte iWinNo,byte iFrameNo)=0;	//广播打开讨论区
	virtual void CloseTalkOver()=0;	//广播关闭讨论区
	virtual void TalkOverData(const char *cszTalkOverData,byte iTalkControl)=0;	//讨论信息
	virtual void OpenWhiteBoard(byte iWinNo,byte iFrameNo)=0;	//广播打开白板
	virtual void WhiteBoardData(const char* cszWhiteBoardData)=0;	//广播白板动作数据包
	virtual void CloseWhiteBoard()=0;	//广播关闭白板
	virtual void OpenScreen(byte iWinNo,byte iFrameNo)=0;	//广播打开屏幕
	virtual void ScreenData(const char* cszWhiteBoardData)=0;	//广播屏幕动作数据包
	virtual void CloseScreen()=0;	//广播关闭屏幕
	virtual void InviteUser(unsigned __int32 iSessionID)=0;	//邀请已登陆的人员参会
	virtual void OpenShareMedia(byte iWinNo,byte iFrameNo)=0;	//广播打开共享媒体
	virtual void CloseShareMedia()=0;	//广播关闭共享媒体

	virtual void InceptVideo(unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,bool bRepetition=false,unsigned __int32 iPresideSessionID=0)=0;	//接收视频
	virtual void FullWin(unsigned __int32 iPresideSessionID,byte iUserCardNo)=0;	//视频已满
	virtual void CloseVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false)=0;	//关闭接收视频
	virtual void CloseVideoChannel(unsigned __int32 iChannelID)=0;	//关闭视频通道
	virtual void BroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,bool bRepetition=false)=0;	//广播设广播视频
	virtual void CloseBroadcastVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false)=0;	//广播关闭广播视频
	virtual void InceptSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iPresideSessionID=0)=0;	//接收音频
	virtual void CloseSound(unsigned __int32 iSessionID,byte iUserCardNo)=0;	//关闭接收音频
	virtual void CloseSoundChannel(unsigned __int32 iChannelID)=0;	//关闭音频通道
	virtual void BroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo)=0;	//广播设广播音频
	virtual void CloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo)=0;	//广播关闭广播音频

	virtual void SwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex)=0;			//广播拖动谁
	virtual void SelectMainFrame(byte ucUserFrameIndex)=0;			//选择主屏

	virtual void SendControlCommand(unsigned __int32 iSessionID,byte iUserCardNo,unsigned __int32 iCommand) = 0;		//云台控制
	virtual void SendControlSpeed(unsigned __int32 iSessionID,byte iUserCardNo,byte ucSpeed) = 0;						//云台速度
	
	virtual void VideoOrder(unsigned __int32 iSessionID)=0;	//广播视频预置

	virtual void AskToProlocutor()=0;		//申请成为发言人
	virtual void SetProlocutor(unsigned __int32 iSessionID)=0;		//设为发言人
	virtual void SetNoProlocutor(unsigned __int32 iSessionID)=0;		//设为非发言人
	virtual void DeleteProlocutor(unsigned __int32 iSessionID)=0;		//删除发言人

	virtual void OpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo)=0;			//打开浮动窗
	virtual void CloseFloatWin()=0;			//关闭浮动窗
	virtual void SetFloatWinRect(unsigned __int16 iFloatWinRect[6])=0;			//设置浮动窗位置

	virtual void SetBandwidth(unsigned __int16 iBandwidth)=0;			//限制的带宽

	virtual void ConferenceSynchronization()=0;			//会议同步
	virtual void SetWatchUser(unsigned __int32 iSessionID)=0;			//设监控人员
	virtual void CloseWatchUser()=0;			//关闭监控人员

	virtual void AllowWatchUserControl()=0;					//允许监控员控制
	virtual void ForbidWatchUserControl()=0;					//不允许监控员控制

	virtual void SetFullScreen()=0;		//设共享屏幕全屏
	virtual void CloseFullScreen()=0;	//广播关闭全屏屏幕

	virtual void StartFile(const char* cFileName)=0;		//开始文件分发
	virtual void CloseFile(const char* cFileName)=0;		//关闭文件分发

	virtual void TestMcuBandwidth()=0; //测试网络带宽

	virtual void OpenConferenceTopic()=0;		//打开会议标题
	virtual void CloseConferenceTopic()=0;	//关闭会议标题

	virtual void QuitMySystem(unsigned __int32 iSessionID)=0;	//强行退出系统

	virtual void AllowInConference()=0;			//允许不在线人员进入会议
	virtual void ForbidInConference()=0;			//不允许不在线人员进入会议

	virtual void Calling()=0;					//发起点名
	virtual void CloseCalling()=0;				//结束点名
	virtual void CallingInConference()=0;		//点名确认
	
	virtual void P2PData(UINT32 iSessionID, const char * pData, int iLen)=0; //发送点对点数据
	virtual void BroadcastData(UINT32 iSessionID,const char * pData, int iLen)=0; //广播数据

	virtual bool FecthVOD()=0;					//请求VOD服务器数据

	virtual void SetLinkage(byte iLinkage=1)=0;		//设置屏幕联动	0:不联动 1:联动
};

#endif // !defined(AFX_IRSCLIENT_H__8C758EE0_772E_494B_912E_3FF6C720A601__INCLUDED_)
