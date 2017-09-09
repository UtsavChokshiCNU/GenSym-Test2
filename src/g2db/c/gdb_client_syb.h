/*================================================================
 *  GDB_CLIENT_SYB.H  - GDB Layer-3         (Sybase)      [header]
 *================================================================*/

#ifndef GDB_CLIENT_SYB_H
#define GDB_CLIENT_SYB_H

#include "csconfig.h" /* for CS_<number> datatypes */

/*-----------------------
    defines
  -----------------------*/

/* max # of columns for Sybase = 256 */

#define  MAX_VNAME_LEN         128   /* (SQLDATA) initial max value length  */
#define  MAX_INAME_LEN         128   /* (SQLIND) max indicator len */
#define  MAX_COLNAME_LEN        30  
#define  SYB_MAX_TRIGGER_NAME_LEN  30 /* defined in sybase database */ 
#define  DATE_LEN               78
#define  UNKNOWN_COLNAME       "UNKNOWN"  /* Used for input descriptors */

/* datatypes */
#define SB_CHAR                  1
#define SB_NUMERIC               2
#define SB_DECIMAL               3
#define SB_INTEGER               4
#define SB_SMALLINT              5
#define SB_FLOAT                 8
/*
** Note: There are 2 definitions for Sybase real types.
**       This is because Sybase changed the value that is returned
**       indicating a real.  In Sybase V10.0.2 and earlier, the value
**       returned was 6.  In Sybase V10.0.3 and up, they are returning
**       the value 7.  Therefore we have 2 definitions.
*/
#define SB_REAL_OLD              6
#define SB_REAL                  7
/*  #define SB_DOUBLE     		           8   */
#define SB_DATETIME              9
#define SB_VARCHAR              12
#define SB_BIT                  14

#define SB_LONGCHAR             -2
#define SB_STRING               -3
#define SB_IMAGE                -4
#define SB_BINARY               -5
#define SB_VARBINARY            -6
#define SB_LONGBINARY           -7
#define SB_TINYINT              -8
#define SB_SMALLDATETIME        -9
#define SB_MONEY               -10
#define SB_SMALLMONEY          -11

/* db specific codes */
#define  CURSOR_NOT_OPEN       -501   /* ?????? */
#define  DB_ALREADY_CONNECTED  -25018
#define  DB_NOT_CONNECTED      -47
#define  DB_END_OF_CURSOR       100

/*-----------------------
    globals
  -----------------------*/

  typedef struct gSQLCA {
      char    sqlcaid[8];
      long    sqlcabc;
      long    sqlcode;
      struct {
        long   sqlerrml;
        char   sqlerrmc[256];
      } sqlerrm;
      char    sqlerrp[8];
      long    sqlerrd[6];
      char    sqlwarn[8];
      char    sqlext[8];
    } gSQLCA;


  typedef struct gSQLDA {
      long            ncols;
      char           *colname;
      long            datalen;
      long            datatype;
      long            retlength;
      long            prec;
      long            scale;
      long            nullable;
      long            row_count; /* number of rows returned by fetch */
      short          *ind;
      char          **data;
  } gSQLDA;


  typedef union {
    unsigned char    t_byte;
    short            t_short;
    int              t_int;
    long             t_long;
    float            t_float;
    double           t_dbl;
    char            *t_str;
  } TRANS_VALUE;

#endif
