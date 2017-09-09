/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "CStreamsTests.h"

TEST_F(test_g2ext_g2_stream_open, CStreamsTests) 
{
    char file_that_exists[] = "../../ext/tests/res/test.txt";
    int stream = g2ext_g2_stream_open(file_that_exists, 0);
    CPPUNIT_ASSERT(stream != FAILURE);
    g2ext_str_close(stream);
}

TEST_F(g2ext_g2_probe_file_exists_ascii, CStreamsTests)
{
    // This tests files that only have ASCII characters in them, which
    // should be portable to all platforms we support
    char *file_that_exists = "../../ext/tests/res/test.txt";
    CPPUNIT_ASSERT(file_that_exists != NULL);
    CPPUNIT_ASSERT_EQUAL(SUCCESS, g2ext_g2_probe_file(file_that_exists));
}

TEST_F(g2ext_g2_probe_file_s16_exists_ascii, CStreamsTests)
{
    // This tests files that only have ASCII characters in them, which
    // should be portable to all platforms we support
    g2chr16_t *file_that_exists = g2pvt_wdups16(L"../../ext/tests/res/test.txt");
    CPPUNIT_ASSERT(file_that_exists != NULL);
    CPPUNIT_ASSERT_EQUAL(SUCCESS, g2ext_g2_probe_file_s16(file_that_exists));
    free(file_that_exists);
}

TEST_F(g2ext_g2_probe_file_doesnt_exist, CStreamsTests)
{
    // This crazy file name shouldn't exist on any platform we
    // support. It's not strictly impossible on all, but unlikely
    // enough
    char *file_doesnt_exist = "//\\";
    CPPUNIT_ASSERT(file_doesnt_exist != NULL);
    CPPUNIT_ASSERT_EQUAL(FAILURE, g2ext_g2_probe_file(file_doesnt_exist));
}

TEST_F(g2ext_g2_probe_file_s16_doesnt_exist, CStreamsTests)
{
    // This crazy file name shouldn't exist on any platform we
    // support. It's not strictly impossible on all, but unlikely
    // enough
    g2chr16_t *file_doesnt_exist = g2pvt_wdups16(L"//\\");
    CPPUNIT_ASSERT(file_doesnt_exist != NULL);
    CPPUNIT_ASSERT_EQUAL(FAILURE, g2ext_g2_probe_file_s16(file_doesnt_exist));
    free(file_doesnt_exist);
}

TEST_F(g2ext_g2_probe_file_empty_name, CStreamsTests)
{
    char empty_filename = 0;
    CPPUNIT_ASSERT_EQUAL(FAILURE, g2ext_g2_probe_file(&empty_filename));
}

TEST_F(g2ext_g2_probe_file_s16_empty_name, CStreamsTests)
{
    g2chr16_t empty_filename = 0;
    CPPUNIT_ASSERT_EQUAL(FAILURE, g2ext_g2_probe_file_s16(&empty_filename));
}


#ifndef _WIN32
// This test doesn't make sense on Windows, as we use wide-string APIs
// for this purpose, so cyrillic is supported
TEST_F(g2ext_g2_probe_file_cyrillic_not_supported_on_C_locale, CStreamsTests)
{
    // "C" locale has to exist and it doesn't support Cyrillic
    CPPUNIT_ASSERT(NULL != setlocale(LC_ALL, "C"));

    // If we can't convert the file name, it's as if it doesn't exist
    g2chr16_t *cyrillic = g2pvt_wdups16(L"Шипак");
    CPPUNIT_ASSERT(cyrillic != NULL);
    CPPUNIT_ASSERT_EQUAL(FAILURE, g2ext_g2_probe_file_s16(cyrillic));
    free(cyrillic);

    // We are _not_ restoring the old locale for the same reasons as
    // the `g2_s16dup2mbs_cyrillic_en_US_UTF8` test.
}
#endif

// Verify whether g2ext_make_unique_filename can create a valid temporary filename
TEST_F(g2ext_make_unique_filename_valid_case, CStreamsTests)
{
    char buffer[MAX_TEMP_SIZE_OS], *prefix = "G2";
    long result = g2ext_make_unique_filename(prefix, MAX_TEMP_SIZE_OS, buffer);
    CPPUNIT_ASSERT(result == 1);
    CPPUNIT_ASSERT(strlen(prefix) < strlen(buffer));
}

// Verify whether g2ext_make_unique_filename answer an error code when buffer is too 
// small for a given prefix
TEST_F(g2ext_make_unique_filename_small_buffer_for_prefix, CStreamsTests)
{
    char buffer[MAX_TEMP_SIZE_OS], *prefix = "this_is_a_29_byte_long_prefix";
    long result = g2ext_make_unique_filename(prefix, 29, buffer);
    CPPUNIT_ASSERT(result == -1);
}

// Verify whether g2ext_make_unique_filename answer includes given prefix 
TEST_F(g2ext_make_unique_filename_prefix, CStreamsTests)
{
    char buffer[MAX_TEMP_SIZE_OS], *prefix = "";
	
    long result = g2ext_make_unique_filename(prefix, MAX_TEMP_SIZE_OS, buffer);
    CPPUNIT_ASSERT(result == 1);
    CPPUNIT_ASSERT(strlen(buffer) > 1);
	
    prefix = "G2";
    result = g2ext_make_unique_filename(prefix, MAX_TEMP_SIZE_OS, buffer);
    CPPUNIT_ASSERT(result == 1);
    CPPUNIT_ASSERT(strstr(buffer, prefix) > 0);
    CPPUNIT_ASSERT(strlen(buffer) > strlen(prefix) + 1);
}

//verify we can read the same char we already wrote
TEST_F(g2ext_test_write_read_char, CStreamsTests)
{
    char filePath[] = "../../ext/tests/res/test.txt";

    //write char to the stream
    long stream = g2ext_g2_stream_open(filePath, 1);    
    long result = g2ext_str_write_char('A', stream);
    CPPUNIT_ASSERT(result == 'A');
    g2ext_str_close(stream);

    //read char from the stream
    stream = g2ext_g2_stream_open(filePath, 0);    
    long character = g2ext_str_read_char(stream);
    g2ext_str_close(stream);

    CPPUNIT_ASSERT(character == 'A');
}

//read non cr characters
TEST_F(g2ext_test_write_buffer_read_non_cr, CStreamsTests)
{
    char filePath[] = "../../ext/tests/res/test.txt";
    char *buffer= "\r\nmlopqr";
    //write char to the stream
    long stream = g2ext_g2_stream_open(filePath, 1);    
    long result = g2ext_g2_stream_write_buffer (stream, buffer, 8, 0);
    CPPUNIT_ASSERT(result == 8);
    g2ext_str_close(stream);

    //read char from the stream
    stream = g2ext_g2_stream_open(filePath, 0);    
    long character = g2ext_str_read_non_cr_char(stream);
    CPPUNIT_ASSERT(character == '\n');

    character = g2ext_str_read_non_cr_char(stream);
    CPPUNIT_ASSERT(character == 'm');

    g2ext_str_close(stream);  
}

//verify we can write and read back the same string
TEST_F(g2ext_test_write_read_string, CStreamsTests)
{
    //write string to the stream
    char filePath[] = "../../ext/tests/res/test.txt";
    long stream = g2ext_g2_stream_open(filePath, 1);
    char *string="push me to the stream!";
    long result = g2ext_str_write_string(string, stream, 0);
    CPPUNIT_ASSERT(result == 22);
    g2ext_str_close(stream);   

    //read the string from the stream
    stream = g2ext_g2_stream_open(filePath, 0);
    char buffer[256];
    result = g2ext_g2_stream_read_string(stream, buffer, 256, 0);
    CPPUNIT_ASSERT(result == 22);
    g2ext_str_close(stream);  
    
    buffer[result] = '\0';
    CPPUNIT_ASSERT(!strcmp(string, buffer));
}

//verify wide string write and read
TEST_F(g2ext_test_write_read_wide_string, CStreamsTests)
{
    //write string to the stream
    char filePath[] = "../../ext/tests/res/test.txt";
    long stream = g2ext_g2_stream_open(filePath, 1);
    unsigned short *wide_string = (unsigned short *)L"ÖĝŒƞƐ";
    long result = g2ext_g2_stream_write_wide_buffer(stream, wide_string, 5, 0);
    CPPUNIT_ASSERT(result == 5);
    g2ext_str_close(stream);  

    //read the string from the stream
    stream = g2ext_g2_stream_open(filePath, 0);
    unsigned short wide_buffer[256];
    result = g2ext_g2_stream_read_wide_buffer(stream, wide_buffer, 256, 0);
    CPPUNIT_ASSERT(result == 5);
    g2ext_str_close(stream);  

    for(int i=0; i<result; i++)
    {
	CPPUNIT_ASSERT(wide_string[i] == wide_buffer[i]);
    }
}

TEST_F(g2ext_test_file_length_non_empty, CStreamsTests)
{
    char filePath[] = "../../ext/tests/res/test.txt";
    char *buffer= "ABC";
    //write 3 chars to the stream
    long stream = g2ext_g2_stream_open(filePath, 1);    
    long result = g2ext_g2_stream_write_buffer (stream, buffer, 3, 0);
    CPPUNIT_ASSERT(result == 3);
    g2ext_str_close(stream);

    //check length of the stream
    stream = g2ext_g2_stream_open(filePath, 0);
    long length = g2ext_str_file_length (stream);
    CPPUNIT_ASSERT(length == 3);
    long nonEmpty = g2ext_str_file_non_empty (stream);
    CPPUNIT_ASSERT(nonEmpty == 1);
    g2ext_str_close(stream);

    //truncate the file
    std::ofstream ofs;
    ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    //re-check length of the stream
    stream = g2ext_g2_stream_open(filePath, 0);
    length = g2ext_str_file_length (stream);
    CPPUNIT_ASSERT(length == 0);
    nonEmpty = g2ext_str_file_non_empty (stream);
    CPPUNIT_ASSERT(nonEmpty == 0);
}

TEST_F(g2ext_test_file_position, CStreamsTests)
{
    char filePath[] = "../../ext/tests/res/test.txt";
    char *buffer= "ABD";

    //get initial position when opened for output
    long stream = g2ext_g2_stream_open(filePath, 1);
    long current_position = g2ext_str_get_file_position (stream);
    CPPUNIT_ASSERT(current_position == 0);
    CPPUNIT_ASSERT(!g2ext_str_eof_p(stream));

    long result = g2ext_g2_stream_write_buffer (stream, buffer, 3, 0);
    current_position = g2ext_str_get_file_position (stream);
    CPPUNIT_ASSERT(current_position == 3);
    CPPUNIT_ASSERT(!g2ext_str_eof_p(stream));

    //replace D by C
    result = g2ext_str_set_file_position (stream, -1 , 1);
    current_position = g2ext_str_get_file_position (stream);
    CPPUNIT_ASSERT(current_position == 2);
    CPPUNIT_ASSERT(!g2ext_str_eof_p(stream));

    result = g2ext_str_write_char('C', stream);
    g2ext_str_close(stream);

    //open for reading and read the 3 characters one by one
    stream = g2ext_g2_stream_open(filePath, 0);
    long character = g2ext_str_read_char(stream);
    character = g2ext_str_read_char(stream);
    character = g2ext_str_read_char(stream);    
    CPPUNIT_ASSERT(character == 'C');
    current_position = g2ext_str_get_file_position (stream);
    CPPUNIT_ASSERT(current_position == 3);
    CPPUNIT_ASSERT(!g2ext_str_eof_p(stream));

    //read one more char and check we reach eof
    g2ext_str_read_char(stream);
    CPPUNIT_ASSERT(g2ext_str_eof_p(stream));
}
