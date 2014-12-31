// VirtualKeyboard.h : main header file for the VirtualKeyboard application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CVirtualKeyboardApp:
// See VirtualKeyboard.cpp for the implementation of this class
//

class CVirtualKeyboardApp : public CWinApp
{
public:
	CVirtualKeyboardApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVirtualKeyboardApp theApp;