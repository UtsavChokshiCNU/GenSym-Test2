// TabTreeFile.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "TabTreeFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabTreeFile

CTabTreeFile::CTabTreeFile()
{
	m_bMultiSelect = true;
}

CTabTreeFile::~CTabTreeFile()
{
}


BEGIN_MESSAGE_MAP(CTabTreeFile, CXTPTreeCtrl)
	//{{AFX_MSG_MAP(CTabTreeFile)
	ON_WM_NCHITTEST_EX()
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabTreeFile message handlers

BOOL CTabTreeFile::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CXTPTreeCtrl::PreCreateWindow( cs ))
		return FALSE;

	// Set the style for the tree control.
	cs.style |= TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

LRESULT CTabTreeFile::OnNcHitTest(CPoint point) 
{
	UINT uFlag=0;

	// Get the cursor location in client coordinates.
	CPoint pt = point;	
	ScreenToClient(&pt);

	// Get a pointer to the tooltip control.
	CToolTipCtrl* pCtrl = (CToolTipCtrl*)CWnd::FromHandle(
		(HWND)::SendMessage(m_hWnd, TVM_GETTOOLTIPS, 0, 0L));

	// If we have a valid tooltip pointer and the cursor
	// is over a tree item, the bring the tooltip control
	// to the top of the Z-order.
	if (pCtrl && HitTest(pt, &uFlag)){
		pCtrl->SetWindowPos(&wndTop,0, 0, 0, 0,
			SWP_NOACTIVATE | SWP_NOSIZE |SWP_NOMOVE);
	}
	
	return (LRESULT)CXTPTreeCtrl::OnNcHitTest(point);
}

void CTabTreeFile::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	// TODO: Add your control notification handler code here
	if (pTVDispInfo->item.pszText)
	{
		SetItemText(pTVDispInfo->item.hItem,
			pTVDispInfo->item.pszText);
	}
	
	*pResult = 0;
}

BOOL CTabTreeFile::PreTranslateMessage(MSG* pMsg) 
{
	// If the tree control has an edit control, don't allow
	// the framework to process accelerators, let the edit
	// control handle it instead...
	
	CEdit* pEditCtrl = GetEditControl();
	if (pEditCtrl && ::IsWindow(pEditCtrl->m_hWnd))
	{
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		
		return TRUE;
	}
	
	return CXTPTreeCtrl::PreTranslateMessage(pMsg);
}

int CTabTreeFile::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTPTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list used by the tree control.
	if (!m_imageList.Create(IDB_IL_FILE, 16, 1, RGB(0x00,0x80,0x80)))
		return -1;
	
	// Get a pointer to the tree control, and set its imagelist.
	SetImageList(&m_imageList, TVSIL_NORMAL);

	// Initialize the view.
	UpdateTree();
	
	return 0;
}

void CTabTreeFile::UpdateTree()
{
	// add the parent item, make it bold
	HTREEITEM htiParent = InsertItem(_T("Solution 'XtremeDemo': 1 project(s)"));
	HTREEITEM htiChild; // child item
	
	htiChild = InsertItem (_T("XtremeDemo Files"), 1, 1, htiParent);
	SetItemState (htiChild, TVIS_BOLD, TVIS_BOLD);
	
	// add the children of the parent item
	HTREEITEM hti = InsertItem(_T("Source Files"), 2, 3, htiChild);
	InsertItem(_T("ChildFrm.cpp"), 4, 4, hti);
	InsertItem(_T("MainFrm.cpp"), 4, 4, hti);
	InsertItem(_T("StdAfx.cpp"), 4, 4, hti);
	InsertItem(_T("XtremeDemo.cpp"), 4, 4, hti);
	InsertItem(_T("XtremeDemo.rc"), 4, 4, hti);
	InsertItem(_T("XtremeDemoDoc.cpp"), 4, 4, hti);
	InsertItem(_T("XtremeDemoView.cpp"), 4, 4, hti);
	Expand(hti, TVE_EXPAND);
	
	hti = InsertItem(_T("Header Files"), 2, 3, htiChild);
	InsertItem(_T("ChildFrm.h"), 5, 5, hti);
	InsertItem(_T("MainFrm.h"), 5, 5, hti);
	InsertItem(_T("Resource.rc"), 5, 5, hti);
	InsertItem(_T("StdAfx.h"), 5, 5, hti);
	InsertItem(_T("XtremeDemo.h"), 5, 5, hti);
	InsertItem(_T("XtremeDemoDoc.h"), 5, 5, hti);
	InsertItem(_T("XtremeDemoView.h"), 5, 5, hti);
	
	hti = InsertItem(_T("Resource Files"), 2, 3, htiChild);
	InsertItem(_T("Toolbar.bmp"), 5, 5, hti);
	InsertItem(_T("XtremeDemo.ico"), 5, 5, hti);
	InsertItem(_T("XtremeDemo.rc2"), 5, 5, hti);
	InsertItem(_T("XtremeDemoDoc.ico"), 5, 5, hti);
	
	InsertItem(_T("ReadMe.txt"), 5, 5, htiChild);
	InsertItem(_T("External Dependencies"), 2, 3, htiChild);
	
	Expand (htiParent, TVE_EXPAND);
	Expand (htiChild, TVE_EXPAND);
}
