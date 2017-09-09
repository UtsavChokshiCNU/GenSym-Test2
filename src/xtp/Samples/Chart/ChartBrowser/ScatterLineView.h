#pragma once

#include "BaseView.h"

// CScatterLineView form view

class CScatterLineView : public CBaseView
{
	DECLARE_DYNCREATE(CScatterLineView)

protected:
	CScatterLineView();           // protected constructor used by dynamic creation
	virtual ~CScatterLineView();

public:
	enum { IDD = IDD_VIEW_LINE };
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

	void OnCheckShowLabels();
	void OnCheckShowMarkers();
	void OnCbnSelchangeComboMarkerSize();
	void OnCbnSelchangeComboMarkerType();


	void CreateChart();

	void OnInitialUpdate();

	void SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY);

	DECLARE_MESSAGE_MAP()
};


