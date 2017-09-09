#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {

#include "Cprim.h"	
extern long g2ext_open_image_stream (char *pathname, char *errbuf, long errlen);
extern long g2ext_close_image_stream (G2pointer istream);
extern long g2ext_image_stream_size(G2pointer istream);
extern long g2ext_image_stream_format (G2pointer istream);
extern long g2ext_image_stream_height (G2pointer istream);
extern long g2ext_image_stream_width(G2pointer istream);
extern long g2ext_image_stream_depth (G2pointer istream);
extern long g2ext_image_stream_ncolors (G2pointer istream);
extern long g2ext_read_image_row(G2pointer istream, unsigned char *buffer, long buflen);
extern long g2ext_create_bigmap(long window_index, long width, long height, long depth);
extern long g2ext_get_pixmap_bits(long bigmap_index, long cx, long cy, long stride, unsigned short *wide_string);
extern long g2ext_get_truecolor_pixel(unsigned short *wide_string, long x, long y, long stride);
						   
}

class ImagesTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(ImagesTest);
	CPPUNIT_TEST(test_get_image_properties_truecolor);
	CPPUNIT_TEST(test_get_image_properties_8bit);
	CPPUNIT_TEST(test_read_image_row);
	CPPUNIT_TEST(test_pixmap);
	CPPUNIT_TEST(test_get_truecolor_pixel);
	CPPUNIT_TEST_SUITE_END();

private:

public:
	void setUp();
	void tearDown();
	void test_get_image_properties_truecolor();
	void test_get_image_properties_8bit();
	void test_read_image_row();
	void test_pixmap();
	void test_get_truecolor_pixel();
};
