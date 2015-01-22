// FlatButton.cpp : implementation file
//

#include "stdafx.h"
#include "FlatButton.h"
#include "../../courtDlg.h"
#include "../UtilBase/UIutil.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatButton

CFlatButton::CFlatButton()
{
	m_bMouseOnButton = FALSE;
	m_bCheck = FALSE;
	m_bShowRedFrame=FALSE;

	m_ptFirst.x = m_ptFirst.y = 0;
	m_ulBitmapRes = 0;
	m_sizeButton.cx = m_sizeButton.cy = 0;
	m_hInstance = NULL;
	m_strFilename = _T("");
	m_bNobmp = false;
	m_strToolTip = _T("");
}

CFlatButton::~CFlatButton()
{
	//m_bmpPic.DeleteObject();
}


BEGIN_MESSAGE_MAP(CFlatButton, CButton)
	//{{AFX_MSG_MAP(CFlatButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatButton message handlers
void CFlatButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	HDC		hDC	=	lpDrawItemStruct->hDC;
	BOOL	bIsPressed = (lpDrawItemStruct->itemState & ODS_SELECTED);
	HBITMAP hBitmap = NULL;
	if (m_bNobmp)
	{
		hBitmap = HBITMAP(m_bmpPic);
	}else
	{
		hBitmap = (HBITMAP)::LoadImage(m_hInstance, m_pszFileName/*modi by tiger,2009.07.06 (LPCTSTR)m_ulBitmapRes*/, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);
	}
	if (hBitmap)
	{
		HDC	hMem = CreateCompatibleDC(hDC);

		if (hMem)
		{
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMem,hBitmap);
			if (hOldBitmap)
			{
				TBTransparentBlt(hDC,
							0,
							0,
							m_sizeButton.cx, m_sizeButton.cy,
							hMem,
							m_ptFirst.x, m_ptFirst.y,
							m_sizeButton.cx, m_sizeButton.cy,
							RGB(255, 0, 255));

				SelectObject(hMem, hOldBitmap);
			}
			::DeleteDC(hMem);
		}
//		::DeleteObject(hBitmap);
	}
    
	if	(m_bCheck || bIsPressed)
	{
		DrawShadowRectangle(hDC, lpDrawItemStruct->rcItem, 0);
	}
	else if	(m_bMouseOnButton)
	{
		DrawShadowRectangle(hDC, lpDrawItemStruct->rcItem, 1);
	}

	if (m_bCheck && m_bShowRedFrame)
	{
		CRect	rc(lpDrawItemStruct->rcItem);
		CDC		*pDC=CDC::FromHandle(hDC);

		if (pDC)
		{
			rc.left+=2;
			rc.top+=2;
			rc.right-=2;
			rc.bottom-=2;

			pDC->FrameRect(&rc, &CBrush(RGB(255, 0, 0)));
		}
	}
}

void CFlatButton::SetBitmap(HINSTANCE hInstance, UINT uBitmapID, SIZE size, POINT point)
{
	m_hInstance = hInstance;
	m_ptFirst = point;
	m_ulBitmapRes = uBitmapID;
	m_pszFileName = (LPCTSTR)uBitmapID;		//add by tiger,2009.07.06	
	m_sizeButton = size;
	m_bNobmp = false;

	if (m_hWnd)
		InvalidateRect(NULL);
}

void CFlatButton::DrawShadowRectangle(HDC hDC, RECT rc, int nType)
{
	HPEN	hPen1, hPen2, hOldPen;

	rc.right -= 1;
	rc.bottom -= 1;
	hPen1 = ::CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	ASSERT(hPen1);
	hPen2 = ::CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	ASSERT(hPen2);

	if	(nType)
		hOldPen = (HPEN)::SelectObject(hDC, hPen1);
	else
		hOldPen = (HPEN)::SelectObject(hDC, hPen2);	

	MoveToEx(hDC, rc.left, rc.bottom, NULL);
	LineTo(hDC, rc.left, rc.top);
	LineTo(hDC, rc.right, rc.top);

	::SelectObject(hDC, hOldPen);
	if	(nType)
		hOldPen = (HPEN)::SelectObject(hDC, hPen2);
	else
		hOldPen = (HPEN)::SelectObject(hDC, hPen1);

	MoveToEx(hDC, rc.right, rc.top, NULL);
	LineTo(hDC, rc.right, rc.bottom);
	LineTo(hDC, rc.left, rc.bottom);

	::SelectObject(hDC, hOldPen);

	::DeleteObject(hPen1);
	::DeleteObject(hPen2);
}

void CFlatButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CButton::OnMouseMove(nFlags, point);

	CWnd* pWnd; 
	CWnd* pParent;

	CButton::OnMouseMove(nFlags, point);

	if (IsWindow(m_toolTip.m_hWnd))
	{
		m_toolTip.UpdateTipText( m_strToolTip , this);
	}

	if (nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE) return;

	pWnd = GetActiveWindow();
	pParent = GetOwner();

		if ((GetCapture() != this) && 
			(
	#ifndef ST_LIKEIE
			pWnd != NULL && 
	#endif
			pParent != NULL)) 
		{
			m_bMouseOnButton = TRUE;
			//SetFocus();
			SetCapture();
			InvalidateRect(NULL);
		}
		else
	{
		CRect rc;
		GetClientRect(&rc);
		if (!rc.PtInRect(point))
		{
		if (m_bMouseOnButton == TRUE)
		{
			m_bMouseOnButton = FALSE;
			InvalidateRect(NULL);
		}
		if (!(nFlags & MK_LBUTTON)) ReleaseCapture();
		}
	}
}

void CFlatButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CButton::OnLButtonUp(nFlags, point) ;
	if (m_bMouseOnButton == TRUE)
	{		
		//if (GetParent())
		//	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
		m_bMouseOnButton = FALSE;
		RedrawWindow();
		return;
	}	
}

void CFlatButton::SetCheck(BOOL bCheck)
{
	m_bCheck = bCheck;
	if	(m_hWnd)
	{
		InvalidateRect(NULL);
	}
}

BOOL CFlatButton::GetCheck()
{
	return m_bCheck;
}

BOOL CFlatButton::Click()
{
    return PostMessage(BM_CLICK);
/*
    BN_CLICKED
        The BN_CLICKED notification message is sent when the user clicks a button. 
        The parent window of the button receives this notification message 
        through the WM_COMMAND message. 

        BN_CLICKED 
        idButton = (int) LOWORD(wParam);    // identifier of button 
    hwndButton = (HWND) lParam;         // handle to button 
*/
}

void CFlatButton::PreSubclassWindow() 
{		
	CButton::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW);

	m_toolTip.Create( this , TTS_ALWAYSTIP) ;
	m_toolTip.Activate( true ) ;
	m_toolTip.AddTool( this, m_strToolTip) ;
	m_toolTip.SetDelayTime(100);
}

BOOL CFlatButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	BOOL bRet = CButton::OnSetCursor(pWnd, nHitTest, message);

	//::SetCursor(AfxGetApp()->LoadCursor(IDC_LINK));
	return bRet;
}

BOOL CFlatButton::TBTransparentBlt(
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

void CFlatButton::SetBitmap(HINSTANCE hInstance,CString lpszPath, SIZE size, POINT point)
{
	m_hInstance = hInstance;
	m_ptFirst = point;
	m_strFilename = lpszPath;
	m_pszFileName = m_strFilename;
	m_sizeButton = size;
	m_bNobmp = true;

	CImage imgTemp;
	imgTemp.Load(m_pszFileName);
	if ( m_bmpPic.m_hObject ) 
		m_bmpPic.Detach();
	m_bmpPic.Attach(imgTemp.Detach());	

	if (m_hWnd)
		InvalidateRect(NULL);
}

BOOL CFlatButton::PreTranslateMessage(MSG* pMsg)
{
	m_toolTip.RelayEvent(pMsg );

	return CButton::PreTranslateMessage(pMsg);
}

void CFlatButton::SetToolTip(CString strToolTip)
{
	m_strToolTip = strToolTip;
	if( m_hWnd )
	{
		if( m_toolTip.m_hWnd )
			m_toolTip.UpdateTipText( strToolTip, this );

	}
}