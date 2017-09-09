//----------------------------------------------------------------------------
#ifndef _ODBC_SQL_SERVER_TESTS_H
#define _ODBC_SQL_SERVER_TESTS_H
//----------------------------------------------------------------------------
#include <cppunit/extensions/HelperMacros.h>
//----------------------------------------------------------------------------

class ODBCSqlServerTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(ODBCSqlServerTest);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST(test_finish);

    CPPUNIT_TEST(test4);
    CPPUNIT_TEST(test5);
    CPPUNIT_TEST(test6);
  CPPUNIT_TEST_SUITE_END();

  public:
    ODBCSqlServerTest() {}
//	~ODBCSqlServerTest() { getchar(); }

    void test_init();
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test_finish();
};
//----------------------------------------------------------------------------
#endif // _ODBC_SQL_SERVER_TESTS_H
//----------------------------------------------------------------------------
