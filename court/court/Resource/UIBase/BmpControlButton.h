#pragma once

#include "BmpBkButton.h"

#define WM_LEFT_BUTTON_DOWN		WM_USER+0x100
#define WM_LEFT_BUTTON_UP		WM_USER+0x101


// CBmpControlButton

class CBmpControlButton : public CBmpBkButton
{
	DECLARE_DYNAMIC(CBmpControlButton)

public:
	CBmpControlButton();
	virtual ~CBmpControlButton();

	virtual BOOL IsPressed();	//按钮是否被按下

	virtual void SetBitmap(UINT nIDResouce);	//设置图片
	virtual void SetBitmapRect(int iLeft, int iTop, int iWidth, int iHeight);	//设置图片大小
	virtual void SetBitmapOrder(int iUp, int iDown, int iLeft, int iRight, int iNormal);	//设置单幅图片顺序

	enum eMouseDownArea { emUp, emDown, emLeft, emRight, emInvalid };
	virtual eMouseDownArea GetClickedArea();	//取得鼠标点击区域

protected:
	CBitmap *m_pBitmap;
	int m_iBmpWidth, m_iBmpHeight, m_iLeftOffset, m_iTopOffset;
	int m_iIndexUp, m_iIndexDown, m_iIndexLeft,m_iIndexRight, m_iNormal;

	eMouseDownArea m_iClickedArea;
	CPoint m_ptClickedPoint;	//在哪个区域
	eMouseDownArea GetPointArea(CDC *pDC, const CPoint &pt) const;	// 检查鼠标落在哪个区域 (eMouseDownArea)
	int GetBmpIndexByPointArea(eMouseDownArea iMousePoint);	//取得位图序号

	//
	virtual void DrawBkBitmap(CDC *pDC, const CRect &rect, int iBmpIndex);
//	virtual void Do_MouseLeave();
	//BOOL m_bIsLBDown;	//左键是否按下

	DECLARE_MESSAGE_MAP()

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


