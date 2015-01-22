// BmpControlButton.cpp : 实现文件
//

#include "stdafx.h"
#include "BmpControlButton.h"
#include "TBBitmapButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CBmpControlButton

IMPLEMENT_DYNAMIC(CBmpControlButton, CBmpBkButton)
CBmpControlButton::CBmpControlButton()
{
//	m_bIsLBDown = FALSE;
	m_pBitmap = NULL ;
	ShowBorder(FALSE);
}

CBmpControlButton::~CBmpControlButton()
{
	if (m_pBitmap)
	{
		delete m_pBitmap;
	}
}


BEGIN_MESSAGE_MAP(CBmpControlButton, CBmpBkButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CBmpControlButton 消息处理程序


void CBmpControlButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CBmpBkButton::TestPressed(lpDrawItemStruct);

	//
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	CRect rect = lpDrawItemStruct->rcItem;

	int nBmpIndex = m_iNormal;
	if (m_bPressed)
	{
		m_iClickedArea = GetPointArea( pDC, m_ptClickedPoint );
		nBmpIndex = GetBmpIndexByPointArea( m_iClickedArea );
	}

//	pDC->SetBkMode(TRANSPARENT);
	DrawBkBitmap(pDC, rect, nBmpIndex);
}

void CBmpControlButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	//m_bIsLBDown = TRUE;
	m_ptClickedPoint = point;
	GetParent()->PostMessage( WM_LEFT_BUTTON_DOWN, (WPARAM)this );

	CBmpBkButton::OnLButtonDown(nFlags, point);
}

void CBmpControlButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (m_bIsLBDown)
	//{
	//	m_bIsLBDown = FALSE;
		GetParent()->PostMessage( WM_LEFT_BUTTON_UP, (WPARAM)this );
	//}

	CBmpBkButton::OnLButtonUp(nFlags, point);
}

void CBmpControlButton::SetBitmap(UINT nIDResouce)
{
	if (!m_pBitmap)
	{
		m_pBitmap = new CBitmap();
	}

	if (nIDResouce != 0)
	{
		m_pBitmap->LoadBitmap( nIDResouce );
	}
}

void CBmpControlButton::SetBitmapRect(int iLeft, int iTop, int iWidth, int iHeight)
{
	m_iBmpHeight = iHeight ;
	m_iBmpWidth = iWidth;
	m_iLeftOffset = iLeft;
	m_iTopOffset = iTop;
}

void CBmpControlButton::SetBitmapOrder(int iUp, int iDown, int iLeft, int iRight, int iNormal)
{
	m_iIndexUp = iUp;
	m_iIndexDown = iDown;
	m_iIndexLeft = iLeft;
	m_iIndexRight = iRight;
	m_iNormal = iNormal;
}

CBmpControlButton::eMouseDownArea CBmpControlButton::GetPointArea(CDC *pDC, const CPoint &pt) const
{
	// 检查鼠标落在哪个区域 (a,b,c,d)

	///*
	//				+-----+
	//				|\ a /|
	//				| \ / |
	//				|d X b|
	//				| / \ |
	//				|/ c \|
	//				+-----+
	//*/

	CRect rect;
	GetClientRect(&rect);

	//计算中点(共用顶点)坐标
	int iMidX = rect.left + (rect.right - rect.left)/2;
	int iMidY = rect.top + (rect.bottom - rect.top)/2;

	//
	CDC aDC, bDC,cDC,dDC;

	//
	aDC.CreateCompatibleDC( pDC );
	bDC.CreateCompatibleDC( pDC );
	cDC.CreateCompatibleDC( pDC );
	dDC.CreateCompatibleDC( pDC );

	//Draw A area
	aDC.BeginPath();
	aDC.MoveTo(rect.left, rect.top);
	aDC.LineTo(iMidX, iMidY);
	aDC.LineTo(rect.right, rect.top);
	aDC.LineTo(rect.left, rect.top);
	aDC.EndPath();

	//Draw B area
	bDC.BeginPath();
	bDC.MoveTo(rect.right, rect.top);
	bDC.LineTo(iMidX, iMidY);
	bDC.LineTo(rect.right, rect.bottom);
	bDC.LineTo(rect.right, rect.top);
	bDC.EndPath();

	//Draw C area
	cDC.BeginPath();
	cDC.MoveTo(rect.left, rect.bottom);
	cDC.LineTo(iMidX, iMidY);
	cDC.LineTo(rect.right, rect.bottom);
	dDC.LineTo(rect.left, rect.bottom);
	cDC.EndPath();

	//Draw D area
	dDC.BeginPath();
	dDC.MoveTo(rect.left,rect.top);
	dDC.LineTo(iMidX, iMidY);
	dDC.LineTo(rect.left, rect.bottom);
	dDC.LineTo(rect.left,rect.top);
	dDC.EndPath();

	//
	CRgn rgnA, rgnB, rgnC, rgnD;
	rgnA.CreateFromPath( &aDC );
	rgnB.CreateFromPath( &bDC );
	rgnC.CreateFromPath( &cDC );
	rgnD.CreateFromPath( &dDC );

	//
	eMouseDownArea iRet = emInvalid;
	if (rgnA.PtInRegion( pt ))
	{
		iRet = emUp;
	}
	else if (rgnB.PtInRegion( pt ))
	{
		iRet = emRight;
	}
	else if (rgnC.PtInRegion( pt ))
	{
		iRet = emDown;
	}
	else if (rgnD.PtInRegion( pt ))
	{
		iRet = emLeft;
	}

	return iRet;
}

void CBmpControlButton::DrawBkBitmap(CDC *pDC, const CRect &rect, int iBmpIndex)
{
	CDC dcSrc;
	dcSrc.CreateCompatibleDC( pDC );
	dcSrc.SelectObject( m_pBitmap );

	//
	int iOffsetX = iBmpIndex * m_iBmpWidth + m_iLeftOffset;
	
	TBTransparentBlt(pDC->m_hDC, 0, 0, rect.Width(),rect.Height(), dcSrc.m_hDC, 
		iOffsetX, m_iLeftOffset, m_iBmpWidth, m_iBmpHeight, RGB(0xff, 0x00, 0xff));

	//
	//if (rect.Width() == m_iBmpWidth && rect.Height() == m_iBmpHeight)
	//{
	//	pDC->BitBlt(0,0,rect.Width(), rect.Height(), &dcSrc, iOffsetX, m_iTopOffset, SRCCOPY );
	//}
	//else
	//{
	//	pDC->StretchBlt( 0,0, rect.Width(), rect.Height(), &dcSrc, iOffsetX, 
	//		m_iTopOffset, m_iBmpWidth, m_iBmpHeight, SRCCOPY );
	//}
}

int CBmpControlButton::GetBmpIndexByPointArea(CBmpControlButton::eMouseDownArea iMousePoint)
{
	int iRet = m_iNormal;
	switch(iMousePoint)
	{
	case emUp:		iRet = m_iIndexUp; 		break;
	case emDown:	iRet = m_iIndexDown;	break;
	case emLeft:	iRet = m_iIndexLeft;	break;
	case emRight:	iRet = m_iIndexRight;	break;
	}

	return iRet;
}

CBmpControlButton::eMouseDownArea CBmpControlButton::GetClickedArea()
{
	return m_iClickedArea;
}
BOOL CBmpControlButton::OnEraseBkgnd(CDC* pDC)
{
	if (m_pBitmap)
	{
		return TRUE ;
	}
	else
	{
		return CBmpBkButton::OnEraseBkgnd(pDC);
	}
}

BOOL CBmpControlButton::IsPressed()
{
	return m_bPressed;
}

//void CBmpControlButton::Do_MouseLeave()
//{
//	TRACE(_T("CBmpControlButton::Do_MouseLeave(), m_bIsLBDown: %d\n"), m_bIsLBDown);
//
//	if (m_bIsLBDown)
//	{
//		m_bIsLBDown = FALSE;
//		GetParent()->PostMessage( WM_LEFT_BUTTON_UP, (WPARAM)this );
//	}
//}