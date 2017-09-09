//----------------------------------------------------------------------------
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/portability/Stream.h> // stdCErr()
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/XmlOutputter.h>
//----------------------------------------------------------------------------
extern "C" long debug = 0; // uses in gdb_utils.c
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    CPPUNIT_NS::TextTestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest()); // add the top suite to the runner

    CPPUNIT_NS::TestResult& mgr = runner.eventManager();
    CPPUNIT_NS::BriefTestProgressListener progress; // shows a message as each test starts
    mgr.addListener(&progress);

    CPPUNIT_NS::TestResultCollector& rc = runner.result();

    bool from_ide = argc > 1 && !strcmp(argv[1], "--ide"); // running test on post build event
	
    if (from_ide)
    {
        runner.setOutputter(new CPPUNIT_NS::CompilerOutputter(&rc, CPPUNIT_NS::stdCOut()));
    }
	
    try 
    {
        int idx = from_ide ? 2 : 1;
        const char* test_path = argc > idx ? argv[idx] : "";
        runner.run(test_path);
    } 
    catch (std::exception& e) 
    {
        CPPUNIT_NS::stdCErr() << std::endl 
			      << "ERROR: " 
			      << e.what() 
			      << std::endl;
    }

    // Create stream for writting XML report
    std::ofstream report("unittest.g2db.xml");
    // Create XML outputter and write report to stream
    CppUnit::XmlOutputter(&rc, report).write();

    return rc.wasSuccessful() ? 0 : 1;
}
//----------------------------------------------------------------------------
