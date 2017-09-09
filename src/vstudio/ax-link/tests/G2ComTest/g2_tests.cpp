#include "stdafx.h"

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>

CComModule _Module;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nCmdShow)
{
	// Initialize application
	// ----------------------
	CoInitialize(NULL);
	_Module.Init(NULL, hInstance);

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

    // Stream for writting XML report
    std::ofstream report("unittest.ax-link.g2com.xml");
    // Create XML outputter and write report to file
    CppUnit::XmlOutputter(&runner.result(), report).write();

	// Comment/Uncomment next line to hide/view results because console window is closed
	//getch();

	//
	_Module.Term();

	CoUninitialize();
	return result ? 0 : -1;
}
