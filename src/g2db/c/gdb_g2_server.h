/*================================================================
 *  GDB_G2_SERVER.H  - GDB Layer-1                        [header]
 *================================================================
 *   This module contains information specific to GDB layer-1.
 *================================================================*/

#ifndef GDB_G2_SERVER_H
#define GDB_G2_SERVER_H

/*-----------------------
    floats - to correct GSI problem
  -----------------------*/
#if defined(vms) && defined(__alpha)
#define flt_of(o_v_t_p)      ((o_v_t_p)->p_value.float_p)
#define set_flt(o_v_t_p,dbl) ((o_v_t_p)->p_type=FLOAT64_TAG,\
                              (o_v_t_p)->p_value.float_p=dbl)
#endif

/*-----------------------
    defines
  -----------------------*/

/* user array */
#define  GET                       1L
#define  SET                       2L
#define  ACTIVE                    3L

/* nulls */
#define  GDB_NULL_CHAR             0L
#define  GDB_NULL_PTR              0L
#define  GDB_NULL_OBJ             -1L
#define  GDB_NULL_ROW             -1L
#define  GDB_NULL_CONTEXT         -1L

/* messaging */
#define  STAT_POS                  0L    /* Positions within rpc ret array */
#define  CODE_POS                  1L
#define  MSG_POS                   2L
#define  NROWS_POS                 3L
#define  FACILITY_POS              3L
#define  INDX_POS                  4L
#define  CURSOR_POS                4L
#define  TIMESTAMP_POS             4L

#define  STAT_ATT                  _T("DB-STATUS")
#define  CODE_ATT                  _T("DB-CODE")
#define  MSG_ATT                   _T("DB-MESSAGE")
#define  NROWS_ATT                 _T("DB-ROWS-PROCESSED")
#define  CURSOR_ATT                _T("DB-CURSOR-POSITION")
#define  IDX_ATT                   _T("OBJECT-HANDLE")
#define  FACILITY_INTERNAL         _T("INTERNAL")
#define  FACILITY_EXTERNAL         _T("EXTERNAL")


/* GENDA mem alloc */
#define  ALLOC_ALL                 0L
#define  ALLOC_ONE                 1L

/* GSI */
#define  MIN_ITEM_HANDLE           1L

/* miscellaneous */
#define  CMD_SZ                    6L
#define  MULTI_CONTEXT_MODE        TRUE

#define  G2_EVENT_MSG_PROC         _T("DB-CONTEXT-EVENT-MSG")
#define  GENSYM_PHONE              _T("(781) 265-7301")

/* item passing */
#define  UNREGISTERED_OBJ_IDX      -100

#define  COL_NAME_ATTRIB           _T("DB-COL-NAMES")
#define  COL_VALUE_ATTRIB          _T("DB-COL-VALUES")
#define  GENERIC_OBJECT_NAME       _T("OBJECT")
#define  ROOT_OBJECT_NAME          _T("DB-QUERY-ITEM")
#define  LIST_OBJECT_NAME          _T("DB-QUERY-ITEM-LIST")
#define  ARRAY_OBJECT_NAME         _T("DB-QUERY-ITEM-ARRAY")
#define  CURSOR_OBJECT_NAME        _T("DB-CURSOR-OBJECT")
#define  TRIGGER_OBJECT_NAME       _T("DB-TRIGGER-OBJECT")
#define  TIME_STAMP_NAME           _T("TIME-STAMP")


#define  LIST_TYPE                 1L
#define  ARRAY_TYPE                2L
#define  OBJECT_REPLACE            1L
#define  OBJECT_APPEND             2L

#define  RETURN_TO_OBJECT          1L
#define  UPDATE_OBJECT_ATTRS       2L
#define  UPDATE_OBJECT_ITEMS       3L
#define  UPDATE_ATTRS              4L
#define  UPDATE_ITEMS              5L

/* configuration */

#define  C_CHARSET                 "DATABASE-CHARSET"
#define  C_CONTEXT_NAME            "CONTEXT-NAME"
#define  C_LOG_FILE                "LOG-FILE"
#define  C_AUTO_RECONNECT          "AUTO-DATABASE-RECONNECT"
#define  C_MAX_CURSORS             "MAXIMUM-DEFINABLE-CURSORS"
#define  C_MAX_COLUMNS             "MAXIMUM-QUERY-COLUMNS"
#define  C_ENABLE_MSG              "ENABLE-MESSAGING"
#define  C_NULL_STR                "NULL-STRING"
#define  C_NULL_NUM                "NULL-NUMBER"
#define  C_ROW_STATUS              "ROW-STATUS-RETURN"

/*-----------------------
    sizes & limits
  -----------------------*/

#define  NUM_STATUS_ARGS           5L
#define  MAX_ATTR_SZ               20L
#define  MAX_SYMB_SZ               10L
#define  SML_GENDA                 1L

/*-----------------------
    triggers
  -----------------------*/
#ifdef XXX

#define  G2_TRIGGER_MSG_PROC       "DB-TRIGGER-EVENT"
#define  MAX_TRIGGERS              51L  /* (1->51 = 50) */

/* triggers are not necessarily context sensitive */
// MOVED to GDB_COMMON.h
typedef struct {
  long     count ;
  long     timeLastChecked ;
  long     checkInterval ;
  char    *names[MAX_TRIGGERS]; /* /// /??????? check me  */
  gsi_int  obj_handle[MAX_TRIGGERS] ;
  gsi_int  context[MAX_TRIGGERS] ;
} trig_struct ;
#endif

/*-----------------------
    info constants
  -----------------------*/

#define  INFO_NUM_CURSORS          30L

#define  GDB_CATEGORY               1L
#define  GDB_TYPE                   2L

#define  GDB_UNKNOWN_TYPE           0L
#define  GDB_SIMPLE_TYPE            1L
#define  GDB_COMPOUND_TYPE          2L
#define  GDB_LIST_OR_ARRAY_TYPE     3L
#define  GDB_PARAM_OR_VAR_TYPE      5L
#define  GDB_USER_TYPE              9L

/*-----------------------
    GSI utils
  -----------------------*/

#define  MAX_GSI_TYPES             51L
#define  MAX_GSI_TYPE_LEN          20L
#define  MAX_GSI_CLASS_LEN        256L

  static GDB_CHAR GSI_TYPES[MAX_GSI_TYPES][MAX_GSI_TYPE_LEN] =
  {
    /* 0*/_T("OBJECT"),
    /* 1*/_T("INT"), _T(""),
    /* 3*/_T("SYM"),
    /* 4*/_T("STR"),
    /* 5*/_T("LOG"),
    /* 6*/_T("FLOAT"),
    /* 7*/_T("ITEM"),
    /* 8*/_T("VALUE"),
    /* 9*/_T("HANDLE"),
    /*10*/_T("QUANTITY"),_T(""), _T(""), _T(""), _T(""), _T(""), _T(""),
    /*17*/_T("INT-ARRAY"), _T(""),
    /*19*/_T("SYM-ARRAY"),
    /*20*/_T("STR-ARRAY"),
    /*21*/_T("LOG-ARRAY"),
    /*22*/_T("FLOAT-ARRAY"),
    /*23*/_T("ITEM-ARRAY"),
    /*24*/_T("VALUE-ARRAY"),
    /*25*/_T("ITEM-OR-VALUE-ARRAY"),
    /*26*/_T("QUANTITY-ARRAY"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""),
    /*33*/_T("INT-LIST"), _T(""),
    /*35*/_T("SYM-LIST"),
    /*36*/_T("STR-LIST"),
    /*37*/_T("LOG-LIST"),
    /*38*/_T("FLOAT-LIST"),
    /*39*/_T("ITEM-LIST"),
    /*40*/_T("VALUE-LIST"),
    /*41*/_T("ITEM-OR-VALUE-LIST"),
    /*42*/_T("QUANTITY_LIST"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""),
    /*49*/_T("SEQUENCE"),
    /*50*/_T("STRUCTURE")
  } ;

extern long gdb_shutdown_on_disconnect ;

/*-----------------------
    prototypes
  -----------------------*/

static long     update_object_status(void *obj_ptr, GENDA *genda_ptr, long action, long shift);
static long     return_event_msg(GENDA *genda_ptr) ;
static long     clear_g2_obj_status(void *item_ptr) ;
static long     return_rpc_status(gsi_item *sargs, long num_sargs, GENDA *genda_ptr, gsi_int call_index) ;
static void     get_item_values (gsi_attr *attrib) ;


/* RPC's */
static void     log_file_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     configuration_rp(gsi_item *arguments, gsi_int count, gsi_int call_index) ;
static void     connect_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     disconnect_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     set_cursor_rp (gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     refresh_cursor_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     sql_function_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     commit_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     rollback_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     kill_bridge_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     exec_stored_proc_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     exec_stored_proc_return_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     ping_db_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;

static void     exec_sql_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     exec_sql_obj_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     exec_immediate_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;

static void     set_trigger_rp(gsi_item *arg, gsi_int count, gsi_int call_index);
static void     get_triggers_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     disable_all_triggers_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;

extern void     check_triggers();  /* needs to be accessible from gdb_main.c */

static void     fetch_records_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;

static void     fetch_query_item_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     update_query_item_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;

static void     fetch_object_update_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     fetch_object_copy_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     fetch_object_list_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;

static void     fetch_structure_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;

/* Utility Functions */
static void     information_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     redirect_callback_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
extern void     poll_check() ;


/* Internal & Development Functions */
static void     get_attrib_info(gsi_item  *object) ;
static void     get_qv_info(gsi_item seq1, gsi_item seq2) ;
static short*   build_qv_list(gsi_attr *attribs,gsi_int nattrs,gsi_item seq1,gsi_item seq2) ;
static long*    build_receptacle_type_list(GENDA* genda_ptr, gsi_item arg3, gsi_item arg4) ;
static GDB_CHAR* column_type_name(long col_num, GENDA* genda_ptr, gsi_item names_item,
                                    gsi_item attr_types_item) ;
static GENDA    *storage_area(long action, gsi_int the_context, long handle, GENDA *genda_ptr) ;
static long     gdb_index(gsi_int the_context, gsi_int gsi_handle, long release) ;

static void     reconfigure_rp(gsi_item *arg, gsi_int count, gsi_int call_index);
static void     break_connect_rp(gsi_item *arg, gsi_int count, gsi_int call_index) ;
static void     disconnect_one_rp(gsi_item *arg, gsi_int count, gsi_int call_index);
static void     dump_bridge_info_rp(gsi_item *arg, gsi_int count, gsi_int call_index);
static void     object_dump(void *theItem) ;

static GDB_CHAR  *gsi_type_to_string (gsi_item *theItem) ;
static long     type_of_item(gsi_item *theItem, long action) ;
static long     compare_kb_ver (long nver);
#endif
