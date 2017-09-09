#if !defined(AFX_EXPLORERBAR_H__919C6B0D_16C4_44D4_B1EF_385B0D2421AF__INCLUDED_)
#define AFX_EXPLORERBAR_H__919C6B0D_16C4_44D4_B1EF_385B0D2421AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExplorerBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXTPExplorerPane window

#ifndef _XTP_INCLUDE_TOOLKIT
#define CXTPTaskPanel CTreeCtrl
#endif


class CExplorerBar : public CXTPTaskPanel
{
// Construction
public:
	CExplorerBar();

// Attributes
public:

// Operations
public:
	void Create(CWnd* pWndParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExplorerBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExplorerBar();


	void OnItemClick(UINT nID);

	void* AddGroup(LPCTSTR lpszGroup);
	void AddLinkItem(void* pGroup, UINT nID, LPCTSTR lpszCaption);

	// Generated message map functions
protected:
	//{{AFX_MSG(CExplorerBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CXTPExplorerPane : public CControlBar
{
public:
	CXTPExplorerPane();
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppCaption)
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	//}}AFX_VIRTUAL
	
	void Create(CWnd* pWndParent);
	CSize CalcFixedLayout(BOOL, BOOL /*bHorz*/);
	
	void OnSize(UINT nType, int cx, int cy);

	LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);
	void OnTreeSelChanged(NMHDR*, LRESULT* pResult);

	CExplorerBar m_wndExplorerBar;
	
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLORERBAR_H__919C6B0D_16C4_44D4_B1EF_385B0D2421AF__INCLUDED_)
