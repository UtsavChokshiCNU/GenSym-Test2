// SelectionView.h : header file
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

#if !defined(_SELECTIONVIEW_H_)
#define _SELECTIONVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CSelectionFrame : public CXTPFrameWnd
{
public:
	CSelectionFrame(CView* pView)
	{
		m_pOwnerView = pView;

	}

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CView* m_pOwnerView;

// Generated message map functions
protected:
	//{{AFX_MSG(CSelectionFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


class CSelectionView : public CXTPReportView
{
	DECLARE_DYNCREATE(CSelectionView)
protected:
	CSelectionView();
	virtual ~CSelectionView();

public:

	//{{AFX_VIRTUAL(CSelectionView)
	protected:
	//}}AFX_VIRTUAL

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CSelectionView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnReportValueChanged(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportSelChanged  (NMHDR *pNotifyStruct, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_SELECTIONVIEW_H_)
