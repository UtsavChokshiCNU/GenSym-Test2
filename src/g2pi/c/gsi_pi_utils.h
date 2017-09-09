/*  ------------- */
/* gsi_pi_utils.h */
/*  ------------- */

#ifndef _GSI_PI_UTILS_H_
#define _GSI_PI_UTILS_H_

#include "osipi.h"
#include "gsi_main.h"

extern char *tfs ;      /* Time Format String */
extern char timebuf[] ;

                    /* yyyy-mon-dd hh:mm:ss */
#define DEF_TFS     "%Y-%m-%d %H:%M:%S"     
#define MAXNOWLEN  30   
#define NOW timestamp(tfs, timebuf, MAXNOWLEN)

#define POLL_RPT_FREQ   60

#define SRV_DAT_FILE "PISRVRS.DAT"
#define G2P_ENV_VAR  "G2PSL"

/* Prototypes: */
/* ----------- */
void    badvalue_handler(long code, unsigned short index) ;
void    build_timestamp(long *pitime, icp_timestamp_type *date) ;
void    build_timestamp_gsi5(long *pitime, gsi_registered_item date, char *sTimetext) ;
int     check_object(gsi_item *object,unsigned short *type,int *srvNr, long *pi_point) ;
int     check_yesno(char *arg, short *value) ;
int     conv_rpc2pi_time(gsi_item *rpc_time, long *pi_time) ;
char    *decodedPW(char *decMe) ;
int     get_init_pi_point(gsi_item ret_arg, gsi_registration *ptrRegistration,
                          long *pt, char *type) ;
int     getNextServerRec(char *buffer, long bufsz, FILE *fpint);
int     get_pi_error_message(long code, unsigned short index) ;
int     gleich(char *str1, char *str2) ;

int     loadServerInfo() ;
int     NotTooBig(PITIMESTAMP *ts) ;
int     osi_parse_init(char *init_str, ARG_ELEMENT_STRUCT *init_args, unsigned short str_len) ;
char    *password() ;
void    piapi_error(PIAPI_STRUCT *api_err ) ;
int     PIPointTypeOf(int srvNr, long pPIPtNr, enum PIPointType *piType) ;
char    PITypeToLet(enum PIPointType type) ;
void    PIValToVar(GsiPiPointStruct *pi_ptr, PI_EVENT *pVal, gsi_registered_item *ptr_regit) ;
void    put_nothing (long *pt_id, float *rval, long *istat, long *time, long *error) ;
int     ReadPIAttr(int piSrvNr, long piPtNr, gsi_int attrCode, gsi_attr ToG2, int firstCall) ;
int     ReadPIVal(GsiPiPointStruct *pPInfo, PI_EVENT *pVals) ;
void    RetrievePIAttrs(gsi_registered_item regItem, gsi_int *pNrAttrsBack, gsi_attr **ppToAttrs) ;
long    switchToServer(int dsrSrv) ;
char    *timestamp (char *format, char *result, long length) ;
char    *timeToStr(PITIMESTAMP *pts) ;
char    *upper_case(char *theString) ;
long    v4round(double dblIn) ;
void    zap(char *ppw) ;


#endif
