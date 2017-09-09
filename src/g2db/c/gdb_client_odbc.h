/*================================================================
 *  GDB_CLIENT_ODBC.H  - GDB Layer-3         (ODBC)      [header]
 *================================================================*/
#include "gdb_globals.h"

#ifndef GDB_CLIENT_ODBC_H
#define GDB_CLIENT_ODBC_H


/*-----------------------
    defines
  -----------------------*/

#define  MAX_VNAME_LEN         128   /* (SQLDATA) initial max value length */  
#define  MAX_COLNAME_LEN        30  
#define  MAX_NATIVE_ERRLEN     256   /* Max length of mssage returned from SQLError */
#define  MAX_ODBC_ERRMSGS        5   /* Max error messages per ODBC call */
#define  MAX_DATE_LEN           23   /* Max length of timestamp data from ODBC */
#define  SS_LEN                  9   /* Length of "ss=xxxxx " (xxxxx is SQLSTATE) */
#define  MAX_ODBC_MSG_LEN       STATUS_MSG_LEN - 10
#define  MAX_INAME_LEN         128   /* (SQLIND) max indicator len */

/* db specific codes */
#define  DB_NOT_CONNECTED      -47
#define  DB_END_OF_CURSOR      100

/* Specific SQLSTATEs from ODBC */
#define  DB_ALREADY_CONNECTED  _T("08002")
#define  DB_CONNECT_NOT_OPEN   _T("08003")

/*-----------------------
    globals
  -----------------------*/

struct gSQLDA {
    long            ncols;
    GDB_CHAR*       colname;
    long            datalen;
    short           datatype;         /* long */
    long            retlength;
    long            colsize; 
    short           decdigs;          /* scale; */
    short           nullable;         /* long */
    long*           ind;
    GDB_CHAR*       data;
    GDB_CHAR*       bdata;            /* holds bind data */
    long            row_count; } ;    /* number of rows returned by fetch */
 typedef struct gSQLDA gSQLDA ;

 typedef struct SQLSTATE_INFO {
      GDB_CHAR         sqlstate[6];
      DWORD           native_errcode;
      GDB_CHAR         native_errmsg[SQL_MAX_MESSAGE_LENGTH + 1];
      WORD            native_errlen;
  } SQLSTATE_INFO;
  
   typedef struct ODBCERR {
      long            code;
      SQLSTATE_INFO   state_array[MAX_ODBC_ERRMSGS];
  } ODBCERR;

  typedef union {
      unsigned char    t_byte;
      short            t_short;
      int              t_int;
      long             t_long;
      float            t_float;
      double           t_dbl;
      char            *t_str;
      GDB_CHAR*         t_wstr ;
  } TRANS_VALUE;


#endif

