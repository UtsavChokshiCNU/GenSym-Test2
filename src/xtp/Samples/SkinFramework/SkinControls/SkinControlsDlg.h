// SkinControlsDlg.h : header file
//

#if !defined(AFX_SKINCONTROLSDLG_H__1B411B9D_1D57_4E6B_854C_0B07916080A9__INCLUDED_)
#define AFX_SKINCONTROLSDLG_H__1B411B9D_1D57_4E6B_854C_0B07916080A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSkinControlsDlg dialog

class CSkinControlsDlg : public CDialog
{
// Construction
public:
	CSkinControlsDlg(CWnd* pParent = NULL);	// standard constructor
	~CSkinControlsDlg();

// Dialog Data
	//{{AFX_DATA(CSkinControlsDlg)
	enum { IDD = IDD_SKINCONTROLS_DIALOG };
	CSliderCtrl	m_wndSlider;
	CTabCtrl	m_wndTab;
	CProgressCtrl	m_wndProgress;
	CListCtrl	m_wndListCtrl;
	CListBox	m_wndListBox;
	CScrollBar	m_wndScrollBar;
	CButton	m_wndCheckBox;
	CButton	m_wndRadio;
	CButton	m_wndButton;
	int		m_nHorizAlign;
	int		m_nVertAlign;
	BOOL	m_bEnabled;
	int		m_nVisualTheme;
	BOOL	m_bRightButton;
	int		m_nScrollPos;
	BOOL	m_bMultiLine;
	CToolBarCtrl  m_wndToolBar;
	//}}AFX_DATA
	CImageList m_ilToolbarTools;

	CString m_strStylesPath;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinControlsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void ModifyButtonsStyle(DWORD dwRemove, DWORD dwAdd);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSkinControlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelChangeComboHorizontal();
	afx_msg void OnSelChangeComboVertical();
	afx_msg void OnCheckEnabled();
	afx_msg void OnRadioVisualTheme();
	afx_msg void OnCheckRightbutton();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckMultiline();
	afx_msg void OnFilters();
	afx_msg void OnToolbarDropDown(NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnButtonMult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINCONTROLSDLG_H__1B411B9D_1D57_4E6B_854C_0B07916080A9__INCLUDED_)
