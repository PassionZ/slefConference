// TransControlButton.cpp : 实现文件
//

#include "stdafx.h"
#include "TransControlButton.h"
#include "BmpControlButton.h"
#include ".\transcontrolbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CTransControlButton

IMPLEMENT_DYNAMIC(CTransControlButton, CButtonST)
CTransControlButton::CTransControlButton()
{
	m_Type = -1;
}

CTransControlButton::~CTransControlButton()
{
}


BEGIN_MESSAGE_MAP(CTransControlButton, CButtonST)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CTransControlButton 消息处理程序


void CTransControlButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetParent()->PostMessage( WM_LEFT_BUTTON_DOWN, (WPARAM)this, (LPARAM)m_Type);

	CButtonST::OnLButtonDown(nFlags, point);
}

void CTransControlButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	GetParent()->PostMessage( WM_LEFT_BUTTON_UP, (WPARAM)this , (LPARAM)m_Type);

	CButtonST::OnLButtonUp(nFlags, point);
}

void CTransControlButton::SetType(int nType)
{
	m_Type = nType;
}

void CTransControlButton::SetContent(CString strContent)
{
	m_strContent = strContent;
}

void CTransControlButton::CreateToolTip(const TCHAR *pTitle, UINT nDelay)
{
	//_tcsncpy(m_szTitle, pTitle, _tcslen(pTitle));
	//m_strContent = pTitle;
	m_toolTip.Create(this, TTS_ALWAYSTIP);
	m_toolTip.AddTool(this);
	m_toolTip.SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
	m_toolTip.SetDelayTime(nDelay);
}

void CTransControlButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (IsWindow(m_toolTip.m_hWnd))
	{
		//_itot(nPos, m_szTitle, 10);		
		//m_toolTip.SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
		m_toolTip.UpdateTipText(m_strContent.GetBuffer(), this);
	}
	CButtonST::OnMouseMove(nFlags, point);
}

BOOL CTransControlButton::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (IsWindow(m_toolTip.m_hWnd)) 
	{
		m_toolTip.RelayEvent(pMsg);
	}
	return CButtonST::PreTranslateMessage(pMsg);
}
