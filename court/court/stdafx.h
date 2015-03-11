
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include "resource.h"



#define  __MORE_DROG__  //�Ƿ�����������ק����
//#undef   __MORE_DROG__

//�Ƿ���IM
#define HAVE_IM_FLAG       0	

//�Ƿ�ʹ��ChatUI.dll�������ʹ��ע�͵������define��
//#define USES_CHATUI				1

//�汾��־
#define RS_FLAG      0
//ϵ����ɫ����
//#define RS_COLOR_FLAG       0				

#ifdef RS_COLOR_FLAG
//�����ڵ���ɫ����
#define COLOR_BACK_GROUND       RGB(233,254,209)
#define COLOR_BACK_GROUND2      RGB(242,253,210)
#define COLOR_TEXT				RGB(0,0,0)
#define BUTTON_BACK_COLOR		RGB(167,219,9)
#define MENU_BACK_COLOR			RGB(243,243,243)
#define COLOR_TEXT_NORMAL		RGB(10,113,191)
#define COLOR_TEXT_SELECT		RGB(255,0,0)//RGB(255, 255, 0)
#define COLOR_TEXT_ACTIVE		RGB(7,80,135)
#define COLOR_BUTTON_NORMAL_BOTTOM		RGB(124,186,80)
#define COLOR_BUTTON_FRAME		RGB(156, 156, 156)

//IDD_USER_DIALOG����ɫ����
#define COLOR_WIN_BACK_DLG		RGB(236, 233, 216)
#define COLOR_USER_BACK_DLG		RGB(166, 182, 255)
#define COLOR_HAVE_USER_BACK_DLG		RGB(57,125,243)
#define COLOR_USER_FRAME_DLG	RGB(255, 255, 255)
#define COLOR_USER_FRAME_INDEX_DLG	RGB(255, 255, 255)
#define COLOR_SCREEN_FRAME_DLG	RGB(255, 0, 0)

//IDD_PRESIDE_CONTROL_DIALOG��button��ɫ����
#define COLOR_BUTTON_FRAME_ACTIVE_PRESIDE_CONTROL_DIALOG		RGB(255, 255, 255)
#define COLOR_BUTTON_NORMAL_BOTTOM_PRESIDE_CONTROL_DIALOG		RGB(172, 172, 172)

//IDD_LOCAL_USER_DIALOG����ɫ����
#define COLOR_CPU_TEXT RGB(0, 255, 0)
#define COLOR_CPU_LOW RGB(0,255,0)
#define COLOR_CPU_HIGH RGB(255,0,0)

//IDD_REPETITION_LIST_DIALOG����ɫ����
#define COLOR_NO_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_BKCOLOR RGB(161,216,122)
#else
//�����ڵ���ɫ����
#define COLOR_BACK_GROUND       RGB(208,214,226)	//RGB(210,210,210)
#define COLOR_BACK_GROUND2		RGB(255,255,255)	//RGB(210,210,210)
#define COLOR_TEXT				RGB(0,0,0)
#define BUTTON_BACK_COLOR		RGB(167,219,9)
#define MENU_BACK_COLOR			RGB(243,243,243)
#define COLOR_TEXT_NORMAL		RGB(10,113,191)
#define COLOR_TEXT_SELECT		RGB(255,0,0)//RGB(255, 255, 0)
#define COLOR_TEXT_ACTIVE		RGB(7,80,135)
#define COLOR_BUTTON_NORMAL_BOTTOM		RGB(101,170,211)//RGB(124,186,80)
#define COLOR_BUTTON_FRAME		RGB(156, 156, 156)

//IDD_USER_DIALOG����ɫ����
#define COLOR_WIN_BACK_DLG		RGB(236, 233, 216)
#define COLOR_USER_BACK_DLG		RGB(255,255,255)	//RGB(208,214,226)	//RGB(166, 182, 255)
#define COLOR_HAVE_USER_BACK_DLG		RGB(57,125,243)
#define COLOR_USER_FRAME_DLG	RGB(201,201,201)	//RGB(255, 255, 255)
#define COLOR_USER_FRAME_INDEX_DLG	RGB(255, 255, 255)
#define COLOR_SCREEN_FRAME_DLG	RGB(255, 0, 0)

//IDD_PRESIDE_CONTROL_DIALOG��button��ɫ����
#define COLOR_BUTTON_FRAME_ACTIVE_PRESIDE_CONTROL_DIALOG		RGB(255, 255, 255)
#define COLOR_BUTTON_NORMAL_BOTTOM_PRESIDE_CONTROL_DIALOG		RGB(172, 172, 172)

//IDD_LOCAL_USER_DIALOG����ɫ����
#define COLOR_CPU_TEXT RGB(0, 255, 0)
#define COLOR_CPU_LOW RGB(0,255,0)
#define COLOR_CPU_HIGH RGB(255,0,0)

//IDD_REPETITION_LIST_DIALOG����ɫ����
#define COLOR_NO_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_TEXT RGB(0, 0, 0)
#define COLOR_REPETITION_USER_BKCOLOR RGB(161,216,122)
#endif

// ��Ƶ�и�������ɫ
#define COLOR_VIDEO_BKCOLOR RGB(0, 0, 0)	// Add Han Huajie 2008/01/15


//�Ի�����Ͽճ��Ŀ��
#define SIDE_WIDTH				3

//�Ƿ�ǿ�Ƹ���
#define HP_UPDATE_FLAG			1

// ʹ���µ��Զ����³���
#define NEW_HPLIVEUPDATE		1		// 0 ��ԭ�����Զ����³���   1  �µ��Զ����³���

//Сͼ����Ϣ
#define WM_MYMESSAGE (WM_USER+1)

//��Ļ����߿���
#define SCREEN_BORDER_WIDTH	3

//ת����ʱ�ַ����ĳ���
#define SZTEMP_LENTH 1024 

#define CONFERENCE_WIN_NUMBER 4

//IP Camera��Ӧ����
#define IP_CAMERA_NO 100
//��Ļ�����Ӧ����
#define SCREEN_IS_VIDEO_NO 198
//�����Ӧ����
#define RGB_IS_VIDEO_NO 199
//����ý���Ӧ����
#define MEDIA_IS_VIDEO_NO 200
//H323��Ӧ�Ŀ���
#define H323_IS_VIDEO_NO 240


#define	 SEPERATE                        (_T("<_|||_>"))


//{{add by tiger,2009.06.18
const int TITALBAR_HEIGHT = 72;	//�������߶�
const int TOOLBAR_HEIGHT = 43;	//�������߶�
const int STATUS_HEIGHT = 44;	//״̬���߶�
const int TALKDLG_HEIGHT = 100;	//�������߶ȣ�δ�㲥ʱ��
const int AFFICHE_HEIGHT = 30;	//��Ļ���߶�
const int MENU_HEIGHT = 29;		//�˵����߶�
const int MAIN_FRAME_WIDTH = 3;	//������߿���
const int MENU_BMP_HEIGHT = 20;	//�˵���ͼƬ�߶�	Add HHJ 2009/10/12
//}}

//
//�Զ�����Ϣ------------------------------------------------
//

#define WM_ACCEPT_CONFERENCE WM_USER+0x12+13000		//�μӻ�����Ϣ, WPARAM = ConferenceID, LPARAM = TRUE | FALSE
#define WM_OPEN_REMOTE_VIDEO WM_USER+0x13+13000		//��Զ���û���Ƶ WPARAM=SessionID, LPARAM=MAKELONG(CardNo, WndIndex)
#define WM_OPEN_REMOTE_AUDIO WM_USER+0x14+13000		//��Զ���û���Ƶ WPARAM=SessionID, LPARAM=LPARAM=MAKELONG(CardNo, WndIndex)
#define WM_CLOSE_REMOTE_VIDEO WM_USER+0x15+13000		//�ر�Զ���û���Ƶ WPARAM=SessionID, LPARAM=CardNo
#define WM_CLOSE_REMOTE_AUDIO WM_USER+0x16+13000		//�ر�Զ���û���Ƶ WPARAM=SessionID, LPARAM=CardNo
#define WM_APPLY_VIDEO_FORMAT_PRESETTING WM_USER+0x17+13000	//Ӧ����Ƶ��ʽԤ���� WPARAM = �û���, LPARAM = ����ָ��,������������򲿷�
#define WM_VIDEO_FULL_SCREEN WM_USER+0x18+13000 //�����Ƶ WPARAM=MAKELONG(x,y), LPARAM=MAKELONG(cx,cy)
#define WM_VIDEO_RESTORE_SCREEN WM_USER+0x19+13000 //�ָ���Ƶ WPARAM=MAKELONG(x,y), LPARAM=MAKELONG(cx,cy)
#define WM_RESIZE_ALL_WND WM_USER+0x1a+13000      //�޸����д��ڵĴ�С, ������Ļ��������, 
#define WM_CAPTURE_FULL_SCREEN WM_USER+0x1b+13000 //��Ļ���� => ȫ��
//WPARAM = IsFullScreen(TRUE|FALSE)
//LPARAM = TRUE|FALSE (send this message to other window)
//

#define WM_CAPTURE_ONCE WM_USER+0x1c+13000    //��Ļ���� => ˢ��
#define WM_SCREEN_VIDEO_BMP_QUALITY WM_USER+0x1d+13000    //��Ļ���� => ͼ������
//0: stop
//1: slowly
//2: slow
//3: normal
#define WM_SCREEN_VIDEO_FRAME_RATE WM_USER+0x1e+13000 //��Ļ���� => ͼ��֡��(L)
//4: 4 bit color 
//8: 8 bit color
//16: 16 bit color 
#define WM_CONFERENCE_SYNC WM_USER+0x1f+13000 //����ͬ��, WPARAM=IsSync

#define WM_OPEN_FLOAT_WIN WM_USER+0x20+13000  //�򿪸�������, WPARAM= SessionID, LPARAM=UerCardNo.
#define WM_CLOSE_FLOAT_WIN WM_USER+0x22+13000  //�رո�������
#define WM_WAVEOUT_MUTE WM_USER+0x24+13000    //���ñ��ؾ��� WPARAM=TRUE|FALSE
#define WM_CAPTURE_FULL_SCREEN_REQUEST WM_USER+0x25+13000 //֪ͨ��������Ļȫ��
//WPARAM = nScreenIndex, LPARAM = IsFullScreen(TRUE | FALSE)
#define WM_CLOSE_CAPTURE_SCREEN_REQUEST WM_USER+0x26+13000    //֪ͨ�����ڹر���Ļ����
#define WM_RELOAD_YUTAI_PARAMETER WM_USER+0x27+13000  //���¼�����̨����
#define WM_AUTO_LOGIN_CONFERENCE WM_USER+0x28+13000  //�Զ��������(�Զ���¼) WPARAM = ConferenceID, LPARAM = TRUE | FALSE
#define WM_SET_WAVEOUT_VOLUME WM_USER+0x29+13000 //���ñ�������
#define WM_YUTAI_ACTION WM_USER+0x2B+13000 //��̨��������,WPARAM = command
#define WM_SCREEN_SWITCH_STATE WM_USER+0x2C+13000 //������Ļ�л�������״̬, WPARAM = Screen Index[0,1]
#define WM_CONFERENCE_CLSOE WM_USER+0x2d+13000    //�˳�������Ϣ
#define WM_SYSTEM_OFF_LINE  WM_USER+0x2e+13000    //ע����Ϣ
#define WM_RECIRCLE_SHOW    WM_USER+0x2f+13000    //������ѭ
//------------------------------------------------------------

#define WM_VIDEO_SETTING_ITEMER_MSG    WM_USER + 265482    //ѡ�����õ���ѡ����Ϣ
// �ͷ� ��Ƶ����ϵͳ ģ����Ϣ����
#define WM_RELEASE_DATAINFOMANAGE_MSG		24860

#define COMPONENTTYPE_DST_SPEAKERS    4
#define COMPONENTTYPE_DST_WAVEIN      7

#ifndef	 _VIDEOSYSTEM_CONFERENCE_HHJ_
	#define  _VIDEOSYSTEM_CONFERENCE_HHJ_
#endif

#ifndef _H323DATAINFO_HHJ_
	#define _H323DATAINFO_HHJ_
#endif

#ifndef _AVIDEO_TEST_HHJ_200912021041_
	#define _AVIDEO_TEST_HHJ_200912021041_
#endif

// H323 ����������ʶ�궨��	Add HHJ 20091211
//#ifndef _H323_GATEWAY_MARK_
//	#define _H323_GATEWAY_MARK_
//#endif

//Զ�̶����־
//#ifndef _REMOTE_SET_LOSS_			
//	#define _REMOTE_SET_LOSS_
//#endif

//#ifndef _IPCAMERA_
//	#define _IPCAMERA_
//#endif

//#ifndef _IFREECOMM_
//	#define _IFREECOMM_
//#endif

//#ifndef _IFREECOMM_
//#ifdef _DEBUG
//#pragma comment(lib,"../../lib/Debug/IPCamera.lib")
//#else
//#pragma comment(lib,"../../lib/release/IPCamera.lib")
//#endif
//#endif


char *ChangTextToUtf8(LPCTSTR szText,char* szTemp);				//�ı��ı���ʽΪUTf8
TCHAR *ChangUtf8ToText(const char* szText,TCHAR *szTemp);				//�ı��ı���ʽ��UTf8ת��
CString GetExePath();


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


