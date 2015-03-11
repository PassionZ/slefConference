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
	virtual void OnConnected(unsigned __int32 iMCUID)=0;//����MCU�ɹ���Call SendLogin
	virtual void OnConnectTimeout(void)=0;//����MCU��ʱ
	virtual void OnDisconnected(void)=0;//���ӶϿ�
	virtual void OnLogin(int nResult,unsigned __int32 iSessionID,const char*cszUserName)=0;//��·����
	virtual void OnMCUItem(TMCUInfo *tMCUInfo)=0;//�Ӹ��ڵ㿪ʼ
	virtual void OnMCUEnd(void)=0;//MUC���� SendPresence,FetchConferenceList
	virtual void OnConferenceListItem(TConferenceBaseInfo *tConferenceBaseInfo)=0; //�����б�
	virtual void OnConferenceListEnd(void)=0;	//�����б��Ѵ���
	virtual void OnFetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray)=0;		//���������Ա��
	virtual void OnSendLoginConference(byte iUserStatus)=0;		//�ص���Ա���
	virtual void OnConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType,byte iFrameResource=1)=0;	//����ģ�� ucScreenType:ǰ4λΪһ��������1��2��3����4λΪ����������1��2
																							//ucTempletType:Ϊ������
	virtual void OnSoundDriverArray(unsigned __int32 iSessionID,CTSoundDriverInfoArray *paTSoundDriverInfoArray)=0;		//��������
	virtual void OnVideoDriverArray(unsigned __int32 iSessionID,CTVideoDriverInfoArray *paTVideoDriverInfoArray)=0;		//��Ƶ����

	virtual void OnChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray)=0;			//�ı�����Ƶ��ʽ

	virtual void OnChangeName(unsigned __int32 iSessionID,const char *cszName)=0; //�ı��û���
		
	//virtual void OnConferenceMember(unsigned __int32 iSessionID,const char*cszUserID,byte iUserStatus,const char*csUserName,unsigned __int32 iMCUID)=0;	//������Ա
	//virtual void OnConferenceMemberPresence(unsigned __int32 iSessionID,byte iOnlineFlag,const char *strOnlineTime)=0;  //������Ա

	virtual void OnConferenceMember(unsigned __int32 iSessionID,const char*cszUserID,byte iUserStatus,const char*csUserName,unsigned __int32 iMCUID)=0;	//������Ա
	virtual void OnConferenceMemberPresence(unsigned __int32 iSessionID,byte iOnlineFlag,unsigned __int32 iMCUID,const char *strOnlineTime)=0;  //������Ա
	virtual void OnConferenceMemberEnter(unsigned __int32 iSessionID)=0;	//�����˻������Ա
	virtual void OnConferenceMemberLeave(unsigned __int32 iSessionID)=0;	//�뿪�˻������Ա
	virtual void OnLoginOutSystem(unsigned __int32 iSessionID)=0;			//���ߵ���Ա
	virtual void OnDeleteConferenceUser(unsigned __int32 iSessionID)=0;		//ɾ������Ա

	virtual void OnAskSpeak(unsigned __int32 iSessionID)=0;	//�ݽ�����
	virtual void OnAllowSpeak(unsigned __int32 iSessionID)=0;	//��Ϊ�ݽ���
	virtual void OnCloseSpeak(unsigned __int32 iSessionID)=0;	//�ر�˭�ݽ�
	virtual void OnAllowKinescope()=0;	//����¼��
	virtual void OnForbidKinescope()=0;	//������¼��
	virtual void OnAllowControl()=0;	//�������
	virtual void OnForbidControl()=0;	//���������
	virtual void OnSetTalk(byte iTalkControl)=0;	//��������
	virtual void OnAllowUseWhiteBoard()=0;			//����ʹ�ðװ�
	virtual void OnForbidUseWhiteBoard()=0;			//������ʹ�ðװ�
	virtual void OnAllowFloatDrag()=0;			//����ı両������
	virtual void OnForbidFloatDrag()=0;			//������ı両������
	virtual void OnAllowAskTalk()=0;				//����������
	virtual void OnForbidAskTalk()=0;				//������������
	virtual void OnAllowAskScreenControl()=0;				//����������
	virtual void OnForbidAskScreenControl()=0;				//������������
	
	virtual void OnAllowKinescope(unsigned __int32 iSessionID)=0;	//����˭¼��
	virtual void OnForbidKinescope(unsigned __int32 iSessionID)=0;	//������˭¼��
	virtual void OnAllowControl(unsigned __int32 iSessionID)=0;	//����˭����
	virtual void OnForbidControl(unsigned __int32 iSessionID)=0;	//������˭����
	virtual void OnSetTalk(unsigned __int32 iSessionID,byte iTalkControl)=0;	//˭����������
	virtual void OnAllowUseWhiteBoard(unsigned __int32 iSessionID)=0;			//����ʹ�ðװ�
	virtual void OnForbidUseWhiteBoard(unsigned __int32 iSessionID)=0;			//������ʹ�ðװ�
	virtual void OnAllowFloatDrag(unsigned __int32 iSessionID)=0;			//�����������϶�
	virtual void OnForbidFloatDrag(unsigned __int32 iSessionID)=0;			//�������������϶�
	virtual void OnAllowAskTalk(unsigned __int32 iSessionID)=0;				//����������
	virtual void OnForbidAskTalk(unsigned __int32 iSessionID)=0;				//������������
	virtual void OnAllowAskScreenControl(unsigned __int32 iSessionID)=0;				//����������Ļ����
	virtual void OnForbidAskScreenControl(unsigned __int32 iSessionID)=0;				//������������Ļ����

	virtual void OnSetBull(const char* cszBullData)=0;	//������Ļ����
	virtual void OnIssueBull()=0;	//����Ļ
	virtual void OnCloseBull()=0;	//�ر���Ļ
	virtual void OnOpenTalkOver(byte iWinNo,byte iFrameNo,byte iFrameResource=1)=0;	//��������
	virtual void OnCloseTalkOver()=0;	//�ر�������
	virtual void OnTalkOverData(unsigned __int32 iSessionID,const char *cszTalkOverData)=0;	//������Ϣ
	virtual void OnHistoryTalkOverData(const char *cszTalkOverData,unsigned __int32 iLen)=0;	//��ʷ������Ϣ
	virtual void OnOpenWhiteBoard(byte iWinNo,byte iFrameNo,unsigned __int32 iChannelID,byte iFrameResource=1)=0;	//�򿪰װ�
	virtual void OnWhiteBoardData(const char *cszWhiteBoardData)=0;	//�װ嶯�����ݰ�
	virtual void OnCloseWhiteBoard()=0;	//�رհװ�
	virtual void OnOpenScreen(unsigned __int32 iSessionID,byte iWinNo,byte iFrameNo,unsigned __int32 iChannelID)=0;	//����Ļ
	virtual void OnScreenData(const char* cszWhiteBoardData)=0;	//��Ļ�������ݰ�
	virtual void OnCloseScreen(unsigned __int32 iSessionID)=0;	//�ر���Ļ
	virtual void OnInviteUser(unsigned __int32 iConferenceID)=0;	//������λ�
	virtual void OnOpenShareMedia(byte iWinNo,byte iFrameNo)=0;	//�򿪹���ý��
	virtual void OnCloseShareMedia()=0;	//�رչ���ý��

	virtual void OnInceptVideo(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,byte ucUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,unsigned __int32 iChannelID,bool bRepetition=false)=0;	//������Ƶ
	virtual void OnCloseVideo(byte iUserCardNo,bool bRepetition=false)=0;			//�رշ�����Ƶ
	virtual void OnFullWin(unsigned __int32 iSessionID,byte ucUserCardNo)=0;	//��Ƶ����
	virtual void OnBroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte ucUserCardNo,unsigned __int32 iChannelID,bool bRepetition=false,byte iFrameResource=1)=0;	//�㲥��㲥��Ƶ
	virtual void OnCloseBroadcastVideo(unsigned __int32 iSessionID,byte ucUserCardNo,bool bRepetition=false,byte iFrameResource=1)=0;	//�㲥�رչ㲥��Ƶ
	virtual void OnInceptSound(unsigned __int32 iPresideSessionID,unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iChannelID)=0;	//������Ƶ
	virtual void OnCloseSound(byte iUserCardNo)=0;	//�رշ�����Ƶ
	virtual void OnBroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iChannelID,byte iFrameResource=1)=0;	//�㲥��㲥��Ƶ
	virtual void OnCloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo,byte iFrameResource=1)=0;	//�㲥�رչ㲥��Ƶ

	virtual void OnSwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex)=0;			//�㲥�϶�˭
	virtual void OnSelectMainFrame(byte ucUserFrameIndex)=0;			//ѡ������

	virtual void OnSendControlCommand(byte iUserCardNo,unsigned __int32 iCommand) = 0;		//��̨����
	virtual void OnSendControlSpeed(byte iUserCardNo,byte ucSpeed) = 0;						//��̨�ٶ�

	virtual void OnVideoOrder(unsigned __int32 iSessionID)=0;	//�㲥��ƵԤ��

	virtual void OnAskToProlocutor(unsigned __int32 iSessionID)=0;		//�����Ϊ������
	virtual void OnSetProlocutor(unsigned __int32 iSessionID)=0;		//��Ϊ������
	virtual void OnSetNoProlocutor(unsigned __int32 iSessionID)=0;		//��Ϊ�Ƿ�����
	virtual void OnDeleteProlocutor(unsigned __int32 iSessionID)=0;		//ɾ��������

	virtual void OnOpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo)=0;			//�򿪸�����
	virtual void OnCloseFloatWin()=0;			//�رո�����
	virtual void OnSetFloatWinRect(unsigned __int16 iFloatWinRect[6])=0;			//���ø�����λ��

	virtual void OnSetBandwidth(unsigned __int16 iBandwidth)=0;			//���ƵĴ���

	virtual void OnSetWatchUser(unsigned __int32 iSessionID)=0;			//������Ա
	virtual void OnCloseWatchUser()=0;			//�رռ����Ա

	virtual void OnAllowWatchUserControl()=0;					//������Ա����
	virtual void OnForbidWatchUserControl()=0;					//��������Ա����

	virtual void OnSetFullScreen(unsigned __int32 iSessionID)=0;		//�蹲����Ļȫ��
	virtual void OnCloseFullScreen(unsigned __int32 iSessionID)=0;	//�㲥�ر�ȫ����Ļ

	virtual void OnOffOnlineSystem()=0;	//ǿ��ע��ϵͳ
	virtual void OnQuitMySystem()=0;	//ǿ���˳�ϵͳ

	virtual void OnStartFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID)=0;		//��ʼ�ļ��ַ�
	virtual void OnCloseFile(unsigned __int32 iSessionID,const char* cFileName,unsigned __int32 iChannelID)=0;      //�ر��ļ��ַ�
    virtual void OnFileExist(const char* cFileName)=0;            //�ļ��Ѵ���

	virtual void OnTestMcuBandwidth(int iDirection, unsigned __int32 iMcuBandwidth)=0;				//�����������

	virtual void OnOpenConferenceTopic()=0;		//�򿪻������
	virtual void OnCloseConferenceTopic()=0;	//�رջ������

	virtual void OnAllowInConference()=0;			//����������Ա�������
	virtual void OnForbidInConference()=0;			//������������Ա�������

	virtual void OnCloseConference(unsigned __int32 iConferenceID)=0;	//�������

	virtual void OnCalling(unsigned __int32 iSessionID)=0;						//�������
	virtual void OnCloseCalling(unsigned __int32 iSessionID)=0;				//��������

	virtual void OnP2PData(UINT32 iSessionID, const char * pData, int len)=0; //���͵�Ե�����
	virtual void OnBroadcastData(UINT32 iSessionID, const char * pData, int iLen)=0; //�㲥����

	virtual void OnVODItem(TVODInfo *tInfo)=0;				//VOD����������
	virtual void OnVODEnd()=0;								//VOD���������ݽ���

	virtual void OnSetLinkage(byte iLinkage=1)=0;		//������Ļ����	0:������ 1:����
	virtual void OnSetFrameResource(byte ucUserFrameIndex)=0;	//ǿ��ָ����Դ
};

#endif // !defined(AFX_IRSCLIENTNOTIFY_H__80E365B9_51CC_44CF_B40B_D410722E7D00__INCLUDED_)
