#if !defined(AFX_WEBSCORAX_H__B72A81A1_2EDD_4C9E_A969_8A0C851F1484__INCLUDED_)
#define AFX_WEBSCORAX_H__B72A81A1_2EDD_4C9E_A969_8A0C851F1484__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WebSCORax.h : main header file for WEBSCORAX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxApp : See WebSCORax.cpp for implementation.

class CWebSCORaxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBSCORAX_H__B72A81A1_2EDD_4C9E_A969_8A0C851F1484__INCLUDED)
