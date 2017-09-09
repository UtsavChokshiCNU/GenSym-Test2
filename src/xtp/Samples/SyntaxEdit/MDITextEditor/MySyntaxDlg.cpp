// MySyntaxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDITextEditor.h"
#include "MySyntaxDlg.h"


// CMySyntaxDlg dialog

IMPLEMENT_DYNAMIC(CMySyntaxDlg, CDialog)

CMySyntaxDlg::CMySyntaxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySyntaxDlg::IDD, pParent)
{

}

CMySyntaxDlg::~CMySyntaxDlg()
{
}

void CMySyntaxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SYNTAX_EDIT, m_edit);
}


BEGIN_MESSAGE_MAP(CMySyntaxDlg, CDialog)
END_MESSAGE_MAP()

void CMySyntaxDlg::OnOK()
{
	 m_edit.GetWindowText(m_Syntax);

	CDialog::OnOK();
}

BOOL CMySyntaxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edit.SetWindowText(m_Syntax);

	return TRUE;
}
