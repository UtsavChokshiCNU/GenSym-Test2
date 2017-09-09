#if !defined(AFX_DateTimeView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
#define AFX_DateTimeView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateTimeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateTimeView form view

#include "BaseView.h"

class CDateTimeView : public CBaseView
{
public:
	CDateTimeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDateTimeView)

// Form Data
public:
	//{{AFX_DATA(CDateTimeView)
	enum { IDD = IDD_VIEW_DATETIME};
	//CXTPComboBox	m_cboPosition;
	//CXTPButton	m_chkShowLabels;
	int		m_nMeasureUnits;
	CString m_strLabelFormat;
	CComboBox m_cmbLabelFormat;
	//}}AFX_DATA

	void CreateChart();

// Attributes
public:
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDateTimeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDateTimeView)
	afx_msg void OnCheckShowLabels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMeasureUnitsChanged();
	afx_msg void OnLabelFormatChanged();
	afx_msg void OnLabelFormatIndexChanged();

	afx_msg void SetLabelFormat(CString strLabelFormat);

	void AddDaySeries();
	void AddHourSeries();
	void AddMonthSeries();
	void AddYearSeries();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DateTimeView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
