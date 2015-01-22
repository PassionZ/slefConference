// MsnSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MsnSliderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsnSliderCtrl

BOOL TBTransparentBlt(
  HDC hdcDest,                 // handle to destination DC
  int nXOriginDest,            // x-coord of upper-left corner
  int nYOriginDest,            // y-coord of upper-left corner
  int nWidthDest,              // destination width
  int nHeightDest,             // destination height
  HDC hdcSrc,                  // handle to source DC
  int nXOriginSrc,             // y-coord of upper-left corner
  int nYOriginSrc,             // x-coord of upper-left corner
  int nWidthSrc,               // source width
  int nHeightSrc,              // source height
  COLORREF clrTransparent		// alpha-blending function
)
{	
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);

	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	
	// 将源DC中的位图拷贝到临时DC中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	
	// 设置透明色
	SetBkColor(hImageDC, clrTransparent);

	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	
	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	COLORREF		nSaveBKColor = GetBkColor(hdcDest);
	COLORREF		nSaveTextColor = GetTextColor(hdcDest);
	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);

	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);	

	SetBkColor(hdcDest,nSaveBKColor);
	SetTextColor(hdcDest,nSaveTextColor);
	return TRUE;
}

CMsnSliderCtrl::CMsnSliderCtrl()
	:m_bHorizontal(true)
	,m_bOnMouseMove(false)
	,m_nMaxPos(100)
	,m_nCurPos(10)
	,m_bMouseDown(false)
	,m_nVolumn(0)
	,m_hNotify(NULL)
	,m_ulMsgID(0)
	,m_ulThumbBmpID(0)
	,m_nThumbCx(8)
	,m_hInstance(NULL)
{
	m_clrBack = RGB(255, 255, 255);
	m_clrFront = RGB(128, 160, 192);
}

CMsnSliderCtrl::~CMsnSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CMsnSliderCtrl, CStatic)
	//{{AFX_MSG_MAP(CMsnSliderCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsnSliderCtrl message handlers

void CMsnSliderCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
}

void CMsnSliderCtrl::SetHorizontal(bool bHorizontal)
{
	m_bHorizontal = bHorizontal;
}

void CMsnSliderCtrl::SetRang(int nMaxPos)
{
	m_nMaxPos = nMaxPos;
}

void CMsnSliderCtrl::SetPos(int nPos)
{
	m_nCurPos = nPos;
}

int CMsnSliderCtrl::GetPos()
{
	return m_nCurPos;
}

BOOL CMsnSliderCtrl::OnEraseBkgnd(CDC* pDC)
{
	Redraw(pDC);
	return FALSE;
}

void CMsnSliderCtrl::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
	/*
	CRect rc;

	GetWindowRect(rc);
	ScreenToClient(rc);
	SetWindowPos(NULL, rc.left, rc.top, 18, rc.Height(), 0);
	*/
}

void CMsnSliderCtrl::Redraw()
{
	CDC* pDC = GetDC();
	if (pDC)
	{
		CRect rc;

		GetClientRect(rc);
		{
			CMemDC3 memDC(pDC, rc);

			Redraw(&memDC);
		}

		ReleaseDC(pDC);
	}
}

void CMsnSliderCtrl::Redraw(CDC* pDC)
{
	if (m_bHorizontal)
	{
		DrawHorizontal(pDC);
	}
	else
	{
		DrawVertical(pDC);
	}
}

void CMsnSliderCtrl::DrawHorizontal(CDC* pDC)
{
	CRect rc, rcChannel;
	CPen penCur(PS_SOLID, 1, m_clrFront), *penSave;
	int cx = 2;
	int cy = 0;

	GetClientRect(rc);
	rcChannel.SetRect(0, cy, rc.Width(), rc.Height()-cy);
	pDC->FillRect(rc, &CBrush(m_clrBack));
	pDC->FillRect(rcChannel, &CBrush(RGB(255, 255, 255)));
	pDC->FrameRect(rcChannel, &CBrush(m_clrFront));

	penSave = pDC->SelectObject(&penCur);
	for (int i=1+cx; i<rc.Width(); i+=(cx+1))
	{
		pDC->MoveTo(i, cy);
		pDC->LineTo(i, rc.Height()-cy);
	}
	pDC->SelectObject(penSave);

	DrawHorizontalVolumn(pDC);
	DrawHorizontalThumb(pDC);
}

void CMsnSliderCtrl::DrawVertical(CDC* pDC)
{

}

void CMsnSliderCtrl::DrawHorizontalThumb(CDC* pDC)
{
	CRect rc = GetThumbRect();
	
	HBITMAP hBitmap = (HBITMAP)::LoadImage(m_hInstance, (LPCTSTR)m_ulThumbBmpID, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);

	if (hBitmap)
	{
		HDC	hMem = CreateCompatibleDC(pDC->m_hDC);

		if (hMem)
		{
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMem, hBitmap);
			if (hOldBitmap)
			{
				TBTransparentBlt(pDC->m_hDC,
								rc.left,
								rc.top,
								rc.Width(),
								rc.Height(),
								hMem, 
								m_bOnMouseMove?rc.Width():0,
								0,
								rc.Width(),
								rc.Height(),
								RGB(255, 0, 255));
				SelectObject(hMem, hOldBitmap);
			}
			::DeleteDC(hMem);
		}
		
		//DrawBitmapToDC(pDC->m_hDC, hBitmap, rc.left, rc.top, rc.Width(), rc.Height(), m_bOnMouseMove?rc.Width():0, 0);
		::DeleteObject(hBitmap);
	}
}

void CMsnSliderCtrl::DrawVerticalThumb(CDC* pDC)
{
}

void CMsnSliderCtrl::DrawHorizontalVolumn(CDC* pDC)
{
	if (!m_nVolumn)
		return;

	CRect rc;
	CPen penCur(PS_SOLID, 1, RGB(0, 255, 0)), *penSave;
	CPen penCur1(PS_SOLID, 1, RGB(255, 255, 0));
	CPen penCur2(PS_SOLID, 1, RGB(255, 0, 0));
	int cx = 2;
	int cy = 0;
	int nVRight = 0, nY, nR;

	GetClientRect(rc);

//	nVRight = (double)m_nVolumn/32767.0*rc.Width();
	nVRight = (double)m_nVolumn/m_nMaxPos*rc.Width();
	nY = rc.Width()*0.5;
	nR = rc.Width()*0.8;

	for (int i=1; i<nVRight; i+=(cx+1))
	{
		if (i < nY)
		{
			penSave = pDC->SelectObject(&penCur);			
		}else if ((i >= nY) && (i < nR)){
			penSave = pDC->SelectObject(&penCur1);			
		}else{
			penSave = pDC->SelectObject(&penCur2);			
		}

		pDC->MoveTo(i, cy+1);
		pDC->LineTo(i, rc.Height()-cy-1);

		pDC->MoveTo(i+1, cy+1);
		pDC->LineTo(i+1, rc.Height()-cy-1);

		pDC->SelectObject(penSave);
	}	
}

void CMsnSliderCtrl::DrawVerticalalVolumn(CDC* pDC)
{
	if (!m_nVolumn)
		return;
}

RECT CMsnSliderCtrl::GetThumbRect()
{
	CRect rc, rcThumb;
	int x;

	GetClientRect(rc);

	if (m_bHorizontal)
	{
		x = rc.Width()*(double)m_nCurPos/(double)m_nMaxPos;
		x -= m_nThumbCx/2;

		if (x < 0)
			x = 0;

		if ((x+m_nThumbCx) > rc.Width())
			x = rc.Width() - m_nThumbCx;

		rcThumb.SetRect(x, 0, x+m_nThumbCx, rc.Height());
	}
	else
	{
	}

	return rcThumb;
}

void CMsnSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rc = GetThumbRect();

	if (rc.PtInRect(point))
	{
		m_bMouseDown = true;
		SetCapture();
	}
	else
	{
		if (point.x > rc.right)
		{
			m_nCurPos += m_nMaxPos/5;
		}
		else if (point.x < rc.left)
		{
			m_nCurPos -= m_nMaxPos/5;
		}

		if (m_nCurPos > 100)
		{
			m_nCurPos = 100;
		}

		if (m_nCurPos < 0)
		{
			m_nCurPos = 0;
		}

		if (m_hNotify && m_ulMsgID)
		{
			::PostMessage(m_hNotify, m_ulMsgID, (WPARAM)m_hWnd, m_nCurPos);
		}
		
		Redraw();
	}

	CStatic::OnLButtonDown(nFlags, point);
}

void CMsnSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CStatic::OnLButtonUp(nFlags, point);

	if (m_bMouseDown)
	{
		m_bMouseDown = false;
		ReleaseCapture();
		Redraw();

		if (m_hNotify && m_ulMsgID)
		{
			::PostMessage(m_hNotify, m_ulMsgID, (WPARAM)m_hWnd, m_nCurPos);
		}
	}	
}

void CMsnSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CStatic::OnMouseMove(nFlags, point);
	CRect rc = GetThumbRect();

	if (m_bMouseDown)
	{
		GetClientRect(rc);
		m_nCurPos = m_nMaxPos*(double)point.x/(double)rc.Width();

		if (m_nCurPos > 100)
		{
			m_nCurPos = 100;
		}

		if (m_nCurPos < 0)
		{
			m_nCurPos = 0;
		}

		/*
		if (m_hNotify && m_ulMsgID)
		{
			::PostMessage(m_hNotify, m_ulMsgID, (WPARAM)m_hWnd, m_nCurPos);
		}
		*/

		m_bOnMouseMove = true;
		Redraw();
		m_bOnMouseMove = false;
	}
	else
	{
		if (rc.PtInRect(point))
		{
			m_bOnMouseMove = true;
			Redraw();
			m_bOnMouseMove = false;
		}
		else
		{
			Redraw();
		}
	}
}

void CMsnSliderCtrl::SetVolumn(int nVolumn)
{
	m_nVolumn = nVolumn;

	/*
	if (m_nVolumn < 0)
		m_nVolumn = 0;

	if (m_nVolumn > 100)
		m_nVolumn = 100;
		*/

	Redraw();
}

void CMsnSliderCtrl::SetHwndNotify(HWND hWnd, unsigned long ulMsgID)
{
	m_hNotify = hWnd;
	m_ulMsgID = ulMsgID;
}

void CMsnSliderCtrl::SetThumbRes(HINSTANCE hInstance, unsigned long ulBmpID, int cx)
{
	m_hInstance = hInstance;
	m_ulThumbBmpID = ulBmpID;
	m_nThumbCx = cx;
}