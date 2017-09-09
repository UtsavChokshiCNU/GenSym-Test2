// CoolGridPage.h : header file
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

#if !defined(AFX_ICONSGRIDPAGE_H__BC1F6C4F_F2AF_4AAC_BFDF_21DE8FE2F1B7__INCLUDED_)
#define AFX_ICONSGRIDPAGE_H__BC1F6C4F_F2AF_4AAC_BFDF_21DE8FE2F1B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCoolGridPage dialog

class CCoolGridPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCoolGridPage)

// Construction
public:
	CCoolGridPage();
	~CCoolGridPage();


// Dialog Data
	//{{AFX_DATA(CCoolGridPage)
	enum { IDD = IDD_PAGE_COOL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	CXTPPropertyGrid m_wndPropertyGrid;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCoolGridPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCoolGridPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONSGRIDPAGE_H__BC1F6C4F_F2AF_4AAC_BFDF_21DE8FE2F1B7__INCLUDED_)
