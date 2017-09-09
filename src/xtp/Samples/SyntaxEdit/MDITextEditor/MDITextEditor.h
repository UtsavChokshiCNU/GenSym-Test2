// MDITextEditor.h : main header file for the MDITEXTEDITOR application
//

#if !defined(AFX_MDITEXTEDITOR_H__758F7CD9_8DF3_4783_A814_02C3EA1A1BA1__INCLUDED_)
#define AFX_MDITEXTEDITOR_H__758F7CD9_8DF3_4783_A814_02C3EA1A1BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CMainFrame;

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorApp:
// See MDITextEditor.cpp for the implementation of this class
//

class CMDITextEditorApp : public CWinApp
{
public:
	CMDITextEditorApp();
	virtual ~CMDITextEditorApp();

	void UpdateAllViews(CView* pSender=NULL);

public:
	CMainFrame*			m_pMainFrame;
	CMultiDocTemplate*	m_pDocTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDITextEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMDITextEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAll();
	afx_msg void OnFileCloseAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL RegisterWindowClass();
	BOOL CreateSingleInstance();
	BOOL ActivateExisting(const CString& csFilePath);

protected:
	int			m_nFilterIndex;
	HANDLE		m_hMutex;
	CString		m_csInitialDir;
};


const TCHAR CLASSNAME_APPINSTANCE[] = _T("Codejock-MDITextEditor-Sample");
const DWORD cdwData_FileName = 1;

extern CMDITextEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDITEXTEDITOR_H__758F7CD9_8DF3_4783_A814_02C3EA1A1BA1__INCLUDED_)
