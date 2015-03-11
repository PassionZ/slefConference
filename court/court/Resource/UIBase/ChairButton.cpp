// ChairButton.cpp : 实现文件
//

#include "stdafx.h"
#include "ChairButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CChairButton

IMPLEMENT_DYNAMIC(CChairButton, CBmpBkButton)
CChairButton::CChairButton()
{
	SetChairIndex();
}

CChairButton::~CChairButton()
{
}


BEGIN_MESSAGE_MAP(CChairButton, CBmpBkButton)
END_MESSAGE_MAP()


void CChairButton::SetChairIndex(int nIndex)
{
	m_nIndex = nIndex;
}

int CChairButton::GetChairIndex()
{
	return m_nIndex;
}



// CChairButton 消息处理程序

