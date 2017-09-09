/*================================================================
 *  GDB_COMMON.H  - GDB Layer-2                           [header]
 *================================================================
 *   This module should only be #included in parent layers.
 *   Constants in this module may support layers 1 & 2 only. 
 *   If a value in this layer is needed in a child layer, then the
 *   value should be passed as a function argument.
 *================================================================*/

#ifndef GDB_COMMON_H
#define GDB_COMMON_H

/*-----------------------
    defines
  -----------------------*/

/* defaults */
#define  DFLT_GENDA_ROWS      200L    /* 1000L */
#define  DFLT_FLOAT_FLAG      TRUE    /* convert function results to float */
#define  DFLT_CONSOLE_OUTPUT  TRUE    /* output messages to console */
#define  DFLT_DB_RECONNECT    FALSE   /* auto-db-reconnect */
#define  DFLT_ENABLE_MESSAGES TRUE    /* enable messaging */
#define  DFLT_AUTO_COMMIT     FALSE   /* enable auto-commit */

#  define DFLT_NULL_STR      _T("")
#  define DFLT_SET_NULL_STR  _T("NULL")

#define  DFLT_NULL_NUM        0L
#define  DFLT_SET_NULL_NUM     -536870912 /* -2**29 */
#define  DFLT_SET_NULL_OPTIONS 100 ;       /* "Null" on, set nulls off */
#define  DFLT_SMART_FETCH     FALSE   /* intelligent retrieval of DECIMAL(x,0) values */

/* limits */
#define  MAX_GENDA_ROWS       50001L   /* max # of rows to alloc for GENDA data */
#define  MAX_FETCH_BATCH      50001L   /* max # of rows per batch to return to G2 */
#define  MAXDEFPARAMLEN       80L     /* max length of init param fields */

/* misc */
#define  DELIM                '-'     /* delimiter used with init params */

/* for handles */
#define  HDL_INUSE            1L
#define  HDL_UNAVAILABLE      0L
#define  HDL_FREE             0L      /* must be 0 */
#define  HDL_GET              1L

/*-----------------------
    triggers
  -----------------------*/


#define  G2_TRIGGER_MSG_PROC       _T("DB-TRIGGER-EVENT")

#define  MAX_TRIGGERS              51L  /* (1->51 = 50) */

/* triggers are not necessarily context sensitive */
typedef struct {
                    long     count;
                    long     timeLastChecked;
                    long     checkInterval;
                    GDB_CHAR  *names[MAX_TRIGGERS]; /* /// /??????? check me  */
                    gsi_int  obj_handle[MAX_TRIGGERS];
                    gsi_int  context[MAX_TRIGGERS];   } trig_struct ;



/*-----------------------
    prototypes
  -----------------------*/
long    alloc_genda(GENDA *sqlGen, long flag) ;
long    free_genda(long action, GENDA *sqlGen) ;
GENDA  *init_genda(long obj_index) ;
long    process_commit(void) ;
long    process_connect(GDB_CHAR *db_user, GDB_CHAR *db_pass, GDB_CHAR *c_str, GDB_CHAR *gsi_connection_str) ;/* add gsi-connection-string. modified for project 28544 Gensym-2012 */
long    process_disconnect(long cleanup_reconnect, gsi_int context_num ) ;
long    process_set_query(GDB_CHAR *sql_stmt, GENDA *sqlGen, long query_type) ;
long    process_set_dynamic_query(GDB_CHAR *sql_stmt, BIND_STRUCT *bind_vars, GENDA *sqlGen, long query_type) ;
long    process_refresh_cursor(GENDA *sqlGen) ;
long    process_rollback() ;
GENDA  *process_sql_function(GDB_CHAR *str) ;
long    execute_stored_proc(GDB_CHAR *sql_stmt) ;
long    execute_stored_proc_return(GDB_CHAR *a, GDB_CHAR *b, GDB_CHAR *c) ;
long    process_stored_proc(GDB_CHAR *sql_stmt, GENDA *sqlGen) ;
long    process_ping_db() ;
long    set_init_params(GDB_CHAR *init_str, long action) ;
long    show_results(GENDA *sqlGen) ;
long    update_genda(GENDA *sqlGen) ;
long    logfileio(long action, GDB_CHAR *iostr) ;

long    iomsg (long flag, long layer, long write_logfile, long setstat, 
	       GENDA *sqlGen, long row_reset, char *argtypes, ...);
long    load_msg( long severity_cd, long idx, long *msg_code, GDB_CHAR *msg_buff, long action );
long    set_stat( long status_id, long msg_id, GENDA *sqlGen, long row_reset, GDB_CHAR *msg_addr );
long    process_reconnect( void );
long    process_trigger( GDB_CHAR *trig_name, long trig_timeout, GDB_CHAR *trig_ret_msg, gsi_int context_num );
long    get_stmt_handle( long *shandle, long action );
long    process_immediate(GDB_CHAR  *stmt) ;
long    process_set_exec_sql_obj( void **bind_vars, GENDA *sqlGen, long index, 
               long datatype, long array_size );
long    process_exec_sql_obj( GENDA *sqlGen, long array_size );
long    process_set_exec_sql( GDB_CHAR *sql_stmt, BIND_STRUCT *bind_vars, GENDA *sqlGen, long exec_type );
long    process_exec_sql( GENDA *sqlGen );
long    process_release_bind( long action, GENDA *sqlGen );
long    process_count_bind_vars( GENDA *sqlGen, GDB_CHAR *bind_vars );
long    process_poll_check ();
long    configure_DSN(gsi_int action, gsi_char* DrvrName, gsi_item* pStruct) ;
long    uses_DSN() ;

#endif
