#ifndef __TEMPLETFREE_H__
#define __TEMPLETFREE_H__

#include "TempletArithmetic.h"

#pragma once

/*
������	����ģ���㷨��
���ܣ�	�ṩ����ģ���㷨���㷨��
*/

class CTempletFree: public CTempletArithmetic
{
public:
	CTempletFree(void);
	~CTempletFree(void);

public:
	void 		SetType(int nType, int nNumber);			// ��������ģ������	
	void 		SetType(int nType){};						
	bool 		GetWndRect(int index, LPRECT lpRect);		// ���������������	
	RECT 		GetFreeRect();								// ���ʣ������	
	RECT 		GetMidRect();								// ����м䴰������	
	RECT 		GetControlRect();							// ��ÿ����������	
	int			GetWindowCount();							// ��ô�����
	void		SetScreenIndex(int nScreenIndex, RECT rcScreen);			// ������Ļ������,1.��׼��Ļ, 2.�ڶ�����Ļ
	int			GetScreenIndex();							// �����Ļ������
	void		GetScreenRect(LPRECT lpRect);				// ���ȫ��Ļ�ĳߴ�
	void		GetBigWindows(int iBigWindows[3]);			//�õ��󴰿�
	void		SetWindowSelected(byte iIndex,bool bSelect){};
	bool		GetWindowSelected(byte iIndex){return false;};
	
	bool		m_bShowBigWindow;
private:
	int			m_nScreenIndex;								// ��Ļ����
	int			m_nMaxWindowNumber;							// ��󴰿���
	int			m_nSideWindowNumber;						// ÿ�ߴ�����
	RECT		m_rectWindow[81];							// ���ڵ�λ��	
	RECT		m_rectFree;									// ʣ������
	CRect		m_rectScreen;								// ��Ļ����
	CRect		m_rectControl;								// �����������
	CRect		m_rectMidWindow;							// �м䴰������

private:
	void InitSetTempletParam(int& l, int& w, int& h);
	// ����ģ��1�Ĳ���
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