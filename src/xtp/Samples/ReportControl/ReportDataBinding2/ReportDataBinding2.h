// ReportDataBinding2.h : main header file for the REPORTDATABINDING2 application
//

#if !defined(AFX_REPORTDATABINDING2_H__3138AC35_C5FF_44A0_9DF5_C441ADDA89F4__INCLUDED_)
#define AFX_REPORTDATABINDING2_H__3138AC35_C5FF_44A0_9DF5_C441ADDA89F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSampleApplication:
// See ReportDataBinding2.cpp for the implementation of this class
//

class CSampleApplication : public CWinApp
{
public:
	CSampleApplication();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleApplication)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSampleApplication)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDATABINDING2_H__3138AC35_C5FF_44A0_9DF5_C441ADDA89F4__INCLUDED_)
