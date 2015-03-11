//////////////////////////////////////////////////////////////////////////
//FileName:			XSplitterWnd.h										//
//																		//
//																		//
//																		//
//																		//
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////

#pragma once


/////////////////////////////////////////////////////////////////////////////
// CXSplitterWnd window

#define WM_SPLITTER_MOVED   (WM_USER+1000)

class CXSplitterWnd : public CWnd
{
// Construction
public:
	CXSplitterWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSplitterWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void AddDownWnd(CWnd* pWnd);
	void AddUpWnd(CWnd* pWnd);
	void BindWithControl(CWnd *parent, DWORD ctrlId);
	void RecalcLayout();
	virtual ~CXSplitterWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXSplitterWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWnd*		m_Parent;
	CPtrArray	m_lstUp;
	CPtrArray	m_lstDown;		
	COLORREF	m_clrBk;
public:
	int			m_iUp;
	int			m_iDown;
	int			m_nTop;
	int			m_nBottom;
	CRect		m_rtSelf;
};

/////////////////////////////////////////////////////////////////////////////
