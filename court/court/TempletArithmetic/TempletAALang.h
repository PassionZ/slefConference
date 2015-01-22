#ifndef __TEMPLET3500_H__
#define __TEMPLET3500_H__
#pragma once

#include "TempletArithmetic.h"


class CTempletAALang: public CTempletArithmetic
{
public:
	CTempletAALang(void);
	~CTempletAALang(void);

public:
	void 		SetType(int nType, int nNumber);			// 设置标准模板类型	
	bool 		GetWndRect(int index, LPRECT lpRect);		// 根据索引获得区域	
	RECT 		GetFreeRect();								// 获得剩余区域	
	RECT 		GetMidRect();								// 获得中间窗口区域	
	RECT 		GetControlRect();							// 获得控制面板区域	
	int			GetWindowCount();							// 获得窗口数
	void		SetScreenIndex(int nScreenIndex, RECT rcScreen);			// 设置屏幕索引号,1.标准屏幕, 2.第二个屏幕
	int			GetScreenIndex();							// 获得屏幕索引号
	void		GetScreenRect(LPRECT lpRect);				// 获得全屏幕的尺寸
	void		GetBigWindows(int iBigWindows[3]);			//得到大窗口

private:
	int			m_nScreenIndex;								// 屏幕索引
	int			m_nWindowNumber;							// 窗口数
	RECT		m_rectWindow[25];							// 窗口的位置	
	bool		m_bSelected[25];							// 窗口是否被选中
	RECT		m_rectFree;									// 剩余区域
	CRect		m_rectScreen;								// 屏幕区域
	CRect		m_rectControl;								// 控制面板区域
	CRect		m_rectMidWindow;							// 中间窗口区域

private:
	void SetInitParam();

	void SetTempletParam(int* pData, int nLeng);

public:
	void SetWindowSelected(byte iIndex,bool bSelect);
	bool GetWindowSelected(byte iIndex);
};

#endif