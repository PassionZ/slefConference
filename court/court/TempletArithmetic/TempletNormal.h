#ifndef __TEMPLETNORMAL_H__
#define __TEMPLETNORMAL_H__
#pragma once

#include "TempletArithmetic.h"

/*
������	��׼ģ���㷨��
���ܣ�	�ṩ��׼ģ���㷨���㷨��
*/

class CTempletNormal: public CTempletArithmetic
{
public:
	CTempletNormal(void);
	~CTempletNormal(void);

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

private:
	// ����ģ��1�Ĳ���
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
	void SetTempletParam30();          //���л�
	
	void SetTempletParam33(void);     //N71 �ұ�3�������һ��
	void SetTempletParam32(void);    //N9 ����3��������1��
	void SetTempletParam34(void);     //N91 �ұ�4�������һ��
	void SetTempletParam31(void);    //N7 ����4��������һ��
	void SetTempletParam35(void);     //4*4
	void SetTempletParam36(void);     //5*5
	void SetTempletParam120();              //wt 2008-05-26 1��2ģ��  ����Ϊ��120
	void SetTempletParam121();				// wt 2008-05-26 121ģ��  ����Ϊ��121
public:
	void SetWindowSelected(byte iIndex,bool bSelect);
	bool GetWindowSelected(byte iIndex);
};

#endif