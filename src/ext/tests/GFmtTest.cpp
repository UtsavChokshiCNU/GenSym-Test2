#include "GFmtTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(GFmtTest);

void GFmtTest::setUp()
{

}

void GFmtTest::tearDown()
{

}

void GFmtTest::test_g_fmt_common()
{
    char buffer1[64];
    char buffer2[64];
    char buffer3[64];
    char buffer4[64];
    char buffer5[64];

    double x1 = 1.145879652347586;
    double x2 = 1.0/7;
    double x3 = -81.69854721369;
    double x4 = -2.346782E12;
    double x5 = 314.0;

    g2ext_g_fmt(buffer1, x1);
    g2ext_g_fmt(buffer2, x2);
    g2ext_g_fmt(buffer3, x3);
    g2ext_g_fmt(buffer4, x4);
    g2ext_g_fmt(buffer5, x5);

    CPPUNIT_ASSERT(!strcmp(buffer1, "1.145879652347586"));
    CPPUNIT_ASSERT(!strcmp(buffer2, "0.14285714285714285"));
    CPPUNIT_ASSERT(!strcmp(buffer3, "-81.69854721369"));
    CPPUNIT_ASSERT(!strcmp(buffer4, "-2.346782e+12"));
    CPPUNIT_ASSERT(!strcmp(buffer5, "314.0"));
}

void GFmtTest::test_g_fmt_limits()
{
    char buffer1[64];
    char buffer2[64];
    char buffer3[64];
    char buffer4[64];

    double x1 = 1.7E308;
    double x2 = 1.7E-308;
    double x3 = -1.7E308;
    double x4 = -1.7E-308;

    g2ext_g_fmt(buffer1, x1);
    g2ext_g_fmt(buffer2, x2);
    g2ext_g_fmt(buffer3, x3);
    g2ext_g_fmt(buffer4, x4);

    CPPUNIT_ASSERT(!strcmp(buffer1, "1.7e+308"));
    CPPUNIT_ASSERT(!strcmp(buffer2, "1.6999999999999997e-308"));
    CPPUNIT_ASSERT(!strcmp(buffer3, "-1.7e+308"));
    CPPUNIT_ASSERT(!strcmp(buffer4, "-1.6999999999999997e-308"));
}

void GFmtTest::test_g_fmt_infinityAndNaN()
{
    char buffer1[64];
    char buffer2[64];
    char buffer3[64];

    double x1 = 1.7E308 * 10;
    double x2 = -1.7E308 * 10;
    long long x3 = 0x7fffffffffffffff;
    double *p = (double*)&x3;

    g2ext_g_fmt(buffer1, x1);
    g2ext_g_fmt(buffer2, x2);
    g2ext_g_fmt(buffer3, *p);

    CPPUNIT_ASSERT(!strcmp(buffer1, "Infinity"));
    CPPUNIT_ASSERT(!strcmp(buffer2, "-Infinity"));
    CPPUNIT_ASSERT(!strcmp(buffer3, "NaN"));
}