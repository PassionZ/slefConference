#ifndef _HPCHATUI_H
#define _HPCHATUI_H

#define TIMER_SPACE		1000	//呼叫时间间隔

class IHPChatUINotify
{
public:	
	//向ulUserID发送消息
	virtual void OnSendChatMessage(unsigned long ulUserID, CString strMessage)=0;
	//插入分隔符
	virtual void OnInsertMark(unsigned long ulUserID)=0;
	//呼叫ulUserID 返回值0:成功 1：自己在会议 2：对方在会议 3：视频呼叫已满
	virtual int OnCall(unsigned long ulUserID)=0;
	//取消呼叫ulUserID
	virtual void OnCancelCall(unsigned long ulUserID)=0;
	//接受ulUserID的呼叫
	virtual void OnAcceptCall(unsigned long ulUserID)=0;
	//拒绝ulUserID的呼叫
	virtual void OnRefuseCall(unsigned long ulUserID)=0;

	//填充聊天历史
	virtual void FillHistory(unsigned long ulUserID)=0;
};

class IHPChatUI
{
public:
	//释放资源
	virtual void ReleaseConnections()=0;
	//打开ulUserID的聊天窗口,bShow是否前台显示
	virtual void OpenChatDlg(unsigned long ulUserID, CString strUserName, BOOL bForegroundShow = FALSE)=0;
	//关闭ulUserID的聊天窗口
	virtual void CloseChatDlg(unsigned long ulUserID)=0;
	//Resize窗口
	virtual void ResizeChatDlg(unsigned long ulUserID)=0;

	//接收到ulUserID发送的消息
	virtual void SendChatMessage(unsigned long ulUserID, CString strUserName, CString strMessage)=0;
	//接收到ulUserID的呼叫
	virtual void Call(unsigned long ulUserID, CString strUserName, BOOL bCallOut = FALSE)=0;
	//接收到ulUserID取消呼叫
	virtual void CancelCall(unsigned long ulUserID)=0;
	//接收到ulUserID接受呼叫
	virtual void AcceptCall(unsigned long ulUserID)=0;
	//接收到ulUserID拒绝呼叫
	virtual void RefuseCall(unsigned long ulUserID)=0;

	//创建视频窗口
	virtual void CreatePlayerWnd(unsigned long ulUserID, CWnd* pPlayerWnd)=0;
	//启用/禁用音视频呼叫按钮
	virtual void EnableCallBtn(unsigned long ulUserID, BOOL bEnable)=0;

	//显示ulUserID聊天历史
	virtual void ShowHistory(unsigned long ulUserID, CString strUserName)=0;
	//插入聊天历史
	virtual void InsertHistory(unsigned long ulUserID, CString strUserName,CString strTime, CString strMessage)=0;
};

AFX_EXT_CLASS IHPChatUI* CreateHPChatUI(IHPChatUINotify& rNotify);

#endif