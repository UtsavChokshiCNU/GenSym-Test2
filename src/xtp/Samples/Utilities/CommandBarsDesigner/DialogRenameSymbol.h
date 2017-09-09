#if !defined(AFX_DIALOGRENAMESYMBOL_H__1032885F_774C_49CB_9807_5CD96F77384B__INCLUDED_)
#define AFX_DIALOGRENAMESYMBOL_H__1032885F_774C_49CB_9807_5CD96F77384B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogRenameSymbol.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogRenameSymbol dialog

class CDialogRenameSymbol : public CDialog
{
// Construction
public:
	CDialogRenameSymbol(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogRenameSymbol)
	enum { IDD = IDD_DIALOG_RESOURCE_RENAME };
	CString m_strName;
	int m_nValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogRenameSymbol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogRenameSymbol)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGRENAMESYMBOL_H__1032885F_774C_49CB_9807_5CD96F77384B__INCLUDED_)
