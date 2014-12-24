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
    //����һ����ɫ����
    //���ɹ���״̬
    static const COLORREF s_colors[];
	// ���Ǳ������ľ��Σ��Խ���intesection�㣩
    long _iCx; 
    long _iCy; 
    // ������εĿ�Ⱥ͸߶�
    int     _iWidth; 
    int     _iHeight; 

    // �Ŵ���С�Ķ���
    double  _dScalingFactor; 

    //�洢������ת�Ƕȣ���X�ᣩ
    double  _dRotationAngle; 

    //��������������ƶԽ����������Ϊtrue
    bool    _bDrawDiagonals; 

    // ������������˾��Σ�������ɫ��
    int     _iColorIndex; 
};


