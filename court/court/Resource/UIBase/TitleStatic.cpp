// TitleStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "TitleStatic.h"
#include ".\titlestatic.h"
#include <atlimage.h>

// CTitleStatic

IMPLEMENT_DYNAMIC(CTitleStatic, CStatic)
CTitleStatic::CTitleStatic()
: m_strPicPath(_T(""))
, m_iHeight(50)
{
}

CTitleStatic::~CTitleStatic()
{
}


BEGIN_MESSAGE_MAP(CTitleStatic, CStatic)
//	ON_WM_ERASEBKGND()
ON_WM_PAINT()
ON_WM_SIZE()
ON_WM_SIZING()
ON_WM_MOVE()
ON_WM_MOVING()
END_MESSAGE_MAP()



// CTitleStatic 消息处理程序


void CTitleStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rc;
	GetClientRect(&rc);
	CDC* pDC = &dc;
	if (pDC)
	{
		pDC->FillRect(&rc, (CBrush*)&CBrush(RGB(255,255,255)/*RGB(147, 171, 234)*/));

		CString str; 
		GetWindowText(str);
		if (str.GetLength() > 0)
		{
			if (m_strPicPath != _T(""))
			{
				CBitmap   bmp;
				CDC   dcMem;  
				CImage imgTemp;

				imgTemp.Load(m_strPicPath);
				if ( bmp.m_hObject ) 
					bmp.Detach();
				bmp.Attach(imgTemp.Detach());
				dcMem.CreateCompatibleDC(pDC);   
				CBitmap*   pOldBitmap   =   dcMem.SelectObject(&bmp);  
				pDC->BitBlt/*StretchBlt*/(rc.Width() - 254, 0, 254, rc.Height(),   
					&dcMem, 0, 0, SRCCOPY);   

				dcMem.SelectObject(pOldBitmap);   
				dcMem.DeleteDC();
				bmp.DeleteObject();
			}

			CFont hFont;
			LOGFONT stFont;
			memset(&stFont,0,sizeof(LOGFONT));
			stFont.lfHeight = MulDiv(20,-pDC->GetDeviceCaps(LOGPIXELSY),72);//设置字体高度为9
			stFont.lfWeight = FW_BOLD;
			stFont.lfCharSet = GB2312_CHARSET;
			_tcscpy(stFont.lfFaceName,_T("宋体"));//设置字样为宋体
			hFont.CreateFontIndirect(&stFont);

			CFont* hOldFont = pDC->SelectObject(&hFont);

			//HGDIOBJ hPreGdiObj = pDC->SelectObject(GetFont());
			TEXTMETRIC tm;
			pDC->GetTextMetrics(&tm);
			int nFontHeight = tm.tmHeight;  // 字体高度

			int nPrvBkMode = pDC->SetBkMode(TRANSPARENT);
			//pDC->TextOut(5, 12, str);
			CRect rcText;
			rcText.left = rc.left + 5;
			rcText.top = (rc.Height() - tm.tmHeight)/2;
			rcText.right = rc.right;
			rcText.bottom = rcText.top + tm.tmHeight;
			pDC->DrawText(str, rcText,DT_VCENTER);

			pDC->SetBkMode(nPrvBkMode);
			pDC->SelectObject(hOldFont);    
			hFont.DeleteObject();
		}
	}
	// 不为绘图消息调用 CStatic::OnPaint()
}

void CTitleStatic::SetParms(CString strPngPicPath)
{
	m_strPicPath = strPngPicPath;
}