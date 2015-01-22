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
	virtual bool Connect(const char*cszMCUHost,unsigned __int16 iMCUPort)=0;//����MCU
	virtual bool SendLogin(const char*cszUserID,const char*cszPassword,byte iOnlineFlag)=0;	//����½��Ϣ
	virtual bool FecthMCU(void)=0;			//����MCU
	virtual bool SendLoginConference(unsigned __int32 iConferenceID,byte iFrameResource=1)=0;	//��½����	

	virtual void SoundDriverArray(CTSoundDriverInfoArray *paTSoundDriverInfoArray)=0;		//��������
	virtual void VideoDriverArray(CTVideoDriverInfoArray *paTVideoDriverInfoArray)=0;		//��Ƶ����

	virtual void ChangUserMicVideoInfo(unsigned __int32 iSessionID,byte iSoundDriverIndex,byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray)=0;			//�ı�����Ƶ��ʽ
	
	virtual bool FetchConferenceList(void)=0;		//��������б�
	virtual void FetchConferenceUserCount(CTConferenceInfoArray *paTConferenceInfoArray)=0;		//���������Ա��
	virtual void LogoutConference(void)=0;		//�˳�����
	virtual void LogoutSystem(void)=0;			//�˳�ϵͳ
	virtual void ChangeConferenceTemplet(byte WinNo,byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType)=0; //�ı�ģ��

	virtual void ChangeName(const char *cszName)=0; //�ı��û���
	virtual void ChangePassword(const char*cszUserID,const char*cszPassword)=0; //�ı��û�����
	
	virtual void AskSpeak()=0;	//�ݽ�����
	virtual void AllowSpeak(unsigned __int32 iSessionID)=0;	//�㲥����˭�ݽ�
	virtual void CloseSpeak(unsigned __int32 iSessionID)=0;	//�㲥�ر�˭�ݽ�
	virtual void AllowKinescope()=0;	//����¼��
	virtual void ForbidKinescope()=0;	//������¼��
	virtual void AllowControl()=0;	//�������
	virtual void ForbidControl()=0;	//���������
	virtual void SetTalk(byte iTalkControl)=0;	//��������
	virtual void AllowUseWhiteBoard()=0;			//����ʹ�ðװ�
	virtual void ForbidUseWhiteBoard()=0;			//������ʹ�ðװ�
	virtual void AllowFloatDrag()=0;			//����ı両������
	virtual void ForbidFloatDrag()=0;			//������ı両������
	virtual void AllowAskTalk()=0;				//����������
	virtual void ForbidAskTalk()=0;				//������������
	virtual void AllowAskScreenControl()=0;				//������Ļ�������
	virtual void ForbidAskScreenControl()=0;				//��������Ļ�������

	virtual void AllowKinescope(unsigned __int32 iSessionID)=0;	//����˭¼��
	virtual void ForbidKinescope(unsigned __int32 iSessionID)=0;	//������˭¼��
	virtual void AllowControl(unsigned __int32 iSessionID)=0;	//����˭����
	virtual void ForbidControl(unsigned __int32 iSessionID)=0;	//������˭����
	virtual void SetTalk(unsigned __int32 iSessionID,byte iTalkControl)=0;	//˭����������
	virtual void AllowUseWhiteBoard(unsigned __int32 iSessionID)=0;			//����˭ʹ�ðװ�
	virtual void ForbidUseWhiteBoard(unsigned __int32 iSessionID)=0;			//������˭ʹ�ðװ�
	virtual void AllowFloatDrag(unsigned __int32 iSessionID)=0;			//�����������϶�
	virtual void ForbidFloatDrag(unsigned __int32 iSessionID)=0;			//�������������϶�
	virtual void AllowAskTalk(unsigned __int32 iSessionID)=0;				//����������
	virtual void ForbidAskTalk(unsigned __int32 iSessionID)=0;				//������������
	virtual void AllowAskScreenControl(unsigned __int32 iSessionID)=0;				//����������Ļ����
	virtual void ForbidAskScreenControl(unsigned __int32 iSessionID)=0;				//��������Ļ����
	
	virtual void SetBull(const char* cszBullData)=0;	//������Ļ����
	virtual void IssueBull()=0;	//�㲥����Ļ
	virtual void CloseBull()=0;	//�㲥�ر���Ļ
	virtual void OpenTalkOver(byte iWinNo,byte iFrameNo)=0;	//�㲥��������
	virtual void CloseTalkOver()=0;	//�㲥�ر�������
	virtual void TalkOverData(const char *cszTalkOverData,byte iTalkControl)=0;	//������Ϣ
	virtual void OpenWhiteBoard(byte iWinNo,byte iFrameNo)=0;	//�㲥�򿪰װ�
	virtual void WhiteBoardData(const char* cszWhiteBoardData)=0;	//�㲥�װ嶯�����ݰ�
	virtual void CloseWhiteBoard()=0;	//�㲥�رհװ�
	virtual void OpenScreen(byte iWinNo,byte iFrameNo)=0;	//�㲥����Ļ
	virtual void ScreenData(const char* cszWhiteBoardData)=0;	//�㲥��Ļ�������ݰ�
	virtual void CloseScreen()=0;	//�㲥�ر���Ļ
	virtual void InviteUser(unsigned __int32 iSessionID)=0;	//�����ѵ�½����Ա�λ�
	virtual void OpenShareMedia(byte iWinNo,byte iFrameNo)=0;	//�㲥�򿪹���ý��
	virtual void CloseShareMedia()=0;	//�㲥�رչ���ý��

	virtual void InceptVideo(unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex,bool bRepetition=false,unsigned __int32 iPresideSessionID=0)=0;	//������Ƶ
	virtual void FullWin(unsigned __int32 iPresideSessionID,byte iUserCardNo)=0;	//��Ƶ����
	virtual void CloseVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false)=0;	//�رս�����Ƶ
	virtual void CloseVideoChannel(unsigned __int32 iChannelID)=0;	//�ر���Ƶͨ��
	virtual void BroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,bool bRepetition=false)=0;	//�㲥��㲥��Ƶ
	virtual void CloseBroadcastVideo(unsigned __int32 iSessionID,byte iUserCardNo,bool bRepetition=false)=0;	//�㲥�رչ㲥��Ƶ
	virtual void InceptSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo,unsigned __int32 iPresideSessionID=0)=0;	//������Ƶ
	virtual void CloseSound(unsigned __int32 iSessionID,byte iUserCardNo)=0;	//�رս�����Ƶ
	virtual void CloseSoundChannel(unsigned __int32 iChannelID)=0;	//�ر���Ƶͨ��
	virtual void BroadcastSound(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserFrameIndex,byte iUserCardNo)=0;	//�㲥��㲥��Ƶ
	virtual void CloseBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo)=0;	//�㲥�رչ㲥��Ƶ

	virtual void SwapWhoToWndPosition(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte iUserCardNo,byte ucUserWndIndex,byte ucUserFrameIndex)=0;			//�㲥�϶�˭
	virtual void SelectMainFrame(byte ucUserFrameIndex)=0;			//ѡ������

	virtual void SendControlCommand(unsigned __int32 iSessionID,byte iUserCardNo,unsigned __int32 iCommand) = 0;		//��̨����
	virtual void SendControlSpeed(unsigned __int32 iSessionID,byte iUserCardNo,byte ucSpeed) = 0;						//��̨�ٶ�
	
	virtual void VideoOrder(unsigned __int32 iSessionID)=0;	//�㲥��ƵԤ��

	virtual void AskToProlocutor()=0;		//�����Ϊ������
	virtual void SetProlocutor(unsigned __int32 iSessionID)=0;		//��Ϊ������
	virtual void SetNoProlocutor(unsigned __int32 iSessionID)=0;		//��Ϊ�Ƿ�����
	virtual void DeleteProlocutor(unsigned __int32 iSessionID)=0;		//ɾ��������

	virtual void OpenFloatWin(unsigned __int32 iSessionID,byte iUserCardNo)=0;			//�򿪸�����
	virtual void CloseFloatWin()=0;			//�رո�����
	virtual void SetFloatWinRect(unsigned __int16 iFloatWinRect[6])=0;			//���ø�����λ��

	virtual void SetBandwidth(unsigned __int16 iBandwidth)=0;			//���ƵĴ���

	virtual void ConferenceSynchronization()=0;			//����ͬ��
	virtual void SetWatchUser(unsigned __int32 iSessionID)=0;			//������Ա
	virtual void CloseWatchUser()=0;			//�رռ����Ա

	virtual void AllowWatchUserControl()=0;					//������Ա����
	virtual void ForbidWatchUserControl()=0;					//��������Ա����

	virtual void SetFullScreen()=0;		//�蹲����Ļȫ��
	virtual void CloseFullScreen()=0;	//�㲥�ر�ȫ����Ļ

	virtual void StartFile(const char* cFileName)=0;		//��ʼ�ļ��ַ�
	virtual void CloseFile(const char* cFileName)=0;		//�ر��ļ��ַ�

	virtual void TestMcuBandwidth()=0; //�����������

	virtual void OpenConferenceTopic()=0;		//�򿪻������
	virtual void CloseConferenceTopic()=0;	//�رջ������

	virtual void QuitMySystem(unsigned __int32 iSessionID)=0;	//ǿ���˳�ϵͳ

	virtual void AllowInConference()=0;			//����������Ա�������
	virtual void ForbidInConference()=0;			//������������Ա�������

	virtual void Calling()=0;					//�������
	virtual void CloseCalling()=0;				//��������
	virtual void CallingInConference()=0;		//����ȷ��
	
	virtual void P2PData(UINT32 iSessionID, const char * pData, int iLen)=0; //���͵�Ե�����
	virtual void BroadcastData(UINT32 iSessionID,const char * pData, int iLen)=0; //�㲥����

	virtual bool FecthVOD()=0;					//����VOD����������

	virtual void SetLinkage(byte iLinkage=1)=0;		//������Ļ����	0:������ 1:����
};

#endif // !defined(AFX_IRSCLIENT_H__8C758EE0_772E_494B_912E_3FF6C720A601__INCLUDED_)
