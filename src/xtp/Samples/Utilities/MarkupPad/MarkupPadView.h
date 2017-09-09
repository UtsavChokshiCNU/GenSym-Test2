// MarkupPadView.h : interface of the CMarkupPadView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARKUPPADVIEW_H__8ABEFFFC_AE65_4566_85AD_5931D2DF5F61__INCLUDED_)
#define AFX_MARKUPPADVIEW_H__8ABEFFFC_AE65_4566_85AD_5931D2DF5F61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMarkupPadView : public CView, public CXTPMarkupContext
{
protected: // create from serialization only
	CMarkupPadView();
	DECLARE_DYNCREATE(CMarkupPadView)

// Attributes
public:
	CMarkupPadDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPadView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);

	void OnRunMouseLeftButtonUp(CXTPMarkupObject* pSender, CXTPMarkupMouseButtonEventArgs* pArgs);
	void OnBorderMouseLeftButtonUp(CXTPMarkupObject* pSender, CXTPMarkupMouseButtonEventArgs* pArgs);
	void OnTextBlockMouseLeftButtonUp(CXTPMarkupObject* pSender, CXTPMarkupMouseButtonEventArgs* pArgs);

	void OnMakeShapeRed(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseEventArgs* pArgs);
	void OnMakeShapeGreen(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseEventArgs* pArgs);
	void OnMakeTextBold(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseEventArgs* pArgs);
	void OnMakeTextNormal(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseEventArgs* pArgs);
	void OnMakeTextYellow(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/);
	void OnMakeTextGreen(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/);
	void OnHideColumn4(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/);
	void OnMoveColumn3(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/);
	void OnShowColumn4(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/);
	void OnSetText1(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/);
	void OnSetText2(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/);
	void ToggleNextControl(CXTPMarkupObject* pSender, CXTPMarkupMouseButtonEventArgs* /*pArgs*/);

	void OnFilePrintPreview();
// Implementation
public:
	virtual ~CMarkupPadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void OnInitialUpdate();

	void CreateCodeMarkup();
	void DrawMarkup(CXTPMarkupDrawingContext* pDC, CRect rc);

public:
	CXTPMarkupUIElement* m_pUIElement;
	BOOL m_bInRender;

// Generated message map functions
protected:
	//{{AFX_MSG(CMarkupPadView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MarkupPadView.cpp
inline CMarkupPadDoc* CMarkupPadView::GetDocument()
   { return (CMarkupPadDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPADVIEW_H__8ABEFFFC_AE65_4566_85AD_5931D2DF5F61__INCLUDED_)
