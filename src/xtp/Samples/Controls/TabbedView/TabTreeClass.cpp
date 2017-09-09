// TabTreeClass.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "TabTreeClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabTreeClass

CTabTreeClass::CTabTreeClass()
{
	m_bMultiSelect = true;
}

CTabTreeClass::~CTabTreeClass()
{
}


BEGIN_MESSAGE_MAP(CTabTreeClass, CXTPTreeCtrl)
	//{{AFX_MSG_MAP(CTabTreeClass)
	ON_WM_NCHITTEST_EX()
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabTreeClass message handlers

BOOL CTabTreeClass::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CXTPTreeCtrl::PreCreateWindow( cs ))
		return FALSE;

	// Set the style for the tree control.
	cs.style |= TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

LRESULT CTabTreeClass::OnNcHitTest(CPoint point) 
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

void CTabTreeClass::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
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

BOOL CTabTreeClass::PreTranslateMessage(MSG* pMsg) 
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

int CTabTreeClass::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTPTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list used by the tree control.
	if (!m_imageList.Create(IDB_IL_CLASS, 16, 1, RGB(0x00,0x80,0x80)))
		return -1;
	
	// Get a pointer to the tree control, and set its imagelist.
	SetImageList(&m_imageList, TVSIL_NORMAL);

	// Initialize the view.
	UpdateTree();
	
	return 0;
}

void CTabTreeClass::UpdateTree()
{
	// Add the parent item
	HTREEITEM htItem = InsertItem(_T("XtremeDemo classes"));
	SetItemState( htItem, TVIS_BOLD, TVIS_BOLD );
	
	// Add children
	HTREEITEM hti = InsertItem(_T("CAboutDlg"), 3, 3, htItem);
	InsertItem(_T("CAboutDlg()"), 4, 4, hti);
	InsertItem(_T("DoDataExchange(CDataExchange *pDX)"), 5, 5, hti);
	
	hti = InsertItem(_T("CChildFrame"), 3, 3, htItem);
	InsertItem(_T("AssertValid()"), 4, 4, hti);
	InsertItem(_T("CChildFrame()"), 4, 4, hti);
	InsertItem(_T("~CChildFrame()"), 4, 4, hti);
	InsertItem(_T("Dump(CDumpContext &dc)"), 4, 4, hti);
	InsertItem(_T("PreCreateWindow(CREATESTRUCT& cs)"), 4, 4, hti);
	
	hti = InsertItem(_T("CMainFrame"), 3, 3, htItem);
	InsertItem(_T("AssertValid()"), 4, 4, hti);
	InsertItem(_T("CMainFrame()"), 4, 4, hti);
	InsertItem(_T("~CMainFrame()"), 4, 4, hti);
	InsertItem(_T("Dump(CDumpContext &dc)"), 4, 4, hti);
	InsertItem(_T("OnCreate(LPCREATESTRUCT lpCreateStruct)"), 5, 5, hti);
	InsertItem(_T("PreCreateWindow(CREATESTRUCT& cs)"), 4, 4, hti);
	InsertItem(_T("m_wndStatusBar"), 7, 7, hti);
	InsertItem(_T("m_wndToolBar"), 7, 7, hti);
	
	hti = InsertItem(_T("CXtremeDemoApp"), 3, 3, htItem);
	InsertItem(_T("CXtremeDemoApp()"), 4, 4, hti);
	InsertItem(_T("InitInstance()"), 4, 4, hti);
	InsertItem(_T("OnAppAbout()"), 4, 4, hti);
	
	hti = InsertItem(_T("CXtremeDemoDoc"), 3, 3, htItem);
	InsertItem(_T("AssertValid()"), 5, 5, hti);
	InsertItem(_T("CXtremeDemoDoc()"), 4, 4, hti);
	InsertItem(_T("~CXtremeDemoDoc()"), 4, 4, hti);
	InsertItem(_T("Dump(CDumpContext &dc)"), 4, 4, hti);
	InsertItem(_T("OnNewDocument()"), 4, 4, hti);
	InsertItem(_T("Serialize(CArchive& ar)"), 4, 4, hti);
	Expand(hti, TVE_EXPAND);
	
	hti = InsertItem(_T("CXtremeDemoView"), 3, 3, htItem);
	InsertItem(_T("AssertValid()"), 4, 4, hti);
	InsertItem(_T("CXtremeDemoView()"), 5, 5, hti);
	InsertItem(_T("~CXtremeDemoView()"), 4, 4, hti);
	InsertItem(_T("Dump(CDumpContext& dc)"), 4, 4, hti);
	InsertItem(_T("GetDocument()"), 4, 4, hti);
	InsertItem(_T("OnBeginPrinting(CDC* pDC, CPrintInfo *pInfo)"), 5, 5, hti);
	InsertItem(_T("OnDraw(CDC *pDC)"), 4, 4, hti);
	InsertItem(_T("OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)"), 5, 5, hti);
	InsertItem(_T("OnPreparePrinting(CPrintInfo *pInfo)"), 5, 5, hti);
	InsertItem(_T("PreCreateWindow(CREATESTRUCT &cs)"), 4, 4, hti);
	
	hti = InsertItem(_T("Globals"), 1, 2, htItem);
	InsertItem(_T("theApp"), 6, 6, hti);
	Expand(hti, TVE_EXPAND);
	
	Expand(htItem, TVE_EXPAND);
}
