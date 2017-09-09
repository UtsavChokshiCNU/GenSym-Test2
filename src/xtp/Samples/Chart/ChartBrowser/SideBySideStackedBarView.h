#pragma once

#include "BaseView.h"

// CSideBySideStackedBarView form view

class CSideBySideStackedBarView : public CBaseView
{
	DECLARE_DYNCREATE(CSideBySideStackedBarView)

protected:
	CSideBySideStackedBarView();           // protected constructor used by dynamic creation
	virtual ~CSideBySideStackedBarView();

public:
	enum { IDD = IDD_VIEW_SIDEBYDIDESTACKEDBAR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	virtual void OnInitialUpdate();

	BOOL	m_bShowLabels;
	BOOL	m_bRotated;
	int m_nGroup;
	BOOL m_b100;

	void CreateChart();
	afx_msg void OnClickedGroup();
	afx_msg void OnCheck100();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnCheckShowLabels();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckRotated();
};

class CFullSideBySideStackedBarView : public CSideBySideStackedBarView
{
	DECLARE_DYNCREATE(CFullSideBySideStackedBarView)

protected:
	CFullSideBySideStackedBarView();           // protected constructor used by dynamic creation
	virtual void OnInitialUpdate();

};
