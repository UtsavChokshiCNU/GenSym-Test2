#if !defined(AFX_TABLISTPAGE_H__C1BEF74B_D4D1_4964_B53E_A03D4D79CB42__INCLUDED_)
#define AFX_TABLISTPAGE_H__C1BEF74B_D4D1_4964_B53E_A03D4D79CB42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabListPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabListPage dialog

class CTabListPage : public CXTPPropertyPage
{
	DECLARE_DYNCREATE(CTabListPage)

// Construction
public:
	CTabListPage();
	~CTabListPage();

// Dialog Data
	//{{AFX_DATA(CTabListPage)
	enum { IDD = IDD_PAGE_LISTCONTROL };
	BOOL	m_bFlatPage;
	int		m_nStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTabListPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabListPage)
	afx_msg void OnCheckFlat();
	afx_msg void OnSelchangeComboStyle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLISTPAGE_H__C1BEF74B_D4D1_4964_B53E_A03D4D79CB42__INCLUDED_)
