/*================================================================
 * GDB_CLIENT_INTER_ORA.C  - GDB Layer-3 (Oracle-7)       [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-3 = gdb_client_inter_ora.c + gdb_client_ora.pc
 *    - provide interface between 'common layer' and 'database
 *      specific layer'
 *
 *================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#if defined(UNICODE)
#include <wchar.h>
#endif

#include "gdb_globals.h"
#include "gdb_genda.h"
#include "gdb_client_ora.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "gsi_main.h"
#include "gdb_utils.h"
#include "gdb_common.h"

#define DBT_VARCHAR        _T("VARCHAR")
#define DBT_VARCHAR2       _T("VARCHAR2")
#define DBT_CHAR           _T("CHAR")
#define DBT_DATE           _T("DATE")
#define DBT_STRING         _T("STRING")
#define DBT_NUMBER         _T("NUMBER")

#define LAYER LAYER3

void dump_descriptor() ;

/* extern globals */
extern CONTEXT_INFO context[MAX_GDB_CONTEXTS] ;
extern BRIDGE_INFO  bridge_info ;
extern long   debug ;
extern long   end_of_cursor ;
extern long   short_messages ;
extern long   max_col_array_size ;

SQLDA_PTRS   *sqlda_ptrs[MAX_GDB_CONTEXTS] ;
gsi_int       context_num ;

/*======================================================================
  get_genda_data
    - load SQLDA(database) data into GENDA(bridge)

    Arguments:
    - sqlGen: GENDA structure receiving the database data
  ======================================================================*/
long get_genda_data(GENDA *sqlGen)
{
    SQLDA*          select_ptr ;
    short**         iptr;  /* for array fetching */
    GDB_CHAR**       vptr;  /* for array fetching */
    register long   row ;
    long            start_row ;
    long            rows_fetched ;
    long            null_len ;
    long            col ;

    context_num = gsi_current_context() ;

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("GET_GENDA_DATA")) ;

    /* since SQLDA is reused for each row fetched, the previous values are not
       cleared-out. Therefore, if a column value = NULL, then set STRING to
      'null_string' and NUMBERS to 'null_number' */

    select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr ;
    if (select_ptr->F < 1) return GDB_ERROR ;

    /* allocate vptr & iptr */
    if ((iptr = (short **)XCALLOC(/*context[context_num].max_ncols*/max_col_array_size, sizeof(short *))) == NULL)
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc iptr array")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    if ((vptr = (GDB_CHAR**)XCALLOC(/*context[context_num].max_ncols*/max_col_array_size, sizeof(GDB_CHAR*))) == NULL)
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc vptr array")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }

    /* initialize vptr & iptr to the starting addr of arrays pointed to by V[] and I[]
       respectively - arrays are traversed via the length of the data elements */

    for(col=0;col<select_ptr->F;col++)
    {
        vptr[col] = (GDB_CHAR*)select_ptr->V[col] ;
        iptr[col] = select_ptr->I[col] ;
    }

    null_len = wcslen(context[context_num].null_string) ;

    if (context[context_num].array_fetch)
    {
        start_row = 0 ;
        /* determine the number of rows in THIS batch */
        rows_fetched = sqlGen->genStat.rows_processed % sqlGen->nrows ;
        /* if # rows fetched == genda size (nrows) */
        if (rows_fetched == 0 && sqlGen->genStat.rows_processed > 0 && sqlGen->genStat.status != EOCURSOR_CD)
            rows_fetched = sqlGen->nrows ;
        /* if sql_function then only process the 1st row (batch not applicable) */
        if (sqlGen->nrows == 1 && sqlGen->genStat.rows_processed > 0 && sqlGen->genStat.status == EOCURSOR_CD)
            rows_fetched = sqlGen->nrows;
    }
    else
    {
        start_row = sqlGen->more_rows ;
        rows_fetched = sqlGen->more_rows ;
    }

    for (row=start_row;row<rows_fetched+1;row++)    /* +1 for EOCURSOR  */
    {
        for(col=0;col<select_ptr->F;col++)
        {
            /* load value buffers */
            switch (select_ptr->T[col])  /* switch on datatype */
            {
                case ORA_CHAR :
                case ORA_DATE :
                case ORA_STRING :   sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE ;

                                    sqlGen->da_col_ptr[col].val[row].gdb_str =
                                        (GDB_CHAR*)XCALLOC(select_ptr->L[col]+1, sizeof(GDB_CHAR)) ;

                                    if (*iptr[col] < 0)
                                    {
                                        /* does this realloc need to happen ???????? */
                                        if ((sqlGen->da_col_ptr[col].val[row].gdb_str =
                                            (GDB_CHAR*)realloc(sqlGen->da_col_ptr[col].val[row].gdb_str,
                                            (null_len+1)*sizeof(GDB_CHAR))) == NULL)
                                        {
                                            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not realloc mem for gdb_str")) ;
                                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINMEMR) ;
                                            return GDB_ERROR ;
                                        }

                                        wcscpy(sqlGen->da_col_ptr[col].val[row].gdb_str, context[context_num].null_string) ;
                                        break ;
                                    }
                                    if (sqlGen->da_col_ptr[col].val[row].gdb_str != NULL)
                                    {
                                        wcsncpy(sqlGen->da_col_ptr[col].val[row].gdb_str, vptr[col], select_ptr->L[col]) ;
                                        sqlGen->da_col_ptr[col].val[row].gdb_str[select_ptr->L[col]] = '\0' ;
                                    }
                                    else
                                    {
                                        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d%d", _T("Value buffer row % col % NOT allocated"), row, col);

                                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                                        return GDB_ERROR ;
                                    }
                                    break ;

                case ORA_FLOAT:     sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE ;
                                    if (*iptr[col] < 0)
                                        sqlGen->da_col_ptr[col].val[row].gdb_dbl = context[context_num].null_number ;
                                    else
                                        sqlGen->da_col_ptr[col].val[row].gdb_dbl = *(double *)vptr[col] ;
                                    break ;

                case ORA_INTEGER:   sqlGen->da_col_ptr[col].data_type = GDB_LONG_TYPE ;
                                    if (*iptr[col] < 0)
                                        sqlGen->da_col_ptr[col].val[row].gdb_long = context[context_num].null_number ;
                                    else
                                        sqlGen->da_col_ptr[col].val[row].gdb_long = *(long *)vptr[col] ;
                                    break ;

                default:            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EINVDTY, select_ptr->T[col], col+1) ;
                                    return GDB_ERROR ;
                                    break ;
            } /*switch*/

            sqlGen->da_col_ptr[col].ind[row] = *iptr[col];  /* load indicators */

            vptr[col] += select_ptr->L[col] ;
            iptr[col]++ ;
        }
    }

    sqlGen->more_rows = rows_fetched; /* removed from loop */

    if (context[context_num].array_fetch)
    {
        if (context[context_num].gbl_status.code == end_of_cursor)
        {
            sqlGen->genStat.status = EOCURSOR_CD;     /* added this for arrays */
            sqlGen->genStat.code = end_of_cursor;  /* added this for arrays */
        }
    }
    else
    {
        if (sqlGen->genStat.code != end_of_cursor)
            sqlGen->more_rows++ ;
    }

    if (iptr != NULL)
        XFREE(iptr) ;
    if (vptr != NULL)
        XFREE(vptr) ;

    return GDB_SUCCESS ;
}


/*======================================================================
  alloc_sqlda_ptrs
     - Allocate an array to store SQLDA addresses. The array is indexed
       via the stmt_handle.
  ======================================================================*/
long alloc_sqlda_ptrs(void)
{
    context_num = gsi_current_context() ;

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("ALLOC_SQLDA_PTRS")) ;

    /* for lack of a better place to assign the DB specific EOC code
       to the global end_of_cursor variable */
    end_of_cursor = DB_END_OF_CURSOR ;

    /*** alloc SQLDA_PTRS array ***/
    if (sqlda_ptrs[context_num] != NULL)
        return GDB_SUCCESS ;

    /* changed from max_cursors[context_num] */
    if ((sqlda_ptrs[context_num] = (SQLDA_PTRS *)XCALLOC(MAX_CURSORS+1, sizeof(SQLDA_PTRS))) == NULL)
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc mem for SQLDA_PTRS")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }

    return GDB_SUCCESS ;
}


/*======================================================================
  db_alloc_genda
    - alloc DB specific data area of GENDA
    - load init SQLDA data into GENDA

    Arguments:
    - sqlGen: GENDA
    - max_rows: number of rows to allocate in the GENDA struct
  ======================================================================*/
long db_alloc_genda(GENDA *sqlGen, long max_rows)
{
    long    shandle ;
    long    col ;
    long    name_len ;

    context_num = gsi_current_context() ;

    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("DB_ALLOC_GENDA"));
    }

    shandle = sqlGen->stmt_handle ;

    for (col=0; col < sqlGen->ncols; col++)
    {
        /* if no column name is supplied by DB */
        name_len = sqlda_ptrs[context_num][shandle].sptr->C[col] ;
        if (name_len == 0)
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EBADCNM, sqlda_ptrs[context_num][shandle].sptr->S[col]);

            return GDB_ERROR ;
        }
        else
        {
            /* if column name is supplied also check for '(' to make sure it's not a function. Also
               if performing a 'sql_function_rp' then skip the check as col name not used */
            sqlda_ptrs[context_num][shandle].sptr->S[col][name_len] = '\0' ;
            if (strchr(sqlda_ptrs[context_num][shandle].sptr->S[col], '(') != NULL && sqlGen->nrows != 1)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, _T("%d%s"), EBADCNM, sqlda_ptrs[context_num][shandle].sptr->S[col]);

                return GDB_ERROR ;
            }
        }

        /* since oracle returns the function-token as a col name (i.e. avg(xxx)), must
           check for the ')' */
        if (sqlda_ptrs[context_num][shandle].sptr->C[col] == 0 || strchr(sqlda_ptrs[context_num][shandle].sptr->S[col], '(') != NULL)
        {
            if ((sqlGen->da_col_ptr[col].col_name = (GDB_CHAR*)XCALLOC(wcslen(GDB_UNKNOWN)+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc col_name buffer"));

                iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            wcscpy(sqlGen->da_col_ptr[col].col_name, GDB_UNKNOWN) ;
        }
        else
        {
            if ((sqlGen->da_col_ptr[col].col_name = (GDB_CHAR*)XCALLOC(name_len+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc col_name buffer")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
                return GDB_ERROR ;
            }
            sqlda_ptrs[context_num][shandle].sptr->S[col][name_len] = '\0' ;
            wcscpy(sqlGen->da_col_ptr[col].col_name, upper_case((GDB_CHAR*)sqlda_ptrs[context_num][shandle].sptr->S[col])) ;
        }

        /** alloc sqlGen->nrows val & ind ptrs **/
        if ((sqlGen->da_col_ptr[col].val = (DATA_VALUE *)XCALLOC(max_rows+1, sizeof(DATA_VALUE))) == NULL)
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc val ptrs"));

            iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        if ((sqlGen->da_col_ptr[col].ind = (long *)XCALLOC(max_rows+1, sizeof(long))) == NULL)
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc ind buffers"));

            iomsg(DBGM, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }

        /** alloc max_rows val buffers **/
        /* Moved allocation to get_genda_data */
        switch (sqlda_ptrs[context_num][shandle].sptr->T[col])
        {
            case ORA_CHAR :
            case ORA_DATE :
            case ORA_STRING :
                                sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE ;
                                break ;

            case ORA_FLOAT :
                                sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE ;
                                break ;

            case ORA_INTEGER:
                                sqlGen->da_col_ptr[col].data_type = GDB_LONG_TYPE ;
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

  ====================================================================== */
long set_error(GENDA *sqlGen)
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
    - load genStat section of GENDA with SQLCA
    - load gbl_status struct with SQLCA

    Arguments:
    - sqlGen: GENDA
  ======================================================================*/
long get_stat(GENDA *sqlGen)
{
    GDB_CHAR prefix_msg[DB_TYPE_LEN+MAX_CONTEXT_NAME_LEN+STAT_SYM_LEN+4] ;
    GDB_CHAR text_msg[STATUS_MSG_LEN+1] ;
    long    batch_row = 0 ;
    size_t  msg_len  = 0 ;
    size_t  warn_len = 0 ;
    size_t  curr_len = 0 ;
    long    tmp_cd ;
    size_t  tmp ;

    context_num = gsi_current_context() ;

    if (context[context_num].gbl_status.msg == NULL)
    {
        if ((context[context_num].gbl_status.msg = (GDB_CHAR*)XCALLOC(STATUS_MSG_LEN+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc mem for gbl_status.msg"));

            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            set_error(sqlGen) ;
            return GDB_ERROR ;
        }
    }

    text_msg[0] = '\0' ;
    prefix_msg[0] = '\0' ;

    /*** load the gbl_status struct ***/
    context[context_num].gbl_status.code = sqlca.sqlcode ;
    if (sqlca.sqlcode >= 0)
    {
        context[context_num].gbl_status.status = SUCCESS_CD ;
        context[context_num].gbl_status.rows_processed = sqlca.sqlerrd[2] ;
        curr_len = sqlca.sqlerrm.sqlerrml;  /* added for exec-sql */
        if (curr_len > STATUS_MSG_LEN)
            curr_len = STATUS_MSG_LEN ;
        wcsncpy(text_msg, (GDB_CHAR*)sqlca.sqlerrm.sqlerrmc, curr_len) ;
        text_msg[curr_len] = '\0' ;
    }
    else if (sqlca.sqlcode < 0)
        context[context_num].gbl_status.rows_processed = 0 ;

    if (sqlca.sqlcode > 0) context[context_num].gbl_status.status = WARN_CD ;
    if (sqlca.sqlcode < 0) context[context_num].gbl_status.status = ERROR_CD ;
    if (sqlca.sqlcode == DB_END_OF_CURSOR)
        context[context_num].gbl_status.status = EOCURSOR_CD ;

    *context[context_num].gbl_status.msg = '\0' ;

    /* load the context info into message first */
    curr_len = load_msg(context[context_num].gbl_status.status, 0, &tmp_cd, prefix_msg, FALSE) ;

    if (sqlca.sqlcode < 0)
    {
        msg_len = STATUS_MSG_LEN - curr_len ;
        if (msg_len > 0)
        {
            sqlglm((unsigned char*)text_msg, &msg_len, &tmp);
            text_msg[tmp] = '\0' ;
        }
        if (!text_msg)
            msg_len = 0 ;
    }

    curr_len += msg_len ;

    if (sqlca.sqlwarn[0] == 'W' && *sqlca.sqlwarn != 0)
    {
        if (sqlca.sqlwarn[1] == 'W')
        {
            warn_len = wcslen(WARN2) ;
            if ((curr_len + warn_len) < STATUS_MSG_LEN)
            {
                curr_len += warn_len ;
                wcscat(text_msg, WARN2) ;
            }
            else
                iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WWRNCAT) ;
        }
        if (sqlca.sqlwarn[4] == 'W')
        {
            warn_len = wcslen(WARN5) ;
            if ((curr_len + warn_len) < STATUS_MSG_LEN)
            {
                curr_len += warn_len ;
                wcscat(text_msg, WARN5) ;
            }
            else
                iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WWRNCAT) ;
        }
        context[context_num].gbl_status.rows_processed = sqlca.sqlerrd[2] ;
    }

    /* concat prefix and message body */
    swprintf(context[context_num].gbl_status.msg, _T("%s%s"), prefix_msg, text_msg) ;

    /*** load the GENDA struct ***/
    if (sqlGen != NULL)
    {
        if (context[context_num].array_fetch)
        {
            if ( sqlGen->genStat.rows_processed == context[context_num].gbl_status.rows_processed &&
                context[context_num].gbl_status.status == EOCURSOR_CD )
            {
                /*
                   This is necessary if the array_size is equal to the # of rows fetched.
                   Since it requires 1 extra fetch in order to get the EOCURSOR code. The
                   last fetch will return 0 rows, but sqlerrd[2] will still reflect the
                   number of rows fetched in the previous fetch. This will cause bridge
                   array indexing problems if not set to 0 rows.
                */
                context[context_num].gbl_status.rows_processed = 0 ;
            }

            /* determine the number of rows in THIS batch (array) */
            batch_row = context[context_num].gbl_status.rows_processed % sqlGen->nrows ;
            if (batch_row == 0 && context[context_num].gbl_status.rows_processed != 0)
            {
                if (context[context_num].gbl_status.status != EOCURSOR_CD)
                    batch_row = sqlGen->nrows-1 ;
                else
                    batch_row = context[context_num].gbl_status.rows_processed ;
            }
        }
        else
            batch_row = sqlGen->more_rows ;

        msg_len = wcslen(context[context_num].gbl_status.msg) ;
        if (sqlGen->genStat.msg == NULL)
        {
            if ((sqlGen->genStat.msg = (GDB_CHAR*)XCALLOC(msg_len+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT alloc mem for genStat.msg"));

                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                set_error(sqlGen) ;
                return GDB_ERROR ;
            }
        }
        else
        {
            if ((sqlGen->genStat.msg = (GDB_CHAR*)
                realloc(sqlGen->genStat.msg,
                (msg_len+1)*sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could NOT realloc mem for genStat.msg"));

                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINMEMR) ;
                set_error(sqlGen) ;
                return GDB_ERROR ;
            }
        }
        wcsncpy(sqlGen->genStat.msg, context[context_num].gbl_status.msg, msg_len) ;
        sqlGen->genStat.msg[msg_len] = '\0' ;
        sqlGen->genStat.code = context[context_num].gbl_status.code ;

        /*    sqlGen->genStat.rows_processed = context[context_num].gbl_status.rows_processed; */
        /*    ?????????
              this was modified since queries which equal the sqlGen->nrows size were not yielding
              the correct 'rows-processed' number when EOCURSOR was encountered (it was being reset
              to 0
        */

        sqlGen->genStat.rows_processed = sqlca.sqlerrd[2] ;
        sqlGen->genStat.status = context[context_num].gbl_status.status ;
    }

    /* reconnect to DB if disconnect detected */
    if (sqlca.sqlcode == DB_NOT_CONNECTED1 || sqlca.sqlcode == DB_NOT_CONNECTED2 ||
        sqlca.sqlcode == DB_NOT_CONNECTED3 )
    {
        context[context_num].gbl_status.status = NOCONNECT_CD ;
        context[context_num].connected_to_db = FALSE ;
        process_reconnect() ;
    }

    /*** reset certain SQLCA fields to NULL ***/
    sqlca.sqlerrm.sqlerrml = 0 ;
    sqlca.sqlerrd[2] = 0 ;
    *sqlca.sqlwarn = 0 ;
    sqlca.sqlcode = 0 ;

    if ((debug & DBG5) && context[context_num].gbl_status.status != SUCCESS_CD)
    {
        printf("\nSQL Message Structure\n") ;
        printf("ver   : %s\n", bridge_info.bridge_version) ;
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
long load_bind_vars(long shandle,  void **bind_vars, long index, long datatype, long array_size )
{
    register long   i ;
    SQLDA*          bind_ptr ;
    GDB_CHAR*        temp ;
    short*          ind_array ;
    long            maxlen, len ;

    context_num = gsi_current_context() ;

    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("LOAD_BIND_VARS"));
    }

    if (shandle == 0) return GDB_ERROR ;

    bind_ptr = sqlda_ptrs[context_num][shandle].bptr ;

    if (bind_ptr == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", ENOTINI) ;
        return GDB_ERROR ;
    }

    /*
       compare G2 datatype to DB datatype - Since Oracle handles this in DB, we
       don't have to worry about it here
       iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, _T("%d%d"), EINCDTP, index) ;
       return GDB_ERROR ;
    */

    if ((ind_array = (short *)XCALLOC(array_size, sizeof(short))) == NULL)
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc indicator array"));

        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }

#ifndef rs6000
    switch(datatype)
    {
        case GDB_INT_TYPE:
            bind_ptr->L[index] = (long)sizeof(long) ;
            if ((bind_ptr->V[index] = (char *)XCALLOC(array_size, bind_ptr->L[index])) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data array")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                XFREE((short *)ind_array) ;
                return GDB_ERROR ;
            }
            if ((bind_ptr->I[index] = (short *)XCALLOC(array_size, sizeof(short))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                XFREE((short *)ind_array) ;
                return GDB_ERROR ;
            }
            memcpy(bind_ptr->V[index], bind_vars, (array_size*bind_ptr->L[index])) ;

            /* Check for null values */
            /* --------------------- */
            for (i=0;i<array_size;i++)
            {
                if ((context[context_num].set_null_options & 0x1) && ((long *)bind_ptr->V[index])[i] == context[context_num].set_null_number)
                    ind_array[i] = -1 ;
            }

            memcpy(bind_ptr->I[index], ind_array, array_size*sizeof(short)) ;
            bind_ptr->T[index] = ORA_INTEGER ;
            break ;

        case GDB_FLOAT_TYPE:
            bind_ptr->L[index] = (long)sizeof(double) ;
            if ((bind_ptr->V[index] = (char *)XCALLOC(array_size, bind_ptr->L[index])) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data array")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                XFREE((short *)ind_array) ;
                return GDB_ERROR ;
            }
            if ((bind_ptr->I[index] = (short *)XCALLOC(array_size, sizeof(short))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                XFREE((short *)ind_array) ;
                return GDB_ERROR ;
            }
            memcpy(bind_ptr->V[index], bind_vars, array_size*bind_ptr->L[index]) ;

            /* check for null values */
            /* --------------------- */
            for (i=0;i<array_size;i++)
            {
                if ((context[context_num].set_null_options & 0x1) &&
                    ((double *)bind_ptr->V[index])[i] == (double)(context[context_num].set_null_number) )
                    ind_array[i] = -1 ;
            }
            memcpy(bind_ptr->I[index], ind_array, array_size*sizeof(short)) ;
            bind_ptr->T[index] = ORA_FLOAT;
            break ;

        case GDB_STRING_TYPE:
            /* the problem with strings is that the memory must be contiguous for Oracle
               to be able to read the array. Therefore, to hack around this, you must
               simulate an array by creating a jumbo string with the proper padding between
               elements. Basically, you cannot use **GDB_CHAR or *GDB_CHAR[n] pointers */

            /* determine max string length */
            maxlen = 0 ;
            for (i=0;i<array_size;i++)
            {
                len = strlen(bind_vars[i]) ;
                if (len > maxlen)
                    maxlen = len ;
            }

            if ((temp = (GDB_CHAR*)XCALLOC(maxlen*array_size+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc load_bind temp array")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                XFREE((short *)ind_array) ;
                return GDB_ERROR ;
            }

            /* copy all the values into 1 contiguous memory region, padding each
               value out to the array size */
            for (i=0;i<array_size;i++)
            {
                swprintf(temp, _T("%s%-*s"), temp, maxlen, bind_vars[i]);

                /* check for null values */
                if ((context[context_num].set_null_options & 0x2) &&
                    !_wcsicmp(bind_vars[i], context[context_num].set_null_string))
                    ind_array[i] = -1 ;
                else if ((context[context_num].set_null_options & 0x4) && !_wcsicmp(bind_vars[i], _T("NULL")))
                    ind_array[i] = -1 ;
            }

            bind_ptr->L[index] = maxlen ;
            if ((bind_ptr->V[index] = (char *)XCALLOC(array_size, bind_ptr->L[index])) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data array")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                XFREE((char *)temp) ;
                XFREE((short *)ind_array) ;
                return GDB_ERROR ;
            }
            if ((bind_ptr->I[index] = (short *)XCALLOC(array_size, sizeof(short))) == NULL)
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
                XFREE((short *)ind_array) ;
                return GDB_ERROR ;
            }
            memcpy(bind_ptr->V[index], temp, array_size*bind_ptr->L[index]) ;
            memcpy(bind_ptr->I[index], ind_array, array_size*sizeof(short)) ;
            bind_ptr->T[index] = ORA_VARCHAR2 ;

            XFREE(temp) ;

            break ;
      } /* switch */
#else

    /**************************************************************************
      DUE TO A PROBLEM WITH FLOATS & BIND DESCRIPTORS ON RS6000 EVERYTHING HERE
      IS CONVERTED TO A STRING BUFFER BEFORE BEING LOADED INTO THE DESCRIPTOR.
      THIS IS OBVIOUSLY LESS EFFICIENT THAN SIMPLY MEMMOVEing THE SOURCE ARRAY
      INTO THE DESCRIPTOR AND SETTING THE APPROPRIATE DESCRIPTOR 'TYPE'.
     **************************************************************************/

    /* the problem with strings is that the memory must be contiguous for Oracle
       to be able to read the array. Therefore, to hack around this, you must
       simulate an array by creating a jumbo string with the proper padding between
       elements. Basically, you cannot use **GDB_CHAR or *GDB_CHAR[n] pointers */

    /* determine max string length */
    switch(datatype)
    {
        case GDB_STRING_TYPE:
            maxlen = 0 ;
            for (i=0;i<array_size;i++)
            {
                len = strlen(bind_vars[i]) ;
                if (len > maxlen)
                    maxlen = len ;
            }
            break ;
        
        case GDB_FLOAT_TYPE:
            maxlen = 40;  /* Max Oracle precision = 38 digits + 1 decimal + 1 sign */
            break ;
        
        case GDB_INT_TYPE:
            maxlen = 10;  /* MAX_G2_INTEGER +1 for sign */
            break ;
        }
    
        if ((temp = (GDB_CHAR*)XCALLOC(maxlen*array_size+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc load_bind temp array")) ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
            XFREE(ind_array) ;
            return GDB_ERROR ;
        }
    
        switch(datatype)
        {
        case GDB_STRING_TYPE:
        /* copy all the values into 1 contiguous memory region, padding each
           value out to the array size */
            for (i=0;i<array_size;i++)
            {
                swprintf(temp, _T("%s%-*s"), temp, maxlen, bind_vars[i]) ;
            
                /* check for null values */
                /* --------------------- */
                if ((context[context_num].set_null_options & 0x2) &&
                    !_wcsicmp(bind_vars[i], context[context_num].set_null_string))
                    ind_array[i] = -1 ;
                else if ((context[context_num].set_null_options & 0x4) &&
                    !_wcsicmp(bind_vars[i], FORMAT_NULL))
                    ind_array[i] = -1 ;
            }
            break ;
        
        case GDB_FLOAT_TYPE:
        /* copy all the values into 1 contiguous memory region, padding each
           value out to the array size */
            for (i=0;i<array_size;i++)
            {
                _snwprintf(temp, STRLEN(temp), _T("%s%-*f"), temp, maxlen, ((double *)bind_vars)[i]) ;
            
                /* check for null values */
                /* --------------------- */
                if ((context[context_num].set_null_options & 0x1) &&
                    ((double *)bind_vars)[i] == context[context_num].set_null_number)
                    ind_array[i] = -1 ;
            }
            break ;
        
        case GDB_INT_TYPE:
        /* copy all the values into 1 contiguous memory region, padding each
           value out to the array size */
            for (i=0;i<array_size;i++)
            {
                swprintf(temp, _T("%s%-*d"), temp, maxlen, ((long *)bind_vars)[i]) ;
            
                /* check for null values */
                /* --------------------- */
                if ((context[context_num].set_null_options & 0x1) &&
                    (long *)bind_vars)[i] == context[context_num].set_null_number )
                    ind_array[i] = -1;  */
            }
            break ;
    }
    
    bind_ptr->L[index] = maxlen ;
    if ((bind_ptr->V[index] = (char *)XCALLOC(maxlen*array_size+1, sizeof(char))) == NULL)
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc data array")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        XFREE((char *)temp) ;
        XFREE((short *)ind_array) ;
        return GDB_ERROR ;
    }
    if ((bind_ptr->I[index] = (short *)XCALLOC(array_size, sizeof(short))) == NULL)
    {
        iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Could not alloc ind array")) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINSMEM) ;
        XFREE((short *)ind_array) ;
        return GDB_ERROR ;
    }
    
    memcpy(bind_ptr->V[index], temp, array_size*bind_ptr->L[index]) ;
    memcpy(bind_ptr->I[index], ind_array, array_size*sizeof(short)) ;
    bind_ptr->T[index] = ORA_VARCHAR2 ;
    
    XFREE(temp) ;

#endif

    XFREE(ind_array) ;

    if (debug & DBG10)
        dump_descriptor(bind_ptr, array_size) ;

    return GDB_SUCCESS ;
}


/*======================================================================
  count_bind_vars
  ======================================================================*/
long count_bind_vars(long shandle, GDB_CHAR *bind_vars )
{
    register long   nBind ;
    SQLDA*          bind_ptr ;
    GDB_CHAR         bind_name[256]; /* note max_bind_name_len = 30 by default and is max colname len in Oracle */

    context_num = gsi_current_context() ;

    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("COUNT_BIND_VARS"));
    }

    if (shandle == 0) return GDB_ERROR ;

    bind_ptr = sqlda_ptrs[context_num][shandle].bptr ;

    nBind = 0 ;
    while (strgettoken(bind_vars, bind_name, ',', nBind) != NULL)
        nBind++ ;

    if (nBind != bind_ptr->N)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", ENUMVAL, nBind, bind_ptr->N) ;
        return GDB_ERROR ;
    }

    return GDB_SUCCESS ;
}



/*======================================================================
  datatype_to_gdb
      - convert a DB specific datatype to a GDB datatype

      may want to return an array here ?????
  ======================================================================*/
long datatype_to_gdb(GENDA *sqlGen, int *dtArray)
{
    register int   row ;
    GDB_CHAR       *dbType ;
    double         prec, scal ;

    context_num = gsi_current_context() ;

    /* This is not really the most elegant way of dealing with this but
    our hands are tied because all DB's don't provide datatype
    info in numeric form when fetching from data dictionary. This
    should not be a problem as schema generation typically is not a
    time critical operation - i.e. it's slow but it works. */

    for (row=0;row<sqlGen->genStat.rows_processed;row++)
    {
        dbType = sqlGen->da_col_ptr[2].val[row].gdb_str ;

        /* Check for STRINGS */
        if (!_wcsicmp(dbType, DBT_VARCHAR)  ||
            !_wcsicmp(dbType, DBT_VARCHAR2) ||
            !_wcsicmp(dbType, DBT_CHAR) ||
            !_wcsicmp(dbType, DBT_DATE) ||
            !_wcsicmp(dbType, DBT_STRING))
        {
            if (debug & DBG2)
                printf("%10s %10s Got a string - %s\n", sqlGen->da_col_ptr[0].val[row].gdb_str,
                sqlGen->da_col_ptr[1].val[row].gdb_str, dbType) ;
            dtArray[row] = GDB_STRING_TYPE ;
            continue ;
        }

        /* Check for NUMBERS */
        if (!_wcsicmp(dbType, DBT_NUMBER))
        {
            prec = sqlGen->da_col_ptr[3].val[row].gdb_dbl ;
            scal = sqlGen->da_col_ptr[4].val[row].gdb_dbl ;

            /* if scale is 0 and precision is 0 then the number could be either
            a float or int. Prec is set to 0 for some 'sql functions'. Therefore
            if prec is 0 assume a float result */

            if (scal == 0 && prec != 0)
            {
                if (debug & DBG2)
                    printf("%10s %10s Got a integer - %s\n", sqlGen->da_col_ptr[0].val[row].gdb_str,
                    sqlGen->da_col_ptr[1].val[row].gdb_str, dbType) ;
                dtArray[row] = GDB_INT_TYPE ;
            }
            else
            {
                if (debug & DBG2)
                    printf("%10s %10s Got a float - %s (%f,%f)\n", sqlGen->da_col_ptr[0].val[row].gdb_str,
                    sqlGen->da_col_ptr[1].val[row].gdb_str, dbType, prec, scal) ;
                dtArray[row] = GDB_FLOAT_TYPE ;
            }
            continue ;
        }

        if (debug & DBG3)
            printf("%10s %10s UNSUPPORTED DATA TYPE - %s (%f,%f)\n", sqlGen->da_col_ptr[0].val[row].gdb_str,
            sqlGen->da_col_ptr[1].val[row].gdb_str, dbType, prec, scal) ;
        dtArray[row] = GDB_UNSUPPORTED_TYPE ;

    } /* for */
    return 0 ;
}


/*======================================================================
  dump_descriptor
      - print the contents of the Oracle descriptor

    Arguments:
    - descr: bind or select descriptor
    - entries: number of DB columns represented by this descriptor
  ======================================================================*/
void dump_descriptor (SQLDA *descr, long entries)
{
    int   n, x ;

#ifdef XXX
    struct SQLDA
    {
        long         N;   /* Descriptor size in number of entries         */
        char       **V;   /* Addresses of data values                     */
        long        *L;   /* Length of data values                        */
        short       *T;   /* Datatypes of each column                     */
        short      **I;   /* Indicator var values                         */
        long         F;   /* Number of variables found by DESCRIBE        */
        char       **S;   /* Names of bind vars used in SQL stmt          */
        short       *M;   /* Ptr to Arr of max lengths of var. names      */
        short       *C;   /* Len of bind var names used in SQL stmt       */
        char       **X;   /* Ptr to Arr of ind. var. name pointers        */
        short       *Y;   /* Ptr to Arr of max lengths of ind. var. names */
        short       *Z;   /* Ptr to Arr of cur lengths of ind. var. names */
    } ;
#endif

    printf("\n\n========================================\n") ;
    printf("DESCRIPTOR DUMP\n") ;
    printf("========================================\n\n") ;
    
    printf("Size Max:   (N): %d\n", descr->N) ;
    printf("Size Actual:(F): %d\n\n", descr->F) ;
    
    for (n=0;n<descr->N;n++)
    {
        printf("  Entry[%d]:\n", n) ;
        printf("    Name     (S): %s\n", descr->S[n]) ;
        printf("    MaxNLen  (M): %d\n", descr->M[n]) ;
        printf("    CurNLen  (C): %d\n", descr->C[n]) ;
        printf("    Type     (T): %d\n", descr->T[n]) ;
        printf("    Val      (V):\n") ;
        
        if (descr->T[n] == ORA_VARCHAR2)
            printf("       '%s'\n", descr->V[n]) ;
        else
        {
            for (x=0;x<entries;x++)
            {
                switch (descr->T[n])
                {
                case ORA_NUMBER:
                case ORA_FLOAT:
                    printf("       %f\n", ((double *)descr->V[n])[x]) ;
                    break ;
                case ORA_INTEGER:
                    printf("       %d\n", ((long *)descr->V[n])[x]) ;
                    break ;
                }
            }
        }
        printf("    ValLen   (L): %d\n", descr->L[n]) ;
        printf("    Ind      (I): %d\n", *descr->I[n]) ;
        printf("\n") ;
    }
    
    printf("\n========================================\n") ;
}
