

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

    _bDrawDiagonals = false; // 没有图纸的对角线


    _iColorIndex = 0; // 设置初始颜色为黑色
}

// WM_PAINT 消息触发后的处理
void CDrawingObject::Paint(CDC* pDC)
{
    double localScale = 1.0;

    localScale = max(_dScalingFactor, 0.05); 

    // 创建一个新笔
    CPen pen(PS_SOLID,6,RGB(0,0,0));

    // 选择新笔，保存旧的
    CPen* oldPen = pDC->SelectObject(&pen);

    // 首先创建一个折线，它描述了缩放因子stratched矩形
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

    // 把这个矩形旋转后的图形绘制出来
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
        // 绘制对角线
        pDC->MoveTo(ptRect[0].x,ptRect[0].y);
        pDC->LineTo(ptRect[2].x,ptRect[2].y);
        pDC->MoveTo(ptRect[1].x,ptRect[1].y);
        pDC->LineTo(ptRect[3].x,ptRect[3].y);
    }

	pDC->SelectObject(oldPen);
}

//此函数负责移动矩形的中心点。
// 递增的X坐标减
//递增递减的Y坐标
void CDrawingObject::Move(LONG ldx,LONG ldy)
{
    _iCx += ldx;
    _iCy += ldy;
}

//此函数缩放输出在矩形
// dZoomFactor - 缩放的缩放因子
// iZx - x坐标变焦中心
// iZy - y坐标缩放中心
void CDrawingObject::Zoom(const double dZoomFactor,const LONG iZx,const LONG iZy)
{
    _dScalingFactor *= dZoomFactor;
}

// 根据用户旋转中心进行旋转
void CDrawingObject::Rotate(const double dAngle,const LONG iOx,const LONG iOy)
{   
    _dRotationAngle += dAngle;
}