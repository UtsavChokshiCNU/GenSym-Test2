#pragma once
#if !defined(AFX_TESTRUNNEREXDLG_H)
#define AFX_TESTRUNNEREXDLG_H
#include <TestRunnerDlg.h>

class TestResultCollector;
class TestRunnerModel;

/////////////////////////////////////////////////////////////////////////////
// TestRunnerExDlg dialog
class TestRunnerExDlg : public TestRunnerDlg
{
public:
	TestRunnerExDlg(
		TestRunnerModel *model,
		CppUnit::TestResultCollector* resultCollector,
        const TCHAR* szDialogResourceId = NULL,
        CWnd* pParent = NULL);
protected:
  CppUnit::TestResultCollector* m_resultCollector;
  //{{AFX_MSG(TestRunnerExDlg)
  afx_msg void OnRun();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif