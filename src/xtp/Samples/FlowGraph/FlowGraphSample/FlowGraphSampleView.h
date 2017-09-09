// FlowGraphSampleView.h : interface of the CFlowGraphSampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOWGRAPHSAMPLEVIEW_H__201D410B_7BFF_4FFB_AAED_7730FD305FB3__INCLUDED_)
#define AFX_FLOWGRAPHSAMPLEVIEW_H__201D410B_7BFF_4FFB_AAED_7730FD305FB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFlowGraphSampleDoc;

#include "FlowGraph/Includes.h"

class CFlowGraphSampleView : public CView
{
protected: // create from serialization only
	CFlowGraphSampleView();
	DECLARE_DYNCREATE(CFlowGraphSampleView)

// Attributes
public:
	CFlowGraphSampleDoc* GetDocument();

	BOOL m_bMetallicTheme;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlowGraphSampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	void OnZoomSliderScroll(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateViewZoom(CCmdUI* pCmdUI);

	
	void OnUpdateHasSelection(CCmdUI* pCmdUI);
	void OnZoomToSelection();
	void OnZoomFitToWindow();

	void CreateDatabaseRelationships();

	void OnQuality(UINT nCmd);
	void OnUpdateQuality(CCmdUI *pCmdUI);


	UINT TrackPopupMenu(CMenu* pMenu, UINT nFlags, int xPos, int yPos);

	int m_nZoom;

// Implementation
public:
	virtual ~CFlowGraphSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


public:

	CXTPFlowGraphControl m_wndControl;

// Generated message map functions
protected:
	//{{AFX_MSG(CFlowGraphSampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEditSelectAll();
	afx_msg void OnFlowgraphShowNodegroupsAlways();
	afx_msg void OnUpdateFlowgraphShowNodegroupsAlways(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnGraphRClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditArrange();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	virtual void OnInitialUpdate();

	afx_msg void OnMetallicTheme();
	afx_msg void OnUpdateMetallicTheme(CCmdUI *pCmdUI);

	afx_msg void OnShowGrid();
	afx_msg void OnUpdateShowGrid(CCmdUI *pCmdUI);

	afx_msg void OnConnectorType(UINT nCmd);
	afx_msg void OnUpdateConnectorType(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in FlowGraphSampleView.cpp
inline CFlowGraphSampleDoc* CFlowGraphSampleView::GetDocument()
   { return (CFlowGraphSampleDoc*)m_pDocument; }
#endif

extern COLORREF clrOfficeColors[];
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOWGRAPHSAMPLEVIEW_H__201D410B_7BFF_4FFB_AAED_7730FD305FB3__INCLUDED_)
