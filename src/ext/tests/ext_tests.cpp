/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#ifdef _WIN32
#include <winsock2.h>
#endif

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>

extern "C" {
#include "cprim.h"
#include "networks.h"
#include "tcp.h"
}

int main(int argc, char* argv[])
{
#ifdef _WIN32
    WSADATA wsaData;
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
    {
        return 1;
    }
#endif
    
    //START modified by Tim for 43662 Gensym-01050-TAM1-IH-SUCA-JIRA-319-TestTCP test suite hangs up  2010.05.10
    //g2ext_max_number_of_sockets = 10;
    g2ext_max_number_of_sockets = 20;
    //END modified by Tim
    g2ext_initialize_socket_index_table();
    
    
    CPPUNIT_NS::TextUi::TestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    
    
    char const* testPath = argc < 2 ? "" : argv[1];
    
    //Please use command "ext_tests.exe -result path_to_file" to change default xml report file.
    const char* resultPath = "api-tests.xml";
    if ((argc == 3) && !strcmp(testPath, "-result")) {
        resultPath = argv[2];
        testPath = "";
    }
    bool result = runner.run(testPath);
    
    // Stream for writting XML report
    std::ofstream report(resultPath);
    
    // Create XML outputter and write report to file
    CppUnit::XmlOutputter(&runner.result(), report).write();
    
#ifdef _WIN32
    WSACleanup();
#endif

    return result ? 0 : -1;
}
