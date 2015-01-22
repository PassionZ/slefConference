// MeSlider.cpp : implementation file
//

#include "stdafx.h"
#include "MeSlider.h"
#include "../../Conference/YunTai/DlgPlayCtl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MeSlider

MeSlider::MeSlider()
{
    m_bDown=m_bKonb=false;
    m_nPos=0;
}

MeSlider::~MeSlider()
{
    m_bmpKnob.DeleteObject();
    m_bmpSlider.DeleteObject();
}


BEGIN_MESSAGE_MAP(MeSlider, CSliderCtrl)
    //{{AFX_MSG_MAP(MeSlider)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
    ON_WM_MBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_KEYDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MeSlider message handlers

void MeSlider::OnPaint() 
{
    CPaintDC dc(this);
    CRect rect;
    CDC memDC,knobDC;
    memDC.CreateCompatibleDC(&dc);
    knobDC.CreateCompatibleDC(&dc);
    CBitmap *pOldBmp=memDC.SelectObject(&m_bmpSlider);
    CBitmap *pOldBmpKnob;
    if(m_bDown)
        pOldBmpKnob=knobDC.SelectObject(&m_bmpKnobx);
    else
        pOldBmpKnob=knobDC.SelectObject(&m_bmpKnob);
    GetClientRect(&rect);	
    if(rect.Width()==86)
    {
        dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,227,16,SRCCOPY);
    }
    else
    {
        dc.StretchBlt(0,0,8,rect.Height(),&memDC,0,0,8,16,SRCCOPY);
        dc.StretchBlt(8,0,rect.Width()-16,rect.Height(),&memDC,8,0,1,16,SRCCOPY);
        dc.StretchBlt(rect.Width()-8,0,8,rect.Height(),&memDC,8,0,8,16,SRCCOPY);
    }
    int max,min;
    GetRange(min,max);
    if (max==0)
        max=1;
    int pos=GetPos();
    rect.right-=15;

    pos=pos*rect.Width()/max;
    dc.StretchBlt(pos,0,15,rect.Height(),&knobDC,0,0,15,16,SRCCOPY);
    memDC.SelectObject(pOldBmp);
    knobDC.SelectObject(pOldBmpKnob);
    memDC.DeleteDC();
    knobDC.DeleteDC();
}

BOOL MeSlider::OnEraseBkgnd(CDC* pDC) 
{	
    return true;
}

void MeSlider::OnSize(UINT nType, int cx, int cy) 
{
    CSliderCtrl::OnSize(nType, cx, cy);		
}
bool MeSlider::LoadBitmaps(UINT IDs,UINT IDk,UINT IDkx)
{
    if(!m_bmpKnob.LoadBitmap(IDk)) return false;
    if(!m_bmpSlider.LoadBitmap(IDs)) return false;
    if(!m_bmpKnobx.LoadBitmap(IDkx)) return false;
    return true;
}

void MeSlider::OnMButtonDown(UINT nFlags, CPoint point) 
{
    CSliderCtrl::OnMButtonDown(nFlags, point);
}

void MeSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{
    ((DlgPlayCtl*)GetParent())->OnSetPos(true,m_nPos);

    m_bDown=false;
    m_bKonb=false;
    ReleaseCapture();
    Invalidate();
    CSliderCtrl::OnLButtonUp(nFlags, point);
}

void MeSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if(!m_bDown)
    {
        ((DlgPlayCtl*)GetParent())->OnSetPos(false,m_nPos);
        SetCapture();
        CRect rect;
        GetClientRect(&rect);
        m_bDown=true;
        m_bKonb=true;
        ReDrawPoint(point);
    }
    //	CSliderCtrl::OnLButtonDown(nFlags, point);
}

void MeSlider::OnMouseMove(UINT nFlags, CPoint point) 
{
    if(m_bKonb)
        ReDrawPoint(point);
    CSliderCtrl::OnMouseMove(nFlags, point);
}

void MeSlider::ReDrawPoint(CPoint point)
{
    CRect rect;
    GetClientRect(&rect);
    int max,min;
    int pos;
    GetRange(min,max);
    rect.right-=15;
    if(point.x>rect.right)
    {
        SetPos(max);
        pos=max;
    }
    else
    {
        pos=max*point.x/rect.Width();
        SetPos(pos);
    }
    if(m_nPos!=pos)
        Invalidate();
    m_nPos=pos;
}


void MeSlider::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
    CSliderCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
    Invalidate();
}

