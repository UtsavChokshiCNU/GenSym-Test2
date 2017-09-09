#if !defined(AFX_UIFRAME_H__88B05ED1_5789_4D06_B733_2B4CB9B7A899__INCLUDED_)
#define AFX_UIFRAME_H__88B05ED1_5789_4D06_B733_2B4CB9B7A899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UIFrame.h : header file
//

#include "UITaskPanel.h"

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CUIFrame frame



class CUIFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CUIFrame)

public:
	CUIFrame();           // protected constructor used by dynamic creation

	CChildView m_wndView;
	CUITaskPanel m_wndTaskPanel;
	CXTPStatusBar  m_wndStatusBar;

	CXTPSplitterWndEx m_wndSplitter;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIFrame)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CUIFrame();

	// Generated message map functions
	//{{AFX_MSG(CUIFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnClose();
	LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	void SetTheme(XTPTaskPanelPaintTheme taskPanelTheme);
	afx_msg void OnThemeOffice2000();
	afx_msg void OnUpdateThemeOffice2000(CCmdUI* pCmdUI);
	afx_msg void OnThemeOffice2003();
	afx_msg void OnUpdateThemeOffice2003(CCmdUI* pCmdUI);
	afx_msg void OnThemeNativewinxp();
	afx_msg void OnUpdateThemeNativewinxp(CCmdUI* pCmdUI);
	afx_msg void OnThemeOffice2000plain();
	afx_msg void OnUpdateThemeOffice2000plain(CCmdUI* pCmdUI);
	afx_msg void OnThemeOfficexpplain();
	afx_msg void OnUpdateThemeOfficexpplain(CCmdUI* pCmdUI);
	afx_msg void OnThemeOffice2003plain();
	afx_msg void OnUpdateThemeOffice2003plain(CCmdUI* pCmdUI);
	afx_msg void OnThemeNativewinxpplain();
	afx_msg void OnUpdateThemeNativewinxpplain(CCmdUI* pCmdUI);
	afx_msg void OnTaskpanelAnimation();
	afx_msg void OnUpdateTaskpanelAnimation(CCmdUI* pCmdUI);

	BOOL CreateTaskPanel();
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UIFRAME_H__88B05ED1_5789_4D06_B733_2B4CB9B7A899__INCLUDED_)
