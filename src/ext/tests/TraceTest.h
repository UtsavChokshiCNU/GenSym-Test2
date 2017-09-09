#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "cprim.h"
typedef void fn_type();
extern void g2ext_note_fn_table_size(int size, fn_type *fn_array[],char *fn_name_array[], int fn_file_size_array[]);
extern long g2ext_get_name_for_function(char *buffer,void *addr);
extern void g2ext_reset_network_io_trace();
extern void g2ext_enable_network_io_trace();
extern void g2ext_enable_consing_trace();
extern void g2ext_network_io_trace_begin(long type,long handle,long fd,long length);
extern void g2ext_network_io_trace_end(long type,long handle,long fd,long io_result,char *buffer);
extern void g2ext_network_io_trace_note(char *note_string);
extern void g2ext_note_allocate_cons(void *cons, void *name);
extern void g2ext_note_reclaim_cons(void *cons, void * name);
extern void g2ext_write_network_io_trace(char *file);
extern void g2ext_write_cons_summary(char *file);  
}


class TraceTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(TraceTest);
	CPPUNIT_TEST(test_g2ext_function_address);
	CPPUNIT_TEST(test_g2ext_network_io_trace);
	CPPUNIT_TEST(test_g2ext_cons_trace);
	CPPUNIT_TEST_SUITE_END();

private:

public:
	void setUp();
	void tearDown();
	void test_g2ext_function_address();
	void test_g2ext_network_io_trace();
	void test_g2ext_cons_trace();
};