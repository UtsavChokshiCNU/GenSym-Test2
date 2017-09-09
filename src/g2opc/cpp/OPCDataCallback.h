#if !defined(AFX_OPCDATACALLBACK_H__05BAC5FC_6A66_422A_94F5_5CD4F614C027__INCLUDED_)
#define AFX_OPCDATACALLBACK_H__05BAC5FC_6A66_422A_94F5_5CD4F614C027__INCLUDED_

#include "stdafx.h"

class CGroup ;

class CAdviseSink : public IAdviseSink
{
public:
   CAdviseSink(CGroup * pGrp);
   ~CAdviseSink(void);

   STDMETHODIMP QueryInterface(REFIID, void**);
   STDMETHODIMP_(ULONG) AddRef(void);
   STDMETHODIMP_(ULONG) Release(void);

   STDMETHODIMP_(void)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
   STDMETHODIMP_(void)  OnViewChange(DWORD, LONG);
   STDMETHODIMP_(void)  OnRename(LPMONIKER);
   STDMETHODIMP_(void)  OnSave(void);
   STDMETHODIMP_(void)  OnClose(void);

protected:
    ULONG               m_cRef;
    UINT                m_data ;
    UINT                m_datatime ;
    UINT                m_write ;
private:
    CGroup              *mp_Grp ;
};

//**************************************************************************
class COPCDataCallback : public IOPCDataCallback
{
public:
	gsi_int context_nr();
    COPCDataCallback(gsi_int ctxNr) ;
   ~COPCDataCallback(void);

   STDMETHODIMP QueryInterface(REFIID, void**);
   STDMETHODIMP_(ULONG) AddRef(void);
   STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP OnDataChange( 
        /* [in] */ DWORD dwTransid,
        /* [in] */ OPCHANDLE hGroup,
        /* [in] */ HRESULT hrMasterquality,
        /* [in] */ HRESULT hrMastererror,
        /* [in] */ DWORD dwCount,
        /* [size_is][in] */ OPCHANDLE __RPC_FAR *phClientItems,
        /* [size_is][in] */ VARIANT __RPC_FAR *pvValues,
        /* [size_is][in] */ WORD __RPC_FAR *pwQualities,
        /* [size_is][in] */ FILETIME __RPC_FAR *pftTimeStamps,
        /* [size_is][in] */ HRESULT __RPC_FAR *pErrors);
    
    STDMETHODIMP OnReadComplete( 
        /* [in] */ DWORD dwTransid,
        /* [in] */ OPCHANDLE hGroup,
        /* [in] */ HRESULT hrMasterquality,
        /* [in] */ HRESULT hrMastererror,
        /* [in] */ DWORD dwCount,
        /* [size_is][in] */ OPCHANDLE __RPC_FAR *phClientItems,
        /* [size_is][in] */ VARIANT __RPC_FAR *pvValues,
        /* [size_is][in] */ WORD __RPC_FAR *pwQualities,
        /* [size_is][in] */ FILETIME __RPC_FAR *pftTimeStamps,
        /* [size_is][in] */ HRESULT __RPC_FAR *pErrors);
    
    STDMETHODIMP OnWriteComplete( 
        /* [in] */ DWORD dwTransid,
        /* [in] */ OPCHANDLE hGroup,
        /* [in] */ HRESULT hrMastererr,
        /* [in] */ DWORD dwCount,
        /* [size_is][in] */ OPCHANDLE __RPC_FAR *pClienthandles,
        /* [size_is][in] */ HRESULT __RPC_FAR *pErrors);
    
    STDMETHODIMP OnCancelComplete( 
        /* [in] */ DWORD dwTransid,
        /* [in] */ OPCHANDLE hGroup);

protected:
   ULONG    m_cRef;
private:
	gsi_int m_ctxNr;
};

#endif // !defined(AFX_OPCDATACALLBACK_H__05BAC5FC_6A66_422A_94F5_5CD4F614C027__INCLUDED_)
