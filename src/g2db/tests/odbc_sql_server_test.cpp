//----------------------------------------------------------------------------
#undef  ODBCVER
#define ODBCVER 0x0300
//----------------------------------------------------------------------------
#include <windows.h>
#include <Sqlucode.h>
#include <sql.h>
#include <odbcss.h>
#include <gdb_utils.h> // wstrrepl
#include "odbc_sql_server_test.h"
//----------------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION(ODBCSqlServerTest);
//----------------------------------------------------------------------------

namespace
{

wchar_t g_DSN[] = L"gensym";
wchar_t g_User[] = L"gensym";
wchar_t g_Passwd[] = L"gensym";
//----------------------------------------------------------------------------
wchar_t g_BadUser[] = L"bad_username";
wchar_t g_BadPasswd[] = L"bad_password";


/*
	MS SQL Server rejects SQL strings which contain 
	unicode line separator (U+2028) character(s).
*/
wchar_t bad_sql[] = 
L"select count(*)\x2028"
L"from sys.all_views\x2028"
L"where 1=1";
//----------------------------------------------------------------------------
wchar_t good_sql[] = 
L"select count(*)\n"
L"from sys.all_views\n"
L"where 1=1";
//----------------------------------------------------------------------------

SQLHENV getEnv(bool del = false)
{
	static SQLHENV hEnv;
	
	if (!hEnv && !del)
	{
		SQLRETURN rc = SQLAllocEnv(&hEnv);
		CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));
	} else if (hEnv && del) {
		SQLRETURN rc = SQLFreeEnv(hEnv);
		CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));
		hEnv = 0;
	}

	return hEnv;
}
//--------------------------------------------------------------------------

SQLHDBC getConn(bool del = false)
{
	static SQLHDBC hDbc;
	
	if (!hDbc && !del)
	{
		SQLRETURN rc = SQLAllocConnect(getEnv(), &hDbc);
		CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));
	} else if (hDbc && del) {
		SQLRETURN rc = SQLFreeConnect(hDbc);
		CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));
		hDbc = 0;
	}
	
	return hDbc;
}
//--------------------------------------------------------------------------

bool openConnection( LPWSTR dsn, LPWSTR username, LPWSTR password )
{
	SQLRETURN rc = SQLConnectW( getConn(), 
							    dsn,	  SQL_NTS, 
							    username, SQL_NTS, 
							    password, SQL_NTS
		                      );

	return SQL_SUCCEEDED(rc);
}
//--------------------------------------------------------------------------

bool closeConnection()
{
	SQLRETURN rc = SQLDisconnect(getConn());
	return SQL_SUCCEEDED(rc);
}
//--------------------------------------------------------------------------

HSTMT createStatement()
{
	HSTMT hStmt = 0;
	
	SQLRETURN rc = SQLAllocStmt(getConn(), &hStmt);
	CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));
	
	return hStmt;
}
//--------------------------------------------------------------------------

void dropStatement(HSTMT hStmt)
{
	SQLRETURN rc = SQLFreeStmt(hStmt, SQL_DROP);
	CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));
}
//--------------------------------------------------------------------------

bool execDirect(HSTMT hStmt, LPWSTR sql)
{
	SQLRETURN rc = SQLExecDirectW(hStmt, sql, SQL_NTS);
	return SQL_SUCCEEDED(rc);
}
//--------------------------------------------------------------------------

SQLSMALLINT getColumnCount(HSTMT hStmt)
{
	SQLSMALLINT cnt = 0;
	
	SQLRETURN rc = SQLNumResultCols(hStmt, &cnt);
	CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));

	return cnt;
}
//--------------------------------------------------------------------------

} // namespace

//----------------------------------------------------------------------------

void ODBCSqlServerTest::test_init()
{
	openConnection(L"gensym", L"gensym", L"gensym");
}
//----------------------------------------------------------------------------

void ODBCSqlServerTest::test_finish()
{
	closeConnection();
	getConn(true);
	getEnv(true);
}
//----------------------------------------------------------------------------

/*
    Test simple SQL.
*/
void ODBCSqlServerTest::test1()
{
	HSTMT stmt = createStatement();
	CPPUNIT_ASSERT(execDirect(stmt, good_sql));
	
	SQLSMALLINT col_cnt = getColumnCount(stmt);
	CPPUNIT_ASSERT(col_cnt == 1);

	dropStatement(stmt);
}
//----------------------------------------------------------------------------

/*
	Test SQL with unicode LINE SEPARATOR characters.
*/
void ODBCSqlServerTest::test2()
{
	HSTMT stmt = createStatement();
	bool ok = execDirect(stmt, bad_sql); // must fail
	dropStatement(stmt);

	CPPUNIT_ASSERT(!ok);
}
//----------------------------------------------------------------------------

/*
	Test SQL with replaced unicode LINE SEPARATOR characters.
*/
void ODBCSqlServerTest::test3()
{
	HSTMT stmt = createStatement();
	
	wchar_t sql[sizeof(bad_sql)];
	wcscpy(sql, bad_sql);

	size_t cnt = wstrrepl(sql, L'\x2028', L'\n');
	CPPUNIT_ASSERT(cnt > 0);

	CPPUNIT_ASSERT(execDirect(stmt, sql));

	SQLSMALLINT col_cnt = getColumnCount(stmt);
	CPPUNIT_ASSERT(col_cnt == 1);
	
	dropStatement(stmt);
}
//----------------------------------------------------------------------------

/*
    Test DSN.
*/
void ODBCSqlServerTest::test4()
{
    CPPUNIT_ASSERT(openConnection(g_DSN, g_User, g_Passwd));
    CPPUNIT_ASSERT(closeConnection());
}
//----------------------------------------------------------------------------

/*
    Test DSN with invalid credentials.
*/
void ODBCSqlServerTest::test5()
{
    CPPUNIT_ASSERT(!openConnection(g_DSN, g_BadUser, g_BadPasswd));
}
//----------------------------------------------------------------------------

/*
    Test DSN with integrated security.
*/
void ODBCSqlServerTest::test6()
{
    closeConnection(); // must be closed

    SQLRETURN rc = SQLSetConnectAttr(getConn(), SQL_COPT_SS_INTEGRATED_SECURITY, (SQLPOINTER)SQL_IS_ON, 0);
    CPPUNIT_ASSERT(SQL_SUCCEEDED(rc));

    CPPUNIT_ASSERT(!openConnection(g_DSN, g_BadUser, g_BadPasswd));
    CPPUNIT_ASSERT(!closeConnection());
}
//----------------------------------------------------------------------------
