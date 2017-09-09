#pragma once

#include "BaseView.h"


// CRadarSplineView form view

class CRadarSplineView : public CBaseView
{
	DECLARE_DYNCREATE(CRadarSplineView)

protected:
	CRadarSplineView();           // protected constructor used by dynamic creation
	virtual ~CRadarSplineView();

public:
	enum { IDD = IDD_VIEW_RADARSPLINE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	BOOL m_bShowLabels;

	BOOL m_bShowAxisX;
	BOOL m_bShowAxisY;

	BOOL m_bInterlaced;

	void CreateChart();

	void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCheckShowLabels();
	afx_msg void OnCheckShowAxisX();
	afx_msg void OnCheckShowAxisY();
	afx_msg void OnCheckInterlaced();
public:
};


