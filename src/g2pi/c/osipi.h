/* This header file contains the pi structure and constant definitions */

/* 6-4-93 : added change to systatus structure to include show_pitime option. pvl */
/* 9-19-93: added #defines for determining which archive mode to use */

/* 10-4-94: changed #define for maxarctiemvals to 1001 per request of Brent A. */
/* 
** 13-4-95  P.Hill   Added STRSZ because it is no longer in GSI3.1 and up
**                   For upgrade to GSI3.2, removed the macros used for 
**                   accessing elements of GSI structures  
*/
#ifndef _OSIPI_H_
#define _OSIPI_H_

#include "piapix.h"
#include "gsi_main.h"

#define STRSZ        256
#define MAXNODENAME   10
#define MAXFILENAME   24

/* Define the system size parameters */
#define MAXEVMPOINTS  2500
#define MAXCONTEXTS   49

#define MAXPOINTSPERCALL 200   /* get data argument */
#define MAXARCTIMEVALS   1001  /* timestamped historical values per call */
#define CHARSPERTAG      12    /* used to be defined in "piparams.h" */
#define CHARSPERLONGTAG  80    /* Used if tag greater than 12 */
#define CHARSPERDIGSTATE  12   /* used to be defined in "piparams.h" */

#define NO_INDEX 0

#define FREE_POINT 0

#define MAXINITARGS  10
#ifndef ARGLEN
    #define ARGLEN 20
#endif
#ifndef MAXKEYLEN
    #define MAXKEYLEN 4
#endif


#define PIB_BAD         128
#define PIB_BADSRV      262146
#define PIB_BADVAL      262147
#define PIB_BADTYPE     262148
#define PIB_NODEF       262150
#define PIB_NOSUCHTAG   262151
#define PIB_TOOLONG     262152

typedef struct {
  char key;
  char arg[ARGLEN+1];
} ARG_ELEMENT_STRUCT;



typedef long    icp_int;

typedef struct {
    icp_int year;
    icp_int month;
    icp_int day;
    icp_int hour;
    icp_int minute;
    icp_int second;
} icp_timestamp_type;

#define NUMERRARGS  2
#define ERRCD_POS   0
#define ERRMSG_POS  1

/* Return codes: */
/* ------------- */
#define GSI_SUCCESS   1L    /* Return upon successful function completion. */
#define GSI_FAILURE   0L    /* Return upon failed function completion. */
#define GSI_FAIL      GSI_FAILURE

/* define the attribute name in G2 for the last recorded timestamp */
/* define the macros to be used in the case statement after the init string 
   has been parsed. The CASE_ENTRY macro assumes that a character is passed as A,
   which is used as the case clause; a function is passed as B which is used to 
   evaluate the contncts of the string D which is the argument. And the result is
   placed in C which is some element of some structure, usually the CtxCfg
   structure. 
*/
#define CASE_PREENTRY(A)  case A:
#define CASE_ENTRY(A,B,C,D,E)  case A : \
   status = B (D, &temp_val); \
   if (status != GSI_SUCCESS){ \
       ret_status = GSI_FAIL;\
       _snprintf(errorMsg, ERMSGSZ, "Invalid parameter for %c option.",  init_args[i].key); \
       LOGMSG(LLEVHIGH, errorMsg) ;\
       _snprintf(errorMsg, ERMSGSZ, "(Configuration of %s failed.)",  E); \
       LOGMSG(LLEVHIGH, errorMsg) ;\
   } else {\
     C = temp_val; }\
   break


/* Define all of the macros used for accessing elements of the corresponding object */
#define BuildPiPoint(A,B,C) C = (A *)malloc(sizeof(A) * B)


/* Define elements for returning the object index */
#define NUMPIVECTORS 5
#define INDEX_POS  0
#define OBJ_INDEX_SYMBOL "OBJECT-INDEX"
#define PIID_POS   1
#define PIID_SYMBOL      "PI-POINT"
#define LRPT_POS   2
#define LRPT_ATTRIBUTE   "LAST-RECORDED-PI-TIME"
#define AUXCOD_POS 3
#define AUXCOD_ATTR      "AUX-CODE"
#define AUXMSG_POS 4
#define AUXMSG_ATTR      "AUX-MSG"


/* Basic rpc argument locations */
#define RET_ARGS 2
#define CODE_POS 0
#define MSG_POS  1

/***** define the timestamp information ******/
#define PITIMELEN 19
#define TIMESIZE 6
#define PI_YEAR_POS   2
#define PI_MONTH_POS  0
#define PI_DAY_POS    1
#define PI_HOUR_POS   3
#define PI_MINUTE_POS  4
#define PI_SECOND_POS  5

/* add for getting the pi time, in rpc_get_pisys_time */
#define TIME_POS    MSG_POS + 1
#define PIYR_POS    MSG_POS + 2
#define PIMON_POS   MSG_POS + 3
#define PIDY_POS    MSG_POS + 4
#define PIHR_POS    MSG_POS + 5
#define PIMIN_POS   MSG_POS + 6
#define PISEC_POS   MSG_POS + 7
#define MAXSYSRETARGS PISEC_POS + 1

/* and for conversions */
#define RPC_RET_SIZE 2
#define DATE_SIZE    6

#define CV_MONTH_POS 0
#define CV_DAY_POS   1
#define CV_YEAR_POS 2
#define CV_HOUR_POS 3
#define CV_MINUTE_POS 4
#define CV_SECOND_POS 5
#define CV_CODE_POS   6
#define CV_MSG_POS    7

#define NO_CODE 0
#define MAXVECTORARGS  5

/* Define index arguments - def_obj */
#define REAL_TYPE 'R'
#define INTEGER_TYPE 'I'
#define DIGITAL_TYPE 'D'

#define FLOAT_DEFAULT    0.0
#define INTEGER_DEFAULT  0
#define SYMBOL_DEFAULT   "G2"


/* define local values */
#define NO_OBJECT 0

/* define Timestamp vector information */
#define TIMESTAMPNAME   "TIMEVECTOR"
#define TV_SIZE         3
#define TV_POS          0
#define MAXNAMES        2

#define INVALID_VECTORNAME   -1


/* define values for getting timestamped (historical) values */
#define OBJECT_POS 0
#define FROM_POS   1
#define TO_POS     2
#define NUMBER_POS  3

#define INVALID_OBJECT   -2
#define INVALID_ARGUMENT -3
#define INVALID_TIME     -4
#define PIAPI_ERROR      -5
#define STARTPOS          0

#define NO_PI_ERROR       0
#define BAD_PI_TIME       0

#define DIG_STAT_ERROR   1000    /* starting point for digita state errors */

/* define the size of the timestamp vector */
#define NUMBER_VECTORS    1        /* only 1 defined for now */



/* define the modes of operation for the rpc to read blocks of data */
#define ARCSEQU_MODE 1
#define ARCINTERP_MODE ARCSEQU_MODE + 1



/* Default context behavior */

/* ------------------------ */

#define DEF_DO_ECHO         FALSE
#define DEF_DO_EXCEPTION    FALSE
#define DEF_DO_TIMESTAMP    FALSE

/* define the context data structure */
typedef struct {    short   alive ;
                    short   do_echo;
                    short   log_level ;
                    short   log_to_file ;
                    short   log_to_screen ;
                    short   log_to_mb ;
                    short   log_to_g2 ;
                    short   log_to_pi ;
                    short   do_exception;
                    short   do_timestamp;   } CtxCfg;

typedef enum { pipUnknown, pipInt, pipFlt, pipDig, pipTxt, pipTim } PIPointType ;


/* define the data structure for pi points */
typedef struct {    long        pt_id;
                    PIPointType pi_type;
                    int         pi_srv ;
                    int         pt_loc;
                    long        pt_slot;
                    long        status;
                    int         g2_atianr ;
                    gsi_int     g2_type ;
                    gsi_int     g2_handle;   } GsiPiPointStruct;

/* define the data structure used for string representation of digital tags */
typedef struct d1 {
  char   digstate[CHARSPERDIGSTATE +1];
  struct d1 *next;
} DIG_STRUCT;

/* Structure for PI API info */
typedef struct {
    char    funct_name[20];
    long    pi_status;
    long    pi_point;
    long    object_ind;
    char    arguments[256];
} PIAPI_STRUCT;


/* Structure for storing information about points/variables */
/* being updated with exception reporting                   */
/* -------------------------------------------------------- */
struct exInfo ;
typedef struct exInfo   {   long            piPt ;
                            int             piSrv ;
                            PIPointType     piType ;
                            gsi_int         varContext ;
                            gsi_int         varHandle ;
                            gsi_int         varType ;
							struct exInfo   *nextPI ;
                            struct exInfo   *nextVar ; } exInfo ;

#if defined(__ALPHA)
#if defined(CC$gfloat)
#define flt_of(o_v_t_p) (o_v_t_p->p_value.float_p)
#define set_flt(o_v_t_p,dbl) (o_v_t_p->p_value.float_p = dbl)
#endif
#endif
#endif
