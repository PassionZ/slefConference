#if !defined(AFX_XSPLITTERWND_H__EC161A05_B1F7_476A_8BD6_869F7DA67A73__INCLUDED_)
#define AFX_XSPLITTERWND_H__EC161A05_B1F7_476A_8BD6_869F7DA67A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XSplitterWnd.h : header file
//

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
	int			m_iUp;
	int			m_iDown;
	COLORREF	m_clrBk;
public:
	int			m_nTop;
	int			m_nBottom;
	CRect		m_rtSelf;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSPLITTERWND_H__EC161A05_B1F7_476A_8BD6_869F7DA67A73__INCLUDED_)
