#if !defined(AFX_TABRESIZABLEPAGE_H__CC4109FF_5822_463E_9084_1BAF61757F22__INCLUDED_)
#define AFX_TABRESIZABLEPAGE_H__CC4109FF_5822_463E_9084_1BAF61757F22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabResizablePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabResizablePage dialog

class CTabResizablePage : public CXTPPropertyPage
{
// Construction
public:
	CTabResizablePage();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabResizablePage)
	enum { IDD = IDD_PAGE_RESIZABLE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabResizablePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CXTPResizeGroupBox m_group1;
	CXTPResizeGroupBox m_group2;

	// Generated message map functions
	//{{AFX_MSG(CTabResizablePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABRESIZABLEPAGE_H__CC4109FF_5822_463E_9084_1BAF61757F22__INCLUDED_)
