/*================================================================
 * GDB_CLIENT_INTER_INF.C  - GDB Layer-3 (Informix-7.10)  [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-3 = gdb_client_inter_inf.c + gdb_client_inf.ec
 *    - provide interface between 'common layer' and 'database
 *      specific layer'
 *================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 
#include "gdb_globals.h"
#include "gdb_genda.h"
#include "gdb_client_inf.h"
#include "gdb_client_inter_inf.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "gsi_main.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#include "sqlca.h"

#define LAYER LAYER3

extern long   sql_get_sqlda();
extern int    rgetlmsg();   /* Informix funct */

extern CONTEXT_INFO  context[MAX_GDB_CONTEXTS];

/* extern globals */
extern long   debug;
extern long   end_of_cursor;
extern long   short_messages;
extern long   max_col_array_size;  
extern BRIDGE_INFO   bridge_info;

SQLDA_PTRS   *sqlda_ptrs[MAX_GDB_CONTEXTS];
gSQLCA       *gsqlca; 
long          row_count[MAX_GDB_CONTEXTS]; /* because INF doesn't report row #'s */

gsi_int       context_num;
/*======================================================================
  get_genda_data
    - load SQLDA(database) data into GENDA(bridge)

    Arguments:
    - sqlGen: GENDA structure receiving the database data
  ======================================================================*/

long get_genda_data( sqlGen )
    GENDA     *sqlGen;
{
  TRANS_VALUE tunion;
  gSQLDA   *select_ptr;
  register long row;
  long		start_row;
  long      rows_fetched;
  long      col;
  long      ind;
  long      datatype;
  long      datalen;
  long      datascale;
  long      null_len;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","GET_GENDA_DATA");

  /* using ncols from select_ptr[0] because ncols is redundant across all 
     columns. This is just easier than accessing sqlGen for the ncols */

  select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr;
  if (select_ptr[0].ncols < 1) return(GDB_ERROR);

  null_len = strlen(context[context_num].null_string); 
  
/* Force array fetching OFF for now */
  context[context_num].array_fetch =  FALSE;
  if (context[context_num].array_fetch) {
    start_row = 0;
    /* determine the number of rows in THIS batch */
    rows_fetched = sqlGen->genStat.rows_processed % sqlGen->nrows;
    /* if # rows fetched == genda size (nrows) */
    if (rows_fetched == 0 && sqlGen->genStat.rows_processed > 0 && 
        sqlGen->genStat.status != EOCURSOR_CD)
      rows_fetched = sqlGen->nrows;
    /* if sql_function then only process the 1st row (batch not applicable) */
    if (sqlGen->nrows == 1 && sqlGen->genStat.rows_processed > 0 &&
        sqlGen->genStat.status == EOCURSOR_CD)
      rows_fetched = sqlGen->nrows;       
  }
  else {
    start_row = sqlGen->more_rows;
    rows_fetched = sqlGen->more_rows;
	/* if sql_function then assign rows_fetch to 1. This chang regarding bridge */
	/* crashed when attempting to select expression during free extral row */
	if (sqlGen->nrows == 1 && sqlGen->genStat.rows_processed)
	  rows_fetched = sqlGen->nrows;	  
  }

  
  for (row=start_row;row<rows_fetched+1;row++) /* The +1 is for EOCURSOR */   
  {
  
	for(col=0;col<select_ptr[0].ncols;col++)
	{
	  datatype  = select_ptr[col].datatype;
      datalen   = select_ptr[col].datalen;
	  datascale = select_ptr[col].scale;
      
	  /* insert gSQLDA into GENDA */
      switch (datatype)
      {
      case INF_CHAR:
      case INF_DATE:
        sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
		
		if ( sqlGen->genStat.code == end_of_cursor ) {
          /* Set the string value to null */
          if ((sqlGen->da_col_ptr[col].val[row].gdb_str = 
			  (char *) calloc(null_len+1,sizeof(char))) == (char *)NULL) {
            iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for gdb_str");
            return (GDB_ERROR);
		  }
          strcpy(sqlGen->da_col_ptr[col].val[row].gdb_str,context[context_num].null_string);
          sqlGen->da_col_ptr[col].ind[row] = INF_NULL_IND;
		}

        else {
			
		  if ((sqlGen->da_col_ptr[col].val[row].gdb_str = 
              (char *)calloc(datalen+1,sizeof(char))) == (char *)NULL) {  
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc gdb_str buffers");
            iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE,"%d",EINSMEM);
            return (GDB_ERROR);
		  }

          tunion.t_str = sqlGen->da_col_ptr[col].val[row].gdb_str;
          sql_get_sqlda( &tunion,
                         &ind,
                         col,
                         sqlGen->stmt_handle,
                         datatype );
          if ( ind < 0 ) {
            if ((sqlGen->da_col_ptr[col].val[row].gdb_str = (char *)realloc(sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_str,
                (null_len+1)*sizeof(char))) == (char *)NULL) {
              iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not realloc mem for gdb_str");
              return (GDB_ERROR);
            }
            strcpy(sqlGen->da_col_ptr[col].val[row].gdb_str,context[context_num].null_string);
          }

          sqlGen->da_col_ptr[col].ind[row] = ind;
        }
        break;

      case INF_SMINT:
        sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE;
        
		if ( sqlGen->genStat.code == end_of_cursor ) {
          /* Set value to null */
          sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number;
          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = INF_NULL_IND;
        }
        else {
          sql_get_sqlda( &tunion,
                         &ind,
                         col,
                         sqlGen->stmt_handle,
                         datatype );
          if ( ind < 0 )
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number;
          else
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_short = tunion.t_short;

          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind;
        }
        break; 

      case INF_INTEGER:
      case INF_SERIAL:
        sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE;

        if ( sqlGen->genStat.code == end_of_cursor ) {
          /* Set value to null */
          sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number;
          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = INF_NULL_IND;
        }
        else {
		  sql_get_sqlda( &tunion,
                         &ind,
                         col,
                         sqlGen->stmt_handle,
                         datatype );
          if ( ind < 0 )
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number;
          else
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = tunion.t_long;

          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind;
        }
        break; 

      case INF_SMFLOAT:
        sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE;
        
		if ( sqlGen->genStat.code == end_of_cursor ) {
          /* Set value to null */
          sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number;
          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = INF_NULL_IND;
        }
        else {
          sql_get_sqlda( &tunion,
                         &ind,
                         col,
                         sqlGen->stmt_handle,
                         datatype );
          if ( ind < 0 )
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_float = (float)context[context_num].null_number;
          else
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_float = tunion.t_float;

          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind;
        }
        break;   

      case INF_FLOAT:
      case INF_DECIMAL:
      case INF_MONEY:
        sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE;

        if ( sqlGen->genStat.code == end_of_cursor ) {
          /* Set value to null */
          sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number;
          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = INF_NULL_IND;
        }
        else {
          sql_get_sqlda( &tunion,
                         &ind,
                         col,
                         sqlGen->stmt_handle,
                         datatype );
          if ( ind < 0 )
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = context[context_num].null_number;
          else
            sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = tunion.t_dbl;

          sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = ind;
        }
        break;   

      default:
        /* sqlGen->da_col_ptr[col].data_type = GDB_UNSUPPORTED_TYPE;*/
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,datatype,col+1);
        return (GDB_ERROR);
		break;


    } /*switch*/ 
  }

}/* end loop for rows */

  if (sqlGen->genStat.code != end_of_cursor)
    sqlGen->more_rows++;
    
  return (GDB_SUCCESS);
}


/*======================================================================
  alloc_sqlda_ptrs
     - Allocate an array to store SQLDA addresses.
       The array is indexed via the stmt_handle.
  ======================================================================*/

long alloc_sqlda_ptrs()
{

  context_num = gsi_current_context();

  if (debug & DBG1) {
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","ALLOC_SQLDA_PTRS");
  }

  /* for lack of a better place to assign the DB specific EOC code
     to the global end_of_cursor variable */
  end_of_cursor = DB_END_OF_CURSOR;

  /*** alloc SQLDA_PTRS array ***/
  if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
    return (GDB_SUCCESS);

  /* changed from max_cursors[context_  num] */
  if ((sqlda_ptrs[context_num] = (SQLDA_PTRS *)calloc(MAX_CURSORS+1,sizeof(SQLDA_PTRS))) == (SQLDA_PTRS *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDA_PTRS");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
    return(GDB_ERROR);
  }

  return (GDB_SUCCESS);
}


/*======================================================================
  db_alloc_genda
    - alloc DB specific data area of GENDA
    - load init SQLDA data into GENDA

    Arguments:
    - sqlGen: GENDA
    - max_rows: number of rows to allocate in the GENDA struct
  ======================================================================*/

long db_alloc_genda( sqlGen, max_rows )
    GENDA  *sqlGen;
    long    max_rows;
{
  gSQLDA   *select_ptr;
  long      col;
  long      name_len;

  context_num = gsi_current_context();

  if (debug & DBG1) {
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","DB_ALLOC_GENDA");
  }

  select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr;

  for (col=0;col<sqlGen->ncols;col++) {
    name_len = strlen(select_ptr[col].colname);
    if (name_len == 0) {
	  iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%s",EBADCNM,GDB_UNKNOWN);
      return (GDB_ERROR);
    }
    else { 
      /*
      ** The following code takes care of the case where a select statement
      ** contains an Informix function such as "SELECT CURRENT FROM ..."
      ** GET DESCRIPTOR returns '(EXPRESSION)' for the column name and
      ** it is not handled correctly in check_column_names.
      ** To take care of it, we will set the column name to "UNKNOWN"
      */ 
      if ( (name_len == 0) && (strchr(select_ptr[col].colname,'(') != NULL) ) {
        strcpy( select_ptr[col].colname, "UNKNOWN");
        name_len = strlen( select_ptr[col].colname);
	  
      }
	  if ( (! strcmp(select_ptr[col].colname,GDB_UNKNOWN) ) && (sqlGen->nrows != 1) ) {
		iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%s",EBADCNM,select_ptr[col].colname);
        return (GDB_ERROR);
      }
    }

	/* Allocate enough bytes for the column name. */
    if ((sqlGen->da_col_ptr[col].col_name = (char *)calloc(name_len+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc col_name buffer");
      iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }
    strcpy(sqlGen->da_col_ptr[col].col_name,upper_case(select_ptr[col].colname)); 

    /*** alloc sqlGen->nrows val & ind ptrs ***/
    if ((sqlGen->da_col_ptr[col].val = (DATA_VALUE *)calloc(max_rows+1,sizeof(DATA_VALUE))) == (DATA_VALUE *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc val ptrs");
      iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }
    if ((sqlGen->da_col_ptr[col].ind = (long *)calloc(max_rows+1,sizeof(long))) == (long *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc ind buffers");
      iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }   

    /** alloc max_rows val buffers **/
    switch (select_ptr[col].datatype) {
      case INF_CHAR :
      case INF_DATE :
      case INF_DTIME:
      case INF_STRING:
      case INF_VCHAR:
      case INF_INTERVAL :
        sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
    /* 
    ** MOVED THE ALLOCATION OF THE VALUE STRUCTURE TO GET_GENDA      
    */
        
        break;  

      case INF_SMINT :
        sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE;
        break;

      case INF_INTEGER :
      case INF_SERIAL :
        sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE;
        break;

      case INF_SMFLOAT :
        sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE;
        break;

      case INF_FLOAT :
      case INF_DECIMAL :
      case INF_MONEY :
        sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE;
        break;
    }
  }
  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d","Allocated % row(s)",max_rows);

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
    - load genStat section of GENDA with SQLCA
    - load gbl_status struct with SQLCA

    Arguments:
    - sqlGen: GENDA
  ======================================================================*/

long get_stat( sqlGen )
    GENDA  *sqlGen;
{
  char   prefix_msg[DB_TYPE_LEN+MAX_CONTEXT_NAME_LEN+STAT_SYM_LEN+4];
  char   inf_msg[STATUS_MSG_LEN+1];
  char   text_msg[STATUS_MSG_LEN+1];
  long   warn_len = 0;
  long   curr_len = 0;
  long   msg_len  = 0;
  long   tmp;

  context_num = gsi_current_context();
  
  if (gsqlca == NULL) return (GDB_ERROR);

  if (context[context_num].gbl_status.msg == (char *)NULL) {
    if ((context[context_num].gbl_status.msg = (char *)calloc(STATUS_MSG_LEN+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc mem for gbl_status.msg");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
      set_error(sqlGen);
      return (GDB_ERROR);
    }
  }

  text_msg[0] = 0;
  prefix_msg[0] = 0;

  /*** load the gbl_status struct ***/
  context[context_num].gbl_status.code = gsqlca->sqlcode; 
  if (gsqlca->sqlcode >= 0) {
    context[context_num].gbl_status.status = SUCCESS_CD;
    context[context_num].gbl_status.rows_processed = row_count[context_num];
  }
  else if (gsqlca->sqlcode < 0)
    context[context_num].gbl_status.rows_processed = 0;
  
  if (gsqlca->sqlcode > 0) context[context_num].gbl_status.status = WARN_CD;
  if (gsqlca->sqlcode < 0) context[context_num].gbl_status.status = ERROR_CD;
  if (gsqlca->sqlcode == DB_END_OF_CURSOR) 
    context[context_num].gbl_status.status = EOCURSOR_CD;

  *context[context_num].gbl_status.msg = 0;


  /* load the context info into message first */
  curr_len = load_msg(context[context_num].gbl_status.status,0,&tmp,prefix_msg,FALSE);

  if (gsqlca->sqlcode < 0) {
     
    msg_len = STATUS_MSG_LEN - curr_len - strlen(gsqlca->sqlerrm);

    if (msg_len > 0) {
      rgetlmsg(gsqlca->sqlcode,inf_msg,msg_len,&tmp);
      /* 
        check to see if there are values in sqlerrm, if so, this means
        that there is an %s in the inf_msg text. The sqlerrm values will
        then be substituted into the %s of the inf_msg using sprintf.
      */
      if (gsqlca->sqlerrm[0] != 0)
        sprintf(text_msg,inf_msg,gsqlca->sqlerrm);
      else
        strcpy(text_msg,inf_msg);
    }
   
    if (text_msg[0] == 0) 
      msg_len = 0;
    else {
      msg_len = strlen(text_msg);
      text_msg[msg_len] = 0;
    }
  }

  curr_len += msg_len;

  if (gsqlca->sqlwarn.sqlwarn0 == 'W'){/*&& (*gsqlca->sqlwarn != 0){*/ 
	/* sqlwarn1 == 'W' has two case so comment it out */
    /*if (gsqlca->sqlwarn.sqlwarn1=='W') {
      warn_len = strlen(WARN2);
      if ((curr_len + warn_len) < STATUS_MSG_LEN) {
        curr_len += warn_len;
        strcat(text_msg,WARN2);
      }
      else
        iomsg(DBG4,LAYER,TRUE,FALSE,NULL,FALSE,"%d",WWRNCAT);
    }*/   
    if (gsqlca->sqlwarn.sqlwarn4 =='W') {
      warn_len = strlen(WARN5);
      if ((curr_len + warn_len) < STATUS_MSG_LEN) {
        curr_len += warn_len;
        strcat(text_msg,WARN5);
      }
      else
        iomsg(DBG4,LAYER,TRUE,FALSE,NULL,FALSE,"%d",WWRNCAT);
    }   
    context[context_num].gbl_status.rows_processed = row_count[context_num];
  }

  /* concat prefix and message body */
  sprintf(context[context_num].gbl_status.msg,"%s%s",prefix_msg,text_msg);

  /*** load the GENDA struct ***/
  if (sqlGen != (GENDA *)NULL)
  {
    msg_len = strlen(context[context_num].gbl_status.msg);
    if (sqlGen->genStat.msg == (char *)NULL) {
      if ((sqlGen->genStat.msg =
          (char *)calloc(msg_len+1,sizeof(char))) == (char *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc mem for genStat.msg");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        set_error(sqlGen);
        return (GDB_ERROR);
      }
    }
    else {
      if (msg_len > 0) {
        if ((sqlGen->genStat.msg = (char *)
             realloc(sqlGen->genStat.msg,
            (msg_len+1)*sizeof(char))) == (char *)NULL) {
          iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT realloc mem for genStat.msg");
          iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINMEMR);
          set_error(sqlGen);
          return (GDB_ERROR);
        }
        strncpy(sqlGen->genStat.msg,context[context_num].gbl_status.msg,msg_len);
      }
    }
    sqlGen->genStat.msg[msg_len] = 0;
    sqlGen->genStat.code = context[context_num].gbl_status.code;
    sqlGen->genStat.rows_processed = context[context_num].gbl_status.rows_processed;
    sqlGen->genStat.status = context[context_num].gbl_status.status;
  }

  if (gsqlca->sqlcode == DB_NOT_CONNECTED) {
    context[context_num].gbl_status.status = NOCONNECT_CD;
    process_reconnect();
  }

  /*** reset certain SQLCA fields to NULL ***/
  gsqlca->sqlwarn.sqlwarn0 = ' ';
  gsqlca->sqlcode = 0;
  
  if ((debug & DBG5) && context[context_num].gbl_status.status != SUCCESS_CD) { 
    printf("\nSQL Message Structure\n");
    printf("ver   : %s\n",bridge_info.bridge_version );
    printf("code  : %d\n",context[context_num].gbl_status.code);
    printf("msg   : %s\n",context[context_num].gbl_status.msg);
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
    char    **bind_vars;
    long     index;
    long     datatype;
    long     array_size;
{
  gSQLDA     *bind_ptr;
  long       i,len;
  long       elmntsize;
  short      *ind_array;
 
  context_num = gsi_current_context();

  if (shandle == 0) return (GDB_ERROR);

  bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

  if (bind_ptr == (gSQLDA *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d",ENOTINI);
    return (GDB_ERROR);
  }

  /*
  ** Eliminated the code to free up the bind_ptr data area because
  ** its already done at this point.
  */

  /* allocate the indicator array for NULLS */
  if ((ind_array = (short *)calloc(array_size,sizeof(short))) == (short *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc indicator array");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
   
  switch(datatype)
  {
    case GDB_INT_TYPE:
      bind_ptr[index].datatype = GDB_INT_TYPE;
      elmntsize = (long)sizeof(long);
      if ((bind_ptr[index].data = (char **)calloc(array_size,elmntsize)) == (char **)NULL)
      {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc data array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        return (GDB_ERROR);
      }
      if ((bind_ptr[index].ind = (short *)calloc(array_size,sizeof(short))) == (short *)NULL)
      {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc ind array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        free((short *)ind_array);
        return (GDB_ERROR);
      } 
     
      memcpy( bind_ptr[index].data, bind_vars, array_size*elmntsize );

      /* check for null values */
      /* --------------------- */
      for (i=0;i<array_size;i++)
      {
        if ((context[context_num].set_null_options & 0x1) && (long *)(bind_ptr[index].data)[i] == context[context_num].set_null_number))
          ind_array[i] = -1;
      }
  
      memcpy(bind_ptr[index].ind,ind_array,array_size*sizeof(short));
      break;

    case GDB_FLOAT_TYPE:
      bind_ptr[index].datatype = GDB_FLOAT_TYPE;
	  elmntsize = (long)sizeof(double);
      if ((bind_ptr[index].data = (char **)calloc(array_size,elmntsize)) == (char **)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc data array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        return (GDB_ERROR);
      }
      if ((bind_ptr[index].ind = (short *)calloc(array_size,sizeof(short))) == (short *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc ind array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        free((short *)ind_array);
        return (GDB_ERROR);
      }     
	  memcpy( bind_ptr[index].data, bind_vars, array_size*elmntsize );

      /* check for null values */
      /* --------------------- */
      for (i=0;i<array_size;i++)
      {
        if ((context[context_num].set_null_options & 0x1) && 
            (double *)(bind_ptr[index].data)[i] == (double)(context[context_num].set_null_number)
          ind_array[i] = -1;
      }

      memcpy(bind_ptr[index].ind,ind_array,array_size*sizeof(short));
      break;

    case GDB_STRING_TYPE:
      bind_ptr[index].datatype = GDB_STRING_TYPE;
	  elmntsize = (long)sizeof(char *);
      if ((bind_ptr[index].data = (char **)calloc(array_size+1,elmntsize)) == (char **)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc data array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        return (GDB_ERROR);
      }
      if ((bind_ptr[index].ind = (short *)calloc(array_size,sizeof(short))) == (short *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc ind array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        free((short *)ind_array);
        return (GDB_ERROR);
      }    
/*      memcpy( bind_ptr[index].data, bind_vars, array_size*elmntsize );	 */
	  
        elmntsize = (long)sizeof(char *);
        for (i=0; i<array_size; i++)
        {
            len = strlen(bind_vars[i]);
            if ((bind_ptr[index].data[i] = (char *)calloc(len+1,elmntsize)) == (char *)NULL)
            {
                iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc data element");
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
                return (GDB_ERROR);
            }
            strcpy( bind_ptr[index].data[i], bind_vars[i] );
		
            /* check for nulls */
            /* --------------- */
            ind_array[i] = 0 ;
            if ((context[context_num].set_null_options & 0x2) && 
                    !strcmpci(bind_vars[i], context[context_num].set_null_string) ) 
                ind_array[i] = -1;
            else
                if ((context[context_num].set_null_options & 0x4) && !strcmpci(bind_vars[i],"NULL"))
                    ind_array[i] = -1;
        }
        memcpy(bind_ptr[index].ind,ind_array,array_size*sizeof(short));
        break;
  } /* end switch */

  free ((short *)ind_array);

  return (GDB_SUCCESS);
}

/*======================================================================
  count_bind_vars
  ======================================================================*/

long count_bind_vars( shandle, bind_vars )
    long     shandle;
    char    *bind_vars;
{
  register int nBind;
  gSQLDA  *bind_ptr;
  char    *bind_name;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","COUNT_BIND_VARS");

  if (shandle == 0) return (GDB_ERROR);

  bind_ptr = sqlda_ptrs[context_num][shandle].bptr;
  
  if ((bind_name = (char *)calloc(context[context_num].max_bind_name_len+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
    return(GDB_ERROR);
  }

  nBind = 0;
  while (strgettoken(bind_vars,bind_name,',',nBind) != NULL)
    nBind++;
  
  if (bind_name != (char *)NULL)
    free(bind_name);

  if (nBind != bind_ptr[0].ncols) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",ENUMVAL,nBind,bind_ptr[0].ncols);
    return (GDB_ERROR);
  }

  return (GDB_SUCCESS);
}
