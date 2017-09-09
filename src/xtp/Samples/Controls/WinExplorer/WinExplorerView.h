// WinExplorerView.h : interface of the CWinExplorerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINEXPLORERVIEW_H__EC639D51_282D_4982_845E_3EACE9AC01FB__INCLUDED_)
#define AFX_WINEXPLORERVIEW_H__EC639D51_282D_4982_845E_3EACE9AC01FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWinExplorerView : public CView
{
protected: // create from serialization only
	CWinExplorerView();
	DECLARE_DYNCREATE(CWinExplorerView)

// Attributes
public:
	CWinExplorerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinExplorerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinExplorerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WinExplorerView.cpp
inline CWinExplorerDoc* CWinExplorerView::GetDocument()
   { return (CWinExplorerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINEXPLORERVIEW_H__EC639D51_282D_4982_845E_3EACE9AC01FB__INCLUDED_)
