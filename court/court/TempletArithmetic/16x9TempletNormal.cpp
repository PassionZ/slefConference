#include "StdAfx.h"
#include "16x9templetnormal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

C16x9TempletNormal::C16x9TempletNormal(void)
{
	m_nWindowNumber			= 0;
	m_nScreenIndex			= 1;
//	m_rectScreen			= AfxGetScreenRect();
}

C16x9TempletNormal::~C16x9TempletNormal(void)
{
}

// 设置标准模板类型
void C16x9TempletNormal::SetType(int nType,int nNumber)
{
	m_nWindowNumber = 0;		//预赋值为0
	m_bRepairTemplet=FALSE;

	memset(&m_rectFree, 0, sizeof(RECT));
	m_rectMidWindow.SetRect(0, 0, 0, 0);

	//if ((m_nScreenIndex==1) && (nType==6))
	//{
	//	nType = 5;
	//}
	if (nType<1)
		nType = 1;
	/*if (nType>7)
		nType = 7;*/

	switch(nType)
	{
	case 1:	// 2x2模板
		SetTempletParam1();	
		break;
	case 2:	// 2x1模板
		SetTempletParam2();	
		break;
	case 3:	// 3x2模板
		SetTempletParam3();	
		break;
	case 4:
		SetTempletParam4();	
		break;
	case 5:
		SetTempletParam5();	
		break;
	case 6:
		SetTempletParam6();	
		m_bRepairTemplet = TRUE;
		break;
	case 7:
		SetTempletParam7();	
		m_bRepairTemplet = TRUE;
		break;
	case 30:
		SetTempletParam30();
		break;
	case 31:
		SetTempletParam31();
		break;
	case 32:
		SetTempletParam32();
		break;
	case 34:
		SetTempletParam34();
		break;
	case 11://wt
		SetTempletParam11();
		break;
	case 22://wt
		SetTempletParam22();
		break;
	case 12://wt
		SetTempletParam12();
		break;
	case 121://wt
		SetTempletParam121();
		break;
	}

	m_nBigWindows[0] = -1;
	m_nBigWindows[1] = -1;
	m_nBigWindows[2] = -1;
	switch (nType)
	{
	case 3:
		m_nBigWindows[0] = 4;
		break;
	case 4:
		m_nBigWindows[0] = 5;
		m_nBigWindows[1] = 6;
		break;
	case 5:
		m_nBigWindows[0] = 9;
		break;
	case 6:
		m_nBigWindows[0] = 6;
		break;
	case 7:
		m_nBigWindows[0] = 1;
		m_nBigWindows[1] = 2;
		break;
	case 30:
		m_nBigWindows[0] = 1;
		break;
	case 31:
		m_nBigWindows[0] = 1;
		break;
	case 32:
		m_nBigWindows[0] = 1;
		break;
	case 34:
		m_nBigWindows[0] = 1;
		break;
	case 11://wt
		m_nBigWindows[0] = 1;
		break;
	case 22://wt
		m_nBigWindows[0] = 1;
	case 12://wt
		m_nBigWindows[0] = 1;
		break;
	case 121://wt
		m_nBigWindows[0] = 1;
		break;
	}
}

// 根据索引获得区域
bool C16x9TempletNormal::GetWndRect(int index, LPRECT lpRect)
{
	if ((index>20) || (index>m_nWindowNumber))
		return false;

	*lpRect=m_rectWindow[index];
	return true;
}

// 获得剩余区域
RECT C16x9TempletNormal::GetFreeRect()
{
	return m_rectFree;
}

// 获得中间窗口区域
RECT C16x9TempletNormal::GetMidRect()
{
	return m_rectMidWindow;
}

// 获得控制面板区域
RECT C16x9TempletNormal::GetControlRect()
{
	return m_rectControl;
}

// 窗口数
int	C16x9TempletNormal::GetWindowCount()
{
	return m_nWindowNumber;
}

// 设置屏幕索引号,1.标准屏幕, 2.第二个屏幕
void C16x9TempletNormal::SetScreenIndex(int nScreenIndex, RECT rcScreen)
{
	m_rectScreen = rcScreen;
	m_nScreenIndex = nScreenIndex;
}

// 获得全屏幕的尺寸
void	C16x9TempletNormal::GetScreenRect(LPRECT lpRect)
{
	if (lpRect)
	{
		*lpRect	= m_rectScreen;
	}
}

void C16x9TempletNormal::SetInitParam()
{
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.Width()/5;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 空闲空间位置
	m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.left+m_rectScreen.Width()/2;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.bottom;
}

// 设置模板1的参数 
// 2x2模板
void C16x9TempletNormal::SetTempletParam1(void)
{
	CRect	rc;
	int		i,j,w,h;


	SetInitParam();

	// 高度和宽度
	w=m_rectScreen.Width()/4.0;
	h=m_rectScreen.Height()/3.0;

	m_nWindowNumber = 12;

	// 设置位置
	for (i=0; i<4; i++)
	{
		for (j=0; j<3; j++)
		{
			rc.left		= m_rectScreen.right-(i+1)*w;
			rc.right	= rc.left+w;
			rc.top		= m_rectScreen.top+j*h;
			rc.bottom	= rc.top+h;

			m_rectWindow[i*3+j]=rc;
		}
	}
}

// 设置模板2的参数 
// 2x1模板
void C16x9TempletNormal::SetTempletParam2(void)
{
	CRect	rc;
	int		i,j,w,h;


	SetInitParam();

	// 高度和宽度
	w=m_rectScreen.Width()/3.0;
	h=m_rectScreen.Height()/2.0;

	m_nWindowNumber = 6;

	// 设置位置
	for (i=0; i<3; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left		= m_rectScreen.right-(i+1)*w;
			rc.right	= rc.left+w;
			rc.top		= m_rectScreen.top+j*h;
			rc.bottom	= rc.top+h;

			m_rectWindow[i*2+j]=rc;
		}
	}
}

// 设置模板3的参数 
// 3x2模板
void C16x9TempletNormal::SetTempletParam3(void)
{
	CRect	rc;
	int		i,w,h;


	SetInitParam();

	// 高度和宽度
	w=m_rectScreen.Width()/4.0;
	h=m_rectScreen.Height()/3.0;

	m_nWindowNumber = 4;

	// 设置位置
	for (i=0; i<3; i++)
	{
		rc.left		= m_rectScreen.right-w;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+i*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i]=rc;
	}

	rc.left		= m_rectScreen.left;
	rc.right	= m_rectScreen.right-w;
	rc.top		= m_rectScreen.top;
	rc.bottom	= m_rectScreen.bottom;

	m_rectWindow[3]=rc;
}

// 设置模板4的参数 
// 3x3模板
void C16x9TempletNormal::SetTempletParam4(void)
{
	CRect	rc;
	int		i,w,h;


	SetInitParam();

	// 高度和宽度
	w=m_rectScreen.Width()/4.0;
	h=m_rectScreen.Height()/3.0;

	m_nWindowNumber = 6;

	// 设置位置
	for (i=0; i<4; i++)
	{
		rc.left		= m_rectScreen.right-(i+1)*w;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+2*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i]=rc;
	}

	rc.left		= m_rectScreen.left;
	rc.right	= m_rectScreen.left+2*w;
	rc.top		= m_rectScreen.top;
	rc.bottom	= m_rectScreen.top+2*h;

	m_rectWindow[4]=rc;

	rc.left		= m_rectScreen.left+2*w;
	rc.right	= m_rectScreen.right;
	rc.top		= m_rectScreen.top;
	rc.bottom	= m_rectScreen.top+2*h;

	m_rectWindow[5]=rc;
}

// 设置模板5的参数 
// 8+1模板
void C16x9TempletNormal::SetTempletParam5(void)
{
	CRect	rc;
	int		i,w,h;


	SetInitParam();

	// 高度和宽度
	w=m_rectScreen.Width()/4.0;
	h=m_rectScreen.Height()/3.0;

	m_nWindowNumber = 9;

	// 设置位置
	for (i=0; i<2; i++)
	{
		rc.left		= m_rectScreen.right-w;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+i*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i]=rc;
	}

	// 设置位置
	for (i=0; i<4; i++)
	{
		rc.left		= m_rectScreen.right-(i+1)*w;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+2*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i+2]=rc;
	}

	// 设置位置
	for (i=0; i<2; i++)
	{
		rc.left		= m_rectScreen.left;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+(1-i)*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i+6]=rc;
		//m_rectWindow[8].right =  m_rectWindow[0].left;
	}

	rc.left		= m_rectScreen.left+w;
	rc.right	= m_rectScreen.left+3*w;
	rc.top		= m_rectScreen.top;
	rc.bottom	= m_rectScreen.top+2*h;

	m_rectWindow[8]=rc;
}

void C16x9TempletNormal::SetTempletParam6(void)
{
	CRect	rc;
	int		i,w,h;


	SetInitParam();

	// 高度和宽度
	w=m_rectScreen.Width()/4.0;
	if (m_bIsTempleteControl)
	{
		w=m_rectScreen.Width()/3.0;
	}
	h=m_rectScreen.Height()/3.0;

	m_nWindowNumber = 6;

	// 设置位置
	for (i=0; i<2; i++)
	{
		rc.left		= m_rectScreen.right-w;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+i*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i]=rc;
	}

	// 设置位置
	for (i=0; i<3; i++)
	{
		rc.left		= m_rectScreen.right-(i+1)*w;
		//if (m_bIsTempleteControl)
		//{
		//	rc.left		= m_rectScreen.right-i*w;
		//}
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+2*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i+2]=rc;
	}

	/*
	// 设置位置
	for (i=0; i<2; i++)
	{
		rc.left		= m_rectScreen.left;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+(1-i)*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i+6]=rc;
	}
	*/

	rc.left		= m_rectScreen.left+w;
	if (m_bIsTempleteControl)
	{
		rc.left		= m_rectScreen.left;
	}
	rc.right	= m_rectScreen.left+3*w;
	if (m_bIsTempleteControl)
	{
		rc.right	= m_rectScreen.left+2*w;
	}
	rc.top		= m_rectScreen.top;
	rc.bottom	= m_rectScreen.top+2*h;

	m_rectWindow[5]=rc;
	m_rectFree = rc;

	// 控制面板区域
	m_rectControl.left		= m_rectScreen.left;
	m_rectControl.right		= m_rectControl.left+w;
	m_rectControl.top		= m_rectScreen.top;
	m_rectControl.bottom	= m_rectScreen.bottom;
}

void C16x9TempletNormal::SetTempletParam7(void)
{
	CRect	rc;
	int		i,w,h;
	int		left = w=0;


	SetInitParam();

	//if (GetScreenIndex() == 0)
	//{
		w=m_rectScreen.Width()/5;
		h=m_rectScreen.Height()/2.0;
		left = w;
	//}
	//else
	//{
	//	w=m_rectScreen.Width()/4;
	//	h=m_rectScreen.Height()/2.0;
	//	left=0;
	//}

	m_nWindowNumber = 10;	

	for (i=0; i<2; i++)
	{
		rc.left		= m_rectScreen.left+i*w*2+left;
		rc.right	= rc.left+w*2;
		rc.top		= m_rectScreen.top;
		rc.bottom	= rc.top+h;

		m_rectWindow[i]=rc;
	}

	for (i=0; i<4; i++)
	{
		rc.left		= m_rectScreen.left+i*w+left;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+h;
		rc.bottom	= rc.top+h/2.0;

		m_rectWindow[i+2]=rc;
	}

	for (i=0; i<4; i++)
	{
		rc.left		= m_rectScreen.left+i*w+left;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+h*3.0/2.0;
		rc.bottom	= rc.top+h/2.0;

		m_rectWindow[i+6]=rc;
	}

	// 控制面板区域
	m_rectControl.left		= m_rectScreen.left;
	m_rectControl.right		= m_rectControl.left+w;
	m_rectControl.top		= m_rectScreen.top;
	m_rectControl.bottom	= m_rectScreen.bottom;
}

// 获得屏幕索引号
int C16x9TempletNormal::GetScreenIndex()
{
	return m_nScreenIndex;
}

void C16x9TempletNormal::GetBigWindows(int iBigWindows[3])			//得到大窗口
{
	int i=0;for ( i=0;i<3;i++)
		iBigWindows[i]=m_nBigWindows[i];
}

void C16x9TempletNormal::SetTempletParam34(void)                   //N91
{
	CRect	rc;
	int		i,w,h;


	SetInitParam();

	// 高度和宽度
	h=m_rectScreen.Height()/4;
	w=m_rectScreen.Width()/4;

	m_nWindowNumber = 5;

	// 设置位置
	for (i=0; i<4; i++) 
	{
		rc.left		= m_rectScreen.right-w;
		rc.right	= m_rectScreen.right;
		rc.top		= m_rectScreen.top+i*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i+1]=rc;
	}

	rc.left		= m_rectScreen.left;
	rc.right	= m_rectScreen.right-w;
	rc.top		= m_rectScreen.top;
	rc.bottom	= m_rectScreen.bottom;

	m_rectWindow[0]=rc;

}

// 设置模板21的参数 
// 
void C16x9TempletNormal::SetTempletParam31(void)              //N7
{

	CRect	rc;
	int		i,w,h;
	
	//// 高度和宽度
	w=m_rectScreen.Width()/4;
	h=m_rectScreen.Height()/4;

	//// 最左边位置
	//l=0;

	//// 控制面板区域
	//m_rectControl.left=m_rectScreen.left;
	//m_rectControl.right=m_rectScreen.left+w;
	//m_rectControl.top=m_rectScreen.top;
	//m_rectControl.bottom=m_rectScreen.top+m_rectScreen.Height();


	//// 空闲空间位置
	//m_rectFree.left=0;
	//m_rectFree.right=0;
	//m_rectFree.top=0;
	//m_rectFree.bottom=0;
	//m_rectMidWindow = m_rectFree;
	SetInitParam();
	m_nWindowNumber=5;

	CRect rc2;
	//// 设置位置
	for (i=0; i<4; i++)
	{
		rc.left = m_rectScreen.left;
		rc.right = rc.left + w;
		rc.top = m_rectScreen.top+i*h;
		rc.bottom = rc.top + h;
		m_rectWindow[i+1]=rc;
	}
	rc.left = m_rectWindow[1].left + w;
	rc.right = m_rectScreen.right;
	rc.top = m_rectScreen.top;
	rc.bottom = m_rectScreen.bottom;
	m_rectWindow[0]=rc;
}

// 设置模板10的参数 
// 3+1模板
void C16x9TempletNormal::SetTempletParam32(void)                //N9, N71
{
	CRect	rc;
	int		i,w,h;


	SetInitParam();

	// 高度和宽度
	w=m_rectScreen.Width()/4.0;
	h=m_rectScreen.Height()/3.0;

	m_nWindowNumber = 4;

	// 设置位置
	for (i=0; i<3; i++)
	{
		rc.left		= m_rectScreen.right-w;
		rc.right	= rc.left+w;
		rc.top		= m_rectScreen.top+i*h;
		rc.bottom	= rc.top+h;

		m_rectWindow[i+1]=rc;
	}

	rc.left		= m_rectScreen.left;
	rc.right	= m_rectScreen.right-w;
	rc.top		= m_rectScreen.top;
	rc.bottom	= m_rectScreen.bottom;

	m_rectWindow[0]=rc;
}

void C16x9TempletNormal::SetTempletParam30()             //画中画
{

	int		w,h;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	h=m_rectScreen.Height()/4;

	SetInitParam();

	m_nWindowNumber=2;

	CRect rc;
	m_rectWindow[0] = m_rectScreen;
	rc.left = m_rectScreen.right - w;
	rc.right = m_rectScreen.right;
	rc.top = m_rectScreen.bottom - h;
	rc.bottom = m_rectScreen.bottom;
	m_rectWindow[1] = rc;

	m_bIsPictureInPicture = TRUE;

}

void C16x9TempletNormal::SetTempletParam11()             //wt 2008-05-21 1×1模板
{

	int		w,h;


	SetInitParam();
	// 高度和宽度
	w=m_rectScreen.Width();
	h=m_rectScreen.Height();

	m_nWindowNumber=1;

	m_rectWindow[0] = m_rectScreen;
}

void C16x9TempletNormal::SetTempletParam22()             //wt 2008-05-21 2×2模板
{

	int		w,h;
	SetInitParam();

	// 高度和宽度
	int x=m_rectScreen.left;
	int y=m_rectScreen.top;
	w=m_rectScreen.Width()/2;
	h=m_rectScreen.Height()/2;


	m_nWindowNumber=4;

	CRect rc;
	for(int i=0;i<2;i++)
	{
		for (int j=0;j<2;j++)
		{
			m_rectWindow[i*2+j].left=x+j*w;
			m_rectWindow[i*2+j].right=x+j*w+w;
			m_rectWindow[i*2+j].top=y+i*h;
			m_rectWindow[i*2+j].bottom=y+i*h+h;
		}
	}
}



void C16x9TempletNormal::SetTempletParam12()             //wt 2008-05-26 1×2模板
{

	int		w,h;


	SetInitParam();
	// 高度和宽度
	int x=m_rectScreen.left;
	int y=m_rectScreen.top;
	w=m_rectScreen.Width()/2;
	h=m_rectScreen.Height();


	m_nWindowNumber=2;

	CRect rc;
	for(int i=0;i<1;i++)
	{
		for (int j=0;j<2;j++)
		{
			m_rectWindow[i*2+j].left=x+j*w;
			m_rectWindow[i*2+j].right=x+j*w+w;
			m_rectWindow[i*2+j].top=y+i*h;
			m_rectWindow[i*2+j].bottom=y+i*h+h;
		}
	}
}

void C16x9TempletNormal::SetTempletParam121()             //wt 2008-05-26 1\2\1模板
{

	int		i,j,w,h;


	SetInitParam();
	// 高度和宽度
	int x=m_rectScreen.left;
	int y=m_rectScreen.top;
	w=m_rectScreen.Width()/2;
	h=w*9/16;
	int l=(m_rectScreen.Height()-h)/2;


	m_nWindowNumber=4;

    i=0;
	j=0;
	m_rectWindow[i*2+j].left=x;
	m_rectWindow[i*2+j].right=x+w;
	m_rectWindow[i*2+j].top=y+l;
	m_rectWindow[i*2+j].bottom=y+h+l;

	j++;
	m_rectWindow[i*2+j].left=x+w;
	m_rectWindow[i*2+j].right=x+2*w;
	m_rectWindow[i*2+j].top=y+l;
	m_rectWindow[i*2+j].bottom=y+h+l;

	j++;
	m_rectWindow[i*2+j].left=x;
	m_rectWindow[i*2+j].right=x+m_rectScreen.Width();
	m_rectWindow[i*2+j].top=y;
	m_rectWindow[i*2+j].bottom=y+l;

	j++;
	m_rectWindow[i*2+j].left=x;
	m_rectWindow[i*2+j].right=x+m_rectScreen.Width();
	m_rectWindow[i*2+j].top=y+h+l;
	m_rectWindow[i*2+j].bottom=y+l+h+l;
}