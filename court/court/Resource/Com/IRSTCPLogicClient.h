// IRSTCPLogicClient.h: interface for the IRSTCPLogicClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRSTCPLOGICCLIENT_H__70F794C8_5F27_4F11_A3CA_0164FF62C954__INCLUDED_)
#define AFX_IRSTCPLOGICCLIENT_H__70F794C8_5F27_4F11_A3CA_0164FF62C954__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRSClientNotify.h"
#include "IRSClient.h"

// add by davy 2005-12-30
#include "../../Include/RSMTMCU/RSMTMCUManager.h"
// end
#include "Config.h" // test

#define DESKCONTROL 1
//#define NETTVANDBROADCAST 1
//#define TESTVIDEO 1

class IRSTCPLogicClient 
	: public CWnd 
	, public IRSClient
	, public IRSTcpClientMsgNotify
	, public AVBufferPool
{
	DECLARE_DYNAMIC(IRSTCPLogicClient)
public:
	IRSTCPLogicClient(IRSClientNotify &rNotify);
	virtual ~IRSTCPLogicClient();

protected:
	DECLARE_MESSAGE_MAP()



public:
	afx_msg LRESULT OnCommandNotify(WPARAM wParam, LPARAM lParam);

public:
	Config			*m_pConf;
	RSMTMCUManager	*m_pMcuManager;
	// 对外 接口 
	std::string		m_strUserID;
	UINT32			m_iConferenceID;	// 当前会议ID
	UINT32			m_iSpeakSessionID;  // 当前发言人ID
	bool			m_bLogined;
	bool			m_bLoginedConference;
	bool		m_bLoginFailed;

private:
	IRSClientNotify *m_pIRSClientNotify;
	bool Start(void);
	TCHAR *GetFilePath(TCHAR *file, TCHAR *path);
	bool			m_bTcp;

	void OnUserLogin(UINT32 iMcuID, char*pData,int nLen);
	void ProcessCommand(UINT32 iCmdID, UINT32 iMcuID, char*pData,int nLen);

	void OnFetchMcuInfo(UINT32 iMcuID, char*pData,int nLen);
	void OnFetchMcuInfoEnd(UINT32 iMcuID, char*pData,int nLen);
	void OnFetchConferenceBaseInfo(UINT32 iMcuID, char*pData,int nLen);
	void OnFetchConferenceBaseInfoEnd(UINT32 iMcuID, char*pData,int nLen);
		void OnFetchConferenceUserInfo(UINT32 iMcuID, char*pData,int nLen);

public:

protected:
	// 来自    IRSClientNotify 接口 
	void OnRSTcpClientMsgNotifyConnected(void);
	void OnRSTcpClientMsgNotifyConnectFailed(void);
	void OnRSTcpClientMsgNotifyDisconnected(void);
	void OnRSTcpClientMsgNotifyInitialized(UINT32 iMcuID);
	void OnRSTcpClientMsgNotifyInitFailed(void);
	void OnRSTcpClientMsgNotifyException(void);
	void OnRSTcpClientMsgNotifyReceivedData(const void*pData,int nLen);

	virtual void OnRSTcpClientCreateChannelNotifyException(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame);
	virtual void OnRSTcpClientCreateChannelNotifyConnected(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame);
	virtual void OnRSTcpClientCreateChannelNotifyConnectFailed(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame);
	virtual void OnRSTcpClientCreateChannelNotifyInitialized(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame);
	virtual void OnRSTcpClientCreateChannelNotifyInitFailed(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame);
	virtual void OnRSTcpClientCreateChannelNotifyDisconnected(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame);
	void OnSendConferenceTemplet(UINT32 iMcuID, char*pData,int nLen);
	void OnSendConferenceMember(UINT32 iMcuID, char*pData,int nLen);

public:
	// 来自    IRSClient 接口 
	virtual bool Connect(const char*cszMCUHost,unsigned __int16 iMCUPort); //连接MCU
	 
	virtual bool SendLogin(const char*cszUserID,const char*cszPassword,byte iOnlineFlag); //发登陆信息
	virtual bool FecthMCU(void);		//请求MCU
	virtual bool SendLoginConference(unsigned __int32 iConferenceID,byte iFrameResource=1);//登陆会议	
	virtual bool FecthVOD(){return true;}				//请求VOD服务器数据
	virtual bool FetchConferenceList(void);	//请求会议列表

	virtual void SoundDriverArray(CTSoundDriverInfoArray *paTSoundDriverInfoArray){}	//声卡驱动
	virtual void VideoDriverArray(CTVideoDriverInfoArray *paTVideoDriverInfoArray){}	//视频驱动

	virtual void ChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray){}		//改变视音频格式

	virtual void FetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray){}	//请求会议人员数
	virtual void LogoutConference(void){}	//退出会议
	virtual void LogoutSystem(void);	//退出系统
	virtual void ChangeConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType){} //改变模板

	virtual void ChangeName(const char *cszName){} //改变用户名
	virtual void ChangePassword(const char*cszUserID,const char*cszPassword){} //改变用户密码

	virtual void AskSpeak(){}//演讲请求
	virtual void AllowSpeak(unsigned __int32 iSessionID){}//广播允许谁演讲
	virtual void CloseSpeak(unsigned __int32 iSessionID){}//广播关闭谁演讲
	virtual void AllowKinescope(){}//允许录像
	virtual void ForbidKinescope(){}//不允许录像
	virtual void AllowControl(){}//允许控制
	virtual void ForbidControl(){}//不允许控制
	virtual void SetTalk(byte iTalkControl){}//讨论设置
	virtual void AllowUseWhiteBoard(){}		//允许使用白板
	virtual void ForbidUseWhiteBoard(){}		//不允许使用白板
	virtual void AllowFloatDrag(){}		//允许改变浮动窗口
	virtual void ForbidFloatDrag(){}		//不允许改变浮动窗口
	virtual void AllowAskTalk(){}			//允许请求发言
	virtual void ForbidAskTalk(){}			//不允许请求发言
	virtual void AllowAskScreenControl(){}			//允许屏幕共享控制
	virtual void ForbidAskScreenControl(){}			//不允许屏幕共享控制

	virtual void AllowKinescope(unsigned __int32 iSessionID){}//允许谁录像
	virtual void ForbidKinescope(unsigned __int32 iSessionID){}//不允许谁录像
	virtual void AllowControl(unsigned __int32 iSessionID){}//允许谁控制
	virtual void ForbidControl(unsigned __int32 iSessionID){}//不允许谁控制
	virtual void SetTalk(unsigned __int32 iSessionID,byte iTalkControl){}//谁的讨论设置
	virtual void AllowUseWhiteBoard(unsigned __int32 iSessionID){}		//允许谁使用白板
	virtual void ForbidUseWhiteBoard(unsigned __int32 iSessionID){}		//不允许谁使用白板
	virtual void AllowFloatDrag(unsigned __int32 iSessionID){}		//允许浮动窗口拖动
	virtual void ForbidFloatDrag(unsigned __int32 iSessionID){}		//不允许浮动窗口拖动
	virtual void AllowAskTalk(unsigned __int32 iSessionID){}			//允许请求发言
	virtual void ForbidAskTalk(unsigned __int32 iSessionID){}			//不允许请求发言
	virtual void AllowAskScreenControl(unsigned __int32 iSessionID){}			//允许请求屏幕控制
	virtual void ForbidAskScreenControl(unsigned __int32 iSessionID){}			//不允许屏幕控制

	virtual void SetBull(const char* cszBullData){}//设置字幕内容
	virtual void IssueBull(){}//广播打开字幕
	virtual void CloseBull(){}//广播关闭字幕
	virtual void OpenTalkOver(byte iWinNo,byte iFrameNo){}//广播打开讨论区
	virtual void CloseTalkOver(){}//广播关闭讨论区
	virtual void TalkOverData(const char *cszTalkOverData,byte iTalkControl){}//讨论信息
	virtual void OpenWhiteBoard(byte iWinNo,byte iFrameNo){}//广播打开白板
	virtual void WhiteBoardData(const char* cszWhiteBoardData){}//广播白板动作数据包
	virtual void CloseWhiteBoard(){}//广播关闭白板
	virtual void OpenScreen(byte iWinNo,byte iFrameNo){}//广播打开屏幕
	virtual void ScreenData(const char* cszWhiteBoardData){}//广播屏幕动作数据包
	virtual void CloseScreen(){}//广播关闭屏幕
	virtual void InviteUser(unsigned __int32 iSessionID){}//邀请已登陆的人员参会
	virtual void OpenShareMedia(byte iWinNo,byte iFrameNo){}//广播打开共享媒体
	virtual void CloseShareMedia(){}//广播关闭共享媒体

	virtual void InceptVideo(unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,bool bRepetition=false,unsigned __int32 iPresideSessionID=0){}//接收视频
	virtual void FullWin(unsigned __int32 iPresideSessionID,byte iUserCardNo){}//视频已满
	virtual void CloseVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false){}//关闭接收视频
	virtual void CloseVideoChannel(unsigned __int32 iChannelID){}//关闭视频通道
	virtual void BroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,bool bRepetition=false){}//广播设广播视频
	virtual void CloseBroadcastVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false){}//广播关闭广播视频
	virtual void InceptSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iPresideSessionID=0){}//接收音频
	virtual void CloseSound(unsigned __int32 iSessionID,byte iUserCardNo){}//关闭接收音频
	virtual void CloseSoundChannel(unsigned __int32 iChannelID){}//关闭音频通道
	virtual void BroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo){}//广播设广播音频
	virtual void CloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo){}//广播关闭广播音频

	virtual void SwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex){}		//广播拖动谁
	virtual void SelectMainFrame(byte ucUserFrameIndex){}		//选择主屏

	virtual void SendControlCommand(unsigned __int32 iSessionID,byte iUserCardNo,unsigned __int32 iCommand){}		//云台控制
	virtual void SendControlSpeed(unsigned __int32 iSessionID,byte iUserCardNo,byte ucSpeed){}						//云台速度

	virtual void VideoOrder(unsigned __int32 iSessionID){}//广播视频预置

	virtual void AskToProlocutor(){}	//申请成为发言人
	virtual void SetProlocutor(unsigned __int32 iSessionID){}	//设为发言人
	virtual void SetNoProlocutor(unsigned __int32 iSessionID){}	//设为非发言人
	virtual void DeleteProlocutor(unsigned __int32 iSessionID){}	//删除发言人

	virtual void OpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo){}		//打开浮动窗
	virtual void CloseFloatWin(){}		//关闭浮动窗
	virtual void SetFloatWinRect(unsigned __int16 iFloatWinRect[6]){}		//设置浮动窗位置

	virtual void SetBandwidth(unsigned __int16 iBandwidth){}		//限制的带宽

	virtual void ConferenceSynchronization(){}		//会议同步
	virtual void SetWatchUser(unsigned __int32 iSessionID){}		//设监控人员
	virtual void CloseWatchUser(){}		//关闭监控人员

	virtual void AllowWatchUserControl(){}				//允许监控员控制
	virtual void ForbidWatchUserControl(){}				//不允许监控员控制

	virtual void SetFullScreen(){}	//设共享屏幕全屏
	virtual void CloseFullScreen(){}//广播关闭全屏屏幕

	virtual void StartFile(const char* cFileName){}	//开始文件分发
	virtual void CloseFile(const char* cFileName){}	//关闭文件分发

	virtual void TestMcuBandwidth(){} //测试网络带宽

	virtual void OpenConferenceTopic(){}	//打开会议标题
	virtual void CloseConferenceTopic(){}//关闭会议标题

	virtual void QuitMySystem(unsigned __int32 iSessionID){}//强行退出系统

	virtual void AllowInConference(){}		//允许不在线人员进入会议
	virtual void ForbidInConference(){}		//不允许不在线人员进入会议

	virtual void Calling(){}				//发起点名
	virtual void CloseCalling(){}			//结束点名
	virtual void CallingInConference(){}	//点名确认

	virtual void P2PData(UINT32 iSessionID, const char * pData, int iLen){} //发送点对点数据
	virtual void BroadcastData(UINT32 iSessionID,const char * pData, int iLen){} //广播数据


	virtual void SetLinkage(byte iLinkage=1){}	//设置屏幕联动	0:不联动 1:联动
			void OnP2PData(UINT32 iMcuID, char*pData,int nLen);   //点对点数据回调
				void OnBroadcastSelectMainFrame(UINT32 iMcuID, char*pData,int nLen);


};

//extern IRSTCPLogicClient*g_pIRSTCPLogicClient=NULL;

#endif // !defined(AFX_IRSTCPLOGICCLIENT_H__70F794C8_5F27_4F11_A3CA_0164FF62C954__INCLUDED_)
