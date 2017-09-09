// ShortcutListBoxView.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShortcutList.h"
#include "ShortcutListBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutListBoxView

IMPLEMENT_DYNCREATE(CShortcutListBoxView, CView)

CShortcutListBoxView::CShortcutListBoxView()
{
}

CShortcutListBoxView::~CShortcutListBoxView()
{
}

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

BEGIN_MESSAGE_MAP(CShortcutListBoxView, CView)
	//{{AFX_MSG_MAP(CShortcutListBoxView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_MESSAGE( WM_XTP_SHORTCUTLBOX_NOTIFY,  OnShortcutLBoxNotify )
	//}}AFX_MSG_MAP
	ON_NOTIFY(PGN_SCROLL, IDC_PAGER_CTRL, OnShortcutListScroll)
	ON_NOTIFY(PGN_CALCSIZE, IDC_PAGER_CTRL, OnShortcutListCalcSize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutListBoxView drawing

void CShortcutListBoxView::OnDraw(CDC*)
{
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutListBoxView diagnostics

#ifdef _DEBUG
void CShortcutListBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CShortcutListBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShortcutListBoxView message handlers

void CShortcutListBoxView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if(m_wndPageScroller.GetSafeHwnd()) {
		m_wndPageScroller.MoveWindow(0,0,cx,cy);
	}
}

int CShortcutListBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the pager control.
	if (!m_wndPageScroller.Create(WS_CHILD|WS_VISIBLE|PGS_VERT,
		CRect(0,0,0,0), this, IDC_PAGER_CTRL ))
	{
		TRACE0("Failed to create CShortcutListCtrl...\n");
		return -1;
	}

	// Create the OutlookBar control using m_wndPageScroller as the parent.
	if (!m_wndShortcutListBox.Create( WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect(0,0,0,0), &m_wndPageScroller, IDC_OUTBAR ))
	{
		TRACE0("Failed to create COutlookBar...\n");
		return -1;
	}

	// Set the CWnd object you want messages sent to.
	m_wndShortcutListBox.SetOwner(this);
//  m_wndShortcutListBox.SetColors(RGB(0xff,0xff,0xff), RGB(0x3a,0x6e,0xa5));

	// Add items to the Outlook Bar control.
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_OUTLOOK,  _T("Outlook Today")),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_CONTACTS, _T("Contacts")     ),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_TASKS,    _T("Tasks")        ),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_JOURNAL,  _T("Journal")      ),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_NOTES,    _T("Notes")        ),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_DELETED,  _T("Deleted Items")),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_PUBLIC,   _T("Public")       ),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_DRAFTS,   _T("Drafts")       ),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_OUTBOX,   _T("Outbox")       ),
	m_wndShortcutListBox.AddMenuItem(IDI_ICON_SENT,     _T("Sent")         ),

	// Insert menu items at a specific index.
	m_wndShortcutListBox.InsertMenuItem(1, IDI_ICON_INBOX,    _T("Inbox")   ),
	m_wndShortcutListBox.InsertMenuItem(2, IDI_ICON_CALENDAR, _T("Calendar")),

	// Set the child HWND to COutlookBar, and button size to 15.
	m_wndPageScroller.SetChild(m_wndShortcutListBox.GetSafeHwnd());
	m_wndPageScroller.SetButtonSize(15);

	m_wndShortcutListBox.EnableMenuItem(2, FALSE);

	return 0;
}

void CShortcutListBoxView::OnShortcutListCalcSize(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMPGCALCSIZE* pNMPGCalcSize = (NMPGCALCSIZE*)pNMHDR;

	switch(pNMPGCalcSize->dwFlag)
	{
	case PGF_CALCWIDTH:
		break;

	case PGF_CALCHEIGHT:
		pNMPGCalcSize->iHeight = m_wndShortcutListBox.GetCount()
			*(::GetSystemMetrics(SM_CYICON)*2);
		break;
	}

	*pResult = 0;
}

void CShortcutListBoxView::OnShortcutListScroll(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMPGSCROLL* pNMPGScroll = (NMPGSCROLL*)pNMHDR;
	UNREFERENCED_PARAMETER(pNMPGScroll);

	*pResult = 0;

	// TODO: Handle pager scroll notification
}

LRESULT CShortcutListBoxView::OnShortcutLBoxNotify(WPARAM wParam, LPARAM lParam)
{
	if ((int)wParam == -1) // -1 means no selection
		return 0;

	switch( lParam ) // control id.
	{
	case IDC_OUTBAR:
		{
			// Get the menu item.
			CXTPShortcutListBox::CONTENT_ITEM* pContentItems = m_wndShortcutListBox.GetMenuItem((int)wParam);
			ASSERT(pContentItems);

			AfxMessageBox(pContentItems->m_strText);
		}
		break;
	}
	return 0;
}

BOOL CShortcutListBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
		return FALSE;

	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	// TODO: Add your specialized code here and/or call the base class

	return TRUE;
}
