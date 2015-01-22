//BaseDlg.h

#pragma once
#include "Resource/UtilBase/VideoDropTarget.h"
//#include "../AVCRecord/AVCRecord.h"
#include "Resource/DataDefine/ResourceDefine.h"
//#include "VirtualAVChannl.h"
//#include "../../Include/H323DataInfo.h"
#include "DlgPMosaicScreenADScreen.h"

//宏定议
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

//拖动定义
#define		DROP_VIDEO_DLG_TO_DLG		1
#define		DROP_VIDEO_TREE_TO_DLG		2
#define		DROP_VIDEO_LOCAL_TO_DLG		3

#define  WM_AUDIO_SETTING_MSG			WM_USER + 25836
#define	 WM_VIDEO_SETTING_MSG			WM_USER + 25837
#define  IDM_USER_VIDEO_FORMAT_SETTING	WM_USER + 26000
#define  IDM_WIN_VIDEO_FORMAT_SETTING	WM_USER + 26001
#define  MW_WIN_VIDEOFORMAT_SET_OKCANAL	WM_USER + 26003	// 窗口视频格式设置对话框 确认取消消息 
#define  MW_WIN_DETAILINFO_OKCANAL		WM_USER + 26005	// 窗口视频格式设置对话框 确认取消消息 

class CConferenceWinDlg;
class CDlgFloatWin;
class CDlgFullScreen;
//
class CBaseWinDlg :
	public CDialog
{
	DECLARE_DYNAMIC(CBaseWinDlg)
public:
	//设置标题栏字体,字的颜色和背景色,	add by tiger,2008.09.27
	virtual void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255)){};
/*
void CBaseDlg::SetWindowPosEx(CRect &rcWindow, CRect rc, CPoint point)
{
	//放大
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
	}else if(2==m_iZoomIn)	//缩小
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

    //这里处理屏幕共享
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

			////模板控制器
			//if (((CConferenceDlg*)(m_pdMainDlg))->GetTemplateControlDlg())
			//	((CConferenceDlg*)(m_pdMainDlg))->GetTemplateControlDlg()->SetDragParam(buffer, 5);
			END_DROP;
		}
		//add by tiger,2008.08.12
		//增加本地视频到模板的拖动
		else
		{
			if (GetFloatWin())
			{
				CConferenceDlg *pDlgConferenceDlg = (CConferenceDlg *)m_pdMainDlg;
				ASSERT(pDlgConferenceDlg);
				TLocalUserInfo *pLocalUserInfo = pDlgConferenceDlg->GetLocalUserInfo();
				ASSERT(pLocalUserInfo);
				if ( pLocalUserInfo->_iStatusFlag == ntPresideLogin ||	//主持人
					pLocalUserInfo->_iStatusFlag == ntWatchUser ||	//监控人员
					pDlgConferenceDlg->IsProlocutor(pLocalUserInfo->_pUserInfo->_iSessionID))	//发言人
				{
					BEGIN_DROP(5);

					unsigned long	ulSource=(unsigned long)this;

					buffer[0] = DROP_VIDEO_LOCAL_TO_DLG;
					memcpy(buffer+1, &ulSource, 4);

					//模板控制器
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
	//设置标题栏字体,字的颜色和背景色,	add by tiger,2008.09.27
	virtual void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255)){};

	virtual void SetSynchronization(bool bEnableSyn);	//唇音同步
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
	virtual void ShowCodeFlow(BOOL bShowCodeFlow);					//显示码流
	virtual void ShowTitleBar(BOOL bShowTitleBar);//为定制，在“操作”菜单中增加“显示标题栏”，且默认选中
												//add by lzl,2008.10.20
	
	virtual void VideoShowMode(VideoShowModeType nVideoShowMode);	// 视频显示模式	Add Han Huajie 2008/01/15
	virtual void CloseVidioSoundWizardDlg(BOOL bIsOK){};			//打开视音频调节
	virtual UINT GetVideoBitrate(){return 0;};
	virtual UINT GetAudioBitrate(){return 0;};   
	virtual unsigned long GetSoundChannelID(){return 0;};					//得到音频通道号
	virtual unsigned long GetVideoChannelID(){return 0;};					//得到视频通道号
	virtual BOOL IsHaveSound(){return m_bOpenAudio;};								//是否有音频
	virtual BOOL IsHaveVideo(){return m_bOpenVideo;};								//是否有视频
	virtual BOOL IsHaveSendSingleAudio(unsigned __int32 iInceptSessionID){return FALSE;};	// 是否已经发送音频	Add Han Huajie    2008-4-17
	virtual BOOL IsHaveSendSingleVideo(unsigned __int32 iInceptSessionID){return FALSE;};	// 是否已经发送视频 Add Han Huajie    2008-4-17
	virtual void ClearSendSingleAVdio(unsigned __int32 iInceptSessionID, BOOL bAVdioFlg){};	// bAVdioFlg: 0 音频, 1 视频	Add Han Huajie    2008-4-17
	virtual void InitCapture(){};					//初始化采集
	virtual BOOL CreateVideoChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0){return FALSE;};	//建立视频通道
	virtual BOOL CloseVideoChannel(){return FALSE;};	//关闭视频通道
	virtual BOOL CreateSoundChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0){return FALSE;};	//建立音频通道
	virtual BOOL CloseSoundChannel(){return FALSE;};	//关闭音频通道
	virtual void SetSendSingleAVdioInfo(unsigned __int32 iInceptSessionID, byte ucUserCardNo, int iAVdioFlg){};	// 设置音视频单个发送的状态信息，iAVdioFlag: 0 音频、 1 视频 
    virtual void OnResizeVideoRect(int x, int y, int cx, int cy);   //指示调整视频大小
    CDlgFloatWin *GetFloatWin() const;
	CWnd *GetFloatWnd() const;
    CString GetSource() const;
	virtual CWnd *GetVideoWindow() const{return NULL;};
	virtual void SetWatch();			//设监控
	virtual void CloseWatch();			//关闭监控
	virtual BOOL StartConferenceRecord()=0;		// 开始会议录像
	virtual void StopConferenceRecord()=0;		// 停止会议录像
	virtual BOOL StartRecord()=0;				// 开始录制
	virtual void StopRecord()=0;				// 停止录像
	virtual void SetMICMute(BOOL bMute){};			// 设置静音		FALSE 静音	TRUE 有声音
	virtual void WindowSelectedToJPG(){};			//拍照
	void SetMainDlg(CDialog *pdMainDlg);		//设主窗口
	void SetIndex(int iIndex);			//设置窗口号
	void SetUserInfo(CString strInviteUserName,unsigned __int32 iSessionID,
        byte ucUserCardNo, FrameInfoType iFrameInfoType,BOOL bDragFlg);

	void SetIsMyInceptVideo(BOOL bIsMyInceptVideo);				//设置是否自己单接的视频
	void SetIsMyInceptSound(BOOL bIsMyInceptSound);				//设置是否自己单接的音频
	BOOL IsMyInceptVideo();				//是否自己单接的视频
	BOOL IsMyInceptSound();				//是否自己单接的音频
	byte GetIndex();					//得到窗口号
    byte GetCardNo();   //得到卡号
	unsigned __int32 GetSessionID();				//会话ID
	byte GetUserCardNo();				//用户视频卡号	0~12
	FrameInfoType GetFrameInfoType();	//框上显示的是哪种信息
    BOOL SetDragFlag(BOOL bFlag);   //设置拖动标志, 返回前一个标志状态
    virtual BOOL GetDragFlag() const;
    BOOL SetFullScreenFlag(BOOL bFlag);  //设置全屏标志
    virtual BOOL GetFullScreenFlag() const;

	//void ExitFullScreen();      //退出全屏
	//void ExitFloatWindow();

	//void FullScreen();

	void SetSelected(bool bSelect);
	bool IsSelected(void);

	

    ////浮动窗口
    //virtual void OpenFloatWindow(BOOL bIsDoubleScreen, unsigned int ulSrcSessionID);

    //virtual void FloatWindowTo(const CRect &rect,       //屏幕位置
    //                            BOOL bIsDoubleScreen);  //是否双屏
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
	DWORD	m_dwH323ChannelNO;		// 音频的唯一标识，区分是发送的哪个音频流
	BOOL m_bIsMyInceptVideo;				//是否自己单接的视频
	BOOL m_bIsMyInceptSound;				//是否自己单接的音频
	BOOL m_bWatch;						//监控标志
	int m_iIndex;						//窗口号
	CDialog *m_pdMainDlg;
    CWnd *m_pConferenceWinDlg;    //所在的模板窗口
	CString m_strUserName;
	unsigned __int32		m_iSessionID;				//会话ID
	byte					m_iCardNo;				//用户视频卡号
	FrameInfoType			m_iFrameInfoType;	//框上显示的是哪种信息
	CVideoDropTarget		m_videoDropTarget;
    CDlgFullScreen          *m_pWndFullScreen;  //全屏窗口
    BOOL                    m_bIsFullScreen;    //是否全屏标志
	BOOL					m_bDragFlg;		//是否允许拖动
	BOOL					m_bShowTitleBar;	//为定制，在“操作”菜单中增加“显示标题栏”，且默认选中
												//是否显示标题栏	//add by lzl,2008.10.20
	
	BOOL					m_bShowCodeFlow; //是否显示码流
	bool					m_bIsAvAdjust;
	BOOL					m_bControl;
	VideoShowModeType		m_nVideoShowMode;	// 视频显示模式
	BOOL					m_bSynchronization;	//唇音同步

	int m_iZoomIn;	//放大或者缩小，0：默认值，1：放大，2：缩小	add by tiger,2008.07.18
	HCURSOR   m_hCursor;	//放大镜指针图标	add by tiger,2008.07.18

	UINT m_ulVideoBitrate;
	UINT m_ulAudioBitrate;

	UINT m_ulAudioBitrateSum;

    //
    virtual BOOL IsAllowDragDrop() const;     //是否允许拖动, 由子类继承实现

	//Mouse事件(继承用)
	//王亮 2005.05.08 
	//在UserDlg中要使用 OnLButtonDown, OnLButtonUp, OnMouseMove 消息
	virtual void Do_LButtonDown(UINT nFlags, CPoint point);
	virtual void Do_LButtonUp(UINT nFlags, CPoint point);
	virtual void Do_MouseMove(UINT nFlags, CPoint point);
    virtual void Do_LButtonDbClick(UINT nFlags, CPoint point);

	int GetDesktopWidth(ScreenNOType ntScreenNO);
	int GetDesktopHeight(ScreenNOType ntScreenNO);

public:
	virtual void SetLocalLoopBackTest(BOOL bLocalLoopBackTest){};		// 设置本地环回测试
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
	BOOL			m_bLocalLoopBackTest;	// 本地环回测试	Add HHJ 2009/7/30
	bool			m_bIsSelected;			//是否被选中
public:
	void DrawSelectedFrame(CDC *pDC);

	//////////////////////////////////////////////////////////////////////////
	// 视频预设置方法	Add HHJ 2009/08/06
	virtual void SetUsingWinVideoFormatInfo(TPreSettingInfo* ptPreSettingInfo){};// 应用视频设置格式
	// End Add
	//////////////////////////////////////////////////////////////////////////
	
	// 得到视频的详细信息
	virtual void GetAVdieoDetailInfo(unsigned long& ulWidth,			// 视频宽度
									 unsigned long& ulHeight,			// 视频高度
									 unsigned long& ulAudioBitrate,		// 音频码流
									 unsigned long& ulAudioLost,		// 音频丢包
									 unsigned long& ulVideoBitrate,		// 视频码流
									 unsigned long& ulVideoLost,		// 视频丢包
									 int& nVolume,						// 音量大小
									 int& nVideoFrame){};					// 视频帧率	
	//设置注册会议退出和注销的消息, 在退出会议时关闭浮动窗口
	virtual void SetCloseMessageHandle(CWnd* pMainWnd){};

	// 创建音频的传输通道回调接口    
	// dwChannelNO:  音频的唯一标识，区分是发送的哪个音频流
	// lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
	virtual void CreateAudioChannelCallBack(DWORD dwChannelNO, LONG lContext){};

	// 创建视频的传输通道回调接口    
	// dwChannelNO:  视频的唯一标识，区分是发送的哪个视频流
	// lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
	virtual void CreateVideoChannelCallBack(DWORD dwChannelNO, LONG lContext){}; 

	// 关闭音频的传输通道回调接口(用于释放相应的发送或接受数据的对象)   
	// dwChannelNO:  音频的唯一标识，区分是关闭的哪个音频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
	virtual void CloseH323AudioChannelCallBack(DWORD dwChannelNO, LONG lContext){};  

	// 关闭视频的传输通道回调接口(用于释放相应的发送或接受数据的对象)     
	// dwChannelNO:  视频的唯一标识，区分是关闭的哪个视频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
	virtual void CloseH323VideoChannelCallBack(DWORD dwChannelNO, LONG lContext){}; 
};

