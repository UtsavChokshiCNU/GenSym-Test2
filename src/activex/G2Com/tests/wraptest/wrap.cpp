// wrap.cpp : Implementation of Cwrap
#include "stdafx.h"
#include "wraptest.h"
#include "wrap.h"

/////////////////////////////////////////////////////////////////////////////
// Cwrap

STDMETHODIMP Cwrap::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_Iwrap,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT Cwrap::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	DrawText(di.hdcDraw, _T("ATL 2.0"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	return S_OK;
}

STDMETHODIMP Cwrap::op1()
{
	subobj.disable();
	return S_OK;
}

STDMETHODIMP Cwrap::get_prop1(long * pVal)
{
	if (!pVal) return S_OK;
	*pVal= subobj.getLongValue();
	return S_OK;
}

STDMETHODIMP Cwrap::put_prop1(long newVal)
{
	subobj.setLongValue(newVal);
	return S_OK;
}
