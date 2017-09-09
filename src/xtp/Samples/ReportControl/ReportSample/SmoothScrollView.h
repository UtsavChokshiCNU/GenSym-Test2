// SmoothScrollView.h : header file
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

#if !defined(__SMOOTHSCROLLVIEW_H__)
#define __SMOOTHSCROLLVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSmoothScrollFrame : public CXTPFrameWnd
{
public:
	CSmoothScrollFrame(CView *pView)
	{
		m_pOwnerView = pView;
	}

protected:
	CStatusBar m_wndStatusBar;
	CToolBar   m_wndToolBar;
	CView     *m_pOwnerView;

protected:
	//{{AFX_MSG(CSmoothScrollFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CSmoothScrollView view

class CSmoothScrollView : public CXTPReportView
{
protected:
	CSmoothScrollView();
	virtual ~CSmoothScrollView();
	DECLARE_DYNCREATE(CSmoothScrollView)

public:

	//{{AFX_VIRTUAL(CSmoothScrollView)
	protected:
	//}}AFX_VIRTUAL

protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext &dc) const;
#endif

protected:
	//{{AFX_MSG(CSmoothScrollView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(__smoothscrollview_h__)
