#pragma once

#include "FlowGraphSampleView.h"


#ifndef __XTPRESIZEDIALOG_H__
#define CXTPResizeDialog CDialog
#endif

// CDialogPerfomanceTest dialog

class CDialogPerfomanceTest : public CXTPResizeDialog
{
	DECLARE_DYNAMIC(CDialogPerfomanceTest)

public:
	CDialogPerfomanceTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogPerfomanceTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_PERFOMANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CXTPFlowGraphControl m_wndControl;
	int m_nSmoothingMode;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonArrange();
	afx_msg void OnSmoothingModeChanged();
};
