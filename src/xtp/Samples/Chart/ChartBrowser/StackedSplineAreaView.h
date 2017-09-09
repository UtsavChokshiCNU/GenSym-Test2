#pragma once

#include "BaseView.h"
	

// CStackedSplineAreaView form view

class CStackedSplineAreaView : public CBaseView
{
	DECLARE_DYNCREATE(CStackedSplineAreaView)

protected:
	CStackedSplineAreaView();           // protected constructor used by dynamic creation
	virtual ~CStackedSplineAreaView();

public:
	enum { IDD = IDD_VIEW_STACKEDSPLINEAREA };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void CreateChart();

	void OnInitialUpdate();

	void SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY);

	afx_msg void OnCbnSelchangeComboMarkerType();
	afx_msg void OnCbnSelchangeComboTransparency();
	afx_msg void OnCheckShowLabels();
	afx_msg void OnCbnSelchangeComboLabelAngle();
	afx_msg void OnCheck100();
	
	BOOL m_bShowLabels;
	int m_nLabelAngle;
	int m_nMarkerType;
	int m_nTransparency;
	BOOL m_b100;

	
	DECLARE_MESSAGE_MAP()
};


class CFullStackedSplineAreaView : public CStackedSplineAreaView
{
	DECLARE_DYNCREATE(CFullStackedSplineAreaView)
		
protected:
	CFullStackedSplineAreaView();           // protected constructor used by dynamic creation
	virtual void OnInitialUpdate();
	
};

