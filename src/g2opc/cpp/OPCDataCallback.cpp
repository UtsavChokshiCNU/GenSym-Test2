/* ========================================================================== */
/*                                                                            */
/*  The OPCDataCallback object manages data received asynchronously and by    */
/*  subscription from OPC 2 & 3 servers.                                      */
/*                                                                            */
/* ========================================================================== */
#include "stdafx.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COPCDataCallback::COPCDataCallback(gsi_int ctx_nr) : m_cRef(1), m_ctxNr(ctx_nr)
{
}


COPCDataCallback::~COPCDataCallback() { }


HRESULT COPCDataCallback::QueryInterface(REFIID riid, void * * pIReq)
{
    if (riid == IID_IUnknown)
        *pIReq = (IUnknown*)this ;
    else if (riid == IID_IOPCDataCallback)
        *pIReq = (IOPCDataCallback*)this ;
    else
    {
        *pIReq = NULL ;
        return E_NOINTERFACE ;
    }
    ((IUnknown*)(*pIReq))->AddRef() ;
    return S_OK ;
}


ULONG COPCDataCallback::AddRef()
{
    return ++m_cRef ;
}

ULONG COPCDataCallback::Release()
{
    if (--m_cRef == 0)
    {
        delete this ;
        return 0 ;
    }
    return m_cRef ;
}



/* ========================================================================== */
/*                                                                            */
/*   This is where the bridges receives values, qualities, and timestamps by  */
/*   subscription from OPC 2/3 servers.  The information is packed into a     */
/*   context-specific table for processing by the GSI thread.                 */
/*                                                                            */
/* ========================================================================== */
HRESULT COPCDataCallback::OnDataChange(DWORD dwTransid, OPCHANDLE hGroup, HRESULT hrMasterquality,
                                       HRESULT hrMastererror, DWORD dwCount, OPCHANDLE * phClientItems,
                                       VARIANT * pvValues, WORD * pwQualities, 
                                       FILETIME * pftTimeStamps, HRESULT *pErrors)
{
    bool            found ;
    gsi_int         ctxNr ;
    item_values     *pVals ;
    long            itemTableLoc ;

    DWORD           dwX = 0;
    OPCHANDLE       *pHdl = phClientItems ;
    VARIANT         *pVar = pvValues ;
    WORD            *pQuality = pwQualities ;
    FILETIME        *pTimeStamp = pftTimeStamps ;
    HRESULT         *phr = pErrors ;

    // Get the context number
    // ----------------------
    ctxNr = context_nr() ;
    if (ctxNr < 0 || ctxNr >= MAX_GDB_CONTEXTS)
        return E_FAIL ;

    context_info    *pCtx = &context[ctxNr] ;

    // Only update on gsi_get_data if in synchronous mode
    // --------------------------------------------------
    if (pCtx->sync_mode)
        return E_FAIL ;

    while (dwX < dwCount)
    {
        EnterCriticalSection(&crtsec_items) ;
        itemTableLoc=OpcUtils::FindItemHdl(*pHdl, ctxNr, &found) ;
        if (!found)
            log_message(TL_ERRORS, L"Handle not found for item in table") ;
        else
        {
            if ((pVals = pCtx->pItemTable[itemTableLoc].pVals) == NULL)
                pVals = pCtx->pItemTable[itemTableLoc].pVals = new item_values ;
            pVals->quality = *pQuality ;
            pVals->status = *pErrors ;
            pVals->timestamp = *pTimeStamp ;
            VariantInit(&pVals->value) ;
            VariantCopy(&(pVals->value), pVar) ;
            if (!pCtx->queued_for_async_processing)
            {
                async_processing_queue.push(ctxNr) ;
                pCtx->queued_for_async_processing = true ;
            }
        }
        LeaveCriticalSection(&crtsec_items) ;
        pHdl++ ;
        pVar++ ;
        pQuality++ ;
        pTimeStamp++ ;
        phr++ ;
        dwX++ ;
    }
    

    
    return S_OK ;
}


// Almost Identical to OnDataChange
// ================================
HRESULT COPCDataCallback::OnReadComplete(DWORD dwTransid, OPCHANDLE hGroup, HRESULT hrMasterquality,
                                         HRESULT hrMastererror, DWORD dwCount, OPCHANDLE * phClientItems,
                                         VARIANT * pvValues, WORD * pwQualities, FILETIME * pftTimeStamps,
                                         HRESULT *pErrors)
{
    log_message(TL_INFO,L"OnReadComplete Callback") ;
    bool            found ;
    gsi_int         ctxNr ;
    item_values     *pVals ;
    long            itemTableLoc ;

    DWORD           dwX = 0;
    OPCHANDLE       *pHdl = phClientItems ;
    VARIANT         *pVar = pvValues ;
    WORD            *pQuality = pwQualities ;
    FILETIME        *pTimeStamp = pftTimeStamps ;
    HRESULT         *phr = pErrors ;

    // Get the context number
    // ----------------------
    ctxNr = context_nr() ;
    if (ctxNr < 0 || ctxNr >= MAX_GDB_CONTEXTS)
        return E_FAIL ;

    context_info    *pCtx = &context[ctxNr] ;

    while (dwX < dwCount)
    {
        EnterCriticalSection(&crtsec_items) ;
        itemTableLoc=OpcUtils::FindItemHdl(*pHdl, ctxNr, &found) ;
        if (!found)
            log_message(TL_ERRORS, L"Handle not found for item in table") ;
        else
        {
            if ((pVals = pCtx->pItemTable[itemTableLoc].pVals) == NULL)
                pVals = pCtx->pItemTable[itemTableLoc].pVals = new item_values ;
            pVals->quality = *pQuality ;
            pVals->status = *pErrors ;
            pVals->timestamp = *pTimeStamp ;
            VariantInit(&pVals->value) ;
            VariantCopy(&(pVals->value), pVar) ;
            if (!pCtx->queued_for_async_processing)
            {
                async_processing_queue.push(ctxNr) ;
                pCtx->queued_for_async_processing = true ;
            }
        }
        LeaveCriticalSection(&crtsec_items) ;
        pHdl++ ;
        pVar++ ;
        pQuality++ ;
        pTimeStamp++ ;
        phr++ ;
        dwX++ ;
    }    
    
    return S_OK ;
}


HRESULT COPCDataCallback::OnWriteComplete(DWORD dwTransid, OPCHANDLE hGroup, HRESULT hrMasterError,
                                          DWORD dwCount, OPCHANDLE * phClientItems, HRESULT * pError)
{
    log_message(TL_INFO,L"OnWriteComplete Callback") ;
    return S_OK ;
}


HRESULT COPCDataCallback::OnCancelComplete(DWORD dwTransid, OPCHANDLE hGroupunsigned)
{
    log_message(TL_INFO,L"OnCancelComplete Callback") ;
    return S_OK ;
}


gsi_int COPCDataCallback::context_nr()
{
    return m_ctxNr ;
}



/* ========================================================================== */
/*                                                                            */
/*      The AdviseSink object manages data received asynchronously and by     */
/*      subscription from OPC 1 servers    .                                  */
/*                                                                            */
/* ========================================================================== */
CAdviseSink::CAdviseSink(CGroup * pGrp) : m_cRef(1), mp_Grp(pGrp)
{
    m_data = RegisterClipboardFormat(L"OPCSTMFORMATDATA") ;
    m_datatime = RegisterClipboardFormat(L"OPCSTMFORMATDATATIME") ;
    m_write = RegisterClipboardFormat(L"OPCSTMFORMATWRITECOMPLETE") ;
}

CAdviseSink::~CAdviseSink(void) {}

HRESULT CAdviseSink::QueryInterface(REFIID riid, void * * pIReq)
{
    if (riid == IID_IUnknown)
        *pIReq = (IUnknown*)this ;
    else if (riid == IID_IAdviseSink)
        *pIReq = (IAdviseSink*)this ;
    else
    {
        *pIReq = NULL ;
        return E_NOINTERFACE ;
    }
    ((IUnknown*)(*pIReq))->AddRef() ;
    return S_OK ;
}

ULONG CAdviseSink::AddRef()
{
    return ++m_cRef ;
}

ULONG CAdviseSink::Release()
{
    if (--m_cRef == 0)
    {
        delete this ;
        return 0 ;
    }
    return m_cRef ;
}


/* ========================================================================== */
/*                                                                            */
/*   This is where the bridges receives values, qualities, and timestamps by  */
/*   subscription from OPC 1 servers.  The information is extracted from the  */
/*   stream and put into a format that can be processed by the OPC 2/3        */
/*   callback object.  The OnDataChange of the OPC 2/3 callback object then   */
/*   prepares the input for processing by the GSI thread.                     */
/*                                                                            */
/* ========================================================================== */
void CAdviseSink::OnDataChange(LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{

    // Sanity checks...
    // If wrong storage medium or null pointer 
    // we can't handle it
    //
    if( TYMED_HGLOBAL != pFE->tymed )
    {
        log_message(TL_ERRORS,L"IAdviseSink Callback Error:Bad tymed (not HGLOBAL)");
        return;
    }
    if( pSTM->hGlobal == 0 )
    {
        log_message(TL_ERRORS, L"IAdviseSink Callback Error:Bad hGlobal");
        return;
    }
    if(pFE->cfFormat != m_datatime)
    {
        log_message(TL_ERRORS, L"IAdviseSink Callback Error: Unexpected format");
        return;
    }


    DWORD           count;
    OPCGROUPHEADER  *grp;
    char            *iptr;
    char            *dptr;
    char            *sptr;
    HRESULT         masterquality;
    unsigned int    i;

    sptr = (char*)GlobalLock(pSTM->hGlobal);
    if(!sptr) return;
    grp = (OPCGROUPHEADER*)sptr;
    if(FAILED(grp->hrStatus))
    {
        log_message_d(TL_ERRORS, L"IAdviseSink Callback Error: hr = ", grp->hrStatus);
        return;
    }

    // Allocate some memory into which to put the returned data
    // --------------------------------------------------------
    OPCHANDLE * handles;
    WORD      * quality;
    VARIANT   * values; 
    FILETIME  * ft;
    HRESULT   * pErrors ;

    count = grp->dwItemCount;

    masterquality = S_OK ;
    handles = new OPCHANDLE[count];
    values  = new VARIANT[count];
    quality = new WORD[count];
    ft      = new FILETIME[count];
    pErrors = new HRESULT [count] ;

    for(i=0; i<count; i++)
    {
        VariantInit(&values[i]);
        pErrors[i] = S_OK ;
    }
    
    // Figure out where the ITEM headers start
    // And also where the DATA starts
    // We will read the two areas in parallel
    // ---------------------------------------
    iptr = sptr + sizeof(OPCGROUPHEADER);
    dptr = iptr + (count * sizeof(OPCITEMHEADER1)); 

    // For each ITEM in the stream...
    // ------------------------------
    for(i=0; i< count; i++)
    {
        OPCITEMHEADER1 * item;

        // find the next item header
        //
        item = (OPCITEMHEADER1*)iptr;
        iptr += sizeof( OPCITEMHEADER1 );

        // Find the data for the item
        //
        dptr = sptr + item->dwValueOffset;

        // Copy the client handle and quality
        //
        handles[i] = item->hClient;
        quality[i] = item->wQuality;
        ft[i] = item->ftTimeStampItem;
        if(quality[i] != OPC_QUALITY_GOOD) 
            masterquality = S_FALSE ;
        VariantCopy(&values[i],(VARIANT*)dptr) ;
    }

    if (count && mp_Grp && mp_Grp->mp_advise_sink)
        mp_Grp->mp_callback_object->OnDataChange(grp->dwTransactionID,grp->hClientGroup,masterquality,S_OK, count,
                                                    handles, values, quality, ft, pErrors);


    // Free all of the scratch variables
    //
    for(i=0; i<count; i++) 
    {
        VariantClear(&values[i]);
    }

    if(handles) delete [] handles;
    if(values) delete [] values;
    if(quality) delete [] quality;
    if(ft) delete [] ft;
    if(pErrors) delete [] pErrors;

}

void CAdviseSink::OnViewChange(DWORD, LONG) {} 
void CAdviseSink::OnRename(LPMONIKER)       {} 
void CAdviseSink::OnSave(void)              {} 
void CAdviseSink::OnClose(void)             {} 
