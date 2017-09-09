// OPCShutdownObj.cpp: implementation of the COPCShutdownObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPCShutdown.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COPCShutdown::COPCShutdown() : m_cRef(0)
{
}


COPCShutdown::~COPCShutdown(void)
{
}


STDMETHODIMP COPCShutdown::QueryInterface(REFIID riid, void** ppv)
{
    *ppv = NULL;
    if (IID_IUnknown==riid || IID_IOPCShutdown==riid)
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
    log_message(TL_INFO, L"Shutdown Request") ;
    return S_OK;
}
