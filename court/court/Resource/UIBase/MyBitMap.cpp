#include "StdAfx.h"
#include ".\mybitmap.h"

CMyBitMap::CMyBitMap(void)
{
	m_hBitMap = NULL ; 
}

CMyBitMap::~CMyBitMap(void)
{
	if(m_hBitMap) 
		DeleteObject(m_hBitMap);
}

void CMyBitMap::SetBitmap(UINT uResID)
{	
	if(m_hBitMap) 
		DeleteObject(m_hBitMap) ;
	m_hBitMap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(uResID));
	if( m_hBitMap )
	{
		::GetObject(m_hBitMap,sizeof(BITMAP),&m_bmp);
	}
}

void CMyBitMap::SetBitmap(const char * pBitMapFile)
{	
	if(m_hBitMap) 
		DeleteObject(m_hBitMap) ;

	CString strPath;
	strPath.Format(_T("%s\\%s"),GetExePath(),CA2W(pBitMapFile));
	//LPCWSTR lpWSTR;
	//lpWSTR = CA2W(pBitMapFile);
	m_hBitMap = (HBITMAP)::LoadImage(_AtlBaseModule.GetResourceInstance(),strPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if( m_hBitMap )
	{
		if( ::GetObject(m_hBitMap,sizeof(BITMAP),&m_bmp) )
		{				
		}
		else
			DeleteObject( m_hBitMap ) ;
	}
}

//在设备上进行画,原点，目标坐标,拉伸
bool CMyBitMap::drawOnDc( HDC hDC, long lx, long ly, long lex, long ley ) 
{
	if( !m_hBitMap )
		return false;
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	if(!hMemDC)
		return false;
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,m_hBitMap);
	::StretchBlt(hDC,lx,ly,lex-lx,ley-ly,hMemDC,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
	::SelectObject(hMemDC,hOldBmp);
	DeleteDC( hMemDC ) ;
	return true;
}

//在设备上进行画,原点，宽，高,只画图像大小
bool CMyBitMap::drawOnDcN( HDC hDC, long lx, long ly ) 
{
	if( !m_hBitMap )
		return false;
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	if(!hMemDC)
		return false;
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,m_hBitMap);
	::BitBlt(hDC,lx,ly,m_bmp.bmWidth,m_bmp.bmHeight,hMemDC,0,0,SRCCOPY);
	::SelectObject(hMemDC,hOldBmp);
	DeleteDC( hMemDC ) ;
	return 0 ;
}
//平铺
bool CMyBitMap::drawOnDcNXY( HDC hDC, long lsx, long lsy, long lex, long ley ) 
{
	if( !m_hBitMap )
		return false;
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	if(!hMemDC)
		return false;
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,m_hBitMap);
	long lh = 0 ;
	long lx = lsx ;
	for( ; lsy < ley ; )
	{
		if( ley - lsy > m_bmp.bmHeight )
			lh = m_bmp.bmHeight ;
		else
			lh = ley -lsy ;

		for( lsx = lx ;lsx < lex ; )
		{
			if( lex - lsx > m_bmp.bmWidth )
			{
				::BitBlt(hDC,lsx,lsy,m_bmp.bmWidth,lh,hMemDC,0,0,SRCCOPY);
				lsx += m_bmp.bmWidth ;
			}
			else
			{
				::BitBlt(hDC,lsx,lsy,lex - lsx,lh,hMemDC,0,0,SRCCOPY);
				lsx = lex ;

			}
		}
		lsy += lh ;
	}
	::SelectObject(hMemDC,hOldBmp);
	DeleteDC( hMemDC ) ;
	return true ;
}