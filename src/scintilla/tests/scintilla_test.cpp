// scintilla_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scintilla_test.h"

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
//int main(int argc,char** argv)
{
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
	
	bool result = runner.run();

	//Please use command "scintilla_test.exe -result path_to_file" to change default xml report file.
	const char* resultPath = "api-tests.xml";
	if ((argc == 3) && !strcmp(argv[1], "-result")) {
		resultPath = argv[2];
	}

    // Stream for writting XML report
    std::ofstream report(resultPath);
    // Create XML outputter and write report to file
    CppUnit::XmlOutputter(&runner.result(), report).write();
	
	CoUninitialize();
	return result ? 0 : -1;
}


