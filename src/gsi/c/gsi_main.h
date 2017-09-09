/*****************************************************************************
:
:  gsi_main.h  --  Include file required by C files that use GSI API.
:
:  Copyright (C) 1986-2017 Gensym Corporation.
:  All rights reserved.
:  Gensym Corporation, 52 Second Avenue, Burlington, MA  01803-4411
:  http://www.gensym.com/
:
:...........................................................................*/

/*--------------------------------------------------------------------------*/
/* This file uses the following compile-time switches.                      */
/* These switches may be defined on the command line used for the compile.  */
/*    GSI_USE_WIDE_STRING_API                                               */
/*    GSI_USE_USER_DATA_FOR_CALLBACKS                                       */
/*    GSI_USE_NEW_SYMBOL_API                                                */
/*    GSI_USE_DLL (WIN32 platforms only)                                    */
/* See the macro GSI_SET_OPTIONS_FROM_COMPILE(), at the end of this file.   */
/*--------------------------------------------------------------------------*/

#ifndef GSI_DEFINED
#define GSI_DEFINED

#ifndef COMMON_CONFIG_H

#if defined(__alpha) || defined(_M_X64) || defined(__x86_64__)
	#define Platform_64bit
#endif /* Word length switch */

#if defined(_WIN32)
	#define Platform_Windows
#endif /* OS switch */

#if defined(Platform_Windows) && defined(Platform_64bit)
	typedef __int64 Gensym_Long;
	typedef unsigned __int64 Gensym_Ulong;
#else
	typedef long Gensym_Long;
	typedef unsigned long Gensym_Ulong;
#endif

#if defined(Platform_Windows)
	typedef __int64 Gensym_Long64;
	typedef unsigned __int64 Gensym_Ulong64;
#else
	typedef long long Gensym_Long64;
	typedef unsigned long long Gensym_Ulong64;
#endif

#endif /* COMMON_CONFIG_H */

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef GSI_USE_PROTOTYPES
#if !defined(__GENSYMKR__) && (defined(__STDC__) || defined(_MSC_VER))
#define GSI_USE_PROTOTYPES 1
#else
#define GSI_USE_PROTOTYPES 0
#endif
#endif

/*--------------------------------------------------------------------------*/
/*		Type definitions for the four GSI data structures           */
/*--------------------------------------------------------------------------*/
typedef void *gsi_struct;

/* These aliases are for convenience */
typedef gsi_struct gsi_item;
typedef gsi_struct gsi_rpc_arg;
typedef gsi_struct gsi_attr;
typedef gsi_struct gsi_registration;
typedef gsi_struct gsi_registered_item;
typedef gsi_registered_item *gsi_registered_item_array;

/*--------------------------------------------------------------------------*/
/*	     Definition for standard GSI integer/long type                       */
/*--------------------------------------------------------------------------*/
typedef Gensym_Long gsi_int;
typedef Gensym_Long64 gsi_long;
typedef Gensym_Ulong64 gsi_ulong;

/*--------------------------------------------------------------------------*/
/*	     Definition for standard GSI character type                     */
/*--------------------------------------------------------------------------*/
#if defined(GSI_USE_WIDE_STRING_API)
typedef unsigned short gsi_char;
#else
typedef char           gsi_char;
#endif

#if defined(GSI_USE_NEW_SYMBOL_API)
typedef void     *gsi_symbol;
#else
typedef gsi_char *gsi_symbol;
#endif


#ifdef GSI_USE_USER_DATA_FOR_CALLBACKS
typedef void   *gsi_rpc_user_data_type;
#else
typedef gsi_int gsi_rpc_user_data_type;
#endif

typedef void *gsi_context_user_data_type;
typedef void *gsi_item_user_data_type;
typedef void *gsi_symbol_user_data_type;

typedef gsi_rpc_user_data_type gsi_procedure_user_data_type;

typedef gsi_rpc_user_data_type gsi_call_identifier_type;

typedef gsi_rpc_user_data_type gsi_function_handle_type;


#define STRING_BUFFER_SIZE_FOR_BUILD_ID 5

typedef struct {
  gsi_int major_version;
  gsi_int minor_version;
  gsi_int revision_number;
  gsi_int release_quality;
  char build_id[STRING_BUFFER_SIZE_FOR_BUILD_ID];
} gsi_version_id;



/*--------------------------------------------------------------------------*/
/*			    Constants used by GSI                           */
/*--------------------------------------------------------------------------*/


#define GSI_IO_UNBLOCKED 1
#define GSI_IO_BLOCKED 0

#define GSI_ACCEPT 0
#define GSI_REJECT 1

#define GSI_UNDEFINED_CONTEXT   -1
#define GSI_VOID_INDEX	        -1
#define GSI_CALL_HANDLE_OF_START 0

#define GSI_ONE_CYCLE	                       0
#define GSI_SUPPRESS_OUTPUT                    1
#define GSI_USE_GFLOATS	                       2
#define GSI_NON_C	                       3
#define GSI_STRING_CHECK                       4
#define GSI_NO_SIGNAL_HANDLERS                 5
#define GSI_WIDE_STRING_API                    6
#define GSI_USER_DATA_FOR_CALLBACKS            7
#define GSI_NO_FLUSH                           8
#define GSI_TRACE_RUN_STATE                    9
#define GSI_NEW_SYMBOL_API                    10
#define GSI_USE_REFERENCES                    11
#define GSI_DISABLE_INTERLEAVING              12
#define GSI_TRACE_RUN_LOOP                    13
#define GSI_PROTECT_INNER_CALLS               14
#define GSI_DO_NOT_REFORMAT_MESSAGES          15
#define GSI_USER_OWNS_GSI_ITEMS               16

#define GSI_NULL_TAG		   0
#define GSI_INTEGER_TAG		   1
#define GSI_SYMBOL_TAG		   3
#define GSI_STRING_TAG		   4
#define GSI_LOGICAL_TAG		   5
#define GSI_FLOAT64_TAG		   6
#define GSI_ITEM_TAG		   7
#define GSI_VALUE_TAG		   8
#define GSI_HANDLE_TAG		   9
#define GSI_QUANTITY_TAG          10
#define GSI_UNSIGNED_SHORT_VECTOR_TAG 11

#define GSI_INTEGER_ARRAY_TAG	  17
#define GSI_SYMBOL_ARRAY_TAG	  19
#define GSI_STRING_ARRAY_TAG	  20
#define GSI_LOGICAL_ARRAY_TAG	  21
#define GSI_FLOAT64_ARRAY_TAG	  22
#define GSI_ITEM_ARRAY_TAG	  23
#define GSI_VALUE_ARRAY_TAG	  24
#define GSI_ITEM_OR_VALUE_ARRAY_TAG 25
#define GSI_QUANTITY_ARRAY_TAG    26

#define GSI_INTEGER_LIST_TAG	  33
#define GSI_SYMBOL_LIST_TAG	  35
#define GSI_STRING_LIST_TAG	  36
#define GSI_LOGICAL_LIST_TAG	  37
#define GSI_FLOAT64_LIST_TAG	  38
#define GSI_ITEM_LIST_TAG	  39
#define GSI_VALUE_LIST_TAG	  40
#define GSI_ITEM_OR_VALUE_LIST_TAG  41
#define GSI_QUANTITY_LIST_TAG     42

#define GSI_SEQUENCE_TAG	  49
#define GSI_STRUCTURE_TAG	  50
#define GSI_INT64_TAG		  51 /* old name */
#define GSI_LONG_TAG		  51

#define GSI_TRUE	   1000
#define GSI_FALSE	  -1000

#define MAX_G2_INTEGER	 536870911
#define MIN_G2_INTEGER	-536870912

#define G2_DEFAULT_MINIMUM_INTERVAL	  1000 /* milliseconds */
#define G2_MINIMUM_MINIMUM_INTERVAL	    50 /* milliseconds */

#define NO_ERR	0

#ifndef TRUE
#  define TRUE	(1)
#endif
#ifndef FALSE
#  define FALSE (0)
#endif
#ifndef NULL_PTR
#  define NULL_PTR 0
#endif
#ifndef NULL
#define NULL 0
#endif

#define GSI_INVALID_PROTOCOL			 1
#define GSI_INVALID_NETWORK_COMBO		 2
#define GSI_INVALID_TCP_PORT_NUMBER		 3
#define GSI_INVALID_DECNET_OBJECT_NAME		 4
#define GSI_INVALID_NETWORK_ADDRESS		 5
#define GSI_ITEM_DEFINITIONS_ARE_READ_ONLY	 6
#define GSI_STRUCTURE_HAS_NO_HANDLE		 7
#define GSI_STRUCTURE_HAS_NO_IDENTIFYING_ATTRS	 8
#define GSI_STRUCTURE_HAS_NO_INSTANCE		 9
#define GSI_STRUCTURE_HAS_NO_TIMESTAMP		10
#define GSI_STRUCTURE_HAS_NO_TIMED_FLAG		11
#define GSI_STRUCTURE_HAS_NO_INTERVAL		12
#define GSI_STRUCTURE_HAS_NO_STATUS		13
#define GSI_STRUCTURE_HAS_NO_ATTRIBUTE_NAME	14
#define GSI_MISSING_INSTANCE_STRUCTURE		15
#define GSI_INCOMPATIBLE_TYPE			16
#define GSI_LOCAL_FUNCTION_UNDEFINED		17
#define GSI_INVALID_CALL_HANDLE			18
#define GSI_REMOTE_DECLARATION_NOT_FOUND	19
#define GSI_INCORRECT_ARGUMENT_COUNT		20
#define GSI_UNEXPECTED_OPERATION		21
#define GSI_INTERNAL_INCONSISTENCY		22
#define GSI_BAD_MAGIC_NUMBER			23
#define GSI_INVALID_CONTEXT			24
#define GSI_ATTRIBUTE_INDEX_OUT_OF_RANGE	25
#define GSI_NO_CLASS_IN_REGISTERED_ITEM		26
#define GSI_G2_LOGICAL_OUT_OF_BOUNDS		27
#define GSI_MISSING_ATTRIBUTE_NAME		28
#define GSI_COUNT_OUT_OF_ARRAY_BOUNDS		29
#define GSI_INCOMPATIBLE_STRUCTURE		30
#define GSI_STRUCTURE_HAS_NO_CLASS_QUALIFIER	31
#define GSI_NO_CLASS_NAME_SPECIFIED		32
#define GSI_ARGUMENT_COUNT_TOO_BIG		33
#define GSI_RPC_ERROR_FROM_G2			34
#define GSI_RPC_ERROR_FROM_G2_PROCEDURE		35
#define GSI_RESERVED_ERROR_CODE			36
#define GSI_CUSTOM_USER_ERROR			37
#define GSI_CONNECTION_LOST			38
#define GSI_OWNEROUS_RECLAMATION_VIOLATION	39
#define GSI_NULL_POINTER_ARGUMENT		40
#define GSI_ITEM_HAS_NO_VALUE			41
#define GSI_NOOP_CODE_ACCESSED			42
#define GSI_ILLEGAL_NESTING_OF_RUN_LOOP		43
#define GSI_STRUCTURE_HAS_NO_HISTORY		44
#define GSI_INCOMPATIBLE_HISTORY_SPEC		45
#define GSI_INVALID_TYPE			46
#define GSI_TYPE_FOR_DATA_SERVICE		47
#define GSI_BAD_MAGIC_NUMBER_IN_QUERY		48
#define GSI_CONTEXT_UNDEFINED			49
#define GSI_INVALID_HANDLE			50
#define GSI_INVALID_HANDLE_OF_NTH		51
#define GSI_TIMESTAMP_OUT_OF_BOUNDS		52
#define GSI_INVALID_TIMESTAMP			53
#define GSI_INVALID_HANDLE_FOR_CONTEXT		54
#define GSI_NO_NAME_IN_REGISTERED_ITEM		55
#define GSI_INCOMPATIBLE_STRUCTURE2		56
#define GSI_ICP_MESSAGE_TOO_LONG		57
#define GSI_ICP_MESSAGE_OUT_OF_SYNCH_CASE_2	58
#define GSI_MAXIMUM_TEXT_STRING_LENGTH_ERROR	59
#define GSI_EXTEND_CURRENT_TEXT_STRING_ERROR    60
#define GSI_UNDEFINED_STRUCTURE_METHOD_ERROR    61
#define GSI_INDEX_SPACE_FULL_ERROR              62
#define GSI_CIRCULARITY_NOT_SUPPORTED           63
#define GSI_NO_MORE_RPC_IDENTIFIERS             64
#define GSI_BAD_RPC_STATE                       65
#define GSI_MALFORMED_SOCKET                    66
#define GSI_UNKNOWN_TYPE_TAG                    67
#define GSI_INVALID_HISTORY_TYPE                68
#define GSI_UNCAUGHT_EXCEPTION                  69
#define GSI_CANNOT_ESTABLISH_LISTENER           70
#define GSI_MAXIMUM_CONTEXTS_EXCEEDED           71
#define GSI_CONNECTION_DENIED                   72
#define GSI_UNKNOWN_STRING_CONVERSION_STYLE     73
#define GSI_ERROR_IN_CONNECT                    74
#define GSI_INVALID_RETURN_VALUE_INDEX          75
#define GSI_INVALID_RETURN_VALUE_KIND           76
#define GSI_INVALID_ATTRIBUTE_TYPE              77
#define GSI_RESUMABLE_ICP_ERROR                 78
#define GSI_UNKNOWN_CALLING_PROCEDURE_INDEX     79
#define GSI_ILLEGAL_ERROR_ARGUMENTS             80
#define GSI_INTEGER_TOO_LARGE                   81
#define GSI_INTEGER_TOO_SMALL                   82
#define GSI_NOT_A_SYMBOL                        83
#define GSI_NO_LICENSE                          84
#define GSI_CONTEXT_HAS_BEEN_KILLED             85
#define GSI_CONTEXT_HAS_BEEN_SHUT_DOWN          86
#define GSI_CALLBACK_NAME_NOT_FOUND             87
#define GSI_INVALID_OPTION_INDEX                88
#define GSI_APPLICATION_LOAD_FAILED             89
#define GSI_NETWORK_ERROR                       90

#define GSI_ATTRIBUTE_NAME_NOT_FOUND           256
#define GSI_TIMESTAMP_NOT_FOUND                257
#define GSI_RPC_ASYNC_ABORT                    258
#define GSI_RPC_LATE_ASYNC_ABORT               259

#define GSI_CHAR_SET_GENSYM               0
#define GSI_CHAR_SET_UTF_G                0
#define GSI_CHAR_SET_ISO_8859_1           1
#define GSI_CHAR_SET_LATIN_1              1
#define GSI_CHAR_SET_ISO_8859_2           2
#define GSI_CHAR_SET_LATIN_2              2
#define GSI_CHAR_SET_ISO_8859_3           3
#define GSI_CHAR_SET_LATIN_3              3
#define GSI_CHAR_SET_ISO_8859_4           4
#define GSI_CHAR_SET_LATIN_4              4
#define GSI_CHAR_SET_ISO_8859_5           5
#define GSI_CHAR_SET_LATIN_CYRILLIC       5
#define GSI_CHAR_SET_ISO_8859_6           6
#define GSI_CHAR_SET_LATIN_ARABIC         6
#define GSI_CHAR_SET_ISO_8859_7           7
#define GSI_CHAR_SET_LATIN_GREEK          7
#define GSI_CHAR_SET_ISO_8859_8           8
#define GSI_CHAR_SET_LATIN_HEBREW         8
#define GSI_CHAR_SET_ISO_8859_9           9
#define GSI_CHAR_SET_LATIN_5              9
#define GSI_CHAR_SET_ISO_8859_10         10
#define GSI_CHAR_SET_LATIN_6             10
#define GSI_CHAR_SET_US_ASCII            11
#define GSI_CHAR_SET_ASCII               11
#define GSI_CHAR_SET_FILTER_TEXT_FOR_GSI 11
#define GSI_CHAR_SET_ISO_646_IRV         11
#define GSI_CHAR_SET_JIS                 12
#define GSI_CHAR_SET_JIS_X_0208          12
#define GSI_CHAR_SET_JIS_EUC             13
#define GSI_CHAR_SET_JIS_X_0208_EUC      13
#define GSI_CHAR_SET_SHIFT_JIS           14
#define GSI_CHAR_SET_SHIFT_JIS_X_0208    14
#define GSI_CHAR_SET_MS_KANJI            14
#define GSI_CHAR_SET_KS                  15
#define GSI_CHAR_SET_KS_C_5601           15
#define GSI_CHAR_SET_KS_EUC              16
#define GSI_CHAR_SET_KS_C_5601_EUC       16
#define GSI_CHAR_SET_UNICODE_UTF_7       17
#define GSI_CHAR_SET_UTF_7               17
#define GSI_CHAR_SET_UNICODE_UTF_8       18
#define GSI_CHAR_SET_UTF_8               18
#define GSI_CHAR_SET_ISO_2022            19
#define GSI_CHAR_SET_X_COMPOUND_TEXT     19

#define GSI_RUN_STATE_DIRECTION_ENTERING_GSI 1
#define GSI_RUN_STATE_DIRECTION_LEAVING_GSI 2
#define GSI_RUN_STATE_DIRECTION_ENTERING_WATCHDOG 3
#define GSI_RUN_STATE_DIRECTION_LEAVING_WATCHDOG 4
#define GSI_RUN_STATE_DIRECTION_ENTERING_GSI_BY_SIGNAL 5

#define GSI_RUN_STATE_TYPE_API 1
#define GSI_RUN_STATE_TYPE_CALLBACK 2
#define GSI_RUN_STATE_TYPE_WAIT 3
#define GSI_RUN_STATE_TYPE_SIGNAL 4

#define GSI_OWNER_IS_USER    0
#define GSI_OWNER_IS_GSI     1
#define GSI_OWNER_IS_CONTEXT 2

#if defined(WIN32)

#define DLLIMPORT __declspec( dllimport )
#define DLLEXPORT __declspec( dllexport )
#define GSI_API DLLEXPORT

#else

#define DLLIMPORT
#define DLLEXPORT
#define GSI_API

#endif

/* #define GSI_API_EXTERN extern "C" DLLEXPORT */
#define GSI_API_EXTERN GSI_API extern


/* Key to the declarations below:
 *   Since many GSI 4.0 api functions take more than one type of argument, and
 *  because all of these types are typedef void * from the C compilers point
 *  of view, we declare them all of type gsi_struct here (again, a void *) and
 *  use the names of the formal variables in the function prototype to
 *  indicate what GSI "types" are acceptable as arguments.  A mnemonic system
 *  is used:
 *    Each formal is named by a series of abbreviations for the GSI "types"
 *  which can be passed in that formal argument, separated by underscores.  The
 *  names are in all caps, to emphasize their mnemonic nature.	'I' stands for
 *  gsi_item, 'RI' for gsi_registered_item, and 'ATT' for gsi_attr.  The
 *  presence of 'REG' means a gsi_registration is acceptable.
 *    For example, an argument that could take an item or a registration would
 *  be named I_ATT, while an argument that could take an item, a registered
 *  item or a registration would be named I_RI_REG.  In all cases, the type of
 *  these arguments is given as gsi_struct, which is a typedef to a pointer to
 *  void.
 */

/*--------------------------------------------------------------------------*/
/*	      Function Prototype declarations for Callback functions        */
/*--------------------------------------------------------------------------*/

#if GSI_USE_PROTOTYPES
#define GSI_CALLBACK_PROTO_0() (void)
#define GSI_CALLBACK_PROTO_1(type1,arg1) \
 (type1 GSI_NON_C_REF(arg1))
#define GSI_CALLBACK_PROTO_2(type1,arg1,type2,arg2) \
 (type1 GSI_NON_C_REF(arg1),type2 GSI_NON_C_REF(arg2))
#define GSI_CALLBACK_PROTO_3(type1,arg1,type2,arg2,type3,arg3) \
 (type1 GSI_NON_C_REF(arg1),type2 GSI_NON_C_REF(arg2),type3 GSI_NON_C_REF(arg3))
#define GSI_CALLBACK_PROTO_4(type1,arg1,type2,arg2,type3,arg3,type4,arg4) \
 (type1 GSI_NON_C_REF(arg1),type2 GSI_NON_C_REF(arg2),type3 GSI_NON_C_REF(arg3),type4 GSI_NON_C_REF(arg4))
#else
#define GSI_CALLBACK_PROTO_0() ()
#define GSI_CALLBACK_PROTO_1(type1,arg1) ()
#define GSI_CALLBACK_PROTO_2(type1,arg1,type2,arg2) ()
#define GSI_CALLBACK_PROTO_3(type1,arg1,type2,arg2,type3,arg3) ()
#define GSI_CALLBACK_PROTO_4(type1,arg1,type2,arg2,type3,arg3,type4,arg4) ()
#endif

#if defined(GSI_USE_NON_C_CALLBACKS)
#define GSI_NON_C_REF(arg) (*arg)
#else
#define GSI_NON_C_REF(arg) (arg)
#endif
/*
 *  Callback functions - Application Initialization
 */
#define declare_gsi_set_up(gsi_set_up) \
  void    gsi_set_up \
          GSI_CALLBACK_PROTO_0()
#define declare_gsi_get_tcp_port(gsi_get_tcp_port) \
  gsi_int gsi_get_tcp_port \
          GSI_CALLBACK_PROTO_0()

/*
 *  Callback functions - flow control
 */
#define declare_gsi_read_callback(gsi_read_callback) \
  void gsi_read_callback \
       GSI_CALLBACK_PROTO_2( gsi_int, context, \
			     gsi_int, state )
#define declare_gsi_write_callback(gsi_write_callback) \
  void gsi_write_callback \
       GSI_CALLBACK_PROTO_2( gsi_int, context, \
			     gsi_int, state )

#define declare_gsi_open_fd(gsi_open_fd) \
  void gsi_open_fd \
       GSI_CALLBACK_PROTO_1( gsi_int, fd )
#define declare_gsi_close_fd(gsi_close_fd) \
  void gsi_close_fd \
       GSI_CALLBACK_PROTO_1( gsi_int, fd )
#define declare_gsi_writing_fd(gsi_writing_fd) \
  void gsi_writing_fd \
       GSI_CALLBACK_PROTO_1( gsi_int, fd )
#define declare_gsi_not_writing_fd(gsi_not_writing_fd) \
  void gsi_not_writing_fd \
       GSI_CALLBACK_PROTO_1( gsi_int, fd )

/*
 *  Callback functions - Connection Management
 */
#define declare_gsi_initialize_context(gsi_initialize_context) \
  gsi_int gsi_initialize_context \
          GSI_CALLBACK_PROTO_2( gsi_char *, remote_process_initialization_string, \
				gsi_int, length )
#define declare_gsi_pause_context(gsi_pause_context) \
  void    gsi_pause_context \
          GSI_CALLBACK_PROTO_0( )
#define declare_gsi_resume_context(gsi_resume_context) \
  void    gsi_resume_context \
          GSI_CALLBACK_PROTO_0( )
#define declare_gsi_start_context(gsi_start_context) \
  void    gsi_start_context \
          GSI_CALLBACK_PROTO_0( )
#define declare_gsi_reset_context(gsi_reset_context) \
  void    gsi_reset_context \
          GSI_CALLBACK_PROTO_0( )
#define declare_gsi_shutdown_context(gsi_shutdown_context) \
  void    gsi_shutdown_context \
          GSI_CALLBACK_PROTO_0( )

/*
 *  Callback functions - Item Registration and Deregistration
 */
#define declare_gsi_receive_registration(gsi_receive_registration) \
  void    gsi_receive_registration \
          GSI_CALLBACK_PROTO_1( gsi_registration, registration )
#define declare_gsi_receive_deregistrations(gsi_receive_deregistrations) \
  void    gsi_receive_deregistrations \
          GSI_CALLBACK_PROTO_2( gsi_registered_item_array, registered_items, \
				gsi_int, count )

/*
 *  Callback functions - Data Service
 */
#define declare_gsi_g2_poll(gsi_g2_poll) \
  void    gsi_g2_poll \
          GSI_CALLBACK_PROTO_0( )
#define declare_gsi_get_data(gsi_get_data) \
  void    gsi_get_data \
          GSI_CALLBACK_PROTO_2( gsi_registered_item_array, registered_items, \
				gsi_int, count )
#define declare_gsi_set_data(gsi_set_data) \
  void    gsi_set_data \
          GSI_CALLBACK_PROTO_2( gsi_registered_item_array, registered_items, \
				gsi_int, count )

/*
 *  Callback functions - Message Passing
 */
#define declare_gsi_receive_message(gsi_receive_message) \
  void    gsi_receive_message \
          GSI_CALLBACK_PROTO_2( gsi_char *, message, \
				gsi_int, length )
/*
 *  Callback functions - GSI Run State callback
 */
#define declare_gsi_run_state_change(gsi_run_state_change) \
  void    gsi_run_state_change \
          GSI_CALLBACK_PROTO_3( gsi_int, direction_code, \
				gsi_int, type_code, \
				char *, name)

/*
 *  Callback functions - Error handling.
 */
#define declare_gsi_error_handler(gsi_error_handler) \
  void    gsi_error_handler \
          GSI_CALLBACK_PROTO_3( gsi_int, error_context, \
				gsi_int, error_code, \
				gsi_char *, error_message )

#define declare_gsi_missing_procedure_handler(gsi_missing_procedure_handler) \
  void    gsi_missing_procedure_handler \
          GSI_CALLBACK_PROTO_1( gsi_char *, name )


#define declare_gsi_idle(gsi_idle) \
  void    gsi_idle \
          GSI_CALLBACK_PROTO_0( )

#ifndef GSI_CALLBACK_EXTERN
#define GSI_CALLBACK_EXTERN extern
#endif

#if !defined(GSI_NON_STANDARD_CALLBACKS)

GSI_CALLBACK_EXTERN declare_gsi_set_up(gsi_set_up);
GSI_CALLBACK_EXTERN declare_gsi_get_tcp_port(gsi_get_tcp_port);
GSI_CALLBACK_EXTERN declare_gsi_initialize_context(gsi_initialize_context);
GSI_CALLBACK_EXTERN declare_gsi_pause_context(gsi_pause_context);
GSI_CALLBACK_EXTERN declare_gsi_resume_context(gsi_resume_context);
GSI_CALLBACK_EXTERN declare_gsi_start_context(gsi_start_context);
GSI_CALLBACK_EXTERN declare_gsi_reset_context(gsi_reset_context);
GSI_CALLBACK_EXTERN declare_gsi_shutdown_context(gsi_shutdown_context);
GSI_CALLBACK_EXTERN declare_gsi_receive_registration(gsi_receive_registration);
GSI_CALLBACK_EXTERN declare_gsi_receive_deregistrations(gsi_receive_deregistrations);
GSI_CALLBACK_EXTERN declare_gsi_g2_poll(gsi_g2_poll);
GSI_CALLBACK_EXTERN declare_gsi_get_data(gsi_get_data);
GSI_CALLBACK_EXTERN declare_gsi_set_data(gsi_set_data);
GSI_CALLBACK_EXTERN declare_gsi_receive_message(gsi_receive_message);

#endif

#define gsi_name_of_gsi_set_up gsin_set_up
#define gsi_name_of_gsi_get_tcp_port gsin_get_tcp_port
#define gsi_name_of_gsi_read_callback gsin_read_callback
#define gsi_name_of_gsi_write_callback gsin_write_callback
#define gsi_name_of_gsi_open_fd gsin_open_fd
#define gsi_name_of_gsi_close_fd gsin_close_fd
#define gsi_name_of_gsi_writing_fd gsin_writing_fd
#define gsi_name_of_gsi_not_writing_fd gsin_not_writing_fd
#define gsi_name_of_gsi_initialize_context gsin_initialize_context
#define gsi_name_of_gsi_pause_context gsin_pause_context
#define gsi_name_of_gsi_resume_context gsin_resume_context
#define gsi_name_of_gsi_start_context gsin_start_context
#define gsi_name_of_gsi_reset_context gsin_reset_context
#define gsi_name_of_gsi_shutdown_context gsin_shutdown_context
#define gsi_name_of_gsi_receive_registration gsin_receive_registration
#define gsi_name_of_gsi_receive_deregistrations gsin_receive_deregistrations
#define gsi_name_of_gsi_g2_poll gsin_g2_poll
#define gsi_name_of_gsi_get_data gsin_get_data
#define gsi_name_of_gsi_set_data gsin_set_data
#define gsi_name_of_gsi_receive_message gsin_receive_message
#define gsi_name_of_gsi_run_state_change gsin_run_state_change
#define gsi_name_of_gsi_error_handler gsin_error_handler
#define gsi_name_of_gsi_missing_procedure_handler gsin_missing_procedure_handler
#define gsi_name_of_gsi_idle gsin_idle

#define gsi_install_error_handler(error_handler_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_error_handler(),error_handler_function,(void *)NULL);

#define gsi_install_missing_procedure_handler(gsi_missing_procedure_handler_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_missing_procedure_handler(),\
			   gsi_missing_procedure_handler_function,(void *)NULL);

#define gsi_install_run_state_change(run_state_change_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_run_state_change(),run_state_change_function,(void *)NULL);

#define gsi_install_gsi_idle(gsi_idle_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_idle(),gsi_idle_function,(void *)NULL);

#define gsi_install_start_context(gsi_start_context_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_start_context(),gsi_start_context_function, \
			   (void *)NULL);

#define gsi_install_reset_context(gsi_reset_context_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_reset_context(),gsi_reset_context_function, \
			   (void *)NULL);

#define gsi_install_open_fd(gsi_open_fd_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_open_fd(),gsi_open_fd_function, \
			   (void *)NULL);

#define gsi_install_close_fd(gsi_close_fd_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_close_fd(),gsi_close_fd_function, \
			   (void *)NULL);

#define gsi_install_writing_fd(gsi_writing_fd_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_writing_fd(),gsi_writing_fd_function, \
			   (void *)NULL);

#define gsi_install_not_writing_fd(gsi_not_writing_fd_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_not_writing_fd(),gsi_not_writing_fd_function, \
			   (void *)NULL);

#define gsi_install_read_callback(gsi_read_callback_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_read_callback(),gsi_read_callback_function, \
                           (void *)NULL);

#define gsi_install_write_callback(gsi_write_callback_function) \
  gsi_initialize_callbacks(gsi_name_of_gsi_write_callback(),gsi_write_callback_function, \
                           (void *)NULL);

#if GSI_USE_PROTOTYPES
#define GSI_API_PROTO(args) args
#else
#define GSI_API_PROTO(args) ()
#endif

#define declare_gsi_watchdog_function(gsi_watchdog_function) \
  void    gsi_watchdog_function \
          GSI_CALLBACK_PROTO_0( )

typedef declare_gsi_watchdog_function(gsi_watchdog_function_type);


#ifdef GSI_USE_USER_DATA_FOR_CALLBACKS

#define gsi_rpc_declare_remote  gsi_rpc_declare_remote_with_user_data
#define gsi_rpc_declare_local   gsi_rpc_declare_local_with_user_data
#define gsi_rpc_call            gsi_rpc_call_with_user_data
#define gsi_rpc_call_with_count gsi_rpc_call_with_count_and_user_data
#define WITH_USER_DATA_FOR_CALLBACKS(arg) arg
#define SEPERATOR_FOR_USER_DATA_FOR_CALLBACKS ,

#define declare_gsi_rpc_receiver_fn(gsi_rpc_receiver_fn) \
  void    gsi_rpc_receiver_fn \
          GSI_CALLBACK_PROTO_4( gsi_procedure_user_data_type, procedure_user_data, \
                                gsi_item *, rpc_arguments, \
                                gsi_int, count, \
                                gsi_call_identifier_type, call_identifier )

#define declare_gsi_rpc_local_fn(gsi_rpc_local_fn) \
  void    gsi_rpc_local_fn \
        GSI_CALLBACK_PROTO_4( gsi_procedure_user_data_type, procedure_user_data, \
			      gsi_item *, rpc_arguments, \
			      gsi_int, count, \
			      gsi_call_identifier_type, call_identifier )

#else

#define gsi_rpc_declare_remote gsi_rpc_declare_remote_plain
#define gsi_rpc_declare_local  gsi_rpc_declare_local_plain
#define WITH_USER_DATA_FOR_CALLBACKS(arg)
#define SEPERATOR_FOR_USER_DATA_FOR_CALLBACKS

#define declare_gsi_rpc_receiver_fn(gsi_rpc_receiver_fn) \
  void    gsi_rpc_receiver_fn \
          GSI_CALLBACK_PROTO_2( gsi_item *, rpc_arguments, \
                                gsi_int, count )

#define declare_gsi_rpc_local_fn(gsi_rpc_local_fn) \
  void    gsi_rpc_local_fn \
        GSI_CALLBACK_PROTO_3( gsi_item *, rpc_arguments, \
			      gsi_int, count, \
			      gsi_call_identifier_type, call_identifier )

#endif

typedef declare_gsi_rpc_receiver_fn(gsi_rpc_receiver_fn_type);

typedef declare_gsi_rpc_local_fn(gsi_rpc_local_fn_type);

#define gsi_convert_string_to_unicode      gsi_convert_str_to_ustr
#define gsi_convert_wide_string_to_unicode gsi_convert_wstr_to_ustr
#define gsi_convert_unicode_to_string      gsi_convert_ustr_to_str
#define gsi_convert_unicode_to_wide_string gsi_convert_ustr_to_wstr

#define gsi_context_remote_process_start_time gsi_context_remote_start_time
#define gsi_context_remote_listener_port gsi_context_remote_port

#if GSI_USE_PROTOTYPES
#define GSI_API_PROTO(args) args
#else
#define GSI_API_PROTO(args) ()
#endif

#ifndef GSI_API_EXTERN
#define GSI_API_EXTERN
#endif

/*--------------------------------------------------------------------------*/
/*	     Function Prototype declarations for GSI API functions          */
/*--------------------------------------------------------------------------*/

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_set_up
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_get_tcp_port
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_read_callback
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_write_callback
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_open_fd
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_close_fd
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_writing_fd
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_not_writing_fd
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_initialize_context
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_pause_context
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_resume_context
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_start_context
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_reset_context
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_shutdown_context
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_receive_registration
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_receive_deregistrations
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_g2_poll
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_get_data
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_set_data
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_receive_message
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_run_state_change
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_error_handler
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_missing_procedure_handler
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_symbol  gsi_name_of_gsi_idle
        GSI_API_PROTO(( void ));

/* (name1,fn1, ... , namen,fnn,(gsi_symbol)0) */
/* Each name is void * (type depends upon whether the new symbol */
/* API is used or not,   */
/* Each fn is a function pointer          */
GSI_API_EXTERN void      gsi_initialize_callbacks
        GSI_API_PROTO(( void *name1, ... ));

/*
 *  Startup, network, and miscellaneous system-level operations.
 */

GSI_API_EXTERN void      gsi_start
        GSI_API_PROTO(( int argc, char **argv ));
/* gsi_start has no wide char equivalent */

#if defined(WIN32)
#ifndef _WINDOWS_
#include <windows.h>
#endif
GSI_API_EXTERN void      gsi_initialize_for_win32
        GSI_API_PROTO(( HANDLE hInstance, char * lpCmdLine ));
#endif

GSI_API_EXTERN gsi_int   gsi_establish_listener
        GSI_API_PROTO(( gsi_char *network, gsi_char *port, gsi_int exact ));
GSI_API_EXTERN gsi_int   gsi_establish_secure_listener
        GSI_API_PROTO(( gsi_char *network, gsi_char *port, gsi_int exact, gsi_char *cert ));
GSI_API_EXTERN void      gsi_close_listeners
        GSI_API_PROTO(( void ));

GSI_API_EXTERN void      gsi_set_context_limit
        GSI_API_PROTO(( gsi_int limit ));
GSI_API_EXTERN void      gsi_kill_context
        GSI_API_PROTO(( gsi_int context ));

GSI_API_EXTERN void	 gsi_set_option
        GSI_API_PROTO(( gsi_int option_index ));
GSI_API_EXTERN void	 gsi_reset_option
        GSI_API_PROTO(( gsi_int option_index ));
GSI_API_EXTERN gsi_int	 gsi_option_is_set
        GSI_API_PROTO(( gsi_int option_index ));

GSI_API_EXTERN gsi_int	 gsi_current_context
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_int	 gsi_current_context_is_secure
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_int	 gsi_context_is_secure
        GSI_API_PROTO(( gsi_int context ));

GSI_API_EXTERN double	  gsi_context_remote_process_start_time
        GSI_API_PROTO(( gsi_int context ));
GSI_API_EXTERN gsi_char  *gsi_context_remote_host
        GSI_API_PROTO(( gsi_int context ));
GSI_API_EXTERN gsi_int    gsi_context_remote_listener_port
        GSI_API_PROTO(( gsi_int context ));

GSI_API_EXTERN void	 gsi_watch_fd
        GSI_API_PROTO(( long file_descriptor ));
GSI_API_EXTERN void	 gsi_unwatch_fd
        GSI_API_PROTO(( long file_descriptor ));
GSI_API_EXTERN void	 gsi_watch_fd_for_writing
        GSI_API_PROTO(( long file_descriptor ));
GSI_API_EXTERN void	 gsi_unwatch_fd_for_writing
        GSI_API_PROTO(( long file_descriptor ));

GSI_API_EXTERN gsi_int	 gsi_is_idle
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_int	 gsi_has_network_connections
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_context_user_data_type gsi_context_user_data
        GSI_API_PROTO(( gsi_int context ));
GSI_API_EXTERN void      gsi_set_context_user_data
        GSI_API_PROTO(( gsi_int context,
			gsi_context_user_data_type context_user_data ));

GSI_API_EXTERN void	 gsi_flush
        GSI_API_PROTO(( gsi_int context ));

GSI_API_EXTERN gsi_int	 gsi_wakeup
        GSI_API_PROTO(( void ));

GSI_API_EXTERN void	 gsi_watchdog
        GSI_API_PROTO(( gsi_watchdog_function_type *watchdog_function,
			gsi_int timeout_interval ));

GSI_API_EXTERN gsi_int	 gsi_context_socket
        GSI_API_PROTO(( gsi_int context ));
GSI_API_EXTERN gsi_int	 gsi_listener_socket
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_int   gsi_context_received_data
        GSI_API_PROTO(( gsi_int context ));
GSI_API_EXTERN void	 gsi_set_run_loop_timeout
        GSI_API_PROTO(( gsi_int max_run_time ));
GSI_API_EXTERN void	 gsi_run_loop
        GSI_API_PROTO(( void ));
GSI_API_EXTERN void	 gsi_set_pause_timeout
        GSI_API_PROTO(( gsi_int max_idle_time ));
GSI_API_EXTERN void	 gsi_pause
        GSI_API_PROTO(( void ));

GSI_API_EXTERN gsi_int   gsi_initiate_connection
        GSI_API_PROTO(( gsi_char *interface_name,
			gsi_char *interface_class_name,
			gsi_int keep_connection_on_g2_reset,
			gsi_char *network, gsi_char *host, gsi_char *port,
			gsi_char *remote_process_initialization_string));


GSI_API_EXTERN gsi_int   gsi_initiate_secure_connection
        GSI_API_PROTO(( gsi_char *interface_name,
			gsi_char *interface_class_name,
			gsi_int keep_connection_on_g2_reset,
			gsi_char *network, gsi_char *host, gsi_char *port,
			gsi_char *remote_process_initialization_string));

#define gsi_initiate_connection_with_user_data gsi_initiate_connection_w_u_d

#define gsi_initiate_secure_connection_with_user_data gsi_initiate_secure_conn_w_u_d

GSI_API_EXTERN gsi_int   gsi_initiate_connection_with_user_data
        GSI_API_PROTO(( gsi_char *interface_name,
			gsi_char *interface_class_name,
			gsi_int keep_connection_on_g2_reset,
			gsi_char *network, gsi_char *host, gsi_char *port,
			gsi_char *remote_process_initialization_string,
			gsi_context_user_data_type context_user_data ));

GSI_API_EXTERN gsi_int   gsi_initiate_secure_connection_with_user_data
        GSI_API_PROTO(( gsi_char *interface_name,
			gsi_char *interface_class_name,
			gsi_int keep_connection_on_g2_reset,
			gsi_char *network, gsi_char *host, gsi_char *port,
			gsi_char *remote_process_initialization_string,
			gsi_context_user_data_type context_user_data ));

/*
 *  Error handling.
 */
GSI_API_EXTERN void      gsi_initialize_error_variable
        GSI_API_PROTO(( gsi_int *error_variable_address ));
GSI_API_EXTERN gsi_char	*gsi_error_message
        GSI_API_PROTO(( gsi_int error_code ));
GSI_API_EXTERN void	 gsi_clear_last_error
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_int	 gsi_last_error
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_char *gsi_last_error_message
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_call_identifier_type gsi_last_error_call_handle
        GSI_API_PROTO(( void ));
GSI_API_EXTERN void	 gsi_signal_error
        GSI_API_PROTO(( gsi_char *originating_function_name,
			gsi_int user_error,
			gsi_char *message ));
GSI_API_EXTERN void      gsi_signal_handler
        GSI_API_PROTO(( int signal_code ));

/*
 *  GSI structure allocation and reclamation.
 */
GSI_API_EXTERN gsi_int   gsi_owner_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT_REG ));
GSI_API_EXTERN gsi_item	*gsi_make_array
        GSI_API_PROTO(( gsi_int  count ));
GSI_API_EXTERN gsi_item	gsi_make_item
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_item	*gsi_make_items
        GSI_API_PROTO(( gsi_int  count ));
GSI_API_EXTERN gsi_attr *gsi_make_attrs
        GSI_API_PROTO(( gsi_int count ));
GSI_API_EXTERN gsi_attr *gsi_make_attrs_with_items
        GSI_API_PROTO(( gsi_int count ));
GSI_API_EXTERN gsi_registered_item  *gsi_make_registered_items
        GSI_API_PROTO(( gsi_int count ));

GSI_API_EXTERN void      gsi_reclaim_array
        GSI_API_PROTO(( gsi_item *array ));
GSI_API_EXTERN void      gsi_reclaim_item
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void      gsi_reclaim_items
        GSI_API_PROTO(( gsi_item *items ));
GSI_API_EXTERN void      gsi_reclaim_attrs
        GSI_API_PROTO(( gsi_attr *attributes ));
GSI_API_EXTERN void      gsi_reclaim_attrs_with_items
        GSI_API_PROTO(( gsi_attr *attributes ));
GSI_API_EXTERN void      gsi_reclaim_registered_items
        GSI_API_PROTO(( gsi_registered_item *registered_items ));

GSI_API_EXTERN gsi_symbol gsi_make_symbol
        GSI_API_PROTO(( gsi_char *name ));
GSI_API_EXTERN gsi_char  *gsi_symbol_name
        GSI_API_PROTO(( gsi_symbol sym ));

GSI_API_EXTERN gsi_symbol_user_data_type gsi_symbol_user_data
        GSI_API_PROTO(( gsi_symbol sym ));
GSI_API_EXTERN void                  gsi_set_symbol_user_data
        GSI_API_PROTO(( gsi_symbol sym, gsi_symbol_user_data_type symbol_user_data ));

/*
 *  Returning data to G2.
 */
GSI_API_EXTERN void  gsi_return_values
        GSI_API_PROTO(( gsi_registered_item *registered_items, gsi_int count, gsi_int context ));
GSI_API_EXTERN void  gsi_return_attrs
        GSI_API_PROTO(( gsi_registered_item registered_item, gsi_attr *attributes,
			gsi_int count, gsi_int context ));
GSI_API_EXTERN void  gsi_return_message
        GSI_API_PROTO(( gsi_char *message, gsi_int context ));
GSI_API_EXTERN void  gsi_return_timed_values
        GSI_API_PROTO(( gsi_registered_item *registered_items, gsi_int count, gsi_int context ));
GSI_API_EXTERN void  gsi_return_timed_attrs
        GSI_API_PROTO(( gsi_registered_item registered_item, gsi_attr *attributes,
			gsi_int count, gsi_int context ));

GSI_API_EXTERN gsi_int  gsi_item_append_flag
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void  gsi_set_item_append_flag
        GSI_API_PROTO(( gsi_item item, gsi_int append_flag ));

#define gsi_update_items_in_lists_and_arrays_flag gsi_update_items_flag
GSI_API_EXTERN gsi_int  gsi_update_items_in_lists_and_arrays_flag
        GSI_API_PROTO(( gsi_item item ));
#define gsi_set_update_items_in_lists_and_arrays_flag gsi_set_update_items_flag
GSI_API_EXTERN void  gsi_set_update_items_in_lists_and_arrays_flag
        GSI_API_PROTO(( gsi_item item, gsi_int immediate_flag ));




/*
 *  RPC related operations.
 */

#define gsi_rpc_declare_remote_with_user_data gsi_rpc_declare_remote_w_u_d
#define gsi_rpc_declare_remote_with_error_handler_and_user_data gsi_rpc_declare_remote_w_e_u_d
#define gsi_rpc_declare_local_with_user_data  gsi_rpc_declare_local_w_u_d
#define gsi_set_rpc_remote_return_value_kind  gsi_set_rpc_remote_return_v_k
#define gsi_set_rpc_remote_return_exclude_user_attrs  gsi_set_rpc_remote_return_e_u_a
#define gsi_set_rpc_remote_return_include_system_attrs  gsi_set_rpc_remote_return_i_s_a
#define gsi_set_rpc_remote_return_include_all_system_attrs_except  gsi_set_rpc_remote_r_i_a_s_a_e

#define gsi_rpc_call_with_user_data           gsi_rpc_call_with_u_d
#define gsi_rpc_call_with_count_and_user_data gsi_rpc_call_with_count_u_d

#ifdef GSI_USE_USER_DATA_FOR_CALLBACKS
GSI_API_EXTERN void    gsi_rpc_declare_remote_with_error_handler_and_user_data
        GSI_API_PROTO(( gsi_function_handle_type *function_handle,
			gsi_char *g2_function_name,
			gsi_rpc_receiver_fn_type *receiver_function,
			gsi_rpc_receiver_fn_type *error_receiver_function,
			WITH_USER_DATA_FOR_CALLBACKS(gsi_procedure_user_data_type procedure_user_data)
			SEPERATOR_FOR_USER_DATA_FOR_CALLBACKS
			gsi_int argument_count,
			gsi_int return_count,
			gsi_int context ));
#endif

GSI_API_EXTERN void    gsi_rpc_declare_remote
        GSI_API_PROTO(( gsi_function_handle_type *function_handle,
			gsi_char *g2_function_name,
			gsi_rpc_receiver_fn_type *receiver_function,
			WITH_USER_DATA_FOR_CALLBACKS(gsi_procedure_user_data_type procedure_user_data)
			SEPERATOR_FOR_USER_DATA_FOR_CALLBACKS
			gsi_int argument_count,
			gsi_int return_count,
			gsi_int context ));

GSI_API_EXTERN void    gsi_rpc_declare_local
        GSI_API_PROTO(( gsi_rpc_local_fn_type *local_function,
			WITH_USER_DATA_FOR_CALLBACKS(gsi_procedure_user_data_type procedure_user_data)
			SEPERATOR_FOR_USER_DATA_FOR_CALLBACKS
			gsi_char *g2_function_name ));

GSI_API_EXTERN void    gsi_rpc_start
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_item *arguments,
			gsi_int context ));
GSI_API_EXTERN void    gsi_rpc_start_with_count
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_item *arguments,
			gsi_int count,
			gsi_int context ));

GSI_API_EXTERN void gsi_rpc_call
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_item *arguments,
			WITH_USER_DATA_FOR_CALLBACKS(gsi_call_identifier_type call_identifier)
			SEPERATOR_FOR_USER_DATA_FOR_CALLBACKS
			gsi_int context ));
GSI_API_EXTERN void gsi_rpc_call_with_count
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_item *arguments,
			gsi_int count,
			WITH_USER_DATA_FOR_CALLBACKS(gsi_call_identifier_type call_identifier)
			SEPERATOR_FOR_USER_DATA_FOR_CALLBACKS
			gsi_int context ));


GSI_API_EXTERN void    gsi_set_rpc_remote_return_value_kind
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_int return_value_index,
			gsi_char *kind ));

GSI_API_EXTERN void    gsi_set_rpc_remote_return_exclude_user_attrs
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_item *attrs));

GSI_API_EXTERN void    gsi_set_rpc_remote_return_include_system_attrs
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_item *attrs));

GSI_API_EXTERN void    gsi_set_rpc_remote_return_include_all_system_attrs_except
        GSI_API_PROTO(( gsi_function_handle_type function_handle,
			gsi_item *attrs));

GSI_API_EXTERN void    gsi_rpc_return_values
        GSI_API_PROTO(( gsi_item *arguments,
			gsi_int count,
			gsi_call_identifier_type call_identifier,
			gsi_int context ));

GSI_API_EXTERN void    gsi_rpc_return_error_values
        GSI_API_PROTO(( gsi_item *arguments,
			gsi_int count,
			gsi_call_identifier_type call_identifier,
			gsi_int context ));

/*
 *  For accessing the main object array.
 */
GSI_API_EXTERN gsi_registration  gsi_registration_of_handle
        GSI_API_PROTO(( gsi_int item_handle, gsi_int context ));
GSI_API_EXTERN gsi_registration  gsi_registration_of_item
        GSI_API_PROTO(( gsi_struct I_RI_REG ));

GSI_API_EXTERN gsi_item_user_data_type gsi_user_data_of
        GSI_API_PROTO(( gsi_registration registration ));
GSI_API_EXTERN void		 gsi_set_user_data
        GSI_API_PROTO(( gsi_registration registration, gsi_item_user_data_type item_user_data ));

/*
 *  For accessing name and class
 *  information from item registrations,
 *  registered items, items, or attributes.
 */
GSI_API_EXTERN gsi_symbol gsi_name_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT_REG ));
GSI_API_EXTERN gsi_symbol gsi_class_name_of
        GSI_API_PROTO(( gsi_struct I_ATT ));
GSI_API_EXTERN void	  gsi_set_name
        GSI_API_PROTO(( gsi_item item, gsi_symbol name ));
GSI_API_EXTERN void	  gsi_set_class_name
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_symbol name ));

/*
 *  For accessing information unique to item
 *  registrations and/or registered items.
 */
GSI_API_EXTERN gsi_int	  gsi_handle_of
        GSI_API_PROTO(( gsi_struct I_RI_REG ));
GSI_API_EXTERN double	  gsi_interval_of
        GSI_API_PROTO(( gsi_struct RI_REG ));
GSI_API_EXTERN gsi_int	  gsi_status_of
        GSI_API_PROTO(( gsi_registered_item registered_item ));
GSI_API_EXTERN gsi_attr   gsi_item_of_identifying_attr_of
        GSI_API_PROTO(( gsi_registration registration, gsi_int identifying_attribute_index ));
GSI_API_EXTERN void	  gsi_set_handle
        GSI_API_PROTO(( gsi_struct I_RI, gsi_int handle_value ));
GSI_API_EXTERN void	  gsi_set_interval
        GSI_API_PROTO(( gsi_registered_item registered_item, gsi_int interval ));
GSI_API_EXTERN void	  gsi_set_status
        GSI_API_PROTO(( gsi_registered_item registered_item, gsi_int status ));

/*
 *  Accessing the value(s) of an item,
 *  registered item, or attribute.
 */
GSI_API_EXTERN gsi_int	   gsi_type_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT_REG ));
GSI_API_EXTERN void	   gsi_set_type
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_int gsi_type ));

GSI_API_EXTERN gsi_int	   gsi_int_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_long	   gsi_long_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_ulong   gsi_ulong_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));		

GSI_API_EXTERN double	   gsi_flt_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_int	   gsi_log_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_char	  *gsi_str_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN unsigned short *gsi_usv_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
#define gsi_usv_length_of(x) gsi_element_count_of(x)
GSI_API_EXTERN gsi_symbol  gsi_sym_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_int	  *gsi_int_array_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN double	  *gsi_flt_array_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_int	  *gsi_log_array_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_symbol *gsi_sym_array_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_char	 **gsi_str_array_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_int	  *gsi_int_list_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN double	  *gsi_flt_list_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_int	  *gsi_log_list_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_symbol *gsi_sym_list_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_char	 **gsi_str_list_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_item   *gsi_elements_of
        GSI_API_PROTO(( gsi_struct I_ATT ));
GSI_API_EXTERN void	   gsi_set_int
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_int integer_value ));
GSI_API_EXTERN void	   gsi_set_long
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_long long_value ));
GSI_API_EXTERN void	   gsi_set_ulong
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_ulong ulong_value ));
GSI_API_EXTERN void	   gsi_set_flt
        GSI_API_PROTO(( gsi_struct I_RI_ATT, double float_value ));
GSI_API_EXTERN void	   gsi_set_log
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_int truth_value ));
GSI_API_EXTERN void	   gsi_set_str
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_char *text_value ));
GSI_API_EXTERN void	   gsi_set_usv
        GSI_API_PROTO(( gsi_struct I_RI_ATT, unsigned short *us_vector, gsi_int length ));
GSI_API_EXTERN void	   gsi_set_sym
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_symbol symbol_value ));
GSI_API_EXTERN void	   gsi_set_int_array
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_int *integers_array, gsi_int count ));
GSI_API_EXTERN void	   gsi_set_flt_array
        GSI_API_PROTO(( gsi_struct I_ATT, double *doubles_array, gsi_int count));
GSI_API_EXTERN void	   gsi_set_log_array
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_int *truth_values_array, gsi_int count));
GSI_API_EXTERN void	   gsi_set_sym_array
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_symbol *symbol_values_array, gsi_int count));
GSI_API_EXTERN void	   gsi_set_str_array
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_char **text_values_array, gsi_int count));
GSI_API_EXTERN void	   gsi_set_int_list
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_int *integers_array, gsi_int count ));
GSI_API_EXTERN void	   gsi_set_flt_list
        GSI_API_PROTO(( gsi_struct I_ATT, double *doubles_array, gsi_int count ));
GSI_API_EXTERN void	   gsi_set_log_list
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_int *truth_values_array, gsi_int count));
GSI_API_EXTERN void	   gsi_set_sym_list
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_symbol *symbol_values_array, gsi_int count));
GSI_API_EXTERN void	   gsi_set_str_list
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_char **text_values_array, gsi_int count));
GSI_API_EXTERN void	   gsi_set_elements
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_item *elements_array, gsi_int count,
			gsi_int type_tag ));

/*
 *  For accessing other relevant data common to
 *  items, registered items, and attributes.
 */
GSI_API_EXTERN gsi_int	   gsi_class_type_of
        GSI_API_PROTO(( gsi_struct I_ATT ));
GSI_API_EXTERN gsi_int	   gsi_set_class_type
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_int type ));
GSI_API_EXTERN gsi_int	   gsi_element_count_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_int	   gsi_attr_count_of
        GSI_API_PROTO(( gsi_struct I_ATT ));
GSI_API_EXTERN gsi_attr   *gsi_attrs_of
        GSI_API_PROTO(( gsi_struct I_ATT ));
GSI_API_EXTERN gsi_attr    gsi_attr_by_name
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_symbol search_name ));
GSI_API_EXTERN gsi_item    gsi_item_of_attr_by_name
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_symbol search_name ));
GSI_API_EXTERN gsi_int	   gsi_history_count_of
        GSI_API_PROTO(( gsi_struct I_ATT ));
GSI_API_EXTERN gsi_int	   gsi_extract_history
        GSI_API_PROTO(( gsi_item item, void **values_address,
			double **timestamps_address, gsi_int *type_address ));
GSI_API_EXTERN gsi_int	   gsi_extract_history_spec
        GSI_API_PROTO(( gsi_item item, gsi_int *maximum_count_address,
			gsi_int *maximum_age_address,
			gsi_int *minimum_interval_address ));

GSI_API_EXTERN void	   gsi_set_element_count
        GSI_API_PROTO(( gsi_item item, gsi_int count ));
GSI_API_EXTERN void	   gsi_set_attr_count
        GSI_API_PROTO(( gsi_struct I_RI_ATT_REG, gsi_int count ));
GSI_API_EXTERN void	   gsi_set_attrs
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_attr *new_attributes, gsi_int count ));
GSI_API_EXTERN void	   gsi_set_attr_by_name
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_symbol search_name, gsi_attr source_attr ));
GSI_API_EXTERN void	   gsi_set_item_of_attr_by_name
        GSI_API_PROTO(( gsi_struct I_ATT, gsi_symbol search_name, gsi_item source_item ));
GSI_API_EXTERN void	   gsi_set_history
        GSI_API_PROTO(( gsi_struct I_ATT, void *values, double *timestamps,
			gsi_int count, gsi_int type, gsi_int maximum_count,
			gsi_int maximum_age, gsi_int min_interval ));

/*
 *  For accessing data unique to attributes.
 */
GSI_API_EXTERN gsi_symbol gsi_attr_name_of
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN gsi_item   gsi_item_of_attr
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN gsi_symbol gsi_unqualified_attr_name_of
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN gsi_symbol gsi_class_qualifier_of
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN gsi_int    gsi_attr_name_is_qualified
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN void	  gsi_set_attr_name
        GSI_API_PROTO(( gsi_attr attribute, gsi_symbol attribute_name ));
GSI_API_EXTERN void	  gsi_set_item_of_attr
        GSI_API_PROTO(( gsi_attr attribute, gsi_item source_item ));
GSI_API_EXTERN void	  gsi_set_unqualified_attr_name
        GSI_API_PROTO(( gsi_attr attribute, gsi_symbol attribute_name ));
GSI_API_EXTERN void	  gsi_set_class_qualifier
        GSI_API_PROTO(( gsi_attr attribute, gsi_symbol attribute_name ));

GSI_API_EXTERN gsi_int    gsi_attr_is_transient
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN void       gsi_set_attr_is_transient
        GSI_API_PROTO(( gsi_attr attribute, gsi_int new_value ));

/*
 *  For converting between timestamp formats
 */
GSI_API_EXTERN void	 gsi_decode_timestamp
        GSI_API_PROTO(( double timestamp, gsi_int *year_address, gsi_int *month_address,
			gsi_int *day_address, gsi_int *hour_address,
			gsi_int *minute_address, gsi_int *second_address ));
GSI_API_EXTERN double	 gsi_encode_timestamp
        GSI_API_PROTO(( gsi_int year, gsi_int month, gsi_int day,
			gsi_int hour, gsi_int minute, gsi_int second ));

/*
 *  Miscellaneous functions
 */
GSI_API_EXTERN void	 gsi_clear_item
        GSI_API_PROTO(( gsi_struct I_RI_ATT ));
GSI_API_EXTERN gsi_int   gsi_is_item
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN gsi_item  gsi_item_of_registered_item
        GSI_API_PROTO(( gsi_registered_item registered_item ));
GSI_API_EXTERN void	 gsi_simple_content_copy
        GSI_API_PROTO(( gsi_item destination, gsi_item source ));
GSI_API_EXTERN double	 gsi_timestamp_of
        GSI_API_PROTO(( gsi_struct I_ATT ));
GSI_API_EXTERN void      gsi_set_timestamp
        GSI_API_PROTO(( gsi_struct I_ATT, double timestamp ));


/*
 * Version information
 */
GSI_API_EXTERN gsi_int	 gsi_major_version
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_int	 gsi_minor_version
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_int	 gsi_release_quality
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_int	 gsi_revision_number
        GSI_API_PROTO(( void ));
GSI_API_EXTERN gsi_int	 gsi_build_id_integer
        GSI_API_PROTO(( void ));


/*
 * GSI Character Set Selection Functions
 */

GSI_API_EXTERN gsi_int   gsi_string_conversion_style
        GSI_API_PROTO(( void ));
GSI_API_EXTERN void      gsi_set_string_conversion_style
        GSI_API_PROTO(( gsi_int style ));

/*
 *  String Conversion Functions
 */
GSI_API_EXTERN short    *gsi_convert_string_to_unicode
        GSI_API_PROTO(( char *string, gsi_int style ));
GSI_API_EXTERN short    *gsi_convert_wide_string_to_unicode
        GSI_API_PROTO(( short *string, gsi_int style ));

GSI_API_EXTERN char     *gsi_convert_unicode_to_string
        GSI_API_PROTO(( short *string, gsi_int style ));
GSI_API_EXTERN short    *gsi_convert_unicode_to_wide_string
        GSI_API_PROTO(( short *string, gsi_int style ));




GSI_API_EXTERN void      gsi_set_local_home
        GSI_API_PROTO(( gsi_item local_home ));

GSI_API_EXTERN gsi_int  gsi_item_reference_flag
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void     gsi_set_item_reference_flag
        GSI_API_PROTO(( gsi_item item, gsi_int reference_flag ));

#define gsi_item_name_is_identifying_flag gsi_item_name_is_ident_flag
#define gsi_set_item_name_is_identifying_flag gsi_set_item_name_is_ident_flag
GSI_API_EXTERN gsi_int  gsi_item_name_is_identifying_flag
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void     gsi_set_item_name_is_identifying_flag
        GSI_API_PROTO(( gsi_item item, gsi_int reference_flag ));

#define gsi_item_class_is_identifying_flag gsi_item_class_is_ident_flag
#define gsi_set_item_class_is_identifying_flag gsi_set_item_class_is_ident_flag
GSI_API_EXTERN gsi_int  gsi_item_class_is_identifying_flag
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void     gsi_set_item_class_is_identifying_flag
        GSI_API_PROTO(( gsi_item item, gsi_int reference_flag ));

GSI_API_EXTERN gsi_int    gsi_attr_is_identifying
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN void       gsi_set_attr_is_identifying
        GSI_API_PROTO(( gsi_attr attribute, gsi_int new_value ));

GSI_API_EXTERN gsi_int gsi_version_information
  GSI_API_PROTO(( gsi_version_id *v_id ));



#define gsi_include_file_revision_version gsi_include_file_rev_version

#if !defined(GSI_USE_DLL)
extern gsi_int gsi_include_file_major_version;
extern gsi_int gsi_include_file_minor_version;
extern gsi_int gsi_include_file_revision_version;
#endif

GSI_API_EXTERN void gsi_set_include_file_version
        GSI_API_PROTO(( gsi_int majr, gsi_int minr, gsi_int rev ));


#define gsi_attr_by_name        gsi_item_of_attr_by_name
#define gsi_set_attr_by_name    gsi_set_item_of_attr_by_name

#define gsi_identifying_attr_of gsi_item_of_identifying_attr_of
#define gsi_registration_of     gsi_registration_of_handle

#define gsi_history_type_of     gsi_class_type_of
#define gsi_set_history_type    gsi_set_class_type

/*--------------------------------------------------------------------------*/
/*		 Declarations for optional version control                  */
/*--------------------------------------------------------------------------*/
#define GSI_INCLUDE_MAJ_VER_NUM	      7L
#define GSI_INCLUDE_MIN_VER_NUM	      0L
#define GSI_INCLUDE_REV_VER_NUM	      0L

#define GSI_PROTOTYPE_RELEASE_QUALITY 0
#define GSI_ALPHA_RELEASE_QUALITY     1
#define GSI_BETA_RELEASE_QUALITY      2
#define GSI_FCS_RELEASE_QUALITY       3

#define GSI_PROTOTYPE_INFO_STRING     "Prototype "
#define GSI_ALPHA_INFO_STRING         "Alpha "
#define GSI_BETA_INFO_STRING          "Beta "
#define GSI_FCS_INFO_STRING           ""



/* NOTE: This file includes convenience preprocessor macro definitions of all the
 * GSI 4.0 API functions, with the "gsi_" prefix stripped.   If you do not want
 * these definitions, you can define the preprocessor macro "__GENSYM_NOALIAS__"
 * before including gsi_main.h in your source files.
 */

#ifndef __GENSYM_NOALIAS__

/*--------------------------------------------------------------------------*/
/*			Alias and convenience macros                        */
/*--------------------------------------------------------------------------*/
#define gsi_make_rpc_args(numargs)	gsi_make_items(numargs)
#define gsi_reclaim_rpc_args(numargs)	gsi_reclaim_items(numargs)
#define is_array_type(type)		((type & 0x30) == 0x10)
#define is_list_type(type)		((type & 0x30) == 0x20)
#define is_simple_value_type(type)	((type>=GSI_INTEGER_TAG)&&(type<=GSI_FLOAT64_TAG))
#define is_compound_value_type(type)    ((type==GSI_SEQUENCE_TAG)||(type==GSI_STRUCTURE_TAG))
#define is_value_type(type)             (is_simple_value_type(type)||is_compound_value_type(type))
#define current_context			gsi_current_context()

/*--------------------------------------------------------------------------*/
/*			Backwards compatibility macros                      */
/*--------------------------------------------------------------------------*/
#define value_of(x)	 gsi_item_of_registered_item(x)
#define set_value(x,y)	 gsi_simple_content_copy(x,y)
#define obj_of(x)	 x
#define attr_of(x)	 gsi_item_of_attr(x)
#define set_attr(x,y)	 gsi_simple_content_copy(x,y)

/*--------------------------------------------------------------------------*/
/*			 Prefix eliminating macros                          */
/*--------------------------------------------------------------------------*/

#define context_user_data_type    gsi_context_user_data_type
#define item_user_data_type       gsi_item_user_data_type
#define symbol_user_data_type     gsi_symbol_user_data_type
#define call_identifier_type      gsi_call_identifier_type
#define function_handle_type      gsi_function_handle_type
#define procedure_user_data_type  gsi_procedure_user_data_type
#define procedure_identifier_type gsi_procedure_user_data_type

#define user_watchdog_function_type gsi_watchdog_function_type

#define VOID_INDEX	     GSI_VOID_INDEX
#define CALL_HANDLE_OF_START GSI_CALL_HANDLE_OF_START

#define NULL_TAG		GSI_NULL_TAG
#define INTEGER_TAG		GSI_INTEGER_TAG
#define LONG_TAG		GSI_LONG_TAG
#define INT64_TAG		GSI_INT64_TAG /* old name */
#define SYMBOL_TAG		GSI_SYMBOL_TAG
#define STRING_TAG		GSI_STRING_TAG
#define LOGICAL_TAG		GSI_LOGICAL_TAG
#define FLOAT64_TAG		GSI_FLOAT64_TAG
#define UNSIGNED_SHORT_VECTOR_TAG GSI_UNSIGNED_SHORT_VECTOR_TAG
#define ITEM_TAG		GSI_ITEM_TAG
#define VALUE_TAG		GSI_VALUE_TAG
#define HANDLE_TAG		GSI_HANDLE_TAG
#define QUANTITY_TAG            GSI_QUANTITY_TAG
#define INTEGER_ARRAY_TAG	GSI_INTEGER_ARRAY_TAG
#define SYMBOL_ARRAY_TAG	GSI_SYMBOL_ARRAY_TAG
#define STRING_ARRAY_TAG	GSI_STRING_ARRAY_TAG
#define LOGICAL_ARRAY_TAG	GSI_LOGICAL_ARRAY_TAG
#define FLOAT64_ARRAY_TAG	GSI_FLOAT64_ARRAY_TAG
#define ITEM_ARRAY_TAG		GSI_ITEM_ARRAY_TAG
#define VALUE_ARRAY_TAG		GSI_VALUE_ARRAY_TAG
#define INTEGER_LIST_TAG	GSI_INTEGER_LIST_TAG
#define SYMBOL_LIST_TAG		GSI_SYMBOL_LIST_TAG
#define STRING_LIST_TAG		GSI_STRING_LIST_TAG
#define LOGICAL_LIST_TAG	GSI_LOGICAL_LIST_TAG
#define FLOAT64_LIST_TAG	GSI_FLOAT64_LIST_TAG
#define ITEM_LIST_TAG		GSI_ITEM_LIST_TAG
#define VALUE_LIST_TAG		GSI_VALUE_LIST_TAG
#define SEQUENCE_TAG            GSI_SEQUENCE_TAG
#define STRUCTURE_TAG           GSI_STRUCTURE_TAG
#define ITEM_OR_VALUE_ARRAY_TAG GSI_ITEM_OR_VALUE_ARRAY_TAG
#define ITEM_OR_VALUE_LIST_TAG  GSI_ITEM_OR_VALUE_LIST_TAG
#define QUANTITY_ARRAY_TAG      GSI_QUANTITY_ARRAY_TAG
#define QUANTITY_LIST_TAG       GSI_QUANTITY_LIST_TAG

#define context_socket(c)		  gsi_context_socket(c)
#define listener_socket()		  gsi_listener_socket()
#define registration_of(x,y)		  gsi_registration_of(x,y)
#define user_data_of(x)			  gsi_user_data_of(x)
#define set_user_data(x,y  )		  gsi_set_user_data(x,y)
#define handle_of(x)			  gsi_handle_of(x)
#define interval_of(x)			  gsi_interval_of(x)
#define status_of(x)			  gsi_status_of(x)
#define identifying_attr_of(x,y)	  gsi_item_of_identifying_attr_of(x,y)
#define set_handle(x,y)			  gsi_set_handle(x,y)
#define set_interval(x,y)		  gsi_set_interval(x,y)
#define set_status(x,y)			  gsi_set_status(x,y)
#define timestamp_of(x)			  gsi_timestamp_of(x)
#define int_of(x)			  gsi_int_of(x)
#define long_of(x)			  gsi_long_of(x)
#define ulong_of(x)			  gsi_ulong_of(x)
#define flt_of(x)			  gsi_flt_of(x)
#define log_of(x)			  gsi_log_of(x)
#define str_of(x)			  gsi_str_of(x)
#define usv_of(x)			  gsi_usv_of(x)
#define sym_of(x)			  gsi_sym_of(x)
#define usv_length_of(x)		  gsi_usv_length_of(x)
#define handle_of(x)			  gsi_handle_of(x)
#define int_array_of(x)			  gsi_int_array_of(x)
#define flt_array_of(x)			  gsi_flt_array_of(x)
#define log_array_of(x)			  gsi_log_array_of(x)
#define sym_array_of(x)			  gsi_sym_array_of(x)
#define str_array_of(x)			  gsi_str_array_of(x)
#define int_list_of(x)			  gsi_int_list_of(x)
#define flt_list_of(x)			  gsi_flt_list_of(x)
#define log_list_of(x)			  gsi_log_list_of(x)
#define sym_list_of(x)			  gsi_sym_list_of(x)
#define str_list_of(x)			  gsi_str_list_of(x)
#define elements_of(x)			  gsi_elements_of(x)
#define set_timestamp(x,y)		  gsi_set_timestamp(x,y)
#define set_int(x,y)			  gsi_set_int(x,y)
#define set_long(x,y)			  gsi_set_long(x,y)
#define set_ulong(x,y)			  gsi_set_ulong(x,y)
#define set_flt(x,y)			  gsi_set_flt(x,y)
#define set_log(x,y)			  gsi_set_log(x,y)
#define set_str(x,y)			  gsi_set_str(x,y)
#define set_usv(x,y,l)			  gsi_set_usv(x,y,l)
#define set_sym(x,y)			  gsi_set_sym(x,y)
#define set_handle(x,y)			  gsi_set_handle(x,y)
#define set_int_array(x,y,z)		  gsi_set_int_array(x,y,z)
#define set_flt_array(x,y,z)		  gsi_set_flt_array(x,y,z)
#define set_log_array(x,y,z)		  gsi_set_log_array(x,y,z)
#define set_sym_array(x,y,z)		  gsi_set_sym_array(x,y,z)
#define set_str_array(x,y,z)		  gsi_set_str_array(x,y,z)
#define set_int_list(x,y,z)		  gsi_set_int_list(x,y,z)
#define set_flt_list(x,y,z)		  gsi_set_flt_list(x,y,z)
#define set_log_list(x,y,z)		  gsi_set_log_list(x,y,z)
#define set_sym_list(x,y,z)		  gsi_set_sym_list(x,y,z)
#define set_str_list(x,y,z)		  gsi_set_str_list(x,y,z)
#define set_elements(x,y,z,w)		  gsi_set_elements(x,y,z,w)
#define type_of(x)			  gsi_type_of(x)
#define class_type_of(x)		  gsi_class_type_of(x)
#define history_type_of(x)		  gsi_history_type_of(x)
#define name_of(x)			  gsi_name_of(x)
#define class_name_of(x)		  gsi_class_name_of(x)
#define element_count_of(x)		  gsi_element_count_of(x)
#define attr_count_of(x)		  gsi_attr_count_of(x)
#define attrs_of(x)			  gsi_attrs_of(x)
#define attr_by_name(x,y)		  gsi_attr_by_name(x,y)
#define history_count_of(x)		  gsi_history_count_of(x)
#define extract_history(w,x,y,z)	  gsi_extract_history(w,x,y,z)
#define extract_history_spec(w,x,y,z)	  gsi_extract_history_spec(w,x,y,z)
#define set_type(x,y)			  gsi_set_type(x,y)
#define set_class_type(x,y)		  gsi_set_class_type(x,y)
#define set_history_type(x,y)		  gsi_set_history_type(x,y)
#define set_name(x,y)			  gsi_set_name(x,y)
#define set_class_name(x,y)		  gsi_set_class_name(x,y)
#define set_element_count(x,y)		  gsi_set_element_count(x,y)
#define set_attr_count(x,y)		  gsi_set_attr_count(x,y)
#define set_attrs(x,y,z)		  gsi_set_attrs(x,y,z)
#define set_attr_by_name(x,y,z)		  gsi_set_attr_by_name(x,y,z)
#define set_history(s,t,u,v,w,x,y,z)	  gsi_set_history(s,t,u,v,w,x,y,z)
#define attr_name_of(x)			  gsi_attr_name_of(x)
#define item_of_attr(x)			  gsi_item_of_attr(x)
#define unqualified_attr_name_of(x)	  gsi_unqualified_attr_name_of(x)
#define class_qualifier_of(x)		  gsi_class_qualifier_of(x)
#define attr_name_is_qualified(x)	  gsi_attr_name_is_qualified(x)
#define set_attr_name(x,y)		  gsi_set_attr_name(x,y)
#define set_item_of_attr(x,y)		  gsi_set_item_of_attr(x,y)
#define set_unqualified_attr_name(x,y)	  gsi_set_unqualified_attr_name(x,y)
#define set_class_qualifier(x,y)	  gsi_set_class_qualifier(x,y)
#define decode_timestamp(t,u,v,w,x,y,z)	  gsi_decode_timestamp(t,u,v,w,x,y,z)
#define encode_timestamp(u,v,w,x,y,z)	  gsi_encode_timestamp(u,v,w,x,y,z)
#define is_item(x)			  gsi_is_item(x)

#endif /* __GENSYM_NOALIAS__ */

/*--------------------------------------------------------------------------*/
/*			     GSI startup declarations                       */
/*--------------------------------------------------------------------------*/

extern int gsi_rpc_2_arg_receiver_fns;


#if defined(GSI_USE_WIDE_STRING_API)
#define GSI_SET_WIDE_STRING_OPTION gsi_set_option(GSI_WIDE_STRING_API);
#else
#define GSI_SET_WIDE_STRING_OPTION
#endif

#if defined(GSI_USE_USER_DATA_FOR_CALLBACKS)
#define GSI_SET_USER_DATA_FOR_CALLBACKS_OPTION gsi_set_option(GSI_USER_DATA_FOR_CALLBACKS);
#else
#define GSI_SET_USER_DATA_FOR_CALLBACKS_OPTION
#endif

/* this switch is automatically set by the DEC C compiler, */
/* if G floats are used at compile time.                   */
#if __G_FLOAT
#define GSI_SET_GFLOATS_OPTION gsi_set_option(GSI_USE_GFLOATS);
#else
#define GSI_SET_GFLOATS_OPTION
#endif

#if defined(GSI_USE_NON_C_CALLBACKS)
#define GSI_SET_NON_C_CALLBACKS_OPTION gsi_set_option(GSI_NON_C);
#else
#define GSI_SET_NON_C_CALLBACKS_OPTION
#endif

#if defined(GSI_USE_NEW_SYMBOL_API)
#define GSI_SET_NEW_SYMBOL_OPTION gsi_set_option(GSI_NEW_SYMBOL_API);
#else
#define GSI_SET_NEW_SYMBOL_OPTION
#endif

#define GSI_INITIALIZE_STANDARD_CALLBACKS \
  gsi_initialize_callbacks(gsi_name_of_gsi_set_up(),gsi_set_up, \
			   gsi_name_of_gsi_get_tcp_port(),gsi_get_tcp_port, \
			   gsi_name_of_gsi_initialize_context(),gsi_initialize_context, \
			   gsi_name_of_gsi_pause_context(),gsi_pause_context, \
			   gsi_name_of_gsi_resume_context(),gsi_resume_context, \
			   gsi_name_of_gsi_shutdown_context(),gsi_shutdown_context, \
			   gsi_name_of_gsi_receive_registration(),gsi_receive_registration, \
			   gsi_name_of_gsi_receive_deregistrations(),gsi_receive_deregistrations, \
			   gsi_name_of_gsi_g2_poll(),gsi_g2_poll, \
			   gsi_name_of_gsi_get_data(),gsi_get_data, \
			   gsi_name_of_gsi_set_data(),gsi_set_data, \
			   gsi_name_of_gsi_receive_message(),gsi_receive_message, \
			   (void *)NULL)

#if defined(GSI_USE_DLL)
#define GSI_INITIALIZE_DLL_CALLBACKS GSI_INITIALIZE_STANDARD_CALLBACKS
#else
#define GSI_INITIALIZE_DLL_CALLBACKS
#endif

#define GSI_SET_INCLUDE_FILE_VERSION \
  gsi_set_include_file_version(GSI_INCLUDE_MAJ_VER_NUM, \
			       GSI_INCLUDE_MIN_VER_NUM, \
			       GSI_INCLUDE_REV_VER_NUM);

#define GSI_SET_OPTIONS_FROM_COMPILE() \
  GSI_SET_INCLUDE_FILE_VERSION \
  GSI_SET_WIDE_STRING_OPTION \
  GSI_SET_USER_DATA_FOR_CALLBACKS_OPTION \
  GSI_SET_GFLOATS_OPTION \
  GSI_SET_NON_C_CALLBACKS_OPTION \
  GSI_SET_NEW_SYMBOL_OPTION \
  GSI_INITIALIZE_DLL_CALLBACKS

#ifdef	__cplusplus
}
#endif

#endif /* ifdef GSI_DEFINED */
