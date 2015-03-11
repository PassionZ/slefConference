#if !defined(AFX_XPBUTTON_H__7C6468A7_65D2_4DD8_B7B3_1CD483294610__INCLUDED_)
#define AFX_XPBUTTON_H__7C6468A7_65D2_4DD8_B7B3_1CD483294610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XPButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXPBt window

class CXPBt : public CButton
{
// Construction
public:
	CXPBt();

    bool GetCheck();

// Attributes
public:

// Operations
public:
	inline void SetNormalTopColor(COLORREF color)
	{
		m_NormalColorTop = color;
	}
	inline void SetNormalBottomColor(COLORREF color)
	{
		m_NormalColorBottom = color;
	}
	inline void SetActiveTextColor(COLORREF color)
	{
		m_ActiveTextColor = color;
	}
	inline void SetNormalTextColor(COLORREF color)
	{
		m_NormalTextColor = color;
	}
	inline void SetSelectTextColor(COLORREF color)
	{
		m_SelectTextColor = color;
	}
	inline void SetFrameColor(COLORREF color)
	{
		m_FrameColor = color;
	}
	inline void SetActiveColor(COLORREF color)
	{
		m_ActiveColor = color;
	}

	inline void SetButtonHavePushFlag(BOOL bButtonHavePushFlag)
	{
		m_bButtonHavePushFlag = bButtonHavePushFlag;
		InvalidateRect(NULL);
	}

	BOOL GetButtonHavePushFlag()
	{
		return m_bButtonHavePushFlag;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPBt)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXPBt();
	virtual void SetWindowText(CString strText);
	// Generated message map functions
protected:
	//{{AFX_MSG(CXPBt)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//    afx_msg BOOL OnSetTipText( UINT id, NMHDR * pTTTStruct, LRESULT * pResult );
	//}}AFX_MSG

	void DrawFace(COLORREF Top, COLORREF Bottom, CRect& rc, CRect CalRc, CDC* pDC);
	void DrawFrame(COLORREF HeightLight, COLORREF ShadowLight, COLORREF FrameColor, CRect& rc, CDC* pDC);
	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	LONG OnMouseLeave(WPARAM, LPARAM);
	LRESULT OnMouseHover(WPARAM w, LPARAM l);
	BOOL m_bIsMouseMove;
	BOOL m_bButtonHavePushFlag;

	COLORREF m_FrameColor;
	COLORREF m_ActiveColor;

	COLORREF m_ActiveTextColor;
	COLORREF m_NormalTextColor;
	COLORREF m_SelectTextColor;
	COLORREF m_FalseTextColor;

	COLORREF m_FrameHeight;
	COLORREF m_FrameShadow;

	COLORREF m_NormalColorTop;
	COLORREF m_NormalColorBottom;
	COLORREF m_FalseColorBottom;

	//按钮获得焦点时按钮的内边框
	CPen m_InsideBoundryPenLeftSel;
	CPen m_InsideBoundryPenRightSel;
	CPen m_InsideBoundryPenTopSel;
	CPen m_InsideBoundryPenBottomSel;

DECLARE_MESSAGE_MAP()
//private:
//    CToolTipCtrl m_ToolTip;//工具提示对象
//    CString m_strInfo;
//    CRect m_rect;

//public:
////    virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
//    virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
//protected:
//    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	//绘制按钮的内边框
	void DrawInsideBorder(CDC *pDC, CRect* rect);
	afx_msg void OnEnable(BOOL bEnable);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPBUTTON_H__7C6468A7_65D2_4DD8_B7B3_1CD483294610__INCLUDED_)
