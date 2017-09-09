#if !defined(AFX_TABLONGPAGE_H__0536BF37_1F4B_457C_BD0D_42C581230099__INCLUDED_)
#define AFX_TABLONGPAGE_H__0536BF37_1F4B_457C_BD0D_42C581230099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabLongPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabLongPage dialog

class CTabLongPage : public CXTPPropertyPage
{
	DECLARE_DYNCREATE(CTabLongPage)

// Construction
public:
	CTabLongPage();
	~CTabLongPage();

// Dialog Data
	//{{AFX_DATA(CTabLongPage)
	enum { IDD = IDD_PAGE_LONG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTabLongPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CXTPPropertyPageStaticCaption m_captions[5];

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabLongPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLONGPAGE_H__0536BF37_1F4B_457C_BD0D_42C581230099__INCLUDED_)
