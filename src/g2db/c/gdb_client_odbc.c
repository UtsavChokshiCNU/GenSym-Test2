
/*================================================================
 *  GDB_CLIENT_ODBC.C    - GDB Layer-3  (ODBC 3.0)   [source]
 *================================================================
 *
 * Author: Peter Hill
 *
 *    - LAYER-3 = gdb_client_inter_odbc.c + gdb_client_odbc.c
 *    - performs all calls to ODBC functions
 *    - extracts data from SQLDA and inserts into GENDA
 *    - upper layers should check status
 *================================================================*/

#if defined(WIN32)
#include <windows.h>
#endif

#include <wchar.h>

#ifndef _WCHAR_T
#  define _WCHAR_T
#endif

#include <sql.h>
#include <sqlext.h>
#include <stdio.h>                                
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <odbcinst.h>
#if defined(WIN32)
#include <odbcss.h>
#else
#include <iodbcext.h>
#endif

#include "gdb_client_odbc.h"
#include "gdb_client_inter_odbc.h"
#include "gdb_globals.h"
#include "gdb_messages.h"
#include "gsi_main.h"
#include "gdb_context.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#include "gdb_g2_client.h"

#define LAYER LAYER3
#define SUPPORTED_ODBC_VERSION  3.0   /* version of ODBC this bridge built with */

/* local function prototypes */
void        load_odbc_err( HENV, HENV, HENV, RETCODE );
void        load_odbc_installer_err( RETCODE l_rc ) ;
void        display_odbc_info( );
long        check_connection_hdl(SQLHDBC);
long        check_sqlstate_disconnect( );
SQLRETURN   bind_column(gSQLDA*, SQLSMALLINT, long, long);
SQLRETURN   bind_parameter(gSQLDA*, long, SQLSMALLINT, long, long);

/* context-sensitive globals */
extern CONTEXT_INFO context[MAX_GDB_CONTEXTS];
extern SQLDA_PTRS   *sqlda_ptrs[MAX_GDB_CONTEXTS];
extern long         max_col_array_size;
extern long         max_value_array_size; /* size of genda in rows */
extern long         row_count[MAX_GDB_CONTEXTS];
extern long         sqlfetch_cnt[MAX_GDB_CONTEXTS];
GDB_CHAR            proc_spt[MAX_GDB_CONTEXTS][5] ;


/* globals */
extern long         debug;
extern gsi_int      context_num;

/* ODBC globals */
extern ODBCERR      g_sqlca;
SQLHENV             henv;
SQLHDBC             hdbc[MAX_GDB_CONTEXTS];
SQLHSTMT            trig_hstmt[MAX_GDB_CONTEXTS];
SQLHSTMT            hstmt[MAX_GDB_CONTEXTS][MAX_CURSORS+1];
float               driver_version[MAX_GDB_CONTEXTS];

SQLRETURN           rc;

/*======================================================================
  sql_setup
    - establish mapping and initial setup to esql variables and 
      structures used by all layers.
    - allocate the environment handle used by all ODBC functions
  ======================================================================*/
long sql_setup()
{
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_SETUP")) ;

    /* 
    ** Allocate the environment handle. 
    ** This is only done once in the program 
    */
    if (henv == NULL) 
    {
      if ( (rc = SQLAllocHandle( SQL_HANDLE_ENV,
                                 SQL_NULL_HANDLE,
                                   &henv )) != SQL_SUCCESS ) 
        {
        /* A memory allocation error */
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
      }

      /* Set environment for ODBC Version 3.0 */
      if ( (rc = SQLSetEnvAttr( henv, SQL_ATTR_ODBC_VERSION, 
                                 (SQLPOINTER)SQL_OV_ODBC3, 0) ) != SQL_SUCCESS ) 
        {
        /* Warning message */
            iomsg( DBG4, LAYER, TRUE, FALSE, NULL, FALSE, "%s",
               _T("Cannot set environment to ODBC Version 3") );
            return GDB_ERROR ;
      }
    }
    return GDB_SUCCESS ;
}
                 

 /*======================================================================
  sql_set_connection_options
    - applies options to connection before opening one
    Arguments:
    - context_num:   context number
  ======================================================================*/
long sql_set_connection_options( gsi_int context_num )
{
    /* Apply Windows integrated security for authenticating connection flag */

    long isec = context[context_num].integrated_security ;
    BOOL ok = FALSE ;

    /* Only call SQLSetConnectAttr() when security flag is TRUE */
    if (isec == SQL_IS_OFF)
	return GDB_SUCCESS;

    rc = SQLSetConnectAttr(hdbc[context_num], SQL_COPT_SS_INTEGRATED_SECURITY, (SQLPOINTER)isec, 0) ;
    ok = SQL_SUCCEEDED(rc) ;

    if (!ok)
    {
        load_odbc_err(henv, hdbc[context_num], SQL_NULL_HSTMT, rc) ;
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ESCONAT) ;
    } else if (context[context_num].console_output)
    {
	wprintf(_T("Config OK   : INTEGRATED_SECURITY set to: %s\n"), WSBOOLEAN(isec == SQL_IS_ON)) ;
    }

    return ok ? GDB_SUCCESS : GDB_ERROR ;
}


/*======================================================================
  sql_connect  (1)
    - establish connection to database
    Arguments:
    - db_user:   database username
    - db_pass:   database password
    - db_server: DSN data source name in the ODBC driver manager
  ======================================================================*/
long sql_connect(GDB_CHAR* db_user, GDB_CHAR* db_pass, GDB_CHAR* db_dsn )
{
    register short  i;
    GDB_CHAR       *odbc_dsn ;
    GDB_CHAR       *odbc_user ;
    GDB_CHAR       *odbc_pass ;
    GDB_CHAR        driver_odbc_ver[6] ;
    char            narrow_driver_odbc_ver[6] ;
    SWORD           length;
    BOOL            new_con;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_CONNECT")) ;

    /* Make sure user, password, dsn are there */
    if (db_user == NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOUSER) ;
        return GDB_ERROR ;
    }
    if (db_pass == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOPASS) ;
        return GDB_ERROR ;
    }
    if (db_dsn == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOCONS) ;
        return GDB_ERROR ;
    }

    /*
    ** Allocate a new connection handle if it has not already been used.
    ** Otherwise, re-use the one already allocated
    */
    new_con = !hdbc[context_num];

    if (new_con)
    {
        rc = SQLAllocHandle( SQL_HANDLE_DBC, henv, &hdbc[context_num] );
        if (!SQL_SUCCEEDED(rc)) 
        {
            load_odbc_err( henv, SQL_NULL_HDBC, SQL_NULL_HSTMT, rc );
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR  ;
        }
    }

    if (!new_con || context[context_num].integrated_security != SQL_IS_DEFAULT)
    	 sql_set_connection_options(context_num) ;
    
    /* Allocate memory for data source name, user, password */     
    if ((odbc_dsn = (GDB_CHAR*)calloc(wcslen(db_dsn)+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_dsn, db_dsn) ;

    if ((odbc_user = (GDB_CHAR*)calloc(wcslen(db_user)+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        free(odbc_dsn) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_user, db_user) ;

    if ((odbc_pass = (GDB_CHAR*)calloc(wcslen(db_pass)+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        free(odbc_dsn) ;
        free(odbc_user) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_pass, db_pass) ;
    
    /* Connect to the ODBC data source name */
    rc = SQLConnect( hdbc[context_num],
                     odbc_dsn, SQL_NTS,
                     odbc_user, SQL_NTS,
                     odbc_pass, SQL_NTS );

    if (!SQL_SUCCEEDED(rc))
    {
      load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
      /* check for already connected */
        if (!wcscmp(g_sqlca.state_array[0].sqlstate, DB_ALREADY_CONNECTED))
        {
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d", IDBCONA) ;
            free(odbc_dsn) ;
            free(odbc_user) ;
            free(odbc_pass) ;
            return GDB_SUCCESS ;
      }
        else
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADCON) ;
            free(odbc_dsn) ;
            free(odbc_user) ;
            free(odbc_pass) ;
            return GDB_ERROR  ;
      }
    }

    iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d", IDBCONE) ;
  
    /* Determine if stored procedures are supported */  
    SQLGetInfo( hdbc[context_num],
                SQL_PROCEDURES,
                proc_spt[context_num],
                5,
                &length );

    /* Determine the ODBC driver version */
    SQLGetInfo( hdbc[context_num], 
                SQL_DRIVER_ODBC_VER, 
                driver_odbc_ver, 
                sizeof(driver_odbc_ver), 
                &length );
    for (i = 0 ; i < 6 ; i++)
        narrow_driver_odbc_ver[i] = (char)driver_odbc_ver[i] ;
    driver_version[context_num] = (float)atof(narrow_driver_odbc_ver) ;

    /*
    ** Auto-commit is the default for ODBC drivers. But the default
    ** for the bridge is no auto-commit. So if the user wants no
    ** auto-commit, set the connection for that behaviour.
    */
    if (context[context_num].auto_commit == FALSE)
    {
        rc = SQLSetConnectAttr( hdbc[context_num], 
                                SQL_ATTR_AUTOCOMMIT, 
                                SQL_AUTOCOMMIT_OFF, 
                                0 );
        if (!SQL_SUCCEEDED(rc)) 
            load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    }

    /* 
    ** Connection is made.
    ** Set the elements of the HSTMT array for the current context to NULL
    ** and set the triggers statement handle to NULL
    */
    for (i=1; i<MAX_CURSORS+1; i++)
      hstmt[context_num][i] = NULL;
    
    trig_hstmt[context_num] = NULL;

    /* Now display info about ODBC driver and data source */
    if (debug & DBG2)
      display_odbc_info();

    /* free memory and return */
    free(odbc_dsn) ;
    free(odbc_user) ;
    free(odbc_pass) ;

    return GDB_SUCCESS  ;
}


/*{{{ connect database using connection string. added for project 28544 Gensym-2012 */
/*======================================================================
  sql_connect  (2)
    - establish connection to database
    Arguments:
    - gsi_connection_str	: database connection string
  ======================================================================*/
long sql_connect_ex(GDB_CHAR* gsi_connection_str)
{
    register short  i;
    GDB_CHAR       *db_connection_str ;
    GDB_CHAR        driver_odbc_ver[6] ;
    char            narrow_driver_odbc_ver[6] ;
    SWORD           length;
    BOOL            new_con;
	GDB_CHAR		conn_str_out[1024];
	SQLSMALLINT		conn_str_out_len;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_CONNECT")) ;

    /* parameter check. actually, this function will not be invoked if no gsi_connection_str provided */
    if ((gsi_connection_str == NULL) || (*gsi_connection_str == 0))
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOCONS) ;
        return GDB_ERROR ;
    }

    /*
    ** Allocate a new connection handle if it has not already been used.
    ** Otherwise, re-use the one already allocated
    */
    new_con = !hdbc[context_num];

    if (new_con)
    {
        rc = SQLAllocHandle( SQL_HANDLE_DBC, henv, &hdbc[context_num] );
        if (!SQL_SUCCEEDED(rc)) 
        {
            load_odbc_err( henv, SQL_NULL_HDBC, SQL_NULL_HSTMT, rc );
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR  ;
        }
    }

    if (!new_con || context[context_num].integrated_security != SQL_IS_DEFAULT)
    	 sql_set_connection_options(context_num) ;
    
    /* Allocate memory for database connection string */     
    if ((db_connection_str = (GDB_CHAR*)calloc(wcslen(gsi_connection_str)+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    wcscpy(db_connection_str, gsi_connection_str) ;
    
    /* Connect to the database */
	rc = SQLDriverConnect(hdbc[context_num],
						  NULL,
						  db_connection_str,
						  SQL_NTS,
						  conn_str_out,
						  sizeof (conn_str_out) / sizeof (GDB_CHAR),
						  &conn_str_out_len,
						  SQL_DRIVER_NOPROMPT);


    if (!SQL_SUCCEEDED(rc))
    {
      load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
      /* check for already connected */
        if (!wcscmp(g_sqlca.state_array[0].sqlstate, DB_ALREADY_CONNECTED))
        {
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d", IDBCONA) ;
			free(db_connection_str);
            return GDB_SUCCESS ;
      }
        else
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADCON) ;
			free(db_connection_str);
            return GDB_ERROR  ;
      }
    }

    iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d", IDBCONE) ;
  
    /* Determine if stored procedures are supported */  
    SQLGetInfo( hdbc[context_num],
                SQL_PROCEDURES,
                proc_spt[context_num],
                5,
                &length );

    /* Determine the ODBC driver version */
    SQLGetInfo( hdbc[context_num], 
                SQL_DRIVER_ODBC_VER, 
                driver_odbc_ver, 
                sizeof(driver_odbc_ver), 
                &length );
    for (i = 0 ; i < 6 ; i++)
        narrow_driver_odbc_ver[i] = (char)driver_odbc_ver[i] ;
    driver_version[context_num] = (float)atof(narrow_driver_odbc_ver) ;

    /*
    ** Auto-commit is the default for ODBC drivers. But the default
    ** for the bridge is no auto-commit. So if the user wants no
    ** auto-commit, set the connection for that behaviour.
    */
    if (context[context_num].auto_commit == FALSE)
    {
        rc = SQLSetConnectAttr( hdbc[context_num], 
                                SQL_ATTR_AUTOCOMMIT, 
                                SQL_AUTOCOMMIT_OFF, 
                                0 );
        if (!SQL_SUCCEEDED(rc)) 
            load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    }

    /* 
    ** Connection is made.
    ** Set the elements of the HSTMT array for the current context to NULL
    ** and set the triggers statement handle to NULL
    */
    for (i=1; i<MAX_CURSORS+1; i++)
      hstmt[context_num][i] = NULL;
    
    trig_hstmt[context_num] = NULL;

    /* Now display info about ODBC driver and data source */
    if (debug & DBG2)
      display_odbc_info();

    /* free memory and return */
	free(db_connection_str);

    return GDB_SUCCESS  ;
}
/*}}}*/


/*======================================================================
  sql_disconnect
    - disconnect from the database
    - only free the connection handle if there was no connection initially
  ======================================================================*/

long sql_disconnect(gsi_int context_num)
{
    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg (DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_DISCONNECT")) ;

    /* If the connection handle is null, send message that you are not connected */
    if (hdbc[context_num] == NULL) 
    {
        iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%s", _T("Database is already disconnected.")) ;
        return GDB_SUCCESS ;
    }

    /* rollback any active transaction if auto-commit is OFF */
    if ( ! context[context_num].auto_commit )
      rc = SQLEndTran( SQL_HANDLE_DBC, hdbc[context_num], SQL_ROLLBACK );
    
    /* free the statement handle for triggers if they are being used */
    if (trig_hstmt[context_num]) 
    {
      rc = SQLFreeHandle( SQL_HANDLE_STMT, trig_hstmt[context_num] );
      trig_hstmt[context_num] = NULL;
    }
    /*
    ** NOTE: 
    ** Before disconnecting from the data source all hstmts associated
    ** with the connection should be freed.  However, upon a disconnect
    ** the odbc driver automatically frees those hstmts.
    ** Therefore, we will not call SQLFreeHandle here.
    */

    /* Disconnect from the data source */
    rc = SQLDisconnect( hdbc[context_num] );

    if (rc < SQL_SUCCESS) 
    {
        /* 
        ** If the disconnect fails it means there is something wrong
        ** with the connection or we are not connected.  Set the connection
        ** handle to NULL which will make sure that we get a new one the next time we
        ** try to connect.  This should eliminate "stale" connection handles.
        ** (Stale conections can occur if a database goes down and then back up again
        **  while the interface object is connected)
        */
        hdbc[context_num] = NULL;
    }
    else 
    {
        rc = SQLFreeHandle( SQL_HANDLE_DBC, hdbc[context_num] );
        load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
        hdbc[context_num] = NULL;
    }

    return (rc < SQL_SUCCESS ? GDB_EXT_ERROR : GDB_SUCCESS);
}
 
 
/*======================================================================
  sql_alloc_descriptors
    - The allocate descriptor SQL statement is done implicitly in ODBC
    - alloc select descriptors (db) and corresponding select_ptr (bridge)
    - store select_ptr in global sqlda_ptrs array
    
    Arguments:
    - shandle: statement handle
    - action: SELECT,BIND
  ======================================================================*/

long sql_alloc_descriptors(long shandle, long action)
{
    gSQLDA  *select_ptr;
    gSQLDA  *bind_ptr;
	long     retcode;
  
    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_ALLOC_DESCRIPTORS")) ;

    if (shandle == 0) return GDB_ERROR ;

    if (action == BIND) 
    {
      /* cleanup if previously allocated */
        if ( sqlda_ptrs[context_num][shandle].bptr != NULL)
        retcode = sql_dealloc_descriptors( shandle, BIND );

      /* alloc 1 descriptor for maximum bind vars */
      if ((bind_ptr = (gSQLDA *)XCALLOC(context[context_num].max_bind_vars,
                       sizeof(gSQLDA))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%d", EALDESC) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
      }

      /*** store bind addr in SQLDA_PTRS array ***/
        if (sqlda_ptrs[context_num] != NULL)
        sqlda_ptrs[context_num][shandle].bptr = bind_ptr; 
        else 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT store bind pointer in SQLDA_PTRS")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
      } 
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Input (BIND) Descriptor Memory Allocated")) ;
    }

    if (action == SELECT)
    {
      /* cleanup if previously allocated */
        if ( sqlda_ptrs[context_num][shandle].sptr != NULL)
        retcode = sql_dealloc_descriptors( shandle, SELECT );

      /* alloc 1 descriptor for each db column */
        if ((select_ptr = (gSQLDA *)XCALLOC(max_col_array_size, sizeof(gSQLDA))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%d", EALDESC) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
      }
           
      /*** store select addr in SQLDA_PTRS array ***/
        if (sqlda_ptrs[context_num] != NULL)
        sqlda_ptrs[context_num][shandle].sptr = select_ptr; 
        else 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT store select pointer in SQLDA_PTRS")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
      } 
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Output (SELECT) Descriptor Memory Allocated")) ;
    }

    return GDB_SUCCESS ;
}


/*======================================================================
  sql_prepare
    - perform a database 'prepare' of the sql statement
    - generate a stmt_id_name & store in SQLDA_PTRS

    Arguments:
    - shandle: statement handle
    - stmt_id: statement id created by the prepare
    - sql_str: sql statement
  ======================================================================*/
long sql_prepare(long shandle, long *stmt_id, GDB_CHAR *sql_str)
{
    long       len,array_size;
    GDB_CHAR   *odbc_sql_stmt ;
 
    context_num = gsi_current_context();

    if (debug & DBG1) 
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_PREPARE")) ;

    if (shandle == 0) return GDB_ERROR ;

    /* Make sure connection is valid */
    if ( !check_connection_hdl(hdbc[context_num]) ) 
      return( GDB_EXT_ERROR );

    /*
    ** If there is an open statement handle, Free it.
    ** and always allocate a new one.
    */
    if (hstmt[context_num][shandle]) 
    {
      rc = SQLFreeHandle( SQL_HANDLE_STMT,hstmt[context_num][shandle] );
      hstmt[context_num][shandle] = 0;
    }

    rc = SQLAllocHandle( SQL_HANDLE_STMT,
                         hdbc[context_num],
                        &hstmt[context_num][shandle] );
    load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    if ( rc < SQL_SUCCESS ) return ( GDB_EXT_ERROR );

    if (*stmt_id != 0) *stmt_id = 0;

    len = wcslen(sql_str) ;
    if ((odbc_sql_stmt = calloc(len+1, sizeof(GDB_CHAR))) == NULL) 
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for odbc_sql_stmt")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_sql_stmt, sql_str) ;
     
    *stmt_id = shandle;

    /*
    ** MS SQL Server rejects SQL strings which contain
    ** unicode line separator (U+2028) character.
    */
#if defined(UNICODE)
    wstrrepl(odbc_sql_stmt, L'\x2028', L'\n') ;
#endif

    *stmt_id = shandle ;

    /*
    ** If array fetching is off, set the number of records to retrieve on
    ** each Fetch to 1.
    */
    array_size = max_value_array_size;
    if (context[context_num].array_fetch == FALSE)
        array_size = 1;

    /* Set up the statement for column-wise binding */

    rc = SQLSetStmtAttr( hstmt[context_num][shandle],
                                      SQL_ATTR_ROW_BIND_TYPE,
                                      SQL_BIND_BY_COLUMN, 0 );
    rc = SQLSetStmtAttr( hstmt[context_num][shandle],
                                      SQL_ATTR_ROW_ARRAY_SIZE,
                                      (SQLPOINTER)array_size, 0 );
    rc = SQLSetStmtAttr( hstmt[context_num][shandle],
                                      SQL_ATTR_ROWS_FETCHED_PTR,
                                      &sqlfetch_cnt[context_num], 0);

    /* prepare the sql statement */
    rc = SQLPrepare( hstmt[context_num][shandle], odbc_sql_stmt, SQL_NTS );
    load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );

    free (odbc_sql_stmt);
    return (rc < SQL_SUCCESS) ? GDB_EXT_ERROR : GDB_SUCCESS ;
}


/*======================================================================
  sql_declare_cursor
    - this function is unnecessary in the ODBC bridge
  
    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
    - stmt_id: statement id created from prepare
  ======================================================================*/
long sql_declare_cursor(GDB_CHAR *curs_name, long shandle, long *stmt_id )
{

    return GDB_SUCCESS ;

}
 

/*======================================================================
  sql_describe_input
    - id all host vars (INPUT VARIABLES) and load into bind descriptor
    - alloc memory for bind vars
    - get values for host bind vars
    - 
  ======================================================================*/
long sql_describe_input(long shandle, BIND_STRUCT *bind_vars, long *stmt_id, long *bind_processed, long action)
{
    gSQLDA         *bind_ptr;
    short           i,bvl;
    SQLSMALLINT     num_params;
    SQLUSMALLINT    pnum;

    context_num = gsi_current_context();

    if (debug & DBG1)
      iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_DESCRIBE_INPUT")) ;

    if (shandle == 0) return GDB_ERROR ;
    
    /* Make sure connection is valid */
    if ( ! check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );

    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;
    if (bind_ptr == (gSQLDA *) NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", ENOTINI) ;
        return GDB_ERROR ;
    }
    if (action == GDB_INIT) 
    {
       
        /* Determine how many parameters the statement has */
        rc = SQLNumParams( hstmt[context_num][shandle], &num_params );

		if(bind_vars == NULL && num_params > 0)
		{
			g_sqlca.code = GDB_BIND_ERROR;
			return GDB_BIND_ERROR;
		}

        load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
        if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
        {
            iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("Could not get parameter count for %"), hstmt[context_num][shandle]) ;
            return GDB_EXT_ERROR ;
        }

        /* Make sure number of parameters is within range */
        if ( num_params > context[context_num].max_bind_vars) 
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EMBVEXD, num_params, context[context_num].max_bind_vars ) ;
            num_params = 0; /* set to 0 to avoid dealloc problems */
            return GDB_ERROR ;
        }
        bind_ptr[0].ncols = num_params;

        /* If there are no input parameters, return */
        if (!num_params) 
        {
            *bind_processed = TRUE;
            return GDB_SUCCESS ;
        }

        /*
        ** Load bind pointer structure with the existing info
        ** from the parameters (descriptors)
        */
        for (i=0, pnum=i+1; pnum<=num_params; i++, pnum++) 
        {
            rc = SQLDescribeParam( hstmt[context_num][shandle],
                                        pnum,
                                        &bind_ptr[i].datatype,
                                        &bind_ptr[i].colsize,
                                        &bind_ptr[i].decdigs, 
                                        &bind_ptr[i].nullable );
            load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
            if ( (rc != SQL_SUCCESS) && 
                 (rc != SQL_SUCCESS_WITH_INFO) ) 
            {
                return ( GDB_EXT_ERROR );
            }

            /* Fudge colsize for date datatypes */
            if ( (bind_ptr[i].datatype == SQL_DATETIME) ||
                 (bind_ptr[i].datatype == SQL_TYPE_TIMESTAMP) )
                bind_ptr[i].colsize = MAX_DATE_LEN;
        }
    } /* end GDB_INIT */

    /* Check to see if bind vars are required */
    if ((!bind_ptr[0].ncols) || (!bind_vars->nBind)) 
    {
        *bind_processed = TRUE;
        return GDB_SUCCESS ;
    }
    if (bind_ptr[0].ncols != bind_vars->nBind) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%d%d", ENUMVAL, bind_vars->nBind, bind_ptr[0].ncols) ;
        return GDB_ERROR ;
    }
      
    for (i=0;i<bind_ptr[0].ncols;i++) 
    {
        bvl = wcslen(bind_vars->bind_array[i]) ;

        /* allocate space for the bind data */
        if ((bind_ptr[i].bdata = (GDB_CHAR*)XCALLOC(bvl+1, sizeof(GDB_CHAR))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for bdata")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }

        /* allocate space for the indicator */
        if ((bind_ptr[i].ind = (long *)XCALLOC(1, sizeof(long))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        /* Copy into bind data into bdata */
        wcscpy(bind_ptr[i].bdata, bind_vars->bind_array[i]) ;

        /* Set the null indicator */
        /* ---------------------- */
        *bind_ptr[i].ind = SQL_NTS;
        if ((context[context_num].set_null_options & 0x2) && 
                ! _wcsicmp(bind_ptr[i].bdata, context[context_num].set_null_string))
            *bind_ptr[i].ind = SQL_NULL_DATA;
        else 
            if ((context[context_num].set_null_options & 0x4) && !_wcsicmp(bind_ptr[i].bdata, _T("NULL")))
                *bind_ptr[i].ind = SQL_NULL_DATA;

        rc = bind_parameter( bind_ptr, GDB_STRING_TYPE, i, context_num, shandle );
        if ( rc != GDB_SUCCESS ) return ( rc );
    }
    
    iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("Bind variables processed: %"), bind_ptr[0].ncols) ;
    *bind_processed = TRUE;

    /* close the cursor.  Do not worry about the error code */
    rc = SQLCloseCursor( hstmt[context_num][shandle] );

    return GDB_SUCCESS ;
}


/*======================================================================
  sql_describe_output
    - 'describe' the 'prepared' sql statement to determine the character-
      istics of the database columns (i.e. datatype, column name, etc)
    - store the results in select_ptr
    - queries only 
  
    Arguments:
    - shandle: statement handle
    - stmt_id: statement id from 'prepare'
    - ncols: # of columns detected
    - query_type:
        * SELECT = standard sql select statement
        * STORED_PROC = stored procedure (currently not supported)
  ======================================================================*/
long sql_describe_output(GENDA *sqlGen, long query_type )
{
    gSQLDA       *select_ptr;
    gSQLDA       *bind_ptr;
    SQLSMALLINT   scol;
    SWORD         num_cols;
    UWORD         dcol;
    SWORD         ddatalen;
    SWORD         ddatatype;
    SQLUINTEGER   dcolsize;
    SQLSMALLINT   ddecdigs;
    SQLSMALLINT   dnullable;
    static GDB_CHAR *dname=NULL ;
    long          shandle;
    long          *stmt_id;
    long          *ncols;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_DESCRIBE_OUTPUT")) ;

    if (sqlGen == NULL) return GDB_ERROR ;
    shandle = sqlGen->stmt_handle ;
    stmt_id = &(sqlGen->stmt_id) ;
    ncols = &(sqlGen->ncols) ;
    if (shandle == 0) return GDB_ERROR ;

    /* Make sure connection is valid */
    if ( ! check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );
    
    select_ptr = sqlda_ptrs[context_num][shandle].sptr;
    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

    /* get the actual # of columns */
    rc = SQLNumResultCols( hstmt[context_num][shandle], &num_cols );
    load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
    if ((rc < SQL_SUCCESS) || (num_cols <= 0)) 
    {
        iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("Could not get descriptor count for %"), hstmt[context_num][shandle]) ;
        return ( GDB_EXT_ERROR );
    }

    if ( num_cols > max_col_array_size) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", ENCOLEX, num_cols, max_col_array_size) ;
        *ncols = 0; /* set to 0 to avoid dealloc problems */
        return GDB_ERROR ;
    }

    *ncols = (long)num_cols;

    /* decimal_flags is an array of flags used for tracking which columns are */
    /* type DECIMAL(x,0) where x >=9.  If we have already allocated it from a */
    /* prior query, release its memory.  Then, allocate a new array based upon*/
    /* the number of columns we currently have.  XCALLOC initializes all      */
    /* element to 0.                                                          */
    /* ---------------------------------------------------------------------- */
    if (sqlGen->decimal_flags) free(sqlGen->decimal_flags) ;
    sqlGen->decimal_flags = NULL ;
    if (*ncols)
    {
        sqlGen->decimal_flags = (char*)XCALLOC(*ncols, sizeof(char)) ;
        if (sqlGen->decimal_flags == NULL)
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for decimal_flags array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
    }

    /* realloc nSQLDA to the actual n needed */
    if ( (sqlda_ptrs[context_num][shandle].sptr = select_ptr = 
         (gSQLDA *)realloc(select_ptr, num_cols*sizeof(gSQLDA))) == NULL) 
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT realloc memory for gSQLDA select pointer")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINMEMR) ;
        return GDB_ERROR ;
    }
    iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("SQLDA memory reallocated for % select-list items"), num_cols) ;
        
    if (dname == NULL)
        if ((dname = (GDB_CHAR*)calloc(context[context_num].max_bind_name_len+1, sizeof(GDB_CHAR))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for dname")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }

    for (dcol=1; dcol<=num_cols; dcol++) 
    {
        /* describe each output column */
        rc = SQLDescribeCol( hstmt[context_num][shandle],
                             dcol,
                             dname,
                             (SQLSMALLINT)context[context_num].max_bind_name_len,
                             &ddatalen,
                             &ddatatype,
                             &dcolsize,
                             &ddecdigs,
                             &dnullable );
        
        load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
                                 
        if (rc < SQL_SUCCESS) 
        {
            iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("Could not get descriptor column info for %"), shandle ) ;
            return (GDB_EXT_ERROR);
        }

        scol = dcol - 1;
        /*
        ** Check to see if we have a function name.  e.g. COUNT(*).
        ** If so, the descriptor name will be NULL. Set the colname to GDB_UNKNOWN.
        */
        if (!(wcslen(dname)))
            wcscpy(dname, GDB_UNKNOWN) ;

        if ((select_ptr[scol].colname = (GDB_CHAR*)calloc(wcslen(dname)+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for SP colname")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }

        /* assign values to select_ptr */
        wcscpy(select_ptr[scol].colname, dname) ;
        select_ptr[scol].ncols      = num_cols;
        select_ptr[scol].datatype   = ddatatype;
        select_ptr[scol].datalen    = ddatalen;
        select_ptr[scol].colsize    = dcolsize;   
        select_ptr[scol].decdigs    = ddecdigs;
        select_ptr[scol].nullable   = dnullable;

        sqlGen->decimal_flags[scol] = (char)(ddatatype == SQL_BIGINT || ((ddatatype == SQL_NUMERIC ||
                ddatatype == SQL_DECIMAL) && dcolsize >= 9 && ddecdigs == 0)) ;
  
        /* Bind the data for the column */
        rc = bind_column( select_ptr, scol, context_num, shandle );
        load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
        if ( rc != GDB_SUCCESS ) return ( GDB_ERROR );
    } /* end for loop */

    return GDB_SUCCESS ;
}


/*======================================================================
  sql_open_cursor
    - open the 'declared' cursor
    - cursors must be opened prior to executing a 'fetch'
    - Not used in ODBC bridge
  
    Arguments:
    - curs_name: cursor name
    - shandle: statement handle

  Note: this does not seem to be used by any of the database bridges
  ======================================================================*/
long sql_open_cursor(GDB_CHAR *curs_name, long shandle)
{
    return GDB_SUCCESS ;
}


/*======================================================================
  sql_fetch
    - execute a previously prepared statement
    - fetch a database row into the defined descriptor
    
    Arguments:
    - curs_name: cursor name
    - shandle: statment handle
  ======================================================================*/
long sql_fetch(GDB_CHAR* curs_name, long shandle)
{
    gSQLDA   *select_ptr;

    context_num = gsi_current_context();

    if (shandle == 0) return GDB_ERROR ;

    /* Make sure connection is valid */
    if ( !check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%s", _T("SQL_FETCH: %"), curs_name) ;
    
    select_ptr = sqlda_ptrs[context_num][shandle].sptr;

    /*
    ** Execute the statement if the row count is zero (first time thru)
    */
    if (select_ptr[0].row_count == 0) 
    {
      rc = SQLExecute( hstmt[context_num][shandle] );
        if (rc != SQL_SUCCESS) 
        {
        if (rc > SQL_SUCCESS)
          load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
            else if (rc < SQL_SUCCESS) 
            {
          load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
          return ( GDB_EXT_ERROR );
        }
      }
	}

    /* fetch record(s) */
    rc = SQLFetch( hstmt[context_num][shandle] );
    if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) 
    {
      /* increment the row count */
      select_ptr[0].row_count += sqlfetch_cnt[context_num];
      row_count[context_num] = select_ptr[0].row_count;
        return GDB_SUCCESS ;
    }

    row_count[context_num] = select_ptr[0].row_count;
    load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );

    return ( GDB_EXT_ERROR );
}


/*======================================================================
  sql_dealloc_descriptors
    - deallocate the allocated descriptor 
    - free column name 
    - free select_ptr

    Arguments:
    - shandle: statement handle
    - action: SELECT,BIND (see sql_alloc_descriptors)
  ======================================================================*/
long sql_dealloc_descriptors(long shandle, long action)
{
    gSQLDA     *select_ptr;
    gSQLDA     *bind_ptr;
    long        status = 0;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_DEALLOC_DESCRIPTORS")) ;

    if (shandle == 0) return GDB_ERROR ;

    if (action == BIND)
    {
        if (debug & DBG6)
            iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("- bind")) ;
    
        bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

        if (bind_ptr ==  NULL)
            return GDB_SUCCESS ;
	    
        sql_release_bind( shandle, action );
        XFREE((gSQLDA *)bind_ptr);
        bind_ptr = NULL ;
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("BIND Descriptor Memory Deallocated")) ;
        sqlda_ptrs[context_num][shandle].bptr = NULL ;
    }

    if (action == SELECT)
    {
        if (debug & DBG6)
            iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("- select")) ;
        
        select_ptr = sqlda_ptrs[context_num][shandle].sptr;

        if (select_ptr ==  NULL)
            return GDB_SUCCESS ;

        sql_release_bind( shandle, action );
        XFREE((gSQLDA *)select_ptr);
        select_ptr = NULL ;
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SELECT Descriptor Memory Deallocated")) ;
        sqlda_ptrs[context_num][shandle].sptr = NULL ;
    
        /* Make sure connection is valid */
        if ( ! check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );
  
        /* release the statement handle. */
        if (hstmt[context_num][shandle]) 
        {
            rc = SQLFreeHandle( SQL_HANDLE_STMT, hstmt[context_num][shandle] );
            if (rc < SQL_SUCCESS) 
            {
                /* Don't call the error handler */
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d",
                       _T("Could not deallocate PREPARE for %"),hstmt[context_num][shandle] );
                status = 1;
            }
            hstmt[context_num][shandle] = NULL;
        }
    }

    return !status ? GDB_SUCCESS : GDB_EXT_ERROR ;
}


/*======================================================================
  sql_close_cursor
    - close a previously opened cursor
    - Not used by ODBC bridge

    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/
long sql_close_cursor(GDB_CHAR* curs_name, long shandle, long release_cursor)
{
    return GDB_SUCCESS ;
}                                             


/*======================================================================
  sql_exec_sql
    - process non-query
    - statement must not contain 'select'
    - sql statement is passed directly to database 'as is'
    - the following steps are performed:
    - Allocate a statement handle
    - Execute the statement
    - De-allocate the statement handle

    Arguments:
    - stmt_str: non-select sql statement

  ======================================================================*/
long sql_exec_sql(GDB_CHAR *stmt_str)
{
    long        len;
    GDB_CHAR   *odbc_sql_stmt ;
    HSTMT       exec_hstmt;
    SQLINTEGER  rows_affected=0;
#ifdef UNICODE
    long        i;
#endif

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_EXEC_SQL")) ;

    /* Make sure connection is valid */
    if ( ! check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );
 
    /* allocate a statement handle */
    rc = SQLAllocHandle( SQL_HANDLE_STMT,
                                      hdbc[context_num],
                                      &exec_hstmt );
    load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );

    len = wcslen(stmt_str) ;
    if ((odbc_sql_stmt = calloc(len+1, sizeof(GDB_CHAR))) == NULL) 
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for odbc_sql_stmt")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_sql_stmt, stmt_str) ;

    /* GENSYMCID-1079: ODBC Unicode Bridge incorrectly passing some characters to MSSQL Server 2008
       Replace all #x2028 (Line-Separator) into #x0a (Newline) for compatibility with old RDBMS */
#ifdef UNICODE
    for (i = 0; i < len; ++ i)
        if (odbc_sql_stmt[i] == 0x2028)
            odbc_sql_stmt[i] = 0x0a;
#endif

    /* execute the statement */
    rc = SQLExecDirect( exec_hstmt, odbc_sql_stmt, len );
    load_odbc_err( henv, hdbc[context_num], exec_hstmt, rc );
    free(odbc_sql_stmt) ;

    if (rc < SQL_SUCCESS) 
    {
        SQLFreeHandle( SQL_HANDLE_STMT, exec_hstmt );
        return GDB_EXT_ERROR ;
    }

    if (rc == SQL_NO_DATA) 
    {
        /* Do not call SQLRowCount if statement returns no data */
        rows_affected = 0;
    }
    else 
    {
        /* Get the number of rows affected */
        rc = SQLRowCount( exec_hstmt, &rows_affected );
        load_odbc_err( henv, hdbc[context_num], exec_hstmt, rc );
        if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
        {
            return GDB_EXT_ERROR ;
        }
    }
    row_count[context_num] = rows_affected;

    /* free the statement handle */
    rc = SQLFreeHandle( SQL_HANDLE_STMT, exec_hstmt );
    load_odbc_err( henv, hdbc[context_num], exec_hstmt, rc );
    exec_hstmt = NULL;

    return  rc<SQL_SUCCESS ? GDB_EXT_ERROR : GDB_SUCCESS ;
}


/*======================================================================
  sql_commit
    - commit (and end) the transaction
  ======================================================================*/

long sql_commit()
{
    RETCODE    lrc;

    context_num = gsi_current_context();

    if (debug & DBG1)
      iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_COMMIT")) ;

    lrc = SQLEndTran( SQL_HANDLE_DBC, hdbc[context_num], SQL_COMMIT );
    load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, lrc );

    return ( lrc < 0 ? GDB_EXT_ERROR : GDB_SUCCESS );
}


/*======================================================================
  sql_rollback
    - rollback (and end) the transaction
  ======================================================================*/
long sql_rollback()
{
    RETCODE    lrc;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_ROLLBACK")) ;
    
    lrc = SQLEndTran( SQL_HANDLE_DBC, hdbc[context_num], SQL_ROLLBACK );
    load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, lrc );

    return (lrc < SQL_SUCCESS) ? GDB_EXT_ERROR : GDB_SUCCESS ;
}


/*======================================================================
  sql_refresh_cursor
    - reposition the cursor pointer to the first row in the cursor
    - close cursor so it can be used again

    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/
long sql_refresh_cursor(GDB_CHAR* curs_name, long shandle)
{
    gSQLDA   *select_ptr;

    context_num = gsi_current_context();

    if (debug & DBG1) 
    {
        if (curs_name != NULL)
            iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%s", _T("SQL_REFRESH: "), curs_name) ;
        else 
            iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_REFRESH")) ;
    }
    /* Make sure connection is valid */
    if ( ! check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );
    
    select_ptr = sqlda_ptrs[context_num][shandle].sptr;
    /* Make sure there is an active statement and atleast 1 row has been retrieved */
 /* if ( hstmt[context_num][shandle] && select_ptr[0].row_count ) */
    if ( hstmt[context_num][shandle] )
    {
        /*
        ** Close ODBC cursor and discard pending results (if any).
        ** This must be called before calling SQLExecute again.
        */
        rc = SQLFreeStmt( hstmt[context_num][shandle], SQL_CLOSE );
        /* To indicate a refreshed cursor set row_count to 0 */
        select_ptr[0].row_count = 0;
    }
    return GDB_SUCCESS ;
}


/*======================================================================
  sql_release
    - release resources allocated by 'prepare' and 'declare cursor'

    Arguments:
    - stmt_id: statement id from 'prepare' 
  ======================================================================*/
long sql_release(long *stmt_id)
{
  *stmt_id = 0;

    return GDB_SUCCESS ;
}


/*======================================================================
  sql_exec_stored_proc
    - execute a database stored procedure that does not return any 
      arguments.
    - format of the input statement: CALL XXXX(arg1, arg2,arg3...)
    - returns error if the ODBC driver does not support procedures

    Arguments:
    - sql_stmt: call to database stored procedure
  ======================================================================*/
long sql_exec_stored_proc(GDB_CHAR* sql_stmt)
{
    long      len;
    GDB_CHAR   *odbc_sql_stmt ;
    HSTMT      proc_hstmt;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_EXEC_STORED_PROC")) ;

    /* Make sure connection is valid */
    if ( ! check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );
 
    /* 
    ** HACK!  CHANGE MESSAGES.H FOR FUTURE RELEASES 
    ** Return an error if the driver does not support database stored procedures
    */
    if (!wcscmp(proc_spt[context_num], _T("N")))
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%s",
        _T("This ODBC driver does not support stored procedures." ));
        return GDB_ERROR ;
    }

    /* allocate a statement handle */
    rc = SQLAllocHandle( SQL_HANDLE_STMT,
                                      hdbc[context_num],
                                      &proc_hstmt);
    load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );

    len = wcslen(sql_stmt) ;
    if ((odbc_sql_stmt = calloc(len+3, sizeof(GDB_CHAR*))) == NULL) 
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for odbc_sql_stmt")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    /* Put brackets around the call to the procedure */
    _snwprintf(odbc_sql_stmt, len+2, _T("{%s}"), sql_stmt) ;

    /* execute the statement */
    rc = SQLExecDirect( proc_hstmt, odbc_sql_stmt, SQL_NTS );
	if (rc == SQL_SUCCESS_WITH_INFO)
		rc = SQLMoreResults(hdbc[context_num]) ;
    load_odbc_err( henv, hdbc[context_num], proc_hstmt, rc );
    free(odbc_sql_stmt) ;

    if (rc < SQL_SUCCESS) 
    {
        SQLFreeHandle( SQL_HANDLE_STMT, proc_hstmt );
        return( GDB_EXT_ERROR );
    }

    /* free the statement handle */
    rc = SQLFreeHandle( SQL_HANDLE_STMT, proc_hstmt );
    load_odbc_err( henv, hdbc[context_num], proc_hstmt, rc );

    return (rc < SQL_SUCCESS) ? GDB_EXT_ERROR : GDB_SUCCESS ;
}


/* ========================================================================= */
/* sql_exec_stored_proc_return                                               */
/*                                                                           */
/* Execute the user-written stored procedure sp_handler.  sp_handler is      */
/* responsible for decoding the string proc_args and dispatching it to the   */
/* stored procedure specified by proc_name.  It is also responsible for      */
/* gathering any values returned by proc_name and returning them to G2       */
/* via proc_ret_val, a string of up to EXSPRET_SZ bytes.                   */
/*                                                                           */
/* Arguments:                                                                */
/* - proc_name: string that only has mean to the author of sp_handler.  The  */
/*   intention is that this should be the name of the stored procedure that  */
/*   sp_handler will call.                                                   */
/* - proc_args: string that should be decoded by sp_handler and dispatched   */
/*   to proc_name                                                            */
/* - proc_ret_val: string that is created by sp_handler from proc_name's     */
/*   returned values and then returned to G2.                                */
/*                                                                           */
/* ========================================================================= */
long sql_exec_stored_proc_return(GDB_CHAR *proc_name, GDB_CHAR *proc_args, GDB_CHAR *proc_ret_val )
{
    HSTMT       proc_hstmt;
    SQLINTEGER  parmlen1=SQL_NTS, parmlen2=SQL_NTS, parmlen3=SQL_NTS;
    int         lenName = (int)wcslen(proc_name), lenArgs = (int)wcslen(proc_args) ;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_EXEC_STORED_PROC")) ;

	/* Initialize return string to null string */
	/* --------------------------------------- */
	memset(proc_ret_val,0,EXSPRET_SZ+1) ;

    /* Make sure connection is valid */
    /* ----------------------------- */
    if ( !check_connection_hdl(hdbc[context_num]) ) return( GDB_EXT_ERROR );
  
    /* Return an error if the driver does not support database stored procedures */
    /* ------------------------------------------------------------------------- */
    if (!wcscmp(proc_spt[context_num], _T("N")))
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%s", _T("This ODBC driver does not support stored procedures." )) ;
        return GDB_ERROR ;
    }

	/* Make sure proc_name and proc_args are not too long */
	/* -------------------------------------------------- */
	if (lenName > EXSPRETRSZ)
	{
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%s%d%d", _T("Length of procedure name (%) exceeds % characters."), lenName, EXSPRETRSZ) ;
        return GDB_ERROR ;
	}
	if (lenArgs > EXSPRET_SZ)
	{
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%s%d%d", _T("Length of argument string (%) exceeds % characters."), lenArgs, EXSPRET_SZ) ;
        return GDB_ERROR ;
	}

    /* Allocate a statement handle */
    /* --------------------------- */
    rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc[context_num], &proc_hstmt );
    load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );

    /* Bind the first parameter: proc_name (input) */
    /* ------------------------------------------- */
    rc = SQLBindParameter(proc_hstmt, 1, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_VARCHAR, 
            wcslen(proc_name), 0, proc_name, 0, &parmlen1) ;
    load_odbc_err( henv, hdbc[context_num], proc_hstmt, rc );
    if ( rc < SQL_SUCCESS )
    {
        SQLFreeHandle( SQL_HANDLE_STMT, proc_hstmt );
        return( GDB_EXT_ERROR );
    }

    /* Bind the second parameter: proc_args (input) */
    /* -------------------------------------------- */
    rc = SQLBindParameter(proc_hstmt, 2, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_VARCHAR, 
            wcslen(proc_args), 0, proc_args, 0, &parmlen2 ) ;
    load_odbc_err( henv, hdbc[context_num], proc_hstmt, rc );
    if (rc < SQL_SUCCESS) 
    {
        SQLFreeHandle(SQL_HANDLE_STMT, proc_hstmt);
        return( GDB_EXT_ERROR );
    }

    /* Bind the third parameter: proc_ret_val (output) */
    /* ----------------------------------------------- */
    rc = SQLBindParameter(proc_hstmt, 3, SQL_PARAM_OUTPUT, SQL_C_TCHAR, SQL_VARCHAR, 
              EXSPRET_SZ+1, 0, (SQLPOINTER)proc_ret_val, EXSPRET_SZ+1, &parmlen3 );
    load_odbc_err( henv, hdbc[context_num], proc_hstmt, rc );
    if ( rc < SQL_SUCCESS )
    {
        SQLFreeHandle(SQL_HANDLE_STMT, proc_hstmt);
        return( GDB_EXT_ERROR );
    }

    /* Call the dispatcher */
    /* ------------------- */
    rc = SQLExecDirect(proc_hstmt, _T("{call sp_handler(?, ?, ?)}"), SQL_NTS) ;
	if (rc == SQL_SUCCESS_WITH_INFO)
		rc = SQLMoreResults(hdbc[context_num]) ;
    load_odbc_err( henv, hdbc[context_num], proc_hstmt, rc );
    if ( rc < SQL_SUCCESS )
    {
        SQLFreeHandle( SQL_HANDLE_STMT, proc_hstmt );
        return( GDB_EXT_ERROR );
    }

    /* free the statement handle */
    /* ------------------------- */
    rc = SQLFreeHandle( SQL_HANDLE_STMT, proc_hstmt );
    load_odbc_err( henv, hdbc[context_num], proc_hstmt, rc );

    return GDB_SUCCESS ;
}


/*======================================================================
  sql_get_sqlda

  NOTE: This is not used with version 3.0 of ODBC ( Version 6.0 of bridge)

    - assuming a fetch has been performed, extract the data for 1
      column (col) in the descriptor and return within TRANS_VALUE union.
    - also extract the indicator 

    Arguments:
    - tunion: structure to hold 1 column of descriptor data
    - t_ind: stores the indicator value
    - col: the column from which the data is requested
    - shandle: statement handle
    - datatype: the datatype for the column (as determined by 'describe
      output'
  ======================================================================*/
long sql_get_sqlda(TRANS_VALUE *tunion, long *t_ind, long col, long shandle, long datatype)
{
    double    dbl_val ;
    float     float_val ;
    int       int_val ;
    gSQLDA   *select_ptr;
    SDWORD    max_col_len;
    SDWORD    ret_len;
    short     short_val;
    UWORD     icol ;
    GDB_CHAR* text_val ;

    select_ptr = sqlda_ptrs[context_num][shandle].sptr;

    icol = col + 1;
    switch (datatype)
    {
        case SQL_CHAR :
        case SQL_VARCHAR :
        case SQL_WCHAR :
        case SQL_WVARCHAR :
                
        /* convert dates and times to character */
        case SQL_DATE :
        case SQL_TIME :
        case SQL_TIMESTAMP :
        case SQL_GUID:      max_col_len = select_ptr[col].datalen + 1 ;
                            if ((text_val = (GDB_CHAR*)calloc(max_col_len, sizeof(GDB_CHAR))) == NULL) 
                            {
                                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for text_val")) ;
                                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                return GDB_ERROR ;
            }
            rc = SQLGetData( hstmt[context_num][shandle],
                                                  icol,
                                              SQL_C_TCHAR ,
                                                  text_val,
                                                  sizeof(GDB_CHAR) * max_col_len,
                                                  &ret_len ); 
            load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
                
            text_val[select_ptr[col].datalen] = 0;
                            wcscpy(tunion->t_wstr, text_val) ;
                            free(text_val) ;
            break;

        case SQL_INTEGER :  rc = SQLGetData( hstmt[context_num][shandle],
                                                  icol,
                                                  SQL_C_LONG,
                                                  &int_val,
                                                  0,
                                                  &ret_len );
            load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );

            tunion->t_int = int_val;
            break;

        case SQL_SMALLINT :
        case SQL_TINYINT :
        case SQL_BIT :      rc = SQLGetData( hstmt[context_num][shandle],
                                                  icol,
                                                  SQL_C_SHORT,
                                                  &short_val,
                                                  0,
                                                  &ret_len );
            load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );

            tunion->t_short = short_val;
            break;

        case SQL_REAL :     rc = SQLGetData( hstmt[context_num][shandle],
                                                  icol,
                                                  SQL_C_DEFAULT,
                                                  &float_val,
                                                  0,
                                                  &ret_len );
            load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
            tunion->t_float = float_val;
            break;

        case SQL_FLOAT :
        case SQL_DOUBLE:    rc = SQLGetData( hstmt[context_num][shandle],
                                                  icol,
                                                  SQL_C_DEFAULT,
                                                  &dbl_val,
                                                  0,
                                                  &ret_len ); 
            load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
            tunion->t_dbl = dbl_val;
            break;

        /* convert numeric and decimal to double */
        case SQL_NUMERIC :
        case SQL_DECIMAL :  rc = SQLGetData( hstmt[context_num][shandle],
                             icol,
                             SQL_C_DOUBLE,
                             &dbl_val,
                             0,
                             &ret_len );
            load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
            tunion->t_dbl = dbl_val;
            break;

        default:            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EINVDTY, datatype, icol) ;
                            return GDB_ERROR ;
            break;
    }
    
    /* set the null indicator */
    if ( ret_len == SQL_NULL_DATA )
        *t_ind = ret_len;
    else
        *t_ind = 0;

    return (rc < SQL_SUCCESS) ? GDB_EXT_ERROR : GDB_SUCCESS ;
}


/*======================================================================
  sql_release_bind
    - deallocate the SQLDA data buffers 

    Arguments:
    - shandle: statement handle
    - action: SELECT,BIND (see sql_dealloc_descriptors)
  ======================================================================*/
long sql_release_bind(long shandle, long action)
{
    gSQLDA  *select_ptr;
    gSQLDA  *bind_ptr;
    long     col ;
    long     status = 0;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_RELEASE_BIND")) ;

    if (shandle == 0) return GDB_ERROR ;

    if (action == BIND) 
    {
        bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

        if (bind_ptr == NULL)
            return GDB_SUCCESS ;

        for (col=0; col < context[context_num].max_bind_vars; col++) 
        {
            /* deallocate the data and NULL indicator portions of the bind_ptr */
            if (bind_ptr[col].data) 
            {
                XFREE(bind_ptr[col].data);
                bind_ptr[col].data = NULL;
            }
            if (bind_ptr[col].bdata) 
            {
                XFREE(bind_ptr[col].bdata);
                bind_ptr[col].bdata = NULL;
            }
            if (bind_ptr[col].ind) 
            {
                XFREE(bind_ptr[col].ind);
                bind_ptr[col].ind = NULL;
            }
        }
    } /* end if (action == BIND) */

    if (action == SELECT) 
    {
        select_ptr = sqlda_ptrs[context_num][shandle].sptr;

        if (select_ptr ==  NULL)
            return GDB_SUCCESS ;

        for (col=0;col<select_ptr[0].ncols;col++) 
        {
            if (select_ptr[col].colname != NULL) 
            {
                XFREE(select_ptr[col].colname);
                select_ptr[col].colname = NULL;
            }

            /* deallocate the data and NULL indicator portions of the select_ptr */
            if (select_ptr[col].data) 
            {
                XFREE(select_ptr[col].data);
                select_ptr[col].data = NULL;
            }
            if (select_ptr[col].ind) 
            {
                XFREE(select_ptr[col].ind);
                select_ptr[col].ind = NULL;
            }
        }
    } /* end if (action == SELECT) */

    return GDB_SUCCESS ;
}


/*======================================================================
  sql_exec_dynamic_sql
    - process non-query
    - statement must not contain 'select'
    - sql statement is passed directly to database 'as is'

    Arguments:
    - stmt_str: non-select sql statement
  ======================================================================*/
long sql_exec_dynamic_sql(long shandle, long stmt_id)
{
    SQLINTEGER  rows_affected=0;

    context_num = gsi_current_context();
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_EXEC_DYNAMIC_SQL")) ;

    if (shandle == 0) return GDB_ERROR ;

    /* Make sure connection is valid */
    if (!check_connection_hdl(hdbc[context_num])) return GDB_EXT_ERROR ;

    rc = SQLExecute( hstmt[context_num][shandle] );
    load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
    {
        return GDB_EXT_ERROR ;
    }

    rc = SQLRowCount( hstmt[context_num][shandle], &rows_affected );
    load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
    {
        return GDB_EXT_ERROR ;
    }

    row_count[context_num] = rows_affected;
    return GDB_SUCCESS ;
}


/*======================================================================
  sql_ping_db
    - attempt to access the database system tables to verify db connection
	- the table that we attempt to access is "sysusers".

    Arguments:
    - none
  ======================================================================*/
long sql_ping_db ()
{
    GDB_CHAR    testsql[100] = _T("SELECT COUNT(*) FROM NONSENSE") ;
    SQLHSTMT    test_stmt;
    short       ping_ok, i;
    SQLSMALLINT rec;

    context_num = gsi_current_context();

    /* Make sure connection is valid */
    if (! check_connection_hdl(hdbc[context_num])) 
    {
        g_sqlca.code = SQL_ERROR;
        hdbc[context_num] = 0;
        return( GDB_EXT_ERROR );
    }

    /* 
    ** Now send an SQL statement that has to access the data source.
    ** This will tell us for sure if we have a good connection.
    */
    rc = SQLAllocHandle( SQL_HANDLE_STMT,
                                      hdbc[context_num],
                                      &test_stmt );

    load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    if (rc < SQL_SUCCESS) 
    {
        hdbc[context_num] = 0;
        return ( GDB_EXT_ERROR );
    }

    rc = SQLExecDirect( test_stmt, testsql, SQL_NTS );

    /* 
    ** Test to check for a disconnected state:
    ** Load the state_array with the current SQLState(s).  
    ** If a sqlstate is equal to one of the states which indicate
    ** a connection error, then the 'Ping' did not succeed, return an error..
    ** For all other types of errors, 'Ping' succeeds, return success. 
    */
    ping_ok = TRUE;
    if (rc != SQL_SUCCESS) 
    {
        rc = SQL_SUCCESS;
        for (i=0, rec=i+1; (i<MAX_ODBC_ERRMSGS) && (rc==SQL_SUCCESS); i++, rec++) 
        {
            rc = SQLGetDiagRec( SQL_HANDLE_STMT,
                                test_stmt,
                                rec,
                                g_sqlca.state_array[i].sqlstate,
                                &g_sqlca.state_array[i].native_errcode,
                                g_sqlca.state_array[i].native_errmsg,
                                MAX_NATIVE_ERRLEN,
                                &g_sqlca.state_array[i].native_errlen );

            if (rc != SQL_SUCCESS) 
            {
                g_sqlca.state_array[i].native_errlen = 0;
                g_sqlca.state_array[i].native_errcode = 0;
                break;
            }
        } /* end for loop */
    }

    /* Commit the transaction if not in auto-commit mode */
    if (context[context_num].auto_commit == FALSE) 
    {
        rc = SQLTransact( henv, hdbc[context_num], SQL_COMMIT );
        if ( rc != SQL_SUCCESS )
            load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    }

    /* free the statement handle */
    SQLFreeHandle( SQL_HANDLE_STMT, test_stmt );

    if (check_sqlstate_disconnect()) 
    {
        /* DB not connected. Ping failed. Return the error */
        g_sqlca.code = SQL_ERROR;
		hdbc[context_num] = 0;
        return( GDB_EXT_ERROR );
    }
    else 
    {
        /* Ping OK. Override any errors with success */
        g_sqlca.state_array[0].native_errlen = 0;
        g_sqlca.state_array[0].native_errmsg[0] = _T('\0');
        g_sqlca.state_array[0].native_errcode = 0;
        g_sqlca.code = SQL_SUCCESS;
        return GDB_SUCCESS ;
    }
}


/*======================================================================
  sql_trigger
    Arguments:
    - trigger-name: name of trigger or pipe to listen on
    - trigger-timeout: seconds to wait for message
  ======================================================================*/
long sql_trigger(GDB_CHAR *trig_name, long trig_timeout, GDB_CHAR *trig_ret_msg, gsi_int context_num )
{
    short       i;
    int         len;
    GDB_CHAR     test_trig_name[MAX_TRIGGER_NAME_LEN+1] ;
    SQLINTEGER  parmlen1=SQL_NTS, parmlen2=SQL_NTS, parmlen3=SQL_NTS;
    SQLINTEGER  parmlen=0;
    static long p_stat;
    static GDB_CHAR t_msg[200];
    static GDB_CHAR t_datetime[30];
    GDB_CHAR     *wDBTYPE = NULL ;
    
    /* 
    ** CAUTION: context_num is passed from L1 as we are outside of
    ** run-loop during check (i.e. not within a context). Therefore
    ** you MUST NOT call any other function that utilizes a context
    ** number derived from gsi_current_context()
	*/
    len = wcslen(trig_name) ;
    if (len > MAX_TRIGGER_NAME_LEN)
    {
        return GDB_ERROR ;
    }
    wcscpy(test_trig_name, trig_name) ;

    /*
    ** Only allocate the statement handle and do the bindings
    ** once.
    */
    if (! trig_hstmt[context_num]) 
    {

        /* allocate a statement handle */
        rc = SQLAllocHandle( SQL_HANDLE_STMT,
                             hdbc[context_num],
                             &trig_hstmt[context_num] );

        load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
        if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );

        /*
        ** Fetch a row of information for the given trigger name from the
        ** trigger table and then delete that row. Both of these operations
        ** are done in the g2odbc_proc_trigs procedure
        */

        /* Bind the first parameter: trigger name (input) */
        rc = SQLBindParameter( trig_hstmt[context_num], 1, SQL_PARAM_INPUT, 
                               SQL_C_TCHAR, SQL_CHAR, len, 0,
                               test_trig_name, 0, &parmlen1);
        load_odbc_err( henv, hdbc[context_num], trig_hstmt[context_num], rc );
        if (rc < SQL_SUCCESS) 
        {
            SQLFreeHandle( SQL_HANDLE_STMT, trig_hstmt[context_num] );
            trig_hstmt[context_num] = NULL;
            return( GDB_EXT_ERROR );
        }

        /* Bind the second parameter: msg (output) */
        rc = SQLBindParameter( trig_hstmt[context_num], 2, SQL_PARAM_OUTPUT, 
                               SQL_C_TCHAR, SQL_CHAR, sizeof(t_msg)-1, 0,
                               t_msg, sizeof(t_msg), &parmlen2 );
        load_odbc_err( henv, hdbc[context_num], trig_hstmt[context_num], rc );
        if (rc < SQL_SUCCESS) 
        {
            SQLFreeHandle( SQL_HANDLE_STMT, trig_hstmt[context_num] );
            trig_hstmt[context_num] = NULL;
            return( GDB_EXT_ERROR );
        }

        /* Bind the third parameter: timestamp (output) */
        rc = SQLBindParameter( trig_hstmt[context_num], 3, SQL_PARAM_OUTPUT, 
                               SQL_C_TCHAR, SQL_CHAR, sizeof(t_datetime)-1, 0,
                               t_datetime, sizeof(t_datetime), &parmlen3 );
        load_odbc_err( henv, hdbc[context_num], trig_hstmt[context_num], rc );
        if (rc < SQL_SUCCESS) 
        {
            SQLFreeHandle( SQL_HANDLE_STMT, trig_hstmt[context_num] );
            trig_hstmt[context_num] = NULL;
            return( GDB_EXT_ERROR );
        }
    
        /* Bind the fourth parameter: the return value */
        rc = SQLBindParameter( trig_hstmt[context_num], 4, SQL_PARAM_OUTPUT, 
                               SQL_C_SLONG, SQL_INTEGER, 0, 0,
                               &p_stat, sizeof(p_stat), &parmlen);
        load_odbc_err( henv, hdbc[context_num], trig_hstmt[context_num], rc );
        if (rc < SQL_SUCCESS) 
        {
            SQLFreeHandle( SQL_HANDLE_STMT, trig_hstmt[context_num] );
            trig_hstmt[context_num] = NULL;
            return( GDB_EXT_ERROR );
        }
    }

    /* execute the statement */
    rc = SQLExecDirect( trig_hstmt[context_num],
                        _T("{call g2odbc_proc_trigs(?, ?, ?, ?)}"),
                        SQL_NTS );
    load_odbc_err( henv, hdbc[context_num], trig_hstmt[context_num], rc );
    if (rc < SQL_SUCCESS) 
    {
        SQLFreeHandle( SQL_HANDLE_STMT, trig_hstmt[context_num] );
		trig_hstmt[context_num] = NULL;
        return( GDB_EXT_ERROR );
    }


    if ((rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO)) 
    {
        if (p_stat != SQL_NO_DATA) 
        {
            /* Remove the trailing blanks from message and date */
            for (i=wcslen(t_msg)-1; (i>=0) && (t_msg[i]==' '); t_msg[i--]= _T('\0'));
            for (i=wcslen(t_datetime)-1; (i>=0) && (t_datetime[i]==_T(' ')); t_datetime[i--]=_T('\0'));
            _snwprintf(trig_ret_msg, 4000, _T("%s <%s>"), t_msg, t_datetime) ;
        }
        else
            *trig_ret_msg = 0;
    }
    else 
    {
        /* 
        ** The following prevents a continuous loop in check_triggers
        ** (never returning to gsi_run_loop) if the database connection
        ** gets dropped.
        */
        *trig_ret_msg = 0;
        if (context[context_num].console_output) 
        {
            wDBTYPE = widen(DB_TYPE) ;
            if (context[context_num].name != NULL)
                wprintf(_T("G2-%s: %s: %s: %d %s\n"), wDBTYPE, context[context_num].name,
                    ERROR_SYM, rc, _T("an error")) ;
            else
                wprintf(_T("G2-%s: %d: %s: %d %s\n"), wDBTYPE, context_num, ERROR_SYM,
                        rc, _T("an error")) ;
            if (wDBTYPE) free(wDBTYPE) ;
        }
        return GDB_EXT_ERROR ;
    }
	
    return GDB_SUCCESS ;
}


/*======================================================================
  sql_poll_check
    - called each time through gsi run-loop.
 ======================================================================*/
long sql_poll_check( void )
{
#if defined(WIN32)
    
  MSG  msg;

  if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
      DispatchMessage( &msg );

#endif
    return GDB_SUCCESS ;
}


/*======================================================================
  sql_exec_sql_obj
    Arguments:
    - shandle: the statement handle
    - array_size: the number of rows to be inserted or updated
    - stmt_id: not used
  ======================================================================*/
long sql_exec_sql_obj(long shandle, long array_size, long stmt_id)
{
    SQLINTEGER      rows_affected=0;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_EXEC_SQL_OBJ")) ;

    if (shandle == 0) return GDB_ERROR ;

    /* 
    ** Specify the number of values for each parameter
    ** (should be the number of values in the G2 array).
    */
    rc = SQLSetStmtAttr( hstmt[context_num][shandle],
                                      SQL_ATTR_PARAMSET_SIZE,
                                      (SQLPOINTER)array_size, 0);
    load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
    
    /* Execute the statement */
    rc = SQLExecute( hstmt[context_num][shandle] );
    load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
    if ( rc < SQL_SUCCESS ) return ( GDB_EXT_ERROR );
	
      /* Get the number of rows affected */
      rc = SQLRowCount( hstmt[context_num][shandle], &rows_affected );
      load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
      if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
      {
          return GDB_EXT_ERROR ;
      }
      row_count[context_num] = rows_affected;
  
      return GDB_SUCCESS ;
  }


/* ========================================================================== */
/*                                                                            */
/*                          The ODBC Bridge uses DSNs                         */
/*                                                                            */
/* ========================================================================== */
long    sql_uses_DSNs()
{
    return -1 ;
}

  
/* ========================================================================== */
/*                                                                            */
/*                           sql_configure_DSN                                */
/*                                                                            */
/* ========================================================================== */
long    sql_configure_DSN(gsi_int action, gsi_char* DrvrName, 
                          gsi_item* pKVStruct, gsi_int *piCode, gsi_char** pDSNName )
{
#define BUFFERSIZ  25
    GDB_CHAR        buffer[BUFFERSIZ] ;
    GDB_CHAR        *pParams ;

    gsi_attr        *pKV ;
    gsi_char        *gstrX, *gstrDSN=NULL ;
    double          gfltX ;
    gsi_int         nrKeys, ginX, ginV, attrType ;
    gsi_item        attrValue ;
    gsi_symbol      gsyX ;
    short           flDSN = 0, haveDSN = 0 ;

    WORD            param1 ;
    RETCODE         lrc;

    unsigned char   OK = 1 ;
    long            lParamStrSize = 2L, idx = 0 ;

    WORD            actionTable[] = { ODBC_ADD_DSN,     ODBC_CONFIG_DSN,     ODBC_REMOVE_DSN,
                                      ODBC_ADD_SYS_DSN, ODBC_CONFIG_SYS_DSN, ODBC_REMOVE_SYS_DSN } ;
    gsi_int         infoCodes[]   = { IDSNADD, IDSNMOD, IDSNDEL, IDSNADD, IDSNMOD, IDSNDEL } ;


    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_CONFIGURE_DSN")) ;

    context_num = gsi_current_context();

    if (--action > 2)
        action -= 7 ;
    if (action < 0 || action > 5)
        return EDSNOPT ;
    else
        *piCode = infoCodes[action] ;
    *pDSNName = NULL ;
    param1 = actionTable[action] ;


    /* Create the configuration string required by SQLConfigDataSource */
    /* from the input structure                                        */
    /* --------------------------------------------------------------- */
    if (gsi_type_of(*pKVStruct) != GSI_STRUCTURE_TAG) 
        return EDSNTYP ;
    nrKeys = gsi_attr_count_of(*pKVStruct) ;
    if (!nrKeys && param1 != ODBC_REMOVE_DSN && param1 != ODBC_REMOVE_SYS_DSN)
        return EDSNEST ;
    pKV = gsi_attrs_of(*pKVStruct) ;

    /* Scan the structure once to determine how much memory we need to allocate */
    /* ------------------------------------------------------------------------ */
    for (ginX = 0 ; ginX < nrKeys ; ginX++)
    {
        gsyX = gsi_attr_name_of(pKV[ginX]) ;
        gstrX = gsi_symbol_name(gsyX) ;
        if (flDSN = !_wcsicmp(gstrX, _T("DSN")))
            if (haveDSN)
                return EDSNMUL ; 
            else
                haveDSN = -1 ;
        lParamStrSize += wcslen(gstrX) ;   
        lParamStrSize++;
        attrValue = gsi_item_of_attr(pKV[ginX]) ;
        attrType = gsi_type_of(attrValue) ;     
        switch (attrType)
        {
            case GSI_STRING_TAG:    gstrX = gsi_str_of(attrValue) ;
                                    lParamStrSize += wcslen(gstrX) ;
                                if (flDSN) *pDSNName = gstrX ;
                                break ;

            case GSI_SYMBOL_TAG:    gsyX = gsi_sym_of(attrValue) ;
                                gstrX = gsi_symbol_name(gsyX) ;
                                    lParamStrSize += wcslen(gstrX) ;
                                if (flDSN) *pDSNName = gstrX ;
                                break ;

            case GSI_INTEGER_TAG:   ginV = gsi_int_of(attrValue) ;
                                    _snwprintf(buffer, BUFFERSIZ-1, _T("%ld"), ginV) ;
                                    lParamStrSize += wcslen(buffer) ;
                                break ;

            case GSI_FLOAT64_TAG:   gfltX = gsi_flt_of(attrValue) ;
                                    _snwprintf(buffer, BUFFERSIZ-1, _T("%f"), gfltX) ;
                                    lParamStrSize += wcslen(buffer) ;
                                break ;

            default:                OK = 0 ;
        }
        if (!OK)
           return EDSNTYP ;
        lParamStrSize++ ;  /* allocate space for the terminating '\0' */
    }

    /* Create the parameter string needed by SQLConfigDataSources */
    /* ---------------------------------------------------------- */
    pParams = (GDB_CHAR*)calloc(lParamStrSize, sizeof(GDB_CHAR)) ; 
    if (!pParams)
        return EINSMEM ;
    for (ginX = 0 ; ginX < nrKeys ; ginX++)
    {
        gsyX = gsi_attr_name_of(pKV[ginX]) ;
        gstrX = gsi_symbol_name(gsyX) ;
        wcscpy(pParams+idx, gstrX) ;
        idx += wcslen(gstrX) ;
        pParams[idx++] = '=' ;

        attrValue = gsi_item_of_attr(pKV[ginX]) ;
        attrType = gsi_type_of(attrValue) ;
        switch (attrType)
        {
            case GSI_STRING_TAG:    gstrX = gsi_str_of(attrValue) ;
                                    wcscpy(pParams+idx, gstrX) ;
                                    idx += wcslen(gstrX) ;
                                break ;

            case GSI_SYMBOL_TAG:    gsyX = gsi_sym_of(attrValue) ;
                                gstrX = gsi_symbol_name(gsyX) ;
                                    wcscpy(pParams+idx, gstrX) ;
                                    idx += wcslen(gstrX) ;
                                break ;

            case GSI_INTEGER_TAG:   ginV = gsi_int_of(attrValue) ;
                                    _snwprintf(buffer, BUFFERSIZ-1, _T("%ld"), ginV) ;
                                    wcscpy(pParams+idx, buffer) ;
                                    idx += wcslen(buffer) ;
                                break ;

            case GSI_FLOAT64_TAG:   gfltX = gsi_flt_of(attrValue) ;
                                    _snwprintf(buffer, BUFFERSIZ-1, _T("%f"), gfltX) ;
                                    wcscpy(pParams+idx, buffer) ;
                                    idx += wcslen(buffer) ;
                                break ;

            default:                OK = 0 ;
        }
        if (!OK)
        {
            free(pParams) ;
            return EDSNTYP ;
        }
        idx++ ;                 /* (calloc already put \0 in pParams[idx] */
    } 

    /* Add, Modify, or Delete the DSN */
    /* ------------------------------ */
    lrc = SQLConfigDataSource(NULL,param1,DrvrName,pParams) ;
    load_odbc_installer_err( lrc );

    /* Free the parameter string memory */
    /* -------------------------------- */
    free(pParams) ;

    return 0 ;
}


  /*======================================================================
    load_odbc_err
      - This function is called whenever an ODBC function is called.
      - It repeatedly calls SQLError until no more error msgs are returned.
      - It loads error information into the g_sqlca structure which is used
        later by the function 'get_stat'
  
      Arguments:
        - l_henv:  environment handle
        - l_hdbc:  database connection handle
        - l_hstmt: database statement handle
        - rc:      return code from the ODBC function
      
    ======================================================================*/
   void load_odbc_err( l_henv, l_hdbc, l_hstmt, l_rc )
      HENV        l_henv;
      HDBC        l_hdbc;
      HSTMT       l_hstmt;
      RETCODE     l_rc;
  {
      RETCODE     lo_rc;
      register short i;
  
      g_sqlca.state_array[0].native_errlen = 0;
      g_sqlca.state_array[0].native_errmsg[0] = _T('\0');
      g_sqlca.code = l_rc;
  
      /* Only get error info for non-sucessful ODBC calls */
      if ( g_sqlca.code != SQL_SUCCESS )
      {
        lo_rc = SQL_SUCCESS;
        for (i=0; (i<MAX_ODBC_ERRMSGS) && (lo_rc==SQL_SUCCESS); i++) 
        {
          lo_rc = SQLError( l_henv,
                            l_hdbc,
                            l_hstmt,
                            g_sqlca.state_array[i].sqlstate,
                            &g_sqlca.state_array[i].native_errcode,
                            g_sqlca.state_array[i].native_errmsg,
                            MAX_NATIVE_ERRLEN,
                            &g_sqlca.state_array[i].native_errlen);
                   
          if ((lo_rc == SQL_SUCCESS) && (debug & DBG1)) 
          {
            wprintf(_T("ODBC Error: "));
            wprintf(_T("sqlstate = '%s'\n"), g_sqlca.state_array[i].sqlstate);
            wprintf(_T("native errcode= %ld\n"), g_sqlca.state_array[i].native_errcode);
            wprintf(_T("native_errmsg = '%s'\n"), g_sqlca.state_array[i].native_errmsg);
            wprintf(_T("native_errlen = '%d'\n"), g_sqlca.state_array[i].native_errlen);
          }
          else if (lo_rc != SQL_SUCCESS) 
          {
            g_sqlca.state_array[i].native_errlen = 0;
            g_sqlca.state_array[i].native_errcode = 0;
            break;
          }
          else 
          {
            ; /* just continue */
          }
        }
      } /* end if ( l_rc != SQL_SUCCESS ) */
  
  }
  
void load_odbc_installer_err( RETCODE l_rc )
{
    RETCODE     lo_rc;
    short       i ;

    g_sqlca.state_array[0].native_errlen = 0;
    g_sqlca.state_array[0].native_errmsg[0] = '\0';
    g_sqlca.code = l_rc ? SQL_SUCCESS : SQL_ERROR ;

    if ( g_sqlca.code != SQL_SUCCESS )
    {
        lo_rc = SQL_SUCCESS;
        for ( i=0; (i<MAX_ODBC_ERRMSGS) && (lo_rc==SQL_SUCCESS); i++ )
        {
            lo_rc = SQLInstallerError(  (WORD)(i+1),
                                        &g_sqlca.state_array[i].native_errcode,
                                        g_sqlca.state_array[i].native_errmsg,
                                        SQL_MAX_MESSAGE_LENGTH-1,
                                        &g_sqlca.state_array[i].native_errlen) ;

            _snwprintf(g_sqlca.state_array[i].sqlstate, 6, _T("%s"), _T("<dsn>")) ;

            if ( (lo_rc == SQL_SUCCESS) && (debug & DBG1) )
            {
                wprintf(_T("ODBC Installer Error: "));
                wprintf(_T("sqlstate = '%s'\n"), g_sqlca.state_array[i].sqlstate);
                wprintf(_T("native errcode= %ld\n"), g_sqlca.state_array[i].native_errcode);
                wprintf(_T("native_errmsg = '%s'\n"), g_sqlca.state_array[i].native_errmsg);
                wprintf(_T("native_errlen = '%d'\n"), g_sqlca.state_array[i].native_errlen);
            }
            else if ( lo_rc != SQL_SUCCESS )
            {
                g_sqlca.state_array[i].native_errlen = 0;
                g_sqlca.state_array[i].native_errcode = 0;
                break;
            }
        }
    }
}


   
   /*======================================================================
    display_odbc_info
      - queries the ODBC driver manager about the driver and displays results
      
      Arguments:
      - none
    ======================================================================*/
  void display_odbc_info()
  {
      SQLINTEGER    ilen;
      SQLSMALLINT   slen;
      SQLUINTEGER   auto_commit=0;
      SQLUSMALLINT  txn_capable=0;
      UWORD         api_conf, sql_conf ;
      GDB_CHAR      dbms_name[100], dbms_ver[100] ;
      GDB_CHAR      driver_name[100], driver_ver[12], driver_mngr_ver[12] ;
      GDB_CHAR      driver_odbc_ver[6] ;
      GDB_CHAR      ds_name[100] ;
      GDB_CHAR      ds_readonly[2] ;
  
      /* Driver manager */
      SQLGetInfo( hdbc[context_num], SQL_ODBC_VER, driver_mngr_ver, sizeof(driver_mngr_ver), &slen );
  
      /* Driver name and version and which version of ODBC it supports */
      SQLGetInfo( hdbc[context_num], SQL_DRIVER_NAME, driver_name, sizeof(driver_name), &slen );
      SQLGetInfo( hdbc[context_num], SQL_DRIVER_VER, driver_ver, sizeof(driver_ver), &slen );
      SQLGetInfo( hdbc[context_num], SQL_DRIVER_ODBC_VER, driver_odbc_ver, sizeof(driver_odbc_ver), &slen );
  
      /* Database name and version */
      rc = SQLGetInfo( hdbc[context_num], SQL_DBMS_NAME, dbms_name, sizeof(dbms_name), &slen );
      rc = SQLGetInfo( hdbc[context_num], SQL_DBMS_VER, dbms_ver, sizeof(dbms_ver), &slen );
  
      /* Data source name and readonly flag */ 
      rc = SQLGetInfo( hdbc[context_num], SQL_DATA_SOURCE_NAME, ds_name, sizeof(ds_name), &slen );
      rc = SQLGetInfo( hdbc[context_num], SQL_DATA_SOURCE_READ_ONLY, ds_readonly, sizeof(ds_readonly), &slen );
  
      /* Conformance levels */
      SQLGetInfo( hdbc[context_num], SQL_ODBC_API_CONFORMANCE, &api_conf, sizeof(api_conf), &slen );
      SQLGetInfo( hdbc[context_num], SQL_ODBC_SQL_CONFORMANCE, &sql_conf, sizeof(sql_conf), &slen );
  
      wprintf(_T("ODBC Info:\n" )) ;
      wprintf(_T("    ODBC Driver Manager Version: %s\n"), driver_mngr_ver ) ;
      wprintf(_T("    ODBC Driver: %s  Version: %s\n"), driver_name, driver_ver ) ;
      wprintf(_T("    Driver supports ODBC Version: %s\n"), driver_odbc_ver ) ;
      wprintf(_T("    DBMS: %s  Version: %s\n"), dbms_name, dbms_ver ) ;
      wprintf(_T("    Data Source Name : %s\n"), ds_name ) ;
      wprintf(_T("    Data Source Read Only? : %s\n"), ds_readonly ) ;
      wprintf(_T("    Supports procedures? : %s\n"), proc_spt[context_num]) ;
   
      wprintf(_T("    ODBC Conformance Level: " )) ;
      if ( api_conf == SQL_OAC_NONE )
        printf("None\n") ;
      else if ( api_conf == SQL_OAC_LEVEL1 )
        printf("1\n") ;
      else if ( api_conf == SQL_OAC_LEVEL2 )
        printf("2\n") ;
      else
        printf("Unknown: (%d)\n", api_conf) ;
  
      printf("    SQL grammar support level: ") ;
      if ( sql_conf == SQL_OSC_MINIMUM )
        printf("Minimum\n") ;
      else if ( sql_conf == SQL_OSC_CORE )
        printf("Core\n") ;
      else if ( sql_conf == SQL_OSC_EXTENDED )
        printf("Extended\n") ;
      else
        printf("Unknown: (%d)\n", sql_conf) ;
  
      /*
      ** Determine if the ODBC driver is capable of transactions and
      ** whether or not auto-commit is on
      */
      rc = SQLGetInfo( hdbc[context_num], SQL_TXN_CAPABLE, &txn_capable, 
                       sizeof(txn_capable), NULL );
      printf("    Transactions supported? : " ) ;
      if ( txn_capable > SQL_TC_NONE ) 
          printf("Yes\n" ) ;
      else
          printf("No\n" ) ;
  
      rc = SQLGetConnectAttr( hdbc[context_num], SQL_ATTR_AUTOCOMMIT, &auto_commit,
                              (SQLINTEGER)NULL, &ilen );
      printf("    Auto-commit : " ) ;
      if ( auto_commit == SQL_AUTOCOMMIT_OFF ) 
          printf("OFF\n") ;
      else 
          printf("ON\n") ;
  }
  
  /*======================================================================
    bind_column
      - binds the columns of the result set to the gSQLDA
      
      Arguments:
      - select_ptr : a pointer to the data
      - scol       : number of the column we are binding
      - ctx        : context number
      - hdl        : handle number
    ======================================================================*/
  SQLRETURN bind_column( select_ptr, scol, ctx, hdl )
      gSQLDA         *select_ptr;
      SQLSMALLINT     scol;
      long            ctx;
      long            hdl;
  {
      SQLSMALLINT     bind_col;
      long            tlen=0;
  
      bind_col = scol + 1;
      switch ( select_ptr[scol].datatype )
      {
          case SQL_CHAR :
          case SQL_VARCHAR :
          case SQL_WCHAR :
          case SQL_WVARCHAR :
          case SQL_LONGVARCHAR :
          case SQL_WLONGVARCHAR:
          case SQL_GUID:
            /* The length is stored as the precision */
            select_ptr[scol].datalen = select_ptr[scol].colsize;
  
            /* G2 can only handle strings 64k long */
            if ( select_ptr[scol].datalen > PR_MAX_GSI_STRING_LEN )
                select_ptr[scol].datalen = PR_MAX_GSI_STRING_LEN;
            
            /* allocate space for data and null indicator */      
            if ( (select_ptr[scol].data = (GDB_CHAR*)calloc((select_ptr[scol].datalen+1)*(max_value_array_size+1), sizeof(GDB_CHAR))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for column data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            if ( (select_ptr[scol].ind = (long*)calloc(max_value_array_size+1, sizeof(long))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            rc = SQLBindCol( hstmt[ctx][hdl],
                             bind_col,
                             SQL_C_TCHAR,
                             select_ptr[scol].data,
                             sizeof(GDB_CHAR) * (select_ptr[scol].datalen+1), /* length in bytes */
                             select_ptr[scol].ind );
            break;

          case SQL_DATE :
          case SQL_TIME :
          case SQL_TIMESTAMP :
          case SQL_TYPE_DATE:
          case SQL_TYPE_TIME :
          case SQL_TYPE_TIMESTAMP :
            /* HACK!
            ** The length is a constant because ODBC returned the wrong value for 
            ** a timestamp thereby truncating data.
            */
            select_ptr[scol].datalen = MAX_DATE_LEN;
  
            if ( (select_ptr[scol].data = (GDB_CHAR*)calloc((select_ptr[scol].datalen+1)*(max_value_array_size+1), sizeof(GDB_CHAR))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for column data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            if ( (select_ptr[scol].ind = (long*)calloc(max_value_array_size+1, sizeof(long))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            rc = SQLBindCol( hstmt[ctx][hdl],
                             bind_col,
                             SQL_C_TCHAR,
                             select_ptr[scol].data,
                             sizeof(GDB_CHAR) * (select_ptr[scol].datalen+1), /* length in characters */
                             select_ptr[scol].ind );
  
            break;
  
        case SQL_INTEGER :
            select_ptr[scol].datalen = sizeof( GDB_INT );
            if ( (select_ptr[scol].data = (GDB_CHAR*)calloc(max_value_array_size+1, sizeof(GDB_INT))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for column data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            if ( (select_ptr[scol].ind = (long*) calloc(max_value_array_size+1, sizeof(long))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            rc = SQLBindCol( hstmt[ctx][hdl],
                             bind_col,
                             SQL_C_LONG,
                             select_ptr[scol].data,
                             /* Changed the following because
                                Oracle did not follow the
                                ODBC 3.0 ref manual */
                             sizeof(long),
                             select_ptr[scol].ind );
            break;
  
        case SQL_SMALLINT :
        case SQL_TINYINT :
        case SQL_BIT :
            select_ptr[scol].datalen = sizeof( GDB_INT );
            if ( (select_ptr[scol].data = (GDB_CHAR*)calloc(max_value_array_size+1, sizeof(GDB_INT))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for column data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            if ( (select_ptr[scol].ind = (long*) calloc(max_value_array_size+1, sizeof(long))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            rc = SQLBindCol( hstmt[ctx][hdl],
                             bind_col,
                             SQL_C_LONG,
                             select_ptr[scol].data,
                             /* Changed the following because
                                Oracle did not follow the
                                ODBC 3.0 ref manual */
                             sizeof(long),
                             select_ptr[scol].ind );
            break;

      case SQL_REAL :
          select_ptr[scol].datalen = sizeof( GDB_FLOAT );
          if ( (select_ptr[scol].data = 
              (GDB_CHAR*)calloc(max_value_array_size+1, sizeof(GDB_FLOAT))) == NULL) 
          {
              iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for column data")) ;
              iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
              return GDB_ERROR ;
          }
          if ( (select_ptr[scol].ind = (long*) calloc(max_value_array_size+1, sizeof(long))) == NULL) 
          {
              iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
              iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
              return GDB_ERROR ;
          }
          rc = SQLBindCol( hstmt[ctx][hdl],
                           bind_col,
                           SQL_C_FLOAT,
                           select_ptr[scol].data,
                           /* Changed the following because
                              Oracle did not follow the
                              ODBC 3.0 ref manual */
                           sizeof(float),
                           select_ptr[scol].ind );

          break;

      case SQL_FLOAT :
      case SQL_DOUBLE :
          select_ptr[scol].datalen = sizeof( GDB_DBL );
          if ( (select_ptr[scol].data = (GDB_CHAR*)calloc(max_value_array_size+1, sizeof(GDB_DBL))) == NULL) 
          {
              iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for column data")) ;
              iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
              return GDB_ERROR ;
          }
          if ( (select_ptr[scol].ind = (long*)calloc(max_value_array_size+1, sizeof(long))) == NULL) 
          {
              iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
              iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
              return GDB_ERROR ;
          }
          rc = SQLBindCol( hstmt[ctx][hdl],
                           bind_col,
                           SQL_C_DOUBLE,
                           select_ptr[scol].data,
                           /* Changed the following because
                              Oracle did not follow the
                              ODBC 3.0 ref manual */
                           sizeof(double),
                           select_ptr[scol].ind );
          break;

      case SQL_NUMERIC :
      case SQL_DECIMAL :
      case SQL_BIGINT:
          select_ptr[scol].datalen = select_ptr[scol].colsize;
          /* allocate space for data and null indicator */
          tlen = select_ptr[scol].datalen + select_ptr[scol].decdigs + 2;
          if ( (select_ptr[scol].data =
              (GDB_CHAR*)calloc(tlen*(max_value_array_size+1), sizeof(GDB_CHAR))) == NULL) 
          {
              iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
              iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
              return GDB_ERROR ;
          }
          if ((select_ptr[scol].ind = (long*)calloc(max_value_array_size+1, sizeof(long))) == NULL) 
          {
              iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for indicator data")) ;
              iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
              return GDB_ERROR ;
          }
          rc = SQLBindCol( hstmt[ctx][hdl],
                           bind_col,
                           SQL_C_TCHAR,
                           select_ptr[scol].data,
                           sizeof(GDB_CHAR) * tlen,  /* length in characters */
                           select_ptr[scol].ind );
          break;
          /*
          ** THIS TEST DOES NOT WORK FOR ORACLE SO THIS IS COMMENTED OUT
          ** If the scale is zero and the precision is greater than zero then
          ** the data type is integer, otherwise, the data type is a double 
          */
/*          if ((select_ptr[scol].colsize > 0) && (!select_ptr[scol].decdigs)) 
{
              select_ptr[scol].datatype = SQL_INTEGER;
              select_ptr[scol].datalen = sizeof( GDB_INT );
              if ( (select_ptr[scol].data = (char *) calloc(max_value_array_size, sizeof(int))) == NULL) 
              {
                  iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"Could not alloc mem for column data") ;
                  iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
                  return GDB_ERROR ;
              }
              if ( (select_ptr[scol].ind = (int *) calloc(max_value_array_size, sizeof(int))) == NULL) 
              {
                  iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"Could not alloc mem for indicator data") ;
                  iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
                  return GDB_ERROR ;
              }
              rc = SQLBindCol( hstmt[ctx][hdl],
                               bind_col,
                               SQL_C_LONG,
                               select_ptr[scol].data,
                               0, // Not used
                               select_ptr[scol].ind );
          }
          else 
          {
              select_ptr[scol].datalen = sizeof( GDB_DBL );
              if ( (select_ptr[scol].data = (char *) calloc(max_value_array_size, sizeof(double))) == NULL) 
              {
                  iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"Could not alloc mem for column data") ;
                  iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
                  return GDB_ERROR ;
              }
              if ( (select_ptr[scol].ind = (int *) calloc(max_value_array_size, sizeof(int))) == NULL) 
              {
                  iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"Could not alloc mem for indicator data") ;
                  iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
                  return GDB_ERROR ;
              }
              rc = SQLBindCol( hstmt[ctx][hdl],
                               bind_col,
                               SQL_C_DOUBLE,
                               select_ptr[scol].data,
                               0, // Not used
                               select_ptr[scol].ind );
          }

          break;
*/
      default :
          iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EINVDTY,
                select_ptr[scol].datatype, bind_col);
          return GDB_ERROR ;
          break;
    } /* end switch */

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
    {
        return GDB_ERROR ;
    }
    else
        return GDB_SUCCESS ;
 
}


/*======================================================================
  bind_parameter
    - binds a g2 array to the input parameters
    
    Arguments:
    - bind_ptr   : pointer to the data
    - datatype   : GDB data type of the bind data
    - bcol       : index into the bind_ptr structure
    - ctx        : context number
    - hdl        : handle number
  ======================================================================*/
SQLRETURN bind_parameter( bind_ptr, datatype, bcol, ctx, hdl )
    gSQLDA         *bind_ptr;
    long            datatype;
    SQLSMALLINT     bcol;
    long            ctx;
    long            hdl;
{
    SQLSMALLINT     pnum;
    long           *iptr;
    double         *dptr;

    pnum = bcol + 1;
    switch ( datatype )
    {
        case GDB_STRING_TYPE :
            rc = SQLBindParameter( hstmt[ctx][hdl],
                                   pnum,
                                   SQL_PARAM_INPUT,
                                   SQL_C_TCHAR,
                                   bind_ptr[bcol].datatype,
                                   bind_ptr[bcol].colsize,
                                   bind_ptr[bcol].decdigs,
                                   bind_ptr[bcol].bdata,
                                   sizeof(GDB_CHAR) * (bind_ptr[bcol].colsize+1),
                                   bind_ptr[bcol].ind );
        break;

        case GDB_WSTRING_TYPE :
            rc = SQLBindParameter( hstmt[ctx][hdl],
                                   pnum,
                                   SQL_PARAM_INPUT,
                                   SQL_C_TCHAR,
                                   bind_ptr[bcol].datatype,
                                   bind_ptr[bcol].colsize,
                                   bind_ptr[bcol].decdigs,
                                   bind_ptr[bcol].bdata,
                                   2 /*sizeof(wchar_t)*/ * (bind_ptr[bcol].colsize+1),
                                   bind_ptr[bcol].ind );
        break;

        case GDB_INT_TYPE :
            iptr = (long *)bind_ptr[bcol].bdata;
            rc = SQLBindParameter( hstmt[ctx][hdl],
                                   pnum,
                                   SQL_PARAM_INPUT,
                                   SQL_C_SLONG,
                                   bind_ptr[bcol].datatype,
                                   0, /* not used, */
                                   0, /* not used */
                                   iptr,
                                   /* Changed the following because
                                      Oracle did not follow the
                                      ODBC 3.0 ref manual */
                                   sizeof(long),
                                   bind_ptr[bcol].ind );
  	    break;

        case GDB_FLOAT_TYPE :
            dptr = (double *)bind_ptr[bcol].bdata;
            rc = SQLBindParameter( hstmt[ctx][hdl],
                                   pnum,
                                   SQL_PARAM_INPUT,
                                   SQL_C_DOUBLE,
                                   bind_ptr[bcol].datatype,
                                   bind_ptr[bcol].colsize,
                                   bind_ptr[bcol].decdigs,
                                   dptr,
                                   /* Changed the following because
                                      Oracle did not follow the
                                      ODBC 3.0 ref manual */
                                   sizeof(double),
                                   bind_ptr[bcol].ind );
  	    break;
    } /* end switch */
    
    load_odbc_err( henv, hdbc[ctx], hstmt[ctx][hdl], rc );
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
    {
        iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d",
              _T("Could not bind parameter number %"),pnum);
        return ( GDB_EXT_ERROR );
    }
    else
        return GDB_SUCCESS ;
 
}


  /*======================================================================
  check_connection_hdl
    - Determines whether or not the bridge has a valid connection handle.
    NOTE: It does not actually access the data source, but instead
          determines whether or not the connection is OK as far as the 
          Driver Manager is concerned.
    
    Arguments:
    - connection: the connection handle
	Returns:
	- True for a valid connection, False otherwise.
  ======================================================================*/
long check_connection_hdl(SQLHDBC connection)
{
    long       testhdbc;
    short      length;
    
    context_num = gsi_current_context();
    
    /* Check to see if the bridge thinks its connected */
    if (!connection)
    {
        g_sqlca.code = SQL_ERROR;
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE,"%d", ENODBCT) ;
        context[context_num].gbl_status.status = NOCONNECT_CD;
        return( FALSE );
    }

    /* Query the ODBC driver manager for the connection handle */
    rc = SQLGetInfo( connection,
                     SQL_DRIVER_HDBC, 
                     &testhdbc, 4, &length );
    if (rc < SQL_SUCCESS) 
    {
        load_odbc_err( henv, connection, NULL, rc );
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENODBCT) ;
        return( FALSE );
    }

    /* We have a valid connection */
    return ( TRUE );
}
	

  /*======================================================================
  check_sqlstate_disconnect
    - Determines whether or not one of the current SQLstates from
	  a call to an ODBC function indicates a disconnected state.
	  to the ODBC data source
    
    Arguments:
    - none
	Returns:
	- True if in a disconnected state, False otherwise.
  ======================================================================*/
long check_sqlstate_disconnect( )
{
    short i;
    for (i=0; (i<MAX_ODBC_ERRMSGS) && (g_sqlca.state_array[i].native_errlen!=0); i++) 
    {
        if ( (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08001"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08003"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08004"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08007"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08S01"))) )
        return  TRUE  ;
    }
    return( FALSE );
}


