#pragma once

#include "BaseView.h"

// CMultipleView form view

class CMultipleView : public CBaseView
{
	DECLARE_DYNCREATE(CMultipleView)

protected:
	CMultipleView();           // protected constructor used by dynamic creation
	virtual ~CMultipleView();

public:
	enum { IDD = IDD_VIEW_MULTIPLEVIEW};
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

	void OnChartClick(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/);

	void OnSize(UINT nType, int cx, int cy);
	void OnCheckShowLabels();
	void OnCheck3DStyle();

	BOOL m_bShowLabels;
	BOOL m_b3DStyle;

	CChartBorder<CXTPChartControl> m_wndControlLeft;
	CChartBorder<CXTPChartControl> m_wndControlRight;

	CXTPChartContent* m_pContent;

	DECLARE_MESSAGE_MAP()
};


