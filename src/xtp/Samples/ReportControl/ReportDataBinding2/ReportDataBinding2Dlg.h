// ReportDataBinding2Dlg.h : header file
//

#if !defined(AFX_REPORTDATABINDING2DLG_H__7DFCD714_17BA_40E5_990B_C81E798B1463__INCLUDED_)
#define AFX_REPORTDATABINDING2DLG_H__7DFCD714_17BA_40E5_990B_C81E798B1463__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

  #define CDialog CXTPResizeDialog


/////////////////////////////////////////////////////////////////////////////
// CStaticLine window

class CStaticLine : public CStatic
{
// Construction
public:
	CStaticLine();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticLine)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticLine();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticLine)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CRecordsReportControl : public CXTPReportControl  
{
public:
	CRecordsReportControl();
	virtual ~CRecordsReportControl();

// Attributes
public:
protected:
	CXTPReportRecord* m_pFocusedRecord;
	CXTPReportRow* m_pTopRow;

// Operations
public:
	BOOL AddNewRecord();
	void DeleteSelectedRows();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordsReportControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL OnFocusChanging(CXTPReportRow* pNewRow, CXTPReportColumn* pNewCol);

	// Generated message map functions
protected:
	//{{AFX_MSG(CRecordsReportControl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog

class CSampleDlg : public CDialog
{
// Construction
public:
	CString m_strConnectionString;
	CSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSampleDlg)
	enum { IDD = IDD_REPORTDATABINDING2_DIALOG };

	CXTPButton	m_btnExitApp;
	CXTPButton	m_btnHelp;
	CXTPButton	m_btnActions;
	CRecordsReportControl m_wndRecordsReportCtrl;
	CListBox m_wndTablesListCtrl;

	CStaticLine	m_wndHorizLine;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	BOOL OpenDatabase(CString strConnection);
	BOOL ShowRecords(CString strTableName);

	// Generated message map functions
	//{{AFX_MSG(CSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHelpButton();
	afx_msg void OnSelchangeTablesList();
	afx_msg void OnButtonDropDown();
	afx_msg void OnValueChanged(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnUpdateDeleteRecords(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteRecordsFromRecordset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddRecords(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddRecordsToRecordset(CCmdUI* pCmdUI);
	afx_msg void OnAddRecords();
	afx_msg void OnAddRecordsToRecordset();
	afx_msg void OnDeleteRecords();
	afx_msg void OnDeleteRecordsFromRecordset();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
};

CString LoadStringFromResources(const UINT nID);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDATABINDING2DLG_H__7DFCD714_17BA_40E5_990B_C81E798B1463__INCLUDED_)
