#pragma once
#include "afxwin.h"


// CMySyntaxDlg dialog

class CMySyntaxDlg : public CDialog
{
	DECLARE_DYNAMIC(CMySyntaxDlg)

public:
	CMySyntaxDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMySyntaxDlg();

	CString m_Syntax;

// Dialog Data
	enum { IDD = IDD_SYNTAX_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CEdit m_edit;
};
