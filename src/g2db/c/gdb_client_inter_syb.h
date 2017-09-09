/*================================================================
 *  GDB_CLIENT_INTER_SYB.H  - GDB Layer-3  (Sybase 10.0.1)
 *================================================================*/

#ifndef GDB_CLIENT_INTER_SYB_H
#define GDB_CLIENT_INTER_SYB_H

/*-----------------------
    defines
  -----------------------*/

#define WARN2            " W:Truncated value"
                    
/*-----------------------
    sybase libraries (error-levels)
  -----------------------*/

#define SYB_CTLIB        1L
#define SYB_CSLIB        2L
#define SYB_GP           3L
#define SYB_PSL          4L
#define SYB_NETP         5L

/*-----------------------
    macros
  -----------------------*/

typedef long    LONGNUM;
#define MSG_LAYER(L)     (LONGNUM) (((L) >> 24) & 0xff)
#define MSG_ORIGIN(O)    (LONGNUM) (((O) >> 16) & 0xff)
#define MSG_SEVERITY(S)  (LONGNUM) (((S) >> 8) & 0xff)
#define MSG_NUMBER(N)    (LONGNUM) ((N) & 0xff)


/*-----------------------
    globals
  -----------------------*/

  typedef struct SQLDA_PTRS {
      gSQLDA     *bptr;
      gSQLDA     *sptr;                 
  } SQLDA_PTRS;

#endif
