#pragma once


// CCpuCtrl

class CCpuCtrl : public CStatic
{
	DECLARE_DYNAMIC(CCpuCtrl)

public:
	CCpuCtrl();
	virtual ~CCpuCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

public:
	void SetGridHeight(int iNewHeight);
	void SetGridCount(int iNewCounts);
	void SetRefreshInterval(int iMs);
	void SetPicPath(CString strPicPath);

private:
	void GetCpuUsgesNt();
	void DrawCpuUsges();
	BOOL IsNt();
	void GetCpuUsges9X();

private:
	COLORREF        m_LableColor;
	COLORREF		m_ForeFontColor;
	COLORREF		m_ForeColor;
	COLORREF		m_BackColor;
	COLORREF		m_FreeColor;
	COLORREF		m_UsedColor;
	int				m_iGridHeight;
	int				m_iGridCount;
	int				m_iRefreshInterval;
	unsigned long	m_fNewUsges;
	LARGE_INTEGER   m_liOldIdleTime;
	LARGE_INTEGER   m_liOldSystemTime;

	CBitmap			m_bmpBk;
};


