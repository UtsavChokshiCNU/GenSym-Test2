// MarkupPad.h : main header file for the MARKUPPAD application
//

#if !defined(AFX_MARKUPPAD_H__A556BD12_B078_46C7_B426_6DEB9B7605A8__INCLUDED_)
#define AFX_MARKUPPAD_H__A556BD12_B078_46C7_B426_6DEB9B7605A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadApp:
// See MarkupPad.cpp for the implementation of this class
//

class CMarkupPadApp : public CWinApp
{
public:
	CMarkupPadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMarkupPadApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPAD_H__A556BD12_B078_46C7_B426_6DEB9B7605A8__INCLUDED_)
