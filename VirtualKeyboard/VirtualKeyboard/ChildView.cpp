// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "VirtualKeyboard.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
    m_pkb = NULL;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_DESKTOP), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
    if(m_pkb)
    {
        m_pkb->draw();
    }
}

bool CChildView::Bind( Keyboard* pkb )
{
    if(!pkb)
        return false;
    m_pkb = pkb;
    pkb->rebind(this);
    return true;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if(m_pkb)
    {
        int index = m_pkb->hit(point);
        if(index >= 0)
        {
            m_pkb->press(index);
        }
    }
    CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if(m_pkb)
    {
        int index = m_pkb->hit(point);
        if(index >= 0)
        {
            m_pkb->release(index);
        }
    }
    CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    static HCURSOR hHand = ::LoadCursor(NULL,IDC_HAND);
    static HCURSOR hArrow = ::GetCursor();
    if(m_pkb)
    {
        int index = m_pkb->hit(point);
        if(index >= 0)
        {
            if(::GetCursor() != hHand)
            {
                ::SetCursor(hHand);
            }
        }
        else
        {
            if(::GetCursor() != hArrow)
            {
                ::SetCursor(hArrow);
            }
        }
    }
    CWnd::OnMouseMove(nFlags, point);
}
