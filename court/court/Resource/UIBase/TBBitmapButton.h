#if !defined(__TBBITMAPBUTTON_H__)
#define __TBBITMAPBUTTON_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef	struct tag_BITMAP_BUTTON
{
	RECT	rc;				//区域
	int		status;			//状态 0.正常, 1.按下
}BITMAP_BUTTON, *PBITMAP_BUTTON;

#define		MAX_BUTTON			10

#define		TBBUTTON_NORMAL		0
#define		TBBUTTON_MOVE		1
#define		TBBUTTON_CHECK		2
#define		TBBUTTON_DISABLE	3

class /*AFX_EXT_CLASS*/ CTBBitmapButton  
{
public:
	CTBBitmapButton();
	virtual ~CTBBitmapButton();

public:
	void				SetBitmapRes(UINT uBitmapRes, HINSTANCE hInstance, int nNumber, SIZE size, POINT posFirst);

	void				OnDraw(HWND hWnd);
	void				OnDraw(HDC hDC);	
	
	void				OnMouseMove(HWND hWnd, POINT pt);
	int					HitTest(POINT pt);

	void				SetCheck(int index, int nStatus);
	int					GetCheck(int index);

	void				GetRect(int index, LPRECT lpRect);
	void				SetFirstPoint(POINT pt);

private:
	void				OnMouseMoveDraw(int index, HWND hWnd);
	void				OnMouseMoveDraw(int index, HDC hDC);

	UINT				m_uBitmapRes;
	HINSTANCE			m_hInstance;

	BITMAP_BUTTON		m_btnBitmap[MAX_BUTTON];
	int					m_nButtonNumber;
	SIZE				m_sizeButton;

	POINT				m_ptFirstPos;

	bool				m_bReset;
};


void DrawBitmapToDC(HDC hDC, HBITMAP hBitmap, int x, int y, int cx, int cy, int sx, int sy);
void DrawTransBitmapToDC(HDC hDC, HBITMAP hBitmap, int x, int y, int cx, int cy, int sx, int sy);
BOOL TBTransparentBlt(
					  HDC hdcDest,                 // handle to destination DC
					  int nXOriginDest,            // x-coord of upper-left corner
					  int nYOriginDest,            // y-coord of upper-left corner
					  int nWidthDest,              // destination width
					  int nHeightDest,             // destination height
					  HDC hdcSrc,                  // handle to source DC
					  int nXOriginSrc,             // y-coord of upper-left corner
					  int nYOriginSrc,             // x-coord of upper-left corner
					  int nWidthSrc,               // source width
					  int nHeightSrc,              // source height
					  COLORREF clrTransparent		// alpha-blending function
					  );

#endif
