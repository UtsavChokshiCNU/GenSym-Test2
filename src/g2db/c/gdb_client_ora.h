/*================================================================
 *  GDB_CLIENT_ORA.H  - GDB Layer-3                       [header]
 *================================================================*/

#ifndef GDB_CLIENT_ORA_H
#define GDB_CLIENT_ORA_H

#include "sqlca.h"
#include "sqlcpr.h"
#include "sqlda.h"   /* should use mms */

/*-----------------------
    defines
  -----------------------*/

#define WARN2    _T("W:Truncated value")
#define WARN5    _T("W:Update or delete without *where*")

/*-----------------------
    globals
  -----------------------*/
typedef struct { SQLDA  *bptr;
                 SQLDA  *sptr;
                 int    fCursorOpen ;  } SQLDA_PTRS ;

/*-----------------------
    defines
  -----------------------*/

#define  MAX_VNAME_LEN          128      /* (V) initial max value length (USE DFLT_BIND_VALUE_LEN) */
#define  MAX_INAME_LEN          128      /* (I) max indicator len (USE DFLT_BIND_VALUE_LEN) */
#define  MAX_COLNAME_LEN         30
#define  DATE_LEN                24

/* Oracle specific datatypes */
#define  ORA_VARCHAR2             1
#define  ORA_NUMBER               2
#define  ORA_INTEGER              3
#define  ORA_FLOAT                4
#define  ORA_STRING               5  
#define  ORA_LONG                 8
#define  ORA_VARCHAR              9
#define  ORA_DOUBLE              10      /* added for clarity */
#define  ORA_ROWID               11 
#define  ORA_DATE                12
#define  ORA_RAW                 23
#define  ORA_LONGRAW             24 
#define  ORA_CHAR                96
#define  ORA_MLSLABEL           106

#define  DB_ALREADY_CONNECTED -1075
#define  DB_NOT_CONNECTED1    -1012
#define  DB_NOT_CONNECTED2    -3113
#define  DB_NOT_CONNECTED3    -3114
#define  DB_END_OF_CURSOR      1403    /*100=ansi,1403=oracle*/
#define  CURSOR_NOT_OPEN      -1002
#define  DB_EMPTY_PIPE        -1405


#endif
