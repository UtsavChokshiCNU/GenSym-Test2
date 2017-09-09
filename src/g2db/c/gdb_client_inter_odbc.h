/*================================================================
 *  GDB_CLIENT_INTER_ODBC.H  - GDB Layer-3  (ODBC 2.0)
 *================================================================*/

#ifndef GDB_CLIENT_INTER_ODBC_H
#define GDB_CLIENT_INTER_ODBC_H

/*-----------------------
    globals
  -----------------------*/

  typedef struct SQLDA_PTRS {
      gSQLDA     *bptr;
      gSQLDA     *sptr;                 
  } SQLDA_PTRS;

#endif
