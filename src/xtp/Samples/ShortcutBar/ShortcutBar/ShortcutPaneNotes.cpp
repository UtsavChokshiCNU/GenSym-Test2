// ShortcutPaneNotes.cpp: implementation of the CShortcutPaneNotes class.
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
#include "ShortcutPaneNotes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShortcutPaneNotes::CShortcutPaneNotes()
{
	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR32, 1, 1);

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_NOTES);
	ASSERT(hIcon);

	m_ilTreeIcons.Add (hIcon);

}

CShortcutPaneNotes::~CShortcutPaneNotes()
{

}

BOOL CShortcutPaneNotes::Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent)
{
	if (!CXTPShortcutBarPane::Create(lpszCaption, pParent))
		return FALSE;

	VERIFY(m_wndTreeNotes.Create(WS_VISIBLE|TVS_HASBUTTONS|TVS_LINESATROOT, CXTPEmptyRect(), this, 0));

	m_wndTreeNotes.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);

	m_wndTreeNotes.InsertItem (_T("Notes"), 0, 0);


	AddItem(_T("My Notes"), &m_wndTreeNotes, 115);


	return TRUE;
}


void CShortcutPaneNotes::SetFlatStyle(BOOL bFlatStyle)
{
	CXTPShortcutBarPane::SetFlatStyle(bFlatStyle);
	ShowCaption(!bFlatStyle);
	
	COLORREF clrBackground = GetBackgroundColor();
	COLORREF clrTextColor = GetTextColor();
		
	m_wndTreeNotes.SendMessage(TVM_SETBKCOLOR, 0, clrBackground); 
	m_wndTreeNotes.SendMessage(TVM_SETTEXTCOLOR, 0, clrTextColor); 
	
	RecalcLayout();
}
