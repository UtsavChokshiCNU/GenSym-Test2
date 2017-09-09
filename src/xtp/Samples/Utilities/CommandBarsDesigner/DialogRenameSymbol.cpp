// DialogRenameSymbol.cpp : implementation file
//

#include "stdafx.h"
#include "commandbarsdesigner.h"
#include "DialogRenameSymbol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRenameSymbol dialog


CDialogRenameSymbol::CDialogRenameSymbol(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRenameSymbol::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRenameSymbol)
	m_strName = _T("");
	m_nValue = 0;
	//}}AFX_DATA_INIT
}


void CDialogRenameSymbol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRenameSymbol)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_nValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRenameSymbol, CDialog)
	//{{AFX_MSG_MAP(CDialogRenameSymbol)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRenameSymbol message handlers
