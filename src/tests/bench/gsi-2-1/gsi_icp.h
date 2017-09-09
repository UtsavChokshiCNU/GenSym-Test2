
/* **********************************************************************

	file : gsi_icp.h

	This file supercedes gsi_types.h and gsi_defines.h. It contains
	the macro definitions for typedefs and #defines.

 **********************************************************************/


#define MAJ_VER_NUM 2      /* defines behavior of gsi base */
#define MIN_VER_NUM 1      /* must match printout on startup */
#define DELTA_VER_NUM 1
#define DELTA_REV_UNIT 0
#define DELTA_REV_NUM 0

#define NULL_BYTE 		0
#define ICPMAXSTRSZ		512
#define GSIMAXSTRSZ		ICPMAXSTRSZ	       /* 512 */
#define SYMBSZ 64
/*#define STRSZ 128*/
#define STRSZ                   256  /* needed to enlarge for sql ?512 */
#define NULCHAR '\0'
#define NO_ERR                  0

#define MAXARRAYSZ 		100
#define READMBXCYCLE            25 /* check the mbx every 25 loops */
#define INITCYCLE               0


#define NULL_PTR                0
#define NULL_STR                '\0'
#define NULL_LEN                0
#define NO_SEL_PORT             0
#define GENSYM_PORT_DEFAULT     22044

#define LEN_POS	 		2
#define NULL_TAG 		0
#define INTEGER_TAG		1
#define FLOAT_TAG		2
#define SYMBOL_TAG		3
#define STRING_TAG		4
#define CHAR_TAG                4
#define LOGICAL_TAG             5
#define FLOAT64_TAG             6

#define GSI_TRUE                1000
#define GSI_FALSE               -1000


#define PROC_WAITING            0
#define PROC_INIT	        1
#define PROC_OK                 2
#define PROC_PAUSE              3
#define PROC_ERROR              4

#define GSI_SUCCESS             1
#define GSI_FAIL                0


#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) > (B) ? (B) : (A))

#define TRUE 1
#define FALSE 0
#define NOT_SINGLE 0
#define SINGLE 1



/* new commands from the c control stuff */

/* control identifiers */
#define   SYSTEM_IS_RUNNING               1
#define   SYSTEM_IS_PAUSED                2
#define   SYSTEM_IS_RESET                 3


#define   PAUSE_G2                        1
#define   RESUME_G2                       2
#define   RESET_G2                        3
#define   START_G2                        4
#define   RESTART_G2                      5
#define   SHUTDOWN_G2                     6
#define   MERGE_G2                        7
#define   LOAD_KB                         8
#define   SAVE_KB                         9
#define   LOAD_C_FILE                     10
#define   LOAD_FORTRAN_FILE               11
#define   LOAD_ATTRIBUTES_FILE            12


/* Icp Mode operational Modifiers */
#define   ICP_STRING_CHECK        0x0001
#define   ICP_ONE_CYCLE           0x0002 
#define   ICP_FORK_GSI            0x0004
#define   ICP_USE_RPCS            0x0008
#define   ICP_EXT_PROC            0x0010
#define   ICP_USE_ADA             0x0020
#define   ICP_NON_C               0x0020
#define   ICP_RPC_ARRARGS         0x0040

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
  } CORR_OBJ_TYPE;

/* We may want to include a macro for the aformentioned structue that would 
   allow users to easily specify the pointer that they will want to change.
   i.e. GSI_OBJ_PTRS[new_ptr->obj_ptr->obj_index].user_def.user_ptr;
*/
#define MACgetobjptr(A) GSI_OBJ_PTRS[A->obj_index].obj_ptr
#define MACgetindexptr(A) GSI_OBJ_PTRS[A].obj_ptr
#define MACgetusrptr(A) GSI_OBJ_PTRS[A->obj_index].user_def.user_ptr
#define MACgetobjindex(A) A->obj_index
#define MACgetobjtype(A) GSI_OBJ_PTRS[A].obj_ptr->value.p_type
#define MACgetobjflt(A) GSI_OBJ_PTRS[A].obj_ptr->value.p_value.float_p
#define MACgetobjsym(A) GSI_OBJ_PTRS[A].obj_ptr->value.p_value.symbol_p
#define MACgetobjstr(A) GSI_OBJ_PTRS[A].obj_ptr->value.p_value.string_p
#define MACgetobjint(A) GSI_OBJ_PTRS[A].obj_ptr->value.p_value.integer_p
#define MACsetintstat(A) (*EXT_STATUS=A)

#define EvalDecConn(A,B) eval_stub(A,B)  /* modify for later use */
/*#define allow_ext_proc() gsi_space()*/  /* comment out for later use */
#define ENABLE_EXT_PROC *DO_EXT_PROC

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
 






