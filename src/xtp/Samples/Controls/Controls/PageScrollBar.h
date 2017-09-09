#if !defined(AFX_PAGESCROLLBAR_H__4999D1BF_9F82_4C81_B6EC_9F9215241CF9__INCLUDED_)
#define AFX_PAGESCROLLBAR_H__4999D1BF_9F82_4C81_B6EC_9F9215241CF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageScrollBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageScrollBar dialog

class CPageScrollBar : public CXTPResizePropertyPage
{
	DECLARE_DYNCREATE(CPageScrollBar)

// Construction
public:
	CPageScrollBar();
	~CPageScrollBar();

// Dialog Data
	//{{AFX_DATA(CPageScrollBar)
	enum { IDD = IDD_PAGE_SCROLLBAR };
	BOOL	m_bEnabled;
	//}}AFX_DATA
	CXTPScrollBar	m_wndScrollBar[7];


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageScrollBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageScrollBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckEnabled();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESCROLLBAR_H__4999D1BF_9F82_4C81_B6EC_9F9215241CF9__INCLUDED_)
