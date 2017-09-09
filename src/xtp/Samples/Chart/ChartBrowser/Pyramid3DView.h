#pragma once

#include "BaseView.h"

// CPyramid3DView form view

class CPyramid3DView : public CBaseView
{
	DECLARE_DYNCREATE(CPyramid3DView)

protected:
	CPyramid3DView(UINT nID = IDD);           // protected constructor used by dynamic creation
	virtual ~CPyramid3DView();

public:
	enum { IDD = IDD_VIEW_PYRAMID3D };
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
	
	afx_msg void OnEditChangePointDistance();
	afx_msg void OnSelChangePointDistance();
	
	afx_msg void OnEditChangeTransparency();
	afx_msg void OnSelChangeTransparency();

	CString m_strPointDistance;
	CComboBox m_cboPointDistance;

	CString m_strTransparency;
	CComboBox m_cboTransparency;

};


