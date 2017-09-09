/*******************************************************************************

File name:               icp.h
Owner:                   Peter Fandel

Purpose:                 This include file serves to define the various
                         structure types and contants required by ICP extension
                         applications.

This file depends on:    Nothing.

Dependent files:         All foreign function, GSI and GSPAN modules and their
                         end-user applications.

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

History:                 18feb93  PAF  Created
                         20may94  PAF  The prefix 'gsi_' was added to those API 
                                       functions which didn't already have it.
                                       Macros were added for back compatibility.
                                       Fixed definition of timed_attr_type.
                         01feb95  PAF  Simplified version numbering system.
			 23mar95  PAF  Added new slots for name and class to
			               obj_def_type.
			 03jan96  GAP 
			 	  NCC  Added ANSI function signatures.

*******************************************************************************/

typedef long    icp_int;

typedef icp_int ffe_int;
typedef icp_int gsi_int;
typedef icp_int gspan_int;

/* These declarations are used for optional version control.
-------------------------------------------------------------*/
#define ICP_INCLUDE_MAJ_VER_NUM        3L
#define ICP_INCLUDE_MIN_VER_NUM        2L

extern icp_int icp_include_file_major_version;
extern icp_int icp_include_file_minor_version;

#define NULL_TAG 		 0L
#define INTEGER_TAG	      0x01L
#define SYMBOL_TAG	      0x03L
#define STRING_TAG	      0x04L
#define LOGICAL_TAG           0x05L
#define FLOAT64_TAG           0x06L
#define ITEM_TAG              0x08L
#define MAX_TYPE_TAG          0x08L

#define NO_ERR                   0L
#define MAX_ATTR_NAME_SIZE     256L

#define ICP_TRUE              1000L
#define ICP_FALSE            -1000L

#define MAX_G2_INTEGER   536870911L
#define MIN_G2_INTEGER  -536870912L

#define VOID_INDEX              -1L

#define ICP_PORT_NUM         22041L

#define UNDEFINED_CONTEXT   0xFFFFFFFFL
#ifdef MSDOS
#    define MAX_CONTEXTS        10L
#else
#    define MAX_CONTEXTS        50L
#endif

#ifndef TRUE
#define TRUE 1L
#endif

#ifndef FALSE
#define FALSE 0L
#endif

/* These symbols specify the parameters of the interruptable 
   sleep mechanism (only available on UNIX).
------------------------------------------------------------*/
#define INTERUPTABLE_INTERVAL  1000 /* Max millisecs to sleep when interruptable */
#define POLLING_INTERVAL         40 /* Max millisecs to sleep when polling */

typedef union {
    icp_int     null;
    icp_int     integer_p;
    icp_int     logical_p;
    double      float_p;
    char       *symbol_p;
    char       *string_p;
} icp_value_union;

typedef struct ovt {
    icp_int           p_type;
    icp_value_union   p_value;
    icp_int           count;
} obj_value_type;

typedef struct owit {
    icp_int         obj_index;
} obj_with_index_type;

typedef struct {
    icp_int         obj_index;
    icp_int         type;       /* type is for gensym internal use only */
    char           *name;
    char           *class;
    obj_value_type  param_1;
    obj_value_type  param_2;
    obj_value_type  param_3;
    obj_value_type  param_4;
    obj_value_type  param_5;
    obj_value_type  param_6;
    icp_int         interval;
    obj_value_type  value;
} obj_def_type;

typedef struct {
    obj_def_type *obj_ptr;
    union {
        icp_int  user_long;
        void    *user_ptr;
    } user_def;
    icp_int  tag;
} corr_obj_type;

typedef struct {
    icp_int        obj_index;
    icp_int        error_cd;
    icp_int        interval;
    obj_value_type value;
} obj_type;

typedef struct {
    icp_int year;
    icp_int month;
    icp_int day;
    icp_int hour;
    icp_int minute;
    icp_int second;
} icp_timestamp_type;

typedef struct at {
    char           attribute[MAX_ATTR_NAME_SIZE];
    obj_value_type value;
} attr_type;

typedef struct {
    char               attribute[MAX_ATTR_NAME_SIZE];
    obj_value_type     value;
    unsigned char      is_timed;
    icp_timestamp_type date;
} timed_attr_type;

typedef struct {
    icp_int             obj_index;
    icp_int             error_cd;
    icp_int             interval;
    obj_value_type      value;
    icp_timestamp_type  date;
} timed_obj_type;

/* Macros used to reference ICP option switches
------------------------------------------------*/
#define icp_set_option(A) (icp_options = icp_options | A)
#define icp_reset_option(A) (icp_options = icp_options & (~A))
#define icp_option_is_set(A) (icp_options & A)

/* ICP option switch values
--------------------------------------------------*/
#define   ICP_STRING_CHECK            0x00000001L
#define   ICP_ONE_CYCLE               0x00000002L
#define   ICP_NON_C                   0x00000020L
#define   ICP_SUPPRESS_OUTPUT         0x00000080L
#define   ICP_USE_GFLOATS             0x00000100L
#define   ICP_FREE_OBJ_PTRS           0x00000200L
#define   ICP_TRAP_NETWORK_ERRORS     0x00000400L
#define   ICP_IGNORE_USER_RPC_ERRORS  0x00000800L
#define   ICP_USE_OLD_SLEEP           0x00001000L
#define   ICP_INSTRUMENTATION         0x00002000L

/* The following ICP option switches are no longer used
but are included such that old bridges will still compile.
-----------------------------------------------------------*/
#define   ICP_FORK_GSI        0x80000000L
#define   ICP_USE_RPCS        0x80000000L
#define   ICP_RPC_ARRARGS     0x80000000L
#define   ICP_USE_ADA         0x00000020L
#define   ICP_VAX_GFLOATS     0x00000100L


/* Miscellaneous macros
-------------------------*/
#ifndef max
#define max(A, B) ((A) > (B) ? (A) : (B))
#endif

#ifndef min
#define min(A, B) ((A) > (B) ? (B) : (A))
#endif


/* Most of the following typedefs and defines support
the old naming conventions for the data structures defined 
above.  Some provide aliases for multi-purpose structures
------------------------------------------------------------*/
typedef obj_def_type        USER_ARG_TYPE;
typedef obj_def_type       *obj_def_ptr_type;
typedef obj_value_type      ICP_PARAM;
typedef obj_value_type      array_value_type;
typedef icp_value_union     ICP_VALUE;
typedef obj_type            TEMP_ARG_TYPE;
typedef obj_value_type      TEMP_PARAM;
typedef obj_value_type      attr_value_type;
typedef obj_value_type      rpc_arg_type;
typedef icp_value_union     TEMP_VALUE;
typedef timed_obj_type      TIME_ARG_TYPE;
typedef attr_type           VECTOR_TYPE;
typedef timed_attr_type     T_VECTOR_TYPE;
typedef icp_timestamp_type  TIMESTAMP;

/* OD_or_O_or_TO_type is (obj_def_type or obj_type or timed_obj_type) */
typedef obj_with_index_type OD_or_O_or_TO_type;
/* O_or_TO_type is (obj_type or timed_obj_type) */
typedef obj_type            O_or_TO_type;
/* A_or_TA_type is (attr_type or timed_attr_type) */
typedef attr_type           A_or_TA_type;
/* OV_or_AV_or_RA_type is (obj_value_type or attr_value_type or rpc_arg_type) */
typedef obj_value_type      OV_or_AV_or_RA_type;

typedef void               *user_def_type;
typedef void               *user_ptr_type;
typedef icp_int	            obj_index_type,
			    tag_type,
			    status_type,
			    interval_type;
typedef icp_int		    G2int_type,
			    G2log_type;
typedef double		    G2flt_type;
typedef char		    G2sym_type,
			    attr_name_type;
typedef char		    G2str_type;
typedef unsigned char	    boolean;


#if !defined(__GENSYMKR__) && defined(__STDC__)			/* ANSI C function signatures: */
#define GSI_PROTO(args) args
#else
#define GSI_PROTO(args) ()
#endif

/*
 * GSI Callback Functions
 */
extern gsi_int		gsi_def_obj GSI_PROTO(( obj_def_type *obj_ptr, obj_def_type *unused ));
extern gsi_int		gsi_g2_poll GSI_PROTO(( void ));
extern gsi_int		gsi_get_data GSI_PROTO(( obj_type *objects, gsi_int count ));
extern gsi_int		gsi_get_tcp_port GSI_PROTO(( void ));
extern gsi_int		gsi_initialize_context GSI_PROTO(( char *str, gsi_int str_len ));
extern gsi_int		gsi_pause_context GSI_PROTO(( void ));
extern gsi_int		gsi_resume_context GSI_PROTO(( void ));
extern gsi_int		gsi_send_message GSI_PROTO(( char *txt_str, gsi_int str_cnt, gsi_int obj_index ));
extern gsi_int		gsi_set_data GSI_PROTO(( obj_type *objects, gsi_int count ));
extern gsi_int		gsi_shutdown_context GSI_PROTO(( void ));
extern gsi_int		gsi_stop_data GSI_PROTO(( obj_type *objects, gsi_int count ));

/*
 * Superseeded Callback Functions
 */
extern gsi_int		allow_ext_proc GSI_PROTO(( void ));
extern gsi_int		InitUsrRpcs GSI_PROTO(( void ));

/* The following function prototypes declare the GSI data structure
   access functions so that compilers know the types of their return
   values.
------------------------------------------------------------------*/
extern obj_def_type       *gsi_def_of GSI_PROTO(( gsi_int index, gsi_int context ));
extern user_ptr_type       gsi_user_ptr_of GSI_PROTO(( gsi_int index, gsi_int context ));
extern icp_int             gsi_user_int_of GSI_PROTO(( gsi_int index, gsi_int context ));
extern obj_value_type     *gsi_def_attr1_of GSI_PROTO(( obj_def_type *obj ));
extern obj_value_type     *gsi_def_attr2_of GSI_PROTO(( obj_def_type *obj ));
extern obj_value_type     *gsi_def_attr3_of GSI_PROTO(( obj_def_type *obj ));
extern obj_value_type     *gsi_def_attr4_of GSI_PROTO(( obj_def_type *obj ));
extern obj_value_type     *gsi_def_attr5_of GSI_PROTO(( obj_def_type *obj ));
extern obj_value_type     *gsi_def_attr6_of GSI_PROTO(( obj_def_type *obj ));
extern obj_value_type     *gsi_obj_of GSI_PROTO(( obj_def_type *obj )) ;
extern obj_value_type     *gsi_value_of GSI_PROTO(( O_or_TO_type *obj ));
extern attr_value_type    *gsi_attr_of GSI_PROTO(( A_or_TA_type *atype ));
extern icp_timestamp_type *gsi_time_of GSI_PROTO(( timed_obj_type *obj ));
extern icp_timestamp_type *gsi_attr_time_of GSI_PROTO(( timed_attr_type *obj ));
extern char               *gsi_attr_name_of GSI_PROTO(( attr_type *obj ));
extern unsigned char       gsi_is_timed GSI_PROTO(( timed_attr_type *obj ));
extern icp_int             gsi_obj_index_of GSI_PROTO(( OD_or_O_or_TO_type *obj ));
extern void                gsi_set_obj_index GSI_PROTO(( OD_or_O_or_TO_type *obj, gsi_int index ));
extern icp_int             gsi_status_of GSI_PROTO(( obj_type *obj ));
extern icp_int             gsi_interval_of GSI_PROTO(( obj_def_type *obj ));
extern icp_int             gsi_type_of GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct ));
extern icp_int             gsi_int_of GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct ));
extern icp_int             gsi_log_of GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct ));
extern double              gsi_flt_of GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct ));
extern char               *gsi_sym_of GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct ));
extern char               *gsi_str_of GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct ));
extern void                gsi_set_user_ptr GSI_PROTO(( gsi_int index, user_ptr_type value, gsi_int context ));
extern void                gsi_set_user_int GSI_PROTO(( gsi_int index, icp_int value, gsi_int context ));
extern void                gsi_set_value GSI_PROTO(( O_or_TO_type *obj, obj_value_type *val ));
extern void                gsi_set_attr GSI_PROTO(( A_or_TA_type *atype, attr_value_type *val ));
extern void                gsi_set_status GSI_PROTO(( obj_type *gsi_struct, gsi_int status ));
extern void                gsi_set_attr_name GSI_PROTO(( attr_type *gsi_struct, char *aname ));
extern void                gsi_set_time GSI_PROTO(( timed_obj_type *obj, icp_timestamp_type *time ));
extern void                gsi_set_attr_time GSI_PROTO(( timed_attr_type *obj, icp_timestamp_type *time ));
extern void                gsi_set_is_timed GSI_PROTO(( timed_attr_type *gsi_struct, unsigned char time ));
extern void                gsi_set_type GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct, icp_int type ));
extern void                gsi_set_int GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct, gsi_int val ));
extern void                gsi_set_log GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct, gsi_int val ));
extern void                gsi_set_flt GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct, double val ));
extern void                gsi_set_sym GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct, char *str ));
extern void                gsi_set_str GSI_PROTO(( OV_or_AV_or_RA_type *gsi_struct, char *sym ));
extern char		  *gsi_name_of GSI_PROTO(( obj_def_type *variable ));
extern char		  *gsi_class_of GSI_PROTO(( obj_def_type *variable ));

/*
 * Function prototypes for GSI Functions
 */
extern boolean              gsi_context_received_data GSI_PROTO(( gsi_int context ));
extern void		    gsi_flush GSI_PROTO(( void ));
extern gsi_int		    gsi_flush_context GSI_PROTO(( gsi_int context ));
extern gsi_int		    gsi_kill_context GSI_PROTO(( gsi_int context ));
extern void		    gsi_pause GSI_PROTO(( void ));
extern gsi_int		    gsi_return_attributes GSI_PROTO(( obj_type *object_ptr, attr_type *vec_list, gsi_int count, gsi_int context ));
extern gsi_int		    gsi_return_message GSI_PROTO(( char *message, gsi_int context ));
extern gsi_int		    gsi_return_timed_attributes GSI_PROTO(( timed_obj_type *object_ptr, timed_attr_type *vec_list, gsi_int count, gsi_int context ));
extern gsi_int		    gsi_return_timed_values GSI_PROTO(( timed_obj_type *obj_list, gsi_int count, gsi_int context ));
extern gsi_int		    gsi_return_values GSI_PROTO(( obj_type *arg_list, gsi_int count, gsi_int context ));
extern gsi_int		    gsi_rpc_call GSI_PROTO(( gsi_int handle, rpc_arg_type *arguments, gsi_int context ));
extern gsi_int		    gsi_rpc_declare_local GSI_PROTO(( gsi_int (*func_ptr)GSI_PROTO(( rpc_arg_type *arg_ptr, gsi_int arg_cnt, gsi_int call_index )), char *name ));
extern gsi_int		    gsi_rpc_declare_remote GSI_PROTO(( char *name, gsi_int (*recvr_ptr)GSI_PROTO(( rpc_arg_type *val_ptr, gsi_int count)), gsi_int arg_count,  gsi_int ret_arg_count, gsi_int *handle_ptr, gsi_int context ));
extern gsi_int		    gsi_rpc_return_values GSI_PROTO(( rpc_arg_type *arguments, gsi_int count, gsi_int call_index, gsi_int context ));
extern gsi_int		    gsi_rpc_start GSI_PROTO(( gsi_int handle, rpc_arg_type *arguments, gsi_int context ));
extern gsi_int		    gsi_run_loop GSI_PROTO(( void ));
extern gsi_int		    gsi_start GSI_PROTO(( int argc, char *argv[] ));
extern void		    gsi_unwatch_fd GSI_PROTO(( gsi_int file_descriptor ));
extern void		    gsi_watch_fd GSI_PROTO(( gsi_int file_descriptor ));
extern gsi_int		    gsi_watchdog GSI_PROTO(( void (*func)GSI_PROTO(( void )), gsi_int period ));

#define gsi_class_name_of(x) gsi_class_of(x)

/* The following defines allow you to use the
old names for certain variables and functions.
-----------------------------------------------*/
#define CurrentContext                 icp_current_context
#define current_context                icp_current_context
#define flush_point                    icp_flush_point
#define DO_EXT_PROC                    do_ext_proc
#define SetIcpMode(x)                 (icp_options = icp_options | x)
#define ResetIcpMode(x)               (icp_options = icp_options & (~x))
#define TestIcpMode(x)                (icp_options & x)
#define ENABLE_EXT_PROC()             *do_ext_proc = TRUE
#define CORR_OBJ_TYPE                  corr_obj_type
#define str_ptr_of(x)                  gsi_str_of(x)
#define sym_ptr_of(x)                  gsi_sym_of(x)
#define gsi_user_def_of(x,y)           gsi_user_ptr_of(x,y)
#define gsi_set_user_def(x,y,z)        gsi_set_user_ptr(x,y,z)

/* The following defines allow shorter (without 'gsi_' prefix) names
for access functions to be used.  Prefixes were added to protect 
against name collisions when linking with third party products.
--------------------------------------------------------------------*/
#define type_of(x)          gsi_type_of(x)
#define name_of(x)          gsi_name_of(x)
#define class_of(x)         gsi_class_of(x)
#define length_of(x)        gsi_length_of(x)
#define set_type(x,y)       gsi_set_type(x,y)
#define int_of(x)           gsi_int_of(x)
#define log_of(x)           gsi_log_of(x)
#define flt_of(x)           gsi_flt_of(x)
#define sym_of(x)           gsi_sym_of(x)
#define str_of(x)           gsi_str_of(x)
#define set_int(x,y)        gsi_set_int(x,y)
#define set_log(x,y)        gsi_set_log(x,y)
#define set_flt(x,y)        gsi_set_flt(x,y)
#define set_sym(x,y)        gsi_set_sym(x,y)
#define set_str(x,y)        gsi_set_str(x,y)
#define obj_index_of(x)     gsi_obj_index_of(x)
#define set_obj_index(x,y)  gsi_set_obj_index(x,y)
#define status_of(x)        gsi_status_of(x)
#define set_status(x,y)     gsi_set_status(x,y)
#define interval_of(x)      gsi_interval_of(x)
#define set_interval(x,y)   gsi_set_interval(x,y)
#define def_attr1_of(x)     gsi_def_attr1_of(x)
#define def_attr2_of(x)     gsi_def_attr2_of(x)
#define def_attr3_of(x)     gsi_def_attr3_of(x)
#define def_attr4_of(x)     gsi_def_attr4_of(x)
#define def_attr5_of(x)     gsi_def_attr5_of(x)
#define def_attr6_of(x)     gsi_def_attr6_of(x)
#define obj_of(x)           gsi_obj_of(x)
#define value_of(x)         gsi_value_of(x)
#define set_value(x,y)      gsi_set_value(x,y)
#define attr_of(x)          gsi_attr_of(x)
#define set_attr(x,y)       gsi_set_attr(x,y)
#define attr_name_of(x)     gsi_attr_name_of(x)
#define set_attr_name(x,y)  gsi_set_attr_name(x,y)
#define time_of(x)          gsi_time_of(x)
#define set_time(x,y)       gsi_set_time(x,y)
#define attr_time_of(x)     gsi_attr_time_of(x)
#define set_attr_time(x,y)  gsi_set_attr_time(x,y)
#define set_is_timed(x,y)   gsi_set_is_timed(x,y)
#define def_of(x,z)         gsi_def_of(x,z)
#define user_def_of(x,z)    gsi_user_ptr_of(x,z)
#define user_ptr_of(x,z)    gsi_user_ptr_of(x,z)
#define user_int_of(x,z)    gsi_user_int_of(x,z)
#define set_user_def(x,y,z) gsi_set_user_ptr(x,y,z)
#define set_user_ptr(x,y,z) gsi_set_user_ptr(x,y,z)
#define set_user_int(x,y,z) gsi_set_user_int(x,y,z)

/* These defines only are active for user code.
-----------------------------------------------*/
#ifndef EXTERNS_DEFINED
    extern corr_obj_type *GSI_OBJ_PTRS;
    extern icp_int       *do_ext_proc;
    extern icp_int        icp_current_context;
    extern icp_int        icp_options;
    extern icp_int        icp_flush_point;
    extern icp_int        icp_max_export_objs;
    extern icp_int        icp_max_import_objs;
    extern icp_int        last_extension_error;
#endif
