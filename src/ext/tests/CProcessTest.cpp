#include "CProcessTest.h"
#if defined(WIN32)
#include <Winsock2.h> //gethostname
#include <windows.h>
#else
#include <unistd.h>
#endif

#if defined(WIN32)
inline void delay( unsigned long ms )
{
    Sleep( ms );
}
#else
inline void delay( unsigned long ms )
{
    usleep( ms * 1000 );
}
#endif

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(CProcessTest);

void CProcessTest::setUp()
{
    //get hostname
    gethostname(_hostname, 256);
#if defined(WIN32)
    //commands to be used for windows process testing
    strcpy(_command1, "cmd /c echo test123 > processtmp1.txt");
    strcpy(_command2, "cmd /c echo working > processtmp2.txt");
    strcpy(_command3, "cmd /c echo voila > processtmp3.txt");
    strcpy(_command4, "echo HappyDay!!! > processtmp4.txt");
    strcpy(_command5, "FOR /L %i IN (0,1,1000000) DO @echo %i");
#else
    //commands to be used for Linux process testing
    strcpy(_command1, "echo test123 > processtmp1.txt");
    strcpy(_command2, "echo working > processtmp2.txt");
    strcpy(_command3, "touch processtmp3.txt");
    strcpy(_command4, "echo HappyDay!!! > processtmp4.txt");
    strcpy(_command5, "sleep 1000");

    g2ext_establish_sigchld_handler();
#endif
}

void CProcessTest::tearDown()
{
#if defined(WIN32) 
   system("del /f processtmp1.txt 2>null");
   system("del /f processtmp2.txt 2>null");
   system("del /f processtmp3.txt 2>null");
   system("del /f processtmp4.txt 2>null");
#else
    system("rm -f processtmp1.txt");
    system("rm -f processtmp2.txt");
    system("rm -f processtmp3.txt");
    system("rm -f processtmp4.txt");
#endif
}

void CProcessTest::test_g2ext_unix_cmd_with_string_output_mx()
{  
    //use cmd to get hostname
    char *command = "hostname";
    char buff[1024];

    long result = g2ext_unix_cmd_with_string_output_mx(command, buff, 1024);

    //compare the 2 hostnames
    CPPUNIT_ASSERT(result == 0);
    CPPUNIT_ASSERT(!strncmp(buff, _hostname, strlen(_hostname)));
}

void CProcessTest::test_g2ext_run_command_line()
{
    char  *command_string = _command1;

    //execute cmd
    g2ext_run_command_line(command_string);
    
    //check result of cmd execution
    ifstream f("processtmp1.txt");
    string buff;
    f >> buff;
    f.close();
    CPPUNIT_ASSERT(!strcmp(buff.c_str(), "test123"));
}


void CProcessTest::test_g2ext_substatus_run_command_line()
{
    char *command_string = _command2;
    long status = g2ext_substatus_run_command_line(command_string);

    //check returned status
    CPPUNIT_ASSERT(status == 0);

    //check result of cmd execution
    ifstream f("processtmp2.txt");
    string buff;
    f >> buff;
    f.close();
    CPPUNIT_ASSERT(!strcmp(buff.c_str(), "working"));
}

void CProcessTest::test_g2ext_spawn_command_directly()
{
    char *command_string= _command3;
    double pid = g2ext_spawn_command_directly(command_string);

    //check returned status
    CPPUNIT_ASSERT(pid > 0);

    //wait for some time untill file is closed
    delay(200);

    //check file existence
    ifstream f("processtmp3.txt");
    CPPUNIT_ASSERT(f);
}

void CProcessTest::test_g2ext_spawn_command_line_process()
{
    char *command_string= _command4;
    double pid = g2ext_spawn_command_line_process(command_string);

    //check returned status
    CPPUNIT_ASSERT(pid > 0);

    //wait for some time untill file is closed
    delay(200);

    //check result of cmd execution
    ifstream f("processtmp4.txt");
    string buff;
    f >> buff;
    f.close();
    CPPUNIT_ASSERT(!strcmp(buff.c_str(), "HappyDay!!!"));
}


void CProcessTest::test_g2ext_exists_kill_process()
{
    //spawn long run process
    char *command_string = _command5;
    double pid = g2ext_spawn_command_line_process(command_string);

    //check existance of spawned process
    int exists = g2ext_process_exists(pid);
    CPPUNIT_ASSERT(exists == 1);

    //kill running spwaned process
    long status = g2ext_kill_spawned_command_line(pid);
    CPPUNIT_ASSERT(status == 0);
    
    //wait for 1 sec untill process is dead
    delay(1000);

    //check spawned process is dead
    exists = g2ext_process_exists(pid);
    CPPUNIT_ASSERT(exists == 0);
}
