#include <conio.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>

#include <setjmp.h>
#include "config.h"
#include "object.h"
#include "core.h"

extern "C" {
    #include "gensym.h"
}

int main(int argc, char* argv[])
{
	// Initialize G2 runtime system.
    //g2int_init_top_level();
    //g2int_userinit();

    CPPUNIT_NS::TextUi::TestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    
    bool result = runner.run();

	//Please use command "librtl_tests.exe -result path_to_file" to change default xml report file.
	const char* resultPath = "api-tests.xml";
	if ((argc == 3) && !strcmp(argv[1], "-result")) {
		resultPath = argv[2];
	}

    // Stream for writting XML report
    std::ofstream report(resultPath);
    // Create XML outputter and write report to file
    CppUnit::XmlOutputter(&runner.result(), report).write();

    // Comment/Uncomment next line to hide/view results because console window is closed
    return result ? 0 : -1;
}

