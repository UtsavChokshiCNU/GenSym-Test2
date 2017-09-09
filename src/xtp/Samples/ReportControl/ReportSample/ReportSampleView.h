// ReportSampleView.h : interface of the CReportSampleView class
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

#if !defined(_REPORTSAMPLEVIEW_H_)
#define _REPORTSAMPLEVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReportSampleDoc;

class CReportSampleView : public CXTPReportView
{
protected: // create from serialization only
	CReportSampleView();
	DECLARE_DYNCREATE(CReportSampleView)

// Attributes
public:
	CReportSampleDoc* GetDocument();

	CXTPReportSubListControl m_wndSubList;
	CXTPReportFilterEditControl m_wndFilterEdit;

	CImageList m_ilIcons;

	BOOL m_bAutomaticFormating;
	BOOL m_bMultilineSample;

	void LoadReportState();
	void SaveReportState();

	CFrameWnd* m_pTaskFrame;
	CFrameWnd* m_pWndSmoothScroll;
	CFrameWnd* m_pWndMerge;
	CFrameWnd* m_pWndSelection;
	CFrameWnd* m_pHeaderFooterFrame;
	CFrameWnd* m_pPropertiesFrame;

	CXTPCommandBarScrollBarCtrl m_wndVScrollBar;
	CXTPCommandBarScrollBarCtrl m_wndHScrollBar;

public:

	//{{AFX_VIRTUAL(CReportSampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

public:
	virtual ~CReportSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	enum Column
	{
		COLUMN_IMPORTANCE   =  0,
		COLUMN_ICON         =  1,
		COLUMN_ATTACHMENT   =  2,
		COLUMN_FROM         =  3,
		COLUMN_SUBJECT      =  4,
		COLUMN_SENT         =  5,
		COLUMN_SIZE         =  6,
		COLUMN_CHECK        =  7,
		COLUMN_PRICE        =  8,
		COLUMN_CREATED      =  9,
		COLUMN_RECEIVED     = 10,
		COLUMN_CONVERSATION = 11,
		COLUMN_CONTACTS     = 12,
		COLUMN_MESSAGE      = 13,
		COLUMN_CC           = 14,
		COLUMN_CATEGORIES   = 15,
		COLUMN_AUTOFORWARD  = 16,
		COLUMN_AUTOARCHIVE  = 17,
		COLUMN_DUE_BY       = 18
	};

	void AddSampleRecords();

// Generated message map functions
protected:
	//{{AFX_MSG(CReportSampleView)

	// Window
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();

	// Report behavior
	afx_msg void OnBehaviorCodejockDefault();
	afx_msg void OnBehaviorCodejock1502();
	afx_msg void OnBehaviorCodejock1501();
	afx_msg void OnBehaviorCodejock1342();
	afx_msg void OnBehaviorOutlook2003();
	afx_msg void OnBehaviorOutlook2007();
	afx_msg void OnBehaviorOutlook2010();
	afx_msg void OnBehaviorExcel2003();
	afx_msg void OnBehaviorExcel2007();
	afx_msg void OnBehaviorExcel2010();
	afx_msg void OnBehaviorCustom();

	afx_msg void OnUpdateBehaviorCodejockDefault(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorCodejock1502   (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorCodejock1501   (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorCodejock1342   (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorOutlook2003    (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorOutlook2007    (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorOutlook2010    (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorExcel2003      (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorExcel2007      (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorExcel2010      (CCmdUI *pCmdUI);
	afx_msg void OnUpdateBehaviorCustom         (CCmdUI *pCmdUI);

	// Report control
	afx_msg void OnReportDoubleBuffering();
	afx_msg void OnReportLockExpand();
	afx_msg void OnReportWatermark();
	afx_msg void OnReportSmoothScrolling();

	afx_msg void OnUpdateReportDoubleBuffering(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportLockExpand     (CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportWatermark      (CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportSmoothScrolling(CCmdUI *pCmdUI);

	// Report header


	afx_msg void OnEnablePreview();
	afx_msg void OnUpdateEnablePreview(CCmdUI* pCmdUI);
	afx_msg void OnAutoGrouping();
	afx_msg void OnUpdateAutoGrouping(CCmdUI* pCmdUI);
	afx_msg void OnGroupBy();
	afx_msg void OnUpdateGroupBy(CCmdUI* pCmdUI);
	afx_msg void OnTestMarkup();
	afx_msg void OnUpdateTestMarkup(CCmdUI* pCmdUI);
	afx_msg void OnGroupShade();
	afx_msg void OnUpdateGroupShade(CCmdUI* pCmdUI);
	afx_msg void OnGroupBold();
	afx_msg void OnUpdateGroupBold(CCmdUI* pCmdUI);
	afx_msg void OnReportcontrolAutomaticformattingsample();
	afx_msg void OnUpdateReportcontrolAutomaticformattingsample(CCmdUI* pCmdUI);
	afx_msg void OnOptionsAllowcolumnresize();
	afx_msg void OnUpdateOptionsAllowcolumnresize(CCmdUI* pCmdUI);
	afx_msg void OnOptionsAllowcolumnsremove();
	afx_msg void OnUpdateOptionsAllowcolumnsremove(CCmdUI* pCmdUI);
	afx_msg void OnOptionsMultipleselection();
	afx_msg void OnUpdateOptionsMultipleselection(CCmdUI* pCmdUI);
	afx_msg void OnOptionsShowitemsingroups();
	afx_msg void OnUpdateOptionsShowitemsingroups(CCmdUI* pCmdUI);

	// Test
	afx_msg void OnTreeViewDlg();
	afx_msg void OnTreeEditDlg();
	afx_msg void OnFormulaDlg();
	afx_msg void OnTestSmoothScroll();
	afx_msg void OnTestTasklist();
	afx_msg void OnTestMerge();
	afx_msg void OnTestSelection();
	afx_msg void OnTestHeaderFooter();
	afx_msg void OnTestPerfomance();
	afx_msg void OnTestProperties();

	// Quality assurance
	afx_msg void OnTestEmpty();
	afx_msg void OnTestConstraints();
	afx_msg void OnTestNotifications();

	afx_msg void OnOptionsAutomaticcolumnsizing();
	afx_msg void OnUpdateOptionsAutomaticcolumnsizing(CCmdUI* pCmdUI);
	afx_msg void OnReportcontrolMultilinesample();
	afx_msg void OnOptionsFullColumnScrolling();
	afx_msg void OnUpdateOptionsFullColumnScrolling(CCmdUI* pCmdUI);
	afx_msg void OnUpdateReportcontrolMultilinesample(CCmdUI* pCmdUI);
	afx_msg void OnReportheaderAllowcolumnreorder();
	afx_msg void OnUpdateReportheaderAllowcolumnreorder(CCmdUI* pCmdUI);
	afx_msg void OnColumnStyle(UINT);
	afx_msg void OnUpdateColumnStyle(CCmdUI* pCmdUI);
	
	afx_msg void OnUpdateOptionsFreezecolumns0(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsFreezecolumns1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsFreezecolumns2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsFreezecolumns3(CCmdUI* pCmdUI);
	
	afx_msg void OnOptionsFreezecolumns0();
	afx_msg void OnOptionsFreezecolumns1();
	afx_msg void OnOptionsFreezecolumns2();
	afx_msg void OnOptionsFreezecolumns3();

	afx_msg void OnReportcontrolRighttoleft();
	afx_msg void OnUpdateReportcontrolRighttoleft(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFreezecolumnsDivider1();
	afx_msg void OnUpdateOptionsFreezecolumnsDivider1(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFreezecolumnsDivider2();
	afx_msg void OnUpdateOptionsFreezecolumnsDivider2(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFreezecolumnsDividerHeader();
	afx_msg void OnUpdateOptionsFreezecolumnsDividerHeader(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFreezecolumnsDividerNone();
	afx_msg void OnUpdateOptionsFreezecolumnsDividerNone(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFreezecolumnsDividerShade();
	afx_msg void OnUpdateOptionsFreezecolumnsDividerShade(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnGridHorizontal(UINT);
	afx_msg void OnUpdateGridHorizontal(CCmdUI* pCmdUI);

	afx_msg void OnGridVertical(UINT);
	afx_msg void OnUpdateGridVertical(CCmdUI* pCmdUI);
	afx_msg void OnReportHyperlinkClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnShowFieldChooser();
	afx_msg void OnReportKeyDown(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportBeginDrag(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportBeforePasteFromText(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportBeforePaste(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportWYSIWYG();
	afx_msg void OnUpdateReportWYSIWYG(CCmdUI *pCmdUI);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnReportIconview();
	afx_msg void OnUpdateReportIconview(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	BOOL OnFindInReport();
	afx_msg void OnReportcontrolDevtest();

private:

	int m_behavior;
};

#ifndef _DEBUG  // debug version in ReportSampleView.cpp
inline CReportSampleDoc* CReportSampleView::GetDocument()
{
	return (CReportSampleDoc*)m_pDocument;
}
#endif

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_REPORTSAMPLEVIEW_H_)
