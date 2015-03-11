// VideoDropTarget.cpp : 实现文件
//

#include "stdafx.h"
#include "VideoDropTarget.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CVideoDropTarget
IMPLEMENT_DYNAMIC(CVideoDropTarget, CCmdTarget)
CVideoDropTarget::CVideoDropTarget()
	: m_hNotifyWnd(NULL)
{
	m_hFormatData = RegisterClipboardFormat(_T("DropVideoData"));
}

CVideoDropTarget::~CVideoDropTarget()
{
}


BEGIN_MESSAGE_MAP(CVideoDropTarget, COleDropTarget)
END_MESSAGE_MAP()



// CVideoDropTarget 消息处理程序

DROPEFFECT CVideoDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	DROPEFFECT dwEffect = DROPEFFECT_NONE;

	if ( pDataObject && pDataObject->GetGlobalData(m_hFormatData))
	{
		dwEffect = DROPEFFECT_COPY;
	}


    return dwEffect;
}

void CVideoDropTarget::OnDragLeave(CWnd* pWnd)
{
	COleDropTarget::OnDragLeave(pWnd);
}

DROPEFFECT CVideoDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	DROPEFFECT dwEffect = DROPEFFECT_NONE;

	if ( pDataObject && pDataObject->GetGlobalData (m_hFormatData))
	{
		dwEffect = DROPEFFECT_COPY;
	}

    return dwEffect;
}

BOOL CVideoDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropEffect, CPoint point)
{
	try{
	if (!pDataObject || pWnd==NULL)
		return FALSE;

	UINT		format = m_hFormatData;
	HGLOBAL     hg = pDataObject->GetGlobalData(format);

	if (hg)
	{		
		char	*pData = (char*)GlobalLock(hg);
		int		nLen = GlobalSize(hg);

		GlobalUnlock(hg);

		if (m_hNotifyWnd)
		{
			PostMessage(m_hNotifyWnd, WM_VIDEO_ON_DROP_NOTIFY, (WPARAM)pData, nLen);
		}		
	}

	}catch(...)
	{
		//AfxMessageBox("CVideoDropTarget::OnDrop");
	}
	return TRUE;
}
