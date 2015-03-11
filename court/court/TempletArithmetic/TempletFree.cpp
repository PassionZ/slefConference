#include "StdAfx.h"
#include "templetFree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTempletFree::CTempletFree(void)
{
	m_nMaxWindowNumber		= 0;
	m_nSideWindowNumber		= 0;
	m_nScreenIndex			= 1;
	m_bShowBigWindow		= true;
//	m_rectScreen			= AfxGetScreenRect();
}

CTempletFree::~CTempletFree(void)
{
}

// 设置自由模板类型
void CTempletFree::SetType(int nType, int nNumber)
{
	ASSERT(nNumber);
	if (nNumber<2)
		nNumber = 2;
	else if (nNumber>9)
		nNumber = 9; 
	if (nType<1)
		nType = 1;
	else if (nType>10)
		nType = 10; 

	m_nMaxWindowNumber = nNumber*nNumber;
	m_nSideWindowNumber = nNumber;

	if (m_bShowBigWindow && (nType>4))
	{
		m_nMaxWindowNumber += 1;
	}

	memset(&m_rectFree, 0, sizeof(RECT));	
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
		SetTempletParam6();	
		break;
	case 6:
		SetTempletParam7();	
		break;
	case 7:
		SetTempletParam8();	
		break;
	case 8:
		SetTempletParam9();	
		break;
	case 9:
		SetTempletParam10();	
		break;
	case 10:
		SetTempletParam5();	
		break;
	}

	m_nBigWindows[0] = -1;
	m_nBigWindows[1] = -1;
	m_nBigWindows[2] = -1;
	switch (nType)
	{
	case 5:
	case 6:
		m_nBigWindows[0] = nNumber*2;
		break;
	case 7:
	case 8:
		m_nBigWindows[0] = (nNumber-1)*4+1;
		break;
	case 9:
	case 10:
		m_nBigWindows[0] = (nNumber-1)*4+1;
		break;
	}

}

// 根据索引获得区域
bool CTempletFree::GetWndRect(int index, LPRECT lpRect)
{
	if ((index>81) || (index>GetWindowCount()))
		return false;

	*lpRect=m_rectWindow[index];
	return true;
}

// 获得剩余区域
RECT CTempletFree::GetFreeRect()
{
	return m_rectFree;
}

// 获得控制面板区域
RECT CTempletFree::GetControlRect()
{
	return m_rectControl;
}

// 窗口数
int	CTempletFree::GetWindowCount()
{
	return m_nMaxWindowNumber;
}

// 设置屏幕索引号,1.标准屏幕, 2.第二个屏幕
void CTempletFree::SetScreenIndex(int nScreenIndex, RECT rcScreen)
{
	m_rectScreen = rcScreen;
	m_nScreenIndex = nScreenIndex;
}

// 获得全屏幕的尺寸
void	CTempletFree::GetScreenRect(LPRECT lpRect)
{
	if (lpRect)
	{
		*lpRect	= m_rectScreen;
	}
}

// 初始化设置模板,获得控制面板区域、每个视频窗口高度和宽度
void CTempletFree::InitSetTempletParam(int& l, int& w, int& h)
{
	// 最左边位置
	l=m_rectScreen.Width()-m_rectScreen.Width()/4*3;

	// 控制面板区域
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// 高度和宽度
	w=m_rectScreen.Width()/m_nSideWindowNumber;
	h=m_rectScreen.Height()/m_nSideWindowNumber;

	m_rectFree.left = 0;
	m_rectFree.top = 0;
	m_rectFree.right = 0;
	m_rectFree.bottom = 0;

	m_rectMidWindow = m_rectFree;
	/*m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.left+m_rectScreen.Width()/2;
	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.bottom;*/
}

// 设置模板1的参数 
// 2x2模板
void CTempletFree::SetTempletParam1(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// 设置位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		for (j=0; j<m_nSideWindowNumber; j++)
		{
			rc.left=m_rectScreen.left+j*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+i*h;
			rc.bottom=rc.top+h;
			if (i == m_nSideWindowNumber -1)
			{
				rc.bottom = m_rectScreen.bottom;
			}

			if (j == (m_nSideWindowNumber-1))
				rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

			m_rectWindow[i*m_nSideWindowNumber+j]=rc;
		}
	}
}

// 设置模板2的参数 
// 2x1模板
void CTempletFree::SetTempletParam2(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// 设置位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		for (j=0; j<m_nSideWindowNumber; j++)
		{
			rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-1)*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+j*h;
			rc.bottom=rc.top+h;
			if (j == m_nSideWindowNumber -1)
			{
				rc.bottom = m_rectScreen.bottom;
			}

			if (i == 0)
				rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

			m_rectWindow[i*m_nSideWindowNumber+j]=rc;
		}
	}
}

// 设置模板3的参数 
// 3x2模板
void CTempletFree::SetTempletParam3(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// 设置位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		for (j=0; j<m_nSideWindowNumber; j++)
		{
			rc.left=m_rectScreen.left+i*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+j*h;
			rc.bottom=rc.top+h;
            if (j == m_nSideWindowNumber -1)
			{
				rc.bottom = m_rectScreen.bottom;
			}
			if (i == (m_nSideWindowNumber-1))
				rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

			m_rectWindow[i*m_nSideWindowNumber+j]=rc;
		}
	}
}

// 设置模板4的参数 
// 3x3模板
void CTempletFree::SetTempletParam4(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// 设置位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		for (j=0; j<m_nSideWindowNumber; j++)
		{
			rc.left=m_rectScreen.left+(m_nSideWindowNumber-j-1)*w;
			rc.right=rc.left+w;
			rc.top=m_rectScreen.top+(m_nSideWindowNumber-i-1)*h;
			rc.bottom=rc.top+h;
            if (i == 0)
			{
				rc.bottom = m_rectScreen.bottom;
			}
			if (j == 0)
				rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

			m_rectWindow[i*m_nSideWindowNumber+j]=rc;
		}
	}
}

// 设置模板5的参数 
// 8+1模板
void CTempletFree::SetTempletParam5(void)
{
	CRect	rc;
	int		i,w,h,l;

	InitSetTempletParam(l, w, h);

	m_nMaxWindowNumber=(m_nSideWindowNumber-1)*4;

	m_rectFree.top=m_rectScreen.top+h;
	m_rectFree.bottom=m_rectScreen.bottom-h;
	m_rectFree.left=m_rectScreen.left+w;
	m_rectFree.right=m_rectScreen.right-w-m_rectScreen.Width()%m_nSideWindowNumber;
	m_rectMidWindow = m_rectFree;

	// 顶部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		m_rectWindow[i]=rc;
	}

	// 右部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

		m_rectWindow[i+m_nSideWindowNumber-1]=rc;
	}

	// 底部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
		rc.bottom = m_rectScreen.bottom;

		if (i == 0)
			rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

		m_rectWindow[i+m_nSideWindowNumber*2-2]=rc;
	}

	// 左部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-i-1)*h;
		rc.bottom=rc.top+h;
        if (i == 0)
		{
			rc.bottom = m_rectScreen.bottom;
		}
		m_rectWindow[i+m_nSideWindowNumber*3-3]=rc;
	}
	if (m_bShowBigWindow)
	{
		m_rectWindow[m_nMaxWindowNumber]=m_rectFree;
		m_nMaxWindowNumber += 1;
	}
}

// 设置模板6的参数 
// 11+1模板
void CTempletFree::SetTempletParam6(void)
{
	CRect	rc;
	int		i,w,h,l;

	InitSetTempletParam(l, w, h);

	m_nMaxWindowNumber=m_nSideWindowNumber*2-1;

	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.bottom-h;
	m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.right-w-m_rectScreen.Width()%m_nSideWindowNumber;
	m_rectMidWindow = m_rectFree;

	// 右部位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;
        if (i == m_nSideWindowNumber-1)
		{
			rc.bottom = m_rectScreen.bottom;
		}
		m_rectWindow[i]=rc;
	}

	// 底部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-2)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
        rc.bottom = m_rectScreen.bottom;
		m_rectWindow[i+m_nSideWindowNumber]=rc;
	}
	if (m_bShowBigWindow)
	{
		m_rectWindow[m_nMaxWindowNumber]=m_rectFree;
		m_nMaxWindowNumber += 1;
	}
}

// 设置模板7的参数 
// 4x5模板
void CTempletFree::SetTempletParam7(void)
{
	CRect	rc;
	int		i,w,h,l;

	InitSetTempletParam(l, w, h);

	m_nMaxWindowNumber=m_nSideWindowNumber*2-1;

	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.bottom-h;
	m_rectFree.left=m_rectScreen.left+w;
	m_rectFree.right=m_rectScreen.right;
	m_rectMidWindow = m_rectFree;

	// 右部位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		rc.left=m_rectScreen.left;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;
        if (i == m_nSideWindowNumber - 1)
		{
			rc.bottom = m_rectScreen.bottom;
		}
		m_rectWindow[i]=rc;
	}

	// 底部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(i+1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
		rc.bottom = m_rectScreen.bottom;

		if (i == (m_nSideWindowNumber-2))
			rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

		m_rectWindow[i+m_nSideWindowNumber]=rc;
	}
	//m_rectWindow[6].top = m_rectWindow[7].top;
	if (m_bShowBigWindow)
	{
		m_rectWindow[m_nMaxWindowNumber]=m_rectFree;
		m_nMaxWindowNumber += 1;
	}
}


// 设置模板8的参数 
// 3x4模板
void CTempletFree::SetTempletParam8(void)
{
	CRect	rc;
	int		i,w,h,l;

	InitSetTempletParam(l, w, h);

	m_nMaxWindowNumber=m_nSideWindowNumber*4-4;

	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.bottom-h*2;
	m_rectFree.left=m_rectScreen.left;
	m_rectFree.right=m_rectScreen.right-w*2-m_rectScreen.Width()%m_nSideWindowNumber;
	m_rectMidWindow = m_rectFree;

	// 右部位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;
		if (i == m_nSideWindowNumber - 1)
		{
			rc.bottom = m_rectScreen.bottom;
		}
		m_rectWindow[i]=rc;
	
	}

	// 底部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-2)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
        rc.bottom = m_rectScreen.bottom;
		m_rectWindow[i+m_nSideWindowNumber]=rc;
	}


	// 右进一部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-2)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+m_nSideWindowNumber*2-1]=rc;
	}

	// 底上一部位置
	for (i=0; i<(m_nSideWindowNumber-2); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-3)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-2)*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+m_nSideWindowNumber*3-2]=rc;
	}
	if (m_bShowBigWindow)
	{
		m_rectWindow[m_nMaxWindowNumber]=m_rectFree;
		m_nMaxWindowNumber += 1;
	}
}

// 设置模板9的参数 
// 6+1模板
void CTempletFree::SetTempletParam9(void)
{
	CRect	rc;
	int		i,w,h,l;

	InitSetTempletParam(l, w, h);

	m_nMaxWindowNumber=m_nSideWindowNumber*4-4;

	m_rectFree.top=m_rectScreen.top;
	m_rectFree.bottom=m_rectScreen.bottom-h*2;
	m_rectFree.left=m_rectScreen.left+w*2;
	m_rectFree.right=m_rectScreen.right;	
	m_rectMidWindow = m_rectFree;

	// 右部位置
	for (i=0; i<m_nSideWindowNumber; i++)
	{
		rc.left=m_rectScreen.left;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;
        if (i == m_nSideWindowNumber - 1)
		{
			rc.bottom = m_rectScreen.bottom;
		}
		m_rectWindow[i]=rc;
	}

	// 底部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(i+1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
		rc.bottom = m_rectScreen.bottom;
		if (i == (m_nSideWindowNumber-2))
			rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;
        
		m_rectWindow[i+m_nSideWindowNumber]=rc;
	}


	// 右进一部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+m_nSideWindowNumber*2-1]=rc;
	}

	// 底上一部位置
	for (i=0; i<(m_nSideWindowNumber-2); i++)
	{
		rc.left=m_rectScreen.left+(i+2)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-2)*h;
		rc.bottom=rc.top+h;

		if (i == (m_nSideWindowNumber-3))
			rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

		m_rectWindow[i+m_nSideWindowNumber*3-2]=rc;
	}
	if (m_bShowBigWindow)
	{
		m_rectWindow[m_nMaxWindowNumber]=m_rectFree;
		m_nMaxWindowNumber += 1;
	}
}

// 设置模板10的参数 
// 8+1模板
void CTempletFree::SetTempletParam10(void)
{
	CRect	rc;
	int		i,w,h,l;

	InitSetTempletParam(l, w, h);

	m_nMaxWindowNumber=(m_nSideWindowNumber-1)*4;

	m_rectFree.top=m_rectScreen.top+h;
	m_rectFree.bottom=m_rectScreen.bottom-h;
	m_rectFree.left=m_rectScreen.left+w;
	m_rectFree.right=m_rectScreen.right-w-m_rectScreen.Width()%m_nSideWindowNumber;
	m_rectMidWindow = m_rectFree;

	// 顶部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{	
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

		m_rectWindow[i]=rc;
	}

	// 底部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
        rc.bottom = m_rectScreen.bottom;
		m_rectWindow[i+m_nSideWindowNumber*1-1]=rc;
	}

	// 左部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-i-1)*h;
		rc.bottom=rc.top+h;
		if (i == 0)
		{
			rc.bottom=m_rectScreen.bottom;
		}
		m_rectWindow[i+m_nSideWindowNumber*2-2]=rc;
	}

	// 右部位置
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;	

		m_rectWindow[i+m_nSideWindowNumber*3-3]=rc;
	}
	if (m_bShowBigWindow)
	{
		m_rectWindow[m_nMaxWindowNumber]=m_rectFree;
		m_nMaxWindowNumber += 1;
	}
}

// 获得中间窗口区域
RECT CTempletFree::GetMidRect()
{
	return m_rectMidWindow;
}

// 获得屏幕索引号
int CTempletFree::GetScreenIndex()
{
	return m_nScreenIndex;
}

void CTempletFree::GetBigWindows(int iBigWindows[3])			//得到大窗口
{
	int i=0;for ( i=0;i<3;i++)
		iBigWindows[i]=m_nBigWindows[i];
}