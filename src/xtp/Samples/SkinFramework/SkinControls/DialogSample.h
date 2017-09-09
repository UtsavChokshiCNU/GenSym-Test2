#if !defined(AFX_DIALOGSAMPLE_H__BC7DF10C_9474_4212_91CA_507CBAEFC744__INCLUDED_)
#define AFX_DIALOGSAMPLE_H__BC7DF10C_9474_4212_91CA_507CBAEFC744__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSample.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogSample dialog

class CDialogSample : public CDialog
{
// Construction
public:
	CDialogSample(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSample)
	enum { IDD = IDD_DIALOG_MUL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSample)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CString m_strStylesPath;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSample)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSAMPLE_H__BC7DF10C_9474_4212_91CA_507CBAEFC744__INCLUDED_)
