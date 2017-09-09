#pragma once

#include "BaseView.h"


// CMarkupTitleView form view

class CMarkupTitleView : public CBaseView
{
	DECLARE_DYNCREATE(CMarkupTitleView)

protected:
	CMarkupTitleView();           // protected constructor used by dynamic creation
	virtual ~CMarkupTitleView();

public:
	enum { IDD = IDD_VIEW_TITLE };
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

	CXTPChartTitle* m_pTitle;
	void SetTitle(CXTPChartTitle* pTitle);

	void OnCbnSelchangeComboDock();
	void OnCbnSelchangeComboAlignment();
	void OnEditChangedText();

	int m_nAlignment;
	int m_nDock;
	CString m_strText;

	DECLARE_MESSAGE_MAP()
};


