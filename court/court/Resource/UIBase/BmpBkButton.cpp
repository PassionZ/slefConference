// BmpBkButton.cpp : implementation file
//

#include "stdafx.h"
#include "BmpBkButton.h"
#include ".\bmpbkbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpBkButton

CBmpBkButton::CBmpBkButton()
{
	m_bSetEvent		= FALSE;
	m_bOver			= FALSE;
	m_bPressed		= FALSE;
	m_bChecked		= FALSE;
	m_bShowBorder	= FALSE;

	//
	m_pBmpOver		= NULL;
	m_pBmpLeave		= NULL;
	m_pBmpPressed	= NULL;
    m_pBmpDisable   = NULL;
}

CBmpBkButton::~CBmpBkButton()
{
	ClearBitmap();
}

void CBmpBkButton::ShowBorder(BOOL bShow)
{
	m_bShowBorder = bShow;
}

BEGIN_MESSAGE_MAP(CBmpBkButton, CButton)
	//{{AFX_MSG_MAP(CBmpBkButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpBkButton message handlers

void CBmpBkButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	TestPressed(lpDrawItemStruct);

	//
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	CRect rect = lpDrawItemStruct->rcItem;

	//

	if (m_bShowBorder)
	{
		rect.DeflateRect(1,1);
		DrawOutsideBorder(pDC, rect);
	}

	if (m_bShowBorder)
	{
		rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
	}
	else
	{
		rect.DeflateRect(1,1);
	}

    if (m_bShowBorder)
    {
	    DrawInsideBorder(pDC, rect);
    }

	

//	int offset = 3;
	DrawBkBitmap(pDC,rect);


	DrawText(pDC, rect);
}

void CBmpBkButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bSetEvent)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bSetEvent = _TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CBmpBkButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//当发生OnMouseLeave事件后,必须重新设置捕获 MouseLeave 事件
	m_bSetEvent = FALSE;
	m_bOver = FALSE;

	InvalidateRect( NULL );
	Do_MouseLeave();

//	TRACE("---OnMouseLeave()\n");
	
	return 0;
}

LRESULT CBmpBkButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	InvalidateRect(NULL);

//	TRACE("---OnMouseHover()\n");
	return 0;
}

BOOL CBmpBkButton::OnEraseBkgnd(CDC* pDC) 
{
	if (m_pBmpLeave || m_pBmpOver || m_pBmpPressed)
	{
		return TRUE ;
	}
	else
	{
		return CButton::OnEraseBkgnd(pDC);
	}
}

void CBmpBkButton::DrawText(CDC *pDC, const CRect &rect)
{
	//显示按钮的文本
	if (m_strText.GetLength() > 0)
	{
		COLORREF oldColor = pDC->SetTextColor(m_color);

		CFont* hFont = GetFont();
		CFont* hOldFont = pDC->SelectObject(hFont);
		CSize szExtent = pDC->GetTextExtent(m_strText, m_strText.GetLength());
		CPoint pt( rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
		if (m_pBmpPressed) 
		{
			pt.Offset(1, 1);
		}

		int nMode = pDC->SetBkMode(TRANSPARENT);
//		if (state & ODS_DISABLED)
//		{
//			pDC->DrawState(pt, szExtent, m_strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
//		}
//		else
		{
			pDC->DrawState(pt, szExtent, m_strText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
		}

		pDC->SetTextColor(oldColor);
		pDC->SelectObject(hOldFont);
		pDC->SetBkMode(nMode);

	}
}

void CBmpBkButton::DrawBkBitmap(CDC *pDC, const CRect &rect)
{
	CDC dc0;
	dc0.CreateCompatibleDC(pDC);
	CBitmap *pBitmap = NULL;

    if (IsWindowEnabled())
    {
        if ((m_bPressed || m_bChecked) && m_pBmpPressed)
        {
            pBitmap = m_pBmpPressed;
        }
        else if (m_bOver && m_pBmpOver)
        {
            pBitmap = m_pBmpOver;
        }
        else
        {
            if (m_pBmpLeave)
            {
                pBitmap = m_pBmpLeave;
            }
        }
    }
    else if (m_pBmpDisable)
    {
        pBitmap = m_pBmpDisable;
    }
    else
    {
        pBitmap = m_pBmpLeave;
    }

	//
	if (pBitmap)
	{
		dc0.SelectObject( pBitmap );

		BITMAP bitmap;
		pBitmap->GetBitmap( &bitmap );

		//
		pDC->BitBlt(rect.left, rect.top, bitmap.bmWidth , bitmap.bmHeight, &dc0, 0,0, SRCPAINT );
		pDC->BitBlt(rect.left, rect.top, bitmap.bmWidth , bitmap.bmHeight, &dc0, 0,0, SRCAND);
	}

	//
	dc0.DeleteDC();
}

void CBmpBkButton::DrawOutsideBorder(CDC *pDC, const CRect &rect)
{
	COLORREF  clBorder = RGB(0,0,0);

	pDC->SetBkMode(TRANSPARENT);
	pDC->Draw3dRect(&rect, clBorder, clBorder);
}

void CBmpBkButton::DrawInsideBorder(CDC *pDC, const CRect &rect)
{
	//if (m_bChecked)
	//{
 //       TRACE("CBmpBkButton: m_bChecked is TRUE\n");
	//}
	//else
	//{
	//	TRACE("CBmpBkButton: m_bChecked is FALSE\n");
	//}

	COLORREF  clBtnHiLight= ::GetSysColor(COLOR_BTNHILIGHT);
	COLORREF  clBtnShadow=::GetSysColor(COLOR_BTNSHADOW);
	COLORREF  clBtnFace=::GetSysColor(COLOR_BTNFACE);


	pDC->SetBkMode( TRANSPARENT );
	if (m_bPressed || m_bChecked)
	{
		pDC->Draw3dRect (&rect,clBtnShadow,clBtnHiLight);
	}
	else if (m_bOver)
	{
		pDC->Draw3dRect (&rect,clBtnHiLight,clBtnShadow);
	}
	else
	{
		pDC->Draw3dRect (&rect,clBtnFace,clBtnFace);
	}
}

void CBmpBkButton::SetBitmap(CImageList *pImageList, UINT nIDOver , 
                             UINT nIDLeave , UINT nIDPressed ,
                             UINT nIDDisable)
{
	
	ClearBitmap();
    
	if (pImageList)
    {
        m_pBmpOver = new CBitmap();
        GetImageFromList(pImageList, nIDOver, m_pBmpOver);

        m_pBmpLeave = new CBitmap();
        GetImageFromList(pImageList, nIDLeave, m_pBmpLeave);

        m_pBmpPressed = new CBitmap();
        GetImageFromList(pImageList, nIDPressed, m_pBmpPressed);

        if (nIDDisable != 0xffffffff)
        {
            m_pBmpDisable = new CBitmap();
            GetImageFromList(pImageList, nIDDisable, m_pBmpDisable);
        }

        InvalidateRect(NULL);
    }
}

void CBmpBkButton::SetBitmap(UINT nIDOver, UINT nIDLeave, UINT nIDPressed)
{
	ClearBitmap();

	if (nIDOver)
	{
		m_pBmpOver = new CBitmap();
        BOOL bRet = m_pBmpOver->LoadBitmap(nIDOver);
		ASSERT(bRet);
	}

	if (nIDLeave)
	{
		m_pBmpLeave = new CBitmap();
        BOOL bRet = m_pBmpLeave->LoadBitmap(nIDLeave);
        ASSERT(bRet);
	}

	if (nIDPressed)
	{
		m_pBmpPressed = new CBitmap();
        BOOL bRet = m_pBmpPressed->LoadBitmap(nIDPressed);
		ASSERT(bRet);
	}

	InvalidateRect(NULL);
}

void CBmpBkButton::SetButtonText(const CString &strText, COLORREF color)
{
	m_strText = strText;
	m_color = color;

	InvalidateRect(NULL);
}

void CBmpBkButton::ClearBitmap()
{
	if (m_pBmpPressed)
	{
		if (m_pBmpPressed->GetSafeHandle())
            m_pBmpPressed->DeleteObject();
		delete m_pBmpPressed;
		m_pBmpPressed = NULL ;
	}

	if (m_pBmpOver)
	{
		if (m_pBmpOver->GetSafeHandle())
			m_pBmpOver->DeleteObject();
		delete m_pBmpOver;
		m_pBmpOver = NULL ;
	}

	if (m_pBmpLeave)
	{
		if (m_pBmpLeave->GetSafeHandle())
			m_pBmpLeave->DeleteObject();
		delete m_pBmpLeave;
		m_pBmpLeave = NULL ;
	}

    if (m_pBmpDisable)
    {
        if (m_pBmpDisable->GetSafeHandle())
			m_pBmpDisable->DeleteObject();

        delete m_pBmpDisable;
        m_pBmpDisable = NULL ;
    }
}

void CBmpBkButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

CString CBmpBkButton::GetButtonText()
{
	return m_strText;
}

void CBmpBkButton::SetChecked(BOOL bChecked)
{
	m_bChecked = bChecked;
	InvalidateRect(NULL);
}

BOOL CBmpBkButton::IsChecked()
{
	return m_bChecked;
}

void CBmpBkButton::TestPressed(const LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_bPressed = FALSE ;
	if (lpDrawItemStruct->itemState & ODS_SELECTED /*ODS_FOCUS*/)
	{
		m_bPressed = TRUE ;
	}
}

void CBmpBkButton::Do_MouseLeave()
{
//	TRACE(_T("CBmpBkButton::Do_MouseLeave()\n"));
}

void CBmpBkButton::GetImageFromList(CImageList *pSrcImageList, 
                                    int nImage, CBitmap* pBitmap)
{   
    //LR_COPYFROMRESOURCE

    //IMAGEINFO tmpImageInfo;
    //if (pSrcImageList->GetImageInfo(0, &tmpImageInfo))
    //{
    //    int left = tmpImageInfo.rcImage.left * nImage;
    //    CopyImage(pSrcImageList, IMAGE_BITMAP, )


    //}


    //First we want to create a temporary image list we can manipulate
    CImageList tmpList;
    tmpList.Create(pSrcImageList);

    //Then swap the requested image to the first spot in the list 
    tmpList.Copy( 0, nImage, ILCF_SWAP );

    //Now we need to get som information about the image 
    IMAGEINFO lastImage;
    tmpList.GetImageInfo(0,&lastImage);

    CDC *pWndDC = GetWindowDC();

    //Heres where it gets fun
    //Create a Compatible Device Context using 
    //the valid DC of your calling window
    CDC dcMem; dcMem.CreateCompatibleDC (pWndDC); 

    //This rect simply stored the size of the image we need
    CRect rect (lastImage.rcImage);

    //Using the bitmap passed in, Create a bitmap 
    //compatible with the window DC
    //We also know that the bitmap needs to be a certain size.
    pBitmap->CreateCompatibleBitmap (pWndDC, rect.Width (), rect.Height ());

    //Select the new destination bitmap into the DC we created above
    CBitmap* pBmpOld = dcMem.SelectObject (pBitmap);

    //This call apparently "draws" the bitmap from the list, 
    //onto the new destination bitmap
    tmpList.DrawIndirect (&dcMem, 0, CPoint (0, 0), 
        CSize (rect.Width (), rect.Height ()), CPoint (0, 0));


    //cleanup by reselecting the old bitmap object into the DC
    dcMem.SelectObject (pBmpOld);

//    pBitmap->DeleteObject();
    dcMem.DeleteDC();
    ReleaseDC(pWndDC);
}

BOOL CBmpBkButton::DestroyWindow()
{
	ClearBitmap();
    return CButton::DestroyWindow();
}
