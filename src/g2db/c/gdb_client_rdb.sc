/*================================================================
 *  GDB_CLIENT_RDB.SC    - GDB Layer-3    (RDB-5.1)       [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-3 = gdb_client_inter_rdb.c + gdb_client_rdb.sc
 *    - performs all calls to database
 *    - extracts data from SQLDA and inserts into GENDA
 *    - upper layers should check status
 *    - only layer requiring pre-compilation (sql$pre)
 *================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <descrip.h> 
#include <ssdef.h> 
#include "gdb_client_rdb.h"
#include "gdb_client_inter_rdb.h"
#include "gdb_globals.h"
#include "gdb_messages.h"
#include "gsi_main.h"
#include "gdb_context.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#include "gdb_g2_client.h"

EXEC SQL INCLUDE SQLCA;

#include <sql_sqlda.h>

#define LAYER LAYER3


/* external variables */
extern gSQLCA   *gsqlca;
extern long      debug;

/* context-sensitive globals */
extern CONTEXT_INFO context[MAX_GDB_CONTEXTS];
extern SQLDA_PTRS  *sqlda_ptrs[MAX_GDB_CONTEXTS];

extern dSQLDA       dsqlda_ptrs[MAX_CURSORS]; /* because RDB SQLDA doesn't support descriptor array */  

extern long         row_count[MAX_GDB_CONTEXTS];  /* because INF doesn't report row #'s */
extern long         max_col_array_size;          

/* globals */
char   connect_name[5];  /* DBxx */
gsi_int  context_num;

long     SQLCODE;  /* required for ANSI mode */

char   rdb_stmt_id_name[5];  

struct dsc$descriptor_s rdb_dsc;
/*======================================================================
  sql_setup
    - establish mapping and initial setup to esql variables and 
      structures used by all layers.
  ======================================================================*/

long sql_setup()
{
  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_SETUP");

  /*** map local sqlca to global gsqlca ***/
  gsqlca = (gSQLCA *)&SQLCA;

  return (GDB_SUCCESS);
}


/*======================================================================
  sql_connect  (1)
    - establish connection to database

    Arguments:
    - db_user: NA
    - db_pass: NA
    - db_conn_str: database connect string
  ======================================================================*/

long sql_connect( db_user,db_pass,db_conn_str )
    char    *db_user;
    char    *db_pass;
    char    *db_conn_str;
{
  char    *ptr1;

  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_CONNECT");

  if (db_conn_str == (char *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",ENOCONS);
    return (GDB_ERROR);
  }

  /* strip >'< from connect string */
  ptr1 = db_conn_str;
  while (*ptr1 != 0) {
    if (*ptr1 == '\'')
      *ptr1 = ' ';
    ptr1++;
  }

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL CONNECT TO :db_conn_str AS :connect_name;

  if (SQLCA.SQLCODE == DB_CONNECTION_IN_USE) {
    iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE,"%d",IDBCONA);
    return (GDB_SUCCESS);
  }

  if (!SQLCA.SQLCODE) {
    iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE,"%d",IDBCONE);
    return (GDB_SUCCESS);
  }

  iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EBADCON);
  return (GDB_ERROR);
}


/*======================================================================
  sql_alloc_descriptors
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
  gSQLDA  *BIND_PTR;
  gSQLDA  *SELECT_PTR;
  long     ncols;

  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_ALLOC_DESCRIPTORS");

  /* alloc space for SQLDA area. NOTE: The space allocated must be equal to
     the size of SQLDA + the MAXimum # of bind/select items * the size of 
     the SQLVAR area. This area will be reallocated after the describe. */

  if (shandle == 0) return (GDB_ERROR);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  if (action == BIND) {
    ncols = context[context_num].max_bind_vars;

    if ((BIND_PTR = (gSQLDA *)calloc(1,sizeof(gSQLDA)+ncols*sizeof(SQLVAR_STRUCT)))
        == (gSQLDA *)NULL) { 
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EALDESC);
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }   

    /*** store bind addr in SQLDA_PTRS array ***/
    if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
      sqlda_ptrs[context_num][shandle].bptr = BIND_PTR; 
    else {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT store bind pointer in SQLDA_PTRS");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);                     
    }
    /*** load SQLDA with default info ***/
    BIND_PTR->SQLN = ncols;       /* max number of bind items */
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Input (BIND) Descriptor Memory Allocated"); 
    return (GDB_SUCCESS) ;
  }
  
  if (action == SELECT) {
    ncols = max_col_array_size;

    if ((SELECT_PTR = (gSQLDA *)calloc(1,sizeof(gSQLDA)+ncols*sizeof(SQLVAR_STRUCT)))
        == (gSQLDA *)NULL) { 
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EALDESC);
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR) ;                     
    }         
    /*** store select addr in SQLDA_PTRS array ***/
    if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
      sqlda_ptrs[context_num][shandle].sptr = SELECT_PTR; 
    else {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT store select pointer in SQLDA_PTRS");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);                     
    } 

    /*** load SQLDA with default info ***/
    SELECT_PTR->SQLN = ncols;       /* max number of select items */

    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Output (SELECT) Descriptor Memory Allocated");
    return (GDB_SUCCESS);
  }

  return (GDB_SUCCESS);
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
    long   shandle;
    long  *stmt_id;
    char  *sql_str;
    
{
  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_PREPARE");

  if (shandle == 0) return (GDB_ERROR);
  if (*stmt_id != 0) *stmt_id = 0;
  
  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  *stmt_id=shandle;
  sprintf(rdb_stmt_id_name,"S%d",shandle);    /* changed from long* to char(5)*/
  EXEC SQL PREPARE :rdb_stmt_id_name FROM :sql_str;  
  
  if (SQLCA.SQLCODE < 0){
    row_count[context_num] = 0;
    *stmt_id = 0; /* stmt_id created dynamically for RDB */
  }
  
  return(SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
    
}                                                                         


/*======================================================================
  sql_declare_cursor
    - declare a cursor in the database
  
    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
    - stmt_id: statement id created from prepare
  ======================================================================*/

long sql_declare_cursor( curs_name, shandle, stmt_id )
    char  *curs_name;
    long   shandle;
    long  *stmt_id;
{
  context_num = gsi_current_context();

  if (shandle == 0) return (GDB_ERROR);

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_DECLARE_CURSOR: %",curs_name);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  sprintf(rdb_stmt_id_name,"S%d",shandle);
  
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL DECLARE :curs_name CURSOR FOR :rdb_stmt_id_name; 

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_describe_input
    - id all host vars (INPUT VARIABLES) and load into bind descriptor
    - alloc memory for bind vars
    - get values for host bind vars
    - currently not supported
  ======================================================================*/

long sql_describe_input( shandle, bind_vars, stmt_id, bind_processed, action)
    long             shandle;
    BIND_STRUCT     *bind_vars;
    long            *stmt_id;   
    long            *bind_processed;
    long             action;
{
  register   long i, n, bvl;
  gSQLDA    *BIND_PTR;
  char     **bind_array = (char **)NULL;
  char      *ptr1,*ptr2;   /* the following vars are temp hacks -- remove for production */
  long       status;

  char buff[80];
  char rdb_msg[STATUS_MSG_LEN];
  int  rdb_msg_len;

  short                 descnt;
  int                   dnamelen;
  int                   ddatalen;
  char                  col_name[31];
  short                 ind_val;
  char                  *text_val;
  char                  *date_val;
  long                  *long_val;
  short                 *short_val; 
  float                 *float_val;
  double                *dbl_val;        
  struct dsc$descriptor_s datetime_desc;

  union {
    short val;
    struct {
      short prec  : 8;
      short scale : 8;
    } bits;
  } num;          
  
  context_num = gsi_current_context();
  
  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DESCRIBE_INPUT");
    
  *bind_processed = FALSE;

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf((char *)connect_name,"DB%d",context_num);

  BIND_PTR = sqlda_ptrs[context_num][shandle].bptr;
  sprintf(rdb_stmt_id_name,"S%d",shandle);  

  if (BIND_PTR == (gSQLDA *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d",ENOTINI);
    return (GDB_ERROR);
  }                                                 

  if (action == GDB_INIT)
  {  
    EXEC SQL SET CONNECT :connect_name;
    if (SQLCA.SQLCODE  < 0 ) return( GDB_EXT_ERROR );

    /* Determine how many bind variables there are */    
    EXEC SQL DESCRIBE :rdb_stmt_id_name MARKERS INTO BIND_PTR;
    descnt = BIND_PTR->SQLD;
    if (SQLCA.SQLCODE < 0) {
      rdb_msg_len = 0;
      rdb_dsc.dsc$b_class = DSC$K_CLASS_S;
      rdb_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
      rdb_dsc.dsc$w_length = STATUS_MSG_LEN;
      rdb_dsc.dsc$a_pointer = rdb_msg;
      SQL$GET_ERROR_TEXT( &rdb_dsc, &rdb_msg_len );
      rdb_msg[rdb_msg_len] = 0;
      iomsg( DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%d%s",
             "DESCRIBE: SQLCODE=% %", SQLCA.SQLCODE, rdb_msg );
      return (GDB_ERROR);
    }
             
    if ( descnt < 0) {
       iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",ENCOLEX,BIND_PTR->SQLN,context[context_num].max_bind_vars);
       BIND_PTR->SQLD = 0;
       return (GDB_ERROR);
     }
     BIND_PTR->SQLN = BIND_PTR->SQLD;  /* max items = max items found */
  
    if ( descnt > context[context_num].max_bind_vars) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EMBVEXD,descnt, context[context_num].max_bind_vars);
      descnt = 0; /* set to 0 to avoid dealloc problems */
      return (GDB_ERROR);
    }
  } /*action == GDB_INIT */   

  /* check If there are no input descriptors, just return success */
  if ( (!BIND_PTR->SQLD) || (!bind_vars->nBind) ) {
      *bind_processed = TRUE;
    return ( GDB_SUCCESS );
  }

  if ( BIND_PTR->SQLD != bind_vars->nBind ) {
    iomsg( DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d%d%d",ENUMVAL,bind_vars->nBind,BIND_PTR->SQLD );
    return( GDB_ERROR );
  }

  /* allocate array to store input bind variable values */ 
  if ((bind_array = (char **)calloc(BIND_PTR->SQLN,sizeof(char *))) == (char **)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for bind_array");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }

  for (i=0;i<BIND_PTR->SQLN;i++) {
    if ( BIND_PTR->SQLVAR[i].SQLTYPE == DATE )
      bvl = DATE_LEN;
    else
      bvl = strlen(bind_vars->bind_array[i]);
    if ((bind_array[i] = (char *)calloc(bvl+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for bind_array");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      if (bind_array != (char **)NULL)
        free ((char **)bind_array);
      return (GDB_ERROR);
    }
  }

  iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d","Bind variables processed: %",BIND_PTR->SQLN);

  /* Load bind variables into bind descriptor */
  for (i=0; i<BIND_PTR->SQLD;i++) { 
    strcpy( bind_array[i], bind_vars->bind_array[i] );

    /* alloc indicator variables */
    if ((BIND_PTR->SQLVAR[i].SQLIND = (short *)calloc(1,sizeof(short))) == (short *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLIND");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return(GDB_ERROR);
    }   

    /* Set the null indicator if required */
    /* ---------------------------------- */
    BIND_PTR->SQLVAR[i].SQLIND = 0;
    if ((context[context_num].set_null_options & 0x2) && 
            ! strcasecmp(bind_array[i], context[context_num].set_null_string))
        BIND_PTR->SQLVAR[i].SQLIND = -1;
    else 
        if ((context[context_num].set_null_options & 0x4) && !strcasecmp(bind_array[i],"NULL"))
	        BIND_PTR->SQLVAR[i].SQLIND = -1;

    switch (BIND_PTR->SQLVAR[i].SQLTYPE)
    {
      case VARCHAR :
      case STRING :
      case CHAR :
        BIND_PTR->SQLVAR[i].SQLTYPE = STRING;
        ++BIND_PTR->SQLVAR[i].SQLLEN ;  /* for the null */
        ddatalen = strlen(bind_array[i]) + 1;
        if( (BIND_PTR->SQLVAR[i].SQLDATA = 
            (char *)calloc(ddatalen,sizeof(char)) ) == (char *)NULL ) {
          iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
          return (GDB_ERROR);
        }
        strcpy( BIND_PTR->SQLVAR[i].SQLDATA, bind_array[i] );
        break;                                                 
    
      case DATE :
          /*
          ** Kluge!
          ** append zeroes to end of date if necessary
          ** If you don't do this, the date will have garbage at the end. 
          */
          if ( strlen(bind_array[i]) <= 11 )
            strcat( bind_array[i], " 00:00:00.00" );
          else if ( strlen(bind_array[i]) <= 14 )
            strcat( bind_array[i], ":00:00.00" );
          else if ( strlen(bind_array[i]) <= 17 )
            strcat( bind_array[i], ":00.00" );
          else if ( strlen(bind_array[i]) <= 20 )
            strcat( bind_array[i], ".00" );
  
          /* Set up the descriptor for the date */
          datetime_desc.dsc$b_class   = DSC$K_CLASS_S;
          datetime_desc.dsc$b_dtype = DSC$K_DTYPE_T;
          datetime_desc.dsc$w_length = strlen(bind_array[i]);
          datetime_desc.dsc$a_pointer = bind_array[i];
          if ( (BIND_PTR->SQLVAR[i].SQLDATA = 
                 (SQL_DATE_VMS *) calloc(1,sizeof(SQL_DATE_VMS))) == NULL ){
            iomsg( DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s",
                   "Could not alloc mem for SQLDATA");
            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
            return(GDB_ERROR);
          }
          if ( SYS$BINTIM( &datetime_desc, BIND_PTR->SQLVAR[i].SQLDATA ) 
               != SS$_NORMAL ) {
            iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EDTBVWF);
            return (GDB_ERROR);
          }
          break;

      case TINYINT :         
      case SMALLINT : 
      case INTEGER :
          status = TRUE;
          num.val = BIND_PTR->SQLVAR[i].SQLLEN;
          if (num.bits.scale > 0) {
            /* scale is not zero so we have a float value */
            BIND_PTR->SQLVAR[i].SQLTYPE = FLOAT;
            BIND_PTR->SQLVAR[i].SQLLEN = sizeof(GDB_FLOAT);
            if ( (float_val = calloc(1,sizeof(GDB_FLOAT)) ) == NULL) {
              status = FALSE;
            }
            else {
              *float_val = (float) atof(bind_array[i]); 
              BIND_PTR->SQLVAR[i].SQLDATA = float_val; 
            }
          }
          else {
            /* scale is zero so we have an integer */

            switch (BIND_PTR->SQLVAR[i].SQLTYPE) {
              case TINYINT :
                if ( (short_val = calloc(1,sizeof(GDB_BYTE))) == NULL){
                  status = FALSE;
                }
                else {
                  *short_val = atoi( bind_array[i]);
                  BIND_PTR->SQLVAR[i].SQLDATA = short_val;
                }
                break;
              case SMALLINT :
                if ( (short_val = calloc(1,sizeof(GDB_SHORT))) == NULL){
                  status = FALSE;
                }
                else {
                  *short_val = atoi( bind_array[i]);
                  BIND_PTR->SQLVAR[i].SQLDATA = short_val;
                }
                break;
              case INTEGER :
                if ( (long_val = calloc(1,sizeof(GDB_INT))) == NULL){
                  status = FALSE;
                }
                else {
                  *long_val = atoi( bind_array[i]);
                  BIND_PTR->SQLVAR[i].SQLDATA = long_val;
                }
                break;
            }
            if (!status) {
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
              iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
              return(GDB_ERROR);
            }                  
          }
          break;

      case FLOAT :  /* real, double */       
      case BIGINT :  /* quadword */          
          if ((BIND_PTR->SQLVAR[i].SQLLEN == sizeof(GDB_FLOAT)) &&
              (BIND_PTR->SQLVAR[i].SQLTYPE != BIGINT)) {            

            if ((float_val = calloc(1,sizeof(GDB_FLOAT))) == NULL) {
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
              iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
              return(GDB_ERROR);
            }

            *float_val = (float) atof (bind_array[i]);
            BIND_PTR->SQLVAR[i].SQLDATA = float_val; 
          }
          else { 
            if ((dbl_val = calloc(1,sizeof(GDB_DBL))) == NULL) {
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
              iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
              return(GDB_ERROR);
            }
            *dbl_val =  ( double ) atof ( bind_array[i] );
            BIND_PTR->SQLVAR[i].SQLDATA = dbl_val;   
          }
          break;

      default :
          iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,BIND_PTR->SQLVAR[i].SQLTYPE,i+1);
          return (GDB_ERROR);
          break;
    }

  } /* end for loop */
                      
    
  /* release the bind array */
  for (i=0;i<BIND_PTR->SQLN;i++) {  
    if (bind_array[i] != (char *)NULL)
      free((char *)bind_array[i]);
  }
  if (bind_array != (char **)NULL)
    free ((char **)bind_array);

  *bind_processed = TRUE;
  
  return (GDB_SUCCESS);
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

long sql_describe_output(GENDA* sqlGen, long query_type )
{
  char buff[80];
  char rdb_msg[ STATUS_MSG_LEN];
  int  rdb_msg_len;

  union {
    short val;
    struct {
      short prec  : 8;
      short scale : 8;
    } bits;
  } num;            

  gSQLDA  *SELECT_PTR;
  long     status;
  long     col;
  long     shandle;
  long    *stmt_id;
  long    *ncols;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DESCRIBE_OUTPUT");

  if (sqlGen == NULL) return (GDB_ERROR);
  shandle = sqlGen->stmt_handle ;
  stmt_id = &(sqlGen->stmt_id) ;
  ncols = &(sqlGen->ncols) ;
  if (shandle == 0) return (GDB_ERROR);
  
  SELECT_PTR = sqlda_ptrs[context_num][shandle].sptr; 
    
  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  sprintf(rdb_stmt_id_name,"S%d",shandle);
  
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  /* DESCRIBE should be execute once after PREPARE */
  if( (query_type == GDB_INIT) || (query_type == SELECT) ){
    EXEC SQL DESCRIBE :rdb_stmt_id_name SELECT LIST INTO SELECT_PTR;
    if (SQLCA.SQLCODE < 0) {
      rdb_msg_len = 0;
      rdb_dsc.dsc$b_class = DSC$K_CLASS_S;
      rdb_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
      rdb_dsc.dsc$w_length = STATUS_MSG_LEN;
      rdb_dsc.dsc$a_pointer = rdb_msg;
      SQL$GET_ERROR_TEXT( &rdb_dsc, &rdb_msg_len );
      rdb_msg[rdb_msg_len] = 0;
      iomsg( DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%d%s",
             "DESCRIBE: SQLCODE=% %", SQLCA.SQLCODE, rdb_msg );
      return (GDB_ERROR);
    }        
  } 
  
  if ( SELECT_PTR->SQLD > SELECT_PTR->SQLN) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",ENCOLEX,SELECT_PTR->SQLD,max_col_array_size);
    SELECT_PTR->SQLD = 0; /* set to 0 to avoid dealloc problems */
    return (GDB_ERROR);
  }
                     
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);
  SELECT_PTR->SQLN = SELECT_PTR->SQLD;  /* max items = max items found */
  *ncols = (long)SELECT_PTR->SQLD;

  /* decimal_flags is an array of flags used for tracking which columns are   */
  /* type DECIMAL(x,0) where x >=9.  If we have already allocated it from a   */
  /* prior query, release its memory.  Then, allocate a new array based upon  */
  /* the number of columns we currently have.  XCALLOC initializes all        */
  /* element to 0.                                                            */
  /* ------------------------------------------------------------------------ */
  if (sqlGen->decimal_flags) free(sqlGen->decimal_flags) ;
  sqlGen->decimal_flags = NULL ;
  if (*ncols)
  {
    sqlGen->decimal_flags = XCALLOC(*ncols, sizeof(char)) ;
    if (sqlGen->decimal_flags == NULL)
    {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for decimal_flags array");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }
  }

  /*** realloc SQLDA SQLVAR area to the actual size needed ***/ 
  if ((sqlda_ptrs[context_num][shandle].sptr = SELECT_PTR = (gSQLDA *)realloc(SELECT_PTR,
       sizeof(gSQLDA)+SELECT_PTR->SQLD*sizeof(SQLVAR_STRUCT))) == (gSQLDA *)NULL) {
     iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s",
     "Could NOT realloc memory for gSQLDA select pointer");
     iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINMEMR);
     return (GDB_ERROR);                     
  }
  iomsg(DBGM,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d", "SQLDA memory reallocated for % select-list items",SELECT_PTR->SQLD);                                    
  /*** get datatype of each select item & alloc space ***/
  for (col=0;col<SELECT_PTR->SQLD;col++)
  {
    /* alloc indicator memory */
    if ((SELECT_PTR->SQLVAR[col].SQLIND = (short *)calloc(1,sizeof(short))) == (short *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLIND");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return(GDB_ERROR);
    }

    /*
    ** Check to see if we have a function name.  e.g. COUNT(*).
    ** If so, the descriptor name will be NULL. Set the colname to GDB_UNKNOWN.
    */
    if ( ! SELECT_PTR->SQLVAR[col].SQLNAME_LEN ) {
      strcpy( SELECT_PTR->SQLVAR[col].SQLNAME, GDB_UNKNOWN );
      SELECT_PTR->SQLVAR[col].SQLNAME_LEN = strlen( GDB_UNKNOWN );
    }

    /* Should coerce internal datatypes to desired external here 
       this will reduce the size of the external datatype switch.
       Also reset descriptor length if necessary */

    switch (SELECT_PTR->SQLVAR[col].SQLTYPE)
    {
      case VARCHAR :
      case STRING :
      case CHAR :
          SELECT_PTR->SQLVAR[col].SQLTYPE = STRING;
          SELECT_PTR->SQLVAR[col].SQLLEN+=1;  /* for char type */
          if ((SELECT_PTR->SQLVAR[col].SQLDATA = (char *)calloc(SELECT_PTR->SQLVAR[col].SQLLEN,sizeof(char))) == NULL) {
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
            return(GDB_ERROR);
          }            
          break;                                                 
    
      case DATE :
/*          SELECT_PTR->SQLVAR[col].SQLTYPE = STRING; */ /**** ??????? ******/
          if ((SELECT_PTR->SQLVAR[col].SQLDATA = (char *)
               calloc(DATE_LEN+1,sizeof(char))) == NULL){ 
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
            return(GDB_ERROR);
          }            
          break;

      case TINYINT :         
      case SMALLINT :      
      case INTEGER :         
          num.val = SELECT_PTR->SQLVAR[col].SQLLEN;
          if (num.bits.scale == 0) {
            status = TRUE;
            switch (SELECT_PTR->SQLVAR[col].SQLTYPE) {
              case TINYINT :
                if ((SELECT_PTR->SQLVAR[col].SQLDATA = calloc(1,sizeof(GDB_BYTE))) == NULL)
                  status = FALSE;
                break;
              case SMALLINT :
                if ((SELECT_PTR->SQLVAR[col].SQLDATA = calloc(1,sizeof(GDB_SHORT))) == NULL)
                   status = FALSE;
                break;
              case INTEGER :
                if ((SELECT_PTR->SQLVAR[col].SQLDATA = calloc(1,sizeof(GDB_INT))) == NULL)
                  status = FALSE;
                break;
            }
            if (!status) {
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
              iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
              return(GDB_ERROR);
            }
          }                  

          else {   /* need to deal with all float types */
            SELECT_PTR->SQLVAR[col].SQLTYPE = FLOAT; /* need to coerce for "functions" */
            SELECT_PTR->SQLVAR[col].SQLLEN = sizeof(GDB_DBL);
            if ((SELECT_PTR->SQLVAR[col].SQLDATA = calloc(1,sizeof(GDB_DBL))) == NULL) { 
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
              iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
              return(GDB_ERROR);
            }
          }
          break;

      case FLOAT :  /* real, double */       
      case BIGINT :  /* quadword */          
          if (SELECT_PTR->SQLVAR[col].SQLLEN == sizeof(GDB_FLOAT) && SELECT_PTR->SQLVAR[col].SQLTYPE != BIGINT) {            
            if ((SELECT_PTR->SQLVAR[col].SQLDATA = calloc(1,sizeof(GDB_FLOAT))) == NULL) { 
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
              iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
              return(GDB_ERROR);
            }
          }
          else { 
            if ((SELECT_PTR->SQLVAR[col].SQLDATA = calloc(1,sizeof(GDB_DBL))) == NULL) {
              iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SQLDATA");
              iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
              return(GDB_ERROR);
            }
          }
          break;

      default :
          iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,SELECT_PTR->SQLVAR[col].SQLTYPE,col+1);
          return (GDB_ERROR);
          break;
    }
  }            
  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_open_cursor
    - open the 'declared' cursor
    - cursors must be opened prior to executing a 'fetch'
  
    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/

long sql_open_cursor( curs_name, shandle )
    char  *curs_name;
    long   shandle;
{
  int row_size;
  gSQLDA  *BIND_PTR;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_OPEN_CURESOR");
    
  BIND_PTR = sqlda_ptrs[context_num][shandle].bptr;

  if (shandle == 0 || curs_name == (char *)NULL)
    return (GDB_ERROR);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  row_size =  context[context_num].genda_rows+1;
  
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  /* set number of rows fetched to zero */
  row_count[context_num] = 0;

  /* syntax OPEN <cursor> USING DESCRIPTOR <descriptor> is only required
     if using input (bind) host variables */ 

  if(BIND_PTR->SQLN > 0) 
    EXEC SQL OPEN :curs_name USING DESCRIPTOR BIND_PTR;
  else 
    EXEC SQL OPEN :curs_name;  

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_fetch
    - fetch a database row into the defined descriptor
    - 'get descriptor' must be used to extract row from descriptor
    
    Arguments:
    - curs_name: cursor name
    - shandle: statment handle
  ======================================================================*/

long sql_fetch( curs_name, shandle )
    char  *curs_name;
    long   shandle;
{
  gSQLDA  *SELECT_PTR;
  long retry=0;
  long     col;
  long     n;

  context_num = gsi_current_context();

  if (shandle == 0) return (GDB_ERROR);

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_FETCH: %",curs_name);

  SELECT_PTR = sqlda_ptrs[context_num][shandle].sptr;

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  /* Init the count */
  SQLCA.SQLERRD[2] = 0;

  EXEC SQL FETCH :curs_name USING DESCRIPTOR SELECT_PTR;     

  if (SQLCA.SQLCODE < 0){ 
    sql_open_cursor(curs_name,shandle);     
    if (SQLCA.SQLCODE != 0) return (GDB_EXT_ERROR);
    EXEC SQL FETCH :curs_name USING DESCRIPTOR SELECT_PTR;
  }

  if (SQLCA.SQLCODE < 0 ) {
    return (GDB_EXT_ERROR);
  }
  else {  
    if (SQLCA.SQLCODE != DB_END_OF_CURSOR)
      row_count[context_num] = SQLCA.SQLERRD[2];
  }

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
  gSQLDA  *BIND_PTR;
  gSQLDA  *SELECT_PTR;
  long     col;

  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DEALLOC_DESCRIPTORS");

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);


  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  if ( action == BIND ) {
    if (debug & DBG6)
      iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s","- bind");
    
    BIND_PTR = sqlda_ptrs[context_num][shandle].bptr;

    if (BIND_PTR ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

    sql_release_bind( shandle, action );

    if (BIND_PTR != (gSQLDA *)NULL) {
      free((gSQLDA *)BIND_PTR);
      BIND_PTR = (gSQLDA *)NULL;
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","BIND Descriptor Memory Deallocated");
    }
    sqlda_ptrs[context_num][shandle].bptr = (gSQLDA *)NULL;

  }

  if (action == SELECT) {
    if (debug & DBG6)
      iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s","- select");

    SELECT_PTR = sqlda_ptrs[context_num][shandle].sptr;

    if (SELECT_PTR ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

    sql_release_bind( shandle, action );

    if (SELECT_PTR != (gSQLDA *)NULL) {
      free((gSQLDA *)SELECT_PTR);
      SELECT_PTR = (gSQLDA *)NULL;
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","SELECT Descriptor Memory Deallocated");
    }
    sqlda_ptrs[context_num][shandle].sptr = (gSQLDA *)NULL;

  }   
  
  return (GDB_SUCCESS);
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
  register long    col;
  gSQLDA  *SELECT_PTR;
  gSQLDA  *BIND_PTR;
  dSQLDA  *desc_ptr;
  long     status = 0;    

  context_num = gsi_current_context();


  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_RELEASE_BIND");

  if (shandle == 0) return (GDB_ERROR);

  if (action == BIND) {
    BIND_PTR = sqlda_ptrs[context_num][shandle].bptr;
    desc_ptr = dsqlda_ptrs; 
    if (BIND_PTR ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

    for (col=0;col<BIND_PTR->SQLN;col++) {

      /* deallocate the NULL indicator and data members of the BIND_PTR */ 
      free(BIND_PTR->SQLVAR[col].SQLIND);
      BIND_PTR->SQLVAR[col].SQLIND = (short *)NULL;  

      switch( BIND_PTR->SQLVAR[col].SQLTYPE)
      {
        case VARCHAR:
        case STRING :
        case CHAR :  
        case DATE : 
          if ( BIND_PTR->SQLVAR[col].SQLDATA != (char *)NULL) {
            free((char*)BIND_PTR->SQLVAR[col].SQLDATA );
            BIND_PTR->SQLVAR[col].SQLDATA = (char *)NULL;
          }       

          if ( desc_ptr[col].data != (char *)NULL) {
            free((char*)desc_ptr[col].data );
            desc_ptr[col].data = (char *)NULL;
          }       

          break;
        case TINYINT :         
        case SMALLINT :
        case INTEGER :
        case FLOAT :  /* real, double */       
        case BIGINT :  /* quadword */     
          if ( BIND_PTR->SQLVAR[col].SQLDATA != NULL) {
            free(BIND_PTR->SQLVAR[col].SQLDATA );
            BIND_PTR->SQLVAR[col].SQLDATA = NULL;
          }
          if ( desc_ptr[col].data != NULL) {
            free(desc_ptr[col].data );
            desc_ptr[col].data = NULL;
          }      
          break;
      }
    } /* end loop */      
  }  /* end action BIND */
   
  if (action == SELECT) { 
    SELECT_PTR = sqlda_ptrs[context_num][shandle].sptr;

    if (SELECT_PTR ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

    for (col=0;col<SELECT_PTR->SQLN;col++) {   

      /* deallocate the NULL indicator and data members of the SELECT_PTR */ 
      if (SELECT_PTR->SQLVAR[col].SQLIND != (short *)NULL) {
        free(SELECT_PTR->SQLVAR[col].SQLIND);
      SELECT_PTR->SQLVAR[col].SQLIND = (short *)NULL;  
      }
      switch( SELECT_PTR->SQLVAR[col].SQLTYPE)
      {
        case VARCHAR:
        case STRING :
        case CHAR :  
        case DATE : 
          if ( SELECT_PTR->SQLVAR[col].SQLDATA != (char *)NULL) {
           
            free((char*)SELECT_PTR->SQLVAR[col].SQLDATA );
            SELECT_PTR->SQLVAR[col].SQLDATA = (char *)NULL;
          }
          break;
        case TINYINT :         
        case SMALLINT :
        case INTEGER :
        case FLOAT :  /* real, double */       
        case BIGINT :  /* quadword */     
          if ( SELECT_PTR->SQLVAR[col].SQLDATA != NULL) {
            free(SELECT_PTR->SQLVAR[col].SQLDATA );
            SELECT_PTR->SQLVAR[col].SQLDATA = NULL;
          }
          break;
      }
    }       
   }/* end action SELECT */

   return (GDB_SUCCESS);
  
}
/*======================================================================
  sql_close_cursor
    - close a previously opened cursor

    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/

long sql_close_cursor( curs_name, shandle, release_cursor )
    char  *curs_name;
    long   shandle;
    long  release_cursor; /* Not used by RDB */
{
  context_num = gsi_current_context();

  if (shandle == 0) return (GDB_ERROR);

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_CLOSE_CURSOR: %",curs_name);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL CLOSE :curs_name;

  if (SQLCA.SQLCODE < 0) {
    iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not close cursor %",curs_name);
    return (GDB_EXT_ERROR);
  }

  return (GDB_SUCCESS);
}                                             


/*======================================================================
  sql_disconnect
    - disconnect from the database
  ======================================================================*/

long sql_disconnect( this_context )
  gsi_int  this_context;
{
  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DISCONNECT");

  /** set context connection name **/
  sprintf(connect_name,"DB%d",this_context);
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL DISCONNECT :connect_name;

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_exec_sql
    - process non-query
    - statement must not contain 'select'
    - sql statement is passed directly to database 'as is'

    Arguments:
    - stmt_str: non-select sql statement
  ======================================================================*/

long sql_exec_sql( stmt_str )
    char    *stmt_str;
{ 
  context_num = gsi_current_context();

  if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_SQL");

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL EXECUTE IMMEDIATE :stmt_str;
  row_count[context_num] = SQLCA.SQLERRD[2];
  
  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
  gSQLDA *BIND_PTR;

  context_num = gsi_current_context();

  if (debug &DBG1)                                           
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_DYNAMIC_SQL");

  if (shandle == 0) return (GDB_ERROR);

  BIND_PTR = sqlda_ptrs[context_num][shandle].bptr;  

  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);
  sprintf(rdb_stmt_id_name,"S%d",shandle);

  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL EXECUTE :rdb_stmt_id_name USING DESCRIPTOR BIND_PTR;
  row_count[context_num] = SQLCA.SQLERRD[2];

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}



/*======================================================================
  sql_commit
    - commit (and end) the transaction
  ======================================================================*/

long sql_commit()
{
  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_COMMIT");


  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL COMMIT;

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_rollback
    - rollback (and end) the transaction
  ======================================================================*/

long sql_rollback()
{
  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_ROLLBACK");

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL ROLLBACK; 

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_refresh_cursor
    - reposition the cursor pointer to the first row in the cursor

    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/

long sql_refresh_cursor( curs_name, shandle )
    char  *curs_name;
    long   shandle;
{
  context_num = gsi_current_context();
  
  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_REFRESH: %",curs_name);

  /* To indicate a refreshed cursor set row_count to 0 */
  row_count[context_num] = 0;

  sql_close_cursor(curs_name,shandle,FALSE);
  sql_open_cursor(curs_name,shandle);
  

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
  context_num = gsi_current_context();

  if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_RELEASE");

  if (stmt_id == NULL || *stmt_id == 0) {
      EXEC SQL RELEASE :rdb_stmt_id_name;   
      if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);
      return (GDB_ERROR);
  }
  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  sprintf(rdb_stmt_id_name,"S%d",*stmt_id);
  
  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  EXEC SQL RELEASE :rdb_stmt_id_name;  /* free the 'prepare'  resources */ 
  *stmt_id = 0;

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_exec_stored_proc
    - execute a database stored procedure that does not return any 
      arguments.

    Arguments:
    - sql_stmt: call to database stored procedure
  ======================================================================*/

long sql_exec_stored_proc( sql_stmt )
    char    *sql_stmt;
{
  long  len;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_STORED_PROC");

  /* Nothing special about calling stored procedures in Rdb, so simply
     pass the stored procedure call to exec-sql to provide compatibility */

  sql_exec_sql (sql_stmt);

  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_exec_stored_proc_return
    - execute a fixed stored procedure that returns 1 argument
    - Not used in RDB bridge

    Arguments:
    - string,string: Only have meaning to database developer
 ======================================================================*/

long sql_exec_stored_proc_return( proc_name, proc_args, proc_ret_val )
    char    *proc_name;
    char    *proc_args;
    char    *proc_ret_val;
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
  char rdb_sql_stmt[60] = 
    "delete from RDB$DATABASE where RDB$FILE_NAME is NULL";

  context_num = gsi_current_context();
  
  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_PING_DB");
   
 /* set context connection name */
  sprintf( connect_name, "DB%d",context_num );

  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);  

  EXEC SQL EXECUTE IMMEDIATE :rdb_sql_stmt;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  exec sql ROLLBACK;      /****** ?????????????? ****/
   
  return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}

/*======================================================================
  sql_trigger
    Arguments:  
    - trigger-name: name of trigger or pipe to listen on
    - trigger-timeout: seconds to wait for message
  ======================================================================*/

long sql_trigger( trig_name, trig_timeout, trig_ret_msg, context_num )
  char    *trig_name;
  long     trig_timeout;
  char    *trig_ret_msg;
  gsi_int  context_num;
{
  int     len;
  char    test_trig_name[RDB_MAX_TRIGGER_NAME_LEN+1];
  char    t_msg[201];
  char    t_datetime[31];
  long    ret_value;
  short   record_found = FALSE;
  static  short first_time = TRUE;
  static  gSQLDA  *SQLDA_PM, *SQLDA_SL;
  static  char *  sel_sql_str =
"SELECT trig_msg, trig_datetime FROM g2_triggers_tbl WHERE trig_datetime = (SELECT MIN(trig_datetime) FROM g2_triggers_tbl WHERE trig_name = ?)";
  static  char *  del_sql_str =
"DELETE FROM g2_triggers_tbl WHERE trig_datetime = (SELECT MIN(trig_datetime) FROM g2_triggers_tbl WHERE trig_name = ?)";

  /* CAUTION: context_num is passed from L1 as we are outside of
     run-loop during check (i.e. not within a context). Therefore
     you MUST NOT call any other function that utilizes a context
     number derived from gsi_current_context() */

  len = strlen(trig_name);
  if (len > RDB_MAX_TRIGGER_NAME_LEN) {
    return (GDB_ERROR);
  }

  strcpy( test_trig_name, trig_name );

  /* set context connection name */
  sprintf( connect_name, "DB%d",context_num );

  EXEC SQL SET CONNECT :connect_name;
  if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

  if ( first_time ) {
    /* Allocate SQLDA structures */

    /* 1 input parameter */
    SQLDA_PM = (gSQLDA *)calloc( 1, sizeof(gSQLDA) + 1*sizeof(SQLVAR_STRUCT) );
    SQLDA_PM->SQLN = 1;

    /* 2 output columns */
    SQLDA_SL = (gSQLDA *)calloc( 1, sizeof(gSQLDA) + 2*sizeof(SQLVAR_STRUCT) );
    SQLDA_SL->SQLN = 2;

    EXEC SQL PREPARE stmt_id FROM :sel_sql_str;
    if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

    /* Describe parameter marker */
    EXEC SQL DESCRIBE stmt_id MARKERS INTO SQLDA_PM;
    if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

    /* Set up the input parameter */
    SQLDA_PM->SQLN = SQLDA_PM->SQLD;
    SQLDA_PM->SQLVAR[0].SQLIND = (short *)calloc(1,sizeof(short) );
    SQLDA_PM->SQLVAR[0].SQLIND = 0;
    SQLDA_PM->SQLVAR[0].SQLTYPE = STRING;
    ++SQLDA_PM->SQLVAR[0].SQLLEN;

    /* Describe select list */
    EXEC SQL DESCRIBE stmt_id SELECT LIST INTO SQLDA_SL;
    if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

    /* Setup select list to receive values */
    SQLDA_SL->SQLN = SQLDA_SL->SQLD;
    SQLDA_SL->SQLVAR[0].SQLIND = (short *)calloc(1,sizeof(short) );
    SQLDA_SL->SQLVAR[0].SQLTYPE = STRING;
    SQLDA_SL->SQLVAR[0].SQLLEN+=1;
    SQLDA_SL->SQLVAR[0].SQLDATA = (char *)
      calloc(SQLDA_SL->SQLVAR[0].SQLLEN+1,sizeof(char) );

    SQLDA_SL->SQLVAR[1].SQLIND = (short *)calloc(1,sizeof(short) );
    SQLDA_SL->SQLVAR[1].SQLTYPE = STRING;
    SQLDA_SL->SQLVAR[1].SQLLEN = 24;
    SQLDA_SL->SQLVAR[1].SQLDATA = (char *)
      calloc(SQLDA_SL->SQLVAR[1].SQLLEN+1,sizeof(char) );
                              
    /* Declare the Cursor */
    EXEC SQL DECLARE curs_name CURSOR FOR stmt_id;
    if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

    /* Prepare the delete statement */
    EXEC SQL PREPARE del_id FROM :del_sql_str;
    if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

    first_time = FALSE;
  }

  /* Set up input parameter */
  SQLDA_PM->SQLVAR[0].SQLDATA = (char *)
                               calloc(strlen(test_trig_name)+1,sizeof(char) );
  strcpy( SQLDA_PM->SQLVAR[0].SQLDATA, test_trig_name );

  /* Open the Cursor */
  EXEC SQL OPEN curs_name USING DESCRIPTOR SQLDA_PM;
  if (SQLCA.SQLCODE < 0) {
    free( SQLDA_PM->SQLVAR[0].SQLDATA );
    return (GDB_EXT_ERROR);
  }

  /* Fetch result */
  record_found = FALSE;
  EXEC SQL FETCH curs_name USING DESCRIPTOR SQLDA_SL;

  if ( ! SQLCA.SQLCODE ) {
    record_found = TRUE;
    /* Get the results */
    strncpy( t_msg, SQLDA_SL->SQLVAR[0].SQLDATA, SQLDA_SL->SQLVAR[0].SQLLEN );
    t_msg[SQLDA_SL->SQLVAR[0].SQLLEN] = 0;

    strncpy( t_datetime, SQLDA_SL->SQLVAR[1].SQLDATA, SQLDA_SL->SQLVAR[1].SQLLEN );
    t_datetime[SQLDA_SL->SQLVAR[1].SQLLEN] = '\0';

    sprintf( trig_ret_msg, "%s <%s>", t_msg, t_datetime );
  }
  else if ( SQLCA.SQLCODE == DB_END_OF_CURSOR ) {
    *trig_ret_msg = 0;
    ret_value = GDB_SUCCESS;
  }
  else {
    /*
    ** The following prevents a continuous loop in check_triggers
    ** (never returning to gsi_run_loop) if the database connection
    ** gets dropped.
    */
    *trig_ret_msg = 0;
    if (context[context_num].console_output) {
      if (context[context_num].name != (char *)NULL)
        printf("G2-%s: %s: %s: %d %s\n",DB_TYPE, context[context_num].name,
                ERROR_SYM, SQLCA.SQLCODE, SQLCA.SQLERRM.SQLERRMC);
      else
        printf("G2-%s: %d: %s: %d %s\n",DB_TYPE, context_num, ERROR_SYM,
                SQLCA.SQLCODE, SQLCA.SQLERRM.SQLERRMC);
    }
    ret_value = GDB_EXT_ERROR ;
  }
  
  /* Close the cursor */
  EXEC SQL CLOSE curs_name;
  if (SQLCA.SQLCODE < 0) { 
    free( SQLDA_PM->SQLVAR[0].SQLDATA );
    return (GDB_EXT_ERROR);
  }

  if ( record_found ) {
    EXEC SQL EXECUTE del_id USING DESCRIPTOR SQLDA_PM;
    free( SQLDA_PM->SQLVAR[0].SQLDATA );
    if (SQLCA.SQLCODE < 0) return (GDB_EXT_ERROR);

    EXEC SQL COMMIT;
    ret_value = (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
  
  }
  else { /* no record found */
    free( SQLDA_PM->SQLVAR[0].SQLDATA );
    EXEC SQL ROLLBACK;
    ret_value = (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
  }

  return (ret_value);

}

/*======================================================================
  sql_poll_check
    - called each time through gsi run-loop.
    - Not used at this time by the RDB bridge
 ======================================================================*/

long sql_poll_check( void )
{
  return (GDB_SUCCESS);
}

/*======================================================================
  sql_exec_sql_obj
    Arguments:
    - shandle: the statement handle
    - array_size: the number of rows to be inserted or updated
  ======================================================================*/

long sql_exec_sql_obj( shandle, array_size, stmt_id )
    long   shandle;
    long   array_size;
    long   stmt_id;
{
    long        row,col;
    gSQLDA     *BIND_PTR;  
    dSQLDA      *desc_ptr;
    int         descnt;
    short       ind_val;
    char        *text_val=0;
    char        date_val[DATE_LEN+1];
    long        long_val;
    short       short_val;
    float       float_val;
    double      dbl_val;
    long        *switch_to_float;
    short       keep_sqltype;
    short       keep_sqllen;
    struct dsc$descriptor_s datetime_desc;

    union {
      short val;
      struct {
        short prec  : 8;
        short scale : 8;
      } bits;
    } num;            
                            
    context_num = gsi_current_context();

    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_SQL_OBJ");

    if (shandle == 0) return (GDB_ERROR);

    BIND_PTR = sqlda_ptrs[context_num][shandle].bptr;

    desc_ptr = dsqlda_ptrs; 
    
    /* set context connection name */
    sprintf(connect_name,"DB%d",context_num);

    sprintf(rdb_stmt_id_name,"S%d",shandle);

    EXEC SQL SET CONNECT :connect_name;
    if (SQLCA.SQLCODE  < 0 ) return( GDB_EXT_ERROR );

    descnt = BIND_PTR->SQLD;
    BIND_PTR->SQLN = BIND_PTR->SQLD;

    /* 
    ** allocate an array that keeps track of whether the database column
    ** is an integer type that needs a float value  e.g. INTEGER(2)
    */
    if ((switch_to_float = calloc(descnt,sizeof(GDB_INT))) == NULL){   
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for Switch array");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return(GDB_ERROR);
    }
     
    row_count[context_num] = 0;
    for (row=0; row<array_size; row++) {
    
      for (col=0; col<descnt;col++) {
        /*BIND_PTR->SQLVAR[col].SQLIND =  &( (short) desc_ptr[col].ind[row] ); */
        BIND_PTR->SQLVAR[col].SQLIND =  &( desc_ptr[col].ind[row] ); 

        if ( switch_to_float[col] ) {
          /* put the type and length back to the original values */
          BIND_PTR->SQLVAR[col].SQLTYPE = keep_sqltype;
          BIND_PTR->SQLVAR[col].SQLLEN = keep_sqllen;
        }

        switch (BIND_PTR->SQLVAR[col].SQLTYPE)
        {
          case VARCHAR :
          case STRING :
          case CHAR :
            if ( row == 0 ) { 
              /* First time through set the datatype and length */
              BIND_PTR->SQLVAR[col].SQLTYPE = STRING;
              ++BIND_PTR->SQLVAR[col].SQLLEN;
            }
 
            text_val = (char *) (desc_ptr[col].data[row]);   
            BIND_PTR->SQLVAR[col].SQLDATA = (char *) text_val;
            break;                                                 

          case DATE :

            strcpy(date_val, (char *) (desc_ptr[col].data[row]) );
            /*
            ** Kluge!
            ** append zeroes to end of date if necessary
            ** If you don't do this, the date will have garbage at the end. 
            */
            if ( strlen(date_val) <= 11 )
              strcat( date_val, " 00:00:00.00" );
            else if ( strlen(date_val) <= 14 )
              strcat( date_val, ":00:00.00" );
            else if ( strlen(date_val) <= 17 )
              strcat( date_val, ":00.00" );
            else if ( strlen(date_val) <= 20 )
              strcat( date_val, ".00" );
  
            /* Set up the descriptor for the date */
            datetime_desc.dsc$b_class   = DSC$K_CLASS_S;
            datetime_desc.dsc$b_dtype = DSC$K_DTYPE_T;
            datetime_desc.dsc$w_length = strlen(date_val);
            datetime_desc.dsc$a_pointer = date_val;
            if ( BIND_PTR->SQLVAR[col].SQLDATA == NULL ) {
              if ( (BIND_PTR->SQLVAR[col].SQLDATA = 
                   (SQL_DATE_VMS *) calloc(1,sizeof(SQL_DATE_VMS))) == NULL ){
                iomsg( DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s",
                       "Could not alloc mem for SQLDATA");
                iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
                free ( switch_to_float );   
                return(GDB_ERROR);
              }
            }
            if ( SYS$BINTIM( &datetime_desc, BIND_PTR->SQLVAR[col].SQLDATA ) 
                             != SS$_NORMAL ) {
              iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d",EDTBVWF);
              free ( switch_to_float );   
              return (GDB_ERROR);
            }
            break;

          case INTEGER :
            if ( row == 0 ) {
              num.val = BIND_PTR->SQLVAR[col].SQLLEN;
              if (num.bits.scale > 0) {
                switch_to_float[col] = TRUE;
                keep_sqltype = BIND_PTR->SQLVAR[col].SQLTYPE;
                keep_sqllen = BIND_PTR->SQLVAR[col].SQLLEN;
              } 
              else {
                switch_to_float[col] = FALSE;
              }
            }

            if ( ! switch_to_float[col] ) {
              /* scale is zero so we have an integer */
              BIND_PTR->SQLVAR[col].SQLDATA = 
                  &( ((long *)desc_ptr[col].data)[row] );
                  /*&( (long)((long *)desc_ptr[col].data)[row] );*/
            }
            else {
              /* scale is not zero so we have a float value */
              BIND_PTR->SQLVAR[col].SQLTYPE = FLOAT;
              BIND_PTR->SQLVAR[col].SQLLEN = sizeof(GDB_DBL);
              BIND_PTR->SQLVAR[col].SQLDATA = 
                  &( ((double *)desc_ptr[col].data)[row] );
                  /*&( (double)((double *)desc_ptr[col].data)[row] );*/
            }
            break;

          case TINYINT :         
          case SMALLINT : 
            if ( row == 0 ) {
              num.val = BIND_PTR->SQLVAR[col].SQLLEN;
              if (num.bits.scale > 0) {
                switch_to_float[col] = TRUE;
                keep_sqltype = BIND_PTR->SQLVAR[col].SQLTYPE;
                keep_sqllen = BIND_PTR->SQLVAR[col].SQLLEN;
              } 
              else {
                switch_to_float[col] = FALSE;
              }
            }

            if ( ! switch_to_float[col] ) {
              /* scale is zero so we have a short */
              BIND_PTR->SQLVAR[col].SQLDATA = 
                  &( ((long *)desc_ptr[col].data)[row] );
            }
            else {
              /* scale is not zero so we have a float value */
              BIND_PTR->SQLVAR[col].SQLTYPE = FLOAT;
              BIND_PTR->SQLVAR[col].SQLLEN = sizeof(GDB_FLOAT);

              /*float_val = (float)((double *)desc_ptr[col].data)[row];*/
              BIND_PTR->SQLVAR[col].SQLDATA = 
                  &( ((double *)desc_ptr[col].data)[row] );
            }
            break;

          case FLOAT :        
          case BIGINT :        
            if (BIND_PTR->SQLVAR[col].SQLLEN == sizeof(GDB_FLOAT)&&BIND_PTR->SQLVAR[col].SQLTYPE != BIGINT) {            
              BIND_PTR->SQLVAR[col].SQLDATA = 
                  &( ((double *)desc_ptr[col].data)[row] );
            }
            else { 
              BIND_PTR->SQLVAR[col].SQLDATA = 
                  &( ((double *)desc_ptr[col].data)[row] );
            }
            break;

          default :
            iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,BIND_PTR->SQLVAR[col].SQLTYPE,col+1);
            free ( switch_to_float );   
            return (GDB_ERROR);
            break;
        } 
      } /* end for col loop */

      EXEC SQL EXECUTE :rdb_stmt_id_name USING DESCRIPTOR BIND_PTR;

      if (SQLCA.SQLCODE < 0) {
        free ( switch_to_float );   
        return (GDB_EXT_ERROR);
      }

      /* Keep track of the number of rows */
      row_count[context_num] += SQLCA.SQLERRD[2];

    } /* end for row loop */

    free ( switch_to_float );   
                      
    return (SQLCA.SQLCODE < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}  

/* ========================================================================== */
/*                                                                            */
/*                      The RDB Bridge does not use DSNs                      */
/*                                                                            */
/* ========================================================================== */
long    sql_uses_DSNs()
{
    return 0;
}


/* ========================================================================== */
/*                                                                            */
/*                           sql_configure_DSN                                */
/*                          ** NOT SUPPORTED **                               */
/*                                                                            */
/* ========================================================================== */
long    sql_configure_DSN(gsi_int action, gsi_char* DrvrName, 
                          gsi_item* pKVStruct, gsi_int *piCode, char** pDSNName )
{
    return ENODSNS ;
}
