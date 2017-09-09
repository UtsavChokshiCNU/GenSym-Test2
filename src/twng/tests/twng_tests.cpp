/*
 * Main unit tests file.
 * Warning: twng.cpp is the changed twng.cpp from TWNG sources
 */

#include "stdafx.h"

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>

//#include "twng.h"

/*int start_tests();

BOOL CTwngApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CTwngApp::Run()
{
	return start_tests();
}

extern "C" {
	//int heap_command_line(int, char**);
	void init_top_level();
	void userinit();
}
*/

int main(int argc, char** argv)
{
    /* Process command line arguments */
//    heap_command_line(argc, argv);

    /* Set up Lisp system internals */
//    init_top_level();

    /* Application specific initialization */
//    userinit();

	// Initialize application
	// ----------------------
    CoInitialize(NULL);

	// Initilize console
	AllocConsole();

    // redirect STDOUT and STDERR to the console
    // ----------------------------------------------------
	{
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		int fdstdout = _open_osfhandle((long) hout, _O_TEXT);
		FILE *fp = _fdopen(fdstdout, "w");
 		*stdout = *fp;
	}
	{
		HANDLE herr = GetStdHandle(STD_ERROR_HANDLE);
		int fdstderr = _open_osfhandle((long) herr, _O_TEXT);
		FILE *fp = _fdopen(fdstderr, "w");
 		*stderr = *fp;
	}

	// Run unit tests
	// --------------
	CPPUNIT_NS::TextUi::TestRunner runner;
	runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	
	char const* testPath = argc < 2 ? "" : argv[1];

	//Please use command "twng_tests.exe -result path_to_file" to change default xml report file.
	const char* resultPath = "api-tests.xml";
	if ((argc == 3) && !strcmp(testPath, "-result")) {
		resultPath = argv[2];
		testPath = "";
	}

	// Stream for writting XML report
	std::ofstream report(resultPath);

    bool result = runner.run(testPath);
    // Create XML outputter and write report to file
    CppUnit::XmlOutputter(&runner.result(), report).write();

#if defined _DEBUG
	if (!result) {
		MessageBox(0, L"Analyze error reports, I must!", L"Failed I have", MB_OK);
	}
#endif

	CoUninitialize();
	return result ? 0 : -1;
}
