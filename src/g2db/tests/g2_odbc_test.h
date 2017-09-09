//----------------------------------------------------------------------------
#ifndef _G2_ODBC_TEST_H_
#define _G2_ODBC_TEST_H_
//----------------------------------------------------------------------------
#include <cppunit/extensions/HelperMacros.h>
//----------------------------------------------------------------------------
namespace G2_ODBC
{
//----------------------------------------------------------------------------
class G2ODBCTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(G2ODBCTest);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_sql_connect);
    CPPUNIT_TEST(test_sql_connect_ex);
    CPPUNIT_TEST(test_sql_disconnect);
    CPPUNIT_TEST(test_process_connect);
    CPPUNIT_TEST(test_process_disconnect);
    CPPUNIT_TEST(test_process_reconnect);
    CPPUNIT_TEST(test_finish);
  CPPUNIT_TEST_SUITE_END();

  public:
    G2ODBCTest() {}

    void test_init();
    void test_sql_connect();
    void test_sql_connect_ex();
    void test_sql_disconnect();
    void test_process_connect();
    void test_process_disconnect();
    void test_process_reconnect();
    void test_finish();
};
//----------------------------------------------------------------------------
} // G2_ODBC
//----------------------------------------------------------------------------
#endif // _G2_ODBC_TEST_H_
//----------------------------------------------------------------------------
