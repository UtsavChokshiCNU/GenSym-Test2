// Controls.h : main header file for the CONTROLS application
//

#if !defined(AFX_CONTROLS_H__D49F90D2_7DED_447E_941B_B556B714C9D2__INCLUDED_)
#define AFX_CONTROLS_H__D49F90D2_7DED_447E_941B_B556B714C9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CControlsApp:
// See Controls.cpp for the implementation of this class
//

class CControlsApp : public CWinApp
{
public:
	CControlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CControlsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLS_H__D49F90D2_7DED_447E_941B_B556B714C9D2__INCLUDED_)
