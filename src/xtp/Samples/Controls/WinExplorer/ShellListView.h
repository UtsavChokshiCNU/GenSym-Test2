#if !defined(AFX_SHELLLISTVIEW_H__218BC459_82F2_4781_889B_72318030490E__INCLUDED_)
#define AFX_SHELLLISTVIEW_H__218BC459_82F2_4781_889B_72318030490E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ShellListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShellListView view

class CShellListView : public CXTPShellListView
{
protected:
	CShellListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CShellListView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	void OnInitialUpdate();

// Implementation
protected:
	virtual ~CShellListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CShellListView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLLISTVIEW_H__218BC459_82F2_4781_889B_72318030490E__INCLUDED_)
