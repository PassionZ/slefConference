
// courtDlg.h : ͷ�ļ�
//

#pragma once
#include "Resource/Com/IRSClient.h"
#include "Resource/Com/IRSClientNotify.h"

#include "DlgPMosaicScreenADScreen.h"

// CcourtDlg �Ի���
class CcourtDlg
	: public CDialogEx
	, public IRSClientNotify

{
	// ����
public:
	CcourtDlg(CWnd* pParent = NULL);	// ��׼���캯��

	~CcourtDlg()
	{
		if (m_pIRSClient)
		{ 
			m_pIRSClient->LogoutSystem();
			delete m_pIRSClient;
			m_pIRSClient=NULL;
		}
	}
	// �Ի�������
	enum { IDD = IDD_COURT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	void LoginConference(unsigned __int32	iConferenceID);

protected:
	void FetchConferenceList();
	void RemoveConferenceInfoArray();
		void SendVideoDriver();						//������������
	void SendSoundDriver();						//������������
	// ʵ��
public:
	HICON m_hIcon;

	CTConferenceUserInfoArray m_aConferenceUserInfoArray;
	CTConferenceInfoArray m_aConferenceInfoArray;
	IRSClient*		m_pIRSClient;
	TLocalUserInfo *m_ptLocalUserInfo;
	void InitDlg();								//��ʼ���Ի���
	CDlgPMosaicScreenADScreen *m_pDlgPMosaicScreenPADScreen;									//����ƽ�崰��

	void InitClient();
	// ���ɵ���Ϣӳ�亯��
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
	virtual void OnConnected(unsigned __int32 iMCUID);//����MCU�ɹ���Call SendLogin
	virtual void OnConnectTimeout();//����MCU��ʱ
	virtual void OnDisconnected();//���ӶϿ�
	virtual void OnLogin(int nResult,unsigned __int32 iSessionID,const char*cszUserName);//Call FecthMCU
	virtual void OnMCUItem(TMCUInfo *tMCUInfo);//�Ӹ��ڵ㿪ʼ
	virtual void OnMCUEnd();//FetchConferenceList
	virtual void OnConferenceListItem(TConferenceBaseInfo *tConferenceBaseInfo);
	virtual void OnConferenceListEnd();
	virtual void OnFetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray){};		//���������Ա��
	virtual void OnSendLoginConference(byte iUserStatus);		//�ص���Ա���
	virtual void OnConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,
		byte iWinNumber,byte iWinType,byte iFrameResource=1){};	
	//ucTempletType:Ϊ������
	virtual void OnSoundDriverArray(unsigned __int32 iSessionID,
		CTSoundDriverInfoArray *paTSoundDriverInfoArray){};		//��������

	virtual void OnVideoDriverArray(unsigned __int32 iSessionID,
		CTVideoDriverInfoArray *paTVideoDriverInfoArray){};		//��Ƶ����

	virtual void OnChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,
		byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray){};			//�ı�����Ƶ��ʽ

	virtual void OnChangeName(unsigned __int32 iSessionID,const char *cszName){}; //�ı��û���

	virtual void OnConferenceMember(unsigned __int32 iSessionID,const char*cszUserID,byte iUserStatus,const char*csUserName,unsigned __int32 iMCUID);
	virtual void OnConferenceMemberPresence(unsigned __int32 iSessionID,byte iOnlineFlag,
		unsigned __int32 iMCUID,const char *strOnlineTime){};

	virtual void OnConferenceMemberEnter(unsigned __int32 iSessionID){};
	virtual void OnConferenceMemberLeave(unsigned __int32 iSessionID){};
	virtual void OnLoginOutSystem(unsigned __int32 iSessionID){};
	virtual void OnDeleteConferenceUser(unsigned __int32 iSessionID){};		//ɾ������Ա

	virtual void OnAskSpeak(unsigned __int32 iSessionID){};	//�ݽ�����
	virtual void OnAllowSpeak(unsigned __int32 iSessionID){};	//��Ϊ�ݽ���
	virtual void OnCloseSpeak(unsigned __int32 iSessionID){};	//�ر�˭�ݽ�
	virtual void OnAllowKinescope(){};	//����¼��
	virtual void OnForbidKinescope(){};	//������¼��
	virtual void OnAllowControl(){};	//�������
	virtual void OnForbidControl(){};	//���������
	virtual void OnSetTalk(byte iTalkControl){};	//��������
	virtual void OnAllowUseWhiteBoard(){};			//����ʹ�ðװ�
	virtual void OnForbidUseWhiteBoard(){};			//������ʹ�ðװ�
	virtual void OnAllowAskScreenControl(){};
	virtual void OnForbidAskScreenControl(){};
	virtual void OnAllowFloatDrag(){};			//����ı両������
	virtual void OnForbidFloatDrag(){};			//������ı両������
	virtual void OnAllowAskTalk(){};				//����������
	virtual void OnForbidAskTalk(){};				//������������

	virtual void OnAllowKinescope(unsigned __int32 iSessionID){};	//����˭¼��
	virtual void OnForbidKinescope(unsigned __int32 iSessionID){};	//������˭¼��
	virtual void OnAllowControl(unsigned __int32 iSessionID){};	//����˭����
	virtual void OnForbidControl(unsigned __int32 iSessionID){};	//������˭����
	virtual void OnSetTalk(unsigned __int32 iSessionID,byte iTalkControl){};	//˭����������
	virtual void OnAllowUseWhiteBoard(unsigned __int32 iSessionID){};			//����˭ʹ�ðװ�
	virtual void OnForbidUseWhiteBoard(unsigned __int32 iSessionID){};			//������˭ʹ�ðװ�
	virtual void OnAllowFloatDrag(unsigned __int32 iSessionID){};			//�����������϶�
	virtual void OnForbidFloatDrag(unsigned __int32 iSessionID){};			//�������������϶�
	virtual void OnAllowAskTalk(unsigned __int32 iSessionID){};				//����������
	virtual void OnForbidAskTalk(unsigned __int32 iSessionID){};				//������������
	virtual void OnAllowAskScreenControl(unsigned __int32 iSessionID){};
	virtual void OnForbidAskScreenControl(unsigned __int32 iSessionID){};

	virtual void OnSetBull(const char* cszBullData){};	//������Ļ����
	virtual void OnIssueBull(){};	//����Ļ
	virtual void OnCloseBull(){};	//�ر���Ļ
	virtual void OnOpenTalkOver(byte iWinNo,byte iFrameNo,byte iFrameResource=1){};	//��������
	virtual void OnCloseTalkOver(){};	//�ر�������
	virtual void OnTalkOverData(unsigned __int32 iSessionID,const char *cszTalkOverData){};	//������Ϣ
	void OnSaveChatHistory(unsigned long ulUserID,CString strUserName,CString strMessage){};
	void ProcessTalkOverData(unsigned __int32 iSessionID,const char *cszTalkOverData,bool bIsIMMsg = false,CString strName = _T("")){};	//������Ϣ
	virtual void OnHistoryTalkOverData(const char *cszTalkOverData,unsigned __int32 iLen){};	//��ʷ������Ϣ
	virtual void OnOpenWhiteBoard(byte iWinNo,byte iFrameNo,unsigned __int32 iChannelID,byte iFrameResource=1){};	//�򿪰װ�
	virtual void OnWhiteBoardData(const char* cszWhiteBoardData){};	//�װ嶯�����ݰ�
	virtual void OnCloseWhiteBoard(){};	//�رհװ�
	virtual void OnOpenScreen(unsigned __int32 iSessionID,byte iWinNo,byte iFrameNo,
		unsigned __int32 iChannelID){};	//����Ļ
	virtual void OnScreenData(const char* cszWhiteBoardData){};	//��Ļ�������ݰ�
	virtual void OnCloseScreen(unsigned __int32 iSessionID){};	//�ر���Ļ
	virtual void OnInviteUser(unsigned __int32 iConferenceID){};	//������λ�
	virtual void OnOpenShareMedia(byte iWinNo,byte iFrameNo){};	//�򿪹���ý��
	virtual void OnCloseShareMedia(){};	//�رչ���ý��

	virtual void OnInceptVideo(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,
		byte ucUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,unsigned __int32 iChannelID,bool bRepetition=false){};	//������Ƶ
	virtual void OnCloseVideo(byte iUserCardNo,bool bRepetition=false){};			//�رշ�����Ƶ

	virtual void OnFullWin(unsigned __int32 iSessionID,byte ucUserCardNo){};	//��������
	virtual void OnBroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,
		byte ucUserFrameIndex,byte ucUserCardNo,unsigned __int32 iChannelID,bool bRepetition=false,byte iFrameResource=1){};	//�㲥��㲥��Ƶ

	virtual void OnCloseBroadcastVideo(unsigned __int32 iSessionID,byte ucUserCardNo,bool bRepetition=false,byte iFrameResource=1){};	//�㲥�رչ㲥��Ƶ
	virtual void OnInceptSound(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,
		byte iUserCardNo,unsigned __int32 iChannelID){};	//������Ƶ
	virtual void OnCloseSound(byte iUserCardNo){};	//�رշ�����Ƶ

	virtual void OnBroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,
		byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iChannelID,byte iFrameResource=1){};	//�㲥��㲥��Ƶ


	virtual void OnSwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,
		byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex){};			//�㲥�϶�˭

	virtual void OnSelectMainFrame(byte ucUserFrameIndex);			//ѡ������

	virtual void OnSendControlCommand(byte iUserCardNo,unsigned __int32 iCommand){};		//��̨����
	virtual void OnSendControlSpeed(byte iUserCardNo,byte ucSpeed){};						//��̨�ٶ�

	virtual void OnVideoOrder(unsigned __int32 iSessionID){};	//�㲥��ƵԤ��

	virtual void OnAskToProlocutor(unsigned __int32 iSessionID){};		//�����Ϊ������
	virtual void OnSetProlocutor(unsigned __int32 iSessionID){};		//��Ϊ������
	virtual void OnSetNoProlocutor(unsigned __int32 iSessionID){};		//��Ϊ�Ƿ�����
	virtual void OnDeleteProlocutor(unsigned __int32 iSessionID){};		//ɾ��������

	virtual void OnOpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo){};			//�򿪸�����
	virtual void OnCloseFloatWin(){};			//�رո�����
	virtual void OnSetFloatWinRect(unsigned __int16 iFloatWinRect[6]){};			//���ø�����λ��

	virtual void OnSetBandwidth(unsigned __int16 iBandwidth){};			//���ƵĴ���

	virtual void OnSetWatchUser(unsigned __int32 iSessionID){};			//������Ա
	virtual void OnCloseWatchUser(){};			//�رռ����Ա

	virtual void OnAllowWatchUserControl(){};					//������Ա����
	virtual void OnForbidWatchUserControl(){};					//��������Ա����

	virtual void OnSetFullScreen(unsigned __int32 iSessionID){};		//�蹲����Ļȫ��
	virtual void OnCloseFullScreen(unsigned __int32 iSessionID){};	//�㲥�ر�ȫ����Ļ

	virtual void OnOffOnlineSystem(){};	//ǿ��ע��ϵͳ
	virtual void OnQuitMySystem(){};	//ǿ���˳�ϵͳ

	virtual void OnStartFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID){};		//��ʼ�ļ��ַ�
	virtual void OnCloseFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID){};		//�ر��ļ��ַ�
	virtual void OnFileExist(const char* cFileName){};            //�ļ��Ѵ���

	virtual void OnTestMcuBandwidth(int iDirection, unsigned __int32 iMcuBandwidth){};				//�����������

	virtual void OnOpenConferenceTopic(){};		//�򿪻������
	virtual void OnCloseConferenceTopic(){};	//�رջ������

	virtual void OnAllowInConference(){};			//����������Ա�������
	virtual void OnForbidInConference(){};			//������������Ա�������

	virtual void OnCloseConference(unsigned __int32 iConferenceID){};		//�������

	virtual void OnCalling(unsigned __int32 iSessionID){};						//�������
	virtual void OnCloseCalling(unsigned __int32 iSessionID){};				//��������

	virtual void OnP2PData(UINT32 iSessionID, const char * pData, int Len);
	virtual void OnBroadcastData(UINT32 iSessionID, const char * pData, int iLen){}; //�㲥����

	virtual void OnVODItem(TVODInfo *tInfo){};				//VOD����������
	virtual void OnVODEnd(){};								//VOD���������ݽ���

	virtual void OnSetLinkage(byte iLinkage=1){};		//������Ļ����	0:������ 1:����
	virtual void OnSetFrameResource(byte ucUserFrameIndex){};	//ǿ��ָ����Դ


	virtual void OnCloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo,byte iFrameResource=1){};	//�㲥�رչ㲥��Ƶ

};
