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

	//void SetSynchronization(bool bEnableSyn);			// ����ͬ��
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
	//void ShowCodeFlow(BOOL bShowCodeFlow);			//��ʾ����
void ShowTitleBar(BOOL bShowTitleBar);//Ϊ���ƣ��ڡ��������˵������ӡ���ʾ������������Ĭ��ѡ��
	//									//add by lzl,2008.10.20
	//
	//void VideoShowMode(VideoShowModeType nVideoShowMode);	// ��Ƶ��ʾģʽ	Add Han Huajie 2008/01/15
	//void OnConvertKeyDownMessage(MSG *pMsg);
	//void PermitControl(unsigned __int32 iSessionID, BOOL bPermit);
	//void StopRecord();	// ֹͣ¼��
	//void SetSpeek(BOOL bIsSpeek);
	//BOOL IsHaveInfo(byte ucUserWndIndex);
    UINT GetFreeWnd(byte **pWndArray = NULL) const;   //����մ�����
	void CloseAllWindow();	//�ر����д��� ¼��ʱʹ��
	void CloseAllWinInfo();	//�ر����д�����Ϣ ����ͬ��ʱʹ��
	BOOL StartConferenceRecord();		// ��ʼ����¼��
	void StopConferenceRecord();		// ֹͣ����¼��
	void SetWatch();			//����
	void CloseWatch();			//�رռ��
	void GetBigWindows(int iBigWindows[3]);						//�õ��󴰿�
	BOOL GetMaxWndIndex(byte &ucUserWndIndex);	//�õ���ǰ���󴰺�
	void SetUseWhiteBoard(byte ucWndIndex,bool bAllowUseWhiteBoard);			//��������ʹ�ðװ�
	byte GetFrameIndex();										//�õ�����
	void CloseUserInfo(unsigned __int32 iSessionID);			//�رմ��˵Ĵ���
	void CloseLocalInfo();			//�ر����б��صĴ���
	void ReceiveControlCommand(byte ucWndIndex,unsigned __int32 iCommand);		//��̨����
	void ReceiveControlSpeed(byte ucWndIndex,byte ucSpeed);						//��̨�ٶ�
	void ShowConferenceUserDlg();
	void SwapWhoToWndPosition(byte ucDragUserWndIndex,byte ucDragUserFrameIndex,byte ucUserWndIndex);			//�㲥�϶�˭
	void InitCapture(byte ucWndIndex,byte ucUserCardNo);					//��ʼ���ɼ�
	CWnd*CloseInfoWin(byte ucWndIndex);							//�ر�xx��
	void CloseWin(byte ucWndIndex);			//�رմ���
	//void OpenInfoWin(unsigned __int32 iSessionID,byte ucWndIndex,CWnd* pWnd,FrameInfoType iFrameInfoType);	//��xx��
	void SetConferenceDlg(CDialog *pConferenceDlg);		//����������ָ��
	void SendLocalSound(byte ucWndIndex,unsigned __int32 iChannelID);			//���ͱ�����Ƶ
	void SendLocalFirstVideo(byte ucWndIndex,unsigned __int32 iChannelID);			//���ͱ��ص�һ�鿨��Ƶ
	void ShowWin(int iWndIndex,CWnd* pWnd);				//��ʾ��Ƶ����
	void SetFrameIndex(int iFrameIndex);			//��������
	void CloseBroadcastLocalNoFirstSound(byte ucUserWndIndex);						//�رչ㲥�����ķǵ�һ����Ƶ
	void CloseBroadcastLocalNoFirstVideo(byte ucUserWndIndex);						//�رչ㲥�����ķǵ�һ����Ƶ
	CWnd* CloseBroadcastLocalSound(byte ucUserWndIndex);						//�رչ㲥��������Ƶ
	CWnd* CloseBroadcastLocalFirstVideo(byte ucUserWndIndex);						//�رչ㲥�����ĵ�һ����Ƶ
	void AddBroadcastLocalSound(byte ucUserWndIndex,unsigned __int32 iChannelID);			//���ӹ㲥��������Ƶ
	void BroadcastLocalNoFirstVideo(byte ucUserWndIndex,unsigned __int32 iChannelID);			//�㲥�����ķǵ�һ����Ƶ
	void BroadcastLocalSound(unsigned __int32 iSessionID,byte ucUserWndIndex,CWnd* pWnd,unsigned __int32 iChannelID);			//�㲥��������Ƶ
	void BroadcastLocalFirstVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,CWnd* pWnd,unsigned __int32 iChannelID);			//�㲥�����ĵ�һ����Ƶ

	BOOL GetWndForSessionIndex(FrameInfoType iFrameInfoType,unsigned __int32 & iSessionID,byte ucUserWndIndex,byte ucUserCardNo) const;	//�õ����ӹ㲥�Ĵ��ں�
	BOOL GetAddWndIndex(FrameInfoType iFrameInfoType,unsigned __int32 iSessionID,byte &ucUserWndIndex,byte ucUserCardNo) const;	//�õ����ӹ㲥�Ĵ��ں�
	BOOL GetFreeWndIndex(byte &ucUserWndIndex);	//�õ��յĴ��ں�
	BOOL AddInceptVideo(unsigned __int32 iSessionID,byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID);	//������Ƶ
	BOOL InceptVideo(unsigned __int32 iSessionID,byte ucUserCardNo,byte ucWndIndex,CString strUserName,		//modifed by tiger,2008.10.08
		unsigned __int32 iChannelID,bool bRepetition=false);	//������Ƶ
	BOOL CloseVideo(unsigned __int32 iSessionID,byte ucUserCardNo,bool bRepetition=false);	//�رս�����Ƶ	//modifed by tiger,2008.10.08
	void AddBroadcastSoundNoLocal(byte ucUserWndIndex,unsigned __int32 iChannelID);			//���ӹ㲥�Ǳ�������Ƶ
	void AddBroadcastVideo(byte ucUserWndIndex,unsigned __int32 iChannelID);	//���ӹ㲥�Ǳ�������Ƶ
	void BroadcastSoundNoLocal(unsigned __int32 iSessionID,byte ucUserWndIndex,CString strUserName,byte iUserCardNo,unsigned __int32 iChannelID);			//�㲥�Ǳ�������Ƶ
	void BroadcastVideo(unsigned __int32 iSessionID,byte ucUserWndIndex,byte ucUserCardNo,CString strUserName,
		unsigned __int32 iChannelID, bool bRepetition=false);			//�㲥�Ǳ�������Ƶ	//modifed by tiger,2008.10.08
	void CloseBroadcastSound(unsigned char ucUserWndIndex);	//�㲥�رչ㲥��Ƶ
	void CloseBroadcastVideo(unsigned char ucUserWndIndex,bool bRepetition=false);	//�㲥�رչ㲥��Ƶ	//modifed by tiger,2008.10.08
	BOOL AddInceptSound(unsigned __int32 iSessionID,byte ucWndIndex,unsigned __int32 iChannelID);	//������Ƶ
	BOOL InceptSound(unsigned __int32 iSessionID,byte ucWndIndex,CString strUserName,byte iUserCardNo,unsigned __int32 iChannelID);	//������Ƶ
	BOOL CloseInceptSound(unsigned __int32 iSessionID,byte iUserCardNo);	//�رս�����Ƶ

	CTWinInfoArray *GetWinInfoArray();				//�õ�������Ϣ����
	BOOL IsOpenInfoWin(unsigned __int32 iSessionID,byte &ucWinNo,FrameInfoType iFrameInfoType);		//�Ƿ����xx��
	BOOL IsInceptSound(unsigned __int32 iSessionID,byte iUserCardNo);				//�Ƿ��������Ƶ
	BOOL IsInceptVideo(unsigned __int32 iSessionID,byte ucUserCardNo);				//�Ƿ��������Ƶ
	BOOL IsSendSingleAudio(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte iUserCardNo);		// �Ƿ��Ѿ�������Ƶ	Add Han Huajie    2008-4-17
	BOOL IsSendSingleVideo(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte ucUserCardNo);		//�Ƿ��Ѿ�������Ƶ	Add Han Huajie    2008-4-17
	BOOL IsBroadcastSound(unsigned __int32 iSessionID,byte iUserCardNo);				//�Ƿ�㲥����Ƶ
	BOOL IsBroadcastVideo(unsigned __int32 iSessionID,byte ucUserCardNo);				//�Ƿ�㲥����Ƶ
	BOOL IsBroadcastWndSound(unsigned char ucUserWndIndex);				//�Ƿ�㲥����Ƶ
	BOOL IsBroadcastWndVideo(unsigned char ucUserWndIndex);				//�Ƿ�㲥����Ƶ
	BOOL IsBroadcast(unsigned __int32 iSessionID);				//˭�Ƿ�㲥��
	void SetLocalUserInfo(TLocalUserInfo* ptLocalUserInfo);//����Ի����ʼ��Ϣ
	BOOL AddSendVideo(byte ucUserCardNo,unsigned __int32 iChannelID);	//���ӷ�����Ƶ
	BOOL AddSendSound(unsigned __int32 iChannelID);	//���ӷ�����Ƶ
	BOOL SendSound(byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//������Ƶ
	BOOL SendVideo(byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID, unsigned __int32 iInceptSessionID = 0);	//������Ƶ
	CWnd *CloseSendVideo(byte iUserCardNo,byte ucWndIndex);	//�رշ�����Ƶ
//	BOOL SendSound(unsigned __int32 iChannelID);	//������Ƶ
	CWnd *CloseSendSound(byte iUserCardNo,byte ucWndIndex);	//�ر���Ƶ

	void SetTemplateDlgIcon(HICON hIcon);
	RECT GetControlRect();					//�õ��������Ŀ��ƴ��ڵ�����
	BOOL IsRepairTemplet();
	RECT GetMidRect();								// ��ô󴰿�����
		
	void InitConferenceWinDlg();
	int  GetFreeWinNumber();					//��ÿյĴ�����
	void SetTemplateInfo(byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType);
	CConferenceWinDlg(CWnd* pParent = NULL);   // standard constructor
    int GetInUseWinCount(); //����ʹ���еĴ���
	BOOL IsFrameNull(byte ucWndIndex);
	int WhoOnlyIncept(unsigned __int32 &iSessionID,byte &iUserCardNo,byte &ucUserWndIndex);					//˭ֻ������ 0:û��,1;��Ƶ,2:��Ƶ,3:������Ƶ
/*	void FullScreen(unsigned __int32 iSessionID,byte iCardNo,BOOL bFull,FrameInfoType iFrameInfoType=ntVideoSound);
	void FullScreen(BOOL bFull);	*/							//�رջ��ȫ��

	void OnSetPrePointName(unsigned __int32 iSessionID,byte iCardNo,char *pData);
	int WhoBroadcastVideoSound(unsigned __int32 &iSessionID,byte &iUserCardNo,byte &ucUserWndIndex);		//˭�㲥����Ƶ����Ƶ���ڵ�
	void FindWinSetUserBroadcastFlag();								//�ҹ㲥��Ա���ù㲥ͼ��
	
	void DropNotify(char *pData,int nLen,byte nWndIndex);		//��Ӧ�϶�

	//���ñ���������	add by tiger,2008.09.27
	void SetTitleFont(LOGFONT logFont_Big,COLORREF crText_Big,COLORREF crBk_Big);

	//{{add by tiger,2009.06.24
	void SetScreenRect(CRect rc);
	//end add}}

	void SetMICMute(BOOL bMute);			// ���þ���		FALSE ����	TRUE ������

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
	void CreateSendDlg(byte ucUserCardNo,byte ucWndIndex,unsigned __int32 iChannelID,TWinInfo *ptWinInfo);	//�������ʹ���
    void CreateNewWin(int iWndIndex);			//���¿մ���
	BOOL InceptWhoSound(unsigned __int32 iSessionID,CString strUserName,byte ucWndIndex,byte iUserCardNo,unsigned __int32 iChannelID);				//����˭����Ƶ
	BOOL InceptWhoCardVideo(unsigned __int32 iSessionID,byte ucUserCardNo,CString strUserName,byte ucWndIndex,		//modifed by tiger,2008.10.08
		unsigned __int32 iChannelID,bool bRepetition=false);				//����˭�ĵڼ��鿨��Ƶ
	BOOL AddInceptWhoSound(byte ucWndIndex,unsigned __int32 iChannelID);				//���ӽ���˭����Ƶ
	BOOL AddInceptWhoCardVideo(byte ucWndIndex,unsigned __int32 iChannelID);				//���ӽ���˭�ĵڼ��鿨��Ƶ
	CDialog *m_pConferenceDlg;					//������
	CWnd *CloseLocalWin(byte ucUserCardNo,int iWinNo);				//�رձ��ش���
	TLocalUserInfo* m_ptLocalUserInfo;
	CImageList*   m_pDragImage;      //�϶�ʱ��ʾ��ͼ���б�
	BOOL          m_bDragging;       //��ʶ�Ƿ������϶�������
	BOOL	m_bWatch;						//��ر�־

	HICON m_hIcon;
	void InitTempletArithmetic();
	void InitConferenceDlg();				//��ʼ�����鴰��
	CTempletArithmetic *m_pTempletArithmetic;
	void	CreateWin();
	int     m_iFrameIndex;			//����
	byte	m_iWinClass;			//������	1��2��3�ڼ�������
	bool	m_bWinTemplate;			//��ģ��ģʽ	0������ʾ����,1��Ϊ��ʾ����
	byte	m_iWinNumber;		 	//������	
	byte	m_iWinType;				//������
	CTWinInfoArray m_aWinInfoArray;
	bool   *m_szbSelect;
	CTPreSettingInfoArray	m_tPreSettingInfoArray;
CDrawingObject m_drawingObject;
	//CBitmap *m_pUserDlgBkBmp;
public:
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	void SetSendSingleAVdioInfo(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte ucUserCardNo, int iAVdioFlg);
	void ClearSendSingleAVdio(unsigned __int32 iPresideSessionID, unsigned __int32 iInceptSessionID, byte iUserCardNo, BOOL bAVdioFlg);	// bAVdioFlg: 0 ��Ƶ, 1 ��Ƶ
	void SetWondowSelected(byte iIndex, bool bSelect);
	bool GetWindowSelected(byte iIndex);
	void SetAllWindowSelected(bool bSelect);

	BOOL WindowSelectedToJPG();			//����

	//////////////////////////////////////////////////////////////////////////
	// ��ƵԤ���÷���	Add HHJ 2009/08/06
private:
	//void InitWinPreSettingInfo();	// ��ʼ��������ƵԤ����
	//void RemoveWinPreSettingInfo();	// �ͷ��Ӵ���ƵԤ����
	//void ReadWinPreSettingInfo(TPreSettingInfo* ptPreSettingInfo, int nScreenNo/*��Ļ��*/, int nWinNo/*ģ�崰�ں�*/);
	//void WriteWinPreSettingInfo(TPreSettingInfo* ptPreSettingInfo, int nScreenNo/*��Ļ��*/, int nWinNo/*ģ�崰�ں�*/);
	void DrawSelectedFrame(CDC *pDC);
	bool m_bShowDlg;
		virtual void Do_LButtonDown(UINT nFlags, CPoint point);
	virtual void Do_LButtonUp(UINT nFlags, CPoint point);
public:
	TPreSettingInfo* GetWinPreSettingInfo(int nWndNo);			// �õ���������Ϣ
	TPreSettingInfo* GetWinPreSettingInfo(CWnd* pSelectWnd);	// �õ���������Ϣ
	void MenueWinUserVideoFormatSet(CWnd* pSelectWnd);		    // ѡ�����ô�����Ƶ��ʽ�����÷���
	void MenueWinVideoFormatSetDlg(CWnd* pSelectWnd, TPreSettingInfo* ptPreSettingInfo);		    //��������Ƶ��ʽ���á����÷���
	void ApplyUsingWinVideoFormatSet(bool bApply);				// Ӧ�� �����ô�����Ƶ��ʽ��
	void ApplyUsingWinVideoFormatInfoSet(byte iCodeType/*��ƵЭ��*/, byte iADADSize/*����ֱ���*/, 
			 byte iHDSize/*����ֱ���*/, byte iBitrate/*��Ƶ����*/, byte iFrameRate/*ͼ��֡��*/);// Ӧ����Ƶ���ø�ʽ
	// End Add
	//////////////////////////////////////////////////////////////////////////
	void SetUserDlgBkBmp(CBitmap* pBmp);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)   
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
	void CloseH323AudioChannelCallBack(DWORD dwChannelNO, LONG lContext);  

	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)     
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
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
