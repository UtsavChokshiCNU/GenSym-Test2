#if !defined(__OPC_RPCS_H__)
#define __OPC_RPCS_H__
#include "gsi_main.h"

/* RPC's */
/* ===== */
    static void rpc_opc_report_connection_status(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_getserverlist(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_getserverstats(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_getactualupdaterate(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_set_groupstate(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_set_qualityfilterlevel(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
	static void rpc_opc_writevqt(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_setbrowserfilter(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_setbrowserdatatype(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_setbrowserrights(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_getbrowserleaves(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
	static void rpc_opc_changebrowserposition(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
	static void rpc_opc_getitemid(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_browse(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_browsepart(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_getproperties(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_getbrowserbranches(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void rpc_opc_triggerdeviceread(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_set_tracelevel(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_tracestart(gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_tracestop (gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_trace_to_g2 (gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_trace_to_stdout (gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
    static void g2_opc_set_tracewithtime (gsi_item *rpc_args, gsi_int count, gsi_int call_index) ;
#endif
