// ShortcutPaneJournal.cpp: implementation of the CShortcutPaneJournal class.
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
#include "shortcutbar.h"
#include "ShortcutPaneJournal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShortcutPaneJournal::CShortcutPaneJournal()
{
	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR32, 1, 1);

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_JOURNAL);
	ASSERT(hIcon);

	m_ilTreeIcons.Add (hIcon);

}

CShortcutPaneJournal::~CShortcutPaneJournal()
{

}

BOOL CShortcutPaneJournal::Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent)
{
	if (!CXTPShortcutBarPane::Create(lpszCaption, pParent))
		return FALSE;

	VERIFY(m_wndTreeJournal.Create(WS_VISIBLE|TVS_HASBUTTONS|TVS_LINESATROOT, CXTPEmptyRect(), this, 0));

	m_wndTreeJournal.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);

	m_wndTreeJournal.InsertItem (_T("Journal"), 0, 0);

	AddItem(_T("My Journal"), &m_wndTreeJournal, 115);


	return TRUE;
}


void CShortcutPaneJournal::SetFlatStyle(BOOL bFlatStyle)
{
	CXTPShortcutBarPane::SetFlatStyle(bFlatStyle);
	ShowCaption(!bFlatStyle);
	
	COLORREF clrBackground = GetBackgroundColor();
	COLORREF clrTextColor = GetTextColor();
		
	m_wndTreeJournal.SendMessage(TVM_SETBKCOLOR, 0, clrBackground); 
	m_wndTreeJournal.SendMessage(TVM_SETTEXTCOLOR, 0, clrTextColor); 
	
	RecalcLayout();
}
