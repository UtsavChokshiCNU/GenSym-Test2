#if !defined(AFX_BACKSTAGEPAGESAVEEMAIL_H__2D794247_017D_43DD_9E00_F8759BCA7BE1__INCLUDED_)
#define AFX_BACKSTAGEPAGESAVEEMAIL_H__2D794247_017D_43DD_9E00_F8759BCA7BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackstagePageSaveEmail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageSaveEmail dialog

class CBackstagePageSaveEmail : public CXTPRibbonBackstagePage
{
	DECLARE_DYNCREATE(CBackstagePageSaveEmail)

// Construction
public:
	CBackstagePageSaveEmail();
	~CBackstagePageSaveEmail();

// Dialog Data
	//{{AFX_DATA(CBackstagePageSaveEmail)
	enum { IDD = IDD_BACKSTAGEPAGE_SAVE_EMAIL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBackstagePageSaveEmail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CXTPRibbonBackstageLabel m_lblCaption;
	CXTPRibbonBackstageSeparator m_lblSeparator;
	CXTPRibbonBackstageButton m_btnSend;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBackstagePageSaveEmail)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGESAVEEMAIL_H__2D794247_017D_43DD_9E00_F8759BCA7BE1__INCLUDED_)
