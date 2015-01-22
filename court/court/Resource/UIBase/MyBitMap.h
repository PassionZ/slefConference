#pragma once


#ifndef _MEMDC_H_
#define _MEMDC_H_

//////////////////////////////////////////////////
// CDQSMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// This class implements a memory Device Context


class CDQSMemDC : public CDC {
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CDQSMemDC(CDC* pDC, const CRect& rcBounds) : CDC()
	{
		if (CreateCompatibleDC(pDC))
		{
			m_bitmap = new CBitmap;
			m_bitmap->CreateCompatibleBitmap(pDC, rcBounds.Width(), rcBounds.Height());
			m_oldBitmap = SelectObject(m_bitmap);
			m_pDC = pDC;
			m_rcBounds = rcBounds;
			//For some reason the background color is not correct,
			//so we use the button face color.
			DWORD	color = ::GetSysColor( COLOR_BTNFACE );
			CBrush bkg(color);
			FillRect(rcBounds, &bkg);        
		}
		else
		{
			//throw exception("CDQSMemDC() error: CreateCompatibleDC()");
		}
	}
	~CDQSMemDC() 
	{
		m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
			this, m_rcBounds.left, m_rcBounds.top, SRCCOPY);
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) delete m_bitmap;

		DeleteDC();
	}
	CDQSMemDC* operator->() {
		return this;
	}
};

#endif

class CMyBitMap
{
public:
	CMyBitMap(void);
	~CMyBitMap(void);
	BITMAP m_bmp ; //位图格式

public:
	HBITMAP m_hBitMap ;	//位图句柄

public:
	void SetBitmap(UINT uResID);
	void SetBitmap(const char * pBitMapFile);
	bool drawOnDc( HDC hDC, long lx, long ly, long lex, long ley ) ;
	bool drawOnDcN( HDC hDC, long lx, long ly ) ;
	bool drawOnDcNXY( HDC hDC, long lsx, long lsy, long lex, long ley ) ;

};
