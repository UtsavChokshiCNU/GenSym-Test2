// CommandBarControls.h : main header file for the COMMANDBARCONTROLS application
//

#if !defined(AFX_COMMANDBARCONTROLS_H__A2386370_01E3_4293_AAEC_9C9DCA4FCFD6__INCLUDED_)
#define AFX_COMMANDBARCONTROLS_H__A2386370_01E3_4293_AAEC_9C9DCA4FCFD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsApp:
// See CommandBarControls.cpp for the implementation of this class
//

class CCommandBarControlsApp : public CWinApp
{
public:
	CCommandBarControlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandBarControlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCommandBarControlsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDBARCONTROLS_H__A2386370_01E3_4293_AAEC_9C9DCA4FCFD6__INCLUDED_)
