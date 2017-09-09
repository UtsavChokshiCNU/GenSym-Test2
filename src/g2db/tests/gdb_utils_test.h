//----------------------------------------------------------------------------
#ifndef _GDB_UTILS_TESTS_H
#define _GDB_UTILS_TESTS_H
//----------------------------------------------------------------------------
#include <cppunit/extensions/HelperMacros.h>
//----------------------------------------------------------------------------

class GdbUtilsTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(GdbUtilsTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST(test4);
  CPPUNIT_TEST_SUITE_END();

  public:
    GdbUtilsTest() {}

    void test1();
    void test2();
    void test3();
    void test4();
};
//----------------------------------------------------------------------------
#endif // _GDB_UTILS_TESTS_H
//----------------------------------------------------------------------------
