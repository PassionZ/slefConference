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

// ��������ģ������
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
	case 1:	// 2x2ģ��
		SetTempletParam1();	
		break;
	case 2:	// 2x1ģ��
		SetTempletParam2();	
		break;
	case 3:	// 3x2ģ��
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

// ���������������
bool CTempletFree::GetWndRect(int index, LPRECT lpRect)
{
	if ((index>81) || (index>GetWindowCount()))
		return false;

	*lpRect=m_rectWindow[index];
	return true;
}

// ���ʣ������
RECT CTempletFree::GetFreeRect()
{
	return m_rectFree;
}

// ��ÿ����������
RECT CTempletFree::GetControlRect()
{
	return m_rectControl;
}

// ������
int	CTempletFree::GetWindowCount()
{
	return m_nMaxWindowNumber;
}

// ������Ļ������,1.��׼��Ļ, 2.�ڶ�����Ļ
void CTempletFree::SetScreenIndex(int nScreenIndex, RECT rcScreen)
{
	m_rectScreen = rcScreen;
	m_nScreenIndex = nScreenIndex;
}

// ���ȫ��Ļ�ĳߴ�
void	CTempletFree::GetScreenRect(LPRECT lpRect)
{
	if (lpRect)
	{
		*lpRect	= m_rectScreen;
	}
}

// ��ʼ������ģ��,��ÿ����������ÿ����Ƶ���ڸ߶ȺͿ��
void CTempletFree::InitSetTempletParam(int& l, int& w, int& h)
{
	// �����λ��
	l=m_rectScreen.Width()-m_rectScreen.Width()/4*3;

	// �����������
	m_rectControl.left=m_rectScreen.left;
	m_rectControl.right=l+m_rectControl.left;
	m_rectControl.top=m_rectScreen.top;
	m_rectControl.bottom=m_rectScreen.Height()+m_rectScreen.top;

	// �߶ȺͿ��
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

// ����ģ��1�Ĳ��� 
// 2x2ģ��
void CTempletFree::SetTempletParam1(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// ����λ��
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

// ����ģ��2�Ĳ��� 
// 2x1ģ��
void CTempletFree::SetTempletParam2(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// ����λ��
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

// ����ģ��3�Ĳ��� 
// 3x2ģ��
void CTempletFree::SetTempletParam3(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// ����λ��
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

// ����ģ��4�Ĳ��� 
// 3x3ģ��
void CTempletFree::SetTempletParam4(void)
{
	CRect	rc;
	int		i,j,w,h,l;

	InitSetTempletParam(l, w, h);

	// ����λ��
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

// ����ģ��5�Ĳ��� 
// 8+1ģ��
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

	// ����λ��
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+i*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top;
		rc.bottom=rc.top+h;

		m_rectWindow[i]=rc;
	}

	// �Ҳ�λ��
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

		m_rectWindow[i+m_nSideWindowNumber-1]=rc;
	}

	// �ײ�λ��
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

	// ��λ��
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

// ����ģ��6�Ĳ��� 
// 11+1ģ��
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

	// �Ҳ�λ��
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

	// �ײ�λ��
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

// ����ģ��7�Ĳ��� 
// 4x5ģ��
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

	// �Ҳ�λ��
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

	// �ײ�λ��
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


// ����ģ��8�Ĳ��� 
// 3x4ģ��
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

	// �Ҳ�λ��
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

	// �ײ�λ��
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-2)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
        rc.bottom = m_rectScreen.bottom;
		m_rectWindow[i+m_nSideWindowNumber]=rc;
	}


	// �ҽ�һ��λ��
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-2)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+m_nSideWindowNumber*2-1]=rc;
	}

	// ����һ��λ��
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

// ����ģ��9�Ĳ��� 
// 6+1ģ��
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

	// �Ҳ�λ��
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

	// �ײ�λ��
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


	// �ҽ�һ��λ��
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		m_rectWindow[i+m_nSideWindowNumber*2-1]=rc;
	}

	// ����һ��λ��
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

// ����ģ��10�Ĳ��� 
// 8+1ģ��
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

	// ����λ��
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{	
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+i*h;
		rc.bottom=rc.top+h;

		rc.right+=m_rectScreen.Width()%m_nSideWindowNumber;

		m_rectWindow[i]=rc;
	}

	// �ײ�λ��
	for (i=0; i<(m_nSideWindowNumber-1); i++)
	{
		rc.left=m_rectScreen.left+(m_nSideWindowNumber-i-1)*w;
		rc.right=rc.left+w;
		rc.top=m_rectScreen.top+(m_nSideWindowNumber-1)*h;
		//rc.bottom=rc.top+h;
        rc.bottom = m_rectScreen.bottom;
		m_rectWindow[i+m_nSideWindowNumber*1-1]=rc;
	}

	// ��λ��
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

	// �Ҳ�λ��
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

// ����м䴰������
RECT CTempletFree::GetMidRect()
{
	return m_rectMidWindow;
}

// �����Ļ������
int CTempletFree::GetScreenIndex()
{
	return m_nScreenIndex;
}

void CTempletFree::GetBigWindows(int iBigWindows[3])			//�õ��󴰿�
{
	int i=0;for ( i=0;i<3;i++)
		iBigWindows[i]=m_nBigWindows[i];
}