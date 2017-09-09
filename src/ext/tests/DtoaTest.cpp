#include "DtoaTest.h"
#include <math.h>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(DtoaTest);

void DtoaTest::setUp()
{
}

void DtoaTest::tearDown()
{
}

void DtoaTest::test_strtod()
{
    char *str="12.356";
    char *se;
    double d = strtod(str, &se);
    CPPUNIT_ASSERT(d == 12.356);

    //leading white spaces
    str = "		      4787496.1452367291";
    d = strtod(str, &se);
    CPPUNIT_ASSERT(d == 4787496.1452367291);
		
    //leading zeros
    str = "000009352.47852";
    d = strtod(str, &se);
    CPPUNIT_ASSERT(d == 9352.47852);
	
    //signed number
    str = " -1.235696547";
    d = strtod(str, &se);
    CPPUNIT_ASSERT(d == -1.235696547);

    //number with exponent	
    str = "2.36589647e19";
    d = strtod(str, &se);
    CPPUNIT_ASSERT(d == 2.36589647e19);
	
    //signed exponent
    str = " 4.786E-22";
    d = strtod(str, &se);
    CPPUNIT_ASSERT(d == 4.786E-22);
		
    //infinity number
    str="Infinity";
    d = strtod(str, &se);
    CPPUNIT_ASSERT( d == 0 );
		
    str="Nan";
    d = strtod(str, &se);
    CPPUNIT_ASSERT( d == 0 );

    //invalid string
    str="Hello";
    d = strtod(str, &se);
    CPPUNIT_ASSERT( d == 0 );

}

void DtoaTest::test_g2ext_dtoa()
{
    int decpt = 0, sign = 0, mode = 0, ndigits = 0;
    char *se;
    double d = sqrt(2.0);
	
    char *str = g2ext_dtoa(d, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT( !strcmp(str, "14142135623730951") && decpt == 1 && sign == 0);
    g2ext_freedtoa(str);
		
    //convert various numbers to ascii
    double d1 = 1.145879652347586;
    char *str1 = g2ext_dtoa(d1, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(str1, "1145879652347586") && decpt == 1  && sign == 0);
    g2ext_freedtoa(str1);

    double d2 = 1.0/7;
    char *str2 = g2ext_dtoa(d2, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(str2, "14285714285714285") && decpt == 0  && sign == 0);
    g2ext_freedtoa(str2);

    double d3 = -81.69854721369;
    char *str3 = g2ext_dtoa(d3, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(str3, "8169854721369") && decpt == 2 && sign == 1);
    g2ext_freedtoa(str3);

    double d4 = -2.346782E12;
    char *str4 = g2ext_dtoa(d4, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(str4, "2346782") && decpt == 13 && sign == 1);
    g2ext_freedtoa(str4);

    double d5 = 314.0;
    char *str5 = g2ext_dtoa(d5, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(str5, "314") && decpt == 3 && sign == 0 );
    g2ext_freedtoa(str5);
	
    //Infinity
    double x1 = 1.7E308 * 10;
    char *strx1 = g2ext_dtoa(x1, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(strx1, "Infinity") && decpt == 9999 && sign == 0);
    g2ext_freedtoa(strx1);

    //-Infinity
    double x2 = -1.7E308 * 10;
    char *strx2 = g2ext_dtoa(x2, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(strx2, "Infinity") && decpt == 9999 && sign == 1);
    g2ext_freedtoa(strx2);

    //Nan
    long long x3 = 0x7fffffffffffffff;
    double *p = (double*)&x3;
    char *strx3 = g2ext_dtoa(*p, mode, ndigits, &decpt, &sign, &se);
    CPPUNIT_ASSERT(!strcmp(strx3, "NaN") && decpt == 9999 && sign == 0);
    g2ext_freedtoa(strx3);
}

void DtoaTest::test_reversibility()
{
    int decpt = 0, sign = 0, mode = 0, ndigits = 0;
    char *se;
    char *sse;

    //double ==> ascii ==> double
    double d1 = sqrt(3.0);
    char *str = g2ext_dtoa(d1, mode, ndigits, &decpt, &sign, &se);
    string asciiStr(str);
    asciiStr.insert(decpt, 1, '.');
    double d2 = strtod(asciiStr.c_str(), &sse);
	
    //did the number conserve its value ?
    CPPUNIT_ASSERT( d1 == d2 );

    // ascii ==> double ==> ascii
    char *str1 = "3.689547125896478"; 
    double d = strtod(str1, &sse);
    char *str2 = g2ext_dtoa(d, mode, ndigits, &decpt, &sign, &se);
    string asciiStr2(str2);
    asciiStr2.insert(decpt, 1, '.');

    //did the number conserve its value ?
    CPPUNIT_ASSERT( !strcmp(str1, asciiStr2.c_str()) );
}
