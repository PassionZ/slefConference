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
	// ���� �ӿ� 
	std::string		m_strUserID;
	UINT32			m_iConferenceID;	// ��ǰ����ID
	UINT32			m_iSpeakSessionID;  // ��ǰ������ID
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
	// ����    IRSClientNotify �ӿ� 
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
	// ����    IRSClient �ӿ� 
	virtual bool Connect(const char*cszMCUHost,unsigned __int16 iMCUPort); //����MCU
	 
	virtual bool SendLogin(const char*cszUserID,const char*cszPassword,byte iOnlineFlag); //����½��Ϣ
	virtual bool FecthMCU(void);		//����MCU
	virtual bool SendLoginConference(unsigned __int32 iConferenceID,byte iFrameResource=1);//��½����	
	virtual bool FecthVOD(){return true;}				//����VOD����������
	virtual bool FetchConferenceList(void);	//��������б�

	virtual void SoundDriverArray(CTSoundDriverInfoArray *paTSoundDriverInfoArray){}	//��������
	virtual void VideoDriverArray(CTVideoDriverInfoArray *paTVideoDriverInfoArray){}	//��Ƶ����

	virtual void ChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray){}		//�ı�����Ƶ��ʽ

	virtual void FetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray){}	//���������Ա��
	virtual void LogoutConference(void){}	//�˳�����
	virtual void LogoutSystem(void);	//�˳�ϵͳ
	virtual void ChangeConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType){} //�ı�ģ��

	virtual void ChangeName(const char *cszName){} //�ı��û���
	virtual void ChangePassword(const char*cszUserID,const char*cszPassword){} //�ı��û�����

	virtual void AskSpeak(){}//�ݽ�����
	virtual void AllowSpeak(unsigned __int32 iSessionID){}//�㲥����˭�ݽ�
	virtual void CloseSpeak(unsigned __int32 iSessionID){}//�㲥�ر�˭�ݽ�
	virtual void AllowKinescope(){}//����¼��
	virtual void ForbidKinescope(){}//������¼��
	virtual void AllowControl(){}//�������
	virtual void ForbidControl(){}//���������
	virtual void SetTalk(byte iTalkControl){}//��������
	virtual void AllowUseWhiteBoard(){}		//����ʹ�ðװ�
	virtual void ForbidUseWhiteBoard(){}		//������ʹ�ðװ�
	virtual void AllowFloatDrag(){}		//����ı両������
	virtual void ForbidFloatDrag(){}		//������ı両������
	virtual void AllowAskTalk(){}			//����������
	virtual void ForbidAskTalk(){}			//������������
	virtual void AllowAskScreenControl(){}			//������Ļ�������
	virtual void ForbidAskScreenControl(){}			//��������Ļ�������

	virtual void AllowKinescope(unsigned __int32 iSessionID){}//����˭¼��
	virtual void ForbidKinescope(unsigned __int32 iSessionID){}//������˭¼��
	virtual void AllowControl(unsigned __int32 iSessionID){}//����˭����
	virtual void ForbidControl(unsigned __int32 iSessionID){}//������˭����
	virtual void SetTalk(unsigned __int32 iSessionID,byte iTalkControl){}//˭����������
	virtual void AllowUseWhiteBoard(unsigned __int32 iSessionID){}		//����˭ʹ�ðװ�
	virtual void ForbidUseWhiteBoard(unsigned __int32 iSessionID){}		//������˭ʹ�ðװ�
	virtual void AllowFloatDrag(unsigned __int32 iSessionID){}		//�����������϶�
	virtual void ForbidFloatDrag(unsigned __int32 iSessionID){}		//�������������϶�
	virtual void AllowAskTalk(unsigned __int32 iSessionID){}			//����������
	virtual void ForbidAskTalk(unsigned __int32 iSessionID){}			//������������
	virtual void AllowAskScreenControl(unsigned __int32 iSessionID){}			//����������Ļ����
	virtual void ForbidAskScreenControl(unsigned __int32 iSessionID){}			//��������Ļ����

	virtual void SetBull(const char* cszBullData){}//������Ļ����
	virtual void IssueBull(){}//�㲥����Ļ
	virtual void CloseBull(){}//�㲥�ر���Ļ
	virtual void OpenTalkOver(byte iWinNo,byte iFrameNo){}//�㲥��������
	virtual void CloseTalkOver(){}//�㲥�ر�������
	virtual void TalkOverData(const char *cszTalkOverData,byte iTalkControl){}//������Ϣ
	virtual void OpenWhiteBoard(byte iWinNo,byte iFrameNo){}//�㲥�򿪰װ�
	virtual void WhiteBoardData(const char* cszWhiteBoardData){}//�㲥�װ嶯�����ݰ�
	virtual void CloseWhiteBoard(){}//�㲥�رհװ�
	virtual void OpenScreen(byte iWinNo,byte iFrameNo){}//�㲥����Ļ
	virtual void ScreenData(const char* cszWhiteBoardData){}//�㲥��Ļ�������ݰ�
	virtual void CloseScreen(){}//�㲥�ر���Ļ
	virtual void InviteUser(unsigned __int32 iSessionID){}//�����ѵ�½����Ա�λ�
	virtual void OpenShareMedia(byte iWinNo,byte iFrameNo){}//�㲥�򿪹���ý��
	virtual void CloseShareMedia(){}//�㲥�رչ���ý��

	virtual void InceptVideo(unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,bool bRepetition=false,unsigned __int32 iPresideSessionID=0){}//������Ƶ
	virtual void FullWin(unsigned __int32 iPresideSessionID,byte iUserCardNo){}//��Ƶ����
	virtual void CloseVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false){}//�رս�����Ƶ
	virtual void CloseVideoChannel(unsigned __int32 iChannelID){}//�ر���Ƶͨ��
	virtual void BroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,bool bRepetition=false){}//�㲥��㲥��Ƶ
	virtual void CloseBroadcastVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false){}//�㲥�رչ㲥��Ƶ
	virtual void InceptSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iPresideSessionID=0){}//������Ƶ
	virtual void CloseSound(unsigned __int32 iSessionID,byte iUserCardNo){}//�رս�����Ƶ
	virtual void CloseSoundChannel(unsigned __int32 iChannelID){}//�ر���Ƶͨ��
	virtual void BroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo){}//�㲥��㲥��Ƶ
	virtual void CloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo){}//�㲥�رչ㲥��Ƶ

	virtual void SwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex){}		//�㲥�϶�˭
	virtual void SelectMainFrame(byte ucUserFrameIndex){}		//ѡ������

	virtual void SendControlCommand(unsigned __int32 iSessionID,byte iUserCardNo,unsigned __int32 iCommand){}		//��̨����
	virtual void SendControlSpeed(unsigned __int32 iSessionID,byte iUserCardNo,byte ucSpeed){}						//��̨�ٶ�

	virtual void VideoOrder(unsigned __int32 iSessionID){}//�㲥��ƵԤ��

	virtual void AskToProlocutor(){}	//�����Ϊ������
	virtual void SetProlocutor(unsigned __int32 iSessionID){}	//��Ϊ������
	virtual void SetNoProlocutor(unsigned __int32 iSessionID){}	//��Ϊ�Ƿ�����
	virtual void DeleteProlocutor(unsigned __int32 iSessionID){}	//ɾ��������

	virtual void OpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo){}		//�򿪸�����
	virtual void CloseFloatWin(){}		//�رո�����
	virtual void SetFloatWinRect(unsigned __int16 iFloatWinRect[6]){}		//���ø�����λ��

	virtual void SetBandwidth(unsigned __int16 iBandwidth){}		//���ƵĴ���

	virtual void ConferenceSynchronization(){}		//����ͬ��
	virtual void SetWatchUser(unsigned __int32 iSessionID){}		//������Ա
	virtual void CloseWatchUser(){}		//�رռ����Ա

	virtual void AllowWatchUserControl(){}				//������Ա����
	virtual void ForbidWatchUserControl(){}				//��������Ա����

	virtual void SetFullScreen(){}	//�蹲����Ļȫ��
	virtual void CloseFullScreen(){}//�㲥�ر�ȫ����Ļ

	virtual void StartFile(const char* cFileName){}	//��ʼ�ļ��ַ�
	virtual void CloseFile(const char* cFileName){}	//�ر��ļ��ַ�

	virtual void TestMcuBandwidth(){} //�����������

	virtual void OpenConferenceTopic(){}	//�򿪻������
	virtual void CloseConferenceTopic(){}//�رջ������

	virtual void QuitMySystem(unsigned __int32 iSessionID){}//ǿ���˳�ϵͳ

	virtual void AllowInConference(){}		//����������Ա�������
	virtual void ForbidInConference(){}		//������������Ա�������

	virtual void Calling(){}				//�������
	virtual void CloseCalling(){}			//��������
	virtual void CallingInConference(){}	//����ȷ��

	virtual void P2PData(UINT32 iSessionID, const char * pData, int iLen){} //���͵�Ե�����
	virtual void BroadcastData(UINT32 iSessionID,const char * pData, int iLen){} //�㲥����


	virtual void SetLinkage(byte iLinkage=1){}	//������Ļ����	0:������ 1:����
			void OnP2PData(UINT32 iMcuID, char*pData,int nLen);   //��Ե����ݻص�
				void OnBroadcastSelectMainFrame(UINT32 iMcuID, char*pData,int nLen);


};

//extern IRSTCPLogicClient*g_pIRSTCPLogicClient=NULL;

#endif // !defined(AFX_IRSTCPLOGICCLIENT_H__70F794C8_5F27_4F11_A3CA_0164FF62C954__INCLUDED_)
