#if !defined(AFX_BMPBKBUTTON_H__1A8FA76C_FFF5_409C_A0EE_4E24947B4A2B__INCLUDED_)
#define AFX_BMPBKBUTTON_H__1A8FA76C_FFF5_409C_A0EE_4E24947B4A2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpBkButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBmpBkButton window

class CBmpBkButton : public CButton
{
// Construction
public:
	CBmpBkButton();
    virtual ~CBmpBkButton();

    virtual void SetBitmap(CImageList *pImageList, UINT nIDOver , 
        UINT nIDLeave , UINT nIDPressed , UINT nIDDisable = 0xffffffff);
	virtual void SetBitmap(UINT nIDOver , UINT nIDLeave , UINT nIDPressed );
    
	virtual void ShowBorder(BOOL bShow);
	virtual void SetChecked(BOOL bChecked);
	virtual BOOL IsChecked();

	virtual void SetButtonText(const CString &strText, COLORREF color=RGB(0,0,0));
	virtual CString GetButtonText();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpBkButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	//{{AFX_MSG(CBmpBkButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	virtual void DrawText(CDC *pDC, const CRect &rect);		//按钮上的文字
	virtual void DrawBkBitmap(CDC *pDC, const CRect &rect);	//背景图
	virtual void DrawOutsideBorder(CDC *pDC, const CRect &rect);	//外边框
	virtual void DrawInsideBorder(CDC *pDC, const CRect &rect);		//内边框
	virtual void TestPressed(const LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void Do_MouseLeave();

	BOOL m_bSetEvent;		//是否设置鼠标时间
	BOOL m_bOver, m_bPressed; //鼠标在按钮上, 鼠标按下
	BOOL m_bShowBorder;	
	BOOL m_bChecked;	//是否选中

	COLORREF m_color;
	CString m_strText;	//按钮上的文字

	//
	void ClearBitmap();
	CBitmap *m_pBmpOver, *m_pBmpLeave, *m_pBmpPressed, *m_pBmpDisable;
private:
    void GetImageFromList(CImageList *pSrcImageList, int nImage, CBitmap* pBitmap);
public:
    virtual BOOL DestroyWindow();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPBKBUTTON_H__1A8FA76C_FFF5_409C_A0EE_4E24947B4A2B__INCLUDED_)
