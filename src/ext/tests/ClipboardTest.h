#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "cprim.h"

extern long g2ext_x11_read_cut_buffer(
				    long window_index,
				    char *buffer,
				    long max_size
				    );

extern long g2ext_x11_write_cut_buffer(
				    long window_index,
				    char *string,
				    long length
				    );
	 
extern long g2ext_read_clipboards (
				    long	     window_index,
				    char *	     latin_1_string,
				    long             latin_1_string_max_length,
				    long             latin_1_desired_p,
				    char *           compound_text_string,
				    long             compound_text_string_max_length,
				    long             compound_text_desired_p,
				    unsigned short * unicode_text_string,
				    long             unicode_text_string_max_length,
				    long             unicode_desired_p,
				    unsigned short * result_wide_string
				   );

extern long g2ext_write_clipboards (
				    long	     window_index,
				    char *	     latin_1_string,
				    long             latin_1_string_length,
				    char *           compound_text_string,
				    long             compound_text_string_length,
				    unsigned short * unicode_text_string,
				    long             unicode_text_string_length
				   );
extern int No_window;

}


class ClipboardTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(ClipboardTest);

	CPPUNIT_TEST(test_g2ext_x11_write_read_cut_buffer);
	CPPUNIT_TEST(test_g2ext_write_read_clipboards);

	CPPUNIT_TEST_SUITE_END();

private:
	long _window_index;
public:
	void setUp();
	void tearDown();
	void test_g2ext_x11_write_read_cut_buffer();
	void test_g2ext_write_read_clipboards();
};
