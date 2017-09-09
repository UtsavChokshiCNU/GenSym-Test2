/*================================================================
 *  GDB_CLIENT_INTER_ORA.H  - GDB Layer-3                [header]
 *================================================================*/

#ifndef GDB_CLIENT_INTER_ORA_H
#define GDB_CLIENT_INTER_ORA_H

/*-----------------------
    defines
  -----------------------*/

#define WARN2    "W:Truncated value"
#define WARN5    "W:Update or delete without *where*"

/*-----------------------
    globals
  -----------------------*/

typedef struct { SQLDA       *bptr;
                 SQLDA       *sptr;
                 int         fCursorOpen ; } SQLDA_PTRS ;

#define NIO sizeof(SQLDA_PTRS)
#endif
