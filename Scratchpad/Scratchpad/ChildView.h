// ChildView.h : CChildView 类的接口
//

#pragma once
#include "DrawingObject.h"



// CChildView 窗口

class CChildView : public CWnd
{
	// 构造
public:
	CChildView();
protected:
CDrawingObject m_drawingObject;
// 保持手势设置
CGestureConfig m_gestureConfig;
// Overrides
protected:
		double m_dblZoomRatioStart;
    double m_dblZoomRatioTotal;             
    CPoint m_ptCenter;
// 手势句柄
// 手势句柄
virtual BOOL OnGestureZoom(CPoint ptCenter, long lDelta);
virtual BOOL OnGesturePan(CPoint ptFrom, CPoint ptTo);
virtual BOOL OnGestureRotate(CPoint ptCenter, double dblAngle);
virtual BOOL OnGesturePressAndTap(CPoint ptFirstFinger, long lDelta);
virtual BOOL OnGestureTwoFingerTap(CPoint ptCenter);
	// 属性
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
//	//　Overrides
//protected:
//	// Handlers for different touch input events
//	BOOL OnTouchInputDown(CPoint pt, PTOUCHINPUT pInput);
//	BOOL OnTouchInputMove(CPoint pt, PTOUCHINPUT pInput);
//	BOOL OnTouchInputUp(CPoint pt, PTOUCHINPUT pInput);
//	// 操作
public:

	// 重写
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

