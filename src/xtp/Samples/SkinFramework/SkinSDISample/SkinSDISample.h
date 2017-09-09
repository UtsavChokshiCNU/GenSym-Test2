// SkinSDISample.h : main header file for the SKINSDISAMPLE application
//

#if !defined(AFX_SKINSDISAMPLE_H__D850416B_A5D0_4033_AE32_F5FD1122177C__INCLUDED_)
#define AFX_SKINSDISAMPLE_H__D850416B_A5D0_4033_AE32_F5FD1122177C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleApp:
// See SkinSDISample.cpp for the implementation of this class
//

class CSkinSDISampleApp : public CWinApp
{
public:
	CSkinSDISampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinSDISampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSkinSDISampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSDISAMPLE_H__D850416B_A5D0_4033_AE32_F5FD1122177C__INCLUDED_)
