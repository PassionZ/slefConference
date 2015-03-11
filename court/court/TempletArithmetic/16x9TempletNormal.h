#ifndef __16X9TEMPLETNORMAL_H__
#define __16X9TEMPLETNORMAL_H__

#include "TempletArithmetic.h"

#pragma once
/*
类名：	标准模板算法类
功能：	提供标准模板算法的算法。
*/

class C16x9TempletNormal: public CTempletArithmetic
{
public:
	C16x9TempletNormal(void);
	~C16x9TempletNormal(void);

public:
	void SetType(int nType, int nNumber);			// 设置标准模板类型	
	bool GetWndRect(int index, LPRECT lpRect);		// 根据索引获得区域	
	RECT GetFreeRect();								// 获得剩余区域	
	RECT GetMidRect();								// 获得中间窗口区域	
	RECT GetControlRect();							// 获得控制面板区域	
	int	GetWindowCount();							// 获得窗口数
	void SetScreenIndex(int nScreenIndex, RECT rcScreen);			// 设置屏幕索引号,1.标准屏幕, 2.第二个屏幕
	int	GetScreenIndex();							// 获得屏幕索引号
	void GetScreenRect(LPRECT lpRect);				// 获得全屏幕的尺寸
	void GetBigWindows(int iBigWindows[3]);			//得到大窗口
	void SetWindowSelected(byte iIndex,bool bSelect){};
	bool GetWindowSelected(byte iIndex){return false;};

private:
	void SetInitParam();

private:
	int			m_nScreenIndex;								// 屏幕索引
	int			m_nWindowNumber;							// 窗口数
	RECT		m_rectWindow[12];							// 窗口的位置	
	RECT		m_rectFree;									// 剩余区域
	CRect		m_rectScreen;								// 屏幕区域
	CRect		m_rectControl;								// 控制面板区域
	CRect		m_rectMidWindow;							// 中间窗口区域

private:
	// 设置模板1的参数
	void SetTempletParam1(void);
	void SetTempletParam2(void);
	void SetTempletParam3(void);
	void SetTempletParam4(void);
	void SetTempletParam5(void);
	void SetTempletParam6(void);
	void SetTempletParam7(void);
	void SetTempletParam34(void);                //N91
	void SetTempletParam31(void);                //N7
	void SetTempletParam32(void);                //N9, N71
	void SetTempletParam30();                    //N5
	void SetTempletParam11();              //wt 2008-05-21 1×1模板  类型为：11
	void SetTempletParam22();				// wt 2008-05-21 2×2模板  类型为：22
	void SetTempletParam12();              //wt 2008-05-26 1×1模板  类型为：12
	void SetTempletParam121();				// wt 2008-05-26 2×2模板  类型为：121

};

#endif