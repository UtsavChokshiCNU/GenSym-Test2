// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__72A9A25F_8390_49F0_B1B8_EB15D2C4BFC4__INCLUDED_)
#define AFX_MAINFRM_H__72A9A25F_8390_49F0_B1B8_EB15D2C4BFC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDatePickerDlg : public CDialogBar
{
public:
	CXTPDatePickerControl& GetDatePicker() { return m_wndDatePicker; }
protected:
	CXTPDatePickerControl  m_wndDatePicker;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnInitDialog();
};

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

	CDatePickerDlg m_dlgDatePicker;	
	CXTPDatePickerControl& GetDatePicker() { return m_dlgDatePicker.GetDatePicker(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__72A9A25F_8390_49F0_B1B8_EB15D2C4BFC4__INCLUDED_)
