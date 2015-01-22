#if !defined(AFX_BUTTONEX_H__90535150_5C24_4DB0_B278_817839622F4B__INCLUDED_)
#define AFX_BUTTONEX_H__90535150_5C24_4DB0_B278_817839622F4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonEx window

class CButtonEx : public CButton
{
// Construction
public:
	CButtonEx();

// Attributes
public:
	int m_nIndex;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CButtonEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonEx)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONEX_H__90535150_5C24_4DB0_B278_817839622F4B__INCLUDED_)
