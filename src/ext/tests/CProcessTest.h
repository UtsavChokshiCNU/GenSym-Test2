#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
extern long g2ext_unix_cmd_with_string_output_mx(char *command, char *buff, long max_bytes);
extern int g2ext_run_command_line(char  *command_string);
extern long g2ext_substatus_run_command_line(char *command_string);
extern double g2ext_spawn_command_directly(char *command_string);
extern double g2ext_spawn_command_line_process(char *command_string);
extern long g2ext_kill_spawned_command_line(double pid);
extern int g2ext_process_exists(double pid);
extern int g2ext_establish_sigchld_handler(void);
}

class CProcessTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(CProcessTest);
	CPPUNIT_TEST(test_g2ext_unix_cmd_with_string_output_mx);
	CPPUNIT_TEST(test_g2ext_run_command_line);
	CPPUNIT_TEST(test_g2ext_substatus_run_command_line);
	CPPUNIT_TEST(test_g2ext_spawn_command_directly);
	CPPUNIT_TEST(test_g2ext_spawn_command_line_process);
	CPPUNIT_TEST(test_g2ext_exists_kill_process);
	CPPUNIT_TEST_SUITE_END();

private:
	char _hostname[256];
	char _command1[256];
	char _command2[256];
	char _command3[256];
	char _command4[256];
	char _command5[256];

public:
	void setUp();
	void tearDown();
	void test_g2ext_unix_cmd_with_string_output_mx();
	void test_g2ext_run_command_line();
	void test_g2ext_substatus_run_command_line();
	void test_g2ext_spawn_command_directly();
	void test_g2ext_spawn_command_line_process();
	void test_g2ext_exists_kill_process();
};
