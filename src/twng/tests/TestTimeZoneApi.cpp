#include "stdafx.h"
#include "TestTimeZoneApi.h"

extern "C" {
	long g2ext_get_current_time_zone(unsigned short *buffer, long buflen)	;	
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestTimeZoneApi);

void TestTimeZoneApi::testGetTimeZoneInfo()
{
	const long MAX_BUF_LEN = 64;
	unsigned short buffer[MAX_BUF_LEN];
	long buflen = MAX_BUF_LEN;
	BOOL bPass = FALSE;

	long rez = g2ext_get_current_time_zone(buffer, buflen);
	
	if( rez > 0)
		bPass = TRUE;

	CPPUNIT_ASSERT(bPass);
}


void TestTimeZoneApi::setUp()
{

}

void TestTimeZoneApi::tearDown()
{

}
