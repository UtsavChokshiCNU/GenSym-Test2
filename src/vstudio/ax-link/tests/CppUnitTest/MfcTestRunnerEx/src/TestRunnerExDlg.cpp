#include "stdafx.h"
#include "mmsystem.h"
#include <cppunit/TestResultCollector.h>
#include <TestRunnerModel.h>
#include "TestRunnerExDlg.h"
#include "ProgressBar.h"
#include "MfcSynchronizationObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TestRunnerExDlg::TestRunnerExDlg(
        TestRunnerModel *model,
        CppUnit::TestResultCollector* resultCollector,
        const TCHAR* szDialogResourceId, CWnd* pParent)
        : TestRunnerDlg(model, szDialogResourceId,	pParent),
		  // store passed pointer to TestResultCollector
		  m_resultCollector(resultCollector)
{
}

BEGIN_MESSAGE_MAP(TestRunnerExDlg, cdxCDynamicDialog)
//{{AFX_MSG_MAP(TestRunnerExDlg)
    ON_BN_CLICKED(ID_RUN, OnRun)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Copy-pasted from TestRunnerDlg and slighty modified
// We cannot call base class method because 
// in this case we cannot add our TestResultCollector
// (m_resultCollector) to m_testObserver.
// See comments for added code lines.
void TestRunnerExDlg::OnRun() 
{
  // reset TestResultCollector to collect new results
  m_resultCollector->reset();

  if ( m_bIsRunning )
    return;

  m_selectedTest = m_model->selectedTest();

  if ( m_selectedTest == 0 )
    return;

  freeState(); 
  reset();

  beRunning();

  int numberOfTests = m_selectedTest->countTestCases();

  m_testsProgress->start( numberOfTests );

  
  m_result = new CPPUNIT_NS::TestResultCollector( new MfcSynchronizationObject() );
  m_testObserver = new CPPUNIT_NS::TestResult( new MfcSynchronizationObject() );
  m_testObserver->addListener( m_result );

  // add TestResultCollector to observer
  m_testObserver->addListener( m_resultCollector );

  m_testObserver->addListener( this );
  m_activeTest = new ActiveTest( m_selectedTest );

  m_testStartTime = timeGetTime();

  m_activeTest->run( m_testObserver );

  m_testEndTime = timeGetTime();
}
