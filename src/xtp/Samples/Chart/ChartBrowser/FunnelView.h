#pragma once

#include "BaseView.h"

// CFunnelView form view

class CFunnelView : public CBaseView
{
	DECLARE_DYNCREATE(CFunnelView)

protected:
	CFunnelView(UINT nID = IDD);           // protected constructor used by dynamic creation
	virtual ~CFunnelView();

public:
	enum { IDD = IDD_VIEW_FUNNEL };
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
	BOOL m_bEqualHeight;
	afx_msg void OnCbnSelchangeComboLabelPosition();
	
	afx_msg void OnEditChangePointDistance();
	afx_msg void OnSelChangePointDistance();
	
	afx_msg void OnEditChangeHeightToWidth();
	afx_msg void OnSelChangeHeightToWidth();

	afx_msg void OnBnClickedCheckEqualHeight();

	CString m_strPointDistance;
	CComboBox m_cboPointDistance;

	CString m_strHeightToWidth;
	CComboBox m_cboHeightToWidth;

};


