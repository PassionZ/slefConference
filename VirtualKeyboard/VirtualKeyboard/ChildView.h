// ChildView.h : interface of the CChildView class
//


#pragma once

#include "Keyboard.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();
    bool Bind(Keyboard* pkb);

// Attributes
private:
    Keyboard* m_pkb;

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

