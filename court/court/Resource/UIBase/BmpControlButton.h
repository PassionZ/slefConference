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

	virtual BOOL IsPressed();	//��ť�Ƿ񱻰���

	virtual void SetBitmap(UINT nIDResouce);	//����ͼƬ
	virtual void SetBitmapRect(int iLeft, int iTop, int iWidth, int iHeight);	//����ͼƬ��С
	virtual void SetBitmapOrder(int iUp, int iDown, int iLeft, int iRight, int iNormal);	//���õ���ͼƬ˳��

	enum eMouseDownArea { emUp, emDown, emLeft, emRight, emInvalid };
	virtual eMouseDownArea GetClickedArea();	//ȡ�����������

protected:
	CBitmap *m_pBitmap;
	int m_iBmpWidth, m_iBmpHeight, m_iLeftOffset, m_iTopOffset;
	int m_iIndexUp, m_iIndexDown, m_iIndexLeft,m_iIndexRight, m_iNormal;

	eMouseDownArea m_iClickedArea;
	CPoint m_ptClickedPoint;	//���ĸ�����
	eMouseDownArea GetPointArea(CDC *pDC, const CPoint &pt) const;	// �����������ĸ����� (eMouseDownArea)
	int GetBmpIndexByPointArea(eMouseDownArea iMousePoint);	//ȡ��λͼ���

	//
	virtual void DrawBkBitmap(CDC *pDC, const CRect &rect, int iBmpIndex);
//	virtual void Do_MouseLeave();
	//BOOL m_bIsLBDown;	//����Ƿ���

	DECLARE_MESSAGE_MAP()

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


