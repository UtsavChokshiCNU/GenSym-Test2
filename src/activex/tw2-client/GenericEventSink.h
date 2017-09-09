// GenericEventSink.h : Declaration of the _CGenericEventSink

#ifndef _GENERIC_EVENT_SINK_H_
#define _GENERIC_EVENT_SINK_H_

class CGenericSinkParent
{
public:
    virtual HRESULT SinkInvoke(DISPID dispIdMember, REFIID riid, LCID lcid,
        WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult,
        EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CGenericEventSink - can be used for any dispinterface, do not use for dual
class CGenericEventSink :public IDispatch
{
private:
    ULONG m_dwRef;

public:
    CGenericSinkParent* mp_parent_obj;
    IID m_sinkIID;

    CGenericEventSink();
    ~CGenericEventSink();

    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void **ppvObject);
    virtual ULONG STDMETHODCALLTYPE AddRef(void);
    virtual ULONG STDMETHODCALLTYPE Release(void);
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( 
        /* [out] */ UINT *pctinfo);
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( 
        /* [in] */ UINT iTInfo,
        /* [in] */ LCID lcid,
        /* [out] */ ITypeInfo **ppTInfo);
    virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
        /* [in] */ REFIID riid,
        /* [size_is][in] */ LPOLESTR *rgszNames,
        /* [in] */ UINT cNames,
        /* [in] */ LCID lcid,
        /* [size_is][out] */ DISPID *rgDispId);
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke( 
        /* [in] */ DISPID dispIdMember,
        /* [in] */ REFIID riid,
        /* [in] */ LCID lcid,
        /* [in] */ WORD wFlags,
        /* [out][in] */ DISPPARAMS *pDispParams,
        /* [out] */ VARIANT *pVarResult,
        /* [out] */ EXCEPINFO *pExcepInfo,
        /* [out] */ UINT __RPC_FAR *puArgErr);
};

#endif //_GENERIC_EVENT_SINK_H_
