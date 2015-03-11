#ifndef __TEMPLETFREE_H__
#define __TEMPLETFREE_H__

#include "TempletArithmetic.h"

#pragma once

/*
类名：	自由模板算法类
功能：	提供自由模板算法的算法。
*/

class CTempletFree: public CTempletArithmetic
{
public:
	CTempletFree(void);
	~CTempletFree(void);

public:
	void 		SetType(int nType, int nNumber);			// 设置自由模板类型	
	void 		SetType(int nType){};						
	bool 		GetWndRect(int index, LPRECT lpRect);		// 根据索引获得区域	
	RECT 		GetFreeRect();								// 获得剩余区域	
	RECT 		GetMidRect();								// 获得中间窗口区域	
	RECT 		GetControlRect();							// 获得控制面板区域	
	int			GetWindowCount();							// 获得窗口数
	void		SetScreenIndex(int nScreenIndex, RECT rcScreen);			// 设置屏幕索引号,1.标准屏幕, 2.第二个屏幕
	int			GetScreenIndex();							// 获得屏幕索引号
	void		GetScreenRect(LPRECT lpRect);				// 获得全屏幕的尺寸
	void		GetBigWindows(int iBigWindows[3]);			//得到大窗口
	void		SetWindowSelected(byte iIndex,bool bSelect){};
	bool		GetWindowSelected(byte iIndex){return false;};
	
	bool		m_bShowBigWindow;
private:
	int			m_nScreenIndex;								// 屏幕索引
	int			m_nMaxWindowNumber;							// 最大窗口数
	int			m_nSideWindowNumber;						// 每边窗口数
	RECT		m_rectWindow[81];							// 窗口的位置	
	RECT		m_rectFree;									// 剩余区域
	CRect		m_rectScreen;								// 屏幕区域
	CRect		m_rectControl;								// 控制面板区域
	CRect		m_rectMidWindow;							// 中间窗口区域

private:
	void InitSetTempletParam(int& l, int& w, int& h);
	// 设置模板1的参数
	void SetTempletParam1(void);
	void SetTempletParam2(void);
	void SetTempletParam3(void);
	void SetTempletParam4(void);
	void SetTempletParam5(void);
	void SetTempletParam6(void);
	void SetTempletParam7(void);
	void SetTempletParam8(void);
	void SetTempletParam9(void);
	void SetTempletParam10(void);	
};
#endif