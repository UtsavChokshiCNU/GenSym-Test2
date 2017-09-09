// HeaderFooterView.h : header file
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

#if !defined(AFX_HEADERFOOTERVIEW_H__5E52F174_9488_44B0_B8E7_48BC345422A2__INCLUDED_)
#define AFX_HEADERFOOTERVIEW_H__5E52F174_9488_44B0_B8E7_48BC345422A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainFrm.h"


class CHeaderFooterFrame : public CXTPFrameWnd
{
public:
	CHeaderFooterFrame(CView *pView)
	{
		m_pOwnerView = pView;
	}

protected:
	//{{AFX_MSG(CHeaderFooterFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CView      *m_pOwnerView;
};

/////////////////////////////////////////////////////////////////////////////
// CHeaderFooterView view

class CHeaderFooterView : public CXTPReportView
{
	typedef CXTPReportView base;
protected:
	CHeaderFooterView();
	DECLARE_DYNCREATE(CHeaderFooterView)

public:

	//{{AFX_VIRTUAL(CHeaderFooterView)
	protected:
	afx_msg void OnEndPrintPreview(CDC *pDC, CPrintInfo *pInfo, POINT point, CPreviewView *pView);
	//}}AFX_VIRTUAL

protected:
	virtual ~CHeaderFooterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CHeaderFooterView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	
	afx_msg void OnShowHeaderRecords();
	afx_msg void OnShowFooterRecords();
	afx_msg void OnShowGroupBy();
	afx_msg void OnUpdateShowGroupBy(CCmdUI* pCmdUI);

	afx_msg void OnHeaderRecordsAllowEdit();
	afx_msg void OnFooterRecordsAllowEdit();

	afx_msg void OnUpdateShowHeaderRecords(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShowFooterRecords(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHeaderRecordsAllowEdit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFooterRecordsAllowEdit(CCmdUI *pCmdUI);

	afx_msg void OnMoveInHeader();
	afx_msg void OnMoveInFooter();
	afx_msg void OnUpdateMoveInHeader(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMoveInFooter(CCmdUI *pCmdUI);

	afx_msg void OnPinFooterRows();
	afx_msg void OnPinFooterRowsPrinted();
	afx_msg void OnUpdatePinFooterRows(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePinFooterRowsPrinted(CCmdUI *pCmdUI);

	afx_msg void OnDrawGridForEmpty();
	afx_msg void OnUpdateDrawGridForEmpty(CCmdUI* pCmdUI);

	// Header divider style
	afx_msg void OnHeaderDividerStyleThin();
	afx_msg void OnHeaderDividerStyleBold();
	afx_msg void OnHeaderDividerStyleNone();
	afx_msg void OnHeaderDividerStyleShade();
	afx_msg void OnHeaderDividerStyleOutlook();

	afx_msg void OnUpdateHeaderDividerStyleThin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHeaderDividerStyleBold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHeaderDividerStyleNone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHeaderDividerStyleShade(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHeaderDividerStyleOutlook(CCmdUI* pCmdUI);
	
	// Footer divider style
	afx_msg void OnFooterDividerStyleThin();
	afx_msg void OnFooterDividerStyleBold();
	afx_msg void OnFooterDividerStyleNone();
	afx_msg void OnFooterDividerStyleShade();
	afx_msg void OnFooterDividerStyleOutlook();

	afx_msg void OnUpdateFooterDividerStyleThin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFooterDividerStyleBold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFooterDividerStyleNone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFooterDividerStyleShade(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFooterDividerStyleOutlook(CCmdUI* pCmdUI);

	// Column style
	afx_msg void OnColumnsStyleFlat();
	afx_msg void OnColumnsStyleExplorer();
	afx_msg void OnColumnsStyleShaded();
	afx_msg void OnColumnsStyleOffice2003();

	afx_msg void OnUpdateColumnsStyleFlat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColumnsStyleExplorer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColumnsStyleShaded(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColumnsStyleOffice2003(CCmdUI* pCmdUI);
	
	afx_msg void OnAddTask();
	afx_msg void OnReportButtonClick(NMHDR * pNotifyStruct, LRESULT *result);
	//}}AFX_MSG

	BOOL Show_XTPDatePicker(CXTPReportControl* pControl, const CRect& rcItem, COleDateTime& rdtDate);
	BOOL Show_MFCDatePicker(CXTPReportControl* pControl, const CRect& rcItem, COleDateTime& rdtDate);

	DECLARE_MESSAGE_MAP()

private:

	CPrintPreviewState *m_pPreviewState;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_HEADERFOOTERVIEW_H__5E52F174_9488_44B0_B8E7_48BC345422A2__INCLUDED_)
