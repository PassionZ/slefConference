#if !defined(__MSNSLIDERCTRL_H__)
#define __MSNSLIDERCTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsnSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsnSliderCtrl window

class CMemDC3 : public CDC {
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CMemDC3(CDC* pDC, const CRect& rcBounds) : CDC()
	{
		CreateCompatibleDC(pDC);
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
		m_bDraw = true;

	}
	~CMemDC3() 
	{
		if (m_bDraw)
		{
			m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
					this, m_rcBounds.left, m_rcBounds.top, SRCCOPY);
		}
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) delete m_bitmap;
	}
	CMemDC3* operator->() {
		return this;
	}
	bool	m_bDraw;
};
class CMsnSliderCtrl : public CStatic
{
// Construction
public:
	CMsnSliderCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsnSliderCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMsnSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMsnSliderCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void		SetHorizontal(bool bHorizontal);
	void		SetRang(int nMaxPos);
	void		SetPos(int nPos);
	int			GetPos();
	void		SetVolumn(int nVolumn);
	void		SetHwndNotify(HWND hWnd, unsigned long ulMsgID);
	void		SetThumbRes(HINSTANCE hInstance, unsigned long ulBmpID, int cx);

	COLORREF		m_clrBack;
	COLORREF		m_clrFront;

private:
	void		Redraw();
	void		Redraw(CDC* pDC);
	void		DrawHorizontal(CDC* pDC);
	void		DrawHorizontalThumb(CDC* pDC);
	void		DrawVertical(CDC* pDC);
	void		DrawVerticalThumb(CDC* pDC);	
	void		DrawHorizontalVolumn(CDC* pDC);
	void		DrawVerticalalVolumn(CDC* pDC);
	RECT		GetThumbRect();

	bool			m_bHorizontal;
	int				m_nCurPos;
	int				m_nMaxPos;
	bool			m_bOnMouseMove;
	bool			m_bMouseDown;
	int				m_nVolumn;
	HWND			m_hNotify;
	unsigned long	m_ulMsgID;
	unsigned long	m_ulThumbBmpID;
	int				m_nThumbCx;
	HINSTANCE		m_hInstance;

};

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
					  );
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSNSLIDERCTRL_H__CA10A433_CFC8_49A9_BCC9_7D01DBB8C816__INCLUDED_)
