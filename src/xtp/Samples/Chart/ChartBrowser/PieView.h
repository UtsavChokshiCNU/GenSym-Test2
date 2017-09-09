#pragma once

#include "BaseView.h"

// CPieView form view

class CPieView : public CBaseView
{
	DECLARE_DYNCREATE(CPieView)

protected:
	CPieView(UINT nID = IDD);           // protected constructor used by dynamic creation
	virtual ~CPieView();

public:
	enum { IDD = IDD_VIEW_PIE };
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


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckShowlabels();
	BOOL m_bShowLabels;
	int m_nPosition;
	afx_msg void OnCbnSelchangeComboLabelPosition();
	afx_msg void OnCbnSelchangeComboExplodedPoints();
	int m_nExplodedPoints;
};


