#pragma once


// CTitleStatic

class CTitleStatic : public CStatic
{
	DECLARE_DYNAMIC(CTitleStatic)

public:
	CTitleStatic();
	virtual ~CTitleStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

private:
	CString m_strPicPath;
	UINT m_iWidth;
	UINT m_iHeight;

public:
	void SetParms(CString strPngPicPath);
};


