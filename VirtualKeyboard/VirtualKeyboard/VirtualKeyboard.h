
// VirtualKeyboard.h : VirtualKeyboard Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CVirtualKeyboardApp:
// �йش����ʵ�֣������ VirtualKeyboard.cpp
//

class CVirtualKeyboardApp : public CWinAppEx
{
public:
	CVirtualKeyboardApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVirtualKeyboardApp theApp;
