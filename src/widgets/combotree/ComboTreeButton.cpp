// ComboTreeButton.cpp : implementation file
//

#include "stdafx.h"
#include "ComboTreeButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ComboTreeButton

ComboTreeButton::ComboTreeButton()
{
}

ComboTreeButton::~ComboTreeButton()
{
}


BEGIN_MESSAGE_MAP(ComboTreeButton, CButton)
	//{{AFX_MSG_MAP(ComboTreeButton)
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ComboTreeButton message handlers

void ComboTreeButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	UINT style = DFCS_SCROLLDOWN;
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		style |= DFCS_PUSHED;
	}
	if (lpDrawItemStruct->itemState & ODS_DISABLED)
	{

		style |= DFCS_INACTIVE;
	}


	DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_SCROLL, style);
}


UINT ComboTreeButton::OnGetDlgCode() 
{
	UINT result = CButton::OnGetDlgCode();
	result |= DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS ;
	return result;

}
