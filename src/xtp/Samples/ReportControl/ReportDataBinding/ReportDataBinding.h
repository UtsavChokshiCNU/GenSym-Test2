// ReportDataBinding.h : main header file for the REPORTDATABINDING application
//

#if !defined(AFX_REPORTDATABINDING_H__32290076_EF84_4162_BA45_232F83BF4C2F__INCLUDED_)
#define AFX_REPORTDATABINDING_H__32290076_EF84_4162_BA45_232F83BF4C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReportDataBindingApp:
// See ReportDataBinding.cpp for the implementation of this class
//

class CReportDataBindingApp : public CWinApp
{
public:
	CReportDataBindingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDataBindingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReportDataBindingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDATABINDING_H__32290076_EF84_4162_BA45_232F83BF4C2F__INCLUDED_)
