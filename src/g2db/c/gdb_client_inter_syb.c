/*================================================================
 * GDB_CLIENT_INTER_SYB.C  - GDB Layer-3 (Sybase-10.0.3)  [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-3 = gdb_client_inter_syb.c + gdb_client_syb.ec
 *    - provide interface between 'common layer' and 'database
 *      specific layer'
 *================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "gdb_globals.h"
#include "gdb_genda.h"
#include "gdb_client_syb.h"
#include "gdb_client_inter_syb.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "gsi_main.h"
#include "gdb_utils.h"
#include "gdb_common.h"

#define LAYER LAYER3

extern long   sql_get_sqlda() ;

/* context-sensitive globals */
extern CONTEXT_INFO  context[MAX_GDB_CONTEXTS] ;

/* external globals */
extern long      debug ;
extern long      end_of_cursor ;
extern long      short_messages ;
extern long      max_col_array_size ;
extern BRIDGE_INFO   bridge_info ;

SQLDA_PTRS      *sqlda_ptrs[MAX_GDB_CONTEXTS] ;
gSQLCA          *gsqlca ;
long             row_count[MAX_GDB_CONTEXTS]; /* because SYB doesn't report row #'s */
gsi_int          context_num ;


/*======================================================================
  get_genda_data
    - load SQLDA(database) data into GENDA(bridge)

    Arguments:
    - sqlGen: GENDA structure receiving the database data
  ======================================================================*/

long get_genda_data( GENDA *sqlGen )
{
    TRANS_VALUE tunion ;
    gSQLDA*         select_ptr ;
    register long   row ;
    long		    start_row ;
    long		    rows_fetched ;
    long            col ;
    long            ind = 0 ;
    long            datatype ;
    long            datalen ;
    long            datascale ;
    long            null_len ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("GET_GENDA_DATA")) ;
    
    select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr ;
    if (select_ptr[0].ncols < 1) return GDB_ERROR ;
    
    null_len = strlen(context[context_num].null_string) ;
    
    /* Force array fetching OFF for now */
    context[context_num].array_fetch =  FALSE ;
    if (context[context_num].array_fetch) 
    {
        start_row = 0 ;

        /* determine the number of rows in THIS batch */
        rows_fetched = sqlGen->genStat.rows_processed % sqlGen->nrows ;

        /* if # rows fetched == genda size (nrows) */
        if (rows_fetched == 0 && sqlGen->genStat.rows_processed > 0 && 
            sqlGen->genStat.status != EOCURSOR_CD)
            rows_fetched = sqlGen->nrows ;

        /* if sql_function then only process the 1st row (batch not applicable) */
        if (sqlGen->nrows == 1 && sqlGen->genStat.rows_processed > 0 &&
            sqlGen->genStat.status == EOCURSOR_CD)
            rows_fetched = sqlGen->nrows ;
    }
    else 
    {
        start_row = sqlGen->more_rows ;
        rows_fetched = sqlGen->more_rows ;
    }
    
    for (row=start_row;row<rows_fetched+1;row++) /* The +1 is for EOCURSOR */   
    {
        
        for(col=0;col<select_ptr[0].ncols;col++)
        {
            datatype  = select_ptr[col].datatype ;
            datalen   = select_ptr[col].datalen ;
            datascale = select_ptr[col].scale ;
            
            /* insert gSQLDA into GENDA */
            switch (datatype)
            {
                case SB_CHAR :
                case SB_STRING :
                case SB_VARCHAR :
                case SB_DATETIME :
                case SB_SMALLDATETIME :
                                        sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE ;
                
                                        if ((sqlGen->da_col_ptr[col].val[row].gdb_str = 
                                            (GDB_CHAR*)calloc(datalen+1, sizeof(GDB_CHAR))) == NULL) 
                                        {
                                            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc gdb_str buffers")) ;
                                            iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
                                            return GDB_ERROR ;
                                        }

/*                                      if (sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_str == NULL)
                                        { 
                                            iomsg(DBG3|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s%d%d", L"Value buffer row % col % NOT allocated", sqlGen->more_rows, col) ;
                                            return GDB_ERROR ;
                                        }
*/

                                        tunion.t_str = sqlGen->da_col_ptr[col].val[row].gdb_str ;
                
                                        sql_get_sqlda(  &tunion,
                                                        &ind,
                                                        col,
                                                        sqlGen->stmt_handle,
                                                        datatype ) ;
                
                                        /* if (ind < 0 || sqlGen->genStat.code[sqlGen->more_rows] == end_of_cursor) {  */
                                        if ( ind < 0 ) 
                                        {
                                            if ((sqlGen->da_col_ptr[col].val[row].gdb_str = 
                                                realloc(sqlGen->da_col_ptr[col].val[row].gdb_str,
                                                (null_len+1)*sizeof(GDB_CHAR))) == NULL) 
                                            {
                                                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not realloc mem for gdb_str")) ;
                                                return GDB_ERROR ;
                                            }
                                            wcscpy(sqlGen->da_col_ptr[col].val[row].gdb_str, context[context_num].null_string) ;
                                        }
                                        sqlGen->da_col_ptr[col].ind[row] = ind ;
                                        break ;
                
                case SB_INTEGER :
                                        sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE ;
                
                                        sql_get_sqlda(  &tunion,
                                                        &ind,
                                                        col,
                                                        sqlGen->stmt_handle,
                                                        datatype ) ;
                
                                        sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = tunion.t_long ;
                
                                        if (ind < 0 || sqlGen->genStat.code == end_of_cursor)
                                            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number ;
                                        sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind ;
                                        break ;
                
                case SB_TINYINT :
                case SB_BIT :
                case SB_SMALLINT :
                                        sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE ;
                
                                        sql_get_sqlda(  &tunion,
                                                        &ind,
                                                        col,
                                                        sqlGen->stmt_handle,
                                                        datatype ) ;
                
                                        sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_short = tunion.t_short ;
                                        if (ind < 0 || sqlGen->genStat.code == end_of_cursor)
                                            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number ;
                                        sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind ;
                                        break ;
                
                case SB_SMALLMONEY :
                case SB_REAL_OLD :
                case SB_REAL :
                                        sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE ;
                
                                        sql_get_sqlda(  &tunion,
                                                        &ind,
                                                        col,
                                                        sqlGen->stmt_handle,
                                                        datatype ) ;
                
                                        sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_float = tunion.t_float ;
                                        if (ind < 0 || sqlGen->genStat.code == end_of_cursor)
                                            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = context[context_num].null_number ;
                                        sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind ;
                                        break ;
                
                case SB_MONEY :
                case SB_FLOAT :
                case SB_NUMERIC :
                case SB_DECIMAL :
                                        sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE ;
                
                                        sql_get_sqlda(  &tunion,
                                                        &ind,
                                                        col,
                                                        sqlGen->stmt_handle,
                                                        datatype ) ;
                
                                        sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = tunion.t_dbl ;
                                        if (ind < 0 || sqlGen->genStat.code == end_of_cursor)
                                            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = context[context_num].null_number ;
                                        sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind ;
                                        break ;
                
                default:
                                        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EINVDTY, datatype, col+1) ;
                                        return GDB_ERROR ;
                                        break ;
                
            } /*switch*/ 
        }
    
    }/* end loop for rows */
  
    if (sqlGen->genStat.code != end_of_cursor)
        sqlGen->more_rows++ ;
  
    return GDB_SUCCESS ;
}


/*======================================================================
  alloc_sqlda_ptrs
     - Allocate an array to store SQLDA addresses.
       The array is indexed via the stmt_handle.
     - SQLDA_PTRS array is not used by Sybase.
     - All EXEC SQL names are generated from shandle
       (e.g. if shandle=1 then stmt_id = S1)
  ======================================================================*/

long alloc_sqlda_ptrs()
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE,  "%s",  _T("ALLOC_SQLDA_PTRS")) ;
    
    /* for lack of a better place to assign the DB specific EOC code
       to the global end_of_cursor variable */
    end_of_cursor = DB_END_OF_CURSOR ;
    
    if (sqlda_ptrs[context_num] != NULL)
        return GDB_SUCCESS ;
    
    /*** alloc SQLDA_PTRS array ***/
    if ((sqlda_ptrs[context_num] = (SQLDA_PTRS *)calloc(MAX_CURSORS+1, sizeof(SQLDA_PTRS))) == NULL) 
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE,  "%s",  _T("Could not alloc mem for SQLDA_PTRS")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ;
}


/*======================================================================
  db_alloc_genda
    - alloc DB specific data area of GENDA
    - load init gSQLDA data into GENDA

    Arguments:
    - sqlGen: GENDA
    - max_rows: number of rows to allocate in the GENDA struct
  ======================================================================*/
long db_alloc_genda( GENDA *sqlGen, long max_rows )
{
    gSQLDA   *select_ptr ;
    long      col ;
    long      name_len ;
    short     no_col_name = 0 ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("DB_ALLOC_GENDA")) ;
    
    select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr ;
    
    for (col=0;col<sqlGen->ncols;col++) 
    {
        name_len = wcslen(select_ptr[col].colname) ;
        if (name_len == 0) 
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EBADCNM, GDB_UNKNOWN) ;
            return GDB_ERROR ;
        }
        else
        {
            /*
             ** if column name is UNKNOWN then check to make sure it's an SQL function.
             ** Otherwise, return an error.
              */
            if ( (!wcscmp(select_ptr[col].colname, GDB_UNKNOWN) ) && (sqlGen->nrows != 1) ) 
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EBADCNM, select_ptr[col].colname) ;
                return GDB_ERROR ;
            }
        }
        
        /* Allocate enough bytes for the column name. */
        if ((sqlGen->da_col_ptr[col].col_name = (char *)calloc(name_len+1, sizeof(char))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc col_name buffer")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        wcscpy(sqlGen->da_col_ptr[col].col_name, upper_case(select_ptr[col].colname)) ;
        
        /*** alloc sqlGen->nrows val & ind ptrs ***/
        if ((sqlGen->da_col_ptr[col].val = (DATA_VALUE *)calloc(max_rows+1, sizeof(DATA_VALUE))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc val ptrs")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        if ((sqlGen->da_col_ptr[col].ind = (long *)calloc(max_rows+1, sizeof(long))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc ind buffers")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }   
        
        /** alloc max_rows val buffers **/
        switch (select_ptr[col].datatype) 
        {
            case SB_CHAR :
            case SB_STRING :
            case SB_VARCHAR :
            case SB_DATETIME :
            case SB_SMALLDATETIME :
                                    sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE ;
/* 
** MOVED THE ALLOCATION OF THE VALUE STRUCTURE TO GET_GENDA      
*/
                                    break ;

            case SB_INTEGER :
                                    sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE ;
                                    break ;

            case SB_TINYINT :
            case SB_BIT :
            case SB_SMALLINT :
                                    sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE ;
                                    break ;
            
            case SB_SMALLMONEY :
            case SB_REAL_OLD :
            case SB_REAL :
                                    sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE ;
                                    break ;
            
            case SB_MONEY :
            case SB_FLOAT :
            case SB_NUMERIC :
            case SB_DECIMAL :
                                    sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE ;
                                    break ;
        }
    }
    iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("Allocated % row(s)"), max_rows) ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  set_error
    - if an error condition cannot be set due to insufficient memory, 
      this function will set a basic error message in the global and GENDA
      status structures so that the bridge will finish its current task and 
      notify the user. This funct should not be called by anything but 
      get_stat.

    Arguments:
      - sqlGen: GENDA
  ======================================================================*/

long set_error ( GENDA *sqlGen )
{
    context_num = gsi_current_context() ;
    
    context[context_num].gbl_status.code   = -1 ;
    context[context_num].gbl_status.status = -1 ;
    
    if (sqlGen != NULL) 
    {
        sqlGen->genStat.code = context[context_num].gbl_status.code ;
        sqlGen->genStat.status = context[context_num].gbl_status.status ;
    }
    
    return 0 ;
}


/*======================================================================
  get_stat
    - load genStat section of GENDA with gSQLCA
    - load gbl_status struct with gSQLCA

    Arguments:
    - sqlGen: GENDA
  ======================================================================*/
long get_stat( GENDA *sqlGen )
{
    GDB_CHAR prefix_msg[DB_TYPE_LEN+MAX_CONTEXT_NAME_LEN+STAT_SYM_LEN+4] ;
    GDB_CHAR text_msg[STATUS_MSG_LEN+1] ;
    long    msg_len  = 0 ;
    long    warn_len = 0 ;
    long    curr_len = 0 ;
    long    syb_layer=0 ;
    long    tmp ;
    
    context_num = gsi_current_context() ;
    
    if (gsqlca == NULL) return GDB_ERROR ;
    
    if (context[context_num].gbl_status.msg == NULL) 
    {
        if ((context[context_num].gbl_status.msg = (GDB_CHAR *)calloc(STATUS_MSG_LEN+1, sizeof(GDB_CHAR))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc mem for gbl_status.msg")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            set_error(sqlGen) ;
            return GDB_ERROR ;
        }
    }
    
    text_msg[0] = 0 ;
    prefix_msg[0] = 0 ;
    
    /*** load the gbl_status struct ***/
    syb_layer = MSG_LAYER(abs(gsqlca->sqlcode)) ;
    context[context_num].gbl_status.code = MSG_NUMBER(abs(gsqlca->sqlcode)) ;
    if (gsqlca->sqlcode >= 0) 
    {
        context[context_num].gbl_status.status = SUCCESS_CD ;
        context[context_num].gbl_status.rows_processed = row_count[context_num] ;
    }
    else if (gsqlca->sqlcode < 0) 
    {
        context[context_num].gbl_status.rows_processed = 0 ;
        context[context_num].gbl_status.code = abs(context[context_num].gbl_status.code) * -1 ;
    }
    
    if (gsqlca->sqlcode > 0) context[context_num].gbl_status.status = WARN_CD ;
    if (gsqlca->sqlcode < 0) context[context_num].gbl_status.status = ERROR_CD ;
    if (gsqlca->sqlcode == DB_END_OF_CURSOR) 
        context[context_num].gbl_status.status = EOCURSOR_CD ;
    
    *context[context_num].gbl_status.msg = 0 ;
    
    /* load the context info into message first */
    curr_len = load_msg(context[context_num].gbl_status.status, 0, &tmp, prefix_msg, FALSE) ;
    
    /* set the message length if there's an error */
    if (gsqlca->sqlcode < 0) 
    {
        msg_len = gsqlca->sqlerrm.sqlerrml ;
        if (msg_len > (STATUS_MSG_LEN - curr_len))
            msg_len = STATUS_MSG_LEN - curr_len ;
        
        if (msg_len > 0) 
        {
            wcsncpy(text_msg, gsqlca->sqlerrm.sqlerrmc, msg_len) ;
            text_msg[msg_len-1] = 0; /* because Sybase doesn't know how to calc lengths */
        }
        if (!text_msg[0]) 
            msg_len = 0 ;
    }
    
    curr_len += msg_len ;
    
    if (gsqlca->sqlwarn[0] == 'W' && *gsqlca->sqlwarn != 0) 
    { 
        if (gsqlca->sqlwarn[1] == 'W') 
        {
            warn_len = strlen(WARN2) ;
            if ((curr_len + warn_len) < STATUS_MSG_LEN) 
            {
                curr_len += warn_len ;
                strcat(text_msg, WARN2) ;
            }
            else
                iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WWRNCAT) ;
        }   
        context[context_num].gbl_status.rows_processed = row_count[context_num] ;
    }
    
    /* concat prefix and message body */
    _snwprintf(context[context_num].gbl_status.msg, msg_len,"%s%s", prefix_msg, text_msg) ;
    
    /*** load the GENDA struct ***/
    if (sqlGen != NULL) 
    {
        msg_len = strlen(context[context_num].gbl_status.msg) ;
        if (sqlGen->genStat.msg == NULL) 
        {
            if ((sqlGen->genStat.msg =
                (char *)calloc(msg_len+1, sizeof(char))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc mem for genStat.msg")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                set_error(sqlGen) ;
                return GDB_ERROR ;
            }
        }
        else 
        {
            if ((sqlGen->genStat.msg = (char *)
                realloc(sqlGen->genStat.msg,
                (msg_len+1)*sizeof(char))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT realloc mem for genStat.msg")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINMEMR) ;
                set_error(sqlGen) ;
                return GDB_ERROR ;
            }
        }
        strncpy(sqlGen->genStat.msg, context[context_num].gbl_status.msg, msg_len) ;
        sqlGen->genStat.msg[msg_len] = 0 ;
        sqlGen->genStat.code = context[context_num].gbl_status.code ;
        sqlGen->genStat.rows_processed = context[context_num].gbl_status.rows_processed ;
        sqlGen->genStat.status = context[context_num].gbl_status.status ;
    }
    
    if ( context[context_num].gbl_status.code == DB_NOT_CONNECTED && 
        syb_layer == SYB_CSLIB ) 
    {
        context[context_num].gbl_status.status = NOCONNECT_CD ;
        process_reconnect() ;
    }
    
    
    /*** reset certain gSQLCA fields to NULL ***/
    gsqlca->sqlerrm.sqlerrml = 0 ;
    *gsqlca->sqlwarn = 0 ;
    gsqlca->sqlcode = 0 ;
    
    if ((debug & DBG5) && context[context_num].gbl_status.status != SUCCESS_CD) 
    { 
        printf("\nSQL Message Structure\n") ;
        printf("ver   : %s\n", bridge_info.bridge_version ) ;
        printf("code  : %d\n", context[context_num].gbl_status.code) ;
        printf("msg   : %s\n", context[context_num].gbl_status.msg) ;
        printf("nrows : %d\n", context[context_num].gbl_status.rows_processed) ;
        printf("stat  : %d\n", context[context_num].gbl_status.status) ;
    }
    
    if ( context[context_num].gbl_status.status != SUCCESS_CD && 
        context[context_num].gbl_status.status != EOCURSOR_CD ) 
        return GDB_ERROR ;
    return GDB_SUCCESS ;
}


/*======================================================================
  load_bind_vars
  ======================================================================*/
long load_bind_vars( long shandle,  GDB_CHAR **bind_vars, long index, 
                     long datatype, long array_size )
{
    gSQLDA     *bind_ptr ;
    long       i, len, opts ;
    long       elmntsize ;
    short      *ind_array ;
    context_num = gsi_current_context() ;
    
    if (shandle == 0) return GDB_ERROR ;
    
    bind_ptr = sqlda_ptrs[context_num][shandle].bptr ;
    
    if (bind_ptr == NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", ENOTINI) ;
        return GDB_ERROR ;
    }
    
    /*
    ** Compare the datatype expected by the database to the datatype in the array 
    ** or list sent from G2.  If the datatypes are incompatible return to the caller
    ** with an error. Free the data area of the gSQLDA if was allocated previously
    ** via a "set" operation.
    */
    switch ( bind_ptr[index].datatype )
    {
    case SB_CHAR :
    case SB_STRING :
    case SB_VARCHAR :
    case SB_DATETIME :
    case SB_SMALLDATETIME :
        if ( datatype != GDB_STRING_TYPE ) 
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%d", EINCDTP, index+1) ;
            return  GDB_ERROR  ;
        }
        if ( bind_ptr[index].data ) 
        {
            for ( i=0; i<=array_size, bind_ptr[index].data[i] ;i++ ) 
            {
                free( bind_ptr[index].data[i] ) ;
                bind_ptr[index].data[i] = NULL ;
            }
            free( bind_ptr[index].data ) ;
            bind_ptr[index].data = NULL ;
        }
        break ;
        
    case SB_INTEGER :
    case SB_SMALLINT :
    case SB_TINYINT :
    case SB_BIT :
        if ( datatype != GDB_INT_TYPE ) 
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%d", EINCDTP, index+1) ;
            return  GDB_ERROR  ;
        }
        if ( bind_ptr[index].data ) 
        {
            free( bind_ptr[index].data ) ;
            bind_ptr[index].data = NULL ;
        }
        break ;
        
    case SB_SMALLMONEY :
    case SB_REAL_OLD :
    case SB_REAL :
    case SB_MONEY :
    case SB_FLOAT :
    case SB_NUMERIC :
    case SB_DECIMAL :
        if ( datatype != GDB_FLOAT_TYPE ) 
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%d", EINCDTP, index+1) ;
            return  GDB_ERROR  ;
        }
        if ( bind_ptr[index].data ) 
        {
            free( bind_ptr[index].data ) ;
            bind_ptr[index].data = NULL ;
        }
        break ;
    }
    
    /* free the NULL indicator area of the gSQLDA if previously allocated */
    if ( bind_ptr[index].ind ) 
    {
        free( bind_ptr[index].ind ) ;
        bind_ptr[index].ind = NULL ;
    }
    
    /* allocate the indicator array for NULLS */
    if ((ind_array = (short *)calloc(array_size, sizeof(short))) == NULL) 
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc indicator array")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    
    opts = context[context_num].set_null_options ;
    switch(datatype) 
    {
        
    case GDB_INT_TYPE:
        elmntsize = (long)sizeof(long) ;
        if ((bind_ptr[index].data = (char **)calloc(array_size, elmntsize)) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        if ((bind_ptr[index].ind = (short *)calloc(array_size, sizeof(short))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            free((short *)ind_array) ;
            return GDB_ERROR ;
        }     
        memcpy( bind_ptr[index].data, bind_vars, array_size*elmntsize ) ;
        
        /* check for null values */
        /* --------------------- */
        for (i=0;i<array_size;i++)
        {
            if ((opts & 0x1) && ((long *)bind_ptr[index].data)[i] == context[context_num].set_null_number)
                ind_array[i] = -1 ;
        }
        memcpy(bind_ptr[index].ind, ind_array, array_size*sizeof(short)) ;
        break ;
        
    case GDB_FLOAT_TYPE:
        elmntsize = (long)sizeof(double) ;
        if ((bind_ptr[index].data = (char **)calloc(array_size, elmntsize)) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        if ((bind_ptr[index].ind = (short *)calloc(array_size, sizeof(short))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            free((short *)ind_array) ;
            return GDB_ERROR ;
        }     
        memcpy( bind_ptr[index].data, bind_vars, array_size*elmntsize ) ;
        
        /* check for null values */
        /* --------------------- */
        for (i=0;i<array_size;i++)
        {
            if ((opts & 0x1) && ((double *)bind_ptr[index].data)[i] == (double)(context[context_num].set_null_number))
                ind_array[i] = -1 ;
        }
        memcpy(bind_ptr[index].ind, ind_array, array_size*sizeof(short)) ;
        break ;
        
    case GDB_STRING_TYPE:
        
        elmntsize = (long)sizeof(char *) ;
        if ((bind_ptr[index].data = (char **)calloc(array_size+1, elmntsize)) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        if ((bind_ptr[index].ind = (short *)calloc(array_size, sizeof(short))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            free((short *)ind_array) ;
            return GDB_ERROR ;
        }     
        /*    memcpy( bind_ptr[index].data, bind_vars, array_size*elmntsize );	 */
        
        elmntsize = (long)sizeof(char *) ;
        for (i=0; i<array_size; i++) 
        {
            len = strlen(bind_vars[i]) ;
            if ((bind_ptr[index].data[i] = (char *)calloc(len+1, elmntsize)) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data element")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            strcpy( bind_ptr[index].data[i], bind_vars[i] ) ;
            
            /* check for nulls */
            /* --------------- */
            if ((opts & 0x2) && !_wcsicmp(bind_vars[i], context[context_num].set_null_string) ) 
                ind_array[i] = -1 ;
            else if ((opts & 0x4) && !_wcsicmp(bind_vars[i], "NULL" )) 
                ind_array[i] = -1 ;
        }
        memcpy(bind_ptr[index].ind, ind_array, array_size*sizeof(short)) ;
        break ;
        
    } /* end switch */
    
    free ( ind_array ) ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  count_bind_vars
  ======================================================================*/
long count_bind_vars( long shandle, GDB_CHAR *bind_vars )
{
    register int nBind ;
    gSQLDA  *bind_ptr ;
    char  bind_name[MAX_VNAME_LEN] ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("COUNT_BIND_VARS")) ;
    
    if (shandle == 0) return GDB_ERROR ;
    
    bind_ptr = sqlda_ptrs[context_num][shandle].bptr ;
    
    nBind = 0 ;
    while (strgettoken(bind_vars, bind_name, ', ', nBind) != NULL)
        nBind++ ;
    
    if (nBind != bind_ptr[0].ncols) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", ENUMVAL, nBind, bind_ptr[0].ncols) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ;
}
