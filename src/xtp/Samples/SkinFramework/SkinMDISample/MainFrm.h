// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__784BE6B5_03A9_40F9_8DB7_58DF56AD001D__INCLUDED_)
#define AFX_MAINFRM_H__784BE6B5_03A9_40F9_8DB7_58DF56AD001D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CXTPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CSkinPropertySheet m_dlgThemes;

// Operations
public:
	void OnSkinChanged();
	void RedrawFrame(CWnd* pWnd);

	void OnShemaChanged(int nSchema);

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

	void SetTheme(int nTheme);


public:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CToolBar m_wndToolBar;

	void ShowThemesDialog();
	static CString GetStylesPath();

	CXTPTabClientWnd m_MTIClientWnd;	

	CXTPDockingPaneManager m_paneManager;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose(); 
	afx_msg void OnViewThemeDialog();
	afx_msg void OnViewTheme();
	afx_msg void OnUpdateViewTheme(CCmdUI* pCmdUI);
	//}}AFX_MSG
	
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnCustomize();
	afx_msg void OnViewThemePopup(UINT nCommand);
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);

	int m_nTheme;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__784BE6B5_03A9_40F9_8DB7_58DF56AD001D__INCLUDED_)
