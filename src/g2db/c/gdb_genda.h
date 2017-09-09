/*================================================================
 *  GDB_GENDA.H                                           [header]
 *================================================================*/

#ifndef GDB_GENDA_H
#define GDB_GENDA_H

/*-----------------------
    globals
  -----------------------*/

  typedef union {
    GDB_BYTE     gdb_byte;
    GDB_SHORT    gdb_short;
    GDB_INT      gdb_int;    
    GDB_LONG     gdb_long;
    GDB_FLOAT    gdb_float;
    GDB_DBL      gdb_dbl;
    GDB_CHAR    *gdb_str;
  } DATA_VALUE;

  typedef struct {
    GDB_CHAR     *col_name;
    long         data_type;
    long        *ind;
    DATA_VALUE  *val;
  } COL_DATA;

  typedef struct {       /* this may go away with 6.0 - use gbl_status */
      long       code;
      GDB_CHAR    *msg;
      long       rows_processed;
      long       status;
  } STATUS_STRUCT;

  typedef struct {
      long       genda_num;       /* # of times this GENDA has been updated */
      long       obj_handle;
      long       stmt_id;
      long       stmt_handle;
      GDB_CHAR    *cursor_name;
      long       ncols;           /* # of db columns  */
      long       nrows;           /* # of db rows to store in GENDA  */
      long       array_size;
      long       bind_processed;  /* bool: have bind vars been processed */
      long       genda_pos;       /* index of last GENDA row returned to G2 */
      long       more_rows;       /* # of rows loaded into THIS GENDA  */
      char*      decimal_flags ;
      COL_DATA  *da_col_ptr;
      STATUS_STRUCT genStat;
  } GENDA ;


#endif
