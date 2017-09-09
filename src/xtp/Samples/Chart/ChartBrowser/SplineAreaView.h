#pragma once

#include "BaseView.h"
// CSplineAreaView dialog

class CSplineAreaView : public CBaseView
{
	DECLARE_DYNCREATE(CSplineAreaView)

public:
	CSplineAreaView();
	virtual ~CSplineAreaView();
// Overrides

// Dialog Data
	enum { IDD = IDD_VIEW_SPLINEAREA};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void CreateChart();
	
	void OnInitialUpdate();
	
	void SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY);
	
	afx_msg void OnCbnSelchangeComboMarkerType();
	afx_msg void OnCbnSelchangeComboTransparency();
	afx_msg void OnCheckShowLabels();
	afx_msg void OnCbnSelchangeComboLabelAngle();
	
	BOOL m_bShowLabels;
	int m_nLabelAngle;
	int m_nMarkerType;
	int m_nTransparency;

	DECLARE_MESSAGE_MAP()
};
