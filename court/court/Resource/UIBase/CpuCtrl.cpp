// CpuCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CpuCtrl.h"
#include <atlimage.h>


// CCpuCtrl

#define SystemBasicInformation       0
#define SystemPerformanceInformation 2
#define SystemTimeInformation        3

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

typedef struct
{
	DWORD   dwUnknown1;
	ULONG   uKeMaximumIncrement;
	ULONG   uPageSize;
	ULONG   uMmNumberOfPhysicalPages;
	ULONG   uMmLowestPhysicalPage;
	ULONG   uMmHighestPhysicalPage;
	ULONG   uAllocationGranularity;
	PVOID   pLowestUserAddress;
	PVOID   pMmHighestUserAddress;
	ULONG   uKeActiveProcessors;
	BYTE    bKeNumberProcessors;
	BYTE    bUnknown2;
	WORD    wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
	LARGE_INTEGER   liIdleTime;
	DWORD           dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
	LARGE_INTEGER liKeBootTime;
	LARGE_INTEGER liKeSystemTime;
	LARGE_INTEGER liExpTimeZoneBias;
	ULONG         uCurrentTimeZoneId;
	DWORD         dwReserved;
} SYSTEM_TIME_INFORMATION;

IMPLEMENT_DYNAMIC(CCpuCtrl, CStatic)
CCpuCtrl::CCpuCtrl()
{
	m_iRefreshInterval = 10;
	m_fNewUsges        = 40;
	m_ForeFontColor    = RGB(0, 0, 0);
	m_ForeColor        = RGB(0, 150, 0);
	m_BackColor        = RGB(230,230,230);	//RGB(148, 148, 148);;//;	//RGB(0, 0, 0);	
	m_FreeColor		   = RGB(36, 35, 35);		//RGB(0, 80, 100);
	m_UsedColor        = RGB(0, 255, 84);		//RGB(0, 140, 0);
	m_LableColor       = RGB(255, 255, 0);
	m_iGridHeight      = 2;
	m_iGridCount       = 40;
	m_liOldIdleTime.QuadPart   = 0;
	m_liOldSystemTime.QuadPart = 0;
}

CCpuCtrl::~CCpuCtrl()
{
	m_bmpBk.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCpuCtrl, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



// CCpuCtrl 消息处理程序


void CCpuCtrl::OnPaint()
{ 
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	DrawCpuUsges(); 
}

BOOL CCpuCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
/*	CRect rc;
	GetClientRect(&rc);
	CDC   dcMem;  

	dcMem.CreateCompatibleDC(pDC);   
	CBitmap *pOldBitmap   =   dcMem.SelectObject(&m_bmpBk);  
	pDC->StretchBlt(0, 0, rc.Width(), rc.Height(),   
		&dcMem, 0, 0, rc.Width(), rc.Height(),SRCCOPY); 
	dcMem.DeleteDC();
*/

	return TRUE;
	//return CStatic::OnEraseBkgnd(pDC);
}

void CCpuCtrl::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

void CCpuCtrl::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(IsNt())
	{
		GetCpuUsgesNt();
	}
	else
	{
		GetCpuUsges9X();
	}

	Invalidate();

	CStatic::OnTimer(nIDEvent);
}

int CCpuCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void CCpuCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CStatic::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}

void CCpuCtrl::SetGridHeight(int iNewHeight)
{
	m_iGridHeight  = iNewHeight;
}

void CCpuCtrl::SetGridCount(int iNewCounts)
{
	m_iGridCount	= iNewCounts;
}

void CCpuCtrl::SetRefreshInterval(int iMs)
{
	m_iRefreshInterval = iMs;
	SetTimer(1, m_iRefreshInterval, NULL); 
}

void CCpuCtrl::GetCpuUsgesNt()
{
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
	SYSTEM_TIME_INFORMATION        SysTimeInfo;
	SYSTEM_BASIC_INFORMATION       SysBaseInfo;
	double                         dbIdleTime;
	double                         dbSystemTime;
	LONG                           status;
	typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);
	PROCNTQSI NtQuerySystemInformation;

	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(
		GetModuleHandle(_T("ntdll")),
		"NtQuerySystemInformation"
		);

	if (!NtQuerySystemInformation)
	{
		return;
	}

	// get number of processors in the system
	status = NtQuerySystemInformation(SystemBasicInformation,
		&SysBaseInfo,sizeof(SysBaseInfo),NULL);

	if (status != NO_ERROR)
	{
		return;
	}

	status = NtQuerySystemInformation(SystemTimeInformation,
		&SysTimeInfo,sizeof(SysTimeInfo),0);
	if (status!=NO_ERROR)
	{
		return;
	}

	// get new CPU's idle time
	status = NtQuerySystemInformation(SystemPerformanceInformation,
		&SysPerfInfo,sizeof(SysPerfInfo),NULL);

	if (status != NO_ERROR)
	{
		return;
	}

	// if it's a first call - skip it
	if (m_liOldIdleTime.QuadPart != 0)
	{
		// CurrentValue = NewValue - OldValue
		dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(m_liOldIdleTime);
		dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(m_liOldSystemTime);

		// CurrentCpuIdle = IdleTime / SystemTime
		dbIdleTime = dbIdleTime / dbSystemTime;

		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
		dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors + 0.5;

		m_fNewUsges = (UINT)dbIdleTime;
	}

	// store new CPU's idle and system time
	m_liOldIdleTime = SysPerfInfo.liIdleTime;
	m_liOldSystemTime = SysTimeInfo.liKeSystemTime;
}

void CCpuCtrl::DrawCpuUsges()
{
	CDC  memDC; 
	CClientDC dc(this);
	CBitmap memBitmap;
	CBitmap *pOldBitmap=NULL;

	CString strUsges;
	CPen FreePen;
	CPen UsedPen;
	CPen *pOldPen    = NULL;
	CPen *pOldMemPen = NULL;

	CRect rect;
	GetClientRect(&rect);

	FreePen.CreatePen(PS_SOLID,1,m_FreeColor);
	UsedPen.CreatePen(PS_SOLID,1,m_UsedColor);

	memDC.CreateCompatibleDC(&dc);
	pOldMemPen=memDC.SelectObject(&FreePen);
	memBitmap.CreateCompatibleBitmap(&dc,rect.right,rect.bottom);

	pOldBitmap=memDC.SelectObject(&memBitmap);

	memDC.FillSolidRect(&rect, m_BackColor);
//	CDC   dcMem;  

//	dcMem.CreateCompatibleDC(&memDC);   
//	pOldBitmap = memDC.SelectObject(&m_bmpBk);  
//	memDC.StretchBlt(0, 0, rect.Width(), rect.Height(),   
//		&dcMem, 5, 5, rect.Width(), rect.Height(),SRCCOPY); 
//	dcMem.DeleteDC();

	//draw unused

	int iBianju = 2;
	int h = rect.Height()-4;
	int iLeft = rect.Width()*2/5;
	int iLeft2 = rect.Width()*2/5 + rect.Width()*3/10 - iBianju/2;
	for(int i=2;i<=h;i+=2)
	{
		memDC.MoveTo(iLeft,rect.bottom-iBianju-i);
		memDC.LineTo(iLeft2 - 1,rect.bottom-iBianju-i);
		memDC.MoveTo(iLeft2 + 1,rect.bottom-iBianju-i);
		memDC.LineTo(rect.right-iBianju,rect.bottom-iBianju-i);
	}

	memDC.SelectObject(&UsedPen);

	CString str;
	str.Format(_T("%3d%%"),m_fNewUsges);

	CFont m_Font;
	m_Font.CreateFont(14,          // nHeight
		5,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial")
		);

	CFont *pFont=memDC.SelectObject(&m_Font);
	memDC.SetTextColor(m_ForeFontColor);
	memDC.SetBkMode(TRANSPARENT);
	memDC.TextOut(0,7/*12*/,str);
	//memDC.TextOut(3,1,_T("CPU"));
	//memDC.TextOut(m_rect.Width()/5,m_rect.Height()*2/3,str);
	//memDC.TextOut(m_rect.Width()/5,m_rect.Height()/3,"CPU");

	h = h*m_fNewUsges/100;
	for(int m=0;m<h;m+=2)
	{
		memDC.MoveTo(iLeft,rect.bottom-iBianju-m);
		memDC.LineTo(iLeft2-1,rect.bottom-iBianju-m);
		memDC.MoveTo(iLeft2+1,rect.bottom-iBianju-m);
		memDC.LineTo(rect.right-iBianju,rect.bottom-iBianju-m);
	}

	dc.BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.SelectObject(pOldMemPen);
	memDC.DeleteDC();
	memBitmap.DeleteObject();

}

BOOL CCpuCtrl::IsNt()
{
	DWORD winVer;

	winVer = GetVersion();

	if(winVer<0x80000000)
	{
		return TRUE;
	}

	return FALSE;
}

void CCpuCtrl::GetCpuUsges9X()
{
	HKEY hkey;
	DWORD dwDataSize;
	DWORD dwType;
	DWORD dwCpuUsage;

	// starting the counter
	if ( RegOpenKeyEx( HKEY_DYN_DATA,
		_T("PerfStats\\StartStat"),
		0,KEY_ALL_ACCESS,
		&hkey ) != ERROR_SUCCESS
		)
	{
		return;
	}

	dwDataSize=sizeof(DWORD);
	RegQueryValueEx( hkey,
		_T("KERNEL\\CPUUsage"),
		NULL,&dwType,
		(LPBYTE)&dwCpuUsage,
		&dwDataSize );

	RegCloseKey(hkey);

	// geting current counter's value
	if ( RegOpenKeyEx( HKEY_DYN_DATA,
		_T("PerfStats\\StatData"),
		0,KEY_READ,
		&hkey ) != ERROR_SUCCESS)
	{
		return;
	}

	dwDataSize=sizeof(DWORD);
	RegQueryValueEx( hkey,
		_T("KERNEL\\CPUUsage"),
		NULL,&dwType,
		(LPBYTE)&dwCpuUsage,
		&dwDataSize );

	m_fNewUsges = dwCpuUsage;
	RegCloseKey(hkey);

	// stoping the counter
	if ( RegOpenKeyEx( HKEY_DYN_DATA,
		_T("PerfStats\\StopStat"),
		0,KEY_ALL_ACCESS,
		&hkey ) != ERROR_SUCCESS)
	{
		return;
	}

	dwDataSize=sizeof(DWORD);
	RegQueryValueEx( hkey,
		_T("KERNEL\\CPUUsage"),
		NULL,&dwType,
		(LPBYTE)&dwCpuUsage,
		&dwDataSize );

	RegCloseKey(hkey);
}

void CCpuCtrl::SetPicPath(CString strPicPath)
{
	CImage imgTemp;
	imgTemp.Load(strPicPath);
	if ( m_bmpBk.m_hObject ) 
		m_bmpBk.Detach();
	m_bmpBk.Attach(imgTemp.Detach());
}