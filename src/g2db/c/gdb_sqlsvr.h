/*================================================================
 *  GDB_CLIENT_SQLSVR.H  - GDB Layer-3         (SQLOLEDB)      [header]
 *================================================================*/

#ifndef GDB_SQLSVR_H
#define GDB_SQLSVR_H


/*-----------------------
    defines
  -----------------------*/

#define  MAX_VNAME_LEN         128   /* (SQLDATA) initial max value length */  
#define  MAX_COLNAME_LEN        30  
#define  MAX_NATIVE_ERRLEN     256   /* Max length of mssage returned from SQLError */
#define  MAX_ODBC_ERRMSGS        5   /* Max error messages per ODBC call */
#define  MAX_DATE_LEN           23   /* Max length of timestamp data from ODBC */
#define  SS_LEN                  9   /* Length of "ss=xxxxx " (xxxxx is SQLSTATE) */
#define  MAX_ODBC_MSG_LEN       STATUS_MSG_LEN - 10
#define  MAX_INAME_LEN         128   /* (SQLIND) max indicator len */
#define  MAX_XML_LEN		   128   /* (SQLIND) max indicator len */
#define  MAX_BINARY_LEN		   65536 /* max supportd binary data 64k */
#define  MAX_VARWCHAR_LEN      1024  /* max records count for fetching unhicode data*/

/* db specific codes */
#define  DB_NOT_CONNECTED      -47
#define  DB_END_OF_CURSOR      100

/* Specific SQLSTATEs from ODBC */
#define  DB_ALREADY_CONNECTED  "08002"
#define  DB_CONNECT_NOT_OPEN   "08003"
#define  SQL_MAX_MESSAGE_LENGTH 512
#define  SQL_MAX_STATE_LENGTH	10

#include "stdio.h"
#include "gdb_globals.h"
#include "gdb_context.h"
#include "gdb_client_sqlsvr.h"

typedef enum query_type{
	  CMD_SELECT,
	  CMD_INSERT,
	  CMD_UPDATE,
	  CMD_DELETE
} CMD_TYPE;

typedef struct bind_proc_args {
      char*		data;
      short		len;                 
} SQL_STORED_PROC_ARG;

#endif


long cpp_sql_setup();
long cpp_sql_connect(wchar_t* db_user,wchar_t* db_pass,wchar_t* db_dsn );
long cpp_sql_disconnect(long context_num);
long cpp_sql_alloc_descriptors(long,long);
long cpp_sql_dealloc_descriptors(long shandle, long action );
long cpp_sql_release_bind(long shandle,long action );
long cpp_check_connection_hdl();
long cpp_sql_prepare(long shandle,long *stmt_id,wchar_t *sql_str );
short cpp_sql_describe_input(long  shandle,BIND_STRUCT *bind_vars,long *stmt_id,long *bind_processed,long action );
short cpp_bind_parameter(gSQLDA *bind_ptr,long datatype,short bcol,long ctx,long hdl );
long cpp_sql_describe_output(GENDA *sqlGen, long query_type );
short cpp_bind_column(gSQLDA* select_ptr,short scol,long ctx,long hdl);
short cpp_load_sql_err();
void cpp_display_sql_info();
long cpp_sql_refresh_cursor(wchar_t *curs_name,long shandle);
long cpp_sql_fetch(wchar_t* curs_name,long shandle );
void cpp_write_segment_data(wchar_t* dest_data,wchar_t* segm_data,long len,long nrow);
long cpp_sql_exec_sql( wchar_t *stmt_str );
long cpp_sql_commit();
long cpp_sql_rollback();
CMD_TYPE cpp_get_cmd_type(wchar_t* sql_stmt);
long cpp_sql_trigger(wchar_t* trig_name,long trig_timeout,wchar_t* trig_ret_msg,long context_num );
long cpp_sql_exec_stored_proc( wchar_t* sql_stmt );
long cpp_sql_exec_stored_proc_return(wchar_t *proc_name, wchar_t *proc_args, wchar_t *proc_ret_val );
