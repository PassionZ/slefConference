
// Scratchpad.h : Scratchpad Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CScratchpadApp:
// �йش����ʵ�֣������ Scratchpad.cpp
//

class CScratchpadApp : public CWinAppEx
{
public:
	CScratchpadApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CScratchpadApp theApp;
