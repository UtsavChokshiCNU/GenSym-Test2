// G2ComConfigurator.cpp : Implementation of CG2ComConfigurator
#include "stdafx.h"
#include "G2Com.h"
#include "G2ComConfigurator.h"

extern DWORD sleepTime ;

/////////////////////////////////////////////////////////////////////////////
// CG2ComConfigurator


STDMETHODIMP CG2ComConfigurator::get_HighThroughput(VARIANT_BOOL *pVal)
{
    *pVal = ::sleepTime ? VARIANT_FALSE : VARIANT_TRUE ;

	return S_OK;
}

STDMETHODIMP CG2ComConfigurator::put_HighThroughput(VARIANT_BOOL newVal)
{
    ::sleepTime = (newVal == VARIANT_TRUE) ? 0 : 10 ;

	return S_OK;
}
