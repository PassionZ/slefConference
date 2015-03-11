// DlgPMosaicScreenADScreen.cpp : 实现文件
//

#include "stdafx.h"

#include "DlgPMosaicScreenADScreen.h"
#include "Resource/UtilBase/util.h"
//#include ".\dlgtempletarrange.h"
#include <atlimage.h>
#include "TempletArithmetic/TempletArithmeticFactory.h"

#include "courtDlg.h"
//#include "../LoginDlg.h"
//#include "../ConferenceDlg.h"
//#include ".\dlgpadscreen.h"
//#include "..\UserDlg.h"	// Added by ClassView
#include <afxwin.h>
#include <gdiplus.h>
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	75
// CDlgPMosaicScreenADScreen 对话框

CDlgPMosaicScreenADScreen::CDlgPMosaicScreenADScreen(CWnd* pParent /*=NULL*/)
: CDialog(CDlgPMosaicScreenADScreen::IDD, pParent)
{
	m_pConfDlg = (CcourtDlg*)pParent;
	m_brushBK.CreateSolidBrush(RGB(87, 123, 202));
	m_szbSelect = NULL;
	m_pImageListThumb = NULL;
	m_pImageListThumb2 = NULL;
	m_pImageTempThumb = NULL;

	m_bDragging = false;
	m_nDragIndex = -1;
	m_nDropIndex = -1;
	m_bFirstDragging = TRUE;
	m_bDragToOther = TRUE;

	int i=0;for ( i=0; i<1; i++)
	{
		m_pdConferenceWinDlg[i]=NULL;
	
	}
			// initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

void CDlgPMosaicScreenADScreen::CreateConferenceWinDlg()
{

	int i=0;for ( i=0;i<1;i++)
	{
		if (!m_pdConferenceWinDlg[i])
		{
			m_pdConferenceWinDlg[i]=new CConferenceWinDlg;
			m_pdConferenceWinDlg[i]->Create(CConferenceWinDlg::IDD, i ? GetDesktopWindow() : this);

			m_pdConferenceWinDlg[i]->SetFrameIndex(i);
			//m_pdConferenceWinDlg[i]->SetLocalUserInfo(m_ptLocalUserInfo);
			m_pdConferenceWinDlg[i]->SetConferenceDlg(this);
			
			//m_ptLocalUserInfo->_pConferenceInfo->_aWinInfo[i]=m_pdConferenceWinDlg[i]->GetWinInfoArray();
		}

		//if (!m_pDlgFullScreen[i])
		//{
		//	m_pDlgFullScreen[i] = new CDlgFullScreen(i);
		//	m_pDlgFullScreen[i]->Create(CDlgFullScreen::IDD, /*this*/GetDesktopWindow());
		//}
	}

	////
	//if (!m_pDlgFloatWin)
	//{
	//	m_pDlgFloatWin = new CDlgFloatWin(this);
	//	m_pDlgFloatWin->Create(CDlgFloatWin::IDD,GetDesktopWindow());
	//	m_pDlgFloatWin->SetWindowPos(0, 0, 0, 0);
	//}

}

CDlgPMosaicScreenADScreen::~CDlgPMosaicScreenADScreen()
{
	GdiplusShutdown(m_gdiplusToken);

}

void CDlgPMosaicScreenADScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_THUMB, m_ListThumbnail);



}

void CDlgPMosaicScreenADScreen::SetCheckTemplet(int templet)
{
	TRACE(_T("CDlgPMosaicScreenADScreen::SetCheckTemplet() %d\n"), templet);

	m_btnTemplet_0.SetCheck(FALSE);
	m_btnTemplet_1.SetCheck(FALSE);
	m_btnTemplet_2.SetCheck(FALSE);
	m_btnTemplet_3.SetCheck(FALSE);
	m_btnTemplet_4.SetCheck(FALSE);
	m_btnTemplet_5.SetCheck(FALSE);
	m_btnTemplet_6.SetCheck(FALSE);
	//m_btnTemplet_7.SetCheck(FALSE);
	//m_btnTemplet_8.SetCheck(FALSE);
	//m_btnTemplet_9.SetCheck(FALSE);
	//m_btnTemplet_10.SetCheck(FALSE);
	//m_btnTemplet_11.SetCheck(FALSE);
	//m_btnTemplet_12.SetCheck(FALSE);
	//m_btnTemplet_13.SetCheck(FALSE);
	switch(templet)
	{
	case 0:	m_btnTemplet_0.SetCheck(TRUE); break;
	case 1:	m_btnTemplet_1.SetCheck(TRUE); break;
	case 2:	m_btnTemplet_2.SetCheck(TRUE); break;
	case 3:	m_btnTemplet_3.SetCheck(TRUE); break;
	case 4:	m_btnTemplet_4.SetCheck(TRUE); break;
	case 5:	m_btnTemplet_5.SetCheck(TRUE); break;
	case 6:	m_btnTemplet_6.SetCheck(TRUE); break;
		//case 35:	m_btnTemplet_7.SetCheck(TRUE); break;
		//case 36:	m_btnTemplet_8.SetCheck(TRUE); break;
		//case 37:	m_btnTemplet_9.SetCheck(TRUE); break;
		//case 38:	m_btnTemplet_10.SetCheck(TRUE); break;
		//case 39:	m_btnTemplet_11.SetCheck(TRUE); break;
		//case 40:	m_btnTemplet_12.SetCheck(TRUE); break;
		//case 41:	m_btnTemplet_13.SetCheck(TRUE); break;
	}

	m_ucType = templet;
}


BEGIN_MESSAGE_MAP(CDlgPMosaicScreenADScreen, CDialog)
	ON_WM_ERASEBKGND()
		ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)

	ON_NOTIFY(NM_CLICK, IDC_LIST_THUMB, OnClickListThumb)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_THUMB, OnKeydownListThumb)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_THUMB, OnBegindragListLeft)

	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON29, OnBnClickedButton29)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_THUMB, OnNMDblclkListThumb)
END_MESSAGE_MAP()


// CDlgPMosaicScreenADScreen 消息处理程序
BOOL  CDlgPMosaicScreenADScreen::GetImageFileNames()
{			
	CString	strExt;
	CString	strName;
	CString	strPattern;
	BOOL	bRC = TRUE;

	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	std::vector<CString>	VectorImageNames;

	if ( m_strImageDir[m_strImageDir.GetLength() - 1] == TCHAR('\\') )	
		strPattern.Format( TEXT("%s*.*"), m_strImageDir );
	else
		strPattern.Format( TEXT("%s\\*.*"), m_strImageDir );

	hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	// filter off the system files and directories
	if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
	{  	  
		// test file extension
		strName = FindFileData.cFileName;
		strExt = strName.Right(3);

		if ( (strExt.CompareNoCase( TEXT("bmp") ) == 0) ||
			(strExt.CompareNoCase( TEXT("jpg") ) == 0) ||
			(strExt.CompareNoCase( TEXT("gif") ) == 0) ||
			(strExt.CompareNoCase( TEXT("tif") ) == 0) ||
			(strExt.CompareNoCase( TEXT("png") ) == 0) )
		{
			// save the image file name
			VectorImageNames.push_back(strName);
		}
	}  

	// loop through to add all of them to our vector	
	while (bRC)
	{
		bRC = ::FindNextFile(hFind, &FindFileData);
		if (bRC)
		{
			// filter off the system files and directories
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
			{
				// test file extension
				strName = FindFileData.cFileName;
				strExt = strName.Right(3);

				if ( (strExt.CompareNoCase( TEXT("bmp") ) == 0) ||
					(strExt.CompareNoCase( TEXT("jpg") ) == 0) ||
					(strExt.CompareNoCase( TEXT("gif") ) == 0) ||
					(strExt.CompareNoCase( TEXT("tif") ) == 0) ||
					(strExt.CompareNoCase( TEXT("png") ) == 0) )
				{
					// save the image file name
					VectorImageNames.push_back(strName);
				}
			}
		}  
		else
		{
			DWORD err = ::GetLastError();
			if (err !=  ERROR_NO_MORE_FILES)
			{
				return FALSE;
			}
		}
	} // end of while loop

	// close the search handle
	::FindClose(hFind);

	// update the names, if any
	if ( !VectorImageNames.empty() )
	{
		// reset the image name vector
		m_VectorImageNames.clear();
		m_VectorImageNames = VectorImageNames;
		return TRUE;
	}

	return FALSE;
}

BOOL CDlgPMosaicScreenADScreen::FindConferenceID(int nID ) 
{
	int i=0;for ( i=0;i<m_pConfDlg->m_aConferenceInfoArray.GetSize();i++)
	{
		//int nID = m_pConfDlg->m_aConferenceInfoArray.GetAt(i)->_iConferenceID;

		
		if (m_pConfDlg->m_aConferenceInfoArray.GetAt(i)->_iConferenceID==nID)
		{
		return TRUE;
		}
	}
		return FALSE;

}
void CDlgPMosaicScreenADScreen::OnBtnLoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// validate image directory
	if (m_strImageDir.IsEmpty())
	{
		return;
	}

	// show hour glass cursor
	BeginWaitCursor();

	// get the names of bitmap files
	if ( !GetImageFileNames() )
	{
		EndWaitCursor();
		return;
	}

	// draw thumbnail images in list control
	DrawThumbnails();

	// draw the selected image in its full size
	//DrawSelectedImage();

	// set focus and select the first thumbnail in the list control
	m_ListThumbnail.SetFocus();
	m_ListThumbnail.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);	
	EndWaitCursor();

}

void CDlgPMosaicScreenADScreen::OnMouseMove(UINT nFlags, CPoint point) 
{
	//While the mouse is moving, this routine is called.
	//This routine will redraw the drag image at the present
	// mouse location to display the dragging.
	//Also, while over a CListCtrl, this routine will highlight
	// the item we are hovering over.

	//// If we are in a drag/drop procedure (m_bDragging is true)
	if (m_bDragging)
	{



		//// Move the drag image
		CPoint pt(point);	//get our current mouse coordinates
		ClientToScreen(&pt); //convert to screen coordinates


		//// Get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT(pDropWnd); //make sure we have a window

		//// If we drag outside current window we need to adjust the highlights displayed
		if (pDropWnd != m_pDropWnd)
		{
			if(m_bFirstDragging )
			{
				int nOffset= -10;
				m_pImageTempThumb->BeginDrag(0, CPoint(nOffset, nOffset - 4));
				m_pImageTempThumb->DragEnter(GetDesktopWindow(), point/*pNMListView->ptAction*/);
				//// Set dragging flag and others
				//m_bDragging = TRUE;	//we are in a drag and drop operation
				m_nDropIndex = -1;	//we don't have a drop index yet
				m_pDragList = &m_ListThumbnail; //make note of which list we are dragging from
				m_pDropWnd = &m_ListThumbnail;	//at present the drag list is the drop list

				//// Capture all mouse messages
				SetCapture ();
				m_bFirstDragging  = FALSE;
			}//if(m_bFirstDragging  = FALSE)

			m_pImageTempThumb->DragMove(pt); //move the drag image to those coordinates
			// Unlock window updates (this allows the dragging image to be shown smoothly)
			m_pImageTempThumb->DragShowNolock(false);

			if (m_nDropIndex != -1) //If we drag over the CListCtrl header, turn off the hover highlight
			{
				TRACE("m_nDropIndex is -1\n");
				CListCtrl* pList = (CListCtrl*)m_pDropWnd;
				VERIFY (pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED));
				// redraw item
				VERIFY (pList->RedrawItems (m_nDropIndex, m_nDropIndex));
				pList->UpdateWindow ();
				m_nDropIndex = -1;
			}
			else //If we drag out of the CListCtrl altogether
			{
				TRACE("m_nDropIndex is not -1\n");
				CListCtrl* pList = (CListCtrl*)m_pDropWnd;
				int i = 0;
				int nCount = pList->GetItemCount();
				for(i = 0; i < nCount; i++)
				{
					pList->SetItemState(i, 0, LVIS_DROPHILITED);
				}
				pList->RedrawItems(0, nCount);
				pList->UpdateWindow();
			}
			m_bDragToOther= TRUE;


			// Save current window pointer as the CListCtrl we are dropping onto
			m_pDropWnd = pDropWnd;

			// Convert from screen coordinates to drop target client coordinates
			pDropWnd->ScreenToClient(&pt);

			//If we are hovering over a CListCtrl we need to adjust the highlights
			if(pDropWnd->IsKindOf(RUNTIME_CLASS (CListCtrl)))
			{			
				//Note that we can drop here
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				UINT uFlags;
				CListCtrl* pList = (CListCtrl*)pDropWnd;

				// Turn off hilight for previous drop target
				pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);
				// Redraw previous item
				pList->RedrawItems (m_nDropIndex, m_nDropIndex);

				// Get the item that is below cursor
				m_nDropIndex = ((CListCtrl*)pDropWnd)->HitTest(pt, &uFlags);
				// Highlight it
				pList->SetItemState(m_nDropIndex, LVIS_DROPHILITED, LVIS_DROPHILITED);
				// Redraw item
				pList->RedrawItems(m_nDropIndex, m_nDropIndex);
				pList->UpdateWindow();
			}
			else
			{
				//If we are not hovering over a CListCtrl, change the cursor
				// to note that we cannot drop here
				SetCursor(LoadCursor(NULL, IDC_NO));
			}
			m_bDragMove = FALSE;
			// Lock window updates
			m_pImageTempThumb->DragShowNolock(true);
		}
		else //花了
		{
			m_bDragToOther= FALSE;
			//移动
			//CListCtrl* pList = (CListCtrl*)m_pDropWnd;
			////pList->SetRedraw(FALSE);
			//pList->ScrollWindow(10,0);
			//SetCursor(LoadCursor(NULL, IDC_NO));
			//pList->RedrawItems(0, pList->GetItemCount());
			//pList->UpdateWindow();
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}


void CDlgPMosaicScreenADScreen::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//This routine is the end of the drag/drop operation.
	//When the button is released, we are to drop the item.
	//There are a few things we need to do to clean up and
	// finalize the drop:
	//	1) Release the mouse capture
	//	2) Set m_bDragging to false to signify we are not dragging
	//	3) Actually drop the item (we call a separate function to do that)

	CListCtrl* pList = &m_ListThumbnail;
	////pList->SetRedraw(FALSE);
	//::SendMessage(pList->m_hWnd,WM_HSCROLL,SB_LINERIGHT,NULL);

	m_nSelectedItem = m_nSelectedItem+5;
	pList->EnsureVisible(m_nSelectedItem, FALSE);

	//pList->ScrollWindow(-30,0);
	//SetCursor(LoadCursor(NULL, IDC_NO));
	// update the selected item index
	//m_nSelectedItem = m_nSelectedItem+5;
	//// draw the selected image
	//DrawSelectedImage();
	//pList->RedrawItems(0, pList->GetItemCount());
	//pList->UpdateWindow();
	//DrawThumbnails();

	//If we are in a drag and drop operation (otherwise we don't do anything)
	//if (FALSE)
	if (m_bDragging)
	{
		// Release mouse capture, so that other controls can get control/messages
		ReleaseCapture ();

		// Note that we are NOT in a drag operation
		m_bDragging = FALSE;

		// End dragging image
		m_pImageTempThumb->DragLeave (GetDesktopWindow ());
		m_pImageTempThumb->EndDrag ();
		delete m_pImageListThumb; //must delete it because it was created at the beginning of the drag

		CPoint pt (point); //Get current mouse coordinates
		ClientToScreen (&pt); //Convert to screen coordinates
		// Get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT (pDropWnd); //make sure we have a window pointer
		// If window is CListCtrl, we perform the drop

		if(m_bDragToOther)
		{
			if (pDropWnd->IsKindOf (RUNTIME_CLASS (CListCtrl)))
			{
				m_pDropList = (CListCtrl*)pDropWnd; //Set pointer to the list we are dropping on
				//DropItemOnList(m_pDragList, m_pDropList); //Call routine to perform the actual drop
			}
		}
		//else //花了
		//{
		//	//移动
		//	CListCtrl* pList = (CListCtrl*)m_pDropWnd;
		//	pList->SetRedraw(FALSE);
		//	pList->ScrollWindow(10,0);
		//	pList->SetRedraw();
		//}

	}

	CDialog::OnLButtonUp(nFlags, point);
}
//void CDlgPMosaicScreenADScreen::DropItemOnList(CListCtrl* pDragList, CListCtrl* pDropList)
//{
//	//This routine performs the actual drop of the item dragged.
//	//It simply grabs the info from the Drag list (pDragList)
//	// and puts that info into the list dropped on (pDropList).
//	//Send:	pDragList = pointer to CListCtrl we dragged from,
//	//		pDropList = pointer to CListCtrl we are dropping on.
//	//Return: nothing.
//
//	////Variables
//
//
//	// Unhilight the drop target
//	pDropList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);
//
//	//Set up the LV_ITEM for retrieving item from pDragList and adding the new item to the pDropList
//	char szLabel[256];
//	LVITEM lviT;
//	LVITEM* plvitem;
//
//	ZeroMemory(&lviT, sizeof (LVITEM)); //allocate and clear memory space for LV_ITEM
//	lviT.iItem		= m_nDragIndex;
//	lviT.mask		= LVIF_TEXT;
//	lviT.pszText		= szLabel;
//	lviT.cchTextMax	= 255;
//
//	lvItem* pItem;
//	lvItem lvi;
//	lvi.plvi = &lviT;
//	lvi.plvi->iItem = m_nDragIndex;
//	lvi.plvi->mask = LVIF_TEXT;
//	lvi.plvi->pszText = szLabel;
//	lvi.plvi->cchTextMax = 255;
//
//	if(pDragList->GetSelectedCount() == 1)
//	{
//		// Get item that was dragged
//		pDragList->GetItem (lvi.plvi);
//		lvi.sCol2 = pDragList->GetItemText(lvi.plvi->iItem, 1);
//
//		// Delete the original item (for Move operation)
//		// This is optional. If you want to implement a Copy operation, don't delete.
//		// This works very well though for re-arranging items within a CListCtrl.
//		// It is written at present such that when dragging from one list to the other
//		//  the item is copied, but if dragging within one list, the item is moved.
//		if(pDragList == pDropList)
//		{
//			pDragList->DeleteItem (m_nDragIndex);
//			if(m_nDragIndex < m_nDropIndex) m_nDropIndex--; //decrement drop index to account for item
//			//being deleted above it
//		}
//
//		// Insert item into pDropList
//		// if m_nDropIndex == -1, iItem = GetItemCount() (inserts at end of list), else iItem = m_nDropIndex
//		lvi.plvi->iItem = (m_nDropIndex == -1) ? pDropList->GetItemCount () : m_nDropIndex;
//		pDropList->InsertItem (lvi.plvi);
//		pDropList->SetItemText(lvi.plvi->iItem, 1, (LPCTSTR)lvi.sCol2);
//
//		// Select the new item we just inserted
//		pDropList->SetItemState (lvi.plvi->iItem, LVIS_SELECTED, LVIS_SELECTED);
//	}
//	else //more than 1 item is being dropped
//	{
//		//We have to parse through all of the selected items from the DragList
//		//1) Retrieve the info for the items and store them in memory
//		//2) If we are reordering, delete the items from the list
//		//3) Insert the items into the list (either same list or different list)
//
//		CList<lvItem*, lvItem*> listItems;
//		POSITION listPos;
//
//		//Retrieve the selected items
//		POSITION pos = pDragList->GetFirstSelectedItemPosition(); //iterator for the CListCtrl
//		while(pos) //so long as we have a valid POSITION, we keep iterating
//		{
//			plvitem = new LVITEM;
//			ZeroMemory(plvitem, sizeof(LVITEM));
//			pItem = new lvItem;
//			//ZeroMemory(pItem, sizeof(lvItem)); //If you use ZeroMemory on the lvItem struct, it creates an error when you try to set sCol2
//			pItem->plvi = plvitem;
//			pItem->plvi->iItem = m_nDragIndex;
//			pItem->plvi->mask = LVIF_TEXT;
//			pItem->plvi->pszText = new char; //since this is a pointer to the string, we need a new pointer to a new string on the heap
//			pItem->plvi->cchTextMax = 255;
//
//			m_nDragIndex = pDragList->GetNextSelectedItem(pos);
//
//			//Get the item
//			pItem->plvi->iItem = m_nDragIndex; //set the index in the drag list to the selected item
//			pDragList->GetItem(pItem->plvi); //retrieve the information
//			pItem->sCol2 = pDragList->GetItemText(pItem->plvi->iItem, 1);
//
//			//Save the pointer to the new item in our CList
//			listItems.AddTail(pItem);
//		} //EO while(pos) -- at this point we have deleted the moving items and stored them in memory
//
//		if(pDragList == pDropList) //we are reordering the list (moving)
//		{
//			//Delete the selected items
//			pos = pDragList->GetFirstSelectedItemPosition();
//			while(pos)
//			{
//				pos = pDragList->GetFirstSelectedItemPosition();
//				m_nDragIndex = pDragList->GetNextSelectedItem(pos);
//
//				pDragList->DeleteItem(m_nDragIndex); //since we are MOVING, delete the item
//				if(m_nDragIndex < m_nDropIndex) m_nDropIndex--; //must decrement the drop index to account
//				//for the deleted items
//			} //EO while(pos)
//		} //EO if(pDragList...
//
//		//Iterate through the items stored in memory and add them back into the CListCtrl at the drop index
//		listPos = listItems.GetHeadPosition();
//		while(listPos)
//		{
//			pItem = listItems.GetNext(listPos);
//
//			m_nDropIndex = (m_nDropIndex == -1) ? pDropList->GetItemCount() : m_nDropIndex;
//			pItem->plvi->iItem = m_nDropIndex;
//			pDropList->InsertItem(pItem->plvi); //add the item
//			pDropList->SetItemText(pItem->plvi->iItem, 1, pItem->sCol2);
//
//			pDropList->SetItemState(pItem->plvi->iItem, LVIS_SELECTED, LVIS_SELECTED); //highlight/select the item we just added
//
//			m_nDropIndex++; //increment the index we are dropping at to keep the dropped items in the same order they were in in the Drag List
//			//If we dont' increment this, the items are added in reverse order
//		} //EO while(listPos)
//
//	}
//}
//
//
void CDlgPMosaicScreenADScreen::OnBegindragListLeft(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//This routine sets the parameters for a Drag and Drop operation.
	//It sets some variables to track the Drag/Drop as well
	// as creating the drag image to be shown during the drag.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	//// Save the index of the item being dragged in m_nDragIndex
	////  This will be used later for retrieving the info dragged
	m_nDragIndex = pNMListView->iItem;

	//// Create a drag image
	POINT pt;
	int nOffset = -10; //offset in pixels for drag image (positive is up and to the left; neg is down and to the right)
	if(m_ListThumbnail.GetSelectedCount() > 1) //more than one item is selected
		pt.x = nOffset;
	pt.y = nOffset;

	m_bFirstDragging = TRUE;

	m_pImageTempThumb = m_ListThumbnail.CreateDragImage(m_nDragIndex, &pt);
	ASSERT(m_pImageListThumb); //make sure it was created
	//We will call delete later (in LButtonUp) to clean this up

	////CBitmap bitmap;
	////if(m_ListThumbnail.GetSelectedCount() > 1) //more than 1 item in list is selected
	////	//bitmap.LoadBitmap(IDB_BITMAP_MULTI);
	////	bitmap.LoadBitmap(IDB_BITMAP_MULTI_BOXES);
	////else
	////	bitmap.LoadBitmap(IDB_BITMAP_BOX);
	////m_pImageTempThumb->Replace(0, &bitmap, &bitmap);

	//// Change the cursor to the drag image
	////	(still must perform DragMove() in OnMouseMove() to show it moving)
	//m_pImageTempThumb->BeginDrag(0, CPoint(nOffset, nOffset - 4));
	//m_pImageTempThumb->DragEnter(GetDesktopWindow(), pNMListView->ptAction);
	//
	////// Set dragging flag and others
	m_bDragging = TRUE;	//we are in a drag and drop operation
	m_nDropIndex = -1;	//we don't have a drop index yet
	m_pDragList = &m_ListThumbnail; //make note of which list we are dragging from
	m_pDropWnd = &m_ListThumbnail;	//at present the drag list is the drop list

	////// Capture all mouse messages
	//SetCapture ();

	*pResult = 0;
}




void CDlgPMosaicScreenADScreen::OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//// TODO: Add your control notification handler code here
	//DWORD dwPos = GetMessagePos();
	//m_dwPos = dwPos;
	//CPoint point(LOWORD(dwPos), HIWORD(dwPos));

	//m_bDragMove = FALSE;

	//// retrieve message info.
	//LPNMITEMACTIVATE pItemAct = (LPNMITEMACTIVATE)pNMHDR;

	//// determine which item receives the click
	//LVHITTESTINFO  hitTest;
	//ZeroMemory(&hitTest, sizeof(LVHITTESTINFO));
	//hitTest.pt = pItemAct->ptAction;
	//m_ListThumbnail.SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hitTest);

	//// draw the selected image
	//if (hitTest.iItem != m_nSelectedItem && hitTest.iItem >= 0)
	//{
	//	m_nSelectedItem = hitTest.iItem;

	//	DrawSelectedImage();
	//}

	// select the item clicked
	*pResult = 0;
}

void CDlgPMosaicScreenADScreen::OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if (pLVKeyDow->wVKey == VK_LEFT || pLVKeyDow->wVKey == VK_RIGHT)
	{	
		// get total number of items in the list
		int nTotal = m_ListThumbnail.GetItemCount();

		// rule out the situation of an empty list
		if (nTotal == 0)
		{
			*pResult = 1; // current record stays selected
			return;
		}

		// reset selected item index
		int  nNewItem = -1;

		// set the selection
		if (pLVKeyDow->wVKey == VK_LEFT)	// left arrow
		{
			if (m_nSelectedItem > 0)
				nNewItem = m_nSelectedItem - 1;
		}
		else	// right arrow
		{
			if (m_nSelectedItem < nTotal-1)
				nNewItem = m_nSelectedItem + 1;
		}

		// update the selection
		if (nNewItem != -1)
		{
			// update the selected item index
			m_nSelectedItem = nNewItem;

			// draw the selected image
			//DrawSelectedImage();
		}	 
	}

	// high-light the selected item
	*pResult = 0;
}


//HBRUSH CDlgPMosaicScreenADScreen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	//pDC->SetBkMode(TRANSPARENT);
//	//pDC->SetTextColor(RGB(255, 255, 255));
//	return m_brushBK;
//}
BOOL CDlgPMosaicScreenADScreen::OnEraseBkgnd(CDC* pDC)
{
	BOOL bRet = TRUE;	//CDialog::OnEraseBkgnd(pDC);
CRect rcClient;
		GetClientRect(&rcClient);
		//m_pTempletArithmetic->GetFreeRect(&rcClient);
		pDC->FillSolidRect(rcClient,RGB(100,100,100));

	// 加载并显示图片
	//BITMAP Bm;    	    //保存位图的宽、高度等数据 
	//HBITMAP hBitmap; 	//保存位图数据句柄 
	//CDC     memDC;
	//CClientDC ClientDC(this);

	//memDC.CreateCompatibleDC(NULL); //产生内存设备情境对象 

	//hBitmap = HBITMAP(m_bmpBk);

	//memDC.SelectObject(hBitmap); //将位图选入内存设备情境对象
	//::GetObject(hBitmap, sizeof(Bm), &Bm); 
	////pDC->BitBlt ( 0, 0, 1080, 800, &memDC, 0, 0, SRCCOPY); 
	//pDC->BitBlt ( 0, 0, Bm.bmWidth, Bm.bmHeight, &memDC, 0, 0, SRCCOPY); 

	//memDC.DeleteDC();

	return bRet;
}

void CDlgPMosaicScreenADScreen::SetWondowSelected(byte iIndex, bool bSelect)
{
	if (0 <= iIndex && iIndex < m_aWinInfoArray.GetSize())
	{
		m_szbSelect[iIndex] = bSelect;
	}

	//if (m_pTempletArithmetic)
	//{
	//	m_pTempletArithmetic->SetWindowSelected(iIndex,bSelect);
	//}
}
// 设置所有窗口的选中状态
void CDlgPMosaicScreenADScreen::SetAllWindowSelected(bool bSelect)
{
	TWinInfo *ptTempWinInfo;
	int i=0;for ( i=0; i<m_aWinInfoArray.GetSize(); i++)
	{
		SetWondowSelected(i,bSelect);
		//ptTempWinInfo = m_aWinInfoArray.GetAt(i);
		//if (ptTempWinInfo)
		//{
		//	((CCUserWinDlgDlg*)(ptTempWinInfo->_pdDialogInf))->SetSelected(bSelect);
		//}
	}
}
bool CDlgPMosaicScreenADScreen::GetWindowSelected(byte iIndex)
{
	if (0 <= iIndex && iIndex < m_aWinInfoArray.GetSize())
	{
		return m_szbSelect[iIndex];
	}

	if (iIndex == 0)
	{
		TRACE(_T("CConferenceWinDlg::GetWindowSelected(%d)=%d"), iIndex, m_szbSelect[iIndex]);
	}

	//if (m_pTempletArithmetic && iIndex >= 0)
	//{
	//	return m_pTempletArithmetic->GetWindowSelected(iIndex);
	//}

	return false;
}
BOOL CDlgPMosaicScreenADScreen::OnInitDialog()
{
	CDialog::OnInitDialog();


	//m_btnTemplet_0.m_bShowRedFrame=TRUE;
	//m_btnTemplet_1.m_bShowRedFrame=TRUE;
	//m_btnTemplet_2.m_bShowRedFrame=TRUE;
	//m_btnTemplet_3.m_bShowRedFrame=TRUE;
	//m_btnTemplet_4.m_bShowRedFrame=TRUE;
	//m_btnTemplet_5.m_bShowRedFrame=TRUE;
	//m_btnTemplet_6.m_bShowRedFrame=TRUE;
	////m_btnTemplet_7.m_bShowRedFrame=TRUE;
	////m_btnTemplet_8.m_bShowRedFrame=TRUE;
	////m_btnTemplet_9.m_bShowRedFrame=TRUE;
	////m_btnTemplet_10.m_bShowRedFrame=TRUE;
	////m_btnTemplet_11.m_bShowRedFrame=TRUE;
	////m_btnTemplet_12.m_bShowRedFrame=TRUE;
	////m_btnTemplet_13.m_bShowRedFrame=TRUE;

	CString strPath = _T("");
	////if (m_nXPE)
	//	strPath = _T("\\SKIN\\DEFAULT\\Max_Login.bmp");
	//else
	//	strPath = _T("\\SKIN\\DEFAULT\\PADbg.jpg");

	//TCHAR strTemp[200];
	//strPath =  GetFileName(strPath,strTemp);

	//CImage imgTemp;
	//imgTemp.Load(strPath);
	//if ( m_bmpBk.m_hObject ) 
	//	m_bmpBk.Detach();
	//m_bmpBk.Attach(imgTemp.Detach());

	//m_btnTemplet_0.SetBitmap(AfxGetApp()->m_hInstance, GetExePath() + _T("\\SKIN\\DEFAULT\\yg1.png"), CSize(87, 150), CPoint(0, 0));
	//m_btnTemplet_1.SetBitmap(AfxGetApp()->m_hInstance, GetExePath() + _T("\\SKIN\\DEFAULT\\yg1.png"), CSize(87, 150), CPoint(0, 0));
	//m_btnTemplet_2.SetBitmap(AfxGetApp()->m_hInstance, GetExePath() + _T("\\SKIN\\DEFAULT\\sp1.png"), CSize(311, 121), CPoint(0, 0));
	//m_btnTemplet_3.SetBitmap(AfxGetApp()->m_hInstance, GetExePath() + _T("\\SKIN\\DEFAULT\\sp1.png"), CSize(311, 121), CPoint(0, 0));
	//m_btnTemplet_4.SetBitmap(AfxGetApp()->m_hInstance, GetExePath() + _T("\\SKIN\\DEFAULT\\sp1.png"), CSize(311, 121), CPoint(0, 0));
	//m_btnTemplet_5.SetBitmap(AfxGetApp()->m_hInstance, GetExePath() + _T("\\SKIN\\DEFAULT\\pg1.png"), CSize(87, 145), CPoint(0, 0));
	//m_btnTemplet_6.SetBitmap(AfxGetApp()->m_hInstance, GetExePath() + _T("\\SKIN\\DEFAULT\\pg1.png"), CSize(87, 145), CPoint(0, 0));

	//		m_btnTemplet_1.ShowWindow(SW_HIDE);
	//m_btnTemplet_2.ShowWindow(SW_HIDE);
	//m_btnTemplet_4.ShowWindow(SW_HIDE);
	//m_btnTemplet_6.ShowWindow(SW_HIDE);
	////m_btnTemplet_0.SetBitmap(AfxGetApp()->m_hInstance, strPicPath/*IDB_BMP_WINLAYOUT*/, CSize(100, 65), CPoint(0, 0));
	////m_btnTemplet_1.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(100, 0));
	////m_btnTemplet_2.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(400, 0));
	////m_btnTemplet_3.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(500, 0));
	////m_btnTemplet_4.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(600, 0));
	////m_btnTemplet_5.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(700, 0));
	////m_btnTemplet_6.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(800, 0));
	////m_btnTemplet_7.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(1200, 0));
	////m_btnTemplet_8.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(1300, 0));
	////m_btnTemplet_9.SetBitmap(AfxGetApp()->m_hInstance, strPicPath/*IDB_BITMAP_NORMAL_TEMPLET*/, CSize(100, 65), CPoint(200, 0));
	////m_btnTemplet_10.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(300, 0));
	////m_btnTemplet_11.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(900, 0));
	////m_btnTemplet_12.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(1000, 0));
	////m_btnTemplet_13.SetBitmap(AfxGetApp()->m_hInstance, strPicPath, CSize(100, 65), CPoint(1100, 0));

	CreateConferenceWinDlg();

//	CRect Mainrect;
//	TWinInfo *ptTempWinInfo;
//
//
//	CTempletArithmeticFactory cTempTempletArithmeticFactory;
//	m_pTempletArithmetic=cTempTempletArithmeticFactory.CreateTempletArithmetic(0x0003 /*ID16x9TEMPLETNORMALID_LOGIC*/);
//	//m_iWinClass=iWinClass;			//屏种类	1，2，3第几个种类
//	//m_bWinTemplate=bWinTemplate;		//屏模板模式	0：不显示所有,1：为显示所有
//	//m_iWinNumber=iWinNumber;			//屏数量	
//	//m_iWinType=iWinType;	
//
//	CRect rect;
//	GetClientRect(&rect);
int nFullWidth=1280/*GetSystemMetrics(SM_CXSCREEN)/2*/ ;       
	int nFullHeight=800 /*GetSystemMetrics(SM_CYSCREEN)/2*/ ;  
//	rect.left = 0;
//	rect.top = 0;
//	rect.bottom = nFullHeight *3/4;
//	rect.right = nFullWidth;
//	m_pTempletArithmetic->SetScreenIndex(1,rect);
//	m_pTempletArithmetic->SetType(22,0/*m_iWinType,m_iWinNumber*/);
//	//m_iWinType	12 '?'	unsigned char
//	//m_iWinNumber	0	unsigned char
//	//m_iWinClass	2 '?'	unsigned char
//	//m_bWinTemplate	true	bool
//	TWinInfo *ptWinInfo = NULL;
	//int n1 = m_pTempletArithmetic->GetWindowCount();
	//int n2 = m_aWinInfoArray.GetSize();
	//int i=0;for ( i=0;i<n1 ;i++)
	//{
	//	CCUserWinDlgDlg *pdUserDlg=new CCUserWinDlgDlg(this);
	//	pdUserDlg->Create(IDD_CUSERWINDLG_DIALOG, this);

	//	pdUserDlg->SetIndex(i);

	//	pdUserDlg->SetSessionID(i);
	//	pdUserDlg->SetMainDlg(m_pConfDlg);

	//	ptWinInfo=new TWinInfo;
	//	ptWinInfo->_pdDialogInf=pdUserDlg;
	//	ptWinInfo->_iSessionID=0;
	//	ptWinInfo->_iFrameInfoType=ntFrameNull;
	//	ptWinInfo->_ptVideoSoundInfo=new TVideoSoundInfo;
	//	ptWinInfo->_ptVideoSoundInfo->_iUserCardNo=255;
	//	ptWinInfo->_ptVideoSoundInfo->_bSound=false;
	//	ptWinInfo->_ptVideoSoundInfo->_bVideo=false;
	//	int nsize=	m_aWinInfoArray.GetSize();
	//	m_aWinInfoArray.Add(ptWinInfo);
	//}
//	int nSize = m_aWinInfoArray.GetSize();
//	if (m_szbSelect)
//	{
//		delete []m_szbSelect;
//		m_szbSelect = NULL;
//	}
//	m_szbSelect = new bool[nSize];
//	for (int i = 0; i < nSize; i++)
//	{
//		m_szbSelect[i] = false;
//	}
	// n2 = m_aWinInfoArray.GetSize();
	//int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
	//{
	//	ptTempWinInfo=m_aWinInfoArray.GetAt(i);
	//	m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);
	//	rect=ptTempWinInfo->_rcScreen;
	//	//rect.left-=Mainrect.left;
	//	//rect.right-=Mainrect.left;
	//	//rect.top-=Mainrect.top;
	//	//rect.bottom-=Mainrect.top;
	//	ptTempWinInfo->_pdDialogInf->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	//	//ptTempWinInfo->_pdDialogInf->RedrawWindow();
	//	ptTempWinInfo->_rcScreen=rect;
	//}

	SetWindowPos(NULL,0,0,nFullWidth,nFullHeight,SWP_SHOWWINDOW | SWP_NOACTIVATE);

	m_pImageListThumb = new CImageList();
	//m_pImageListThumb2 = new CImageList();
	// TODO: Add extra initialization here
	m_pImageListThumb->Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
	m_ListThumbnail.SetImageList(m_pImageListThumb, LVSIL_NORMAL);

	//m_pImageListThumb2->Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
	//m_ListAllScreen.SetImageList(m_pImageListThumb2, LVSIL_NORMAL);

	m_nSelectedItem = 0;
	m_strImageDir  = GetExePath() + _T("data\\image\\");

	//生成缩略图的文件 
	//bool AVScreenCapture::Capture(char**ppData,int&nLen)

	OnBtnLoad();
	InitConferenceWin(0);
		//m_ListThumbnail.SetWindowPos(NULL,0  +20,nFullHeight -(THUMBNAIL_HEIGHT+40) ,nFullWidth-20*2,THUMBNAIL_HEIGHT+40 ,SWP_SHOWWINDOW );
	return TRUE;
}
void CDlgPMosaicScreenADScreen::InitConferenceWin(int iWinIndex)
{
	TRACE("CConferenceDlg::InitConferenceWin %d\n",iWinIndex);
	//AutoLockResource Lock;


	////检查,关闭全屏视频窗口
	//if (m_pDlgFullScreen[iWinIndex] && 
	//	m_pDlgFullScreen[iWinIndex]->GetFullScreenWnd() != NULL)
	//{
	//	CBaseDlg *pDlg = (CBaseDlg *)m_pDlgFullScreen[iWinIndex]->GetFullScreenWnd();
	//	//if (pDlg->GetFrameInfoType() == ntVideoSound)
	//	{
	//		m_pDlgFullScreen[iWinIndex]->RestoreScreen();   //关闭全屏视频窗口
	//	}
	//}

	int nClassType = 0;
	int nType = 0;
	//if (!m_ptLocalUserInfo || !m_ptLocalUserInfo->_pConferenceInfo)
	//{
	//	return;
	//}
	//nClassType = m_ptLocalUserInfo->_pConferenceInfo->_iWinClass[iWinIndex];
	//nType = m_ptLocalUserInfo->_pConferenceInfo->_iWinType[iWinIndex];
	if (m_pdConferenceWinDlg[iWinIndex])
	{
		m_pdConferenceWinDlg[iWinIndex]->SetTemplateInfo(2,true, 0, 12);
	}
	//if (GetTemplateControlDlg() != NULL)
	//	GetTemplateControlDlg()->SetTemplateInfo(iWinIndex,nClassType,m_ptLocalUserInfo->_pConferenceInfo->_bWinTemplate[iWinIndex], m_ptLocalUserInfo->_pConferenceInfo->_iWinNumber[iWinIndex], nType);

	//m_pdConferenceWinDlg[iWinIndex]->SetTemplateDlgIcon(m_hIcon);
	m_pdConferenceWinDlg[iWinIndex]->InitConferenceWinDlg();

	//if (GetTemplateControlDlg() != NULL)
	//{
	//	GetTemplateControlDlg()->InitTemplateControlDlg(iWinIndex);
	//	SetTempleteControlWndFrameTypeAndCard();
	//}


	TRACE("CConferenceDlg::InitConferenceWin end\n");
//m_pDlgToolbar->OnBnClickedBtnTbFullscreen();
}
void  CDlgPMosaicScreenADScreen::DrawThumbnails()
{
	CBitmap*    pImage = NULL;
	HBITMAP		hBmp = NULL;
	POINT		pt;
	CString		strPath;
	int			i;

	// no images
	if (m_VectorImageNames.empty())
		return;

	// set the length of the space between thumbnails
	// you can also calculate and set it based on the length of your list control
	int nGap = 6;

	// hold the window update to avoid flicking
	m_ListThumbnail.SetRedraw(FALSE);

	// reset our image list
	for (i = 0; i<m_pImageListThumb->GetImageCount(); i++)
		m_pImageListThumb->Remove(i);	

	// remove all items from list view
	if (m_ListThumbnail.GetItemCount() != 0)
		m_ListThumbnail.DeleteAllItems();

	// set the size of the image list
	m_pImageListThumb->SetImageCount(m_VectorImageNames.size());
	i = 0;

	// draw the thumbnails
	std::vector<CString>::iterator	iter;
	for (iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)
	{		
		// load the bitmap
		strPath.Format( _T("%s\%s"), m_strImageDir, *iter );

		//USES_CONVERSION;
		Bitmap img( (strPath) );
		Bitmap* pThumbnail = static_cast<Bitmap*>(img.GetThumbnailImage(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, NULL, NULL));
		if(NULL == pThumbnail  )
		{
			continue;
		}
		// attach the thumbnail bitmap handle to an CBitmap object
		pThumbnail->GetHBITMAP(NULL, &hBmp);
		pImage = new CBitmap();		 
		pImage->Attach(hBmp);

		// add bitmap to our image list
		m_pImageListThumb->Replace(i, pImage, NULL);

		// put item to display
		// set the image file name as item text
		m_ListThumbnail.InsertItem(i, m_VectorImageNames[i], i);

		// get current item position	 
		m_ListThumbnail.GetItemPosition(i, &pt);	 

		// shift the thumbnail to desired position
		pt.x = nGap + i*(THUMBNAIL_WIDTH + nGap);
		m_ListThumbnail.SetItemPosition(i, pt);
		i++;

		delete pImage;
		delete pThumbnail;
	}

	// let's show the new thumbnails
	m_ListThumbnail.SetRedraw(); 
}

void  CDlgPMosaicScreenADScreen::DrawSelectedImage()
{

	int i=0;
	for ( i=0; i<m_aWinInfoArray.GetSize(); i++)
	{
	 if(GetWindowSelected(i))
	 {
		int nSessionID=	m_aWinInfoArray.GetAt(i)->_iSessionID ;

	 }
	}

	CString		strPath;

	// read the image file
	if (m_strImageDir.Right(1) == TEXT("\\") )
		strPath.Format( TEXT("%s%s"), m_strImageDir, m_VectorImageNames[m_nSelectedItem] );
	else
		strPath.Format( TEXT("%s\\%s"), m_strImageDir, m_VectorImageNames[m_nSelectedItem] );

	//USES_CONVERSION;
	Image img( /*A2W*/(strPath) );

	//上墙
	int n2 = m_aWinInfoArray.GetSize();
	Graphics gc( this->GetDC()->GetSafeHdc() );
	//int i=0;
	for ( i=0;i<n2 ;i++)
	{
		Rect		DesRect;
		DesRect.X = m_aWinInfoArray.GetAt(i)->_rcScreen.left;
		DesRect.Y = m_aWinInfoArray.GetAt(i)->_rcScreen.top;
		DesRect.Width =  m_aWinInfoArray.GetAt(i)->_rcScreen.right -  m_aWinInfoArray.GetAt(i)->_rcScreen.left;
		DesRect.Height =  m_aWinInfoArray.GetAt(i)->_rcScreen.bottom -  m_aWinInfoArray.GetAt(i)->_rcScreen.top;

		// draw the image
		gc.DrawImage(&img, DesRect);
	}

	int nPart, nAll, nConfID ;
	int iSessionID;
	//邀请到该会议室 
	//显示分割效果
	//m_pConfDlg->ControlD( iSessionID, 1, 4,171);

}

void CDlgPMosaicScreenADScreen::SetNomalTempletType(int nType)
{
	SetCheckTemplet(nType);
}

unsigned char CDlgPMosaicScreenADScreen::GetNomalTempletType()			//得到模板类型
{
	TRACE(_T("CDlgPMosaicScreenADScreen::GetNomalTempletType(): %d\n"), m_ucType);
	return m_ucType;
}


BOOL CDlgPMosaicScreenADScreen::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message != WM_KEYDOWN)
	{
		return CDialog::PreTranslateMessage( pMsg );
	}

	if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	// TODO: 在此添加专用代码和/或调用基类
	if(WM_LBUTTONDOWN==pMsg->message)
	{	
		DWORD dwPos = GetMessagePos();
		m_dwPos = dwPos;
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));

		m_bDragMove = TRUE;


	}
	if(WM_MOUSEMOVE==pMsg->message )
	{	
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));

		if(m_bDragMove)
		{
			CPoint point1(LOWORD(m_dwPos), HIWORD(m_dwPos));
			int nX= point1.x - point.x;
			TRACE("WM_MOUSEMOVE is nX %d \n",nX);
			if(nX >1 )
			{
				::PostMessage(m_ListThumbnail,WM_HSCROLL,SB_LINELEFT,NULL);

			}
			else if(nX <-1 )
			{
				::PostMessage(m_ListThumbnail,WM_HSCROLL,SB_LINERIGHT,NULL);

			}
			m_dwPos = dwPos;
		}

	}	
	//if(WM_LBUTTONUP==pMsg->message ) //listctl里无法接收到up 命令?
	//{	
	//	DWORD dwPos = GetMessagePos();
	//	m_dwPos = dwPos;
	//	CPoint point(LOWORD(dwPos), HIWORD(dwPos));

	//	m_bDragMove = FALSE;
	//}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPMosaicScreenADScreen::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_btnTemplet_0.GetSafeHwnd() && m_btnTemplet_6.GetSafeHwnd())
	{
		m_btnTemplet_0.SetWindowPos(&wndTop, 552,12, 87, 150, SWP_SHOWWINDOW | SWP_NOACTIVATE);
		m_btnTemplet_1.SetWindowPos(&wndTop, 686,12, 87, 150, SWP_SHOWWINDOW | SWP_NOACTIVATE);
		m_btnTemplet_2.SetWindowPos(&wndTop, 47,185, 311, 121, SWP_SHOWWINDOW | SWP_NOACTIVATE);
		m_btnTemplet_3.SetWindowPos(&wndTop, 47,332,  311, 121, SWP_SHOWWINDOW | SWP_NOACTIVATE);
		m_btnTemplet_4.SetWindowPos(&wndTop, 47,490, 311, 121, SWP_SHOWWINDOW | SWP_NOACTIVATE);
		m_btnTemplet_5.SetWindowPos(&wndTop, 552,645, 87, 145, SWP_SHOWWINDOW | SWP_NOACTIVATE);
		m_btnTemplet_6.SetWindowPos(&wndTop, 686,645,  87, 145, SWP_SHOWWINDOW | SWP_NOACTIVATE);

		m_btnTemplet_1.ShowWindow(SW_HIDE);
		m_btnTemplet_2.ShowWindow(SW_HIDE);
		m_btnTemplet_4.ShowWindow(SW_HIDE);
		m_btnTemplet_6.ShowWindow(SW_HIDE);
	}
	//n2 = m_aWinInfoArray.GetSize();
	if (m_ListThumbnail.GetSafeHwnd()  )
	{
		CRect rect;
		TWinInfo *ptTempWinInfo;
		int i=0;for ( i=0;i<m_aWinInfoArray.GetSize();i++)
		{
			ptTempWinInfo=m_aWinInfoArray.GetAt(i);
			m_pTempletArithmetic->GetWndRect(i,ptTempWinInfo->_rcScreen);
			rect=ptTempWinInfo->_rcScreen;
			//rect.left-=Mainrect.left;
			//rect.right-=Mainrect.left;
			//rect.top-=Mainrect.top;
			//rect.bottom-=Mainrect.top;
			ptTempWinInfo->_pdDialogInf->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
			//ptTempWinInfo->_pdDialogInf->RedrawWindow();
			ptTempWinInfo->_rcScreen=rect;
		}
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN) /2 ; 
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN)/2;       
		GetDlgItem(IDC_BUTTON6)->SetWindowPos(NULL,40  +20,nFullHeight -(THUMBNAIL_HEIGHT+40)-40 ,40, 40 ,SWP_SHOWWINDOW );
		GetDlgItem(IDC_BUTTON1)->SetWindowPos(NULL,40*3  +20,nFullHeight -(THUMBNAIL_HEIGHT+40)-40 ,40 , 40 ,SWP_SHOWWINDOW );
		GetDlgItem(IDC_BUTTON29)->SetWindowPos(NULL,40*6  +20,nFullHeight -(THUMBNAIL_HEIGHT+40)-40 ,40, 40 ,SWP_SHOWWINDOW );
		GetDlgItem(IDC_BUTTON2)->SetWindowPos(NULL,40*18  +20,nFullHeight -(THUMBNAIL_HEIGHT+40)-40 ,40, 40 ,SWP_SHOWWINDOW );
		
		GetDlgItem(IDC_COMBO1)->SetWindowPos(NULL,40*9  +20,nFullHeight -(THUMBNAIL_HEIGHT+40)-40 ,40, 40 ,SWP_SHOWWINDOW );
		
		m_ListThumbnail.SetWindowPos(NULL,0  +20,nFullHeight -(THUMBNAIL_HEIGHT+40) ,nFullWidth-20*2,THUMBNAIL_HEIGHT+30 ,SWP_SHOWWINDOW );
	
		m_pdConferenceWinDlg[0]->SetWindowPos(NULL,0,0,nFullWidth /*rcMain.Width()*/ ,nFullHeight-(THUMBNAIL_HEIGHT+40),SWP_SHOWWINDOW | SWP_NOACTIVATE);
	
	}

}
void CDlgPMosaicScreenADScreen::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CDlgPMosaicScreenADScreen::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnOK();
}

void CDlgPMosaicScreenADScreen::OnLvnBegindragListThumb(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDlgPMosaicScreenADScreen::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgPMosaicScreenADScreen::OnBnClickedButton29()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgPMosaicScreenADScreen::OnNMDblclkListThumb(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();
	m_dwPos = dwPos;
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));

	m_bDragMove = FALSE;

	// retrieve message info.
	LPNMITEMACTIVATE pItemAct = (LPNMITEMACTIVATE)pNMHDR;

	// determine which item receives the click
	LVHITTESTINFO  hitTest;
	ZeroMemory(&hitTest, sizeof(LVHITTESTINFO));
	hitTest.pt = pItemAct->ptAction;
	m_ListThumbnail.SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hitTest);

	// draw the selected image
	if (hitTest.iItem != m_nSelectedItem && hitTest.iItem >= 0)
	{
		m_nSelectedItem = hitTest.iItem;

		DrawSelectedImage();
	}

	*pResult = 0;
}

void CDlgPMosaicScreenADScreen::DropNotify(char *pData,int nLen,byte ucScreenIndex,byte nWndIndex)		//响应拖动
{
	
}
