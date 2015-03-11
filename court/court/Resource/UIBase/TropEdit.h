#pragma once


// CTropEdit

class CTropEdit : public CEdit
{
	DECLARE_DYNAMIC(CTropEdit)

public:
	CTropEdit();
	virtual ~CTropEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


