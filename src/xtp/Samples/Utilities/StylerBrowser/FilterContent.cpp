// FilterContent.cpp : implementation file
//

#include "stdafx.h"
#include "styler.h"
#include "FilterContent.h"
#include "FilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterContent

IMPLEMENT_DYNCREATE(CFilterContent, CCmdTarget)

CFilterContent::CFilterContent()
{
	EnableAutomation();
}

CFilterContent::~CFilterContent()
{
}


BEGIN_INTERFACE_MAP(CFilterContent, CCmdTarget)
	INTERFACE_PART(CFilterContent, IID_IClassFactory, ClassFactory)
	INTERFACE_PART(CFilterContent, IID_IInternetProtocol, InternetProtocol)
	INTERFACE_PART(CFilterContent, IID_IInternetProtocolRoot, InternetProtocol)
END_INTERFACE_MAP()




STDMETHODIMP_(ULONG) CFilterContent::XClassFactory::AddRef()
{
	METHOD_PROLOGUE(CFilterContent, ClassFactory)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG)  CFilterContent::XClassFactory::Release()
{                            
	METHOD_PROLOGUE(CFilterContent, ClassFactory)
	return pThis->ExternalRelease();
}

STDMETHODIMP CFilterContent::XClassFactory::QueryInterface (REFIID riid, void **ppvObj)
{
	METHOD_PROLOGUE(CFilterContent, ClassFactory)
	HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}


STDMETHODIMP CFilterContent::XClassFactory::CreateInstance( 
            /* [unique][in] */ IUnknown __RPC_FAR* /*pUnkOuter*/,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
{
	METHOD_PROLOGUE(CFilterContent, ClassFactory)
	
	pThis->InternalQueryInterface(&riid, ppvObject);
	pThis->ExternalAddRef();

	return S_OK;

}
        
STDMETHODIMP CFilterContent::XClassFactory::LockServer (/* [in] */ BOOL /*fLock*/)
{
	return E_NOTIMPL;
}


/////////////////////////////////////////

STDMETHODIMP_(ULONG)  CFilterContent::XInternetProtocol::AddRef()
{
	METHOD_PROLOGUE(CFilterContent, InternetProtocol)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CFilterContent::XInternetProtocol::Release()
{                            
	METHOD_PROLOGUE(CFilterContent, InternetProtocol)
	return pThis->ExternalRelease();
}

STDMETHODIMP CFilterContent::XInternetProtocol::QueryInterface (REFIID riid, void **ppvObj)
{
	METHOD_PROLOGUE(CFilterContent, InternetProtocol)
	HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}

STDMETHODIMP CFilterContent::XInternetProtocol::Start(
        LPCWSTR szUrl,
        IInternetProtocolSink *pIProtSink,
        IInternetBindInfo* /*pIBindInfo*/,
        DWORD /*grfSTI*/,
        HANDLE_PTR /*dwReserved*/)
{

	METHOD_PROLOGUE(CFilterContent, InternetProtocol)
		
	if(pIProtSink!=NULL)
	{
		CString strUrl(szUrl);	

		for (int i = 0; i < CFilterDialog::m_lstFilter.GetSize(); i++)
		{
		
			if (strUrl.Find(CFilterDialog::m_lstFilter[i]) != -1)
			{
				pIProtSink->AddRef();
				pIProtSink->ReportData(BSCF_FIRSTDATANOTIFICATION || BSCF_LASTDATANOTIFICATION || BSCF_DATAFULLYAVAILABLE, 42, 42);
				pIProtSink->ReportResult(S_OK, 0, 0);
				pIProtSink->Release();

				pThis->InternalRelease();
				return S_OK;
			}
			
		}
	}
									
	return INET_E_USE_DEFAULT_PROTOCOLHANDLER;
}

STDMETHODIMP CFilterContent::XInternetProtocol::Continue(PROTOCOLDATA * /*pStateInfo*/)
{
	return S_OK;
}

STDMETHODIMP CFilterContent::XInternetProtocol::Abort(HRESULT /*hrReason*/,DWORD /*dwOptions*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP CFilterContent::XInternetProtocol::Terminate(DWORD /*dwOptions*/)
{
	return  S_OK;
}

STDMETHODIMP CFilterContent::XInternetProtocol::Suspend()
{
	return E_NOTIMPL;
}

STDMETHODIMP CFilterContent::XInternetProtocol::Resume()
{

	return E_NOTIMPL;
}


STDMETHODIMP CFilterContent::XInternetProtocol::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	BYTE bytePlaceHold[]=	{0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x01, 0x00,
						0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
						0xFF, 0xFF, 0xFF, 0x21, 0xF9, 0x04, 0x01, 0x00,
						0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00,
						0x01, 0x00, 0x01, 0x00, 0x00, 0x02, 0x01, 0x44,
						0x00, 0x3B};



	try
	{

		if(cb >= 42 && pv != NULL)
		{
			MEMCPY_S(pv, bytePlaceHold, 42);
			*pcbRead =	42;
		}
		else
			*pcbRead = 0;
		
	}
	catch(...)
	{
	}

	return S_FALSE;
}

STDMETHODIMP CFilterContent::XInternetProtocol::Seek(
        LARGE_INTEGER /*dlibMove*/,
        DWORD /*dwOrigin*/,
        ULARGE_INTEGER * /*plibNewPosition*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP CFilterContent::XInternetProtocol::LockRequest(DWORD /*dwOptions*/)
{
	return S_OK;
}

STDMETHODIMP CFilterContent::XInternetProtocol::UnlockRequest()
{
	return S_OK;
}

