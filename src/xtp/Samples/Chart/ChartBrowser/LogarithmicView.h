#if !defined(AFX_LogarithmicView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
#define AFX_LogarithmicView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogarithmicView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogarithmicView form view

#include "BaseView.h"

class CLogarithmicView : public CBaseView
{
public:
	CLogarithmicView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLogarithmicView)

// Form Data
public:
	//{{AFX_DATA(CLogarithmicView)
	enum { IDD = IDD_VIEW_LOGARITHMIC};
	//CXTPComboBox	m_cboPosition;
	//CXTPButton	m_chkShowLabels;
	//}}AFX_DATA

	void CreateChart();

// Attributes
public:
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogarithmicView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogarithmicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void OnSize(UINT nType, int cx, int cy);

	// Generated message map functions
	//{{AFX_MSG(CLogarithmicView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LogarithmicView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
