/*================================================================
 *  GDB_CLIENT_RDB.H  - GDB Layer-3         (RDB)         [header]
 *================================================================*/

/* The SQLCA & SQLDA data structures incorporated into this file
   were extracted from the DEC Rdb SQL Reference Manual Appendix
   B & C. In some cases these structures where modified to provide
   a cleaner interface to GENDA. This file should be verified and
   modified (if necessary) whenever these Rdb data structures are
   changed by DEC. */

#ifndef GDB_CLIENT_RDB_H
#define GDB_CLIENT_RDB_H

/*-----------------------
    defines
  -----------------------*/

#define  MAX_VNAME_LEN       128   /* (SQLDATA) initial max value length  */
#define  MAX_INAME_LEN       128   /* (SQLIND) max indicator len */
#define  MAX_COLNAME_LEN      30  
#define  DATE_LEN             24   /* 13=date_only, 24=date+time */
#define  RDB_MAX_TRIGGER_NAME_LEN  30   /* Check Database */

/* datatypes */
#define  VARCHAR             449
#define  CHAR                453
#define  FLOAT               481
#define  DECIMAL             485
#define  INTEGER             497
#define  SMALLINT            501
#define  DATE                503
#define  BIGINT              505  /* for clarity */
#define  QUADWORD            505
#define  STRING              507  /* ASCIZ */
#define  SEGSTRING           509
#define  TINYINT             515
#define  VARBYTE             516

/* db specific codes */
#define  DB_NOT_CONNECTED_START   -1022
#define  DB_NOT_CONNECTED_STOP    -1016   /* this is a major hack */
#define  DB_CONNECTION_IN_USE     -1017
#define  DB_NOT_CONNECTED1        -1012
#define  DB_NOT_CONNECTED2        -3113
#define  DB_NOT_CONNECTED3        -3114
#define  CURSOR_NOT_OPEN           -501
#define  DB_END_OF_CURSOR           100

/*-----------------------
    globals
  -----------------------*/

#ifdef XXX
  typedef struct SQLVAR2_STRUCT {
        short SQLTYPE;
        long  SQLLEN;
        long  SQLOCTET_LEN;
        char  *SQLDATA;
        long  *SQLIND;
        long  SQLCHRONO_SCALE;
        long  SQLCHRONO_PRECISION;
        short SQLNAME_LEN;
        char  SQLNAME[MAX_COLNAME_LEN];
        char  SQLCHAR_SET_NAME[MAX_COLNAME_LEN];
        char  SQLCHAR_SET_SCHEMA[MAX_COLNAME_LEN];
        char  SQLCHAR_SET_CATALOG[MAX_COLNAME_LEN];
      } SQLVAR2_STRUCT;  
#endif

  typedef struct gSQLCA {
      char  SQLCAID[8];
      int   SQLCABC;
      int   SQLCODE;
      struct { 
        short   SQLERRML;
        char    SQLERRMC[70];  /* for now, const in gdb_common.h */
      } SQLERRM;
      int SQLERRD[6];
      struct { 
        char SQLWARN0[1];
        char SQLWARN1[1];
        char SQLWARN2[1];
        char SQLWARN3[1];
        char SQLWARN4[1];
        char SQLWARN5[1];
        char SQLWARN6[1];
        char SQLWARN7[1];
      } SQLWARN; /* not used in RDB SQL */
      char SQLEXT[8];
    } gSQLCA;

  typedef struct SQLVAR_STRUCT {
      short SQLTYPE;
      short SQLLEN;
      char  *SQLDATA;
      short *SQLIND;
      short SQLNAME_LEN;
      char  SQLNAME[MAX_COLNAME_LEN];
  } SQLVAR_STRUCT;  

  typedef struct gSQLDA {
      char  SQLDAID[8];
      int   SQLDABC;
      short SQLN;
      short SQLD;
      SQLVAR_STRUCT SQLVAR[];
  } gSQLDA;

  typedef struct {
    short            *ind;
    char             **data;
  } dSQLDA;

  typedef struct {
    char             **data;
  } HB_STRUCT;

#endif
