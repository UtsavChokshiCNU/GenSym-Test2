#include "stdafx.h"
#include "G2Gateway.h"

unsigned long CG2GatewayObj::AddRef()
{		
	return 1; 
}

unsigned long CG2GatewayObj::Release()
{
	return 1;
}

HRESULT CG2GatewayObj::QueryInterface( REFIID iid, void** ppvObject )
{
	if(iid == IID_IConnectionPointContainer)
	{		
		CComPtr<IConnectionPointContainer> pCPC;
		*ppvObject = static_cast<IConnectionPointContainer*>(this);
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	
	static_cast<IUnknown*>(*ppvObject)->AddRef();
	return S_OK;

}

int CG2GatewayObj::getRequestLen()
{
	return mpContext->Requests.Count;
}

long CG2GatewayObj::G2ClientConnect(VARIANT_BOOL WaitFlag)
{
	return Connect(WaitFlag);
}

void CG2GatewayObj::G2ClientDisconnect()
{
	Disconnect();
}
