// ReportDataBindingDlg.h : header file
//

#if !defined(AFX_REPORTDATABINDINGDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
#define AFX_REPORTDATABINDINGDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordsReportControl.h"
#include "MenuInit.h"

/////////////////////////////////////////////////////////////////////////////
// CReportDataBindingDlg dialog

  #define CDialog CXTPResizeDialog

class CReportDataBindingDlg : public CDialog
{
// Construction
public:
	CReportDataBindingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReportDataBindingDlg)
	enum { IDD = IDD_REPORTDATABINDING_DIALOG };
	//}}AFX_DATA
	CXTPReportControl m_wndTablesReportCtrl;
	CRecordsReportControl m_wndRecordsReportCtrl;

	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecords;	

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDataBindingDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void OpenDatabase(CString strConnection);
	void ShowRecords(CString strTable);

	// Generated message map functions
	//{{AFX_MSG(CReportDataBindingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnOpenDatabaseButton();
	afx_msg void OnActionButton();
	afx_msg void OnAddRecToRecset();
	afx_msg void OnDeleteRecFromRecset();
	afx_msg void OnAddRecord();
	afx_msg void OnDeleteRecord();
	afx_msg void OnUpdateAddRecToRecset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddRecord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteRecFromRecset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteRecord(CCmdUI* pCmdUI);
	afx_msg void OnService();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	//}}AFX_MSG
	afx_msg void OnTableChanged(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnValueChanged(NMHDR * pNotifyStruct, LRESULT * result);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDATABINDINGDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
