#if !defined(AFX_PAGEGENERAL_H__41D37C17_F52E_4A52_880E_4DC50516CB3B__INCLUDED_)
#define AFX_PAGEGENERAL_H__41D37C17_F52E_4A52_880E_4DC50516CB3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageGeneral.h : header file
//
#include "resource.h"
#include "OptionsPage.h"
/////////////////////////////////////////////////////////////////////////////
// CPageGeneral dialog

class CPageGeneral : public COptionsPage
{
	DECLARE_DYNCREATE(CPageGeneral)

// Construction
public:
	
	CPageGeneral();
	~CPageGeneral();

// Dialog Data
	//{{AFX_DATA(CPageGeneral)
	enum { IDD = IDD_PAGE_GENERAL };
	CComboBox	m_cmbUrls;
	BOOL	m_bConfirmCloseAll;
	BOOL	m_bConfirmExit;
	BOOL	m_bOneInstance;
	int		m_nDocking;
	int		m_nStartup;
	BOOL	m_bRestoreWindowPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();


	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageGeneral)
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonDeleteall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEGENERAL_H__41D37C17_F52E_4A52_880E_4DC50516CB3B__INCLUDED_)
