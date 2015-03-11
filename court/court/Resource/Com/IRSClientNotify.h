// IRSClientNotify.h: interface for the IRSClientNotify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRSCLIENTNOTIFY_H__80E365B9_51CC_44CF_B40B_D410722E7D00__INCLUDED_)
#define AFX_IRSCLIENTNOTIFY_H__80E365B9_51CC_44CF_B40B_D410722E7D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DataDefine/ResourceDefine.h"

class IRSClientNotify  
{
public:
	IRSClientNotify(){};
	virtual ~IRSClientNotify(){};
public:
	virtual void OnConnected(unsigned __int32 iMCUID)=0;//连接MCU成功，Call SendLogin
	virtual void OnConnectTimeout(void)=0;//连接MCU超时
	virtual void OnDisconnected(void)=0;//连接断开
	virtual void OnLogin(int nResult,unsigned __int32 iSessionID,const char*cszUserName)=0;//登路返回
	virtual void OnMCUItem(TMCUInfo *tMCUInfo)=0;//从根节点开始
	virtual void OnMCUEnd(void)=0;//MUC结束 SendPresence,FetchConferenceList
	virtual void OnConferenceListItem(TConferenceBaseInfo *tConferenceBaseInfo)=0; //会议列表
	virtual void OnConferenceListEnd(void)=0;	//会议列表已传完
	virtual void OnFetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray)=0;		//请求会议人员数
	virtual void OnSendLoginConference(byte iUserStatus)=0;		//回调人员身份
	virtual void OnConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType,byte iFrameResource=1)=0;	//会议模板 ucScreenType:前4位为一号屏种类1，2，3，后4位为二号屏种类1，2
																							//ucTempletType:为屏类型
	virtual void OnSoundDriverArray(unsigned __int32 iSessionID,CTSoundDriverInfoArray *paTSoundDriverInfoArray)=0;		//声卡驱动
	virtual void OnVideoDriverArray(unsigned __int32 iSessionID,CTVideoDriverInfoArray *paTVideoDriverInfoArray)=0;		//视频驱动

	virtual void OnChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray)=0;			//改变视音频格式

	virtual void OnChangeName(unsigned __int32 iSessionID,const char *cszName)=0; //改变用户名
		
	//virtual void OnConferenceMember(unsigned __int32 iSessionID,const char*cszUserID,byte iUserStatus,const char*csUserName,unsigned __int32 iMCUID)=0;	//会议人员
	//virtual void OnConferenceMemberPresence(unsigned __int32 iSessionID,byte iOnlineFlag,const char *strOnlineTime)=0;  //在线人员

	virtual void OnConferenceMember(unsigned __int32 iSessionID,const char*cszUserID,byte iUserStatus,const char*csUserName,unsigned __int32 iMCUID)=0;	//会议人员
	virtual void OnConferenceMemberPresence(unsigned __int32 iSessionID,byte iOnlineFlag,unsigned __int32 iMCUID,const char *strOnlineTime)=0;  //在线人员
	virtual void OnConferenceMemberEnter(unsigned __int32 iSessionID)=0;	//进入了会议的人员
	virtual void OnConferenceMemberLeave(unsigned __int32 iSessionID)=0;	//离开了会议的人员
	virtual void OnLoginOutSystem(unsigned __int32 iSessionID)=0;			//下线的人员
	virtual void OnDeleteConferenceUser(unsigned __int32 iSessionID)=0;		//删除的人员

	virtual void OnAskSpeak(unsigned __int32 iSessionID)=0;	//演讲请求
	virtual void OnAllowSpeak(unsigned __int32 iSessionID)=0;	//设为演讲人
	virtual void OnCloseSpeak(unsigned __int32 iSessionID)=0;	//关闭谁演讲
	virtual void OnAllowKinescope()=0;	//允许录像
	virtual void OnForbidKinescope()=0;	//不允许录像
	virtual void OnAllowControl()=0;	//允许控制
	virtual void OnForbidControl()=0;	//不允许控制
	virtual void OnSetTalk(byte iTalkControl)=0;	//讨论设置
	virtual void OnAllowUseWhiteBoard()=0;			//允许使用白板
	virtual void OnForbidUseWhiteBoard()=0;			//不允许使用白板
	virtual void OnAllowFloatDrag()=0;			//允许改变浮动窗口
	virtual void OnForbidFloatDrag()=0;			//不允许改变浮动窗口
	virtual void OnAllowAskTalk()=0;				//允许请求发言
	virtual void OnForbidAskTalk()=0;				//不允许请求发言
	virtual void OnAllowAskScreenControl()=0;				//允许请求发言
	virtual void OnForbidAskScreenControl()=0;				//不允许请求发言
	
	virtual void OnAllowKinescope(unsigned __int32 iSessionID)=0;	//允许谁录像
	virtual void OnForbidKinescope(unsigned __int32 iSessionID)=0;	//不允许谁录像
	virtual void OnAllowControl(unsigned __int32 iSessionID)=0;	//允许谁控制
	virtual void OnForbidControl(unsigned __int32 iSessionID)=0;	//不允许谁控制
	virtual void OnSetTalk(unsigned __int32 iSessionID,byte iTalkControl)=0;	//谁的讨论设置
	virtual void OnAllowUseWhiteBoard(unsigned __int32 iSessionID)=0;			//允许使用白板
	virtual void OnForbidUseWhiteBoard(unsigned __int32 iSessionID)=0;			//不允许使用白板
	virtual void OnAllowFloatDrag(unsigned __int32 iSessionID)=0;			//允许浮动窗口拖动
	virtual void OnForbidFloatDrag(unsigned __int32 iSessionID)=0;			//不允许浮动窗口拖动
	virtual void OnAllowAskTalk(unsigned __int32 iSessionID)=0;				//允许请求发言
	virtual void OnForbidAskTalk(unsigned __int32 iSessionID)=0;				//不允许请求发言
	virtual void OnAllowAskScreenControl(unsigned __int32 iSessionID)=0;				//允许请求屏幕控制
	virtual void OnForbidAskScreenControl(unsigned __int32 iSessionID)=0;				//不允许请求屏幕控制

	virtual void OnSetBull(const char* cszBullData)=0;	//设置字幕内容
	virtual void OnIssueBull()=0;	//打开字幕
	virtual void OnCloseBull()=0;	//关闭字幕
	virtual void OnOpenTalkOver(byte iWinNo,byte iFrameNo,byte iFrameResource=1)=0;	//打开讨论区
	virtual void OnCloseTalkOver()=0;	//关闭讨论区
	virtual void OnTalkOverData(unsigned __int32 iSessionID,const char *cszTalkOverData)=0;	//讨论信息
	virtual void OnHistoryTalkOverData(const char *cszTalkOverData,unsigned __int32 iLen)=0;	//历史讨论信息
	virtual void OnOpenWhiteBoard(byte iWinNo,byte iFrameNo,unsigned __int32 iChannelID,byte iFrameResource=1)=0;	//打开白板
	virtual void OnWhiteBoardData(const char *cszWhiteBoardData)=0;	//白板动作数据包
	virtual void OnCloseWhiteBoard()=0;	//关闭白板
	virtual void OnOpenScreen(unsigned __int32 iSessionID,byte iWinNo,byte iFrameNo,unsigned __int32 iChannelID)=0;	//打开屏幕
	virtual void OnScreenData(const char* cszWhiteBoardData)=0;	//屏幕动作数据包
	virtual void OnCloseScreen(unsigned __int32 iSessionID)=0;	//关闭屏幕
	virtual void OnInviteUser(unsigned __int32 iConferenceID)=0;	//被邀请参会
	virtual void OnOpenShareMedia(byte iWinNo,byte iFrameNo)=0;	//打开共享媒体
	virtual void OnCloseShareMedia()=0;	//关闭共享媒体

	virtual void OnInceptVideo(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,byte ucUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,unsigned __int32 iChannelID,bool bRepetition=false)=0;	//接收视频
	virtual void OnCloseVideo(byte iUserCardNo,bool bRepetition=false)=0;			//关闭发送视频
	virtual void OnFullWin(unsigned __int32 iSessionID,byte ucUserCardNo)=0;	//视频已满
	virtual void OnBroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte ucUserCardNo,unsigned __int32 iChannelID,bool bRepetition=false,byte iFrameResource=1)=0;	//广播设广播视频
	virtual void OnCloseBroadcastVideo(unsigned __int32 iSessionID,byte ucUserCardNo,bool bRepetition=false,byte iFrameResource=1)=0;	//广播关闭广播视频
	virtual void OnInceptSound(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iChannelID)=0;	//接收音频
	virtual void OnCloseSound(byte iUserCardNo)=0;	//关闭发送音频
	virtual void OnBroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iChannelID,byte iFrameResource=1)=0;	//广播设广播音频
	virtual void OnCloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo,byte iFrameResource=1)=0;	//广播关闭广播视频

	virtual void OnSwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex)=0;			//广播拖动谁
	virtual void OnSelectMainFrame(byte ucUserFrameIndex)=0;			//选择主屏

	virtual void OnSendControlCommand(byte iUserCardNo,unsigned __int32 iCommand) = 0;		//云台控制
	virtual void OnSendControlSpeed(byte iUserCardNo,byte ucSpeed) = 0;						//云台速度

	virtual void OnVideoOrder(unsigned __int32 iSessionID)=0;	//广播视频预置

	virtual void OnAskToProlocutor(unsigned __int32 iSessionID)=0;		//申请成为发言人
	virtual void OnSetProlocutor(unsigned __int32 iSessionID)=0;		//设为发言人
	virtual void OnSetNoProlocutor(unsigned __int32 iSessionID)=0;		//设为非发言人
	virtual void OnDeleteProlocutor(unsigned __int32 iSessionID)=0;		//删除发言人

	virtual void OnOpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo)=0;			//打开浮动窗
	virtual void OnCloseFloatWin()=0;			//关闭浮动窗
	virtual void OnSetFloatWinRect(unsigned __int16 iFloatWinRect[6])=0;			//设置浮动窗位置

	virtual void OnSetBandwidth(unsigned __int16 iBandwidth)=0;			//限制的带宽

	virtual void OnSetWatchUser(unsigned __int32 iSessionID)=0;			//设监控人员
	virtual void OnCloseWatchUser()=0;			//关闭监控人员

	virtual void OnAllowWatchUserControl()=0;					//允许监控员控制
	virtual void OnForbidWatchUserControl()=0;					//不允许监控员控制

	virtual void OnSetFullScreen(unsigned __int32 iSessionID)=0;		//设共享屏幕全屏
	virtual void OnCloseFullScreen(unsigned __int32 iSessionID)=0;	//广播关闭全屏屏幕

	virtual void OnOffOnlineSystem()=0;	//强行注销系统
	virtual void OnQuitMySystem()=0;	//强行退出系统

	virtual void OnStartFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID)=0;		//开始文件分发
	virtual void OnCloseFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID)=0;      //关闭文件分发
    virtual void OnFileExist(const char* cFileName)=0;            //文件已存在

	virtual void OnTestMcuBandwidth(int iDirection, unsigned __int32 iMcuBandwidth)=0;				//测试网络带宽

	virtual void OnOpenConferenceTopic()=0;		//打开会议标题
	virtual void OnCloseConferenceTopic()=0;	//关闭会议标题

	virtual void OnAllowInConference()=0;			//允许不在线人员进入会议
	virtual void OnForbidInConference()=0;			//不允许不在线人员进入会议

	virtual void OnCloseConference(unsigned __int32 iConferenceID)=0;	//会议结束

	virtual void OnCalling(unsigned __int32 iSessionID)=0;						//发起点名
	virtual void OnCloseCalling(unsigned __int32 iSessionID)=0;				//结束点名

	virtual void OnP2PData(UINT32 iSessionID, const char * pData, int len)=0; //发送点对点数据
	virtual void OnBroadcastData(UINT32 iSessionID, const char * pData, int iLen)=0; //广播数据

	virtual void OnVODItem(TVODInfo *tInfo)=0;				//VOD服务器数据
	virtual void OnVODEnd()=0;								//VOD服务器数据结束

	virtual void OnSetLinkage(byte iLinkage=1)=0;		//设置屏幕联动	0:不联动 1:联动
	virtual void OnSetFrameResource(byte ucUserFrameIndex)=0;	//强制指定资源
};

#endif // !defined(AFX_IRSCLIENTNOTIFY_H__80E365B9_51CC_44CF_B40B_D410722E7D00__INCLUDED_)
