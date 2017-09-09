#include "g2_odbc_src.h"

//----------------------------------------------------------------------------
namespace G2_ODBC
{
//----------------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION(G2ODBCTest);
//----------------------------------------------------------------------------
wchar_t g_DSN[] = L"gensym";
wchar_t g_User[] = L"gensym";
wchar_t g_Passwd[] = L"gensym";
//----------------------------------------------------------------------------
wchar_t g_BadUser[] = L"bad_username";
wchar_t g_BadPasswd[] = L"bad_password";
//--------------------------------------------------------------------------
wchar_t g_GSI_CONNECTION_STR[] = L"DSN=Gensym;UID=gensym;PWD=gensym";

//----------------------------------------------------------------------------

void G2ODBCTest::test_init()
{
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, sql_setup());
}
//----------------------------------------------------------------------------

void G2ODBCTest::test_finish()
{
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
}
//----------------------------------------------------------------------------

/*
*/
void G2ODBCTest::test_sql_connect()
{
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, sql_connect(g_User, g_Passwd, g_DSN));
	sql_disconnect(gsi_current_context());
}
//----------------------------------------------------------------------------

/*
*/
void G2ODBCTest::test_sql_connect_ex()
{
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, sql_connect_ex(g_GSI_CONNECTION_STR));
	sql_disconnect(gsi_current_context());
}
//----------------------------------------------------------------------------

/*
*/
void G2ODBCTest::test_sql_disconnect()
{
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, sql_connect(g_User, g_Passwd, g_DSN));
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, sql_disconnect(gsi_current_context()));
}
//----------------------------------------------------------------------------

/*
*/
void G2ODBCTest::test_process_connect()
{
	// connect db by sql_connect
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_connect(g_User, g_Passwd, g_DSN, L""));
	context[gsi_current_context()].available = TRUE;
	process_disconnect(TRUE, gsi_current_context());
	
	// connect db by sql_connect_ex
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_connect(L"", L"", L"", g_GSI_CONNECTION_STR));
	context[gsi_current_context()].available = TRUE;
	process_disconnect(TRUE, gsi_current_context());
}
//----------------------------------------------------------------------------

/*
*/
void G2ODBCTest::test_process_disconnect()
{
	// connect db by sql_connect
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_connect(g_User, g_Passwd, g_DSN, L""));
	context[gsi_current_context()].available = TRUE;
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_disconnect(TRUE, gsi_current_context()));
	
	// connect db by sql_connect_ex
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_connect(L"", L"", L"", g_GSI_CONNECTION_STR));
	context[gsi_current_context()].available = TRUE;
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_disconnect(TRUE, gsi_current_context()));
}
//----------------------------------------------------------------------------

/*
*/
void G2ODBCTest::test_process_reconnect()
{
	// connect db by sql_connect
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_connect(g_User, g_Passwd, g_DSN, L""));
	context[gsi_current_context()].available = TRUE;
	process_disconnect(FALSE,gsi_current_context()); 
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_reconnect());
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_disconnect(TRUE, gsi_current_context()));
	
	// connect db by sql_connect_ex
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_connect(L"", L"", L"", g_GSI_CONNECTION_STR));
	context[gsi_current_context()].available = TRUE;
	process_disconnect(FALSE,gsi_current_context());
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_reconnect());
	CPPUNIT_ASSERT_EQUAL(GDB_SUCCESS, process_disconnect(TRUE, gsi_current_context()));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
} // G2_ODBC
//----------------------------------------------------------------------------