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


// CCUserWinDlgDlg �Ի���
class CCUserWinDlgDlg : public CBaseDlg
{
	// ����
public:
	CCUserWinDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
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
	//CWnd *m_pConferenceWinDlg;    //���ڵ�ģ�崰��
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:

	//int m_iSessionID;						//���ں�
	//int m_iIndex;						//���ں�
	//CDialog *m_pdMainDlg;
	void SetIndex(int iIndex)			//���ô��ں�
	{
		m_iIndex=iIndex+1;
	}
	void SetSessionID(int iSessionID)			//���ô��ں�
	{
		m_iSessionID=iSessionID;
	}
	void SetMainDlg(CDialog *pdMainDlg)		//��������
	{
		m_pdMainDlg=pdMainDlg;
	}
CDrawingObject m_drawingObject;

	CString m_strText;
	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
		virtual BOOL StartConferenceRecord(){return FALSE;}		// ��ʼ����¼��
	virtual void StopConferenceRecord(){}		// ֹͣ����¼��
	virtual BOOL StartRecord(){return FALSE;}				// ��ʼ¼��
	virtual void StopRecord(){}				// ֹͣ¼��
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
//	void CloseVidioSoundWizardDlg(BOOL bIsOK);			//�ر�����Ƶ����
//    UINT GetVideoBitrate();
//    UINT GetAudioBitrate();
//    
//	//����¼��
//	//////////////////////////////////////////////////////////////////////////
//	BOOL StartConferenceRecord();		// ��ʼ����¼��
//	void StopConferenceRecord();		// ֹͣ����¼��
//	//////////////////////////////////////////////////////////////////////////
//
//    void SetWatch();			//����
//	void CloseWatch();			//�رռ��
//	BOOL CreateVideoChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//������Ƶͨ��
//	BOOL CloseVideoChannel();	//�ر���Ƶͨ��
//	BOOL CreateSoundChannel(unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//������Ƶͨ��
//	BOOL CloseSoundChannel();	//�ر���Ƶͨ��
//	//BOOL IsHaveSound();					//�Ƿ�����Ƶ
//	//BOOL IsHaveVideo();					//�Ƿ�����Ƶ
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
//	afx_msg LRESULT OnRecordMessage(WPARAM wParam, LPARAM lParam);			//¼����Ϣ
//	afx_msg void OnRemoteSetting();
//	afx_msg void OnAudioSetting();
//	afx_msg void OnVideoSetting();
//	void ShowRemoteCtrlSetting(ComParameter ComPar);
////    afx_msg LRESULT OnResizeWindow(WPARAM wParam, LPARAM lParam);
//
//	//�ص�����IAVUserPlayerNotify
//	////////////////////////////////////////////////////
//public:
//	//////////////////////////////////////////////////////////////////////////
//	// IOVideoDisNotify �ص��ӿ�
//	//�����Ƶ���ݰ��Ļص�
//	virtual void OnIOAudioDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples);	//pass
//	//�����Ƶ���ݰ��Ļص�
//	virtual void OnIOVideoDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType);	//pass
//	virtual void OnIOVideoDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen){};		//current not used
//	//�����Ƶ�������ݰ��Ļص�
//	virtual void OnIOVideoSubDecNotifyFrame(unsigned char*pFrameData, int nWidth, int nHeight, VIDEO_FRAME_TYPE nFrameType){};			//current not used
//	virtual void OnIOVideoSubDecNotifyFramePacket(unsigned char*pPacketData,int nPacketLen){};	//current not used
//	//////////////////////////////////////////////////////////////////////////
//
//	//tiger Audio
//	//////////////////////////////////////////////////////////////////////////
//	//�����������Ƶ���ݰ��Ļص�
//	virtual void OnIOAudioPlayDecNotifyFrame(unsigned char*pFrameData, int nFrameLen, double dSamples);
//	//////////////////////////////////////////////////////////////////////////
//
//
//	void OnIHPAVPlayerNotifyAudioLevel(int nAudioLevel);	//
//	void ResizeControls(void);
//
//	void OnIAVVideoReceiverNotifyReceivedVideoFrame(const char*pData,int nLen);	//��Ƶ����, ����¼��
//	void OnIAVVideoReceiverNotifyConnected(/*unsigned long ulIP*/);
//
//	void OnIAVAudioReceiverNotifyReceivedAudioFrame(const char*pData,int nLen);	//��Ƶ����, ����¼��
//	void OnIAVAudioReceiverNotifyConnected(/*unsigned long ulIP*/);
//
//	//�ص�����IAVCRecordEvent
//	//////////////////////////////////////////////////////////////////////////
//	virtual void OnAVCRecordFactoryEvent_FullFile();
//	//virtual int SendFrame(const char*pData,int nLen);
//	virtual int SendFrame(DWORD dwMessage, DWORD dwParam1, DWORD dwParam2);
//	BOOL DoStartRecord(CString strRecordPathName);		// ִ�п�ʼ¼��
//	BOOL StartRecord(); // ��ʼ¼��
//	void StopRecord();// ֹͣ¼��
//
//	//���ñ���������,�ֵ���ɫ�ͱ���ɫ,	add by tiger,2008.09.27
//	void SetTitleFont(LOGFONT logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255));
//
//	void ShowTitleBar(BOOL bShow);	//Ϊ���ƣ��ڡ��������˵������ӡ���ʾ������������Ĭ��ѡ��
//									//modifed by lzl,2008.10.20
//
//	void WindowSelectedToJPG();			//����
//
//private:
//	void FormateTitlebar();	//add by tiger,2008.09.27
//    void SetTitleBarColor() ;
//    void ResetWindowRgn();
//    bool CheckAllControl();     //����û�Ȩ��
//    void NewAVUserPlayer();
//	void DestroyAVUserPlayer();	//�ͷ�AVUserPlayer
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
//	CDlgAVInfo *m_pDlgAVInfo;	//����
//	IDlgYT	*m_pDlgYT;			//��̨���ƴ���
////	CDlgFloatWin *m_pDlgFloatWin;	//��������
//    CPrePointSetDlg *m_pDlgPrepointSet;
//
//    //��������
//    int m_nCurVolume;   //��ǰ��������С
//    unsigned long m_ulVolumeTime;   //�����ѳ�����ʱ��
//    UINT_PTR m_nVolumeTimer;
//    bool m_bInVoiceInspirite;   //������
//	CDlgCtrlRemoteSetting *m_pDlgCtrlRemoteSetting;
//
//	//ǰһ��
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
//	//����¼��
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
//	//����TIMER
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
//	BOOL m_bFullScreenCpture;	// �Ƿ�ȫ���ɼ���Ļ
//	//CBitmap *m_pBkBitmap;
//
//	CDetailInfoDlg*		m_pDetailInfoDlg;
//	VIDEO_DIS_SIZE		video_size;
//
//	ISendAVdieoDataInfo* m_pISendAVdieoDataInfo;	// H323 ���ݷ��ͽӿ�
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
//	afx_msg LRESULT OnAudioSetMessage(WPARAM wParam, LPARAM lParam);	// ��Ƶ���öԻ���ȷ����Ϣ
//	afx_msg LRESULT OnVideoSetMessage(WPARAM wParam, LPARAM lParam);	// ��Ƶ���öԻ���ȷ����Ϣ
//	virtual void SetSynchronization(bool bEnableSyn);
//	virtual void Do_LButtonDown(UINT nFlags, CPoint point);
//	virtual void SetLocalLoopBackTest(BOOL bLocalLoopBackTest);		// ���ñ��ػ��ز���	Add HH
//
//	//////////////////////////////////////////////////////////////////////////
//	// ��ƵԤ���÷���	Add HHJ 2009/08/06
//	afx_msg void OnWinUserVideoFormatSet();
//	afx_msg void OnWinVideoFormatSet();
//	afx_msg LRESULT OnWinVideoFormatSetMessage(WPARAM wParam, LPARAM lParam);	// ��Ƶ���öԻ���ȷ����Ϣ
//	virtual void SetUsingWinVideoFormatInfo(TPreSettingInfo* ptPreSettingInfo);// Ӧ����Ƶ���ø�ʽ
//	// End Add
//	//////////////////////////////////////////////////////////////////////////
//	void SetBkBmp(CBitmap* pBmp);
//
//	//////////////////////////////////////////////////////////////////////////
//	// ��Ƶ��ϸ��Ϣ add HHJ 2009/08/24
//	afx_msg void OnDetailInfoShow();
//	// �õ���Ƶ����ϸ��Ϣ
//	virtual void GetAVdieoDetailInfo(unsigned long& ulWidth,			// ��Ƶ���
//		unsigned long& ulHeight,			// ��Ƶ�߶�
//		unsigned long& ulAudioBitrate,		// ��Ƶ����
//		unsigned long& ulAudioLost,			// ��Ƶ����
//		unsigned long& ulVideoBitrate,		// ��Ƶ����
//		unsigned long& ulVideoLost,			// ��Ƶ����
//		int& nVolume,						// ������С
//		int& nVideoFrame);					// ��Ƶ֡��	
//	afx_msg LRESULT OnWinDetailInfoMessage(WPARAM wParam, LPARAM lParam);	// ��Ƶ���öԻ���ȷ����Ϣ
//	// End Add
//	//////////////////////////////////////////////////////////////////////////
//
//
//	// ������Ƶ�Ĵ���ͨ���ص��ӿ�    
//	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������Ƿ��͵��ĸ���Ƶ��
//	// lContext:   Ӧ�ó��������ģ����û�����ͨ��ʱ���룬�˴�ԭ�ⷵ��
//	virtual void CreateAudioChannelCallBack(DWORD dwChannelNO, LONG lContext);
//
//	// ������Ƶ�Ĵ���ͨ���ص��ӿ�    
//	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������Ƿ��͵��ĸ���Ƶ��
//	// lContext:   Ӧ�ó��������ģ����û�����ͨ��ʱ���룬�˴�ԭ�ⷵ��
//	virtual void CreateVideoChannelCallBack(DWORD dwChannelNO, LONG lContext); 
//
//	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)   
//	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
//	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
//	virtual void CloseH323AudioChannelCallBack(DWORD dwChannelNO, LONG lContext);  
//
//	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)     
//	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
//	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
//	virtual void CloseH323VideoChannelCallBack(DWORD dwChannelNO, LONG lContext); 
//};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__A193E93B_05EE_4345_9299_3E249C6BDB82__INCLUDED_)
