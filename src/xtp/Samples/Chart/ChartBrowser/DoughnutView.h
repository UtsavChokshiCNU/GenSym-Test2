#pragma once


#include "PieView.h"

// CDoughnutView form view

class CDoughnutView : public CPieView
{
	DECLARE_DYNCREATE(CDoughnutView)

protected:
	CDoughnutView(UINT nID = IDD);           // protected constructor used by dynamic creation
	virtual ~CDoughnutView();

public:
	enum { IDD = IDD_VIEW_DOUGHNUT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
public:
	int m_nHoleRadius;
	afx_msg void OnEnChangeEditHoleRadius();
};


