// g2mfcDlg.h : header file
//

#if !defined(AFX_G2MFCDLG_H__58F7A244_D7A1_4966_B054_81B59672C7DE__INCLUDED_)
#define AFX_G2MFCDLG_H__58F7A244_D7A1_4966_B054_81B59672C7DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CG2mfcDlg dialog
#include "g2gateway4.h"

class CG2mfcDlg : public CDialog
{
// Construction
public:
	CG2mfcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CG2mfcDlg)
	enum { IDD = IDD_G2MFC_DIALOG };
	CButton	m_Con;
	CString	m_ConStr;
	CString	m_State;
	CString	m_Msg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CG2mfcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool b_State;
	HICON m_hIcon;
    CG2Gateway4 m_G2Gateway4;
	// Generated message map functions
	//{{AFX_MSG(CG2mfcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnRpcStartedG2gateway1(LPCTSTR ProcedureName, VARIANT FAR* InputArguments);
	afx_msg void OnG2ConnectedG2gateway1();
	afx_msg void OnButton2();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G2MFCDLG_H__58F7A244_D7A1_4966_B054_81B59672C7DE__INCLUDED_)
