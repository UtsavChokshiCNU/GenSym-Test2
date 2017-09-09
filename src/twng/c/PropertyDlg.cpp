// PropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyDlg.h"

BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
END_MESSAGE_MAP()

CPropertyDlg::CPropertyDlg(CWnd* pParent) : 
	CDialog(IDD_PROPDLG, pParent)
{
}


void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDITID, m_id);
    DDX_Text(pDX, IDC_EDITVAL, m_description);
}

