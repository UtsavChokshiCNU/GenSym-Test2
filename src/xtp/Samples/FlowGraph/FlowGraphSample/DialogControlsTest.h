#pragma once

#include "FlowGraphSampleView.h"

// CDialogControlsTest dialog

class CDialogControlsTest : public CDialog
{
	DECLARE_DYNAMIC(CDialogControlsTest)

public:
	CDialogControlsTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogControlsTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTROLS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CXTPFlowGraphControl m_wndControl;

	CTreeCtrl m_wndTreeCtrl;
	CListCtrl m_wndListView;

	virtual BOOL OnInitDialog();
};
