#ifndef _OSIPI_BRIDGE_H_
#define _OSIPI_BRIDGE_H_

#include "osipi.h"

typedef struct serverInfo { char    *srvrName ;
                            long    nrPts ;
                            short   fLoggedIn ;
                            short   fUser ;
                            char    *user ;
                            short   fPW ;
                            char    *password ;
                            short   errRptd ;       } serverInfo ;

extern CtxCfg                   CtxCfgs[] ;
extern function_handle_type     ErrorHandle[];
extern short                    deReging ;
extern int                      gNrServers ;
extern serverInfo               *gServer ;
extern int                      gCurSrvr ;
extern int                      *pNrPIPts ;
extern gsi_int                  erLkUp[] ;

/* Prototypes: */
/* ----------- */
extern void gsi_error_handler(gsi_int context, gsi_int code, gsi_char *msg) ;
static void rpc_get_pisys_time(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_name_vector(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_get_interp_values(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_get_property(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_get_timed_values(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_set_debug_mode(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_shutdown(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_read(gsi_item *args, gsi_int count, gsi_int call_index) ;
static void rpc_trans_stat(gsi_item *args, gsi_int count, gsi_int call_index) ;

int         exPtCount(long lContext) ;
int         GetMatchIndex (int srvNr, long point, exInfo **ppInfo) ;
int         init_context(CtxCfg *systatus) ;
int         pi_get_timed_values(gsi_item *args, gsi_int count, unsigned short arcmode,
                                gsi_int call_index) ;
void        removeExRptInfoFor(GsiPiPointStruct *pi_ptr) ;
int         SendData (PI_EVENT *pSnap, exInfo *pInfo) ;
int         UpdateEventList(GsiPiPointStruct *pi_ptr, int *pTellPI) ;

/* defines for rpc_set_debug_mode */
/* ------------------------------ */
#define MODEPOS  0
#define MAXDEBUGMODEARGS 2
#define RETCODEPOS 0
#define RETMSGPOS 1
#define ONSYM "ON"
#define OFFSYM "OFF"

#endif
