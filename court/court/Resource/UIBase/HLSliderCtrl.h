#if !defined(AFX_HLSliderCtrl_H__C57F008B_7FC4_4881_87BA_5FAH__INCLUDED_20090904_)
#define AFX_HLSliderCtrl_H__C57F008B_7FC4_4881_87BA_5FAH__INCLUDED_20090904_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHLSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHLSliderCtrl window

class CHLSliderCtrl : public CSliderCtrl
{
    // Construction
public:
    CHLSliderCtrl();


    // Attributes
public:
	DWORD GetPosEx();
	void SetPosEx(DWORD pos);
    bool LoadBitmaps(UINT IDs,UINT IDk,UINT IDkx); 
	void LoadBitmaps(CString strPathbackdrop/*����ͼƬ·��*/, CString strPathPiece/*��̬����ͼƬ·��*/,  CString strPathPieceDown/*��갴�·���ͼƬ·��*/, CString strLeftPath/*���������������ͼ*/);
    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHLSliderCtrl)
    //}}AFX_VIRTUAL

    // Implementation

    virtual ~CHLSliderCtrl();

private:
	void ReDrawPoint(CPoint point);

    // Generated message map functions
protected:
    //{{AFX_MSG(CHLSliderCtrl)
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

private:
	CBitmap		m_bmpBackdrop;		// ����ͼƬ
	CBitmap		m_bmpPiece;			// �ƿ�ͼƬ
	CBitmap		m_bmpPieceDown;		// ��갴���ƿ�ͼƬ
	CBitmap		m_bmpLeft;			// һ����ߵ�ͼƬ
	bool		m_bKonb;
	DWORD		m_nPos;
	bool		m_bDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESLIDER_H__C57F008B_7FC4_4881_87BA_5FA9D8A9C28C__INCLUDED_)
