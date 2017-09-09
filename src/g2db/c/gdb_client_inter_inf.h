/*================================================================
 *  GDB_CLIENT_INTER_INF.H  - GDB Layer-3 (Informix-7.10) [header]
 *================================================================*/

#ifndef GDB_CLIENT_INTER_INF_H
#define GDB_CLIENT_INTER_INF_H

/*-----------------------
    defines
  -----------------------*/

#define WARN2    " W:Truncated value"
#define WARN5    " W:Update or delete without *where*"

/*-----------------------
    globals
  -----------------------*/

  typedef struct SQLDA_PTRS {
      gSQLDA     *bptr;
      gSQLDA     *sptr;                 
  } SQLDA_PTRS;

#endif
