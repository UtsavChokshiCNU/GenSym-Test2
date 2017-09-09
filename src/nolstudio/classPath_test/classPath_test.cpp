// classPath_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "classPath_test.h"
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

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
{
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
	
	// Comment/Uncomment next lines to hide/view results because console window is closed
	printf("Press any key to exit");
	getch();
	
	
	CoUninitialize();
	return result ? 0 : -1;
}


