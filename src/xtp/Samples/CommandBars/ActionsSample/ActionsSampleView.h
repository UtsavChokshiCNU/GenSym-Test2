// ActionsSampleView.h : interface of the CActionsSampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTIONSSAMPLEVIEW_H__FA7DE792_002D_4C8A_BA13_F55F88209C7B__INCLUDED_)
#define AFX_ACTIONSSAMPLEVIEW_H__FA7DE792_002D_4C8A_BA13_F55F88209C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CActionsSampleCntrItem;

class CActionsSampleView : public CRichEditView
{
protected: // create from serialization only
	CActionsSampleView();
	DECLARE_DYNCREATE(CActionsSampleView)

// Attributes
public:
	CActionsSampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionsSampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CActionsSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CActionsSampleView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

	void OnCharUnderline();
	void OnCharItalic();
	void OnCharBold();

	void UpdateActionsState();
};

#ifndef _DEBUG  // debug version in ActionsSampleView.cpp
inline CActionsSampleDoc* CActionsSampleView::GetDocument()
   { return (CActionsSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIONSSAMPLEVIEW_H__FA7DE792_002D_4C8A_BA13_F55F88209C7B__INCLUDED_)
