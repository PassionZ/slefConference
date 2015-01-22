

#include "stdafx.h"
#include "DrawingObject.h"

const COLORREF CDrawingObject::s_colors[] = 
{
	RGB(210,0,0),	 // RED
    RGB(255,139,23), // yellow   
    RGB(146,208,80), // green
    RGB(13,13,13),   // black
    RGB(149,179,215) // blue
};


CDrawingObject::CDrawingObject(void)
{
    
}

CDrawingObject::~CDrawingObject(void)
{
}


void CDrawingObject::ShiftColor(void)
{

    _iColorIndex++;

    if(MAX_COLORS == _iColorIndex)
 
        _iColorIndex = 0;
}



void CDrawingObject::ResetObject(const int cxClient,const int cyClient)
{
    
    _iCx = cxClient/2;
    _iCy = cyClient/2;

  TRACE(  "centen %d %d (_iCx%d,_iCy%d)\n" ,cxClient,cyClient,_iCx,_iCy);
    _iWidth = cxClient/2;
    _iHeight = cyClient/2;

    // Initial scaling factor is 1.0 (no scaling)
    _dScalingFactor = 1.0;

    // Initial rotation angle is 0.0 (no rotation)
    _dRotationAngle = 0.0; 

    _bDrawDiagonals = false; // û��ͼֽ�ĶԽ���


    _iColorIndex = 0; // ���ó�ʼ��ɫΪ��ɫ
}

// WM_PAINT ��Ϣ������Ĵ���
void CDrawingObject::Paint(CDC* pDC)
{
    double localScale = 1.0;

    localScale = max(_dScalingFactor, 0.05); 

    // ����һ���±�
    CPen pen(PS_SOLID,6,RGB(0,0,0));

    // ѡ���±ʣ�����ɵ�
    CPen* oldPen = pDC->SelectObject(&pen);

    // ���ȴ���һ�����ߣ�����������������stratched����
    POINT ptRect[5];    

    ptRect[0].x = -(LONG)(localScale * _iWidth/2);
    ptRect[0].y = -(LONG)(localScale * _iHeight/2);

    ptRect[1].x = (LONG)(localScale * _iWidth/2);
    ptRect[1].y = ptRect[0].y;

    ptRect[2].x = ptRect[1].x;
    ptRect[2].y = (LONG)(localScale * _iHeight/2);

    ptRect[3].x = ptRect[0].x;
    ptRect[3].y = ptRect[2].y;
    
    ptRect[4].x = ptRect[0].x;
    ptRect[4].y = ptRect[0].y;

  
    double dCos = cos(_dRotationAngle);
    double dSin = sin(_dRotationAngle);

    for(int i=0; i<5; i++)
    {
        LONG lDX = ptRect[i].x;
        LONG lDY = ptRect[i].y;

        ptRect[i].x = (LONG)(lDX*dCos + lDY*dSin);
        ptRect[i].y = (LONG)(lDY*dCos - lDX*dSin);
    }

    // �����������ת���ͼ�λ��Ƴ���
    for(int i=0; i<5; i++)
    {
        ptRect[i].x += _iCx;
        ptRect[i].y += _iCy;
    }    
	CRgn rgn;
	rgn.CreatePolygonRgn(ptRect,5,WINDING);

	CBrush brush;	
	brush.CreateSolidBrush(s_colors[_iColorIndex]);

	//pDC->FillRgn(&rgn, &brush);
    pDC->Polyline(ptRect,5);

    if(_bDrawDiagonals)
    {
        // ���ƶԽ���
        pDC->MoveTo(ptRect[0].x,ptRect[0].y);
        pDC->LineTo(ptRect[2].x,ptRect[2].y);
        pDC->MoveTo(ptRect[1].x,ptRect[1].y);
        pDC->LineTo(ptRect[3].x,ptRect[3].y);
    }

	pDC->SelectObject(oldPen);
}

//�˺��������ƶ����ε����ĵ㡣
// ������X�����
//�����ݼ���Y����
void CDrawingObject::Move(LONG ldx,LONG ldy)
{
    _iCx += ldx;
    _iCy += ldy;
}

//�˺�����������ھ���
// dZoomFactor - ���ŵ���������
// iZx - x����佹����
// iZy - y������������
void CDrawingObject::Zoom(const double dZoomFactor,const LONG iZx,const LONG iZy)
{
    _dScalingFactor *= dZoomFactor;
}

// �����û���ת���Ľ�����ת
void CDrawingObject::Rotate(const double dAngle,const LONG iOx,const LONG iOy)
{   
    _dRotationAngle += dAngle;
}