//BaseDlg.h

#pragma once
#include "Resource/UtilBase/VideoDropTarget.h"
//#include "../AVCRecord/AVCRecord.h"
#include "Resource/DataDefine/ResourceDefine.h"
//#include "VirtualAVChannl.h"
//#include "../../Include/H323DataInfo.h"
#include "DlgPMosaicScreenADScreen.h"

//�궨��
#define BEGIN_DROP(size) \
	UINT	format = RegisterClipboardFormat(_T("DropVideoData"));\
	COleDataSource*	pDataSource = new COleDataSource;\
	if (pDataSource)\
		{\
		HGLOBAL			clipbuffer;\
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, size);\
		char* buffer = (char*)GlobalLock(clipbuffer);\
		if (buffer)\
			{

#define END_DROP \
	pDataSource->CacheGlobalData(format, clipbuffer);\
	GlobalUnlock(clipbuffer);\
	pDataSource->DoDragDrop();\
			}\
			delete pDataSource;\
		}

//�϶�����
#define		DROP_VIDEO_DLG_TO_DLG		1
#define		DROP_VIDEO_TREE_TO_DLG		2
#define		DROP_VIDEO_LOCAL_TO_DLG		3

#define  WM_AUDIO_SETTING_MSG			WM_USER + 25836
#define	 WM_VIDEO_SETTING_MSG			WM_USER + 25837
#define  IDM_USER_VIDEO_FORMAT_SETTING	WM_USER + 26000
#define  IDM_WIN_VIDEO_FORMAT_SETTING	WM_USER + 26001
#define  MW_WIN_VIDEOFORMAT_SET_OKCANAL	WM_USER + 26003	// ������Ƶ��ʽ���öԻ��� ȷ��ȡ����Ϣ 
#define  MW_WIN_DETAILINFO_OKCANAL		WM_USER + 26005	// ������Ƶ��ʽ���öԻ��� ȷ��ȡ����Ϣ 

class CConferenceWinDlg;
class CDlgFloatWin;
class CDlgFullScreen;
//
class CBaseWinDlg :
	public CDialog
{
	DECLARE_DYNAMIC(CBaseWinDlg)
public:
	//���ñ���������,�ֵ���ɫ�ͱ���ɫ,	add by tiger,2008.09.27
	virtual void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255)){};
/*
void CBaseDlg::SetWindowPosEx(CRect &rcWindow, CRect rc, CPoint point)
{
	//�Ŵ�
	if (1==m_iZoomIn)
	{
		if ((point.x - rc.left) < rc.Width()/4)
		{
			rcWindow.right += rc.Width()/4;				
		}else
		{
			if ((rc.right - point.x) < rc.Width()/4)
			{
				rcWindow.left -= rc.Width()/4;
			}else
			{
				rcWindow.left -= rc.Width()/8;
				rcWindow.right += rc.Width()/8;
			}
		}
		if ((point.y - rc.top) < rc.Height()/4)
		{
			rcWindow.bottom += rc.Height()/4;
		}else
		{
			if ((rc.bottom - point.y) < rc.Height()/4)
			{
				rcWindow.top -= rc.Height()/4;
			}else
			{
				rcWindow.top -= rc.Height()/8;
				rcWindow.bottom += rc.Height()/8;
			}
		}
	}else if(2==m_iZoomIn)	//��С
	{
		rcWindow.left += rc.Width()/8;
		rcWindow.right -= rc.Width()/8;
		if (rcWindow.Width() > rc.Width())
		{
			if (rcWindow.left > rc.left)
			{
				rcWindow.left = rc.left;
				rcWindow.right -= rc.Width()/8;
			}else
			{
				if (rcWindow.right < rc.right)
				{
					rcWindow.right = rc.right;
					rcWindow.left += rc.Height()/8;
				}
			}					
		}else
		{
			rcWindow.left = rc.left;
			rcWindow.right = rc.right;
		}
		rcWindow.top += rc.Height()/8;
		rcWindow.bottom -= rc.Height()/8;
		if (rcWindow.Height() > rc.Height())
		{
			if (rcWindow.top > rc.top)
			{
				rcWindow.top = rc.top;
				rcWindow.bottom -= rc.Height()/8;
			}else
			{
				if (rcWindow.bottom < rc.bottom)
				{
					rcWindow.bottom = rc.bottom;
					rcWindow.top += rc.Height()/8;
				}
			}
		}else
		{
			rcWindow.top = rc.top;
			rcWindow.bottom = rc.bottom;
		}

	}
}
void CBaseDlg::DrawSelectedFrame(CDC *pDC)
{
	CRect T_rect;
	GetClientRect(T_rect);

	if (IsSelected())
	{
		const int nLineWidth = 2;
		CRect rectTop = T_rect;
		rectTop.bottom = nLineWidth;

		CRect rectBottom = T_rect;
		rectBottom.top = rectBottom.bottom - nLineWidth;

		CRect rectLeft = T_rect;
		rectLeft.right = nLineWidth;
		CRect rectRight = T_rect;
		rectRight.left = rectRight.right - nLineWidth;

		pDC->FillRect(&rectTop, &CBrush(RGB(255,0,0)));
		pDC->FillRect(&rectBottom, &CBrush(RGB(255,0,0)));
		pDC->FillRect(&rectLeft, &CBrush(RGB(255,0,0)));
		pDC->FillRect(&rectRight, &CBrush(RGB(255,0,0)));
	}
}
void CBaseDlg::Do_LButtonDown(UINT nFlags, CPoint point)
{
	BOOL bControlDown = GetKeyState(VK_CONTROL) & 0x80;
	if (!m_bIsFullScreen)
	{
		if (!bControlDown)
		{
			if (m_pdMainDlg)
			{
				((CConferenceDlg*)m_pdMainDlg)->SetAllWindowSelected(false);
			}
			SetSelected(true);
		}
		else
		{
			SetSelected(!IsSelected());
		}
	}

	if (!m_pdMainDlg||(m_iFrameInfoType == ntFrameNull))
		return;

	if (((CConferenceDlg*)(m_pdMainDlg))->IsIM())
		return;

    //���ﴦ����Ļ����
    if (((m_iFrameInfoType == ntVideoSound && m_iCardNo==SCREEN_IS_VIDEO_NO)||(m_iFrameInfoType == ntScreen)) && 
        m_pdMainDlg && 
        (((CConferenceDlg *)m_pdMainDlg)->GetLocalMemberSessionID() != GetSessionID()))
    {
		BOOL	bControl=GetKeyState(VK_CONTROL) & 0x80;
		if (m_bControl && !bControl)
			return ;
    }

 	if (GetFullScreenFlag()||m_bIsAvAdjust)
		return;

	if (GetFloatWin())
	{
		if(GetFloatWnd() == this)
			return;
		if (m_iIndex == 0)
		{
			SetDragFlag(TRUE);
		}
	}
	else
	{
		if (m_iIndex == 0)
		{
			SetDragFlag(FALSE);
		}
	}	
	
	if ((m_iFrameInfoType != ntFrameNull) && IsAllowDragDrop())
	{
		if (m_iIndex!=0)
		{
			BEGIN_DROP(5);

			unsigned long	ulSource=(unsigned long)this;

			buffer[0] = DROP_VIDEO_DLG_TO_DLG;
			memcpy(buffer+1, &ulSource, 4);

			////ģ�������
			//if (((CConferenceDlg*)(m_pdMainDlg))->GetTemplateControlDlg())
			//	((CConferenceDlg*)(m_pdMainDlg))->GetTemplateControlDlg()->SetDragParam(buffer, 5);
			END_DROP;
		}
		//add by tiger,2008.08.12
		//���ӱ�����Ƶ��ģ����϶�
		else
		{
			if (GetFloatWin())
			{
				CConferenceDlg *pDlgConferenceDlg = (CConferenceDlg *)m_pdMainDlg;
				ASSERT(pDlgConferenceDlg);
				TLocalUserInfo *pLocalUserInfo = pDlgConferenceDlg->GetLocalUserInfo();
				ASSERT(pLocalUserInfo);
				if ( pLocalUserInfo->_iStatusFlag == ntPresideLogin ||	//������
					pLocalUserInfo->_iStatusFlag == ntWatchUser ||	//�����Ա
					pDlgConferenceDlg->IsProlocutor(pLocalUserInfo->_pUserInfo->_iSessionID))	//������
				{
					BEGIN_DROP(5);

					unsigned long	ulSource=(unsigned long)this;

					buffer[0] = DROP_VIDEO_LOCAL_TO_DLG;
					memcpy(buffer+1, &ulSource, 4);

					//ģ�������
					if (((CConferenceDlg*)(m_pdMainDlg))->GetTemplateControlDlg())
						((CConferenceDlg*)(m_pdMainDlg))->GetTemplateControlDlg()->SetDragParam(buffer, 5);
					END_DROP;
				}
			}			
		}
		//end add
	}

}

void CBaseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Do_LButtonDown(nFlags, point);
	//CDialog::OnLButtonDown(nFlags, point);
}
*/
};

class CBaseDlg :
	public CDialog
{
	DECLARE_DYNAMIC(CBaseDlg)
public:
	//���ñ���������,�ֵ���ɫ�ͱ���ɫ,	add by tiger,2008.09.27
	virtual void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255)){};

	virtual void SetSynchronization(bool bEnableSyn);	//����ͬ��
	//void PictureInPictureFullScreen();
	//void PictureInPictureExitFullScreen();
	virtual void ResizeControls(void);
	virtual void ShowRemoteCtrlSetting(ComParameter ComPar){};
	virtual void RemoteYunTaiInit(){};
	virtual BOOL IsControling(){return FALSE;};
	virtual void OnPermitControl(unsigned __int32 iSessionID, BOOL bPermit){};
	virtual BOOL IsControlerDlgExist(unsigned __int32 iSessionID){return FALSE;};
	virtual void ClearAllControlerDlg(){};
	virtual void DeleteControlerDlg(unsigned __int32 iSessionID){};
	virtual void DeleteAllControler(){};
	virtual void AddControler(unsigned __int32 iSessionID){};
	virtual void AddControlerDlg(unsigned __int32 iSessionID){};
	virtual void DeleteControler(unsigned __int32 iSessionID){};
	virtual void OnUserScreenControlKeyDown(MSG* pMsg){};
	CBaseDlg(UINT nIDD,CWnd* pParent = NULL);
	virtual ~CBaseDlg(void);
	CDialog *GetMainDlg();
	virtual void ShowCodeFlow(BOOL bShowCodeFlow);					//��ʾ����
	virtual void ShowTitleBar(BOOL bShowTitleBar);//Ϊ���ƣ��ڡ��������˵������ӡ���ʾ������������Ĭ��ѡ��
												//add by lzl,2008.10.20
	
	virtual void VideoShowMode(VideoShowModeType nVideoShowMode);	// ��Ƶ��ʾģʽ	Add Han Huajie 2008/01/15
	virtual void CloseVidioSoundWizardDlg(BOOL bIsOK){};			//������Ƶ����
	virtual UINT GetVideoBitrate(){return 0;};
	virtual UINT GetAudioBitrate(){return 0;};   
	virtual unsigned long GetSoundChannelID(){return 0;};					//�õ���Ƶͨ����
	virtual unsigned long GetVideoChannelID(){return 0;};					//�õ���Ƶͨ����
	virtual BOOL IsHaveSound(){return m_bOpenAudio;};								//�Ƿ�����Ƶ
	virtual BOOL IsHaveVideo(){return m_bOpenVideo;};								//�Ƿ�����Ƶ
	virtual BOOL IsHaveSendSingleAudio(unsigned __int32 iInceptSessionID){return FALSE;};	// �Ƿ��Ѿ�������Ƶ	Add Han Huajie    2008-4-17
	virtual BOOL IsHaveSendSingleVideo(unsigned __int32 iInceptSessionID){return FALSE;};	// �Ƿ��Ѿ�������Ƶ Add Han Huajie    2008-4-17
	virtual void ClearSendSingleAVdio(unsigned __int32 iInceptSessionID, BOOL bAVdioFlg){};	// bAVdioFlg: 0 ��Ƶ, 1 ��Ƶ	Add Han Huajie    2008-4-17
	virtual void InitCapture(){};					//��ʼ���ɼ�
	virtual BOOL CreateVideoChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0){return FALSE;};	//������Ƶͨ��
	virtual BOOL CloseVideoChannel(){return FALSE;};	//�ر���Ƶͨ��
	virtual BOOL CreateSoundChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0){return FALSE;};	//������Ƶͨ��
	virtual BOOL CloseSoundChannel(){return FALSE;};	//�ر���Ƶͨ��
	virtual void SetSendSingleAVdioInfo(unsigned __int32 iInceptSessionID, byte ucUserCardNo, int iAVdioFlg){};	// ��������Ƶ�������͵�״̬��Ϣ��iAVdioFlag: 0 ��Ƶ�� 1 ��Ƶ 
    virtual void OnResizeVideoRect(int x, int y, int cx, int cy);   //ָʾ������Ƶ��С
    CDlgFloatWin *GetFloatWin() const;
	CWnd *GetFloatWnd() const;
    CString GetSource() const;
	virtual CWnd *GetVideoWindow() const{return NULL;};
	virtual void SetWatch();			//����
	virtual void CloseWatch();			//�رռ��
	virtual BOOL StartConferenceRecord()=0;		// ��ʼ����¼��
	virtual void StopConferenceRecord()=0;		// ֹͣ����¼��
	virtual BOOL StartRecord()=0;				// ��ʼ¼��
	virtual void StopRecord()=0;				// ֹͣ¼��
	virtual void SetMICMute(BOOL bMute){};			// ���þ���		FALSE ����	TRUE ������
	virtual void WindowSelectedToJPG(){};			//����
	void SetMainDlg(CDialog *pdMainDlg);		//��������
	void SetIndex(int iIndex);			//���ô��ں�
	void SetUserInfo(CString strInviteUserName,unsigned __int32 iSessionID,
        byte ucUserCardNo, FrameInfoType iFrameInfoType,BOOL bDragFlg);

	void SetIsMyInceptVideo(BOOL bIsMyInceptVideo);				//�����Ƿ��Լ����ӵ���Ƶ
	void SetIsMyInceptSound(BOOL bIsMyInceptSound);				//�����Ƿ��Լ����ӵ���Ƶ
	BOOL IsMyInceptVideo();				//�Ƿ��Լ����ӵ���Ƶ
	BOOL IsMyInceptSound();				//�Ƿ��Լ����ӵ���Ƶ
	byte GetIndex();					//�õ����ں�
    byte GetCardNo();   //�õ�����
	unsigned __int32 GetSessionID();				//�ỰID
	byte GetUserCardNo();				//�û���Ƶ����	0~12
	FrameInfoType GetFrameInfoType();	//������ʾ����������Ϣ
    BOOL SetDragFlag(BOOL bFlag);   //�����϶���־, ����ǰһ����־״̬
    virtual BOOL GetDragFlag() const;
    BOOL SetFullScreenFlag(BOOL bFlag);  //����ȫ����־
    virtual BOOL GetFullScreenFlag() const;

	//void ExitFullScreen();      //�˳�ȫ��
	//void ExitFloatWindow();

	//void FullScreen();

	void SetSelected(bool bSelect);
	bool IsSelected(void);

	

    ////��������
    //virtual void OpenFloatWindow(BOOL bIsDoubleScreen, unsigned int ulSrcSessionID);

    //virtual void FloatWindowTo(const CRect &rect,       //��Ļλ��
    //                            BOOL bIsDoubleScreen);  //�Ƿ�˫��
    //virtual void CloseFloatWindow( BOOL bIsDoubleScreen );

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT			OnVideoOnDropNotify(WPARAM wParam, LPARAM lParam);

protected:
	DWORD	m_dwH323ChannelNO;		// ��Ƶ��Ψһ��ʶ�������Ƿ��͵��ĸ���Ƶ��
	BOOL m_bIsMyInceptVideo;				//�Ƿ��Լ����ӵ���Ƶ
	BOOL m_bIsMyInceptSound;				//�Ƿ��Լ����ӵ���Ƶ
	BOOL m_bWatch;						//��ر�־
	int m_iIndex;						//���ں�
	CDialog *m_pdMainDlg;
    CWnd *m_pConferenceWinDlg;    //���ڵ�ģ�崰��
	CString m_strUserName;
	unsigned __int32		m_iSessionID;				//�ỰID
	byte					m_iCardNo;				//�û���Ƶ����
	FrameInfoType			m_iFrameInfoType;	//������ʾ����������Ϣ
	CVideoDropTarget		m_videoDropTarget;
    CDlgFullScreen          *m_pWndFullScreen;  //ȫ������
    BOOL                    m_bIsFullScreen;    //�Ƿ�ȫ����־
	BOOL					m_bDragFlg;		//�Ƿ������϶�
	BOOL					m_bShowTitleBar;	//Ϊ���ƣ��ڡ��������˵������ӡ���ʾ������������Ĭ��ѡ��
												//�Ƿ���ʾ������	//add by lzl,2008.10.20
	
	BOOL					m_bShowCodeFlow; //�Ƿ���ʾ����
	bool					m_bIsAvAdjust;
	BOOL					m_bControl;
	VideoShowModeType		m_nVideoShowMode;	// ��Ƶ��ʾģʽ
	BOOL					m_bSynchronization;	//����ͬ��

	int m_iZoomIn;	//�Ŵ������С��0��Ĭ��ֵ��1���Ŵ�2����С	add by tiger,2008.07.18
	HCURSOR   m_hCursor;	//�Ŵ�ָ��ͼ��	add by tiger,2008.07.18

	UINT m_ulVideoBitrate;
	UINT m_ulAudioBitrate;

	UINT m_ulAudioBitrateSum;

    //
    virtual BOOL IsAllowDragDrop() const;     //�Ƿ������϶�, ������̳�ʵ��

	//Mouse�¼�(�̳���)
	//���� 2005.05.08 
	//��UserDlg��Ҫʹ�� OnLButtonDown, OnLButtonUp, OnMouseMove ��Ϣ
	virtual void Do_LButtonDown(UINT nFlags, CPoint point);
	virtual void Do_LButtonUp(UINT nFlags, CPoint point);
	virtual void Do_MouseMove(UINT nFlags, CPoint point);
    virtual void Do_LButtonDbClick(UINT nFlags, CPoint point);

	int GetDesktopWidth(ScreenNOType ntScreenNO);
	int GetDesktopHeight(ScreenNOType ntScreenNO);

public:
	virtual void SetLocalLoopBackTest(BOOL bLocalLoopBackTest){};		// ���ñ��ػ��ز���
    virtual BOOL DestroyWindow();
    virtual BOOL Create(UINT nIDTemplet, CWnd* pParentWnd);
    CWnd *SetConferenceWnd(CWnd* pParentWnd);
    CWnd *GetConferenceWnd() const;

	//virtual float GetK();
	//virtual float GetWidth_K();
	//afx_msg void OnCloseUser();
	//afx_msg void OnMenuZoomIn();	//add by tiger,2008.07.17
	//afx_msg void OnMenuRevert();	//add by tiger,2008.07.17
	//afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);	//add by tiger,2008.07.18
	//afx_msg void OnMoveWindowToPos();

protected:
	virtual void SetWindowPosEx(CRect &rcWindow, CRect rc, CPoint point);
protected:
	bool			m_bOpenAudio;
	bool			m_bOpenVideo;
	BOOL			m_bLocalLoopBackTest;	// ���ػ��ز���	Add HHJ 2009/7/30
	bool			m_bIsSelected;			//�Ƿ�ѡ��
public:
	void DrawSelectedFrame(CDC *pDC);

	//////////////////////////////////////////////////////////////////////////
	// ��ƵԤ���÷���	Add HHJ 2009/08/06
	virtual void SetUsingWinVideoFormatInfo(TPreSettingInfo* ptPreSettingInfo){};// Ӧ����Ƶ���ø�ʽ
	// End Add
	//////////////////////////////////////////////////////////////////////////
	
	// �õ���Ƶ����ϸ��Ϣ
	virtual void GetAVdieoDetailInfo(unsigned long& ulWidth,			// ��Ƶ���
									 unsigned long& ulHeight,			// ��Ƶ�߶�
									 unsigned long& ulAudioBitrate,		// ��Ƶ����
									 unsigned long& ulAudioLost,		// ��Ƶ����
									 unsigned long& ulVideoBitrate,		// ��Ƶ����
									 unsigned long& ulVideoLost,		// ��Ƶ����
									 int& nVolume,						// ������С
									 int& nVideoFrame){};					// ��Ƶ֡��	
	//����ע������˳���ע������Ϣ, ���˳�����ʱ�رո�������
	virtual void SetCloseMessageHandle(CWnd* pMainWnd){};

	// ������Ƶ�Ĵ���ͨ���ص��ӿ�    
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������Ƿ��͵��ĸ���Ƶ��
	// lContext:   Ӧ�ó��������ģ����û�����ͨ��ʱ���룬�˴�ԭ�ⷵ��
	virtual void CreateAudioChannelCallBack(DWORD dwChannelNO, LONG lContext){};

	// ������Ƶ�Ĵ���ͨ���ص��ӿ�    
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������Ƿ��͵��ĸ���Ƶ��
	// lContext:   Ӧ�ó��������ģ����û�����ͨ��ʱ���룬�˴�ԭ�ⷵ��
	virtual void CreateVideoChannelCallBack(DWORD dwChannelNO, LONG lContext){}; 

	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)   
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
	virtual void CloseH323AudioChannelCallBack(DWORD dwChannelNO, LONG lContext){};  

	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)     
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
	virtual void CloseH323VideoChannelCallBack(DWORD dwChannelNO, LONG lContext){}; 
};

