#pragma once


#include "BaseView.h"
// CBubbleView form view

class CBubbleView : public CBaseView
{
	DECLARE_DYNCREATE(CBubbleView)

protected:
	CBubbleView();           // protected constructor used by dynamic creation
	virtual ~CBubbleView();

public:
	enum { IDD = IDD_VIEW_BUBBLE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


	void CreateChart();

	void OnInitialUpdate();

	void UpdateBubbleSize();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditMin();
	double m_dMinSize;
	double m_dMaxSize;
	int m_nMarkerType;
	afx_msg void OnEnChangeEditMax();
	afx_msg void OnCbnSelchangeComboTransparency();
	afx_msg void OnCbnSelchangeComboMarkerType();
	int m_nTransparency;
};


