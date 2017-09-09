/*================================================================
 * GDB_CLIENT_INTER_RDB.C  - GDB Layer-3   (RDB-5.1)      [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-3 = gdb_client_inter_rdb.c + gdb_client_rdb.sc
 *    - provide interface between 'common layer' and 'database
 *      specific layer'
 *================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>   /* for isdigit */
#include <descrip.h>
#include <ssdef.h>   
#include "gdb_globals.h"
#include "gdb_genda.h"
#include "gdb_client_rdb.h"
#include "gdb_client_inter_rdb.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "gsi_main.h"
#include "gdb_utils.h"
#include "gdb_common.h"


#define LAYER LAYER3

extern CONTEXT_INFO  context[MAX_GDB_CONTEXTS];    
/* This RDB specific to hold object array */
extern dSQLDA        dsqlda_ptrs[MAX_CURSORS];  /* because RDB SQLDA doesn't support descriptor array *     

extern char  *upper_case();
extern long   process_reconnect();
extern long   load_msg();

/* globals */
extern long   debug;
extern long   end_of_cursor;
extern long   short_messages;
extern long   max_col_array_size;  
extern BRIDGE_INFO  bridge_info;

SQLDA_PTRS   *sqlda_ptrs[MAX_GDB_CONTEXTS]; 
gSQLCA       *gsqlca;
long         row_count[MAX_GDB_CONTEXTS];

gsi_int       context_num;
struct dsc$descriptor_s rdb_dsc;
/*======================================================================
  get_genda_data
    - load SQLDA(database) data into GENDA(bridge)

    Arguments:
    - sqlGen: GENDA structure receiving the database data
  ======================================================================*/

long get_genda_data( sqlGen )
    GENDA     *sqlGen;
{
  union {
    short val;
    struct {
      short prec  : 8;
      short scale : 8;
    } bits;
  } num;   

  register long row; 
  gSQLDA  *select_ptr;
  long     start_row;
  long     rows_fetched;
  char     buff[100];
  long     null_len;
  long     col;


 context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","GET_GENDA_DATA");

  /* since SQLDA is reused for each row fetched, the previous values are not
     cleared-out. Therefore, if a column value = NULL, then set STRING to 
     'null_string' and NUMBERS to 'null_number'. */

  select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr;
  if (select_ptr->SQLD < 1) return(GDB_ERROR);

  null_len = strlen(context[context_num].null_string);

  /* Force array fetching OFF for now */
  context[context_num].array_fetch = FALSE;
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
  } 

  for (row=start_row;row<rows_fetched+1;row++) /* The +1 is for EOCURSOR */   
  {

    for(col=0;col<select_ptr->SQLD;col++)
    {
      /* load indicator variables */
      sqlGen->da_col_ptr[col].ind[sqlGen->more_rows] = *select_ptr->SQLVAR[col].SQLIND;

      /* load value buffers into GENDA*/
      switch (select_ptr->SQLVAR[col].SQLTYPE) {   /* switch on datatype */
        case VARCHAR :
        case CHAR :
        case SEGSTRING :
        case STRING :
          sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
          if ((sqlGen->da_col_ptr[col].val[row].gdb_str = 
              (char *)calloc(select_ptr->SQLVAR[col].SQLLEN+1,sizeof(char))) == (char *)NULL) {
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc gdb_str buffers");
            iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE,"%d",EINSMEM);
            return (GDB_ERROR);
          }                       
     
          if (*select_ptr->SQLVAR[col].SQLIND < 0 || sqlGen->genStat.code == end_of_cursor) {
            if ((sqlGen->da_col_ptr[col].val[row].gdb_str = (char*)realloc(sqlGen->da_col_ptr[col].val[row].gdb_str,
                (null_len+1)*sizeof(char))) == (char *)NULL) {
              iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EINMEMR);
              return (GDB_ERROR);
            }

            strcpy(sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_str,context[context_num].null_string);
            break;
          }
          if (sqlGen->da_col_ptr[col].val[row].gdb_str != NULL) {

            strncpy(sqlGen->da_col_ptr[col].val[row].gdb_str,
              select_ptr->SQLVAR[col].SQLDATA,select_ptr->SQLVAR[col].SQLLEN);
            sqlGen->da_col_ptr[col].val[row].gdb_str[select_ptr->SQLVAR[col].SQLLEN] = 0;
          }
          else {
            iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d%d","Value buffer row % col % NOT allocated",row,col); 
            iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EINMEMR);
            return (GDB_ERROR);
          }
          break;

        case DATE :
          sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
          if ((sqlGen->da_col_ptr[col].val[row].gdb_str = (char *)calloc(DATE_LEN,sizeof(char))) == (char *)NULL) {
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc gdb_str buffers");
              iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE,"%d",EINSMEM);
              return (GDB_ERROR);
          }     

          if (*select_ptr->SQLVAR[col].SQLIND < 0 || sqlGen->genStat.code == end_of_cursor) {  
          /* it has been change to below because can't include end_of_cursor */
          /*if (*select_ptr->SQLVAR[col].SQLIND < 0 ){  */
            if ((sqlGen->da_col_ptr[col].val[row].gdb_str = (char *)realloc(sqlGen->da_col_ptr[col].val[row].gdb_str,
                (null_len+1)*sizeof(char))) == (char *)NULL) {
              iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EINMEMR);
              return (GDB_ERROR);
            }

           strcpy(sqlGen->da_col_ptr[col].val[row].gdb_str,context[context_num].null_string);
          break;
        }
        if (sqlGen->da_col_ptr[col].val[row].gdb_str != NULL) {
          rdb_dsc.dsc$b_class   = DSC$K_CLASS_S;
          rdb_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
          rdb_dsc.dsc$w_length = DATE_LEN-1;
          rdb_dsc.dsc$a_pointer = sqlGen->da_col_ptr[col].val[row].gdb_str;
          if (SYS$ASCTIM(0,&rdb_dsc,select_ptr->SQLVAR[col].SQLDATA,0) == SS$_NORMAL) {
            sqlGen->da_col_ptr[col].val[row].gdb_str[DATE_LEN-1] = 0;
            if (*select_ptr->SQLVAR[col].SQLIND < 0)
              *sqlGen->da_col_ptr[col].val[row].gdb_str = 0;
          }
          else
            strcpy(sqlGen->da_col_ptr[col].val[row].gdb_str,"DATE_ERROR");
        }
        else {
          iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d%d","Value buffer row % col % NOT allocated",row,col); 
          iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EINMEMR);
          return (GDB_ERROR);
        }
        break;

        case TINYINT :
        case SMALLINT :
        case INTEGER :
        case BIGINT :
          num.val = select_ptr->SQLVAR[col].SQLLEN;
          if (num.bits.scale > 0 || select_ptr->SQLVAR[col].SQLTYPE == BIGINT) {
            if (context[context_num].gbl_status.status == 0) { /* dont change status if it has another msg */
              if (select_ptr->SQLVAR[col].SQLNAME_LEN > 0) {
                strncpy(buff,select_ptr->SQLVAR[col].SQLNAME,select_ptr->SQLVAR[col].SQLNAME_LEN);
                buff[select_ptr->SQLVAR[col].SQLNAME_LEN] = 0;
              }
              else
                sprintf(buff,"COLUMN #%d",col+1);
              iomsg(DBG4,LAYER,TRUE,FALSE,NULL,FALSE,"%d%s%s%s",WTYPCHG,buff,"INTEGER","FLOAT");
            }

            sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE;
            if (*select_ptr->SQLVAR[col].SQLIND < 0 || sqlGen->genStat.code == end_of_cursor)
              sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = context[context_num].null_number;
            else {
              if (num.bits.scale > 0)
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = (*(GDB_LONG *)select_ptr->SQLVAR[col].SQLDATA)/pow(10,num.bits.scale);
              else
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = *(GDB_LONG *)select_ptr->SQLVAR[col].SQLDATA;
            }
            break;
          }
          if (*select_ptr->SQLVAR[col].SQLIND < 0 || sqlGen->genStat.code == end_of_cursor)
             sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long = context[context_num].null_number;
          else {
            switch (select_ptr->SQLVAR[col].SQLTYPE) {
              case TINYINT :
                sqlGen->da_col_ptr[col].data_type = GDB_BYTE_TYPE;
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_byte = *(GDB_BYTE *)select_ptr->SQLVAR[col].SQLDATA;
                break;
              case SMALLINT :
                sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE;
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_short = *(GDB_SHORT *)select_ptr->SQLVAR[col].SQLDATA;
                break;
              case INTEGER :
                sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE;  
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_int = *(GDB_INT *)select_ptr->SQLVAR[col].SQLDATA;
                break;
              case BIGINT :
                sqlGen->da_col_ptr[col].data_type = GDB_LONG_TYPE;
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_long =
                *(GDB_LONG *)select_ptr->SQLVAR[col].SQLDATA;
                break;
            }
          }
          break;
  
          case FLOAT :
            if (*select_ptr->SQLVAR[col].SQLIND < 0 || sqlGen->genStat.code == end_of_cursor)
              sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_dbl = context[context_num].null_number;        
            else {
              if (select_ptr->SQLVAR[col].SQLLEN == sizeof(GDB_FLOAT)) {
                sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE;
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_float = *(GDB_FLOAT *)select_ptr->SQLVAR[col].SQLDATA;
              }
              else {
                /*
                ** ????????
                ** RDB returns double precision as float, so cast to a float
                */
                sqlGen->da_col_ptr[col].data_type = GDB_DBL_TYPE;
                sqlGen->da_col_ptr[col].val[sqlGen->more_rows].gdb_float = 
                    *(GDB_FLOAT *)select_ptr->SQLVAR[col].SQLDATA;
              }
            }
            break;   
  
        default:
          iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,select_ptr->SQLVAR[col].SQLTYPE,col+1);
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
     - All EXEC SQL names are generated from shandle
       (e.g. if shandle=1 then stmt_id = S1)
  ======================================================================*/

long alloc_sqlda_ptrs()
{
  long    i;

  context_num = gsi_current_context();

  if (debug & DBG1) {
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","ALLOC_SQLDA_PTRS");
  }


  /* for lack of a better place to assign the DB specific EOC code
     to the global end_of_cursor variable */
  end_of_cursor = DB_END_OF_CURSOR;

  if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
    return (GDB_SUCCESS);

  /*** alloc SQLDA_PTRS array ***/
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
    - load init gSQLDA data into GENDA

    Arguments:
    - sqlGen: GENDA
    - max_rows: number of rows to allocate in the GENDA struct
  ======================================================================*/

long db_alloc_genda( sqlGen, max_rows )
    GENDA  *sqlGen;
    long    max_rows;
{
  gSQLDA  *select_ptr;
  long     shandle;
  long     col,row;
  long     name_len;
  short    no_col_name = 0;

  context_num = gsi_current_context();

  if (debug & DBG1) {
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","DB_ALLOC_GENDA");
  }

  select_ptr = sqlda_ptrs[context_num][sqlGen->stmt_handle].sptr;

  shandle = sqlGen->stmt_handle;
  for (col=0;col<sqlGen->ncols;col++) {
    name_len = select_ptr->SQLVAR[col].SQLNAME_LEN;
    if (name_len == 0) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%s",EBADCNM,GDB_UNKNOWN);
      return (GDB_ERROR);
 
      /*name_len = strlen(funct_col_name[context_num][col]);*/
      /*no_col_name = 1;*/
    }
    else {
      select_ptr->SQLVAR[col].SQLNAME[name_len] = 0;
      if (strchr(select_ptr->SQLVAR[col].SQLNAME,'(') != NULL)
        strcpy(sqlGen->da_col_ptr[col].col_name,GDB_UNKNOWN);    /* ?? 
        name_len = strlen(funct_col_name[context_num][col]);*/
    }

    if ((sqlGen->da_col_ptr[col].col_name = (char *)calloc(name_len+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc col_name buffer");
      iomsg(DBGM,LAYER,TRUE,TRUE,sqlGen,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }

    if (select_ptr->SQLVAR[col].SQLNAME_LEN == 0){
      strcpy(sqlGen->da_col_ptr[col].col_name,GDB_UNKNOWN);
    }else {
      select_ptr->SQLVAR[col].SQLNAME[name_len] = 0;
      strcpy(sqlGen->da_col_ptr[col].col_name,upper_case(select_ptr->SQLVAR[col].SQLNAME)); 
    }
  
    /*** alloc sqlGen->nrows val ptrs & ind buffers ***/
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
    switch (select_ptr->SQLVAR[col].SQLTYPE) {
      case VARCHAR :
      case CHAR :
      case SEGSTRING :        
      case STRING :
        sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;
/*
** MOVED THE ALLOCATION OF THE VALUE STRUCTURE TO GET GET_GENDA 
*/   
        break;  

      case DATE :
        sqlGen->da_col_ptr[col].data_type = GDB_STRING_TYPE;

        break;  
      case TINYINT :
        sqlGen->da_col_ptr[col].data_type = GDB_BYTE_TYPE;
        break;
      case SMALLINT :
        sqlGen->da_col_ptr[col].data_type = GDB_SHORT_TYPE;
        break;
      case INTEGER :
        sqlGen->da_col_ptr[col].data_type = GDB_INT_TYPE;
        break;
      case BIGINT :  /* quadword */
        sqlGen->da_col_ptr[col].data_type = GDB_LONG_TYPE;
        break;

      case FLOAT :
        if (select_ptr->SQLVAR[col].SQLLEN == sizeof(GDB_FLOAT))
          sqlGen->da_col_ptr[col].data_type = GDB_FLOAT_TYPE;
        else
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
    - load genStat section of GENDA with gSQLCA
    - load gbl_status struct with gSQLCA

    Arguments:
    - sqlGen: GENDA
  ======================================================================*/

long get_stat( sqlGen )
    GENDA  *sqlGen;
{
  char   prefix_msg[DB_TYPE_LEN+MAX_CONTEXT_NAME_LEN+STAT_SYM_LEN+4];
  char   text_msg[STATUS_MSG_LEN+1];
  long   msg_len  = 0;
  long   curr_len = 0;
  long   tmp_cd;
  long   tmp;

  if (gsqlca == (gSQLCA *)NULL) return (GDB_ERROR);

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
  context[context_num].gbl_status.code = gsqlca->SQLCODE; 
  if (gsqlca->SQLCODE >= 0) {
    context[context_num].gbl_status.status = SUCCESS_CD;
    context[context_num].gbl_status.rows_processed = row_count[context_num];
/* gsqlca->SQLERRD[2]; */
  }
  if (gsqlca->SQLCODE > 0) context[context_num].gbl_status.status = WARN_CD;
  if (gsqlca->SQLCODE < 0) context[context_num].gbl_status.status = ERROR_CD;
  if (gsqlca->SQLCODE == DB_END_OF_CURSOR) 
    context[context_num].gbl_status.status = EOCURSOR_CD;

  *context[context_num].gbl_status.msg = 0;

  /* load the context info into message first */
  curr_len = load_msg(context[context_num].gbl_status.status,0,&tmp,prefix_msg,FALSE);

  
  if (gsqlca->SQLCODE != 0) {   /* error or warning */
    tmp = 0;
    msg_len = STATUS_MSG_LEN - curr_len;
    if (msg_len > 0) {
      rdb_dsc.dsc$b_class   = DSC$K_CLASS_S;
      rdb_dsc.dsc$b_dtype   = DSC$K_DTYPE_T;
      rdb_dsc.dsc$a_pointer = text_msg;
      rdb_dsc.dsc$w_length  = msg_len;
      SQL$GET_ERROR_TEXT(&rdb_dsc,&tmp);
    }
    if (tmp > 0)
      text_msg[tmp] = 0;
    else
      text_msg[0] = 0;
  }

  curr_len += msg_len;

  /* Rdb does not utilize SQLCA warning fields */

  if (gsqlca->SQLCODE < 0)
    context[context_num].gbl_status.rows_processed = 0;

  /* concat prefix and message body */
  sprintf(context[context_num].gbl_status.msg,"%s%s",prefix_msg,text_msg);

  /*** load the GENDA struct ***/
  if (sqlGen != (GENDA *)NULL) {
    msg_len = strlen(context[context_num].gbl_status.msg);
    /*** alloc genStat buffers ***/
    if (sqlGen->genStat.msg == (char *)NULL) {
      if ((sqlGen->genStat.msg = 
          (char *)calloc((msg_len+1),sizeof(char))) == (char *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT alloc mem for genStat.msg");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        set_error(sqlGen);
        return (GDB_ERROR);
      }
    }
    else {
      if ((sqlGen->genStat.msg = (char *)realloc(sqlGen->genStat.msg,(msg_len+1)*sizeof(char))) == (char *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT realloc mem for genStat.msg");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINMEMR);
        set_error(sqlGen);
        return (GDB_ERROR);
      }
    }
    strncpy(sqlGen->genStat.msg,context[context_num].gbl_status.msg,msg_len);
    sqlGen->genStat.msg[msg_len] = 0;
    sqlGen->genStat.code = context[context_num].gbl_status.code;
    if (gsqlca->SQLERRD[1]) /* is SELECT statment */     
      sqlGen->genStat.rows_processed = context[context_num].gbl_status.rows_processed;
    else
      sqlGen->genStat.rows_processed = row_count[context_num]; /* gsqlca->SQLERRD[2]; */
    sqlGen->genStat.status = context[context_num].gbl_status.status;
  }
     /* changed to gdb60b1 */
 /* if ( gsqlca->SQLCODE >= DB_NOT_CONNECTED_START && 
       gsqlca->SQLCODE <= DB_NOT_CONNECTED_STOP && 
       gsqlca->SQLCODE != DB_CONNECTION_IN_USE )  */

   /* reconnect to DB if disconnect detected */
   if ( gsqlca->SQLCODE == DB_NOT_CONNECTED1 || 
        gsqlca->SQLCODE == DB_NOT_CONNECTED2 ||
        gsqlca->SQLCODE == DB_NOT_CONNECTED3 ||
        gsqlca->SQLCODE == DB_NOT_CONNECTED_STOP ) {
    context[context_num].gbl_status.status = NOCONNECT_CD;
    context[context_num].connected_to_db = FALSE; 
    process_reconnect();
  }
   
  /* reset certain SQLCA fields to 'null' */
  gsqlca->SQLERRM.SQLERRML = 0;
  gsqlca->SQLERRD[2] = 0;
  *gsqlca->SQLWARN.SQLWARN0 = 0;
  gsqlca->SQLCODE = 0;

  if ((debug & DBG5) && context[context_num].gbl_status.status != SUCCESS_CD) { 
    printf("\nSQL Message Structure\n");
    printf("ver   : %s\n",bridge_info.bridge_version);
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
  dSQLDA     *desc_ptr;  
  gSQLDA     *bind_ptr;
  register long i;
  long       elmntsize;
  short      *ind_array;
  double     *tmp_dbl;
  long       len;        
  int        n;
  long       opts ;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","LOAD_BIND_VARS");

  if (shandle == 0) return (GDB_ERROR);

  bind_ptr = sqlda_ptrs[context_num][shandle].bptr;
  desc_ptr = dsqlda_ptrs;
  
  if (bind_ptr == (gSQLDA *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d",ENOTINI);
    return (GDB_ERROR);
  }

  /*
  ** Compare the datatype expected by the database to the datatype in the array 
  ** or list sent from G2.  If the datatypes are incompatible return to the caller
  ** with an error. Free the data area of the gSQLDA if was allocated previously
  ** via a "set" operation.
  */

  /* release the bind value if allocated via previous set operation */
  switch ( bind_ptr->SQLVAR[index].SQLTYPE )
  {
    case CHAR :
    case STRING :
    case VARCHAR :
    case DATE :
      if ( datatype != GDB_STRING_TYPE ) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d%d",EINCDTP,index+1);
        return( GDB_ERROR );
      }
      if ( desc_ptr[index].data ) {
        for ( i=0; i<=array_size, desc_ptr[index].data[i] ;i++ ) {
          free( desc_ptr[index].data[i] );
          desc_ptr[index].data[i] = NULL;
        }
        free( desc_ptr[index].data );
        desc_ptr[index].data = NULL;
      }
      break;

    case TINYINT :         
    case SMALLINT :
    case INTEGER : 
      if ( (datatype != GDB_INT_TYPE) && (datatype != GDB_FLOAT_TYPE) ) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d%d",EINCDTP,index+1);
        return( GDB_ERROR );
      }
      if ( desc_ptr[index].data ) {
        free( desc_ptr[index].data );
        desc_ptr[index].data = NULL;
      }
      break;

    case FLOAT :    /* real,double */
    case BIGINT :    
      if ( datatype != GDB_FLOAT_TYPE ) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d%d",EINCDTP,index+1);
        return( GDB_ERROR );
      }
      if ( desc_ptr[index].data ) {
        free( desc_ptr[index].data );
        desc_ptr[index].data = NULL;
      }
      break;
      
  }

  /* free the NULL indicator area of the gSQLDA if previously allocated */
  if ( desc_ptr[index].ind ) {
    free( desc_ptr[index].ind );
    desc_ptr[index].ind = NULL;
  }

  /* allocate the indicator array for NULLS */
  if ((ind_array = (short *)calloc(array_size,sizeof(short))) == (short *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc indicator array");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
    return (GDB_ERROR);
  }

  opts = context[context_num].set_null_options ;
  switch(datatype) {

    case GDB_INT_TYPE:
    elmntsize = (long)sizeof(long);
      if ((desc_ptr[index].data = (char**)calloc(array_size,elmntsize)) == (char **)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc data array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        return (GDB_ERROR);
      }
      if ((desc_ptr[index].ind = (short *)calloc(array_size,sizeof(short))) == (short *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc ind array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        free((short *)ind_array);
        return (GDB_ERROR);
      } 

      memcpy(desc_ptr[index].data,bind_vars,array_size*elmntsize);   

      /* check for null values */
      /* --------------------- */
      for (i=0;i<array_size;i++)
      {
        if ((opts & 0x1) && ((long *)desc_ptr[index].data)[i] == context[context_num].set_null_number)
          ind_array[i] = -1;  
      }
      memcpy(desc_ptr[index].ind,ind_array,array_size*sizeof(short));
      break;

    case GDB_FLOAT_TYPE:
      elmntsize = (long)sizeof(double);
      if ((desc_ptr[index].data = (char **)calloc(array_size,elmntsize)) == (char **)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc data array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        return (GDB_ERROR);
      }
      if ((desc_ptr[index].ind = (short *)calloc(array_size,sizeof(short))) == (short *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc ind array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        free((short *)ind_array);
        return (GDB_ERROR);
      }     
      memcpy( desc_ptr[index].data, bind_vars, array_size*elmntsize ); 

      /* check for null values */
      /* --------------------- */
      tmp_dbl = (double *)desc_ptr[index].data;

      for (i=0;i<array_size;i++)
      {
        if ((opts & 0x1) && *tmp_dbl == (double)context[context_num].set_null_number )
          ind_array[i] = -1;
        tmp_dbl++;
      }
      memcpy(desc_ptr[index].ind,ind_array,array_size*sizeof(short));
      break;

    case GDB_STRING_TYPE:
      elmntsize = (long)sizeof(char *);
      if ((desc_ptr[index].data = (char **)calloc(array_size+1,elmntsize)) == (char **)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc load_bind temp array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        free((short *)ind_array);
        return (GDB_ERROR);
      }

      if ((desc_ptr[index].ind = (short *)calloc(array_size,sizeof(short))) == (short *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc ind array");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
        free((short *)ind_array);
        return (GDB_ERROR);
      }     

      for (i=0; i<array_size; i++) {
        len = strlen(bind_vars[i]);
        if ((desc_ptr[index].data[i] = (char *)calloc(len+1,elmntsize)) == (char *)NULL) {
          iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc data element");
          iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EINSMEM);
          return (GDB_ERROR);
        }
        strcpy( desc_ptr[index].data[i], bind_vars[i] );

        /* check for nulls */
        /* --------------- */
        if ((opts & 0x2) && !strcmpci(bind_vars[i],context[context_num].set_null_string))
          ind_array[i] = -1;
        else if ((opts & 0x4) & !strcmpci(bind_vars[i],"NULL"))
          ind_array[i] = -1;
      }
      memcpy(desc_ptr[index].ind,ind_array,array_size*sizeof(short));
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
  register long nBind;
  gSQLDA     *bind_ptr;   
  char   bind_name[MAX_VNAME_LEN];
  
  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","COUNT_BIND_VARS");

  if (shandle == 0) return (GDB_ERROR);

  bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

  nBind = 0;
  while (strgettoken(bind_vars,bind_name,',',nBind) != NULL)
    nBind++;

  if (nBind != bind_ptr->SQLN) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",ENUMVAL,nBind,bind_ptr->SQLN);
    return (GDB_ERROR);
  }  
  
  return (GDB_SUCCESS);
}

