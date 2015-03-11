// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UserDlg.h"
//#include "../Resource/utilBase/util.h"
//#include ".\userdlg.h"
//#include "ConferenceWinDlg.h"
//#include "YunTai/DlgCtrlSetting.h"
//#include "PrePointSetDlg.h"
//#include "ConferenceDlg.h"
//#include "../AVCRecordPlayer/IAVRecordPlay.h"
//#include "AutoLockResource.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UM_AV_RECEIVE_NOTIFY	(WM_USER+100)
enum {
	HP_VIDEO_RECEIVE_CONNECTED=0,
	HP_AUDIOO_RECEIVE_CONNECTED
};

#define UM_RECORD	(WM_USER+101)
enum {
	RECORD_FULL=0,
};

// CCUserWinDlgDlg 对话框



CCUserWinDlgDlg::CCUserWinDlgDlg(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CCUserWinDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
			m_bSelect = false;
}

void CCUserWinDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCUserWinDlgDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCUserWinDlgDlg 消息处理程序

BOOL CCUserWinDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

////在OnInitDialog里进行初始化，添加如下代码 
//SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
//  GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
// HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); 
// if(hInst) 
// {            
//  typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);          
//  MYFUNC fun = NULL;
//  //取得SetLayeredWindowAttributes函数指针     
//  fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
//  if(fun)
//   fun(this->GetSafeHwnd(),0,128,2);     
//  FreeLibrary(hInst); 
// }
	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}



// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCUserWinDlgDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting


	CDC*	pDC=GetDC();
	OnEraseBkgnd(pDC);
    ReleaseDC(pDC);
	m_drawingObject.Paint(&dc);
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CCUserWinDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//设置标题栏字体,字的颜色和背景色,	add by tiger,2008.09.27
//void CCUserWinDlgDlg::SetTitleFont(LOGFONT logfont,COLORREF crText,COLORREF crBk)
//{
//	if (m_pVideoPlayer)
//	{
//		m_pVideoPlayer->SetTitleFont(logfont,crText,crBk);
//	}	
//}


void CCUserWinDlgDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		TRACE(  "Do_LButtonDown。\n");
	Do_LButtonDown(nFlags, point);

	//CDialog::OnLButtonDown(nFlags, point);
}

void CCUserWinDlgDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		TRACE(  "Do_LButtonUp。\n");
Do_LButtonUp(nFlags, point);
	//CDialog::OnLButtonUp(nFlags, point);
}
void CCUserWinDlgDlg::Do_LButtonDown(UINT nFlags, CPoint point)
{
	BOOL bControlDown = GetKeyState(VK_CONTROL) & 0x80;
	{
			m_bSelect = true;
		if (!bControlDown)
		{
		((CConferenceWinDlg*)m_pConferenceWinDlg)->SetAllWindowSelected(  false);
		((CConferenceWinDlg*)m_pConferenceWinDlg)->SetWondowSelected(m_iIndex - 1, true);
		RedrawWindow();
		}
		else
		{
		((CConferenceWinDlg*)m_pConferenceWinDlg)->SetWondowSelected(m_iIndex - 1, !IsSelected());
		RedrawWindow();	//m_bSelect = false;
		}
	}

}

void CCUserWinDlgDlg::Do_LButtonUp(UINT nFlags, CPoint point)
{

}
BOOL CCUserWinDlgDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		
	CFont	 newFont, *pOldFont;
	 m_strText = "解码器";
	TCHAR strTempText[255]=_T("");

	CRect T_rect;
	this->GetClientRect(&T_rect);

	pDC->SetTextColor(COLOR_USER_FRAME_INDEX_DLG);
	
		pDC->FrameRect(T_rect, &CBrush(COLOR_USER_FRAME_DLG));
		pDC->FillSolidRect(T_rect.left+1,T_rect.top+1,T_rect.Width()-2,T_rect.Height()-2,COLOR_USER_BACK_DLG);

		pDC->SetBkMode(TRANSPARENT);



        //计算输出位置( 居中 )
        CSize rc = pDC->GetTextExtent( m_strText) ;
        int x = (T_rect.Width()-rc.cx)/2;
        int y = (T_rect.Height()-rc.cy)/2;
		
		if (newFont.CreatePointFont(250, _T("黑体")))
		{
			pOldFont=pDC->SelectObject(&newFont);
            pDC->TextOut(2, 2, m_strText);
			pDC->SelectObject(pOldFont);
		}

DrawSelectedFrame(pDC);

return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//// CUserDlg dialog
//
//IMPLEMENT_DYNAMIC(CUserDlg, CBaseDlg)
//CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
//	: CBaseDlg(CUserDlg::IDD, pParent)
//	,m_pAVAudioReceiver(NULL)
//	,m_pAVVideoReceiver(NULL)
//	,m_ulAudioReceiverChannelID(0)
//	,m_ulVideoReceiverChannelID(0)
//	,m_IsReceivingAudio(true)
//	,m_IsReceivingVideo(true)
//    ,m_hTitleDlgTimer(0L)
//    ,m_nVolumeTimer(0L)
//    ,m_ulVolumeTime(0L)
//	,m_iAudioLevelTitleTimer(0)
//	,m_pAVCRecordFactory(NULL)
//	,m_pAVCRecordAudioStream(NULL)
//	,m_pAVCRecordVideoStream(NULL)
//	,m_pConferenceRecordVideoStream(NULL)
//	,m_pConferenceRecordAudioStream(NULL)
//	,m_bIsConferenceFirstFrame(TRUE)
//	,m_bIsFirstFrame(TRUE)
//    ,m_bInVoiceInspirite(false)
//    ,m_pDlgPrepointSet(NULL)
//    ,m_LastAudioBitrate(0.0f)
//    ,m_LastVideoBitrate(0.0f)
//	//,m_pdWizardDlg(NULL)
//	,m_pAudioSettingDlg(NULL)
//	,m_pVideoSettingDlg(NULL)
//	,m_pDlgFile(NULL)
//	,m_bCloseDlgFileFlag(FALSE)
//	,m_strRecordPathName(_T(""))
//	,m_pDlgCtrlRemoteSetting(NULL)
//	, m_bFullScreenCpture(FALSE)
//	, m_pWinVideoFormatSetDlg(NULL)
//	//, m_pBkBitmap(NULL)
//	, m_pDetailInfoDlg(NULL)
//	, m_pISendAVdieoDataInfo(NULL)
//	,m_bHaveAudioData(FALSE)
//	, m_bHaveVideoData(FALSE)
//	,m_pAudioPlay(NULL)
//	,m_nCurVolume(0)
//{
//	//{{AFX_DATA_INIT(CUserDlg)
//		// NOTE: the ClassWizard will add member initialization here
//	//}}AFX_DATA_INIT
//	m_pVideoPlayer=NULL;
//	m_pDlgYT = NULL;
//	m_pDlgAVInfo = NULL;
////	m_bMoving = false;
//	m_nTimerCheckAudioDisconnected=0;
//	m_nTimerCheckVideoDisconnected=0;
//
////  m_nVideoDataSource = emStream;
//}
//
//
//void CUserDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	//{{AFX_DATA_MAP(CUserDlg)
//		// NOTE: the ClassWizard will add DDX and DDV calls here
//	//}}AFX_DATA_MAP
//}
//
//
//BEGIN_MESSAGE_MAP(CUserDlg, CBaseDlg)
//	//{{AFX_MSG_MAP(CUserDlg)
// 	ON_WM_ERASEBKGND()
//	//}}AFX_MSG_MAP
//	ON_WM_SIZE()
//	ON_WM_CONTEXTMENU()
//	ON_COMMAND(IDM_RECORD,OnRecord)
//	ON_COMMAND(IDM_TO_JPG,OnToJPG)
//	ON_COMMAND(IDM_BROADCAST_VIDEO,OnBroadCaseVideo)
//	ON_COMMAND(IDM_BROADCAST_AVDIEO, OnBroadcastAVdieo)
//	ON_COMMAND(IDM_AVWIZARD,OnAVWizard)
//	ON_COMMAND(IDM_AUDIO_SETTING, OnAudioSetting)
//	ON_COMMAND(IDM_VIDEO_SETTING, OnVideoSetting)
//	ON_COMMAND(IDM_TITLE_BAR,OnTitleBar)
//	ON_COMMAND(IDM_STATUS_BAR,OnVideoControlBar)
//	ON_COMMAND(IDM_PRESET_POINT,OnSetPrepoint)
//	ON_COMMAND(IDM_BROADCAST_SOUND, OnBroadcastSound)
//	ON_COMMAND(IDM_WACTH_AVDIEO, OnWacthAVdieo)
//	ON_COMMAND(IDM_INCEPT_VIDEO, OnInceptVideo)
//	ON_COMMAND(IDM_INCEPT_SOUND, OnInceptSound)
////	ON_COMMAND(IDM_CLOSE_USER, OnCloseUser)
//	ON_COMMAND(IDM_SCREEN_CONTROL, OnScreenControl)
//	ON_COMMAND(IDM_SCREEN_CANCELCONTROL, OnScreenCancelControl)
//	ON_COMMAND(IDM_CONTROL_REMOTESET, OnRemoteSetting)
//    ON_WM_TIMER()
//	ON_MESSAGE(UM_AV_RECEIVE_NOTIFY,OnReveiveMessage)
//	ON_MESSAGE(UM_RECORD,OnRecordMessage)
//
////    ON_MESSAGE(WM_VIDEO_FULL_SCREEN, OnResizeWindow)
////    ON_MESSAGE(WM_VIDEO_RESTORE_SCREEN, OnResizeWindow)
//	ON_COMMAND(IDM_SHOW_CODE_FLOW, OnShowCodeFlow)
//	ON_COMMAND(IDM_LOCK_AVEDIO, OnLockAvdio)
//	ON_WM_PAINT()
//	//ON_WM_SHOWWINDOW()
//	ON_COMMAND(IDM_FULL_SCREEN, OnFullScreen)
//	ON_COMMAND(IDM_FULL_SCREEN_CAPTURE, OnFullScreenCpture)
//	ON_COMMAND(IDM_SEEING_PROPORTION_INCISE_SHOW, OnVideoShowModeCut)
//	ON_COMMAND(IDM_SEEING_PROPORTION_PADDED_SHOW, OnVideoShowModeFill)
//	ON_COMMAND(IDM_FULL_PANORAMA_SHOW, OnVideoShowModeFull)
//	ON_COMMAND(IDM_SYNC_HRONIZATION, OnSyncHronization)
////	ON_WM_LBUTTONDOWN()
//
////	ON_WM_MOUSEWHEEL()
//
//	ON_MESSAGE(WM_AUDIO_SETTING_MSG,OnAudioSetMessage)
//	ON_MESSAGE(WM_VIDEO_SETTING_MSG,OnVideoSetMessage)
//
//	ON_COMMAND(IDM_USER_VIDEO_FORMAT_SETTING, OnWinUserVideoFormatSet)
//	ON_COMMAND(IDM_WIN_VIDEO_FORMAT_SETTING,  OnWinVideoFormatSet)
//	ON_MESSAGE(MW_WIN_VIDEOFORMAT_SET_OKCANAL, OnWinVideoFormatSetMessage)
//	ON_COMMAND(IDM_DETAILINFO_SHOW,  OnDetailInfoShow)
//	ON_MESSAGE(MW_WIN_DETAILINFO_OKCANAL, OnWinDetailInfoMessage)
//	ON_WM_DESTROY()
//END_MESSAGE_MAP()
//
///////////////////////////////////////////////////////////////////////////////
//// CUserDlg message handlers
//
//BOOL CUserDlg::OnInitDialog() 
//{
//	CBaseDlg::OnInitDialog();
//	
//	// TODO: Add extra initialization here
//
//	// AutoLockResource Lock;
//
//	m_pDlgAVInfo = new CDlgAVInfo(this);
//	m_pDlgAVInfo->Create(CDlgAVInfo::IDD,this);
////	m_pDlgAVInfo->SetRemoteVolume(TRUE);
//
//	if (!m_pDlgYT)
//	{
//		m_pDlgYT = CreateDlgYT( this, this );
//	}
//
//	//if (!m_pDlgCtrlRemoteSetting)
//	//{
//	//	m_pDlgCtrlRemoteSetting = new CDlgCtrlRemoteSetting(m_pdMainDlg, this);
//	//	m_pDlgCtrlRemoteSetting->Create(m_pDlgCtrlRemoteSetting->IDD,this);
//	//}
//
//	TCHAR strText[255]=_T("");
//
//	project_language_loadstring(_T("DIALOG"), _T("FLOAT_TEXT"), strText, 255);
//	m_strFloat.Format(_T("%s"),strText);
//
//	//CImage imgTemp;
//	//imgTemp.Load(GetExePath() + _T("\\SKIN\\DEFAULT\\UserDlgBk.png"));
//	//if ( m_BkBitmap.m_hObject ) 
//	//	m_BkBitmap.Detach();
//	//m_BkBitmap.Attach(imgTemp.Detach());	
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	              // EXCEPTION: OCX Property Pages should return FALSE
//}
//
//BOOL CUserDlg::OnEraseBkgnd(CDC *pDC)
//{
//	CFont	 newFont, *pOldFont;
//	CString strText;
//	TCHAR strTempText[255]=_T("");
//
//	CRect T_rect;
//	this->GetClientRect(&T_rect);
//
//	if (m_iIndex==0 && !m_bLocalLoopBackTest)
//	{
//		pDC->FillSolidRect(T_rect,COLOR_USER_BACK_DLG);
//		return TRUE;
//	}
//
//	pDC->SetTextColor(COLOR_USER_FRAME_INDEX_DLG);
//
//	if ((!m_pVideoPlayer)&&(!m_pAudioPlay))
//	{
//	//	CPaintDC dc(this);
//	/*	CDC dcMem; 
//		dcMem.CreateCompatibleDC(pDC); 
//
//		CBitmap *pbmpOld=dcMem.SelectObject(m_pBkBitmap);
//		int iLeft,iTop;
//		iLeft = (1920 - T_rect.Width())/2;
//		iTop = (1080 - T_rect.Height())/2;
//		//pDC->StretchBlt(0,0,T_rect.Width(),T_rect.Height(),&dcMem,iLeft,iTop,T_rect.Width(),T_rect.Height(),SRCCOPY);
//		pDC->BitBlt(0,0,T_rect.Width(),T_rect.Height(),&dcMem,iLeft,iTop,SRCCOPY);
//		dcMem.SelectObject(pbmpOld);
//		dcMem.DeleteDC();
//*/
//		pDC->FrameRect(T_rect, &CBrush(COLOR_USER_FRAME_DLG));
//		pDC->FillSolidRect(T_rect.left+1,T_rect.top+1,T_rect.Width()-2,T_rect.Height()-2,COLOR_USER_BACK_DLG);
//
//		pDC->SetBkMode(TRANSPARENT);
//
//		//if (m_strUserName!="")
//		//{
//		//	project_language_loadstring(_T("IDD_USER_DIALOG"), _T("IDD_USER_DIALOG_INVITE_USER"), strTempText, 255);
//		//	strText.Format(_T("%s%s..."), strTempText,m_strUserName);
//		//}
//		//else
////		strText.Format(_T("%d"), m_iIndex);
//
//        ////计算输出位置( 居中 )
//        //CSize rc = pDC->GetTextExtent( strText) ;
//        //int x = (T_rect.Width()-rc.cx)/2;
//        //int y = (T_rect.Height()-rc.cy)/2;
//		
///*		if (newFont.CreatePointFont(250, _T("黑体")))
//		{
//			pOldFont=pDC->SelectObject(&newFont);
//            pDC->TextOut(2, 2, strText);
//			pDC->SelectObject(pOldFont);
//		}
//*/
//		DrawSelectedFrame(pDC);
//		return TRUE;
//	}
//	else
//	{
//		if (m_bWatch  && !m_bLocalLoopBackTest)
//		{
//			project_language_loadstring(_T("DIALOG"), _T("AUDIO_VIDEO_WINDOWS"), strTempText, 255);
//			strText.Format(_T("%s"), strTempText);
//
//			//
//			pDC->FillSolidRect(T_rect,COLOR_HAVE_USER_BACK_DLG);
//			if (newFont.CreatePointFont(250, _T("黑体")))
//			{
//				pOldFont=pDC->SelectObject(&newFont);
//
//				//计算输出位置( 居中 )
//				CSize rc = pDC->GetTextExtent( strText) ;
//				int x = (T_rect.Width()-rc.cx)/2;
//				int y = (T_rect.Height()-rc.cy)/2;
//
//				pDC->TextOut(x, y, strText);
//				pDC->SelectObject(pOldFont);
//			}
//			DrawSelectedFrame(pDC);
//			return TRUE;
//		}
//		else
//			if (!m_bHaveVideoData)
//			{
//				//if (m_pVideoPlayer&&m_pVideoPlayer->IsWindowVisible())
//				//	m_pVideoPlayer->ShowWindow(FALSE);
//				
//				if (GetRecordFlag())
//				{
//					pDC->FrameRect(T_rect, &CBrush(COLOR_USER_FRAME_DLG));
//					pDC->FillSolidRect(T_rect.left+1,T_rect.top+1,T_rect.Width()-2,T_rect.Height()-2,COLOR_USER_BACK_DLG);
//				}
//				else
//					pDC->FillSolidRect(T_rect,COLOR_HAVE_USER_BACK_DLG);
//				DrawSelectedFrame(pDC);
//
//				return TRUE;
//			}
//
//		if ((T_rect.Width()!=0) && (T_rect.Height()!=0) /*&& (m_iCardNo != 200)*/)	// Modi Han Huajie 2008/01/15 
//		{
//			if (m_nVideoShowMode != ntVideoShowModeFill)
//			{
//				DrawSelectedFrame(pDC);
//				return TRUE;
//			}
//
//			//修正系数
//			float g = GetK();
//			float x, y;
//
//			if (m_pVideoPlayer)
//			{
//				VIDEO_DIS_SIZE tVideoSize;
//				m_pVideoPlayer->GetVideoSize(&tVideoSize);
//				x=tVideoSize.width/(GetWidth_K()*g);
//				y=tVideoSize.height;
//			}
//			else
//			{
//				x = 352.0;
//				y = 288.0;
//			}
//
//			if ((T_rect.Width()*y/x) > T_rect.Height())
//			{
//				int cx = T_rect.Height()*x/y;
//				int x  = (T_rect.Width() - cx)/2;
//
//				CRect Fill_Rect;
//				Fill_Rect.left = 0;					Fill_Rect.right  = x;
//				Fill_Rect.top  = 0;					Fill_Rect.bottom = T_rect.bottom;
//
//				//deleted by tiger,2008.10.14
//				//if (m_pDlgAVInfo->IsWindowVisible())
//				//	Fill_Rect.top = 12;
//
//				if (m_pDlgYT && m_pDlgYT->IsWindowVisible())
//					Fill_Rect.bottom -= 17;
//
//				pDC->FillRect(&Fill_Rect, (CBrush*)&CBrush(COLOR_VIDEO_BKCOLOR));
//
//				Fill_Rect.left  = T_rect.right - x - 1;
//				Fill_Rect.right = T_rect.right;
//				pDC->FillRect(&Fill_Rect, (CBrush*)&CBrush(COLOR_VIDEO_BKCOLOR));
//
//			}
//			else				
//			{
//				int cy = T_rect.Width()*y/x;
//				int y  = (T_rect.Height() - cy)/2;
//
//				CRect Fill_Rect;
//				Fill_Rect.left = 0;					Fill_Rect.right  = T_rect.right;
//				Fill_Rect.top  = 0;					Fill_Rect.bottom = y;
//
//				//deleted by tiger,2008.10.14
//				//if (m_pDlgAVInfo->IsWindowVisible())
//				//	Fill_Rect.top = 12;
//
//				pDC->FillRect(&Fill_Rect, (CBrush*)&CBrush(COLOR_VIDEO_BKCOLOR));
//
//				Fill_Rect.top    = T_rect.bottom - y - 1;
//				Fill_Rect.bottom = T_rect.bottom;
//
//				if (m_pDlgYT && m_pDlgYT->IsWindowVisible())
//				{
//					if (y > 17)
//					{
//						Fill_Rect.bottom  -= 17;
//						pDC->FillRect(&Fill_Rect, (CBrush*)&CBrush(COLOR_VIDEO_BKCOLOR));
//					}
//				}
//				else
//				{
//					pDC->FillRect(&Fill_Rect, (CBrush*)&CBrush(COLOR_VIDEO_BKCOLOR));
//				}
//			}
//		}
//	}
//	DrawSelectedFrame(pDC);
//	
//	return TRUE;
//}
//
////////////////////////////////////////////////////////////////////////////
//// IOVideoDisNotify 回调接口
////输出音频数据包的回调
//void CUserDlg::OnIOAudioDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)
//{
//	if (m_pISendAVdieoDataInfo)
//		m_pISendAVdieoDataInfo->SetAudioData((BYTE*)pFrameData, nFrameLen, dSamples, m_dwH323ChannelNO);
//}
//
////输出视频数据包的回调
//void CUserDlg::OnIOVideoDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType)
//{
//	if (m_pISendAVdieoDataInfo)
//		m_pISendAVdieoDataInfo->SetVideoData((BYTE*)pFrameData, nWidth, nHeight, nFrameType, m_dwH323ChannelNO);
//}
//
////////////////////////////////////////////////////////////////////////////
//
//void CUserDlg::OnIHPAVPlayerNotifyAudioLevel(int nAudioLevel)//音量改变,显示音量
//{
//	//if (m_pDlgAVInfo)
//	//{
//	//	m_pDlgAVInfo->DisplayVolume( nAudioLevel );
//	//}
//
//    //语音激励
//    m_nCurVolume = nAudioLevel;
//    if (!m_nVolumeTimer && m_nCurVolume)
//    {
//        m_nVolumeTimer = 20;
//        SetTimer(m_nVolumeTimer, 50, NULL);
//    }
//
//	//主界面音量杆，控件现在没支持,先屏蔽
//	//if (NULL == m_pdMainDlg)
//	//	return;
//
//	//CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//	//pdMainDlg->SetVolumn(m_nCurVolume);
//}
//
//void CUserDlg::ResizeControls(void)
//{
//	//TRACE("CUserDlg::ResizeControls begin\n");
//	CBaseDlg::ResizeControls();
//	
//	if (NULL == GetSafeHwnd())
//		return;
//
//	if ((NULL == m_pVideoPlayer)&&(NULL == m_pAudioPlay))
//	{	
//		ResetWindowRgn();
//		return;
//	}
//
//	CRect	rc,rc2;
//	GetClientRect(&rc);
//
//	rc2=rc;
//	if ((m_bWatch)&&(m_pVideoPlayer))
//	{
//		m_pVideoPlayer->SetWindowPosition(0, 0, 0, 0);
//		CDC*	pDC=GetDC();
//		OnEraseBkgnd(pDC);
//		ReleaseDC(pDC);
//		return;
//	}
//
//	if ((rc.Width()!=0) && (rc.Height()!=0))	
//	{
//		float x, y;
//		if (m_pVideoPlayer)
//		{
//			VIDEO_DIS_SIZE tVideoSize;
//			m_pVideoPlayer->GetVideoSize(&tVideoSize);
//			x=tVideoSize.width/GetWidth_K();
//			y=tVideoSize.height;
//		}
//		else
//		{
//			x = 352.0;
//			y = 288.0;
//		}
//
//		switch(m_nVideoShowMode)
//		{
//		case ntVideoShowModeCut:
//			if ((rc.Width()*y/x) > rc.Height())
//			{
//				int cy=rc.Width()*y/x;
//				int y=(rc.Height() - cy)/2;
//
//				rc2.top += y;
//				rc2.bottom = rc2.top + cy;
//			}
//			else
//			{
//				int cx=rc.Height()*x/y;
//				int x=(rc.Width() - cx)/2;
//
//				rc2.left += x;
//				rc2.right = rc2.left + cx;
//			}	
//			break;
//		case ntVideoShowModeFill:
//			if ((rc.Width()*y/x) > rc.Height())
//			{
//				int cx=rc.Height()*x/y;
//				int x=(rc.Width() - cx)/2;
//
//				rc2.left += x;
//				rc2.right = rc2.left + cx;
//			}
//			else				
//			{
//				int cy=rc.Width()*y/x;
//				int y=(rc.Height() - cy)/2;
//
//				rc2.top += y;
//				rc2.bottom = rc2.top + cy;
//			}
//			break;
//		default:
//			break;
//		}
//	}
//
//	//TRACE("CUserDlg::ResizeControls begin 1\n");
//	if(m_pVideoPlayer && m_iZoomIn == 0)
//	{
//		m_pVideoPlayer->SetWindowPosition(rc2.left, rc2.top, rc2.Width(), rc2.Height());
//	}
//	//TRACE("CUserDlg::ResizeControls begin 2\n");
//
//	int iSelectFrameWidth = 0;
//	if (IsSelected())
//	{
//		iSelectFrameWidth = 2;
//	}
//
//	//视频控制		
//	if (m_pDlgYT)
//	{
//		m_pDlgYT->SetWindowPos(NULL , 0, rc.bottom-17-iSelectFrameWidth, rc.Width()-iSelectFrameWidth*2, 17, SWP_NOACTIVATE);
//	}
//
//	if (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd())
//	{
//		CRect TitleRc;
//		m_pDlgAVInfo->GetClientRect(&TitleRc);
//
//		if (m_pDlgYT->IsWindowVisible())
//		{
//			m_pDlgAVInfo->SetWindowPos(NULL, 
//									   iSelectFrameWidth, 
//									   rc.bottom-17-TitleRc.Height()-iSelectFrameWidth, 
//									   TitleRc.Width(), 
//									   TitleRc.Height(), 
//									   SWP_NOACTIVATE);
//		}
//		else
//		{
//			m_pDlgAVInfo->SetWindowPos(	NULL, 
//										iSelectFrameWidth, 
//										rc.bottom-TitleRc.Height()-iSelectFrameWidth, 
//										TitleRc.Width(), 
//										TitleRc.Height(), 
//										SWP_NOACTIVATE);
//		}
//	}
//
//    ResetWindowRgn();
//
//	//TRACE("CUserDlg::ResizeControls end\n");
//}
//
////////////////////////////////////////////////////////////////
////void CUserDlg::OnVolume(int vol)
////{
////	if(m_pVideoPlayer->HasAudio())
////    {
////		m_pVideoPlayer->SetVolume(vol);
////	}
////}
//
////
////BOOL CUserDlg::IsHaveSound()					//是否有音频
////{
////	//TRACE("CUserDlg::IsHaveSound\n");
////	//AVAutoLock l(&m_CritSecIAVAudioReceiver);
////	return (m_pAVAudioReceiver!=NULL);
////
////	return FALSE;
////}
////
////BOOL CUserDlg::IsHaveVideo()					//是否有视频
////{
////	//TRACE("CUserDlg::IsHaveVideo()\n");
////	//AVAutoLock l(&m_CritSecIAVVideoReceiver);
////	return (m_pAVVideoReceiver!=NULL);
////
////	return FALSE;
////}
//
//BOOL CUserDlg::DestroyWindow()
//{
//	// AutoLockResource Lock;
//
//	m_bLocalLoopBackTest = FALSE;
//
//	//TRACE("CUserDlg::DestroyWindow()\n");
//	if (m_pDetailInfoDlg)
//	{
//		if (m_pDetailInfoDlg->GetSafeHwnd())
//			m_pDetailInfoDlg->DestroyWindow();
//
//		delete m_pDetailInfoDlg;
//		m_pDetailInfoDlg = NULL;
//	}
//
//	//if (m_pdWizardDlg)
//	//{
//	//	m_pdWizardDlg->DestroyWindow();
//	//	delete m_pdWizardDlg;
//	//	m_pdWizardDlg=NULL;
//	//}
//
//	if (m_pAudioSettingDlg)
//	{
//		if (m_pAudioSettingDlg->GetSafeHwnd())
//			m_pAudioSettingDlg->DestroyWindow();
//
//		delete m_pAudioSettingDlg;
//		m_pAudioSettingDlg = NULL;
//	}
//
//	if (m_pVideoSettingDlg)
//	{
//		if (m_pVideoSettingDlg->GetSafeHwnd())
//			m_pVideoSettingDlg->DestroyWindow();
//
//		delete m_pVideoSettingDlg;
//		m_pVideoSettingDlg = NULL;
//	}
//
//	if (m_pWinVideoFormatSetDlg)
//	{
//		if (m_pWinVideoFormatSetDlg->GetSafeHwnd())
//			m_pWinVideoFormatSetDlg->DestroyWindow();
//
//		delete m_pWinVideoFormatSetDlg;
//		m_pWinVideoFormatSetDlg = NULL;
//	}
// 
//	if (m_pDlgCtrlRemoteSetting)
//	{
//		m_pDlgCtrlRemoteSetting->DestroyWindow();
//		delete m_pDlgCtrlRemoteSetting;
//		m_pDlgCtrlRemoteSetting = NULL;
//	}
//
//	m_bCloseDlgFileFlag=TRUE;
//	//if (m_pDlgFile)
//	//	m_pDlgFile->SendMessage(WM_QUIT);
//
//	if (m_bControl)
//		OnScreenCancelControl();
//
//	ExitFullScreen();
//	DestroyAVUserPlayer();
//	CloseSoundChannel();
//	CloseVideoChannel();
//	if (m_pAudioPlay)
//	{
//		m_pAudioPlay->ReleaseAudio();
//		delete m_pAudioPlay;
//		m_pAudioPlay=NULL;
//	}
//
//	m_pISendAVdieoDataInfo = NULL;
//	m_dwH323ChannelNO = 0;
//	StopConferenceRecord();
//	StopRecord();
//
//	if (m_pDlgAVInfo)
//	{
//		if (m_pDlgAVInfo->GetSafeHwnd())
//			m_pDlgAVInfo->DestroyWindow();
//
//		delete m_pDlgAVInfo;
//
//        m_pDlgAVInfo = NULL;
//	}
//	
//	if (m_pDlgYT)
//	{
//		m_pDlgYT->DestroyWindow();
//		delete m_pDlgYT;
//
//        m_pDlgYT = NULL;
//	}
//
//    if (m_pDlgPrepointSet)
//    {
//        m_pDlgPrepointSet->DestroyWindow();
//        delete m_pDlgPrepointSet;
//        m_pDlgPrepointSet = NULL;
//    }
//
//	//m_BkBitmap.DeleteObject();
//	//TRACE("CUserDlg::DestroyWindow() end\n");
//	return CBaseDlg::DestroyWindow();
//}
//
//BOOL CUserDlg::CreateSoundChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID)	//建立音频通道
//{
//	//TRACE("CUserDlg::CreateSoundChannel()\n");
//	m_bHaveAudioData=FALSE;
//	
//	{
//		if (NULL==m_pAudioPlay)
//		{
//			m_pAudioPlay=IOCreateAudioPlay((IOAudioPlayNotify *)this); 
//			m_pAudioPlay->SetVolume(100);
//		}
//		//AVAutoLock l(&m_CritSecIAVAudioReceiver);
//
//		if (m_pAVAudioReceiver)
//		{
//			if (m_bLocalLoopBackTest)
//			{
//				m_pAVAudioReceiver->ReleaseConnections();
//				ReleaseAudioChannl(m_pAVAudioReceiver);
//				m_pAVAudioReceiver = NULL;
//			}
//			else
//			{
//				//WriteErrorLogString(m_strUserName,_T("CUserDlg::CreateSoundChannel"),_T("ReleaseConnections begin "));
//				m_pAVAudioReceiver->ReleaseConnections();
//				delete m_pAVAudioReceiver;
//				m_pAVAudioReceiver=NULL;
//				//WriteErrorLogString(m_strUserName,_T("CUserDlg::CreateSoundChannel"),_T("ReleaseConnections end"));
//			}	
//		}
//
//		m_IsReceivingAudio=true;
//		m_ulAudioReceiverChannelID=iChannelID;
//
//		if (m_bLocalLoopBackTest)
//		{
//			m_pAVAudioReceiver = CreateVirtualIAVAudioReceiverChannl((IAVAudioReceiverNotify*)this, iChannelID);
//		}
//		else
//		{
//			if (GetRecordFlag())
//				m_pAVAudioReceiver=CreateAVAudioPlayer(*this,iChannelID);
//			else
//				m_pAVAudioReceiver=CreateIAVAudioReceiverUDP(*this,iChannelID);
//		}
//
//		if (m_iAudioLevelTitleTimer == 0)
//		{
//			m_iAudioLevelTitleTimer = 1231;
//			SetTimer(m_iAudioLevelTitleTimer, 200, NULL);    
//			OnTimer(m_iAudioLevelTitleTimer);
//		}
//
//		if (m_nTimerCheckAudioDisconnected==0)
//		{
//			m_nTimerCheckAudioDisconnected=1001;
//			SetTimer(m_nTimerCheckAudioDisconnected,1000,NULL);
//		}
//
//		m_bOpenAudio=true;
//
//#ifdef _H323_GATEWAY_MARK_
//		if (m_pdMainDlg)
//		{
//			CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//
//			TConferenceUserInfo* pUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//			if (pUserInfo)
//			{
//				// 创建H323数据发送
//				CDataInfoManage* pH323Manage = pdMainDlg->GetDataInfoManage();
//				if (NULL == pH323Manage)
//					return TRUE;
//
//				pdMainDlg->SetH323AudioAplayWnd(this);
//				CString strName;
//				if (m_iCardNo == SCREEN_IS_VIDEO_NO)
//					strName.Format(_T("%s %s"), m_strUserName, _T("屏幕"));
//				else if (m_iCardNo == MEDIA_IS_VIDEO_NO)
//					strName.Format(_T("%s %s"), m_strUserName, _T("媒体"));
//				else
//					strName.Format(_T("%s %d"), m_strUserName, m_iCardNo);
//
//				USES_CONVERSION;
//				pH323Manage->CreateAudioChannel(1, W2A(strName), 0, m_dwH323ChannelNO, 0);
//			}
//		}
//#endif
//
//		//FormateTitlebar();
//		ShowTitleBar(TRUE);
//	
//		//TRACE("CUserDlg::CreateSoundChannel() end\n");
//		return TRUE;
//	}
//
//}
//BOOL CUserDlg::CloseSoundChannel()	//关闭音频通道
//{
//	//TRACE("CUserDlg::CloseSoundChannel()\n");
//
//	m_bOpenAudio=false;
//
//	m_IsReceivingAudio=false;
//	m_ulAudioReceiverChannelID=0;
//	if (m_nTimerCheckAudioDisconnected)
//	{
//		KillTimer(m_nTimerCheckAudioDisconnected);
//		m_nTimerCheckAudioDisconnected=0;
//	}
//
//	if (m_iAudioLevelTitleTimer)
//	{
//		KillTimer(m_iAudioLevelTitleTimer);
//		m_iAudioLevelTitleTimer = 0;
//	}
//
//	{
//		//AVAutoLock l(&m_CritSecIAVAudioReceiver);
//		if (m_pAVAudioReceiver)
//		{
//			m_pAVAudioReceiver->EnableReceive(m_IsReceivingAudio);
//		}
//
//		if (m_pAVAudioReceiver)
//		{
//			if (m_bLocalLoopBackTest)
//			{
//				ReleaseAudioChannl(m_pAVAudioReceiver);
//				m_pAVAudioReceiver = NULL;
//			}
//			else
//			{
//				//WriteErrorLogString(_T("CUserDlg"),_T("CloseSoundChannel"),_T("ReleaseConnections begin"));
//				m_pAVAudioReceiver->ReleaseConnections();
//				delete m_pAVAudioReceiver;
//				m_pAVAudioReceiver=NULL;
//				//WriteErrorLogString(_T("CUserDlg"),_T("CloseSoundChannel"),_T("ReleaseConnections end"));
//
//				if (m_pdMainDlg)
//				{
//					TConferenceUserInfo* pUserInfo = ((CConferenceDlg*)m_pdMainDlg)->GetConferenceUserInfo(m_iSessionID);
//					if (pUserInfo)
//						((CConferenceDlg*)m_pdMainDlg)->SetUserCardInfo(pUserInfo, 1, m_iCardNo, 0);
//
//#ifdef _H323_GATEWAY_MARK_
//					// 关闭H323数据发送
//					CDataInfoManage* pH323Manage = ((CConferenceDlg*)m_pdMainDlg)->GetDataInfoManage();
//					if (NULL == pH323Manage)
//						return TRUE;
//
//					pH323Manage->CloseAudioChannel(m_dwH323ChannelNO, 0);	
//#endif
//				}
//			}	
//		}
//	}
//
//	//TRACE("CUserDlg::CloseSoundChannel() end\n");
//	return TRUE;
//}
//
//BOOL CUserDlg::CreateVideoChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID)	//建立视频通道
//{	
//	//TRACE("CUserDlg::CreateVideoChannel()\n");
//	if (!m_pVideoPlayer)
//		NewAVUserPlayer();
//
//	m_bHaveVideoData=FALSE;
//
//	{
//		//AVAutoLock l(&m_CritSecIAVVideoReceiver);
//		if (m_pAVVideoReceiver)
//		{
//			if (m_bLocalLoopBackTest)
//			{
//				m_pAVVideoReceiver->ReleaseConnections();
//				ReleaseVideoChannl(m_pAVVideoReceiver);
//				m_pAVVideoReceiver = NULL;
//			}
//			else
//			{
//				m_pAVVideoReceiver->ReleaseConnections();
//				delete m_pAVVideoReceiver;
//				m_pAVVideoReceiver=NULL;
//			}
//		}
//
//		m_IsReceivingVideo=true;
//		m_ulVideoReceiverChannelID=iChannelID;
//
//		//TRACE("CUserDlg::CreateVideoChannel() 1\n");
//		if (m_bLocalLoopBackTest)
//		{
//			m_pAVVideoReceiver = CreateVirtualVideoVideoReceiverChannl((IAVVideoReceiverNotify*)this, iChannelID);
//		}
//		else
//		{
//			if (GetRecordFlag())
//				m_pAVVideoReceiver=CreateAVVideoPlayer(*this,iChannelID);
//			else
//			{
//				if ((m_pdMainDlg)&&(!((CConferenceDlg*)m_pdMainDlg)->GetVideoTCPorUDP()))
//					m_pAVVideoReceiver=CreateIAVVideoReceiverUDP(*this,iChannelID);
//				else
//					m_pAVVideoReceiver=CreateIAVVideoReceiverTCP(*this,iChannelID);
//			}
//		}
//		
//		//TRACE("CUserDlg::CreateVideoChannel() 2\n");
//
//		if (m_nTimerCheckVideoDisconnected==0)
//		{
//			m_nTimerCheckVideoDisconnected=1002;
//			SetTimer(m_nTimerCheckVideoDisconnected,1000,NULL);
//		}
//
//		if (m_pVideoPlayer)
//		{
//			CRect rc;
//			GetClientRect(&rc);
//			video_size.width  = 320;//rc.Width();
//			video_size.height = 240;//rc.Height();
//
//			m_pVideoPlayer->OpenVideoDisplay(VIDEO_DIS_TYPE_H264RAW, video_size);
//			m_pVideoPlayer->ShowWindow(FALSE);
//			m_pVideoPlayer->StartVideoDisplay();
//
//			//FormateTitlebar();
//			//打开标题栏
//			ShowTitleBar(TRUE);
//
//			ResizeControls();
//		}
//
//		m_bOpenVideo=true;
//
//#ifdef _H323_GATEWAY_MARK_
//		// 创建H323数据发送
//		if (m_pdMainDlg)
//		{
//			CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//
//			TConferenceUserInfo* pUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//			if (pUserInfo)
//			{
//				CDataInfoManage* pH323Manage = pdMainDlg->GetDataInfoManage();
//				if (NULL == pH323Manage)
//					return TRUE;
//
//				pdMainDlg->SetH323VideoAplayWnd(this);
//				CString strName;
//				if (m_iCardNo == SCREEN_IS_VIDEO_NO)
//				 	strName.Format(_T("%s %s"), m_strUserName, _T("屏幕"));
//				else if (m_iCardNo == MEDIA_IS_VIDEO_NO)
//					strName.Format(_T("%s %s"), m_strUserName, _T("媒体"));
//				else
//					strName.Format(_T("%s %d"), m_strUserName, m_iCardNo);
//
//				USES_CONVERSION;
//				pH323Manage->CreateVideoChannel(1, W2A(strName), 0, m_dwH323ChannelNO, 0);
//			}
//		}
//#endif
//		return TRUE;
//	}
//}
//
//BOOL CUserDlg::CloseVideoChannel()	//关闭视频通道
//{
//	//TRACE("CUserDlg::CloseVideoChannel()\n");
//	m_bOpenVideo=false;
//
//	m_IsReceivingVideo=false;
//	m_ulVideoReceiverChannelID=0;
//	if (m_nTimerCheckVideoDisconnected)
//	{
//		KillTimer(m_nTimerCheckVideoDisconnected);
//		m_nTimerCheckVideoDisconnected=0;
//	}
//
//	if (m_pVideoPlayer)
//	{
//		if (!(m_pVideoPlayer->IsStopVideoDisplay()))
//			m_pVideoPlayer->StopVideoDisplay();
//	}
//
//	TRACE(_T("CUserDlg::CloseVideoChannel(), DestroyAVUserPlayer \r\n"));
//	if (!IsHaveSound())	//deleted by tiger,2008.10.08
//		DestroyAVUserPlayer();
//
//	{
//		AutoLockResource AutoLock;
//		//AVAutoLock l(&m_CritSecIAVVideoReceiver);
//		if (m_pAVVideoReceiver && (!m_bLocalLoopBackTest))
//		{
//			TRACE(_T("CUserDlg::CloseVideoChannel(), m_pAVVideoReceiver->EnableReceive(%d) \r\n"), m_IsReceivingVideo);
//			m_pAVVideoReceiver->EnableReceive(m_IsReceivingVideo);
//		}
//
//		if (m_pAVVideoReceiver)
//		{
//			if (m_bLocalLoopBackTest)
//			{
//				ReleaseVideoChannl(m_pAVVideoReceiver);
//				m_pAVVideoReceiver = NULL;
//			}
//			else
//			{
//				TRACE(_T("CUserDlg::CloseVideoChannel(), m_pAVVideoReceiver->ReleaseConnections() \r\n"));
//				//WriteErrorLogString(_T("CUserDlg"),_T("CloseVideoChannel"),_T("ReleaseConnections begin"));
//				////////////////////////////////////////////////////////////////////////////////////////////
//				//作个记号，有的时候程序退不出来，就是因为这个函数挂起了	//add by tiger,2009.09.25
//				m_pAVVideoReceiver->ReleaseConnections();
//				TRACE(_T("CUserDlg::CloseVideoChannel(), delete m_pAVVideoReceiver \r\n"));
//				delete m_pAVVideoReceiver;
//				m_pAVVideoReceiver=NULL;
//				//WriteErrorLogString(_T("CUserDlg"),_T("CloseVideoChannel"),_T("ReleaseConnections end"));
//
//				if (m_pdMainDlg)
//				{
//					TConferenceUserInfo* pUserInfo = ((CConferenceDlg*)m_pdMainDlg)->GetConferenceUserInfo(m_iSessionID);
//					if (pUserInfo)
//						((CConferenceDlg*)m_pdMainDlg)->SetUserCardInfo(pUserInfo, 1, m_iCardNo, 0);
//
//#ifdef _H323_GATEWAY_MARK_
//					// 关闭H323数据发送
//					CDataInfoManage* pH323Manage = ((CConferenceDlg*)m_pdMainDlg)->GetDataInfoManage();
//					if (NULL == pH323Manage)
//						return TRUE;
//
//					pH323Manage->CloseVideoChannel(m_dwH323ChannelNO, 0);
//#endif
//				}
//			}
//		}
//	}
//
//	m_bHaveVideoData=FALSE;
//
//	//TRACE("CUserDlg::CloseVideoChannel() end\r\n");
//	return TRUE;
//}
//
//void CUserDlg::DestroyAVUserPlayer()	//释放AVUserPlayer
//{
//	//TRACE("CUserDlg::DestroyAVUserPlayer()\n");
//	if (m_pVideoPlayer)
//	{
//		//TRACE("CUserDlg::DestroyAVUserPlayer() CloseVideoDisplay\n");
//		m_pVideoPlayer->CloseVideoDisplay();
//		//TRACE("CUserDlg::DestroyAVUserPlayer() delete m_pVideoPlayer\n");
//		delete m_pVideoPlayer;
//		//TRACE("CUserDlg::DestroyAVUserPlayer() delete m_pVideoPlayer end\n");
//		m_pVideoPlayer=NULL;
//	}
//
//	m_strUserName="";
//	m_iSessionID=0;
//	m_iCardNo=255;
//	m_iFrameInfoType=ntFrameNull;
//
//	//TRACE("CUserDlg::DestroyAVUserPlayer() end\r\n");
//}
//
//void CUserDlg::NewAVUserPlayer()
//{
//	// AutoLockResource Lock;
//
//	//TRACE("CUserDlg::NewAVUserPlayer()\r\n");
//	if (m_pVideoPlayer==NULL && GetSafeHwnd())
//	{
//        m_pVideoPlayer=IOCreateVideoDis(this, this);
//
//		if (m_bSynchronization && m_pVideoPlayer)
//		{
//			m_pVideoPlayer->EnableSyn(m_bSynchronization);	
//			//add by tiger,2008.09.28
//			if (m_pdMainDlg)
//			{
//				m_pVideoPlayer->SetTitleFont(((CConferenceDlg*)m_pdMainDlg)->GetBigTitleLogfont(),
//					((CConferenceDlg*)m_pdMainDlg)->GetBigTitleTextColor(),
//					((CConferenceDlg*)m_pdMainDlg)->GetBigTitleBkColor());
//			}			
//			//end add
//		}
//	}
//
//	if (!m_pVideoPlayer)
//	{
//		TRACE(_T("NewAVUserPlayer:播放创建失败！\r\n"));
//	}else
//	{
//		TRACE(_T("NewAVUserPlayer:播放创建成功！\r\n"));
//	}
//	//TRACE("CUserDlg::NewAVUserPlayer() end\n");
//}
//
//void CUserDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialog::OnSize(nType, cx, cy);
//	ResizeControls();
//
//	if(GetSafeHwnd())
//	{
//		Invalidate();
//	}
//}
//
//void CUserDlg::OnContextMenu(CWnd* pWnd, CPoint pt)
//{
//	if (m_bLocalLoopBackTest)
//		return;
//
//	CConferenceDlg *pDlgConferenceDlg = (CConferenceDlg *)m_pdMainDlg;
//	ASSERT(pDlgConferenceDlg);
//	if (NULL == pDlgConferenceDlg)
//		return;
//
//	TLocalUserInfo *pLocalUserInfo = pDlgConferenceDlg->GetLocalUserInfo();
//	ASSERT(pLocalUserInfo);
//	if (NULL == pLocalUserInfo)
//		return;
//
//	if ((NULL==m_pVideoPlayer)&&(NULL==m_pAudioPlay))
//    {
//		if (pLocalUserInfo->_iStatusFlag == ntConferenceUser)
//			return;
//
//		// 窗口视频格式
//		CMenu popMenu;
//		if (popMenu.CreatePopupMenu())
//		{
//			if (NULL == m_pConferenceWinDlg)
//				return;
//
//			TCHAR strText[255]=_T("");
//			project_language_loadstring(_T("MENU"), _T("MENU_VIDEO_FORMAT_SETTING"), strText, 255);
//			popMenu.AppendMenu(MF_STRING, IDM_USER_VIDEO_FORMAT_SETTING, strText);	// 启用窗口视频格式
//			project_language_loadstring(_T("MENU"), _T("MENU_WIN_VIDEO_FORMAT_SETTING"), strText, 255);
//			popMenu.AppendMenu(MF_STRING, IDM_WIN_VIDEO_FORMAT_SETTING, strText);	// 窗口视频格式设置
//
//			TPreSettingInfo* ptPreSettingInfo =  ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetWinPreSettingInfo(this);
//			if (ptPreSettingInfo)
//			{
//				popMenu.CheckMenuItem(IDM_USER_VIDEO_FORMAT_SETTING, ptPreSettingInfo->_bUseFlag ? MF_CHECKED : MF_UNCHECKED);
//			}
//
//			CPoint pp;
//			::GetCursorPos(&pp);
//
//			int nSelected = popMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD, pp.x, pp.y, this, NULL);	
//			popMenu.DestroyMenu();
//
//			::PostMessage(this->m_hWnd, WM_COMMAND, WPARAM(nSelected), 0);
//		}
//
//        return ;
//    }
//	BOOL	bControl=GetKeyState(VK_CONTROL) & 0x80;
//	//当是屏幕共享,且正在控制别人,且没有按control键时不显示菜单
//	if (m_iCardNo == SCREEN_IS_VIDEO_NO && m_bControl && !bControl)
//	{
//		return;
//	}
//    //
//    //根据不同的身份, 显示不同的功能菜单
//    //
//
//    CMenu popMenu;
//    if (!popMenu.CreatePopupMenu())
//    {
//        return ;
//    }
//
//	if ((pLocalUserInfo->_iStatusFlag==ntConferenceUser)&&(pDlgConferenceDlg->IsSpeak()))
//		ContextMenu_PrdsideLogin(popMenu);
//	else
//	{
//		switch(pLocalUserInfo->_iStatusFlag)
//		{
//		case ntPresideLogin :  ContextMenu_PrdsideLogin(popMenu);        break;
//		case ntConferenceUser: ContextMenu_ConferenceUser(popMenu);      break;
//		case ntWatchUser: 
//			ASSERT(pLocalUserInfo->_pConferenceInfo);
//			ContextMenu_WatchUser(popMenu, pLocalUserInfo->_pConferenceInfo->_bWatchUserControl);  
//			break;
//		case ntIM: ContextMenu_IMUser(popMenu);      break;
//		}
//	}
//
//    //如果是屏幕共享
//    if (m_iCardNo == SCREEN_IS_VIDEO_NO)
//    {
//        popMenu.RemoveMenu(IDM_STATUS_BAR, MF_BYCOMMAND);
//        popMenu.RemoveMenu(IDM_PRESET_POINT, MF_BYCOMMAND);
//    }
//
//
//    CPoint pp;
//    ::GetCursorPos(&pp);
//
//    //popMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pp.x, pp.y, this);
//    //popMenu.DestroyMenu();
//
//	int nSelected =popMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD, 
//		pp.x, pp.y, this, NULL);	
//
//	popMenu.DestroyMenu();
//
//	::PostMessage(this->m_hWnd, WM_COMMAND, WPARAM(nSelected), 0);
//}
//
//void CUserDlg::OnRecord()
//{
//	if (GetRecordFlag())
//		return;
//	if(m_pAVCRecordFactory)
//		StopRecord();
//	else
//		StartRecord();
//}
//
//void CUserDlg::OnBroadCaseVideo()
//{
//	((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastVideo(m_iSessionID,m_iCardNo);
//}
//
//void CUserDlg::OnAVWizard()
//{
//	/*if (GetRecordFlag())
//		return;
//
//	if (!m_pdMainDlg)
//		return;
//
//	if (m_pdWizardDlg)
//	{
//		m_pdWizardDlg->DestroyWindow();
//		delete m_pdWizardDlg;
//		m_pdWizardDlg=NULL;
//	}
//
//    if (!m_pdWizardDlg)
//    {
//        //m_pdWizardDlg=new CDlgRemoteAVWizard(this);
//        //m_pdWizardDlg->SetCardNo( m_iCardNo );
//        //m_pdWizardDlg->Create(CDlgRemoteAVWizard::IDD, this);
//    }
//
//    m_bIsAvAdjust = true;
//
//    //
//	CConferenceDlg *pDlgConferenceDlg = (CConferenceDlg *)m_pdMainDlg;
//	TConferenceUserInfo *pConferenceUserInfo = pDlgConferenceDlg->GetConferenceUserInfo(m_iSessionID);
//    m_pdWizardDlg->SetCardNo( m_iCardNo );
//    m_pdWizardDlg->SetUserInfo( pConferenceUserInfo );
//	m_pdWizardDlg->InitDlgData();
//
//	//CRect rect;
//	//m_pdWizardDlg->GetWindowRect(&rect);
//	//CPoint		pp;
//	//::GetCursorPos(&pp);
//	//m_pdWizardDlg->SetWindowPos(NULL,pp.x,pp.y,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
//
//	//音视频调节 Add  Han Huajie    2008-3-14
//	CPoint		pp;
//	CRect		Wizardrc, rc;
//	m_pConferenceWinDlg->GetWindowRect(&rc);
//	m_pdWizardDlg->GetClientRect(&Wizardrc);
//	int nWizardWidth = Wizardrc.Width();
//	int nWizardHeigth = Wizardrc.Height();
//
//	::GetCursorPos(&pp);
//	if (pp.x + nWizardWidth >= rc.right && pp.y + nWizardHeigth >= rc.bottom)
//		m_pdWizardDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//	else
//	{
//		if (pp.x + nWizardWidth >= rc.right)
//			m_pdWizardDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, pp.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//		else
//		{
//			if (pp.y + nWizardHeigth >= rc.bottom)
//				m_pdWizardDlg->SetWindowPos(NULL, pp.x, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//			else
//				m_pdWizardDlg->SetWindowPos(NULL,pp.x,pp.y,0,0,SWP_SHOWWINDOW | SWP_NOSIZE);
//		}
//	}*/
//}
//
//void CUserDlg::CloseVidioSoundWizardDlg(BOOL bIsOK)			//打开视音频调节
//{
// /*   if (!m_pdWizardDlg)
//    {
//        return ;
//    }
//
//    if (bIsOK)
//    {
//		TVideoCardInfo *ptVideoCardInfo=NULL,*ptVideoCardInfo1=NULL;
//		CConferenceDlg *pDlgConferenceDlg = (CConferenceDlg *)m_pdMainDlg;
//		TConferenceUserInfo *pConferenceUserInfo = pDlgConferenceDlg->GetConferenceUserInfo(m_iSessionID);
//        CTVideoCardInfoArray aTempVideoCardInfoArray;
//		ptVideoCardInfo=m_pdWizardDlg->GetVideoCardSettingPtr();
//		if (ptVideoCardInfo)
//			aTempVideoCardInfoArray.Add(ptVideoCardInfo);
//
//		int iOldVideoDriverIndex=255;
//		if (m_pdWizardDlg)
//			iOldVideoDriverIndex=m_pdWizardDlg->GetOldVideoDriverIndex();
//		if (ptVideoCardInfo&&(iOldVideoDriverIndex!=255)&&(iOldVideoDriverIndex!=ptVideoCardInfo->_iVideoDriverIndex))
//			int i=0;for ( i=0;i<pConferenceUserInfo->_aVideoCardInfo.GetSize();i++)
//			{
//				ptVideoCardInfo1=pConferenceUserInfo->_aVideoCardInfo.GetAt(i);
//				if ((ptVideoCardInfo1!=ptVideoCardInfo)&&(ptVideoCardInfo->_iVideoDriverIndex==ptVideoCardInfo1->_iVideoDriverIndex))
//				{
//					ptVideoCardInfo1->_iVideoDriverIndex=iOldVideoDriverIndex;
//					aTempVideoCardInfoArray.Add(ptVideoCardInfo1);
//					break;
//				}
//			}
//
//        pDlgConferenceDlg->ChangUserMicVideoInfo(m_iSessionID, pConferenceUserInfo->_iSoundDriverIndex,
//            pConferenceUserInfo->_iUserMicType, &aTempVideoCardInfoArray);
//    }
//
//	if (m_pdWizardDlg->GetSafeHwnd())
//	{
//		m_pdWizardDlg->DestroyWindow();
//		delete m_pdWizardDlg;
//		m_pdWizardDlg=NULL;
//		//m_pdWizardDlg->ShowWindow(SW_HIDE);
//	}
//*/
//	m_bIsAvAdjust = false;
//}
//
//void CUserDlg::OnTitleBar()
//{
//    /*if (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd())
//    {
//        ShowTitleBar(!m_pDlgAVInfo->IsWindowVisible());
//        ResetWindowRgn();
//    }*/
//	if (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd())
//	{
//		ShowTitleBar(!m_pDlgAVInfo->IsWindowVisible());
//		if (((CConferenceDlg*)m_pdMainDlg)->GetINFOTrans() && m_pVideoPlayer)
//		{
//			m_pVideoPlayer->EnableTitle(m_pDlgAVInfo->IsWindowVisible());
//		}
////		FormateTitlebar();
//		ResetWindowRgn();
//	}
//}
//
//void CUserDlg::OnVideoControlBar()
//{
//	if (m_pDlgYT && m_pDlgYT->GetWnd() && m_pDlgYT->GetWnd()->GetSafeHwnd())
//	{
//		int nCmd = (m_pDlgYT->IsWindowVisible() ? SWP_HIDEWINDOW : SWP_SHOWWINDOW);
//		m_pDlgYT->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | nCmd);
//        ResetWindowRgn();
//	}
//}
//
//void CUserDlg::OnSetPrepoint()
//{
//    if (!m_pDlgPrepointSet)
//    {
//		// AutoLockResource Lock;
//
//        m_pDlgPrepointSet = new CPrePointSetDlg();
//
//        m_pDlgPrepointSet->SetLocation(CPrePointSetDlg::eRemote);
//        m_pDlgPrepointSet->SetEventNotifyHandle(this);
//        m_pDlgPrepointSet->Create(CPrePointSetDlg::IDD);
//    }
//    
//    m_pDlgPrepointSet->CenterWindow();
//    m_pDlgPrepointSet->ShowWindow(SW_SHOW);	
//
//	if (CheckAllControl())
//	{
//		((CConferenceDlg *)m_pdMainDlg)->GetPrePointName(m_iSessionID,m_iCardNo);
//	}	
//}
//void CUserDlg::ReSetListData(char * pData)
//{
//	if (m_pDlgPrepointSet)
//	{
//		m_pDlgPrepointSet->ReSetListData(pData , false);
//	}
//}
//
//void CUserDlg::OnCommand(LONG lngCommand)
//{
//	if (CheckAllControl())
//	{
//		((CConferenceDlg *)m_pdMainDlg)->SendControlCommand(m_iSessionID ,m_iCardNo, lngCommand);
//	}
//}
//
//void CUserDlg::OnSpeed(int nSpeed)
//{
//	if (CheckAllControl())
//	{
//		((CConferenceDlg *)m_pdMainDlg)->SendControlSpeed(m_iSessionID,m_iCardNo, nSpeed);
//	}
//}
//void CUserDlg::OnSetPrePointName(char *pData)
//{
//	if (CheckAllControl())
//	{
//		((CConferenceDlg *)m_pdMainDlg)->SendPrePointName(m_iSessionID,pData);
//	}
//}
//
//void CUserDlg::OnIAVVideoReceiverNotifyReceivedVideoFrame(const char*pData,int nLen)
//{
//	try
//	{
//		////TRACE("CUserDlg::OnIAVVideoReceiverNotifyReceivedVideoFrame()\n");
//		m_bHaveVideoData=TRUE;
//
//		{
//			//AVAutoLock l(&m_CritSecIAVVideoReceiver);
//			if(m_pVideoPlayer)
//			{
//				if (!(m_pVideoPlayer->IsStopVideoDisplay()))
//				{
//#ifndef _H323_GATEWAY_MARK_
//					if (!m_pVideoPlayer->IsWindowVisible())
//						m_pVideoPlayer->ShowWindow(TRUE);
//#endif
//
//					{
//						//if (VIDEO_HEADER_EXT_GET_KEYFRAME((unsigned char*)pData))
//						//	m_bHaveVideoData=TRUE;
//						m_pVideoPlayer->SetVideoPacket((unsigned char*)pData,nLen);
//					}
//				}
//
//			}
//		}
//
//
//		{
//			if (m_pAVCRecordFactory)
//			{
//				AVAutoLock lll(&m_CritSecRecordVideo);
//				bool bKeyFrame=VIDEO_HEADER_EXT_GET_KEYFRAME((unsigned char*)pData);
//				if(m_bIsFirstFrame && !bKeyFrame)
//					return;
//				m_bIsFirstFrame = FALSE;
//				if(m_pAVCRecordVideoStream)
//					m_pAVCRecordVideoStream->WriteData((char*)pData, nLen, bKeyFrame);
//			}
//		}
//
//		{
//			AVAutoLock llll(&m_CritSecConferenceRecordVideo);
//			bool bKeyFrame=VIDEO_HEADER_EXT_GET_KEYFRAME((unsigned char*)pData);
//			if(m_bIsConferenceFirstFrame && !bKeyFrame)
//				return;
//			m_bIsConferenceFirstFrame = FALSE;
//			if(m_pConferenceRecordVideoStream)
//				m_pConferenceRecordVideoStream->WriteData((char*)pData, nLen, bKeyFrame);
//		}
//
//		////TRACE("CUserDlg::OnIAVVideoReceiverNotifyReceivedVideoFrame() end\n");
//	}
//	catch (CException* e)
//	{
//		
//	}
//
//}
//
//void CUserDlg::OnIAVVideoReceiverNotifyConnected(/*unsigned long ulIP*/)
//{
//	PostMessage(UM_AV_RECEIVE_NOTIFY,HP_VIDEO_RECEIVE_CONNECTED,0);
//}
//
//void CUserDlg::OnIAVAudioReceiverNotifyReceivedAudioFrame(const char*pData,int nLen)
//{
//	try
//	{
//		m_ulAudioBitrateSum+=nLen;
//		////TRACE("CUserDlg::OnIAVAudioReceiverNotifyReceivedAudioFrame()\n");
//
//		m_bHaveAudioData=TRUE;
//
//		if(m_pAudioPlay)
//		{
//			{
//#ifdef _H323_GATEWAY_MARK_
//				m_pAudioPlay->SetAudioPacket((unsigned char*)pData,nLen,FALSE);
//#else
//				//			AVAutoLock l(&m_CritSecIAVAudioReceiver);
//				m_pAudioPlay->SetAudioPacket((unsigned char*)pData,nLen);
//				//TRACE(_T("CUserDlg::SetAudioPacket nPacketLen:%d\n"), nLen);
//#endif
//			}
//
//			{
//				if (m_pAVCRecordFactory)
//				{
//					AVAutoLock ll(&m_CritSecRecordAudio);
//					if(m_pAVCRecordAudioStream)
//						m_pAVCRecordAudioStream->WriteData((char*)pData, nLen, false);
//				}
//			}
//
//			{
//				AVAutoLock lll(&m_CritSecConferenceRecordAudio);
//				if(m_pConferenceRecordAudioStream)
//					m_pConferenceRecordAudioStream->WriteData((char*)pData, nLen, false);
//			}
//		}
//
//		////TRACE("CUserDlg::OnIAVAudioReceiverNotifyReceivedAudioFrame() end\n");
//	}
//	catch (CException* e)
//	{
//		
//	}
//}
//
//void CUserDlg::OnIAVAudioReceiverNotifyConnected(/*unsigned long ulIP*/)
//{
//	PostMessage(UM_AV_RECEIVE_NOTIFY,HP_AUDIOO_RECEIVE_CONNECTED,0);
//}
//
//void CUserDlg::OpenFloatWindow(BOOL bIsDoubleScreen, unsigned int ulSrcSessionID)
//{
//    //if (GetFloatWnd() == this)  //已浮动
//    //{
//    //    return ;
//    //}
//
//    //
//    //双屏, 在屏幕上显示一个虚框
//    //单屏, 在指定的区域浮动显示视频
//    //
//
//    int wsStyle = (bIsDoubleScreen ? CDlgFloatWin::wsBorder : CDlgFloatWin::wsVideo);
//    GetFloatWin()->OpenFloat(this, wsStyle, 3);
//
//	ASSERT(m_pdMainDlg);
//	if (NULL == m_pdMainDlg)
//		return;
//
//    //权限
//    TLocalUserInfo *pUser = ((CConferenceDlg *)m_pdMainDlg)->GetLocalUserInfo();
//    if (pUser)
//    {
//        if (ntPresideLogin == pUser->_iStatusFlag)
//        {
//            GetFloatWin()->ShowCloseButton(true);
//            GetFloatWin()->EnableResize(true);
//        }
//        else
//        {
//            GetFloatWin()->ShowCloseButton(false);
//            GetFloatWin()->EnableResize(false);
//        }
//    }
//}
//
//void CUserDlg::FloatWindowTo(const CRect &rect, BOOL bIsDoubleScreen)
//{
//    ASSERT( GetFloatWin() );
//    GetFloatWin()->SetWindowPos(rect.left, rect.top, rect.Width(), rect.Height());
//}
//
//void CUserDlg::CloseFloatWindow( BOOL bIsDoubleScreen )	//恢复位置
//{
//    ASSERT( GetFloatWin() );
//    GetFloatWin()->CloseFloat();
//}
//
//void CUserDlg::OnBroadcastSound()
//{
//	((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastSound(m_iSessionID,m_iCardNo);
//}
//
//void CUserDlg::OnBroadcastAVdieo()
//{
//	ASSERT(m_pConferenceWinDlg);
//	if (NULL == m_pConferenceWinDlg)
//		return;
//
//	TConferenceUserInfo *pUserInfo = ((CConferenceDlg *)m_pdMainDlg)->GetConferenceUserInfo(m_iSessionID);
//	ASSERT(pUserInfo);
//	if (NULL == pUserInfo)
//		return;
//
//	if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndSound(m_iIndex-1) &&
//		((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1))
//	{
//		if (pUserInfo->_aSoundDriverInfo.GetSize() > 0)
//			((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastSound(m_iSessionID,m_iCardNo);
//		
//		if (pUserInfo->_aVideoDriverInfo.GetSize() > 0)
//			((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastVideo(m_iSessionID,m_iCardNo);
//
//		return;
//	}
//
//	if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1))
//	{
//		if (pUserInfo->_aSoundDriverInfo.GetSize() > 0)
//			((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastSound(m_iSessionID,m_iCardNo);
//		
//		return;
//	}
//
//	if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndSound(m_iIndex-1))
//	{
//		if (pUserInfo->_aVideoDriverInfo.GetSize() > 0)
//			((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastVideo(m_iSessionID,m_iCardNo);
//	}
//
//	if (pUserInfo->_aSoundDriverInfo.GetSize() > 0)
//		((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastSound(m_iSessionID,m_iCardNo);
//
//	if (pUserInfo->_aVideoDriverInfo.GetSize() > 0)
//		((CConferenceDlg*)m_pdMainDlg)->ButtonBroadcastVideo(m_iSessionID,m_iCardNo);
//}
//
//void CUserDlg::OnWacthAVdieo()
//{
//	if (IsHaveVideo() && IsHaveSound())
//	{
//		((CConferenceDlg*)m_pdMainDlg)->ButtonInceptSound(m_iSessionID,m_iCardNo);
//		((CConferenceDlg*)m_pdMainDlg)->ButtonInceptVideo(m_iSessionID,m_iCardNo);
//	}
//	else 
//	{
//		if (IsHaveVideo())
//		{
//			((CConferenceDlg*)m_pdMainDlg)->ButtonInceptSound(m_iSessionID,m_iCardNo);
//		}
//		else if (IsHaveSound())
//		{
//			((CConferenceDlg*)m_pdMainDlg)->ButtonInceptVideo(m_iSessionID,m_iCardNo);
//		}
//	}
//}
//
//void CUserDlg::OnInceptVideo()
//{
//	((CConferenceDlg*)m_pdMainDlg)->ButtonInceptVideo(m_iSessionID,m_iCardNo);
//}
//
//void CUserDlg::OnInceptSound()
//{
//	((CConferenceDlg*)m_pdMainDlg)->ButtonInceptSound(m_iSessionID,m_iCardNo);
//}
//
//void CUserDlg::OnScreenControl()
//{	
//	((CConferenceDlg*)m_pdMainDlg)->SendInternetCommand(GetSessionID(), "ScreenControl", 13);
//}
//
//void CUserDlg::OnScreenCancelControl()
//{
//	m_bControl = FALSE;
//	((CConferenceDlg*)m_pdMainDlg)->SendInternetCommand(GetSessionID(), " ", 19);
//}
//
//void CUserDlg::OnRemoteSetting()
//{
//	char buffer[13];
//	buffer[12] = m_iCardNo;
//	char *p = "AskParameter";
//	memcpy(buffer, p, 12);
//	((CConferenceDlg*)m_pdMainDlg)->SendInternetCommand(GetSessionID(), buffer, 13);
//}
//
//void CUserDlg::OnAudioSetting()
//{
//	// AutoLockResource Lock;
//
//	CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//	if (NULL == pdMainDlg)
//		return;
//
//	TConferenceUserInfo *pConferenceUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//	if (NULL == pConferenceUserInfo)
//		return;
//
//	if (NULL == m_pAudioPlay)
//		return;
//
//	if (m_pAudioSettingDlg)
//	{
//		if (m_pAudioSettingDlg->GetSafeHwnd())
//			m_pAudioSettingDlg->DestroyWindow();
//
//		delete m_pAudioSettingDlg;
//		m_pAudioSettingDlg = NULL;
//	}
//
//	if (NULL == m_pAudioSettingDlg)
//	{
//		m_pAudioSettingDlg = new CAudioSettingDlg(this);
//		m_pAudioSettingDlg->Create(CAudioSettingDlg::IDD, this);
//	}
//
//	if (m_pAudioSettingDlg && m_pAudioSettingDlg->GetSafeHwnd())
//	{
//		m_pAudioSettingDlg->SetRemoteFlage();
//		m_pAudioSettingDlg->SetConferenceUserInfo(pConferenceUserInfo, m_iCardNo, m_pAudioPlay->GetVolume());
//		m_pAudioSettingDlg->InitAudioDate();
//
//		CPoint		pp;
//		CRect		Wizardrc, rc;
//		m_pConferenceWinDlg->GetWindowRect(&rc);
//		m_pAudioSettingDlg->GetClientRect(&Wizardrc);
//		int nWizardWidth = Wizardrc.Width();
//		int nWizardHeigth = Wizardrc.Height();
//
//		::GetCursorPos(&pp);
//		if (pp.x + nWizardWidth >= rc.right && pp.y + nWizardHeigth >= rc.bottom)
//			m_pAudioSettingDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//		else
//		{
//			if (pp.x + nWizardWidth >= rc.right)
//				m_pAudioSettingDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, pp.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//			else
//			{
//				if (pp.y + nWizardHeigth >= rc.bottom)
//					m_pAudioSettingDlg->SetWindowPos(NULL, pp.x, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//				else
//					m_pAudioSettingDlg->SetWindowPos(NULL,pp.x,pp.y,0,0,SWP_SHOWWINDOW | SWP_NOSIZE);
//			}
//		}
//	}
//
//}
//
//void CUserDlg::OnVideoSetting()
//{
//	// AutoLockResource Lock;
//
//	CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//	if (NULL == pdMainDlg)
//		return;
//
//	TConferenceUserInfo *pConferenceUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//	if (NULL == pConferenceUserInfo)
//		return;
//
//	if (m_pVideoSettingDlg)
//	{
//		if (m_pVideoSettingDlg->GetSafeHwnd())
//			m_pVideoSettingDlg->DestroyWindow();
//
//		delete m_pVideoSettingDlg;
//		m_pVideoSettingDlg = NULL;
//	}
//
//	if (NULL == m_pVideoSettingDlg)
//	{
//		m_pVideoSettingDlg = new CVideoSettingDlg(this);
//		m_pVideoSettingDlg->Create(CVideoSettingDlg::IDD, this);
//	}
//
//	if (m_pVideoSettingDlg && m_pVideoSettingDlg->GetSafeHwnd())
//	{
//		m_pVideoSettingDlg->SetConferenceUserInfo(pConferenceUserInfo, m_iCardNo);
//
//		CPoint		pp;
//		CRect		Wizardrc, rc;
//		m_pConferenceWinDlg->GetWindowRect(&rc);
//		m_pVideoSettingDlg->GetClientRect(&Wizardrc);
//		int nWizardWidth = Wizardrc.Width();
//		int nWizardHeigth = Wizardrc.Height();
//
//		::GetCursorPos(&pp);
//		if (pp.x + nWizardWidth >= rc.right && pp.y + nWizardHeigth >= rc.bottom)
//			m_pVideoSettingDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//		else
//		{
//			if (pp.x + nWizardWidth >= rc.right)
//				m_pVideoSettingDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, pp.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//			else
//			{
//				if (pp.y + nWizardHeigth >= rc.bottom)
//					m_pVideoSettingDlg->SetWindowPos(NULL, pp.x, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//				else
//					m_pVideoSettingDlg->SetWindowPos(NULL,pp.x,pp.y,0,0,SWP_SHOWWINDOW | SWP_NOSIZE);
//			}
//		}
//	}
//}
//
//void CUserDlg::ShowRemoteCtrlSetting(ComParameter ComPar)
//{
//	if (!m_pDlgCtrlRemoteSetting)
//	{
//		// AutoLockResource Lock;
//
//		m_pDlgCtrlRemoteSetting = new CDlgCtrlRemoteSetting(m_pdMainDlg, this);
//		m_pDlgCtrlRemoteSetting->Create(m_pDlgCtrlRemoteSetting->IDD,this);
//	}
//	m_pDlgCtrlRemoteSetting->SetParameter(ComPar);
//}
//
//void CUserDlg::OnTimer(UINT nIDEvent)
//{
//    if (m_hTitleDlgTimer == nIDEvent)
//    {
//        FormateTitlebar();		
//
//        ResizeControls();
//		return;
//    }
//	if (m_pAudioPlay && nIDEvent == m_iAudioLevelTitleTimer)
//	{
//		OnIHPAVPlayerNotifyAudioLevel(m_pAudioPlay->GetOutVolume());
//		return;
//	}
//	if (m_nTimerCheckAudioDisconnected==nIDEvent)
//	{
//		GetAudioBitrate();
//		BOOL bDisconnected=FALSE;
//		{
//			//AVAutoLock l(&m_CritSecIAVAudioReceiver);
//			if (m_pAVAudioReceiver)
//			{
//				if (!m_bHaveAudioData)
//					m_pAVAudioReceiver->EnableReceive(TRUE);
//
//				bDisconnected=m_pAVAudioReceiver->IsDisconnected();
//				//CString strTemp;
//				//strTemp.Format(_T("%d"),bDisconnected);
//				////WriteErrorLogString(m_strUserName,_T("CUserDlg::OnTimer IsDisconnected"),strTemp);
//			}
//			else
//			{
//				bDisconnected=TRUE;
//			}
//		}
//		if (bDisconnected)
//		{
//			//WriteErrorLogString(m_strUserName,_T("CUserDlg::OnTimer"),_T("Reconnecte"));
//			CreateSoundChannel(m_ulAudioReceiverChannelID);
//		}
//		return;
//	}
//	if (m_nTimerCheckVideoDisconnected==nIDEvent)
//	{
//		BOOL bDisconnected=FALSE;
//		{
//			//AVAutoLock l(&m_CritSecIAVVideoReceiver);
//			if (m_pAVVideoReceiver)
//			{
//				if (!m_bHaveVideoData)
//					m_pAVVideoReceiver->EnableReceive(TRUE);
//				bDisconnected=m_pAVVideoReceiver->IsDisconnected();
//			}
//			else
//			{
//				bDisconnected=TRUE;
//			}
//		}
//		if (bDisconnected)
//		{
//			CreateVideoChannel(m_ulVideoReceiverChannelID);
//		}
//
//		if (m_bWatch)
//		{
//			m_pVideoPlayer->ShowWindow(FALSE);			
//		}
//		return;
//	}
//
//    //语音激励
//    if (m_nVolumeTimer == nIDEvent && 
//        ((CConferenceDlg*)m_pdMainDlg)->IsVoiceInspirit())
//    {
//        if (m_nCurVolume)
//        {
//            m_ulVolumeTime += 50;       //时间片是 50ms
//        }
//        else
//        {
//			if (m_ulVolumeTime>0)
//				m_ulVolumeTime-=50;
//        }
//
//        //换人 ?
//        if (m_bInVoiceInspirite && 
//            m_ulVolumeTime >= ((CConferenceDlg*)m_pdMainDlg)->GetSeparateVoiceInspiritTime()*1000)
//        {
//            m_bInVoiceInspirite = false;
//            m_ulVolumeTime = 0;
//        }
//
//        //激励
//        if (!m_bInVoiceInspirite &&
//            m_ulVolumeTime > ((CConferenceDlg*)m_pdMainDlg)->GetDecideVoiceInspiritTime() * 1000)  
//        {
//            m_bInVoiceInspirite = true;
//            ASSERT(m_pConferenceWinDlg);
//
//            //得到大窗口号
//            int iBigWndArray[3] = {-1, -1, -1};
//            ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetBigWindows(iBigWndArray);
//            if (iBigWndArray[0] == -1)  //没有大窗口
//            {
//                m_ulVolumeTime = 0;
//                return ;
//            }
//
//            //优先使用空闲窗口
//            int nFrameNo = -1;
//            TWinInfo *pWinInfo = NULL;
//            int i=0;for ( i=0;i<3;i++)
//            {
//                if (iBigWndArray[i] < 1)    //GetBigWindows取到的窗口序号从1开始
//                {
//                    continue;
//                }
//
//                pWinInfo = ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetWinInfoArray()->GetAt(iBigWndArray[i]-1);
//				if (m_iIndex==iBigWndArray[i])
//					return;
//                if (pWinInfo && pWinInfo->_iFrameInfoType==ntFrameNull)
//                {
//                    nFrameNo = iBigWndArray[i]-1;
//                    break;
//                }
//            }
//
//            //没有空闲窗口则使用第1个
//            nFrameNo = (nFrameNo==-1) ? iBigWndArray[0]-1 : nFrameNo;
//
//            //交换窗口, 参考: GetMaxWndIndex
//            if (GetIndex() != nFrameNo)
//            {
//                ((CConferenceWinDlg*)m_pConferenceWinDlg)->SwapWhoToWndPosition(GetIndex(), 
//                    ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetFrameIndex(), nFrameNo);
//            }
//        }
//		return;
//    }
//}
//
//void CUserDlg::Do_LButtonDbClick(UINT nFlags, CPoint point) // 最大化/恢复视频显示窗口
//{
//	if (!m_iZoomIn)
//	{
//		OnFullScreen();
//	}
//	CBaseDlg::Do_LButtonDbClick(nFlags, point);
//}
//
//void CUserDlg::SetWatch()			//设监控
//{
//	CBaseDlg::SetWatch();
//
//	m_pVideoPlayer->ShowWindow(FALSE);
//	//m_pVideoPlayer->Mute(true);
//	m_pAudioPlay->SetVolume(0);
//}
//
//void CUserDlg::CloseWatch()			//关闭监控
//{
//	CBaseDlg::CloseWatch();
//
//	m_pVideoPlayer->ShowWindow(TRUE);
//}
//
//// 开始录制
//BOOL CUserDlg::StartRecord()
//{
//	StopRecord();
//
//	CString	Filter = _T("RCS Files (*.rcs)|*.rcs||");
//
//	CFileDialog dlgFile(FALSE, _T("rcs"), NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,Filter,this);
//
//	//////////////////////////////////////////////////////////////////////////
//
//	if (GetXPE())		// Modi Han Huajie 2007/11/17
//	{
//		dlgFile.m_ofn.lpstrInitialDir = _T("D:\\");
//	}
//	try
//	{
//		if (dlgFile.DoModal() != IDOK)
//		{
//			return FALSE;
//		}
//		if (m_bCloseDlgFileFlag)
//			return FALSE;
//	}
//	catch (CException* e)
//	{
//		return FALSE;
//	}
//
//	if ((NULL==m_pVideoPlayer)&&(NULL==m_pAudioPlay))
//		return FALSE;
//
//	m_strRecordPathName=dlgFile.GetPathName();
//
//	if (GetXPE())		// Modi Han Huajie 2007/11/17
//	{
//		if (m_strRecordPathName.GetAt(0) == 'C')
//		{
//			TCHAR strText[256], strTilte[256];
//			project_language_loadstring(_T("MESSAGE_BOX"), _T("MESSAGE_BOX_TITLE"), strTilte, 255);
//			project_language_loadstring(_T("MESSAGE_BOX"), _T("MESSAGE_BOX_NOT_SAVE_MIDIA"), strText, 255);
//
//			if (MessageBox(strText, strTilte, MB_YESNO | MB_ICONEXCLAMATION ) == IDYES)
//			{
//				dlgFile.DestroyWindow();
//				m_strRecordPathName = _T("");
//				StartRecord();
//				return FALSE;
//			}
//			else
//			{
//				return FALSE;
//			}
//		}
//	}
//
//	return DoStartRecord(m_strRecordPathName);
//}
//
//BOOL CUserDlg::DoStartRecord(CString strRecordPathName)		// 执行开始录像
//{
//	USES_CONVERSION;
//
//	if(m_pAVCRecordFactory){
//		m_pAVCRecordFactory->ReleaseConnections();
//		m_pAVCRecordFactory = NULL;
//	}
//
//	if(!CreateAVCRecordFactory(&m_pAVCRecordFactory,this))
//		return FALSE;
//
//	AVC_FILE_HEADER afh;
//	memset(&afh,0,sizeof(afh));
//
//	if(!m_pAVCRecordFactory->Connect(CT2A(strRecordPathName), &afh)){
//		m_pAVCRecordFactory->ReleaseConnections();
//		m_pAVCRecordFactory = NULL;
//		return FALSE;
//	}
//
//	{
//		AVAutoLock l(&m_CritSecRecordVideo);
//		if(m_pAVCRecordFactory->CreateRecordSingleStream(AVC_FRAME_TYPE_VIDEO,m_iSessionID,m_iCardNo,(IAVCRecordSingleStream **)&m_pAVCRecordVideoStream))
//		{
//			m_bIsFirstFrame = TRUE;
//			{
//				//AVAutoLock ll(&m_CritSecIAVVideoReceiver);
//				if (m_pAVVideoReceiver)
//					m_pAVVideoReceiver->EnableReceive(TRUE);
//			}
//
//		}
//	}
//
//	{
//		AVAutoLock l(&m_CritSecRecordAudio);
//		m_pAVCRecordFactory->CreateRecordSingleStream(AVC_FRAME_TYPE_AUDIO,m_iSessionID,m_iCardNo,(IAVCRecordSingleStream **)&m_pAVCRecordAudioStream);
//	}
//
//	return TRUE;
//}
//
//// 停止录像
//void CUserDlg::StopRecord()
//{
//	{
//		AVAutoLock l(&m_CritSecRecordAudio);
//		if (m_pAVCRecordAudioStream)
//		{
//			m_pAVCRecordAudioStream->NotifyStreamClose();
//			m_pAVCRecordAudioStream = NULL;
//		}
//	}
//
//	{
//		AVAutoLock l(&m_CritSecRecordVideo);
//		if (m_pAVCRecordVideoStream)
//		{
//			m_pAVCRecordVideoStream->NotifyStreamClose();
//			m_pAVCRecordVideoStream = NULL;
//		}
//	}
//	if(m_pAVCRecordFactory)
//	{
//		m_pAVCRecordFactory->ReleaseConnections();
//		m_pAVCRecordFactory = NULL;
//	}
//}
//
//void CUserDlg::OnAVCRecordFactoryEvent_FullFile(void)
//{
//	PostMessage(UM_RECORD,RECORD_FULL,0);
//}
//
//LRESULT CUserDlg::OnRecordMessage(WPARAM wParam, LPARAM lParam)			//录像消息
//{
//	switch (wParam)
//	{
//	case RECORD_FULL:
//		if(m_pAVCRecordFactory)
//		{
//			StopRecord();
//			CString strRecordPathName;
//			CTime t = CTime::GetCurrentTime();
//			CString nowtime = t.Format("%Y_%m%d_%H%M%S");
//			CString strTemp;
//			strTemp=m_strRecordPathName;
//			strTemp.Replace(_T(".rcs"), _T("_"));
//			strRecordPathName=strTemp+nowtime+_T(".rcs");
//			DoStartRecord(strRecordPathName);
//		}
//		break;
//	}
//
//	return 0;
//}
//
//BOOL CUserDlg::StartConferenceRecord()		// 开始会议录像
//{
//	if (!m_pdMainDlg)
//		return FALSE;
//
//	IAVCRecordFactory*pIAVCRecordFactory=((CConferenceDlg *)m_pdMainDlg)->GetConferenceRecordFactory();
//
//	if (!pIAVCRecordFactory)
//		return FALSE;
//
//	{
//		AVAutoLock l(&m_CritSecConferenceRecordVideo);
//		if (m_pConferenceRecordVideoStream==NULL)
//		{
//			if(pIAVCRecordFactory->CreateRecordSingleStream(AVC_FRAME_TYPE_VIDEO,m_iSessionID,m_iCardNo,(IAVCRecordSingleStream **)&m_pConferenceRecordVideoStream))
//			{
//				m_bIsConferenceFirstFrame = TRUE;	
//				{
//					//AVAutoLock ll(&m_CritSecIAVVideoReceiver);
//					if (m_pAVVideoReceiver)
//						m_pAVVideoReceiver->EnableReceive(TRUE);
//				}
//
//			}	
//		}
//	}
//
//	{
//		AVAutoLock l(&m_CritSecConferenceRecordAudio);
//		if (m_pConferenceRecordAudioStream==NULL)
//			pIAVCRecordFactory->CreateRecordSingleStream(AVC_FRAME_TYPE_AUDIO,m_iSessionID,m_iCardNo,(IAVCRecordSingleStream **)&m_pConferenceRecordAudioStream);
//	}
//
//	return TRUE;
//}
//
//void CUserDlg::StopConferenceRecord()		// 停止会议录像
//{
//	{
//		AVAutoLock l(&m_CritSecConferenceRecordAudio);
//		if (m_pConferenceRecordAudioStream)
//		{
//			m_pConferenceRecordAudioStream->NotifyStreamClose();
//			m_pConferenceRecordAudioStream = NULL;
//		}
//	}
//
//	{
//		AVAutoLock l(&m_CritSecConferenceRecordVideo);
//		if (m_pConferenceRecordVideoStream)
//		{
//			m_pConferenceRecordVideoStream->NotifyStreamClose();
//			m_pConferenceRecordVideoStream = NULL;
//		}
//	}
//}
//
//bool CUserDlg::CheckAllControl()
//{
//    CConferenceDlg *pDlgConferenceDlg = (CConferenceDlg *)m_pdMainDlg;
//    ASSERT(pDlgConferenceDlg);
//    TLocalUserInfo *pLocalUserInfo = pDlgConferenceDlg->GetLocalUserInfo();
//    ASSERT(pLocalUserInfo);
//
//    bool bValue = false;
//    switch(pLocalUserInfo->_iStatusFlag)
//    {
//    case ntPresideLogin :       bValue = true;          //主持人恒有控制权限
//        break;
//    case ntConferenceUser:      bValue = (TRUE == pDlgConferenceDlg->GetAllowControl());   //与会者
//        break;
//    case ntWatchUser:   //监控人员
//        if (pLocalUserInfo->_pConferenceInfo)
//        {
//            bValue = pLocalUserInfo->_pConferenceInfo->_bWatchUserControl;
//        }
//        break;
//    }
//
//    return bValue;
//}
//
//void CUserDlg::ContextMenu_PrdsideLogin(CMenu &popMenu)
//{
//    UINT nStatus;
//    TCHAR strText[255]=_T("");
//
//	//得到会议人员信息;
//	ASSERT(m_pdMainDlg);
//	//TRACE("CUserDlg::ContextMenu_PrdsideLogin:%d",m_iSessionID);
//	TConferenceUserInfo *pUserInfo = ((CConferenceDlg *)m_pdMainDlg)->GetConferenceUserInfo(m_iSessionID);
//	//ASSERT(pUserInfo);
//	if (!pUserInfo)
//	{
//		return;
//	}
//
//	project_language_loadstring(_T("MENU"), _T("MENU_FULL_SCREENSHOW"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_FULL_SCREEN,strText);
//	if (GetFullScreenFlag())
//		popMenu.CheckMenuItem(IDM_FULL_SCREEN, MF_BYCOMMAND|MF_CHECKED);
//
//	project_language_loadstring(_T("MENU"), _T("MENU_SHOW_NAME"), strText, 255);	//会场名称
//	popMenu.AppendMenu(MF_STRING,IDM_TITLE_BAR,strText);
//	nStatus = (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd() && m_pDlgAVInfo->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//	popMenu.CheckMenuItem(IDM_TITLE_BAR, nStatus);
//
//	popMenu.AppendMenu(MF_SEPARATOR);
//
//	project_language_loadstring(_T("MENU"), _T("MENU_DETAILS_INF"), strText, 255);	// 详细信息
//	popMenu.AppendMenu(MF_STRING,IDM_DETAILINFO_SHOW,strText);
//	nStatus = (m_pDetailInfoDlg && m_pDetailInfoDlg->GetSafeHwnd() && m_pDetailInfoDlg->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//	popMenu.CheckMenuItem( IDM_DETAILINFO_SHOW, nStatus );
//
//	project_language_loadstring(_T("MENU"), _T("MENU_YUNTAI_CONTROL"), strText, 255);	// 云台控制
//	popMenu.AppendMenu(MF_STRING,IDM_STATUS_BAR,strText);
//	nStatus = (m_pDlgYT && m_pDlgYT->GetWnd() && m_pDlgYT->GetWnd()->GetSafeHwnd() 
//		&& m_pDlgYT->IsWindowVisible()? MF_CHECKED : MF_UNCHECKED);
//	popMenu.CheckMenuItem(IDM_STATUS_BAR, nStatus);
//
//	project_language_loadstring(_T("MENU"), _T("MENU_TO_JPG"), strText, 255);		// 拍照
//	popMenu.AppendMenu(MF_STRING,IDM_TO_JPG,strText);
//
//	project_language_loadstring(_T("MENU"), _T("MENU_AVIEDO_RECORD"), strText, 255);		// 录制
//	popMenu.AppendMenu(MF_STRING,IDM_RECORD,strText);
//	if (m_pAVCRecordFactory)
//		popMenu.CheckMenuItem(IDM_RECORD, MF_BYCOMMAND|MF_CHECKED);	
//
//	//add by tiger,2008.07.17
//	//放大
//	if (0==m_iZoomIn || 2==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_ZOOMIN"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}else if (1==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_REDUCE"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}
//	//还原
//	project_language_loadstring(_T("MENU"), _T("MENU_REVERT"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_REVERT,strText);
//	//end add
//	
//	if (m_iCardNo ==  SCREEN_IS_VIDEO_NO)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_FULLSCREEN_CAPTURE"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_FULL_SCREEN_CAPTURE, strText);	// 全屏采集屏幕
//		if (m_bFullScreenCpture)
//			popMenu.CheckMenuItem(IDM_FULL_SCREEN_CAPTURE, MF_BYCOMMAND|MF_CHECKED);
//	}
//
//	////////////////////////////////////////////////////////////////////////////////
//	// 视频显示模式菜单 Add Han Hua jie 2008/01/14
//	CMenu MenuVideoMode;
//	MenuVideoMode.CreateMenu();
//	project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_INCISE_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_SEEING_PROPORTION_INCISE_SHOW,strText);					// 视觉比例切割显示
//	project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_PADDED_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_SEEING_PROPORTION_PADDED_SHOW,strText);					// 视觉比例填补显示
//	project_language_loadstring(_T("MENU"), _T("MENU_FULL_PANORAMA_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_FULL_PANORAMA_SHOW,strText);								// 视频全景显示
//
//	MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_INCISE_SHOW, MF_UNCHECKED);
//	MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_PADDED_SHOW, MF_UNCHECKED);
//	MenuVideoMode.CheckMenuItem(IDM_FULL_PANORAMA_SHOW, MF_UNCHECKED);
//
//	switch(m_nVideoShowMode)
//	{
//	case ntVideoShowModeCut:
//		MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_INCISE_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_INCISE_SHOW"), strText, 255);
//		break;
//	case ntVideoShowModeFill:
//		MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_PADDED_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_PADDED_SHOW"), strText, 255);
//		break;
//	case ntVideoShowModeFull:
//		MenuVideoMode.CheckMenuItem(IDM_FULL_PANORAMA_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_FULL_PANORAMA_SHOW"), strText, 255);
//		break;
//	default:
//		break;
//	}
//
//	popMenu.AppendMenu(MF_POPUP,(UINT_PTR)MenuVideoMode.m_hMenu,strText);
//
//	////////////////////////////////////////////////////////////////////////////////
//
//	if (((CConferenceDlg*)m_pdMainDlg)->ConferenceSynchronization())
//	 popMenu.AppendMenu(MF_SEPARATOR);
//
//	if (m_iCardNo>H323_IS_VIDEO_NO)
//	{
//		if (GetFloatWnd() != this/* && m_iCardNo != 200*/)  //单屏主持人不能直接关闭浮动窗口
//		{
//			popMenu.AppendMenu(MF_SEPARATOR);
//
//			project_language_loadstring(_T("MENU"), _T("MENU_CLOSE_CONFERENCEHALL"), strText, 255);
//			popMenu.AppendMenu(MF_STRING,IDM_CLOSE_USER,strText);
//		}
//		return;
//	}
//
//	TLocalUserInfo *pLocalUserInfo = ((CConferenceDlg*)m_pdMainDlg)->GetLocalUserInfo();
//	ASSERT(pLocalUserInfo);
//	if (NULL == pLocalUserInfo)
//		return;
//
//	if (m_iCardNo != MEDIA_IS_VIDEO_NO && m_iCardNo !=  SCREEN_IS_VIDEO_NO)
//	{
//		if ((pUserInfo->_aSoundDriverInfo.GetSize()) > 0 && (pUserInfo->_aVideoDriverInfo.GetSize() > 0) && 
//			(pLocalUserInfo->_pPresideUserInfo && pLocalUserInfo->_pPresideUserInfo->_bVASynchronizationFlag))
//		{
//			project_language_loadstring(_T("DIALOG"), _T("BROADCAST_CONFERENCE_HALL"), strText, 255);
//			popMenu.AppendMenu(MF_STRING,IDM_BROADCAST_AVDIEO,strText);
//
//			if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndSound(m_iIndex-1) &&
//				((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1))
//			{
//				popMenu.CheckMenuItem(IDM_BROADCAST_AVDIEO, MF_BYCOMMAND|MF_CHECKED);
//			}
//		}
//	}
//
//	//
//	//检查系统中的视/音频设备, 显示菜单
//	//
//
//	//是否广播视频
//	BOOL bIsBroadcastVideo = ((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1);
//	int nVideoDeviceCount = pUserInfo->_aVideoCardInfo.GetSize()-1;
//	int nVoiceDeviceCount;
//	if ((pUserInfo->_iUserMicType!=255)/*||(pUserInfo->_aVideoCardInfo.GetSize()>0)*/)
//		nVoiceDeviceCount=1;
//	else
//		nVoiceDeviceCount=0;
//
//	if (((pLocalUserInfo->_iStatusFlag==ntConferenceUser)||(((CConferenceDlg*)m_pdMainDlg)->ConferenceSynchronization()))&&(m_iCardNo<H323_IS_VIDEO_NO))						//如果是演讲人有广播
//	{
//		if ((nVideoDeviceCount>0||m_iCardNo == MEDIA_IS_VIDEO_NO || m_iCardNo ==  SCREEN_IS_VIDEO_NO) &&
//			(pLocalUserInfo->_pPresideUserInfo && pLocalUserInfo->_pPresideUserInfo->_bVASynchronizationFlag))
//		{
//			//if (GetFloatWnd() != this)
//			//{
//			project_language_loadstring(_T("DIALOG"), _T("BROADCAST_CONFERENCE_VIDEO"), strText, 255);
//			popMenu.AppendMenu(MF_STRING,IDM_BROADCAST_VIDEO,strText);
//
//			if (bIsBroadcastVideo)
//			{
//				popMenu.CheckMenuItem(IDM_BROADCAST_VIDEO, MF_BYCOMMAND|MF_CHECKED);
//			}
//			//}
//		}
//
//		if ((nVoiceDeviceCount>0||m_iCardNo == MEDIA_IS_VIDEO_NO || m_iCardNo ==  SCREEN_IS_VIDEO_NO) &&
//			(pLocalUserInfo->_pPresideUserInfo && pLocalUserInfo->_pPresideUserInfo->_bVASynchronizationFlag))
//		{
//			//if (GetFloatWnd() != this)
//			//{
//			project_language_loadstring(_T("DIALOG"), _T("BROADCAST_CONFERENCE_SOUND"), strText, 255);
//			popMenu.AppendMenu(MF_STRING,IDM_BROADCAST_SOUND,strText);
//
//			if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndSound(m_iIndex-1))
//				popMenu.CheckMenuItem(IDM_BROADCAST_SOUND, MF_BYCOMMAND|MF_CHECKED);
//			//}
//		}
//	}
//
//	if (m_iCardNo != MEDIA_IS_VIDEO_NO && m_iCardNo != SCREEN_IS_VIDEO_NO)
//	{
//		//////////////////////////////////////////////////////////////////////////
//		// 观看会场
//		if (GetFloatWnd() != this)
//		{
//			if ((pUserInfo->_aSoundDriverInfo.GetSize()) > 0 && (pUserInfo->_aVideoDriverInfo.GetSize() > 0))
//			{
//				project_language_loadstring(_T("DIALOG"), _T("WACTH_CONFERECNE_HALL"), strText, 255);
//				popMenu.AppendMenu(MF_STRING,IDM_WACTH_AVDIEO,strText);	// 观看会场
//
//				if (IsHaveVideo() && IsHaveSound())
//					popMenu.CheckMenuItem(IDM_WACTH_AVDIEO, MF_BYCOMMAND|MF_CHECKED);
//			}
//			
//			if (nVideoDeviceCount>0 ||m_iCardNo == MEDIA_IS_VIDEO_NO || m_iCardNo ==  SCREEN_IS_VIDEO_NO)
//			{
//				project_language_loadstring(_T("DIALOG"), _T("WACTH_CONFERENCE_VIDEO"), strText, 255);
//				popMenu.AppendMenu(MF_STRING,IDM_INCEPT_VIDEO,strText);
//				if (IsHaveVideo())
//					popMenu.CheckMenuItem(IDM_INCEPT_VIDEO, MF_BYCOMMAND|MF_CHECKED);
//			}
//
//			if (nVoiceDeviceCount>0 ||m_iCardNo == MEDIA_IS_VIDEO_NO || m_iCardNo ==  SCREEN_IS_VIDEO_NO)
//			{
//				project_language_loadstring(_T("DIALOG"), _T("RECEIVE_CONFERENCE_SOUND"), strText, 255);
//				popMenu.AppendMenu(MF_STRING,IDM_INCEPT_SOUND,strText);
//				if (IsHaveSound())
//					popMenu.CheckMenuItem(IDM_INCEPT_SOUND, MF_BYCOMMAND|MF_CHECKED);
//			}
//		}
//		//////////////////////////////////////////////////////////////////////////
//
//		//project_language_loadstring(_T("CONTROL_MENU"), _T("IDM_SYNC_HRONIZATION"), strText, 255);
//		//popMenu.AppendMenu(MF_STRING, IDM_SYNC_HRONIZATION, strText);	// 唇音同步
//		//int nFlag = m_bSynchronization ? MF_CHECKED : MF_UNCHECKED;
//		//popMenu.CheckMenuItem(IDM_SYNC_HRONIZATION, nFlag);
//	}
//
//    if (m_iCardNo != MEDIA_IS_VIDEO_NO)   //200: 共享媒体
//    {
//		popMenu.AppendMenu(MF_SEPARATOR);
//
//		if (pUserInfo->_aVideoDriverInfo.GetSize() > 0 || m_iCardNo == SCREEN_IS_VIDEO_NO || m_iCardNo == MEDIA_IS_VIDEO_NO)
//		{
//			project_language_loadstring(_T("DIALOG"), _T("VIDEO_SETTING"), strText, 255);
//			popMenu.AppendMenu(MF_STRING,IDM_VIDEO_SETTING, strText);	// 视频设置
//		}
//
//		if (pUserInfo->_aSoundDriverInfo.GetSize() > 0 || m_iCardNo ==  MEDIA_IS_VIDEO_NO)
//		{
//			project_language_loadstring(_T("DIALOG"), _T("AUDIO_SETTING"), strText, 255);
//			popMenu.AppendMenu(MF_STRING,IDM_AUDIO_SETTING, strText);	// 音频设置
//		}
//
//		if ((m_iCardNo != SCREEN_IS_VIDEO_NO) && pUserInfo &&(pUserInfo->_aVideoCardInfo.GetSize()>1))
//		{
//			//project_language_loadstring(_T("MENU"), _T("MENU_LOCK_AVEDIO"), strText, 255);
//			//popMenu.AppendMenu(MF_STRING,IDM_LOCK_AVEDIO,strText);
//
//			//////////////////////////////////////////////////////////////////////////
//
//			project_language_loadstring(_T("MENU"), _T("MENU_YUNTAI_SETTING"), strText, 255);	// 云台设置
//			popMenu.AppendMenu(MF_STRING,IDM_CONTROL_REMOTESET,strText);
//
//			project_language_loadstring(_T("MENU"), _T("MENU_PRESETPOINT_CONTROL"), strText, 255);	// 预置点设置
//			popMenu.AppendMenu(MF_STRING,IDM_PRESET_POINT,strText);
//
//			popMenu.AppendMenu(MF_SEPARATOR);
//
//			if (m_pConferenceWinDlg)
//			{
//				project_language_loadstring(_T("MENU"), _T("MENU_VIDEO_FORMAT_SETTING"), strText, 255);
//				popMenu.AppendMenu(MF_STRING, IDM_USER_VIDEO_FORMAT_SETTING, strText);	// 启用窗口视频格式
//				project_language_loadstring(_T("MENU"), _T("MENU_WIN_VIDEO_FORMAT_SETTING"), strText, 255);
//				popMenu.AppendMenu(MF_STRING, IDM_WIN_VIDEO_FORMAT_SETTING, strText);	// 窗口视频格式设置
//
//				TPreSettingInfo* ptPreSettingInfo =  ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetWinPreSettingInfo(this);
//				if (ptPreSettingInfo)
//				{
//					popMenu.CheckMenuItem(IDM_USER_VIDEO_FORMAT_SETTING, ptPreSettingInfo->_bUseFlag ? MF_CHECKED : MF_UNCHECKED);
//				}
//			}
//			
//			//////////////////////////////////////////////////////////////////////////
//
//			
//			//TVideoCardInfo* pTVideoCardInfo = NULL;
//			//if (pUserInfo)
//			//{
//			//	pTVideoCardInfo = pUserInfo->_aVideoCardInfo.GetAt(m_iCardNo);
//			//}
//			//
//			//if (pTVideoCardInfo)
//			//{
//			//	popMenu.CheckMenuItem(IDM_LOCK_AVEDIO, pTVideoCardInfo->_iLockSessionID ? MF_CHECKED : MF_UNCHECKED);
//			//}
//		}
//     }
//	//tigertemp
//	 if (m_iCardNo ==  SCREEN_IS_VIDEO_NO)
//	 {
//		 if (!m_bControl)
//		 {
//		    
//			project_language_loadstring(_T("MENU"), _T("MENU_SCREEN_CONTROL"), strText, 255);
//			popMenu.AppendMenu(MF_STRING, IDM_SCREEN_CONTROL, strText);
//		 }
//		 else
//		 {
//			project_language_loadstring(_T("MENU"), _T("MENU_SCREEN_CONTROL_CANCEL"), strText, 255);
//			popMenu.AppendMenu(MF_STRING, IDM_SCREEN_CANCELCONTROL, strText);
//		 }
//	 }
//
//    if (!GetFullScreenFlag() && !GetFloatWnd()&&(m_iCardNo!=SCREEN_IS_VIDEO_NO))
//    {
//        //没有全屏, 并且在不在1号屏上的视频图像
//        if (((CConferenceWinDlg *)m_pConferenceWinDlg)->GetFrameIndex() !=0 &&
//			((CConferenceWinDlg *)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1))  //广播得视频
//        {
//            project_language_loadstring(_T("MENU"), _T("MENU_FLOAT_VIDEOWIND"), strText, 255);
//            popMenu.AppendMenu(MF_STRING,ID_FLOAT_VIDEO, strText);
//
//            if (GetFloatWin() && GetFloatWin()->IsWindowVisible())
//            {
//                popMenu.CheckMenuItem(ID_FLOAT_VIDEO, MF_BYCOMMAND | MF_CHECKED);
//            }
//        }
//    }
//
//    if (GetFloatWnd() != this/* && m_iCardNo != 200*/)  //单屏主持人不能直接关闭浮动窗口
//    {
//        popMenu.AppendMenu(MF_SEPARATOR);
//
//        project_language_loadstring(_T("MENU"), _T("MENU_CLOSE_CONFERENCEHALL"), strText, 255);
//        popMenu.AppendMenu(MF_STRING,IDM_CLOSE_USER,strText);
//    }
//}
//
//void CUserDlg::ContextMenu_ConferenceUser(CMenu &popMenu)
//{
//	UINT nStatus;
//	TCHAR strText[255]=_T("");
//
//	project_language_loadstring(_T("MENU"), _T("MENU_FULL_SCREENSHOW"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_FULL_SCREEN,strText);
//	if (GetFullScreenFlag())
//		popMenu.CheckMenuItem(IDM_FULL_SCREEN, MF_BYCOMMAND|MF_CHECKED);
//
//	if (m_bControl && SCREEN_IS_VIDEO_NO == m_iCardNo)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_FULLSCREEN_CAPTURE"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_FULL_SCREEN_CAPTURE, strText);	// 全屏采集屏幕
//		if (m_bFullScreenCpture)
//			popMenu.CheckMenuItem(IDM_FULL_SCREEN_CAPTURE, MF_BYCOMMAND|MF_CHECKED);
//	}
//
//	//标题栏
//	project_language_loadstring(_T("MENU"), _T("MENU_SHOW_NAME"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_TITLE_BAR,strText);
//	nStatus = (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd() && m_pDlgAVInfo->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//	popMenu.CheckMenuItem(IDM_TITLE_BAR, nStatus);
//
//	popMenu.AppendMenu(MF_SEPARATOR);
//
//	//project_language_loadstring(_T("MENU"), _T("IDM_TITLE_BAR"), strText, 255);	// 详细信息
//	popMenu.AppendMenu(MF_STRING,IDM_DETAILINFO_SHOW,_T("详细信息")/*strText*/);
//	nStatus = (m_pDetailInfoDlg && m_pDetailInfoDlg->GetSafeHwnd() && m_pDetailInfoDlg->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//	popMenu.CheckMenuItem( IDM_DETAILINFO_SHOW, nStatus );
//
//	//if (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd() && m_pDlgAVInfo->IsWindowVisible())
//	//{
//	//	project_language_loadstring(_T("MENU"), _T("IDM_SHOW_CODE_FLOW"), strText, 255);	// 显示码流
//	//	popMenu.AppendMenu(MF_STRING,IDM_SHOW_CODE_FLOW,strText);
//	//	popMenu.CheckMenuItem(IDM_SHOW_CODE_FLOW, m_bShowCodeFlow ? MF_CHECKED : MF_UNCHECKED);
//	//}
//
//	if (((CConferenceDlg *)m_pdMainDlg)->GetAllowControl()) //允许控制
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_YUNTAI_CONTROL"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_STATUS_BAR,strText);
//		nStatus = (m_pDlgYT && m_pDlgYT->GetWnd() && m_pDlgYT->GetWnd()->GetSafeHwnd() &&
//			m_pDlgYT->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//		popMenu.CheckMenuItem(IDM_STATUS_BAR, nStatus);
//
//		project_language_loadstring(_T("MENU"), _T("MENU_PRESETPOINT_CONTROL"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_PRESET_POINT,strText);
//	}
//
//	project_language_loadstring(_T("MENU"), _T("MENU_TO_JPG"), strText, 255);		// 拍照
//	popMenu.AppendMenu(MF_STRING,IDM_TO_JPG,strText);
//
//	if (((CConferenceDlg *)m_pdMainDlg)->GetLocalUserInfo()->_pUserInfo->_bAllowKinescope)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_AVIEDO_RECORD"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_RECORD,strText);
//		if (m_pAVCRecordFactory)
//			popMenu.CheckMenuItem(IDM_RECORD, MF_BYCOMMAND|MF_CHECKED);
//	}
//
//	//add by tiger,2008.07.24
//	//放大
//	if (0==m_iZoomIn || 2==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_ZOOMIN"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}else if (1==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_REDUCE"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}
//	//还原
//	project_language_loadstring(_T("MENU"), _T("MENU_REVERT"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_REVERT,strText);
//	//end add
//
//	//tigertemp
//	if (m_iCardNo ==  SCREEN_IS_VIDEO_NO)
//	{
//		//popMenu.AppendMenu(MF_SEPARATOR);
//
//		if (!m_bControl)
//		{
//			if (((CConferenceDlg *)(m_pdMainDlg))->GetAllowScreenControl())
//			{
//				project_language_loadstring(_T("MENU"), _T("MENU_SCREEN_CONTROL"), strText, 255);
//				popMenu.AppendMenu(MF_STRING, IDM_SCREEN_CONTROL, strText);
//			}
//		}
//		else
//		{
//			project_language_loadstring(_T("MENU"), _T("MENU_SCREEN_CONTROL_CANCEL"), strText, 255);
//			popMenu.AppendMenu(MF_STRING, IDM_SCREEN_CANCELCONTROL, strText);
//		}
//	}
//
//	popMenu.AppendMenu(MF_SEPARATOR);
//	////////////////////////////////////////////////////////////////////////////////
//	// 视频显示模式菜单 Add Han Hua jie 2008/01/14
//	CMenu MenuVideoMode;
//	MenuVideoMode.CreateMenu();
//	project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_INCISE_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_SEEING_PROPORTION_INCISE_SHOW,strText);					// 视觉比例切割显示
//	project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_PADDED_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_SEEING_PROPORTION_PADDED_SHOW,strText);					// 视觉比例填补显示
//	project_language_loadstring(_T("MENU"), _T("MENU_FULL_PANORAMA_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_FULL_PANORAMA_SHOW,strText);								// 视频全景显示
//
//	MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_INCISE_SHOW, MF_UNCHECKED);
//	MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_PADDED_SHOW, MF_UNCHECKED);
//	MenuVideoMode.CheckMenuItem(IDM_FULL_PANORAMA_SHOW, MF_UNCHECKED);
//
//	switch(m_nVideoShowMode)
//	{
//	case ntVideoShowModeCut:
//		MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_INCISE_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_INCISE_SHOW"), strText, 255);
//		break;
//	case ntVideoShowModeFill:
//		MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_PADDED_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_PADDED_SHOW"), strText, 255);
//		break;
//	case ntVideoShowModeFull:
//		MenuVideoMode.CheckMenuItem(IDM_FULL_PANORAMA_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_FULL_PANORAMA_SHOW"), strText, 255);
//		break;
//	default:
//		break;
//	}
//
//	popMenu.AppendMenu(MF_POPUP,(UINT_PTR)MenuVideoMode.m_hMenu,strText);
//
//	//if (m_iCardNo != MEDIA_IS_VIDEO_NO && m_iCardNo != MEDIA_IS_VIDEO_NO)
//	//{
//	//	project_language_loadstring(_T("CONTROL_MENU"), _T("IDM_SYNC_HRONIZATION"), strText, 255);
//	//	popMenu.AppendMenu(MF_STRING, IDM_SYNC_HRONIZATION, strText);	// 唇音同步
//	//	int nFlag = m_bSynchronization ? MF_CHECKED : MF_UNCHECKED;
//	//	popMenu.CheckMenuItem(IDM_SYNC_HRONIZATION, nFlag);
//	//}
//}
//
//void CUserDlg::ContextMenu_WatchUser(CMenu &popMenu, bool bIsAllowControl)
//{
//    UINT nStatus;          
//    TCHAR strText[255]=_T("");
//
//	//得到会议人员信息;
//	ASSERT(m_pdMainDlg);
//	TConferenceUserInfo *pUserInfo = ((CConferenceDlg *)m_pdMainDlg)->GetConferenceUserInfo(m_iSessionID);
//	ASSERT(pUserInfo);
//
//    //标题栏
//    project_language_loadstring(_T("MENU"), _T("MENU_SHOW_NAME"), strText, 255);
//    popMenu.AppendMenu(MF_STRING,IDM_TITLE_BAR,strText);
//    nStatus = (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd() && m_pDlgAVInfo->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//    popMenu.CheckMenuItem(IDM_TITLE_BAR, nStatus);
//
//	popMenu.AppendMenu(MF_SEPARATOR);
//
//	//project_language_loadstring(_T("MENU"), _T("IDM_TITLE_BAR"), strText, 255);	// 详细信息
//	popMenu.AppendMenu(MF_STRING,IDM_DETAILINFO_SHOW,_T("详细信息")/*strText*/);
//	nStatus = (m_pDetailInfoDlg && m_pDetailInfoDlg->GetSafeHwnd() && m_pDetailInfoDlg->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//	popMenu.CheckMenuItem( IDM_DETAILINFO_SHOW, nStatus );
//
//	//if (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd() && m_pDlgAVInfo->IsWindowVisible())
//	//{
//	//	project_language_loadstring(_T("MENU"), _T("IDM_SHOW_CODE_FLOW"), strText, 255);	// 显示码流
//	//	popMenu.AppendMenu(MF_STRING,IDM_SHOW_CODE_FLOW,strText);
//	//	popMenu.CheckMenuItem(IDM_SHOW_CODE_FLOW, m_bShowCodeFlow ? MF_CHECKED : MF_UNCHECKED);
//	//}
//
//	project_language_loadstring(_T("MENU"), _T("MENU_FULL_SCREENSHOW"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_FULL_SCREEN,strText);
//	if (GetFullScreenFlag())
//		popMenu.CheckMenuItem(IDM_FULL_SCREEN, MF_BYCOMMAND|MF_CHECKED);
//
//	//add by tiger,2008.07.24
//	//放大
//	if (0==m_iZoomIn || 2==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_ZOOMIN"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}else if (1==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_REDUCE"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}
//	//还原
//	project_language_loadstring(_T("MENU"), _T("MENU_REVERT"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_REVERT,strText);
//	//end add
//
//	if (SCREEN_IS_VIDEO_NO == m_iCardNo)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_FULLSCREEN_CAPTURE"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_FULL_SCREEN_CAPTURE, strText);	// 全屏采集屏幕
//		if (m_bFullScreenCpture)
//			popMenu.CheckMenuItem(IDM_FULL_SCREEN_CAPTURE, MF_BYCOMMAND|MF_CHECKED);
//	}
//
//	popMenu.AppendMenu(MF_SEPARATOR);
//
//	////////////////////////////////////////////////////////////////////////////////
//	// 视频显示模式菜单 Add Han Hua jie 2008/01/14
//	CMenu MenuVideoMode;
//	MenuVideoMode.CreateMenu();
//	project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_INCISE_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_SEEING_PROPORTION_INCISE_SHOW,strText);					// 视觉比例切割显示
//	project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_PADDED_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_SEEING_PROPORTION_PADDED_SHOW,strText);					// 视觉比例填补显示
//	project_language_loadstring(_T("MENU"), _T("MENU_FULL_PANORAMA_SHOW"), strText, 255);
//	MenuVideoMode.AppendMenu(MF_STRING,IDM_FULL_PANORAMA_SHOW,strText);								// 视频全景显示
//
//	MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_INCISE_SHOW, MF_UNCHECKED);
//	MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_PADDED_SHOW, MF_UNCHECKED);
//	MenuVideoMode.CheckMenuItem(IDM_FULL_PANORAMA_SHOW, MF_UNCHECKED);
//
//	switch(m_nVideoShowMode)
//	{
//	case ntVideoShowModeCut:
//		MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_INCISE_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_INCISE_SHOW"), strText, 255);
//		break;
//	case ntVideoShowModeFill:
//		MenuVideoMode.CheckMenuItem(IDM_SEEING_PROPORTION_PADDED_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_SEEING_PROPORTION_PADDED_SHOW"), strText, 255);
//		break;
//	case ntVideoShowModeFull:
//		MenuVideoMode.CheckMenuItem(IDM_FULL_PANORAMA_SHOW, MF_CHECKED);
//		project_language_loadstring(_T("MENU"), _T("MENU_FULL_PANORAMA_SHOW"), strText, 255);
//		break;
//	default:
//		break;
//	}
//
//	popMenu.AppendMenu(MF_POPUP,(UINT_PTR)MenuVideoMode.m_hMenu,strText);
//
//	//if (m_iCardNo != MEDIA_IS_VIDEO_NO && m_iCardNo != MEDIA_IS_VIDEO_NO)
//	//{
//	//	project_language_loadstring(_T("CONTROL_MENU"), _T("IDM_SYNC_HRONIZATION"), strText, 255);
//	//	popMenu.AppendMenu(MF_STRING, IDM_SYNC_HRONIZATION, strText);	// 唇音同步
//	//	int nFlag = m_bSynchronization ? MF_CHECKED : MF_UNCHECKED;
//	//	popMenu.CheckMenuItem(IDM_SYNC_HRONIZATION, nFlag);
//	//}
//
//    //监控人员允许控制
//    if (bIsAllowControl) 
//    {
//		project_language_loadstring(_T("MENU"), _T("MENU_TO_JPG"), strText, 255);		// 拍照
//		popMenu.AppendMenu(MF_STRING,IDM_TO_JPG,strText);
//
//        //录像
//        if (((CConferenceDlg *)m_pdMainDlg)->GetLocalUserInfo()->_pUserInfo->_bAllowKinescope)
//        {
//            project_language_loadstring(_T("MENU"), _T("MENU_AVIEDO_RECORD"), strText, 255);
//            popMenu.AppendMenu(MF_STRING,IDM_RECORD,strText);
//            if (m_pAVCRecordFactory)
//                popMenu.CheckMenuItem(IDM_RECORD, MF_BYCOMMAND|MF_CHECKED);
//        }
//
//		//if (m_iCardNo != MEDIA_IS_VIDEO_NO)   //200: 共享媒体
//		//{
//		//	project_language_loadstring(_T("MENU"), _T("MENU_AVWIZARD"), strText, 255);
//		//	popMenu.AppendMenu(MF_STRING,IDM_AVWIZARD,strText);
//
//		//	if ((m_iCardNo !=SCREEN_IS_VIDEO_NO)&&(pUserInfo->_aVideoCardInfo.GetSize()>1))
//		//	{
//		//		project_language_loadstring(_T("MENU"), _T("MENU_LOCK_AVEDIO"), strText, 255);
//		//		popMenu.AppendMenu(MF_STRING,IDM_LOCK_AVEDIO,strText);
//
//		//		TVideoCardInfo* pTVideoCardInfo = pUserInfo->_aVideoCardInfo.GetAt(m_iCardNo);
//		//		if (pTVideoCardInfo)
//		//		{
//		//			popMenu.CheckMenuItem(IDM_LOCK_AVEDIO, pTVideoCardInfo->_iLockSessionID ? MF_CHECKED : MF_UNCHECKED);
//		//		}
//		//	}
//		//}
//
//		if (m_iCardNo!=SCREEN_IS_VIDEO_NO)
//			if (!GetFullScreenFlag() && !GetFloatWnd()&&(m_iCardNo!=SCREEN_IS_VIDEO_NO))
//			{
//				//没有全屏, 并且在不在1号屏上的视频图像
//				if (((CConferenceWinDlg *)m_pConferenceWinDlg)->GetFrameIndex() !=0 &&
//					((CConferenceWinDlg *)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1))  //广播得视频
//				{
//					project_language_loadstring(_T("MENU"), _T("MENU_FLOAT_VIDEOWIND"), strText, 255);
//					popMenu.AppendMenu(MF_STRING,ID_FLOAT_VIDEO, strText);
//
//					if (GetFloatWin() && GetFloatWin()->IsWindowVisible())
//					{
//						popMenu.CheckMenuItem(ID_FLOAT_VIDEO, MF_BYCOMMAND | MF_CHECKED);
//					}
//				}
//			}
//
//		popMenu.AppendMenu(MF_SEPARATOR);
//
//        if (((CConferenceDlg *)m_pdMainDlg)->GetAllowControl()) //允许控制(控制云台)
//        {
//            project_language_loadstring(_T("MENU"), _T("MENU_YUNTAI_CONTROL"), strText, 255);
//            popMenu.AppendMenu(MF_STRING,IDM_STATUS_BAR,strText);
//            nStatus = (m_pDlgYT && m_pDlgYT->GetWnd() && m_pDlgYT->GetWnd()->GetSafeHwnd() &&
//                m_pDlgYT->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//            popMenu.CheckMenuItem(IDM_STATUS_BAR, nStatus);
//
//            project_language_loadstring(_T("MENU"), _T("MENU_PRESETPOINT_CONTROL"), strText, 255);
//            popMenu.AppendMenu(MF_STRING,IDM_PRESET_POINT,strText);
//
//            popMenu.AppendMenu(MF_SEPARATOR);
//        }
//
//        //
//        //检查系统中的视/音频设备, 显示菜单
//        //
//
//        int nVideoDeviceCount = pUserInfo->_aVideoCardInfo.GetSize()-1;
//        int nVoiceDeviceCount;
//		if ((pUserInfo->_iUserMicType!=255)/*||(pUserInfo->_aVideoCardInfo.GetSize()>0)*/)
//			nVoiceDeviceCount=1;
//		else
//			nVoiceDeviceCount=0;
//
//        CConferenceWinDlg *pWndTemp = NULL;
//
//		//if (!((CConferenceDlg*)m_pdMainDlg)->IsIM())		// 判断是IM 不显示下面菜单 Modi Han Hua jie 2007/11/21
//		{
//			if (nVideoDeviceCount>0)
//			{
//				if (GetFloatWnd() != this)
//				{
//					project_language_loadstring(_T("DIALOG"), _T("BROADCAST_CONFERENCE_VIDEO"), strText, 255);
//					popMenu.AppendMenu(MF_STRING,IDM_BROADCAST_VIDEO,strText);
//
//					if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1))
//					{
//						popMenu.CheckMenuItem(IDM_BROADCAST_VIDEO, MF_BYCOMMAND|MF_CHECKED);
//					}
//				}
//			}
//
//			if (nVoiceDeviceCount>0)
//			{
//				if (GetFloatWnd() != this)
//				{
//					project_language_loadstring(_T("DIALOG"), _T("BROADCAST_CONFERENCE_SOUND"), strText, 255);
//					popMenu.AppendMenu(MF_STRING,IDM_BROADCAST_SOUND,strText);
//
//					if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndSound(m_iIndex-1))
//						popMenu.CheckMenuItem(IDM_BROADCAST_SOUND, MF_BYCOMMAND|MF_CHECKED);
//				}
//			}
//		}
//
//        if (nVideoDeviceCount>0)
//        {
//            if (GetFloatWnd() != this)
//            {
//                project_language_loadstring(_T("DIALOG"), _T("WACTH_CONFERENCE_VIDEO"), strText, 255);
//                popMenu.AppendMenu(MF_STRING,IDM_INCEPT_VIDEO,strText);
//                if (IsHaveVideo())
//                    popMenu.CheckMenuItem(IDM_INCEPT_VIDEO, MF_BYCOMMAND|MF_CHECKED);
//            }
//        }
//
//        if (nVoiceDeviceCount>0)
//        {
//            if (GetFloatWnd() != this)
//            {
//                project_language_loadstring(_T("DIALOG"), _T("RECEIVE_CONFERENCE_SOUND"), strText, 255);
//                popMenu.AppendMenu(MF_STRING,IDM_INCEPT_SOUND,strText);
//                if (IsHaveSound())
//                    popMenu.CheckMenuItem(IDM_INCEPT_SOUND, MF_BYCOMMAND|MF_CHECKED);
//            }
//        }
//
//		if (GetFloatWnd() != this/* && m_iCardNo != 200*/)  //单屏主持人不能直接关闭浮动窗口
//		{
//			popMenu.AppendMenu(MF_SEPARATOR);
//
//			project_language_loadstring(_T("MENU"), _T("MENU_CLOSE_CONFERENCEHALL"), strText, 255);
//			popMenu.AppendMenu(MF_STRING,IDM_CLOSE_USER,strText);
//		}
//    }
//}
//
//void CUserDlg::ContextMenu_IMUser(CMenu &popMenu)
//{
//	UINT nStatus;
//	TCHAR strText[255]=_T("");
//	bool bInsertSeparatorMenuItem = false;
//
//	project_language_loadstring(_T("MENU"), _T("MENU_TO_JPG"), strText, 255);		// 拍照
//	popMenu.AppendMenu(MF_STRING,IDM_TO_JPG,strText);
//
//	project_language_loadstring(_T("MENU"), _T("MENU_AVIEDO_RECORD"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_RECORD,strText);
//	if (m_pAVCRecordFactory)
//		popMenu.CheckMenuItem(IDM_RECORD, MF_BYCOMMAND|MF_CHECKED);
//
//	project_language_loadstring(_T("MENU"), _T("MENU_FULL_SCREENSHOW"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_FULL_SCREEN,strText);
//	if (GetFullScreenFlag())
//		popMenu.CheckMenuItem(IDM_FULL_SCREEN, MF_BYCOMMAND|MF_CHECKED);
//
//	//add by tiger,2008.07.24
//	//放大
//	if (0==m_iZoomIn || 2==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_ZOOMIN"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}else if (1==m_iZoomIn)
//	{
//		project_language_loadstring(_T("MENU"), _T("MENU_REDUCE"), strText, 255);
//		popMenu.AppendMenu(MF_STRING,IDM_ZOOMIN,strText);
//	}
//	//还原
//	project_language_loadstring(_T("MENU"), _T("MENU_REVERT"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_REVERT,strText);
//	//end add
//
//	popMenu.AppendMenu(MF_SEPARATOR);
//
//	//标题栏
//	project_language_loadstring(_T("MENU"), _T("MENU_SHOW_NAME"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_TITLE_BAR,strText);
//	nStatus = (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd() && m_pDlgAVInfo->IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
//	popMenu.CheckMenuItem(IDM_TITLE_BAR, nStatus);
//	
//	popMenu.AppendMenu(MF_SEPARATOR);
//
//	//if (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd() && m_pDlgAVInfo->IsWindowVisible())
//	//{
//	//	project_language_loadstring(_T("MENU"), _T("IDM_SHOW_CODE_FLOW"), strText, 255);	// 显示码流
//	//	popMenu.AppendMenu(MF_STRING,IDM_SHOW_CODE_FLOW,strText);
//	//	popMenu.CheckMenuItem(IDM_SHOW_CODE_FLOW, m_bShowCodeFlow ? MF_CHECKED : MF_UNCHECKED);
//	//}
//
//	popMenu.AppendMenu(MF_SEPARATOR);
//
//	project_language_loadstring(_T("MENU"), _T("MENU_CLOSE_CONFERENCEHALL"), strText, 255);
//	popMenu.AppendMenu(MF_STRING,IDM_CLOSE_USER,strText);
//
//}
//
//void CUserDlg::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//
//	CDC*	pDC=GetDC();
//	OnEraseBkgnd(pDC);
//    ReleaseDC(pDC);
//}
//
//void CUserDlg::ResetWindowRgn()
//{
//	if ( !m_pDlgAVInfo || !m_pDlgYT)
//	{
//		return ;
//	}
//
//	CWnd *pDlgVideoWindow=GetVideoWindow();
//	if (!pDlgVideoWindow)
//	{
//		Invalidate();
//		return;
//	}
//
//	HWND	hVideoWnd = pDlgVideoWindow->GetSafeHwnd();
//	HWND	hTitleWnd = m_pDlgAVInfo->GetSafeHwnd();
//	HWND	hControlWnd = m_pDlgYT->GetWnd()->GetSafeHwnd();
//
//	CRect rc, WindowsRc;
//	GetClientRect(&rc);
//	GetWindowRect(WindowsRc);
//
//	int x, y, cx, cy;    
//	CRect rcWindow, rcClient;
//	::GetClientRect(hVideoWnd, &rcClient);
//	::GetWindowRect(hVideoWnd, &rcWindow);
//
//	int iSelectFrameWidth = 0;
//	if (IsSelected())
//	{
//		iSelectFrameWidth = 2;
//	}
//
//	x=0; y=0; cx=rcClient.Width(); cy=rcClient.Height();
//
//	if (rc.Width() <= cx)
//	{
//		x  = WindowsRc.left - rcWindow.left + iSelectFrameWidth;
//		cx = cx - (rcWindow.right - WindowsRc.right) - iSelectFrameWidth;
//	}
//
//	if (rc.Height() <= cy)
//	{
//		y = WindowsRc.top - rcWindow.top + iSelectFrameWidth;
//		cy = cy - (rcWindow.bottom - WindowsRc.bottom) - iSelectFrameWidth;
//	}
//
// 	CRect rcControl(0,0,0,0);
//	if (::IsWindowVisible(hControlWnd))
//	{
//		::GetWindowRect(hControlWnd, &rcControl);	
//		//cy=cy-(rcWindow.bottom-rcControl.top);
//
//		(CWnd::FromHandle(hControlWnd))->SetWindowPos(NULL, iSelectFrameWidth, 
//											rc.bottom-rcControl.Height()-iSelectFrameWidth, 
//											rc.Width()-iSelectFrameWidth*2, 
//											rcControl.Height(), SWP_NOACTIVATE);
//		cy -= rcControl.Height();
//	}
//	
//	if (m_pDlgAVInfo->IsWindowVisible())
//	{
//		CRect rcTitle;
//		CRgn rgnVideoTitle;
//		m_pDlgAVInfo->GetClientRect(&rcTitle);
//
//		if (::IsWindowVisible(hControlWnd))
//		{
//			CRect rcControl;
//			::GetClientRect(hControlWnd, &rcControl);
//			m_pDlgAVInfo->SetWindowPos(NULL, 
//									   iSelectFrameWidth, 
//									   rc.Height() - rcTitle.Height() - rcControl.Height() - iSelectFrameWidth, 
//									   rcTitle.Width(), 
//									   rcTitle.Height(), 
//									   SWP_NOACTIVATE);
//		}
//		else
//		{
//			m_pDlgAVInfo->SetWindowPos(NULL, 
//									   iSelectFrameWidth, 
//									   rc.Height() - rcTitle.Height() - iSelectFrameWidth, 
//									   rcTitle.Width(), 
//									   rcTitle.Height(), 
//									   SWP_NOACTIVATE);
//		}
//
//		CRect rcWinTitle;
//		::GetWindowRect(hTitleWnd, &rcWinTitle);
//		BOOL bSucceeded = rgnVideoTitle.CreateRectRgn(rcWinTitle.left   - rcWindow.left, 
//													  rcWinTitle.top    - rcWindow.top, 
//													  rcWinTitle.right  - rcWindow.left, 
//													  rcWinTitle.bottom - rcWindow.top);
//		ASSERT(bSucceeded == TRUE);
//
//		CRgn rgnVideo;
//		rgnVideo.CreateRectRgn(x, y , cx , cy );
//		rgnVideo.CombineRgn((CRgn*)&rgnVideo, (CRgn*)&rgnVideoTitle, RGN_DIFF);
//
//		::SetWindowRgn(hVideoWnd,(HRGN)rgnVideo, TRUE);
//		::DeleteObject((HRGN)rgnVideo);
//
//		return;
//	}
//
//	HRGN rgnVideo = ::CreateRectRgn(x, y, cx, cy);
//	::SetWindowRgn(hVideoWnd,rgnVideo,TRUE);
//	::DeleteObject(rgnVideo);
//}
//
//
//void CUserDlg::ShowTitleBar(BOOL bShow)
//{
//    if (m_pDlgAVInfo && m_pDlgAVInfo->GetSafeHwnd())
//    {
//        if (bShow)
//        {
//            if (m_hTitleDlgTimer == 0)
//            {
//                m_hTitleDlgTimer = 1230;
//                SetTimer(m_hTitleDlgTimer, 2000, NULL);     //2秒的效果比较好
//				OnTimer(m_hTitleDlgTimer);
//            }
//
//            m_pDlgAVInfo->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | 
//                SWP_NOACTIVATE | SWP_SHOWWINDOW);
//        }
//        else
//        {
//            m_pDlgAVInfo->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | 
//                SWP_NOACTIVATE | SWP_HIDEWINDOW);
//
//            if (m_hTitleDlgTimer)
//            {
//                KillTimer(m_hTitleDlgTimer);
//                m_hTitleDlgTimer = 0;
//            }
//        }
//    }
//	if (RS_FLAG == 1)//此功能为定制,add by lzl,2008.10.20
//		ResetWindowRgn();	
//}
//
//void CUserDlg::SetTitleBarColor()
//{
//    //根据音视频流显示不同的背景色
//    COLORREF bkColor = RGB(255,255,128);    //local default
//    COLORREF textColor = RGB(0,0,0);
//    if (IsHaveSound())
//    {
//        bkColor = RGB(128,255,128); //绿
//        textColor = RGB(128,0,64);
//    }
//
//    if (IsHaveVideo())
//    {
//        bkColor = RGB(0,128,255);   //蓝
//        textColor = RGB(255,255,255);
//    }
//
//    if (IsHaveVideo() && IsHaveSound())
//    {
//        bkColor = RGB(255,255,128); //黄
//        textColor = RGB(0,0,0);
//    }
//
//    if (m_pDlgAVInfo)
//    {
//        m_pDlgAVInfo->SetBkColor(bkColor);
//        m_pDlgAVInfo->SetTextColor(textColor);
//    }
//}
//
//void CUserDlg::IAVInfoNotify_OnVolume(int nVolume)
//{
//    if(m_pAudioPlay)
//    {
//        m_pAudioPlay->SetVolume(nVolume);
//    }
//}
//
//UINT CUserDlg::GetVideoBitrate()
//{
//    if (m_pVideoPlayer)
//    {
//        m_ulVideoBitrate=((UINT)(m_pVideoPlayer->GetVideoBitrate()))/8;
//		return m_ulVideoBitrate;
//    }
//    
//    return 0L;
//}
//
//UINT CUserDlg::GetAudioBitrate()
//{
//	m_ulAudioBitrate=m_ulAudioBitrateSum;
//	m_ulAudioBitrateSum=0;
//	return m_ulAudioBitrate;
//}
//
//void CUserDlg::OnResizeVideoRect(int x, int y, int cx, int cy)
//{
//    ResizeControls();
//}
//
//LRESULT CUserDlg::OnReveiveMessage(WPARAM wParam, LPARAM lParam)
//{
//	switch (wParam)
//	{
//	case HP_VIDEO_RECEIVE_CONNECTED:
//		{
//			if (m_pAVVideoReceiver)
//			{
//				m_pAVVideoReceiver->EnableReceive(m_IsReceivingVideo);
//			}
//			break;
//		}
//	case HP_AUDIOO_RECEIVE_CONNECTED:
//		{
//			if (m_pAVAudioReceiver)
//			{
//				m_pAVAudioReceiver->EnableReceive(m_IsReceivingAudio);
//			}
//			break;
//		}
//	}
//
//	return 0;
//}
//
//BOOL CUserDlg::IsControling()
//{
//	return m_bControl;
//}
//
//void CUserDlg::OnPermitControl(unsigned __int32 iSessionID, BOOL bPermit)
//{
//	if (m_iCardNo == SCREEN_IS_VIDEO_NO && iSessionID == m_iSessionID)
//	{
//		m_bControl = bPermit;
//	}
//}
//
//void CUserDlg::OnUserScreenControlKeyDown(MSG* pMsg)
//{
//	if (m_iCardNo == SCREEN_IS_VIDEO_NO && m_bControl)
//	{
//		BOOL	bShift=GetKeyState(VK_SHIFT) & 0x80;
//		BOOL	bControl=GetKeyState(VK_CONTROL) & 0x80;
//		BOOL	bAtl=GetKeyState(VK_MENU) & 0x80;
//		if (pMsg->message == WM_KEYDOWN 
//			)
//		{
//			WPARAM wParam = 0;
//			LPARAM lParam = 0;
//			lParam = pMsg->wParam;
//			wParam = bShift?1:0;
//			wParam|= bControl?2:0;
//			wParam |= bAtl?4:0;
//			SendFrame(-1, wParam, lParam);
//		}
//	}
//}
//
//BOOL CUserDlg::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	if (m_iCardNo == SCREEN_IS_VIDEO_NO)
//	{
//		if (pMsg->message != WM_KEYDOWN)
//		{
//			BOOL	bShift=GetKeyState(VK_SHIFT) & 0x80;
//			BOOL	bControl=GetKeyState(VK_CONTROL) & 0x80;
//			BOOL	bAtl=GetKeyState(VK_MENU) & 0x80;
//			DWORD	dwParam	= pMsg->wParam;
//			pMsg->wParam=bShift?1:0;
//			pMsg->wParam|=bControl?2:0;
//			pMsg->wParam|=bAtl?4:0;
//			SendFrame(-1, pMsg->wParam, 0);
//			pMsg->wParam=dwParam;
//			SendFrame(pMsg->message, pMsg->wParam, pMsg->lParam);
//		}
//	}
//	return __super::PreTranslateMessage(pMsg);
//}
//
//int CUserDlg:: SendFrame(DWORD dwMessage, DWORD dwParam1, DWORD dwParam2)
//{	
//	//add by tiger,2008.07.23
//	if (m_iZoomIn)
//	{
//		return -1;
//	}	
//	//end add
//
//	if (!m_bControl)
//	{
//		return -1;
//	}
//	if (!m_pAVVideoReceiver)
//	{
//		return -1;
//	}
//	if (WM_KEYDOWN == dwMessage)
//	{
//		DWORD	dwParam	= dwParam1;
//
//		dwParam1		= dwParam2&0xff0000;
//		dwParam2		= dwParam;
//
//		char pData[12];
//		ZeroMemory(pData,12);
//		memcpy(pData,	&dwMessage,		4);
//		memcpy(pData+4,	&dwParam1,		4);
//		memcpy(pData+8,	&dwParam2,		4);
//		m_pAVVideoReceiver->SendFrame(pData, 12);
//	}
//	else if((WM_MOUSEMOVE == dwMessage)||
//		(WM_LBUTTONUP == dwMessage)||
//		(WM_LBUTTONDOWN == dwMessage)||
//		(WM_LBUTTONDBLCLK == dwMessage) ||
//		(WM_RBUTTONUP == dwMessage)||
//		(WM_RBUTTONDOWN == dwMessage)||
//		(WM_RBUTTONDBLCLK == dwMessage) ||
//		(WM_MBUTTONUP == dwMessage)||
//		(WM_MBUTTONDOWN == dwMessage)||
//		(WM_MBUTTONDBLCLK == dwMessage))
//	{
//		POINT	point;
//		::GetCursorPos(&point);
//
//		::ScreenToClient(m_hWnd, &point);
//		if (m_pVideoPlayer)
//		{
//			int nVideoWidth = m_pVideoPlayer->GetWidth();
//			int nVideoHeight = m_pVideoPlayer->GetHeight();
//			CRect rect;
//			GetClientRect(&rect);
//			int nWndWidth = rect.Width();
//			int nWndHeight = rect.Height();
//			double dblX=((double)nVideoWidth)/((double)nWndWidth);
//			dblX*=(double)point.x;
//			point.x=dblX;
//
//			double dblY=((double)nVideoHeight)/((double)nWndHeight);
//			dblY*=(double)point.y;
//			point.y=dblY;
//			dwParam1	= point.x;
//			dwParam2	= point.y;	
//			if (m_ptLastMouse.x==point.x && m_ptLastMouse.y==point.y && WM_MOUSEMOVE == dwMessage)
//			{
//				//	//TRACE("%d==%d,%d==%d\n",m_ptLastMouse.x,point.x,m_ptLastMouse.y,point.y);
//				return 1;
//			}	
//			m_ptLastMouse.x=point.x;
//			m_ptLastMouse.y=point.y;
//			char pData[12];
//			ZeroMemory(pData,12);
//			memcpy(pData,	&dwMessage,		4);
//			memcpy(pData+4,	&dwParam1,		4);
//			memcpy(pData+8,	&dwParam2,		4);
//			BOOL bControl = GetKeyState(VK_CONTROL) & 0x80;
//			if ((dwMessage == WM_RBUTTONDOWN || dwMessage == WM_RBUTTONUP) && bControl)
//			{
//				return FALSE;
//			}
//			m_pAVVideoReceiver->SendFrame(pData, 12);
//	/*		if (WM_RBUTTONDOWN == dwMessage)
//			{
//				dwMessage = WM_RBUTTONUP;
//				Sleep(5);
//				memcpy(pData,	&dwMessage,		4);
//				m_pAVVideoReceiver->SendFrame(pData, 12);
//			}*/
//		}
//	}
//		else if (WM_MOUSEWHEEL == dwMessage)
//		{
//			dwParam1=dwParam1;
//			dwParam2=0;
//			char pData[12];
//			ZeroMemory(pData,12);
//			memcpy(pData,	&dwMessage,		4);
//			memcpy(pData+4,	&dwParam1,		4);
//			memcpy(pData+8,	&dwParam2,		4);
//			m_pAVVideoReceiver->SendFrame(pData, 12);
//		}
//		else if (dwMessage == -1)
//		{
//			char pData[12];
//			ZeroMemory(pData,12);
//			memcpy(pData,	&dwMessage,		4);
//			memcpy(pData+4,	&dwParam1,		4);
//			memcpy(pData+8,	&dwParam2,		4);
//			m_pAVVideoReceiver->SendFrame(pData, 12);
//		}
//	
//	return 1;
//}
//
//void CUserDlg::OnShowCodeFlow()
//{
//	m_bShowCodeFlow = !m_bShowCodeFlow;
//	OnTimer(m_hTitleDlgTimer);
//}
//void CUserDlg::OnFullScreen()
//{
//	if (GetFloatWnd() == this)
//	{
//		return ;
//	}
//
//	if (m_iCardNo == 255 || m_iSessionID == 0)
//		return;
//
//	if (m_pdMainDlg)
//	{
//		CConferenceDlg *pDlg = (CConferenceDlg *)m_pdMainDlg;
//		int nScreenIndex = ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetFrameIndex();
//		m_pWndFullScreen = pDlg->GetWndFullScreen(nScreenIndex);
//		BOOL	bControl=GetKeyState(VK_CONTROL) & 0x80;
//		if (m_pWndFullScreen->GetFullScreenWnd() == this)
//		{
//			if (!m_bControl || bControl)
//			{
//				ExitFullScreen();
//				if (((pDlg->GetLocalUserInfo()->_iStatusFlag==ntPresideLogin)
//					||(pDlg->GetLocalUserInfo()->_iStatusFlag==ntWatchUser))
//					&&(pDlg->ConferenceWinLayoutSynchronization()))
//					pDlg->ToAllConferenceUserFullScreen(m_iSessionID, m_iCardNo, false);
//			}
//		}
//		else
//		{
//			if (!m_bControl || bControl)
//			{
//				FullScreen();			
//				if (((pDlg->GetLocalUserInfo()->_iStatusFlag==ntPresideLogin)
//					||(pDlg->GetLocalUserInfo()->_iStatusFlag==ntWatchUser))
//					&&(pDlg->ConferenceWinLayoutSynchronization()))
//					pDlg->ToAllConferenceUserFullScreen(m_iSessionID, m_iCardNo, true);
//			}
//		}
//	}
//}
//
//void CUserDlg::OnLockAvdio()
//{
//	((CConferenceDlg *)m_pdMainDlg)->SendLockAvdioMessage(m_iSessionID, m_iCardNo);
//}
//
//void CUserDlg::OnFullScreenCpture()
//{
//	if (GetFloatWnd() == this)
//	{
//		return ;
//	}
//
//	if (m_pdMainDlg)
//	{
//		CConferenceDlg *pDlg = (CConferenceDlg *)m_pdMainDlg;
//		int nScreenIndex = ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetFrameIndex();
//		m_pWndFullScreen = pDlg->GetWndFullScreen(nScreenIndex);
//		BOOL	bControl=GetKeyState(VK_CONTROL) & 0x80;
//		if (m_pWndFullScreen->GetFullScreenWnd() == this)
//		{
//			if (!m_bControl || bControl)
//			{
//				ExitFullScreen();
//
//				pDlg->ToAllConferenceUserFullScreen(m_iSessionID, m_iCardNo, false);
//
//				m_bFullScreenCpture = FALSE;
//			}
//		}
//		else
//		{
//			if (!m_bControl || bControl)
//			{
//				FullScreen();
//				pDlg->ToAllConferenceUserFullScreen(m_iSessionID, m_iCardNo, true);
//				m_bFullScreenCpture = TRUE;
//			}
//		}
//	}
//}
//
//// 视频显示模式菜单响应及接口调用	Add Han Huajie 2008/01/15
//void CUserDlg::VideoShowMode(VideoShowModeType nVideoShowMode)
//{
//	m_nVideoShowMode = nVideoShowMode;
//	ResizeControls();
//}
//
//void CUserDlg::OnVideoShowModeCut()				// 视觉比例切割显示
//{
//	VideoShowMode(ntVideoShowModeCut);
//}
//
//void CUserDlg::OnVideoShowModeFill()			// 视觉比例填补显示
//{
//	VideoShowMode(ntVideoShowModeFill);
//}
//
//void CUserDlg::OnVideoShowModeFull()			// 视频全景显示
//{
//	VideoShowMode(ntVideoShowModeFull);
//}
//// End Add
//
//void CUserDlg::OnSyncHronization()
//{
////	AfxMessageBox(_T("CUserDlg::OnSyncHronization"));
//	m_bSynchronization = !m_bSynchronization;
//	SetSynchronization(m_bSynchronization);
//}
//
//void CUserDlg::SetSynchronization(bool bEnableSyn)
//{
//	m_bSynchronization = bEnableSyn;
//
//	if (m_pAudioPlay)
//		m_pAudioPlay->EnableSyn(m_bSynchronization);
//}
//
//CWnd *CUserDlg::GetVideoWindow() const
//{
//	if (m_pVideoPlayer)
//		return CWnd::FromHandle(m_pVideoPlayer->GetHWnd());
//
//	return NULL;
//}
//
////////////////////////////////////////////////////////////////////////////
////add by tiger,2008.07.17
//
//void CUserDlg::Do_LButtonDown(UINT nFlags, CPoint point)
//{
//	if (!m_iZoomIn)
//	{
//		CBaseDlg::Do_LButtonDown(nFlags, point);
//		return;
//	}
//
//	CRect	rc;
//	GetClientRect(&rc);
//
//	if(m_pVideoPlayer){
//		CWnd *pDlgVideoWindow=GetVideoWindow();
//		if (!pDlgVideoWindow)
//		{
//			CBaseDlg::Do_LButtonDown(nFlags, point);
//			return;
//		}
//
//		HWND	hVideoWnd = pDlgVideoWindow->GetSafeHwnd();
//
//		CRect rcWindow;
//		::GetWindowRect(hVideoWnd, &rcWindow);
//		ScreenToClient(&rcWindow);
//		{	// 此处计算位置
//			SetWindowPosEx(rcWindow,rc,point);		
//		}
//		m_pVideoPlayer->SetWindowPosition(rcWindow.left,rcWindow.top, rcWindow.Width(), rcWindow.Height());
//	}
//
//	////标题栏
//	//if (m_pDlgAVInfo)
//	//{
//	//	m_pDlgAVInfo->SetWindowPos(NULL ,0,0,rc.Width(),12,SWP_NOACTIVATE);
//	//}
//
//	//视频控制		
//	if (m_pDlgYT)
//	{
//		m_pDlgYT->SetWindowPos(NULL ,0,rc.bottom-17,rc.Width(),17,SWP_NOACTIVATE);
//	}
//
//	ResetWindowRgn();
//
//	CBaseDlg::Do_LButtonDown(nFlags, point);
//}
////end add
////////////////////////////////////////////////////////////////////////////
//
//
////格式化标题栏，add by tiger,2008.09,27
//void CUserDlg::FormateTitlebar()
//{
//	CString text, str1;
//	if (GetFloatWnd() == this)
//	{
//		str1 =m_strFloat;
//	}
//
//	if (m_iCardNo > 0)
//	{
//		if (m_iCardNo==255)
//		{
//			text=_T("");
//		}
//		else
//		{
//			if (m_iCardNo == SCREEN_IS_VIDEO_NO)
//				text.Format(_T("%s %s"), m_strUserName, _T("S"));
//			else if (m_iCardNo == MEDIA_IS_VIDEO_NO)
//				text.Format(_T("%s %s"), m_strUserName, _T("M"));
//			else
//				text.Format(_T("%s %d"), m_strUserName, m_iCardNo+1);
//		}
//	}
//	else
//		text.Format(_T("%s"), m_strUserName);
//
//	////显示透明标题栏
//	//if (m_pdMainDlg && ((CConferenceDlg*)m_pdMainDlg)->GetINFOTrans() && m_pDlgAVInfo->IsWindowVisible()
//	//	&& m_pVideoPlayer != NULL && m_pVideoPlayer->HasVideo() )//lzl modified 2008.10.31
//	//{
//	//	m_pVideoPlayer->EnableTitle(TRUE);
//	//	m_pVideoPlayer->SetTitleText(text,((CConferenceDlg*)m_pdMainDlg)->GetTitleBarAlign());
//	//}//显示透明标题栏end
//	//else
//	{
//		if (m_pVideoPlayer)
//		{
//			m_pVideoPlayer->EnableTitle(FALSE);
//		}		
//		m_pDlgAVInfo->SetText(text);
//		SetTitleBarColor();//lzl modified 2008.10.31
//	}
//
//	ResetWindowRgn();
//}
//
//
////设置标题栏字体,字的颜色和背景色,	add by tiger,2008.09.27
//void CUserDlg::SetTitleFont(LOGFONT logfont,COLORREF crText,COLORREF crBk)
//{
//	if (m_pVideoPlayer)
//	{
//		m_pVideoPlayer->SetTitleFont(logfont,crText,crBk);
//	}	
//}
////end add
//
//void CUserDlg::SetLocalLoopBackTest(BOOL bLocalLoopBackTest)
//{
//	m_bLocalLoopBackTest = bLocalLoopBackTest;
//
//	if (m_pDlgAVInfo)
//	{
//		if (m_pDlgAVInfo->GetSafeHwnd())
//			m_pDlgAVInfo->DestroyWindow();
//
//		delete m_pDlgAVInfo;
//		m_pDlgAVInfo = NULL;
//	}
//}
//
//LRESULT CUserDlg::OnAudioSetMessage(WPARAM wParam, LPARAM lParam)
//{
//	CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//	if (NULL == pdMainDlg)
//		return 0L;
//
//	TConferenceUserInfo *pConferenceUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//	if (NULL == pConferenceUserInfo)
//		return 0L;
//
//	if (NULL == m_pAudioPlay)
//		return 0L;
//
//	if (m_pAudioSettingDlg && m_pAudioSettingDlg->GetSafeHwnd())
//	{
//		if (wParam)
//		{	// 确定
//
//			//麦克风
//			if (pConferenceUserInfo->_iUserMicType != 255)
//			{
//				int nIndex	= 0;
//				int nCodec	= 0;
//				int nCardNo = 0;
//				int nVolume = 0;
//				m_pAudioSettingDlg->GetAudioDate(nIndex,  nCodec, nCardNo, nVolume);
//
//				if (nCardNo == m_iCardNo)
//				{
//					pConferenceUserInfo->_iSoundDriverIndex = nIndex;
//					pConferenceUserInfo->_iUserMicType      = nCodec;
//
//					m_pAudioPlay->SetVolume(nVolume);
//				}
//
//				pdMainDlg->ChangUserMicVideoInfo(m_iSessionID, pConferenceUserInfo->_iSoundDriverIndex,
//					pConferenceUserInfo->_iUserMicType, NULL/*&pConferenceUserInfo->_aVideoCardInfo*/);
//			}
//		}
//		else
//		{	// 取消
//
//		}
//	}
//
//	if (m_pAudioSettingDlg)
//	{
//		if (m_pAudioSettingDlg->GetSafeHwnd())
//			m_pAudioSettingDlg->DestroyWindow();
//
//		delete m_pAudioSettingDlg;
//		m_pAudioSettingDlg = NULL;
//	}
//
//	return 0L;
//}
//
//LRESULT CUserDlg::OnVideoSetMessage(WPARAM wParam, LPARAM lParam)
//{
//	CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//	if (NULL == pdMainDlg)
//		return 0L;
//
//	TConferenceUserInfo *pConferenceUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//	if (NULL == pConferenceUserInfo)
//		return 0L;
//
//	if (m_pVideoSettingDlg && m_pVideoSettingDlg->GetSafeHwnd())
//	{
//		if (wParam)
//		{	// 确定
//			int	nCardNo			= 0;		
//			int	nDriverIndex	= 255;	
//			int	nCodec			= 0;		
//			int	nRatio			= 0;		
//			int	nQuality		= 0;		
//			int	nFrameRate		= 0;
//			BOOL bDenoise		= 0;
//
//			m_pVideoSettingDlg->GetVideoDate(nDriverIndex, nCodec, nRatio, nQuality, nFrameRate, bDenoise, nCardNo);
//
//			if (m_iCardNo == nCardNo)
//			{
//				CTVideoCardInfoArray aTempVideoCardInfoArray;
//				TVideoCardInfo*	ptVideoCardInfo = NULL;
//				ptVideoCardInfo = GetVideoCardSetting(pConferenceUserInfo->_aVideoCardInfo, nCardNo);
//				if (ptVideoCardInfo)
//				{
//					ptVideoCardInfo->_iVideoDriverIndex = nDriverIndex;
//					ptVideoCardInfo->_iUserCodeType     = nCodec;
//					ptVideoCardInfo->_iUserDisplayType  = nRatio;
//					ptVideoCardInfo->_iUserPicQuality   = nQuality;
//					ptVideoCardInfo->_iUserFrame        = nFrameRate;
//					ptVideoCardInfo->_bUserRemoveConfusion = bDenoise;
//
//					aTempVideoCardInfoArray.Add(ptVideoCardInfo);
//				}
//
//				int iOldVideoDriverIndex = m_pVideoSettingDlg->GetOldDriverIndex();
//
//				if (ptVideoCardInfo && (iOldVideoDriverIndex != 255) && (iOldVideoDriverIndex != nDriverIndex))
//				{
//					int i=0;for ( i=0; i<pConferenceUserInfo->_aVideoCardInfo.GetSize(); i++)
//					{
//						TVideoCardInfo* ptVideoCardInfo1 = NULL;
//						ptVideoCardInfo1 = pConferenceUserInfo->_aVideoCardInfo.GetAt(i);
//						if ((ptVideoCardInfo1 != ptVideoCardInfo) && (nDriverIndex == ptVideoCardInfo1->_iVideoDriverIndex))
//						{
//							ptVideoCardInfo1->_iVideoDriverIndex = iOldVideoDriverIndex;
//							aTempVideoCardInfoArray.Add(ptVideoCardInfo1);
//							break;
//						}
//					}
//				}
//
//				pdMainDlg->ChangUserMicVideoInfo(m_iSessionID, pConferenceUserInfo->_iSoundDriverIndex,
//												pConferenceUserInfo->_iUserMicType, &aTempVideoCardInfoArray);
//			}
//		}
//		else
//		{	// 取消
//
//		}
//	}
//
//	if (m_pVideoSettingDlg)
//	{
//		if (m_pVideoSettingDlg->GetSafeHwnd())
//			m_pVideoSettingDlg->DestroyWindow();
//
//		delete m_pVideoSettingDlg;
//		m_pVideoSettingDlg = NULL;
//	}
//
//	return 0L;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 视频预设置	Add HHJ 2009/08/06
//void CUserDlg::OnWinUserVideoFormatSet()
//{
//	if (NULL == m_pConferenceWinDlg)
//		return;
//
//	((CConferenceWinDlg*)m_pConferenceWinDlg)->MenueWinUserVideoFormatSet(this);
//}
//
//void CUserDlg::OnWinVideoFormatSet()
//{
//	if (NULL == m_pConferenceWinDlg)
//		return;
//
//	TPreSettingInfo* ptPreSettingInfo = ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetWinPreSettingInfo(this);
//	if (NULL == ptPreSettingInfo)
//		return;
//
//	if (NULL == m_pWinVideoFormatSetDlg)
//	{
//		// AutoLockResource Lock;
//
//		m_pWinVideoFormatSetDlg = new CWinVideoFormatSetDlg(this);
//		m_pWinVideoFormatSetDlg->Create(CWinVideoFormatSetDlg::IDD, this);
//	}
//
//	if (m_pWinVideoFormatSetDlg->GetSafeHwnd())
//	{
//		m_pWinVideoFormatSetDlg->SetPreSettingInfo(ptPreSettingInfo);
//
//		CPoint		pp;
//		CRect		Wizardrc, rc;
//		m_pConferenceWinDlg->GetWindowRect(&rc);
//		m_pWinVideoFormatSetDlg->GetClientRect(&Wizardrc);
//		int nWizardWidth = Wizardrc.Width();
//		int nWizardHeigth = Wizardrc.Height();
//
//		::GetCursorPos(&pp);
//		if (pp.x + nWizardWidth >= rc.right && pp.y + nWizardHeigth >= rc.bottom)
//			m_pWinVideoFormatSetDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//		else
//		{
//			if (pp.x + nWizardWidth >= rc.right)
//				m_pWinVideoFormatSetDlg->SetWindowPos(NULL, rc.right-nWizardWidth-10, pp.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//			else
//			{
//				if (pp.y + nWizardHeigth >= rc.bottom)
//					m_pWinVideoFormatSetDlg->SetWindowPos(NULL, pp.x, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//				else
//					m_pWinVideoFormatSetDlg->SetWindowPos(NULL,pp.x,pp.y,0,0,SWP_SHOWWINDOW | SWP_NOSIZE);
//			}
//		}	
//	}
//
//}
//
//void CUserDlg::SetUsingWinVideoFormatInfo(TPreSettingInfo* ptPreSettingInfo)	// 应用视频设置格式
//{
//	if (SCREEN_IS_VIDEO_NO == m_iCardNo || MEDIA_IS_VIDEO_NO == m_iCardNo)
//		return;
//
//	if (ptPreSettingInfo)
//	{
//		if (ptPreSettingInfo->_bUseFlag)
//		{
//			CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//			if (NULL == pdMainDlg)
//				return;
//
//			TConferenceUserInfo *pConferenceUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//			if (NULL == pConferenceUserInfo)
//				return;
//
//			CTVideoCardInfoArray aTempVideoCardInfoArray;
//			TVideoDriverInfo* ptVideoDriverInfo = NULL;
//			TVideoCardInfo*	  ptVideoCardInfo   = NULL;
//			ptVideoCardInfo = GetVideoCardSetting(pConferenceUserInfo->_aVideoCardInfo, m_iCardNo);
//			if (NULL == ptVideoCardInfo)
//				return;
//
//			ptVideoDriverInfo = pConferenceUserInfo->_aVideoDriverInfo.GetAt(ptVideoCardInfo->_iVideoDriverIndex);
//			if (NULL == ptVideoDriverInfo)
//				return;
//
//			ptVideoCardInfo->_iUserCodeType			= ptPreSettingInfo->_iCodeType;
//
//			if (ptVideoDriverInfo->_bVideo_HDDevice)
//				ptVideoCardInfo->_iUserDisplayType  = ptPreSettingInfo->_iHDDisplayType;
//			else
//				ptVideoCardInfo->_iUserDisplayType  = ptPreSettingInfo->_iDisplayType;
//
//			ptVideoCardInfo->_iUserPicQuality		= ptPreSettingInfo->_iPicQuality;
//			ptVideoCardInfo->_iUserFrame			= ptPreSettingInfo->_iFrame;
//
//			aTempVideoCardInfoArray.Add(ptVideoCardInfo);
//
//			pdMainDlg->ChangUserMicVideoInfo(m_iSessionID, pConferenceUserInfo->_iSoundDriverIndex,
//				pConferenceUserInfo->_iUserMicType, &aTempVideoCardInfoArray);
//		}
//	}
//}
//
//LRESULT CUserDlg::OnWinVideoFormatSetMessage(WPARAM wParam, LPARAM lParam)	// 视频设置对话框确认消息
//{
//	if (NULL == m_pConferenceWinDlg)
//		return 0L;
//
//	if (1 == wParam)
//	{
//		if (m_pWinVideoFormatSetDlg)
//		{
//			((CConferenceWinDlg*)m_pConferenceWinDlg)->MenueWinVideoFormatSetDlg(this, m_pWinVideoFormatSetDlg->GetPreSettingInfo());
//		}
//	}
//
//	if (m_pWinVideoFormatSetDlg)
//	{
//		if (m_pWinVideoFormatSetDlg->GetSafeHwnd())
//			m_pWinVideoFormatSetDlg->DestroyWindow();
//
//		delete m_pWinVideoFormatSetDlg;
//		m_pWinVideoFormatSetDlg = NULL;
//	}
//
//	return 0L;
//}
//// End Add
////////////////////////////////////////////////////////////////////////////
//
//void CUserDlg::SetBkBmp(CBitmap* pBmp)
//{
//	//m_pBkBitmap = pBmp;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 视频详细信息 add HHJ 2009/08/24
//void CUserDlg::OnDetailInfoShow()
//{
//	ASSERT(m_pConferenceWinDlg);
//	if (NULL == m_pConferenceWinDlg)
//		return;
//
//	if (NULL == m_pDetailInfoDlg)
//	{
//		// AutoLockResource Lock;
//
//		m_pDetailInfoDlg = new CDetailInfoDlg(this);
//		m_pDetailInfoDlg->Create(CDetailInfoDlg::IDD, this);
//	}
//
//	if (m_pDetailInfoDlg && m_pDetailInfoDlg->GetSafeHwnd())
//	{
//		m_pDetailInfoDlg->SetInfoDate(m_strUserName, m_iCardNo);
//
//		CPoint		pp;
//		CRect		Wizardrc, rc;
//		m_pConferenceWinDlg->GetWindowRect(&rc);
//		m_pDetailInfoDlg->GetClientRect(&Wizardrc);
//		int nWizardWidth = Wizardrc.Width();
//		int nWizardHeigth = Wizardrc.Height();
//
//		::GetCursorPos(&pp);
//		if (pp.x + nWizardWidth >= rc.right && pp.y + nWizardHeigth >= rc.bottom)
//			m_pDetailInfoDlg->SetWindowPos(&CWnd::wndTop, rc.right-nWizardWidth-10, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//		else
//		{
//			if (pp.x + nWizardWidth >= rc.right)
//				m_pDetailInfoDlg->SetWindowPos(&CWnd::wndTop, rc.right-nWizardWidth-10, pp.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//			else
//			{
//				if (pp.y + nWizardHeigth >= rc.bottom)
//					m_pDetailInfoDlg->SetWindowPos(&CWnd::wndTop, pp.x, rc.bottom-nWizardHeigth-30, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//				else
//					m_pDetailInfoDlg->SetWindowPos(&CWnd::wndTop,pp.x,pp.y,0,0,SWP_SHOWWINDOW | SWP_NOSIZE);
//			}
//		}	
//	}
//}
//// 得到视频的详细信息
//void CUserDlg::GetAVdieoDetailInfo(unsigned long& ulWidth,			// 视频宽度
//												  unsigned long& ulHeight,			// 视频高度
//												  unsigned long& ulAudioBitrate,		// 音频码流
//												  unsigned long& ulAudioLost,			// 音频丢包
//												  unsigned long& ulVideoBitrate,		// 视频码流
//												  unsigned long& ulVideoLost,			// 视频丢包
//												  int& nVolume,						// 音量大小
//												  int& nVideoFrame)					// 视频帧率	
//{
//	ulAudioBitrate	= m_ulAudioBitrate;
//	ulAudioLost     = 0;
//	nVolume=m_nCurVolume;
//	if (m_pVideoPlayer)
//	{
//		if (m_pVideoPlayer->HasVideo())
//		{
//			VIDEO_DIS_SIZE tVideoSize;
//			m_pVideoPlayer->GetVideoSize(&tVideoSize);
//			ulWidth			= tVideoSize.width;
//			ulHeight		= tVideoSize.height;
//			ulVideoBitrate	= m_ulVideoBitrate;
//			ulVideoLost		= 0/*m_pVideoPlayer->GetVideoLostCount()*/;
//			nVideoFrame     = 15;
//			CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//			if (NULL == pdMainDlg)
//				return;
//			TConferenceUserInfo *pConferenceUserInfo = pdMainDlg->GetConferenceUserInfo(m_iSessionID);
//			if (NULL == pConferenceUserInfo)
//				return;
//			if (pConferenceUserInfo->_aVideoCardInfo.GetSize()>0)
//				nVideoFrame     = pConferenceUserInfo->_aVideoCardInfo.GetAt(m_iCardNo)->_iUserFrame;
//			else
//				nVideoFrame=0;
//			//nVideoFrame     =m_pVideoPlayer->GetVideoFrameRate();
//		}
//	}
//}
//
//LRESULT CUserDlg::OnWinDetailInfoMessage(WPARAM wParam, LPARAM lParam)
//{
//	if (m_pDetailInfoDlg)
//	{
//		if (m_pDetailInfoDlg->GetSafeHwnd())
//			m_pDetailInfoDlg->DestroyWindow();
//
//		delete m_pDetailInfoDlg;
//		m_pDetailInfoDlg = NULL;
//	}
//
//	return 0L;
//}
//// End Add
////////////////////////////////////////////////////////////////////////////
//
//
//// 创建音频的传输通道回调接口    
//// dwChannelNO:  音频的唯一标识，区分是发送的哪个音频流
//// lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
//void CUserDlg::CreateAudioChannelCallBack(DWORD dwChannelNO, LONG lContext)
//{
//	CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//	if (NULL == pdMainDlg)
//		return;
//
//	CDataInfoManage* pH323Manage = pdMainDlg->GetDataInfoManage();
//	if (NULL == pH323Manage)
//		return;
//
//	m_pISendAVdieoDataInfo = pH323Manage->CreateHLSendAVdieoDataInfo(this, dwChannelNO);
//
//	m_dwH323ChannelNO = dwChannelNO;
//
//	pdMainDlg->SetH323AudioAplayWnd(NULL);
//}
//
//// 创建视频的传输通道回调接口    
//// dwChannelNO:  视频的唯一标识，区分是发送的哪个视频流
//// lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
//void CUserDlg::CreateVideoChannelCallBack(DWORD dwChannelNO, LONG lContext) 
//{
//	CConferenceDlg *pdMainDlg = (CConferenceDlg*)m_pdMainDlg;
//	if (NULL == pdMainDlg)
//		return;
//
//	CDataInfoManage* pH323Manage = pdMainDlg->GetDataInfoManage();
//	if (NULL == pH323Manage)
//		return;
//
//	m_pISendAVdieoDataInfo = pH323Manage->CreateHLSendAVdieoDataInfo(this, dwChannelNO);
//
//	m_dwH323ChannelNO = dwChannelNO;
//
//	pdMainDlg->SetH323VideoAplayWnd(NULL);
//}
//
//// 关闭音频的传输通道回调接口(用于释放相应的发送或接受数据的对象)   
//// dwChannelNO:  音频的唯一标识，区分是关闭的哪个音频流
//// lContext:	应用程序上下文，由用户定义其作用，用于扩展
//void CUserDlg::CloseH323AudioChannelCallBack(DWORD dwChannelNO, LONG lContext)
//{
//	if (m_dwH323ChannelNO == dwChannelNO)
//	{
//		if (m_pISendAVdieoDataInfo)
//			m_pISendAVdieoDataInfo->ReleaseSendAudioDataInfo(dwChannelNO);
//
//		if (!m_bOpenVideo)
//		{
//			m_pISendAVdieoDataInfo = NULL;
//			m_dwH323ChannelNO = 0;
//		}
//	}
//}
//
//// 关闭视频的传输通道回调接口(用于释放相应的发送或接受数据的对象)     
//// dwChannelNO:  视频的唯一标识，区分是关闭的哪个视频流
//// lContext:	应用程序上下文，由用户定义其作用，用于扩展
//void CUserDlg::CloseH323VideoChannelCallBack(DWORD dwChannelNO, LONG lContext)
//{
//	if (m_dwH323ChannelNO == dwChannelNO)
//	{
//		if (m_pISendAVdieoDataInfo)
//			m_pISendAVdieoDataInfo->ReleaseSendVideoDataInfo(dwChannelNO);
//
//		if (!m_bOpenAudio)
//		{
//			m_pISendAVdieoDataInfo = NULL;
//			m_dwH323ChannelNO = 0;
//		}
//	}
//}
//
////输出音频数据包的回调
//void CUserDlg::OnIOAudioPlayDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples)
//{
//	if (m_pISendAVdieoDataInfo)
//		m_pISendAVdieoDataInfo->SetAudioData((BYTE*)pFrameData, nFrameLen, dSamples, m_dwH323ChannelNO);
//}
//
//void CUserDlg::WindowSelectedToJPG()			//拍照
//{
//	CString	strFilter = _T("JPEG (*.JPG;*.JPEG;*.PGE)|*.jpg||");
//
//	CFileDialog fileDlg(FALSE, _T("jpg"), NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,this);
//
//	if (fileDlg.DoModal() != IDOK)
//	{
//		return ;
//	}
//
//	//
//	if (m_pVideoPlayer)
//	{
//		USES_CONVERSION;
//		m_pVideoPlayer->CaptureToJPGFile(CT2A(fileDlg.GetPathName()));
//	}
//}
//
//void CUserDlg::OnToJPG()
//{
//	WindowSelectedToJPG();
//}


void CCUserWinDlgDlg::OnSize(UINT nType, int cx, int cy)
{
	CBaseDlg::OnSize(nType, cx, cy);
		m_drawingObject.ResetObject(cx,cy);

	// TODO: 在此处添加消息处理程序代码
}
