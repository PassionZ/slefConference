
// courtDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "court.h"
#include "courtDlg.h"
#include "afxdialogex.h"
#include "Resource/Com/IRSClient.h"
#include "Resource/Com/ClientFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcourtDlg �Ի���



CcourtDlg::CcourtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcourtDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ptLocalUserInfo=NULL;
	
	m_ptLocalUserInfo=new TLocalUserInfo;
	m_ptLocalUserInfo->_pUserInfo=new TConferenceUserInfo;
	m_ptLocalUserInfo->_pUserInfo->_ptMediaInfo=new TMediaInfo;
	m_ptLocalUserInfo->_pConferenceInfo=NULL;
	wsprintf(m_ptLocalUserInfo->_pUserInfo->_strUserName,_T(""));
	m_ptLocalUserInfo->_iStatusFlag=ntStatusFlageNull;
}

void CcourtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcourtDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CcourtDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CcourtDlg ��Ϣ�������

BOOL CcourtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	InitClient();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_pIRSClient->Connect("192.168.0.65",7800);

	InitDlg();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CcourtDlg::InitDlg()
{

	m_ptLocalUserInfo=new TLocalUserInfo;
	m_ptLocalUserInfo->_pUserInfo=new TConferenceUserInfo;
	m_ptLocalUserInfo->_pUserInfo->_ptMediaInfo=new TMediaInfo;
	m_ptLocalUserInfo->_pConferenceInfo=NULL;
	wsprintf(m_ptLocalUserInfo->_pUserInfo->_strUserName,_T(""));
	m_ptLocalUserInfo->_iStatusFlag=ntStatusFlageNull;

	int ndefValue = 0;
	//if (RS_FLAG == 1)//�˹��ܣ�Ĭ��ѡ��Ϊ�����ʺ�����Ϊ����,add by lzl,2008.10.20
	//	ndefValue = ReadConfigDefaultInt(_T("Operate"), _T("OperateType"), ntOperateAccounts);// ��Config.ini
	//else
	//	ndefValue = ReadConfigDefaultInt(_T("Operate"), _T("OperateType"), ntOperateLogin);	// ��Config.ini Add Han Huajie 2008/01/14

	m_ptLocalUserInfo->_iOperateType= ntOperateLogin ;
	////(OperateType)ReadIniInt(_T("Operate"), _T("OperateType"), ndefValue);
	m_ptLocalUserInfo->_pPresideUserInfo=NULL;
	m_ptLocalUserInfo->_bVideoOrder=false;
	m_ptLocalUserInfo->_pUserInfo->_iMCUID=0;
	m_ptLocalUserInfo->_pUserInfo->_iOnlineFlag=0;
	m_ptLocalUserInfo->_pUserInfo->_InfoType=ntUser;
	m_ptLocalUserInfo->_pUserInfo->_phRoot=new HTREEITEM;
	m_ptLocalUserInfo->_pUserInfo->_iSoundDriverIndex=0;
	m_ptLocalUserInfo->_pUserInfo->_iUserMicType=255;
	m_ptLocalUserInfo->_bShowTitleBar=TRUE;		//add by lzl,2008.10.20
	m_ptLocalUserInfo->_bShowCodeFlow=TRUE;

				m_ptLocalUserInfo->_bShowHaveUserMCU=0;
		m_ptLocalUserInfo->_iShowUserState = 0;// ��ʾ����Ա״̬
	m_ptLocalUserInfo->_iVideoShowMode = ntVideoShowModeCut;

	/*m_pdConferenceListDlg->SetConferenceInfoArray(&m_aConferenceInfoArray);
	m_pdConferenceListDlg->ShowWindow(SW_SHOW);

	MoveConferenceListDlg();
	if (m_pDlgLogin)
	{
		m_pDlgLogin->SetLocalUser(m_ptLocalUserInfo);
	}

	InitVideoSoundInfo();
	InitMediaInfo();
	ReadLocalSetting();*/

	////�������� Timer
	//if (m_ptLocalUserInfo->_bConferenceNotify)
	//{
	//	m_nTimerConferenceNotify = 1023;
	//	UINT nSpaceTime = m_ptLocalUserInfo->_iConferenceMin*1000*60;   //�Է���Ϊ��λ
	//	SetTimer(m_nTimerConferenceNotify,nSpaceTime,NULL);
	//}

}
void CcourtDlg::InitClient()
{
	CClientFactory cTempClientFactory;
	if (m_pIRSClient){ m_pIRSClient->LogoutSystem();delete m_pIRSClient;m_pIRSClient=NULL;}
	m_pIRSClient=cTempClientFactory.CreateClient(1,*this);
}
void CcourtDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcourtDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcourtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcourtDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pIRSClient->LogoutSystem();

	CDialogEx::OnOK();
}

//////////////////////////////////////////////////////////////////////////
void CcourtDlg::OnConnectTimeout()
{
	AfxMessageBox(_T("OnConnectTimeout"));
OnBnClickedOk();
}

void CcourtDlg::OnDisconnected()//���ӶϿ�
{
	AfxMessageBox(_T("OnDisconnected"));

OnBnClickedOk();
}

void CcourtDlg::OnConnected(unsigned __int32 iMCUID)
{


	m_pIRSClient->SendLogin("eserver", "123", 3);

}

void CcourtDlg::OnLogin(int nResult,unsigned __int32 iSessionID,const char*cszUserName)//Call FecthMCU
{
		USES_CONVERSION;
	wsprintf(m_ptLocalUserInfo->_pUserInfo->_strUserName,_T("%s"),CA2W(cszUserName));
			//ChangUtf8ToText(cszUserName,m_ptLocalUserInfo->_pUserInfo->_strUserName);
		m_ptLocalUserInfo->_pUserInfo->_iSessionID=iSessionID;
	m_pIRSClient->FecthMCU();

}
void CcourtDlg::OnMCUEnd()//Call FecthMCU
{
	if (m_pIRSClient)
	{
		m_pIRSClient->FetchConferenceList();
	}

}
void CcourtDlg::OnConferenceListEnd()//Call FecthMCU
{
	int nSize = m_aConferenceInfoArray.GetSize();
	if (m_pIRSClient)
	{
		m_pIRSClient->FetchConferenceUserCount(&m_aConferenceInfoArray);	// ���������Ա�� Add Han Huajie 2008-2-26

	}
	LoginConference(120);
}

void CcourtDlg::SendSoundDriver()						//������������
{
	m_pIRSClient->SoundDriverArray(&(m_ptLocalUserInfo->_pUserInfo->_aSoundDriverInfo));
	//CString strTemp;
	//strTemp.Format(_T("%d"),m_ptLocalUserInfo->_pUserInfo->_aSoundDriverInfo.GetSize());
	//WriteErrorLogString(_T("CConferenceDlg"),_T("SendSoundDriver size"),strTemp);
}

void CcourtDlg::SendVideoDriver()						//������������
{
	m_pIRSClient->VideoDriverArray(&(m_ptLocalUserInfo->_pUserInfo->_aVideoDriverInfo));

	//CString strTemp;
	//strTemp.Format(_T("%d"),m_ptLocalUserInfo->_pUserInfo->_aVideoDriverInfo.GetSize());
	//WriteErrorLogString(_T("CConferenceDlg"),_T("SendVideoDriver size"),strTemp);
}
void CcourtDlg::OnSendLoginConference(byte iUserStatus)		//�ص���Ա���
{
	SendSoundDriver();						//������������
		SendVideoDriver();						//������������

		m_pIRSClient->ChangUserMicVideoInfo(m_ptLocalUserInfo->_pUserInfo->_iSessionID,m_ptLocalUserInfo->_pUserInfo->_iSoundDriverIndex, m_ptLocalUserInfo->_pUserInfo->_iUserMicType,&(m_ptLocalUserInfo->_pUserInfo->_aVideoCardInfo));


}
void CcourtDlg::RemoveConferenceInfoArray()
{
	int i=0;for ( i=0;i<m_aConferenceInfoArray.GetSize();i++)
		delete m_aConferenceInfoArray.GetAt(i);

	m_aConferenceInfoArray.RemoveAll();
}
void CcourtDlg::FetchConferenceList()
{
	RemoveConferenceInfoArray();
	if (m_pIRSClient)
	{
		m_pIRSClient->FetchConferenceList();
	}
}
void CcourtDlg::OnConferenceListItem(TConferenceBaseInfo *tConferenceBaseInfo)
{
	int i=0;for ( i=0;i<m_aConferenceInfoArray.GetSize();i++)
	{
		if (m_aConferenceInfoArray.GetAt(i)->_iConferenceID==tConferenceBaseInfo->_iConferenceID)
			return;
	}

	TConferenceInfo *tTempConferenceInfo=new TConferenceInfo;
	tTempConferenceInfo->_iFullScreenSessionID = 0;
	tTempConferenceInfo->_iConferenceID=tConferenceBaseInfo->_iConferenceID;
	wsprintf(tTempConferenceInfo->_strConferenceName,_T("%s"),tConferenceBaseInfo->_strConferenceName);
	wsprintf(tTempConferenceInfo->_strConferenceTopic,_T("%s"),tConferenceBaseInfo->_strConferenceTopic);
	tTempConferenceInfo->_iPresentCount = 0;
	tTempConferenceInfo->_iConferenceUserCount = 0;
	m_aConferenceInfoArray.Add(tTempConferenceInfo);
}
void CcourtDlg::LoginConference(unsigned __int32	iConferenceID)
{
	//
	m_pIRSClient->SendLoginConference(iConferenceID/*m_ptLocalUserInfo->_pUserInfo->_iFrameResource*/);

}
void CcourtDlg::OnConferenceMember(unsigned __int32 iSessionID,const char*cszUserID,byte iUserStatus,const char*csUserName,unsigned __int32 iMCUID)
{
	TConferenceUserInfo *pConferenceUserInfo=NULL;
	HTREEITEM AfterhRoot=TVI_FIRST;
	if (m_ptLocalUserInfo->_pUserInfo->_iSessionID==iSessionID)
	{
		pConferenceUserInfo=m_ptLocalUserInfo->_pUserInfo;
		//if (IsIM())
		//	return;
	}
	else
	{
		pConferenceUserInfo=new TConferenceUserInfo;
		pConferenceUserInfo->_iSessionID=iSessionID;
		pConferenceUserInfo->_iMCUID=0;
		ChangUtf8ToText(cszUserID,pConferenceUserInfo->_iUserID);
		ChangUtf8ToText(csUserName,pConferenceUserInfo->_strUserName);
		pConferenceUserInfo->_phRoot=new HTREEITEM;
		pConferenceUserInfo->_iSoundDriverIndex=0;
		pConferenceUserInfo->_iUserMicType=255;
		pConferenceUserInfo->_iUserStatus=iUserStatus;
		pConferenceUserInfo->_iOnlineFlag=0;
		pConferenceUserInfo->_InfoType=ntUser;
		pConferenceUserInfo->_bPresentFlag=0;
		pConferenceUserInfo->_iMCUID=iMCUID;
		wsprintf(pConferenceUserInfo->_strOnlineTime,_T("99999999999999"));

	//if (!m_bLoginConferenceEndFlag)
			m_aConferenceUserInfoArray.Add(pConferenceUserInfo);
		/*	else
		{
			CString strSource=pConferenceUserInfo->_strUserName,strSource2=pConferenceUserInfo->_iUserID;

			if ((m_ptLocalUserInfo->_strSearchUser==_T(""))||(BlurFindStr(strSource,m_ptLocalUserInfo->_strSearchUser)||BlurFindStr(strSource2,m_ptLocalUserInfo->_strSearchUser)))
			{
				int j=0;
				for ( j=0;j<m_aMCUInfoArray.GetSize();j++)
					if (m_aMCUInfoArray.GetAt(j)->_iMCUID==iMCUID)
						break;

				for (int k=j;k<m_aMCUInfoArray.GetSize();k++)
				{
					TMCUInfo *ptMCUInfo=m_aMCUInfoArray.GetAt(k);
					if ((ptMCUInfo->_iUPMCUid==iMCUID)&&(ptMCUInfo->_phRoot!=NULL))
						AfterhRoot=*(ptMCUInfo->_phRoot);
				}

				int iInsertAt=ConferenceUserInfoByOrder(pConferenceUserInfo,AfterhRoot);
				m_aConferenceUserInfoArray.InsertAt(iInsertAt,pConferenceUserInfo);

				SaveConferenceUserInfoArrayStream(pConferenceUserInfo);

				if (m_ptLocalUserInfo->_iShowUserState!=0)
					return;

				if (j<m_aMCUInfoArray.GetSize())
					m_pdConferenceMainDlg->AddUserOffOnline(pConferenceUserInfo,m_aMCUInfoArray.GetAt(j),AfterhRoot);
			}
		}*/
	}
}
void CcourtDlg::OnMCUItem(TMCUInfo *tMCUInfo)//�Ӹ��ڵ㿪ʼ
{
	TMCUInfo *tTempMCUInfo=new TMCUInfo;

	tTempMCUInfo->_iMCUID=tMCUInfo->_iMCUID;
	tTempMCUInfo->_iUPMCUid=tMCUInfo->_iUPMCUid;
	wsprintf(tTempMCUInfo->_strMCUName,_T("%s"),tMCUInfo->_strMCUName);
	wsprintf(tTempMCUInfo->_strMCUIPAddress,_T("%s"),tMCUInfo->_strMCUIPAddress);
	tTempMCUInfo->_InfoType=ntMCU;
	tTempMCUInfo->_phRoot=new HTREEITEM;

	//m_aMCUInfoArray.Add(tTempMCUInfo);	

	//if(m_pdConferenceMainDlg)
	//	ReInitTree();
}