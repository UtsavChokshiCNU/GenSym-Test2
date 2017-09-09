// FlowGraphSample.h : main header file for the FLOWGRAPHSAMPLE application
//

#if !defined(AFX_FLOWGRAPHSAMPLE_H__6AE80F87_E074_4C8D_B8CE_38FC3F851D85__INCLUDED_)
#define AFX_FLOWGRAPHSAMPLE_H__6AE80F87_E074_4C8D_B8CE_38FC3F851D85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleApp:
// See FlowGraphSample.cpp for the implementation of this class
//

class CFlowGraphSampleApp : public CWinApp
{
public:
	CFlowGraphSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlowGraphSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFlowGraphSampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOWGRAPHSAMPLE_H__6AE80F87_E074_4C8D_B8CE_38FC3F851D85__INCLUDED_)
