
/*
** Generated code begins here.
*/
# line 1 "gdb_client_syb.cp"

/*
** This file was generated on Sun May 15 08:34:20 2016
**  by Sybase Embedded SQL Preprocessor Sybase ESQL/C Precompiler/15.7/P/PC Int
** el/BUILD1570-011/OPT/Tue Aug 16 05:44:32 2011
*/
# line 1 "gdb_client_syb.cp"
# line 1 "gdb_client_syb.cp"
#define _SQL_SCOPE extern
# line 1 "gdb_client_syb.cp"
#include <sybhesql.h>

/*
** Generated code ends here.
*/
# line 1 "gdb_client_syb.cp"
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


/*
** SQL STATEMENT: 1
** EXEC SQL INCLUDE SQLCA;

*/
# line 38 "gdb_client_syb.cp"
# line 38 "gdb_client_syb.cp"
SQLCA sqlca;

/*
** Generated code ends here.
*/
# line 38 "gdb_client_syb.cp"


/* Prototype */
/* --------- */
long sql_set_textsize(long limit) ;



/*
** SQL STATEMENT: 1
** EXEC SQL BEGIN DECLARE SECTION;

*/
# line 45 "gdb_client_syb.cp"

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


/*
** SQL STATEMENT: 2
** EXEC SQL END DECLARE SECTION;

*/
# line 59 "gdb_client_syb.cp"

/*
** Generated code ends here.
*/
# line 59 "gdb_client_syb.cp"


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

/*
** SQL STATEMENT: 3
** EXEC SQL WHENEVER SQLERROR   CONTINUE;

*/
# line 84 "gdb_client_syb.cp"


/*
** SQL STATEMENT: 4
** EXEC SQL WHENEVER SQLWARNING CONTINUE;

*/
# line 85 "gdb_client_syb.cp"


/*
** SQL STATEMENT: 5
** EXEC SQL WHENEVER NOT FOUND  CONTINUE;

*/
# line 86 "gdb_client_syb.cp"


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
  
  
           /*
           ** SQL STATEMENT: 5
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 124 "gdb_client_syb.cp"

    char         *sb_user;
    char         *sb_pass;
    char         *sb_server;
  
           /*
           ** SQL STATEMENT: 6
           ** EXEC SQL END DECLARE SECTION;

           */
# line 128 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 128 "gdb_client_syb.cp"


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
    
           /*
           ** SQL STATEMENT: 7
           ** EXEC SQL CONNECT :sb_user IDENTIFIED BY :sb_pass AT :connect_name;
           */
# line 172 "gdb_client_syb.cp"
# line 172 "gdb_client_syb.cp"
           {
# line 172 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 172 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 172 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 172 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 172 "gdb_client_syb.cp"
               {
# line 172 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 172 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_NONANSI_CONNECT;
# line 172 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 172 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 172 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                   {
# line 172 "gdb_client_syb.cp"
                       if (_sql->doDecl == CS_TRUE)
# line 172 "gdb_client_syb.cp"
                       {
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_USERNAME, sb_user, CS_NULLTERM, NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_PASSWORD, sb_pass, CS_NULLTERM, NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = _sqlctdiag(_sql, CS_CLEAR, 
# line 172 "gdb_client_syb.cp"
                                   CS_UNUSED);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_capability(_sql->conn.connection, CS_SET,
# line 172 "gdb_client_syb.cp"
                                    CS_CAP_RESPONSE, CS_RES_NOSTRIPBLANKS, 
# line 172 "gdb_client_syb.cp"
                                   &_sql->cstrue);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_EXTRA_INF, &_sql->cstrue, CS_UNUSED, 
# line 172 "gdb_client_syb.cp"
                                   NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_ANSI_BINDS, &_sql->cstrue, CS_UNUSED, 
# line 172 "gdb_client_syb.cp"
                                   NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_connect(_sql->conn.connection, NULL, 0);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_GET, 
# line 172 "gdb_client_syb.cp"
                                   CS_TDS_VERSION, &_sql->temp_int, CS_UNUSED, 
# line 172 "gdb_client_syb.cp"
                                   &_sql->outlen);
# line 172 "gdb_client_syb.cp"
                               if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                               {
# line 172 "gdb_client_syb.cp"
                                   if (_sql->temp_int < CS_TDS_50)
# line 172 "gdb_client_syb.cp"
                                   {
# line 172 "gdb_client_syb.cp"
                                       _sqlsetintrerr(_sql, (CS_INT) 
# line 172 "gdb_client_syb.cp"
                                           _SQL_INTRERR_25013);
# line 172 "gdb_client_syb.cp"
                                   }
# line 172 "gdb_client_syb.cp"
                                   
# line 172 "gdb_client_syb.cp"
                               }
# line 172 "gdb_client_syb.cp"
                               
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_ANSINULL, &_sql->cstrue, CS_UNUSED, 
# line 172 "gdb_client_syb.cp"
                                   NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_ANSIPERM, &_sql->cstrue, CS_UNUSED, 
# line 172 "gdb_client_syb.cp"
                                   NULL);
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_STR_RTRUNC, &_sql->cstrue, CS_UNUSED,
# line 172 "gdb_client_syb.cp"
                                    NULL);
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_ARITHABORT, &_sql->csfalse, 
# line 172 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_TRUNCIGNORE, &_sql->cstrue, 
# line 172 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_ARITHIGNORE, &_sql->csfalse, 
# line 172 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_ISOLATION, &_sql->Level3, CS_UNUSED, 
# line 172 "gdb_client_syb.cp"
                                   NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_CHAINXACTS, &_sql->cstrue, CS_UNUSED,
# line 172 "gdb_client_syb.cp"
                                    NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_CURCLOSEONXACT, &_sql->cstrue, 
# line 172 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 172 "gdb_client_syb.cp"
                           {
# line 172 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 172 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 172 "gdb_client_syb.cp"
                                   CS_OPT_QUOTED_IDENT, &_sql->cstrue, 
# line 172 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 172 "gdb_client_syb.cp"
                           }
# line 172 "gdb_client_syb.cp"
                           
# line 172 "gdb_client_syb.cp"
                           _sql->retcode = _sqlepilog(_sql);
# line 172 "gdb_client_syb.cp"
                       }
# line 172 "gdb_client_syb.cp"
                       
# line 172 "gdb_client_syb.cp"
                   }
# line 172 "gdb_client_syb.cp"
                   
# line 172 "gdb_client_syb.cp"
               }
# line 172 "gdb_client_syb.cp"
               
# line 172 "gdb_client_syb.cp"
           }
# line 172 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 172 "gdb_client_syb.cp"

  else  
    
           /*
           ** SQL STATEMENT: 8
           ** EXEC SQL CONNECT :sb_user IDENTIFIED BY :sb_pass AT :connect_name U
           ** SING :sb_server;
           */
# line 174 "gdb_client_syb.cp"
# line 174 "gdb_client_syb.cp"
           {
# line 174 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 174 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 174 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 174 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 174 "gdb_client_syb.cp"
               {
# line 174 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 174 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_NONANSI_CONNECT;
# line 174 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 174 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 174 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                   {
# line 174 "gdb_client_syb.cp"
                       if (_sql->doDecl == CS_TRUE)
# line 174 "gdb_client_syb.cp"
                       {
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_USERNAME, sb_user, CS_NULLTERM, NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_PASSWORD, sb_pass, CS_NULLTERM, NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = _sqlctdiag(_sql, CS_CLEAR, 
# line 174 "gdb_client_syb.cp"
                                   CS_UNUSED);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_capability(_sql->conn.connection, CS_SET,
# line 174 "gdb_client_syb.cp"
                                    CS_CAP_RESPONSE, CS_RES_NOSTRIPBLANKS, 
# line 174 "gdb_client_syb.cp"
                                   &_sql->cstrue);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_EXTRA_INF, &_sql->cstrue, CS_UNUSED, 
# line 174 "gdb_client_syb.cp"
                                   NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_ANSI_BINDS, &_sql->cstrue, CS_UNUSED, 
# line 174 "gdb_client_syb.cp"
                                   NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_connect(_sql->conn.connection, sb_server,
# line 174 "gdb_client_syb.cp"
                                    CS_NULLTERM);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_con_props(_sql->conn.connection, CS_GET, 
# line 174 "gdb_client_syb.cp"
                                   CS_TDS_VERSION, &_sql->temp_int, CS_UNUSED, 
# line 174 "gdb_client_syb.cp"
                                   &_sql->outlen);
# line 174 "gdb_client_syb.cp"
                               if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                               {
# line 174 "gdb_client_syb.cp"
                                   if (_sql->temp_int < CS_TDS_50)
# line 174 "gdb_client_syb.cp"
                                   {
# line 174 "gdb_client_syb.cp"
                                       _sqlsetintrerr(_sql, (CS_INT) 
# line 174 "gdb_client_syb.cp"
                                           _SQL_INTRERR_25013);
# line 174 "gdb_client_syb.cp"
                                   }
# line 174 "gdb_client_syb.cp"
                                   
# line 174 "gdb_client_syb.cp"
                               }
# line 174 "gdb_client_syb.cp"
                               
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_ANSINULL, &_sql->cstrue, CS_UNUSED, 
# line 174 "gdb_client_syb.cp"
                                   NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_ANSIPERM, &_sql->cstrue, CS_UNUSED, 
# line 174 "gdb_client_syb.cp"
                                   NULL);
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_STR_RTRUNC, &_sql->cstrue, CS_UNUSED,
# line 174 "gdb_client_syb.cp"
                                    NULL);
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_ARITHABORT, &_sql->csfalse, 
# line 174 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_TRUNCIGNORE, &_sql->cstrue, 
# line 174 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_ARITHIGNORE, &_sql->csfalse, 
# line 174 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_ISOLATION, &_sql->Level3, CS_UNUSED, 
# line 174 "gdb_client_syb.cp"
                                   NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_CHAINXACTS, &_sql->cstrue, CS_UNUSED,
# line 174 "gdb_client_syb.cp"
                                    NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_CURCLOSEONXACT, &_sql->cstrue, 
# line 174 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           if (_sql->retcode == CS_SUCCEED)
# line 174 "gdb_client_syb.cp"
                           {
# line 174 "gdb_client_syb.cp"
                               _sql->retcode = 
# line 174 "gdb_client_syb.cp"
                                   ct_options(_sql->conn.connection, CS_SET, 
# line 174 "gdb_client_syb.cp"
                                   CS_OPT_QUOTED_IDENT, &_sql->cstrue, 
# line 174 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL);
# line 174 "gdb_client_syb.cp"
                           }
# line 174 "gdb_client_syb.cp"
                           
# line 174 "gdb_client_syb.cp"
                           _sql->retcode = _sqlepilog(_sql);
# line 174 "gdb_client_syb.cp"
                       }
# line 174 "gdb_client_syb.cp"
                       
# line 174 "gdb_client_syb.cp"
                   }
# line 174 "gdb_client_syb.cp"
                   
# line 174 "gdb_client_syb.cp"
               }
# line 174 "gdb_client_syb.cp"
               
# line 174 "gdb_client_syb.cp"
           }
# line 174 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 174 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 8
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 214 "gdb_client_syb.cp"

    int         ncols;
  
           /*
           ** SQL STATEMENT: 9
           ** EXEC SQL END DECLARE SECTION;

           */
# line 216 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 216 "gdb_client_syb.cp"


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
     
  
           /*
           ** SQL STATEMENT: 10
           ** EXEC SQL SET CONNECTION :connect_name;
           */
# line 272 "gdb_client_syb.cp"
# line 272 "gdb_client_syb.cp"
           {
# line 272 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 272 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 272 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 272 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 272 "gdb_client_syb.cp"
               {
# line 272 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 272 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_CONNECTION;
# line 272 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 272 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 272 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 272 "gdb_client_syb.cp"
                   {
# line 272 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 272 "gdb_client_syb.cp"
                   }
# line 272 "gdb_client_syb.cp"
                   
# line 272 "gdb_client_syb.cp"
               }
# line 272 "gdb_client_syb.cp"
               
# line 272 "gdb_client_syb.cp"
           }
# line 272 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 272 "gdb_client_syb.cp"

  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);


  
           /*
           ** SQL STATEMENT: 11
           ** EXEC SQL ALLOCATE DESCRIPTOR :syb_descriptor_name WITH MAX :ncols;
           */
# line 276 "gdb_client_syb.cp"
# line 276 "gdb_client_syb.cp"
           {
# line 276 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 276 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 276 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 276 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 276 "gdb_client_syb.cp"
               {
# line 276 "gdb_client_syb.cp"
                   _sql->descSize = ncols;
# line 276 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 276 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_ALLOC_DESC;
# line 276 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 276 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 276 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 276 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 276 "gdb_client_syb.cp"
                   {
# line 276 "gdb_client_syb.cp"
                   }
# line 276 "gdb_client_syb.cp"
                   
# line 276 "gdb_client_syb.cp"
               }
# line 276 "gdb_client_syb.cp"
               
# line 276 "gdb_client_syb.cp"
           }
# line 276 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 276 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 12
           ** EXEC SQL AT :connect_name PREPARE :syb_stmt_id_name FROM :syb_sql_s
           ** tmt;
           */
# line 331 "gdb_client_syb.cp"
# line 331 "gdb_client_syb.cp"
           {
# line 331 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 331 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 331 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 331 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 331 "gdb_client_syb.cp"
               {
# line 331 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 331 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_PREPARE;
# line 331 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 331 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 331 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 331 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 331 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 331 "gdb_client_syb.cp"
                   {
# line 331 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 331 "gdb_client_syb.cp"
                           CS_PREPARE, syb_stmt_id_name, CS_NULLTERM, 
# line 331 "gdb_client_syb.cp"
                           syb_sql_stmt, CS_NULLTERM);
# line 331 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 331 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 331 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 331 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 331 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 331 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 331 "gdb_client_syb.cp"
                       {
# line 331 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 331 "gdb_client_syb.cp"
                           {
# line 331 "gdb_client_syb.cp"
                           case CS_CMD_FAIL:
# line 331 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 331 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_ALL);
# line 331 "gdb_client_syb.cp"
                           break;
# line 331 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 331 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 331 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 331 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 331 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 331 "gdb_client_syb.cp"
                           break;
# line 331 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 331 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 331 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25004);
# line 331 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 331 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 331 "gdb_client_syb.cp"
                           break;
# line 331 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 331 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 331 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25005);
# line 331 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 331 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 331 "gdb_client_syb.cp"
                           break;
# line 331 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 331 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 331 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25006);
# line 331 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 331 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 331 "gdb_client_syb.cp"
                           break;
# line 331 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 331 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 331 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25009);
# line 331 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 331 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 331 "gdb_client_syb.cp"
                           break;
# line 331 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 331 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 331 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25010);
# line 331 "gdb_client_syb.cp"
                           break;
# line 331 "gdb_client_syb.cp"
                           }
# line 331 "gdb_client_syb.cp"
                           
# line 331 "gdb_client_syb.cp"
                       }
# line 331 "gdb_client_syb.cp"
                       
# line 331 "gdb_client_syb.cp"
                       if ((_sql->retcode != CS_END_RESULTS) && (_sql->retcode 
# line 331 "gdb_client_syb.cp"
                           != CS_CANCELED) && (_sql->retcode != 
# line 331 "gdb_client_syb.cp"
                           CS_RET_HAFAILOVER) && (_sql->resloop != CS_FALSE))
# line 331 "gdb_client_syb.cp"
                       {
# line 331 "gdb_client_syb.cp"
                           _sql->retcode = ct_cancel(NULL, _sql->conn.command, 
# line 331 "gdb_client_syb.cp"
                               CS_CANCEL_ALL);
# line 331 "gdb_client_syb.cp"
                           }
# line 331 "gdb_client_syb.cp"
                            else {
# line 331 "gdb_client_syb.cp"
                           if (((_sql->retcode != CS_CANCELED) && 
# line 331 "gdb_client_syb.cp"
                               (_sql->retcode != CS_RET_HAFAILOVER)))
# line 331 "gdb_client_syb.cp"
                           {
# line 331 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 331 "gdb_client_syb.cp"
                           }
# line 331 "gdb_client_syb.cp"
                           
# line 331 "gdb_client_syb.cp"
                       }
# line 331 "gdb_client_syb.cp"
                       
# line 331 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 331 "gdb_client_syb.cp"
                   }
# line 331 "gdb_client_syb.cp"
                   
# line 331 "gdb_client_syb.cp"
               }
# line 331 "gdb_client_syb.cp"
               
# line 331 "gdb_client_syb.cp"
           }
# line 331 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 331 "gdb_client_syb.cp"

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

  
           /*
           ** SQL STATEMENT: 13
           ** EXEC SQL AT :connect_name DECLARE :syb_curs_name CURSOR FOR :syb_st
           ** mt_id_name;
           */
# line 371 "gdb_client_syb.cp"
# line 371 "gdb_client_syb.cp"
           {
# line 371 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 371 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 371 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 371 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 371 "gdb_client_syb.cp"
               {
# line 371 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 371 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 371 "gdb_client_syb.cp"
                   ;
# line 371 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 371 "gdb_client_syb.cp"
                   _sql->moreData.curData.norebind = CS_FALSE;
# line 371 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_DYNAMIC_DECLARE_CURSOR;
# line 371 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 371 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 371 "gdb_client_syb.cp"
                   _sql->curName.fnlen = CS_NULLTERM;
# line 371 "gdb_client_syb.cp"
                   strcpy(_sql->curName.first_name, syb_curs_name);
# line 371 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 371 "gdb_client_syb.cp"
                   {
# line 371 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 371 "gdb_client_syb.cp"
                   }
# line 371 "gdb_client_syb.cp"
                   
# line 371 "gdb_client_syb.cp"
               }
# line 371 "gdb_client_syb.cp"
               
# line 371 "gdb_client_syb.cp"
           }
# line 371 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 371 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 13
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 396 "gdb_client_syb.cp"

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
  
           /*
           ** SQL STATEMENT: 14
           ** EXEC SQL END DECLARE SECTION;

           */
# line 409 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 409 "gdb_client_syb.cp"


  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_DESCRIBE_INPUT");
  
  *bind_processed = FALSE;

  if (shandle == 0) return (GDB_ERROR);

  /* set context connection name */
  sprintf((char *)connect_name,"DB%d",context_num);

  
           /*
           ** SQL STATEMENT: 15
           ** EXEC SQL SET CONNECTION :connect_name;
           */
# line 423 "gdb_client_syb.cp"
# line 423 "gdb_client_syb.cp"
           {
# line 423 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 423 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 423 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 423 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 423 "gdb_client_syb.cp"
               {
# line 423 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 423 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_CONNECTION;
# line 423 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 423 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 423 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 423 "gdb_client_syb.cp"
                   {
# line 423 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 423 "gdb_client_syb.cp"
                   }
# line 423 "gdb_client_syb.cp"
                   
# line 423 "gdb_client_syb.cp"
               }
# line 423 "gdb_client_syb.cp"
               
# line 423 "gdb_client_syb.cp"
           }
# line 423 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 423 "gdb_client_syb.cp"

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

    
           /*
           ** SQL STATEMENT: 16
           ** EXEC SQL DESCRIBE INPUT :syb_stmt_id_name USING SQL DESCRIPTOR :syb
           ** _descriptor_name;
           */
# line 439 "gdb_client_syb.cp"
# line 439 "gdb_client_syb.cp"
           {
# line 439 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 439 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 439 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 439 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 439 "gdb_client_syb.cp"
               {
# line 439 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 439 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_DESCRIBE_IN;
# line 439 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 439 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 439 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 439 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 439 "gdb_client_syb.cp"
                   {
# line 439 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 439 "gdb_client_syb.cp"
                           CS_DESCRIBE_INPUT, syb_stmt_id_name, CS_NULLTERM, 
# line 439 "gdb_client_syb.cp"
                           NULL, CS_UNUSED);
# line 439 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 439 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 439 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 439 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 439 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 439 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 439 "gdb_client_syb.cp"
                       {
# line 439 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 439 "gdb_client_syb.cp"
                           {
# line 439 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 439 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 439 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 439 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 439 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 439 "gdb_client_syb.cp"
                           break;
# line 439 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 439 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 439 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25004);
# line 439 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 439 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 439 "gdb_client_syb.cp"
                           break;
# line 439 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 439 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 439 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25005);
# line 439 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 439 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 439 "gdb_client_syb.cp"
                           break;
# line 439 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 439 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 439 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25006);
# line 439 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 439 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 439 "gdb_client_syb.cp"
                           break;
# line 439 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 439 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 439 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25009);
# line 439 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 439 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 439 "gdb_client_syb.cp"
                           break;
# line 439 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 439 "gdb_client_syb.cp"
                               _sql->descName.fnlen = CS_NULLTERM;
# line 439 "gdb_client_syb.cp"
                               strcpy(_sql->descName.first_name, 
# line 439 "gdb_client_syb.cp"
                                   syb_descriptor_name);
# line 439 "gdb_client_syb.cp"
                               _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 439 "gdb_client_syb.cp"
                                   _sql->descName.first_name, 
# line 439 "gdb_client_syb.cp"
                                   _sql->descName.fnlen, CS_USE_DESC, 
# line 439 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL, NULL, CS_UNUSED, NULL, 
# line 439 "gdb_client_syb.cp"
                                   NULL);
# line 439 "gdb_client_syb.cp"
                           break;
# line 439 "gdb_client_syb.cp"
                           }
# line 439 "gdb_client_syb.cp"
                           
# line 439 "gdb_client_syb.cp"
                       }
# line 439 "gdb_client_syb.cp"
                       
# line 439 "gdb_client_syb.cp"
                       if ((_sql->retcode != CS_END_RESULTS) && (_sql->retcode 
# line 439 "gdb_client_syb.cp"
                           != CS_CANCELED) && (_sql->retcode != 
# line 439 "gdb_client_syb.cp"
                           CS_RET_HAFAILOVER) && (_sql->resloop != CS_FALSE))
# line 439 "gdb_client_syb.cp"
                       {
# line 439 "gdb_client_syb.cp"
                           _sql->retcode = ct_cancel(NULL, _sql->conn.command, 
# line 439 "gdb_client_syb.cp"
                               CS_CANCEL_ALL);
# line 439 "gdb_client_syb.cp"
                           }
# line 439 "gdb_client_syb.cp"
                            else {
# line 439 "gdb_client_syb.cp"
                           if (((_sql->retcode != CS_CANCELED) && 
# line 439 "gdb_client_syb.cp"
                               (_sql->retcode != CS_RET_HAFAILOVER)))
# line 439 "gdb_client_syb.cp"
                           {
# line 439 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 439 "gdb_client_syb.cp"
                           }
# line 439 "gdb_client_syb.cp"
                           
# line 439 "gdb_client_syb.cp"
                       }
# line 439 "gdb_client_syb.cp"
                       
# line 439 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 439 "gdb_client_syb.cp"
                   }
# line 439 "gdb_client_syb.cp"
                   
# line 439 "gdb_client_syb.cp"
               }
# line 439 "gdb_client_syb.cp"
               
# line 439 "gdb_client_syb.cp"
           }
# line 439 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 439 "gdb_client_syb.cp"


    if (sqlca.sqlcode < 0)
    {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","DESCRIBE INPUT: %", sqlca.sqlerrm.sqlerrmc);
      return (GDB_ERROR);
    }

    /* Determine how many bind variables there are */
    
           /*
           ** SQL STATEMENT: 17
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name :descnt = COUNT;

           */
# line 448 "gdb_client_syb.cp"
# line 448 "gdb_client_syb.cp"
           {
# line 448 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 448 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 448 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 448 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 448 "gdb_client_syb.cp"
               {
# line 448 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 448 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 448 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 448 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 448 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 448 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 448 "gdb_client_syb.cp"
                   {
# line 448 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.count = 0;
# line 448 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 448 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 448 "gdb_client_syb.cp"
                           CS_GETCNT, CS_UNUSED, NULL, &descnt, CS_UNUSED, 
# line 448 "gdb_client_syb.cp"
                           NULL, NULL);
# line 448 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 448 "gdb_client_syb.cp"
                   }
# line 448 "gdb_client_syb.cp"
                   
# line 448 "gdb_client_syb.cp"
               }
# line 448 "gdb_client_syb.cp"
               
# line 448 "gdb_client_syb.cp"
           }
# line 448 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 448 "gdb_client_syb.cp"

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
	  
           /*
           ** SQL STATEMENT: 18
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           ** 		                      :ddatatype   = TYPE,
           ** 		                      :ddatalen    = LENGTH,
           **                               :dprec       = PRECISION,
           **                               :dscale      = SCALE;

           */
# line 483 "gdb_client_syb.cp"
# line 479 "gdb_client_syb.cp"
           {
# line 479 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 479 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 479 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 479 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 479 "gdb_client_syb.cp"
               {
# line 479 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 479 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 479 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 479 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 479 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 479 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 479 "gdb_client_syb.cp"
                   {
# line 479 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 479 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 479 "gdb_client_syb.cp"
                           CS_GETATTR, col_num, &_sql->dfmtUTIL, NULL, 
# line 479 "gdb_client_syb.cp"
                           CS_UNUSED, NULL, NULL);
# line 479 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 479 "gdb_client_syb.cp"
                       {
# line 479 "gdb_client_syb.cp"
                           dscale = _sql->dfmtUTIL.scale;
# line 479 "gdb_client_syb.cp"
                       }
# line 479 "gdb_client_syb.cp"
                       
# line 479 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 479 "gdb_client_syb.cp"
                       {
# line 479 "gdb_client_syb.cp"
                           dprec = _sql->dfmtUTIL.precision;
# line 479 "gdb_client_syb.cp"
                       }
# line 479 "gdb_client_syb.cp"
                       
# line 479 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 479 "gdb_client_syb.cp"
                       {
# line 479 "gdb_client_syb.cp"
                           ddatalen = _sql->dfmtUTIL.maxlength;
# line 479 "gdb_client_syb.cp"
                       }
# line 479 "gdb_client_syb.cp"
                       
# line 479 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 479 "gdb_client_syb.cp"
                       {
# line 479 "gdb_client_syb.cp"
                           ddatatype = _sqldtcnv(_sql, _sql->dfmtUTIL.datatype,
# line 479 "gdb_client_syb.cp"
                                CS_GET);
# line 479 "gdb_client_syb.cp"
                       }
# line 479 "gdb_client_syb.cp"
                       
# line 479 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 479 "gdb_client_syb.cp"
                   }
# line 479 "gdb_client_syb.cp"
                   
# line 479 "gdb_client_syb.cp"
               }
# line 479 "gdb_client_syb.cp"
               
# line 479 "gdb_client_syb.cp"
           }
# line 479 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 483 "gdb_client_syb.cp"


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
	    
           /*
           ** SQL STATEMENT: 19
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **             DATA = :text_val,
           **             INDICATOR = :ind_val;
           */
# line 572 "gdb_client_syb.cp"
# line 570 "gdb_client_syb.cp"
           {
# line 570 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 570 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 570 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 570 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 570 "gdb_client_syb.cp"
               {
# line 570 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 570 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 570 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 570 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 570 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 570 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 570 "gdb_client_syb.cp"
                   {
# line 570 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.count = 0;
# line 570 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.maxlength = 
# line 570 "gdb_client_syb.cp"
                       _sql_MIN(16384,_SQL_PCHAR_LEN);
# line 570 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 570 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.status = CS_INPUTVALUE;
# line 570 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtNULLCHAR.name, 1);
# line 570 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.namelen = 0;
# line 570 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 570 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 570 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtNULLCHAR, 
# line 570 "gdb_client_syb.cp"
                       SQLNULLSTR(text_val), CS_NULLTERM, NULL, &ind_val);
# line 570 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtNULLCHAR, CS_CHAR_TYPE);
# line 570 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 570 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 570 "gdb_client_syb.cp"
                   }
# line 570 "gdb_client_syb.cp"
                   
# line 570 "gdb_client_syb.cp"
               }
# line 570 "gdb_client_syb.cp"
               
# line 570 "gdb_client_syb.cp"
           }
# line 570 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 572 "gdb_client_syb.cp"

	    break;

	  case SB_INTEGER :
	    long_val = atoi( text_val );
	    
           /*
           ** SQL STATEMENT: 20
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **             DATA = :long_val,
           **             INDICATOR = :ind_val;
           */
# line 579 "gdb_client_syb.cp"
# line 577 "gdb_client_syb.cp"
           {
# line 577 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 577 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 577 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 577 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 577 "gdb_client_syb.cp"
               {
# line 577 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 577 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 577 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 577 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 577 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 577 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 577 "gdb_client_syb.cp"
                   {
# line 577 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.count = 0;
# line 577 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.status = CS_INPUTVALUE;
# line 577 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_INT_TYPE.name, 1);
# line 577 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.namelen = 0;
# line 577 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 577 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 577 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_INT_TYPE, 
# line 577 "gdb_client_syb.cp"
                           &long_val, CS_UNUSED, NULL, &ind_val);
# line 577 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_INT_TYPE, CS_INT_TYPE);
# line 577 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 577 "gdb_client_syb.cp"
                   }
# line 577 "gdb_client_syb.cp"
                   
# line 577 "gdb_client_syb.cp"
               }
# line 577 "gdb_client_syb.cp"
               
# line 577 "gdb_client_syb.cp"
           }
# line 577 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 579 "gdb_client_syb.cp"

		break;

	  case SB_SMALLINT :
	  case SB_TINYINT :
	  case SB_BIT :
	    short_val = (short) atoi( text_val );
	    
           /*
           ** SQL STATEMENT: 21
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **             DATA = :short_val,
           **             INDICATOR = :ind_val;
           */
# line 588 "gdb_client_syb.cp"
# line 586 "gdb_client_syb.cp"
           {
# line 586 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 586 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 586 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 586 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 586 "gdb_client_syb.cp"
               {
# line 586 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 586 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 586 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 586 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 586 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 586 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 586 "gdb_client_syb.cp"
                   {
# line 586 "gdb_client_syb.cp"
                       _sql->dfmtCS_SMALLINT_TYPE.count = 0;
# line 586 "gdb_client_syb.cp"
                       _sql->dfmtCS_SMALLINT_TYPE.status = CS_INPUTVALUE;
# line 586 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_SMALLINT_TYPE.name, 1);
# line 586 "gdb_client_syb.cp"
                       _sql->dfmtCS_SMALLINT_TYPE.namelen = 0;
# line 586 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 586 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 586 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_SMALLINT_TYPE, 
# line 586 "gdb_client_syb.cp"
                           &short_val, CS_UNUSED, NULL, &ind_val);
# line 586 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_SMALLINT_TYPE, 
# line 586 "gdb_client_syb.cp"
                           CS_SMALLINT_TYPE);
# line 586 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 586 "gdb_client_syb.cp"
                   }
# line 586 "gdb_client_syb.cp"
                   
# line 586 "gdb_client_syb.cp"
               }
# line 586 "gdb_client_syb.cp"
               
# line 586 "gdb_client_syb.cp"
           }
# line 586 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 588 "gdb_client_syb.cp"

	    break;

	  case SB_SMALLMONEY :
	  case SB_REAL_OLD :
	  case SB_REAL :
	    float_val = (float) atof( text_val );
	    
           /*
           ** SQL STATEMENT: 22
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **             DATA = :float_val,
           **             INDICATOR = :ind_val;
           */
# line 597 "gdb_client_syb.cp"
# line 595 "gdb_client_syb.cp"
           {
# line 595 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 595 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 595 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 595 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 595 "gdb_client_syb.cp"
               {
# line 595 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 595 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 595 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 595 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 595 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 595 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 595 "gdb_client_syb.cp"
                   {
# line 595 "gdb_client_syb.cp"
                       _sql->dfmtCS_REAL_TYPE.count = 0;
# line 595 "gdb_client_syb.cp"
                       _sql->dfmtCS_REAL_TYPE.status = CS_INPUTVALUE;
# line 595 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_REAL_TYPE.name, 1);
# line 595 "gdb_client_syb.cp"
                       _sql->dfmtCS_REAL_TYPE.namelen = 0;
# line 595 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 595 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 595 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_REAL_TYPE, 
# line 595 "gdb_client_syb.cp"
                           &float_val, CS_UNUSED, NULL, &ind_val);
# line 595 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_REAL_TYPE, CS_REAL_TYPE);
# line 595 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 595 "gdb_client_syb.cp"
                   }
# line 595 "gdb_client_syb.cp"
                   
# line 595 "gdb_client_syb.cp"
               }
# line 595 "gdb_client_syb.cp"
               
# line 595 "gdb_client_syb.cp"
           }
# line 595 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 597 "gdb_client_syb.cp"

	    break;

	  case SB_FLOAT :
	  case SB_MONEY :
	  case SB_NUMERIC :
	  case SB_DECIMAL :
	    dbl_val = (double) atof( text_val );
	    
           /*
           ** SQL STATEMENT: 23
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **             DATA = :dbl_val,
           **             INDICATOR= :ind_val;
           */
# line 607 "gdb_client_syb.cp"
# line 605 "gdb_client_syb.cp"
           {
# line 605 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 605 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 605 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 605 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 605 "gdb_client_syb.cp"
               {
# line 605 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 605 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 605 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 605 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 605 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 605 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 605 "gdb_client_syb.cp"
                   {
# line 605 "gdb_client_syb.cp"
                       _sql->dfmtCS_FLOAT_TYPE.count = 0;
# line 605 "gdb_client_syb.cp"
                       _sql->dfmtCS_FLOAT_TYPE.status = CS_INPUTVALUE;
# line 605 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_FLOAT_TYPE.name, 1);
# line 605 "gdb_client_syb.cp"
                       _sql->dfmtCS_FLOAT_TYPE.namelen = 0;
# line 605 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 605 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 605 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_FLOAT_TYPE, 
# line 605 "gdb_client_syb.cp"
                           &dbl_val, CS_UNUSED, NULL, &ind_val);
# line 605 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_FLOAT_TYPE, CS_FLOAT_TYPE);
# line 605 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 605 "gdb_client_syb.cp"
                   }
# line 605 "gdb_client_syb.cp"
                   
# line 605 "gdb_client_syb.cp"
               }
# line 605 "gdb_client_syb.cp"
               
# line 605 "gdb_client_syb.cp"
           }
# line 605 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 607 "gdb_client_syb.cp"

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

  
           /*
           ** SQL STATEMENT: 23
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 664 "gdb_client_syb.cp"

    CS_INT          descnt;
    CS_INT          dcol;
    CS_INT          ddatatype;
    CS_INT          ddatalen;               
    CS_INT          dprec;
    CS_INT          dscale;
    CS_INT          dnullable;
    CS_CHAR         dname[MAX_COLNAME_LEN];
  
           /*
           ** SQL STATEMENT: 24
           ** EXEC SQL END DECLARE SECTION;

           */
# line 673 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 673 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 25
           ** EXEC SQL SET CONNECTION :connect_name;
           */
# line 691 "gdb_client_syb.cp"
# line 691 "gdb_client_syb.cp"
           {
# line 691 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 691 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 691 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 691 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 691 "gdb_client_syb.cp"
               {
# line 691 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 691 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_CONNECTION;
# line 691 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 691 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 691 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 691 "gdb_client_syb.cp"
                   {
# line 691 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 691 "gdb_client_syb.cp"
                   }
# line 691 "gdb_client_syb.cp"
                   
# line 691 "gdb_client_syb.cp"
               }
# line 691 "gdb_client_syb.cp"
               
# line 691 "gdb_client_syb.cp"
           }
# line 691 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 691 "gdb_client_syb.cp"

  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  sprintf(syb_stmt_id_name,"S%d",shandle);
  sprintf(syb_descriptor_name,"SD%d",shandle);

  
           /*
           ** SQL STATEMENT: 26
           ** EXEC SQL DESCRIBE OUTPUT :syb_stmt_id_name USING SQL DESCRIPTOR :sy
           ** b_descriptor_name ;
           */
# line 697 "gdb_client_syb.cp"
# line 697 "gdb_client_syb.cp"
           {
# line 697 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 697 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 697 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 697 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 697 "gdb_client_syb.cp"
               {
# line 697 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 697 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_DESCRIBE_OUT;
# line 697 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 697 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 697 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 697 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 697 "gdb_client_syb.cp"
                   {
# line 697 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 697 "gdb_client_syb.cp"
                           CS_DESCRIBE_OUTPUT, syb_stmt_id_name, CS_NULLTERM, 
# line 697 "gdb_client_syb.cp"
                           NULL, CS_UNUSED);
# line 697 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 697 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 697 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 697 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 697 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 697 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 697 "gdb_client_syb.cp"
                       {
# line 697 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 697 "gdb_client_syb.cp"
                           {
# line 697 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 697 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 697 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 697 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 697 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 697 "gdb_client_syb.cp"
                           break;
# line 697 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 697 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 697 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25004);
# line 697 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 697 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 697 "gdb_client_syb.cp"
                           break;
# line 697 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 697 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 697 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25005);
# line 697 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 697 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 697 "gdb_client_syb.cp"
                           break;
# line 697 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 697 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 697 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25006);
# line 697 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 697 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 697 "gdb_client_syb.cp"
                           break;
# line 697 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 697 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 697 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25009);
# line 697 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 697 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 697 "gdb_client_syb.cp"
                           break;
# line 697 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 697 "gdb_client_syb.cp"
                               _sql->descName.fnlen = CS_NULLTERM;
# line 697 "gdb_client_syb.cp"
                               strcpy(_sql->descName.first_name, 
# line 697 "gdb_client_syb.cp"
                                   syb_descriptor_name);
# line 697 "gdb_client_syb.cp"
                               _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 697 "gdb_client_syb.cp"
                                   _sql->descName.first_name, 
# line 697 "gdb_client_syb.cp"
                                   _sql->descName.fnlen, CS_USE_DESC, 
# line 697 "gdb_client_syb.cp"
                                   CS_UNUSED, NULL, NULL, CS_UNUSED, NULL, 
# line 697 "gdb_client_syb.cp"
                                   NULL);
# line 697 "gdb_client_syb.cp"
                           break;
# line 697 "gdb_client_syb.cp"
                           }
# line 697 "gdb_client_syb.cp"
                           
# line 697 "gdb_client_syb.cp"
                       }
# line 697 "gdb_client_syb.cp"
                       
# line 697 "gdb_client_syb.cp"
                       if ((_sql->retcode != CS_END_RESULTS) && (_sql->retcode 
# line 697 "gdb_client_syb.cp"
                           != CS_CANCELED) && (_sql->retcode != 
# line 697 "gdb_client_syb.cp"
                           CS_RET_HAFAILOVER) && (_sql->resloop != CS_FALSE))
# line 697 "gdb_client_syb.cp"
                       {
# line 697 "gdb_client_syb.cp"
                           _sql->retcode = ct_cancel(NULL, _sql->conn.command, 
# line 697 "gdb_client_syb.cp"
                               CS_CANCEL_ALL);
# line 697 "gdb_client_syb.cp"
                           }
# line 697 "gdb_client_syb.cp"
                            else {
# line 697 "gdb_client_syb.cp"
                           if (((_sql->retcode != CS_CANCELED) && 
# line 697 "gdb_client_syb.cp"
                               (_sql->retcode != CS_RET_HAFAILOVER)))
# line 697 "gdb_client_syb.cp"
                           {
# line 697 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 697 "gdb_client_syb.cp"
                           }
# line 697 "gdb_client_syb.cp"
                           
# line 697 "gdb_client_syb.cp"
                       }
# line 697 "gdb_client_syb.cp"
                       
# line 697 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 697 "gdb_client_syb.cp"
                   }
# line 697 "gdb_client_syb.cp"
                   
# line 697 "gdb_client_syb.cp"
               }
# line 697 "gdb_client_syb.cp"
               
# line 697 "gdb_client_syb.cp"
           }
# line 697 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 697 "gdb_client_syb.cp"

  if (sqlca.sqlcode < 0) {
    iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE,"%s%s","DESCRIBE OUTPUT: %",sqlca.sqlerrm.sqlerrmc);
    return (GDB_ERROR);
  }

  /* get the actual # of columns */
  
           /*
           ** SQL STATEMENT: 27
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name :descnt = COUNT;

           */
# line 704 "gdb_client_syb.cp"
# line 704 "gdb_client_syb.cp"
           {
# line 704 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 704 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 704 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 704 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 704 "gdb_client_syb.cp"
               {
# line 704 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 704 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 704 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 704 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 704 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 704 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 704 "gdb_client_syb.cp"
                   {
# line 704 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.count = 0;
# line 704 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 704 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 704 "gdb_client_syb.cp"
                           CS_GETCNT, CS_UNUSED, NULL, &descnt, CS_UNUSED, 
# line 704 "gdb_client_syb.cp"
                           NULL, NULL);
# line 704 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 704 "gdb_client_syb.cp"
                   }
# line 704 "gdb_client_syb.cp"
                   
# line 704 "gdb_client_syb.cp"
               }
# line 704 "gdb_client_syb.cp"
               
# line 704 "gdb_client_syb.cp"
           }
# line 704 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 704 "gdb_client_syb.cp"

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
    
           /*
           ** SQL STATEMENT: 28
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :dcol 
           **                             :dname       = NAME,
           **                             :ddatatype   = TYPE,
           **                             :ddatalen    = LENGTH,
           **                             :dprec       = PRECISION,
           **                             :dscale      = SCALE,
           **                             :dnullable   = NULLABLE;

           */
# line 754 "gdb_client_syb.cp"
# line 748 "gdb_client_syb.cp"
           {
# line 748 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 748 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 748 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 748 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 748 "gdb_client_syb.cp"
               {
# line 748 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 748 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 748 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 748 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 748 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 748 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 748 "gdb_client_syb.cp"
                   {
# line 748 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 748 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 748 "gdb_client_syb.cp"
                           CS_GETATTR, dcol, &_sql->dfmtUTIL, NULL, CS_UNUSED, 
# line 748 "gdb_client_syb.cp"
                           NULL, NULL);
# line 748 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 748 "gdb_client_syb.cp"
                       {
# line 748 "gdb_client_syb.cp"
                           dnullable = _sql->dfmtUTIL.status & CS_CANBENULL ? 
# line 748 "gdb_client_syb.cp"
                               1 : 0;
# line 748 "gdb_client_syb.cp"
                       }
# line 748 "gdb_client_syb.cp"
                       
# line 748 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 748 "gdb_client_syb.cp"
                       {
# line 748 "gdb_client_syb.cp"
                           dscale = _sql->dfmtUTIL.scale;
# line 748 "gdb_client_syb.cp"
                       }
# line 748 "gdb_client_syb.cp"
                       
# line 748 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 748 "gdb_client_syb.cp"
                       {
# line 748 "gdb_client_syb.cp"
                           dprec = _sql->dfmtUTIL.precision;
# line 748 "gdb_client_syb.cp"
                       }
# line 748 "gdb_client_syb.cp"
                       
# line 748 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 748 "gdb_client_syb.cp"
                       {
# line 748 "gdb_client_syb.cp"
                           ddatalen = _sql->dfmtUTIL.maxlength;
# line 748 "gdb_client_syb.cp"
                       }
# line 748 "gdb_client_syb.cp"
                       
# line 748 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 748 "gdb_client_syb.cp"
                       {
# line 748 "gdb_client_syb.cp"
                           ddatatype = _sqldtcnv(_sql, _sql->dfmtUTIL.datatype,
# line 748 "gdb_client_syb.cp"
                                CS_GET);
# line 748 "gdb_client_syb.cp"
                       }
# line 748 "gdb_client_syb.cp"
                       
# line 748 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 748 "gdb_client_syb.cp"
                       {
# line 748 "gdb_client_syb.cp"
                           strcpy(dname, _sql->dfmtUTIL.name);
# line 748 "gdb_client_syb.cp"
                       }
# line 748 "gdb_client_syb.cp"
                       
# line 748 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 748 "gdb_client_syb.cp"
                   }
# line 748 "gdb_client_syb.cp"
                   
# line 748 "gdb_client_syb.cp"
               }
# line 748 "gdb_client_syb.cp"
               
# line 748 "gdb_client_syb.cp"
           }
# line 748 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 754 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 28
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 851 "gdb_client_syb.cp"

    CS_INT         row_size;
  
           /*
           ** SQL STATEMENT: 29
           ** EXEC SQL END DECLARE SECTION;

           */
# line 853 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 853 "gdb_client_syb.cp"

    
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

  
           /*
           ** SQL STATEMENT: 30
           ** EXEC SQL AT :connect_name OPEN :syb_curs_name row_count = :row_size
           ** 
           **        USING SQL DESCRIPTOR :syb_descriptor_name;
           */
# line 877 "gdb_client_syb.cp"
# line 876 "gdb_client_syb.cp"
           {
# line 876 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 876 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 876 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 876 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 876 "gdb_client_syb.cp"
               {
# line 876 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 876 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_OPEN_WDESC_STMT;
# line 876 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 876 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 876 "gdb_client_syb.cp"
                   _sql->curName.fnlen = CS_NULLTERM;
# line 876 "gdb_client_syb.cp"
                   strcpy(_sql->curName.first_name, syb_curs_name);
# line 876 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 876 "gdb_client_syb.cp"
                   {
# line 876 "gdb_client_syb.cp"
                       _sql->retcode = ct_cursor(_sql->conn.command, 
# line 876 "gdb_client_syb.cp"
                           CS_CURSOR_ROWS, NULL, CS_UNUSED, NULL, CS_UNUSED, 
# line 876 "gdb_client_syb.cp"
                           row_size);
# line 876 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 876 "gdb_client_syb.cp"
                       {
# line 876 "gdb_client_syb.cp"
                           if (_sql->stmtData.persistent == CS_TRUE)
# line 876 "gdb_client_syb.cp"
                           {
# line 876 "gdb_client_syb.cp"
                               _sql->retcode = ct_cursor(_sql->conn.command, 
# line 876 "gdb_client_syb.cp"
                                   CS_CURSOR_OPEN, NULL, CS_UNUSED, NULL, 
# line 876 "gdb_client_syb.cp"
                                   CS_UNUSED, CS_RESTORE_OPEN);
# line 876 "gdb_client_syb.cp"
                               }
# line 876 "gdb_client_syb.cp"
                                else {
# line 876 "gdb_client_syb.cp"
                               _sql->retcode = ct_cursor(_sql->conn.command, 
# line 876 "gdb_client_syb.cp"
                                   CS_CURSOR_OPEN, NULL, CS_UNUSED, NULL, 
# line 876 "gdb_client_syb.cp"
                                   CS_UNUSED, CS_UNUSED);
# line 876 "gdb_client_syb.cp"
                           }
# line 876 "gdb_client_syb.cp"
                           
# line 876 "gdb_client_syb.cp"
                       }
# line 876 "gdb_client_syb.cp"
                       
# line 876 "gdb_client_syb.cp"
                       _sql->descName.fnlen = CS_NULLTERM;
# line 876 "gdb_client_syb.cp"
                       strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 876 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 876 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 876 "gdb_client_syb.cp"
                           CS_USE_DESC, CS_UNUSED, NULL, NULL, CS_UNUSED, NULL,
# line 876 "gdb_client_syb.cp"
                            NULL);
# line 876 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 876 "gdb_client_syb.cp"
                       {
# line 876 "gdb_client_syb.cp"
                           _sql->retcode = ct_send(_sql->conn.command);
# line 876 "gdb_client_syb.cp"
                           _sql->hastate = (_sql->retcode == 
# line 876 "gdb_client_syb.cp"
                               CS_RET_HAFAILOVER);
# line 876 "gdb_client_syb.cp"
                       }
# line 876 "gdb_client_syb.cp"
                       
# line 876 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 876 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 876 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 876 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 876 "gdb_client_syb.cp"
                       {
# line 876 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 876 "gdb_client_syb.cp"
                           {
# line 876 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 876 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 876 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 876 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 876 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 876 "gdb_client_syb.cp"
                           break;
# line 876 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 876 "gdb_client_syb.cp"
                               _sql->resloop = CS_FALSE;
# line 876 "gdb_client_syb.cp"
                           break;
# line 876 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 876 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 876 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25005);
# line 876 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 876 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 876 "gdb_client_syb.cp"
                           break;
# line 876 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 876 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 876 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25006);
# line 876 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 876 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 876 "gdb_client_syb.cp"
                           break;
# line 876 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 876 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 876 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25009);
# line 876 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 876 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 876 "gdb_client_syb.cp"
                           break;
# line 876 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 876 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 876 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25010);
# line 876 "gdb_client_syb.cp"
                           break;
# line 876 "gdb_client_syb.cp"
                           }
# line 876 "gdb_client_syb.cp"
                           
# line 876 "gdb_client_syb.cp"
                       }
# line 876 "gdb_client_syb.cp"
                       
# line 876 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 876 "gdb_client_syb.cp"
                   }
# line 876 "gdb_client_syb.cp"
                   
# line 876 "gdb_client_syb.cp"
               }
# line 876 "gdb_client_syb.cp"
               
# line 876 "gdb_client_syb.cp"
           }
# line 876 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 877 "gdb_client_syb.cp"


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
  
           /*
           ** SQL STATEMENT: 31
           ** EXEC SQL AT :connect_name FETCH :syb_curs_name INTO SQL DESCRIPTOR 
           ** :syb_descriptor_name;
           */
# line 916 "gdb_client_syb.cp"
# line 916 "gdb_client_syb.cp"
           {
# line 916 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 916 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 916 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 916 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 916 "gdb_client_syb.cp"
               {
# line 916 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 916 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_FETCH_IDESC_STMT;
# line 916 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 916 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 916 "gdb_client_syb.cp"
                   _sql->curName.fnlen = CS_NULLTERM;
# line 916 "gdb_client_syb.cp"
                   strcpy(_sql->curName.first_name, syb_curs_name);
# line 916 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 916 "gdb_client_syb.cp"
                   {
# line 916 "gdb_client_syb.cp"
                       _sql->doDecl = CS_FALSE;
# line 916 "gdb_client_syb.cp"
                       if ((_sql->stmtData.bind == CS_TRUE) ||
# line 916 "gdb_client_syb.cp"
                       (_sql->moreData.curData.norebind == CS_FALSE))
# line 916 "gdb_client_syb.cp"
                       {
# line 916 "gdb_client_syb.cp"
                           _sql->descName.fnlen = CS_NULLTERM;
# line 916 "gdb_client_syb.cp"
                           strcpy(_sql->descName.first_name, 
# line 916 "gdb_client_syb.cp"
                               syb_descriptor_name);
# line 916 "gdb_client_syb.cp"
                           _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 916 "gdb_client_syb.cp"
                               _sql->descName.first_name, _sql->descName.fnlen,
# line 916 "gdb_client_syb.cp"
                                CS_USE_DESC, CS_UNUSED, NULL, NULL, CS_UNUSED, 
# line 916 "gdb_client_syb.cp"
                               NULL, NULL);
# line 916 "gdb_client_syb.cp"
                           if (_sql->stmtData.bind == CS_TRUE)
# line 916 "gdb_client_syb.cp"
                           {
# line 916 "gdb_client_syb.cp"
                               _sql->stmtData.bind = CS_FALSE;
# line 916 "gdb_client_syb.cp"
                               _sql->doDecl = CS_TRUE;
# line 916 "gdb_client_syb.cp"
                           }
# line 916 "gdb_client_syb.cp"
                           
# line 916 "gdb_client_syb.cp"
                       }
# line 916 "gdb_client_syb.cp"
                       
# line 916 "gdb_client_syb.cp"
                       _sql->retcode = ct_fetch(_sql->conn.command, CS_UNUSED, 
# line 916 "gdb_client_syb.cp"
                           CS_UNUSED, CS_UNUSED, &_sql->rowsread);
# line 916 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 916 "gdb_client_syb.cp"
                       if ((_sql->retcode == CS_END_DATA)||(_sql->retcode == 
# line 916 "gdb_client_syb.cp"
                       CS_FAIL)||
# line 916 "gdb_client_syb.cp"
                       (_sql->retcode == CS_SCROLL_CURSOR_ENDS))
# line 916 "gdb_client_syb.cp"
                       {
# line 916 "gdb_client_syb.cp"
                           _sql->retcode = _sqlResults(_sql);
# line 916 "gdb_client_syb.cp"
                       }
# line 916 "gdb_client_syb.cp"
                       
# line 916 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 916 "gdb_client_syb.cp"
                       sqlca.sqlerrd[2] = _sql->rowsread;
# line 916 "gdb_client_syb.cp"
                   }
# line 916 "gdb_client_syb.cp"
                   
# line 916 "gdb_client_syb.cp"
               }
# line 916 "gdb_client_syb.cp"
               
# line 916 "gdb_client_syb.cp"
           }
# line 916 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 916 "gdb_client_syb.cp"


  if (sqlca.sqlcode < 0) {
    sql_open_cursor(curs_name,shandle);
    if (sqlca.sqlcode != 0) return (GDB_EXT_ERROR);
    sprintf(syb_descriptor_name,"SD%d",shandle);
    
           /*
           ** SQL STATEMENT: 32
           ** EXEC SQL AT :connect_name FETCH :syb_curs_name INTO SQL DESCRIPTOR 
           ** :syb_descriptor_name;
           */
# line 922 "gdb_client_syb.cp"
# line 922 "gdb_client_syb.cp"
           {
# line 922 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 922 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 922 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 922 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 922 "gdb_client_syb.cp"
               {
# line 922 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 922 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_FETCH_IDESC_STMT;
# line 922 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 922 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 922 "gdb_client_syb.cp"
                   _sql->curName.fnlen = CS_NULLTERM;
# line 922 "gdb_client_syb.cp"
                   strcpy(_sql->curName.first_name, syb_curs_name);
# line 922 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 922 "gdb_client_syb.cp"
                   {
# line 922 "gdb_client_syb.cp"
                       _sql->doDecl = CS_FALSE;
# line 922 "gdb_client_syb.cp"
                       if ((_sql->stmtData.bind == CS_TRUE) ||
# line 922 "gdb_client_syb.cp"
                       (_sql->moreData.curData.norebind == CS_FALSE))
# line 922 "gdb_client_syb.cp"
                       {
# line 922 "gdb_client_syb.cp"
                           _sql->descName.fnlen = CS_NULLTERM;
# line 922 "gdb_client_syb.cp"
                           strcpy(_sql->descName.first_name, 
# line 922 "gdb_client_syb.cp"
                               syb_descriptor_name);
# line 922 "gdb_client_syb.cp"
                           _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 922 "gdb_client_syb.cp"
                               _sql->descName.first_name, _sql->descName.fnlen,
# line 922 "gdb_client_syb.cp"
                                CS_USE_DESC, CS_UNUSED, NULL, NULL, CS_UNUSED, 
# line 922 "gdb_client_syb.cp"
                               NULL, NULL);
# line 922 "gdb_client_syb.cp"
                           if (_sql->stmtData.bind == CS_TRUE)
# line 922 "gdb_client_syb.cp"
                           {
# line 922 "gdb_client_syb.cp"
                               _sql->stmtData.bind = CS_FALSE;
# line 922 "gdb_client_syb.cp"
                               _sql->doDecl = CS_TRUE;
# line 922 "gdb_client_syb.cp"
                           }
# line 922 "gdb_client_syb.cp"
                           
# line 922 "gdb_client_syb.cp"
                       }
# line 922 "gdb_client_syb.cp"
                       
# line 922 "gdb_client_syb.cp"
                       _sql->retcode = ct_fetch(_sql->conn.command, CS_UNUSED, 
# line 922 "gdb_client_syb.cp"
                           CS_UNUSED, CS_UNUSED, &_sql->rowsread);
# line 922 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 922 "gdb_client_syb.cp"
                       if ((_sql->retcode == CS_END_DATA)||(_sql->retcode == 
# line 922 "gdb_client_syb.cp"
                       CS_FAIL)||
# line 922 "gdb_client_syb.cp"
                       (_sql->retcode == CS_SCROLL_CURSOR_ENDS))
# line 922 "gdb_client_syb.cp"
                       {
# line 922 "gdb_client_syb.cp"
                           _sql->retcode = _sqlResults(_sql);
# line 922 "gdb_client_syb.cp"
                       }
# line 922 "gdb_client_syb.cp"
                       
# line 922 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 922 "gdb_client_syb.cp"
                       sqlca.sqlerrd[2] = _sql->rowsread;
# line 922 "gdb_client_syb.cp"
                   }
# line 922 "gdb_client_syb.cp"
                   
# line 922 "gdb_client_syb.cp"
               }
# line 922 "gdb_client_syb.cp"
               
# line 922 "gdb_client_syb.cp"
           }
# line 922 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 922 "gdb_client_syb.cp"

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
  
           /*
           ** SQL STATEMENT: 33
           ** EXEC SQL SET CONNECTION :connect_name;
           */
# line 1026 "gdb_client_syb.cp"
# line 1026 "gdb_client_syb.cp"
           {
# line 1026 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1026 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1026 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1026 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1026 "gdb_client_syb.cp"
               {
# line 1026 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1026 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_CONNECTION;
# line 1026 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1026 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1026 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1026 "gdb_client_syb.cp"
                   {
# line 1026 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1026 "gdb_client_syb.cp"
                   }
# line 1026 "gdb_client_syb.cp"
                   
# line 1026 "gdb_client_syb.cp"
               }
# line 1026 "gdb_client_syb.cp"
               
# line 1026 "gdb_client_syb.cp"
           }
# line 1026 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1026 "gdb_client_syb.cp"

  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  
           /*
           ** SQL STATEMENT: 34
           ** EXEC SQL DEALLOCATE DESCRIPTOR :syb_descriptor_name;
           */
# line 1029 "gdb_client_syb.cp"
# line 1029 "gdb_client_syb.cp"
           {
# line 1029 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1029 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1029 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1029 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1029 "gdb_client_syb.cp"
               {
# line 1029 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1029 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_DEALLOCATE_DESCRIPTOR;
# line 1029 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1029 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1029 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1029 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1029 "gdb_client_syb.cp"
                   {
# line 1029 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1029 "gdb_client_syb.cp"
                   }
# line 1029 "gdb_client_syb.cp"
                   
# line 1029 "gdb_client_syb.cp"
               }
# line 1029 "gdb_client_syb.cp"
               
# line 1029 "gdb_client_syb.cp"
           }
# line 1029 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1029 "gdb_client_syb.cp"

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

  
           /*
           ** SQL STATEMENT: 35
           ** EXEC SQL AT :connect_name CLOSE :syb_curs_name;
           */
# line 1179 "gdb_client_syb.cp"
# line 1179 "gdb_client_syb.cp"
           {
# line 1179 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1179 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1179 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1179 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1179 "gdb_client_syb.cp"
               {
# line 1179 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1179 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_CLOSE_STMT;
# line 1179 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1179 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1179 "gdb_client_syb.cp"
                   _sql->curName.fnlen = CS_NULLTERM;
# line 1179 "gdb_client_syb.cp"
                   strcpy(_sql->curName.first_name, syb_curs_name);
# line 1179 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1179 "gdb_client_syb.cp"
                   {
# line 1179 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1179 "gdb_client_syb.cp"
                   }
# line 1179 "gdb_client_syb.cp"
                   
# line 1179 "gdb_client_syb.cp"
               }
# line 1179 "gdb_client_syb.cp"
               
# line 1179 "gdb_client_syb.cp"
           }
# line 1179 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1179 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 36
           ** EXEC SQL DISCONNECT :connect_name;
           */
# line 1203 "gdb_client_syb.cp"
# line 1203 "gdb_client_syb.cp"
           {
# line 1203 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1203 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1203 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1203 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1203 "gdb_client_syb.cp"
               {
# line 1203 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1203 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_DISCONNECT;
# line 1203 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1203 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1203 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1203 "gdb_client_syb.cp"
                   {
# line 1203 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1203 "gdb_client_syb.cp"
                   }
# line 1203 "gdb_client_syb.cp"
                   
# line 1203 "gdb_client_syb.cp"
               }
# line 1203 "gdb_client_syb.cp"
               
# line 1203 "gdb_client_syb.cp"
           }
# line 1203 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1203 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 37
           ** EXEC SQL AT :connect_name EXECUTE IMMEDIATE :syb_sql_stmt;
           */
# line 1239 "gdb_client_syb.cp"
# line 1239 "gdb_client_syb.cp"
           {
# line 1239 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1239 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1239 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1239 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1239 "gdb_client_syb.cp"
               {
# line 1239 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1239 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_EXECUTE_IMMEDIATE;
# line 1239 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1239 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1239 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1239 "gdb_client_syb.cp"
                   {
# line 1239 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1239 "gdb_client_syb.cp"
                           CS_EXEC_IMMEDIATE, NULL, CS_UNUSED, syb_sql_stmt, 
# line 1239 "gdb_client_syb.cp"
                           CS_NULLTERM);
# line 1239 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1239 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1239 "gdb_client_syb.cp"
                       _sql->retcode = _sqlResults(_sql);
# line 1239 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1239 "gdb_client_syb.cp"
                   }
# line 1239 "gdb_client_syb.cp"
                   
# line 1239 "gdb_client_syb.cp"
               }
# line 1239 "gdb_client_syb.cp"
               
# line 1239 "gdb_client_syb.cp"
           }
# line 1239 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1239 "gdb_client_syb.cp"


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
  
           /*
           ** SQL STATEMENT: 38
           ** EXEC SQL AT :connect_name EXECUTE :syb_stmt_id_name USING 
           **       SQL DESCRIPTOR :syb_descriptor_name;
           */
# line 1282 "gdb_client_syb.cp"
# line 1281 "gdb_client_syb.cp"
           {
# line 1281 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1281 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1281 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1281 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1281 "gdb_client_syb.cp"
               {
# line 1281 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1281 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_EXECUTE;
# line 1281 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1281 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1281 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 1281 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 1281 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1281 "gdb_client_syb.cp"
                   {
# line 1281 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1281 "gdb_client_syb.cp"
                           CS_EXECUTE, syb_stmt_id_name, CS_NULLTERM, NULL, 
# line 1281 "gdb_client_syb.cp"
                           CS_UNUSED);
# line 1281 "gdb_client_syb.cp"
                       _sql->descName.fnlen = CS_NULLTERM;
# line 1281 "gdb_client_syb.cp"
                       strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1281 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1281 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1281 "gdb_client_syb.cp"
                           CS_USE_DESC, CS_UNUSED, NULL, NULL, CS_UNUSED, NULL,
# line 1281 "gdb_client_syb.cp"
                            NULL);
# line 1281 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1281 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1281 "gdb_client_syb.cp"
                       _sql->retcode = _sqlResults(_sql);
# line 1281 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1281 "gdb_client_syb.cp"
                   }
# line 1281 "gdb_client_syb.cp"
                   
# line 1281 "gdb_client_syb.cp"
               }
# line 1281 "gdb_client_syb.cp"
               
# line 1281 "gdb_client_syb.cp"
           }
# line 1281 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1282 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 39
           ** EXEC SQL AT :connect_name COMMIT TRANSACTION;

           */
# line 1304 "gdb_client_syb.cp"
# line 1304 "gdb_client_syb.cp"
           {
# line 1304 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1304 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1304 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1304 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1304 "gdb_client_syb.cp"
               {
# line 1304 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1304 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_TRANS;
# line 1304 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1304 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1304 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1304 "gdb_client_syb.cp"
                   {
# line 1304 "gdb_client_syb.cp"
                       _sql->retcode = ct_command(_sql->conn.command, 
# line 1304 "gdb_client_syb.cp"
                           CS_LANG_CMD, "COMMIT TRANSACTION", 18, CS_UNUSED);
# line 1304 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1304 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1304 "gdb_client_syb.cp"
                       _sql->retcode = _sqlResults(_sql);
# line 1304 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1304 "gdb_client_syb.cp"
                   }
# line 1304 "gdb_client_syb.cp"
                   
# line 1304 "gdb_client_syb.cp"
               }
# line 1304 "gdb_client_syb.cp"
               
# line 1304 "gdb_client_syb.cp"
           }
# line 1304 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1304 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 40
           ** EXEC SQL AT :connect_name ROLLBACK TRANSACTION;

           */
# line 1325 "gdb_client_syb.cp"
# line 1325 "gdb_client_syb.cp"
           {
# line 1325 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1325 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1325 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1325 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1325 "gdb_client_syb.cp"
               {
# line 1325 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1325 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_TRANS;
# line 1325 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1325 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1325 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1325 "gdb_client_syb.cp"
                   {
# line 1325 "gdb_client_syb.cp"
                       _sql->retcode = ct_command(_sql->conn.command, 
# line 1325 "gdb_client_syb.cp"
                           CS_LANG_CMD, "ROLLBACK TRANSACTION", 20, CS_UNUSED);
# line 1325 "gdb_client_syb.cp"
                       
# line 1325 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1325 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1325 "gdb_client_syb.cp"
                       _sql->retcode = _sqlResults(_sql);
# line 1325 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1325 "gdb_client_syb.cp"
                   }
# line 1325 "gdb_client_syb.cp"
                   
# line 1325 "gdb_client_syb.cp"
               }
# line 1325 "gdb_client_syb.cp"
               
# line 1325 "gdb_client_syb.cp"
           }
# line 1325 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1325 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 41
           ** EXEC SQL AT :connect_name DEALLOCATE PREPARE :syb_stmt_id_name;
           */
# line 1404 "gdb_client_syb.cp"
# line 1404 "gdb_client_syb.cp"
           {
# line 1404 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1404 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1404 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1404 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1404 "gdb_client_syb.cp"
               {
# line 1404 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1404 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_DEALLOCATE_PREPARE;
# line 1404 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1404 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1404 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 1404 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 1404 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1404 "gdb_client_syb.cp"
                   {
# line 1404 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1404 "gdb_client_syb.cp"
                   }
# line 1404 "gdb_client_syb.cp"
                   
# line 1404 "gdb_client_syb.cp"
               }
# line 1404 "gdb_client_syb.cp"
               
# line 1404 "gdb_client_syb.cp"
           }
# line 1404 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1404 "gdb_client_syb.cp"
	


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

  
           /*
           ** SQL STATEMENT: 42
           ** EXEC SQL AT :connect_name PREPARE :syb_stmt_id_name FROM :syb_sql_s
           ** tmt;
           */
# line 1459 "gdb_client_syb.cp"
# line 1459 "gdb_client_syb.cp"
           {
# line 1459 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1459 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1459 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1459 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1459 "gdb_client_syb.cp"
               {
# line 1459 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1459 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_PREPARE;
# line 1459 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1459 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1459 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 1459 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 1459 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1459 "gdb_client_syb.cp"
                   {
# line 1459 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1459 "gdb_client_syb.cp"
                           CS_PREPARE, syb_stmt_id_name, CS_NULLTERM, 
# line 1459 "gdb_client_syb.cp"
                           syb_sql_stmt, CS_NULLTERM);
# line 1459 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1459 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1459 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 1459 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 1459 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 1459 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 1459 "gdb_client_syb.cp"
                       {
# line 1459 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 1459 "gdb_client_syb.cp"
                           {
# line 1459 "gdb_client_syb.cp"
                           case CS_CMD_FAIL:
# line 1459 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1459 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_ALL);
# line 1459 "gdb_client_syb.cp"
                           break;
# line 1459 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 1459 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1459 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 1459 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1459 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1459 "gdb_client_syb.cp"
                           break;
# line 1459 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 1459 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1459 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25004);
# line 1459 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1459 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1459 "gdb_client_syb.cp"
                           break;
# line 1459 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 1459 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1459 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25005);
# line 1459 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1459 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1459 "gdb_client_syb.cp"
                           break;
# line 1459 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 1459 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1459 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25006);
# line 1459 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1459 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1459 "gdb_client_syb.cp"
                           break;
# line 1459 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 1459 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1459 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25009);
# line 1459 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1459 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1459 "gdb_client_syb.cp"
                           break;
# line 1459 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 1459 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1459 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25010);
# line 1459 "gdb_client_syb.cp"
                           break;
# line 1459 "gdb_client_syb.cp"
                           }
# line 1459 "gdb_client_syb.cp"
                           
# line 1459 "gdb_client_syb.cp"
                       }
# line 1459 "gdb_client_syb.cp"
                       
# line 1459 "gdb_client_syb.cp"
                       if ((_sql->retcode != CS_END_RESULTS) && (_sql->retcode 
# line 1459 "gdb_client_syb.cp"
                           != CS_CANCELED) && (_sql->retcode != 
# line 1459 "gdb_client_syb.cp"
                           CS_RET_HAFAILOVER) && (_sql->resloop != CS_FALSE))
# line 1459 "gdb_client_syb.cp"
                       {
# line 1459 "gdb_client_syb.cp"
                           _sql->retcode = ct_cancel(NULL, _sql->conn.command, 
# line 1459 "gdb_client_syb.cp"
                               CS_CANCEL_ALL);
# line 1459 "gdb_client_syb.cp"
                           }
# line 1459 "gdb_client_syb.cp"
                            else {
# line 1459 "gdb_client_syb.cp"
                           if (((_sql->retcode != CS_CANCELED) && 
# line 1459 "gdb_client_syb.cp"
                               (_sql->retcode != CS_RET_HAFAILOVER)))
# line 1459 "gdb_client_syb.cp"
                           {
# line 1459 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 1459 "gdb_client_syb.cp"
                           }
# line 1459 "gdb_client_syb.cp"
                           
# line 1459 "gdb_client_syb.cp"
                       }
# line 1459 "gdb_client_syb.cp"
                       
# line 1459 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1459 "gdb_client_syb.cp"
                   }
# line 1459 "gdb_client_syb.cp"
                   
# line 1459 "gdb_client_syb.cp"
               }
# line 1459 "gdb_client_syb.cp"
               
# line 1459 "gdb_client_syb.cp"
           }
# line 1459 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1459 "gdb_client_syb.cp"

  free((char *)syb_sql_stmt);
  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);

  
           /*
           ** SQL STATEMENT: 43
           ** EXEC SQL AT :connect_name EXECUTE :syb_stmt_id_name;
           */
# line 1463 "gdb_client_syb.cp"
# line 1463 "gdb_client_syb.cp"
           {
# line 1463 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1463 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1463 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1463 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1463 "gdb_client_syb.cp"
               {
# line 1463 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1463 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_EXECUTE;
# line 1463 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1463 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1463 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 1463 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 1463 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1463 "gdb_client_syb.cp"
                   {
# line 1463 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1463 "gdb_client_syb.cp"
                           CS_EXECUTE, syb_stmt_id_name, CS_NULLTERM, NULL, 
# line 1463 "gdb_client_syb.cp"
                           CS_UNUSED);
# line 1463 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1463 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1463 "gdb_client_syb.cp"
                       _sql->retcode = _sqlResults(_sql);
# line 1463 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1463 "gdb_client_syb.cp"
                   }
# line 1463 "gdb_client_syb.cp"
                   
# line 1463 "gdb_client_syb.cp"
               }
# line 1463 "gdb_client_syb.cp"
               
# line 1463 "gdb_client_syb.cp"
           }
# line 1463 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1463 "gdb_client_syb.cp"

  if (sqlca.sqlcode < 0) return (GDB_EXT_ERROR);  

  /* since the 'dealloc' will clear any error message generated by the 
     execute stmt, skip the 'dealloc prepare' on error since it doesn't
     use much memory anyway and we want the error message to return */

  
           /*
           ** SQL STATEMENT: 44
           ** EXEC SQL AT :connect_name DEALLOCATE PREPARE :syb_stmt_id_name;
           */
# line 1470 "gdb_client_syb.cp"
# line 1470 "gdb_client_syb.cp"
           {
# line 1470 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1470 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1470 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1470 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1470 "gdb_client_syb.cp"
               {
# line 1470 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1470 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_DEALLOCATE_PREPARE;
# line 1470 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1470 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1470 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 1470 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 1470 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1470 "gdb_client_syb.cp"
                   {
# line 1470 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1470 "gdb_client_syb.cp"
                   }
# line 1470 "gdb_client_syb.cp"
                   
# line 1470 "gdb_client_syb.cp"
               }
# line 1470 "gdb_client_syb.cp"
               
# line 1470 "gdb_client_syb.cp"
           }
# line 1470 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1470 "gdb_client_syb.cp"


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
  
           /*
           ** SQL STATEMENT: 44
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 1505 "gdb_client_syb.cp"

    CS_INT   result;
    CS_CHAR  syb_sql_stmt[60]= "SELECT COUNT(*) FROM sysusers";
  
           /*
           ** SQL STATEMENT: 45
           ** EXEC SQL END DECLARE SECTION;

           */
# line 1508 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 1508 "gdb_client_syb.cp"


  context_num = gsi_current_context();

  if (debug & DBG1)
    iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE,"%s","SQL_PING_DB");

  /* set context connection name */
  sprintf( connect_name, "DB%d",context_num );

  /* prepare the statement */
  
           /*
           ** SQL STATEMENT: 46
           ** EXEC SQL AT :connect_name PREPARE ping FROM :syb_sql_stmt;
           */
# line 1519 "gdb_client_syb.cp"
# line 1519 "gdb_client_syb.cp"
           {
# line 1519 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1519 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1519 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1519 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1519 "gdb_client_syb.cp"
               {
# line 1519 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1519 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_PREPARE;
# line 1519 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1519 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1519 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = 4;
# line 1519 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, "ping");
# line 1519 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1519 "gdb_client_syb.cp"
                   {
# line 1519 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1519 "gdb_client_syb.cp"
                           CS_PREPARE, "ping", 4, syb_sql_stmt, CS_NULLTERM);
# line 1519 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1519 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1519 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 1519 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 1519 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 1519 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 1519 "gdb_client_syb.cp"
                       {
# line 1519 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 1519 "gdb_client_syb.cp"
                           {
# line 1519 "gdb_client_syb.cp"
                           case CS_CMD_FAIL:
# line 1519 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1519 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_ALL);
# line 1519 "gdb_client_syb.cp"
                           break;
# line 1519 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 1519 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1519 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 1519 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1519 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1519 "gdb_client_syb.cp"
                           break;
# line 1519 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 1519 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1519 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25004);
# line 1519 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1519 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1519 "gdb_client_syb.cp"
                           break;
# line 1519 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 1519 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1519 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25005);
# line 1519 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1519 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1519 "gdb_client_syb.cp"
                           break;
# line 1519 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 1519 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1519 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25006);
# line 1519 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1519 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1519 "gdb_client_syb.cp"
                           break;
# line 1519 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 1519 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1519 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25009);
# line 1519 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1519 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1519 "gdb_client_syb.cp"
                           break;
# line 1519 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 1519 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1519 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25010);
# line 1519 "gdb_client_syb.cp"
                           break;
# line 1519 "gdb_client_syb.cp"
                           }
# line 1519 "gdb_client_syb.cp"
                           
# line 1519 "gdb_client_syb.cp"
                       }
# line 1519 "gdb_client_syb.cp"
                       
# line 1519 "gdb_client_syb.cp"
                       if ((_sql->retcode != CS_END_RESULTS) && (_sql->retcode 
# line 1519 "gdb_client_syb.cp"
                           != CS_CANCELED) && (_sql->retcode != 
# line 1519 "gdb_client_syb.cp"
                           CS_RET_HAFAILOVER) && (_sql->resloop != CS_FALSE))
# line 1519 "gdb_client_syb.cp"
                       {
# line 1519 "gdb_client_syb.cp"
                           _sql->retcode = ct_cancel(NULL, _sql->conn.command, 
# line 1519 "gdb_client_syb.cp"
                               CS_CANCEL_ALL);
# line 1519 "gdb_client_syb.cp"
                           }
# line 1519 "gdb_client_syb.cp"
                            else {
# line 1519 "gdb_client_syb.cp"
                           if (((_sql->retcode != CS_CANCELED) && 
# line 1519 "gdb_client_syb.cp"
                               (_sql->retcode != CS_RET_HAFAILOVER)))
# line 1519 "gdb_client_syb.cp"
                           {
# line 1519 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 1519 "gdb_client_syb.cp"
                           }
# line 1519 "gdb_client_syb.cp"
                           
# line 1519 "gdb_client_syb.cp"
                       }
# line 1519 "gdb_client_syb.cp"
                       
# line 1519 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1519 "gdb_client_syb.cp"
                   }
# line 1519 "gdb_client_syb.cp"
                   
# line 1519 "gdb_client_syb.cp"
               }
# line 1519 "gdb_client_syb.cp"
               
# line 1519 "gdb_client_syb.cp"
           }
# line 1519 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1519 "gdb_client_syb.cp"

  if ( sqlca.sqlcode < 0 ) return ( GDB_EXT_ERROR );

  /* execute the statement */
  
           /*
           ** SQL STATEMENT: 47
           ** EXEC SQL AT :connect_name EXECUTE ping INTO :result;
           */
# line 1523 "gdb_client_syb.cp"
# line 1523 "gdb_client_syb.cp"
           {
# line 1523 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1523 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1523 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1523 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1523 "gdb_client_syb.cp"
               {
# line 1523 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1523 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_EXECUTE;
# line 1523 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1523 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1523 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = 4;
# line 1523 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, "ping");
# line 1523 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1523 "gdb_client_syb.cp"
                   {
# line 1523 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1523 "gdb_client_syb.cp"
                           CS_EXECUTE, "ping", 4, NULL, CS_UNUSED);
# line 1523 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1523 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1523 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 1523 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 1523 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 1523 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 1523 "gdb_client_syb.cp"
                       {
# line 1523 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 1523 "gdb_client_syb.cp"
                           {
# line 1523 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 1523 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1523 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 1523 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1523 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1523 "gdb_client_syb.cp"
                           break;
# line 1523 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 1523 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1523 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25004);
# line 1523 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1523 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1523 "gdb_client_syb.cp"
                           break;
# line 1523 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 1523 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1523 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25005);
# line 1523 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1523 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1523 "gdb_client_syb.cp"
                           break;
# line 1523 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 1523 "gdb_client_syb.cp"
                               _sql->dfmtCS_INT_TYPE.count = 0;
# line 1523 "gdb_client_syb.cp"
                                   _sql->retcode = ct_bind(_sql->conn.command, 
# line 1523 "gdb_client_syb.cp"
                                       1, &_sql->dfmtCS_INT_TYPE, &result, 
# line 1523 "gdb_client_syb.cp"
                                       NULL, NULL);
# line 1523 "gdb_client_syb.cp"
                               _sql->retcode = ct_fetch(_sql->conn.command, 
# line 1523 "gdb_client_syb.cp"
                                   CS_UNUSED, CS_UNUSED, CS_UNUSED, 
# line 1523 "gdb_client_syb.cp"
                                   &_sql->rowsread);
# line 1523 "gdb_client_syb.cp"
                               _sql->hastate = (_sql->retcode == 
# line 1523 "gdb_client_syb.cp"
                                   CS_RET_HAFAILOVER);
# line 1523 "gdb_client_syb.cp"
                               if ((_sql->retcode == CS_SUCCEED) || 
# line 1523 "gdb_client_syb.cp"
                                   (_sql->retcode == CS_ROW_FAIL))
# line 1523 "gdb_client_syb.cp"
                               {
# line 1523 "gdb_client_syb.cp"
                                   _sql->retcode = ct_bind(_sql->conn.command, 
# line 1523 "gdb_client_syb.cp"
                                       CS_UNUSED, NULL, NULL, NULL, NULL);
# line 1523 "gdb_client_syb.cp"
                                   _sql->retcode = ct_fetch(_sql->conn.command,
# line 1523 "gdb_client_syb.cp"
                                        CS_UNUSED, CS_UNUSED, CS_UNUSED, 
# line 1523 "gdb_client_syb.cp"
                                       &_sql->rowsread);
# line 1523 "gdb_client_syb.cp"
                                   _sql->hastate = (_sql->retcode == 
# line 1523 "gdb_client_syb.cp"
                                       CS_RET_HAFAILOVER);
# line 1523 "gdb_client_syb.cp"
                               }
# line 1523 "gdb_client_syb.cp"
                               
# line 1523 "gdb_client_syb.cp"
                           break;
# line 1523 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 1523 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1523 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25009);
# line 1523 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1523 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1523 "gdb_client_syb.cp"
                           break;
# line 1523 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 1523 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1523 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25010);
# line 1523 "gdb_client_syb.cp"
                           break;
# line 1523 "gdb_client_syb.cp"
                           }
# line 1523 "gdb_client_syb.cp"
                           
# line 1523 "gdb_client_syb.cp"
                       }
# line 1523 "gdb_client_syb.cp"
                       
# line 1523 "gdb_client_syb.cp"
                       if ((_sql->retcode != CS_END_RESULTS) && (_sql->retcode 
# line 1523 "gdb_client_syb.cp"
                           != CS_CANCELED) && (_sql->retcode != 
# line 1523 "gdb_client_syb.cp"
                           CS_RET_HAFAILOVER) && (_sql->resloop != CS_FALSE))
# line 1523 "gdb_client_syb.cp"
                       {
# line 1523 "gdb_client_syb.cp"
                           _sql->retcode = ct_cancel(NULL, _sql->conn.command, 
# line 1523 "gdb_client_syb.cp"
                               CS_CANCEL_ALL);
# line 1523 "gdb_client_syb.cp"
                           }
# line 1523 "gdb_client_syb.cp"
                            else {
# line 1523 "gdb_client_syb.cp"
                           if (((_sql->retcode != CS_CANCELED) && 
# line 1523 "gdb_client_syb.cp"
                               (_sql->retcode != CS_RET_HAFAILOVER)))
# line 1523 "gdb_client_syb.cp"
                           {
# line 1523 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 1523 "gdb_client_syb.cp"
                           }
# line 1523 "gdb_client_syb.cp"
                           
# line 1523 "gdb_client_syb.cp"
                       }
# line 1523 "gdb_client_syb.cp"
                       
# line 1523 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1523 "gdb_client_syb.cp"
                   }
# line 1523 "gdb_client_syb.cp"
                   
# line 1523 "gdb_client_syb.cp"
               }
# line 1523 "gdb_client_syb.cp"
               
# line 1523 "gdb_client_syb.cp"
           }
# line 1523 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1523 "gdb_client_syb.cp"


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

  
           /*
           ** SQL STATEMENT: 47
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 1543 "gdb_client_syb.cp"

    CS_CHAR   test_trig_name[SYB_MAX_TRIGGER_NAME_LEN+1];
    CS_CHAR   t_msg[200];
    CS_CHAR   t_datetime[30];
    CS_BIT    t_success ;
  
           /*
           ** SQL STATEMENT: 48
           ** EXEC SQL END DECLARE SECTION;

           */
# line 1548 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 1548 "gdb_client_syb.cp"


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
  
           /*
           ** SQL STATEMENT: 49
           ** EXEC SQL AT :connect_name EXEC g2_proc_trig
           **               :test_trig_name,
           **               :t_msg OUT,
           **               :t_datetime OUT,
           **               :t_success OUT ;
           */
# line 1576 "gdb_client_syb.cp"
# line 1572 "gdb_client_syb.cp"
           {
# line 1572 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1572 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1572 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1572 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1572 "gdb_client_syb.cp"
               {
# line 1572 "gdb_client_syb.cp"
                   _sql->stmtIdlen = CS_UNUSED;
# line 1572 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1572 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_EXECUTE_PROCEDURE;
# line 1572 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1572 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1572 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1572 "gdb_client_syb.cp"
                   {
# line 1572 "gdb_client_syb.cp"
                       _sql->retcode = ct_command(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                           CS_RPC_CMD, "g2_proc_trig", 12, CS_NO_RECOMPILE);
# line 1572 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 1572 "gdb_client_syb.cp"
                       {
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.count = 0;
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.maxlength = 
# line 1572 "gdb_client_syb.cp"
                           _sql_MIN(16384,SYB_MAX_TRIGGER_NAME_LEN+1);
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.status = CS_INPUTVALUE;
# line 1572 "gdb_client_syb.cp"
                           _sql->retcode = ct_param(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                               &_sql->dfmtNULLCHAR, 
# line 1572 "gdb_client_syb.cp"
                           SQLNULLSTR(test_trig_name), (CS_INT) CS_NULLTERM, 
# line 1572 "gdb_client_syb.cp"
                               (CS_SMALLINT) 0);
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.status = 0;
# line 1572 "gdb_client_syb.cp"
                       }
# line 1572 "gdb_client_syb.cp"
                       
# line 1572 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 1572 "gdb_client_syb.cp"
                       {
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.count = 0;
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.maxlength = 
# line 1572 "gdb_client_syb.cp"
                           _sql_MIN(16384,200);
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.status = CS_RETURN;
# line 1572 "gdb_client_syb.cp"
                           _sql->retcode = ct_param(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                               &_sql->dfmtNULLCHAR, 
# line 1572 "gdb_client_syb.cp"
                           SQLNULLSTR(t_msg), (CS_INT) CS_NULLTERM, 
# line 1572 "gdb_client_syb.cp"
                               (CS_SMALLINT) 0);
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.status = 0;
# line 1572 "gdb_client_syb.cp"
                       }
# line 1572 "gdb_client_syb.cp"
                       
# line 1572 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 1572 "gdb_client_syb.cp"
                       {
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.count = 0;
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.maxlength = 
# line 1572 "gdb_client_syb.cp"
                           _sql_MIN(16384,30);
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.status = CS_RETURN;
# line 1572 "gdb_client_syb.cp"
                           _sql->retcode = ct_param(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                               &_sql->dfmtNULLCHAR, 
# line 1572 "gdb_client_syb.cp"
                           SQLNULLSTR(t_datetime), (CS_INT) CS_NULLTERM, 
# line 1572 "gdb_client_syb.cp"
                               (CS_SMALLINT) 0);
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtNULLCHAR.status = 0;
# line 1572 "gdb_client_syb.cp"
                       }
# line 1572 "gdb_client_syb.cp"
                       
# line 1572 "gdb_client_syb.cp"
                       if (_sql->retcode == CS_SUCCEED)
# line 1572 "gdb_client_syb.cp"
                       {
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtCS_BIT_TYPE.count = 0;
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtCS_BIT_TYPE.status = CS_RETURN;
# line 1572 "gdb_client_syb.cp"
                           _sql->retcode = ct_param(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                               &_sql->dfmtCS_BIT_TYPE, &t_success, (CS_INT) 
# line 1572 "gdb_client_syb.cp"
                               CS_UNUSED, (CS_SMALLINT) 0);
# line 1572 "gdb_client_syb.cp"
                           _sql->dfmtCS_BIT_TYPE.status = 0;
# line 1572 "gdb_client_syb.cp"
                       }
# line 1572 "gdb_client_syb.cp"
                       
# line 1572 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1572 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1572 "gdb_client_syb.cp"
                       _sql->resloop = CS_TRUE;
# line 1572 "gdb_client_syb.cp"
                       while ((!_sql->hastate) && (_sql->resloop == CS_TRUE) 
# line 1572 "gdb_client_syb.cp"
                           && ((_sql->retcode = ct_results(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                           &_sql->restype)) == CS_SUCCEED))
# line 1572 "gdb_client_syb.cp"
                       {
# line 1572 "gdb_client_syb.cp"
                           switch ( _sql->restype )
# line 1572 "gdb_client_syb.cp"
                           {
# line 1572 "gdb_client_syb.cp"
                           case CS_COMPUTE_RESULT:
# line 1572 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1572 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25003);
# line 1572 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1572 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1572 "gdb_client_syb.cp"
                           break;
# line 1572 "gdb_client_syb.cp"
                           case CS_CURSOR_RESULT:
# line 1572 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1572 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25004);
# line 1572 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1572 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1572 "gdb_client_syb.cp"
                           break;
# line 1572 "gdb_client_syb.cp"
                           case CS_PARAM_RESULT:
# line 1572 "gdb_client_syb.cp"
                               _sql->dfmtNULLCHAR.count = 0;
# line 1572 "gdb_client_syb.cp"
                               _sql->dfmtNULLCHAR.maxlength = 
# line 1572 "gdb_client_syb.cp"
                               _sql_MIN(16384,200);
# line 1572 "gdb_client_syb.cp"
                               _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1572 "gdb_client_syb.cp"
                                   _sql->retcode = ct_bind(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                                       1, &_sql->dfmtNULLCHAR, t_msg, NULL, 
# line 1572 "gdb_client_syb.cp"
                                       NULL);
# line 1572 "gdb_client_syb.cp"
                               _sql->dfmtNULLCHAR.count = 0;
# line 1572 "gdb_client_syb.cp"
                               _sql->dfmtNULLCHAR.maxlength = 
# line 1572 "gdb_client_syb.cp"
                               _sql_MIN(16384,30);
# line 1572 "gdb_client_syb.cp"
                               _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1572 "gdb_client_syb.cp"
                                   _sql->retcode = ct_bind(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                                       2, &_sql->dfmtNULLCHAR, t_datetime, 
# line 1572 "gdb_client_syb.cp"
                                       NULL, NULL);
# line 1572 "gdb_client_syb.cp"
                               _sql->dfmtCS_BIT_TYPE.count = 0;
# line 1572 "gdb_client_syb.cp"
                                   _sql->retcode = ct_bind(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                                       3, &_sql->dfmtCS_BIT_TYPE, &t_success, 
# line 1572 "gdb_client_syb.cp"
                                       NULL, NULL);
# line 1572 "gdb_client_syb.cp"
                               _sql->retcode = ct_fetch(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                                   CS_UNUSED, CS_UNUSED, CS_UNUSED, 
# line 1572 "gdb_client_syb.cp"
                                   &_sql->rowsread);
# line 1572 "gdb_client_syb.cp"
                               _sql->hastate = (_sql->retcode == 
# line 1572 "gdb_client_syb.cp"
                                   CS_RET_HAFAILOVER);
# line 1572 "gdb_client_syb.cp"
                               if ((_sql->retcode == CS_SUCCEED) || 
# line 1572 "gdb_client_syb.cp"
                                   (_sql->retcode == CS_ROW_FAIL))
# line 1572 "gdb_client_syb.cp"
                               {
# line 1572 "gdb_client_syb.cp"
                                   _sql->retcode = ct_bind(_sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                                       CS_UNUSED, NULL, NULL, NULL, NULL);
# line 1572 "gdb_client_syb.cp"
                                   _sql->retcode = ct_fetch(_sql->conn.command,
# line 1572 "gdb_client_syb.cp"
                                        CS_UNUSED, CS_UNUSED, CS_UNUSED, 
# line 1572 "gdb_client_syb.cp"
                                       &_sql->rowsread);
# line 1572 "gdb_client_syb.cp"
                                   _sql->hastate = (_sql->retcode == 
# line 1572 "gdb_client_syb.cp"
                                       CS_RET_HAFAILOVER);
# line 1572 "gdb_client_syb.cp"
                               }
# line 1572 "gdb_client_syb.cp"
                               
# line 1572 "gdb_client_syb.cp"
                           break;
# line 1572 "gdb_client_syb.cp"
                           case CS_ROW_RESULT:
# line 1572 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1572 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25006);
# line 1572 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1572 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1572 "gdb_client_syb.cp"
                           break;
# line 1572 "gdb_client_syb.cp"
                           case CS_STATUS_RESULT:
# line 1572 "gdb_client_syb.cp"
                               _sql->retcode = ct_cancel(NULL, 
# line 1572 "gdb_client_syb.cp"
                                   _sql->conn.command, CS_CANCEL_CURRENT);
# line 1572 "gdb_client_syb.cp"
                           break;
# line 1572 "gdb_client_syb.cp"
                           case CS_DESCRIBE_RESULT:
# line 1572 "gdb_client_syb.cp"
                               _sqlsetintrerr(_sql, (CS_INT) 
# line 1572 "gdb_client_syb.cp"
                                   _SQL_INTRERR_25010);
# line 1572 "gdb_client_syb.cp"
                           break;
# line 1572 "gdb_client_syb.cp"
                           }
# line 1572 "gdb_client_syb.cp"
                           
# line 1572 "gdb_client_syb.cp"
                       }
# line 1572 "gdb_client_syb.cp"
                       
# line 1572 "gdb_client_syb.cp"
                       if ((_sql->retcode != CS_END_RESULTS) && (_sql->retcode 
# line 1572 "gdb_client_syb.cp"
                           != CS_CANCELED) && (_sql->retcode != 
# line 1572 "gdb_client_syb.cp"
                           CS_RET_HAFAILOVER) && (_sql->resloop != CS_FALSE))
# line 1572 "gdb_client_syb.cp"
                       {
# line 1572 "gdb_client_syb.cp"
                           _sql->retcode = ct_cancel(NULL, _sql->conn.command, 
# line 1572 "gdb_client_syb.cp"
                               CS_CANCEL_ALL);
# line 1572 "gdb_client_syb.cp"
                           }
# line 1572 "gdb_client_syb.cp"
                            else {
# line 1572 "gdb_client_syb.cp"
                           if (((_sql->retcode != CS_CANCELED) && 
# line 1572 "gdb_client_syb.cp"
                               (_sql->retcode != CS_RET_HAFAILOVER)))
# line 1572 "gdb_client_syb.cp"
                           {
# line 1572 "gdb_client_syb.cp"
                               _sql->retcode = CS_SUCCEED;
# line 1572 "gdb_client_syb.cp"
                           }
# line 1572 "gdb_client_syb.cp"
                           
# line 1572 "gdb_client_syb.cp"
                       }
# line 1572 "gdb_client_syb.cp"
                       
# line 1572 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1572 "gdb_client_syb.cp"
                   }
# line 1572 "gdb_client_syb.cp"
                   
# line 1572 "gdb_client_syb.cp"
               }
# line 1572 "gdb_client_syb.cp"
               
# line 1572 "gdb_client_syb.cp"
           }
# line 1572 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1576 "gdb_client_syb.cp"

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
  
           /*
           ** SQL STATEMENT: 49
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 1629 "gdb_client_syb.cp"

    CS_INT          descnt;
    CS_INT          col_num;
    CS_SMALLINT		ind_val;
	  CS_CHAR			*text_val;
	  CS_INT			long_val;
	  CS_SMALLINT		short_val;
	  CS_FLOAT		dbl_val;
	  CS_REAL			float_val;
  
           /*
           ** SQL STATEMENT: 50
           ** EXEC SQL END DECLARE SECTION;

           */
# line 1638 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 1638 "gdb_client_syb.cp"


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
	      
           /*
           ** SQL STATEMENT: 51
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **                 DATA = :text_val,
           **                 INDICATOR = :ind_val;
           */
# line 1682 "gdb_client_syb.cp"
# line 1680 "gdb_client_syb.cp"
           {
# line 1680 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1680 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1680 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1680 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1680 "gdb_client_syb.cp"
               {
# line 1680 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1680 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 1680 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1680 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1680 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1680 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1680 "gdb_client_syb.cp"
                   {
# line 1680 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.count = 0;
# line 1680 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.maxlength = 
# line 1680 "gdb_client_syb.cp"
                       _sql_MIN(16384,_SQL_PCHAR_LEN);
# line 1680 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1680 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.status = CS_INPUTVALUE;
# line 1680 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtNULLCHAR.name, 1);
# line 1680 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.namelen = 0;
# line 1680 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1680 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1680 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtNULLCHAR, 
# line 1680 "gdb_client_syb.cp"
                       SQLNULLSTR(text_val), CS_NULLTERM, NULL, &ind_val);
# line 1680 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtNULLCHAR, CS_CHAR_TYPE);
# line 1680 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1680 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1680 "gdb_client_syb.cp"
                   }
# line 1680 "gdb_client_syb.cp"
                   
# line 1680 "gdb_client_syb.cp"
               }
# line 1680 "gdb_client_syb.cp"
               
# line 1680 "gdb_client_syb.cp"
           }
# line 1680 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1682 "gdb_client_syb.cp"

	      break;

	    case SB_INTEGER :
	      long_val = (long) ((long *)bind_ptr[i].data)[row];
	      
           /*
           ** SQL STATEMENT: 52
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **                 DATA = :long_val,
           **                 INDICATOR = :ind_val;
           */
# line 1689 "gdb_client_syb.cp"
# line 1687 "gdb_client_syb.cp"
           {
# line 1687 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1687 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1687 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1687 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1687 "gdb_client_syb.cp"
               {
# line 1687 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1687 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 1687 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1687 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1687 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1687 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1687 "gdb_client_syb.cp"
                   {
# line 1687 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.count = 0;
# line 1687 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.status = CS_INPUTVALUE;
# line 1687 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_INT_TYPE.name, 1);
# line 1687 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.namelen = 0;
# line 1687 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1687 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1687 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_INT_TYPE, 
# line 1687 "gdb_client_syb.cp"
                           &long_val, CS_UNUSED, NULL, &ind_val);
# line 1687 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_INT_TYPE, CS_INT_TYPE);
# line 1687 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1687 "gdb_client_syb.cp"
                   }
# line 1687 "gdb_client_syb.cp"
                   
# line 1687 "gdb_client_syb.cp"
               }
# line 1687 "gdb_client_syb.cp"
               
# line 1687 "gdb_client_syb.cp"
           }
# line 1687 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1689 "gdb_client_syb.cp"

		  break;

	    case SB_SMALLINT :
	    case SB_TINYINT :
	    case SB_BIT :
	      short_val = (short) ((long *)bind_ptr[i].data)[row];
	      
           /*
           ** SQL STATEMENT: 53
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **                 DATA = :short_val,
           **                 INDICATOR = :ind_val;
           */
# line 1698 "gdb_client_syb.cp"
# line 1696 "gdb_client_syb.cp"
           {
# line 1696 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1696 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1696 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1696 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1696 "gdb_client_syb.cp"
               {
# line 1696 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1696 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 1696 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1696 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1696 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1696 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1696 "gdb_client_syb.cp"
                   {
# line 1696 "gdb_client_syb.cp"
                       _sql->dfmtCS_SMALLINT_TYPE.count = 0;
# line 1696 "gdb_client_syb.cp"
                       _sql->dfmtCS_SMALLINT_TYPE.status = CS_INPUTVALUE;
# line 1696 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_SMALLINT_TYPE.name, 1);
# line 1696 "gdb_client_syb.cp"
                       _sql->dfmtCS_SMALLINT_TYPE.namelen = 0;
# line 1696 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1696 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1696 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_SMALLINT_TYPE, 
# line 1696 "gdb_client_syb.cp"
                           &short_val, CS_UNUSED, NULL, &ind_val);
# line 1696 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_SMALLINT_TYPE, 
# line 1696 "gdb_client_syb.cp"
                           CS_SMALLINT_TYPE);
# line 1696 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1696 "gdb_client_syb.cp"
                   }
# line 1696 "gdb_client_syb.cp"
                   
# line 1696 "gdb_client_syb.cp"
               }
# line 1696 "gdb_client_syb.cp"
               
# line 1696 "gdb_client_syb.cp"
           }
# line 1696 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1698 "gdb_client_syb.cp"

	      break;

	    case SB_SMALLMONEY :
	    case SB_REAL_OLD :
	    case SB_REAL :
	      float_val = (float) ((double *)bind_ptr[i].data)[row];
	      
           /*
           ** SQL STATEMENT: 54
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **                 DATA = :float_val,
           **                 INDICATOR = :ind_val;
           */
# line 1707 "gdb_client_syb.cp"
# line 1705 "gdb_client_syb.cp"
           {
# line 1705 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1705 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1705 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1705 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1705 "gdb_client_syb.cp"
               {
# line 1705 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1705 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 1705 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1705 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1705 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1705 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1705 "gdb_client_syb.cp"
                   {
# line 1705 "gdb_client_syb.cp"
                       _sql->dfmtCS_REAL_TYPE.count = 0;
# line 1705 "gdb_client_syb.cp"
                       _sql->dfmtCS_REAL_TYPE.status = CS_INPUTVALUE;
# line 1705 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_REAL_TYPE.name, 1);
# line 1705 "gdb_client_syb.cp"
                       _sql->dfmtCS_REAL_TYPE.namelen = 0;
# line 1705 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1705 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1705 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_REAL_TYPE, 
# line 1705 "gdb_client_syb.cp"
                           &float_val, CS_UNUSED, NULL, &ind_val);
# line 1705 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_REAL_TYPE, CS_REAL_TYPE);
# line 1705 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1705 "gdb_client_syb.cp"
                   }
# line 1705 "gdb_client_syb.cp"
                   
# line 1705 "gdb_client_syb.cp"
               }
# line 1705 "gdb_client_syb.cp"
               
# line 1705 "gdb_client_syb.cp"
           }
# line 1705 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1707 "gdb_client_syb.cp"

	      break;

	    case SB_FLOAT :
	    case SB_MONEY :
	    case SB_NUMERIC :
	    case SB_DECIMAL :
	      dbl_val = (double) ((double *)bind_ptr[i].data)[row];
	      
           /*
           ** SQL STATEMENT: 55
           ** EXEC SQL SET DESCRIPTOR :syb_descriptor_name VALUE :col_num
           **                 DATA = :dbl_val,
           **                 INDICATOR= :ind_val;
           */
# line 1717 "gdb_client_syb.cp"
# line 1715 "gdb_client_syb.cp"
           {
# line 1715 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1715 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1715 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1715 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1715 "gdb_client_syb.cp"
               {
# line 1715 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1715 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_DESCRIPTOR;
# line 1715 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1715 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1715 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1715 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1715 "gdb_client_syb.cp"
                   {
# line 1715 "gdb_client_syb.cp"
                       _sql->dfmtCS_FLOAT_TYPE.count = 0;
# line 1715 "gdb_client_syb.cp"
                       _sql->dfmtCS_FLOAT_TYPE.status = CS_INPUTVALUE;
# line 1715 "gdb_client_syb.cp"
                       _sqlmemcpy(" ", _sql->dfmtCS_FLOAT_TYPE.name, 1);
# line 1715 "gdb_client_syb.cp"
                       _sql->dfmtCS_FLOAT_TYPE.namelen = 0;
# line 1715 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1715 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1715 "gdb_client_syb.cp"
                           CS_SETATTR, col_num, &_sql->dfmtCS_FLOAT_TYPE, 
# line 1715 "gdb_client_syb.cp"
                           &dbl_val, CS_UNUSED, NULL, &ind_val);
# line 1715 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_FLOAT_TYPE, CS_FLOAT_TYPE);
# line 1715 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1715 "gdb_client_syb.cp"
                   }
# line 1715 "gdb_client_syb.cp"
                   
# line 1715 "gdb_client_syb.cp"
               }
# line 1715 "gdb_client_syb.cp"
               
# line 1715 "gdb_client_syb.cp"
           }
# line 1715 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1717 "gdb_client_syb.cp"

	      break;

        default :
          iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE,"%d%d%d",EINVDTY,bind_ptr[i].datatype,col_num);
          return (GDB_ERROR);
          break;
      } /* end switch */

	}

    /* Execute the statement */
    
           /*
           ** SQL STATEMENT: 56
           ** EXEC SQL AT :connect_name EXECUTE :syb_stmt_id_name USING 
           **         SQL DESCRIPTOR :syb_descriptor_name;
           */
# line 1730 "gdb_client_syb.cp"
# line 1729 "gdb_client_syb.cp"
           {
# line 1729 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1729 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1729 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1729 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1729 "gdb_client_syb.cp"
               {
# line 1729 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1729 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_EXECUTE;
# line 1729 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1729 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1729 "gdb_client_syb.cp"
                   _sql->stmtName.fnlen = CS_NULLTERM;
# line 1729 "gdb_client_syb.cp"
                   strcpy(_sql->stmtName.first_name, syb_stmt_id_name);
# line 1729 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1729 "gdb_client_syb.cp"
                   {
# line 1729 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1729 "gdb_client_syb.cp"
                           CS_EXECUTE, syb_stmt_id_name, CS_NULLTERM, NULL, 
# line 1729 "gdb_client_syb.cp"
                           CS_UNUSED);
# line 1729 "gdb_client_syb.cp"
                       _sql->descName.fnlen = CS_NULLTERM;
# line 1729 "gdb_client_syb.cp"
                       strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1729 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1729 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1729 "gdb_client_syb.cp"
                           CS_USE_DESC, CS_UNUSED, NULL, NULL, CS_UNUSED, NULL,
# line 1729 "gdb_client_syb.cp"
                            NULL);
# line 1729 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1729 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1729 "gdb_client_syb.cp"
                       _sql->retcode = _sqlResults(_sql);
# line 1729 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1729 "gdb_client_syb.cp"
                   }
# line 1729 "gdb_client_syb.cp"
                   
# line 1729 "gdb_client_syb.cp"
               }
# line 1729 "gdb_client_syb.cp"
               
# line 1729 "gdb_client_syb.cp"
           }
# line 1729 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1730 "gdb_client_syb.cp"

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

  
           /*
           ** SQL STATEMENT: 56
           ** EXEC SQL BEGIN DECLARE SECTION;

           */
# line 1788 "gdb_client_syb.cp"

    int              idx;
    short            ind_val=0;
    char            *text_val;
    CS_CHAR          date_val[DATE_LEN]="";
    short            short_val=0;
    int              int_val=0;
    float            float_val=0.0;
    double           dbl_val=0.0;
  
           /*
           ** SQL STATEMENT: 57
           ** EXEC SQL END DECLARE SECTION;

           */
# line 1797 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 1797 "gdb_client_syb.cp"

   
  context_num = gsi_current_context();

  select_ptr = sqlda_ptrs[context_num][shandle].sptr;

  /** set context connection name **/
  sprintf(connect_name,"DB%d",context_num);

  
           /*
           ** SQL STATEMENT: 58
           ** EXEC SQL SET CONNECTION :connect_name;
           */
# line 1806 "gdb_client_syb.cp"
# line 1806 "gdb_client_syb.cp"
           {
# line 1806 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1806 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1806 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1806 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1806 "gdb_client_syb.cp"
               {
# line 1806 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1806 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_SET_CONNECTION;
# line 1806 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1806 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1806 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1806 "gdb_client_syb.cp"
                   {
# line 1806 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1806 "gdb_client_syb.cp"
                   }
# line 1806 "gdb_client_syb.cp"
                   
# line 1806 "gdb_client_syb.cp"
               }
# line 1806 "gdb_client_syb.cp"
               
# line 1806 "gdb_client_syb.cp"
           }
# line 1806 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1806 "gdb_client_syb.cp"

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

      
           /*
           ** SQL STATEMENT: 59
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
           **                               :text_val = DATA,         
           **                               :ind_val  = INDICATOR;

           */
# line 1826 "gdb_client_syb.cp"
# line 1824 "gdb_client_syb.cp"
           {
# line 1824 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1824 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1824 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1824 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1824 "gdb_client_syb.cp"
               {
# line 1824 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1824 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 1824 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1824 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1824 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1824 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1824 "gdb_client_syb.cp"
                   {
# line 1824 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.count = 0;
# line 1824 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.maxlength = _SQL_PCHAR_LEN;
# line 1824 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1824 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1824 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1824 "gdb_client_syb.cp"
                           CS_GETATTR, idx, &_sql->dfmtNULLCHAR, text_val, 
# line 1824 "gdb_client_syb.cp"
                           CS_UNUSED, NULL, &ind_val);
# line 1824 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtNULLCHAR, CS_CHAR_TYPE);
# line 1824 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1824 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1824 "gdb_client_syb.cp"
                   }
# line 1824 "gdb_client_syb.cp"
                   
# line 1824 "gdb_client_syb.cp"
               }
# line 1824 "gdb_client_syb.cp"
               
# line 1824 "gdb_client_syb.cp"
           }
# line 1824 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1826 "gdb_client_syb.cp"

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

      
           /*
           ** SQL STATEMENT: 60
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
           **                               :date_val = DATA,         
           **                               :ind_val  = INDICATOR;

           */
# line 1841 "gdb_client_syb.cp"
# line 1839 "gdb_client_syb.cp"
           {
# line 1839 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1839 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1839 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1839 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1839 "gdb_client_syb.cp"
               {
# line 1839 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1839 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 1839 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1839 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1839 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1839 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1839 "gdb_client_syb.cp"
                   {
# line 1839 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.count = 0;
# line 1839 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.maxlength = DATE_LEN;
# line 1839 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1839 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1839 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1839 "gdb_client_syb.cp"
                           CS_GETATTR, idx, &_sql->dfmtNULLCHAR, date_val, 
# line 1839 "gdb_client_syb.cp"
                           CS_UNUSED, NULL, &ind_val);
# line 1839 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtNULLCHAR, CS_CHAR_TYPE);
# line 1839 "gdb_client_syb.cp"
                       _sql->dfmtNULLCHAR.format = CS_FMT_NULLTERM;
# line 1839 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1839 "gdb_client_syb.cp"
                   }
# line 1839 "gdb_client_syb.cp"
                   
# line 1839 "gdb_client_syb.cp"
               }
# line 1839 "gdb_client_syb.cp"
               
# line 1839 "gdb_client_syb.cp"
           }
# line 1839 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1841 "gdb_client_syb.cp"

      strcpy(tunion->t_str,date_val);
      *t_ind  = (long)ind_val;
      break;

    case SB_INTEGER :
      
           /*
           ** SQL STATEMENT: 61
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
           **                               :int_val  = DATA,
           **                               :ind_val  = INDICATOR;

           */
# line 1849 "gdb_client_syb.cp"
# line 1847 "gdb_client_syb.cp"
           {
# line 1847 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1847 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1847 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1847 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1847 "gdb_client_syb.cp"
               {
# line 1847 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1847 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 1847 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1847 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1847 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1847 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1847 "gdb_client_syb.cp"
                   {
# line 1847 "gdb_client_syb.cp"
                       _sql->dfmtCS_INT_TYPE.count = 0;
# line 1847 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1847 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1847 "gdb_client_syb.cp"
                           CS_GETATTR, idx, &_sql->dfmtCS_INT_TYPE, &int_val, 
# line 1847 "gdb_client_syb.cp"
                           CS_UNUSED, NULL, &ind_val);
# line 1847 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_INT_TYPE, CS_INT_TYPE);
# line 1847 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1847 "gdb_client_syb.cp"
                   }
# line 1847 "gdb_client_syb.cp"
                   
# line 1847 "gdb_client_syb.cp"
               }
# line 1847 "gdb_client_syb.cp"
               
# line 1847 "gdb_client_syb.cp"
           }
# line 1847 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1849 "gdb_client_syb.cp"

      tunion->t_int = int_val;
      *t_ind  = (long)ind_val;
      break;

    case SB_TINYINT :
    case SB_BIT :
    case SB_SMALLINT :
      
           /*
           ** SQL STATEMENT: 62
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
           **                               :short_val = DATA,
           **                               :ind_val   = INDICATOR;

           */
# line 1859 "gdb_client_syb.cp"
# line 1857 "gdb_client_syb.cp"
           {
# line 1857 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1857 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1857 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1857 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1857 "gdb_client_syb.cp"
               {
# line 1857 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1857 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 1857 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1857 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1857 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1857 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1857 "gdb_client_syb.cp"
                   {
# line 1857 "gdb_client_syb.cp"
                       _sql->dfmtCS_SMALLINT_TYPE.count = 0;
# line 1857 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1857 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1857 "gdb_client_syb.cp"
                           CS_GETATTR, idx, &_sql->dfmtCS_SMALLINT_TYPE, 
# line 1857 "gdb_client_syb.cp"
                           &short_val, CS_UNUSED, NULL, &ind_val);
# line 1857 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_SMALLINT_TYPE, 
# line 1857 "gdb_client_syb.cp"
                           CS_SMALLINT_TYPE);
# line 1857 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1857 "gdb_client_syb.cp"
                   }
# line 1857 "gdb_client_syb.cp"
                   
# line 1857 "gdb_client_syb.cp"
               }
# line 1857 "gdb_client_syb.cp"
               
# line 1857 "gdb_client_syb.cp"
           }
# line 1857 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1859 "gdb_client_syb.cp"

      tunion->t_short = short_val;
      *t_ind  = (long)ind_val;
      break;

    case SB_SMALLMONEY :
    case SB_REAL_OLD :
    case SB_REAL :
      
           /*
           ** SQL STATEMENT: 63
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
           **                               :float_val = DATA,
           **                               :ind_val   = INDICATOR;

           */
# line 1869 "gdb_client_syb.cp"
# line 1867 "gdb_client_syb.cp"
           {
# line 1867 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1867 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1867 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1867 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1867 "gdb_client_syb.cp"
               {
# line 1867 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1867 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 1867 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1867 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1867 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1867 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1867 "gdb_client_syb.cp"
                   {
# line 1867 "gdb_client_syb.cp"
                       _sql->dfmtCS_REAL_TYPE.count = 0;
# line 1867 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1867 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1867 "gdb_client_syb.cp"
                           CS_GETATTR, idx, &_sql->dfmtCS_REAL_TYPE, 
# line 1867 "gdb_client_syb.cp"
                           &float_val, CS_UNUSED, NULL, &ind_val);
# line 1867 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_REAL_TYPE, CS_REAL_TYPE);
# line 1867 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1867 "gdb_client_syb.cp"
                   }
# line 1867 "gdb_client_syb.cp"
                   
# line 1867 "gdb_client_syb.cp"
               }
# line 1867 "gdb_client_syb.cp"
               
# line 1867 "gdb_client_syb.cp"
           }
# line 1867 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1869 "gdb_client_syb.cp"

      tunion->t_float = float_val;
      *t_ind  = (long)ind_val;
      break;

    case SB_MONEY :
    case SB_FLOAT :
    case SB_NUMERIC :
    case SB_DECIMAL :
      
           /*
           ** SQL STATEMENT: 64
           ** EXEC SQL GET DESCRIPTOR :syb_descriptor_name value :idx 
           **                               :dbl_val = DATA,
           **                               :ind_val = INDICATOR;

           */
# line 1880 "gdb_client_syb.cp"
# line 1878 "gdb_client_syb.cp"
           {
# line 1878 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1878 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1878 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1878 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1878 "gdb_client_syb.cp"
               {
# line 1878 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1878 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_GET_DESCRIPTOR;
# line 1878 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_UNUSED;
# line 1878 "gdb_client_syb.cp"
                   _sql->descName.fnlen = CS_NULLTERM;
# line 1878 "gdb_client_syb.cp"
                   strcpy(_sql->descName.first_name, syb_descriptor_name);
# line 1878 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1878 "gdb_client_syb.cp"
                   {
# line 1878 "gdb_client_syb.cp"
                       _sql->dfmtCS_FLOAT_TYPE.count = 0;
# line 1878 "gdb_client_syb.cp"
                       _sql->retcode = ct_dyndesc(_sql->conn.command, 
# line 1878 "gdb_client_syb.cp"
                           _sql->descName.first_name, _sql->descName.fnlen, 
# line 1878 "gdb_client_syb.cp"
                           CS_GETATTR, idx, &_sql->dfmtCS_FLOAT_TYPE, &dbl_val,
# line 1878 "gdb_client_syb.cp"
                            CS_UNUSED, NULL, &ind_val);
# line 1878 "gdb_client_syb.cp"
                       _sqlInitDfmt(&_sql->dfmtCS_FLOAT_TYPE, CS_FLOAT_TYPE);
# line 1878 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1878 "gdb_client_syb.cp"
                   }
# line 1878 "gdb_client_syb.cp"
                   
# line 1878 "gdb_client_syb.cp"
               }
# line 1878 "gdb_client_syb.cp"
               
# line 1878 "gdb_client_syb.cp"
           }
# line 1878 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1880 "gdb_client_syb.cp"

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
    
           /*
           ** SQL STATEMENT: 64
           ** EXEC SQL BEGIN DECLARE SECTION ;
           */
# line 1901 "gdb_client_syb.cp"

    char	 txtBuf[25] ;
    
           /*
           ** SQL STATEMENT: 65
           ** EXEC SQL END DECLARE SECTION ;
           */
# line 1903 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 1903 "gdb_client_syb.cp"


    sprintf(txtBuf,"SET TEXTSIZE %ld", limit) ;
    
           /*
           ** SQL STATEMENT: 66
           ** EXEC SQL AT :connect_name EXECUTE IMMEDIATE :txtBuf ;
           */
# line 1906 "gdb_client_syb.cp"
# line 1906 "gdb_client_syb.cp"
           {
# line 1906 "gdb_client_syb.cp"
                _SQL_CT_HANDLES * _sql;
# line 1906 "gdb_client_syb.cp"
               _sqlinitctx(&_sql, CS_CURRENT_VERSION, CS_TRUE, &sqlca, (long 
# line 1906 "gdb_client_syb.cp"
                   *)NULL, (CS_CHAR *)NULL);
# line 1906 "gdb_client_syb.cp"
               if (_sql != (_SQL_CT_HANDLES *) NULL)
# line 1906 "gdb_client_syb.cp"
               {
# line 1906 "gdb_client_syb.cp"
                   _sql->stmtData.persistent = CS_FALSE;
# line 1906 "gdb_client_syb.cp"
                   _sql->stmttype = SQL_EXECUTE_IMMEDIATE;
# line 1906 "gdb_client_syb.cp"
                   _sql->connName.lnlen = CS_NULLTERM;
# line 1906 "gdb_client_syb.cp"
                   strcpy(_sql->connName.last_name, connect_name);
# line 1906 "gdb_client_syb.cp"
                   if ((_sql->retcode = _sqlprolog(_sql)) == CS_SUCCEED)
# line 1906 "gdb_client_syb.cp"
                   {
# line 1906 "gdb_client_syb.cp"
                       _sql->retcode = ct_dynamic(_sql->conn.command, 
# line 1906 "gdb_client_syb.cp"
                           CS_EXEC_IMMEDIATE, NULL, CS_UNUSED, txtBuf, 
# line 1906 "gdb_client_syb.cp"
                           CS_NULLTERM);
# line 1906 "gdb_client_syb.cp"
                       _sql->retcode = ct_send(_sql->conn.command);
# line 1906 "gdb_client_syb.cp"
                       _sql->hastate = (_sql->retcode == CS_RET_HAFAILOVER);
# line 1906 "gdb_client_syb.cp"
                       _sql->retcode = _sqlResults(_sql);
# line 1906 "gdb_client_syb.cp"
                       _sql->retcode = _sqlepilog(_sql);
# line 1906 "gdb_client_syb.cp"
                   }
# line 1906 "gdb_client_syb.cp"
                   
# line 1906 "gdb_client_syb.cp"
               }
# line 1906 "gdb_client_syb.cp"
               
# line 1906 "gdb_client_syb.cp"
           }
# line 1906 "gdb_client_syb.cp"
           

           /*
           ** Generated code ends here.
           */
# line 1906 "gdb_client_syb.cp"

    return (sqlca.sqlcode < 0 ? GDB_EXT_ERROR : GDB_SUCCESS);

}


           /*
           ** Generated code begins here.
           */
# line 1911 "gdb_client_syb.cp"

           /*
           ** Generated code ends here.
           */
# line 1911 "gdb_client_syb.cp"
