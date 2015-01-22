#ifndef __16X9TEMPLETNORMAL_H__
#define __16X9TEMPLETNORMAL_H__

#include "TempletArithmetic.h"

#pragma once
/*
������	��׼ģ���㷨��
���ܣ�	�ṩ��׼ģ���㷨���㷨��
*/

class C16x9TempletNormal: public CTempletArithmetic
{
public:
	C16x9TempletNormal(void);
	~C16x9TempletNormal(void);

public:
	void SetType(int nType, int nNumber);			// ���ñ�׼ģ������	
	bool GetWndRect(int index, LPRECT lpRect);		// ���������������	
	RECT GetFreeRect();								// ���ʣ������	
	RECT GetMidRect();								// ����м䴰������	
	RECT GetControlRect();							// ��ÿ����������	
	int	GetWindowCount();							// ��ô�����
	void SetScreenIndex(int nScreenIndex, RECT rcScreen);			// ������Ļ������,1.��׼��Ļ, 2.�ڶ�����Ļ
	int	GetScreenIndex();							// �����Ļ������
	void GetScreenRect(LPRECT lpRect);				// ���ȫ��Ļ�ĳߴ�
	void GetBigWindows(int iBigWindows[3]);			//�õ��󴰿�
	void SetWindowSelected(byte iIndex,bool bSelect){};
	bool GetWindowSelected(byte iIndex){return false;};

private:
	void SetInitParam();

private:
	int			m_nScreenIndex;								// ��Ļ����
	int			m_nWindowNumber;							// ������
	RECT		m_rectWindow[12];							// ���ڵ�λ��	
	RECT		m_rectFree;									// ʣ������
	CRect		m_rectScreen;								// ��Ļ����
	CRect		m_rectControl;								// �����������
	CRect		m_rectMidWindow;							// �м䴰������

private:
	// ����ģ��1�Ĳ���
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
	void SetTempletParam11();              //wt 2008-05-21 1��1ģ��  ����Ϊ��11
	void SetTempletParam22();				// wt 2008-05-21 2��2ģ��  ����Ϊ��22
	void SetTempletParam12();              //wt 2008-05-26 1��1ģ��  ����Ϊ��12
	void SetTempletParam121();				// wt 2008-05-26 2��2ģ��  ����Ϊ��121

};

#endif