// SimpleChart.h : main header file for the SIMPLECHART application
//

#if !defined(AFX_SIMPLECHART_H__EC4B612E_3B65_43A0_8B04_E3E17515980A__INCLUDED_)
#define AFX_SIMPLECHART_H__EC4B612E_3B65_43A0_8B04_E3E17515980A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleChartApp:
// See SimpleChart.cpp for the implementation of this class
//

class CSimpleChartApp : public CWinApp
{
public:
	CSimpleChartApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleChartApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSimpleChartApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLECHART_H__EC4B612E_3B65_43A0_8B04_E3E17515980A__INCLUDED_)
