// CHLSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "HLSliderCtrl.h"
#include <atlimage.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHLSliderCtrl

CHLSliderCtrl::CHLSliderCtrl()
{
    m_bDown=m_bKonb=false;
    m_nPos=0;
}

CHLSliderCtrl::~CHLSliderCtrl()
{
	m_bmpPieceDown.DeleteObject();
    m_bmpPiece.DeleteObject();
    m_bmpBackdrop.DeleteObject();
	m_bmpLeft.DeleteObject();
}


BEGIN_MESSAGE_MAP(CHLSliderCtrl, CSliderCtrl)
    //{{AFX_MSG_MAP(CHLSliderCtrl)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
    ON_WM_MBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_KEYDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHLSliderCtrl message handlers

void CHLSliderCtrl::OnPaint() 
{
    CPaintDC dc(this);
    CRect rect;
	GetClientRect(&rect);

	BITMAP BmBK, BmPiece;    	    //保存位图的宽、高度等数据 
	HBITMAP hBitmap; 		//保存位图数据句柄 
    CDC memDC;
    memDC.CreateCompatibleDC(&dc);
    CBitmap *pOldBmp = memDC.SelectObject(&m_bmpBackdrop);

	hBitmap = HBITMAP(m_bmpBackdrop);

	::GetObject(hBitmap, sizeof(BmBK), &BmBK);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 10, 0, 10, BmBK.bmHeight, SRCCOPY);
	dc.StretchBlt(0, 0, 10, rect.Height(), &memDC, 0, 0, 10, BmBK.bmHeight, SRCCOPY);
	dc.StretchBlt(rect.Width()-10, 0, 10, rect.Height(), &memDC, BmBK.bmWidth-10, 0, 10, BmBK.bmHeight, SRCCOPY);
	
	if(m_bDown)
	{
		hBitmap = HBITMAP(m_bmpPieceDown);
		memDC.SelectObject(hBitmap);
		::GetObject(hBitmap, sizeof(BmPiece), &BmPiece);
	}
	else
	{
		hBitmap = HBITMAP(m_bmpPiece);
		memDC.SelectObject(hBitmap);
		::GetObject(hBitmap, sizeof(BmPiece), &BmPiece);
	}

    int max,min;
    GetRange(min,max);
    if (max == 0)
        max = 1;

    rect.right -= BmPiece.bmWidth;
	DWORD pos = m_nPos*rect.Width()/max;
	if (pos < 1)
		pos = 0;
	//TRACE(_T("Width = %d,     Pos = %d   m_nPos = %d \n"), rect.Width(), pos, m_nPos);

	dc.StretchBlt(pos, (BmBK.bmHeight-BmPiece.bmHeight)/2 , BmPiece.bmWidth, BmPiece.bmHeight, 
				&memDC, 0, 0, BmPiece.bmWidth, BmPiece.bmHeight, SRCCOPY);

	memDC.SelectObject(&m_bmpLeft);

	if (pos < BmPiece.bmWidth)
	{
		dc.StretchBlt(0, 0, pos, rect.Height(), &memDC, 0, 0, 10, rect.Height(), SRCCOPY);
	}
	else
	{
		dc.StretchBlt(0, 0, 10, rect.Height(), &memDC, 0, 0, 10, rect.Height(), SRCCOPY);
		dc.StretchBlt(10, 0, pos-10, rect.Height(), &memDC, 10, 0, 10, rect.Height(), SRCCOPY);
	}

    memDC.SelectObject(pOldBmp);
    memDC.DeleteDC();
}

BOOL CHLSliderCtrl::OnEraseBkgnd(CDC* pDC) 
{	
    return true;
}

void CHLSliderCtrl::OnSize(UINT nType, int cx, int cy) 
{
    CSliderCtrl::OnSize(nType, cx, cy);		
}

DWORD CHLSliderCtrl::GetPosEx()
{
	return m_nPos;
}
void CHLSliderCtrl::SetPosEx(DWORD pos)
{
	SetPos(pos);
	m_nPos = pos;
	Invalidate();
}

bool CHLSliderCtrl::LoadBitmaps(UINT IDs,UINT IDk,UINT IDkx)
{
    if(!m_bmpPiece.LoadBitmap(IDk)) return false;
    if(!m_bmpBackdrop.LoadBitmap(IDs)) return false;
    if(!m_bmpPieceDown.LoadBitmap(IDkx)) return false;
    return true;
}

void CHLSliderCtrl::LoadBitmaps(CString strPathbackdrop/*背景图片路径*/, 
								CString strPathPiece/*常态方块图片路径*/,  
								CString strPathPieceDown/*鼠标按下方块图片路径*/, 
								CString strLeftPath/*方块左边行走区域图*/)
{
	CImage imgTemp;
	imgTemp.Load(strPathbackdrop);
	if ( m_bmpBackdrop.m_hObject ) 
		m_bmpBackdrop.Detach();

	m_bmpBackdrop.Attach(imgTemp.Detach());

	imgTemp.Load(strPathPiece);
	if ( m_bmpPiece.m_hObject ) 
		m_bmpPiece.Detach();

	m_bmpPiece.Attach(imgTemp.Detach());

	imgTemp.Load(strPathPieceDown);
	if ( m_bmpPieceDown.m_hObject ) 
		m_bmpPieceDown.Detach();

	m_bmpPieceDown.Attach(imgTemp.Detach());

	imgTemp.Load(strLeftPath);
	if ( m_bmpLeft.m_hObject ) 
		m_bmpLeft.Detach();

	m_bmpLeft.Attach(imgTemp.Detach());
}

void CHLSliderCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
    CSliderCtrl::OnMButtonDown(nFlags, point);
}

void CHLSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	SetPos(m_nPos);
	GetParent()->PostMessage(WM_HSCROLL, m_nPos, (long)m_hWnd);
    m_bDown=false;
    m_bKonb=false;
    ReleaseCapture();
    Invalidate();
    CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CHLSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if(!m_bDown)
    {
        //((DlgPlayCtl*)GetParent())->OnSetPos(false,m_nPos);
        //SetCapture();
        //CRect rect;
        //GetClientRect(&rect);
        m_bDown=true;
        m_bKonb=true;
        ReDrawPoint(point);
    }

    CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CHLSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (point.x >= 0)
	{
		if(m_bKonb)
			ReDrawPoint(point);

		CSliderCtrl::OnMouseMove(nFlags, point);
	}
}

void CHLSliderCtrl::ReDrawPoint(CPoint point)
{
    CRect rect;
    GetClientRect(&rect);

	BITMAP BmPiece; 
	HBITMAP hBitmap = HBITMAP(m_bmpPieceDown);
	::GetObject(hBitmap, sizeof(BmPiece), &BmPiece);

    int max,min;
    DWORD pos;
    GetRange(min,max);
    rect.right -= BmPiece.bmWidth;
    if(point.x>rect.right)
    {
        SetPos(max);
        pos=max;
    }
    else
    {
        pos=max*point.x/rect.Width();
        SetPos(pos);
    }
    if(m_nPos!=pos)
        Invalidate();
    m_nPos=pos;
}


void CHLSliderCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
    CSliderCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
    Invalidate();
}

