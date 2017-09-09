/*================================================================
 * GDB_CLIENT_INTER_SQLSVR.C  - GDB Layer-3  [source]
 *================================================================
 *
 *
 *    - LAYER-3 = gdb_client_inter_sqlsvr.c + gdb_client_sqlsvr.c
 *    - provide interface between 'common layer' and 'database
 *      specific layer'
 *================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
  
#include "gdb_globals.h"
#include "gdb_genda.h"
#include "gdb_client_sqlsvr.h"
#include "gdb_client_inter_sqlsvr.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "gsi_main.h"
#include "gdb_utils.h"
#include "gdb_common.h"

#define LAYER LAYER3

/* external functions */
extern char        sql_get_sqlda();
extern SQLRETURN   bind_parameter( );
extern long        check_sqlstate_disconnect( );

/* context-sensitive globals */
extern STATUS_STRUCT  gbl_status[MAX_GDB_CONTEXTS];
extern long           max_cursors[MAX_GDB_CONTEXTS];
extern CONTEXT_INFO   context[MAX_GDB_CONTEXTS];

/* external globals */
extern long      debug;
extern long      end_of_cursor;
extern BRIDGE_INFO   bridge_info;


/* ODBC globals */
ODBCERR          g_sqlca;
SQLDA_PTRS      *sqlda_ptrs[MAX_GDB_CONTEXTS];
long             row_count[MAX_GDB_CONTEXTS]; 
long             sqlfetch_cnt[MAX_GDB_CONTEXTS]; 
gsi_int          context_num;

enum DataTypeEnum
{
    adEmpty = 0,
    adTinyInt = 16,
    adSmallInt = 2,
    adInteger = 3,
    adBigInt = 20,
    adUnsignedTinyInt = 17,
    adUnsignedSmallInt = 18,
    adUnsignedInt = 19,
    adUnsignedBigInt = 21,
    adSingle = 4,
    adDouble = 5,
    adCurrency = 6,
    adDecimal = 14,
    adNumeric = 131,
    adBoolean = 11,
    adError = 10,
    adUserDefined = 132,
    adVariant = 12,
    adIDispatch = 9,
    adIUnknown = 13,
    adGUID = 72,
    adDate = 7,
    adDBDate = 133,
    adDBTime = 134,
    adDBTimeStamp = 135,
    adBSTR = 8,
    adChar = 129,
    adVarChar = 200,
    adLongVarChar = 201,
    adWChar = 130,
    adVarWChar = 202,
    adLongVarWChar = 203,
    adBinary = 128,
    adVarBinary = 204,
    adLongVarBinary = 205,
    adChapter = 136,
    adFileTime = 64,
    adPropVariant = 138,
    adVarNumeric = 139,
    adArray = 8192
};


/*======================================================================
  get_genda_data
    - load SQLDA(database) data into GENDA(bridge)

    Arguments:
    - sqlGen: GENDA structure receiving the database data
  ======================================================================*/

long get_genda_data( sqlGen )
    GENDA     *sqlGen;
{
    gSQLDA       *select_ptr;

    long          col;
    long          null_len;
    long          row;
    long          in_row;
    long          start_row;
    long          last_row;
    long          tlen;
    wchar_t         *temp_str;
    wchar_t        **data_ptr;
    SQLUINTEGER  *start_pos;
	char Chardata[100] = {'\0'};
	int dataLen = 0;
    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("GET_GENDA_DATA"));

    select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr;
    if (select_ptr[0].ncols < 1) return( GDB_ERROR );

    null_len = wcslen(context[context_num].null_string);
    
    /*
    ** This next if statement takes care of the case where the last 
    ** sql_fetch returned EOCURSOR, and the prior fetch returned 1 or
    ** more rows, but not an entire genda full (nrows) of rows.
    ** In this situation we basically want to ignore the sql_fetch.
    */
    if ( sqlfetch_cnt[context_num] > 1 ) {
        if ( (sqlGen->genStat.status == EOCURSOR_CD) &&
             (sqlGen->more_rows >= 1) &&
             (sqlGen->more_rows < sqlGen->nrows) )
        {
            return( GDB_SUCCESS );
        }
        start_row = 0;
        /* determine the number of rows in this batch */
        last_row = sqlGen->genStat.rows_processed % sqlGen->nrows;
        /* if # rows fetched == genda size (nrows) */
        if ( (last_row == 0 && sqlGen->genStat.rows_processed > 0) && 
             (sqlGen->genStat.status != EOCURSOR_CD) )
            last_row = sqlGen->genStat.rows_processed;
        /* if sql_function then only process the 1st row (batch not applicable) */
        if ( (sqlGen->nrows == 1) && (sqlGen->genStat.rows_processed > 0) &&
             (sqlGen->genStat.status == EOCURSOR_CD) )
            last_row = sqlGen->nrows;
    }
    else {
        start_row = sqlGen->more_rows;
        last_row = sqlGen->more_rows;
    }
	/*
    ** This next if statement takes care of the case where the last 
    ** sql_fetch returned empty fetch and the prior fetch returned 1 or
    ** more rows but it has not been processed yet.
    ** In this situation we basically want to ignore the sql_fetch.
    */
    if ( (sqlfetch_cnt[context_num] == 0) &&
             (sqlGen->more_rows >= 1) &&
             (sqlGen->more_rows < sqlGen->nrows) )
        {
            return( GDB_SUCCESS );
        }
    /* Initialize array keeping track of where to get the next string */
    data_ptr = (wchar_t **)calloc(select_ptr[0].ncols, sizeof(wchar_t *) );
    start_pos = (int *)calloc(select_ptr[0].ncols, sizeof(int) );
    for ( col=0; col<select_ptr[0].ncols; col++ ) {
        data_ptr[col] = select_ptr[col].data;
        start_pos[col] = 0;
    }

    for (row=start_row, in_row=0; row<last_row+1; row++, in_row++) /* The +1 is for EOCURSOR */   
    {    
        for(col=0;col<select_ptr[0].ncols;col++)
        {
            /* insert gSQLDA into GENDA */
            switch (select_ptr[col].datatype)
            {
				
				case adBSTR:
              	case adVarChar:
				case adChar:            
				case adDate:
				case adDBDate:
				case adDBTime:
				case adGUID:
				case adDBTimeStamp:
                    sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
                    if ((sqlGen->da_col_ptr[col].val[row].gdb_str = 
                         (wchar_t *)calloc(select_ptr[col].datalen+1,sizeof(wchar_t))) == (wchar_t *)NULL) {
                        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc gdb_str buffers"));
                        iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE, "%d", EINSMEM);
                        free( data_ptr );                        
                        free( start_pos );                        
                        return ( GDB_ERROR );
                    }
 
                    wcsncpy( sqlGen->da_col_ptr[col].val[row].gdb_str,
                             &data_ptr[col][start_pos[col]],
                             select_ptr[col].datalen );
                    sqlGen->da_col_ptr[col].val[row].gdb_str[select_ptr[col].datalen] = (wchar_t)NULL;
					
                    start_pos[col] += select_ptr[col].datalen+1;
                
                    if ( ( (select_ptr[col].ind[in_row]== SQL_NULL_DATA) &&
                           (in_row < last_row) ) ||
                         (sqlGen->genStat.code == end_of_cursor) ) {
                        if ((sqlGen->da_col_ptr[col].val[row].gdb_str = (wchar_t *)realloc(sqlGen->da_col_ptr[col].val[row].gdb_str,
                            (null_len+1)*sizeof(wchar_t))) == (wchar_t *)NULL) {
                            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINMEMR);
                            free( data_ptr );                        
                            free( start_pos );                        
                            return ( GDB_ERROR );
                        }
                        wcscpy(sqlGen->da_col_ptr[col].val[row].gdb_str,context[context_num].null_string);
                    }
                    sqlGen->da_col_ptr[col].ind[row] = select_ptr[col].ind[row];
                    break;

                case adUnsignedTinyInt:
				case adInteger:
				case adSmallInt:
				case adTinyInt:
				case adBoolean: //Boolean types expected than G2 Server support integer to bool types convertion
                    sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE;

                    if ( (select_ptr[col].ind[in_row] == SQL_NULL_DATA) ||
                         (sqlGen->genStat.code == end_of_cursor) )
                        sqlGen->da_col_ptr[col].val[row].gdb_long = context[context_num].null_number;
                    else
                        sqlGen->da_col_ptr[col].val[row].gdb_long = *((long *)data_ptr[col]);

                    sqlGen->da_col_ptr[col].ind[row] = select_ptr[col].ind[row];
                    ((long *)data_ptr[col])++;

                break; 
				case adBigInt:
				case adUnsignedBigInt:
				case adUnsignedInt:
                    sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE;

                    if ( (select_ptr[col].ind[in_row] == SQL_NULL_DATA) ||
                         (sqlGen->genStat.code == end_of_cursor) )
                        sqlGen->da_col_ptr[col].val[row].gdb_long = context[context_num].null_number;
                    else
                        sqlGen->da_col_ptr[col].val[row].gdb_short = *((int *)data_ptr[col]);

                    sqlGen->da_col_ptr[col].ind[row] = select_ptr[col].ind[row];
                    ((int *)data_ptr[col])++;

                break;
                
               case adSingle :
                    sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE;
                    
                    if ( (select_ptr[col].ind[in_row] == SQL_NULL_DATA) ||
                         (sqlGen->genStat.code == end_of_cursor) )
                        sqlGen->da_col_ptr[col].val[row].gdb_dbl = context[context_num].null_number;
                    else
                        sqlGen->da_col_ptr[col].val[row].gdb_float = *((float *)data_ptr[col]);

                    sqlGen->da_col_ptr[col].ind[row] = select_ptr[col].ind[row];
                    ((float *)data_ptr[col])++;

                break;

				case adDouble:
                    sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE;
                    if ( (select_ptr[col].ind[in_row] == SQL_NULL_DATA) ||
                         (sqlGen->genStat.code == end_of_cursor) )
                        sqlGen->da_col_ptr[col].val[row].gdb_dbl = context[context_num].null_number;
                    else
                        sqlGen->da_col_ptr[col].val[row].gdb_dbl = *((double *)data_ptr[col]);

                    sqlGen->da_col_ptr[col].ind[row] = select_ptr[col].ind[row];
                    ((double *)data_ptr[col])++;

                break;
				case adWChar:
				case adVarWChar:
				case adLongVarWChar:
				case adLongVarChar:
				case adBinary:
				case adVarBinary:
				case adLongVarBinary:
                    sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
                    if ((sqlGen->da_col_ptr[col].val[row].gdb_str = 
                         (wchar_t *)calloc(select_ptr[col].datalen+1,sizeof(wchar_t))) == (wchar_t *)NULL) {
                        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc gdb_str buffers"));
                        iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE, "%d", EINSMEM);
                        free( data_ptr );                        
                        free( start_pos );                        
                        return ( GDB_ERROR );
                    }
 
                    wcsncpy( sqlGen->da_col_ptr[col].val[row].gdb_str,
                             &data_ptr[col][start_pos[col]],
                             select_ptr[col].datalen );
                    sqlGen->da_col_ptr[col].val[row].gdb_str[select_ptr[col].datalen] = (wchar_t)NULL;

                    start_pos[col] += select_ptr[col].datalen+1;
                
                    if ( ( (select_ptr[col].ind[in_row]== SQL_NULL_DATA) &&
                           (in_row < last_row) ) ||
                         (sqlGen->genStat.code == end_of_cursor) ) {
                        if ((sqlGen->da_col_ptr[col].val[row].gdb_str = (wchar_t *)realloc(sqlGen->da_col_ptr[col].val[row].gdb_str,
                            (null_len+1)*sizeof(wchar_t))) == (wchar_t *)NULL) {
                            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINMEMR);
                            free( data_ptr );                        
                            free( start_pos );                        
                            return ( GDB_ERROR );
                        }
                        wcscpy(sqlGen->da_col_ptr[col].val[row].gdb_str,context[context_num].null_string);
                    }
                    sqlGen->da_col_ptr[col].ind[row] = select_ptr[col].ind[row];
                    break;
				break;
				case adVarNumeric:
				case adDecimal:
				case adNumeric:								
				case adCurrency:
                    /* Field encompasses sign, data, and null (i.e., length = precision + 2) */
                    /* --------------------------------------------------------------------- */
                    tlen = select_ptr[col].datalen + select_ptr[col].decdigs + 2;

                    if ((temp_str = (wchar_t *)calloc(tlen,sizeof(wchar_t))) == (wchar_t *)NULL) {
                        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc gdb_str buffers"));
                        iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE, "%d", EINSMEM);
                        free( data_ptr );                        
                        free( start_pos );                        
                        return ( GDB_ERROR );
                    }
                    wcscpy( temp_str, &data_ptr[col][start_pos[col]] );
                    start_pos[col] += tlen;
                    
                    if ( (select_ptr[col].ind[in_row]== SQL_NULL_DATA) ||
                         (sqlGen->genStat.code == end_of_cursor) ) {
                        sqlGen->da_col_ptr[col].val[row].gdb_dbl = context[context_num].null_number;
                    }
                    else {

                        /* integer if scale = 0 and precision <= 8, i.e., if tlen <= 10 (tlen < 11) */
                        /* ------------------------------------------------------------------------ */
                        if ( select_ptr[col].decdigs == 0 && tlen < 11 ) {
                            sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE;
                            sqlGen->da_col_ptr[col].val[row].gdb_int = _wtoi(temp_str);
                        }

                        /*    float if scale is non-zero or precision >= 9    */
                        /* -------------------------------------------------- */
                        else {
                            sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE;
							dataLen = tlen;
							WideCharToMultiByte(CP_ACP,0,temp_str,-1,Chardata,dataLen,NULL,NULL);
							Chardata[dataLen] = '\0';							
							sqlGen->da_col_ptr[col].val[row].gdb_dbl = atof(Chardata);
                        }
                    }
                    sqlGen->da_col_ptr[col].ind[row] = select_ptr[col].ind[row];
                    free( temp_str );
                    break;
                break;

        } /*switch*/ 

    } /* end for column loop */

  } /* end for row loop */

    /* set more_rows to the number fetched for this genda */
    if ( sqlfetch_cnt[context_num] > 1 ) {
        sqlGen->more_rows = last_row; 
    }
    else {
        if (sqlGen->genStat.code != end_of_cursor)
            sqlGen->more_rows++;
    }

    free( data_ptr );                        
    free( start_pos );                        
    return ( GDB_SUCCESS );
}


/*======================================================================
  alloc_sqlda_ptrs
     - Allocate an array to store SQLDA addresses.
       The array is indexed via the stmt_handle.
     - All EXEC SQL names are generated from shandle
       (e.g. if shandle=1 then stmt_id = S1)
  ======================================================================*/
long alloc_sqlda_ptrs()
{

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("ALLOC_SQLDA_PTRS"));

  /* for lack of a better place to assign the DB specific EOC code
     to the global end_of_cursor variable */
  end_of_cursor = DB_END_OF_CURSOR;

  if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
    return (GDB_SUCCESS);

  /* alloc SQLDA_PTRS array */
  if ((sqlda_ptrs[context_num] = (SQLDA_PTRS *)calloc(MAX_CURSORS+1,sizeof(SQLDA_PTRS))) 
        == (SQLDA_PTRS *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for SQLDA_PTRS"));
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
    return(GDB_ERROR);
  }

  return (GDB_SUCCESS);

}

/*======================================================================
  db_alloc_genda
    - alloc DB specific data area of GENDA
    - load init gSQLDA data into GENDA

    Arguments:
    - sqlGen: GENDA
    - max_rows: number of rows to allocate in the GENDA struct 
                Add one for EOCURSOR
  ======================================================================*/

long db_alloc_genda( sqlGen, max_rows )
    GENDA     *sqlGen;
    long       max_rows;
{

  gSQLDA   *select_ptr;
  long      col;
  long      name_len;
  short     get_fcn = FALSE;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("DB_ALLOC_GENDA"));

  select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr;

  for (col=0;col<sqlGen->ncols;col++) {
    name_len = wcslen(select_ptr[col].colname);
    if (name_len == 0) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%s", EBADCNM, GDB_UNKNOWN);
      return (GDB_ERROR);
    }
    else {
      /*
      ** if column name is UNKNOWN then check to make sure it's an SQL function.
      ** Otherwise, return an error.
      */
      if ( (! wcscmp(select_ptr[col].colname,GDB_UNKNOWN) ) && (sqlGen->nrows != 1) ) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%s", EBADCNM, select_ptr[col].colname);
        return (GDB_ERROR);
      }
    }

    /* allocate enough bytes for column name and set the column name in genda */
    if ((sqlGen->da_col_ptr[col].col_name = (wchar_t *)calloc(name_len+1,sizeof(wchar_t))) == (wchar_t *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc col_name buffer"));
      iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE, "%d", EINSMEM);
      return (GDB_ERROR);
    }
    wcscpy(sqlGen->da_col_ptr[col].col_name, upper_case(select_ptr[col].colname));
    
    /*** alloc sqlGen->nrows val & ind ptrs ***/
    if ((sqlGen->da_col_ptr[col].val = (DATA_VALUE *)calloc(max_rows+1,sizeof(DATA_VALUE))) == (DATA_VALUE *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc val ptrs"));
      iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE, "%d", EINSMEM);
      return (GDB_ERROR);
    }
    if ((sqlGen->da_col_ptr[col].ind = (long *)calloc(max_rows+1,sizeof(long))) == (long *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc ind buffers"));
      iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE, "%d", EINSMEM);
      return (GDB_ERROR);
    }   

    /** alloc max_rows val buffers **/
    switch (select_ptr[col].datatype) {
		case adVarChar:
		case adChar:            
		case adBSTR:
		case adDate:
		case adDBDate:
		case adDBTime:
		case adDBTimeStamp:
            sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
            break;  
		case adWChar:
		case adVarWChar:
		case adLongVarWChar:
			sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
            break;
        case adBigInt:
		case adUnsignedBigInt:
		case adUnsignedInt:
            sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE;
            break;

		case adInteger:
            sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE;
            break;

        case adSingle:
            sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE;
            break;
		case adDouble:
		case adDecimal:
		case adNumeric:
		case adVarNumeric:
            sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE;
            break;
    }

  } /* end for loop */
  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s%d", _T("Allocated % row(s)"), max_rows);
  return (GDB_SUCCESS);

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

long set_error (sqlGen)
    GENDA   *sqlGen;
{
  context_num = gsi_current_context();

  context[context_num].gbl_status.code   = -1;
  context[context_num].gbl_status.status = -1;  

  if (sqlGen != (GENDA *)NULL) {
    sqlGen->genStat.code = context[context_num].gbl_status.code;
    sqlGen->genStat.status = context[context_num].gbl_status.status;
  }

  return 0;

}

/*======================================================================
  get_stat
    - load genStat section of GENDA with gSQLCA
    - load gbl_status struct with gSQLCA

    Arguments:
    - sqlGen: GENDA

  REVISIONS
  ----------

  Date            Who     Version      What
  ----            ---     -------      ----
  2-Apr-1997       PH       5.2R3      Make sure error message does not
                                       overrun its buffer.
  ======================================================================*/

long get_stat( sqlGen )
    GENDA   *sqlGen;
{

  wchar_t   prefix_msg[DB_TYPE_LEN+MAX_CONTEXT_NAME_LEN+STAT_SYM_LEN+4];
  wchar_t   text_msg[MAX_ODBC_MSG_LEN+1];
  wchar_t   ss_msg[10];
  long   msg_len  = 0;
  long   warn_len = 0;
  long   prefix_len = 0;
  long   odbc_msg_len = 0;                                    
  long   syb_layer=0;
  long   prev_status;
  long   tmp;
  short  i, numerrs=0, notDSN;

  context_num = gsi_current_context();

  if (context[context_num].gbl_status.msg == (wchar_t *)NULL) {
    if ((context[context_num].gbl_status.msg = (wchar_t *)calloc(MAX_ODBC_MSG_LEN+1,sizeof(wchar_t))) == (wchar_t *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc mem for gbl_status.msg"));
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
      set_error(sqlGen);
      return (GDB_ERROR);
    }
  }

  /* initialize messages */
  text_msg[0] = 0;
  prefix_msg[0] = 0;
  context[context_num].gbl_status.code = g_sqlca.code;
  prev_status = context[context_num].gbl_status.status;

  switch ( g_sqlca.code ) {

    case ( SQL_SUCCESS ):
      context[context_num].gbl_status.status = SUCCESS_CD;
      context[context_num].gbl_status.rows_processed = row_count[context_num];
      context[context_num].gbl_status.code = g_sqlca.code;
      break;
       
    case ( SQL_SUCCESS_WITH_INFO ):
      context[context_num].gbl_status.status = WARN_CD;
      context[context_num].gbl_status.rows_processed = row_count[context_num];
      context[context_num].gbl_status.code = g_sqlca.code;
      break;

    case ( SQL_NO_DATA_FOUND ):
      context[context_num].gbl_status.status = EOCURSOR_CD;
      context[context_num].gbl_status.rows_processed = row_count[context_num];
      context[context_num].gbl_status.code = g_sqlca.code;
      break;

    case ( SQL_ERROR ):
    case ( SQL_INVALID_HANDLE ):
	case (GDB_BIND_ERROR):
      context[context_num].gbl_status.status = ERROR_CD;
      context[context_num].gbl_status.rows_processed = 0;
	  if ( ! context[context_num].gbl_status.code )
        context[context_num].gbl_status.code = ERROR_CD;
      else
        context[context_num].gbl_status.code = abs(context[context_num].gbl_status.code) * -1; 
      break;

    default:
      break;
  }

  prefix_len = load_msg(context[context_num].gbl_status.status,0,&tmp,prefix_msg,FALSE);
   
  /* set the message length and the text_msg if there's an error */
  if (g_sqlca.code != 0) {
    msg_len = 0;
    /* loop to add each ODBC error message to the text message */
    for (i = 0; (g_sqlca.state_array[i].native_errlen != 0); i++ ) {
      
      /* 
	  ** Set the length of the odbc message to the lesser of the length
      ** of the message and the number of chars left in the text message buffer
      ** so we don't write past the end fo the text message buffer.
      */
        notDSN = wcscmp(L"<dsn>",g_sqlca.state_array[i].sqlstate) ? 1 : 0 ;
        odbc_msg_len = ( MAX_ODBC_MSG_LEN -msg_len -notDSN * SS_LEN -prefix_len -1 < g_sqlca.state_array[i].native_errlen) ?
	                        MAX_ODBC_MSG_LEN -msg_len -notDSN * SS_LEN -prefix_len -1 :
                            g_sqlca.state_array[i].native_errlen;

      /* copy odbc message to the text message */
	  if ( odbc_msg_len > 0 )
      {
        numerrs++;
        if (!wcscmp(L"<dsn>",g_sqlca.state_array[i].sqlstate))
            _snwprintf( ss_msg, SS_LEN, L"%s", !i?"":"; " );
        else
            _snwprintf( ss_msg, SS_LEN, L"%sss=%5s ", !i?"":"; ", g_sqlca.state_array[i].sqlstate );
        if (i==0)
          wcsncpy( text_msg, ss_msg, SS_LEN+1 );
        else
          wcsncat( text_msg, ss_msg, SS_LEN+3 );

        wcsncat( text_msg, g_sqlca.state_array[i].native_errmsg, odbc_msg_len );
        msg_len += notDSN*SS_LEN + odbc_msg_len + (i?2:0);
        text_msg[msg_len] = 0;
      }
      else {
        /* stop when the length of errmsg is 0 */
        break;
      }
	  if ( g_sqlca.state_array[0].native_errcode ) 
        context[context_num].gbl_status.code = abs(g_sqlca.state_array[0].native_errcode) * -1; 
    
	} /* end for loop */
    
    text_msg[msg_len] = 0;

    if (!text_msg[0]) 
      msg_len = 0;
  }
  /*
  ** This next if statement is a Kludge!
  ** Change the gbl_status msg to the text_msg just generated if one
  ** or more of the following are true:	(otherwise leave it alone)
  ** 1) there are ODBC error messages
  ** 2) the current status indicates success
  ** 3) the previous status was success
  */
  if ( (msg_len) ||
       (context[context_num].gbl_status.status >= SUCCESS_CD) ||
       (prev_status >= SUCCESS_CD) ) {
    context[context_num].gbl_status.msg[0] = 0;
    /* concat prefix and message body */
    _snwprintf(context[context_num].gbl_status.msg, MAX_ODBC_MSG_LEN, L"%s%s", prefix_msg, text_msg);
  }

  /* load the GENDA struct */

  if (sqlGen != (GENDA *)NULL) {
    msg_len = wcslen(context[context_num].gbl_status.msg);

    if ( sqlGen->more_rows >= sqlGen->nrows )
      sqlGen->more_rows = 0;

    if (sqlGen->genStat.msg == (wchar_t *)NULL) {
      if ((sqlGen->genStat.msg =
          (wchar_t *)calloc(msg_len+1,sizeof(wchar_t))) == (wchar_t *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT alloc mem for genStat.msg"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
        set_error(sqlGen);
        return (GDB_ERROR);
      }
    }
    else {
      if ((sqlGen->genStat.msg = (wchar_t *)
           realloc(sqlGen->genStat.msg,
          (msg_len+1)*sizeof(wchar_t))) == (wchar_t *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT realloc mem for genStat.msg"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINMEMR);
        set_error(sqlGen);
        return (GDB_ERROR);
      }
    }
	if( g_sqlca.code == GDB_BIND_ERROR )
	{
		msg_len = wcslen(GDB_BIND_ERROR_MSG) + 1;
		sqlGen->genStat.msg = (wchar_t *)realloc(sqlGen->genStat.msg,(msg_len+1)*sizeof(wchar_t));
		wcsncpy(sqlGen->genStat.msg,GDB_BIND_ERROR_MSG, msg_len);
		iomsg(DBG3,LAYER,TRUE,FALSE,NULL,FALSE, "%s", sqlGen->genStat.msg);
	}
	else
		wcsncpy(sqlGen->genStat.msg, context[context_num].gbl_status.msg, msg_len);
    sqlGen->genStat.msg[msg_len] = 0;
    sqlGen->genStat.code = context[context_num].gbl_status.code;
    sqlGen->genStat.rows_processed = context[context_num].gbl_status.rows_processed;
    sqlGen->genStat.status = context[context_num].gbl_status.status;
  }

  /* Check for a disconnected state and reconnect if necessary */
  if ( (check_sqlstate_disconnect() ) ||
       (abs(context[context_num].gbl_status.code) == (GDB_MSG_BASE + ENODBCT)) ) {
    context[context_num].connected_to_db = FALSE;
    context[context_num].gbl_status.status = NOCONNECT_CD;
    process_reconnect();
  }

  /*** reset certain g_sqlca fields to NULL ***/

  g_sqlca.code = SQL_SUCCESS;
  g_sqlca.state_array[0].sqlstate[0] = '\0';
  g_sqlca.state_array[0].native_errmsg[0] = '\0';  
  g_sqlca.state_array[0].native_errlen = 0;
  g_sqlca.state_array[0].native_errcode = 0;

  if ((debug & DBG5) && context[context_num].gbl_status.status != SUCCESS_CD) { 
    printf("\nSQL Message Structure\n");
    printf("ver   : %s\n",bridge_info.bridge_version );
    printf("code  : %d\n",context[context_num].gbl_status.code);
    wprintf(_T("msg   : %s\n"),context[context_num].gbl_status.msg);
    printf("nrows : %d\n",context[context_num].gbl_status.rows_processed);
    printf("stat  : %d\n",context[context_num].gbl_status.status);
  }

  if ( context[context_num].gbl_status.status != SUCCESS_CD && 
       context[context_num].gbl_status.status != EOCURSOR_CD ) 
    return (GDB_ERROR);
  return (GDB_SUCCESS);

}


/*======================================================================
  load_bind_vars
  ======================================================================*/
long load_bind_vars( shandle, bind_vars, index, datatype, array_size )
    long     shandle;
    wchar_t    **bind_vars;
    long     index;
    long     datatype;
    long     array_size;
{
    gSQLDA     *bind_ptr;
    long       *ind_array, len, len2, lX;
    short       elmntsize;
    wchar_t       *tptr;
	SQLRETURN   rc;

    context_num = gsi_current_context();

    if (shandle == 0) return (GDB_ERROR);

    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

    if (bind_ptr == (gSQLDA *)NULL) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE, "%d", ENOTINI);
        return (GDB_ERROR);
    }

    /*
    ** Compare the datatype expected by the database to the datatype in 
    ** the array or list sent from G2.  If the datatypes are incompatible
    ** return to the caller with an error. Free the data area of the 
    ** gSQLDA if was allocated previously via a "set" operation.
    */
    switch ( bind_ptr[index].datatype )
    {
        case SQL_CHAR :
        case SQL_VARCHAR :
        case SQL_LONGVARCHAR :
        case SQL_DATETIME :
        case SQL_TIME :
        case SQL_TYPE_DATE :
        case SQL_TYPE_TIME :
        case SQL_TYPE_TIMESTAMP :
        case SQL_GUID:
            if ( datatype != GDB_STRING_TYPE ) {
                iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE, "%d%d", EINCDTP,index+1);
	            return( GDB_ERROR );
	        }
  	    break;

        case SQL_INTEGER :
        case SQL_SMALLINT :
        case SQL_TINYINT :
        case SQL_BIT :
            if ( datatype != GDB_INT_TYPE ) {
                iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE, "%d%d", EINCDTP, index+1);
                return( GDB_ERROR );
            }
  	    break;

        case SQL_DOUBLE :
        case SQL_REAL :
        case SQL_FLOAT :
        case SQL_NUMERIC :
        case SQL_DECIMAL :
            if ( datatype != GDB_FLOAT_TYPE ) {
                iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE, "%d%d", EINCDTP, index+1);
                return( GDB_ERROR );
            }
  	    break;
    }

    /* free the bind data area of the gSQLDA */
    if ( bind_ptr[index].bdata ) {
        free( bind_ptr[index].bdata );
        bind_ptr[index].bdata = NULL;
    }
    /* free the NULL indicator area of the gSQLDA */
    if ( bind_ptr[index].ind ) {
        free( bind_ptr[index].ind );
        bind_ptr[index].ind = NULL;
    }

    /* allocate the indicator array for NULLS */
    if ((ind_array = (long *)calloc(array_size,sizeof(long))) == (long *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc indicator array"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
        return (GDB_ERROR);
    }

    switch(datatype) {

        case GDB_INT_TYPE:
            elmntsize = (long)sizeof(long);
            if ((bind_ptr[index].bdata = 
                (wchar_t *)calloc(array_size+1, elmntsize)) == (wchar_t *)NULL) {
                iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc data array"));
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
                return (GDB_ERROR);
            }

            if ((bind_ptr[index].ind = (long *)calloc(array_size+1,sizeof(long))) == (long *)NULL) {
                iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc ind array"));
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
                free((long *)ind_array);
                return (GDB_ERROR);
            }     
            memcpy( bind_ptr[index].bdata, bind_vars, array_size*elmntsize );

            /* check for null values */
            /* --------------------- */
            for (lX=0;lX<array_size;lX++)
            {
                if ((context[context_num].set_null_options & 0x1) && 
                        (long)bind_vars[lX] == context[context_num].set_null_number ) 
                    ind_array[lX] = SQL_NULL_DATA;
            }
            memcpy(bind_ptr[index].ind, ind_array, array_size*sizeof(long));
            break;
        
        case GDB_FLOAT_TYPE:
            elmntsize = (long)sizeof(double);
            if ((bind_ptr[index].bdata = 
                (wchar_t *)calloc(array_size+1, elmntsize)) == (wchar_t *)NULL) {
                iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc data array"));
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
                free((long *)ind_array);
                return (GDB_ERROR);
            }

            if ((bind_ptr[index].ind = (long *)calloc(array_size+1,sizeof(long))) == (long *)NULL) {
                iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc ind array"));
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
                free((long *)ind_array);
                return (GDB_ERROR);
            }     
            memcpy( bind_ptr[index].bdata, bind_vars, array_size*elmntsize );

            /* check for null values */
            /* --------------------- */
            for (lX=0;lX<array_size;lX++)
            {
                if ((context[context_num].set_null_options & 0x1) && 
                        ((double *)bind_ptr[index].bdata)[lX] == (double)(context[context_num].set_null_number))
                    ind_array[lX] = SQL_NULL_DATA ;
            } 
            memcpy(bind_ptr[index].ind,ind_array,array_size*sizeof(long));
            break;

        case GDB_STRING_TYPE:
            elmntsize = (long)sizeof(wchar_t);
            /* calc the total number of chars in the bind_var array */
            len = (bind_ptr[index].colsize+1) * array_size;

            if ((bind_ptr[index].bdata = 
                (wchar_t *)calloc(len, elmntsize)) == (wchar_t *)NULL) {
                iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc data array"));
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
                free((long *)ind_array);
                return (GDB_ERROR);
            }
            if ((bind_ptr[index].ind = (long *)calloc(array_size+1,sizeof(long))) == (long *)NULL) {
                iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc ind array"));
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
                free((long *)ind_array);
                return (GDB_ERROR);
            }     
	  
            tptr = bind_ptr[index].bdata;
            for (lX=0; lX<array_size; lX++) {
                /*
                ** check to make sure the length of the bind value is not
                ** greater than the length of the database column
                */
                len2 = wcslen(bind_vars[lX]);
                if ( len2 > bind_ptr[index].colsize ) {
                    iomsg( DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%d%d",
                           EBVEXLN, bind_vars[lX], len2, bind_ptr[index].colsize );
                    free((long *)ind_array);
                    return( GDB_ERROR );
                }

                wcscpy( tptr, bind_vars[lX] );
                tptr += (bind_ptr[index].colsize + 1);

                /* check for nulls */
                /* --------------- */
                ind_array[lX] = SQL_NTS;
                if ( (context[context_num].set_null_options & 0x2) && 
                        !_wcsicmp(bind_vars[lX], context[context_num].set_null_string) ) 
                    ind_array[lX] = SQL_NULL_DATA;
                else if ((context[context_num].set_null_options & 0x4) && !wcscmp(bind_vars[lX], _T("NULL") )) 
                    ind_array[lX] = SQL_NULL_DATA;
            }
            memcpy(bind_ptr[index].ind, ind_array, array_size*sizeof(long));
            break;

    } /* end switch */
    free ((long *)ind_array);

    /* Bind the parameter */
    rc = bind_parameter( bind_ptr, datatype, index, context_num, shandle );

    return( rc );
}

/*======================================================================
  count_bind_vars
  ======================================================================*/
long count_bind_vars( shandle, bind_vars )
    long     shandle;
    wchar_t    *bind_vars;
{
    register int nBind;
    gSQLDA  *bind_ptr;
    wchar_t  bind_name[MAX_VNAME_LEN];

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("COUNT_BIND_VARS"));

    if (shandle == 0) return (GDB_ERROR);

    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

    nBind = 0;
    while (strgettoken(bind_vars,bind_name,',',nBind) != NULL)
        nBind++;

    if (nBind != bind_ptr[0].ncols) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%d%d", ENUMVAL, nBind, bind_ptr[0].ncols);
        return (GDB_ERROR);
    }

    return (GDB_SUCCESS);
}
