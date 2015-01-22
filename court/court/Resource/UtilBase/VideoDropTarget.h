//#ifndef  __VIDEODROPTARGET_H__
//#define	__VIDEODROPTARGET_H__
//
#pragma once

#define		WM_VIDEO_ON_DROP_NOTIFY		WM_USER+1

// CVideoDropTarget ÃüÁîÄ¿±ê
class CVideoDropTarget : public COleDropTarget
{
protected:
	DECLARE_DYNAMIC(CVideoDropTarget)

public:
	CVideoDropTarget();
	virtual ~CVideoDropTarget();

	HWND	m_hNotifyWnd;
	UINT	m_hFormatData;
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave(CWnd* pWnd);
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropEffect, CPoint point);
};

//#endif