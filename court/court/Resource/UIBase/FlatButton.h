#if !defined(AFX_FLATBUTTON_H__170EF53F_5D6F_49F2_9654_AAB3A1DDA08B__INCLUDED_)
#define AFX_FLATBUTTON_H__170EF53F_5D6F_49F2_9654_AAB3A1DDA08B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlatButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlatButton window

class CFlatButton : public CButton
{
// Construction
public:
	CFlatButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL GetCheck();
	void SetCheck(BOOL bCheck);

    BOOL Click();

	virtual ~CFlatButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFlatButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void DrawShadowRectangle(HDC hDC, RECT rc, int nType);
	BOOL		m_bMouseOnButton;
	BOOL		m_bCheck;
	bool		m_bNobmp;

	POINT			m_ptFirst;
	unsigned long	m_ulBitmapRes;
	SIZE			m_sizeButton;
	HINSTANCE		m_hInstance;
	LPCTSTR			m_pszFileName;		//Í¼Æ¬Â·¾¶
	CString			m_strFilename;
	CBitmap			m_bmpPic;

	CToolTipCtrl	m_toolTip;
	CString			m_strToolTip ;

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

public:
	void SetBitmap(HINSTANCE hInstance, UINT uBitmapID, SIZE size, POINT point);
	void SetBitmap(HINSTANCE hInstance, CString lpszPath, SIZE size, POINT point);

	BOOL		m_bShowRedFrame;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetToolTip(CString strToolTip);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATBUTTON_H__170EF53F_5D6F_49F2_9654_AAB3A1DDA08B__INCLUDED_)
