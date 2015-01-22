#pragma once

#include "Resource/UIBase/FlatButton.h"
#include "afxwin.h"
//#include "../../Resource/UIBase/XPButton.h"
#include "Resource/DataDefine/ResourceDefine.h"
#include "TEMPLETARITHMETIC/TempletArithmetic.h"	// Added by ClassView
//#include "TempletArithmetic/TempletArithmeticFactory.h"
#include "afxcmn.h"
//#include	"../ImageArea.h"
#include	<vector>
#include "ConferenceWinDlg.h"
#include "resource.h"
//#include "courtDlg.h"
// CDlgPMosaicScreenADScreen 对话框
class CcourtDlg;

class CDlgPMosaicScreenADScreen : public CDialog
{
public:
	CDlgPMosaicScreenADScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPMosaicScreenADScreen();

	// 对话框数据
	enum { IDD = IDD_DLG_MosaicScreenPAD };
	void SetWondowSelected(byte iIndex, bool bSelect);
	void CreateConferenceWinDlg();
	void InitConferenceWin(int iWinIndex);

	CConferenceWinDlg *m_pdConferenceWinDlg[CONFERENCE_WIN_NUMBER];			//屏窗口
protected:
		ULONG_PTR	m_gdiplusToken;
int						m_nSelectedItem;
	std::vector<CString>	m_VectorImageNames;		// vector holding the image names
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//afx_msg HBRUSH				OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL				OnInitDialog();

	//afx_msg void 				OnBnClickedButtonTemplet7();
	//afx_msg void 				OnBnClickedButtonTemplet8();
	//afx_msg void				OnBnClickedButtonTemplet9();
	//afx_msg void				OnBnClickedButtonTemplet10();
	//afx_msg void				OnBnClickedButtonTemplet11();
	//afx_msg void				OnBnClickedButtonTemplet12();
	//afx_msg void				OnBnClickedButtonTemplet13();
	//afx_msg HBRUSH				OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

private:
	CcourtDlg             *m_pConfDlg;
	CFlatButton 				m_btnTemplet_0;
	CFlatButton 				m_btnTemplet_1;
	CFlatButton 				m_btnTemplet_2;
	CFlatButton 				m_btnTemplet_3;
	CFlatButton 				m_btnTemplet_4;
	CFlatButton 				m_btnTemplet_5;
	CFlatButton 				m_btnTemplet_6;
	//CFlatButton 				m_btnTemplet_7;
	//CFlatButton 				m_btnTemplet_8;
	//CFlatButton 				m_btnTemplet_9;
	//CFlatButton 				m_btnTemplet_10;
	//CFlatButton 				m_btnTemplet_11;
	//CFlatButton 				m_btnTemplet_12;
	//CFlatButton 				m_btnTemplet_13;
	int m_nVideoPostion ;
	int m_nPutVideoPostion  ;
	void 						SetCheckTemplet(int templet);	

	CBrush						m_brushBK;
	unsigned char				m_ucType;

	CBitmap		m_bmpBk;

public:
	void SetAllWindowSelected(bool bSelect);

	bool GetWindowSelected(byte iIndex);
	void  DrawSelectedImage();	
	void  DrawThumbnails();		
	//CImageArea	m_ImageRect;
	CString	m_strImageDir;
	CImageList*				m_pImageListThumb2;		// image list holding the thumbnails
	CImageList*				m_pImageListThumb;		// image list holding the thumbnails
	CImageList*				m_pImageTempThumb;		// image list holding the thumbnails
	//void DropItemOnList(CListCtrl* pDragList, CListCtrl* pDropList);
	CListCtrl* m_pDragList;		//Which ListCtrl we are dragging FROM
	CListCtrl* m_pDropList;		//Which ListCtrl we are dropping ON
	BOOL		m_bDragging;	//T during a drag operation
	BOOL		m_bFirstDragging;	//T during a drag operation
	int			m_nDragIndex;	//Index of selected item in the List we are dragging FROM
	int			m_nDropIndex;	//Index at which to drop i tem in the List we are dropping ON
	CWnd*		m_pDropWnd;		//Pointer to window we are dropping on (will be cast to CListCtrl* type)
	BOOL		m_bDragToOther;	//T during a drag operation

	BOOL		m_bDragMove;	//T during a drag operation
	DWORD m_dwPos ;

	CListCtrl	m_ListThumbnail;
	CTempletArithmetic *m_pTempletArithmetic;
	CTWinInfoArray m_aWinInfoArray;
	bool   *m_szbSelect;
	 //void Capture(bool bCapture=true);
	void						SetNomalTempletType(int nType);
	unsigned char				GetNomalTempletType();			//得到模板类型
	afx_msg void OnBnClickedButton1();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton2();
	CListCtrl m_listCtrl;
	afx_msg void OnLvnBegindragListThumb(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindragListLeft(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBtnLoad();
	BOOL  GetImageFileNames();	// gather the image file names
	BOOL  FindConferenceID(int nID );	// gather the image file names

	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnNMDblclkListThumb(NMHDR *pNMHDR, LRESULT *pResult);
	void DropNotify(char *pData,int nLen,byte ucScreenIndex,byte nWndIndex);		//响应拖动

};
