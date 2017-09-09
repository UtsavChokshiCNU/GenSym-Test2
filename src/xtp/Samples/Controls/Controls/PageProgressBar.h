#if !defined(AFX_PAGEPROGRESSBAR_H__7C5080C5_FE0F_4DDD_A696_CC1DE2B82D90__INCLUDED_)
#define AFX_PAGEPROGRESSBAR_H__7C5080C5_FE0F_4DDD_A696_CC1DE2B82D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageProgressBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar dialog

class CPageProgressBar : public CXTPResizePropertyPage
{
// Construction
public:
	CPageProgressBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageProgressBar)
	enum { IDD = IDD_PAGE_PROGRESSBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CXTPProgressCtrl m_wndProgressBar[7];
	BOOL m_bPause;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageProgressBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageProgressBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonStep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPROGRESSBAR_H__7C5080C5_FE0F_4DDD_A696_CC1DE2B82D90__INCLUDED_)
