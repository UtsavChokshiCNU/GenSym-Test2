
/* **********************************************************************

	file : gsi_icp.h

	This file supercedes gsi_types.h and gsi_defines.h. It contains
	the macro definitions for typedefs and #defines.

 **********************************************************************/



#define MAJ_VER_NUM 3L      /* defines behavior of gsi base */
#define MIN_VER_NUM 0L      /* must match printout on startup */
#define DELTA_REV_NUM 0L    /* Revs reflect bug fixes */

/*
-- New name for GSIMAIN is START_GSI
*/
void gsimain();
#define start_gsi(count, cmd_args) gsimain(count, cmd_args)



#define NULL_BYTE 		0L
#define ICPMAXSTRSZ		256L
#define GSIMAXSTRSZ		ICPMAXSTRSZ
#define STRSZ                   ICPMAXSTRSZ
#define SYMBSZ 			64L
#define NULCHAR			'\0'
#define NO_ERR                  0L

#define MAXARRAYSZ 		100L
#define READMBXCYCLE            25L /* check the mbx every 25 loops */
#define INITCYCLE               0L


#define NULL_PTR                0L
#define NULL_STR                '\0'
#define NULL_LEN                0L
#define NO_SEL_PORT             0L

#define LEN_POS	 		2L
#define NULL_TAG 		0L
#define INTEGER_TAG		1L
#define FLOAT_TAG		2L
#define SYMBOL_TAG		3L
#define STRING_TAG		4L
#define CHAR_TAG                4L
#define LOGICAL_TAG             5L
#define FLOAT64_TAG             6L
#define LONGSTR_TAG             7L

#define GSI_TRUE                1000L
#define GSI_FALSE               -1000L


#define PROC_WAITING            0L
#define PROC_INIT	        1L
#define PROC_OK                 2L
#define PROC_PAUSE              3L
#define PROC_ERROR              4L

#define GSI_SUCCESS             1
#define GSI_FAIL                0

#ifndef max
#define max(A, B) ((A) > (B) ? (A) : (B))
#endif

#ifndef min
#define min(A, B) ((A) > (B) ? (B) : (A))
#endif

#ifndef TRUE
#define TRUE 1L
#endif

#ifndef FALSE
#define FALSE 0L
#endif

#define NOT_SINGLE 0L
#define SINGLE 1L



/* new commands from the c control stuff */

/* control identifiers */
#define   SYSTEM_IS_RUNNING               1L
#define   SYSTEM_IS_PAUSED                2L
#define   SYSTEM_IS_RESET                 3L


#define   PAUSE_G2                        1L
#define   RESUME_G2                       2L
#define   RESET_G2                        3L
#define   START_G2                        4L
#define   RESTART_G2                      5L
#define   SHUTDOWN_G2                     6L
#define   MERGE_G2                        7L
#define   LOAD_KB                         8L
#define   SAVE_KB                         9L
#define   LOAD_C_FILE                     10L
#define   LOAD_FORTRAN_FILE               11L
#define   LOAD_ATTRIBUTES_FILE            12L


/*
-- Icp Mode operational Modifiers
*/
#define   ICP_STRING_CHECK        0x0001L
#define   ICP_ONE_CYCLE           0x0002L
#define   ICP_FORK_GSI            0x0004L
#define   ICP_USE_RPCS            0x0008L
#define   ICP_EXT_PROC            0x0010L
#define   ICP_USE_ADA             0x0020L
#define   ICP_NON_C               0x0020L
#define   ICP_RPC_ARRARGS         0x0040L
#define   ICP_SUPPRESS_OUTPUT     0x0080L
#define   ICP_VAX_GFLOATS         0x0100L
#define   ICP_FREE_OBJ_PTRS       0x0200L
#define   ICP_DISABLE_LISTENERS   0x0400L


typedef struct {
  char char_1;
  char char_2;
} ICP_CHARS;

typedef union {
  unsigned short icp_int;
  ICP_CHARS      icp_char;
} ICP_BYTE;



typedef union {
  long int null;
  long int integer_p;
  long int logical_p;
  double float_p;
  char *longstr_p;
  char symbol_p[SYMBSZ];
  char string_p[STRSZ];
  } TEMP_VALUE;

typedef union {
  long int null;
  long int integer_p;
  long int logical_p;
  double float_p;
  char *symbol_p;
  char *string_p;
  } ICP_VALUE;

typedef struct {
   unsigned short p_type;
   TEMP_VALUE p_value;
} TEMP_PARAM;

typedef struct {
   unsigned short p_type;
   ICP_VALUE p_value;
} ICP_PARAM;

typedef struct {
   short int short_1;
   short int short_2;
} SHORT_STRUCT;

typedef union {
   long icp_long_p;
   SHORT_STRUCT shorts_p;
} ICP_LONG;

typedef struct {
  unsigned short obj_index;
  unsigned short type;         /* gensym internal use only */
  ICP_PARAM param_1;
  ICP_PARAM param_2;
  ICP_PARAM param_3;
  ICP_PARAM param_4;
  ICP_PARAM param_5;
  ICP_PARAM param_6;
  short int interval;
  ICP_PARAM value;            /* value.p_value.p_type for external use */
  } USER_ARG_TYPE;

typedef struct {
  unsigned short obj_index;
  TEMP_PARAM param_1;
  TEMP_PARAM param_2;
  TEMP_PARAM param_3;
  TEMP_PARAM param_4;
  TEMP_PARAM param_5;
  TEMP_PARAM param_6;
  short int interval;
  TEMP_PARAM value;
 } ICP_ARG_TYPE;

typedef struct {
  USER_ARG_TYPE *obj_ptr;
  union {
	unsigned long user_long;
	char *user_ptr;
	}user_def;
  short int tag;
  } CORR_OBJ_TYPE;



/* We may want to include a macro for the aformentioned structue that would
   allow users to easily specify the pointer that they will want to change.
   i.e. GSI_OBJ_PTRS[new_ptr->obj_ptr->obj_index].user_def.user_ptr;

	These are now obsolete !!!! 9/30/91 pvl
*/
#define MACgetobjptr(A) 	GSI_OBJ_PTRS[A->obj_index].obj_ptr
#define MACgetindexptr(A) 	GSI_OBJ_PTRS[A].obj_ptr
#define MACgetusrptr(A) 	GSI_OBJ_PTRS[A->obj_index].user_def.user_ptr
#define MACgetobjindex(A) 	A->obj_index
#define MACgetobjtype(A) 	GSI_OBJ_PTRS[A].obj_ptr->value.p_type
#define MACgetobjflt(A) 	GSI_OBJ_PTRS[A].obj_ptr->value.p_value.float_p
#define MACgetobjsym(A) 	GSI_OBJ_PTRS[A].obj_ptr->value.p_value.symbol_p
#define MACgetobjstr(A) 	GSI_OBJ_PTRS[A].obj_ptr->value.p_value.string_p
#define MACgetobjint(A) 	GSI_OBJ_PTRS[A].obj_ptr->value.p_value.integer_p
#define MACsetintstat(A) 	(*EXT_STATUS=A)


#define EvalDecConn(A,B) eval_stub(A,B)  /* modify for later use */
/*#define allow_ext_proc() gsi_space()*/  /* comment out for later use */
#define ENABLE_EXT_PROC() *DO_EXT_PROC=TRUE

#define SetIcpMode(A) (IcpMode = IcpMode | A)
#define ResetIcpMode(A) (IcpMode = IcpMode & (~A))
#define TestIcpMode(A) (IcpMode & A)
#define SetMaxOpen(A) (GwMaxOpen=A)

typedef struct {
  unsigned short obj_index;
  unsigned short error_cd;
  unsigned short interval;
  ICP_PARAM value;
  } RET_ARG_TYPE;

typedef struct {
  unsigned short obj_index;
  unsigned short error_cd;
  unsigned short interval;
  TEMP_PARAM value;
  } TEMP_ARG_TYPE;

typedef struct {
  unsigned short year;
  unsigned short month;
  unsigned short day;
  unsigned short hour;
  unsigned short minute;
  unsigned short second;
  } TIMESTAMP;

typedef struct {
  char attribute[STRSZ];
  TEMP_PARAM value;
  } VECTOR_TYPE;

typedef struct {
  char attribute[STRSZ];
  unsigned char is_timed;
  TEMP_PARAM value;
  TIMESTAMP date;
  } T_VECTOR_TYPE;


typedef struct {
  unsigned short obj_index;
  unsigned short error_cd;
  unsigned short interval;
  TEMP_PARAM value;
  TIMESTAMP date;
  } TIME_ARG_TYPE;


typedef struct {
	unsigned short	data_length;
	unsigned char	data_type;
	unsigned char	data_class;
	char	*string_ptr;	
	} DESCRIPT_STRUCT;



/*
-- The following are aliases for the new access functions (see GW_GSI).
-- The intent is to better match naming conventions of G2 and common sense.
*/       
typedef TEMP_ARG_TYPE	obj_type;
typedef TEMP_PARAM	obj_value_type;
typedef USER_ARG_TYPE*	obj_def_type;
typedef ICP_PARAM 	obj_def_value_type;
typedef VECTOR_TYPE	attr_type;
typedef TEMP_PARAM	attr_value_type;
typedef TEMP_PARAM	rpc_arg_type;
typedef TIME_ARG_TYPE	timed_obj_type;
typedef T_VECTOR_TYPE	timed_attr_type;
typedef TIMESTAMP	time_stamp_type;

typedef unsigned long   user_def_type;

typedef unsigned short	obj_index_type,
			tag_type,
			status_type,
			interval_type;

typedef long		G2int_type,
			G2log_type;

typedef double		G2flt_type;

typedef char		G2sym_type,
			attr_name_type;

typedef char		G2str_type;
typedef unsigned char	boolean;

/*
-- MUST prototype the float return accessor...
*/
G2flt_type flt_of ();


/*
-- Alias name for GSI_TYPE_OF.  TYPE_OF produces name collisions...
*/
tag_type gsi_type_of();
#define type_of(x) gsi_type_of(x)



/*
-- should be the last section of the file
*/
#ifndef EXTERNS_DEFINED
extern CORR_OBJ_TYPE *GSI_OBJ_PTRS;
extern unsigned short *DO_EXT_PROC;
extern unsigned short *EXT_STATUS;
extern unsigned long IcpMode;
extern unsigned short GWMAXOPEN;
extern unsigned short GWMAXG2OBJS;
extern unsigned short GWMAXOBJS;
extern unsigned short CurrentContext;
extern unsigned short HIGH_WATER_MARK;
#define EXTERNS_DEFINED TRUE
#endif
