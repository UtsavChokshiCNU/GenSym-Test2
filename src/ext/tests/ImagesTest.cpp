#include "ImagesTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ImagesTest);

void ImagesTest::setUp()
{

}

void ImagesTest::tearDown()
{

}

void ImagesTest::test_get_image_properties_truecolor()
{
    G2pointer istream;
    char errbuf[512];
    char *imgFile="../../ext/tests/res/SampleImg.jpg";
    istream = g2ext_open_image_stream(imgFile, errbuf, 512);
    CPPUNIT_ASSERT(istream != -1);

    long size = g2ext_image_stream_size(istream);
    long format = g2ext_image_stream_format(istream);
    long height = g2ext_image_stream_height(istream);
    long width = g2ext_image_stream_width(istream);
    long depth = g2ext_image_stream_depth(istream);
    long ncolor = g2ext_image_stream_ncolors (istream);

    CPPUNIT_ASSERT(size == 15728640);
    CPPUNIT_ASSERT(format == 5);
    CPPUNIT_ASSERT(height == 2048);
    CPPUNIT_ASSERT(width == 2560);
    CPPUNIT_ASSERT(depth == 24);
    CPPUNIT_ASSERT(ncolor == 0);

    g2ext_close_image_stream(istream);
}

void ImagesTest::test_get_image_properties_8bit()
{
    G2pointer istream;
    char errbuf[512];
    char *imgFile="../../ext/tests/res/8bitSample.jpg";
    istream = g2ext_open_image_stream(imgFile, errbuf, 512);
    CPPUNIT_ASSERT(istream != -1);

    long size = g2ext_image_stream_size(istream);
    long format = g2ext_image_stream_format(istream);
    long height = g2ext_image_stream_height(istream);
    long width = g2ext_image_stream_width(istream);
    long depth = g2ext_image_stream_depth(istream);
    long ncolor = g2ext_image_stream_ncolors (istream);

    CPPUNIT_ASSERT(size == 50268);
    CPPUNIT_ASSERT(format == 5);
    CPPUNIT_ASSERT(height == 177);
    CPPUNIT_ASSERT(width == 284);
    CPPUNIT_ASSERT(depth == 8);
    CPPUNIT_ASSERT(ncolor == 256);

    g2ext_close_image_stream(istream);
}

void ImagesTest::test_read_image_row()
{
    G2pointer istream;
    char errbuf[512];
    char *imgFile="../../ext/tests/res/SampleImg.jpg";
    istream = g2ext_open_image_stream(imgFile, errbuf, 512);
    CPPUNIT_ASSERT(istream != -1);

    long height = g2ext_image_stream_height(istream);
    long width = g2ext_image_stream_width(istream);
    long depth = g2ext_image_stream_depth(istream);
    
    long row_size = width*depth/8;

    unsigned char *buffer = ( unsigned char *)malloc(row_size);

    //read first row
    long result = g2ext_read_image_row (istream, buffer, row_size);
    CPPUNIT_ASSERT(result == row_size);
    CPPUNIT_ASSERT(buffer[0] == 158);
    CPPUNIT_ASSERT(buffer[100] == 190);
    CPPUNIT_ASSERT(buffer[5000] == 234);
    CPPUNIT_ASSERT(buffer[7000] == 186);

    //read all remaining rows
    for(int i = 1; i<height ; i++)
    {
	result = g2ext_read_image_row(istream, buffer, row_size);
	CPPUNIT_ASSERT(result == row_size);
    }

    //last row
    CPPUNIT_ASSERT(buffer[0] == 231);
    CPPUNIT_ASSERT(buffer[100] == 137);
    CPPUNIT_ASSERT(buffer[5000] == 38);
    CPPUNIT_ASSERT(buffer[7000] == 163);

    //read one more row
    result = g2ext_read_image_row(istream, buffer, row_size);
    CPPUNIT_ASSERT(result == 0);

    g2ext_close_image_stream(istream);
    free(buffer);
}

void ImagesTest::test_pixmap()
{
    //Create Blank pixmap 70 * 50 (24bit)
    long width = 70;
    long height = 50;
    long depth = 24;
    const long image_size = 70 * 50 *3;
    long bigmap_index = g2ext_create_bigmap(0, width, height, depth);

    unsigned char wide_string[image_size];
    memset((char*)wide_string, 'A', image_size);
    long result = g2ext_get_pixmap_bits(bigmap_index, width, height, width*3, (unsigned short *)wide_string);

    CPPUNIT_ASSERT(!strcmp((char*)wide_string, "")); 
}

void ImagesTest::test_get_truecolor_pixel()
{
    unsigned char pixels4x3[] = {
	123, 45, 23,  	255, 0, 0,   	98, 47, 56,   	189, 210, 36,
	45, 63, 102,  	205, 12, 23, 	26, 210, 120, 	10, 60, 89,
	100, 56, 79,	245, 250, 220,	17, 34, 46,	180, 156, 66
	};

    int result = g2ext_get_truecolor_pixel((unsigned short *)pixels4x3, 2, 1 , 12);

    int r = result & 0x0000FF;
    int g = (result & 0x00FF00) >> 8;
    int b = (result & 0xFF0000) >> 16;

    CPPUNIT_ASSERT(b == 26);
    CPPUNIT_ASSERT(g == 210);
    CPPUNIT_ASSERT(r == 120);
}