#pragma once

#include "BaseView.h"

// CStepLineView form view

class CStepLineView : public CBaseView
{
	DECLARE_DYNCREATE(CStepLineView)

protected:
	CStepLineView();           // protected constructor used by dynamic creation
	virtual ~CStepLineView();

public:
	enum { IDD = IDD_VIEW_STEPLINE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	BOOL m_bShowLabels;
	BOOL m_bShowMarkers;
	int m_nMarkerType;
	int m_nMarkerSize;
	BOOL m_bInvertedStep;

	void OnCheckShowLabels();
	void OnCheckShowMarkers();
	void OnCbnSelchangeComboMarkerSize();
	void OnCbnSelchangeComboMarkerType();
	void OnCheckInvertedStep();

	void CreateChart();

	void OnInitialUpdate();

	void SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY);

	DECLARE_MESSAGE_MAP()
};


