//====================================================================
//==============XP Style Button=============
//Author	tiger
//Date		2005-12-5
//Version	2.0
//E-mail	tiger.blue@163.com
//====================================================================
//====================================================================
//==============XP Style Button=============
//Author	tiger
//Date		2003-3-31
//Version	1.0
//E-mail	tiger.blue@163.com
//====================================================================
////////////////////////////////////////////////////////////////////
// XPButton.cpp : implementation file
//

#include "stdafx.h"
#include "XPBt.h"
#include ".\xpbt.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPBt

CXPBt::CXPBt()
{
	m_bIsMouseMove = 0;

	m_NormalTextColor	= RGB(255, 255, 255);
	m_SelectTextColor	= RGB(255, 255, 0);
	m_ActiveTextColor	= RGB(0, 0, 255);
	m_FalseTextColor    = RGB(128,128,128);

	m_ActiveColor		= RGB(255, 120, 80);

	m_NormalColorTop	= RGB(255, 255, 255);
	m_NormalColorBottom = RGB(0, 128, 255);
	m_FalseColorBottom  = RGB(150, 150, 150);

	m_FrameColor		= RGB(0, 64, 128);
	m_FrameHeight		= RGB(230, 230, 230);
	m_FrameShadow		= RGB(128, 128, 128);

	m_bButtonHavePushFlag=false;

	m_InsideBoundryPenLeftSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, m_ActiveColor); 
	m_InsideBoundryPenTopSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, m_ActiveColor);
	m_InsideBoundryPenRightSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, m_ActiveColor);
	m_InsideBoundryPenBottomSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, m_ActiveColor);
} 

CXPBt::~CXPBt()
{
	m_InsideBoundryPenLeftSel.DeleteObject();
	m_InsideBoundryPenTopSel.DeleteObject();
	m_InsideBoundryPenRightSel.DeleteObject();
	m_InsideBoundryPenBottomSel.DeleteObject();
}


BEGIN_MESSAGE_MAP(CXPBt, CButton)
	//{{AFX_MSG_MAP(CXPBt)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
 //   ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnSetTipText)
 ON_WM_ERASEBKGND()
 ON_WM_ENABLE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXPBt message handlers

bool CXPBt::GetCheck()
{
    return m_bButtonHavePushFlag;
}

void CXPBt::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	//*

}

void CXPBt::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
		//Invalidate();
		
	//TRACKMOUSEEVENT trackmouseevent;
	//trackmouseevent.cbSize = sizeof(trackmouseevent);
	//trackmouseevent.dwFlags = TME_LEAVE;
	//trackmouseevent.hwndTrack = GetSafeHwnd();
	//trackmouseevent.dwHoverTime = 1;//HOVER_DEFAULT;
	//_TrackMouseEvent(&trackmouseevent);
	
	TRACKMOUSEEVENT t_MouseEvent;
	t_MouseEvent.cbSize      = sizeof(TRACKMOUSEEVENT);
	t_MouseEvent.dwFlags     = TME_LEAVE | TME_HOVER;
	t_MouseEvent.hwndTrack   = m_hWnd;
	t_MouseEvent.dwHoverTime = 1;
	::_TrackMouseEvent(&t_MouseEvent);

	CButton::OnMouseMove(nFlags, point);
}
LRESULT CXPBt::OnMouseHover(WPARAM w, LPARAM l)
{
	if( m_bIsMouseMove == 0 )
	{
		m_bIsMouseMove = 1;
		RedrawWindow();		
		//TRACE(TEXT("OnMouseHover(m_bMouseIsOver=TRUE;) \n"));
	}	
	return 0;
}

LONG CXPBt::OnMouseLeave(WPARAM, LPARAM)
{
	if( m_bIsMouseMove == 1 )
	{
		m_bIsMouseMove = 0;
		RedrawWindow();
	}
	return 0;
}

void CXPBt::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	UINT nBS = GetButtonStyle();

	// Add BS_OWNERDRAW style
	SetButtonStyle(nBS | BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

void CXPBt::DrawFace(COLORREF Top, COLORREF Bottom, CRect& rc, CRect CalRc, CDC* pDC)
{
	//pDC->FillRect(rc, &CBrush(Top)); 	
	CPen Pen;
	CPen* pOldPen = pDC->SelectObject(&Pen);

	int R, G, B;
	R = (GetRValue(Top) - GetRValue(Bottom)) / CalRc.Height();
	G = (GetGValue(Top) - GetGValue(Bottom)) / CalRc.Height();
	B = (GetBValue(Top) - GetBValue(Bottom)) / CalRc.Height();

	//R = R>0 ? R : -R;
	//G = G>0 ? G : -G;
	//B = B>0 ? B : -B;

	int ColR = GetRValue(Top), ColG = GetGValue(Top), ColB = GetBValue(Top);
	COLORREF ColMax = Top > Bottom ? Top : Bottom;
	COLORREF ColMin = Top > Bottom ? Bottom: Top;

	for(int i=0; i<rc.Height(); i++)
	{
		ColR -= R;
		ColG -= G;
		ColB -= B;

		/*
		if( ColR >= GetRValue(ColMax) || ColR <= GetRValue(ColMin) ||
		ColG >= GetGValue(ColMax) || ColG <= GetGValue(ColMin) ||
		ColB >= GetBValue(ColMax) || ColB <= GetBValue(ColMin) )
		{
		R = G = B = 0;
		}///*/


		Pen.DeleteObject();
		Pen.CreatePen(PS_SOLID, 1, RGB(ColR, ColG, ColB));

		pDC->SelectObject(&Pen);

		pDC->MoveTo(rc.left, rc.top+i);
		pDC->LineTo(rc.right, rc.top+i);
	}

	pDC->SelectObject(pOldPen);
	Pen.DeleteObject();
}

void CXPBt::DrawFrame(COLORREF HeightLight, COLORREF ShadowLight, COLORREF FrameColor, CRect& rc, CDC* pDC)
{
	CBrush NullBrush;
	NullBrush.CreateStockObject(NULL_BRUSH);
	CBrush* pOldBrush = pDC->SelectObject(&NullBrush);

	CPen Pen;
	Pen.CreatePen(PS_SOLID, 1, FrameColor);
	CPen* pOldPen = pDC->SelectObject(&Pen);
	
	pDC->RoundRect(rc, CPoint(3, 3));
	rc.DeflateRect(1, 1, 1, 1); 
	pDC->Draw3dRect(rc, HeightLight, ShadowLight);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

    Pen.DeleteObject();
    NullBrush.DeleteObject();
}

BOOL CXPBt::OnEraseBkgnd(CDC* pDC)
{	
	
	CFont tFont;
	CFont *pOldFont;
	//tFont.CreatePointFont(90,_T("Tahoma"));	
	tFont.CreatePointFont(100,_T("宋体"));	

	pOldFont=pDC->SelectObject(&tFont);	

	UINT nState  = GetState();
	
	CRect rc;
	GetClientRect(&rc);

	UINT uStyle   = DFCS_BUTTONPUSH;

	pDC->SetBkMode(TRANSPARENT);
	CString strText;
	GetWindowText(strText);

	if (!IsWindowEnabled())
		//		pDC->DrawState(pt, szExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
	{
		DrawFace(m_NormalColorTop,m_FalseColorBottom, rc, rc, pDC);
		DrawFrame(m_FrameHeight, m_FrameShadow, m_FrameColor, rc, pDC);
		pDC->SetTextColor(m_FalseTextColor);
	}
	else 
	{
		if(( nState & ODS_SELECTED )||m_bButtonHavePushFlag)
		{
			m_bIsMouseMove = 0;
			DrawFace(m_NormalColorBottom, m_NormalColorTop, rc, rc, pDC);
			DrawFrame(m_FrameShadow, m_FrameShadow, m_FrameColor, rc, pDC);	
			pDC->SetTextColor(m_SelectTextColor);				
		}
		else //Normal
		{
			DrawFace(m_NormalColorTop, m_NormalColorBottom, rc, rc, pDC);
			DrawFrame(m_FrameHeight, m_FrameShadow, m_FrameColor, rc, pDC);
			pDC->SetTextColor(m_NormalTextColor);				
		}

		if( m_bIsMouseMove )
		{
			DrawInsideBorder(pDC,&rc);
			pDC->SetTextColor(m_ActiveTextColor);
		}
		
	}


	pDC->DrawText(strText, strText.GetLength(), 
		rc, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	//*///
	pDC->SelectObject(pOldFont);

	ReleaseDC(pDC);

	return TRUE;
}

void CXPBt::SetWindowText(CString strText)
{
	CButton::SetWindowText(strText);
	RedrawWindow();
}

//绘制按钮的内边框
void CXPBt::DrawInsideBorder(CDC *pDC, CRect* rect)
{
	CPen *pLeft, *pRight, *pTop, *pBottom;

	/*if (m_bSelected && !m_bOver)
	{*/
		pLeft = & m_InsideBoundryPenLeftSel;
		pRight = &m_InsideBoundryPenRightSel;
		pTop = &m_InsideBoundryPenTopSel;
		pBottom = &m_InsideBoundryPenBottomSel;
	//}
	//else
	//{
	//	pLeft = &m_InsideBoundryPenLeft;
	//	pRight = &m_InsideBoundryPenRight;
	//	pTop = &m_InsideBoundryPenTop;
	//	pBottom = &m_InsideBoundryPenBottom;
	//}

	CPoint oldPoint = pDC->MoveTo(rect->left, rect->bottom - 1);
	CPen* pOldPen = pDC->SelectObject(pLeft);
	pDC->LineTo(rect->left, rect->top + 1);
	pDC->SelectObject(pRight);
	pDC->MoveTo(rect->right - 1, rect->bottom - 1);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pTop);
	pDC->MoveTo(rect->left - 1, rect->top);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pBottom);
	pDC->MoveTo(rect->left, rect->bottom);
	pDC->LineTo(rect->right - 1, rect->bottom);
	pDC->SelectObject(pOldPen);
	pDC->MoveTo(oldPoint);

	//if (m_bSelected && !m_bOver)
	//	DrawFocusRect(pDC->m_hDC,rect);
}
void CXPBt::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);

	RedrawWindow();
}
