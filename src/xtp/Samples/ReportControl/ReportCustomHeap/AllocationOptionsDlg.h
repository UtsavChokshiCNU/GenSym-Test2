#if !defined(AFX_ALLOCATIONOPTIONSDLG_H__3CA0997A_81FF_4409_BDE0_9975C4F16349__INCLUDED_)
#define AFX_ALLOCATIONOPTIONSDLG_H__3CA0997A_81FF_4409_BDE0_9975C4F16349__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AllocationOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAllocationOptionsDlg dialog

class CAllocationOptionsDlg : public CDialog
{
// Construction
public:
	CAllocationOptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAllocationOptionsDlg)
	enum { IDD = IDD_ALLOCATION_OPTIONS_DLG };
	CButton	m_ctrlUseCustomHeap;
	CButton	m_ctrlRowsBatchAlloc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllocationOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAllocationOptionsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALLOCATIONOPTIONSDLG_H__3CA0997A_81FF_4409_BDE0_9975C4F16349__INCLUDED_)
