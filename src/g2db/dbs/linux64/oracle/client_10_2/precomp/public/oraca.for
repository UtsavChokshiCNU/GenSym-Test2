C     
C     $Header: oraca.for 31-jul-99.19:44:49 apopat Exp $ oraca.for 
C     
C     *****************************************************************
C     *                                                               *
C     *               O  R  A  C  A  .  F  O  R                       *
C     *                                                               *
C     *****************************************************************
C     *                                                               *
C     *  ORAAID : Reserved.                                           *
C     *  ORAABC : Reserved.                                           *
C     *  ORACHF : Check cursor cache consistency flag. If .NE. 0,     *
C     *           then directs SQLLIB to check cursor cache before    *
C     *           every cursor operation (OPEN, FETCH, SELECT, etc.). *
C     *           It's a good idea to set this flag when developing   *
C     *           a new pgm; and to turn it off for Production use    *
C     *           of your pgm because there is a performance          *
C     *           penalty. ORADBF must be set as well.                *
C     *  ORADBF : Master DEBUG flag. If .NE. 0, then put SQLLIB in    *
C     *           DEBUG mode.                                         *
C     *  ORAHPF : Check heap consistency flag. If .NE. 0, directs     *
C     *           SQLLIB to check heap consistency. Useful for deter- *
C     *           mining if someone is clobbering memory "owned" by   *
C     *           the PCC. MUST BE SET BEFORE 1ST CONNECT. Subsequent *
C     *           attempts to change ORAHPF are ignored. ORADBF must  *
C     *           also be set.                                        *
C     *  ORATXF : Save text of SQL stmt flag. If set, then text       *
C     *           of current SQL stmt will be saved in ORATXL and     *
C     *           ORATXC (in VARCHAR format).                         *
C     *                                                               *
C     *           0 = Don't save text of SQL stmt (default).          *
C     *           1 = Save SQL stmt on SQLWARNING/SQLERROR.           *
C     *           2 = Save SQL stmt on SQLERROR.                      *
C     *           3 = Always save SQL stmt.                           *
C     *                                                               *
C     *  ORATXL : Nr of chars in ORATXC                               *
C     *  ORATXC : Saved text of SQL stmt                              *
C     *  ORAFNL : Nr of chars in ORAFNC                               *
C     *  ORAFNC : Saved filename containing SQL stmt                  *
C     *  ORASLN : Saved line within file containing SQL stmt          *
C     *                                                               *
C     *   Cursor cache statistics. Set after COMMIT or ROLLBACK. Each *
C     *   CONNECT'd DATABASE has its own set of statistics.           *
C     *                                                               *
C     *   ORAHOC  : Highest Max Open OraCursors requested. Highest    *
C     *             value for MAXOPENCURSORS by any CONNECT to this   *
C     *             DATABASE.                                         *
C     *   ORAMOC  : Max Open OraCursors required. Specifies the max nr*
C     *             of OraCursors required to run this pgm. Can be    *
C     *             higher than ORAHOC if working set (MAXOPENCURSORS)*
C     *             was set too low, thus forcing the PCC to expand   *
C     *             the cache.                                        *
C     *   ORACOC  : Current nr of OraCursors used.                    *
C     *   ORANOR  : Nr of OraCursor cache reassignments. Can show the *
C     *             degree of "thrashing" in the cache. Optimally,    *
C     *             this nr should be kept as low as possible (time   *
C     *             vs space optimization).                           *
C     *   ORANPR  : Nr of SQL stmt "parses".                          *
C     *   ORANEX  : Nr of SQL stmt "executes". Optimally, the rela-   *
C     *             tionship of ORANEX to ORANPR should be kept as    *
C     *             high as possible.                                 *
C     *                                                               *
C     *****************************************************************
C     *  Note: some compilers do  not  allow CHAR and INT data in the *
C     *  same common block;  therefore the CHAR vars are declared as  *
C     *  LOGICAL*1.  Sigh.                                            *
C     *****************************************************************
C     * MODIFIED                                                      *
C     *   Clare      02/20/86 - Add heap consistency check.           *
C     *   Clare      03/12/86 - ORACA cuc statistics.                 *
C     *****************************************************************
 
      LOGICAL*1   ORAAID  (8)
      INTEGER*4   ORAABC
C
C     Flags which can be set by User.
C
      INTEGER*4   ORACHF
      INTEGER*4   ORADBF
      INTEGER*4   ORAHPF
      INTEGER*4   ORATXF
C
C     ORASTXT : Saved SQL stmt.
C
      INTEGER*2   ORATXL
      LOGICAL*1   ORATXC (70)
C
C     ORASFNM : Saved filename containing SQL stmt.
C
      INTEGER*2   ORAFNL
      LOGICAL*1   ORAFNC (70)
C
C     ORASLN : Saved line nr within ORASFNM of SQL stmt.
C
      INTEGER*4   ORASLN
C
C     Cursor cache statistics.
C
      INTEGER*4   ORAHOC
      INTEGER*4   ORAMOC
      INTEGER*4   ORACOC
      INTEGER*4   ORANOR
      INTEGER*4   ORANPR
      INTEGER*4   ORANEX
 
      COMMON /ORACA/
     1  ORAAID,ORAABC,
     2  ORACHF,ORADBF,ORAHPF,ORATXF,
     3  ORATXL,ORATXC,ORAFNL,ORAFNC,ORASLN,
     4  ORAHOC,ORAMOC,ORACOC,ORANOR,ORANPR,ORANEX
C
C     END ORACA
