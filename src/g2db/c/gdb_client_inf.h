/*================================================================
 *  GDB_CLIENT_INF.H  - GDB Layer-3                       [header]
 *================================================================*/

#ifndef GDB_CLIENT_INF_H
#define GDB_CLIENT_INF_H

#include "sqltypes.h"
#include "sqlstype.h"
/*-----------------------
    defines
  -----------------------*/

#define  MAX_COLNAME_LEN           256
#define  DATE_LEN                 3081    /* hack for Informix datetime bug */
#define  DEF_TXT_BUF_SIZE          512
#define  INF_MAX_TRIGGER_NAME_LEN  18 /* defined in Informix database */ 

/* Informix specific datatypes */

#define INF_CHAR                SQLCHAR         /*   0 */
#define INF_SMINT               SQLSMINT        /*   1 */
#define INF_INTEGER             SQLINT          /*   2 */
#define INF_FLOAT               SQLFLOAT        /*   3 */
#define INF_SMFLOAT             SQLSMFLOAT      /*   4 */
#define INF_DECIMAL             SQLDECIMAL      /*   5 */
#define INF_SERIAL              SQLSERIAL       /*   6 */
#define INF_DATE                SQLDATE         /*   7 */
#define INF_MONEY               SQLMONEY        /*   8 */
#define INF_NULL                SQLNULL         /*   9 */
#define INF_DTIME               SQLDTIME        /*  10 */
#define INF_BYTE                SQLBYTES        /*  11 */
#define INF_TEXT                SQLTEXT         /*  12 */
#define INF_VCHAR               SQLVCHAR        /*  13 */
#define INF_INTERVAL            SQLINTERVAL     /*  14 */
#define INF_NCHAR               SQLNCHAR        /*  15 */
#define INF_NVCHAR              SQLNVCHAR       /*  16 */
#define INF_STRING              CSTRINGTYPE    /* 109 */ /* This used be CSSTRING but not in sqltypes.h */

#define  DB_ALREADY_CONNECTED    -1802
#define  DB_NOT_CONNECTED        -1803
#define  DB_END_OF_CURSOR          100
#define  DB_SERVER_BUSY           -439

/* The following 2 defs are for the indicator field of Informix descriptors */
#define  INF_NULL_IND                   -1
#define  INF_NON_NULL_IND                0

/*-----------------------
    globals
  -----------------------*/

  typedef struct gSQLCA {
      long            sqlcode;
      char            sqlerrm[72];
      char            sqlerrp[8];
      long            sqlerrd[6];
      struct gsqlcaw_s {
        char      sqlwarn0;
        char      sqlwarn1;
        char      sqlwarn2;
        char      sqlwarn3;
        char      sqlwarn4;
        char      sqlwarn5;
        char      sqlwarn6;
        char      sqlwarn7;
      } sqlwarn;
    } gSQLCA;

  typedef struct gSQLDA {
      short           ncols;
      char           *colname;
      short           datalen;
      short           datatype;
      long            retlength;
      long            prec;
      long            scale;
      long            nullable;
      short          *ind;
      char          **data;
      long            row_count;
  } gSQLDA;

  typedef union {
    short        t_short;
    int          t_int;
    long         t_long;
    float        t_float;
    double       t_dbl;
    char        *t_str;
  } TRANS_VALUE;


#endif
