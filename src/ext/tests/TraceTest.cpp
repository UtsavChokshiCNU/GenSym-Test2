#include "TraceTest.h"
#include <fstream>
CPPUNIT_TEST_SUITE_REGISTRATION(TraceTest);

using namespace std;

void TraceTest::setUp()
{
}

void TraceTest::tearDown()
{
}


void TraceTest::test_g2ext_function_address()
{
    static fn_type * x_fn_array[] = {
    (fn_type *)0xa301,
    (fn_type *)0x2f85,
    (fn_type *)0x4621,
    (fn_type *)0x4785,
    (fn_type *)0x2598,
    (fn_type *)0x9521,
    (fn_type *)0x6985,
    (fn_type *)0x41fb,
    (fn_type *)0x8730,
    (fn_type *)0xfe39
    };

    static char *x_fn_name_array[] = {
     "USE-DATES-INSTEAD-OF-VERSIONS-P",
     "load-INIT",
     "GENSYM",
     "STRING-OR-SYMBOL-EQUAL",
     "EVAL-FEATURE",
     "SYSTEM-P",
     "SET-FILE-PROPERTY",
     "GET-FILE-PROPERTY",
     "GET-DEFAULT-INCLUDE-TEST",
     "NON-OPTIONAL-OR-INCLUDED-OPTIONAL-MODULE-P"
    };

    static int x_fn_file_size_array[] = {
	0,2,40,43,44,45,163,164,180,183
    };

    g2ext_note_fn_table_size(10, x_fn_array, x_fn_name_array, x_fn_file_size_array);

    char buffer1[1024];
    long result = g2ext_get_name_for_function(buffer1, (void*)0x4785);
    CPPUNIT_ASSERT(result == 22);
    CPPUNIT_ASSERT(strcmp(buffer1,"STRING-OR-SYMBOL-EQUAL") == 0);

    char buffer2[1024];
    result = g2ext_get_name_for_function(buffer2, (void*)0x41fb);
    CPPUNIT_ASSERT(result == 17);
    CPPUNIT_ASSERT(strcmp(buffer2,"GET-FILE-PROPERTY") == 0);
}

void TraceTest::test_g2ext_network_io_trace()
{
    g2ext_reset_network_io_trace();
    g2ext_enable_network_io_trace();

    long type1 = 2L;
    long handle1 = 100L;
    long fd1 = 5000L; 
    long length = 64L;
    g2ext_network_io_trace_begin(type1,handle1,fd1,length);

    long type2 = 4L;
    long handle2 = 100L;
    long fd2 = 1L;
    long ioresult = 4L;
    char *buffer = "ABCD";
    g2ext_network_io_trace_end(type2, handle2, fd2, ioresult, buffer);

    g2ext_network_io_trace_note("This is an important note!");

    char *file="./TestTrace.log";
    g2ext_write_network_io_trace(file);

    std::fstream traceFileStream(file);
    char line[1024];
    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "Begin Network Input/Output Trace") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strstr (line, "0               Note" ) != 0);
    CPPUNIT_ASSERT(strstr (line, "Enabling network io tracing" ) != 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strstr (line, "1         Begin Read" ) != 0);
    CPPUNIT_ASSERT(strstr (line, "Handle: 100, fd: 5000, Length: 64" ) != 0);
 
    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strstr (line, "2           End Read" ) != 0);
    CPPUNIT_ASSERT(strstr (line, "Handle: 100, fd: 1, Result: 4") != 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "065 066 067 068 ") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strstr (line, "3               Note" ) != 0);
    CPPUNIT_ASSERT(strstr (line, "This is an important note!") != 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "End Network Input/Output Trace") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "") == 0);
    CPPUNIT_ASSERT(traceFileStream.eof());
}

void TraceTest::test_g2ext_cons_trace()
{
    long cons1 = 456L;
    long cons2 = 6320L;
    void *name = 0;
    
    g2ext_enable_consing_trace();
    g2ext_note_allocate_cons((void*)cons1, name);
    g2ext_note_allocate_cons((void*)cons2, name);
    g2ext_note_reclaim_cons((void*)cons1, (void*)name);
    g2ext_note_reclaim_cons((void*)cons2, (void*)name);
    g2ext_note_reclaim_cons((void*)cons1, (void*)name);
    g2ext_note_reclaim_cons((void*)cons2, (void*)name);

    g2ext_enable_consing_trace();
    g2ext_note_allocate_cons((void*)cons1, (void*)name);
    g2ext_note_allocate_cons((void*)cons2, (void*)name);
    g2ext_note_allocate_cons((void*)cons1, (void*)name);
    g2ext_note_allocate_cons((void*)cons2, (void*)name);

    char *file="./TestConsTrace.log";
    g2ext_write_cons_summary(file);

    fstream traceFileStream(file);
    char line[1024];
    traceFileStream.getline(line, 1024);
    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "          4  1c8  allocate") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "          5  18b0  allocate") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "          6  1c8  reclaim ") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "          7  18b0  reclaim ") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "          8  1c8  reclaim ") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "          9  1c8  allocate") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "         10  18b0  allocate") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "         11  1c8  allocate") == 0);

    traceFileStream.getline(line, 1024);
    CPPUNIT_ASSERT(strcmp(line, "") == 0);
    CPPUNIT_ASSERT(traceFileStream.eof());
}
