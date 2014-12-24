// ChildView.h : CChildView ��Ľӿ�
//

#pragma once
#include "DrawingObject.h"



// CChildView ����

class CChildView : public CWnd
{
	// ����
public:
	CChildView();
protected:
CDrawingObject m_drawingObject;
// ������������
CGestureConfig m_gestureConfig;
// Overrides
protected:
		double m_dblZoomRatioStart;
    double m_dblZoomRatioTotal;             
    CPoint m_ptCenter;
// ���ƾ��
// ���ƾ��
virtual BOOL OnGestureZoom(CPoint ptCenter, long lDelta);
virtual BOOL OnGesturePan(CPoint ptFrom, CPoint ptTo);
virtual BOOL OnGestureRotate(CPoint ptCenter, double dblAngle);
virtual BOOL OnGesturePressAndTap(CPoint ptFirstFinger, long lDelta);
virtual BOOL OnGestureTwoFingerTap(CPoint ptCenter);
	// ����
public:

//private:
//	int m_iCurrColor;                    // The current stroke color
//	CStrokeCollection m_StrkColFinished; // The user finished entering strokes 
//	// after user lifted his or her finger.
//	CStrokeCollection m_StrkColDrawing;  // The Strokes collection the user is
//	// currently drawing.
//	// Overrides
//protected:
//	COLORREF GetTouchColor(bool bPrimaryContact);
//	virtual BOOL OnTouchInput(CPoint pt, int nInputNumber, int nInputsCount, PTOUCHINPUT pInput);
//	//��Overrides
//protected:
//	// Handlers for different touch input events
//	BOOL OnTouchInputDown(CPoint pt, PTOUCHINPUT pInput);
//	BOOL OnTouchInputMove(CPoint pt, PTOUCHINPUT pInput);
//	BOOL OnTouchInputUp(CPoint pt, PTOUCHINPUT pInput);
//	// ����
public:

	// ��д
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

