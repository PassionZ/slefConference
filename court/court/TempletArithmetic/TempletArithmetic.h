#ifndef __LIBAVTM_H__
#define __LIBAVTM_H__

class CTempletArithmetic
{
public:	
	CTempletArithmetic(){m_bIsPictureInPicture = FALSE; m_bIsTempleteControl = FALSE;m_bRepairTemplet=FALSE;};
	BOOL IsRepairTemplet(){return m_bRepairTemplet;};
	BOOL GetIsPictureInPicture(){return m_bIsPictureInPicture;};
	void SetIsTempleteControl(BOOL bIsTempleteControl){m_bIsTempleteControl = bIsTempleteControl;};
	virtual void SetType(int nType, int nNumber) = 0;
	virtual bool GetWndRect(int index, LPRECT lpRect) = 0;
	virtual RECT GetFreeRect() = 0;
	virtual RECT GetMidRect() = 0;
	virtual RECT GetControlRect() = 0;
	virtual int	GetWindowCount() = 0;
	virtual void SetScreenIndex(int nScreenIndex, RECT rcScreen) = 0;
	virtual int	GetScreenIndex() = 0;
	virtual void GetScreenRect(LPRECT lpRect) = 0;
	virtual void GetBigWindows(int iBigWindows[3]) = 0;						//得到大窗口
	virtual void SetWindowSelected(byte iIndex,bool bSelect) = 0;
	virtual bool GetWindowSelected(byte iIndex) = 0;
protected:
	int		m_nBigWindows[3];
	BOOL    m_bIsPictureInPicture;
	BOOL    m_bIsTempleteControl;
	BOOL	m_bRepairTemplet;
};

#endif