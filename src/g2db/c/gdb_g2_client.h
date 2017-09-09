/*================================================================
 *  GDB_G2_CLIENT.H                                       [header]
 *================================================================*/

#ifndef GDB_G2_CLIENT_H
#define GDB_G2_CLIENT_H

/*-----------------------
    prototypes
  -----------------------*/

/* ESQL */

extern long    sql_connect( GDB_CHAR *db_user, GDB_CHAR *db_pass, GDB_CHAR *db_conn_str );
/*{{{ connect db using gsi_connection_string. for project 28544 Gensym-2012 */
#ifdef SUPPORT_GSI_CONNECTION_STR
extern long    sql_connect_ex(GDB_CHAR *gsi_connection_str);
#endif
/*}}}*/
extern long    sql_disconnect( gsi_int context_num );
extern long    sql_set_connection_options( gsi_int context_num );
extern long    sql_ping_db( void );

extern long    sql_setup( void );

extern long    sql_alloc_descriptors( long shandle, long action );
extern long    sql_dealloc_descriptors( long shandle, long action );
extern long    sql_release( long *stmt_id );

extern long    sql_describe_input( long shandle, BIND_STRUCT *bind_vars, long *stmt_id, long *bind_processed, long action );
extern long    sql_describe_output( GENDA* sqlGen, long query_type );

extern long    sql_prepare( long shandle, long *stmt_id, GDB_CHAR *sql_str );
extern long    sql_declare_cursor( GDB_CHAR *curs_name, long shandle, long *stmt_id );
extern long    sql_refresh_cursor( GDB_CHAR *curs_name, long shandle );
extern long    sql_fetch( GDB_CHAR *curs_name, long shandle );
extern long    sql_close_cursor( GDB_CHAR *curs_name, long shandle, long release_cursor );
extern long    sql_close_cursor_release( GDB_CHAR *curs_name, long shandle );

extern long    sql_commit( void );
extern long    sql_rollback( void );

extern long    sql_exec_stored_proc( GDB_CHAR *sql_stmt );
extern long    sql_exec_stored_proc_return( GDB_CHAR *sp_proc_name, GDB_CHAR *sp_proc_args, GDB_CHAR *sp_proc_return_text );
extern long    sql_trigger(GDB_CHAR *trig_name, long trig_timeout, GDB_CHAR *trig_ret_msg, gsi_int context_num);

extern long    sql_exec_sql( GDB_CHAR *stmt_str );
extern long    sql_exec_dynamic_sql( long shandle, long stmt_id );
extern long    sql_exec_sql_obj( long shandle, long array_size, long stmt_id );

extern long    sql_release_bind( long shandle, long action );

/* Utilities */

extern long    count_bind_vars( long shandle, GDB_CHAR *bind_vars );
extern long    load_bind_vars( long shandle, void **bind_vars, long index, long datatype, long array_size );
extern long    get_stat( GENDA *sqlGen );
extern long    get_genda_data( GENDA *sqlGen );
extern long    alloc_sqlda_ptrs( void );
extern long    db_alloc_genda( GENDA *sqlGen, long max_rows );
extern long    sql_poll_check();
extern long    sql_configure_DSN(gsi_int action, gsi_char* DrvrName, gsi_item* pKVStruct, gsi_int *piCode, gsi_char** pDSNName ) ;
extern long    sql_uses_DSNs() ;

#endif /* GDB_G2_CLIENT_H */
