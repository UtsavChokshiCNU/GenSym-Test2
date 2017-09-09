#if !defined(AFX_ChartFromFileView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
#define AFX_ChartFromFileView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartFromFileView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartFromFileView form view

#include "BaseView.h"

class CChartFromFileView : public CBaseView
{
public:
	CChartFromFileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChartFromFileView)

// Form Data
public:
	//{{AFX_DATA(CChartFromFileView)
	enum { IDD = IDD_VIEW_SIMPLE };
	//CXTPComboBox	m_cboPosition;
	//CXTPButton	m_chkShowLabels;
	BOOL	m_bShowLabels;
	//}}AFX_DATA

	void CreateChart();

// Attributes
public:
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartFromFileView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChartFromFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChartFromFileView)
	afx_msg void OnCheckShowLabels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboLabelPosition();
	afx_msg void OnBnClickedCheckRotated();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ChartFromFileView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
