#if !defined(AFX_DIALOGTIMELINEPROPERTIES_H__09F62D04_C136_4376_8B7D_C468F3A9F9DE__INCLUDED_)
#define AFX_DIALOGTIMELINEPROPERTIES_H__09F62D04_C136_4376_8B7D_C468F3A9F9DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogTimeLineProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogTimeLineProperties dialog

class CDialogTimeLineProperties : public CDialog
{
// Construction
public:
	CDialogTimeLineProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogTimeLineProperties)
	enum { IDD = IDD_DIALOG_PROPERTIES };
	int		m_nMin;
	int		m_nMax;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogTimeLineProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogTimeLineProperties)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTIMELINEPROPERTIES_H__09F62D04_C136_4376_8B7D_C468F3A9F9DE__INCLUDED_)
