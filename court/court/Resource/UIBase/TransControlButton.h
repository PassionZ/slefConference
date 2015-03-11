#include "BtnST.h"

#pragma once

// CTransControlButton
enum
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	SPEED_FASTEST,
	SPEED_FAST,
	SPEED_SLOWEST,
	SPEED_SLOW
};

class CTransControlButton : public CButtonST
{
	DECLARE_DYNAMIC(CTransControlButton)

public:
	CTransControlButton();
	virtual ~CTransControlButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void SetType(int nDirection);
	void SetContent(CString strContent);
	void CreateToolTip(const TCHAR *pTitle, UINT nDelay);
private:
	int m_Type;
	CString m_strContent;
	CToolTipCtrl m_toolTip;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


