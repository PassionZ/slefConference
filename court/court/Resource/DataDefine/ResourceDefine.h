            // ResourceDefine.h: interface for the CResourceDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEDEFINE_H__9ACA1E49_32C3_439B_BF25_3A372B7C5A38__INCLUDED_)
#define AFX_RESOURCEDEFINE_H__9ACA1E49_32C3_439B_BF25_3A372B7C5A38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define CONFERENCE_WIN_NUMBER 4

//////////////////////////////////////////////////////////////////////
// Enums
const int nSeperateWidth = 5;
// ��Ļ��	Add Hhj		2008/01/17	 
typedef enum _eScreenNOType { ntSCREEN_ONE = 0, ntSCREEN_TWO, ntSCREEN_THREE, ntSCREEN_FOUR} ScreenNOType;

// ��Ļ�����ѡ��״̬  Add Hhj  2008/07/17
typedef enum ScreenNoteStatus {pointer, pen, middlepen, bigpen, erase} ScreenNoteStatus;	

// VideoShowMode Type		0:�Ӿ������и���ʾ 1:�Ӿ��������ʾ 2:��Ƶȫ����ʾ
typedef enum _eVideoShowModeType { ntVideoShowModeCut,ntVideoShowModeFill,ntVideoShowModeFull} VideoShowModeType;

// Screen Type
typedef enum _eScreenType { ntScreen4x3,ntScreen16x9,ntScreen16x10} ScreenType;

// Operate Type 0:�����鴴������  1:��������������
typedef enum _eConfOperateType { ntOperateConfCreate = 0, ntOperateConfName } ConfOperateType;

// Operate Type 	1:����½���� 2:���������� 3:���ʺ����� 
typedef enum _eOperateType { ntOperateLogin=1,ntOperateName,ntOperateAccounts} OperateType;

// FrameInfo Type
typedef enum _eFrameInfoType { ntFrameNull,ntVideoSound,ntWhiteBoard,ntScreen,ntTalkOver,ntMedio,ntFloatWin } FrameInfoType;

// Info Type
typedef enum _eInfoType { ntNull,ntMCU,ntUser } InfoType;

// Template Type
typedef enum _eTemplateType { ntTemplateNull,ntFree,ntNormal,nt16x9 } TemplateType;	

// StatusFlag Type		0:û��½��1���ѵ�½��2�������ˣ�3������ߣ�4�������Ա 
//5+0���뵥Ԫ 5+1�������Ԫ 5+2�ǽ����� 5+3ƴ�ӷ�����PAD 5+4 ���� pad 5+5����PC 5+6���ԱPC 5+7������ԭ��(�����˺ͱ绤��) 5+8��Ժ����ͥ
typedef enum _eStatusFlagType { ntStatusFlageNull,ntLogin,ntPresideLogin,ntConferenceUser,ntWatchUser,ntIM , } StatusFlagType;

// Popedom Type
typedef enum _ePopedomType { ntAllowKinescope,ntAllowControl,ntSetTalk,ntAllowUseWhiteBoard,ntAllowFloatDrag,ntAllowAskTalk, nScreenControl } PopedomType;

//////////////////////////////////////////////////////////////////////
// Struct
//Info
typedef struct _TInfo
{
	InfoType	_InfoType;				//��Ϣ����	0:�� 1:MCU 2:User
} TInfo;		//������

//User Info
typedef struct _TUserInfo  :public TInfo
{
	TCHAR		_strUserName[51];				//�û���
	TCHAR		_iUserID[21];					//�û�ID
	unsigned __int32		_iSessionID;				//�ỰID
	unsigned __int32			_iConferenceID;				//����ID
	bool		_bPresentFlag;				//ȱϯ��־ 0:ȱϯ1:�ڻ�
	byte		_iOnlineFlag;				//���߱�־	0:������
														//1:����������Ƶ
														//2:��������Ƶ����Ƶ
														//3:��������Ƶ����Ƶ
														//4:����������Ƶ
	unsigned __int32			_iMCUID;				//��½��MCU��id
	TCHAR		_strOnlineTime[15];						//��½ʱ�� ��ʽ��yyyymmddhhmmss
	byte		_iUserStatus;							//ͬStatusFlagType
	HTREEITEM	*_phRoot;
} TUserInfo;		//������ߺͷǶ���MCU�е��û��б�

// Video Card Info
typedef struct _TVideoCardInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	byte			_iUserCardNo;				//�û���Ƶ����	0~12  199·��Ϊ��������
	byte			_iUserCodeType;				//�û���Ƶ��������	4:X264 VBR(HP_VIDEO_CODEC_WMVA),
												//						3:X264 CBR(HP_VIDEO_CODEC_H264_VBR_HARDWARE),
												//						1:H263++ VBR(HP_VIDEO_CODEC_H263P)

	byte			_iUserDisplayType;			//�û��ֱ���	0:176*144
												//				1:242*176
												//				2:320*240
												//				3:352*288
												//				4:640*480
												//				5:704*576

	byte			_iUserFrame;				//�û�֡��
	bool			_bUserPreventInterleaved;	//ͼ�������Զ�����
	bool			_bUserRemoveConfusion;		//�û���Ƶȥ��							
	byte			_iUserMaxStream;			//�û���Ƶģʽ ��û��
	byte			_iUserPicQuality;			//�û�ͼ������
	byte			_iVideoDriverIndex;			//��Ƶ�豸��
	unsigned __int32	_iLockSessionID;		//��˭��������Ƶ
} TVideoCardInfo;
typedef CTypedPtrArray<CPtrArray, TVideoCardInfo*> CTVideoCardInfoArray;

// Video Driver Info
typedef struct _TVideoDriverInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	TCHAR			_strDriverName[256];				//�豸����
	bool			_bVideo_HDDevice;					//�Ƿ��Ǹ��忨
	bool			_bAcquisitionCardHaveSound;			//�ɼ����������ɼ�
} TVideoDriverInfo;
typedef CTypedPtrArray<CPtrArray, TVideoDriverInfo*> CTVideoDriverInfoArray;

// Sound Driver Info
typedef struct _TSoundDriverInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	TCHAR			_strDriverName[256];				//�豸����
} TSoundDriverInfo;
typedef CTypedPtrArray<CPtrArray, TSoundDriverInfo*> CTSoundDriverInfoArray;

// Media Info
typedef struct _TMediaInfo				//ý���ʽ�ṹ
{
	byte		_iCodeType;				//��������
	byte		_iDisplayType;			//�ֱ���
	byte		_iFrame;				//֡��
	byte		_iMaxStream;			//�������
	byte		_iPicQuality;			//ͼ������
	bool		_bAutoQuality;			//ͼ�������Զ�����
}TMediaInfo;

//Conference User Info
typedef struct _TConferenceUserInfo	: public TUserInfo
{
	//���û��������˺��ڶ���MCU�м�¼
	byte			_iUserMicType;				//�û���Ƶ��������	0:MS G.723.1,2:WB,255:����Ƶ
	bool			_bAllowKinescope;			//����¼��
	bool			_bAllowControl;				//������̨����
	byte			_iTalkControl;				//���ۿ���	0:��ֹ����,1:��������,2:������������,3:��������,4:���������������
	bool			_bAllowUseWhiteBoard;		//����ʹ�ðװ�
	bool			_bAllowFloatDrag;			//�����������϶�
	bool			_bAllowAskTalk;				//����������
	bool			_bAllowAskScreenControl;	//����������Ļ����
	byte			_iSoundDriverIndex;			//��Ƶ�豸��
	TCHAR			_strMediaFile[256];			//ý���ļ�·��
	TMediaInfo		*_ptMediaInfo;				//ý���ʽ�ṹ
	byte			_iFrameResource;			//��Դ��	0:1����Դ��1:2����Դ

	CTVideoCardInfoArray _aVideoCardInfo;		//��Ƶ������
	CTSoundDriverInfoArray _aSoundDriverInfo;	//����������Ϣ
	CTVideoDriverInfoArray _aVideoDriverInfo;	//��Ƶ������Ϣ

	//�����ڴ�
	bool		_bControl;					//�Ƿ���ʾ������	(��ͬ��)
} TConferenceUserInfo;		//�����˺Ͷ���MCU���û��б����û�

typedef struct _TConferenceUserADDInfo	: public TUserInfo
{
	//TConferenceUserInfo userinfo;
	
		bool bControl ;
		 int nPart ;
		 int nAll ;
		 int ndefValue ;
		 int nPersonType ;


} TConferenceUserAddInfo;		//�����˺Ͷ���MCU���û��б����û�

// Conference Base Info
typedef struct _TConferenceBaseInfo
{
	unsigned __int32			_iConferenceID;	//����ID				
	TCHAR		_strConferenceName[61];			//��������
	TCHAR		_strConferenceTopic[255];		//��������
} TConferenceBaseInfo;

//��������״̬
typedef struct _TConferenceNotifyState
{
    TConferenceBaseInfo *pInfo;
    unsigned nNotifyCount;
}TConferenceNotifyState;

// VideoSound Info
typedef struct _TVideoSoundInfo
{
	byte			_iUserCardNo;				//�û���Ƶ����	0~12
	bool			_bSound;					//�Ƿ�㲥��Ƶ
	bool			_bVideo;					//�Ƿ�㲥��Ƶ
} TVideoSoundInfo;		//��MCU�м�¼

// Win Info
typedef struct _TWinInfo
{
	FrameInfoType			_iFrameInfoType;	//������ʾ����������Ϣ
	unsigned __int32		_iSessionID;		//�ỰID
	TVideoSoundInfo*		_ptVideoSoundInfo;	//������ʾ��������Ƶ��������Ƶ��Ϣ
	
	//�ڱ�������
	CWnd*				_pdDialogInf;		//�Ի���ָ��
	CRect					_rcScreen;			//���ڵ�����
} TWinInfo;		//��MCU�м�¼
typedef CTypedPtrArray<CPtrArray, TWinInfo*> CTWinInfoArray;

//// WhiteBoard Info
//typedef struct _TWhiteBoardInfo
//{
//	byte			_iWinNo;					//����
//	byte			_iFrameNo;					//�ڼ�����
//} TWhiteBoardInfo;		//��MCU�м�¼

//Screen Info
//typedef struct _TScreenInfo
//{
//	unsigned __int32		_iSessionID;		//�ỰID
//	byte			_iWinNo;					//����
//	byte			_iFrameNo;					//�ڼ�����
//} TScreenInfo;			//��MCU�м�¼

//TalkOver Info
//typedef struct _TTalkOverInfo
//{
//	byte			_iWinNo;					//����
//	byte			_iFrameNo;					//�ڼ�����
//} TTalkOverInfo;			//��MCU�м�¼

//Medio Info
//typedef struct _TMedioInfo
//{
//	unsigned __int32		_iSessionID;		//�ỰID
//	byte			_iWinNo;					//����
//	byte			_iFrameNo;					//�ڼ�����
//} TMedioInfo;			//��MCU�м�¼


//Prolocutor Info
//�ڱ����м�¼
typedef struct _TProlocutorInfo
{
	TConferenceUserInfo	*_pConferenceUserInfo;	//��������Ϣ
	BOOL			_bIsProlocutor;				//�Ƿ��Ƿ�����
} TProlocutorInfo;
typedef CTypedPtrArray<CPtrArray, TProlocutorInfo*> CTProlocutorInfoArray;

// Conference Info
typedef struct _TConferenceInfo : public TConferenceBaseInfo
{
	unsigned __int16			_iBandwidth;	//���ƵĴ���
	byte			_iOneWinClass;				//1��������	1��2��3�ڼ������� ��TemplateType
	bool			_bOneWinTemplate;			//1����ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte			_iOneWinNumber;				//1��������	
	byte			_iOneWinType;				//1��������
	byte			_iTwoWinClass;				//2��������	1��2��3�ڼ������� ��TemplateType
	bool			_bTwoWinTemplate;			//2����ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte			_iTwoWinNumber;				//2��������
	byte			_iTwoWinType;				//2��������

	//��MCU�м�¼
	unsigned __int32			_iSpokesmanID;				//�ݽ���ID	0�����ݽ���
	byte		_iFrameNo;					//��ʾ������
	bool		_bAllowKinescope;			//����¼��
	bool		_bAllowControl;				//�������
	byte		_iTalkControl;				//���ۿ���	0:��ֹ����,1:��������,2:������������,4:���������������
	bool		_bAllowUseWhiteBoard;		//����ʹ�ðװ�
	bool		_bAllowFloatDrag;			//�����������϶�
	bool		_bAllowAskTalk;				//����������
	bool		_bAllowAskScreenControl;	//����������Ļ����
	TCHAR		_strAfficheSet[30 + 8 + 256];		//��Ļ����(���� + ��ɫ + �ı���Ϣ)
	bool		_bAfficheFlag;				//��Ļ����
	CTWinInfoArray	*_aWinInfo[CONFERENCE_WIN_NUMBER];				//���鴰����Ϣ
	bool		_bConferenceTopicFlag;		//������ⷢ��
	unsigned __int32		_iFloatWinUserSessionID;				//�������û��ỰID 0���޸�����
	byte		_iUserCardNo;					//�������û�����
	unsigned __int16		_iFloatWinRect[6];		//����������
	bool		_bWatchUserControl;			//�����Ա����Ȩ��		�����Ա����
	unsigned __int32 _iFullScreenSessionID;		//������Ļȫ����ԱID
	bool		_bIsAllowInConference;			//�Ƿ�����������Ա�������
	bool		_bCalling;						//����
	byte		_iLinkage;						//��Ļ����	0:������ 1:����

	unsigned __int32 _iPresentCount;			//������������
	unsigned __int32 _iConferenceUserCount;		//����������

	byte			_iWinClass[CONFERENCE_WIN_NUMBER];				//������	1��2��3�ڼ������� ��TemplateType
	bool			_bWinTemplate[CONFERENCE_WIN_NUMBER];			//��ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte			_iWinNumber[CONFERENCE_WIN_NUMBER];				//������	
	byte			_iWinType[CONFERENCE_WIN_NUMBER];				//������
	//�����˱���
//	CTProlocutorInfoArray	_aAskSpeakUserInfo;	//�����Ե���Ϣ
} TConferenceInfo;

// MCU Info
typedef struct _TMCUInfo:public TInfo
{
	unsigned __int32			_iMCUID;					//MCUID
	TCHAR		_strMCUName[31];				//MCU����
	TCHAR		_strMCUIPAddress[15];			//IP��ַ
	unsigned __int32			_iUPMCUid;					//�ϼ�MCUid
	HTREEITEM	*_phRoot;
} TMCUInfo;

//Repetition User Info
//typedef struct _TRepetitionUserInfo
//{
//	TConferenceUserInfo	*_pConferenceUserInfo;	//����ѭ���û�ָ��
//	bool		_bRepetitionDegree;			//�����ѱ���ѭ��
//} TRepetitionUserInfo;			//�����˱���

//  PreSetting Info
typedef struct _TPreSettingInfo
{
	bool		_bUseFlag;			//�Ƿ�����
	byte		_iCodeType;			//��������
	byte		_iDisplayType;		//����ֱ���
	byte		_iFrame;			//֡��
	byte		_iVideoMode;		//��Ƶģʽ
	byte		_iPicQuality;		//��Ƶ����
	byte		_iHDDisplayType;	//����ֱ���
	bool		_bAutoPicQuality;	//ͼ�������Զ�����	//modified by lzl,2008.10.29
}TPreSettingInfo;
typedef CTypedPtrArray<CPtrArray, TPreSettingInfo*> CTPreSettingInfoArray;	

// Preside User Info
typedef struct _TPresideUserInfo
{
	//�ڱ��ر��������
	byte			_iRepetitionUserNumber;		//��ѭ�û���
	byte			_iRepetitionTime;			//��ѭʱ��
	byte			_iWhatWinRepetition;		//��ѭ����Ļ��
	bool			_bRepetitionSoundFlag;		//��ѭʱ������־
	byte			_iBroadcast;				//��ѭ��־ 0: ����ѭ 1: ��ѭʱ�㲥 2: ��ѭʱ����(���㲥)

	bool			_bConferenceSynchronizationFlag;	//����ͬ��
	bool			_bVASynchronizationFlag;			//����Ƶͬ��
	bool			_bWinLayoutSynchronizationFlag;		//���ڲ���ͬ��
//	bool			_bConferencePreSettingFlag;	//�Ƿ�ʹ�û���Ԥ����

    bool        _bVoiceInspirit;            //�����л�
	byte		_iInspiritTimeSegment;		//ÿ������Ϊһ�������л�ʱ���
	byte		_iInspiritTimeSpeak;		//ÿ�������л�ʱ�������˭����
	
	//bool		_bBigWinFlag;				//�󴰿����ñ�־
	//bool		_bLittleWinFlag;			//С�������ñ�־
	bool		_bUp9WinFlag;				//����9�������ñ�־
	bool		_bDown9WinFlag;				//С��9�������ñ�־
	//byte		_iBigWinCodeType;			//�󴰿ڱ�������
	//byte		_iBigWinDisplayType;		//�󴰿ڷֱ���
	//byte		_iBigWinFrame;				//�󴰿�֡��
	//bool		_bBigWinPreventInterleaved;	//�󴰿ڷ�ֹ����ɨ��
	//byte		_iBigWinMaxStream;			//�󴰿��������
	//byte		_iBigWinPicQuality;			//�󴰿�ͼ������
	//byte		_iLittleWinCodeType;		//С���ڱ�������
	//byte		_iLittleWinDisplayType;		//С���ڷֱ���
	//byte		_iLittleWinFrame;			//С����֡��
	//bool		_bLittleWinPreventInterleaved;	//С���ڷ�ֹ����ɨ��
	//byte		_iLittleWinMaxStream;		//С�����������
    //byte		_iLittleWinPicQuality;		//С����ͼ������
	byte		_iDown9WinCodeType;			//С��9���ڱ�������
	byte		_iDown9WinDisplayType;		//С��9���ڷֱ���
	byte		_iDown9WinFrame;			//С��9����֡��
	bool		_bDown9WinPreventInterleaved;	//С��9���ڷ�ֹ����ɨ��
	byte		_iDown9WinMaxStream;		//С��9�����������
	byte		_iDown9WinPicQuality;		//С��9����ͼ������
	byte		_iUp9WinCodeType;			//����9���ڱ�������
	byte		_iUp9WinDisplayType;		//����9���ڷֱ���
	byte		_iUp9WinFrame;				//����9����֡��
	bool		_bUp9WinPreventInterleaved;	//����9���ڷ�ֹ����ɨ��
	byte		_iUp9WinMaxStream;			//����9�����������
	byte		_iUp9WinPicQuality;			//����9����ͼ������

	bool		_bAutoPicQuality;			//ͼ�������Զ����� lzl add 2008.10.29

	CTPreSettingInfoArray	_aPreSettingInfoArray;		//Ԥ���ò�������
	CTWinInfoArray	_aVideoInfoArray;		//��¼���ؽ��մ��ڵ���Ϣ

} TPresideUserInfo;


// Local User Info
typedef struct _TLocalUserInfo
{
	////�ڱ��ر��������	
//	bool		_bShowMainWin;				//����¼ʱ����ʾ������
//	TCHAR		_strPicDir;					//ͼ��·��
	BOOL		_bConferenceNotify;			//�Ƿ��������
	int			_iConferenceMin;			//ÿ������ÿ������������һ��
	int			_iConferenceAwakeNumber;	//ÿ���������Ѽ���
	BOOL		_bLogAwake;					//��ÿ�ε�¼ʱ����
	int			_iConferenceInviteFlag;		//�������뷽ʽ:
											// 0: �ܾ���������
											// 1: �����Ի�����ʾ
											// 2: �Զ��������
	BOOL		_bExitAndJoinNewMeet;		//�˳���ǰ����, �������µĻ���.
	int			_iCallingCloseSecond;       //��������ʱ����������
	BOOL		_bAutoCalling;				//�Ƿ����������Զ�����
	int			_iAutoCallingMinSect;		//�Զ�����ʱ��η���
	unsigned __int32		_iCallingSessionID;	//�����߻ỰID
	BOOL		_bRunControlerHook;			//���п�����
	BOOL		_bUseVideoSoundSynchronization;		//���ô���ͬ��
	int			_iVideoSoundSynchronizationTime;	//����Ƶ����ͬ�������ʱ��Ĵ�С����С10�룬���5���� ��λ��
	BOOL		_bToAllConferenceUserFullScreen;	//��Ƶ�������֪ͨ���г�Ա
	ScreenType	_iScreenType[CONFERENCE_WIN_NUMBER];					//��������
	OperateType	_iOperateType;				//��ʲô�������� 
	VideoShowModeType _iVideoShowMode;		//��Ƶ��ʾģʽ
	BOOL		_bScreenShowMode[CONFERENCE_WIN_NUMBER];			//��Ļ��ʾģʽ
	int			_iShowUserState;			//��ʾ����Ա״̬  0:��ʾ������Ա 1:ֻ��ʾ������Ա 2:ֻ��ʾ�ڻ���Ա
	
	//�����ڴ���ʱ����
	BOOL		_bShowTitleBar;				//Ϊ���ƣ��ڡ��������˵������ӡ���ʾ������������Ĭ��ѡ��
											//add by lzl,2008.10.20

	BOOL		_bShowCodeFlow;				//��ʾ����
	CString		_strPassword;				//����
	TCHAR		_strMCUIPAddress[256];		//IP��ַ
	unsigned __int16 _iMCUPort;				//ʹ�õĶ˿�
	int			_iStatusFlag;				//��ݱ�־	0:û��½��1���ѵ�½��2�������ˣ�3������ߣ�4�����Ա
	BOOL		_bVideoOrder;				//��ƵԤ��
	BOOL		_bVideoTCPorUDP;			//��Ƶ���䷽ʽTCP/UDP  1:TCP 0:UDP
	BOOL		_bShowHaveUserMCU;			//��ʾ���˵�MCU�ڵ�
	CString		_strSearchUser;				//���ҵ��˵��ֶ�
	TConferenceUserInfo	*_pUserInfo;		//���û�ָ��
	TConferenceInfo		*_pConferenceInfo;	//����Ļ���
	TPresideUserInfo	*_pPresideUserInfo;	//�������д�����
} TLocalUserInfo;

//TalkOver Data Info
typedef struct _TTalkOverDataInfo
{
	unsigned __int32		_iSessionID;	//�û�ID
	TCHAR		_cTalkOver_Data[256];			//���۵���Ϣ
} TTalkOverDataInfo;			//��MCU�м�¼

//��ƵCOM����
struct ComParameter
{
	int nType;
	int nComPort;
	int nSerialNumber;
};

// VOD Info
typedef struct _TVODInfo
{
	TCHAR		_strVODName[90];									//VOD����
	TCHAR		_strVODIPAddress[45];								//IP��ַ
} TVODInfo;


typedef CTypedPtrArray<CPtrArray, TTalkOverDataInfo*> CTTalkOverDataInfoArray;

typedef CTypedPtrArray<CPtrArray, TConferenceBaseInfo*> CTConferenceBaseInfoArray;
typedef CTypedPtrArray<CPtrArray, TConferenceInfo*> CTConferenceInfoArray;
typedef CTypedPtrArray<CPtrArray, TMCUInfo*> CTMCUInfoArray;
typedef CTypedPtrArray<CPtrArray, TUserInfo*> CTUserInfoArray;
typedef CTypedPtrArray<CPtrArray, TConferenceUserInfo*> CTConferenceUserInfoArray;
typedef CTypedPtrArray<CPtrArray, TConferenceNotifyState *> CTConferenceNotifyStateArray;
typedef CTypedPtrArray<CPtrArray, TVODInfo *> CTVODInfoArray;

//
TVideoCardInfo *GetVideoCardSetting(CTVideoCardInfoArray &array, int nCardNo);

typedef struct _TSelectedUserInfo
{
	TConferenceUserInfo*	_ptConferenceUserInfo;		// ѡ�е���Ա��Ϣ				
	byte					_iSeleCardNo;				// ѡ�е���Ա��Ϣ�Ŀ���	
} TSelectedUserInfo;
typedef CTypedPtrArray<CPtrArray, TSelectedUserInfo*> CTSelectedUserInfoArray;


//��Ƶ����͸��������λ��ö���������� add lzl 2008-9-26
typedef enum _ETitleBarPos { TOP_LEFT=0,BOTOM_LEFT} ETitleBarPos;

#endif // !defined(AFX_RESOURCEDEFINE_H__9ACA1E49_32C3_439B_BF25_3A372B7C5A38__INCLUDED_)
