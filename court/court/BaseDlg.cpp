//basedlg.cpp
//

#include "stdafx.h"
#include "basedlg.h"
#include "ConferenceWinDlg.h"
//#include "DlgFullScreen.h"
//#include "ConferenceDlg.h"
//#include "DlgFloatWin.h"
//#include "MScreenInfo.h"
//#include "ConferenceConfig.h"
#include "DlgPMosaicScreenADScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBaseDlg, CDialog)
CBaseDlg::CBaseDlg(UINT nIDD,CWnd* pParent)
:CDialog(nIDD, pParent)
,m_iZoomIn(0)	//add by tiger,2008.07.17
,m_hCursor(NULL)	//add by tiger,2008.07.18
,m_bLocalLoopBackTest(FALSE)
,m_bIsSelected(false)
,m_dwH323ChannelNO(0)
,m_ulVideoBitrate(0)
,m_ulAudioBitrate(0)
,m_ulAudioBitrateSum(0)
{
	m_iIndex=0;
	m_pdMainDlg=NULL;
	m_strUserName="";
	m_iSessionID=0;				//会话ID
	m_iCardNo=255;				//用户视频卡号	0~12
	m_iFrameInfoType=ntFrameNull;	//框上显示的是哪种信息
	m_bDragFlg=FALSE;
    m_pWndFullScreen = NULL;
	m_bWatch=FALSE;
    m_bIsFullScreen = FALSE;
    m_pWndFullScreen = NULL;
//	m_bFloat = false;
    m_pConferenceWinDlg = NULL;
	m_bIsMyInceptVideo=FALSE;				//是否自己单接的视频
	m_bIsMyInceptSound=FALSE;				//是否自己单接的音频
	m_bShowCodeFlow = TRUE;
	m_bIsAvAdjust=false;
	m_bControl = FALSE;
	m_nVideoShowMode = ntVideoShowModeCut;

	//CConferenceConfig ConferenceConfig;
	//m_bSynchronization = ConferenceConfig.GetSynchronization();

	m_bOpenAudio=false;
	m_bOpenVideo=false;
}

CBaseDlg::~CBaseDlg(void)
{
}
BEGIN_MESSAGE_MAP(CBaseDlg, CDialog)
	ON_MESSAGE(WM_VIDEO_ON_DROP_NOTIFY,OnVideoOnDropNotify)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDBLCLK()
	//ON_COMMAND(IDM_CLOSE_USER, OnCloseUser)
	//ON_COMMAND(IDM_ZOOMIN, OnMenuZoomIn)	//add by tiger,2008.07.18
	//ON_COMMAND(IDM_REVERT, OnMenuRevert)	//add by tiger,2008.07.18
	//ON_COMMAND(ID_FLOAT_VIDEO,OnMoveWindowToPos)
	//ON_WM_SETCURSOR()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CBaseDlg::SetIndex(int iIndex)			//设置窗口号
{
	m_iIndex=iIndex+1;
}

void CBaseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Do_LButtonDown(nFlags, point);
	//CDialog::OnLButtonDown(nFlags, point);
}

void CBaseDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	Do_LButtonUp(nFlags, point);
    //CDialog::OnLButtonUp(nFlags, point);
}

void CBaseDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	Do_MouseMove(nFlags, point);
    //CDialog::OnMouseMove(nFlags, point);
}

void CBaseDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	Do_LButtonDbClick(nFlags, point);
	    
    //CDialog::OnMButtonDblClk(nFlags, point);
}

void CBaseDlg::SetMainDlg(CDialog *pdMainDlg)		//设主窗口
{
	m_pdMainDlg=pdMainDlg;
}
BOOL CBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_videoDropTarget.Register(this);
	m_videoDropTarget.m_hNotifyWnd = m_hWnd;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
// 响应用户拖动
LRESULT CBaseDlg::OnVideoOnDropNotify(WPARAM wParam, LPARAM lParam)
{
	char	*pData = (char*)wParam;
	int		nLen = lParam;

	//if (m_pdMainDlg)
	//	if (((CDlgPMosaicScreenADScreen*)(m_pdMainDlg))->IsIM())
	//	{
	//		GlobalFree(pData);
	//		return 0;
	//	}

	if (GetFullScreenFlag()||m_bIsAvAdjust)
	{
		GlobalFree(pData);
		return 0;
	}
		
	//if (GetFloatWnd() == this)
	//{
	//	GlobalFree(pData);
	//	return 0;
	//}

	if (pData[0] == DROP_VIDEO_TREE_TO_DLG)
	{
		((CConferenceWinDlg*)m_pConferenceWinDlg)->DropNotify(pData, nLen, m_iIndex);
		GlobalFree(pData);
		return 0;
	}
	unsigned long	ulSource = 0;
	CBaseDlg* pBaseDlg = NULL;

	memcpy(&ulSource, pData+1, 4);
	pBaseDlg = (CBaseDlg*)ulSource;

	if ((!pBaseDlg)||(!pBaseDlg->GetSafeHwnd()))
	{
		GlobalFree(pData);
		return 0;
	}

	if(pBaseDlg->GetFrameInfoType()==ntFrameNull)
	{
		GlobalFree(pData);
		return 0;
	}

	if (((pBaseDlg!=this) && (m_iIndex!=0)))
	{
		((CConferenceWinDlg*)m_pConferenceWinDlg)->DropNotify(pData, nLen, m_iIndex);
	}

	GlobalFree(pData);

	return 0;
}

void CBaseDlg::SetUserInfo(CString strInviteUserName,unsigned __int32 iSessionID,byte ucUserCardNo,FrameInfoType iFrameInfoType,BOOL bDragFlg)
{
	m_strUserName=strInviteUserName;
	m_iSessionID=iSessionID;
	m_iCardNo=ucUserCardNo;
	m_iFrameInfoType=iFrameInfoType;
	m_bDragFlg=bDragFlg;

	if (SCREEN_IS_VIDEO_NO == ucUserCardNo)
		m_nVideoShowMode = ntVideoShowModeFull;
}

void CBaseDlg::ResizeControls(void)
{
	//if (m_pConferenceWinDlg)
	//{
	//	if (m_bIsFullScreen)                 //要全屏
	//	{
	//		((CConferenceWinDlg*)(m_pConferenceWinDlg))->PictureInPictureChangeBack();
	//	}
	//	else
	//	{
	//		((CConferenceWinDlg*)(m_pConferenceWinDlg))->PictureInPictureResetWindowRgn();
	//	}
	//}
	
}

//void CBaseDlg::PictureInPictureFullScreen()
//{
//	if (m_pConferenceWinDlg)
//	{
//		((CConferenceWinDlg*)(m_pConferenceWinDlg))->PictureInPictureChangeBack();
//	}
//}
//
//void CBaseDlg::PictureInPictureExitFullScreen()
//{
//	if (m_pConferenceWinDlg)
//	{
//		((CConferenceWinDlg*)(m_pConferenceWinDlg))->PictureInPictureResetWindowRgn();
//	}
//}

byte CBaseDlg::GetIndex()					//得到窗口号
{
	return m_iIndex-1;
}

unsigned __int32 CBaseDlg::GetSessionID()				//会话ID
{
	return m_iSessionID;
}

byte CBaseDlg::GetUserCardNo()				//用户视频卡号	0~12
{
	return m_iCardNo;
}

FrameInfoType CBaseDlg::GetFrameInfoType()	//框上显示的是哪种信息
{
	return m_iFrameInfoType;
}
BOOL CBaseDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message != WM_KEYDOWN)
	{
		return CDialog::PreTranslateMessage( pMsg );
	}

	if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

CDialog *CBaseDlg::GetMainDlg()
{
	return m_pdMainDlg;
}

void CBaseDlg::Do_LButtonDown(UINT nFlags, CPoint point)
{
	BOOL bControlDown = GetKeyState(VK_CONTROL) & 0x80;
	if (!m_bIsFullScreen)
	{
		if (!bControlDown)
		{
			if (m_pdMainDlg)
			{
				((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->SetAllWindowSelected(false);
			}
			SetSelected(true);
		}
		else
		{
			SetSelected(!IsSelected());
		}
	}

	if (!m_pdMainDlg||(m_iFrameInfoType == ntFrameNull))
		return;

	//if (((CDlgPMosaicScreenADScreen*)(m_pdMainDlg))->IsIM())
	//	return;

  //  //这里处理屏幕共享
  //  if (((m_iFrameInfoType == ntVideoSound && m_iCardNo==SCREEN_IS_VIDEO_NO)||(m_iFrameInfoType == ntScreen)) && 
  //      m_pdMainDlg && 
  //      (((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->GetLocalMemberSessionID() != GetSessionID()))
  //  {
		//BOOL	bControl=GetKeyState(VK_CONTROL) & 0x80;
		//if (m_bControl && !bControl)
		//	return ;
  //  }

 	if (GetFullScreenFlag()||m_bIsAvAdjust)
		return;

	/*if (GetFloatWin())
	{
		if(GetFloatWnd() == this)
			return;
		if (m_iIndex == 0)
		{
			SetDragFlag(TRUE);
		}
	}
	else
	{
		if (m_iIndex == 0)
		{
			SetDragFlag(FALSE);
		}
	}	*/
	
	if ((m_iFrameInfoType != ntFrameNull) && IsAllowDragDrop())
	{
		if (m_iIndex!=0)
		{
			BEGIN_DROP(5);

			unsigned long	ulSource=(unsigned long)this;

			buffer[0] = DROP_VIDEO_DLG_TO_DLG;
			memcpy(buffer+1, &ulSource, 4);

			////模板控制器
			//if (((CDlgPMosaicScreenADScreen*)(m_pdMainDlg))->GetTemplateControlDlg())
			//	((CDlgPMosaicScreenADScreen*)(m_pdMainDlg))->GetTemplateControlDlg()->SetDragParam(buffer, 5);
			END_DROP;
		}
		//add by tiger,2008.08.12
		//增加本地视频到模板的拖动
		else
		{
			//if (GetFloatWin())
			//{
			//	CDlgPMosaicScreenADScreen *pDlgConferenceDlg = (CDlgPMosaicScreenADScreen *)m_pdMainDlg;
			//	ASSERT(pDlgConferenceDlg);
			//	TLocalUserInfo *pLocalUserInfo = pDlgConferenceDlg->GetLocalUserInfo();
			//	ASSERT(pLocalUserInfo);
			//	if ( pLocalUserInfo->_iStatusFlag == ntPresideLogin ||	//主持人
			//		pLocalUserInfo->_iStatusFlag == ntWatchUser ||	//监控人员
			//		pDlgConferenceDlg->IsProlocutor(pLocalUserInfo->_pUserInfo->_iSessionID))	//发言人
			//	{
			//		BEGIN_DROP(5);

			//		unsigned long	ulSource=(unsigned long)this;

			//		buffer[0] = DROP_VIDEO_LOCAL_TO_DLG;
			//		memcpy(buffer+1, &ulSource, 4);

			//		//模板控制器
			//		if (((CDlgPMosaicScreenADScreen*)(m_pdMainDlg))->GetTemplateControlDlg())
			//			((CDlgPMosaicScreenADScreen*)(m_pdMainDlg))->GetTemplateControlDlg()->SetDragParam(buffer, 5);
			//		END_DROP;
			//	}
			//}			
		}
		//end add
	}

}

void CBaseDlg::Do_LButtonUp(UINT nFlags, CPoint point)
{

}

void CBaseDlg::Do_MouseMove(UINT nFlags, CPoint point)
{

}

void CBaseDlg::Do_LButtonDbClick(UINT nFlags, CPoint point)
{
}

byte CBaseDlg::GetCardNo()
{
    return m_iCardNo;
}

void CBaseDlg::SetWatch()			//设监控
{
	m_bWatch=TRUE;
}
void CBaseDlg::CloseWatch()			//关闭监控
{
	m_bWatch=FALSE;
}

//
//void CBaseDlg::OpenFloatWindow(BOOL bIsDoubleScreen, unsigned int ulSrcSessionID)
//{
//	//双屏, 在屏幕上显示一个虚框
//	//单屏, 在指定的区域浮动显示视频
//	//
//
//	int wsStyle = (bIsDoubleScreen ? CDlgFloatWin::wsBorder : CDlgFloatWin::wsVideo);
//	GetFloatWin()->OpenFloat(this, wsStyle, 3);
//
//	ASSERT(m_pdMainDlg);
//	if (NULL == m_pdMainDlg)
//		return;
//
//	//权限
//	TLocalUserInfo *pUser = ((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->GetLocalUserInfo();
//	if (pUser)
//	{
//		if (ntPresideLogin == pUser->_iStatusFlag)
//		{
//			GetFloatWin()->ShowCloseButton(true);
//			GetFloatWin()->EnableResize(true);
//		}
//		else
//		{
//			GetFloatWin()->ShowCloseButton(false);
//			GetFloatWin()->EnableResize(false);
//		}
//	}
//}
//
//void CBaseDlg::FloatWindowTo(const CRect &rect, BOOL bIsDoubleScreen)
//{
//    GetFloatWin()->SetWindowPos(rect.left, rect.top, rect.Width(), rect.Height());
//}
//
//void CBaseDlg::CloseFloatWindow( BOOL bIsDoubleScreen )
//{
//    GetFloatWin()->CloseFloat();
//}

BOOL CBaseDlg::SetDragFlag(BOOL bFlag)
{
    BOOL bRet = m_bDragFlg;
    m_bDragFlg = bFlag;

    return bRet;
}

BOOL CBaseDlg::GetDragFlag() const
{
    return m_bDragFlg;
}

BOOL CBaseDlg::GetFullScreenFlag() const
{
    return m_bIsFullScreen;
}

BOOL CBaseDlg::SetFullScreenFlag(BOOL bFlag)
{
    BOOL bRet = m_bIsFullScreen;
    m_bIsFullScreen = bFlag;

    return bRet;
}

BOOL CBaseDlg::IsAllowDragDrop() const
{
    return m_bDragFlg;
}
BOOL CBaseDlg::DestroyWindow()
{
	m_videoDropTarget.m_hNotifyWnd = NULL;
	m_videoDropTarget.Revoke();


    return CDialog::DestroyWindow();
}

CString CBaseDlg::GetSource() const
{
    return m_strUserName;
}

void CBaseDlg::OnResizeVideoRect(int x, int y, int cx, int cy)
{
    ////TRACE(_T("CBaseDlg::OnResizeVideoRect"));
}
//
//CDlgFloatWin *CBaseDlg::GetFloatWin() const
//{
//    return ((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->GetFloatWinWnd();
//}
//
//CWnd *CBaseDlg::GetFloatWnd() const
//{
//	if (m_pdMainDlg)
//		return ((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->GetFloatWnd();
//
//	return NULL;
//}

BOOL CBaseDlg::Create(UINT nIDTemplet, CWnd* pParentWnd)
{
    m_pConferenceWinDlg = pParentWnd;
    return CDialog::Create(nIDTemplet, pParentWnd);
}

CWnd *CBaseDlg::SetConferenceWnd(CWnd* pParentWnd)
{
    CWnd *pOld = m_pConferenceWinDlg;
    m_pConferenceWinDlg = pParentWnd;

    return pOld;
}

CWnd *CBaseDlg::GetConferenceWnd() const
{
    return m_pConferenceWinDlg;
}

BOOL CBaseDlg::IsMyInceptVideo()				//是否自己单接的视频
{
	return m_bIsMyInceptVideo;
}
BOOL CBaseDlg::IsMyInceptSound()				//是否自己单接的音频
{
	return m_bIsMyInceptSound;
}

void CBaseDlg::SetIsMyInceptVideo(BOOL bIsMyInceptVideo)				//设置是否自己单接的视频
{
	m_bIsMyInceptVideo=bIsMyInceptVideo;
}

void CBaseDlg::SetIsMyInceptSound(BOOL bIsMyInceptSound)				//设置是否自己单接的音频
{
	m_bIsMyInceptSound=bIsMyInceptSound;
}

//void CBaseDlg::ExitFullScreen()
//{
//	//检查全屏, 如果是全屏, 则先关掉全屏
//	if (GetFullScreenFlag())
//	{
//		SetFullScreenFlag(FALSE);
//		if ((m_iCardNo==SCREEN_IS_VIDEO_NO)&&((m_iFrameInfoType==ntVideoSound) || (m_iFrameInfoType==ntScreen))&&
//			(m_iSessionID==((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->GetLocalMemberSessionID()))
//		{
//			::SetWindowRgn(m_pWndFullScreen->GetSafeHwnd(), NULL, TRUE);
//			((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->SetFullScreenCaptureFlag(false);
//			//if ((((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->IsBroadcastVideo(m_iSessionID,m_iCardNo))||(((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->IsBroadcastSound(m_iSessionID,m_iCardNo)))
//			//	((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->CloseFullScreen();
//		}
//		int nScreenIndex = ((CConferenceWinDlg *)m_pConferenceWinDlg)->GetFrameIndex();
//		if (m_pWndFullScreen)
//		{
//			((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->ShowScreenShowModeDlgMainBake(nScreenIndex,SWP_SHOWWINDOW);
//			m_pWndFullScreen->RestoreScreen();
//			m_pWndFullScreen = NULL;
//
//			((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->ShowAllDlg();
//		}
//#ifdef USES_CHATUI	//即时通讯 2007-12-17 IM
//		if(NULL != m_pdMainDlg)
//		{
//			((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->ResizeChatDlg(m_iSessionID);
//		}
//#endif
//		
//		((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->ApplyVideoFormatSetting(m_iIndex-1,nScreenIndex,m_iIndex-1,nScreenIndex);
//		PictureInPictureExitFullScreen();
//		((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->FullScreenTM(nScreenIndex,m_iIndex-1,FALSE);
//	}
//}
//
//void CBaseDlg::ExitFloatWindow()
//{
//	if (GetFloatWin()&&(GetFloatWnd() == this))
//	{
//		m_pdMainDlg->SendMessage(WM_CLOSE_FLOAT_WIN);
//		GetFloatWin()->CloseFloat();
//	}
//}


//add by lzl,2008.10.20
void CBaseDlg::ShowTitleBar(BOOL bShowTitleBar)				//显示标题栏
{
	m_bShowTitleBar = bShowTitleBar;
}
//end add

void CBaseDlg::ShowCodeFlow(BOOL bShowCodeFlow)				//显示码流
{
	m_bShowCodeFlow = bShowCodeFlow;
}

void CBaseDlg::VideoShowMode(VideoShowModeType nVideoShowMode)	// 视频显示模式	Add Han Huajie 2008/01/15
{
	m_nVideoShowMode = nVideoShowMode;
}

//void CBaseDlg::FullScreen()
//{
//	if (GetFloatWnd() == this)    //浮动窗口
//	{
//		return ;
//	}
//
//	if (m_pdMainDlg)
//	{
//		CDlgPMosaicScreenADScreen *pDlg = (CDlgPMosaicScreenADScreen *)m_pdMainDlg;
//		if ((m_iCardNo==SCREEN_IS_VIDEO_NO)&&(m_iFrameInfoType==ntVideoSound || m_iFrameInfoType == ntScreen))
//		{
//			pDlg->SetFullScreenCaptureFlag(true);
//		}
//		int nScreenIndex = ((CConferenceWinDlg *)m_pConferenceWinDlg)->GetFrameIndex();
//		m_pWndFullScreen = pDlg->GetWndFullScreen(nScreenIndex);
//
//		if (m_pWndFullScreen->GetFullScreenWnd() != this)
//		{
//			CRect rect,rectMain;
//			GetWindowRect(rect);
//			m_pConferenceWinDlg->GetWindowRect(rectMain);
//			rect.top=rect.top-rectMain.top;
//			rect.left=rect.left-rectMain.left;
//			rect.right=rect.right-rectMain.left;
//			rect.bottom=rect.bottom-rectMain.top;
//
//			//if ((m_iCardNo==SCREEN_IS_VIDEO_NO)&&(m_iFrameInfoType==ntVideoSound)&&(m_iSessionID==((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->GetLocalMemberSessionID()))
//			//	if ((((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->IsBroadcastVideo(m_iSessionID,m_iCardNo))||(((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->IsBroadcastSound(m_iSessionID,m_iCardNo)))
//			//		pDlg->SetFullScreen();
//
//			m_pWndFullScreen->ShowFullScreen(this, nScreenIndex, rect);
//			((CDlgPMosaicScreenADScreen *)m_pdMainDlg)->ShowScreenShowModeDlgMainBake(nScreenIndex,SWP_HIDEWINDOW);
//
//			pDlg->ApplyVideoFormatSetting(m_iIndex-1,nScreenIndex,m_iIndex-1,nScreenIndex);
//
//			PictureInPictureFullScreen();
//		}
//		pDlg->FullScreenTM(nScreenIndex,m_iIndex-1,TRUE);
//		if (pDlg->GetTemplateControlDlg())
//			pDlg->GetTemplateControlDlg()->SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE); 
//	}
//	ResizeControls();
//
//
//}

//float CBaseDlg::GetK()
//{
//	float k=1.0;
//
//	return k;
//}
//
//float CBaseDlg::GetWidth_K()
//{
//	float k=1.0;
//
//	if (m_pdMainDlg == NULL)
//		return k;
//
//	TLocalUserInfo* pLocalUserDlg = ((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->GetLocalUserInfo();
//	
//	if (pLocalUserDlg && m_iIndex == 0)
//	{
//		switch(pLocalUserDlg->_iScreenType[0])
//		{
//		case ntScreen4x3:
//			k=((float)4/(float)3)/((float)GetDesktopWidth(ntSCREEN_ONE)/(float)GetDesktopHeight(ntSCREEN_ONE));
//			break;
//		case ntScreen16x9:
//			k=((float)16/(float)9)/((float)GetDesktopWidth(ntSCREEN_ONE)/(float)GetDesktopHeight(ntSCREEN_ONE));
//			break;
//		case ntScreen16x10:
//			k=((float)16/(float)10)/((float)GetDesktopWidth(ntSCREEN_ONE)/(float)GetDesktopHeight(ntSCREEN_ONE));
//			break;
//		default:
//			k=((float)4/(float)3)/((float)GetDesktopWidth(ntSCREEN_ONE)/(float)GetDesktopHeight(ntSCREEN_ONE));
//			break;
//		}
//
//		return k;
//	}
//
//	if (pLocalUserDlg && m_pConferenceWinDlg->GetSafeHwnd())
//	{
//		CWnd *pParentWnd = GetParent();
//
//		if (pParentWnd)
//		{
//			CRect rc;
//			pParentWnd->GetClientRect(&rc);
//
//			switch(pLocalUserDlg->_iScreenType[((CConferenceWinDlg*)m_pConferenceWinDlg)->GetFrameIndex()])
//			{
//			case ntScreen4x3:
//				k=((float)4/(float)3)/((float)rc.Width()/(float)rc.Height());
//				break;
//			case ntScreen16x9:
//				k=((float)16/(float)9)/((float)rc.Width()/(float)rc.Height());
//				break;
//			case ntScreen16x10:
//				k=((float)16/(float)10)/((float)rc.Width()/(float)rc.Height());
//				break;
//			default:
//				k=((float)4/(float)3)/((float)rc.Width()/(float)rc.Height());
//				break;
//			}
//		}
//	}
//
//	return k;
//}
//
//int CBaseDlg::GetDesktopWidth(ScreenNOType ntScreenNO)
//{
//	CMScreenInfo MScreenInfo;
//	return MScreenInfo.GetDesktopWidth((short)ntScreenNO);
//}
//
//int CBaseDlg::GetDesktopHeight(ScreenNOType ntScreenNO)
//{
//	CMScreenInfo MScreenInfo;
//	return MScreenInfo.GetDesktopHeight((short)ntScreenNO);
//}
//void CBaseDlg::OnCloseUser()
//{
//	if (GetRecordFlag())
//		return;
//
//	if (((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->IsIM())
//	{
//#ifdef USES_CHATUI
//		((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CancelCall(m_iSessionID);
//#endif
//		((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CloseCalling(m_iSessionID);
//		return;
//	}
//
//	//
//	if (m_iCardNo == SCREEN_IS_VIDEO_NO)
//	{
//		m_bControl = FALSE;
//	}
//
//	bool bAudioBroadcasted=false;
//	bool bVideoBroadcasted=false;
//
//	if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndVideo(m_iIndex-1))
//	{
//		bVideoBroadcasted=true;
//		((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CloseBroadcastVideo(m_iSessionID,m_iCardNo);
//	}
//
//	if (((CConferenceWinDlg*)m_pConferenceWinDlg)->IsBroadcastWndSound(m_iIndex-1))
//	{
//		bAudioBroadcasted=true;
//		((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CloseBroadcastSound(m_iSessionID,m_iCardNo);
//	}
//
//	if ((m_pdMainDlg)&&(((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->GetLocalMemberSessionID()!=m_iSessionID))
//	{
//		if (IsHaveVideo()&&IsHaveSound())
//		{
//			if (!bVideoBroadcasted)
//			{
//				((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CloseVideo(m_iSessionID,m_iCardNo);
//			}
//
//			if (!bAudioBroadcasted)
//			{
//				((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CloseInceptSound(m_iSessionID,m_iCardNo);
//			}
//		}
//		else
//		{
//			if (IsHaveVideo())
//			{
//				if (!bVideoBroadcasted)
//					((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CloseVideo(m_iSessionID,m_iCardNo);
//				return;
//			}
//			if (IsHaveSound())
//			{
//				if (!bAudioBroadcasted)
//					((CDlgPMosaicScreenADScreen*)m_pdMainDlg)->CloseInceptSound(m_iSessionID,m_iCardNo);
//				return;
//			}
//		}
//	}
//}

void CBaseDlg::SetSynchronization(bool bEnableSyn)
{
	//m_bSynchronization = bEnableSyn;
}

//////////////////////////////////////////////////////////////////////////
//add by tiger,2008.07.18
////“放大”或“缩小” 菜单
//void CBaseDlg::OnMenuZoomIn()
//{
//	if (1 == m_iZoomIn)	//如果目前是放大,则指针图标设为缩小
//	{
//		m_iZoomIn = 2;
//		m_hCursor = LoadCursor(AfxGetInstanceHandle(), (LPCTSTR)IDC_CURSOR3);
//		if	(m_hCursor)
//		{
//			::SetCursor(m_hCursor);
//		}
//	}else	//如果目前不是放大,则指针图标设为放大
//	{
//		m_iZoomIn = 1;
//		m_hCursor = LoadCursor(AfxGetInstanceHandle(), (LPCTSTR)IDC_CURSOR2);
//		if	(m_hCursor)
//		{
//			::SetCursor(m_hCursor);
//		}
//	}
//}
////“还原” 菜单
//void CBaseDlg::OnMenuRevert()
//{
//	m_iZoomIn = 0;	
//	m_hCursor = NULL;//LoadCursor(AfxGetInstanceHandle(), (LPCTSTR)IDC_ARROW);
//	PostMessage(WM_SETCURSOR);
//	ResizeControls();
//}
//
//BOOL CBaseDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	if	(m_hCursor!=NULL)
//	{
//		::SetCursor(m_hCursor);
//		return TRUE;
//	}
//	return __super::OnSetCursor(pWnd, nHitTest, message);
//}

void CBaseDlg::SetWindowPosEx(CRect &rcWindow, CRect rc, CPoint point)
{
	//放大
	if (1==m_iZoomIn)
	{
		if ((point.x - rc.left) < rc.Width()/4)
		{
			rcWindow.right += rc.Width()/4;				
		}else
		{
			if ((rc.right - point.x) < rc.Width()/4)
			{
				rcWindow.left -= rc.Width()/4;
			}else
			{
				rcWindow.left -= rc.Width()/8;
				rcWindow.right += rc.Width()/8;
			}
		}
		if ((point.y - rc.top) < rc.Height()/4)
		{
			rcWindow.bottom += rc.Height()/4;
		}else
		{
			if ((rc.bottom - point.y) < rc.Height()/4)
			{
				rcWindow.top -= rc.Height()/4;
			}else
			{
				rcWindow.top -= rc.Height()/8;
				rcWindow.bottom += rc.Height()/8;
			}
		}
	}else if(2==m_iZoomIn)	//缩小
	{
		rcWindow.left += rc.Width()/8;
		rcWindow.right -= rc.Width()/8;
		if (rcWindow.Width() > rc.Width())
		{
			if (rcWindow.left > rc.left)
			{
				rcWindow.left = rc.left;
				rcWindow.right -= rc.Width()/8;
			}else
			{
				if (rcWindow.right < rc.right)
				{
					rcWindow.right = rc.right;
					rcWindow.left += rc.Height()/8;
				}
			}					
		}else
		{
			rcWindow.left = rc.left;
			rcWindow.right = rc.right;
		}
		rcWindow.top += rc.Height()/8;
		rcWindow.bottom -= rc.Height()/8;
		if (rcWindow.Height() > rc.Height())
		{
			if (rcWindow.top > rc.top)
			{
				rcWindow.top = rc.top;
				rcWindow.bottom -= rc.Height()/8;
			}else
			{
				if (rcWindow.bottom < rc.bottom)
				{
					rcWindow.bottom = rc.bottom;
					rcWindow.top += rc.Height()/8;
				}
			}
		}else
		{
			rcWindow.top = rc.top;
			rcWindow.bottom = rc.bottom;
		}

	}
}
//end add 
//////////////////////////////////////////////////////////////////////////

//void CBaseDlg::OnMoveWindowToPos()
//{
//	bool bValue = false;
//
//	//只有2屏上的视频才能浮动, 并且不是全屏窗口
//	if (!GetFullScreenFlag() &&
//		((CConferenceWinDlg *)m_pConferenceWinDlg)->GetFrameIndex() != 0
//		) 
//	{
//		//权限
//		CDlgPMosaicScreenADScreen *pDlgConferenceDlg = (CDlgPMosaicScreenADScreen *)m_pdMainDlg;
//		ASSERT(pDlgConferenceDlg);
//		TLocalUserInfo *pLocalUserInfo = pDlgConferenceDlg->GetLocalUserInfo();
//		ASSERT(pLocalUserInfo);
//
//		switch(pLocalUserInfo->_iStatusFlag)
//		{
//		case ntPresideLogin :       bValue = true;          //主持人恒有控制权限
//			break;
//		case ntWatchUser:   //监控人员
//			if (pLocalUserInfo->_pConferenceInfo)
//			{
//				bValue = pLocalUserInfo->_pConferenceInfo->_bWatchUserControl;
//			}
//			break;
//		}
//	}
//
//	if (bValue)
//	{
//		if (!GetFloatWin() || !GetFloatWin()->IsWindowVisible())  //打开浮动窗口
//		{
//			m_pdMainDlg->PostMessage(WM_OPEN_FLOAT_WIN, m_iSessionID, m_iCardNo);
//		}
//		else    //关闭浮动窗口
//		{
//			ASSERT(m_pdMainDlg);
//			m_pdMainDlg->PostMessage(WM_CLOSE_FLOAT_WIN);
//		}
//	}
//}

void CBaseDlg::SetSelected(bool bSelect)
{
	//m_bIsSelected = bSelect;
	if (m_pConferenceWinDlg && m_iIndex>0)
	{
		((CConferenceWinDlg*)m_pConferenceWinDlg)->SetWondowSelected(m_iIndex - 1, bSelect);
		RedrawWindow();
		//Invalidate();
		ResizeControls();

		if (m_nVideoShowMode == ntVideoShowModeFill)
		{
			ShowWindow(SW_HIDE);
			ShowWindow(SW_SHOW);
		}
	}
}

bool CBaseDlg::IsSelected(void)
{
	if (m_pConferenceWinDlg && m_iIndex > 0 && !m_bIsFullScreen)
	{
		return ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetWindowSelected(m_iIndex - 1);
	}
	return false;
}

void CBaseDlg::DrawSelectedFrame(CDC *pDC)
{
	CRect T_rect;
	GetClientRect(T_rect);

	if (IsSelected())
	{
		const int nLineWidth = 2;
		CRect rectTop = T_rect;
		rectTop.bottom = nLineWidth;

		CRect rectBottom = T_rect;
		rectBottom.top = rectBottom.bottom - nLineWidth;

		CRect rectLeft = T_rect;
		rectLeft.right = nLineWidth;
		CRect rectRight = T_rect;
		rectRight.left = rectRight.right - nLineWidth;

		pDC->FillRect(&rectTop, &CBrush(RGB(255,0,0)));
		pDC->FillRect(&rectBottom, &CBrush(RGB(255,0,0)));
		pDC->FillRect(&rectLeft, &CBrush(RGB(255,0,0)));
		pDC->FillRect(&rectRight, &CBrush(RGB(255,0,0)));
	}
}