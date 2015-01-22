// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__88998EBB_1AC8_46F1_9BD3_203A614BD168__INCLUDED_)
#define AFX_STDAFX_H__88998EBB_1AC8_46F1_9BD3_203A614BD168__INCLUDED_

#ifdef _WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable: 4786)  // identifier was truncated to 'number' characters in the debug information
#pragma warning(disable: 4503)  // identifier was truncated to 'number' characters in the debug information
#pragma warning(disable: 4800)  // identifier was truncated to 'number' characters in the debug information

#else
#define TRACE printf
#define AFX_EXT_CLASS
#define MAX_PATH 4096
#endif

//#ifdef WIN32
//#include <Afxtempl.h>;
//#endif

//#define NETTVANDBROADCAST

#include "../libHPNETIO/libHPNETIO.h"
#include "../libHPNETIO/AVMTSocket.h"
#include "../libHPNETIO/AVIOEventManager.h"
#ifdef NETTVANDBROADCAST
#include "./DataDefine/RSMsgdefine.h"
#else
#include "../DataDefine/RSMsgdefine.h"
#endif

extern char g_szModulePathFile[MAX_PATH];
extern int GetModulePathFile(char* szModulePathFile, char*szFullPath);
extern int GenModulePathFile();
const char* GetCurDateTime();


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__88998EBB_1AC8_46F1_9BD3_203A614BD168__INCLUDED_)
