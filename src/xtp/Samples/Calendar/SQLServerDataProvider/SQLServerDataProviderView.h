// SQLServerDataProviderView.h : interface of the CSQLServerDataProviderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLSERVERDATAPROVIDERVIEW_H__8FE5799D_0E4B_494B_8CE9_6049C38FA1CA__INCLUDED_)
#define AFX_SQLSERVERDATAPROVIDERVIEW_H__8FE5799D_0E4B_494B_8CE9_6049C38FA1CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSQLServerDataProviderView : public CXTPCalendarControlView
{
protected: // create from serialization only
	CSQLServerDataProviderView();
	DECLARE_DYNCREATE(CSQLServerDataProviderView)

// Attributes
public:
	CSQLServerDataProviderDoc* GetDocument();

	CXTPCalendarController m_calController;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLServerDataProviderView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

	afx_msg void OnCalendarViewDay();
	afx_msg void OnCalendarViewWorkWeek();
	afx_msg void OnCalendarViewWeek();
	afx_msg void OnCalendarViewMonth();
	afx_msg void OnUpdateCalendarViewDay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalendarViewWorkWeek(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalendarViewWeek(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalendarViewMonth(CCmdUI* pCmdUI);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSQLServerDataProviderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSQLServerDataProviderView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SQLServerDataProviderView.cpp
inline CSQLServerDataProviderDoc* CSQLServerDataProviderView::GetDocument()
   { return (CSQLServerDataProviderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLSERVERDATAPROVIDERVIEW_H__8FE5799D_0E4B_494B_8CE9_6049C38FA1CA__INCLUDED_)
