#if !defined(AFX_MESLIDER_H__C57F008B_7FC4_4881_87BA_5FA9D8A9C28C__INCLUDED_)
#define AFX_MESLIDER_H__C57F008B_7FC4_4881_87BA_5FA9D8A9C28C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MeSlider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MeSlider window

class MeSlider : public CSliderCtrl
{
    // Construction
public:
    MeSlider();
    CBitmap m_bmpSlider;
    CBitmap m_bmpKnob;
    CBitmap m_bmpKnobx;

    // Attributes
public:
    bool LoadBitmaps(UINT IDs,UINT IDk,UINT IDkx); 
    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MeSlider)
    //}}AFX_VIRTUAL

    // Implementation
public:
    bool m_bKonb;
    void ReDrawPoint(CPoint point);
    int m_nPos;
    bool m_bDown;
    virtual ~MeSlider();

    // Generated message map functions
protected:
    //{{AFX_MSG(MeSlider)
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESLIDER_H__C57F008B_7FC4_4881_87BA_5FA9D8A9C28C__INCLUDED_)
