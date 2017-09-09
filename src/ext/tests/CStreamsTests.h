#pragma once
#include "GoogleStyleTest.h"
#include "cstreams.h"
extern "C" {
#include "cprim.h"
#ifdef _WIN32
#define MAX_TEMP_SIZE_OS MAX_PATH
#else
#define MAX_TEMP_SIZE_OS L_tmpnam
#endif

extern long g2ext_g2_probe_file(char *pathname);
extern long g2ext_g2_probe_file_s16(g2chr16_t *pathname);
extern long g2ext_make_unique_filename(char *id_suggestion, int buffer_size, char *buffer);
extern long g2ext_str_write_char (long character, long stream_index);
extern long g2ext_str_read_char(long stream_index);
extern long g2ext_g2_stream_write_buffer (long stream_index, char *buffer, long number_of_characters, long start_index);
extern long g2ext_str_read_non_cr_char (long stream_index);
extern long g2ext_str_write_string(char *string, long stream_index, long write_newline_p);
extern long g2ext_g2_stream_read_string(long stream_index, char string[], long number_of_characters, long start_index);
extern long g2ext_g2_stream_write_wide_buffer(long stream_index, unsigned short *wide_string_buffer, long number_of_16_bit_characters, long start_index);
extern long g2ext_g2_stream_read_wide_buffer(long stream_index, unsigned short *wide_string_buffer, long number_of_16_bit_characters, long start_index);
extern long g2ext_str_file_length (long stream_index);
extern long g2ext_str_file_non_empty (long stream_index);
extern long g2ext_str_set_file_position (long stream_index, long new_position, long seek_mode);
extern long g2ext_str_get_file_position (long stream_index);
extern long g2ext_str_eof_p (long stream_index);
}

extern g2chr16_t *g2pvt_wdups16(wchar_t const*src);

class CStreamsTests: public GoogleStyleTest<CStreamsTests> {

public:
	void test_g2ext_g2_stream_open();
	void g2ext_g2_probe_file_exists_ascii();
	void g2ext_g2_probe_file_s16_exists_ascii();
	void g2ext_g2_probe_file_doesnt_exist();
	void g2ext_g2_probe_file_s16_doesnt_exist();
	void g2ext_g2_probe_file_empty_name();
	void g2ext_g2_probe_file_s16_empty_name();
	#ifndef _WIN32
	g2ext_g2_probe_file_cyrillic_not_supported_on_C_locale();
	#endif
	void g2ext_make_unique_filename_valid_case();
	void g2ext_make_unique_filename_small_buffer_for_prefix();
	void g2ext_make_unique_filename_prefix();
	void g2ext_test_write_read_char();
	void g2ext_test_write_buffer_read_non_cr();
	void g2ext_test_write_read_string();
	void g2ext_test_write_read_wide_string();
	void g2ext_test_file_length_non_empty();
	void g2ext_test_file_position();
};