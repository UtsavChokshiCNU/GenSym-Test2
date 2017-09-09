/*================================================================
 *  GDB_CONTEXT.H  - GDB Layer-2                           [header]
 *================================================================*/

#ifndef GDB_CONTEXT_H
#define GDB_CONTEXT_H

#include "gdb_genda.h"

  typedef struct GDB_HANDLE_STRUCT {
    GDB_CHAR      context;
    long      id;
  } GDB_HANDLE_STRUCT;

  /* used to store info for a registered G2 item */
  typedef struct REGISTERED_ITEM_STRUCT {
      long   hcount;
      GENDA  **addr;
      long   *gsi_handle;  
  } REGISTERED_ITEM_STRUCT;

  typedef struct DB_CONNECT_INFO {
    GDB_CHAR     *username;
    GDB_CHAR     *password;
    GDB_CHAR     *connection;
    GDB_CHAR     *gsi_connection_str; /* add gsi-connection-string. for project 28544 Gensym-2012 */
  } DB_CONNECT_INFO;

  typedef struct CONTEXT_INFO
  {
     /* These 2 are necessary until GSI provides the ability to "kill" a
        context manually */
      long   active;              /* flag: context has been initialized - 'initialize_context'*/
      long   available;           /* flag: context has been configured - 'configuration_rp' */

      GDB_CHAR   *name;               /* name of this context */
      long   genda_rows;          /* # rows to fetch before returning data to G2 */
      long   max_cursors;         /* max # of simultaneous open cursors */
  /*  long   max_ncols;     */      /* max # of columns allowed per query */
      long   max_bind_vars;       /* max # bind variables */
      int    max_bind_name_len;   /* max bind variable value length */
      long   max_reg_items;       /* max # of registered items (object indices) per context */
      long   max_text_len ;       /* max readable length of text field */
      int    need_textsize ;      /* only set textsize if max_text_len was set */
      GDB_CHAR  *null_string;         /* return value for DB strings given indicator is NULL */
      long   null_number;         /* return value for DB numbers given indicator is NULL */
      GDB_CHAR  *set_null_string ;    /* value used to force NULL in text fields */
      long   set_null_number ;    /* value used to force NULL in numeric fields */
      char   set_null_options ;   /* whether to use set-null-number, set-null-text, & "NULL" */
      FILE  *logfile_ptr;         /* pointer to logfile */
      GDB_CHAR   *logfile_name;       /* name of logfile */
      long   logfile_filter;      /* filter arguments for logfile */
      long   logfile_active;      /* flag: logfile is active or inactive */
      long   logfile_ts;          /* flag: timestamp all logfile messages */
      long   enable_messaging;    /* flag: send status info to 'G2_EVENT_MSG_PROC' */
      long   auto_db_reconnect;   /* flag: attempt reconnect to DB if connect broken */
      long   console_output;      /* flag: display errors & warnings to console */
      long   db_reconnecting;     /* flag: attempting a DB reconnect (used to avoid recursive reconnect) */
      long   array_fetch;         /* flag: utilize DB array fetching if supported */
      long   iomsg_ts;            /* flag: timestamp all console messages */
      long   no_rpc_return;       /* flag: return the rpc 'status' values */
      long   connected_to_db;     /* flag: connected to database */
      long   auto_commit;         /* flag: enable auto-commit (ODBC support) */
      long   smart_fetch ;        /* flag: intelligent fetch of DECIMAL(x,0) values */
      long   integrated_security; /* flag: use Windows integrated security for authenticating connection */

      REGISTERED_ITEM_STRUCT reg_item;    /* replacement for CORR_OBJ_PTRS GSI global structure */
      DB_CONNECT_INFO        db_connect_info;
      STATUS_STRUCT          gbl_status;
      GDB_HANDLE_STRUCT      gdb_handle[MAX_CURSORS+1];

  } CONTEXT_INFO;



#endif
