// ButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "DlgYTPrevCtrl.h"
#include "ButtonEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonEx

CButtonEx::CButtonEx()
{
	m_nIndex = 0;
}

CButtonEx::~CButtonEx()
{
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	//{{AFX_MSG_MAP(CButtonEx)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonEx message handlers

void CButtonEx::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	DlgYTPrevCtrl* pParent = (DlgYTPrevCtrl*)GetParent();
	if (GetSafeHwnd() && pParent)
	{	
		if (pParent->m_bTabKeyDown)
		{
			pParent->SetButtonClick(m_nIndex);
			pParent->m_bTabKeyDown = false;		
		}
	}
}
