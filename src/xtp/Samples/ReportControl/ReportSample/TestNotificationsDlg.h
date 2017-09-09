// TestNotificationsDlg.h
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_TESTNOTIFICATIONSDLG_H_)
#define _TESTNOTIFICATIONSDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestNotificationsDlg dialog

class CTestNotificationsDlg : public CDialog
{
public:
	CTestNotificationsDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CTestNotificationsDlg)
	enum { IDD = IDD_TEST_NOTIFICATIONS };
	BOOL	m_bCancelFocusChanging;
	BOOL	m_bCancelLButtonDown;
	BOOL	m_bCancelLButtonUp;
	BOOL	m_bCancelSelectionClear;
	BOOL	m_bCancelSelectionAdd;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTestNotificationsDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CTestNotificationsDlg)
	afx_msg void OnReportClick(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportRClick(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportDblClick(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportLButtonDown(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportLButtonUp(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportSelChanging(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportSelChanged(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnReportFocusChanging(NMHDR *pNotifyStruct, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int AddNotification(LPCTSTR pszNotification, int nRow, LPCTSTR pszParameter = _T(""));

	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
	CListCtrl m_wndNotifications;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TESTNOTIFICATIONSDLG_H_)
