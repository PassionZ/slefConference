#if !defined(AFX_CONFERENCEWINDLG_H__F7DE1D65_B12B_4DE7_B958_4DAFE9678FD0__INCLUDED_)
#define AFX_CONFERENCEWINDLG_H__F7DE1D65_B12B_4DE7_B958_4DAFE9678FD0__INCLUDED_

#include "RESOURCE\DATADEFINE\ResourceDefine.h"	// Added by ClassView
#include "TEMPLETARITHMETIC\TempletArithmetic.h"	// Added by ClassView
#include "resource.h"
//#include "TempleteControlDlg.h"
//#include "TempleteControlParentWnd.h"
//#include "TMDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConferenceWinDlg.h : header file
//
#include "DrawingObject.h"

/////////////////////////////////////////////////////////////////////////////
// CConferenceWinDlg dialog
class CConferenceWinDlg : public CDialog
{
// Construction
public:

	//void SetSynchronization(bool bEnableSyn);			// 唇音同步
	////void PictureInPictureResizeWnd();
	//void SetTempleteControlWndFrameTypeAndCard();
	CWnd *GetBaseDlg(int iBaseDlgNo);
	//void PictureInPictureResetWindowRgn();
	//void PictureInPictureChangeBack(); 
	//void ShowRemoteCtrlSetting(unsigned __int32 iSessionID, int nChannelID, ComParameter ComPar);
	//void RemoteYunTaiInit();
	//void FullScreenScreenCaptureDlg(unsigned __int32 iSessionID);
	//void ExitFullScreenScreenCaptureDlg(unsigned __int32 iSessionID);
	//BOOL IsControling();
	//BOOL IsControlerDlgExist(unsigned __int32 iSessionID);
	//void ClearAllControlerDlg();
	//void DeleteControlerDlg(unsigned __int32 iSessionID);
	//void DeleteControler(unsigned __int32 iSessionID);
	//void DeleteAllControler();
	//void AddControler(unsigned __int32 iSessionID);
	//void AddControlerDlg(unsigned __int32 iSessionID);
	//void ShowCodeFlow(BOOL bShowCodeFlow);			//显示码流
void ShowTitleBar(BOOL bShowTitleBar);//为定制，在“操作”菜单中增加“显示标题栏”，且默认选中
	//									//add by lzl,2008.10.20
	//
	//void VideoShowMode(VideoShowModeType nVideoShowMode);	// 视频显示模式	Add Han Huajie 2008/01/15
	//void OnConvertKeyDownMessage(MSG *pMsg);
	//void PermitControl(unsigned __int32 iSessionID, BOOL bPermit);
	//void StopRecord();	// 停止录像
	//void SetSpeek(BOOL bIsSpeek);
	//BOOL IsHaveInfo(byte ucUserWndIndex);
    UINT GetFreeWnd(byte **pWndArray = NULL) const;   //计算空窗口数
	void CloseAllWindow();	//关闭所有窗口 录像时使用
	void CloseAllWinInfo();	//关闭所有窗口信息 会议同步时使用
	BOOL StartConferenceRecord();		// 开始会议录像
	void StopConferenceRecord();		// 停止会议录像
	void SetWatch();			//设监控
	void CloseWatch();			//关闭监控
	void GetBigWindows(int iBigWindows[3]);						//得到大窗口
	BOOL GetMaxWndIndex(byte &ucUserWndIndex);	//得到当前屏大窗号
	void SetUseWhiteBoard(byte ucWndIndex,bool bAllowUseWhiteBoard);			//设置允许使用白板
	byte GetFrameIndex();										//得到屏号
	void CloseUserInfo(unsigned __int32 iSessionID);			//关闭此人的窗口
	void CloseLocalInfo();			//关闭所有本地的窗口
	void ReceiveControlCommand(byte ucWndIndex,unsigned __int32 iCommand);		//云台控制
	void ReceiveControlSpeed(byte ucWndIndex,byte ucSpeed);						//云台速度
	void ShowConferenceUserDlg();
	void SwapWhoToWndPosition(byte ucDragUserWndIndex,byte ucDragUserFrameIndex,byte ucUserWndIndex);			//广播拖动谁
	void InitCapture(byte ucWndIndex,byte ucUserCardNo);					//初始化采集
	CWnd*CloseInfoWin(byte ucWndIndex);							//关闭xx区
	void CloseWin(byte ucWndIndex);			//关闭窗口
	//void OpenInfoWin(unsigned __int32 iSessionID,byte ucWndIndex,CWnd* pWnd,FrameInfoType iFrameInfoType);	//打开xx区
	void SetConferenceDlg(CDialog *pConferenceDlg);		//设置主窗口指针
	void SendLocalSound(byte ucWndIndex,unsigned __int32 iChannelID);			//发送本地音频
	void SendLocalFirstVideo(byte ucWndIndex,unsigned __int32 iChannelID);			//发送本地第一块卡视频
	void ShowWin(int iWndIndex,CWnd* pWnd);				//显示视频窗口
	void SetFrameIndex(int iFrameIndex);			//设置屏号
	void CloseBroadcastLocalNoFirstSound(byte ucUserWndIndex);						//关闭广播本机的非第一卡音频
	void CloseBroadcastLocalNoFirstVideo(byte ucUserWndIndex);						//关闭广播本机的非第一卡视频
	CWnd* CloseBroadcastLocalSound(byte ucUserWndIndex);						//关闭广播本机的音频
	CWnd* CloseBroadcastLocalFirstVideo(byte ucUserWndIndex);						//关闭广播本机的第一卡视频
	void AddBroadcastLocalSound(byte ucUserWndIndex,unsigned __int32 iChannelID);			//增加广播本机的音频
	void BroadcastLocalNoFirstVideo(byte ucUserWndIndex,unsigned __int32 iChannelID);			//广播本机的非第一卡视频
	void BroadcastLocalSound(unsigned __int32 iSessionID,byte ucUserWndIndex,CWnd* pWnd,unsigned __int32 iChannelID);			//广播本机的音频
	void BroadcastLocalFirstVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,CWnd* pWnd,unsigned __int32 iChannelID);			//广播本机的第一卡视频

	BOOL GetWndForSessionIndex(FrameInfoType iFrameInfoType,unsigned __int32 & iSessionID,byte ucUserWndIndex,byte ucUserCardNo) const;	//得到增加广播的窗口号
	BOOL GetAddWndIndex(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte &ucUserWndIndex,byte ucUserCardNo) const;	//得到增加广播的窗口号
	BOOL GetFreeWndIndex(byte &ucUserWndIndex);	//得到空的窗口号
	BOOL AddInceptVideo(unsigned __int32 iSessionID,byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID);	//增加视频
	BOOL InceptVideo(unsigned __int32 iSessionID,byte ucUserCardNo,byte ucWndIndex,CString strUserName,		//modifed by tiger,2008.10.08
		unsigned __int32 iChannelID,bool bRepetition=false);	//接收视频
	BOOL CloseVideo(unsigned __int32 iSessionID,byte ucUserCardNo,bool bRepetition=false);	//关闭接收视频	//modifed by tiger,2008.10.08
	void AddBroadcastSoundNoLocal(byte ucUserWndIndex,unsigned __int32 iChannelID);			//增加广播非本机的音频
	void AddBroadcastVideo(byte ucUserWndIndex,unsigned __int32 iChannelID);	//增加广播非本机的视频
	void BroadcastSoundNoLocal(unsigned __int32 iSessionID,byte ucUserWndIndex,CString strUserName,byte iUserCardNo,unsigned __int32 iChannelID);			//广播非本机的音频
	void BroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserCardNo,CString strUserName,
		unsigned __int32 iChannelID, bool bRepetition=false);			//广播非本机的视频	//modifed by tiger,2008.10.08
	void CloseBroadcastSound(unsigned char ucUserWndIndex);	//广播关闭广播音频
	void CloseBroadcastVideo(unsigned char ucUserWndIndex,bool bRepetition=false);	//广播关闭广播视频	//modifed by tiger,2008.10.08
	BOOL AddInceptSound(unsigned __int32 iSessionID,byte ucWndIndex,unsigned __int32 iChannelID);	//增加音频
	BOOL InceptSound(unsigned __int32 iSessionID,byte ucWndIndex,CString strUserName,byte iUserCardNo,unsigned __int32 iChannelID);	//接收音频
	BOOL CloseInceptSound(unsigned __int32 iSessionID,byte iUserCardNo);	//关闭接收音频

	CTWinInfoArray *GetWinInfoArray();				//得到窗口信息数组
	BOOL IsOpenInfoWin(unsigned __int32 iSessionID,byte &ucWinNo,FrameInfoType iFrameInfoType);		//是否打开了xx区
	BOOL IsInceptSound(unsigned __int32 iSessionID,byte iUserCardNo);				//是否接收了音频
	BOOL IsInceptVideo(unsigned __int32 iSessionID,byte ucUserCardNo);				//是否接收了视频
	BOOL IsSendSingleAudio(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte iUserCardNo);		// 是否已经发送音频	Add Han Huajie    2008-4-17
	BOOL IsSendSingleVideo(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte ucUserCardNo);		//是否已经发送视频	Add Han Huajie    2008-4-17
	BOOL IsBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo);				//是否广播了音频
	BOOL IsBroadcastVideo(unsigned __int32 iSessionID,byte ucUserCardNo);				//是否广播了视频
	BOOL IsBroadcastWndSound(unsigned char ucUserWndIndex);				//是否广播了音频
	BOOL IsBroadcastWndVideo(unsigned char ucUserWndIndex);				//是否广播了视频
	BOOL IsBroadcast(unsigned __int32 iSessionID);				//谁是否广播了
	void SetLocalUserInfo(TLocalUserInfo* ptLocalUserInfo);//传入对话框初始信息
	BOOL AddSendVideo(byte ucUserCardNo,unsigned __int32 iChannelID);	//增加发送视频
	BOOL AddSendSound(unsigned __int32 iChannelID);	//增加发送音频
	BOOL SendSound(byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//发送音频
	BOOL SendVideo(byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//发送视频
	CWnd *CloseSendVideo(byte iUserCardNo,byte ucWndIndex);	//关闭发送视频
//	BOOL SendSound(unsigned __int32 iChannelID);	//发送音频
	CWnd *CloseSendSound(byte iUserCardNo,byte ucWndIndex);	//关闭音频

	void SetTemplateDlgIcon(HICON hIcon);
	RECT GetControlRect();					//得到现在屏的控制窗口的坐标
	BOOL IsRepairTemplet();
	RECT GetMidRect();								// 获得大窗口区域
		
	void InitConferenceWinDlg();
	int  GetFreeWinNumber();					//获得空的窗口数
	void SetTemplateInfo(byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType);
	CConferenceWinDlg(CWnd* pParent = NULL);   // standard constructor
    int GetInUseWinCount(); //计算使用中的窗口
	BOOL IsFrameNull(byte ucWndIndex);
	int WhoOnlyIncept(unsigned __int32 &iSessionID,byte &iUserCardNo,byte &ucUserWndIndex);					//谁只单接了 0:没有,1;音频,2:视频,3:有视音频
/*	void FullScreen(unsigned __int32 iSessionID,byte iCardNo,BOOL bFull,FrameInfoType iFrameInfoType=ntVideoSound);
	void FullScreen(BOOL bFull);	*/							//关闭或打开全屏

	void OnSetPrePointName(unsigned __int32 iSessionID,byte iCardNo,char *pData);
	int WhoBroadcastVideoSound(unsigned __int32 &iSessionID,byte &iUserCardNo,byte &ucUserWndIndex);		//谁广播了视频或音频窗口的
	void FindWinSetUserBroadcastFlag();								//找广播人员设置广播图标
	
	void DropNotify(char *pData,int nLen,byte nWndIndex);		//响应拖动

	//设置标题栏字体	add by tiger,2008.09.27
	void SetTitleFont(LOGFONT logFont_Big,COLORREF crText_Big,COLORREF crBk_Big);

	//{{add by tiger,2009.06.24
	void SetScreenRect(CRect rc);
	//end add}}

	void SetMICMute(BOOL bMute);			// 设置静音		FALSE 静音	TRUE 有声音

// Dialog Data
	//{{AFX_DATA(CConferenceWinDlg)
	enum { IDD = IDD_CONFERENCE_WIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConferenceWinDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
CGestureConfig m_gestureConfig;
		double m_dblZoomRatioStart;
    double m_dblZoomRatioTotal;             
    CPoint m_ptCenter;
	// Generated message map functions
	//{{AFX_MSG(CConferenceWinDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnGestureZoom(CPoint ptCenter, long lDelta);
virtual BOOL OnGesturePan(CPoint ptFrom, CPoint ptTo);
virtual BOOL OnGestureRotate(CPoint ptCenter, double dblAngle);
virtual BOOL OnGesturePressAndTap(CPoint ptFirstFinger, long lDelta);
virtual BOOL OnGestureTwoFingerTap(CPoint ptCenter);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	void CreateSendDlg(byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID,TWinInfo *ptWinInfo);	//创建发送窗口
    void CreateNewWin(int iWndIndex);			//建新空窗口
	BOOL InceptWhoSound(unsigned __int32 iSessionID,CString strUserName,byte ucWndIndex,byte iUserCardNo,unsigned __int32 iChannelID);				//接收谁的音频
	BOOL InceptWhoCardVideo(unsigned __int32 iSessionID,byte ucUserCardNo,CString strUserName,byte ucWndIndex,		//modifed by tiger,2008.10.08
		unsigned __int32 iChannelID,bool bRepetition=false);				//接收谁的第几块卡视频
	BOOL AddInceptWhoSound(byte ucWndIndex,unsigned __int32 iChannelID);				//增加接收谁的音频
	BOOL AddInceptWhoCardVideo(byte ucWndIndex,unsigned __int32 iChannelID);				//增加接收谁的第几块卡视频
	CDialog *m_pConferenceDlg;					//主窗口
	CWnd *CloseLocalWin(byte ucUserCardNo,int iWinNo);				//关闭本地窗口
	TLocalUserInfo* m_ptLocalUserInfo;
	CImageList*   m_pDragImage;      //拖动时显示的图象列表
	BOOL          m_bDragging;       //标识是否正在拖动过程中
	BOOL	m_bWatch;						//监控标志

	HICON m_hIcon;
	void InitTempletArithmetic();
	void InitConferenceDlg();				//初始化会议窗口
	CTempletArithmetic *m_pTempletArithmetic;
	void	CreateWin();
	int     m_iFrameIndex;			//屏号
	byte	m_iWinClass;			//屏种类	1，2，3第几个种类
	bool	m_bWinTemplate;			//屏模板模式	0：不显示所有,1：为显示所有
	byte	m_iWinNumber;		 	//屏数量	
	byte	m_iWinType;				//屏类型
	CTWinInfoArray m_aWinInfoArray;
	bool   *m_szbSelect;
	CTPreSettingInfoArray	m_tPreSettingInfoArray;
CDrawingObject m_drawingObject;
	//CBitmap *m_pUserDlgBkBmp;
public:
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	void SetSendSingleAVdioInfo(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte ucUserCardNo, int iAVdioFlg);
	void ClearSendSingleAVdio(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte iUserCardNo, BOOL bAVdioFlg);	// bAVdioFlg: 0 音频, 1 视频
	void SetWondowSelected(byte iIndex, bool bSelect);
	bool GetWindowSelected(byte iIndex);
	void SetAllWindowSelected(bool bSelect);

	BOOL WindowSelectedToJPG();			//拍照

	//////////////////////////////////////////////////////////////////////////
	// 视频预设置方法	Add HHJ 2009/08/06
private:
	//void InitWinPreSettingInfo();	// 初始化窗口视频预设置
	//void RemoveWinPreSettingInfo();	// 释放视窗口频预设置
	//void ReadWinPreSettingInfo(TPreSettingInfo* ptPreSettingInfo, int nScreenNo/*屏幕号*/, int nWinNo/*模板窗口号*/);
	//void WriteWinPreSettingInfo(TPreSettingInfo* ptPreSettingInfo, int nScreenNo/*屏幕号*/, int nWinNo/*模板窗口号*/);
	void DrawSelectedFrame(CDC *pDC);
	bool m_bShowDlg;
		virtual void Do_LButtonDown(UINT nFlags, CPoint point);
	virtual void Do_LButtonUp(UINT nFlags, CPoint point);
public:
	TPreSettingInfo* GetWinPreSettingInfo(int nWndNo);			// 得到与设置信息
	TPreSettingInfo* GetWinPreSettingInfo(CWnd* pSelectWnd);	// 得到与设置信息
	void MenueWinUserVideoFormatSet(CWnd* pSelectWnd);		    // 选择“启用窗口视频格式”调用方法
	void MenueWinVideoFormatSetDlg(CWnd* pSelectWnd, TPreSettingInfo* ptPreSettingInfo);		    //“窗口视频格式设置”调用方法
	void ApplyUsingWinVideoFormatSet(bool bApply);				// 应用 “启用窗口视频格式”
	void ApplyUsingWinVideoFormatInfoSet(byte iCodeType/*视频协议*/, byte iADADSize/*标清分辨率*/, 
			 byte iHDSize/*高清分辨率*/, byte iBitrate/*视频码流*/, byte iFrameRate/*图像帧率*/);// 应用视频设置格式
	// End Add
	//////////////////////////////////////////////////////////////////////////
	void SetUserDlgBkBmp(CBitmap* pBmp);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 关闭音频的传输通道回调接口(用于释放相应的发送或接受数据的对象)   
	// dwChannelNO:  音频的唯一标识，区分是关闭的哪个音频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
	void CloseH323AudioChannelCallBack(DWORD dwChannelNO, LONG lContext);  

	// 关闭视频的传输通道回调接口(用于释放相应的发送或接受数据的对象)     
	// dwChannelNO:  视频的唯一标识，区分是关闭的哪个视频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
	void CloseH323VideoChannelCallBack(DWORD dwChannelNO, LONG lContext); 
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFERENCEWINDLG_H__F7DE1D65_B12B_4DE7_B958_4DAFE9678FD0__INCLUDED_)
