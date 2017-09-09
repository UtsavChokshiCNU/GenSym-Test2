// OPCShutdown.cpp: implementation of the COPCShutdown class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <opccomn_i.c>
#include "OPCShutdown.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COPCShutdown::COPCShutdown() : m_cRef(1)
{
}


COPCShutdown::~COPCShutdown(void)
{
}


STDMETHODIMP COPCShutdown::QueryInterface(REFIID riid, void** ppv)
{
    *ppv = NULL;
    if (IID_IUnknown == riid || IID_IOPCShutdown == riid)
        *ppv = this;
    if (NULL!=*ppv)
    {
        ((LPUNKNOWN)*ppv)->AddRef();
        return S_OK ;
    }

    return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) COPCShutdown::AddRef(void)
{
    return ++m_cRef;
}


STDMETHODIMP_(ULONG) COPCShutdown::Release(void)
{
    if (0 != --m_cRef)
        return m_cRef;

    delete this;
    return 0;
}

STDMETHODIMP COPCShutdown::ShutdownRequest(LPCWSTR szReason)
{
    long    i, server_nr, nr_servers ;

    log_message(TL_INFO, L"Shutdown Request") ;

    // Find the CServer that points to this COPCShutdown
    // -------------------------------------------------
    for (i=0, nr_servers=0 ;  i<MAX_GDB_CONTEXTS && nr_servers<g_nr_servers; i++)
        if (g_servers[i].mp_shutdown_object == this)
            break ;
        else if (g_servers[i].m_pOPCServer)
            nr_servers++ ;

    if (i >= g_nr_servers)
    {
        log_message(TL_ERRORS, L"Cannot find server to shut down");
        return E_FAIL ;
    }

    // Find every context that uses this server and disconnect it from the server
    // --------------------------------------------------------------------------
    context_info    *pCtx ;
    server_nr = i ;
    for (i=0, pCtx=context ; i < MAX_GDB_CONTEXTS && g_servers[server_nr].m_nr_ctxs_using ; i++, pCtx++)
        if (pCtx->pServer == &g_servers[server_nr])
            shutdown_context(i,false) ;
        

    return S_OK;
}
