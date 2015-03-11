#ifndef __DATADEFINE_H
#define __DATADEFINE_H


#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "../libHPBaseclass/ListPtr.h"

using namespace std;

#define SYSTEM32
//#define SYSTEM16
//#define SYSTEM64

//#define NETTVANDBROADCAST 

#ifdef SYSTEM32							// 32λϵͳ
typedef unsigned short	UINT16;			// 16λ�޷��������������Σ�
typedef unsigned int	UINT32;			// 32λ�޷������������Σ�
typedef unsigned long	UNLONG32;		// 32λ�޷�������, ��Щ����������64λ�������Σ�

#else //if SYSTEM16						// 16λϵͳ
typedef unsigned short	UINT8;			// 8λ�޷��������������Σ�
typedef unsigned int	UINT16;			// 16λ�޷������������Σ�
typedef unsigned long	UINT32;			// 32λ�޷�������, ��Щ����������64λ�������Σ�

//#else if SYSTEM64						// 64λϵͳ
//typedef unsigned short	UINT32;		// 32λ�޷��������������Σ���
//typedef unsigned int		UINT64;		// 64λ�޷������������Σ�
//typedef unsigned long		ULONG64;	// 64λ�޷�������, ��Щ����������64λ�������Σ���

#endif

//#ifndef WIN32
//typedef UINT32 /*unsigned __int32*/UINT32;
typedef unsigned char byte;

//#endif

typedef UINT32* UINT32PTR;
typedef std::string STRING;
//typedef std::list<void*> LISTPTR;
typedef std::map<UINT32,void*> UINT32MAPPTR;

//////////////////////////////////////////////////////////////////////////
// add by davy 2006-1-4

// FrameInfo Type
typedef enum _EFrameInfoType { _eFrameNull=0,_eFrameAudioVideo,_eFrameWhiteBoard,_eFrameDesktop,_eFrameTalkOver,_eFrameFile,_eFrameMedio } EFrameInfoType;

typedef enum _EInfoType { _eInfoNull=0,_eTopMcu,_eSonMcu, _eUser, _eServerDog } EInfoType;

typedef enum _ETalkType { _eTalkNull=0,_eTalkPublic,_eTalkPresider,_eTalkGroup, _eTalkPresiderGroup} ETalkType;


//Info
typedef struct _tInfo
{
	EInfoType	_InfoType;				//��Ϣ����	0:�� 1:TOPMCU 2:SONMCU 3:User
} tInfo;		

//User Info
typedef struct _tUserInfo  :public tInfo
{
	//������ߺͷǶ���MCU�е��û��б�
	char		_strUserName[150];						//�û���
	char		_iUserID[60];							//�û�ID
	/*unsigned __int32*/UINT32			_iSessionID;	//�ỰID
	/*unsigned __int32*/UINT32			_iConferenceID;	//����ID
	bool		_bPresentFlag;							//ȱϯ��־  0:ȱϯ1:�ڻ�
	byte		_iOnlineFlag;							//���߱�־	
														//0:������
														//1:����������Ƶ
														//2:��������Ƶ����Ƶ
														//3:��������Ƶ����Ƶ
														//4:����������Ƶ
	/*unsigned __int32*/UINT32			_iMCUID;		//��½��MCU��id
	char		_strOnlineTime[42];						//��½ʱ�� ��ʽ��yyyymmddhhmmss
//	HTREEITEM	*_phRoot;

	//bool operator < (const _tUserInfo &m)const {
	//	return atol(_strOnlineTime)< atol(m._strOnlineTime);
	//}

	byte		_iDegreeFlag;							//�û���ݱ�־ 0:xxx 1:xxx 2:������ 3:����� 4:�����Ա
	bool		_bAllowEnterConference;					//�Ƿ�����������

#ifdef NETTVANDBROADCAST
	//�������
	byte		_iLevel;
#endif
} tUserInfo;		

// Video Card Info
typedef struct _tVideoCardInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	byte			_iUserCardNo;				//�û���Ƶ����	1~13
	byte			_iUserCodeType;				//�û���Ƶ��������	
												//4:X264 VBR(AVVIDEO_CODEC_WMVA),
												//3:X264 CBR(AVVIDEO_CODEC_WMV9),
												//1:H263++ VBR(AVVIDEO_CODEC_H263P)
	byte			_iUserDisplayType;			//�û��ֱ���	0:176*144
												//				1:242*176
												//				2:320*240
												//				3:352*288
												//				4:640*480
												//				5:704*576
	byte			_iUserFrame;				//�û�֡��	5��10��15��20��25��30
	bool			_bUserPreventInterleaved;	//�û���ֹ����ɨ��	
	byte			_iUserMaxStream;			//�û��������	0:0,1:64,2:128,3:384, 4:512,5:768,6:1024,7:2048
	byte			_iUserPicQuality;			//�û�ͼ������	0:64,1:128,2:256,3:512,4:1024,5:2048

	// add
	//////////////////////////////////////////////////////////////////////////
	byte			_iVideoDriverIndex;			//��Ƶ�豸��
	//////////////////////////////////////////////////////////////////////////

	bool			_bUserRemoveConfusion;		//�û���Ƶȥ��
	
} tVideoCardInfo;
//typedef CTypedPtrArray<CPtrArray, tVideoCardInfo*> CTVideoCardInfoArray;
typedef /*list<tVideoCardInfo*>*/ListPtr ListtVideoCardInfo;

// add
//////////////////////////////////////////////////////////////////////////
// Video Driver Info
typedef struct _tVideoDriverInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	char			_strDriverName[1024];				//�豸����
	bool			_bHDVideo;							//�Ƿ�����豸
	bool			_bHaveSound;						//�ɼ����������ɼ�
} tVideoDriverInfo;
//typedef CTypedPtrArray<CPtrArray, TVideoDriverInfo*> CTVideoDriverInfoArray;
typedef /*list<tVideoDriverInfo*>*/ListPtr ListtVideoDriverInfo;

// Sound Driver Info
typedef struct _tSoundDriverInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	char			_strDriverName[1024];				//�豸����
} tSoundDriverInfo;
//typedef CTypedPtrArray<CPtrArray, TSoundDriverInfo*> CTSoundDriverInfoArray;
typedef /*list<tSoundDriverInfo*>*/ListPtr ListtSoundDriverInfo;
//////////////////////////////////////////////////////////////////////////

//Conference User Info
typedef struct _tConferenceUserInfo	: public tUserInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	byte			_iUserMicType;									//�û���Ƶ��������	0:MS G.723.1,2:WB,255:����Ƶ
	bool			_bAllowKinescope;								//����¼��
	bool			_bAllowControl;									//�������
	byte			_iTalkControl;									//���ۿ���	0:��ֹ����,1:��������,2:������������,3:�����ڳ�Ա����
	//byte			_iUserCardNumber;								//�û��м�����Ƶ��	0������Ƶ
	/*CTVideoCardInfoArray*/ListtVideoCardInfo _aVideoCardInfo;		//��Ƶ������

	// add
	//////////////////////////////////////////////////////////////////////////
	byte			_iSoundDriverIndex;			//��Ƶ�豸��
	bool			_bAllowUseWhiteBoard;		//����ʹ�ðװ�
	/*CTSoundDriverInfoArray*/ListtSoundDriverInfo _aSoundDriverInfo;	//��Ƶ������Ϣ
	/*CTVideoDriverInfoArray*/ListtVideoDriverInfo _aVideoDriverInfo;	//����������Ϣ
	//////////////////////////////////////////////////////////////////////////

	//bool operator < (const _tConferenceUserInfo &m)const {
	//	return atol(_strOnlineTime)< atol(m._strOnlineTime);
	//}

	bool		_bAllowEnterConference;										//�Ƿ�����������

	bool		_bAskToProlocutor;											//�Ƿ���ʾ���뷢����
	bool		_bFloatWin;													//�Ƿ����긡������
	//add by davy 20071218
	bool		_bScreenControl;											//�Ƿ�������Ļ����
				
} tConferenceUserInfo;		//�����˺Ͷ���MCU���û��б����û�

// Conference Base Info
typedef struct _tConferenceBaseInfo
{
	/*unsigned __int32*/UINT32			_iConferenceID;	//����ID				
	char		_strConferenceName[180];				//��������
	char		_strConferenceTopic[765];				//��������

#ifdef NETTVANDBROADCAST
	//������Ӽ���Ƶֱ��
	byte		_iAnonymous;							//�Ƿ�����������0������1����
	byte		_iActivate;
#endif

} tConferenceBaseInfo;

//add by davy 2008-2-22
typedef struct _tConferenceCount
{
	UINT32			_iConferenceID;	//����ID		
	UINT16			_iCount;		//���߻����Ա����
	UINT16			_iTotalCount;	//�����Ա����
} tConferenceCount;
typedef ListPtr ListtConferenceCount;

// VideoSound Info
typedef struct _tVideoSoundInfo
{
	//��MCU�м�¼
	byte			_iUserCardNo;				//�û���Ƶ����	1~13
	bool			_bSound;					//�Ƿ�����Ƶ
	bool			_bVideo;					//�Ƿ�����Ƶ

	// add
	//////////////////////////////////////////////////////////////////////////
	/*unsigned __int32*/UINT32		_iSoundChannelID;		//��Ƶͨ����
	/*unsigned __int32*/UINT32		_iVideoChannelID;		//��Ƶͨ����
	//////////////////////////////////////////////////////////////////////////
	
} tVideoSoundInfo;		

// Win Info
typedef struct _tWinInfo
{
	//��MCU�м�¼
	EFrameInfoType			_iFrameInfoType;			//������ʾ����������Ϣ
	/*unsigned __int32*/UINT32		_iSessionID;		//�ỰID
	tVideoSoundInfo*		_ptVideoSoundInfo;			//������ʾ��������Ƶ��������Ƶ��Ϣ

	// add
	//////////////////////////////////////////////////////////////////////////
	/*unsigned __int32*/UINT32		_iChannelID;		//ͨ����
	//////////////////////////////////////////////////////////////////////////

	//��Ļ��Դ
	byte	_iScreenResourceID;
} tWinInfo;		
//typedef CTypedPtrArray<CPtrArray, tWinInfo*> CTWinInfoArray;
typedef /*list<tWinInfo*>*/ListPtr ListtWinInfo;

//Ask Speak User Info
//��MCU�м�¼
//typedef CTypedPtrArray<CPtrArray, tConferenceUserInfo*> CTAskSpeakUserInfoArray;
//typedef /*list<tConferenceUserInfo*>*/ListPtr ListtConferenceUserInfo;

typedef struct _tProlocutorInfo
{
	UINT32 _iSessionID; // ���뷢����
	byte   _iStatus;	// ������״̬ 0��ȡ�����ԣ�2����Ϊ����
} tProlocutorInfo;
typedef /*list<tProlocutorInfo*>*/ListPtr ListtProlocutorInfo;

//��Ļ��Դ
typedef struct _tScreenResourceInfo
{
	byte			_iWinClass;						//����	1��2��3�ڼ������� ��TemplateType
	bool			_bWinTemplate;					//ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte			_iWinNumber;					//����	
	byte			_iWinType;						//����

	ListtWinInfo    _aWinInfo;						//������Ϣ
} tScreenResourceInfo;
typedef ListPtr ListtScreenResourceInfo;

typedef struct _tScreenResource
{
	byte			_iFrameNo;						//��ʾ������
	bool			_bInterLock;					//�Ƿ���������Ļ��Դ����
	ListtScreenResourceInfo _aScreenResourceInfo;	//��Ļ��Դ��ϸ��Ϣ
} tScreenResource;
typedef ListPtr ListtScreenResource;

// Conference Info
typedef struct _tConferenceInfo : public tConferenceBaseInfo
{
	/*unsigned __int16*/UINT16			_iBandwidth;	//���ƵĴ���
	byte			_iOneWinClass;						//1��������	1��2��3�ڼ������� ��TemplateType
	bool			_bOneWinTemplate;					//1����ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte			_iOneWinNumber;						//1��������	
	byte			_iOneWinType;						//1��������
	byte			_iTwoWinClass;						//2��������	1��2�ڼ�������	��TemplateType
	bool			_bTwoWinTemplate;					//2����ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte			_iTwoWinNumber;						//2��������
	byte			_iTwoWinType;						//2��������

	//��MCU�м�¼
	/*unsigned __int32*/UINT32			_iSpokesmanID;			//������ID	0�����ݽ���
	bool		_bAllowKinescope;								//����¼��
	bool		_bAllowControl;									//�������
//	bool		_bBeginRepetition;								//��ʼ��ѭ
	byte		_iTalkControl;									//���ۿ���	0:��ֹ����,1:��������,2:������������
	char		_strAfficheSet[768];							//��������
	bool		_bAfficheFlag;									//���淢��
//	bool		_bWhiteBoard;									//����װ��־
	/*CTWinInfoArray*/ListtWinInfo	_aOneWinInfo;				//����1������Ϣ
	/*CTWinInfoArray*/ListtWinInfo	_aTwoWinInfo;				//����2������Ϣ
//	byte		_iAskSpeakUserNumber;							//�м�����������
//	/*CTAskSpeakUserInfoArray*/ListtConferenceUserInfo	_aAskSpeakUserInfo;	//�����Ե���Ϣ

	// add
	//////////////////////////////////////////////////////////////////////////
	byte		_iFrameNo;					//��ʾ������
	bool		_bAllowUseWhiteBoard;		//����ʹ�ðװ�
	//////////////////////////////////////////////////////////////////////////

	/*unsigned __int32*/UINT32		_iFloatWinUserSessionID;				//�������û��ỰID 0���޸�����
	byte		_iUserCardNo;												//�������û�����
	/*unsigned __int32*/UINT16		_iFloatWinRect[6];						//����������

	/*unsigned __int32*/UINT32		_iWatchUserID;							//�����ԱID
	bool		_bWatchUserControl;											//�����Ա����Ȩ��		�����Ա����

	/*unsigned __int32*/UINT32 _iFullScreenSessionID;						//������Ļȫ����ԱID

	bool		_bConferenceTopic;											//�Ƿ���ʾ�������

	bool		_bAllowEnterConference;										//�Ƿ�����������

	bool		_bAskToProlocutor;											//�Ƿ���ʾ���뷢����
	bool		_bFloatWin;													//�Ƿ����긡������
	//add by davy 20071218
	bool		_bScreenControl;											//�Ƿ�������Ļ����
	
	ListtProlocutorInfo	_aProlocutorInfo;									//���뷢�����б�

	//add by davy 2007-06-18
	UINT32			_iCallID;												//������ID

#ifdef NETTVANDBROADCAST 
	byte		_iLevel;		//�������
	UINT32		_iSessionID;	//���ӻ�

	byte		_iChannelID;	//����Ƶ��
#endif

	//��Ļ��Դ
	ListtScreenResource _aScreenResource;

} tConferenceInfo;

// MCU Info
typedef struct _tMCUInfo:public tInfo
{
	/*unsigned __int32*/UINT32			_iMCUID;					//MCUID
	char		_strMCUName[90];									//MCU����
	char		_strMCUIPAddress[45];								//IP��ַ
	/*unsigned __int32*/UINT32			_iUPMCUid;					//�ϼ�MCUid
//	HTREEITEM	*_phRoot;

	byte		_ucStatus;
} tMCUInfo;

// VOD Info
typedef struct _tVODInfo
{
	char		_strVODName[90];									//VOD����
	char		_strVODIPAddress[45];								//IP��ַ
} tVODInfo;

//TalkOver Data Info
typedef struct _tTalkOverDataInfo
{
	/*unsigned __int32*/UINT32		_iSessionID;	//�û�ID
	char		_cTalkOver_Data[768];				//���۵���Ϣ
} tTalkOverDataInfo;			//��MCU�м�¼
//typedef CTypedPtrArray<CPtrArray, TTalkOverDataInfo*> CTTalkOverDataInfoArray;
//
//typedef CTypedPtrArray<CPtrArray, TConferenceBaseInfo*> CTConferenceBaseInfoArray;
//typedef CTypedPtrArray<CPtrArray, TConferenceInfo*> CTConferenceInfoArray;
////typedef CTypedPtrArray<CPtrArray, TRepetitionUserInfo*> CTRepetitionUserInfoArray;
//typedef CTypedPtrArray<CPtrArray, TMCUInfo*> CTMCUInfoArray;
//typedef CTypedPtrArray<CPtrArray, TUserInfo*> CTUserInfoArray;
//typedef CTypedPtrArray<CPtrArray, TConferenceUserInfo*> CTConferenceUserInfoArray;

typedef /*list<tTalkOverDataInfo*>*/ListPtr ListtTalkOverDataInfo;
typedef /*list<tConferenceBaseInfo*>*/ListPtr ListtConferenceBaseInfo;
typedef /*list<tConferenceInfo*>*/ListPtr ListtConferenceInfo;
typedef /*list<tMCUInfo*>*/ListPtr ListtMCUInfo;
typedef /*list<tUserInfo*>*/ListPtr ListtUserInfo;
typedef /*list<tConferenceUserInfo*>*/ListPtr ListtConferenceUserInfo;


typedef struct _tTempletInfo 
{
	byte			_iTempletClass;						//ģ������	1��2��3�ڼ������� ��TemplateType
	//bool			_bTempletTemplate;					//ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte			_iTempletNumber;					//ģ������	
	byte			_iTempletType;						//ģ������
	byte			_iTempletWinNumber;					//ģ�崰������
} tTempletInfo;
typedef /*list<tTempletInfo*>*/ListPtr ListtTempletInfo;

// rsftp
typedef struct _tFileInfo 
{
	UINT32	_iFileHandle;			// file IO handle
	std::string	_strFileName;		// file name
	UINT32	_iFileTotalLength;		// file total length
	bool	_bCompleted;			// is completed? is equal _iFileTotalLength = filelen(_iFileHandle)
	UINT32	_iCurFileLength;		// file current length
	UINT32	_iConferenceID;			
} tFileInfo;
typedef /*list<tFileInfo*>*/ListPtr ListtFileInfo;

// Channel Info
typedef struct _tChannelInfo:public tInfo
{
	UINT32		_iTelevisionID;			//����ID
	UINT32		_iChannelID;			//����Ƶ��ID
	char		_cChannelName[20];		//����Ƶ������
	char		_cChannelMark[50];		//����Ƶ������
	byte		_iActiveStatus;			//Ƶ����ǰ״̬ 
} tChannelInfo;
typedef /*list<tChannelInfo*>*/ListPtr ListtChannelInfo;

#endif

