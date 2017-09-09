#include <winsock2.h>
#include "gsi_main.h"
#include "osipi_bridge.h"


/* Return a text list list with the names of the known servers */
/* =========================================================== */
static void rpc_get_links(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *retVal = gsi_make_items(1) ;
    char        **wkar = NULL ;
    int         i ;

    gsi_set_type(*retVal, GSI_STRING_LIST_TAG) ;
    if (gNrServers > 0)
    {
        wkar = (char **)malloc(gNrServers * sizeof(char *)) ;
        if (wkar != NULL)
            for (i=0 ; i < gNrServers ; i++)
                wkar[i] = gServer[i].srvrName ;
    }
    gsi_set_str_list(*retVal, wkar, gNrServers) ;
    if (wkar != NULL) free(wkar) ;
    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
}


static void rpc_get_items(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *retVal = gsi_make_items(1) ;
    char        *fake[] = { "@ version" } ;

    gsi_set_type(*retVal, GSI_STRING_LIST_TAG) ;
    gsi_set_str_list(*retVal, fake, 1) ;
    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
}

static void rpc_get_full_path(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *retVal = gsi_make_items(1) ;

    gsi_set_type(*retVal, GSI_STRING_TAG) ;
    gsi_set_str(*retVal, "@ version") ;
    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
}

static void rpc_get_update_rate(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *retVal = gsi_make_items(1) ;

    gsi_set_flt(*retVal, -1.0) ;
    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
}

static void rpc_get_statistics(gsi_item *args, gsi_int count, gsi_int call_index)
{
    int         i ;
    gsi_item    *retVal = gsi_make_items(1) ;
    gsi_attr    *pAttrs = gsi_make_attrs_with_items(8) ;

    gsi_set_type(*retVal, GSI_STRUCTURE_TAG) ;
    
    gsi_set_attr_name(pAttrs[0],"SENT");
    gsi_set_attr_name(pAttrs[1],"RECEIVED");
    gsi_set_attr_name(pAttrs[2],"RETRIED");
    gsi_set_attr_name(pAttrs[3],"FAILED");
    gsi_set_attr_name(pAttrs[4],"OVERRUN");
    gsi_set_attr_name(pAttrs[5],"TIMED-OUT");
    gsi_set_attr_name(pAttrs[6],"SPARE1");
    gsi_set_attr_name(pAttrs[7],"SPARE2");

    for (i=0; i<8; i++)
        gsi_set_int(pAttrs[i],-1) ;

    gsi_set_attrs(*retVal, pAttrs, 8) ;

    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
    gsi_reclaim_attrs(pAttrs) ;
}

static void rpc_get_data_type(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *retVal = gsi_make_items(1) ;

    gsi_set_int(*retVal, 0) ;
    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
}

static void rpc_get_access_rights(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *retVal = gsi_make_items(1) ;

    gsi_set_int(*retVal, 3) ;
    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
}

static void rpc_is_null(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *retVal = gsi_make_items(1) ;

    gsi_set_type(*retVal, GSI_LOGICAL_TAG) ;
    gsi_set_log(*retVal, GSI_FALSE) ;

    gsi_rpc_return_values(retVal, 1, call_index, gsi_current_context());
    gsi_reclaim_items(retVal);
}


void registerUndocumentedRPCs()
{
    gsi_rpc_declare_local(rpc_get_links,            "GET-LINKS" );
    gsi_rpc_declare_local(rpc_get_items,            "GET-ITEMS" );
    gsi_rpc_declare_local(rpc_get_full_path,        "GET-FULL-PATH" );
    gsi_rpc_declare_local(rpc_get_update_rate,      "GET-UPDATE-RATE" );
    gsi_rpc_declare_local(rpc_get_statistics,       "GET-STATISTICS" );
    gsi_rpc_declare_local(rpc_get_data_type,        "GET-DATA-TYPE" );
    gsi_rpc_declare_local(rpc_get_access_rights,    "GET-ACCESS-RIGHTS" );
    gsi_rpc_declare_local(rpc_is_null,              "IS-NULL" );
}

