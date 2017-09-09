// ChartBrowser.h : main header file for the CHARTBROWSER application
//

#if !defined(AFX_CHARTBROWSER_H__E5145EB3_DA1C_496C_B2EC_CF3F1ED8C1B8__INCLUDED_)
#define AFX_CHARTBROWSER_H__E5145EB3_DA1C_496C_B2EC_CF3F1ED8C1B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChartBrowserApp:
// See ChartBrowser.cpp for the implementation of this class
//

class CChartBrowserApp : public CWinApp
{
public:
	CChartBrowserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartBrowserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CChartBrowserApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTBROWSER_H__E5145EB3_DA1C_496C_B2EC_CF3F1ED8C1B8__INCLUDED_)
