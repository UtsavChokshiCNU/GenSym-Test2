#if !defined(AFX_BACKSTAGEPAGERECENT_H__10737206_E208_4FEA_95FE_3B34A7809536__INCLUDED_)
#define AFX_BACKSTAGEPAGERECENT_H__10737206_E208_4FEA_95FE_3B34A7809536__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackstagePageRecent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackstagePageRecent dialog

class CBackstagePageRecent : public CXTPRibbonBackstagePage
{
	DECLARE_DYNCREATE(CBackstagePageRecent)

// Construction
public:
	CBackstagePageRecent();
	~CBackstagePageRecent();

// Dialog Data
	//{{AFX_DATA(CBackstagePageRecent)
	enum { IDD = IDD_BACKSTAGEPAGE_RECENT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBackstagePageRecent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	BOOL OnSetActive();


	CXTPRibbonBackstageSeparator m_lblSeparator1;
	CXTPRibbonBackstageLabel m_lblRecent;

	CXTPRecentFileListBox m_wndList;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBackstagePageRecent)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnRecentFileListClick();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGERECENT_H__10737206_E208_4FEA_95FE_3B34A7809536__INCLUDED_)
