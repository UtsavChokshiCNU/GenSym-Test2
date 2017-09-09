/*===============================================================
 *  GDB_CLIENT_SYB.CP    - GDB Layer-3  (Sybase-10.0.2)   [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-3 = gdb_client_inter_syb.c + gdb_client_syb.cp
 *    - performs all calls to database
 *    - extracts data from SQLDA and inserts into GENDA
 *    - upper layers should check status
 *    - only layer requiring pre-compilation (CPRE)
 *================================================================
 *
 * Precompiler Switches
 * --------------------
 *    -Cansi_c  = ansi C
 *    -O        = input file (.cp) name
 *
 *================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sybhesql.h>          /*<-required for Sybase */
#include <sybtesql.h>          /*<-*/
#include "gdb_client_syb.h"
#include "gdb_client_inter_syb.h"
#include "gdb_globals.h"
#include "gdb_messages.h"
#include "gsi_main.h"
#include "gdb_context.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#include "gdb_g2_client.h"

#define LAYER LAYER3

EXEC SQL INCLUDE SQLCA;

/* Prototype */
/* --------- */
long sql_set_textsize(long limit) ;


EXEC SQL BEGIN DECLARE SECTION;
  char            *syb_sql_stmt;
  char             syb_curs_name[MAX_DCURS_LEN];
  char             syb_stmt_id_name[5];
  char             connect_name[5];

  /* NOTE:
  ** The descriptors are given names in the bridge based on whether they are
  ** used as input descriptors or output descriptors.
  ** Descriptors for output (select) variables have names prefixed with 'SD'
  ** Descriptors for input (bind) variables have names prefixed with 'BD'
  */
  char             syb_descriptor_name[6];

EXEC SQL END DECLARE SECTION;

/* context-sensitive globals */
extern CONTEXT_INFO context[MAX_GDB_CONTEXTS];
extern SQLDA_PTRS  *sqlda_ptrs[MAX_GDB_CONTEXTS];
extern long         row_count[MAX_GDB_CONTEXTS]; /* because SYB doesn't report row #'s */
extern long         max_col_array_size;
/*extern long         force_cursor_close[MAX_GDB_CONTEXTS];
*/

/* globals */
extern gSQLCA      *gsqlca;
extern long         debug;
gsi_int context_num;

/*=================================================
WARNING::connect_name must be defined to the current
context prior to executing ANY EXEC SQL statement,
whether the statement explicitly uses the connect_
name or not. Connect_name is used internally and
is referenced within the precompiler generated C
code.
=================================================*/

/* these are here ONLY to avoid compiler warnings */
EXEC SQL WHENEVER SQLERROR   CONTINUE;
EXEC SQL WHENEVER SQLWARNING CONTINUE;
EXEC SQL WHENEVER NOT FOUND  CONTINUE;

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
  sql_connect  (1)
    - establish connection to database

    Arguments:
    - db_user: database username
    - db_pass: database password
    - db_server: database server name
  ======================================================================*/

long sql_connect( db_user,db_pass,db_server )
    char    *db_user;
    char    *db_pass;
    char    *db_server;
{
  
  EXEC SQL BEGIN DECLARE SECTION;
    char         *sb_user;
    char         *sb_pass;
    char         *sb_server;
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_CONNECT");

  /** username, password, server **/
  if (db_user == (char *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",ENOUSER);
    return (GDB_ERROR);
  }
  if (db_pass == (char *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",ENOPASS);
    return (GDB_ERROR);
  }
#ifdef XXX
  if (db_server == (char *)NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d",ENOCONS);
    return (GDB_ERROR);
  }
#endif

  if ((sb_user = (char *)calloc(strlen(db_user)+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  if ((sb_pass = (char *)calloc(strlen(db_pass)+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  if ((sb_server = (char *)calloc(strlen(db_server)+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  *sb_server = 0;
  strcpy(sb_user,db_user);
  strcpy(sb_pass,db_pass);
  strcpy(sb_server,db_server);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  if (*sb_server == 0)
    EXEC SQL CONNECT :sb_user IDENTIFIED BY :sb_pass AT :connect_name;
  else  
    EXEC SQL CONNECT :sb_user IDENTIFIED BY :sb_pass AT :connect_name USING :sb_server;

  free((char *)sb_user);
  free((char *)sb_pass);
  free((char *)sb_server);

  if (sqlca.sqlcode == DB_ALREADY_CONNECTED) {
    iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE,"%d",IDBCONA);
    return (GDB_SUCCESS);
  }
    
  if (!sqlca.sqlcode) {
    iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE,"%d",IDBCONE);
    if (context[context_num].need_textsize)
        sql_set_textsize(context[context_num].max_text_len) ;
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

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_ALLOC_DESCRIPTORS");

  if (shandle == 0) return (GDB_ERROR);
     
  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  if (action == BIND) {
    ncols = context[context_num].max_bind_vars;

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
	 
    sprintf(syb_descriptor_name,"BD%d",shandle);
  }

  if (action == SELECT) {
    ncols = max_col_array_size; /*context[context_num].max_ncols;*/

    /* alloc 1 descriptor for each db column */

    if ((select_ptr = (gSQLDA *)calloc(ncols,sizeof(gSQLDA))) == (gSQLDA *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%d",EALDESC);
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);                     
    }   
    /*** store select addr in SQLDA_PTRS array ***/
    if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
      sqlda_ptrs[context_num][shandle].sptr = select_ptr; 
    else {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT store select pointer in SQLDA_PTRS");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);                     
    }

    sprintf(syb_descriptor_name,"SD%d",shandle);
  }
     
  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);


  EXEC SQL ALLOCATE DESCRIPTOR :syb_descriptor_name WITH MAX :ncols;

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
  gSQLDA  *select_ptr;


  context_num = gsi_current_context();
 
  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_PREPARE");

  if (shandle == 0) return (GDB_ERROR);

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  len = strlen(sql_str);
  if ((syb_sql_stmt = calloc(len+1,sizeof(char))) == NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for syb_sql_stmt");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  strcpy(syb_sql_stmt,sql_str);
     
  *stmt_id = shandle;
  sprintf(syb_stmt_id_name,"S%d",shandle);  /* stmt_id must be a string for Sybase */
  
  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL AT :connect_name PREPARE :syb_stmt_id_name FROM :syb_sql_stmt;
  if (sqlca.sqlcode != 0) {
    if (select_ptr != NULL) select_ptr[0].row_count = 0;
    *stmt_id = 0; /* stmt_id created dynamically for Sybase */
  }

  free (syb_sql_stmt);

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

  if (shandle == 0) return (GDB_ERROR);

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_DECLARE_CURSOR: %",curs_name);

  sprintf(syb_stmt_id_name,"S%d",shandle);
  strcpy(syb_curs_name,curs_name);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL AT :connect_name DECLARE :syb_curs_name CURSOR FOR :syb_stmt_id_name;

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
  register long     i, bvl;
  gSQLDA  *bind_ptr;
  char   **bind_array = (char **)NULL;

  EXEC SQL BEGIN DECLARE SECTION;
    CS_INT			descnt;
    CS_INT			col_num;
    CS_INT          ddatatype;
    CS_INT          ddatalen;
    CS_INT          dprec;
    CS_INT          dscale;
    CS_SMALLINT		ind_val;
    CS_CHAR			*text_val;
  	CS_INT			long_val;
	CS_SMALLINT		short_val;
	CS_FLOAT		dbl_val;
	CS_REAL			float_val;
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DESCRIBE_INPUT");
  
  *bind_processed = FALSE;

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf((char *)connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if ( sqlca.sqlcode < 0 ) return( GDB_EXT_ERROR );

  bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

  if (bind_ptr == (gSQLDA *) NULL) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%d",ENOTINI);
    return (GDB_ERROR);
  }

  sprintf( syb_stmt_id_name, "S%d", shandle );
  sprintf( syb_descriptor_name, "BD%d", shandle );

  if ( action == GDB_INIT )
  {

    EXEC SQL DESCRIBE INPUT :syb_stmt_id_name USING SQL DESCRIPTOR :syb_descriptor_name;

    if (sqlca.sqlcode < 0)
    {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","DESCRIBE INPUT: %", sqlca.sqlerrm.sqlerrmc);
      return (GDB_ERROR);
    }

    /* Determine how many bind variables there are */
    EXEC SQL GET DESCRIPTOR :syb_descriptor_name :descnt = COUNT;
    if (sqlca.sqlcode < 0) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","GET DESCRIPTOR: %",sqlca.sqlerrm.sqlerrmc);
      return (GDB_ERROR);
    }

    /*
    ** The following test is most likely not necessary because the error
    ** condition will be picked up by the previous call to DESCRIBE INPUT
    ** But it is kept here to be consistent wth the other database bridges
    */
    if ( descnt > context[context_num].max_bind_vars) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EMBVEXD,descnt,context[context_num].max_bind_vars );
      descnt = 0; /* set to 0 to avoid dealloc problems */
      return (GDB_ERROR);
    }

    /* If there are no input descriptors, just return success */
    if ( !descnt ) {
	  *bind_processed = TRUE;
	  return ( GDB_SUCCESS );
	}

    /* Load bind pointer with the existing info in the descriptors */
    for (i=0,col_num=i+1; i<descnt; i++,col_num++) {

      /*
      ** Examine the existing descriptor.  With Sybase, only the following
      ** fields are available for input descriptors:
      ** TYPE and LENGTH. (PRECISION and SCALE are also available for numbers)
      */
	  EXEC SQL GET DESCRIPTOR :syb_descriptor_name VALUE :col_num
		                      :ddatatype   = TYPE,
		                      :ddatalen    = LENGTH,
                              :dprec       = PRECISION,
                              :dscale      = SCALE;

      if (sqlca.sqlcode < 0) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","GET DESCRIPTOR: %",sqlca.sqlerrm.sqlerrmc);
        return (GDB_ERROR);
      }

      if ((bind_ptr[i].colname = (char *)calloc(strlen(GDB_UNKNOWN)+1,sizeof(char))) == (char *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for bind_ptr.colname");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
        return (GDB_ERROR);
      }

      /*
      ** Store the values in bind_ptr.
      ** Fudge the column name to "UNKNOWN" because Sybase does not return 
  	  ** the column name for input bind descriptors
      */
      strcpy( bind_ptr[i].colname, GDB_UNKNOWN );
      bind_ptr[i].ncols     = descnt;
      bind_ptr[i].datatype  = ddatatype;
      bind_ptr[i].datalen   = ddatalen;
      bind_ptr[i].prec      = dprec;   
      bind_ptr[i].scale     = dscale;
    }

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

  iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d","Bind variables processed: %",bind_vars->nBind);

  /* Load bind variables into bind descriptor */
  for (i=0,col_num=i+1; i<bind_ptr[0].ncols; i++,col_num++) {
    strcpy( bind_array[i], bind_vars->bind_array[i] );

    if ((text_val = (char *)calloc(strlen(bind_array[i])+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }

    /* Set the null indicator if required */
    /* ---------------------------------- */
    strcpy( text_val, bind_array[i] );
    ind_val = 0;
    if ((context[context_num].set_null_options & 0x2) && 
            ! strcmpci(text_val, context[context_num].set_null_string))
        ind_val = -1;
    else 
        if ((context[context_num].set_null_options & 0x4) && !strcmpci(text_val,"NULL"))
            ind_val = -1;


	/* Based on the descriptor type, the data may need to be converted */
	switch ( bind_ptr[i].datatype )
	{
	  case SB_VARCHAR :
	  case SB_STRING :
	  case SB_CHAR :
	  case SB_DATETIME :
	  case SB_SMALLDATETIME :
	    EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
            DATA = :text_val,
            INDICATOR = :ind_val;
	    break;

	  case SB_INTEGER :
	    long_val = atoi( text_val );
	    EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
            DATA = :long_val,
            INDICATOR = :ind_val;
		break;

	  case SB_SMALLINT :
	  case SB_TINYINT :
	  case SB_BIT :
	    short_val = (short) atoi( text_val );
	    EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
            DATA = :short_val,
            INDICATOR = :ind_val;
	    break;

	  case SB_SMALLMONEY :
	  case SB_REAL_OLD :
	  case SB_REAL :
	    float_val = (float) atof( text_val );
	    EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
            DATA = :float_val,
            INDICATOR = :ind_val;
	    break;

	  case SB_FLOAT :
	  case SB_MONEY :
	  case SB_NUMERIC :
	  case SB_DECIMAL :
	    dbl_val = (double) atof( text_val );
	    EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
            DATA = :dbl_val,
            INDICATOR= :ind_val;
	    break;

      default :
          iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,ddatatype,col_num);
          return (GDB_ERROR);
          break;
    }

    free( (char *)text_val );
    if (sqlca.sqlcode < 0) {
	  iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not set descriptor for %",syb_descriptor_name);
      break;
    }

  } /* end for loop */

  /* release the bind array */
  for (i=0;i<bind_ptr[0].ncols;i++) {  
    if (bind_array[i] != (char *)NULL)
      free((char *)bind_array[i]);
  }
  if (bind_array != (char **)NULL)
    free ((char **)bind_array);

  if ( sqlca.sqlcode < 0 )
    return( GDB_EXT_ERROR );

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
  gSQLDA  *select_ptr;
  long     scol;
  long     shandle;
  long    *stmt_id;
  long    *ncols;

  EXEC SQL BEGIN DECLARE SECTION;
    CS_INT          descnt;
    CS_INT          dcol;
    CS_INT          ddatatype;
    CS_INT          ddatalen;               
    CS_INT          dprec;
    CS_INT          dscale;
    CS_INT          dnullable;
    CS_CHAR         dname[MAX_COLNAME_LEN];
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

  sprintf(syb_stmt_id_name,"S%d",shandle);
  sprintf(syb_descriptor_name,"SD%d",shandle);

  EXEC SQL DESCRIBE OUTPUT :syb_stmt_id_name USING SQL DESCRIPTOR :syb_descriptor_name ;
  if (sqlca.sqlcode < 0) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","DESCRIBE OUTPUT: %",sqlca.sqlerrm.sqlerrmc);
    return (GDB_ERROR);
  }

  /* get the actual # of columns */
  EXEC SQL GET DESCRIPTOR :syb_descriptor_name :descnt = COUNT;
  if (sqlca.sqlcode < 0) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","GET DESCRIPTOR %",sqlca.sqlerrm.sqlerrmc);
    return (GDB_ERROR);
  }

  if ( descnt > max_col_array_size /*context[context_num].max_ncols*/ ) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",ENCOLEX,descnt,max_col_array_size /*context[context_num].max_ncols*/);
    *ncols = 0; /* set to 0 to avoid dealloc problems */
    return (GDB_ERROR);
  }

  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);
  *ncols = (long)descnt;

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

  /*** realloc nSQLDA to the actual n needed ***/
  if ((sqlda_ptrs[context_num][shandle].sptr = select_ptr = (gSQLDA *)realloc(select_ptr,
       descnt*sizeof(gSQLDA))) == (gSQLDA *)NULL) {
     iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could NOT realloc memory for gSQLDA select pointer");
     iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINMEMR);
     return (GDB_ERROR);                     
  }
  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%d","SQLDA memory reallocated for % select-list items",descnt);

  for (dcol=1;dcol<descnt+1;dcol++) {
    EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :dcol 
                            :dname       = NAME,
                            :ddatatype   = TYPE,
                            :ddatalen    = LENGTH,
                            :dprec       = PRECISION,
                            :dscale      = SCALE,
                            :dnullable   = NULLABLE;

    if (sqlca.sqlcode < 0) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","GET DESCRIPTOR: %",sqlca.sqlerrm.sqlerrmc);
      return (GDB_ERROR);
    }

    scol = dcol - 1;
	/*
	** Check to see if we have a function name.  e.g. COUNT(*).
	** If so, the descriptor name will be NULL. Set the colname to GDB_UNKNOWN.
	*/
	if ( !(strlen(dname)) )
	  strcpy( dname, GDB_UNKNOWN );

    if ((select_ptr[scol].colname = (char *)calloc(strlen(dname)+1,sizeof(char))) == (char *)NULL) {
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for SP colname");
      iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
      return (GDB_ERROR);
    }

    strcpy(select_ptr[scol].colname,dname);
    select_ptr[scol].ncols     = descnt;
    select_ptr[scol].datatype  = ddatatype;
    select_ptr[scol].datalen   = ddatalen;
    select_ptr[scol].prec      = dprec;   
    select_ptr[scol].scale     = dscale;
    select_ptr[scol].nullable  = dnullable;
  
    switch (ddatatype)
    {
      case SB_DATETIME :
      case SB_SMALLDATETIME :
          select_ptr[scol].datalen = ddatalen = DATE_LEN;
          break;
                
      case SB_VARCHAR :
      case SB_CHAR :
          select_ptr[scol].datatype = ddatatype = SB_CHAR;
          break;                                                 

      case SB_STRING :
          select_ptr[scol].datatype = ddatatype = SB_CHAR;
          select_ptr[scol].datalen  = ddatalen = context[context_num].max_text_len ;
          break;                                                 
    
      case SB_INTEGER :         
      case SB_TINYINT :         
      case SB_SMALLINT :   
      case SB_BIT :
      case SB_REAL_OLD :
      case SB_REAL :
          ; /* nothing unusual */
      break;                                                 

      case SB_FLOAT :         
      case SB_MONEY :
          select_ptr[scol].datatype = ddatatype = SB_FLOAT;
          break;

      case SB_SMALLMONEY :
          select_ptr[scol].datatype = ddatatype = SB_REAL;
          break;

      case SB_DECIMAL :
      case SB_NUMERIC :
          sqlGen->decimal_flags[scol] = (char)(dprec >= 9 && dscale == 0) ;
          select_ptr[scol].datalen = ddatalen = sizeof(double);
          select_ptr[scol].datatype = ddatatype = SB_FLOAT;
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
  gSQLDA  *select_ptr;

  EXEC SQL BEGIN DECLARE SECTION;
    CS_INT         row_size;
  EXEC SQL END DECLARE SECTION;
    
  context_num = gsi_current_context();

  if (shandle == 0 || curs_name == (char *)NULL)
    return (GDB_ERROR);

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_OPEN_CURSOR: %",curs_name);

  /* Set the cursor name and bind descriptor name */
  strcpy(syb_curs_name,curs_name);
  sprintf(syb_descriptor_name,"BD%d",shandle);

  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);
  row_size = context[context_num].genda_rows+1;

  /* set number of rows fetched to zero */
  select_ptr[0].row_count = row_count[context_num] = 0;

  EXEC SQL AT :connect_name OPEN :syb_curs_name row_count = :row_size
       USING SQL DESCRIPTOR :syb_descriptor_name;

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
  gSQLDA  *select_ptr;

  long     retry=0;
  long     prev_sqlcode=0;

  context_num = gsi_current_context();

  if (shandle == 0) return (GDB_ERROR);

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_FETCH: %",curs_name);

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /* set context connection name and cursor name */
  sprintf(connect_name,"DB%d",context_num);
  strcpy(syb_curs_name,curs_name);

  sprintf(syb_descriptor_name,"SD%d",shandle);
  EXEC SQL AT :connect_name FETCH :syb_curs_name INTO SQL DESCRIPTOR :syb_descriptor_name;

  if (sqlca.sqlcode < 0) {
    sql_open_cursor(curs_name,shandle);
    if (sqlca.sqlcode != 0) return (GDB_EXT_ERROR);
    sprintf(syb_descriptor_name,"SD%d",shandle);
    EXEC SQL AT :connect_name FETCH :syb_curs_name INTO SQL DESCRIPTOR :syb_descriptor_name;
  }


  if (sqlca.sqlcode >=0 && sqlca.sqlcode != DB_END_OF_CURSOR) {
    select_ptr[0].row_count += 1;
    row_count[context_num] = select_ptr[0].row_count;
  }

  /* workaround for Sybase locking problem. Note: The cursor will only be closed
     on and EOCURSOR */
/*
**  if (force_cursor_close[context_num] && 
**     (sqlca.sqlcode == DB_END_OF_CURSOR || sqlca.sqlcode < 0) ) {
*/
  if ( sqlca.sqlcode == DB_END_OF_CURSOR || sqlca.sqlcode < 0 ) {
    /*
	** need to save old status as close_cursor will change it
    ** Note: The message info will be lost on an error in this case
	*/
    prev_sqlcode = sqlca.sqlcode;  
    sql_close_cursor( curs_name, shandle, FALSE );
    sqlca.sqlcode = prev_sqlcode;
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
  gSQLDA  *bind_ptr;
  long     status = 0;
 
  context_num = gsi_current_context();
  
  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DEALLOC_DESCRIPTORS");

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);

  sprintf(syb_stmt_id_name,"S%d",shandle);


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
    sprintf( syb_descriptor_name,"BD%d",shandle );
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
    sprintf(syb_descriptor_name,"SD%d",shandle);
  }
  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL DEALLOCATE DESCRIPTOR :syb_descriptor_name;
  if (sqlca.sqlcode < 0) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not deallocate SQLDA for %",syb_descriptor_name);
  }

  /*
  ** NOTE! NOTE! NOTE!
  ** The Deallocation of the prepared statement is being commented out for
  ** now because it makes the statement id invalid which can cause a Fetch
  ** to fail. This was done for Bind variable support.
  ** By commenting this out, There may be a small memory leak
  **
  **  EXEC SQL AT :connect_name DEALLOCATE PREPARE :syb_stmt_id_name;
  **  if (sqlca.sqlcode < 0) {
  **    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not deallocate PREPARE for %",syb_stmt_id_name);
  **    status = 1;
  **  }
  */

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

    for (col=0; col<context[context_num].max_bind_vars; col++) {

      if (bind_ptr[col].colname != NULL) {
        free(bind_ptr[col].colname);
        bind_ptr[col].colname = NULL;
      }

	  /* deallocate the data and NULL indicator portions of the bind_ptr */
      switch ( bind_ptr[col].datatype )
      {
        case SB_CHAR :
        case SB_STRING :
        case SB_VARCHAR :
        case SB_DATETIME :
        case SB_SMALLDATETIME :
          if ( bind_ptr[col].data ) {
	        for ( i=0; bind_ptr[col].data[i] ;i++ ) {
		      free( bind_ptr[col].data[i] );
		      bind_ptr[col].data[i] = NULL;
	        }
            free( bind_ptr[col].data );
            bind_ptr[col].data = NULL;
          }
  	      break;

        case SB_INTEGER :
        case SB_SMALLINT :
        case SB_TINYINT :
        case SB_BIT :
        case SB_SMALLMONEY :
        case SB_REAL_OLD :
        case SB_REAL :
        case SB_MONEY :
        case SB_FLOAT :
        case SB_NUMERIC :
        case SB_DECIMAL :
          if ( bind_ptr[col].data ) {
            free( bind_ptr[col].data );
            bind_ptr[col].data = NULL;
          }
  	      break;
	  } /* end switch */

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
      if (select_ptr[col].colname != NULL) {
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
    long     release_cursor; /* Not used by Sybase */

{
  context_num = gsi_current_context();

  if (shandle == 0) return (GDB_ERROR);

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_CLOSE_CURSOR: %",curs_name);
  
  strcpy(syb_curs_name,curs_name);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL AT :connect_name CLOSE :syb_curs_name;

  if (sqlca.sqlcode < 0) {
    iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","Could not close cursor %",syb_curs_name);
    return (GDB_EXT_ERROR);
  }

  return (GDB_SUCCESS);
}                                             


/*======================================================================
  sql_disconnect
    - disconnect from the database
  ======================================================================*/
long sql_disconnect( context_num )
  gsi_int   context_num;
{
  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DISCONNECT");

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

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
  if ((syb_sql_stmt = calloc(len+1,sizeof(char))) == NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for syb_sql_stmt");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  strcpy(syb_sql_stmt,stmt_str);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL AT :connect_name EXECUTE IMMEDIATE :syb_sql_stmt;

  free (syb_sql_stmt);
  row_count[context_num] = sqlca.sqlerrd[2];

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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
  /* SQLDA            *bind_ptr;*/

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_EXEC_DYNAMIC_SQL");

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf(connect_name,"DB%d",context_num);

  /* stmt_id must be a string for Sybase */
  sprintf(syb_stmt_id_name,"S%d",shandle);

  /* set the descriptor name */
  sprintf(syb_descriptor_name,"BD%d",shandle);
  
  /* Execute the statement */
  EXEC SQL AT :connect_name EXECUTE :syb_stmt_id_name USING 
      SQL DESCRIPTOR :syb_descriptor_name;

  row_count[context_num] = sqlca.sqlerrd[2];
  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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

  EXEC SQL AT :connect_name COMMIT TRANSACTION;

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
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

  EXEC SQL AT :connect_name ROLLBACK TRANSACTION;

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
  int      status;
  gSQLDA  *select_ptr;


  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s%s","SQL_REFRESH: %",curs_name);

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;
        
  /* To indicate a refreshed cursor set row_count to 0 */
  select_ptr[0].row_count = row_count[context_num] = 0;

  sql_close_cursor(curs_name, shandle, FALSE);

  /* ignore the return for now and open the cursor */
  sql_open_cursor(curs_name,shandle);

  status = sqlca.sqlcode;

/* BUG
** to workaround sybase lock bug 41011051 
**
**  if (force_cursor_close[context_num])
*/
    sql_close_cursor( curs_name, shandle, FALSE );

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_release
    - release any database resources allocated by 'prepare' in Sybase

    Arguments:
    - stmt_id: statement id from 'prepare'   (same as shandle in Sybase)
  ======================================================================*/

long sql_release( stmt_id )
    long    *stmt_id;
{
  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_RELEASE");

  /*
  ** Because stmt_id and shandle are the same value in Sybase, we can
  ** do the following:
  */
  sprintf(syb_stmt_id_name,"S%d",*stmt_id);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);
  
  if ( *stmt_id == 0 )
      return(GDB_SUCCESS);

  EXEC SQL AT :connect_name DEALLOCATE PREPARE :syb_stmt_id_name;	


  /* ?????????
  ** DEALLOCATE above may make the following unnecessary 
  **
  ** to workaround sybase lock bug 41011051 
  */
/*
  if (force_cursor_close[context_num]) {
    sprintf(syb_curs_name,"CURSOR%d_%d",context_num,*stmt_id);
    sql_close_cursor( syb_curs_name, *stmt_id, FALSE );
  }
*/

  *stmt_id = 0;

  return( GDB_SUCCESS );
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
  if ((syb_sql_stmt = (char *)calloc(len+1,sizeof(char))) == (char *)NULL) {
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for syb_sql_stmt");
    iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
    return (GDB_ERROR);
  }
  strcpy(syb_sql_stmt,sql_stmt);

  sprintf(syb_stmt_id_name,"SP_%d",context_num);

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL AT :connect_name PREPARE :syb_stmt_id_name FROM :syb_sql_stmt;
  free((char *)syb_sql_stmt);
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  EXEC SQL AT :connect_name EXECUTE :syb_stmt_id_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);  

  /* since the 'dealloc' will clear any error message generated by the 
     execute stmt, skip the 'dealloc prepare' on error since it doesn't
     use much memory anyway and we want the error message to return */

  EXEC SQL AT :connect_name DEALLOCATE PREPARE :syb_stmt_id_name;

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/*======================================================================
  sql_exec_stored_proc_return
    - execute a fixed stored procedure that returns 1 argument
    - Not used in Sybase bridge

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
    CS_INT   result;
    CS_CHAR  syb_sql_stmt[60]= "SELECT COUNT(*) FROM sysusers";
  EXEC SQL END DECLARE SECTION;

  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_PING_DB");

  /* set context connection name */
  sprintf( connect_name, "DB%d",context_num );

  /* prepare the statement */
  EXEC SQL AT :connect_name PREPARE ping FROM :syb_sql_stmt;
  if ( sqlca.sqlcode < 0 ) return ( GDB_EXT_ERROR );

  /* execute the statement */
  EXEC SQL AT :connect_name EXECUTE ping INTO :result;

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
    CS_CHAR   test_trig_name[SYB_MAX_TRIGGER_NAME_LEN+1];
    CS_CHAR   t_msg[200];
    CS_CHAR   t_datetime[30];
    CS_BIT    t_success ;
  EXEC SQL END DECLARE SECTION;

  t_msg[0] = '\0';
  t_datetime[0] = '\0';

  /* CAUTION: context_num is passed from L1 as we are outside of
     run-loop during check (i.e. not within a context). Therefore
     you MUST NOT call any other function that utilizes a context
     number derived from gsi_current_context() */

  len = strlen(trig_name);
  if (len > SYB_MAX_TRIGGER_NAME_LEN) {
    return (GDB_ERROR);
  }
  strcpy( test_trig_name, trig_name );
   
  /* set context connection name */
  sprintf( connect_name, "DB%d",context_num );
  
  /*
  ** Fetch a row of information for the given trigger name from the
  ** trigger table and then delete that row. Both of these operations
  ** are done in the g2_process_trig_proc procedure
  */
  EXEC SQL AT :connect_name EXEC g2_proc_trig
              :test_trig_name,
              :t_msg OUT,
              :t_datetime OUT,
              :t_success OUT ;
  if ( ! sqlca.sqlcode && t_success ) {
    sprintf( trig_ret_msg, "%s <%s>", t_msg, t_datetime );
  }
  else if ( !t_success ) {
    *trig_ret_msg = 0;
  }
  else {
	/* 
	** The following prevents a continuous loop in check_triggers
	** (never returning to gsi_run_loop) if the database connection
	** gets dropped.
    */
    *trig_ret_msg = 0;
    if (context[context_num].console_output) 
	{
      if (context[context_num].name != (char *)NULL)
        wprintf(_T("G2-%s: %s: %s: %d %s\n"), wDB_TYPE, context[context_num].name,
                ERROR_SYM, sqlca.sqlcode, sqlca.sqlerrm.sqlerrmc);
      else
        wprintf(_T("G2-%s: %d: %s: %d %s\n"), wDB_TYPE, context_num, ERROR_SYM,
		        sqlca.sqlcode, sqlca.sqlerrm.sqlerrmc);
    }
    return( GDB_EXT_ERROR );
  }
  return (GDB_SUCCESS);

}

/*======================================================================
  sql_poll_check
    - called each time through gsi run-loop.
    - Not used at this time by the Sybase bridge
 ======================================================================*/

long sql_poll_check( void )
{
  return (GDB_SUCCESS);
}


/*======================================================================
  sql_exec_sql_obj
    Arguments:
    - shandle: the staement handle
    - array_size: the number of rows to be inserted or updated
  ======================================================================*/

long sql_exec_sql_obj( shandle, array_size, stmt_id )
    long   shandle;
    long   array_size;
    long   stmt_id;
{
  EXEC SQL BEGIN DECLARE SECTION;
    CS_INT          descnt;
    CS_INT          col_num;
    CS_SMALLINT		ind_val;
	  CS_CHAR			*text_val;
	  CS_INT			long_val;
	  CS_SMALLINT		short_val;
	  CS_FLOAT		dbl_val;
	  CS_REAL			float_val;
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

  /* stmt_id must be a string for Sybase */
  sprintf(syb_stmt_id_name,"S%d",shandle);

  /* set the descriptor name */
  sprintf(syb_descriptor_name,"BD%d",shandle);

  descnt = (long) bind_ptr[0].ncols;

  /* For each row of data, set up the descriptor and then execute the statement */
  for (row=0; row<array_size; row++) {

    for ( i=0,col_num=i+1; i<descnt;  i++,col_num++ ) {

	  /* set the value for null indicator */
	  ind_val = (short) bind_ptr[i].ind[row];

	  /* Based on the descriptor type, the data may need to be converted */
	  switch ( bind_ptr[i].datatype )
	  {
	    case SB_VARCHAR :
	    case SB_STRING :
	    case SB_CHAR :
	    case SB_DATETIME :
	    case SB_SMALLDATETIME :
		  text_val = (char *) bind_ptr[i].data[row];
	      EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
                DATA = :text_val,
                INDICATOR = :ind_val;
	      break;

	    case SB_INTEGER :
	      long_val = (long) ((long *)bind_ptr[i].data)[row];
	      EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
                DATA = :long_val,
                INDICATOR = :ind_val;
		  break;

	    case SB_SMALLINT :
	    case SB_TINYINT :
	    case SB_BIT :
	      short_val = (short) ((long *)bind_ptr[i].data)[row];
	      EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
                DATA = :short_val,
                INDICATOR = :ind_val;
	      break;

	    case SB_SMALLMONEY :
	    case SB_REAL_OLD :
	    case SB_REAL :
	      float_val = (float) ((double *)bind_ptr[i].data)[row];
	      EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
                DATA = :float_val,
                INDICATOR = :ind_val;
	      break;

	    case SB_FLOAT :
	    case SB_MONEY :
	    case SB_NUMERIC :
	    case SB_DECIMAL :
	      dbl_val = (double) ((double *)bind_ptr[i].data)[row];
	      EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
                DATA = :dbl_val,
                INDICATOR= :ind_val;
	      break;

        default :
          iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,bind_ptr[i].datatype,col_num);
          return (GDB_ERROR);
          break;
      } /* end switch */

	}

    /* Execute the statement */
    EXEC SQL AT :connect_name EXECUTE :syb_stmt_id_name USING 
        SQL DESCRIPTOR :syb_descriptor_name;
    if (sqlca.sqlcode < 0)  return (GDB_EXT_ERROR);

  } /* end for row loop */

  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);

}


/* ========================================================================== */
/*                                                                            */
/*                     The Sybase Bridge does not use DSNs                    */
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
  gSQLDA   *select_ptr;

  EXEC SQL BEGIN DECLARE SECTION;
    int              idx;
    short            ind_val=0;
    char            *text_val;
    CS_CHAR          date_val[DATE_LEN]="";
    short            short_val=0;
    int              int_val=0;
    float            float_val=0.0;
    double           dbl_val=0.0;
  EXEC SQL END DECLARE SECTION;
   
  context_num = gsi_current_context();

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  EXEC SQL SET CONNECTION :connect_name;
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  sprintf(syb_descriptor_name,"SD%d",shandle);

  idx = col + 1;
  switch (datatype)
  {
    case SB_CHAR :
    case SB_STRING :
    case SB_VARCHAR :

      if ((text_val = (char *)calloc(select_ptr[col].datalen+1,sizeof(char))) == (char *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE,"%s","Could not alloc mem for text_val");
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE,"%d",EINSMEM);
        return (GDB_ERROR);
      }

      EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
                              :text_val = DATA,         
                              :ind_val  = INDICATOR;
      text_val[select_ptr[col].datalen] = 0;
      strcpy(tunion->t_str,text_val);
      *t_ind  = (long)ind_val;
      if(text_val != (char*) NULL){
        free ((char *)text_val);
        text_val = (char*) NULL;
      }
      break;

    case SB_DATETIME :
    case SB_SMALLDATETIME :

      EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
                              :date_val = DATA,         
                              :ind_val  = INDICATOR;
      strcpy(tunion->t_str,date_val);
      *t_ind  = (long)ind_val;
      break;

    case SB_INTEGER :
      EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
                              :int_val  = DATA,
                              :ind_val  = INDICATOR;
      tunion->t_int = int_val;
      *t_ind  = (long)ind_val;
      break;

    case SB_TINYINT :
    case SB_BIT :
    case SB_SMALLINT :
      EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
                              :short_val = DATA,
                              :ind_val   = INDICATOR;
      tunion->t_short = short_val;
      *t_ind  = (long)ind_val;
      break;

    case SB_SMALLMONEY :
    case SB_REAL_OLD :
    case SB_REAL :
      EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
                              :float_val = DATA,
                              :ind_val   = INDICATOR;
      tunion->t_float = float_val;
      *t_ind  = (long)ind_val;
      break;

    case SB_MONEY :
    case SB_FLOAT :
    case SB_NUMERIC :
    case SB_DECIMAL :
      EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
                              :dbl_val = DATA,
                              :ind_val = INDICATOR;
      tunion->t_dbl = dbl_val;
      *t_ind = (long)ind_val;
      break;

    default:
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,datatype,idx);
      return (GDB_ERROR);
      break;
  }
  return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*             Tell the Server how much of a text field to send              */
/*                                                                           */
/* ------------------------------------------------------------------------- */
long sql_set_textsize(long limit)
{
    EXEC SQL BEGIN DECLARE SECTION ;
    char	 txtBuf[25] ;
    EXEC SQL END DECLARE SECTION ;

    sprintf(txtBuf,"SET TEXTSIZE %ld", limit) ;
    EXEC SQL AT :connect_name EXECUTE IMMEDIATE :txtBuf ;
    return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);

}

