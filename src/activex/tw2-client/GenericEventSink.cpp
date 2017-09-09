// CGenericEventSink.cpp : Implementation of CGenericEventSink
#include "StdAfx.h"
#include "GenericEventSink.h"

/////////////////////////////////////////////////////////////////////////////
// CGenericEventSink

CGenericEventSink::CGenericEventSink()
{
    ATLTRACE("CGenericEventSink Constructed\n");
	_Module.Lock();
    m_dwRef = 0;
    m_sinkIID = IID_NULL;
}

CGenericEventSink::~CGenericEventSink()
{
    ATLTRACE("CGenericEventSink Destroyed\n");

    _Module.Unlock();
}

STDMETHODIMP CGenericEventSink::QueryInterface(REFIID iid, void **ppvObject)
{
    AddRef();

	if (InlineIsEqualGUID(IID_IUnknown, iid))
    {
        *ppvObject = (void*)(IUnknown*)this;
        return _ATLDUMPIID(iid, "CGenericEventSink", S_OK);
    }

	if (InlineIsEqualGUID(IID_IDispatch, iid))
    {
        *ppvObject = (void*)(IDispatch*)this;
        return _ATLDUMPIID(iid, "CGenericEventSink", S_OK);
    }

	if (InlineIsEqualGUID(m_sinkIID, iid))
    {
        *ppvObject = (void*)(IDispatch*)this;
        return _ATLDUMPIID(iid, "CGenericEventSink", S_OK);
    }

    Release();
    return _ATLDUMPIID(iid, "CGenericEventSink", E_NOINTERFACE);
}

ULONG CGenericEventSink::AddRef()
{
    ATLTRACE("CGenericEventSink::AddRef()\n");

    m_dwRef++;
    return m_dwRef;
}

ULONG CGenericEventSink::Release()
{
    ATLTRACE("CGenericEventSink::Release()\n");

    m_dwRef--;
	if (m_dwRef == 0)
    {
		delete this;
        return 0;
    }

	return m_dwRef;
}

STDMETHODIMP CGenericEventSink::GetTypeInfoCount(UINT* pctinfo)
{
    *pctinfo = 0;
    return S_OK;
}

STDMETHODIMP CGenericEventSink::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP CGenericEventSink::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames,
    UINT cNames, LCID lcid, DISPID* rgdispid)
{
    return E_NOTIMPL;
}

// Override the Invoke method and forward it to the connection object.
STDMETHODIMP CGenericEventSink::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
    WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
    EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr)
{
	ATLTRACE("GenericEventSink: Forwarding invoke on outgoing interface:%d\n",dispIdMember);
    return mp_parent_obj->SinkInvoke(dispIdMember, riid, lcid,
        wFlags, pDispParams, pVarResult,pExcepInfo, puArgErr);
}