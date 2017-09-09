#pragma once

#include "BaseView.h"


// CAreaView form view

class CAreaView : public CBaseView
{
	DECLARE_DYNCREATE(CAreaView)

protected:
	CAreaView();           // protected constructor used by dynamic creation
	virtual ~CAreaView();

public:
	enum { IDD = IDD_VIEW_AREA };
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

	BOOL m_bShowLabels;
	int m_nLabelAngle;
	int m_nMarkerType;
	int m_nTransparency;

	DECLARE_MESSAGE_MAP()
};


