#ifndef _HPCHATUI_H
#define _HPCHATUI_H

#define TIMER_SPACE		1000	//����ʱ����

class IHPChatUINotify
{
public:	
	//��ulUserID������Ϣ
	virtual void OnSendChatMessage(unsigned long ulUserID, CString strMessage)=0;
	//����ָ���
	virtual void OnInsertMark(unsigned long ulUserID)=0;
	//����ulUserID ����ֵ0:�ɹ� 1���Լ��ڻ��� 2���Է��ڻ��� 3����Ƶ��������
	virtual int OnCall(unsigned long ulUserID)=0;
	//ȡ������ulUserID
	virtual void OnCancelCall(unsigned long ulUserID)=0;
	//����ulUserID�ĺ���
	virtual void OnAcceptCall(unsigned long ulUserID)=0;
	//�ܾ�ulUserID�ĺ���
	virtual void OnRefuseCall(unsigned long ulUserID)=0;

	//���������ʷ
	virtual void FillHistory(unsigned long ulUserID)=0;
};

class IHPChatUI
{
public:
	//�ͷ���Դ
	virtual void ReleaseConnections()=0;
	//��ulUserID�����촰��,bShow�Ƿ�ǰ̨��ʾ
	virtual void OpenChatDlg(unsigned long ulUserID, CString strUserName, BOOL bForegroundShow = FALSE)=0;
	//�ر�ulUserID�����촰��
	virtual void CloseChatDlg(unsigned long ulUserID)=0;
	//Resize����
	virtual void ResizeChatDlg(unsigned long ulUserID)=0;

	//���յ�ulUserID���͵���Ϣ
	virtual void SendChatMessage(unsigned long ulUserID, CString strUserName, CString strMessage)=0;
	//���յ�ulUserID�ĺ���
	virtual void Call(unsigned long ulUserID, CString strUserName, BOOL bCallOut = FALSE)=0;
	//���յ�ulUserIDȡ������
	virtual void CancelCall(unsigned long ulUserID)=0;
	//���յ�ulUserID���ܺ���
	virtual void AcceptCall(unsigned long ulUserID)=0;
	//���յ�ulUserID�ܾ�����
	virtual void RefuseCall(unsigned long ulUserID)=0;

	//������Ƶ����
	virtual void CreatePlayerWnd(unsigned long ulUserID, CWnd* pPlayerWnd)=0;
	//����/��������Ƶ���а�ť
	virtual void EnableCallBtn(unsigned long ulUserID, BOOL bEnable)=0;

	//��ʾulUserID������ʷ
	virtual void ShowHistory(unsigned long ulUserID, CString strUserName)=0;
	//����������ʷ
	virtual void InsertHistory(unsigned long ulUserID, CString strUserName,CString strTime, CString strMessage)=0;
};

AFX_EXT_CLASS IHPChatUI* CreateHPChatUI(IHPChatUINotify& rNotify);

#endif