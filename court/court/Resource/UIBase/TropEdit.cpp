// TropEdit.cpp : ʵ���ļ�
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



// CTropEdit ��Ϣ�������


void CTropEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetParent()->PostMessage(WM_LBUTTONDOWN);

	//CEdit::OnLButtonDown(nFlags, point);
}
