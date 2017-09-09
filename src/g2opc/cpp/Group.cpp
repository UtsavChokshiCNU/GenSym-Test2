// Group.cpp: implementation of the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Group.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CGroup::CGroup(gsi_int ctxNr, OPCHANDLE server_assigned_hdl) : m_ctxNr(ctxNr), 
                                           m_group_handle(server_assigned_hdl), mp_Next(NULL)
{
    mp_callback_object = new COPCDataCallback(ctxNr) ;
    mp_advise_sink     = new CAdviseSink(this) ;
}


/* ========================================================================== */
/*                                                                            */
/*       We shutdown an OPCGroup by deleting its associated Group object.     */
/*                                                                            */
/*   - if we have set this group up for data callbacks, Unadvise the server   */
/*   - release the callback object                                            */
/*   - release the callback connection point                                  */
/*   - release the data callback object                                       */
/*   - remove every item from the group                                       */
/*   - free the item table                                                    */
/*   - deregister the OPCGroup from the OPCServer                             */
/*   - release the OPCGroup                                                   */
/*   - take the Group object out of the Server's chain of Groups              */
/*                                                                            */
/* ========================================================================== */
CGroup::~CGroup()
{
    context_info    *pCtxInfo = NULL ;
    CServer         *pServer ;
    IDataObject     *pIDO = NULL ;
    IOPCServer      *pOPCServer = NULL ;
    HRESULT         hr ;
    long            dbgRefCt ;

    if (m_ctxNr >= 0 && m_ctxNr < MAX_GDB_CONTEXTS)
    {
        pCtxInfo = &context[m_ctxNr] ;
        pServer = pCtxInfo->pServer ;
        if (pServer)
            pOPCServer = pServer->m_pOPCServer ;

        // Stop data callbacks
        // -------------------
        if (pCtxInfo->p_ConnectionPoint)
        {
            if (pCtxInfo->dcb_cookie && pCtxInfo->b_usesV2dcb)
            {
                hr = pCtxInfo->p_ConnectionPoint->Unadvise(pCtxInfo->dcb_cookie) ;
                pCtxInfo->dcb_cookie = 0 ;
            }
            dbgRefCt = pCtxInfo->p_ConnectionPoint->Release() ;
        }

        // If we have OPC 1.0A Callbacks, break the connection
        // ---------------------------------------------------
        if (pCtxInfo->dcb_cookie)  // && !pCtxInfo->b_usesV2dcb
        {
            if (pCtxInfo->pItemMgt && SUCCEEDED(pCtxInfo->pItemMgt->QueryInterface(IID_IDataObject,(LPVOID*)&pIDO)))
                pIDO->DUnadvise(pCtxInfo->dcb_cookie) ;
            pCtxInfo->dcb_cookie = 0 ;
        }

        // Release the data callback object
        // --------------------------------
        if (mp_callback_object)
        {
            dbgRefCt = mp_callback_object->Release() ;
            mp_callback_object = NULL ;
        }

        // Release the AdviseSink
        // ----------------------
        if (mp_advise_sink)
        {
            dbgRefCt = mp_advise_sink->Release() ;
            mp_advise_sink = NULL ;
        }

        // Clean up any items that are still associated with this group
        // ------------------------------------------------------------
        if (pCtxInfo->pItemTable)
        {
            OPCHANDLE   *phServer = NULL ;
            HRESULT     *pErrors = NULL ;

            if (pCtxInfo->nrItems && pCtxInfo->pItemMgt)
                phServer = new OPCHANDLE[pCtxInfo->nrItems] ;
            
            for (long L=0 ; L < pCtxInfo->nrItems ; L++)
            {
                if (phServer)
                    phServer[L] = pCtxInfo->pItemTable[L].hItemS ;
                if (pCtxInfo->pItemTable[L].pVals)
                {
                    VariantClear(&pCtxInfo->pItemTable[L].pVals->value) ;
                    delete pCtxInfo->pItemTable[L].pVals ;
                    pCtxInfo->pItemTable[pCtxInfo->nrItems].hItem = pCtxInfo->pItemTable[pCtxInfo->nrItems].hItemS = 0 ;
                    pCtxInfo->pItemTable[L].pVals = NULL ;
                }
            }

            if (phServer)
            {
                hr = pCtxInfo->pItemMgt->RemoveItems(pCtxInfo->nrItems, phServer, &pErrors) ;
                if (hr != S_OK)
                    log_message(TL_ERRORS,L"Failed to remove some or all items");
                if (pErrors)
                    CoTaskMemFree(pErrors);
            }

            delete [] pCtxInfo->pItemTable ;
            pCtxInfo->pItemTable = NULL ;
            pCtxInfo->nrItems = 0 ;
        }

        // Remove the OPCGroup from the list processed by the OPCServer
        // ------------------------------------------------------------
        if (pCtxInfo->hGroupS)
            hr = pOPCServer->RemoveGroup(pCtxInfo->hGroupS, TRUE) ;
    }

}
