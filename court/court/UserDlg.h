#if !defined(AFX_USERDLG_H__A193E93B_05EE_4345_9299_3E249C6BDB82__INCLUDED_)
#define AFX_USERDLG_H__A193E93B_05EE_4345_9299_3E249C6BDB82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//

//#include "../../Include/IOVideoDis.h"
//#include "../../Include/DataDefine/AVMTMCUClient.h"
//#include "DlgFloatWin.h"
//#include "DlgRemoteAVWizard.h"
//#include "DlgCtrlRemoteSetting.h"
//#include "./YunTai/DlgAVInfo.h"
#include "resource.h"
#include "BaseDlg.h"
//#include "PrePointSetDlg.h"
//#include "WinVideoFormatSetDlg.h"
#include <map>
#include "DrawingObject.h"


// CCUserWinDlgDlg 对话框
class CCUserWinDlgDlg : public CBaseDlg
{
	// 构造
public:
	CCUserWinDlgDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_USER_DIALOG };
	//BOOL Create(UINT nIDTemplet, CWnd* pParentWnd)
	//{
	//	m_pConferenceWinDlg = pParentWnd;
	//	return CDialog::Create(nIDTemplet, pParentWnd);
	//}

	virtual void Do_LButtonDown(UINT nFlags, CPoint point);
	virtual void Do_LButtonUp(UINT nFlags, CPoint point);
	bool m_bSelect;
protected:
	//CWnd *m_pConferenceWinDlg;    //所在的模板窗口
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:

	//int m_iSessionID;						//窗口号
	//int m_iIndex;						//窗口号
	//CDialog *m_pdMainDlg;
	void SetIndex(int iIndex)			//设置窗口号
	{
		m_iIndex=iIndex+1;
	}
	void SetSessionID(int iSessionID)			//设置窗口号
	{
		m_iSessionID=iSessionID;
	}
	void SetMainDlg(CDialog *pdMainDlg)		//设主窗口
	{
		m_pdMainDlg=pdMainDlg;
	}
CDrawingObject m_drawingObject;

	CString m_strText;
	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool IsSelected(void)
	{
		if (m_pConferenceWinDlg && m_iIndex > 0 )
		{
			return ((CConferenceWinDlg*)m_pConferenceWinDlg)->GetWindowSelected(m_iIndex - 1);
		}
		return false;
	}

	//void DrawSelectedFrame(CDC *pDC)
	//{
	//	CRect T_rect;
	//	GetClientRect(T_rect);

	//	if (IsSelected())
	//	{
	//		const int nLineWidth = 2;
	//		CRect rectTop = T_rect;
	//		rectTop.bottom = nLineWidth;

	//		CRect rectBottom = T_rect;
	//		rectBottom.top = rectBottom.bottom - nLineWidth;

	//		CRect rectLeft = T_rect;
	//		rectLeft.right = nLineWidth;
	//		CRect rectRight = T_rect;
	//		rectRight.left = rectRight.right - nLineWidth;

	//		pDC->FillRect(&rectTop, &CBrush(RGB(255,0,0)));
	//		pDC->FillRect(&rectBottom, &CBrush(RGB(255,0,0)));
	//		pDC->FillRect(&rectLeft, &CBrush(RGB(255,0,0)));
	//		pDC->FillRect(&rectRight, &CBrush(RGB(255,0,0)));
	//	}
	//}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
		virtual BOOL StartConferenceRecord(){return FALSE;}		// 开始会议录像
	virtual void StopConferenceRecord(){}		// 停止会议录像
	virtual BOOL StartRecord(){return FALSE;}				// 开始录制
	virtual void StopRecord(){}				// 停止录像
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
//
//class CUserDlg 
//	: public CBaseDlg
//	, public IDlgYTNotify			//		
//	, public IAVAudioReceiverNotify
//	, public IAVVideoReceiverNotify
//	, public IAVCRecordFactoryEvent
//    , public IAVInfoNotify  
//	, public ISendAVdieoDataInfoCallBack
//	, public IOVideoDisNotify
//	, public IOAudioPlayNotify
//{
//	DECLARE_DYNAMIC(CUserDlg)
//// Construction
//public:
//	void CloseVidioSoundWizardDlg(BOOL bIsOK);			//关闭视音频调节
//    UINT GetVideoBitrate();
//    UINT GetAudioBitrate();
//    
//	//会议录像
//	//////////////////////////////////////////////////////////////////////////
//	BOOL StartConferenceRecord();		// 开始会议录像
//	void StopConferenceRecord();		// 停止会议录像
//	//////////////////////////////////////////////////////////////////////////
//
//    void SetWatch();			//设监控
//	void CloseWatch();			//关闭监控
//	BOOL CreateVideoChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//建立视频通道
//	BOOL CloseVideoChannel();	//关闭视频通道
//	BOOL CreateSoundChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//建立音频通道
//	BOOL CloseSoundChannel();	//关闭音频通道
//	//BOOL IsHaveSound();					//是否有音频
//	//BOOL IsHaveVideo();					//是否有视频
//    virtual BOOL DestroyWindow();
//	CWnd *GetVideoWindow() const;
//	//
////	void OnVolume(int vol);
//
//    CUserDlg(CWnd* pParent = NULL);   // standard constructor
//
//// Dialog Data
//	//{{AFX_DATA(CUserDlg)
//	enum { IDD = IDD_USER_DIALOG };
//		// NOTE: the ClassWizard will add data members here
//	//}}AFX_DATA
//
//
//// Overrides
//	// ClassWizard generated virtual function overrides
//	//{{AFX_VIRTUAL(CUserDlg)
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//	//}}AFX_VIRTUAL
//
//// Implementation
//protected:
//
//	// Generated message map functions
//	//{{AFX_MSG(CUserDlg)
//	virtual BOOL OnInitDialog();
// 	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//
//    afx_msg void OnSize(UINT nType, int cx, int cy);
//    afx_msg void OnContextMenu(CWnd* pWnd, CPoint pt);
//    afx_msg void OnRecord();
//	afx_msg void OnToJPG();
//    afx_msg void OnBroadCaseVideo();
//    afx_msg void OnAVWizard();
//    afx_msg void OnTitleBar();
//    afx_msg void OnVideoControlBar();
//    afx_msg void OnVideoControlSet();
//    afx_msg void OnSetPrepoint();
////    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
////    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//    afx_msg void OnBroadcastSound();
//	afx_msg void OnBroadcastAVdieo();
//	afx_msg void OnWacthAVdieo();
//    afx_msg void OnInceptVideo();
//    afx_msg void OnInceptSound();
////    afx_msg void OnCloseUser();
//	afx_msg void OnScreenControl();
//	afx_msg void OnScreenCancelControl();
//    afx_msg void OnTimer(UINT nIDEvent);
//	afx_msg LRESULT OnReveiveMessage(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT OnRecordMessage(WPARAM wParam, LPARAM lParam);			//录像消息
//	afx_msg void OnRemoteSetting();
//	afx_msg void OnAudioSetting();
//	afx_msg void OnVideoSetting();
//	void ShowRemoteCtrlSetting(ComParameter ComPar);
////    afx_msg LRESULT OnResizeWindow(WPARAM wParam, LPARAM lParam);
//
//	//回调函数IAVUserPlayerNotify
//	////////////////////////////////////////////////////
//public:
//	//////////////////////////////////////////////////////////////////////////
//	// IOVideoDisNotify 回调接口
//	//输出音频数据包的回调
//	virtual void OnIOAudioDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples);	//pass
//	//输出视频数据包的回调
//	virtual void OnIOVideoDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType);	//pass
//	virtual void OnIOVideoDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen){};		//current not used
//	//输出视频子流数据包的回调
//	virtual void OnIOVideoSubDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType){};			//current not used
//	virtual void OnIOVideoSubDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen){};	//current not used
//	//////////////////////////////////////////////////////////////////////////
//
//	//tiger Audio
//	//////////////////////////////////////////////////////////////////////////
//	//解码后的输出音频数据包的回调
//	virtual void OnIOAudioPlayDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples);
//	//////////////////////////////////////////////////////////////////////////
//
//
//	void OnIHPAVPlayerNotifyAudioLevel(int nAudioLevel);	//
//	void ResizeControls(void);
//
//	void OnIAVVideoReceiverNotifyReceivedVideoFrame(const char*pData,int nLen);	//视频数据, 用于录像
//	void OnIAVVideoReceiverNotifyConnected(/*unsigned long ulIP*/);
//
//	void OnIAVAudioReceiverNotifyReceivedAudioFrame(const char*pData,int nLen);	//音频数据, 用于录像
//	void OnIAVAudioReceiverNotifyConnected(/*unsigned long ulIP*/);
//
//	//回调函数IAVCRecordEvent
//	//////////////////////////////////////////////////////////////////////////
//	virtual void OnAVCRecordFactoryEvent_FullFile();
//	//virtual int SendFrame(const char*pData,int nLen);
//	virtual int SendFrame(DWORD dwMessage, DWORD dwParam1, DWORD dwParam2);
//	BOOL DoStartRecord(CString strRecordPathName);		// 执行开始录像
//	BOOL StartRecord(); // 开始录制
//	void StopRecord();// 停止录像
//
//	//设置标题栏字体,字的颜色和背景色,	add by tiger,2008.09.27
//	void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255));
//
//	void ShowTitleBar(BOOL bShow);	//为定制，在“操作”菜单中增加“显示标题栏”，且默认选中
//									//modifed by lzl,2008.10.20
//
//	void WindowSelectedToJPG();			//拍照
//
//private:
//	void FormateTitlebar();	//add by tiger,2008.09.27
//    void SetTitleBarColor() ;
//    void ResetWindowRgn();
//    bool CheckAllControl();     //检查用户权限
//    void NewAVUserPlayer();
//	void DestroyAVUserPlayer();	//释放AVUserPlayer
//
//    void ContextMenu_PrdsideLogin(CMenu &popMenu);
//    void ContextMenu_ConferenceUser(CMenu &popMenu);
//    void ContextMenu_WatchUser(CMenu &popMenu, bool bIsAllowControl);
//	void ContextMenu_IMUser(CMenu &popMenu);
//
//	BOOL m_bHaveAudioData;
//	BOOL m_bHaveVideoData;
//	CString m_strRecordPathName;
//	CString m_strFloat;
//	UINT	m_nTimerCheckAudioDisconnected,m_nTimerCheckVideoDisconnected;
//	IOVideoDis *m_pVideoPlayer;
//	IOAudioPlay *m_pAudioPlay;
//	CDlgAVInfo *m_pDlgAVInfo;	//标题
//	IDlgYT	*m_pDlgYT;			//云台控制窗口
////	CDlgFloatWin *m_pDlgFloatWin;	//浮动窗口
//    CPrePointSetDlg *m_pDlgPrepointSet;
//
//    //语音激励
//    int m_nCurVolume;   //当前的语音大小
//    unsigned long m_ulVolumeTime;   //语音已持续的时间
//    UINT_PTR m_nVolumeTimer;
//    bool m_bInVoiceInspirite;   //激励中
//	CDlgCtrlRemoteSetting *m_pDlgCtrlRemoteSetting;
//
//	//前一个
////	bool m_bMoving;
//
//	IAVAudioReceiver*			m_pAVAudioReceiver;
//	IAVVideoReceiver*			m_pAVVideoReceiver;
//
//	IAVCRecordFactory * m_pAVCRecordFactory;
//	IAVCRecordSingleStream * m_pAVCRecordVideoStream;
//	IAVCRecordSingleStream * m_pAVCRecordAudioStream;
//
//	BOOL m_bIsFirstFrame;
//
//	//会议录像
//	//////////////////////////////////////////////////////////////////////////
//	IAVCRecordSingleStream * m_pConferenceRecordVideoStream;
//	IAVCRecordSingleStream * m_pConferenceRecordAudioStream;
//
//	BOOL m_bIsConferenceFirstFrame;
//	//////////////////////////////////////////////////////////////////////////
//
//	//AVCritSec m_CritSecIAVVideoReceiver;
//	//AVCritSec m_CritSecIAVAudioReceiver;
//
//	AVCritSec m_CritSecRecordVideo;
//	AVCritSec m_CritSecRecordAudio;
//
//	AVCritSec m_CritSecConferenceRecordVideo;
//	AVCritSec m_CritSecConferenceRecordAudio;
//
//	unsigned long				m_ulAudioReceiverChannelID;
//	unsigned long				m_ulVideoReceiverChannelID;
//	bool						m_IsReceivingAudio;
//	bool						m_IsReceivingVideo;
//    double m_LastAudioBitrate ;
//    double m_LastVideoBitrate ;
//
//	//标题TIMER
//    UINT_PTR m_hTitleDlgTimer;
//
//	UINT_PTR m_iAudioLevelTitleTimer;
//
//	//CDlgRemoteAVWizard *m_pdWizardDlg;
//	CAudioSettingDlg* m_pAudioSettingDlg;
//	CVideoSettingDlg* m_pVideoSettingDlg;
//	CWinVideoFormatSetDlg* m_pWinVideoFormatSetDlg;
//
//	CDialog *m_pDlgFile;
//	BOOL m_bCloseDlgFileFlag;
//	CPoint m_ptLastMouse;
//	//std::string strBeingControlerID;
//
//	BOOL m_bFullScreenCpture;	// 是否全屏采集屏幕
//	//CBitmap *m_pBkBitmap;
//
//	CDetailInfoDlg*		m_pDetailInfoDlg;
//	VIDEO_DIS_SIZE		video_size;
//
//	ISendAVdieoDataInfo* m_pISendAVdieoDataInfo;	// H323 数据发送接口
//
//	//CPrepointSettingEvent
////	virtual void OnSendControlSpeed(int nSpeed);
////	virtual void OnSendControlCommand(int nCommand);
//
//	//IDlgYTNotify
//	virtual void OnCommand(LONG lngCommand);
//	virtual void OnSpeed(int nSpeed);
//	virtual void OnSetPrePointName(char *pData);
//    //IAVInfoNotify
//    virtual void IAVInfoNotify_OnVolume(int nVolume);
//
//    //
//    CRect m_OldRect;
//	//virtual void Do_LButtonDown(UINT nFlags, CPoint point);
//	//virtual void Do_LButtonUp(UINT nFlags, CPoint point);
//	//virtual void Do_MouseMove(UINT nFlags, CPoint point);
//    virtual void Do_LButtonDbClick(UINT nFlags, CPoint point);
//    virtual void OpenFloatWindow(BOOL bIsDoubleScreen, unsigned int ulSrcSessionID);
//    virtual void OnResizeVideoRect(int x, int y, int cx, int cy);
//    virtual void FloatWindowTo(const CRect &rect, BOOL bIsDoubleScreen);
//    virtual void CloseFloatWindow( BOOL bIsDoubleScreen );
//	
//public:
//	afx_msg void OnPaint();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	void OnUserScreenControlKeyDown(MSG* pMsg);
//	void OnPermitControl(unsigned int iSessionID, BOOL bPermit);
//	BOOL IsControling();
//	afx_msg void OnShowCodeFlow();
//
//	afx_msg void OnFullScreen();
//	afx_msg void OnLockAvdio();
//	afx_msg void OnFullScreenCpture();
//	void ReSetListData(char * pData);
//
//	void VideoShowMode(VideoShowModeType nVideoShowMode);
//	afx_msg void OnVideoShowModeCut();
//	afx_msg void OnVideoShowModeFill();
//	afx_msg void OnVideoShowModeFull();
//	afx_msg void OnSyncHronization();
//	afx_msg LRESULT OnAudioSetMessage(WPARAM wParam, LPARAM lParam);	// 音频设置对话框确认消息
//	afx_msg LRESULT OnVideoSetMessage(WPARAM wParam, LPARAM lParam);	// 视频设置对话框确认消息
//	virtual void SetSynchronization(bool bEnableSyn);
//	virtual void Do_LButtonDown(UINT nFlags, CPoint point);
//	virtual void SetLocalLoopBackTest(BOOL bLocalLoopBackTest);		// 设置本地环回测试	Add HH
//
//	//////////////////////////////////////////////////////////////////////////
//	// 视频预设置方法	Add HHJ 2009/08/06
//	afx_msg void OnWinUserVideoFormatSet();
//	afx_msg void OnWinVideoFormatSet();
//	afx_msg LRESULT OnWinVideoFormatSetMessage(WPARAM wParam, LPARAM lParam);	// 视频设置对话框确认消息
//	virtual void SetUsingWinVideoFormatInfo(TPreSettingInfo* ptPreSettingInfo);// 应用视频设置格式
//	// End Add
//	//////////////////////////////////////////////////////////////////////////
//	void SetBkBmp(CBitmap* pBmp);
//
//	//////////////////////////////////////////////////////////////////////////
//	// 视频详细信息 add HHJ 2009/08/24
//	afx_msg void OnDetailInfoShow();
//	// 得到视频的详细信息
//	virtual void GetAVdieoDetailInfo(unsigned long& ulWidth,			// 视频宽度
//		unsigned long& ulHeight,			// 视频高度
//		unsigned long& ulAudioBitrate,		// 音频码流
//		unsigned long& ulAudioLost,			// 音频丢包
//		unsigned long& ulVideoBitrate,		// 视频码流
//		unsigned long& ulVideoLost,			// 视频丢包
//		int& nVolume,						// 音量大小
//		int& nVideoFrame);					// 视频帧率	
//	afx_msg LRESULT OnWinDetailInfoMessage(WPARAM wParam, LPARAM lParam);	// 视频设置对话框确认消息
//	// End Add
//	//////////////////////////////////////////////////////////////////////////
//
//
//	// 创建音频的传输通道回调接口    
//	// dwChannelNO:  音频的唯一标识，区分是发送的哪个音频流
//	// lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
//	virtual void CreateAudioChannelCallBack(DWORD dwChannelNO, LONG lContext);
//
//	// 创建视频的传输通道回调接口    
//	// dwChannelNO:  视频的唯一标识，区分是发送的哪个视频流
//	// lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
//	virtual void CreateVideoChannelCallBack(DWORD dwChannelNO, LONG lContext); 
//
//	// 关闭音频的传输通道回调接口(用于释放相应的发送或接受数据的对象)   
//	// dwChannelNO:  音频的唯一标识，区分是关闭的哪个音频流
//	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
//	virtual void CloseH323AudioChannelCallBack(DWORD dwChannelNO, LONG lContext);  
//
//	// 关闭视频的传输通道回调接口(用于释放相应的发送或接受数据的对象)     
//	// dwChannelNO:  视频的唯一标识，区分是关闭的哪个视频流
//	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
//	virtual void CloseH323VideoChannelCallBack(DWORD dwChannelNO, LONG lContext); 
//};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__A193E93B_05EE_4345_9299_3E249C6BDB82__INCLUDED_)
