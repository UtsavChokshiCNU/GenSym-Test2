// ViewBase.h : header file
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

#if !defined(AFX_VIEW1_H__DB5DD4BB_239B_4D1D_8478_3CA079B61C83__INCLUDED_)
#define AFX_VIEW1_H__DB5DD4BB_239B_4D1D_8478_3CA079B61C83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CViewBase view

class CViewBase : public CView
{
protected:
	CViewBase();
	virtual ~CViewBase();
	DECLARE_DYNCREATE(CViewBase)

protected:
	CFont m_font;
	CString m_strView;

	//{{AFX_VIRTUAL(CView1)
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CViewBase)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CView1 view

class CView1 : public CViewBase
{
protected:
	CView1();
	virtual ~CView1();
	DECLARE_DYNCREATE(CView1)
};

/////////////////////////////////////////////////////////////////////////////
// CView2 view

class CView2 : public CViewBase
{
protected:
	CView2();
	virtual ~CView2();
	DECLARE_DYNCREATE(CView2)
};

/////////////////////////////////////////////////////////////////////////////
// CView3 view

class CView3 : public CViewBase
{
protected:
	CView3();
	virtual ~CView3();
	DECLARE_DYNCREATE(CView3)
};

/////////////////////////////////////////////////////////////////////////////
// CView4 view

class CView4 : public CViewBase
{
protected:
	CView4();
	virtual ~CView4();
	DECLARE_DYNCREATE(CView4)
};

/////////////////////////////////////////////////////////////////////////////
// CView5 view

class CView5 : public CViewBase
{
protected:
	CView5();
	virtual ~CView5();
	DECLARE_DYNCREATE(CView5)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW1_H__DB5DD4BB_239B_4D1D_8478_3CA079B61C83__INCLUDED_)
