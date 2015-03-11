#if !defined(__COLORTABCTRL_H__)
#define __COLORTABCTRL_H__


/////////////////////////////////////////////////////////////////////////////
// CColorTabCtrl window
class CMemDC : public CDC
{
public:

    CMemDC(CDC* pDC) : CDC()
    {
        ASSERT(pDC != NULL);

        m_pDC = pDC;
        m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();
              
        if (m_bMemDC) 
        {
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
            SetWindowOrg(m_rect.left, m_rect.top);
        }
        else 
        {
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
    
    ~CMemDC()
    {
        if (m_bMemDC) 
        {    
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            SelectObject(m_pOldBitmap);
        } else {
            m_hDC = m_hAttribDC = NULL;
        }
    }

    CMemDC* operator->() {return this;}
        
    operator CMemDC*() {return this;}

private:    
    CBitmap* m_pOldBitmap;  // bitmap originally found in CMemDC
    CDC*     m_pDC;         // Saves CDC passed in constructor
    CRect    m_rect;        // Rectangle of drawing area.
    BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
	CBitmap  m_bitmap;      // Offscreen bitmap
};

class CMemDC2 : public CDC {
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CMemDC2(CDC* pDC, const CRect& rcBounds) : CDC()
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
	~CMemDC2() 
	{
		if (m_bDraw)
		{
			m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
					this, m_rcBounds.left, m_rcBounds.top, SRCCOPY);
		}
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) delete m_bitmap;
	}
	CMemDC2* operator->() {
		return this;
	}
	CBitmap* GetMemBitmap()
	{
		return m_bitmap;
	}
	bool	m_bDraw;
};
class CColorTabCtrl : public CTabCtrl
{
// Construction
public:
	CColorTabCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorTabCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void Redraw(CDC* pDC);
	virtual ~CColorTabCtrl();

	// Generated message map functions
protected:
	void DrawItem(CDC* pDC, int index, LPRECT lpRect);
	//{{AFX_MSG(CColorTabCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	BOOL TBTransparentBlt(
								HDC hdcDest,                 // handle to destination DC
								int nXOriginDest,            // x-coord of upper-left corner
								int nYOriginDest,            // y-coord of upper-left corner
								int nWidthDest,              // destination width
								int nHeightDest,             // destination height
								HDC hdcSrc,                  // handle to source DC
								int nXOriginSrc,             // x-coord of upper-left corner
								int nYOriginSrc,             // y-coord of upper-left corner
								int nWidthSrc,               // source width
								int nHeightSrc,              // source height
								COLORREF clrTransparent		// alpha-blending function
								);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif