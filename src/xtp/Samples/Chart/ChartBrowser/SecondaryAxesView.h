#pragma once

#include "BaseView.h"

// CSecondaryAxesView form view

class CSecondaryAxesView : public CBaseView
{
	DECLARE_DYNCREATE(CSecondaryAxesView)

protected:
	CSecondaryAxesView();           // protected constructor used by dynamic creation
	virtual ~CSecondaryAxesView();

public:
	enum { IDD = IDD_VIEW_SECONDARYAXES };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	BOOL m_bSecondaryAxisX;
	BOOL m_bSecondaryAxisY;
	BOOL m_bVisibleX;
	BOOL m_bVisibleY;

	void OnCheckSecondaryAxisX();
	void OnCheckSecondaryAxisY();
	void OnCheckVisibleX();
	void OnCheckVisibleY();

	void CreateChart();

	void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
};


