// TropEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "TropEdit.h"
#include ".\tropedit.h"


// CTropEdit

IMPLEMENT_DYNAMIC(CTropEdit, CEdit)
CTropEdit::CTropEdit()
{
}

CTropEdit::~CTropEdit()
{
}


BEGIN_MESSAGE_MAP(CTropEdit, CEdit)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CTropEdit 消息处理程序


void CTropEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetParent()->PostMessage(WM_LBUTTONDOWN);

	//CEdit::OnLButtonDown(nFlags, point);
}
