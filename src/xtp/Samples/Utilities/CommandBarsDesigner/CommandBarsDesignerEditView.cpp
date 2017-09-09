// CommandBarsDesignerEditView.cpp : implementation file
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
#include "commandbarsdesigner.h"
#include "CommandBarsDesignerEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandBarsDesignerEditView

IMPLEMENT_DYNCREATE(CCommandBarsDesignerEditView, CEditViewBase)

CCommandBarsDesignerEditView::CCommandBarsDesignerEditView()
{

	
	m_hInstance = LoadLibrary(_T("RICHED20.DLL"));
	
	if (m_hInstance)
	{
#ifdef _UNICODE
		m_strClass = _T("RichEdit20W");
#else
		m_strClass = _T("RichEdit20A");
#endif
	}
}

CCommandBarsDesignerEditView::~CCommandBarsDesignerEditView()
{
}


BEGIN_MESSAGE_MAP(CCommandBarsDesignerEditView, CEditViewBase)
	//{{AFX_MSG_MAP(CCommandBarsDesignerEditView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandBarsDesignerEditView drawing

void CCommandBarsDesignerEditView::OnDraw(CDC*)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCommandBarsDesignerEditView diagnostics

#ifdef _DEBUG
void CCommandBarsDesignerEditView::AssertValid() const
{
	CEditViewBase::AssertValid();
}

void CCommandBarsDesignerEditView::Dump(CDumpContext& dc) const
{
	CEditViewBase::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommandBarsDesignerEditView message handlers

void CCommandBarsDesignerEditView::OnInitialUpdate()
{
	CEditViewBase::OnInitialUpdate();

	if (m_fnt.GetSafeHandle() == 0)
	{
		NONCLIENTMETRICS ncm;
		::ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
		ncm.cbSize = sizeof(NONCLIENTMETRICS);

		VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));

		STRCPY_S(ncm.lfMenuFont.lfFaceName, LF_FACESIZE, _T("Courier"));

		m_fnt.CreateFontIndirect(&ncm.lfMenuFont);
		SetFont(&m_fnt);
	}

	if (m_hInstance)
	{
		SendMessage(EM_SETTEXTMODE, TM_PLAINTEXT | TM_MULTILEVELUNDO);
		SendMessage(EM_SETEVENTMASK, 0, ENM_CHANGE);
		SendMessage(EM_EXLIMITTEXT, 0, 0xffffff); // 16 MB
	}

	
	SetTabStops(12);
}
