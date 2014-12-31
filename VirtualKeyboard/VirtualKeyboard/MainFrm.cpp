// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VirtualKeyboard.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    m_wndView.Bind(&m_kb);
    m_hForground = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

    CSize sz = m_kb.getSize();
    cs.cx = sz.cx + ( GetSystemMetrics(SM_CXEDGE) + GetSystemMetrics(SM_CXSIZEFRAME) ) * 2;
    cs.cy = sz.cy +   GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYCAPTION)
                  + ( GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CXSIZEFRAME) ) * 2;

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		  | WS_MINIMIZEBOX | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.dwExStyle |= WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_APPWINDOW ;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if(m_hForground == NULL)
    {
        m_hForground = ::GetForegroundWindow();
        ModifyStyleEx(WS_EX_NOACTIVATE,0);
        SetForegroundWindow();
    }
    CFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void CMainFrame::OnNcMouseMove(UINT nHitTest, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if(m_hForground != NULL)
    {
        ::SetForegroundWindow(m_hForground);
        ModifyStyleEx(0,WS_EX_NOACTIVATE);
        m_hForground = NULL;
    }
    CFrameWnd::OnNcMouseMove(nHitTest, point);
}
