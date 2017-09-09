#if !defined(AFX_DIALOGMARKERPROPERTIES_H__9BEF803F_B012_44EF_8E87_70703498D858__INCLUDED_)
#define AFX_DIALOGMARKERPROPERTIES_H__9BEF803F_B012_44EF_8E87_70703498D858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogMarkerProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogMarkerProperties dialog

class CDialogMarkerProperties : public CDialog
{
// Construction
public:
	CDialogMarkerProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogMarkerProperties)
	enum { IDD = IDD_DIALOG_MARKER };
	CString	m_strCaption;
	int		m_nPosition;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMarkerProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogMarkerProperties)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMARKERPROPERTIES_H__9BEF803F_B012_44EF_8E87_70703498D858__INCLUDED_)
