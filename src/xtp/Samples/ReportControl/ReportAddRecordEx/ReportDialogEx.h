// ReportDialogEx.h : main header file for the REPORTDIALOGEX application
//

#if !defined(AFX_REPORTDIALOGEX_H__32290076_EF84_4162_BA45_232F83BF4C2F__INCLUDED_)
#define AFX_REPORTDIALOGEX_H__32290076_EF84_4162_BA45_232F83BF4C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReportDialogExApp:
// See ReportDialogEx.cpp for the implementation of this class
//

class CReportDialogExApp : public CWinApp
{
public:
	CReportDialogExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDialogExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReportDialogExApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDIALOGEX_H__32290076_EF84_4162_BA45_232F83BF4C2F__INCLUDED_)
