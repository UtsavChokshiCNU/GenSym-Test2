#pragma once

#include "BaseView.h"


// CPointView form view

class CPointView : public CBaseView
{
	DECLARE_DYNCREATE(CPointView)

protected:
	CPointView();           // protected constructor used by dynamic creation
	virtual ~CPointView();

public:
	enum { IDD = IDD_VIEW_POINT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	BOOL m_bShowLabels;
	int m_nLabelAngle;
	int m_nMarkerType;
	int m_nMarkerSize;

	void CreateChart();

	void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCheckShowLabels();
	afx_msg void OnCbnSelchangeComboLabelAngle();
	afx_msg void OnCbnSelchangeComboMarkerSize();
	afx_msg void OnCbnSelchangeComboMarkerType();
public:
};


