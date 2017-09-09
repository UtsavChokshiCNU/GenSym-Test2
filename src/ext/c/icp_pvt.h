/*******************************************************************************

File name:               icp_pvt.h
Owner:                   Peter Fandel

Purpose:                 This include file has defines and typedefs and globals
                         required by all extensions.

This file depends on:    Nothing.

Dependent files:         extensn.c, icp.c, gsi.c, gspan.c, foreign.c, rpc.c

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

History:                 16oct92  PAF  Cleaned out & Rewritten.


*******************************************************************************/

/* These declarations are used for optional version control.
-------------------------------------------------------------*/
#define ALPHA        "Alpha "
#define BETA         "Beta "
#define UNQUALIFIED  ""

#define ICP_MAJ_VER_NUM         3L
#define ICP_MIN_VER_NUM         2L
#define ICP_RELEASE_QUALIFIER   UNQUALIFIED  /* Must be ALPHA, BETA, or UNQUALIFIED. */
#define ICP_DELTA_REV_NUM       1L   /* Revs reflect bug fixes */

extern icp_int gensym_include_files_match;

/* The type definition for 'icp_byte' should always come out to an unsigned
   sixteen bit integer and thus may depend on the compiler and platform.
---------------------------------------------------------------------------*/
typedef unsigned short icp_byte;

#define ICP_SUCCESS       1L
#define ICP_FAILURE       0L

typedef struct {
    gsi_int obj_index;
    gsi_int type;
    gsi_int symbol_index;
    gsi_int rp_def_index;
    gsi_int call_index;
    gsi_int arg_count;
    gsi_int ret_count;
} rp_def_obj;

typedef struct {
    char         name[MAX_ATTR_NAME_SIZE];
    gsi_int    (*return_function)();
    rp_def_obj  *rp_def_ptr;
} remote_proc;

typedef struct {
    gsi_int    status;
    rp_def_obj rp_definition;
} rp_def_struct;

typedef struct {
  gsi_int         number;           /* Number of context.                   */
  gsi_int         state;            /* ACTIVE, INACTIVE, or RE_USE.         */
  gsi_int         socket;           /* Network socket used by this context. */
  gsi_int         partner_type;     /* CLIENT, G2_SERVER, or GSI_SERVER.    */
  gsi_int         server_status;    /* NONE, PAUSED, RUNNING, or RESET.     */
  gsi_int         loaded;           /* TRUE if write_buff is loaded.        */
  time_t          last_probe_time;  /* Time of last nop message to partner. */
  time_t          last_poll_time;   /* Time of last poll to partner.        */
  icp_byte       *read_buff;        /* Buffer into which ICP messages come. */
  icp_byte       *write_buff;       /* Buffer out of which ICP messages go. */
  obj_type       *object_buff;      /* Used for get/set/stop data calls.    */
  corr_obj_type  *export_tbl;       /* Pointed to by GSI_OBJ_PTRS.          */
  corr_obj_type  *import_tbl;       /* Used exclusively for RPCs.           */
  remote_proc    *remote_proc_tbl;  /* Remote procedures locally callable.  */
  rp_def_struct  *rp_def_tbl;       /* Definitions assoc. with remote procs.*/
  rpc_arg_type   *rpc_ret_buff;     /* Used to return args from G2 procs.   */
  gsi_int         read_index;       /* Index into read_buff.                */
  gsi_int         write_index;      /* Index into write_buff.               */
  gsi_int         object_index;     /* Index into object_buff.              */
  gsi_int         export_count;     /* Number of objects in export_tbl.     */
  gsi_int         import_count;     /* Number of objects in import_tbl.     */
  gsi_int         export_tbl_size;  /* Size of export_tbl.                  */
  gsi_int         import_tbl_size;  /* Size of import_tbl.                  */
  gsi_int         max_export_used;  /* Highest export table obj index used. */
  gsi_int         max_import_used;  /* Highest import table obj index used. */
  gsi_int         bytes_read;       /* Bytes "pre-read" in read_buff.       */
  gsi_int         do_ext_proc;      /* If TRUE, allow_ext_proc() is called. */
  boolean         received_data;    /* If TRUE data was recvd last run loop.*/
  /*  added as of 11 Sep 1995  by ncc.  */
  gsi_int	  peer_major_version; /* major version of peer.  Initialized to -1. */
  gsi_int         peer_minor_version; /* minor version of peer.  Initialized to -1. */
} ctx_struct;

typedef struct {
    gsi_int  obj_index;
    gsi_int  type;
    char    *symbol;
} symb_struct;

#define NETWORK_FAIL   -1L  /* Used as a return value from the network layer. */
#define BAD_READ       -1L
#define BAD_WRITE      -1L
#define INVALID_SOCKET -1L

#define ACTIVE    1L
#define INACTIVE  2L
#define RE_USE    3L

#define NO_DATA   9999999L
#define SEND      1L
#define NO_SEND   0L


/* The following defines are used to indicate the type of an object
hanging off of a corresponding object or import object table.
----------------------------------------------------------------*/
#define ICP_OBJ_DEF     1L /* An obj_def_type structure (export_tbl only). */
#define ICP_SYMBOL      2L /* A symbol structure */
#define ICP_LOCAL_FUNC  3L /* A local function structure (export_tbl only). */
#define ICP_REMOTE_PROC 3L /* A remote procedure structure (import_tbl only). */
#define ICP_CALL        4L /* A call structure */


#ifdef MSDOS
#    define BUFFER_SIZE          4096L
#    define INITIAL_MAX_OBJECTS   250L
#    define MAX_REMOTE_PROCS       30L
#else
#    define BUFFER_SIZE         32768L
#    define INITIAL_MAX_OBJECTS  2000L
#    define MAX_REMOTE_PROCS      100L
#endif
#define INITIAL_FLUSH_POINT 512L  /* Default setting for write buffer flush. */

#define MAX_ICP_US_INT  63000L  /* Maximum unsigned short value in ICP. */
#define MIN_ICP_INT    -31500L  /* Minumum signed integer in one ICP byte. */
#define MAX_ICP_INT     31500L  /* Maximum signed integer in one ICP byte. */
#define MAX_ICP_INT_LEN   500L  /* Max number of ICP bytes to make integer. */
#define ICP_BYTE_SIZE       2L  /* Number of 8-bit bytes in an ICP byte. */
#define ICP_MSG_OFFSET  64000L  /* Offset added to ICP message IDs.  */
#define END_OF_GROUP        1L  /* Marks end of an ICP message group. */
#define ICP_ARRAY_SIZE    320L  /* No. of pointers to ICP message receivers. */
#define INIT_MSG_INDX       1L
#define MIN_IMPORT_INDEX    1L  /* Min valid import table index for RP def.  */
#define MAX_NO_ARGS       200L
#define MAX_LOCAL_FUNCS   100L  /* Max number of local functions to export. */
#define OBJ_BUFF_LEN       50L  /* Max objects in set/get/stop data calls. */
#define NUM_TIME_ARGS       6L  /* The numbers of parts in a timestamp. */
#define EXTERNAL_SYSTEM_OK  2L  /* This may later be a variable. */
#define PROBE_FREQUENCY    20L  /* Probe every connected process every 20 sec */
#define POLL_FREQUENCY      1L  /* Poll any connected G2 servers every second */
#define NULL_PTR            0L  /* I dont love you since you ate my dog. */
#define NULL_CHAR         '\0'  /* Used to null terminate C strings. */
#define NO_OF_MSGS         50L  /* Number of messages in message table. */
#define SLEEP_TIME         20L  /* Value passed to g2ext_sys_sleep(). */
#define MAX_WRITE_SIZE    512L  /* Max amount of bytes I can pass in a call to
                                   g2ext_network_write(). */
#define MAX_VAX_NAME_SIZE  32L  /* Used in debugging GSI. */
#define MAX_SYMBOL_SIZE   256L  /* Used when a symbol is interned over ICP */
#define ICP_USER_MSG_SIZE  75L  /* Max size of message in the message table. */
#define ICP_USER_MSG_PART_SIZE 128L  /* Max size of one "line" of an ICP user
                                                                     message. */
#define TOTAL_ICP_MSG_SIZE     256L  /* Max size of entire ICP message. */

#define integer_is_out_of_range(int_x)  ((int_x > MAX_G2_INTEGER) ||  \
                                         (int_x < MIN_G2_INTEGER))
#define logical_is_out_of_range(log_x)  ((log_x > ICP_TRUE) ||  \
                                         (log_x < ICP_FALSE))


#define INDEX_SPACE_NAME       "STANDARD-ICP-OBJECT-INDEX-SPACE"
#define UNDEFINED               -1L
#define INTERNAL_DEFAULT_PORT   22041L
#define INTERNAL_DEFAULT_NAME  "GSI0"

typedef char icp_user_msg[ICP_USER_MSG_SIZE];

/* The following defines are for the errors that can occur within GSI.
----------------------------------------------------------------------*/
#define INTERNAL_INCONSISTENCY     1L
#define INTERNAL_WARNING           2L
#define ICP_OUT_OF_SYNCH           3L
#define ICP_READ_ERROR             4L
#define ICP_WRITE_ERROR            5L
#define INVALID_ICP_MESSAGE        6L
#define UNUSED_ERROR_NUMBER        7L
#define NO_MORE_MEMORY             8L
#define NO_MORE_CONTEXTS           9L
#define CONTEXT_UNDEFINED         10L
#define CONTEXT_INVALID           11L
#define NO_MORE_IMPORTS           12L
#define NO_MORE_REMOTE_PROCS      13L
#define NO_MORE_LOCAL_FUNCTIONS   14L
#define INVALID_INDEX             15L
#define INVALID_TYPE_TAG          16L
#define ARG_COUNT_INCONSISTENCY   17L
#define INVALID_CALL_INDEX        18L
#define FUNCTION_NAME_TOO_LONG    19L
#define FUNCTION_UNDEFINED        20L
#define RET_FUNCTION_UNDEFINED    21L
#define RPC_ERROR1                22L
#define RPC_ERROR2                23L
#define CANT_MAKE_CONNECTION      24L
#define GET_SOCKET_FAILED         25L
#define CLOSE_SOCKET_FAILED       26L
#define TOO_MANY_NETWORKS         27L
#define TOO_MANY_LISTENERS        28L
#define INVALID_NETWORK           29L
#define INVALID_NETWORK_COMBO     30L
#define NO_SUPPORT_ON_PC          31L
#define NETWORK_ACCEPT_FAILED     32L
#define RUN_LOOP_NESTING          33L
#define G2_INTEGER_OVERFLOW       34L
#define LOGICAL_OUT_OF_RANGE      35L
#define EXPECTED_OBJ_DEF_TYPE     36L
#define WRITE_BUFFER_FULL         37L
#define GFLOAT_API_UNSUPPORTED    38L
#define RPC_ASYNC_ABORT           39L
#define LATE_RPC_ASYNC_ABORT      40L

/* The following defines are for the ICP messages used by all extensions.
--------------------------------------------------------------------------*/
#define ENLARGE_CORR_ICP_OBJECT_SPACE   15L
#define NOP                             16L
#define WRITE_USER_MESSAGE_STRING       65L

/* The following defines are for the ICP messages used to connect to G2.
----------------------------------------------------------------------------*/
#define I_AM_ALIVE                      14L
#define INITIALIZE_G2_SERVER           120L
#define G2DS_SHUT_DOWN_SERVER          121L
#define G2_SEND_DATA_VALUES_IF_ANY     124L
#define G2DS_SERVER_STATUS             127L
#define RETURN_G2DS_VERSION            170L
#define MESSAGE_GROUP_ID               181L

/* The following defines support connectivity to G2.
------------------------------------------------------*/
#define CLIENT      1L
#define G2_SERVER   2L
#define GSI_SERVER  3L

#define FAKE_G2_MAJ_VER_NUM   4L
#define FAKE_G2_MIN_VER_NUM   0L

#define NONE      0L
#define RUNNING   1L
#define PAUSED    2L
#define RESET     3L

extern gsi_int byte_swap_temporary;
#if defined(i386) || defined(WIN32) || defined(__osf__) || defined(linux)
#  define LOW_BYTE(b) ((b>>8)&0xff)
#  define HIGH_BYTE(b) (b&0xff)
#  define BYTE_SWAP_FOR_ICP(byte) \
  (byte_swap_temporary=(byte),(gsi_int)(LOW_BYTE(byte_swap_temporary)+(HIGH_BYTE(byte_swap_temporary)<<8)))
#else
#  define BYTE_SWAP_FOR_ICP(byte) (byte)
#endif

#define rdicpbyte()  BYTE_SWAP_FOR_ICP(curr_ctx->read_buff[curr_ctx->read_index++])
#define wricpbyte(A) if (curr_ctx->write_index >= (BUFFER_SIZE - 2))            \
                      ext_error(WRITE_BUFFER_FULL,"wricpbyte",NO_DATA,NO_SEND); \
                     else                                                       \
                      curr_ctx->write_buff[curr_ctx->write_index++]=(icp_byte)BYTE_SWAP_FOR_ICP(A)

#ifdef DEFINE_GLOBALS

    gsi_int         icp_sleep_enabled = TRUE;
    gsi_int         within_run_loop_extent = FALSE;
    ctx_struct      icp_context_table[MAX_CONTEXTS];
    ctx_struct     *curr_ctx;
    gsi_int         icp_current_context = MAX_CONTEXTS;
    gsi_int         icp_allocated_contexts = 0;
    gsi_int         icp_active_contexts = 0;
    gsi_int         last_extension_error = 0;
    gsi_int         icp_flush_point = INITIAL_FLUSH_POINT;
    gsi_int         icp_options = 0;
    gsi_int        *do_ext_proc;
    gsi_int       (*icp_shutdown_function)();
    gsi_int         icp_max_export_objs = INITIAL_MAX_OBJECTS;
    gsi_int         icp_max_import_objs = INITIAL_MAX_OBJECTS;
    char            where_in_extension[MAX_VAX_NAME_SIZE + 1];
    corr_obj_type  *GSI_OBJ_PTRS;
    gsi_int         g2_server_major_version = 0;
    gsi_int         g2_server_minor_version = 0;
    gsi_int         icp_include_file_major_version = ICP_MAJ_VER_NUM;
    gsi_int         icp_include_file_minor_version = ICP_MIN_VER_NUM;

/*  The null ICP function is pointed to by default by every slot in the
    GSI function array used to call the appropriate ICP handler (receiver)
    for ICP messages.  The function is defined in gw_gsi.c.
    -----------------------------------------------------------------------*/
    extern gsi_int null_icp();
    gsi_int (*icp_func_array[ICP_ARRAY_SIZE])() = {
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64000 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64005 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64010 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64015 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64020 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64025 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64030 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64035 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64040 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64045 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64050 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64055 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64060 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64065 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64070 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64075 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64080 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64085 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64090 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64095 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64100 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64105 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64110 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64115 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64120 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64125 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64130 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64135 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64140 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64145 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64150 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64155 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64160 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64165 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64170 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64175 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64180 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64185 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64190 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64195 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64200 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64205 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64210 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64215 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64220 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64225 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64230 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64235 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64240 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64245 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64250 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64255 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64260 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64265 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64270 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64275 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64280 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64285 */
      null_icp, null_icp, null_icp, null_icp, null_icp, /* 64290 */
      null_icp, null_icp, null_icp, null_icp, null_icp  /* 64295 */
    };

    icp_user_msg icp_user_msg_tbl[NO_OF_MSGS] = {
/* 00 */ "12345678901234567890123456789012345678901234567890123456789012345678",
/* 01 */ "Internal inconsistency, please inform customer support",
/* 02 */ "Internal warning, please inform customer support",
/* 03 */ "ICP out of synch",
/* 04 */ "Network error while reading - shutting down context...",
/* 05 */ "Network error while writing - shutting down context...",
/* 06 */ "Invalid ICP message sent by other process",
/* 07 */ "Unused error.  If you get this please inform customer support.",
/* 08 */ "No more memory available on host",
/* 09 */ "No more contexts available",
/* 10 */ "Desired context is undefined",
/* 11 */ "Desired context is invalid or inactive",
/* 12 */ "No more imports available",
/* 13 */ "No more remote procedures may be declared",
/* 14 */ "No more local functions may be declared",
/* 15 */ "Invalid object index, check your user code",
/* 16 */ "Invalid type tag, check your user code",
/* 17 */ "Number of arguments received conflicts with RPC declaration",
/* 18 */ "Call index doesn't correspond to an outstanding RPC in this context",
/* 19 */ "Name of local function too long, max name length is 255 characters",
/* 20 */ "Local function undefined, check spelling in rpc_declare_local() call",
/* 21 */ "Could not find receiver function, check spelling",
/* 22 */ "Error occurred in a remote procedure - procedure never executed",
/* 23 */ "Error occurred during execution of a remote procedure",
/* 24 */ "Something went wrong attempting to establish a GSI connection",
/* 25 */ "Something went wrong attempting to get a new socket number",
/* 26 */ "Something went wrong attempting to close a socket.",
/* 27 */ "Too many network types were specified in the command line.",
/* 28 */ "Too many port numbers and/or network object names in command line.",
/* 29 */ "Invalid network protocol specified on the command line.",
/* 30 */ "You may not open two listeners with the same network protocol.",
/* 31 */ "The toolkit function you requested is not supported on PC platforms",
/* 32 */ "Something went wrong attempting to accept a new connection",
/* 33 */ "Nesting calls to gsi_run_loop() is not supported.",
/* 34 */ "G2 does not support integers with more than 30 significant bits.",
/* 35 */ "Logical values for G2 may range from -1000 (F) to 1000 (T) inclusive",
/* 36 */ "Access function expected an argument of type *obj_def_type.",
/* 37 */ "Write buffer full - break your transmission into smaller chunks.",
/* 38 */ "With Gfloats, use direct structure access instead of this API func.",
/* 39 */ "This call has been aborted by the client - no values returned.",
/* 40 */ "An RPC has been aborted by the client while return en route.",
/* 41 */ "Unused error.  If you get this please inform customer support.",
/* 42 */ "Unused error.  If you get this please inform customer support.",
/* 43 */ "Unused error.  If you get this please inform customer support.",
/* 44 */ "Unused error.  If you get this please inform customer support.",
/* 45 */ "Unused error.  If you get this please inform customer support.",
/* 46 */ "Unused error.  If you get this please inform customer support.",
/* 47 */ "Unused error.  If you get this please inform customer support.",
/* 48 */ "Unused error.  If you get this please inform customer support.",
/* 49 */ "Unused error.  If you get this please inform customer support."
    }; /* end initializing message table */

#else

    extern gsi_int        icp_sleep_enabled;
    extern gsi_int        within_run_loop_extent;
    extern ctx_struct     icp_context_table[];
    extern ctx_struct    *curr_ctx;
    extern gsi_int        icp_current_context;
    extern gsi_int        icp_allocated_contexts;
    extern gsi_int        icp_active_contexts;
    extern gsi_int        last_extension_error;
    extern gsi_int        icp_flush_point;
    extern gsi_int        icp_options;
    extern gsi_int      (*icp_func_array[])();
    extern icp_user_msg   icp_user_msg_tbl[];
    extern gsi_int       *do_ext_proc;
    extern gsi_int      (*icp_shutdown_function)();
    extern gsi_int        icp_max_export_objs;
    extern gsi_int        icp_max_import_objs;
    extern char           where_in_extension[];
    extern corr_obj_type *GSI_OBJ_PTRS;
    extern gsi_int        g2_server_major_version;
    extern gsi_int        g2_server_minor_version;
    extern gsi_int        icp_include_file_major_version;
    extern gsi_int        icp_include_file_minor_version;

#endif

extern double rd_icp_64float();

/*
 * jh, 7/8/94.  Added externs to cover "intra-ext" C functions.  These functions
 * previously returned values of type long, and were externed implicitly as int.
 * Although nothing seems to have gone wrong yet, explicit externs will
 * certainly increase our robustness.  For further details (including what
 * "intra-ext" means) see my note this date in /bt/ab/rtl/c/gensym.h.
 */
extern long g2ext_foreign_partition_float(/* double, unsigned char * */);
extern long g2ext_network_connect(/* char * */);
extern long g2ext_network_close(/* long */);
extern long g2ext_network_accept(/* void */);
extern long g2ext_get_next_connection(/* void */);
extern long g2ext_get_network_listener(/* long, char *, long */);
extern long g2ext_network_listener_count(/* void */);
extern long g2ext_network_read(/* long, char *, long */);
extern long g2ext_network_write(/* long, char *, long, long */);
