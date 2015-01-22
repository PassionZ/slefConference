#include "stdafx.h"
#include "TBBitmapButton.h"
#include "MsnSliderCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void DrawTransBitmapToDC(HDC hDC, HBITMAP hBitmap, int x, int y, int cx, int cy, int sx, int sy)
{
	HDC	hMem = CreateCompatibleDC(hDC);

	if (hMem)
	{
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMem, hBitmap);
		if (hOldBitmap)
		{
			TBTransparentBlt(	hDC,
				x,
				y,
				cx,
				cy,
				hMem,
				sx,
				sy,
				cx,
				cy,
				RGB(234, 236, 236));
			SelectObject(hMem, hOldBitmap);
		}
		::DeleteDC(hMem);
	}
}

void DrawBitmapToDC(HDC hDC, HBITMAP hBitmap, int x, int y, int cx, int cy, int sx, int sy)
{
	HDC	hMem = CreateCompatibleDC(hDC);

	if (hMem)
	{
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMem, hBitmap);
		if (hOldBitmap)
		{
			::BitBlt(	hDC,
				x,
				y,
				cx,
				cy,
				hMem,
				sx,
				sy,
				SRCCOPY);
			SelectObject(hMem, hOldBitmap);
		}
		::DeleteDC(hMem);
	}
}

CTBBitmapButton::CTBBitmapButton()
	: m_nButtonNumber(0)
	, m_uBitmapRes(0)
	, m_hInstance(0)
	, m_bReset(true)
{
	m_sizeButton.cx = m_sizeButton.cy = m_ptFirstPos.x = m_ptFirstPos.y = 0;
	memset(m_btnBitmap, 0, sizeof(BITMAP_BUTTON)*MAX_BUTTON);
}

CTBBitmapButton::~CTBBitmapButton()
{

}

void CTBBitmapButton::SetFirstPoint(POINT pt)
{
	m_ptFirstPos = pt;
	int i=0;for ( i=0; i<m_nButtonNumber; i++)
	{
		m_btnBitmap[i].rc.left		= m_ptFirstPos.x + i * m_sizeButton.cx;
		m_btnBitmap[i].rc.right		= m_btnBitmap[i].rc.left + m_sizeButton.cx;
		m_btnBitmap[i].rc.top		= m_ptFirstPos.y;
		m_btnBitmap[i].rc.bottom	= m_ptFirstPos.y + m_sizeButton.cy;
	}
}

void CTBBitmapButton::SetBitmapRes(UINT uBitmapRes, HINSTANCE hInstance, int nNumber, SIZE size, POINT posFirst)
{
	ASSERT(nNumber <= MAX_BUTTON);
	if (nNumber > MAX_BUTTON)
		return;

	m_uBitmapRes		= uBitmapRes;
	m_hInstance			= hInstance;
	m_nButtonNumber		= nNumber;
	m_sizeButton		= size;
	m_ptFirstPos		= posFirst;

	int i=0;for ( i=0; i<m_nButtonNumber; i++)
	{
		m_btnBitmap[i].status		= 0;
		m_btnBitmap[i].rc.left		= m_ptFirstPos.x + i * size.cx;
		m_btnBitmap[i].rc.right		= m_btnBitmap[i].rc.left + size.cx;
		m_btnBitmap[i].rc.top		= m_ptFirstPos.y;
		m_btnBitmap[i].rc.bottom	= m_ptFirstPos.y + size.cy;
	}
}

void CTBBitmapButton::OnDraw(HWND hWnd)
{
	HDC hDC = GetDC(hWnd);

	if (hDC)
	{
		OnDraw(hDC);
		ReleaseDC(hWnd, hDC);
	}
}

void CTBBitmapButton::OnDraw(HDC hDC)
{
	ASSERT(hDC && m_uBitmapRes && m_hInstance);
	if (!hDC || !m_uBitmapRes || !m_hInstance)
		return ;

	HBITMAP	hBitmap = (HBITMAP)::LoadImage(m_hInstance, (LPCTSTR)m_uBitmapRes, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);
	if (hBitmap)
	{
		int	by;
		int i=0;for ( i=0; i<m_nButtonNumber; i++)
		{
			by = 0;
			switch (m_btnBitmap[i].status)
			{
			case TBBUTTON_NORMAL:	by = 0; break;
			case TBBUTTON_MOVE:		by = 1; break;
			case TBBUTTON_CHECK:	by = 2; break;
			case TBBUTTON_DISABLE:	by = 3; break;
			}

			/*
			HDC	hMem = CreateCompatibleDC(hDC);

			if (hMem)
			{
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMem, hBitmap);
				if (hOldBitmap)
				{
					TBTransparentBlt(
								hDC,
								m_btnBitmap[i].rc.left,
								m_btnBitmap[i].rc.top,
								m_sizeButton.cx,
								m_sizeButton.cy,
								hMem,
								i*m_sizeButton.cx,
								by*m_sizeButton.cy,
								m_sizeButton.cx,
								m_sizeButton.cy,
								RGB(255, 0, 255));
					SelectObject(hMem, hOldBitmap);
				}
				::DeleteDC(hMem);
			}
			*/
			DrawTransBitmapToDC(	hDC,
							hBitmap,
							m_btnBitmap[i].rc.left,
							m_btnBitmap[i].rc.top,
							m_sizeButton.cx,
							m_sizeButton.cy,
							i*m_sizeButton.cx,
							by*m_sizeButton.cy);
		}
		::DeleteObject(hBitmap);
	}
}

void CTBBitmapButton::SetCheck(int index, int nStatus)
{
	//ASSERT(index <= m_nButtonNumber);
	if (index > m_nButtonNumber)
		return;

	int i=0;for ( i=0; i<m_nButtonNumber; i++)
	{
		if (index == i)
		{
			m_btnBitmap[i].status = nStatus;
			break;
		}
	}
}

int CTBBitmapButton::GetCheck(int index)
{
	//ASSERT(index <= m_nButtonNumber);
	if (index > m_nButtonNumber)
		return -1;

	int i=0;for ( i=0; i<m_nButtonNumber; i++)
	{
		if (index == i)
		{
			return  m_btnBitmap[i].status;
		}
	}

	return -1;
}

void CTBBitmapButton::OnMouseMove(HWND hWnd, POINT pt)
{
	int index = HitTest(pt);
	if ( index != -1)
	{
		if (m_btnBitmap[index].status == TBBUTTON_NORMAL)
		{
			m_bReset = true;
			OnMouseMoveDraw(index, hWnd);		
		}
	}
	else if (m_bReset)
	{
		m_bReset = false;
		OnDraw(hWnd);
	}
}

int	CTBBitmapButton::HitTest(POINT pt)
{
	int i=0;for ( i=0; i<m_nButtonNumber; i++)
	{
		if (::PtInRect(&(m_btnBitmap[i].rc), pt))
		{
			if ((m_btnBitmap[i].status == -1) || (m_btnBitmap[i].status == TBBUTTON_DISABLE))
				return -1;

			return i;
		}
	}
	return -1;
}

void CTBBitmapButton::OnMouseMoveDraw(int index, HWND hWnd)
{
	ASSERT(index <= m_nButtonNumber);
	if (index > m_nButtonNumber)
		return;

	HDC hDC = GetDC(hWnd);

	if (hDC)
	{
		OnMouseMoveDraw(index, hDC);
		ReleaseDC(hWnd, hDC);
	}
}

void CTBBitmapButton::OnMouseMoveDraw(int index, HDC hDC)
{
	ASSERT(index <= m_nButtonNumber);
	if (index > m_nButtonNumber)
		return;

	ASSERT(hDC && m_uBitmapRes && m_hInstance);
	if (!hDC || !m_uBitmapRes || !m_hInstance)
		return ;

	HBITMAP	hBitmap = (HBITMAP)::LoadImage(m_hInstance, (LPCTSTR)m_uBitmapRes, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);
	if (hBitmap)
	{
		int i=0;for ( i=0; i<m_nButtonNumber; i++)
		{
			int by = m_btnBitmap[i].status;

			if (index == i)
				by = 1;

			/*
			HDC	hMem = CreateCompatibleDC(hDC);

			if (hMem)
			{
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMem, hBitmap);
				if (hOldBitmap)
				{
					TBTransparentBlt(
								hDC,
								m_btnBitmap[i].rc.left,
								m_btnBitmap[i].rc.top,
								m_sizeButton.cx,
								m_sizeButton.cy,
								hMem,
								i*m_sizeButton.cx,
								by*m_sizeButton.cy,
								m_sizeButton.cx,
								m_sizeButton.cy,
								RGB(255, 0, 255));
					SelectObject(hMem, hOldBitmap);
				}
				::DeleteDC(hMem);
			}
			*/
			DrawTransBitmapToDC(	hDC,
							hBitmap,
							m_btnBitmap[i].rc.left,
							m_btnBitmap[i].rc.top,
							m_sizeButton.cx,
							m_sizeButton.cy,
							i*m_sizeButton.cx,
							by*m_sizeButton.cy);

		}
		::DeleteObject(hBitmap);
	}
}

void CTBBitmapButton::GetRect(int index, LPRECT lpRect)
{
	ASSERT(index <= m_nButtonNumber);
	if (index > m_nButtonNumber)
		return;

	ASSERT(lpRect);
	if (!lpRect)
		return;

	int i=0;for ( i=0; i<m_nButtonNumber; i++)
	{
		if (index == i)
		{
			*lpRect = m_btnBitmap[i].rc;
			break;
		}
	}
}