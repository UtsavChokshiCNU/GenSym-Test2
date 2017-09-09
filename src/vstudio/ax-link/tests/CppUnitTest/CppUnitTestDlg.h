// CppUnitTestDlg.h : header file
//
//{{AFX_INCLUDES()
#include "g2gateway4.h"
//}}AFX_INCLUDES

#if !defined(AFX_CPPUNITTESTDLG_H__1A42C1C5_DC30_45F6_9874_3903A40A4FC0__INCLUDED_)
#define AFX_CPPUNITTESTDLG_H__1A42C1C5_DC30_45F6_9874_3903A40A4FC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestDlg dialog

class CCppUnitTestDlg : public CDialog
{
// Construction
public:
	BOOL Start();
	BOOL CallDeferred();
	BOOL Call();
	BOOL PostMessage();
	static BOOL WaitUntilTRUE(BOOL* bVar, DWORD dwMilliseconds);
	BOOL m_bRpcReturnedEventFired;
	BOOL m_bRunStateKnownEventFired;
	BOOL m_bConnectedEventFired;
	BOOL m_bDisconnectedEventFired;
	BOOL Disconnect();
	BOOL Connect();
	CCppUnitTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCppUnitTestDlg)
	enum { IDD = IDD_CPPUNITTEST_DIALOG };
	CG2Gateway4	m_g2g;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCppUnitTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCppUnitTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnG2ConnectedG2gateway1();
	afx_msg void OnG2DisconnectedG2gateway1();
	afx_msg void OnG2RunStateKnownG2gateway1();
	afx_msg void OnRpcCalledG2gateway1(LPCTSTR ProcedureName, VARIANT FAR* InputArguments, VARIANT FAR* ReturnArguments);
	afx_msg void OnRpcReturnedG2gateway1(LPCTSTR ProcedureName, VARIANT FAR* ReturnArguments, VARIANT FAR* DeferredCallIdentifier);
	afx_msg void OnG2PausedG2gateway1();
	afx_msg void OnG2ResetG2gateway1();
	afx_msg void OnG2ResumedG2gateway1();
	afx_msg void OnG2StartedG2gateway1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPUNITTESTDLG_H__1A42C1C5_DC30_45F6_9874_3903A40A4FC0__INCLUDED_)
