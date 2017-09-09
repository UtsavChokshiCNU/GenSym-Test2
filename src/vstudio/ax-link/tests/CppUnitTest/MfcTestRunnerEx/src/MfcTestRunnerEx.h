#pragma once
#if !defined(AFX_MFCTESTRUNNEREX_H)
#define AFX_MFCTESTRUNNEREX_H

#include <cppunit/ui/mfc/TestRunner.h>
#include <cppunit/TestResultCollector.h>


class AFX_EXT_CLASS MfcTestRunnerEx: public CppUnit::MfcTestRunner
{
public:
	MfcTestRunnerEx();
	void run();
	CppUnit::TestResultCollector& result();
private:
	CppUnit::TestResultCollector resultCollector;
};

#endif