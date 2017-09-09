#pragma once

#include "BaseView.h"
	

// CStackedAreaView form view

class CStackedAreaView : public CBaseView
{
	DECLARE_DYNCREATE(CStackedAreaView)

protected:
	CStackedAreaView();           // protected constructor used by dynamic creation
	virtual ~CStackedAreaView();

public:
	enum { IDD = IDD_VIEW_STACKEDAREA };
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


class CFullStackedAreaView : public CStackedAreaView
{
	DECLARE_DYNCREATE(CFullStackedAreaView)

protected:
	CFullStackedAreaView();           // protected constructor used by dynamic creation
	virtual void OnInitialUpdate();

};

