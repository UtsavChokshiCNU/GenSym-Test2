//----------------------------------------------------------------------------
#ifndef _G2_ODBC_SRC_H_
#define _G2_ODBC_SRC_H_
//----------------------------------------------------------------------------
#include <windows.h>
#include <Sqlucode.h>
#include <sql.h>
#include <odbcss.h>
#include "g2_odbc_test.h"
#include "gsi_main.h"
#include "gdb_globals.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "GDB_CLIENT_ODBC.H"
#include "GDB_UTILS.H"
//----------------------------------------------------------------------------
namespace G2_ODBC
{
extern ODBCERR          g_sqlca;
extern gsi_int context_num;
extern CONTEXT_INFO context[MAX_GDB_CONTEXTS];
extern SQLHDBC hdbc[MAX_GDB_CONTEXTS];
extern SQLRETURN           rc;
extern SQLHENV             henv;
extern wchar_t             proc_spt[MAX_GDB_CONTEXTS][5] ;
extern float               driver_version[MAX_GDB_CONTEXTS];
extern SQLHSTMT            hstmt[MAX_GDB_CONTEXTS][MAX_CURSORS+1];
extern SQLHSTMT            trig_hstmt[MAX_GDB_CONTEXTS];
extern long             row_count[MAX_GDB_CONTEXTS]; 

extern BRIDGE_INFO bridge_info ;

gsi_int gsi_current_context();
long sql_setup();
long sql_connect(wchar_t* db_user, wchar_t* db_pass, wchar_t* db_dsn );
long sql_connect_ex(wchar_t* gsi_connection_str);
long sql_disconnect(gsi_int context_num);
long process_connect(wchar_t *db_user, wchar_t *db_pass, wchar_t *c_str, wchar_t *gsi_connection_str );
long process_reconnect();
long process_disconnect(long  cleanup_reconnect, gsi_int context_num);
} // G2_ODBC
//----------------------------------------------------------------------------
#endif // _G2_ODBC_SRC_H_
//----------------------------------------------------------------------------
