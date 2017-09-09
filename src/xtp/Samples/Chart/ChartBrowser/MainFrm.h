// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__0FA44040_F396_4A5B_AE95_24E6661057DE__INCLUDED_)
#define AFX_MAINFRM_H__0FA44040_F396_4A5B_AE95_24E6661057DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBaseView;
#include "ExplorerBar.h"
#include "AppCaption.h"


#ifndef _XTP_INCLUDE_TOOLKIT
#define CXTPFrameWnd CFrameWnd
#define CXTPStatusBar CStatusBar
#endif


class CMainFrame : public CXTPFrameWnd
{
	
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

	void SetView(CRuntimeClass* pViewClass);

// Operations
public:

#ifdef _XTP_INCLUDE_TOOLKIT
	CXTPDockingPaneManager m_paneManager;
#endif

	CAppCaption m_wndCaption;

	CBaseView* m_pView;

	CXTPExplorerPane m_wndExplorerBar;


	int m_nAppearance;
	void UpdateAppearance();

	int m_nPalette;
	void UpdatePalette();

	virtual void RecalcLayout(BOOL bNotify = TRUE);

#ifdef _XTP_INCLUDE_TOOLKIT
	void OnInitCommandsPopup(CXTPPopupBar* pCommandBar);
#else
	void OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu);
#endif


	CStringArray m_arrAppearance;
	CStringArray m_arrPalette;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdatePalette(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppearance(CCmdUI* pCmdUI);
	afx_msg void OnPalette(UINT nID);
	afx_msg void OnAppearance(UINT nID);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0FA44040_F396_4A5B_AE95_24E6661057DE__INCLUDED_)
