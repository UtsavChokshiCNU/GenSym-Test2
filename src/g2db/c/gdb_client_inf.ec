/*================================================================
 *  GDB_CLIENT_INF.EC    - GDB Layer-3  (Informix-7.23)   [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-3 = gdb_client_inter_inf.c + gdb_client_inf.ec
 *    - performs all calls to database
 *    - extracts data from SQLDA and inserts into GENDA
 *    - upper layers should check status
 *    - only layer requiring pre-compilation (ESQL)
 *================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gdb_client_inf.h"
#include "gdb_client_inter_inf.h"
#include "gdb_globals.h"
#include "gdb_messages.h"
#include "gsi_main.h"
#include "gdb_context.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#include "gdb_g2_client.h"

#define LAYER LAYER3

EXEC SQL INCLUDE SQLCA;
EXEC SQL INCLUDE SQLDA;
EXEC SQL INCLUDE DECIMAL;

#ifdef WindowsNT
#include "sqlproto.h"
#endif
             
EXEC SQL BEGIN DECLARE SECTION; 
  char          *inf_sql_stmt;
  char           inf_curs_name[MAX_DCURS_LEN+1];
  char           inf_stmt_id_name[5];
  char           connect_name[5];          /* DBxxx = MUST BE GLOBAL */
  char           inf_descriptor_name[6];
   /* NOTE:
  ** The descriptors are given names in the bridge based on whether they are
  ** used as input descriptors or output descriptors.
  ** Descriptors for output (select) variables have names prefixed with 'SD'
  ** Descriptors for input (bind) variables have names prefixed with 'BD'
  */
  short    bind_count;/* because informix does not support bind variable count*/
EXEC SQL END DECLARE SECTION;

extern SQLDA_PTRS *sqlda_ptrs[MAX_GDB_CONTEXTS];

/* extern globals */
extern gSQLCA   *gsqlca;
extern long      debug;

/* context-sensitive globals */
extern CONTEXT_INFO context[MAX_GDB_CONTEXTS];
extern SQLDA_PTRS  *sqlda_ptrs[MAX_GDB_CONTEXTS];
extern long         row_count[MAX_GDB_CONTEXTS];  /* because INF doesn't report row #'s */
extern long         max_col_array_size;          


/* to avoid rollback infinite loops */
EXEC SQL WHENEVER SQLERROR   CONTINUE;
EXEC SQL WHENEVER SQLWARNING CONTINUE;

long     SQLCODE;  /* required for ANSI mode */
gsi_int  context_num;

typedef struct COL_STRUCT {
  int        ncols;
  COL_DATA  *col_data;
} COL_STRUCT;


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
  gsqlca = (gSQLCA *)&sqlca;

  return (GDB_SUCCESS);
}


/*======================================================================
  sql_connect
    - establish connection to database

    Arguments:
    - db_user: database username
    - db_pass: database password
    - db_conn_str: database connect string (e.g. <db_name>@<server_name>)
  ======================================================================*/

long sql_connect( db_user,db_pass,db_conn_str )
    char    *db_user;
    char    *db_pass;
    char    *db_conn_str;
{
  EXEC SQL BEGIN DECLARE SECTION;
    char      *inf_user;
    char      *inf_pass;
    char      *conn_str;
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_CONNECT");

  /** username & password **/
  if (db_user == (char *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",ENOUSER);
    return (GDB_ERROR);
  }
  if (db_pass == (char *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",ENOPASS);
    return (GDB_ERROR);
  }
  /** connect str **/
  if (db_conn_str == (char *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",ENOCONS);
    return (GDB_ERROR);
  }

  if ((inf_user = (char *)calloc(strlen(db_user)+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return(GDB_ERROR);
  }
  if ((inf_pass = (char *)calloc(strlen(db_pass)+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    free ((char *)inf_user);
    return(GDB_ERROR);
  }
  if ((conn_str = (char *)calloc(strlen(db_conn_str)+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    free ((char *)inf_user);
    free ((char *)inf_pass);
    return(GDB_ERROR);
  }

  strcpy(inf_user,db_user);
  strcpy(inf_pass,db_pass);
  strcpy(conn_str,db_conn_str);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL CONNECT TO :conn_str AS :connect_name USER :inf_user USING :inf_pass WITH CONCURRENT TRANSACTION;

  free ((char *)inf_user);
  free ((char *)inf_pass);
  free ((char *)conn_str);

  if (sqlca.sqlcode == DB_ALREADY_CONNECTED) {
    iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE,"%d",IDBCONA);
    return (GDB_SUCCESS);
  }

  if (!sqlca.sqlcode) {
    iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE,"%d",IDBCONE);
    return (GDB_SUCCESS);
  }
  
  iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EBADCON);
  return (GDB_EXT_ERROR);
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
  gSQLDA  *select_ptr;
  gSQLDA  *bind_ptr;

  EXEC SQL BEGIN DECLARE SECTION;
    int         ncols;
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1) {
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_ALLOC_DESCRIPTORS");
  }

  if (shandle == 0) return (GDB_ERROR);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  if (action == BIND) {
    ncols = context[context_num].max_bind_vars;

    bind_ptr = (gSQLDA *)NULL;
    if ((bind_ptr = (gSQLDA *)calloc(context[context_num].max_bind_vars,
	     sizeof(gSQLDA))) == (gSQLDA *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EALDESC);
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }   

	/*** store select addr in SQLDA_PTRS array ***/
    if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
      sqlda_ptrs[context_num][shandle].bptr = bind_ptr; 
    else {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT store bind pointer in SQLDA_PTRS");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);                     
    }
	 
    sprintf(inf_descriptor_name,"BD%d",shandle);
  }

  if (action == SELECT) {
    ncols = max_col_array_size;

    /*** alloc 1 descriptor for each db column ***/

    select_ptr = (gSQLDA *)NULL;
    if ((select_ptr = (gSQLDA *)calloc(ncols,sizeof(gSQLDA))) == (gSQLDA *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EALDESC);
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);                     
    }   
    /*** select addr in SQLDA_PTRS array ***/
    if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
      sqlda_ptrs[context_num][shandle].sptr = select_ptr; 
    else {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT store select pointer in SQLDA_PTRS");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }

    sprintf(inf_descriptor_name,"SD%d",shandle);
  }

  EXEC SQL SET CONNECTION :connect_name;
    if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL ALLOCATE DESCRIPTOR :inf_descriptor_name WITH MAX :ncols;

  if (sqlca.sqlcode < 0) {
    iomsg(DBG3|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EALDESC);
    return (GDB_EXT_ERROR);
  }

  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Output (SELECT) Descriptor Memory Allocated");
 
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
    long     shandle;
    long    *stmt_id;
    char    *sql_str;
{
  long  len;
  int      ch   = '?';
  char     *search;
  char     *tmp_search;
   
  context_num = gsi_current_context();

  if (debug & DBG1) {
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_PREPARE");
  }

  if (shandle == 0) return (GDB_ERROR);
  if (*stmt_id != 0) *stmt_id = 0;

  len = strlen(sql_str);
  if ((inf_sql_stmt = (char *)calloc(len+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for inf_sql_stmt");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  strcpy(inf_sql_stmt,sql_str);

  *stmt_id = shandle;
  sprintf(inf_stmt_id_name,"S%d",shandle);
  
  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
  
  EXEC SQL PREPARE :inf_stmt_id_name from :inf_sql_stmt;
  
  if (sqlca.sqlcode < 0) {
    row_count[context_num] = 0;
    *stmt_id = 0; /* stmt_id created dynamically for Informix */
  }
  /* Determine how many bind variables there are */
  if ((search = (char *)calloc(strlen(inf_sql_stmt)+1,sizeof(char))) == (char *)NULL) {
    if (inf_sql_stmt!=(char *)NULL){ 
      free ((char *)inf_sql_stmt);
      inf_sql_stmt = (char*)NULL;
    }
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for search");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  strcpy(search,inf_sql_stmt); 
  tmp_search = search;
  
  bind_count = 0;  
  while(search)
  { 
     search = strchr(search, ch);
     if(search) bind_count++, search++;
  }
    
  if (tmp_search!=(char *)NULL){ 
    free(tmp_search); 
    tmp_search = (char*) NULL;
  }
  search = (char*)NULL;

  if (inf_sql_stmt!=(char *)NULL){ 
      free ((char *)inf_sql_stmt);
      inf_sql_stmt = (char*)NULL;
  }

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
    char    *curs_name;
    long     shandle;
    long    *stmt_id;
{
  
  context_num = gsi_current_context();

  if (debug & DBG1) {
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_DECLARE_CURSOR: %",curs_name);
  }

  if (shandle == 0) return (GDB_ERROR);

  sprintf(inf_stmt_id_name,"S%d",shandle);
  strcpy(inf_curs_name,curs_name);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL DECLARE :inf_curs_name CURSOR FOR :inf_stmt_id_name;

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}

/*======================================================================
  sql_describe_input
    - id all host vars (INPUT VARIABLES) and load into bind descriptor
    - alloc memory for bind vars
    - get values for host bind vars
    - currently not supported
  ======================================================================*/

long sql_describe_input( shandle, bind_vars, stmt_id, bind_processed, action )
  long           shandle;
  BIND_STRUCT   *bind_vars;
  long          *stmt_id;
  long          *bind_processed;
  long           action;
{
  register long     i,bvl;
  gSQLDA  *bind_ptr;
  char   **bind_array = (char **)NULL; 
  char     inf_msg[STATUS_MSG_LEN + 1];
  long     msg_len;

  EXEC SQL BEGIN DECLARE SECTION;
    short		   descnt;
    int  		   col_num;
    short      ind_val;
	char 		  *text_val;
    long       convtype;
    short      dlen;
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DESCRIBE_INPUT");
  
  *bind_processed = FALSE;

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf((char *)connect_name,"DB%d",context_num);

  bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

  if (bind_ptr == (gSQLDA *) NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d",ENOTINI);
    return (GDB_ERROR);
  }

  sprintf( inf_stmt_id_name, "S%d", shandle );
  sprintf( inf_descriptor_name, "BD%d", shandle );  
 
  if ( action == GDB_INIT )
  {
    descnt = bind_count;

    if(descnt > 0) {
     
      if ( descnt > context[context_num].max_bind_vars) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EMBVEXD,descnt,context[context_num].max_bind_vars );
        descnt = 0; /* set to 0 to avoid dealloc problems */
        return (GDB_ERROR);
      }
 
      EXEC SQL SET CONNECTION :connect_name;
      if ( sqlca.sqlcode < 0 ) return( GDB_EXT_ERROR );

      EXEC SQL SET DESCRIPTOR :inf_descriptor_name COUNT = :descnt;
      if (sqlca.sqlcode < 0) {             
        rgetlmsg(sqlca.sqlcode, inf_msg, sizeof(inf_msg), &msg_len);
        inf_msg[msg_len] = 0;
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%d%s",
            "SET DESCRIPTOR: SQLCODE=% %", sqlca.sqlcode, inf_msg );
        return (GDB_ERROR);
      }
    }

    /* If there are no input descriptors, just return success */
    if ( !descnt ) {
	  *bind_processed = TRUE;
	  return ( GDB_SUCCESS );
	 }

    /* Load bind pointer with datatype SQLNCHAR */
    for (i=0,col_num=i+1; i<descnt; i++,col_num++) {
      
      if ((bind_ptr[i].colname = (char *)calloc(strlen(GDB_UNKNOWN)+1,sizeof(char))) == (char *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for bind_ptr.colname");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
        return (GDB_ERROR);
      }

      /*
	  ** Store the values in bind_ptr. data type all set to CHAR 
	  */
      strcpy( bind_ptr[i].colname, GDB_UNKNOWN );
      bind_ptr[i].ncols     = descnt;
      bind_ptr[i].datatype  = SQLCHAR;
      
    }/* end for */

  } /* if ( action == GDB_INIT ) */

  /* Check to see if bind vars are required */
  if ( (!bind_ptr[0].ncols) || (!bind_vars->nBind) ) {
      *bind_processed = TRUE;
    return ( GDB_SUCCESS );
  }

  if (bind_ptr[0].ncols != bind_vars->nBind) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d%d%d",ENUMVAL,bind_vars->nBind,bind_ptr[0].ncols);
    return (GDB_ERROR);  
  }  

  /* allocate array to store input bind variable values */ 
  if ((bind_array = (char **)calloc(bind_ptr[0].ncols,sizeof(char *))) == (char **)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for bind_array");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }

  for (i=0;i<bind_ptr[0].ncols;i++) {
    bvl = strlen(bind_vars->bind_array[i]);
    if ((bind_array[i] = (char *)calloc(bvl+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for bind_array");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      if (bind_array != (char **)NULL)
        free ((char **)bind_array);
      return (GDB_ERROR);
    }      
  }

  iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d","Bind variables processed: %",bind_ptr[0].ncols);

  convtype = SQLNCHAR;
  /* Load bind variables into bind descriptor */
  for (i=0,col_num=i+1; i<bind_ptr[0].ncols; i++,col_num++) {
    strcpy( bind_array[i], bind_vars->bind_array[i] );
   
    /* Set the null indicator */
    text_val = bind_array[i];


    /* Set the null indicator if required */
    /* ---------------------------------- */
    ind_val = INF_NON_NULL_IND;
    if ((context[context_num].set_null_options & 0x2) && 
            ! strcmpci(text_val, context[context_num].set_null_string))
        ind_val = INF_NULL_IND;
    else 
        if ((context[context_num].set_null_options & 0x4) && !strcmpci(text_val,"NULL"))
	        ind_val = INF_NULL_IND;

    if ( ind_val == INF_NULL_IND ) {
	    EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num
           TYPE = :convtype,
           INDICATOR = :ind_val;
    }
    else {
      if (text_val)
        dlen = strlen(text_val) + 1;
      else
        dlen = 0;
	    EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num
           TYPE = :convtype,
           LENGTH = :dlen,
           INDICATOR = :ind_val,
           DATA = :text_val;
    }
	
    if ( sqlca.sqlcode < 0 ){
      rgetlmsg(sqlca.sqlcode, inf_msg, sizeof(inf_msg), &msg_len);
      inf_msg[msg_len] = 0;
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%d%s",
            "SET DESCRIPTOR: SQLCODE=% %", sqlca.sqlcode, inf_msg );
      return (GDB_ERROR);
    }
   
  } /* end for loop */

 
  /* release the bind array */
  for (i=0;i<bind_ptr[0].ncols;i++) {  
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
    - stmt_id: statement id from 'prepare' (na for Informix)
    - ncols: # of columns detected
    - query_type:
        * SELECT = standard sql select statement
        * STORED_PROC = stored procedure (currently not supported)
  ======================================================================*/

long sql_describe_output(GENDA* sqlGen, long query_type )
{
  gSQLDA  *select_ptr;
  long     scol;
  char     inf_msg[STATUS_MSG_LEN + 1];
  long     msg_len;
  long     shandle;
  long    *stmt_id;
  long    *ncols;

   
  EXEC SQL BEGIN DECLARE SECTION;
    int            n;
    int            dcol;
    short          ddatatype;
    short          ddatalen;
    short          dprec;
    short          dscale;
    short          dnullable;
    string         dname[MAX_COLNAME_LEN]; /* cannot dynamically allocate */

  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DESCRIBE_OUTPUT");

  if (sqlGen == NULL) return (GDB_ERROR);
  shandle = sqlGen->stmt_handle ;
  stmt_id = &(sqlGen->stmt_id) ;
  ncols = &(sqlGen->ncols) ;
  if (shandle == 0) return (GDB_ERROR);

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  sprintf(inf_stmt_id_name,"S%d",shandle);
  sprintf(inf_descriptor_name,"SD%d",shandle);

  EXEC SQL DESCRIBE :inf_stmt_id_name USING SQL DESCRIPTOR :inf_descriptor_name;
  if (sqlca.sqlcode <0) {
    rgetlmsg(sqlca.sqlcode, inf_msg, sizeof(inf_msg), &msg_len);
    inf_msg[msg_len] = 0;
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%d%s",
          "DESCRIBE: SQLCODE=% %", sqlca.sqlcode, inf_msg );
    return (GDB_ERROR);
  }

  /* get the actual # of columns */
  EXEC SQL GET DESCRIPTOR :inf_descriptor_name :n = COUNT;
  if (sqlca.sqlcode < 0) {
    rgetlmsg(sqlca.sqlcode, inf_msg, sizeof(inf_msg), &msg_len);
    inf_msg[msg_len] = 0;
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%d%s",
          "GET DESCRIPTOR: SQLCODE=% %", sqlca.sqlcode, inf_msg );
    return (GDB_ERROR);
  }

  if ( n > max_col_array_size /*context[context_num].max_ncols*/) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",ENCOLEX,n,max_col_array_size);
    *ncols = 0; /* set to 0 to avoid dealloc problems */
    return (GDB_ERROR);
  }

  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
  *ncols = (long)n;

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
      return (GDB_ERROR); /* addr of indicator vars */
    }
  }

  /* realloc nSQLDA to the actual n needed */
  if ((sqlda_ptrs[context_num][shandle].sptr = select_ptr = (gSQLDA *)realloc(select_ptr,
       n*sizeof(gSQLDA))) == (gSQLDA *)NULL) {
     iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT realloc memory for SQLDA select pointer");
     iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINMEMR);
     return (GDB_ERROR);                     
  }

  if(debug && DBG6)
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d","SQLDA memory reallocated for % select-list items",n);
	
  for (dcol=1;dcol<n+1;dcol++) {

    EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :dcol 
        :ddatatype   = TYPE,
        :ddatalen    = LENGTH,
        :dprec       = PRECISION,
        :dscale      = SCALE,
        :dnullable   = NULLABLE,
        :dname       = NAME;

    if (sqlca.sqlcode < 0) {
      rgetlmsg(sqlca.sqlcode, inf_msg, sizeof(inf_msg), &msg_len);
      inf_msg[msg_len] = 0;
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%d%s",
            "GET DESCRIPTOR: SQLCODE=% %", sqlca.sqlcode, inf_msg );
      return (GDB_ERROR);
    }

    scol = dcol - 1;

    /* 
    ** check to see if we have a function name. e.g. COUNT(*). 
    ** If so, the descriptor name will bee NULL. Set the col. name to GDB_UNKNOW.
    */
    if( !(strlen(dname)) )
      strcpy( dname, GDB_UNKNOWN);

    if ((select_ptr[scol].colname = (char *)calloc(strlen(dname)+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SP colname");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }
     
    strcpy(select_ptr[scol].colname,dname);
  
    select_ptr[scol].ncols     = (short)n;
    select_ptr[scol].datatype  = ddatatype;
    select_ptr[scol].datalen   = ddatalen;
    select_ptr[scol].prec      = dprec;      
    select_ptr[scol].scale     = dscale; 
    select_ptr[scol].nullable  = dnullable; 
  
    /* this switch is mostly for consistency with other db bridges */
    switch (ddatatype) 
    {
      case INF_DTIME :
          /* datetime always returns a length of 3080. If a smaller buffer size
             is used, this WILL result in memory corruption due to Informix' 
             writing beyond the end of the buffer. */
      case INF_DATE :
          /* date always returns a length of 4 (stored as long in db). Therefore 
             to fetch a date as a string, a buff must be allocated with enough
             space to store a date string of the largest size (128 should do it).*/            
      case INF_INTERVAL :
          select_ptr[scol].datalen = DATE_LEN; 

          if (ddatalen > DATE_LEN) /* hack for 'datetime' datatype */
            select_ptr[scol].datalen = ddatalen;

          select_ptr[scol].datatype = ddatatype = INF_DATE;
          break;

      case INF_VCHAR :
      case INF_CHAR :
          select_ptr[scol].datatype = ddatatype = INF_CHAR;
          break;                                                 

      case INF_SMINT :
      case INF_INTEGER :
      case INF_SERIAL :
      case INF_FLOAT :         
      case INF_SMFLOAT :
      case INF_MONEY :
          break ;

      case INF_DECIMAL :
          sqlGen->decimal_flags[scol] = (char)(dprec >= 9 && dscale == 0) ;
          break;

      default :
          iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,ddatatype,dcol);
          return (GDB_ERROR);
          break;
    }
  }
  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
    char    *curs_name;
    long     shandle;
{
  gSQLDA   *select_ptr;

  EXEC SQL BEGIN DECLARE SECTION;
    int         row_size;
  EXEC SQL END DECLARE SECTION;
  
  context_num = gsi_current_context();

  if (shandle == 0 || curs_name == (char *)NULL)
    return (GDB_ERROR);

  if (debug & DBG1) 
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_OPEN_CURSOR: %",curs_name);

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /* Set the cursor name and bind descriptor name */
  strcpy(inf_curs_name,curs_name);
  sprintf(inf_descriptor_name,"BD%d",shandle);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  row_size = context[context_num].genda_rows+1;

  /* To indicate a refreshed cursor set row_count to 0 */
  select_ptr[0].row_count = row_count[context_num] = 0;

  if(bind_count > 0)
    EXEC SQL OPEN :inf_curs_name USING SQL DESCRIPTOR :inf_descriptor_name; 
  else
    EXEC SQL OPEN :inf_curs_name;
 
  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
    char    *curs_name;
    long     shandle;
{
  gSQLDA   *select_ptr;

  context_num = gsi_current_context();

  if (shandle == 0)
    return (GDB_ERROR);

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_FETCH: %",curs_name);

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /* set context connection name and cursor name */
  sprintf(connect_name,"DB%d",context_num);
  strcpy(inf_curs_name,curs_name);
 
  sprintf(inf_descriptor_name,"SD%d",shandle);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
  EXEC SQL FETCH :inf_curs_name USING SQL DESCRIPTOR :inf_descriptor_name;


  /*** if can't fetch make sure cursor is open and retry ***/
  if (sqlca.sqlcode < 0) {
    sql_open_cursor(curs_name,shandle);
    if (sqlca.sqlcode != 0) return (GDB_EXT_ERROR);
    sprintf(inf_descriptor_name,"SD%d",shandle);
    EXEC SQL SET CONNECTION :connect_name;
    EXEC SQL FETCH :inf_curs_name USING SQL DESCRIPTOR :inf_descriptor_name;
  }

  if (sqlca.sqlcode < 0 ) {
    return (GDB_EXT_ERROR);
  }
  else {
    if (sqlca.sqlcode != DB_END_OF_CURSOR) {
      row_count[context_num] = ++(select_ptr[0].row_count);
    }
  }
 
  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
  gSQLDA  *select_ptr;
  long     status = 0;

  gSQLDA  *bind_ptr;   /* new */

  context_num = gsi_current_context();

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DEALLOC_DESCRIPTORS");

  if (shandle == 0) return (GDB_ERROR);
  
  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);
  
  if ( action == BIND )	{
    if (debug & DBG6)
      iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s","- bind");
    
    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

    if (bind_ptr ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

	sql_release_bind( shandle, action );

    if (bind_ptr != (gSQLDA *)NULL) {
      free((gSQLDA *)bind_ptr);
      bind_ptr = (gSQLDA *)NULL;
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","BIND Descriptor Memory Deallocated");
    }
   
    sqlda_ptrs[context_num][shandle].bptr = (gSQLDA *)NULL;

	/* set the name of the Bind descriptor */
    sprintf( inf_descriptor_name,"BD%d",shandle );
  }

  if (action == SELECT) {
    if (debug & DBG6)
      iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s","- select");

    select_ptr = sqlda_ptrs[context_num][shandle].sptr;

    if (select_ptr ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

	sql_release_bind( shandle, action );

    if (select_ptr != (gSQLDA *)NULL) {
      free((gSQLDA *)select_ptr);
      select_ptr = (gSQLDA *)NULL;
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","SELECT Descriptor Memory Deallocated");
    }

      sqlda_ptrs[context_num][shandle].sptr = (gSQLDA *)NULL;

	/* set the name of the Select descriptor */
    sprintf(inf_descriptor_name,"SD%d",shandle);
  }

  EXEC SQL SET CONNECTION :connect_name;
    if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL DEALLOCATE DESCRIPTOR :inf_descriptor_name;
  if (sqlca.sqlcode < 0) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not deallocate SQLDA for %",inf_descriptor_name);
  }
  

  return (!status ? GDB_SUCCESS : GDB_EXT_ERROR);
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
  register long    col, i;
  gSQLDA  *select_ptr;
  gSQLDA  *bind_ptr;
  long     status = 0;

  context_num = gsi_current_context();


  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_RELEASE_BIND");

  if (shandle == 0) return (GDB_ERROR);

  if (action == BIND) {
    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

    if (bind_ptr ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

    for (col=0;col<context[context_num].max_bind_vars;col++) {

      if (bind_ptr[col].colname != NULL) {
        free(bind_ptr[col].colname);
        bind_ptr[col].colname = NULL;
      }

	  /* deallocate the data and NULL indicator portions of the bind_ptr */
      switch (bind_ptr[col].datatype) 
      {
        case GDB_STRING_TYPE :
          if ( bind_ptr[col].data != NULL) {
	        for ( i=0; bind_ptr[col].data[i] ;i++ ) {
		      free( bind_ptr[col].data[i] );
		      bind_ptr[col].data[i] = NULL;
	        }
            free( bind_ptr[col].data );
            bind_ptr[col].data = NULL;
          }
  	      break;
                                                      
        case GDB_INT_TYPE :
        case GDB_SHORT_TYPE :
        case GDB_LONG_TYPE : 
        case GDB_FLOAT_TYPE : 
        case GDB_DBL_TYPE :    
          if ( bind_ptr[col].data != NULL) {
            free( bind_ptr[col].data );
            bind_ptr[col].data = NULL;
          }
          break;
      }/* end swich */

      if ( bind_ptr[col].ind ) {
        free( bind_ptr[col].ind );
        bind_ptr[col].ind = NULL;
      }
    }

  }

  if (action == SELECT) {
    select_ptr = sqlda_ptrs[context_num][shandle].sptr;

    if (select_ptr ==  (gSQLDA *)NULL)
      return (GDB_SUCCESS);

    for (col=0;col<select_ptr[0].ncols;col++) {
      if (select_ptr[col].colname != (char*) NULL) {
        free(select_ptr[col].colname);
        select_ptr[col].colname = NULL;
      }
    }
  }

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
    char    *curs_name;
    long     shandle;
    long     release_cursor; /* Not used by Informix */
{
  context_num = gsi_current_context();

  if (shandle == 0) return (GDB_ERROR);

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_CLOSE_CURSOR: %",curs_name);
  
  strcpy(inf_curs_name,curs_name);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL CLOSE :inf_curs_name;

  if (sqlca.sqlcode < 0) {
    iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not close cursor %",inf_curs_name);
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
 /* context_num = gsi_current_context();  */

  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DISCONNECT");

  /** set context connection name **/
  sprintf(connect_name,"DB%d",this_context);

  EXEC SQL DISCONNECT :connect_name;

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS); 
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
  long    len;

  context_num = gsi_current_context();


  if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_SQL");

  len = strlen(stmt_str);
  if ((inf_sql_stmt = (char *)calloc(len+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for inf_sql_stmt");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  strcpy(inf_sql_stmt,stmt_str);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL EXECUTE IMMEDIATE :inf_sql_stmt;

  if(inf_sql_stmt != (char*)NULL){
    free ((char *)inf_sql_stmt);
    inf_sql_stmt = (char*)NULL;
  }

  row_count[context_num] = gsqlca->sqlerrd[2];

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);    
}

/*======================================================================
  sql_exec_dynamic_sql
    - process non-query
    - statement must not contain 'select'
    - sql statement is passed directly to database 'as is'

    Arguments:
    - stmt_str: non-select sql statement
    - stmt_id: statement id created by the prepare
  ======================================================================*/

long sql_exec_dynamic_sql( shandle, stmt_id )
    long   shandle;
    long   stmt_id;

{

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_DYNAMIC_SQL");

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);

  /* stmt_id must be a string for Informix */
  sprintf(inf_stmt_id_name,"S%d",shandle);

  /* set the descriptor name */
  sprintf(inf_descriptor_name,"BD%d",shandle);
  
  /* Execute the statement */
  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  if(bind_count == 0)
    EXEC SQL EXECUTE :inf_stmt_id_name;
  else
    EXEC SQL EXECUTE :inf_stmt_id_name USING SQL DESCRIPTOR :inf_descriptor_name;
  
  row_count[context_num] = gsqlca->sqlerrd[2];

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}

/*======================================================================
  sql_commit
    - commit (and end) the transaction
    - commit may only be performed if a 'begin work' has been issued
  ======================================================================*/

long sql_commit()
{
 
  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_COMMIT");


  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL COMMIT WORK;

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}

/*======================================================================
  sql_rollback
    - rollback (and end) the transaction
    - rollback may only be performed if a 'begin work' has been issued
  ======================================================================*/

long sql_rollback()
{
  context_num = gsi_current_context();
  
  if (debug & DBG1) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_ROLLBACK");

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL ROLLBACK WORK;

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_refresh_cursor
    - reposition the cursor pointer to the first row in the cursor

    Arguments:
    - curs_name: cursor name
    - shandle: statement handle
  ======================================================================*/

long sql_refresh_cursor( curs_name, shandle )
    char    *curs_name;
    long     shandle;
{
  gSQLDA  *select_ptr;

  context_num = gsi_current_context();
  
  if (debug & DBG1) {
    if ( curs_name != NULL ) 
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_REFRESH: %",curs_name);
    else
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_REFRESH");
  }

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /* To indicate a refreshed cursor set row_count to 0 */
  select_ptr[0].row_count = row_count[context_num] = 0;

  sql_close_cursor( curs_name, shandle, FALSE );
  if ( sqlca.sqlcode >= 0 )
    sql_open_cursor(curs_name,shandle);

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_release
    - release resources allocated by 'prepare' and 'declare cursor'

    Arguments:
    - stmt_id: statement id from 'prepare' (na for Informix)
  ======================================================================*/

long sql_release( stmt_id )
    long    *stmt_id;
{
  if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_RELEASE");

  /*** Note: stmt_id = shandle for Informix ***/
  if (stmt_id == NULL || *stmt_id == 0){
    EXEC SQL FREE :inf_stmt_id_name;    /* free the 'prepare' resources */
     if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
    EXEC SQL FREE :inf_curs_name;     /* free the 'cursor'  resources */
     if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
    return (GDB_ERROR);
  }

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
  
  /* this method of getting the cursor name is dangerous since cursor name
     creation occurs in L2. It is being done here to avoid changing function
     args for Informix */
  
  sprintf(inf_curs_name,"CURSOR%d_%d",context_num,*stmt_id);
  sprintf(inf_stmt_id_name,"S%d",*stmt_id);

  EXEC SQL FREE :inf_stmt_id_name;  /* free the 'prepare' resources */
    if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
  EXEC SQL FREE :inf_curs_name;     /* free the 'cursor'  resources */
    if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  *stmt_id = 0;

  return (GDB_SUCCESS);
}

/*======================================================================
  sql_exec_stored_proc
    - execute a database stored procedure that does not return any 
      arguments.
    - must perform a 'set chained off' prior to executing this 
      procedure

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

  len = strlen(sql_stmt);

  if ((inf_sql_stmt = (char *)calloc(len+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for syb_sql_stmt");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }

  strcpy(inf_sql_stmt,sql_stmt);
  sprintf(inf_stmt_id_name,"SP_%d",context_num);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL PREPARE :inf_stmt_id_name from :inf_sql_stmt;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL EXECUTE :inf_stmt_id_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);  

  free((char *)inf_sql_stmt);
  
  EXEC SQL free :inf_stmt_id_name;
  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);

}


/*======================================================================
  sql_exec_stored_proc_return
    - execute a fixed stored procedure that returns 1 argument
    - Not used in Informix bridge

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
  EXEC SQL BEGIN DECLARE SECTION;
    long nr;
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_PING_DB");

  /* set context connection name */
  sprintf( connect_name, "DB%d",context_num );

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL SELECT COUNT(*) INTO :nr FROM systables;

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
  
  EXEC SQL BEGIN DECLARE SECTION;
    char   test_trig_name[INF_MAX_TRIGGER_NAME_LEN+1];
    string t_msg[200];
    string t_datetime[30];
  EXEC SQL END DECLARE SECTION;

  /* CAUTION: context_num is passed from L1 as we are outside of
     run-loop during check (i.e. not within a context). Therefore
     you MUST NOT call any other function that utilizes a context
     number derived from gsi_current_context() */

  len = strlen(trig_name);
  if (len > INF_MAX_TRIGGER_NAME_LEN) {
    return (GDB_ERROR);
  }
  
  /* 
  ** Convert trigger's name in G2 to lowercase 
  ** assume the trigger name created by lowercase in the database 
  */
 /* rdownshift(trig_name);   rjf-removed 11/11/97 since G2 uses upcase for symbols */       
  
  strcpy( test_trig_name, trig_name );
   
  /* set context connection name */
  sprintf( connect_name, "DB%d",context_num );
  
  /*
  ** Fetch a row of information for the given trigger name from the
  ** trigger table and then delete that row. Both of these operations
  ** are done in the g2_process_trig_proc procedure
  */
  EXEC SQL SET CONNECTION :connect_name;
   if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL EXECUTE PROCEDURE g2_return_trigger(:test_trig_name) INTO :t_msg,:t_datetime; /* Informix procedure name max. lenght is 18 */
   if ( !sqlca.sqlcode) {
     sprintf( trig_ret_msg, "%s <%s>", t_msg, t_datetime );  
  }
  else if ( sqlca.sqlcode == DB_END_OF_CURSOR ) {
     *trig_ret_msg = 0;
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
                ERROR_SYM, sqlca.sqlcode, sqlca.sqlerrm);
      else
        printf("G2-%s: %d: %s: %d %s\n",DB_TYPE, context_num, ERROR_SYM,
		        sqlca.sqlcode, sqlca.sqlerrm);
    }
    return( GDB_EXT_ERROR );
  }
  return (GDB_SUCCESS);

}

/*======================================================================
  sql_poll_check
    - called each time through gsi run-loop.
    - Not used at this time by the Informix bridge
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
    - stmt_id: statement id created by the prepare
  ======================================================================*/

long sql_exec_sql_obj( shandle, array_size, stmt_id )
    long   shandle;
    long   array_size;
    long   stmt_id;
{
  EXEC SQL BEGIN DECLARE SECTION;
    int          descnt;
    int          col_num;
    short        ind_val;
    short        dlen;
    char        *text_val;
    long         long_val;
    double       float_val;
    long         convtype;
  EXEC SQL END DECLARE SECTION;

  long        row,i;
  gSQLDA     *bind_ptr;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_SQL_OBJ");

  if (shandle == 0) return (GDB_ERROR);

  bind_ptr = sqlda_ptrs[context_num][shandle].bptr;
  
  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);

  /* stmt_id must be a string for Informix */
  sprintf(inf_stmt_id_name,"S%d",shandle);

  /* set the descriptor name */
  sprintf(inf_descriptor_name,"BD%d",shandle);

  /* initialize the row count */
  row_count[context_num] = 0;

  descnt = (long) bind_ptr[0].ncols;

  /* For each row of data, set up the descriptor and then execute the statement */
  for (row=0; row<array_size; row++) {

    for ( i=0,col_num=i+1; i<descnt;  i++,col_num++ ) {

	  /* set the value for null indicator */
	  ind_val = (short) bind_ptr[i].ind[row];

    /* Based on type, the data may need to be converted to CHAR */
    switch ( bind_ptr[i].datatype )
	  {
      case GDB_STRING_TYPE :

        convtype = SQLNCHAR;
        if ( ind_val == INF_NULL_IND ) {
	        EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num
               TYPE = :convtype,
               INDICATOR = :ind_val;
        }
        else {
          text_val = (char *) bind_ptr[i].data[row];
          if (text_val)
            dlen = strlen(text_val) + 1;
          else
            dlen = 0;
	        EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num
               TYPE = :convtype,
               LENGTH = :dlen,
               INDICATOR = :ind_val,
               DATA = :text_val;
        }

        if ( sqlca.sqlcode < 0 ){    
          iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not set descriptor for %",inf_descriptor_name);
          return (GDB_EXT_ERROR);   
        }
	      break;

	    case GDB_INT_TYPE :

        convtype = SQLINT;
        if ( ind_val == INF_NULL_IND ) {
	        EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num
               TYPE = :convtype,
               INDICATOR = :ind_val;
        }
        else {
          long_val = (long) ((long *)bind_ptr[i].data)[row];
          EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num
               DATA = :long_val,
               TYPE = :convtype,      
               INDICATOR = :ind_val;
        }
        if ( sqlca.sqlcode < 0 ){    
          iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not set descriptor for %",inf_descriptor_name);
          return (GDB_EXT_ERROR);   
        }
        break;

	    case GDB_FLOAT_TYPE :
        convtype = SQLDECIMAL;

        if ( ind_val == INF_NULL_IND ) {
	        EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num
               TYPE = :convtype,
               INDICATOR = :ind_val;
        }
        else {
          float_val = (float) ((double *)bind_ptr[i].data)[row];
          EXEC SQL SET DESCRIPTOR :inf_descriptor_name VALUE :col_num 
               DATA = :float_val,
               TYPE = :convtype,           
               INDICATOR = :ind_val;
        }
        if ( sqlca.sqlcode < 0 ){    
          iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not set descriptor for %",inf_descriptor_name);
          return (GDB_EXT_ERROR);   
        }
	      break;

      default :
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,bind_ptr[i].datatype,col_num);
        return (GDB_ERROR);
        break;
    } /* end switch */

    } /* end for column loop */

    /* Execute the statement */
    EXEC SQL SET CONNECTION :connect_name;
    if (sqlca.sqlcode < 0)  return (GDB_EXT_ERROR);
    
    EXEC SQL EXECUTE :inf_stmt_id_name USING SQL DESCRIPTOR :inf_descriptor_name;
    if (sqlca.sqlcode < 0)  return (GDB_EXT_ERROR);
    row_count[context_num]++;
  
  } /* end for row loop */

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);

}


/* ========================================================================== */
/*                                                                            */
/*                    The Informix Bridge does not use DSNs                   */
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


/*======================================================================
  sql_get_sqlda
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

long sql_get_sqlda( tunion,t_ind,col,shandle,datatype )
    TRANS_VALUE *tunion;
    long     *t_ind;
    long      col;
    long      shandle;
    long      datatype;
{
  gSQLDA  *select_ptr;

  EXEC SQL BEGIN DECLARE SECTION;
    int              idx;
    short            ind_val;
    char          *text_val;
    short            short_val;
    int              int_val;
    float            float_val;
    double           dbl_val;
    decimal          decimal_val;
    string           date_val[DATE_LEN];
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  sprintf(inf_descriptor_name,"SD%d",shandle);

  idx = col + 1;
  switch (datatype)
  {
    case INF_CHAR :
    case INF_VCHAR :
    case INF_DTIME :
        if ((text_val = (char *)calloc((select_ptr[col].datalen)+1,sizeof(char))) == (char *)NULL) {
          iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for text_val");
          iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
          return (GDB_ERROR);
        }

      EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :idx 
                              :text_val = DATA,
                              :ind_val  = INDICATOR;
/*      text_val[select_ptr[col].datalen] = 0; */
      strcpy(tunion->t_str,text_val);
      *t_ind  = (long)ind_val;
      if(text_val != (char*) NULL){
        free ((char *)text_val);
        text_val = (char*) NULL;
      }
      break;

    case INF_DATE :
      EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :idx 
                              :date_val = DATA,
                              :ind_val  = INDICATOR;
      strcpy(tunion->t_str,date_val);
      *t_ind  = (long)ind_val;
      break;

    case INF_SMINT :
      EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :idx 
                              :short_val = DATA,
                              :ind_val = INDICATOR;
      tunion->t_short = short_val;
      *t_ind  = (long)ind_val;
      break;

    case INF_INTEGER :
    case INF_SERIAL :
      EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :idx 
                              :int_val = DATA,
                              :ind_val = INDICATOR;
      tunion->t_int = int_val;
      *t_ind  = (long)ind_val;
      break;

    case INF_SMFLOAT :
      EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :idx 
                              :float_val = DATA,
                              :ind_val = INDICATOR;
      tunion->t_float = float_val;
      *t_ind = (long)ind_val;
      break;

    case INF_FLOAT :
      EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :idx 
                              :dbl_val = DATA,
                              :ind_val = INDICATOR;
      tunion->t_dbl = dbl_val;
      *t_ind = (long)ind_val;
      break;

    case INF_DECIMAL :   /* money(p) = decimal(p,2) unless scale is specified */
    case INF_MONEY :     /* money is always a decimal */

      EXEC SQL GET DESCRIPTOR :inf_descriptor_name VALUE :idx 
                              :decimal_val = DATA,
                              :ind_val = INDICATOR;

      /* convert the decimal_val to a double */
      dectodbl(&decimal_val,&dbl_val);

      tunion->t_dbl = dbl_val;
      *t_ind = (long)ind_val;
      break;

    default :
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,datatype,idx);
      return (GDB_ERROR);
      break;
  }

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


