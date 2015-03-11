#include "StdAfx.h"
#include "templetnormal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTempletNormal::CTempletNormal(void)
{
	m_nWindowNumber			= 0;
	m_nScreenIndex			= 1;
//	m_rectScreen			= AfxGetScreenRect();
	int i=0;for ( i=0; i < 25; i++)
	{
		SetWindowSelected(i,false);
	}
}

CTempletNormal::~CTempletNormal(void)
{
}

// 设置标准模板类型
void CTempletNormal::SetType(int nType,int nNumber)
{
	m_nWindowNumber = 0;		//预赋值为0
	m_bRepairTemplet=FALSE;

	memset(&m_rectFree, 0, sizeof(RECT));
	m_rectMidWindow.SetRect(0, 0, 0, 0);

	if (nType<0)
		nType = 0;
	//if (nType>24)
	//	nType = 24;

	switch(nType)
	{
	case 0:	// 标准模板
		SetTempletParam0();	
		m_bRepairTemplet = TRUE;
		break;
	case 1:	// 2x2模板
		SetTempletParam1();
		//SetTempletParam18();
		//SetTempletParam19();
		m_bRepairTemplet = TRUE;
		break;
	case 2:	// 2x1模板
		SetTempletParam2();	
		m_bRepairTemplet = TRUE;
		break;
	case 3:	// 3x2模板
		SetTempletParam3();	
		//SetTempletParam17();
		m_bRepairTemplet = TRUE;
		break;
	case 4:
		SetTempletParam4();	
		m_bRepairTemplet = TRUE;
		break;
	case 5:
		SetTempletParam5();	
		m_bRepairTemplet = TRUE;
		break;
	case 6:
		SetTempletParam6();	
		m_bRepairTemplet = TRUE;
		break;
	case 7:
		SetTempletParam7();	
		m_bRepairTemplet = TRUE;
		break;
	case 8:
		SetTempletParam8();	
		m_bRepairTemplet = TRUE;
		break;
	case 9:
		SetTempletParam9();	
		break;
	case 10:
		SetTempletParam10();	
		break;
	case 11:
		SetTempletParam11();
		m_bRepairTemplet = TRUE;
		break;
	case 12:
		SetTempletParam12();
		break;
	case 13:
		SetTempletParam13();
		m_bRepairTemplet = TRUE;
		break;
	case 14:
		SetTempletParam14();
		m_bRepairTemplet = TRUE;
		break;
	case 15:
		SetTempletParam15();
		m_bRepairTemplet = TRUE;
		break;
	case 16:
		SetTempletParam16();
		m_bRepairTemplet = TRUE;
		break;
	case 17:
		SetTempletParam17();
		m_bRepairTemplet = TRUE;
		break;
	case 18:
		SetTempletParam18();
		m_bRepairTemplet = TRUE;
		break;
	case 19:
		SetTempletParam19();
		m_bRepairTemplet = TRUE;
		break;
	case 20:
		SetTempletParam20();
		m_bRepairTemplet = TRUE;
		break;
	case 21:
		SetTempletParam21();
		break;
	case 22:
		SetTempletParam22();
		break;
	case 23:
		SetTempletParam23();
		break;
	case 24:
		SetTempletParam24();
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
	case 33:
		SetTempletParam33();
		break;
	case 34:
		SetTempletParam34();
		break;
	case 35:
		SetTempletParam35();
		break;
	case 36:
		SetTempletParam36();
		break;
	case 120://wt
		SetTempletParam120();
		break;
	case 121://wt
		SetTempletParam121();
		break;
	//case 26:
	//	SetTempletParam30();
	//	break;
	}

	m_nBigWindows[0] = -1;
	m_nBigWindows[1] = -1;
	m_nBigWindows[2] = -1;
	switch (nType)
	{
	case 0:
		m_nBigWindows[0] = 1;
		break;
	case 1:
		//{{add by yry at 2005.6.1
		//	m_nBigWindows[0] = 3;
		//}}add end
		break;
		//{{add by yry at 2005.4.13
	case 2:
		m_nBigWindows[0] = 3;
		break;
	case 7:
		//	m_nBigWindows[0] = 1;
		break;
		//}}add end
	case 3:
		m_nBigWindows[0] = 7;
		m_nBigWindows[1] = 8;
		break;
	case 5:
		m_nBigWindows[0] = 9;
		break;
	case 6:
		m_nBigWindows[0] = 12;
		break;
	case 9:
		m_nBigWindows[0] = 8;
		break;
	case 10:
		m_nBigWindows[0] = 10;
		break;
	case 11:
		m_nBigWindows[0] = 5;
		break;
	case 12:
		m_nBigWindows[0] = 6;
		break;
	case 13:
		m_nBigWindows[0] = 4;
		break;
	case 14:
		m_nBigWindows[0] = 5;
		m_nBigWindows[1] = 6;
		break;
	case 15:
		m_nBigWindows[0] = 5;
		break;
	case 16:
		m_nBigWindows[0] = 6;
		break;
	case 17:
		m_nBigWindows[0] = 1;
		m_nBigWindows[1] = 2;
		break;
	case 18:
		m_nBigWindows[0] = 1;
		m_nBigWindows[1] = 2;
		m_nBigWindows[2] = 3;
		break;
	case 19:
		m_nBigWindows[0] = 7;
		m_nBigWindows[1] = 8;
		break;
	case 20:
		m_nBigWindows[0] = 2;
		break;
	case 21:
		m_nBigWindows[0] = 1;
		break;
	case 23:
		m_nBigWindows[0] = 1;
		m_nBigWindows[1] = 2;
		break;
	case 24:
		m_nBigWindows[0] = 1;
		m_nBigWindows[1] = 2;
		break;
	case 30:                        //N5   1
		m_nBigWindows[0] = 1;
		break;
	case 31:                        //N7   1
		m_nBigWindows[0] = 1;
		break;
	case 32:                       // N9    1 
		m_nBigWindows[0] = 1;
		break;
	case 33:                       // N71   1
		m_nBigWindows[0] = 1;
		break;
	case 34:                      //N91     1
		m_nBigWindows[0] = 1;
		break;
	case 35:                      //4*4
		m_nBigWindows[0] = 1;
		break;
	case 36:                      //5*5
		m_nBigWindows[0] = 1;
		break;
	case 120://wt
		m_nBigWindows[0] = 1;
		break;
	case 121://wt
		m_nBigWindows[0] = 1;
		break;
	}

}

// 根据索引获得区域
bool CTempletNormal::GetWndRect(int index, LPRECT lpRect)
{
	if ((index>25) || (index>m_nWindowNumber))
		return false;

	*lpRect=m_rectWindow[index];
	return true;
}

// 获得剩余区域
RECT CTempletNormal::GetFreeRect()
{
	return m_rectFree;
}

// 获得中间窗口区域
RECT CTempletNormal::GetMidRect()
{
	return m_rectMidWindow;
}

// 获得控制面板区域
RECT CTempletNormal::GetControlRect()
{
	return m_rectControl;
}

// 窗口数
int	CTempletNormal::GetWindowCount()
{
	return m_nWindowNumber;
}

// 设置屏幕索引号,1.标准屏幕, 2.第二个屏幕
void CTempletNormal::SetScreenIndex(int nScreenIndex, RECT rcScreen)
{
	m_nScreenIndex = nScreenIndex;
	m_rectScreen = rcScreen;

}

// 获得全屏幕的尺寸
void	CTempletNormal::GetScreenRect(LPRECT lpRect)
{
	if (lpRect)
	{
		*lpRect	= m_rectScreen;
	}
}


// 设置模板0的参数 
// 演讲模板
void CTempletNormal::SetTempletParam0(void)
{
	
	CRect	rc;
	int		l;

	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
    //l = 0;
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;


	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.left+m_rectScreen.Width();
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.top+m_rectScreen.Height();
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=1;
	m_rectWindow[0] = m_rectFree;
}

// 设置模板1的参数 
// 2x2模板
void CTempletNormal::SetTempletParam1(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/5*2;
	if (m_bIsTempleteControl)
	{
		w=m_rectScreen.Width()/2;
	}
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/2;

	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;
	

	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=4;

	// 设置位置
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 1)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[i*2+j]=rc;
		}
	}
}

// 设置模板2的参数 
// 2x1模板
void CTempletNormal::SetTempletParam2(void)
{
	CRect	rc;
	int		i,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/5*2;
	if (m_bIsTempleteControl)
	{
		w= m_rectScreen.Width()/2;
	}
	h=(int)((double)w*0.75);

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()+m_rectScreen.left;
	m_rectFree.top=h+m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;

	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=3;

	// 设置位置
	for (i=0; i<2; i++)
	{
		rc.left=m_rectScreen.left+l+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		if (i == 1)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}

		m_rectWindow[i]=rc;
	}

	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

// 设置模板3的参数 
// 3x2模板
void CTempletNormal::SetTempletParam3(void)
{
	CRect	rc;
	int		i,j,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/15*4;
	if (m_bIsTempleteControl)
	{
		w = m_rectScreen.Width()/3;
	}
	h=(int)((double)w*0.75);

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()+m_rectScreen.left;
	m_rectFree.top=h*2+m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=8;

	// 设置位置
	for (i=0; i<2; i++)
	{
		for (j=0; j<3; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 2)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[i*3+j]=rc;
		}
	}

	m_rectWindow[m_nWindowNumber-2] = m_rectFree;
	m_rectWindow[m_nWindowNumber-1] = m_rectFree;

	m_rectWindow[m_nWindowNumber-2].right = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;
	m_rectWindow[m_nWindowNumber-1].left = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;
}

// 设置模板4的参数 
// 3x3模板
void CTempletNormal::SetTempletParam4(void)
{
	CRect	rc;
	int		i,j,w,h,l;
	m_bIsTempleteControl = true;	//add by tiger,2009.07.30

	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/15*4;
	if (m_bIsTempleteControl)
	{
		w = m_rectScreen.Width()/3;
	}
	h=m_rectScreen.Height()/3;

	// 空闲空间位置
	m_rectFree.left = 0;
	m_rectFree.top = 0;
	m_rectFree.right = 0;
	m_rectFree.bottom = 0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=9;

	// 设置位置
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 2)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			if (i == 2)
			{
				rc.bottom = m_rectScreen.Height()+m_rectScreen.top;
			}

			m_rectWindow[i*3+j]=rc;
		}
	}
}

// 设置模板5的参数 
// 8+1模板
void CTempletNormal::SetTempletParam5(void)
{
	CRect	rc;
	int		i,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=(m_rectScreen.Width()-l)/3;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/4;

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()-w+m_rectScreen.left;
	m_rectFree.top=h+m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()-h+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=9;

	// 顶部三个窗口
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+l+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		if (i == 2)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}
		m_rectWindow[i]=rc;
	}

	// 右部三个窗口
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+l+2*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h+h;
		rc.bottom=rc.top+h;

		rc.right = m_rectScreen.Width()+m_rectScreen.left;

		m_rectWindow[i+3]=rc;
	}

	//底部二个窗口
	for (i=0; i<2; i++)
	{
		rc.left=m_rectScreen.left+l+w-i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+3*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+6]=rc;
	}

	m_rectFree.right = m_rectWindow[4].left;
	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

// 设置模板6的参数 
// 11+1模板
void CTempletNormal::SetTempletParam6(void)
{
	CRect	rc;
	int		i,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		w = m_rectScreen.Width()/4;
	}
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/5;

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()-w+m_rectScreen.left;
	m_rectFree.top=h+m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()-h+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=12;

	// 顶部三个窗口
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+l+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		if (i == 3)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}
		m_rectWindow[i]=rc;
	}

	// 右部三个窗口
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+l+3*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h+h;
		rc.bottom=rc.top+h;

		rc.right = m_rectScreen.Width()+m_rectScreen.left;
		m_rectWindow[i+4]=rc;
	}

	//底部二个窗口
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+l+2*w-i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+4*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+8]=rc;
	}

	m_rectFree.right = m_rectWindow[4].left;
	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

// 设置模板7的参数 
// 4x5模板
void CTempletNormal::SetTempletParam7(void)
{
	CRect	rc;
	int		i,j,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		w=m_rectScreen.Width()/4;
	}
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/5;

	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;

	m_nWindowNumber=20;

	// 设置位置
	for (i=0; i<5; i++)
	{
		for (j=0; j<4; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 3)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}
			m_rectWindow[i*4+j]=rc;
		}
	}
}


// 设置模板8的参数 
// 3x4模板
void CTempletNormal::SetTempletParam8(void)
{
	CRect	rc;
	int		i,j,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=(m_rectScreen.Width()-l)/3;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/4;

	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	

	m_nWindowNumber=12;

	// 设置位置
	for (i=0; i<4; i++)
	{
		for (j=0; j<3; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 2)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}
			m_rectWindow[i*3+j]=rc;
		}
	}
}

// 设置模板9的参数 
// 6+1模板
void CTempletNormal::SetTempletParam9(void)
{
	CRect	rc;
	int		i,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/4;

	// 空闲空间位置
	//m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()-w+m_rectScreen.left;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()-h+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=8;


	// 右部三个窗口
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+3*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right = m_rectScreen.Width()+m_rectScreen.left;

		m_rectWindow[i]=rc;
	}

	//底部三个窗口
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+3*w-i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+3*h;
		rc.bottom=rc.top+h;
		
		//{{add by tiger,2009.09.01
			rc.bottom++;
		//end add}}

		if (i == 0)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}

		m_rectWindow[i+3]=rc;
	}

	//{{add by tiger,2009.09.01
	m_rectFree.right--;
	m_rectFree.bottom--;
	//end add}}

	m_rectWindow[m_nWindowNumber-2].left = m_rectScreen.left;
	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

// 设置模板10的参数 
// 8+1模板
void CTempletNormal::SetTempletParam10(void)
{
	CRect	rc;
	int		i,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/5;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/5;

	// 空闲空间位置
	//m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()-w+m_rectScreen.left;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()-h+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=10;


	// 右部三个窗口
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+l+3*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right = m_rectScreen.Width()+m_rectScreen.left;
		m_rectWindow[i]=rc;
	}

	//底部三个窗口
	for (i=0; i<5; i++)
	{
		rc.left=m_rectScreen.left+l+3*w-i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+4*h;
		rc.bottom=rc.top+h;

		//{{add by tiger,2009.09.01
		rc.bottom++;
		//end add}}

		if (i == 0)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}
		m_rectWindow[i+4]=rc;
	}

	m_rectFree.right = m_rectWindow[0].left;
	m_rectFree.bottom--;	//add by tiger,2009.09.01
	m_rectWindow[m_nWindowNumber-2].left = m_rectScreen.left;
	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

// 设置模板10的参数 
// 8+1模板
void CTempletNormal::SetTempletParam11(void)
{
	CRect	rc;
	int		i,w,h;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	h=m_rectScreen.Height()/4;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectControl.left+m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		m_rectControl.right = 0;
	}
	m_rectControl.top=h;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 空闲空间位置
	m_rectFree.left=m_rectControl.Width()+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.right;
	m_rectFree.top=m_rectScreen.top+h;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=5;

	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		if (i == 3)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}
		m_rectWindow[i]=rc;
	}

	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

void CTempletNormal::SetTempletParam12(void)
{
	CRect	rc;
	int		i,w,h,l;

	// 最左边位置
	l=m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/3;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/3;

	// 空闲空间位置
	//m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()-w+m_rectScreen.left;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()-h+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=6;

	// 右部三个窗口
	for (i=0; i<2; i++)
	{
		rc.left=m_rectScreen.left+2*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right = m_rectScreen.Width()+m_rectScreen.left;

		m_rectWindow[i]=rc;
	}

	//底部三个窗口
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+(2-i)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+2*h;
		rc.bottom=rc.top+h;

		if (i == 0)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}
		m_rectWindow[i+2]=rc;
	}

	m_rectFree.right = m_rectWindow[0].left;
	m_rectFree.bottom = m_rectWindow[4].top;
	m_rectWindow[m_nWindowNumber-2].left = m_rectScreen.left;
	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

void CTempletNormal::SetTempletParam13(void)
{
	CRect	rc;
	int		i,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/15*4;
	if (m_bIsTempleteControl)
	{
		w = m_rectScreen.Width()/3;
	}
	h=(int)((double)w*0.75);

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()+m_rectScreen.left;
	m_rectFree.top=h+m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;

	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=4;

	// 设置位置
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+l+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		if (i == 2)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}

		m_rectWindow[i]=rc;
	}

	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

void CTempletNormal::SetTempletParam14(void)
{
	CRect	rc;
	int		i,w,h,l;

	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	if (m_bIsTempleteControl)
	{
		w = m_rectScreen.Width()/3;
	}
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/4;

	// 空闲空间位置
	//m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.left=m_rectScreen.left+l;
	m_rectFree.right=m_rectScreen.Width()-w+m_rectScreen.left;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=6;


	// 右部三个窗口
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.Width()-w+m_rectScreen.left;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right = m_rectScreen.Width()+m_rectScreen.left;
		m_rectWindow[i]=rc;
	}
	
	for (i=0; i<2; i++)
	{
		rc = m_rectFree;
		rc.top = m_rectFree.top+((m_rectFree.bottom-m_rectFree.top)/2.0)*i;
		rc.bottom = rc.top+((m_rectFree.bottom-m_rectFree.top)/2.0);		
		m_rectWindow[m_nWindowNumber-2+i] = rc;
	}
}

void CTempletNormal::SetTempletParam15(void)
{
	CRect	rc;
	int		i,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		w = m_rectScreen.Width()/4;
	}
	h=(int)((double)w*0.75);

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()+m_rectScreen.left;
	m_rectFree.top=h+m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;

	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=5;

	// 设置位置
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+l+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		if (i == 3)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}

		m_rectWindow[i]=rc;
	}

	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
}

void CTempletNormal::SetTempletParam16(void)
{
	CRect	rc;
	int		i,w,h;

	// 高度和宽度
	w=m_rectScreen.Width()/5;
	h=m_rectScreen.Height()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectControl.left+w;
	if (m_bIsTempleteControl)
	{
		m_rectControl.right = 0;
	}
	m_rectControl.top=h;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 空闲空间位置
	m_rectFree.left=m_rectControl.Width()+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.right;
	m_rectFree.top=m_rectScreen.top+h;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=6;

	for (i=0; i<5; i++)
	{
		rc.left=m_rectScreen.left+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		if (i == 4)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}
		m_rectWindow[i]=rc;
	}

	m_rectWindow[m_nWindowNumber-1] = m_rectFree;
	
}

void CTempletNormal::SetTempletParam17(void)
{	
	CRect	rc;
	int		i,j,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/5*2;
	h=m_rectScreen.Height()/2;

	// 最左边位置
	l=m_rectScreen.Width()/5;
    if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;
	

	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=10;

	CRect rc2;
	// 设置位置
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 1)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[i*2+j]=rc;
		}
	}

	rc2=m_rectWindow[3];
	m_rectMidWindow = m_rectWindow[1];
	m_rectWindow[1] = m_rectWindow[2];
	w=m_rectMidWindow.Width()/2;
	h=m_rectMidWindow.Height()/2;
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left=m_rectMidWindow.left+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectMidWindow.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 1)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[2+i*2+j]=rc;
		}
	}

	m_rectMidWindow = rc2;
	w=m_rectMidWindow.Width()/2;
	h=m_rectMidWindow.Height()/2;
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left=m_rectMidWindow.left+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectMidWindow.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 1)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[6+i*2+j]=rc;
		}
	}
	m_rectMidWindow = m_rectFree;
}

void CTempletNormal::SetTempletParam18(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/5*2;
	if (m_bIsTempleteControl)
	{
		w=m_rectScreen.Width()/2;
	}
	h=m_rectScreen.Height()/2;

	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;
	

	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=7;

	// 设置位置
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 1)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[i*2+j]=rc;
		}
	}

	m_rectMidWindow = m_rectWindow[3];
	w=m_rectMidWindow.Width()/2;
	h=m_rectMidWindow.Height()/2;
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left=m_rectMidWindow.left+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectMidWindow.top+i*h;
			rc.bottom=rc.top+h;

			if (j == 1)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[3+i*2+j]=rc;
		}
	}
	m_rectMidWindow = m_rectFree;
}

void CTempletNormal::SetTempletParam19(void)
{
	CRect	rc;
	int		i,j,w,h,l;


	// 最左边位置
	l=m_rectScreen.Width()/5;
	if (m_bIsTempleteControl)
	{
		l = 0;
	}
	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/15*4;
	if (m_bIsTempleteControl)
	{
		w = m_rectScreen.Width()/3;
	}
	h=(int)((double)w*0.75);

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()+m_rectScreen.left;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top-h*2;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=8;

	// 设置位置
	for (i=0; i<2; i++)
	{
		for (j=0; j<3; j++)
		{
			rc.left=m_rectScreen.left+l+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.Height()+m_rectScreen.top-h*2+h*i;
			rc.bottom=rc.top+h;

			if (j == 2)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[i*3+j]=rc;
		}
	}

	m_rectWindow[m_nWindowNumber-2] = m_rectFree;
	m_rectWindow[m_nWindowNumber-1] = m_rectFree;

	m_rectWindow[m_nWindowNumber-2].right = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;
	m_rectWindow[m_nWindowNumber-1].left = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;	
}

void CTempletNormal::SetTempletParam20(void)
{
	CRect	rc;
	int		w,h;

	// 高度和宽度
	w=m_rectScreen.Width()/5;
	h=m_rectScreen.Height()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectControl.left+w;
	//if (m_bIsTempleteControl)
	//{
	//	m_rectControl.right = 0;
	//}
	m_rectControl.top=h;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 空闲空间位置
	m_rectFree.left=m_rectControl.Width()+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.right;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=2;

	rc.left=m_rectScreen.left;
	rc.right=rc.left+w;
	rc.top=m_rectScreen.top;
	rc.bottom=rc.top+h;

	m_rectWindow[0]=rc;
	m_rectWindow[1] = m_rectFree;
	


}
void CTempletNormal::SetTempletParam21(void)
{
	CRect	rc;
	int		l;

	// 最左边位置
	l=m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.Width()/5;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 空闲空间位置
	m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.left+m_rectScreen.Width();
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.top+m_rectScreen.Height();
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=1;
	m_rectWindow[0] = m_rectFree;
	//1号屏1个窗口的大模板

}
void CTempletNormal::SetTempletParam22(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/4*2;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/2;

	// 最左边位置
	l=m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.Width()/5;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;
	

	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=4;

	// 设置位置
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			rc.left=m_rectScreen.left+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			//{{add by tiger,2009.09.01
			if (i == 1)
			{
				if (m_rectScreen.Height()%2)
				{
					rc.bottom++;
				}
			}
			//end add}}

			if (j == 1)
			{
				rc.right = m_rectScreen.Width()+m_rectScreen.left;
			}

			m_rectWindow[i*2+j]=rc;
		}
	}
//2*2全屏模板
}
void CTempletNormal::SetTempletParam23(void)
{
	CRect	rc;
	int		j,w,h,l;


	// 最左边位置
	l=0;//m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.Width()/5;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/3;
	h=(int)((double)w*0.90);

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()+m_rectScreen.left;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top-h;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=5;
	// 设置位置
	for (j=0; j<3; j++)
	{
		rc.left=m_rectScreen.left+j*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.Height()+m_rectScreen.top-h;;
		rc.bottom=rc.top+h;

		if (j == 2)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}

		m_rectWindow[2+j]=rc;
	}

	m_rectWindow[m_nWindowNumber-5] = m_rectFree;
	m_rectWindow[m_nWindowNumber-4] = m_rectFree;

	m_rectWindow[m_nWindowNumber-5].right = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;
	m_rectWindow[m_nWindowNumber-4].left = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;	

}
void CTempletNormal::SetTempletParam24(void)
{
	CRect	rc;
	int		j,w,h,l;


	// 最左边位置
	l=0;//m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.Width()/5;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	h=(int)((double)w*0.75);

	// 空闲空间位置
	m_rectFree.left=l+m_rectScreen.left;
	m_rectFree.right=m_rectScreen.Width()+m_rectScreen.left;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.Height()+m_rectScreen.top-h;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=6;
	// 设置位置
	for (j=0; j<4; j++)
	{
		rc.left=m_rectScreen.left+j*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.Height()+m_rectScreen.top-h;;
		rc.bottom=rc.top+h;

		if (j == 3)
		{
			rc.right = m_rectScreen.Width()+m_rectScreen.left;
		}

		m_rectWindow[2+j]=rc;
	}

	m_rectWindow[m_nWindowNumber-6] = m_rectFree;
	m_rectWindow[m_nWindowNumber-5] = m_rectFree;

	m_rectWindow[m_nWindowNumber-6].right = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;
	m_rectWindow[m_nWindowNumber-5].left = m_rectFree.left+(m_rectFree.right-m_rectFree.left)/2;	

}

void CTempletNormal::SetTempletParam34(void)                  //N91 右边4个，左边一个
{	
	CRect	rc;
	int		i,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	h=m_rectScreen.Height()/4;

	// 最左边位置
	l=0;

	SetInitParam();

	m_nWindowNumber=5;

	CRect rc2;
	// 设置位置
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+l+3*w;
		rc.right=m_rectScreen.right;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+1]=rc;
	}


	rc.left=m_rectScreen.left;
	rc.right=m_rectWindow[1].left;
	rc.top=m_rectScreen.top;
	rc.bottom=m_rectScreen.bottom;

	m_rectWindow[0]=rc;
}

//4*4全屏
void CTempletNormal::SetTempletParam35(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/4;

	// 最左边位置
	l=m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.Width()/5;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;


	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=16;

	// 设置位置
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			rc.left=m_rectScreen.left+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			//{{add by tiger,2009.09.01
			if (i == 3)
			{
				if (m_rectScreen.Height()%2)
				{
					rc.bottom++;
				}
			}
			//end add}}

			m_rectWindow[i*4+j]=rc;
		}
	}
}

//5*5全屏
void CTempletNormal::SetTempletParam36(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/5;
	//h=(int)((double)w*0.75);
	h=m_rectScreen.Height()/5;

	// 最左边位置
	l=m_rectScreen.Width()/5;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.Width()/5;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;


	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=25;

	// 设置位置
	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			rc.left=m_rectScreen.left+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;

			//{{add by tiger,2009.09.01
			if (i == 4)
			{
				if (m_rectScreen.Height()%2)
				{
					rc.bottom++;
				}
			}
			//end add}}

			m_rectWindow[i*5+j]=rc;
			TRACE("i=%d,j=%d,left:%d\t\ttop:%d\t\tright:%d\t\tbootom:%d\n",i,j,m_rectWindow[i*5+j].left,m_rectWindow[i*5+j].top,m_rectWindow[i*5+j].right,m_rectWindow[i*5+j].bottom);
		}
	}
}

void CTempletNormal::SetInitParam()
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

void CTempletNormal::SetTempletParam30()             //画中画
{

	int		w,h;
	w=m_rectScreen.Width()/4;
	h=m_rectScreen.Height()/4;

	SetInitParam();

	// 高度和宽度
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
// 设置模板28的参数 
void CTempletNormal::SetTempletParam33(void)                //N71 右边3个，左边一个
{	
	CRect	rc;
	int		i,w,h,l;
	
	// 高度和宽度
	w=m_rectScreen.Width()/4;
	h=m_rectScreen.Height()/3;

	// 最左边位置
	l=0;

	SetInitParam();

	m_nWindowNumber=4;

	CRect rc2;
	// 设置位置
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+l+3*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+1]=rc;
	}


	rc.left=m_rectScreen.left;
	rc.right=m_rectWindow[1].left;
	rc.top=m_rectScreen.top;
	rc.bottom=m_rectScreen.bottom;

	m_rectWindow[0]=rc;
}

// 设置模板29的参数 
void CTempletNormal::SetTempletParam32(void)    //N9 上面3个，下面1个
{	
	CRect	rc;
	int		i,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/3;
	h=m_rectScreen.Height()/3;

	// 最左边位置
	l=0;

	SetInitParam();

	m_nWindowNumber=4;

	CRect rc2;
	// 设置位置
	for (i=0; i<3; i++)
	{
		rc.left=m_rectScreen.left+l+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		m_rectWindow[i+1]=rc;
	}


	rc.left=m_rectScreen.left;
	rc.right=m_rectScreen.right;
	rc.top=m_rectWindow[1].bottom;
	rc.bottom=m_rectScreen.bottom;

	m_rectWindow[0]=rc;
}

// 设置模板31的参数 
void CTempletNormal::SetTempletParam31(void)    //N7 上面4个，下面一个
{	
	CRect	rc;
	int		i,w,h,l;

	// 高度和宽度
	w=m_rectScreen.Width()/4;
	h=m_rectScreen.Height()/4;

	// 最左边位置
	l=0;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=m_rectScreen.left+w;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.top+m_rectScreen.Height();


	// 空闲空间位置
	m_rectFree.left=0;
	m_rectFree.right=0;
	m_rectFree.top=0;
	m_rectFree.bottom=0;
	m_rectMidWindow = m_rectFree;

	m_nWindowNumber=5;

	CRect rc2;
	// 设置位置
	for (i=0; i<4; i++)
	{
		rc.left=m_rectScreen.left+l+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		m_rectWindow[i+1]=rc;
	}


	rc.left=m_rectScreen.left;
	rc.right=m_rectScreen.right;
	rc.top=m_rectWindow[1].bottom;
	rc.bottom=m_rectScreen.bottom;

	m_rectWindow[0]=rc;
}
// 获得屏幕索引号
int CTempletNormal::GetScreenIndex()
{
	return m_nScreenIndex;
}

void CTempletNormal::GetBigWindows(int iBigWindows[3])			//得到大窗口
{
	int i=0;for ( i=0;i<3;i++)
		iBigWindows[i]=m_nBigWindows[i];
}

void CTempletNormal::SetTempletParam120()             //wt 2008-05-26 1×2模板
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

void CTempletNormal::SetTempletParam121()             //wt 2008-05-26 1\2\1模板
{

	int		i,j,w,h;


	SetInitParam();
	// 高度和宽度
	int x=m_rectScreen.left;
	int y=m_rectScreen.top;
	w=m_rectScreen.Width()/2;
	h=w*3/4;
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

void CTempletNormal::SetWindowSelected(byte iIndex,bool bSelect)
{
	if (iIndex >= 0 && iIndex < 25)
	{
		if (iIndex == 0)
		{
			int i = 0;
		}
		m_bSelected[iIndex] = bSelect;
	}
}

bool CTempletNormal::GetWindowSelected(byte iIndex)
{
	if (iIndex >= 0 && iIndex < 25)
	{
		if (iIndex == 0)
		{
			bool bb = m_bSelected[iIndex];
		}
		return m_bSelected[iIndex];
	}
	return false;
}