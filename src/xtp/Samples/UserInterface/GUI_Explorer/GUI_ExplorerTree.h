// GUI_ExplorerTree.h : header file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUI_EXPLORERTREE_H__B01A7EC3_36F2_4245_BC2F_7F42421914F0__INCLUDED_)
#define AFX_GUI_EXPLORERTREE_H__B01A7EC3_36F2_4245_BC2F_7F42421914F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGUI_ExplorerTree view

class CGUI_ExplorerTree : public CView
{
protected:
	CGUI_ExplorerTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGUI_ExplorerTree)

// Attributes
public:
	void SelectParentItem();

// Operations
public:
	CXTPCaption      m_wndCaption;
	CXTPShellTreeCtrl    m_shellTree;

	inline CXTPShellTree& GetTreeCtrl() {
		return m_shellTree;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUI_ExplorerTree)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGUI_ExplorerTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	int GetHeaderHeight() const;

	//{{AFX_MSG(CGUI_ExplorerTree)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnCaptionButton();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_EXPLORERTREE_H__B01A7EC3_36F2_4245_BC2F_7F42421914F0__INCLUDED_)
