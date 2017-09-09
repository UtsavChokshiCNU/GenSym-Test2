// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__370FD79D_FD3D_4788_8A51_8E4A873FEA51__INCLUDED_)
#define AFX_MAINFRM_H__370FD79D_FD3D_4788_8A51_8E4A873FEA51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CShellTreeView;
class CShellListView;

#define CMainFrameBase CXTPFrameWnd

class CAddressComboBox : public CComboBoxEx
{
	BOOL PreTranslateMessage(MSG* pMsg);
};

class CMainFrame : public CMainFrameBase
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void UpdateTheme();

	CXTPStatusBar   m_wndStatusBar;
    CXTPSplitterWndEx   m_wndSplitter;
    CAddressComboBox   m_wndAddressCombo;
    CXTPWindowPos       m_wndPosition;
    CShellTreeView*    m_pTreeView;
    CShellListView*    m_pListView;
    CXTPRegistryManager m_regMgr;
    BOOL               m_bOfficeTheme;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	afx_msg void OnViews();
	afx_msg void OnFolders();
	afx_msg void OnUpdateFolders(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnClose();
	afx_msg void OnCustomize();
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl); // Called by the XTK to create the controls on the CommandBars
	afx_msg void OnViewStyle(UINT nCommandID);
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnAddressBarEnter();
	afx_msg void OnSelEndOkAddressBar();
	DECLARE_MESSAGE_MAP()

	friend class CShellTreeView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__370FD79D_FD3D_4788_8A51_8E4A873FEA51__INCLUDED_)
