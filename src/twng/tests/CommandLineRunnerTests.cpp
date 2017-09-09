#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "CommandLineRunner.h"

class CommandLineRunnerTests : public CPPUNIT_NS::TestFixture  
{
  CPPUNIT_TEST_SUITE(CommandLineRunnerTests);
    CPPUNIT_TEST(testRun);
  CPPUNIT_TEST_SUITE_END();

public:
	void testRun()
	{
		CommandLineRunner runner;
		wchar_t cmd[20];
		wcscpy_s(cmd, L"cmd /c java");
		CPPUNIT_ASSERT(runner.run(cmd));
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(CommandLineRunnerTests);

/*
cmd /c java -cp d:\Gensym\branches\SBCL_dev_branch-44340-mine\src\vstudio2008\twng\test-debug\jfree\jfree-lib.jar;d:\Gensym\branches\SBCL_dev_branch-44340-mine\src\vstudio2008\twng\test-debug\jfree\jfreechart-1.0.13.jar;d:\Gensym\branches\SBCL_dev_branch-44340-mine\src\vstudio2008\twng\test-debug\jfree\jcommon-1.0.16.jar gensym.charts.ChartsRunner 4000
*/
