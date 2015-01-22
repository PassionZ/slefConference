#include "stdafx.h"
#include "ColorTabCtrl.h"
#include "../UtilBase/UIutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorTabCtrl

CColorTabCtrl::CColorTabCtrl()
{
}

CColorTabCtrl::~CColorTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CColorTabCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorTabCtrl message handlers

void CColorTabCtrl::PreSubclassWindow() 
{
	CTabCtrl::PreSubclassWindow();

	ModifyStyle(TCS_OWNERDRAWFIXED, 0);
}

void CColorTabCtrl::OnPaint() 
{
	CPaintDC	dc(this);
	
	Redraw(&dc);
}

BOOL CColorTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return __super::OnEraseBkgnd(pDC);
}

void CColorTabCtrl::Redraw(CDC *pDC)
{
	CRect		rc;

	GetClientRect(&rc);
	CMemDC2		memDC(pDC, &rc);

	//memDC.FillSolidRect(&rc, RGB(255, 255, 255));
	memDC.m_bDraw = false;
	memDC.SelectObject(GetFont());

	int nCount = GetItemCount();

	if (!nCount) // no pages added
		return;

	//while (nCount--)
	int i=0;for ( i=0; i<nCount; i++)
	{
		GetItemRect(i, &rc);
		DrawItem(&memDC, i, rc);
	}

	GetClientRect(&rc);
	TBTransparentBlt(pDC->m_hDC,
						0, 0, rc.Width(), rc.Height(),
						memDC.m_hDC,
						 0,0, rc.Width(), rc.Height(),
						::GetSysColor( COLOR_BTNFACE ));
}

void CColorTabCtrl::DrawItem(CDC* pDC, int index, LPRECT lpRect)
{
	TC_ITEM     tci;
	TCHAR		strItemText[255]=_T("");
	bool		bSelected=GetCurSel()==index;
	CRect		rc2,rc(0, 0, lpRect->right-lpRect->left, lpRect->bottom-lpRect->top);
	CMemDC2		memDC(pDC, rc);
	CBrush		m_brush,*pBrush;

	memDC.m_bDraw = false;
	tci.mask        = TCIF_TEXT | TCIF_IMAGE;
	tci.pszText     = strItemText;
	tci.cchTextMax  = 254;

	GetItem(index, &tci);
	rc2=rc;
	rc2.bottom+=50;
	//rc2.right+=50;
	if (bSelected)
	{
		//m_brush.CreateSolidBrush(RGB(255, 153, 0));
		m_brush.CreateSolidBrush(RGB(248, 221, 134));
	}
	else
	{
		rc2.top=4;
		m_brush.CreateSolidBrush(RGB(255, 255, 255));		
	}
	pBrush=memDC.SelectObject(&m_brush);
	memDC.RoundRect(rc2, CPoint(20, 20));
	memDC.SelectObject(pBrush);
	memDC.MoveTo(rc.right-1, rc.top);
	//memDC.LineTo(rc.right-1, rc.bottom);

	memDC.SetBkMode(TRANSPARENT);
	rc2=rc;
	rc2.left+=2;
	rc2.top+=2;
	if (bSelected)
	{
		//memDC.SetTextColor(RGB(255, 0, 0));
		rc2.left+=1;
		rc2.top+=1;
	}
	else
	{
		//memDC.SetTextColor(RGB(0, 0, 0));
	}	
	memDC.DrawText(strItemText, rc2, DT_CENTER);
	pDC->BitBlt(lpRect->left, lpRect->top,
				rc.Width(), rc.Height(),
				&memDC,
				0, 0, SRCCOPY);
}

BOOL CColorTabCtrl::TBTransparentBlt(
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
