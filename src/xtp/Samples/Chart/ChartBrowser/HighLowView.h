#pragma once


#include "BaseView.h"
// CHighLowView form view

class CHighLowView : public CBaseView
{
	DECLARE_DYNCREATE(CHighLowView)

protected:
	CHighLowView(UINT nIDD = IDD);           // protected constructor used by dynamic creation
	virtual ~CHighLowView();

public:
	enum { IDD = IDD_VIEW_HIGHLOW };
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

	BOOL m_bThickStyle;
	void OnCheckThickStyle();


	DECLARE_MESSAGE_MAP()
};


