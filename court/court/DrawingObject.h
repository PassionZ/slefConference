#pragma once
#include "stdafx.h"
//#include <windows.h>
#include <math.h>


#define MAX_COLORS 5
#define PI 3.1415926535897932384626433832795

// CDrawingObject class holds information about rectangle. Instead of storing

class CDrawingObject
{
public:
    CDrawingObject(void);

    void ResetObject(const int cxClient,const int cyClient);

    void Paint(CDC* pDC);
    void Move(LONG ldx,LONG ldy);
    void TogleDrawDiagonals(void){_bDrawDiagonals = !_bDrawDiagonals;}
    void Zoom(const double dZoomFactor,const LONG iZx,const LONG iZy);
    void Rotate(const double dAngle,const LONG iOx,const LONG iOy);
    void ShiftColor(void);

public:
    ~CDrawingObject(void);

private:
    //这是一个颜色数组
    //生成过渡状态
    static const COLORREF s_colors[];
	// 我们保留中心矩形（对角线intesection点）
    long _iCx; 
    long _iCy; 
    // 定义矩形的宽度和高度
    int     _iWidth; 
    int     _iHeight; 

    // 放大缩小的定义
    double  _dScalingFactor; 

    //存储矩形旋转角度（从X轴）
    double  _dRotationAngle; 

    //这个变量触发绘制对角线如果设置为true
    bool    _bDrawDiagonals; 

    // 这个变量定义了矩形（索引颜色）
    int     _iColorIndex; 
};


