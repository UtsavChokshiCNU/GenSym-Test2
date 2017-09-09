// CppUnitTest.h : main header file for the CPPUNITTEST application
//

#if !defined(AFX_CPPUNITTEST_H__15AB5FE4_E00D_492D_92BE_FDACA0A864EC__INCLUDED_)
#define AFX_CPPUNITTEST_H__15AB5FE4_E00D_492D_92BE_FDACA0A864EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestApp:
// See CppUnitTest.cpp for the implementation of this class
//

class CCppUnitTestApp : public CWinApp
{
public:
	CCppUnitTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCppUnitTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCppUnitTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPUNITTEST_H__15AB5FE4_E00D_492D_92BE_FDACA0A864EC__INCLUDED_)
