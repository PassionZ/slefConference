// ConferenceWinDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "Conference.h"
#include "ConferenceWinDlg.h"
#include "TempletArithmetic/TempletArithmeticFactory.h"

#include "UserDlg.h"	// Added by ClassView
//#include "ConferenceDlg.h"
//#include "AVLocalVideoCaptureDlg.h"
#include "Resource/utilBase/util.h"
//#include "wbdlg.h"
//#include "LocalMediaCaptureDlg.h"
//#include "AVLocalVideoRGBCaptureDlg.h"
//#include "AVLocalVideoScreenCaptureDlg.h"
//#include "TMDlg.h"
#include "BaseDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConferenceWinDlg dialog


CConferenceWinDlg::CConferenceWinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConferenceWinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConferenceWinDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pTempletArithmetic=NULL;
	m_ptLocalUserInfo=NULL;
	m_iFrameIndex=0;
	m_pConferenceDlg=NULL;
	m_bWatch=FALSE;
	m_szbSelect = NULL;

	m_bShowDlg =false;



}

void CConferenceWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConferenceWinDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConferenceWinDlg, CDialog)
	//{{AFX_MSG_MAP(CConferenceWinDlg)
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOMMAND()
	//	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConferenceWinDlg message handlers


BOOL CConferenceWinDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//不在任务栏上显示
	//::SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, WS_EX_TOOLWINDOW)

	//在CChildView类视图中加入ＷＭ－CREATE消息的处理函数
	GetGestureConfig(&m_gestureConfig);

	// 只有旋转不是默认启用
	m_gestureConfig.EnableRotate();

	SetGestureConfig(&m_gestureConfig);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CConferenceWinDlg::DestroyWindow() 
{
	CloseAllWindow();

	//RemoveWinPreSettingInfo();

	return CDialog::DestroyWindow();
}
BOOL CConferenceWinDlg::OnGesturePan(CPoint ptFrom, CPoint ptTo)
{
	int dx = ptTo.x - ptFrom.x;
	int dy = ptTo.y - ptFrom.y;
	if (dx != 0 || dy != 0)
	{
		m_drawingObject.Move(dx, dy);
		RedrawWindow();
	}
	return TRUE;
}
BOOL CConferenceWinDlg::OnGestureZoom(CPoint ptCenter, long lDelta)
{
	if ((m_pCurrentGestureInfo->dwFlags & GF_BEGIN) == GF_BEGIN)
	{
		m_dblZoomRatioStart = m_dblZoomRatioTotal = lDelta;
	}
	else if (lDelta != 0)
	{
		m_dblZoomRatioTotal += lDelta;
		double zoomFactor = (double)m_dblZoomRatioTotal / m_dblZoomRatioStart;
		m_drawingObject.Zoom(zoomFactor, ptCenter.x, ptCenter.y);
		m_dblZoomRatioStart = m_dblZoomRatioTotal;
		RedrawWindow();
	}
	return TRUE;
}

BOOL CConferenceWinDlg::OnGestureRotate(CPoint ptCenter, double dblAngle)
{
	if ((m_pCurrentGestureInfo->dwFlags & GF_BEGIN) == GF_BEGIN)
	{
		// 创建旋转中心
		m_ptCenter = ptCenter;
	}
	else if (dblAngle != 0.)
	{
		m_drawingObject.Rotate(dblAngle * PI / 100.0, m_ptCenter.x, m_ptCenter.y);
		RedrawWindow();
	}
	return TRUE;
}
BOOL CConferenceWinDlg::OnGesturePressAndTap(CPoint ptFirstFinger, long lDelta)
{
	if ((m_pCurrentGestureInfo->dwFlags & GF_BEGIN) != 0)
	{
		m_drawingObject.ShiftColor();
		RedrawWindow();
	}
	return TRUE;
}
BOOL CConferenceWinDlg::OnGestureTwoFingerTap(CPoint ptCenter)
{
	m_drawingObject.TogleDrawDiagonals();
	RedrawWindow();
	return TRUE;
}
CWnd *CConferenceWinDlg::GetBaseDlg(int iBaseDlgNo)
{
	CBaseDlg *pBaseDlg = NULL;
	pBaseDlg = (CBaseDlg*)m_aWinInfoArray.GetAt(iBaseDlgNo)->_pdDialogInf;
	return pBaseDlg;
}

void CConferenceWinDlg::CloseAllWindow() 
{
	TWinInfo *ptTempWinInfo;
	CDialog *pdTempDlg;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		ptTempWinInfo=m_aWinInfoArray.GetAt(i);
		delete ptTempWinInfo->_ptVideoSoundInfo;
		pdTempDlg=(CDialog*)ptTempWinInfo->_pdDialogInf;
		if (m_pConferenceDlg && ((CBaseDlg*)pdTempDlg)->GetUserCardNo())
		{
			m_pConferenceDlg->SetWindowRgn(NULL,TRUE);
		}
		pdTempDlg->DestroyWindow();
		delete pdTempDlg;
		delete ptTempWinInfo;
	}
	m_aWinInfoArray.RemoveAll();

	if (m_szbSelect)
	{
		delete []m_szbSelect;
		m_szbSelect = NULL;
	}

	if (m_pTempletArithmetic)
	{
		delete m_pTempletArithmetic;
		m_pTempletArithmetic=NULL;
	}
}

void CConferenceWinDlg::SetTemplateInfo(byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType)
{
	m_iWinClass=iWinClass;			//屏种类	1，2，3第几个种类
	m_bWinTemplate=bWinTemplate;		//屏模板模式	0：不显示所有,1：为显示所有
	m_iWinNumber=iWinNumber;			//屏数量	
	m_iWinType=iWinType;				//屏类型
}

void CConferenceWinDlg::InitConferenceWinDlg()
{
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitTempletArithmetic();
	CreateWin();
	//InitWinPreSettingInfo();
	InitConferenceDlg();
}

void CConferenceWinDlg::InitTempletArithmetic()
{
	CTempletArithmeticFactory cTempTempletArithmeticFactory;
	if (m_pTempletArithmetic)
		delete m_pTempletArithmetic;
	switch(m_iWinClass)
	{
	case ntFree:
		m_pTempletArithmetic=cTempTempletArithmeticFactory.CreateTempletArithmetic(TEMPLETFREE_LOGIC);
		break;
	case ntNormal:
		m_pTempletArithmetic=cTempTempletArithmeticFactory.CreateTempletArithmetic(TEMPLETNORMAL_LOGIC);
		break;
	case nt16x9:
		m_pTempletArithmetic=cTempTempletArithmeticFactory.CreateTempletArithmetic(ID16x9TEMPLETNORMALID_LOGIC);
		break;
	default:
		//AV_MessageBox(_T("MESSAGE_BOX_ERROR_DATABASE_TEMPLET"), m_hWnd);
		m_pTempletArithmetic=cTempTempletArithmeticFactory.CreateTempletArithmetic(TEMPLETFREE_LOGIC);
		m_iWinClass=1;
		m_iWinType=1;
		m_iWinNumber=1;
	}

	CRect rect;
	GetWindowRect(&rect);
	m_pTempletArithmetic->SetScreenIndex(1,rect);
	m_pTempletArithmetic->SetType(m_iWinType,m_iWinNumber);

}

void CConferenceWinDlg::CreateWin()
{
	// 1. 计算正在使用中的 VideoWindow 的个数 A
	// 2. 和新模板的 VideoWindow 的个数 B 进行比较
	// 3. 如果 A > B, 则给出提示: "请关闭视频", 退出操作;

	TWinInfo *ptWinInfo = NULL;

	if (m_aWinInfoArray.GetSize()==m_pTempletArithmetic->GetWindowCount())
		return;

	if (m_aWinInfoArray.GetSize()<m_pTempletArithmetic->GetWindowCount())
	{
		for (int i=m_aWinInfoArray.GetSize();i<m_pTempletArithmetic->GetWindowCount();i++)
		{
			// AutoLockResource Lock;

			CCUserWinDlgDlg *pdUserDlg=new CCUserWinDlgDlg;
			pdUserDlg->Create(IDD_USER_DIALOG, this);
			pdUserDlg->SetIndex(i);
			pdUserDlg->SetMainDlg(m_pConferenceDlg);
			//pdUserDlg->SetBkBmp(m_pUserDlgBkBmp);
			//if(RS_FLAG == 1)//此功能（默认显示标题栏）为定制 。add by lzl,2008.10.20
			//	pdUserDlg->ShowTitleBar(m_ptLocalUserInfo->_bShowTitleBar);	
			//pdUserDlg->ShowCodeFlow(m_ptLocalUserInfo->_bShowCodeFlow);
			ptWinInfo=new TWinInfo;
			ptWinInfo->_pdDialogInf=pdUserDlg;
			ptWinInfo->_iSessionID=0;
			ptWinInfo->_iFrameInfoType=ntFrameNull;
			ptWinInfo->_ptVideoSoundInfo=new TVideoSoundInfo;
			ptWinInfo->_ptVideoSoundInfo->_iUserCardNo=255;
			ptWinInfo->_ptVideoSoundInfo->_bSound=false;
			ptWinInfo->_ptVideoSoundInfo->_bVideo=false;
			int nsize=	m_aWinInfoArray.GetSize();
			m_aWinInfoArray.Add(ptWinInfo);
		}


	}
	else
	{
		//注意: 要从后向前记录, 在删除的时候会影响 m_aWinInfoArray 的长度
		int nDeleteCount = m_aWinInfoArray.GetSize() - m_pTempletArithmetic->GetWindowCount();
		for (int j = m_aWinInfoArray.GetSize(); (j > 0 && nDeleteCount > 0); j--)
		{
			//这里可以直接删除, 在 SwapVideoWindowWhenChangeConferenceTemplet 已经做过处理了
			ptWinInfo = m_aWinInfoArray.GetAt(j-1);
			delete ptWinInfo->_ptVideoSoundInfo;

			ptWinInfo->_pdDialogInf->DestroyWindow();
			delete ptWinInfo->_pdDialogInf;
			delete ptWinInfo;
			m_aWinInfoArray.RemoveAt(j-1);

			nDeleteCount -= 1;
		}
	}

	if (m_szbSelect)
	{
		delete []m_szbSelect;
		m_szbSelect = NULL;
	}

	int nSize = m_aWinInfoArray.GetSize();
	m_szbSelect = new bool[nSize];
	for (int i = 0; i < nSize; i++)
	{
		m_szbSelect[i] = false;
	}
}

void CConferenceWinDlg::InitConferenceDlg()				//初始化会议窗口
{
	CRect rect,Mainrect;
	TWinInfo *ptTempWinInfo;

	GetWindowRect(Mainrect);

	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		ptTempWinInfo=m_aWinInfoArray.GetAt(i);
		m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);
		rect=ptTempWinInfo->_rcScreen;
		rect.left-=Mainrect.left;
		rect.right-=Mainrect.left;
		rect.top-=Mainrect.top;
		rect.bottom-=Mainrect.top;
		ptTempWinInfo->_pdDialogInf->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width() , rect.Height() , SWP_SHOWWINDOW);
		//ptTempWinInfo->_pdDialogInf->RedrawWindow();
		ptTempWinInfo->_rcScreen=rect;

		ptTempWinInfo->_pdDialogInf->ShowWindow(SW_HIDE);
	}
	////如果是画中画，要将大窗口挖空
	//if (m_pTempletArithmetic->GetIsPictureInPicture())
	//{
	//	CRect rectBig;
	//	m_pTempletArithmetic->GetWndRect(0, rectBig);
	//	rectBig.left -= Mainrect.left;
	//	rectBig.right -= Mainrect.left;
	//	CRect rectSmall;
	//	m_pTempletArithmetic->GetWndRect(1, rectSmall);
	//	rectSmall.left -= Mainrect.left;
	//	rectSmall.right -= Mainrect.left;
	//	CRgn rgnBig;
	//	CRgn rgnSmall;
	//	VERIFY(rgnBig.CreateRectRgn(rectBig.left, rectBig.top, rectBig.right, rectBig.bottom));
	//	VERIFY(rgnSmall.CreateRectRgn(rectSmall.left, rectSmall.top, rectSmall.right, rectSmall.bottom));
	//	CRgn rgn;
	//	VERIFY(rgn.CreateRectRgn(0,0, 50, 50));
	//	rgn.CombineRgn(&rgnBig, &rgnSmall, RGN_DIFF);
	//	ptTempWinInfo=m_aWinInfoArray.GetAt(0);
	//	ptTempWinInfo->_pdDialogInf->SetWindowRgn(rgn, TRUE);
	//}
	//ptTempWinInfo=m_aWinInfoArray.GetAt(1);
	//ptTempWinInfo->_pdDialogInf->MoveWindow(0,0,0,0);
}


int CConferenceWinDlg::GetFreeWinNumber()
{
	int iWinNumber=0;

	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
		if (m_aWinInfoArray.GetAt(i)->_iFrameInfoType==ntFrameNull)
			iWinNumber++;

	return iWinNumber;
}



CTWinInfoArray *CConferenceWinDlg::GetWinInfoArray()				//得到窗口信息数组
{
	return &m_aWinInfoArray;
}


BOOL CConferenceWinDlg::GetAddWndIndex(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte &ucUserWndIndex,byte ucUserCardNo)	const //得到增加广播的窗口号
{
	TWinInfo *ptTempWinInfo;
	int i=0;
	for (i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		ptTempWinInfo=m_aWinInfoArray.GetAt(i);
		if ((ptTempWinInfo->_iFrameInfoType==iFrameInfoType)&&(ptTempWinInfo->_iSessionID==iSessionID)&&(ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo==ucUserCardNo))
		{
			ucUserWndIndex=i;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CConferenceWinDlg::GetWndForSessionIndex(FrameInfoType iFrameInfoType,unsigned __int32 & iSessionID,byte ucUserWndIndex,byte ucUserCardNo)	const //得到增加广播的窗口号
{
	TWinInfo *ptTempWinInfo;
	int i=0;
	for (i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		ptTempWinInfo=m_aWinInfoArray.GetAt(ucUserWndIndex);
		if ((ptTempWinInfo->_iFrameInfoType==iFrameInfoType) &&(ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo==ucUserCardNo))
		{
			iSessionID=ptTempWinInfo->_iSessionID;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CConferenceWinDlg::GetFreeWndIndex(byte &ucUserWndIndex)	//得到空的窗口号
{
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		if (m_aWinInfoArray.GetAt(i)->_iFrameInfoType==ntFrameNull)
		{
			ucUserWndIndex=i;
			return TRUE;
		}
	}
	return FALSE;
}


void CConferenceWinDlg::SetFrameIndex(int iFrameIndex)			//设置屏号
{
	m_iFrameIndex=iFrameIndex;
	if (iFrameIndex != 0 )
	{
		ModifyStyle(WS_CHILD,WS_POPUP);
	}
}

void CConferenceWinDlg::ShowWin(int iWndIndex,CWnd* pWnd)				//显示视频窗口
{
	TRACE("CConferenceWinDlg::ShowWin begin\n");
	TWinInfo *ptTempWinInfo=m_aWinInfoArray.GetAt(iWndIndex);

	//#ifdef USES_CHATUI	//即时通讯 2007-12-17 IM
	//	BOOL bIM = (NULL != m_pConferenceDlg) && !((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->IsIM();
	//	if(bIM)
	//	{
	//		pWnd->SetParent(this);
	//		pWnd->SetWindowPos(&wndTop, ptTempWinInfo->_rcScreen.left, ptTempWinInfo->_rcScreen.top, ptTempWinInfo->_rcScreen.Width(), ptTempWinInfo->_rcScreen.Height(), SWP_SHOWWINDOW | SWP_NOACTIVATE);
	//	/*	FrameInfoType enFrameType = ptTempWinInfo->_iFrameInfoType;
	//		int nCardID = ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo;
	//		CString strMemberName = ((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->GetSource();
	//		((CDlgPMosaicScreenADScreen*)(m_pConferenceDlg))->GetTemplateControlDlg()->GetTMDlg(m_iFrameIndex)->GetParentWindow(iWndIndex)->SetFrameInfoTypeAndCardID(enFrameType, nCardID, strMemberName);*/
	//	}
	//
	//	((CBaseDlg*)(pWnd))->SetIndex(iWndIndex);
	//
	//	if (ptTempWinInfo->_iFrameInfoType == ntVideoSound && ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo==SCREEN_IS_VIDEO_NO && ptTempWinInfo->_iSessionID==m_ptLocalUserInfo->_pUserInfo->_iSessionID && !GetRecordFlag())
	//		((CBaseDlg*)ptTempWinInfo->_pdDialogInf)->ResizeControls();
	//
	//	if(bIM)
	//	{
	//		ShowConferenceUserDlg();
	//	}
	//#else
	//BOOL bInConference = (NULL != m_pConferenceDlg) && !((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->IsIM();
	//if (bInConference)
	//{
	//	FrameInfoType enFrameType = ptTempWinInfo->_iFrameInfoType;
	//	int nCardID = ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo;
	//	CString strMemberName = ((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->GetSource();
	//	if (((CDlgPMosaicScreenADScreen*)(m_pConferenceDlg))->GetTemplateControlDlg())
	//		((CDlgPMosaicScreenADScreen*)(m_pConferenceDlg))->GetTemplateControlDlg()->GetTMDlg(m_iFrameIndex)->GetParentWindow(iWndIndex)->SetFrameInfoTypeAndCardID(enFrameType, nCardID, strMemberName);
	//}
	pWnd->SetParent(this);
	pWnd->SetWindowPos(&wndTop, ptTempWinInfo->_rcScreen.left, ptTempWinInfo->_rcScreen.top, ptTempWinInfo->_rcScreen.Width(), ptTempWinInfo->_rcScreen.Height(), SWP_SHOWWINDOW | SWP_NOACTIVATE);

	((CBaseDlg*)(pWnd))->SetIndex(iWndIndex);

	if (ptTempWinInfo->_iFrameInfoType == ntVideoSound && ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo==SCREEN_IS_VIDEO_NO && ptTempWinInfo->_iSessionID==m_ptLocalUserInfo->_pUserInfo->_iSessionID )
		((CBaseDlg*)ptTempWinInfo->_pdDialogInf)->ResizeControls();

	//if (bInConference)
	//	ShowConferenceUserDlg();
	//#endif
	TRACE("CConferenceWinDlg::ShowWin end\n");
}


void CConferenceWinDlg::CreateNewWin(int iWndIndex)				//建新空窗口
{
	// AutoLockResource Lock;

	CCUserWinDlgDlg *pdUserDlg=new CCUserWinDlgDlg(this);
	pdUserDlg->Create(CCUserWinDlgDlg::IDD, this);
	pdUserDlg->SetIndex(iWndIndex);
	pdUserDlg->SetMainDlg(m_pConferenceDlg);
	//pdUserDlg->SetBkBmp(m_pUserDlgBkBmp);
	//pdUserDlg->ShowCodeFlow(m_ptLocalUserInfo->_bShowCodeFlow);
	TWinInfo *tWinInfo=m_aWinInfoArray.GetAt(iWndIndex);
	tWinInfo->_pdDialogInf=pdUserDlg;
	tWinInfo->_iFrameInfoType=ntFrameNull;
	tWinInfo->_ptVideoSoundInfo->_iUserCardNo=255;
	tWinInfo->_ptVideoSoundInfo->_bSound=false;
	tWinInfo->_ptVideoSoundInfo->_bVideo=false;

	ShowWin(iWndIndex,pdUserDlg);
}

void CConferenceWinDlg::SetConferenceDlg(CDialog *pConferenceDlg)		//设置主窗口指针
{
	m_pConferenceDlg=pConferenceDlg;
}
//
//void CConferenceWinDlg::OpenInfoWin(unsigned __int32 iSessionID,byte ucWndIndex,CWnd* pWnd,FrameInfoType iFrameInfoType)	//打开xx区
//{
//	TWinInfo *ptTempWinInfo=m_aWinInfoArray.GetAt(ucWndIndex);
//
//	if (pWnd)
//	{
//		BOOL bDragFlg=FALSE;
//		if ((m_ptLocalUserInfo->_iStatusFlag==ntPresideLogin)||(m_ptLocalUserInfo->_iStatusFlag==ntWatchUser)||(((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->IsSpeak())||(((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->IsIM()))
//			bDragFlg=TRUE;
//		ptTempWinInfo->_iSessionID=iSessionID;
//		ptTempWinInfo->_iFrameInfoType=iFrameInfoType;
//		ptTempWinInfo->_pdDialogInf->DestroyWindow();
//		delete ptTempWinInfo->_pdDialogInf;
//		ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo=255;
//		if (iFrameInfoType == ntScreen)
//			ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo = SCREEN_IS_VIDEO_NO;
//		ptTempWinInfo->_pdDialogInf=(CDialog*)pWnd;
//		((CBaseDlg*)ptTempWinInfo->_pdDialogInf)->SetIndex(ucWndIndex);
//		((CBaseDlg*)ptTempWinInfo->_pdDialogInf)->SetMainDlg(m_pConferenceDlg);
//        ((CBaseDlg*)ptTempWinInfo->_pdDialogInf)->SetConferenceWnd(this);
//        ((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->SetUserInfo(_T(""),iSessionID,ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo,iFrameInfoType,bDragFlg);
//		if (((CDlgPMosaicScreenADScreen *)m_pConferenceDlg)->GetConferenceRecordFactory())
//			((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->StartConferenceRecord();
//		if (m_ptLocalUserInfo->_iStatusFlag==ntWatchUser)
//			((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->SetWatch();
//		ShowWin(ucWndIndex,pWnd);
//	}
//}

CWnd*CConferenceWinDlg::CloseInfoWin(byte ucWndIndex)							//关闭xx区
{
	TWinInfo *ptTempWinInfo=m_aWinInfoArray.GetAt(ucWndIndex);
	ptTempWinInfo->_iSessionID=0;
	ptTempWinInfo->_iFrameInfoType=ntFrameNull;
	CWnd*pWnd=ptTempWinInfo->_pdDialogInf;
	((CBaseDlg*)pWnd)->SetIndex(0);
	CreateNewWin(ucWndIndex);
	return pWnd;
}

void CConferenceWinDlg::SwapWhoToWndPosition(byte ucDragUserWndIndex,byte ucDragUserFrameIndex,byte ucUserWndIndex)			//广播拖动谁
{
	//((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->SwapWhoToWndPosition(ucDragUserWndIndex,ucDragUserFrameIndex,ucUserWndIndex,m_iFrameIndex);
}

void CConferenceWinDlg::CloseWin(byte ucWndIndex)			//关闭窗口
{
	TWinInfo *ptWinInfo=m_aWinInfoArray.GetAt(ucWndIndex);
	if (ptWinInfo->_iFrameInfoType==ntVideoSound)
	{
		CWnd *pWnd;
		pWnd=CloseInfoWin(ucWndIndex);
		if (pWnd)
		{
			pWnd->DestroyWindow();
			delete pWnd;
			pWnd=NULL;
		}
	}
}

byte CConferenceWinDlg::GetFrameIndex()										//得到屏号
{
	return m_iFrameIndex;
}


BOOL CConferenceWinDlg::OnEraseBkgnd(CDC* pDC)
{


	CRect T_rect;
	GetClientRect(T_rect);


	//pDC->SetTextColor(COLOR_USER_FRAME_INDEX_DLG);

	//pDC->FrameRect(T_rect, &CBrush(COLOR_USER_FRAME_DLG));
	pDC->FillSolidRect(T_rect.left+1,T_rect.top+1,T_rect.Width()-2,T_rect.Height()-2,COLOR_USER_BACK_DLG);

	//pDC->SetBkMode(TRANSPARENT);
	CRect rect/*,Mainrect*/;
	//  CRect rectarray[5];    

	TWinInfo *ptTempWinInfo;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		ptTempWinInfo=m_aWinInfoArray.GetAt(i);
		//m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);
		rect=ptTempWinInfo->_rcScreen;
		//rect.left-=Mainrect.left;
		//rect.right-=Mainrect.left;
		//rect.top-=Mainrect.top;
		//rect.bottom-=Mainrect.top;
		//ptTempWinInfo->_pdDialogInf->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width() , rect.Height() , SWP_SHOWWINDOW);
		//ptTempWinInfo->_pdDialogInf->RedrawWindow();
		//ptTempWinInfo->_rcScreen=rect;

		//rectarray[i] = rect;

		pDC->FrameRect(rect, &CBrush(COLOR_USER_FRAME_DLG));
		/*	pDC->SetTextColor(COLOR_USER_FRAME_INDEX_DLG);
		pDC->FrameRect(rect, &CBrush(COLOR_USER_FRAME_DLG));
		pDC->FillSolidRect(rect.left+1,rect.top+1,rect.Width()-2,rect.Height()-2,COLOR_USER_BACK_DLG);*/
	}

	////pDC->SetTextColor(COLOR_USER_FRAME_INDEX_DLG);
	//pDC->FrameRect(rectarray[1], &CBrush(COLOR_USER_FRAME_DLG));
	//pDC->FrameRect(rectarray[2], &CBrush(COLOR_USER_FRAME_DLG));
	//pDC->FrameRect(rectarray[3], &CBrush(COLOR_USER_FRAME_DLG));
	//pDC->FrameRect(rectarray[4], &CBrush(COLOR_USER_FRAME_DLG));
	//pDC->FrameRect(rectarray[5], &CBrush(COLOR_USER_FRAME_DLG));
	//pDC->FrameRect(rectarray[0], &CBrush(COLOR_USER_FRAME_DLG));

	//pDC->FillSolidRect(rectarray[0].left+1,rectarray[0].top+1,rectarray[0].Width()-2,rectarray[0].Height()-2,COLOR_USER_BACK_DLG);
	//pDC->FillSolidRect(rectarray[1].left+1,rectarray[1].top+1,rectarray[1].Width()-2,rectarray[1].Height()-2,COLOR_USER_BACK_DLG);
	//pDC->FillSolidRect(rectarray[2].left+1,rectarray[2].top+1,rectarray[2].Width()-2,rectarray[2].Height()-2,COLOR_USER_BACK_DLG);
	//pDC->FillSolidRect(rectarray[3].left+1,rectarray[3].top+1,rectarray[3].Width()-2,rectarray[3].Height()-2,COLOR_USER_BACK_DLG);
	//pDC->FillSolidRect(rectarray[4].left+1,rectarray[4].top+1,rectarray[4].Width()-2,rectarray[4].Height()-2,COLOR_USER_BACK_DLG);
	//pDC->FillSolidRect(rectarray[5].left+1,rectarray[5].top+1,rectarray[5].Width()-2,rectarray[5].Height()-2,COLOR_USER_BACK_DLG);


	if (m_iWinType == 37 || m_iWinType == 38)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		//m_pTempletArithmetic->GetFreeRect(&rcClient);
		pDC->FillSolidRect(rcClient,RGB(0,0,0));
	}

	if (m_pConferenceDlg)
	{
		/*CWnd *pWnd=((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->GetFloatWnd();
		if (pWnd)
		for ( i=0;i<m_aWinInfoArray.GetSize();i++)
		{
		TWinInfo *ptTempWinInfo=m_aWinInfoArray.GetAt(i);
		if ((ptTempWinInfo->_pdDialogInf==pWnd)&&(ptTempWinInfo->_iFrameInfoType==ntVideoSound || ptTempWinInfo->_iFrameInfoType==ntScreen))
		{
		pDC->FillSolidRect(ptTempWinInfo->_rcScreen,RGB(0,0,255));
		return TRUE;
		}
		}*/
	}
	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}

void CConferenceWinDlg::GetBigWindows(int iBigWindows[3])						//得到大窗口
{
	if (m_pTempletArithmetic)
	{
		m_pTempletArithmetic->GetBigWindows(iBigWindows);
	}
}

void CConferenceWinDlg::SetWatch()			//设监控
{
	CBaseDlg *pdTempDlg;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		pdTempDlg=(CBaseDlg*)(m_aWinInfoArray.GetAt(i)->_pdDialogInf);
		pdTempDlg->SetWatch();
	}
}
void CConferenceWinDlg::CloseWatch()			//关闭监控
{
	CBaseDlg *pdTempDlg;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		pdTempDlg=(CBaseDlg*)(m_aWinInfoArray.GetAt(i)->_pdDialogInf);
		pdTempDlg->CloseWatch();
	}
}

int CConferenceWinDlg::GetInUseWinCount()
{
	int nRet = 0;
	int i=0;for ( i=0; i<m_aWinInfoArray.GetSize(); i++)
	{
		if (m_aWinInfoArray.GetAt(i)->_iFrameInfoType!= ntFrameNull)
		{
			nRet++;
		}
	}

	return nRet;
}

void CConferenceWinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//过滤 Alt-F4
	if (!((nID & 0xFFF0)==SC_CLOSE))
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}



UINT CConferenceWinDlg::GetFreeWnd(byte **pWinArray) const
{
	UINT nRet = 0;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		if (m_aWinInfoArray.GetAt(i)->_iFrameInfoType==ntFrameNull)
		{
			if (pWinArray)
			{
				(*pWinArray)[nRet] = i;
			}

			nRet++;
		}
	}

	return nRet;
}


//add by lzl,2008.10.20
void CConferenceWinDlg::ShowTitleBar(BOOL bShowTitleBar)
{
	CBaseDlg *pdTempDlg;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		pdTempDlg=(CBaseDlg*)(m_aWinInfoArray.GetAt(i)->_pdDialogInf);
		pdTempDlg->ShowTitleBar(bShowTitleBar);
	}
}
//void CConferenceWinDlg::FullScreen(unsigned __int32 iSessionID,byte iCardNo,BOOL bFull,FrameInfoType iFrameInfoType)
//{
//	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
//	{
//		TWinInfo *ptTempWinInfo=m_aWinInfoArray.GetAt(i);
//		if ((ptTempWinInfo->_iFrameInfoType==iFrameInfoType)&&(iSessionID == ptTempWinInfo->_iSessionID)&&(ptTempWinInfo->_ptVideoSoundInfo->_iUserCardNo==iCardNo))
//		{
//			if (bFull)
//				((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->FullScreen();
//			else
//				((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->ExitFullScreen();
//			return;
//		}
//	}
//}
//
//void CConferenceWinDlg::FullScreen(BOOL bFull)
//{
//	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
//	{
//		TWinInfo *ptTempWinInfo=m_aWinInfoArray.GetAt(i);
//		//if (ptTempWinInfo->_iFrameInfoType==ntVideoSound)
//		{
//			if (bFull)
//				((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->FullScreen();
//			else
//				((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->ExitFullScreen();
//		}
//	}
//}


void CConferenceWinDlg::DropNotify(char	*pData,int nLen,byte nWndIndex)		//响应拖动
{
	if (m_pConferenceDlg)
		((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->DropNotify(pData,nLen,m_iFrameIndex,nWndIndex);
}


//设置标题栏字体	add by tiger,2008.09.27
void CConferenceWinDlg::SetTitleFont(LOGFONT logFont_Big,COLORREF crText_Big,COLORREF crBk_Big)
{
	CBaseDlg *pBaseDlg;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		pBaseDlg=(CBaseDlg*)(m_aWinInfoArray.GetAt(i)->_pdDialogInf);
		pBaseDlg->SetTitleFont(logFont_Big, crText_Big, crBk_Big);
	}
}

//{{add by tiger,2009.06.24

void CConferenceWinDlg::SetScreenRect(CRect rc)
{
	if (m_pTempletArithmetic)
	{
		m_pTempletArithmetic->SetScreenIndex(1,rc);
	}
}
//end add}}

void CConferenceWinDlg::SetWondowSelected(byte iIndex, bool bSelect)
{
	if (0 <= iIndex && iIndex < m_aWinInfoArray.GetSize())
	{
		m_szbSelect[iIndex] = bSelect;
	}

	//if (m_pTempletArithmetic)
	//{
	//	m_pTempletArithmetic->SetWindowSelected(iIndex,bSelect);
	//}
}

bool CConferenceWinDlg::GetWindowSelected(byte iIndex)
{
	if (0 <= iIndex && iIndex < m_aWinInfoArray.GetSize())
	{
		return m_szbSelect[iIndex];
	}

	if (iIndex == 0)
	{
		TRACE(_T("CConferenceWinDlg::GetWindowSelected(%d)=%d"), iIndex, m_szbSelect[iIndex]);
	}

	//if (m_pTempletArithmetic && iIndex >= 0)
	//{
	//	return m_pTempletArithmetic->GetWindowSelected(iIndex);
	//}

	return false;
}

void CConferenceWinDlg::SetAllWindowSelected(bool bSelect)
{
	TWinInfo *ptTempWinInfo;
	int i=0;for ( i=0; i<m_aWinInfoArray.GetSize(); i++)
	{
		ptTempWinInfo = m_aWinInfoArray.GetAt(i);
		if (ptTempWinInfo)
		{
			((CBaseDlg*)(ptTempWinInfo->_pdDialogInf))->SetSelected(bSelect);
		}
	}

}



BOOL CConferenceWinDlg::PreTranslateMessage(MSG* pMsg)
{
	//if (pMsg && (WM_KEYDOWN == pMsg->message))
	//{
	//	if (pMsg->wParam == VK_ESCAPE)
	//	{
	//		if (((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->IsFullScreenTemplet())
	//			((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->FullScreenTemplet(false);

	//		return TRUE;
	//	}

	//	if (pMsg->wParam == VK_RETURN)
	//	{
	//		return TRUE;
	//	}
	//}

	//if (pMsg && (WM_KEYDOWN == pMsg->message))
	//{
	//	if (m_pConferenceDlg)
	//		((CDlgPMosaicScreenADScreen*)m_pConferenceDlg)->OnCaptureKeyDownMessage(pMsg);
	//}

	if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CConferenceWinDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect T_rect;

	GetClientRect(T_rect);


	//pDC->SetTextColor(COLOR_USER_FRAME_INDEX_DLG);

	//pDC->FrameRect(T_rect, &CBrush(COLOR_USER_FRAME_DLG));
	//pDC->FillSolidRect(T_rect.left+1,T_rect.top+1,T_rect.Width()-2,T_rect.Height()-2,COLOR_USER_BACK_DLG);

	//pDC->SetBkMode(TRANSPARENT);
	//CRect rect/*,Mainrect*/;
	//CRect rectarray[5];    

	//TWinInfo *ptTempWinInfo;
	//int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	//{
	//	ptTempWinInfo=m_aWinInfoArray.GetAt(i);
	//	m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);
	//	rect=ptTempWinInfo->_rcScreen;
	//	//rect.left-=Mainrect.left;
	//	//rect.right-=Mainrect.left;
	//	//rect.top-=Mainrect.top;
	//	//rect.bottom-=Mainrect.top;
	//	//ptTempWinInfo->_pdDialogInf->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width() , rect.Height() , SWP_SHOWWINDOW);
	//	//ptTempWinInfo->_pdDialogInf->RedrawWindow();
	//	//ptTempWinInfo->_rcScreen=rect;

	////rectarray[i] = rect;

	//	//pDC->SetTextColor(COLOR_USER_FRAME_INDEX_DLG);
	//dc.FrameRect(rect, &CBrush(COLOR_USER_FRAME_DLG));
	//	dc.FillSolidRect(rect.left+1,rect.top+1,rect.Width()-2,rect.Height()-2,COLOR_USER_BACK_DLG);
	//}


	//计算输出位置( 居中 )
	/*  CSize rc = pDC->GetTextExtent( m_strText) ;
	int x = (T_rect.Width()-rc.cx)/2;
	int y = (T_rect.Height()-rc.cy)/2;

	if (newFont.CreatePointFont(250, _T("黑体")))
	{
	pOldFont=pDC->SelectObject(&newFont);
	pDC->TextOut(2, 2, m_strText);
	pDC->SelectObject(pOldFont);
	}*/
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	DrawSelectedFrame(&dc);
	m_drawingObject.Paint(&dc);

}


void CConferenceWinDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	m_drawingObject.ResetObject(cx,cy);

	// TODO: 在此处添加消息处理程序代码
}


void CConferenceWinDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bShowDlg =true;

	//TWinInfo *ptTempWinInfo;
	//int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	//{
	//	ptTempWinInfo=m_aWinInfoArray.GetAt(i);
	//	m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);

	//	ptTempWinInfo->_pdDialogInf->ShowWindow(SW_SHOW);
	//}

	CDialog::OnMouseMove(nFlags, point);
}


void CConferenceWinDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bShowDlg =false;

	//TWinInfo *ptTempWinInfo;
	//int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	//{
	//	ptTempWinInfo=m_aWinInfoArray.GetAt(i);
	//	m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);

	//	ptTempWinInfo->_pdDialogInf->ShowWindow(SW_HIDE);
	//}

	CDialog::OnMouseLeave();
}


void CConferenceWinDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Do_LButtonDown(nFlags, point);

	CDialog::OnLButtonDown(nFlags, point);
}
void CConferenceWinDlg::Do_LButtonDown(UINT nFlags, CPoint point)
{
	BOOL bControlDown = GetKeyState(VK_CONTROL) & 0x80;
	{
		CRect rectPoint;

		TWinInfo *ptTempWinInfo;
		int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
		{
			ptTempWinInfo=m_aWinInfoArray.GetAt(i);
			//m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);
			rectPoint=ptTempWinInfo->_rcScreen;
			if(rectPoint.PtInRect(point))
			{
				//m_bSelect = true;
				if (!bControlDown)
				{
					/*((CConferenceWinDlg*)m_pConferenceWinDlg)->*/SetAllWindowSelected(  false);
					/*((CConferenceWinDlg*)m_pConferenceWinDlg)->*/SetWondowSelected(i, true);
				}
				else
				{
					/*((CConferenceWinDlg*)m_pConferenceWinDlg)->*/SetWondowSelected(i, !GetWindowSelected(i));
				}
				RedrawWindow();	//m_bSelect = false;
				return;
			}
		}


	}

}

void CConferenceWinDlg::DrawSelectedFrame(CDC *pDC)
{
	CRect T_rect;

	TWinInfo *ptTempWinInfo;
	int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	{
		ptTempWinInfo=m_aWinInfoArray.GetAt(i);
		if (GetWindowSelected(i))
		{
			T_rect = ptTempWinInfo->_rcScreen;
			const int nLineWidth = 2;
			CRect rectTop = T_rect;
			rectTop.bottom =rectTop.top- nLineWidth;

			CRect rectBottom = T_rect;
			rectBottom.top = rectBottom.bottom - nLineWidth;

			CRect rectLeft = T_rect;
			rectLeft.right = rectLeft.left-nLineWidth;
			CRect rectRight = T_rect;
			rectRight.left = rectRight.right - nLineWidth;

			pDC->FillRect(&rectTop, &CBrush(RGB(255,0,0)));
			pDC->FillRect(&rectBottom, &CBrush(RGB(255,0,0)));
			pDC->FillRect(&rectLeft, &CBrush(RGB(255,0,0)));
			pDC->FillRect(&rectRight, &CBrush(RGB(255,0,0)));
		}
	}

}
void CConferenceWinDlg::Do_LButtonUp(UINT nFlags, CPoint point)
{

}