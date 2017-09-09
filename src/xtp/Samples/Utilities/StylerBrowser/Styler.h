// Styler.h : main header file for the STYLER application
//

#if !defined(AFX_STYLER_H__E5C751C5_9965_11D6_874C_0050228CE6CB__INCLUDED_)
#define AFX_STYLER_H__E5C751C5_9965_11D6_874C_0050228CE6CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStylerApp:
// See Styler.cpp for the implementation of this class
//

class CStylerApp : public CWinApp
{
public:
	CStylerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStylerApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

protected:
	BOOL OneInstance(CCommandLineInfo&);
	BOOL ProcessShellCommand(CCommandLineInfo& cmdInfo);

// Implementation
	//{{AFX_MSG(CStylerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


CString GetModuleDir();
inline BOOL PathFileExists(CString str)
{
	CFileStatus fStatus;
	
	if (! CFile::GetStatus(str, fStatus))
		return FALSE;

	return TRUE;
}

#endif // !defined(AFX_STYLER_H__E5C751C5_9965_11D6_874C_0050228CE6CB__INCLUDED_)
