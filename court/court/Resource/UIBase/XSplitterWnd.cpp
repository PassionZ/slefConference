// XSplitterWnd.cpp : implementation file
//

#include "stdafx.h"
#include "XSplitterWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SPLITTER_COLOR			RGB(133, 133, 133)
#define BACK_COLOR				RGB(218, 218, 218)

/////////////////////////////////////////////////////////////////////////////
// CXSplitterWnd

CXSplitterWnd::CXSplitterWnd()
{
	m_Parent		=		NULL;
	m_iUp			=		-1;
	m_iDown			=		-1;
	m_clrBk			=		SPLITTER_COLOR;
	m_nTop			=		0;
	m_nBottom		=		0;
}

CXSplitterWnd::~CXSplitterWnd()
{
	m_lstUp.RemoveAll	();
	m_lstDown.RemoveAll	();
}


BEGIN_MESSAGE_MAP(CXSplitterWnd, CWnd)
	//{{AFX_MSG_MAP(CXSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CXSplitterWnd message handlers

void CXSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
    GetWindowRect(&m_rtSelf);
    m_Parent->ScreenToClient(&m_rtSelf);
	// don't handle if capture already set
	if (::GetCapture() != NULL) return;

    // don't handle if no room to drag
    RECT rectMouseClip;
		
    //if (!GetMouseClipRect(&rectMouseClip, point)) return;
	m_Parent->GetWindowRect(&rectMouseClip);
	rectMouseClip.top		 +=	m_nTop;
	rectMouseClip.bottom	 -=	m_nBottom;
    ::ClipCursor(&rectMouseClip);
	
	// set capture to the window which received this message
	SetCapture();
	ASSERT(this == CWnd::GetCapture());

    // get DC for drawing
	CDC* pDrawDC;
    pDrawDC = m_Parent->GetDC();
	ASSERT_VALID(pDrawDC);

    int     curX, curY;
	int     xDiff, yDiff;
	CRect   rectOrg, rectCur, rectOld;
    CSize   sizeBar;

    GetWindowRect(rectOrg);
    sizeBar = CSize(rectOrg.Width(), rectOrg.Height());

    m_Parent->ScreenToClient(rectOrg);
    pDrawDC->DrawDragRect(&rectOrg, sizeBar, NULL, sizeBar);
    rectOld = rectCur = rectOrg;
    xDiff = yDiff = 0;

	// get messages until capture lost or cancelled/accepted
	for (;;) {
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));

		if (CWnd::GetCapture() != this)
			break;

		switch (msg.message) {
		// handle movement/accept messages
		case WM_MOUSEMOVE:
//			m_btUp.EnableWindow(true);
//			m_btDown.EnableWindow(true);
			// handle resize cases (and part of move)
            curX = (int)(short)LOWORD(msg.lParam);
            curY = (int)(short)HIWORD(msg.lParam);

            xDiff = curX - point.x;
            yDiff = curY - point.y;

            rectCur = rectOrg;
            rectCur.top += yDiff;
            rectCur.bottom += yDiff;
            pDrawDC->DrawDragRect(&rectCur, sizeBar, &rectOld, sizeBar);
            rectOld = rectCur;

            break;

		// handle cancel messages
		case WM_KEYDOWN:
			if (msg.wParam != VK_ESCAPE)
				break;
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
            goto ExitLoop;

		// just dispatch rest of the messages
		default:
			DispatchMessage(&msg);
			break;
		}
	}

ExitLoop:
	if	(pDrawDC->m_hDC)
	{
		pDrawDC->DrawDragRect(&rectCur, sizeBar, NULL, sizeBar);

		m_Parent->ReleaseDC(pDrawDC);
		ReleaseCapture();
		::ClipCursor(NULL);

		if (yDiff == 0) return;

		// move the splitter bar & re-position the attached panes if necessary
		MoveWindow(rectCur, FALSE);
		RecalcLayout();

		m_Parent->SendMessage(WM_SPLITTER_MOVED, yDiff, GetDlgCtrlID());
		GetWindowRect(&m_rtSelf);
		m_Parent->ScreenToClient(&m_rtSelf);
	}
}

BOOL CXSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(AfxGetApp()->LoadCursor(AFX_IDC_VSPLITBAR));
    return TRUE;
}

void CXSplitterWnd::RecalcLayout()
{
	CWnd*	pane;
    RECT	rcBar, rcPane;
	int		cy;

    GetWindowRect(&rcBar);
    m_Parent->ScreenToClient(&rcBar);
	cy		=		rcBar.bottom	-	m_rtSelf.bottom;

    int i;

    for (i=0; i<m_lstUp.GetSize(); i++) {
        pane = (CWnd*)m_lstUp.GetAt(i);
        pane->GetWindowRect(&rcPane);
        m_Parent->ScreenToClient(&rcPane);		
		if(	i==m_iUp	)
		{
			rcPane.top		+=	cy;
			rcPane.bottom	+=	cy;
		}
		else
		{
			rcPane.bottom	+=	cy;
		}
		pane->MoveWindow(&rcPane, FALSE);
    }

    for (i=0; i<m_lstDown.GetSize(); i++) {
        pane = (CWnd*)m_lstDown.GetAt(i);

		if(	pane->IsWindowVisible())
		{
			pane->GetWindowRect(&rcPane);
			m_Parent->ScreenToClient(&rcPane);

			if(	i==m_iDown	)
			{
				rcPane.top		+=	cy;
				rcPane.bottom	+=	cy;
			}
			else
			{
				rcPane.top	+=	cy;
			}
			pane->MoveWindow(&rcPane, FALSE);
		}
    }
	CRect rect;
	m_Parent->Invalidate();
}

void CXSplitterWnd::BindWithControl(CWnd *parent, DWORD ctrlId)
{
    m_Parent = parent;
    SubclassWindow(m_Parent->GetDlgItem(ctrlId)->GetSafeHwnd());

    // Make sure to get mouse message from the dialog window
    DWORD style = GetStyle();
    ::SetWindowLong(GetSafeHwnd(), GWL_STYLE, style | SS_NOTIFY);
}

void CXSplitterWnd::AddUpWnd(CWnd *pWnd)
{
	m_lstUp.Add(pWnd);
}

void CXSplitterWnd::AddDownWnd(CWnd *pWnd)
{
	m_lstDown.Add( pWnd	);
}

void CXSplitterWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);
	dc.FillRect(&rc,&CBrush(BACK_COLOR));

	CPen pen(PS_SOLID, 1, m_clrBk), *pPen;

	pPen = dc.SelectObject(&pen);
	if (pPen)
	{
		dc.MoveTo(0, rc.Height()/2);
		dc.LineTo(rc.Width(), rc.Height()/2);
		dc.SelectObject(pPen);
	}
}
