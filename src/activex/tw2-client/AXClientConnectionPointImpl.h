// AXClientConnectionPointImpl.h
#ifndef _AXCLIENT_CONNECTION_POINT_IMPL_H
#define _AXCLIENT_CONNECTION_POINT_IMPL_H

template <class T, const IID* piid, class CDV = CComDynamicUnkArray>
class ATL_NO_VTABLE IAXClientConnectionPointImpl:
    public IConnectionPointImpl<T, piid, CDV>
{
public:
    // these 2 methods allow our wrappers of the java bean objects
    // to call advise on the bean on the first call to advise
    // of any of the out going interface of a wrapper.
    virtual HRESULT AdviseCalled() = 0;
	STDMETHOD(Advise)(IUnknown* pUnkSink, DWORD* pdwCookie)
    {
        HRESULT hresult;

        hresult = AdviseCalled();
        if (FAILED(hresult))
            return hresult;

        return IConnectionPointImpl<T, piid, CDV>::Advise(pUnkSink, pdwCookie);
    };
};

#endif // _AXCLIENT_CONNECTION_POINT_IMPL_H