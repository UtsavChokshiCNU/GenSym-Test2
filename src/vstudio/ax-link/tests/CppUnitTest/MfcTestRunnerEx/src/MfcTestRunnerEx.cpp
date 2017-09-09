#include "StdAfx.h"
#include "afxmt.h"
#include <TestRunnerModel.h>
#include <MfcSynchronizationObject.h>
#include "MfcTestRunnerEx.h"
#include "TestRunnerExDlg.h"


MfcTestRunnerEx::MfcTestRunnerEx()
  : resultCollector(new MfcSynchronizationObject())
{
}


void 
MfcTestRunnerEx::run() 
{ 
	bool comInit = SUCCEEDED(CoInitialize( NULL));

	TestRunnerModel model(getRootTest());
	TestRunnerExDlg dlg(&model, &resultCollector); 
	dlg.DoModal(); 
	if (comInit)
		CoUninitialize();
}



CppUnit::TestResultCollector& MfcTestRunnerEx::result()
{
	return resultCollector;
}
