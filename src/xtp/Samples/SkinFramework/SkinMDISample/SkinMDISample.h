// SkinMDISample.h : main header file for the SKINMDISAMPLE application
//

#if !defined(AFX_SKINMDISAMPLE_H__7A3FAB07_C578_4F15_8B55_581FB507733B__INCLUDED_)
#define AFX_SKINMDISAMPLE_H__7A3FAB07_C578_4F15_8B55_581FB507733B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleApp:
// See SkinMDISample.cpp for the implementation of this class
//

class CSkinMDISampleApp : public CWinApp
{
public:
	CSkinMDISampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinMDISampleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSkinMDISampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINMDISAMPLE_H__7A3FAB07_C578_4F15_8B55_581FB507733B__INCLUDED_)
