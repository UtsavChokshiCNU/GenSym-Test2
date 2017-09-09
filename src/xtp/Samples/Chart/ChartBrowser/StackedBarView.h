#pragma once

#include "BaseView.h"

// CStackedBarView form view

class CStackedBarView : public CBaseView
{
	DECLARE_DYNCREATE(CStackedBarView)

protected:
	CStackedBarView();           // protected constructor used by dynamic creation
	virtual ~CStackedBarView();

public:
	enum { IDD = IDD_VIEW_STACKEDBAR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	virtual void OnInitialUpdate();

	BOOL	m_bShowLabels;
	BOOL	m_bRotated;
	void CreateChart();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnCheckShowLabels();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckRotated();
};

class CFullStackedBarView : public CStackedBarView
{
	DECLARE_DYNCREATE(CFullStackedBarView)

protected:
	CFullStackedBarView();           // protected constructor used by dynamic creation
	virtual void OnInitialUpdate();

};
