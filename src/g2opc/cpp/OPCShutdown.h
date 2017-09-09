// OPCShutdown.h: interface for the COPCShutdownObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCSHUTDOWN_H__8D1193CD_A48E_4B9A_A3FF_61131864D89C__INCLUDED_)
#define AFX_OPCSHUTDOWN_H__8D1193CD_A48E_4B9A_A3FF_61131864D89C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "opccomn.h"

class COPCShutdown : public IOPCShutdown  
{
public:
	COPCShutdown();
	virtual ~COPCShutdown();
    STDMETHODIMP QueryInterface(REFIID, void**);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    STDMETHODIMP ShutdownRequest( LPCWSTR szReason) ;
protected:
   ULONG    m_cRef;
};

#endif // !defined(AFX_OPCSHUTDOWN_H__8D1193CD_A48E_4B9A_A3FF_61131864D89C__INCLUDED_)
