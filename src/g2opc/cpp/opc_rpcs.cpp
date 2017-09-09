#include "StdAfx.h"
#include <tchar.h>
#include <comcat.h>
#include "gsi_main.h"
#include "opc_rpcs.h"
#include "opc_log.h"
#include "opc_utils.h"


void gsi_set_up ()
{
    gsi_set_option(GSI_STRING_CHECK);
    gsi_set_option(GSI_NEW_SYMBOL_API) ;
    gsi_set_option(GSI_PROTECT_INNER_CALLS) ;
    GSI_SET_WIDE_STRING_OPTION 
    gsi_rpc_declare_local(rpc_opc_report_connection_status, (gsi_char*)_T("RPC-OPC-REPORT-CONNECTION-STATUS"));
    gsi_rpc_declare_local(rpc_opc_getserverlist,            (gsi_char*)_T("RPC-OPC-GETSERVERLIST"));
    gsi_rpc_declare_local(rpc_opc_getserverstats,           (gsi_char*)_T("RPC-OPC-GETSERVERSTATS")) ;
    gsi_rpc_declare_local(rpc_opc_getactualupdaterate,      (gsi_char*)_T("RPC-OPC-GETACTUALUPDATERATE")) ;
    gsi_rpc_declare_local(g2_opc_set_groupstate,            (gsi_char*)_T("G2-OPC-SET-GROUPSTATE")) ;
    gsi_rpc_declare_local(g2_opc_set_qualityfilterlevel,    (gsi_char*)_T("G2-OPC-SET-QUALITYFILTERLEVEL")) ;
    gsi_rpc_declare_local(rpc_opc_writevqt,                 (gsi_char*)_T("RPC-OPC-WRITEVQT")) ;
    gsi_rpc_declare_local(rpc_opc_setbrowserfilter,         (gsi_char*)_T("RPC-OPC-SETBROWSERFILTER")) ;
    gsi_rpc_declare_local(rpc_opc_triggerdeviceread,        (gsi_char*)_T("RPC-OPC-TRIGGERDEVICEREAD")) ;
    gsi_rpc_declare_local(rpc_opc_setbrowserdatatype,       (gsi_char*)_T("RPC-OPC-SETBROWSERDATATYPE")) ;
    gsi_rpc_declare_local(rpc_opc_setbrowserrights,         (gsi_char*)_T("RPC-OPC-SETBROWSERRIGHTS")) ;
    gsi_rpc_declare_local(rpc_opc_getbrowserleaves,         (gsi_char*)_T("RPC-OPC-GETBROWSERLEAVES")) ;
    gsi_rpc_declare_local(rpc_opc_getbrowserbranches,       (gsi_char*)_T("RPC-OPC-GETBROWSERBRANCHES")) ;
    gsi_rpc_declare_local(rpc_opc_changebrowserposition,    (gsi_char*)_T("RPC-OPC-CHANGEBROWSERPOSITION")) ;
    gsi_rpc_declare_local(rpc_opc_getitemid,                (gsi_char*)_T("RPC-OPC-GETITEMID")) ;
    gsi_rpc_declare_local(rpc_opc_getproperties,            (gsi_char*)_T("RPC-OPC-GETPROPERTIES")) ;
    gsi_rpc_declare_local(rpc_opc_browse,                   (gsi_char*)_T("RPC-OPC-BROWSE")) ;
    gsi_rpc_declare_local(rpc_opc_browsepart,               (gsi_char*)_T("RPC-OPC-BROWSEPART")) ;
    gsi_rpc_declare_local(g2_opc_set_tracelevel,            (gsi_char*)_T("G2-OPC-SET-TRACELEVEL"));
    gsi_rpc_declare_local(g2_opc_tracestart,                (gsi_char*)_T("G2-OPC-TRACESTART")) ;
    gsi_rpc_declare_local(g2_opc_tracestop,                 (gsi_char*)_T("G2-OPC-TRACESTOP")) ;
    gsi_rpc_declare_local(g2_opc_trace_to_g2,               (gsi_char*)_T("G2-OPC-TRACE-TO-G2")) ;
    gsi_rpc_declare_local(g2_opc_trace_to_stdout,           (gsi_char*)_T("G2-OPC-TRACE-TO-STDOUT")) ;
	gsi_rpc_declare_local(g2_opc_set_tracewithtime,         (gsi_char*)_T("G2-OPC-SET-TRACEWITHTIME")) ;
}



/* ========================================================================== */
/*                                                                            */
/*         Return symbol that will be stored in interface object to           */
/*                      reflect the connection status.                        */
/*                                                                            */
/* ========================================================================== */
static void rpc_opc_report_connection_status(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_char    *txt_conn_stat = L"BRIDGE";
    gsi_int     ctx_nr = gsi_current_context() ;
    gsi_item    *retvals = gsi_make_items(1) ;

    if (retvals && ctx_nr >= 0 && ctx_nr < MAX_GDB_CONTEXTS)
    {
        if (context[ctx_nr].pServer)
            if (context[ctx_nr].pItemMgt)
                txt_conn_stat = L"GROUP" ;
            else
                txt_conn_stat = L"SERVER";
    }
    else
        return ;
    gsi_set_sym(retvals[0], gsi_make_symbol(txt_conn_stat)) ;
    gsi_rpc_return_values(retvals, 1, call_index, ctx_nr) ;
    gsi_reclaim_items(retvals) ;
}


/* ========================================================================== */
/*                                                                            */
/*         Return to G2 a text-list containing the program IDs of the         */
/*              OPC Servers that are registered on this machine               */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_getserverlist(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    CATID               catid[3] ;
	CLSID               ClsID;
    HRESULT             hr ;
    ICatInformation*    pICatInformation = NULL ;
	IEnumGUID*          pIEnumGUID = 0;
    long                nrServers=0, lX=0, lY ;
    LPOLESTR            progID = NULL ;
	ULONG               lFetched = 0 ;
    

    /* If the OPC Foundation adds additional DAC Server specifications, the   */
    /* size of catid should be increased and additional initialization lines  */
    /* should be added below.                                                 */
    /* ---------------------------------------------------------------------- */
    catid[0] = IID_CATID_OPCDAServer10 ;
    catid[1] = IID_CATID_OPCDAServer20 ;
    catid[2] = IID_CATID_OPCDAServer30 ;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,NULL, CLSCTX_INPROC_SERVER, IID_ICatInformation, (void**) &pICatInformation) ;
    if ( SUCCEEDED(hr) )
    {
        HRESULT hr = pICatInformation->EnumClassesOfCategories(	3, catid, 0, 0, &pIEnumGUID ) ;
        if ( SUCCEEDED(hr) )
        {
            // We step through the enumerator twice.  The first time is just  //
            // count the number of servers so we know how big an array we     //
            // need to allocate.                                              //
            // -------------------------------------------------------------- //
            pIEnumGUID->Reset();           
            while ( S_OK == pIEnumGUID->Next( 1, &ClsID, &lFetched ) )
            {
                nrServers++ ;
            }

            
            // Allocate the structures we will need to return the values to   //
            // G2.  Fill them in.                                             //
            // -------------------------------------------------------------- //
            gsi_item    server_names = gsi_make_item() ;
            gsi_char    **name_list = new gsi_char*[nrServers] ;
            
            if (name_list)
            {
                LPOLESTR lpClsIDString = NULL;

                pIEnumGUID->Reset();           
                while ( S_OK == pIEnumGUID->Next( 1, &ClsID, &lFetched ) && lX < nrServers  )
            {
                if ( S_OK == StringFromIID( ClsID, &lpClsIDString ) )
                {
                    ProgIDFromCLSID( ClsID, &progID );
                    name_list[lX++] = progID ;
                    CoTaskMemFree( lpClsIDString );
                }
                }
            }
            pIEnumGUID->Release() ;

            // Build the text list & return it to G2 //
            // ------------------------------------- //
            gsi_symbol symX = gsi_make_symbol(_T("TEXT-LIST")) ;
            gsi_set_class_name(server_names, symX) ;
            gsi_set_type(server_names, GSI_NULL_TAG) ;
            gsi_set_str_list(server_names, name_list, lX) ;
            gsi_rpc_return_values(&server_names, 1, call_index, gsi_current_context()) ;
            for (lY=0; lY < lX; lY++)
              CoTaskMemFree(name_list[lY]) ;
            delete [] name_list ;
            gsi_reclaim_item(server_names) ;
        }
        
    }
	pICatInformation->Release() ;
}




/* ========================================================================== */
/*                                                                            */
/*     Return information about the configuration of the OPC Server that      */
/*                       is being used by this context.                       */
/*                                                                            */
/* returned values:                                                           */
/*                                                                            */
/*      1 - the current time of OPC Server in UNIX time                       */
/*      2 - the time when the process started in UNIX time                    */
/*      3 - the total number of groups managed by the server                  */
/*      4 - the approximate percent bandwidth currently in use by server      */
/*      5 - the OPC Server version                                            */
/*      6 - vendor information for the OPC server                             */
/*      7 - error code: 0:Success  -1: Failed to get OPC Server state         */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_getserverstats(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_int         ctx_nr ;
    gsi_item        *ret_vals ;
    HRESULT         hr ;
    long            error_code = -2 ;
    OPCSERVERSTATUS *server_stats ;
    time_t          current_time, start_time ;

#define VERSIZE 10
    wchar_t         buffer[VERSIZE+1] ;

    // If the current context is OK and we have a server pointer,
    // use IOPCServer::GetStatus to retrieve the requested info.
    // ----------------------------------------------------------
    ctx_nr = gsi_current_context() ;
    if (ctx_nr >= 0 && ctx_nr < MAX_GDB_CONTEXTS)
    {
        error_code = -1 ;
        if (context[ctx_nr].pServer)
        {
            hr = context[ctx_nr].pServer->m_pOPCServer->GetStatus(&server_stats) ;
            if (SUCCEEDED(hr))
                error_code = 0 ;
        }
    }

    // Prepare the array of return values
    // -----------------------------------
    ret_vals = gsi_make_items(7) ;
    if (!error_code)
    {
        current_time = OpcUtils::FileTimeToUnixTime(server_stats->ftCurrentTime) ;
        start_time = OpcUtils::FileTimeToUnixTime(server_stats->ftStartTime) ;
        _snwprintf(buffer,VERSIZE, L"%d.%d.%d",server_stats->wMajorVersion, 
                                               server_stats->wMinorVersion, 
                                               server_stats->wBuildNumber) ;
        buffer[VERSIZE] = 0 ;
    }
    gsi_set_flt(ret_vals[0], !error_code ? current_time : 0.0) ;
    gsi_set_flt(ret_vals[1], !error_code ? start_time : 0.0) ;
    gsi_set_int(ret_vals[2], !error_code ? server_stats->dwGroupCount : 0) ;
    gsi_set_int(ret_vals[3], !error_code ? server_stats->dwBandWidth  : 0) ;
    gsi_set_str(ret_vals[4], !error_code ? buffer : L"0.0.0") ;
    gsi_set_str(ret_vals[5], !error_code ? server_stats->szVendorInfo : L"") ;
    gsi_set_int(ret_vals[6], (error_code==-2) ? -1 : error_code) ;

    
    // Return the values & free the allocated memory
    // ---------------------------------------------
    if (error_code >= -1)
        gsi_rpc_return_values(ret_vals, 7, call_index, ctx_nr) ;
    gsi_reclaim_items(ret_vals) ;

    if (!error_code)
    {
        CoTaskMemFree(server_stats->szVendorInfo) ;
        CoTaskMemFree(server_stats) ;
    }
}


/* ========================================================================== */
/*                                                                            */
/*          Get the actual update rate for this context's OPC Group           */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_getactualupdaterate(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    BOOL            active ;
    DWORD           update_rate ;
    DWORD           LCID ;
    FLOAT           percent_deadband ;
    gsi_int         ctx_nr ;
    gsi_item        *ret_vals ;
    HRESULT         hr ;
    long            error_code = -2 ;
    LONG            time_bias ;
    LPWSTR          group_name ;
    OPCHANDLE       hClientGroup ;
    OPCHANDLE       hServerGroup ;

    // If the current context is OK and we have a server pointer,
    // use IOPCServer::GetStatus to retrieve the requested info.
    // ----------------------------------------------------------
    ctx_nr = gsi_current_context() ;
    if (ctx_nr >= 0 && ctx_nr < MAX_GDB_CONTEXTS)
    {
        error_code = -1 ;
        if (context[ctx_nr].pItemMgt)
        {
            IOPCGroupStateMgt  *pGrpStMgt = NULL ;
            hr = context[ctx_nr].pItemMgt->QueryInterface(IID_IOPCGroupStateMgt, (LPVOID*)&pGrpStMgt) ;
            if (SUCCEEDED(hr))
            {
                hr = pGrpStMgt->GetState(&update_rate, &active,
                            &group_name, &time_bias, &percent_deadband, &LCID, 
                            &hClientGroup, &hServerGroup) ;
                if (SUCCEEDED(hr))
                    error_code = 0 ;
            }
            if (pGrpStMgt)
                hr = pGrpStMgt->Release() ;
        }
    }

    // Prepare the array of return values
    // -----------------------------------
    ret_vals = gsi_make_items(2) ;
    gsi_set_int(ret_vals[0], !error_code ? update_rate  : 0) ;
    gsi_set_int(ret_vals[1], (error_code==-2) ? -1 : error_code) ;

    // Return the values & free the allocated memory
    // ---------------------------------------------
    if (error_code >= -1)
        gsi_rpc_return_values(ret_vals, 2, call_index, ctx_nr) ;
    gsi_reclaim_items(ret_vals) ;

    if (!error_code)
    {
        CoTaskMemFree(group_name) ;
    }
}


/* ========================================================================== */
/*                                                                            */
/*    Set the update rate, deadband, and state of this context's OPC Group    */
/*                                                                            */
/*  Returned error codes:                                                     */
/*                                                                            */
/*      1 : Success but actual update rate does not match requested rate      */
/*      0 : Success                                                           */
/*     -1 : Invalid group handle                                              */
/*     -2 : Operation failed for unknown reasons                              */
/*     -3 : Not enough memory (not used)                                      */
/*     -4 : An argument to the RPC was invalid                                */
/*     -5 : Invalid argument type                                             */
/*     -6 : Invalid number of arguments                                       */
/*                                                                            */
/* ========================================================================== */
void g2_opc_set_groupstate(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool                validating = true ;
    gsi_int             ctx_nr ;
    gsi_item            *ret_vals ;
    HRESULT             hr ;
    IOPCGroupStateMgt   *pGrpStMgt = NULL ;
    long                error_code = -7 ; // Invalid context number
    long                update_rate ;
    long                actual_rate ;
    long                bool_as_nr ;
    long                dbgCt ;
    double              dead_band ;
    BOOL                active ;
    LPWSTR              szErrorMsg = L"OK" ;


    ctx_nr = gsi_current_context() ;
    if (ctx_nr >= 0 && ctx_nr < MAX_GDB_CONTEXTS)
    {
        /* Validate the new settings */
        /* ------------------------- */
        error_code = -2 ;  // (unknown error)
        while(validating)  // Provides an easy way to jump past
                           // code we do not wish to execute
        {
            if (!context[ctx_nr].pServer)
            {
               // No Server
                szErrorMsg = L"Not connected to an OPC Server" ;
               break ;
            }
            if (!context[ctx_nr].pItemMgt)
            {
                // Active Group
                error_code = -1 ;
                szErrorMsg = L"Not connect to an OPC Group";
                break ;
            }
            if (count != 3)
            {
                // Wrong number of parameters
                error_code = -6 ;
                szErrorMsg = L"Invalid number of arguments";
                break ;
            
            }
            if (gsi_type_of(rpc_arguments[0]) != GSI_INTEGER_TAG ||
                gsi_type_of(rpc_arguments[1]) != GSI_FLOAT64_TAG ||
                gsi_type_of(rpc_arguments[2]) != GSI_LOGICAL_TAG )
            {
                error_code = -5 ;
                szErrorMsg = L"Invalid argument type";
                break ;
            }
            if ( ( (update_rate = gsi_int_of(rpc_arguments[0])) < 0) ||
                 ( (dead_band = gsi_flt_of(rpc_arguments[1])) < 0.0) )
            {
                error_code = -4 ;
                szErrorMsg = L"Invalid parameter";
                break ;
            }
            else
            {
                bool_as_nr = gsi_log_of(rpc_arguments[2]) ;
                active = (bool_as_nr >= 0) ;
            }
            hr = context[ctx_nr].pItemMgt->QueryInterface(IID_IOPCGroupStateMgt, (LPVOID*)&pGrpStMgt) ;
            if (FAILED(hr))
            {
                szErrorMsg = L"Unable to get IOPCGroupStateMgt interface";
                break ;
            }
            validating = false ;
            break ;
        }

        if (!validating)
        {
            hr = pGrpStMgt->SetState((unsigned long*)(&update_rate), 
                         (unsigned long*)&actual_rate, &active, NULL, (float*)&dead_band, NULL, NULL) ;
            if (SUCCEEDED(hr))
                error_code = (update_rate == actual_rate) ? 0 : 1 ;
            else
                szErrorMsg = L"Server failed to set new state";
        }


        // Release pointer to IOPCGroupStateMgt interface
        // ----------------------------------------------
        if (pGrpStMgt)
            dbgCt = pGrpStMgt->Release() ;
            
        // Prepare the array of return values
        // -----------------------------------
        ret_vals = gsi_make_items(2) ;
        gsi_set_int(ret_vals[0], error_code) ;
        gsi_set_str(ret_vals[1], szErrorMsg) ;

        // Return the values & free the allocated memory
        // ---------------------------------------------
        gsi_rpc_return_values(ret_vals, 2, call_index, ctx_nr) ;
        gsi_reclaim_items(ret_vals) ;
    }
}


/* ========================================================================== */
/*                                                                            */
/*  Set the quality filter that we will use to decide which values to return  */
/*                                                                            */
/*  Returned error codes:                                                     */
/*                                                                            */
/*      1 : Invalid quality filter level                                      */
/*      0 : Success                                                           */
/*     -1 : Failed                                                            */
/*     -2 : Invalid number of arguments                                       */
/*                                                                            */
/* ========================================================================== */
void g2_opc_set_qualityfilterlevel(gsi_item *rpc_arguments, gsi_int count, call_identifier_type call_index)
{
    gsi_int         ctx_nr ;
    gsi_item        *ret_vals ;
    long            error_code = -1 ; // Assume will fail
    long            x, good, bad, uncertain ;

    ctx_nr = gsi_current_context() ;
    if (ctx_nr >= 0 && ctx_nr < MAX_GDB_CONTEXTS)
    {
        /* Validate the new settings */
        /* ------------------------- */
        if (count == 1)
        {
            if (gsi_type_of(rpc_arguments[0]) == GSI_INTEGER_TAG)
            {
                x = gsi_int_of(rpc_arguments[0]) ;
                if (x >= 0)
                {
                    uncertain = x % 10 ;
                    x = (x-uncertain) / 10 ;
                    bad = x % 10 ;
                    good = (x-bad) / 10 ;
                    if (good <=1 && bad <= 1 && uncertain <=1)
                        error_code = 0 ;
                    else
                        error_code = 1 ;
                }
            }
        }
        else
            error_code = -2 ;  // wrong # of arguments
            
        // Set the quality filters if the input is OK
        // ------------------------------------------
        if (error_code == 0)
        {
            g_lev1_good = (good == 1) ;
            g_lev1_bad  = (bad  == 1) ;
            g_lev1_uncertain = (uncertain == 1) ;
        }
             
        // Prepare the array of return values
        // -----------------------------------
        ret_vals = gsi_make_items(1) ;
        gsi_set_int(ret_vals[0], error_code) ;

        // Return the values & free the allocated memory
        // ---------------------------------------------
        gsi_rpc_return_values(ret_vals, 1, call_index, ctx_nr) ;
        gsi_reclaim_items(ret_vals) ;
    }
}


/* ========================================================================== */
/*                                                                            */
/*   Allows G2 to refresh on demand all data items directly from the device   */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_triggerdeviceread(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    context_info        *pCtxInfo ;
    DWORD               dwCancelId ;
    gsi_int             ctx_nr = gsi_current_context() ;
    gsi_item            *retval ;
    HRESULT             hr ;
    IOPCAsyncIO2        *pIa2 ;
    long                error_code = -1 ;
    static long         dwTransId = 1 ;

    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;
    pCtxInfo = &context[ctx_nr] ;

    // Get the IOPCAsyncIO2 pointer if possible & execute the Refresh method
    while (1)
    {
        if (pCtxInfo->pServer == NULL || pCtxInfo->pItemMgt == NULL)
            break ;
        hr = pCtxInfo->pItemMgt->QueryInterface(IID_IOPCAsyncIO2, (LPVOID*)&pIa2) ;
        if (FAILED(hr))
        {
            log_message(TL_ERRORS, L"Unable to retrieve IOPCAsyncIO2 pointer.") ;
            break ;
        }
        hr = pIa2->Refresh2(OPC_DS_CACHE, dwTransId++,&dwCancelId);
        pIa2->Release() ;
        if (FAILED(hr))
        {
            log_message(TL_ERRORS, L"Refresh2 failed.") ;
            break ;
        }
        error_code = 0 ;
        break ;
    }

    // Return the error code to G2
    // ---------------------------
    retval = gsi_make_items(1) ;
    gsi_set_int(retval[0], error_code) ;
    gsi_rpc_return_values(retval, 1, call_index, ctx_nr) ;
    gsi_reclaim_items(retval) ;
}


/* ========================================================================== */
/*                                                                            */
/*     Writes the value, quality, and timestamp of the specified item-id.     */
/*                                                                            */
/*            This RPC is specific to OPC Data Access 3.0 servers.            */
/*                                                                            */
/*  Returned error codes:                                                     */
/*                                                                            */
/*      1 : Partially succeeded                                               */
/*      0 : Success                                                           */
/*     -1 : Failed                                                            */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_writevqt(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool                start_validating = true ;
    BOOL                ok ;
    context_info        *pCtxInfo ;
    double              s ;
    FILETIME            ft ;
    gsi_int             ctx_nr = gsi_current_context() ;
	gsi_int				valueType, gintX, qualityCode ;
    gsi_item            *ret_vals ;
	gsi_char*			gstrX ;
	HRESULT				hr, *pErrors = NULL ;
    int                 nr_flds ;
	IOPCItemIO			*pItemIO = NULL ;
    long                error_code = -1 ;
    LPWSTR				szErrorMsg = NULL ;
	LPWSTR				szItemID = NULL ;
    LPWSTR              szDate = NULL ;
	OPCITEMVQT			objVQT ;
    SYSTEMTIME          st ;
	VARIANT				varValue ;

    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;
    pCtxInfo = &context[ctx_nr] ;

	// Validate input: Are we connected to a server?  Is it version 3.0+?
	//                 Are there 4 input parameters, each of the correct type?
	// -----------------------------------------------------------------------
	while (start_validating)
	{
        start_validating = false ;
		if (pCtxInfo->pServer == NULL)
		{
			szErrorMsg = L"Not connected to an OPC Server";
			break ;
		}
		hr = pCtxInfo->pServer->m_pOPCServer->QueryInterface(IID_IOPCItemIO, (LPVOID*)&pItemIO) ;
		if FAILED(hr)
		{
			szErrorMsg = L"Unable to obtain IOPCItemIO pointer.  Server version 3.0 or greater?" ;
			break ;
		}
		if (count != 4)
		{
			szErrorMsg = L"Invalid number of input parameters";
			break ;
		}
		if (gsi_type_of(rpc_arguments[0]) != GSI_STRING_TAG || 
		    gsi_type_of(rpc_arguments[2]) != GSI_STRING_TAG || gsi_type_of(rpc_arguments[3]) != GSI_INTEGER_TAG)
		{
			szErrorMsg = L"Parameter data type error";
			break ;
		}
        qualityCode = gsi_int_of(rpc_arguments[3]) ;
        if (qualityCode != OPC_GOOD_NONSPEC && qualityCode != OPC_BAD_NONSPEC && qualityCode != OPC_UNC_NONSPEC)
        {
            szErrorMsg = L"Quality code must be 0 (good), 300 (bad), or 400 (uncertain)";
            break ;
        }
        else
        {
            objVQT.bQualitySpecified = true ;
            if (qualityCode == OPC_GOOD_NONSPEC)
                objVQT.wQuality = OPC_QUALITY_GOOD ;
            else if (qualityCode == OPC_UNC_NONSPEC)
                objVQT.wQuality = OPC_QUALITY_UNCERTAIN ;
            else
                objVQT.wQuality = OPC_QUALITY_BAD ;

        }

		VariantInit(&varValue) ;
		valueType = gsi_type_of(rpc_arguments[1]) ;
		switch (valueType)
		{
		case GSI_INTEGER_TAG:	varValue.vt = VT_I4 ;
								varValue.lVal = gsi_int_of(rpc_arguments[1]) ;
								break ;
		case GSI_FLOAT64_TAG:	varValue.vt = VT_R8 ;
								varValue.dblVal = gsi_flt_of(rpc_arguments[1]) ;
								break ;
		case GSI_SYMBOL_TAG:	gstrX = gsi_symbol_name(rpc_arguments[1]) ;
		case GSI_STRING_TAG:	if (valueType == GSI_STRING_TAG)
									gstrX = gsi_str_of(rpc_arguments[1]) ;
								varValue.vt = VT_BSTR ;
								varValue.bstrVal = ::SysAllocString(gstrX) ;
								break ;								
		case GSI_LOGICAL_TAG:	varValue.vt = VT_BOOL ;
								gintX = gsi_log_of(rpc_arguments[1]) ;
								varValue.boolVal = (gintX < 0) ? VARIANT_FALSE : VARIANT_TRUE ;
								break ;
        default:                szErrorMsg=L"Invalid value type";
                                break ;
		}
        if (szErrorMsg != NULL)
            break ;
        else
            objVQT.vDataValue = varValue ;


        // Decode the date if it is properly formatted
        // -------------------------------------------
        szDate = gsi_str_of(rpc_arguments[2]) ;
        if (wcslen(szDate) == 0)
            objVQT.bTimeStampSpecified = false ;
        else
        {
            nr_flds = swscanf(szDate, L"%d/%d/%d %d:%d:%f",&st.wYear,&st.wMonth,&st.wDay,&st.wHour,&st.wMinute,&s, szDate) ;
            if (nr_flds != 6)
            {
                szErrorMsg = L"Time format is YYYY/MM/DD HH:MI:SS.mmmm";
                break ;
            }
            st.wSecond = (int)s ;
            st.wMilliseconds = (int)(1000*(s-st.wSecond + .0005)) ;
            ok = SystemTimeToFileTime(&st, &ft) ;
            if (!ok)
            {
                szErrorMsg = L"Unable to convert date to OPC Format" ;
                break ;
            }   
            objVQT.bTimeStampSpecified = true ;
            objVQT.ftTimeStamp = ft ;
        }
	}


	// Build the input to IOPCItemIO::WriteVQT
	// ---------------------------------------
	if (szErrorMsg == NULL)
	{
		// Call WriteVQT and decode the results
		// ------------------------------------
        szItemID = gsi_str_of(rpc_arguments[0]) ;
		hr = pItemIO->WriteVQT(1, (const unsigned short**)&szItemID, &objVQT, &pErrors) ;
        if (FAILED(hr))
        {
            szErrorMsg = L"Server reported writevqt failure";
        }
        else
            error_code = 0 ;

	}

    // Return the error code to G2
    // ---------------------------
    ret_vals = gsi_make_items(2) ;
    gsi_set_int(ret_vals[0], error_code) ;
    gsi_set_str(ret_vals[1], szErrorMsg) ;
    gsi_rpc_return_values(ret_vals, 2, call_index, ctx_nr) ;
    gsi_reclaim_items(ret_vals) ;
}





/* ========================================================================== */
/* =========== Browse RPCs that use IOPCBrowseServerAddressSpace ============ */
/* ========================================================================== */

/* ========================================================================== */
/*                                                                            */
/*         Change the filter that is used when browsing the namespace         */
/*                                                                            */
/*    The filter is a wildcard string that conforms to the Visual Basic       */
/*                                 LIKE operator,                             */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_setbrowserfilter(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool        validating = true ;
    gsi_char    *filter ;
    gsi_int     ctx_nr = gsi_current_context() ;
    gsi_item    *retval ;
    long        error_code = -1 ;

    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;
    
    while (validating)
    {
        // Validate the input
        // ------------------
        if (count < 1)
        {
            log_message(TL_ERRORS, L"rpc-opc-setbrowserfilter: missing filter.");
            break ;
        }
        if (gsi_type_of(rpc_arguments[0]) != GSI_STRING_TAG)
        {
            log_message(TL_ERRORS, L"rpc-opc-setbrowserfilter: filter must be a string.") ;
            break ;
        }

        // Free up the memory used by the prior filter
        // -------------------------------------------
        if (context[ctx_nr].elementNameFilter)
            delete [] context[ctx_nr].elementNameFilter ;

        // Extract the new filter, allocate memory to hold it, and attach it the context
        // -----------------------------------------------------------------------------
        filter = gsi_str_of(rpc_arguments[0]) ;
        context[ctx_nr].elementNameFilter = new wchar_t [wcslen(filter) + 1] ;
        wcscpy(context[ctx_nr].elementNameFilter, filter) ;
        error_code = 0 ;
        validating = false ;
    }

    // Tell G2 whether we succeeded or not
    // -----------------------------------
    retval = gsi_make_items(1) ;
    gsi_set_int(retval[0], error_code) ;
    gsi_rpc_return_values(retval, 1, call_index, ctx_nr) ;
    gsi_reclaim_items(retval) ;
}



/* ========================================================================== */
/*                                                                            */
/*   Set the data type filter that will be used when browsing the namespace   */
/*                                                                            */
/*                          0: No filter                                      */
/*                          1: Short integer                                  */
/*                          2: Long integer                                   */
/*                          3: Single-precision float                         */
/*                          4: Double-precision float                         */
/*                          5: Text                                           */
/*                          6: Truth-value                                    */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_setbrowserdatatype(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool        validating = true ;
    gsi_int     ctx_nr = gsi_current_context() ;
    gsi_int     x = -1;
    gsi_item    *retval ;
    long        error_code = -1 ;
    VARTYPE     *pVT ;

    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;
    pVT = &context[ctx_nr].typeFilter ;
    
    // Validate the input
    // ------------------
    while (validating)
    {
        if (count < 1)
        {
            log_message(TL_ERRORS, L"rpc-opc-setbrowserdatatype: missing filter.");
            break ;
        }
        if (gsi_type_of(rpc_arguments[0]) == GSI_INTEGER_TAG)
        {
            x = gsi_int_of(rpc_arguments[0]) ;
        }
        if (x < 0 || x > 6)
        {
            log_message(TL_ERRORS, L"rpc-opc-setbrowserdatatype: data type must be an integer between 0 & 6.") ;
            break ;
        }
        validating = false ;
        error_code = 0 ;
        break;
    }


    // Assign the data type filter to the context
    // ------------------------------------------
    switch(x)
    {
        case 0 :    *pVT = VT_EMPTY ;
                    break ;
        case 1 :    *pVT = VT_I2 ;
                    break ;
        case 2 :    *pVT = VT_I4 ;
                    break ;
        case 3 :    *pVT = VT_R4 ;
                    break ;
        case 4:     *pVT = VT_R8 ;
                    break ;
        case 5 :    *pVT = VT_BSTR ;
                    break ;
        case 6 :    *pVT = VT_BOOL ;
                    break ;
    } ;


    // Tell G2 whether we succeeded or not
    // -----------------------------------
    retval = gsi_make_items(1) ;
    gsi_set_int(retval[0], error_code) ;
    gsi_rpc_return_values(retval, 1, call_index, ctx_nr) ;
    gsi_reclaim_items(retval) ;
}


/* ========================================================================== */
/*                                                                            */
/* Set the access rights filter that will be used when browsing the namespace */
/*                                                                            */
/*                 0: No filter                                               */
/*                 1: The client can read the data item’s value               */
/*                 2: The client can edit the data item’s value               */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_setbrowserrights(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_int     ctx_nr = gsi_current_context() ;
    gsi_int     x = -1;
    gsi_item    *retval ;
    long        error_code = -1 ;

    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    // Validate the input
    // ------------------
    while (1)
    {
        if (count < 1)
        {
            log_message(TL_ERRORS, L"rpc-opc-setbrowserrights: missing filter.");
            break ;
        }
        if (gsi_type_of(rpc_arguments[0]) == GSI_INTEGER_TAG)
        {
            x = gsi_int_of(rpc_arguments[0]) ;
        }
        if (x < 0 || x > 2)
            log_message(TL_ERRORS, L"rpc-opc-setbrowserrights: data type must be an integer between 0 & 2.") ;
        else
        {
            context[ctx_nr].rightsFilter = (short)x;
            error_code = 0 ;
        }
        break;
    }

    // Tell G2 whether we succeeded or not
    // -----------------------------------
    retval = gsi_make_items(1) ;
    gsi_set_int(retval[0], error_code) ;
    gsi_rpc_return_values(retval, 1, call_index, ctx_nr) ;
    gsi_reclaim_items(retval) ;
}


/* ========================================================================== */
/*                                                                            */
/*   Code shared by rpc-opc-getbrowserleaves and rpc-opc-getbrowserbranches   */
/*                                                                            */
/* ========================================================================== */
void internal_browser(OPCBROWSETYPE dwBrowseFilterType, gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
#define BATCH_SIZE 100
    context_info                    *pCtxInfo = NULL ;
    DWORD                           nrRetrieved = 0 ;
    DWORD                           nrItems = 0 ;
    enum stages { validating, browsing, wrapup } stage = validating ; 
    gsi_char**                      textArray = NULL ;
    gsi_int                         ctx_nr ;
    gsi_item                        *retval ;
    gsi_symbol                      class_name ;
    HRESULT                         hr ;
    IOPCBrowseServerAddressSpace    *pIBrowse = NULL ;
    long                            itemArraySize = BATCH_SIZE, ct ;
    LPWSTR                          szMsg = NULL ;
    LPENUMSTRING                    pEnum = NULL ;
    short                           errorLevel = TL_ERRORS ;


    ctx_nr = gsi_current_context() ;
    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    /* Determine if it is possible to process rpc-opc-getbrowserleaves */
    /* --------------------------------------------------------------- */
    while(stage == validating)  // Provides an easy way to jump past
                                // code we do not wish to execute
    {
        retval = gsi_make_items(1) ;
        if (!retval)
        {
            szMsg = L"Unable to allocate return values. Out of memory?" ;
            errorLevel = TL_CRITICAL ;
            break ;
        }
        gsi_set_type(retval[0], GSI_STRING_LIST_TAG) ;
        class_name = gsi_make_symbol(L"TEXT-LIST") ;
        gsi_set_class_name(retval[0], class_name) ;
        gsi_set_str_list(retval[0], NULL, 0) ;

        if (!context[ctx_nr].pServer)
        {
            szMsg = L"Not connected to server, Cannot process rpc-opc-getbrowserleaves" ;
            break ;
        }
        hr = context[ctx_nr].pServer->m_pOPCServer->QueryInterface(IID_IOPCBrowseServerAddressSpace, (LPVOID*)&pIBrowse) ;
        if (FAILED(hr))
        {
            szMsg = L"Server failed to return pointer to optional IOPCBrowseServerAddressSpace" ;
            break ;   
        }
        stage = szMsg ? wrapup : browsing ;
        break ;
    }

    // Get the list of items & build and array of item IDs strings //
    // ----------------------------------------------------------- //
    while (stage == browsing)
    {
        pCtxInfo = &context[ctx_nr] ;
        hr = pIBrowse->BrowseOPCItemIDs(dwBrowseFilterType,
                                 pCtxInfo->elementNameFilter?pCtxInfo->elementNameFilter:L"",
                                 dwBrowseFilterType==OPC_BRANCH?0:pCtxInfo->typeFilter,
                                 dwBrowseFilterType==OPC_BRANCH?0:pCtxInfo->rightsFilter,&pEnum) ;
        ct = pIBrowse->Release() ;
        if (SUCCEEDED(hr))
        {
            textArray = new gsi_char* [BATCH_SIZE] ;
            if (textArray == NULL)
            {
                szMsg = L"Allocation of text array failed.  Out of memory?" ;
                errorLevel = TL_CRITICAL ;
                break ;
            }
            hr = pEnum->Next(BATCH_SIZE, textArray, &nrRetrieved) ;
        }

        bool more = false ;
        if (SUCCEEDED(hr))
        {
            nrItems = nrRetrieved ;
            more = (nrRetrieved == BATCH_SIZE) ;
        }


        // This code will only be executed when there are more than BATCH_SIZE items
        // -------------------------------------------------------------------------
        while (more)
        {
            gsi_char** newArray = new gsi_char* [nrItems + BATCH_SIZE] ;
            if (newArray == NULL)
            {
                szMsg = L"Allocation of text array failed.  Out of memory?" ;
                errorLevel = TL_CRITICAL ;
                break ;
            }
            memcpy(newArray, textArray, nrItems * sizeof(gsi_char*)) ;
            delete [] textArray ;
            textArray = newArray ;
            itemArraySize += BATCH_SIZE ;
            hr = pEnum->Next(BATCH_SIZE, textArray+nrItems, &nrRetrieved) ;
            if (FAILED(hr))
                more = false ;
            else
            {
                nrItems += nrRetrieved ;
                more = (nrRetrieved == BATCH_SIZE) ;
            }
        }
        if (FAILED(hr))
        {
            szMsg = dwBrowseFilterType == OPC_LEAF ? L"rpc-opc-getbrowserleaves: Browsing for leaves failed" :
                                                     L"rpc-opc-getbrowserbranches: Browsing for branches failed" ;
            break ;
        }

        // Finish constructing text list
        // -----------------------------
        if (nrItems)
            gsi_set_str_list(retval[0], textArray, nrItems) ;

        stage = wrapup ;
    }



    // Return text list to G2
    // ----------------------
    gsi_rpc_return_values(retval, 1, call_index, ctx_nr) ;


    // Log any error messages
    // ----------------------
    if (szMsg)
        log_message(errorLevel, szMsg) ;


    // Clean Up
    // --------
    if (pEnum)
        ct = pEnum->Release() ;
    if (nrItems && textArray )
        for (unsigned long lng = 0 ; lng < nrItems ; lng++)
            CoTaskMemFree(textArray[lng]) ;
    if (textArray)
        delete [] textArray ;
    gsi_reclaim_items(retval) ;

}


/* ========================================================================== */
/*                                                                            */
/*                 Return a text list of items at the current                 */
/*                     IOPCBrowseAddressNameSpace location                    */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_getbrowserleaves(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    internal_browser(OPC_LEAF, rpc_arguments, count, call_index) ;
}


/* ========================================================================== */
/*                                                                            */
/*                 Return a text list of items at the current                 */
/*                     IOPCBrowseAddressNameSpace location                    */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_getbrowserbranches(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    internal_browser(OPC_BRANCH, rpc_arguments, count, call_index) ;
}


/* ========================================================================== */
/*                                                                            */
/*            Change the IOPCBrowseAddressNameSpace browse point              */
/*                                                                            */
/*      Input arguments:                                                      */
/*            [0] - direction:                                                */
/*                  1 : up                                                    */
/*                  2 : down                                                  */
/*                  3 : move to specified location                            */
/*            [1] - location                                                  */
/*                  for DOWN, the branch to move into                         */
/*                  for UP, not used ... should be NULL string                */
/*                  for TO, fully qualified name or NULL string for root      */
/*                                                                            */
/*      Returns error code :                                                  */
/*                    0 success                                               */
/*                   -1 failed                                                */
/*                    1 invalid argument                                      */
/*                    2 out of memory                                         */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_changebrowserposition(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool                            validating = true ;
    gsi_char*                       location ;
    gsi_int                         ctx_nr ;
    gsi_int                         error_code = -1 ;
    gsi_int                         action_code ;
    HRESULT                         hr ;
    IOPCBrowseServerAddressSpace    *pIBrowse = NULL ;
    LPWSTR                          szErrorMsg = NULL ;

    ctx_nr = gsi_current_context() ;
    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    /* Validate the input & make sure we can get an IOPCBrowseServerAddressSpace pointer */
    /* --------------------------------------------------------------------------------- */
    while(validating)  // Provides an easy way to jump past
                       // code we do not wish to execute
    {
        if (!context[ctx_nr].pServer)
        {
            szErrorMsg = L"rpc_opc_changebrowserposition: Not connected to an OPC Server" ;
            break ;
        }
        if (count != 2)
        {
            szErrorMsg = L"rpc_opc_changebrowserposition: invalid number of arguments";
            break ;
        
        }
        if (gsi_type_of(rpc_arguments[0]) != GSI_INTEGER_TAG ||
            gsi_type_of(rpc_arguments[1]) != GSI_STRING_TAG )
        {
            error_code = 1 ;
            szErrorMsg = L"rpc_opc_changebrowserposition: invalid argument type";
            break ;
        }
        action_code = gsi_int_of(rpc_arguments[0]) ;
        if (action_code < OPC_BROWSE_UP || action_code > OPC_BROWSE_TO)
        {
            error_code = 1 ;
            szErrorMsg = L"rpc_opc_changebrowserposition: direction code must have value of 1, 2, or 3";
            break ;
        }
        location = gsi_str_of(rpc_arguments[1]) ;
        if (action_code == OPC_BROWSE_UP && wcslen(location))
        {
			szErrorMsg = L"Browse-to location ignored when browsing up (set to \"\")";
            location = L"" ;;
        }
        hr = context[ctx_nr].pServer->m_pOPCServer->QueryInterface(IID_IOPCBrowseServerAddressSpace, (LPVOID*)&pIBrowse) ;
        if (FAILED(hr))
        {
            szErrorMsg = L"rpc_opc_changebrowserposition: request for (optional) IOPCBrowseServerAddressSpace failed" ;
            break ;   
        }
        error_code = 0 ;
        validating = false ;
    }

    /* Try to change the browser position */
    /* ---------------------------------- */
    if (error_code == 0)
    {
        hr = pIBrowse->ChangeBrowsePosition((OPCBROWSEDIRECTION)action_code, location) ;
        pIBrowse->Release() ;
        if (FAILED(hr))
        {
            error_code = -1 ;
            szErrorMsg = (action_code==OPC_BROWSE_TO) ? L"rpc_opc_changebrowserposition failed." :
                                                        L"rpc_opc_changebrowserposition failed." ;
        }
    }

    /* Inform G2 of the success or failure of this procedure */
    /* ----------------------------------------------------- */
    gsi_item    *retval = gsi_make_items(1) ;
    gsi_set_int(retval[0], error_code) ;
    gsi_rpc_return_values(retval, 1, call_index, ctx_nr) ;
    gsi_reclaim_items(retval) ;


    /* Log any error messages */
    /* ---------------------- */
    if (szErrorMsg)
        log_message(error_code?TL_ERRORS:TL_WARNINGS, szErrorMsg) ;
}


/* ========================================================================== */
/*                                                                            */
/*   Convert item ID at the current IOPCBrowseAddressNameSpace browse point   */
/*                         to a fully qualified item ID                       */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_getitemid(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool                            validating = true ;
    gsi_char*                       itemIDin  = NULL ;
    gsi_char*                       itemIDout = L"" ;
    gsi_int                         ctx_nr ;
    gsi_int                         error_code = -1 ;
    HRESULT                         hr ;
    IOPCBrowseServerAddressSpace    *pIBrowse = NULL ;
    LPWSTR                          szErrorMsg = NULL ;

    ctx_nr = gsi_current_context() ;
    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    /* Validate the input & make sure we can get an IOPCBrowseServerAddressSpace pointer */
    /* --------------------------------------------------------------------------------- */
    while(validating)  // Provides an easy way to jump past
                       // code we do not wish to execute
    {
        if (!context[ctx_nr].pServer)
        {
            szErrorMsg = L"rpc_opc_getitemid: Not connected to an OPC Server" ;
            break ;
        }
        if (count != 1)
        {
            szErrorMsg = L"rpc_opc_getitemid: invalid number of arguments";
            break ;
        
        }
        if (gsi_type_of(rpc_arguments[0]) != GSI_STRING_TAG )
        {
            error_code = 1 ;
            szErrorMsg = L"rpc_opc_getitemid: invalid argument type";
            break ;
        }
        hr = context[ctx_nr].pServer->m_pOPCServer->QueryInterface(IID_IOPCBrowseServerAddressSpace, (LPVOID*)&pIBrowse) ;
        if (FAILED(hr))
        {
            szErrorMsg = L"rpc_opc_getitemid: request for (optional) IOPCBrowseServerAddressSpace failed" ;
            break ;   
        }
        error_code = 0 ;
        validating = false ;
    }

    /* Try to qualify the item ID */
    /* -------------------------- */
    if (error_code == 0)
    {
        itemIDin = gsi_str_of(rpc_arguments[0]) ;
        hr = pIBrowse->GetItemID(itemIDin, &itemIDout) ;
        pIBrowse->Release() ;
        if (FAILED(hr))
            szErrorMsg = L"rpc_opc_getitem: server failed to return qualified item ID.";
    }

    /* Return the qualified item ID or a NULL string to G2 */
    /* --------------------------------------------------- */
    gsi_item    *retval = gsi_make_items(1) ;
    gsi_set_str(retval[0], itemIDout) ;
    gsi_rpc_return_values(retval, 1, call_index, ctx_nr) ;
    gsi_reclaim_items(retval) ;

    /* Free the memory occupied by the fully qualified item ID */
    /* ------------------------------------------------------- */
    if (szErrorMsg == NULL)
        CoTaskMemFree(itemIDout) ;

    /* Log any error messages */
    /* ---------------------- */
    if (szErrorMsg)
        log_message(TL_ERRORS, szErrorMsg) ;
}



/* ========================================================================== */
/* =================== Browse RPCs that use IOPCBrowser ===================== */
/* ========================================================================== */

/* ========================================================================== */
/*                                                                            */
/*    Browse a single branch of the address space and returns a text list     */
/*    containing the list of branches or leaves depending on the browse       */
/*    filter. This RPC is specific to OPC Data Access 3.0 servers.            */
/*                                                                            */
/*      Input arguments:                                                      */
/*            [0] - the name of a branch to browse or the NULL                */
/*                  string to start browsing from the root                    */
/*            [1] - browse type                                               */
/*                  1 - all                                                   */
/*                  2 - branches                                              */
/*                  3 - leaves                                                */
/*            [2] - browse filter.  Similar to VB LIKE                        */
/*                                                                            */
/*      Returns:                                                              */
/*            [0] - text list containing requested item IDs                   */
/*            [1] - error code                                                */
/*                   0 success                                                */
/*                  -1 failed                                                 */
/*                   1 partially succeeded                                    */
/*            [2] - status message                                            */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_browse(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool                validating = true,
                        processing ;
    gsi_int             ctx_nr ;
    gsi_item*           ret_vals = NULL ;
    gsi_char**          item_id = NULL ;
    gsi_symbol          class_name ;
    int                 error_code = -2 ;
    long                lngBrowseFilterNr ;
    short               errorLevel = TL_ERRORS ;

    BOOL                bMore = false ;
    DWORD               dwNrReturned  = 0 ;
    DWORD               propertyTable = 1 ;
    HRESULT             hr ;
    IOPCBrowse          *pIBrowse ;
    LPWSTR              szItemID;
    LPWSTR              szElementNameFilter ;
    LPWSTR              szVendorFilter = L"" ;
    LPWSTR              szMsg = NULL ;
    LPWSTR              szP2e = NULL;
    OPCBROWSEELEMENT    *pElement = NULL ;
    OPCBROWSEFILTER     dwBrowseFilter ;


    ctx_nr = gsi_current_context() ;
    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    /* Validate the new settings */
    /* ------------------------- */
    while(validating)  // Provides an easy way to jump past
                       // code we do not wish to execute
    {
        ret_vals = gsi_make_items(3) ;
        if (!ret_vals)
        {
            szMsg = L"Unable to allocate return values. (Out of Memory?)" ;
            errorLevel = TL_CRITICAL ;
            break ;
        }
        error_code = -1 ;  // (We can now return status to G2) ;
        gsi_set_type(ret_vals[0], GSI_STRING_LIST_TAG) ;
        class_name = gsi_make_symbol(L"TEXT-LIST") ;
        gsi_set_class_name(ret_vals[0], class_name) ;
        gsi_set_str_list(ret_vals[0], NULL, 0) ;
        if (!context[ctx_nr].pServer)
        {
           szMsg = L"Not connected to server, rpc_opc_browse" ;
           break ;
        }

        // The following errors were treated as critical because 
        // they should not occur unless there is an error in the kb.
        if (count != 3)
        {
            szMsg = L"Wrong number of parameters to rpc_opc_browse" ;
            errorLevel = TL_CRITICAL ;
            break ;
        }

        if (gsi_type_of(rpc_arguments[0]) != GSI_STRING_TAG  ||
            gsi_type_of(rpc_arguments[1]) != GSI_INTEGER_TAG ||
            gsi_type_of(rpc_arguments[2]) != GSI_STRING_TAG )
        {
            szMsg = L"Invalid parameter data type, rpc_opc_browse" ;
            errorLevel = TL_CRITICAL ;
            break ;
        }

        lngBrowseFilterNr = gsi_int_of(rpc_arguments[1]) ;
        if (lngBrowseFilterNr < 1 || lngBrowseFilterNr > 3)
        {
            szMsg = L"rpc-opc-browse: Invalid browse type code" ;
            break ;
        }
        validating = false ;
        break ;
    }

    
    processing = !validating && szMsg == NULL;
    while(processing)
    {
        szItemID = gsi_str_of(rpc_arguments[0]) ;
        dwBrowseFilter = (OPCBROWSEFILTER)lngBrowseFilterNr ;
        szElementNameFilter = gsi_str_of(rpc_arguments[2]) ;

        // This feature is only supported by DAC 3.0 (at this writing)
        // The QueryInterface will fail if we are using an older OPC DAC
        // -------------------------------------------------------------
        hr = context[ctx_nr].pServer->m_pOPCServer->QueryInterface(IID_IOPCBrowse, (void**)&pIBrowse) ;
        if (FAILED(hr))
        {
            szMsg = L"rpc-opc-browse: Unable to find browse interface (old server?)" ;
            break ;
        }
        szP2e = (LPWSTR)CoTaskMemAlloc(2) ;
        wcscpy(szP2e,L"") ;

        hr = pIBrowse->Browse(szItemID, &szP2e, 0, dwBrowseFilter, szElementNameFilter, szVendorFilter,
                              true, false, 0, &propertyTable, &bMore, &dwNrReturned, &pElement) ; 
        pIBrowse->Release() ;
        if (FAILED(hr))
        {
            szMsg = L"rpc-opc-browse: Browse call failed" ;
            break ;
        }
        if (dwNrReturned)
        {
            item_id = new gsi_char* [dwNrReturned] ;
            if (!item_id)
            {
                szMsg = L"rpc-opc-browse: Unable to allocate item-id array. (Out of Memory?)" ;
                break ;
            }
            for (unsigned long iX = 0 ; iX < dwNrReturned ; iX++)
                item_id[iX] = (pElement+iX)->szItemID ;
            gsi_set_str_list(ret_vals[0], item_id, dwNrReturned) ;
        }
        error_code = 0 ;
        processing = false ;
        break ;
    }

    gsi_set_int(ret_vals[1], error_code) ;

    if (!szMsg)
        szMsg = L"OK";
    else
        log_message(errorLevel, szMsg, ctx_nr) ;
    gsi_set_str(ret_vals[2], szMsg) ;

    // Return the values to G2
    // -----------------------
    gsi_rpc_return_values(ret_vals, 3, call_index, ctx_nr) ;

    // Release the allocated memory
    // ----------------------------
    gsi_reclaim_items(ret_vals) ;
    if (szP2e)
        CoTaskMemFree(szP2e) ;
    if (pElement)
    {
        if (dwNrReturned)
            for (unsigned long lngX = 0 ; lngX < dwNrReturned ; lngX++)
            {
                if (pElement[lngX].szName)
                    CoTaskMemFree(pElement[lngX].szName) ;
                if (pElement[lngX].szItemID)
                    CoTaskMemFree(pElement[lngX].szItemID) ;
            }
        CoTaskMemFree(pElement) ;
    }
    if (item_id)
        delete [] item_id ;
}


/* ========================================================================== */
/*                                                                            */
/*  Implementation of rpc-opc-browsepart.  Similar to rpc-opc-browse except:  */
/*                                                                            */
/*  - includes a specification of the maximum number of items to return       */
/*  - if there are more items than the maximum to return, the call will       */
/*    return a "continuation point".  The continuation point can be passed    */
/*    to this method on subsequent calls to return the remaining items.       */
/*                                                                            */
/*                                                                            */
/*      Input arguments:                                                      */
/*            [0] - the name of a branch to browse or the NULL                */
/*                  string to start browsing from the root                    */
/*            [1] - continuation point.  NULL string the first time this      */
/*                  procedure is called for this branch location, the value   */
/*                  returned by the prior call to this procedure on           */
/*                  subsequent calls.                                         */
/*            [2] - maximum number of items to return                         */
/*            [3] - browse type                                               */
/*                  1 - all                                                   */
/*                  2 - branches                                              */
/*                  3 - leaves                                                */
/*            [4] - browse filter.  Similar to VB LIKE                        */
/*                                                                            */
/*      Returns:                                                              */
/*            [0] - text list containing requested item IDs                   */
/*            [1] - continuation point.  If not all the items were returned   */
/*                  and the OPC Server supports continuation points, a string */
/*                  that should be passed to the subsequent call of           */
/*                  rpc-opc-browsepart to get the next list of items          */
/*            [2] - a truth value that will be true if the OPC Server does    */
/*                  not support continuation points and not all the items     */
/*                  were returned.                                            */
/*            [3] - error code                                                */
/*                   0 success                                                */
/*                  -1 failed                                                 */
/*                   1 partially succeeded                                    */
/*            [4] - status message                                            */
/*                                                                            */
/* ========================================================================== */
void rpc_opc_browsepart(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool                validating = true,
                        processing ;
    gsi_int             ctx_nr ;
    gsi_int             max_returned ;
    gsi_item*           ret_vals = NULL ;
    gsi_char**          item_id = NULL ;
    gsi_symbol          class_name ;
    int                 error_code = -1 ;
    long                lngBrowseFilterNr ;
    long                cpSize ;
    short               errorLevel = TL_ERRORS ;

    BOOL                bMore = false ;
    DWORD               dwNrReturned  = 0 ;
    DWORD               propertyTable = 1 ;
    HRESULT             hr ;
    IOPCBrowse          *pIBrowse ;
    LPWSTR              szItemID;
    LPWSTR              szContinuationPt ;
    LPWSTR              szElementNameFilter ;
    LPWSTR              szVendorFilter = L"" ;
    LPWSTR              szMsg = NULL ;
    LPWSTR              szP2e = NULL ;
    OPCBROWSEELEMENT    *pElement = NULL ;
    OPCBROWSEFILTER     dwBrowseFilter ;


    ctx_nr = gsi_current_context() ;
    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    /* Validate the new settings */
    /* ------------------------- */
    while(validating)  // Provides an easy way to jump past
                       // code we do not wish to execute
    {
        ret_vals = gsi_make_items(5) ;
        if (!ret_vals)
        {
            szMsg = L"Unable to allocate return values. (Out of Memory?)" ;
            errorLevel = TL_CRITICAL ;
            break ;
        }

        // Build an array of return items with default values
        // --------------------------------------------------
        gsi_set_type(ret_vals[0], GSI_STRING_LIST_TAG) ;
        class_name = gsi_make_symbol(L"TEXT-LIST") ;
        gsi_set_class_name(ret_vals[0], class_name) ;
        gsi_set_str_list(ret_vals[0], NULL, 0) ;
        gsi_set_str(ret_vals[1],L"") ;
        gsi_set_log(ret_vals[2],GSI_FALSE) ;

        if (!context[ctx_nr].pServer)
        {
           szMsg = L"Not connected to server, rpc_opc_browse" ;
           break ;
        }

        // The following errors were treated as critical because 
        // they should not occur unless there is an error in the kb.
        if (count != 5)
        {
            szMsg = L"Wrong number of parameters to rpc_opc_browsepart" ;
            errorLevel = TL_CRITICAL ;
            break ;
        }

        if (gsi_type_of(rpc_arguments[0]) != GSI_STRING_TAG  ||
            gsi_type_of(rpc_arguments[1]) != GSI_STRING_TAG  ||
            gsi_type_of(rpc_arguments[2]) != GSI_INTEGER_TAG ||
            gsi_type_of(rpc_arguments[3]) != GSI_INTEGER_TAG ||
            gsi_type_of(rpc_arguments[4]) != GSI_STRING_TAG )
        {
            szMsg = L"Invalid parameter data type, rpc_opc_browsepart" ;
            errorLevel = TL_CRITICAL ;
            break ;
        }

        max_returned = gsi_int_of(rpc_arguments[2]) ;
        if (max_returned < 1)
        {
            szMsg = L"rpc_opc_browsepart: maximum items to return must be 1 or greater" ;
            break ;
        }
        lngBrowseFilterNr = gsi_int_of(rpc_arguments[3]) ;
        if (lngBrowseFilterNr < 1 || lngBrowseFilterNr > 3)
        {
            szMsg = L"rpc_opc_browsepart: invalid browse type number." ;
            break ;
        }
        validating = false ;
        break ;
    }

    // Get the list of items from the server
    // -------------------------------------
    processing = !validating ;
    while(processing)
    {
        szItemID = gsi_str_of(rpc_arguments[0]) ;
        szContinuationPt = gsi_str_of(rpc_arguments[1]) ;
        cpSize = (wcslen(szContinuationPt)+1) * sizeof(wchar_t) ;
        dwBrowseFilter = (OPCBROWSEFILTER)lngBrowseFilterNr ;
        szElementNameFilter = gsi_str_of(rpc_arguments[4]) ;

        // This feature is only supported by DAC 3.0 (at this writing)
        // The QueryInterface will fail if we are using an older OPC DAC
        // -------------------------------------------------------------
        hr = context[ctx_nr].pServer->m_pOPCServer->QueryInterface(IID_IOPCBrowse, (void**)&pIBrowse) ;
        if (FAILED(hr))
        {
            szMsg = L"rpc-opc-browsepart: Unable to find browse interface (old server?)" ;
            break ;
        }

        szP2e = (LPWSTR)CoTaskMemAlloc(cpSize) ;
        wcscpy(szP2e,szContinuationPt) ;

        hr = pIBrowse->Browse(szItemID, &szP2e, max_returned, dwBrowseFilter, szElementNameFilter, szVendorFilter,
                              true, false, 0, &propertyTable, &bMore, &dwNrReturned, &pElement) ; 
        pIBrowse->Release() ;
        if (FAILED(hr))
        {
            szMsg = L"rpc-opc-browsepart: Browse call failed" ;
            break ;
        }
        if (dwNrReturned)
        {
            item_id = new gsi_char* [dwNrReturned] ;
            if (!item_id)
            {
                szMsg = L"rpc-opc-browsepart: Unable to allocate item-id array. (Out of Memory?)" ;
                break ;
            }
            for (unsigned long iX = 0 ; iX < dwNrReturned ; iX++)
                item_id[iX] = (pElement+iX)->szItemID ;
            gsi_set_str_list(ret_vals[0], item_id, dwNrReturned) ;
        }
        error_code = 0 ;
        processing = false ;
        break ;
    }


    // Return the results to G2 & Clean Up
    // -----------------------------------
    if (!error_code)
        szMsg = L"OK";
    else
        log_message(errorLevel, szMsg, ctx_nr) ;

    if (ret_vals)
    {
        
        gsi_set_str(ret_vals[1], error_code ? L"" : szP2e) ;       
        gsi_set_log(ret_vals[2], error_code ? GSI_FALSE : (bMore ? GSI_TRUE : GSI_FALSE));
        gsi_set_int(ret_vals[3], error_code) ;
        gsi_set_str(ret_vals[4], szMsg) ;

        // Return the values to G2
        // -----------------------
        gsi_rpc_return_values(ret_vals, 5, call_index, ctx_nr) ;

        // Release the allocated memory
        // ----------------------------
        gsi_reclaim_items(ret_vals) ;
        if (szP2e)
            CoTaskMemFree(szP2e) ;
        if (pElement)
        {
            if (dwNrReturned)
                for (unsigned long lngX = 0 ; lngX < dwNrReturned ; lngX++)
                {
                    if (pElement[lngX].szName)
                        CoTaskMemFree(pElement[lngX].szName) ;
                    if (pElement[lngX].szItemID)
                        CoTaskMemFree(pElement[lngX].szItemID) ;
                }
            CoTaskMemFree(pElement) ;
        }
        if (item_id)
            delete [] item_id ;
    }
}



// ========================================================================== //
//                                                                            //
//        Return a list of the item properties associated with an item        //
//                                                                            //
//          OPC 3.0 Server required.  Uses IOPCBrowse::GetProperties.         //
//                                                                            //
// ========================================================================== //
HRESULT GetItemProperties(IOPCServer* pOPCServer, gsi_char* szItemID, int& nr_props, gsi_item*& pPropIdArray,
                          gsi_char**& pPropDescArray, gsi_char**& pPropTypeArray, gsi_char**& pPropValArray,
                          LPWSTR& szMsg);

void rpc_opc_getproperties(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    bool                newly_validating ;
    DWORD               bogus               = 0 ;
    gsi_char**          pPropDescArray      = NULL ;
    gsi_char**          pPropTypeArray      = NULL ;
    gsi_char**          pPropValArray       = NULL ;
    gsi_int             ctx_nr ;
    gsi_int             error_code          = -1 ;
    gsi_int             nr_props            = 0 ;
    gsi_item*           pPropIdArray        = NULL ;
    gsi_item*           ret_vals            = NULL ;
    gsi_symbol          class_name ;
    HRESULT             hr ;
    LPWSTR              szMsg               = NULL ;

    ctx_nr = gsi_current_context() ;
    if (ctx_nr < 0 || ctx_nr >= MAX_GDB_CONTEXTS)
        return ;

    // Allocate & initialize return values
    // -----------------------------------
    ret_vals = gsi_make_items(7) ;
    if (!ret_vals)
    {
        szMsg = L"Unable to allocate return values. (Out of Memory?)" ;
        log_message(TL_CRITICAL, szMsg, ctx_nr) ;
        return ;
    }

    // The data types of the returned lists are illogical but were
    // chosen to maintain compatibility with prior versions of OPCLink
    // ---------------------------------------------------------------
    gsi_set_int(ret_vals[0], 0) ;                                           // 0: number of properties
    class_name = gsi_make_symbol(L"VALUE-LIST") ;
    gsi_set_class_name(ret_vals[1], class_name) ;
    gsi_set_elements(ret_vals[1], pPropIdArray, 0, GSI_VALUE_LIST_TAG) ;    // 1: property IDs
    gsi_set_type(ret_vals[2], GSI_STRING_LIST_TAG) ;                        // 2: property description
    class_name = gsi_make_symbol(L"TEXT-LIST") ;
    gsi_set_class_name(ret_vals[2], class_name) ;
    gsi_set_type(ret_vals[2], GSI_NULL_TAG) ;
    gsi_set_type(ret_vals[3], GSI_STRING_LIST_TAG) ;                        // 3: property type
    gsi_set_class_name(ret_vals[3], class_name) ;
    gsi_set_type(ret_vals[3], GSI_NULL_TAG) ;
    gsi_set_type(ret_vals[4], GSI_STRING_LIST_TAG) ;                        // 4: property value
    gsi_set_class_name(ret_vals[4], class_name) ;
    gsi_set_type(ret_vals[4], GSI_NULL_TAG) ;



    // Validate input: We are connected to a server, it supports IOPCBrowse,
    // and there is one textual input.
    // ---------------------------------------------------------------------
    newly_validating = true ;
    while(newly_validating)  // Provides an easy way to jump past
                             // code we do not wish to execute
    {
        newly_validating = false ;

        if (!context[ctx_nr].pServer)
        {
           szMsg = L"rpc-opc-getproperties: Not connected to server" ;
           break ;
        }

        if (count != 1)
        {
            szMsg = L"Number of arguments not equal to 1";
            break ;
        }
        if (gsi_type_of(rpc_arguments[0]) != GSI_STRING_TAG)
        {
            szMsg = L"rpc-opc-getproperties: Item ID should be a string" ;
            break ;
        }
    }

    if (szMsg == NULL)
    {
        gsi_char* pItemID = gsi_str_of(rpc_arguments[0]);
        int nPropCount = nr_props;
        hr = GetItemProperties(context[ctx_nr].pServer->m_pOPCServer, pItemID, nPropCount,
            pPropIdArray, pPropDescArray, pPropTypeArray, pPropValArray, szMsg);

        nr_props = nPropCount;

        if (SUCCEEDED(hr) && szMsg == NULL)
        {
            gsi_set_int(ret_vals[0], nr_props) ;
            gsi_set_elements(ret_vals[1],pPropIdArray, nr_props, GSI_VALUE_LIST_TAG) ;
            gsi_set_str_list(ret_vals[2],pPropDescArray, nr_props) ;
            gsi_set_str_list(ret_vals[3],pPropTypeArray, nr_props) ;
            gsi_set_str_list(ret_vals[4],pPropValArray,  nr_props) ;
            error_code = 0 ;
        }
    }
    gsi_set_int(ret_vals[5], error_code) ;
    gsi_set_str(ret_vals[6], (szMsg == NULL) ? L"" : szMsg) ;

    // Return the results to G2
    // ------------------------
    gsi_rpc_return_values(ret_vals, 7, call_index, gsi_current_context()) ;


    // Free all the memory we used
    // ---------------------------
    if (pPropIdArray)
        gsi_reclaim_items(pPropIdArray) ;    
    if (pPropDescArray)
    {
        for (long lngX=0 ; lngX < nr_props ; lngX++)
            if (pPropDescArray[lngX]) SysFreeString(pPropDescArray[lngX]) ;
        delete [] pPropDescArray ;
    }
    if (pPropTypeArray)
    {
        for (long lngX=0 ; lngX < nr_props ; lngX++)
            if (pPropTypeArray[lngX]) SysFreeString(pPropTypeArray[lngX]) ;
        delete [] pPropTypeArray ;
    }
    if (pPropValArray)  
    {
        for (long lngX=0 ; lngX < nr_props ; lngX++)
            if (pPropValArray[lngX]) SysFreeString(pPropValArray[lngX]) ;
        delete [] pPropValArray ;
    }

    gsi_reclaim_items(ret_vals) ;

}

HRESULT GetItemProperties(IOPCServer* pOPCServer, gsi_char* pItemID, int& nr_props, gsi_item*& pPropIdArray,
                          gsi_char**& pPropDescArray, gsi_char**& pPropTypeArray, gsi_char**& pPropValArray,
                          LPWSTR& szMsg)
{
    OPCITEMPROPERTIES   *pItemPropContainer = NULL ;
    DWORD               *pPropertyIDs       = NULL;
    LPWSTR              *pDescriptions      = NULL;
    VARTYPE             *pvtDataTypes       = NULL;
    VARIANT             *pvData             = NULL;


    IOPCBrowse* pIBrowse = NULL;
    IOPCItemProperties* pItemsProperties = NULL;

    // Get IOPCBrowse interface if there is the OPC DA 3.0
    HRESULT hr = pOPCServer->QueryInterface(IID_IOPCBrowse, (void**) &pIBrowse);

    if (hr == E_NOINTERFACE)
    {
        // Get IOPCItemProperties interface if there is the OPC DA 2.0
        hr = pOPCServer->QueryInterface(IID_IOPCItemProperties, (void**) &pItemsProperties);
    }

    if (FAILED(hr))
    {
        szMsg = L"rpc-opc-getproperties: Unable to find browse interface (old server?)" ;
    }

    // Get properties
    if (szMsg == NULL)
    {
        DWORD   dwItemCount = 1 ;
        DWORD   dwPropCount = 0 ;

        if (pIBrowse != NULL)
        {
            DWORD bogus = 0;
            hr = pIBrowse->GetProperties(dwItemCount, &pItemID, true, dwPropCount, &bogus, &pItemPropContainer) ;
            if (SUCCEEDED(hr) && pItemPropContainer != NULL)
            {
                nr_props = (long)pItemPropContainer->dwNumProperties;
            }
        }
        else if (pItemsProperties != NULL)
        {
            DWORD dwCount = 0;
            hr = pItemsProperties->QueryAvailableProperties(pItemID, &dwCount, &pPropertyIDs, &pDescriptions, &pvtDataTypes);

            if (SUCCEEDED(hr))
            {
                nr_props = dwCount;
                HRESULT *pErrors = NULL;

                hr = pItemsProperties->GetItemProperties(pItemID, dwCount, pPropertyIDs, &pvData, &pErrors);

                if (pErrors != NULL)
                {
                    CoTaskMemFree(pErrors);
                }
            }
        }

        // Create properties
        if (FAILED(hr) || pItemPropContainer == NULL && pIBrowse != NULL)
        {
            szMsg = L"Server failed to retrieve properties";
        }
        else
        {
            if (nr_props)
            {
                pPropIdArray   = gsi_make_items(nr_props) ;
                pPropDescArray = new gsi_char* [nr_props] ;
                pPropTypeArray = new gsi_char* [nr_props] ;
                pPropValArray  = new gsi_char* [nr_props] ;
                if (!pPropIdArray || !pPropDescArray || !pPropTypeArray || !pPropValArray)
                {
                    szMsg = L"Unable to allocate return values. (Out of Memory?)" ;
                    log_message(TL_CRITICAL, szMsg, gsi_current_context()) ;
                }
            }
        }
    }

    // Copy properties
    if (szMsg == NULL)
    {
        OPCITEMPROPERTY* pItemPropStruct = NULL;

        if (pIBrowse != NULL)
        {
            pItemPropStruct = pItemPropContainer->pItemProperties ;
        }
        for (long lx = 0 ; lx < nr_props ; lx++)
        {
            DWORD dwItemId = pIBrowse != NULL ? pItemPropStruct[lx].dwPropertyID : pPropertyIDs[lx];
            LPWSTR szDescription = pIBrowse != NULL ? pItemPropStruct[lx].szDescription : pDescriptions[lx];
            VARTYPE varType = pIBrowse != NULL ? pItemPropStruct[lx].vtDataType : pvtDataTypes[lx];
            VARIANT vValue = pIBrowse != NULL ? pItemPropStruct[lx].vValue : pvData[lx];

            gsi_set_flt(pPropIdArray[lx], (double) dwItemId) ;
            pPropDescArray[lx] = SysAllocString(szDescription) ;
            pPropTypeArray[lx] = OpcUtils::ConvertVariantTypeToText(varType) ;
            pPropValArray[lx]  = OpcUtils::CStr(vValue) ;
        }
    }

    // Free all the memory we used
    // ---------------------------
    if (pIBrowse)
    {
        pIBrowse->Release();
    }
    if (pItemsProperties)
    {
        pItemsProperties->Release();
    }

    if (pPropertyIDs)
    {
        CoTaskMemFree(pPropertyIDs);
    }

    if (pvtDataTypes)
    {
        CoTaskMemFree(pvtDataTypes);
    }

    if (pvData)
    {
        for (int i = 0 ; i < nr_props ; i++)
            VariantClear(&pvData[i]) ;
        CoTaskMemFree(pvData) ;
    }

    if (pItemPropContainer)
    {
        if (pItemPropContainer->pItemProperties)
        {
            for (int i = 0 ; i < nr_props ; i++)
                VariantClear(&pItemPropContainer->pItemProperties[i].vValue) ;
            CoTaskMemFree(pItemPropContainer->pItemProperties) ;
        }
        CoTaskMemFree(pItemPropContainer) ;
    }

    return hr;
}

// =========================================================================  //
//                                                                            //
//               Specify the severity of messages to be logged                //
//                                                                            //
// =========================================================================  //
void g2_opc_set_tracelevel(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_item    *pRetVal = gsi_make_items(1) ;
    long        errFlag = -1 ;   // Assume failure
    long        newLevel ;

    // Validate input & extract new logging level
    // ------------------------------------------
    if (count == 1)
        if (gsi_type_of(rpc_arguments[0]) == GSI_INTEGER_TAG)
        {
            newLevel = gsi_int_of(rpc_arguments[0]) ;
            if (newLevel >= TL_FATAL_ONLY && newLevel <= TL_INFO)
            {
                errFlag = 0 ;   // Success
                g_traceLevel = (short)newLevel ;
            }
        }

    gsi_set_int(pRetVal[0],errFlag) ; 
    gsi_rpc_return_values(pRetVal, 1, call_index, gsi_current_context()) ;
    gsi_reclaim_items(pRetVal) ;
}


/* ========================================================================== */
/*                                                                            */
/*                               Turn on tracing                              */
/*                                                                            */
/* ========================================================================== */
void g2_opc_tracestart(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_item    *pRetVal = gsi_make_items(1) ;

    if (count == 0)
    {
        g_traceOn = false ;
        gsi_set_int(pRetVal[0], 0) ;
    }
    else
        gsi_set_int(pRetVal[0], -1) ; 
    gsi_rpc_return_values(pRetVal, 1, call_index, gsi_current_context()) ;
    gsi_reclaim_items(pRetVal) ;
}


/* ========================================================================== */
/*                                                                            */
/*                              Turn off tracing                              */
/*                                                                            */
/* ========================================================================== */
void g2_opc_tracestop(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_item    *pRetVal = gsi_make_items(1) ;

    if (count == 0)
    {
        g_traceOn = true ;
        gsi_set_int(pRetVal[0], 0) ;
    }
    else
        gsi_set_int(pRetVal[0], -1) ; 
    gsi_rpc_return_values(pRetVal, 1, call_index, gsi_current_context()) ;
    gsi_reclaim_items(pRetVal) ;
}


/* ========================================================================== */
/*                                                                            */
/*                Enable or disable tracing to G2 message board               */
/*                                                                            */
/* ========================================================================== */
void g2_opc_trace_to_g2(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_item    *pRetVal = gsi_make_items(1) ;
    long        errFlag = -1 ;   // Assume failure
    long        newState ;

    // Validate input & set new trace-to-G2 state
    // ------------------------------------------
    if (count == 1)
        if (gsi_type_of(rpc_arguments[0]) == GSI_LOGICAL_TAG)
        {
            newState = gsi_log_of(rpc_arguments[0]) ;
            g_logToG2 = (newState == GSI_TRUE) ? true : false ;
            errFlag = 0 ;   // Success
        }

    gsi_set_int(pRetVal[0],errFlag) ; 
    gsi_rpc_return_values(pRetVal, 1, call_index, gsi_current_context()) ;
    gsi_reclaim_items(pRetVal) ;
}


/* ========================================================================== */
/*                                                                            */
/*                    Enable or disable tracing to console                    */
/*                                                                            */
/* ========================================================================== */
void g2_opc_trace_to_stdout(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_item    *pRetVal = gsi_make_items(1) ;
    long        errFlag = -1 ;   // Assume failure
    long        newState ;

    // Validate input & set new trace-to-stdout state
    // ----------------------------------------------
    if (count == 1)
        if (gsi_type_of(rpc_arguments[0]) == GSI_LOGICAL_TAG)
        {
            newState = gsi_log_of(rpc_arguments[0]) ;
            g_logToStdout = (newState == GSI_TRUE) ? true : false ;
            errFlag = 0 ;   // Success
        }

    gsi_set_int(pRetVal[0],errFlag) ; 
    gsi_rpc_return_values(pRetVal, 1, call_index, gsi_current_context()) ;
    gsi_reclaim_items(pRetVal) ;
}


/* ========================================================================== */
/*                                                                            */
/*        Turn on or off the use of a timestamp with the logged message       */
/*                                                                            */
/* ========================================================================== */
void g2_opc_set_tracewithtime(gsi_item *rpc_arguments, gsi_int count, gsi_int call_index)
{
    gsi_item    *pRetVal = gsi_make_items(1) ;
    long        errFlag = -1 ;   // Assume failure
    long        newState ;

    // Validate input & set new trace-to-stdout state
    // ----------------------------------------------
    if (count == 1)
        if (gsi_type_of(rpc_arguments[0]) == GSI_LOGICAL_TAG)
        {
            newState = gsi_log_of(rpc_arguments[0]) ;
            g_traceWithTime = (newState == GSI_TRUE) ? true : false ;
            errFlag = 0 ;   // Success
        }

    gsi_set_int(pRetVal[0],errFlag) ; 
    gsi_rpc_return_values(pRetVal, 1, call_index, gsi_current_context()) ;
    gsi_reclaim_items(pRetVal) ;
}
