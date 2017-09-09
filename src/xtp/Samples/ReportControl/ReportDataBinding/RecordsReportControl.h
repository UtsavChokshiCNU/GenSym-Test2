// RecordsReportControl.h: interface for the CRecordsReportControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDSREPORTCONTROL_H__7361D7E3_7483_4EAC_BDC2_15CA2BC0F49B__INCLUDED_)
#define AFX_RECORDSREPORTCONTROL_H__7361D7E3_7483_4EAC_BDC2_15CA2BC0F49B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	void AddNewRecord();
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

#endif // !defined(AFX_RECORDSREPORTCONTROL_H__7361D7E3_7483_4EAC_BDC2_15CA2BC0F49B__INCLUDED_)
