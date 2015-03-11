// IVideoSystem.h

#if !defined(_VIDEOSYSTEM_H__20091124_092009__INCLUDED_HHJ_)
#define _VIDEOSYSTEM_H__20091124_092009__INCLUDED_HHJ_

// **************************************************************
//  VideoSystem Interface   version:  1.0   ��  date: 11/24/2009
//  -------------------------------------------------------------
//  ��Ƶ����ϵͳ����ӿ�
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
//                                                 By:    HHJ
// ***************************************************************


#define  MY_VIDEO_CONFERENCE_SYSTEM_MSG   WM_USER + 14678
typedef enum _ewParamDate {enSystemQuit = 0/*ϵͳ�˳�*/, enExitConf} eWPARAM_DATE;


#ifdef _VIDEOSYSTEM_CONFERENCE_HHJ_
#define DllExport_VIDEO_CONF_SYSTEM __declspec(dllexport)
#else
#define DllExport_VIDEO_CONF_SYSTEM __declspec(dllimport) 
#endif



//////////////////////////////////////////////////////////////////////////
//    ��Ƶ����ϵͳ�ص�֪ͨ�ӿڣ� ��̳�
//////////////////////////////////////////////////////////////////////////
interface IVideoConfSystemNotify
{
public:
	IVideoConfSystemNotify(){};
	virtual ~IVideoConfSystemNotify(){};

	// �õ��û���¼MCU����Ϣ
	// nMcuLevel     MCU ����Ŀǰֻ��0
	// pszServerIP   ��������IP��ַ
	// pszUserID     �û���¼��ID���û���¼�ʺţ�
	// pszPassword	 ��½����
	virtual void GetLoginMCUInfo(int &nMcuLevel, CString &strServerIP, CString &strUserID, CString &strPassword) = 0;
	// �õ�Ҫ��������ҵ�ID
	virtual int GetLoginConferenceID() = 0;
	//�õ�¼���ļ�·������
	virtual CString GetFilePathName() = 0;
};



//////////////////////////////////////////////////////////////////////////
//    ��Ƶ����ϵͳ���ýӿ�
//////////////////////////////////////////////////////////////////////////
interface IVideoConfSystem
{
public:
	IVideoConfSystem(){};
	virtual ~IVideoConfSystem(){};

public:
	// �ͷ���Ƶ����ϵͳ
	virtual void ReleaseVideoConfSystem(IVideoConfSystem* pISystem) = 0;
	virtual void SendDlgMessage(MSG* pMsg) = 0;
};


// ������Ƶ����ϵͳ���ýӿ�
DllExport_VIDEO_CONF_SYSTEM IVideoConfSystem* CreateIVideoConferenceSystem(IVideoConfSystemNotify* pINotify,	// ��Ƶ����ϵͳ�ص�֪ͨ�ӿ�
																		   HWND hWnd,							// �ص���Ϣ�Ľ��ܴ��ھ��
																		   BOOL bStartFromOcx,					// �����Ƿ�� OCX ����
																		   int  nFlage);						// ���ñ�ʶ 0: ����������� 1: ����¼�����
#endif