// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "ScratchPad.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView() 
//:m_iCurrColor(0)
{
}

CChildView::~CChildView()
{
	//for (int i = 0; i < m_StrkColDrawing.GetCount(); ++i)
	//{
	//	delete m_StrkColDrawing[i];
	//}

	//for (int i = 0; i < m_StrkColFinished.GetCount(); ++i)
	//{
	//	delete m_StrkColFinished[i];
	//}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	m_drawingObject.Paint(&dc);
	// TODO: �ڴ˴������Ϣ����������

	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}
//COLORREF CChildView::GetTouchColor(bool bPrimaryContact)
//{
//	static COLORREF c_arrColor[] =  // Secondary colors array
//	{
//		RGB(255, 0, 0),             // Red
//			RGB(0, 255, 0),             // Green
//			RGB(0, 0, 255),             // Blue
//			RGB(0, 255, 255),           // Cyan
//			RGB(255, 0, 255),           // Magenta
//			RGB(255, 255, 0)            // Yellow
//	};
//
//	COLORREF color;
//	if (bPrimaryContact)
//	{
//		// The primary contact is drawn in black.
//		color = RGB(0,0,0);         // Black
//	}
//	else
//	{
//		// Take current secondary color.
//		color = c_arrColor[m_iCurrColor];
//
//		// Move to the next color in the array.
//		m_iCurrColor = (m_iCurrColor + 1) % (sizeof(c_arrColor)/sizeof(c_arrColor[0]));
//	}
//
//	return color;
//}
//BOOL CChildView::OnTouchInputDown(CPoint pt, PTOUCHINPUT pInput)
//{
//	// Create new stroke and add point to it.
//	COLORREF strokeColor = GetTouchColor((pInput->dwFlags & TOUCHEVENTF_PRIMARY) != 0);
//
//	CStroke* pStrkNew = new CStroke(pInput->dwID, strokeColor);
//	pStrkNew->Add(pt);
//
//	// Add new stroke to the collection of strokes in drawing.
//	m_StrkColDrawing.Add(pStrkNew);   
//
//	return true;
//}
//BOOL CChildView::OnTouchInput(CPoint pt, int nInputNumber, int nInputsCount, PTOUCHINPUT pInput)
//{    
//	if ((pInput->dwFlags & TOUCHEVENTF_DOWN) == TOUCHEVENTF_DOWN) // Touch Down event
//	{
//		return OnTouchInputDown(pt, pInput);
//	}
//	else if ((pInput->dwFlags & TOUCHEVENTF_MOVE) == TOUCHEVENTF_MOVE) // Touch Move event
//	{
//		return OnTouchInputMove(pt, pInput);
//	}
//	else if ((pInput->dwFlags & TOUCHEVENTF_UP) == TOUCHEVENTF_UP) // Touch Move event
//	{
//		return OnTouchInputUp(pt, pInput);
//	}
//
//	return false;
//}
//BOOL CChildView::OnTouchInputMove(CPoint pt, PTOUCHINPUT pInput)
//{
//	// Find the stroke in the collection of the strokes in drawing.
//	int strokeIndex = m_StrkColDrawing.FindStrokeById(pInput->dwID);
//
//	if (strokeIndex >= 0)
//	{
//		CStroke* pStrk =  m_StrkColDrawing[strokeIndex];
//
//		// Add contact point to the stroke
//		pStrk->Add(pt);
//
//		// Draw the last stroke
//		pStrk->Draw(GetDC());
//	}
//
//	return true;
//}
//
//BOOL CChildView::OnTouchInputUp(CPoint pt, PTOUCHINPUT pInput)
//{
//	// Find the stroke in the collection of the strokes in drawing.
//	int strokeIndex = m_StrkColDrawing.FindStrokeById(pInput->dwID);
//
//	if (strokeIndex >= 0)
//	{
//		CStroke* pStrkCopy = m_StrkColDrawing[strokeIndex];
//
//		// Remove this stroke from the collection of strokes in drawing.
//		m_StrkColDrawing.RemoveAt(strokeIndex);
//
//		// Add this stroke to the collection of finished strokes.
//		m_StrkColFinished.Add(pStrkCopy);
//	}
//
//	return true;
//}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//if (!RegisterTouchWindow())
	//{
	//	ASSERT(FALSE);
	//}
	// TODO:  �ڴ������ר�õĴ�������
//��CChildView����ͼ�м���ףͣ�CREATE��Ϣ�Ĵ�����
 GetGestureConfig(&m_gestureConfig);

// ֻ����ת����Ĭ������
m_gestureConfig.EnableRotate();

 SetGestureConfig(&m_gestureConfig);
	return 0;
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	m_drawingObject.ResetObject(cx,cy);
	// TODO: �ڴ˴������Ϣ����������
}
BOOL CChildView::OnGesturePan(CPoint ptFrom, CPoint ptTo)
{
int dx = ptTo.x - ptFrom.x;
int dy = ptTo.y - ptFrom.y;
if (dx != 0 || dy != 0)
{
m_drawingObject.Move(dx, dy);
RedrawWindow();
}
return TRUE;
}
BOOL CChildView::OnGestureZoom(CPoint ptCenter, long lDelta)
{
if ((m_pCurrentGestureInfo->dwFlags & GF_BEGIN) == GF_BEGIN)
{
m_dblZoomRatioStart = m_dblZoomRatioTotal = lDelta;
}
else if (lDelta != 0)
{
m_dblZoomRatioTotal += lDelta;
double zoomFactor = (double)m_dblZoomRatioTotal / m_dblZoomRatioStart;
m_drawingObject.Zoom(zoomFactor, ptCenter.x, ptCenter.y);
m_dblZoomRatioStart = m_dblZoomRatioTotal;
RedrawWindow();
}
return TRUE;
}

BOOL CChildView::OnGestureRotate(CPoint ptCenter, double dblAngle)
{
if ((m_pCurrentGestureInfo->dwFlags & GF_BEGIN) == GF_BEGIN)
{
// ������ת����
m_ptCenter = ptCenter;
}
else if (dblAngle != 0.)
{
m_drawingObject.Rotate(dblAngle * PI / 100.0, m_ptCenter.x, m_ptCenter.y);
RedrawWindow();
}
return TRUE;
}
BOOL CChildView::OnGesturePressAndTap(CPoint ptFirstFinger, long lDelta)
{
if ((m_pCurrentGestureInfo->dwFlags & GF_BEGIN) != 0)
{
m_drawingObject.ShiftColor();
RedrawWindow();
}
return TRUE;
}
BOOL CChildView::OnGestureTwoFingerTap(CPoint ptCenter)
{
m_drawingObject.TogleDrawDiagonals();
RedrawWindow();
return TRUE;
}

//LRESULT CChildView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	switch ( message)  
//       {  
//           //   
//           //case WM_TOUCH://��㴥��  
//           //   return GST_WndProcessGesture( GetSafeHwnd(), wParam, lParam);//���ô�������Ĵ�����  
//           //      
//   
//              break;  
//   
//           default:  
//   
//              break;  
//       }  
//	return CWnd::WindowProc(message, wParam, lParam);
//}
