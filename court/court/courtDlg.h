
// courtDlg.h : 头文件
//

#pragma once
#include "Resource/Com/IRSClient.h"
#include "Resource/Com/IRSClientNotify.h"

#include "DlgPMosaicScreenADScreen.h"

// CcourtDlg 对话框
class CcourtDlg
	: public CDialogEx
	, public IRSClientNotify

{
	// 构造
public:
	CcourtDlg(CWnd* pParent = NULL);	// 标准构造函数

	~CcourtDlg()
	{
		if (m_pIRSClient)
		{ 
			m_pIRSClient->LogoutSystem();
			delete m_pIRSClient;
			m_pIRSClient=NULL;
		}
	}
	// 对话框数据
	enum { IDD = IDD_COURT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	void LoginConference(unsigned __int32	iConferenceID);

protected:
	void FetchConferenceList();
	void RemoveConferenceInfoArray();
		void SendVideoDriver();						//发送视音驱动
	void SendSoundDriver();						//发送声卡驱动
	// 实现
public:
	HICON m_hIcon;

	CTConferenceUserInfoArray m_aConferenceUserInfoArray;
	CTConferenceInfoArray m_aConferenceInfoArray;
	IRSClient*		m_pIRSClient;
	TLocalUserInfo *m_ptLocalUserInfo;
	void InitDlg();								//初始化对话框
	CDlgPMosaicScreenADScreen *m_pDlgPMosaicScreenPADScreen;									//法官平板窗口

	void InitClient();
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


	//////////////////////////////////////////////////////////////////////////
	virtual void OnAVSPlayerNotify_PlayEvent(unsigned long ulParam1, unsigned long ulParam2){};

	//////////////////////////////////////////////////////////////////////////
	virtual void OnConnected(unsigned __int32 iMCUID);//连接MCU成功，Call SendLogin
	virtual void OnConnectTimeout();//连接MCU超时
	virtual void OnDisconnected();//连接断开
	virtual void OnLogin(int nResult,unsigned __int32 iSessionID,const char*cszUserName);//Call FecthMCU
	virtual void OnMCUItem(TMCUInfo *tMCUInfo);//从根节点开始
	virtual void OnMCUEnd();//FetchConferenceList
	virtual void OnConferenceListItem(TConferenceBaseInfo *tConferenceBaseInfo);
	virtual void OnConferenceListEnd();
	virtual void OnFetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray){};		//请求会议人员数
	virtual void OnSendLoginConference(byte iUserStatus);		//回调人员身份
	virtual void OnConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,
		byte iWinNumber,byte iWinType,byte iFrameResource=1){};	
	//ucTempletType:为屏类型
	virtual void OnSoundDriverArray(unsigned __int32 iSessionID,
		CTSoundDriverInfoArray *paTSoundDriverInfoArray){};		//声卡驱动

	virtual void OnVideoDriverArray(unsigned __int32 iSessionID,
		CTVideoDriverInfoArray *paTVideoDriverInfoArray){};		//视频驱动

	virtual void OnChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,
		byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray){};			//改变视音频格式

	virtual void OnChangeName(unsigned __int32 iSessionID,const char *cszName){}; //改变用户名

	virtual void OnConferenceMember(unsigned __int32 iSessionID,const char*cszUserID,byte iUserStatus,const char*csUserName,unsigned __int32 iMCUID);
	virtual void OnConferenceMemberPresence(unsigned __int32 iSessionID,byte iOnlineFlag,
		unsigned __int32 iMCUID,const char *strOnlineTime){};

	virtual void OnConferenceMemberEnter(unsigned __int32 iSessionID){};
	virtual void OnConferenceMemberLeave(unsigned __int32 iSessionID){};
	virtual void OnLoginOutSystem(unsigned __int32 iSessionID){};
	virtual void OnDeleteConferenceUser(unsigned __int32 iSessionID){};		//删除的人员

	virtual void OnAskSpeak(unsigned __int32 iSessionID){};	//演讲请求
	virtual void OnAllowSpeak(unsigned __int32 iSessionID){};	//设为演讲人
	virtual void OnCloseSpeak(unsigned __int32 iSessionID){};	//关闭谁演讲
	virtual void OnAllowKinescope(){};	//允许录像
	virtual void OnForbidKinescope(){};	//不允许录像
	virtual void OnAllowControl(){};	//允许控制
	virtual void OnForbidControl(){};	//不允许控制
	virtual void OnSetTalk(byte iTalkControl){};	//讨论设置
	virtual void OnAllowUseWhiteBoard(){};			//允许使用白板
	virtual void OnForbidUseWhiteBoard(){};			//不允许使用白板
	virtual void OnAllowAskScreenControl(){};
	virtual void OnForbidAskScreenControl(){};
	virtual void OnAllowFloatDrag(){};			//允许改变浮动窗口
	virtual void OnForbidFloatDrag(){};			//不允许改变浮动窗口
	virtual void OnAllowAskTalk(){};				//允许请求发言
	virtual void OnForbidAskTalk(){};				//不允许请求发言

	virtual void OnAllowKinescope(unsigned __int32 iSessionID){};	//允许谁录像
	virtual void OnForbidKinescope(unsigned __int32 iSessionID){};	//不允许谁录像
	virtual void OnAllowControl(unsigned __int32 iSessionID){};	//允许谁控制
	virtual void OnForbidControl(unsigned __int32 iSessionID){};	//不允许谁控制
	virtual void OnSetTalk(unsigned __int32 iSessionID,byte iTalkControl){};	//谁的讨论设置
	virtual void OnAllowUseWhiteBoard(unsigned __int32 iSessionID){};			//允许谁使用白板
	virtual void OnForbidUseWhiteBoard(unsigned __int32 iSessionID){};			//不允许谁使用白板
	virtual void OnAllowFloatDrag(unsigned __int32 iSessionID){};			//允许浮动窗口拖动
	virtual void OnForbidFloatDrag(unsigned __int32 iSessionID){};			//不允许浮动窗口拖动
	virtual void OnAllowAskTalk(unsigned __int32 iSessionID){};				//允许请求发言
	virtual void OnForbidAskTalk(unsigned __int32 iSessionID){};				//不允许请求发言
	virtual void OnAllowAskScreenControl(unsigned __int32 iSessionID){};
	virtual void OnForbidAskScreenControl(unsigned __int32 iSessionID){};

	virtual void OnSetBull(const char* cszBullData){};	//设置字幕内容
	virtual void OnIssueBull(){};	//打开字幕
	virtual void OnCloseBull(){};	//关闭字幕
	virtual void OnOpenTalkOver(byte iWinNo,byte iFrameNo,byte iFrameResource=1){};	//打开讨论区
	virtual void OnCloseTalkOver(){};	//关闭讨论区
	virtual void OnTalkOverData(unsigned __int32 iSessionID,const char *cszTalkOverData){};	//讨论信息
	void OnSaveChatHistory(unsigned long ulUserID,CString strUserName,CString strMessage){};
	void ProcessTalkOverData(unsigned __int32 iSessionID,const char *cszTalkOverData,bool bIsIMMsg = false,CString strName = _T("")){};	//讨论信息
	virtual void OnHistoryTalkOverData(const char *cszTalkOverData,unsigned __int32 iLen){};	//历史讨论信息
	virtual void OnOpenWhiteBoard(byte iWinNo,byte iFrameNo,unsigned __int32 iChannelID,byte iFrameResource=1){};	//打开白板
	virtual void OnWhiteBoardData(const char* cszWhiteBoardData){};	//白板动作数据包
	virtual void OnCloseWhiteBoard(){};	//关闭白板
	virtual void OnOpenScreen(unsigned __int32 iSessionID,byte iWinNo,byte iFrameNo,
		unsigned __int32 iChannelID){};	//打开屏幕
	virtual void OnScreenData(const char* cszWhiteBoardData){};	//屏幕动作数据包
	virtual void OnCloseScreen(unsigned __int32 iSessionID){};	//关闭屏幕
	virtual void OnInviteUser(unsigned __int32 iConferenceID){};	//被邀请参会
	virtual void OnOpenShareMedia(byte iWinNo,byte iFrameNo){};	//打开共享媒体
	virtual void OnCloseShareMedia(){};	//关闭共享媒体

	virtual void OnInceptVideo(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,
		byte ucUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,unsigned __int32 iChannelID,bool bRepetition=false){};	//接收视频
	virtual void OnCloseVideo(byte iUserCardNo,bool bRepetition=false){};			//关闭发送视频

	virtual void OnFullWin(unsigned __int32 iSessionID,byte ucUserCardNo){};	//窗口已满
	virtual void OnBroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,
		byte ucUserFrameIndex,byte ucUserCardNo,unsigned __int32 iChannelID,bool bRepetition=false,byte iFrameResource=1){};	//广播设广播视频

	virtual void OnCloseBroadcastVideo(unsigned __int32 iSessionID,byte ucUserCardNo,bool bRepetition=false,byte iFrameResource=1){};	//广播关闭广播视频
	virtual void OnInceptSound(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,
		byte iUserCardNo,unsigned __int32 iChannelID){};	//接收音频
	virtual void OnCloseSound(byte iUserCardNo){};	//关闭发送音频

	virtual void OnBroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,
		byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iChannelID,byte iFrameResource=1){};	//广播设广播音频


	virtual void OnSwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,
		byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex){};			//广播拖动谁

	virtual void OnSelectMainFrame(byte ucUserFrameIndex);			//选择主屏

	virtual void OnSendControlCommand(byte iUserCardNo,unsigned __int32 iCommand){};		//云台控制
	virtual void OnSendControlSpeed(byte iUserCardNo,byte ucSpeed){};						//云台速度

	virtual void OnVideoOrder(unsigned __int32 iSessionID){};	//广播视频预置

	virtual void OnAskToProlocutor(unsigned __int32 iSessionID){};		//申请成为发言人
	virtual void OnSetProlocutor(unsigned __int32 iSessionID){};		//设为发言人
	virtual void OnSetNoProlocutor(unsigned __int32 iSessionID){};		//设为非发言人
	virtual void OnDeleteProlocutor(unsigned __int32 iSessionID){};		//删除发言人

	virtual void OnOpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo){};			//打开浮动窗
	virtual void OnCloseFloatWin(){};			//关闭浮动窗
	virtual void OnSetFloatWinRect(unsigned __int16 iFloatWinRect[6]){};			//设置浮动窗位置

	virtual void OnSetBandwidth(unsigned __int16 iBandwidth){};			//限制的带宽

	virtual void OnSetWatchUser(unsigned __int32 iSessionID){};			//设监控人员
	virtual void OnCloseWatchUser(){};			//关闭监控人员

	virtual void OnAllowWatchUserControl(){};					//允许监控员控制
	virtual void OnForbidWatchUserControl(){};					//不允许监控员控制

	virtual void OnSetFullScreen(unsigned __int32 iSessionID){};		//设共享屏幕全屏
	virtual void OnCloseFullScreen(unsigned __int32 iSessionID){};	//广播关闭全屏屏幕

	virtual void OnOffOnlineSystem(){};	//强行注销系统
	virtual void OnQuitMySystem(){};	//强行退出系统

	virtual void OnStartFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID){};		//开始文件分发
	virtual void OnCloseFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID){};		//关闭文件分发
	virtual void OnFileExist(const char* cFileName){};            //文件已存在

	virtual void OnTestMcuBandwidth(int iDirection, unsigned __int32 iMcuBandwidth){};				//测试网络带宽

	virtual void OnOpenConferenceTopic(){};		//打开会议标题
	virtual void OnCloseConferenceTopic(){};	//关闭会议标题

	virtual void OnAllowInConference(){};			//允许不在线人员进入会议
	virtual void OnForbidInConference(){};			//不允许不在线人员进入会议

	virtual void OnCloseConference(unsigned __int32 iConferenceID){};		//会议结束

	virtual void OnCalling(unsigned __int32 iSessionID){};						//发起点名
	virtual void OnCloseCalling(unsigned __int32 iSessionID){};				//结束点名

	virtual void OnP2PData(UINT32 iSessionID, const char * pData, int Len);
	virtual void OnBroadcastData(UINT32 iSessionID, const char * pData, int iLen){}; //广播数据

	virtual void OnVODItem(TVODInfo *tInfo){};				//VOD服务器数据
	virtual void OnVODEnd(){};								//VOD服务器数据结束

	virtual void OnSetLinkage(byte iLinkage=1){};		//设置屏幕联动	0:不联动 1:联动
	virtual void OnSetFrameResource(byte ucUserFrameIndex){};	//强制指定资源


	virtual void OnCloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo,byte iFrameResource=1){};	//广播关闭广播视频

};
