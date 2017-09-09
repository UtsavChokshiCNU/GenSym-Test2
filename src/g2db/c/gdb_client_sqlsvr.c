/*================================================================
 *  GDB_CLIENT_SQLSVR.C    - GDB Layer-3   [source]
 *================================================================
 *
 * Author: Peter Hill
 *
 *    - LAYER-3 = gdb_client_inter_sqlsvr.c + gdb_client_sqlsvr.c
 *    - performs all calls to ODBC functions
 *    - extracts data from SQLDA and inserts into GENDA
 *    - upper layers should check status
 *================================================================*/

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <odbcinst.h>

#include "gdb_sqlsvr.h"
#include "gdb_client_inter_sqlsvr.h"
#include "gdb_globals.h"
#include "gdb_messages.h"
#include "gsi_main.h"
#include "gdb_context.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#include "gdb_g2_client.h"

#define LAYER LAYER3
#define SUPPORTED_ODBC_VERSION  3.0   // version of ODBC this bridge built with

/* local function prototypes */
void        display_odbc_info( );
long        check_connection_hdl( );
long        check_sqlstate_disconnect( );
SQLRETURN   bind_column( );
SQLRETURN   bind_parameter( );

/* context-sensitive globals */
extern CONTEXT_INFO context[MAX_GDB_CONTEXTS];
extern SQLDA_PTRS   *sqlda_ptrs[MAX_GDB_CONTEXTS];
extern long         max_col_array_size;
extern long         max_value_array_size; /* size of genda in rows */
extern long         row_count[MAX_GDB_CONTEXTS];
extern long         sqlfetch_cnt[MAX_GDB_CONTEXTS];
char                proc_spt[MAX_GDB_CONTEXTS][5];


/* globals */
extern long         debug;
gsi_int             context_num;

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
    
    return cpp_sql_setup();
}
                 
/*======================================================================
  sql_connect  (1)
    - establish connection to database
    Arguments:
    - db_user:   database username
    - db_pass:   database password
    - db_server: DSN data source name in the ODBC driver nanager
  ======================================================================*/

long sql_connect( db_user,db_pass,db_dsn )
    wchar_t    *db_user;
    wchar_t    *db_pass;
    wchar_t    *db_dsn;
{
        return cpp_sql_connect(db_user,db_pass,db_dsn);

}


/*======================================================================
  sql_disconnect
    - disconnect from the database
    - only free the connection handle if there was no connection initially
  ======================================================================*/

long sql_disconnect( context_num )
  gsi_int context_num;
{
    return cpp_sql_disconnect(context_num);
 
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

long sql_alloc_descriptors( shandle, action )
    long     shandle;
    long     action;
{
    return cpp_sql_alloc_descriptors( shandle, action );
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

long sql_prepare( shandle, stmt_id, sql_str )
    long     shandle;
    long    *stmt_id;
    wchar_t    *sql_str;
{
	return cpp_sql_prepare(shandle,stmt_id,sql_str );
}

/*======================================================================
  sql_declare_cursor
    - this function is unnecessary in the ODBC bridge
  
    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
    - stmt_id: statement id created from prepare
  ======================================================================*/

long sql_declare_cursor( curs_name, shandle, stmt_id )
    wchar_t    *curs_name;
    long     shandle;
    long    *stmt_id;
{

  return ( GDB_SUCCESS );

}
 

/*======================================================================
  sql_describe_input
    - id all host vars (INPUT VARIABLES) and load into bind descriptor
    - alloc memory for bind vars
    - get values for host bind vars
    - 
  ======================================================================*/
long sql_describe_input( shandle, bind_vars, stmt_id, bind_processed, action )
  long          shandle;
  BIND_STRUCT  *bind_vars;
  long         *stmt_id;
  long         *bind_processed;
  long          action;
{
	return cpp_sql_describe_input(shandle, bind_vars, stmt_id, bind_processed, action);
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
	return cpp_sql_describe_output(sqlGen, query_type );
}


/*======================================================================
  sql_open_cursor
    - open the 'declared' cursor
    - cursors must be opened prior to executing a 'fetch'
    - Not used in ODBC bridge
  
    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/

long sql_open_cursor( curs_name, shandle )
    wchar_t    *curs_name;
    long     shandle;
{
    return ( GDB_SUCCESS );
}


/*======================================================================
  sql_fetch
    - execute a previously prepared statement
    - fetch a database row into the defined descriptor
    
    Arguments:
    - curs_name: cursor name
    - shandle: statment handle
  ======================================================================*/

long sql_fetch( curs_name, shandle )
    wchar_t    *curs_name;
    long     shandle;
{
	return cpp_sql_fetch(curs_name,shandle);
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

long sql_dealloc_descriptors( shandle, action )
    long     shandle;
    long     action;
{   
    return cpp_sql_dealloc_descriptors(shandle, action );
}


/*======================================================================
  sql_close_cursor
    - close a previously opened cursor
    - Not used by ODBC bridge

    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/

long sql_close_cursor( curs_name, shandle, release_cursor )
    wchar_t    *curs_name;
    long     shandle;
    long     release_cursor; /* Not used by ODBC */
{
  return (GDB_SUCCESS);
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

long sql_exec_sql( stmt_str )
    wchar_t    *stmt_str;
{
	return cpp_sql_exec_sql( stmt_str );
}


/*======================================================================
  sql_commit
    - commit (and end) the transaction
  ======================================================================*/

long sql_commit()
{
	return cpp_sql_commit();
}


/*======================================================================
  sql_rollback
    - rollback (and end) the transaction
  ======================================================================*/

long sql_rollback()
{
	return cpp_sql_rollback();
}


/*======================================================================
  sql_refresh_cursor
    - reposition the cursor pointer to the first row in the cursor
    - close cursor so it can be used again

    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/

long sql_refresh_cursor( curs_name, shandle )
    wchar_t    *curs_name;
    long     shandle;
{
	return cpp_sql_refresh_cursor(curs_name,shandle);
}


/*======================================================================
  sql_release
    - release resources allocated by 'prepare' and 'declare cursor'

    Arguments:
    - stmt_id: statement id from 'prepare' 
  ======================================================================*/

long sql_release( stmt_id )
    long    *stmt_id;
{

  *stmt_id = 0;

  return (GDB_SUCCESS);

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

long sql_exec_stored_proc( sql_stmt )
    wchar_t    *sql_stmt;
{
	return cpp_sql_exec_stored_proc(sql_stmt);
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
long sql_exec_stored_proc_return(wchar_t *proc_name, wchar_t *proc_args, wchar_t *proc_ret_val )
{
	return cpp_sql_exec_stored_proc_return(proc_name, proc_args, proc_ret_val );   
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
    gSQLDA   *select_ptr ;
    SDWORD    max_col_len ;
    SDWORD    ret_len ;
    short     short_val ;
    UWORD     icol ;
    wchar_t*  text_val ;

    select_ptr = sqlda_ptrs[context_num][shandle].sptr ;

    icol = (UWORD) col + 1 ;
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
                            if ((text_val = calloc(max_col_len, sizeof(wchar_t))) == NULL) 
                            {
                                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for text_val")) ;
                                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                return GDB_ERROR ;
                            }
                            rc = SQLGetData( hstmt[context_num][shandle],
                                              icol,
                                              SQL_C_TCHAR,
                                              text_val,
                                              max_col_len,
                                              &ret_len ) ;
                
                            text_val[select_ptr[col].datalen] = 0 ;
#if defined(UNICODE)
                            wcscpy(tunion->t_wstr, text_val) ;
#else
                            strcpy(tunion->t_str, text_val) ;
#endif
                            free(text_val) ;
                            break ;

        case SQL_INTEGER :  rc = SQLGetData( hstmt[context_num][shandle],
                                              icol,
                                              SQL_C_LONG,
                                              &int_val,
                                              0,
                                              &ret_len ) ;
                            tunion->t_int = int_val ;
                            break ;

        case SQL_SMALLINT :
        case SQL_TINYINT :
        case SQL_BIT :      rc = SQLGetData( hstmt[context_num][shandle],
                                              icol,
                                              SQL_C_SHORT,
                                              &short_val,
                                              0,
                                              &ret_len ) ;

                            tunion->t_short = short_val ;
                            break ;

        case SQL_REAL :     rc = SQLGetData( hstmt[context_num][shandle],
                                              icol,
                                              SQL_C_DEFAULT,
                                              &float_val,
                                              0,
                                              &ret_len ) ;
                            tunion->t_float = float_val ;
                            break ;

        case SQL_FLOAT :
        case SQL_DOUBLE:    rc = SQLGetData( hstmt[context_num][shandle],
                                              icol,
                                              SQL_C_DEFAULT,
                                              &dbl_val,
                                              0,
                                              &ret_len ) ;
                            tunion->t_dbl = dbl_val ;
                            break ;

            /* convert numeric and decimal to double */
        case SQL_NUMERIC :
        case SQL_DECIMAL :  rc = SQLGetData( hstmt[context_num][shandle],
                                             icol,
                                             SQL_C_DOUBLE,
                                             &dbl_val,
                                             0,
                                             &ret_len ) ;

                            tunion->t_dbl = dbl_val ;
                            break ;

        default:            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EINVDTY, datatype, icol) ;
                            return GDB_ERROR ;
                            break ;
    }
    
    /* set the null indicator */
    if (ret_len == SQL_NULL_DATA)
        *t_ind = ret_len ;
    else
        *t_ind = 0 ;

    return (rc < SQL_SUCCESS) ? GDB_EXT_ERROR : GDB_SUCCESS ;
}

/*======================================================================
  sql_release_bind
    - deallocate the SQLDA data buffers 

    Arguments:
    - shandle: statement handle
    - action: SELECT,BIND (see sql_dealloc_descriptors)
  ======================================================================*/
                                             
long sql_release_bind( shandle, action )
    long     shandle;
    long     action;
{
	return cpp_sql_release_bind(shandle,action );
}


/*======================================================================
  sql_exec_dynamic_sql
    - process non-query
    - statement must not contain 'select'
    - sql statement is passed directly to database 'as is'

    Arguments:
    - stmt_str: non-select sql statement
  ======================================================================*/

long sql_exec_dynamic_sql( shandle, stmt_id )
    long   shandle;
    long   stmt_id;
{    
    return ( GDB_SUCCESS );
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
	return 0;
}

/*======================================================================
  sql_trigger
    Arguments:
    - trigger-name: name of trigger or pipe to listen on
    - trigger-timeout: seconds to wait for message
  ======================================================================*/

long sql_trigger( trig_name, trig_timeout, trig_ret_msg, context_num )
    wchar_t    *trig_name;
    long     trig_timeout;
    wchar_t    *trig_ret_msg;
    gsi_int  context_num;
{
    return cpp_sql_trigger(trig_name, trig_timeout, trig_ret_msg, context_num);
}


/*======================================================================
  sql_poll_check
    - called each time through gsi run-loop.
 ======================================================================*/

long sql_poll_check( void )
{
  MSG  msg;

  if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
      DispatchMessage( &msg );

  return (GDB_SUCCESS);
}


/*======================================================================
  sql_exec_sql_obj
    Arguments:
    - shandle: the statement handle
    - array_size: the number of rows to be inserted or updated
    - stmt_id: not used
  ======================================================================*/

long sql_exec_sql_obj( shandle, array_size, stmt_id )
    long   shandle;
    long   array_size;
    long   stmt_id;
{  
      return( GDB_SUCCESS );
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
                          gsi_item* pKVStruct, gsi_int *piCode, wchar_t** pDSNName )
{
#define BUFFERSIZ  25
    wchar_t         buffer[BUFFERSIZ] ;
    wchar_t        *pParams ;

    gsi_attr        *pKV ;
    gsi_char        *gstrX, *gstrDSN=NULL ;
    double          gfltX ;
    gsi_int         nrKeys, ginX, ginV, attrType ;
    gsi_item        attrValue ;
    gsi_symbol      gsyX ;
    short           flDSN = 0, haveDSN = 0 ;

    WORD            param1 ;
    RETCODE         lrc  = 0;

    unsigned char   OK = 1 ;
    long            lParamStrSize = 2L, idx = 0 ;

    WORD            actionTable[] = { ODBC_ADD_DSN,     ODBC_CONFIG_DSN,     ODBC_REMOVE_DSN,
                                      ODBC_ADD_SYS_DSN, ODBC_CONFIG_SYS_DSN, ODBC_REMOVE_SYS_DSN } ;
    gsi_int         infoCodes[]   = { IDSNADD, IDSNMOD, IDSNDEL, IDSNADD, IDSNMOD, IDSNDEL } ;


    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SQL_CONFIGURE_DSN")) ;

    context_num = gsi_current_context() ;

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
        lParamStrSize++ ;
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
        lParamStrSize++ ;  // allocate space for the terminating '\0'
    }

    /* Create the parameter string needed by SQLConfigDataSources */
    /* ---------------------------------------------------------- */
    pParams = calloc(lParamStrSize, sizeof(wchar_t)) ; 
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

    /* Free the parameter string memory */
    /* -------------------------------- */
    free(pParams) ;

    return 0 ;
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
	  return cpp_bind_column( select_ptr, scol,ctx,hdl);
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
	return cpp_bind_parameter( bind_ptr, datatype, bcol, ctx, hdl ); 
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
long check_connection_hdl()
{
	return cpp_check_connection_hdl();
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
    for ( i=0; (i<MAX_ODBC_ERRMSGS) && (g_sqlca.state_array[i].native_errlen!=0); i++ ) {
        if ( (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08001"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08003"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08004"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08007"))) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, _T("08S01"))) )
        return ( TRUE );
    }
    return( FALSE );
}
