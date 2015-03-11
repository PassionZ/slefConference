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
	void 		SetType(int nType, int nNumber);			// ���ñ�׼ģ������	
	bool 		GetWndRect(int index, LPRECT lpRect);		// ���������������	
	RECT 		GetFreeRect();								// ���ʣ������	
	RECT 		GetMidRect();								// ����м䴰������	
	RECT 		GetControlRect();							// ��ÿ����������	
	int			GetWindowCount();							// ��ô�����
	void		SetScreenIndex(int nScreenIndex, RECT rcScreen);			// ������Ļ������,1.��׼��Ļ, 2.�ڶ�����Ļ
	int			GetScreenIndex();							// �����Ļ������
	void		GetScreenRect(LPRECT lpRect);				// ���ȫ��Ļ�ĳߴ�
	void		GetBigWindows(int iBigWindows[3]);			//�õ��󴰿�

private:
	int			m_nScreenIndex;								// ��Ļ����
	int			m_nWindowNumber;							// ������
	RECT		m_rectWindow[25];							// ���ڵ�λ��	
	bool		m_bSelected[25];							// �����Ƿ�ѡ��
	RECT		m_rectFree;									// ʣ������
	CRect		m_rectScreen;								// ��Ļ����
	CRect		m_rectControl;								// �����������
	CRect		m_rectMidWindow;							// �м䴰������

private:
	void SetInitParam();

	void SetTempletParam(int* pData, int nLeng);

public:
	void SetWindowSelected(byte iIndex,bool bSelect);
	bool GetWindowSelected(byte iIndex);
};

#endif