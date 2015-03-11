#ifndef __TEMPLETNORMAL_H__
#define __TEMPLETNORMAL_H__
#pragma once

#include "TempletArithmetic.h"

/*
类名：	标准模板算法类
功能：	提供标准模板算法的算法。
*/

class CTempletNormal: public CTempletArithmetic
{
public:
	CTempletNormal(void);
	~CTempletNormal(void);

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

private:
	// 设置模板1的参数
	void SetTempletParam0(void);
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
	void SetTempletParam11(void);
	void SetTempletParam12(void);
	void SetTempletParam13(void);
	void SetTempletParam14(void);
	void SetTempletParam15();
	void SetTempletParam16();
	void SetTempletParam17();
	void SetTempletParam18();
	void SetTempletParam19();
	void SetTempletParam20();
	void SetTempletParam21();
	void SetTempletParam22();
	void SetTempletParam23();
	void SetTempletParam24();
	void SetTempletParam30();          //画中画
	
	void SetTempletParam33(void);     //N71 右边3个，左边一个
	void SetTempletParam32(void);    //N9 上面3个，下面1个
	void SetTempletParam34(void);     //N91 右边4个，左边一个
	void SetTempletParam31(void);    //N7 上面4个，下面一个
	void SetTempletParam35(void);     //4*4
	void SetTempletParam36(void);     //5*5
	void SetTempletParam120();              //wt 2008-05-26 1×2模板  类型为：120
	void SetTempletParam121();				// wt 2008-05-26 121模板  类型为：121
public:
	void SetWindowSelected(byte iIndex,bool bSelect);
	bool GetWindowSelected(byte iIndex);
};

#endif