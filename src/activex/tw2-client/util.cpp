// util.cpp
#include "stdafx.h"
#include "AXClient.h"
#include "helpers.h"
#include "util.h"

HRESULT CreateScriptUtilitiesInstance(IDispatch** ppSU)
{
    CLSID CLSID_Temp;
    SmartComPtr<IDispatch> pSUtemp;
    SmartVariant varResult;
    
    ATLTRACE("CreateScriptUtilitiesInstance()\n");
    
    if (FAILED(CLSIDFromProgID(L"ScriptUtilities.Bean", &CLSID_Temp)))
    {
        ATLTRACE(" Can't get CLSID for SU Bean.");
        return E_CANT_GET_SU_CLSID;
    }
    
    if (FAILED(CoCreateInstance(CLSID_Temp, NULL, CLSCTX_INPROC_SERVER,
        IID_IDispatch, (void **) &pSUtemp)))
    {
        ATLTRACE(" Can't create SU Bean.");
        return E_CANT_CREATE_SU_BEAN;
    }
    
    // bean methods do not throw exceptions correctly, so use the real object
    if (FAILED(InvokeMethod(pSUtemp, L"getThis", NULL, 0, &varResult)))
    {
        ATLTRACE(" Can't create the SU object.");
        return E_CANT_CREATE_SU_OBJ;
    }
    
    *ppSU = varResult.DetachObject();
    return S_OK;
}
    
HRESULT InvokeMethod(IDispatch *obj, OLECHAR *MethodName, VARIANTARG *args,
                  int nArg, VARIANT *Result)
{
	DISPID dispid;
	EXCEPINFO excepinfo;

    HRESULT hr = obj->GetIDsOfNames(IID_NULL, &MethodName, 1,
        LOCALE_SYSTEM_DEFAULT, &dispid);
    if (FAILED(hr))
        return hr;

    hr = DispatchInvoke(obj, dispid, args, nArg, Result, &excepinfo);

	if (hr == DISP_E_EXCEPTION) {
		ATLTRACE("*InvokeMethod(%ws): Exception: %ws\n", MethodName,
            excepinfo.bstrDescription);
        SysFreeString(excepinfo.bstrDescription);
	}
    else if (hr == DISP_E_TYPEMISMATCH) {
		ATLTRACE("*InvokeMethod(%ws): Type Mismatch on method call.\n",
            MethodName);
    }
    else if (hr == DISP_E_BADPARAMCOUNT) {
		ATLTRACE("*InvokeMethod(%ws): Invalid number of parameters on method call.\n",
            MethodName);
    }
    else if (FAILED(hr)) {
		ATLTRACE("*InvokeMethod(%ws): Error on method call: 0x%X!!!\n\n\n",
            MethodName, hr);
    }

    return hr;
}

//
// This is a dispatch wrapper.  It simplfies the calling of IDispatch interfaces
// This also will return error info
//
BSTR CallDispatch(IDispatch *obj, OLECHAR *MethodName, VARIANTARG *args,
                  int nArg, VARIANT *Result)
{
	DISPID dispid = GetDispId(obj, MethodName);
    if (dispid == -1)
    {
        ATLTRACE("*CallDispatch(%ws): Unable to find method\n", MethodName);
		return L"Unable to get the ID of a method from the internal object.";
    }

    BSTR error_msg = CallInvoke(obj, dispid, args, nArg, Result);
    if (error_msg != NULL)
    {
		ATLTRACE("*CallDispatch(%ws): Error on method.\n\n\n",
            MethodName);
    }

    return error_msg;
}

DISPID GetDispId(IDispatch *obj, OLECHAR *methodName)

{
	DISPID dispid;
	HRESULT hr = obj->GetIDsOfNames(IID_NULL, &methodName, 1, LOCALE_SYSTEM_DEFAULT,&dispid);
	if (FAILED(hr)) return -1;
	return dispid;
}

//
// This is a invoke wrapper.  It simplfies the calling of IDispatch interfaces
// This also will return error info
//
BSTR CallInvoke(IDispatch *obj, DISPID dispid, VARIANTARG *args,
                  int nArg, VARIANT *Result)
{
	EXCEPINFO excepinfo;

    HRESULT hr = DispatchInvoke(obj, dispid, args, nArg, Result, &excepinfo);

	if (hr == DISP_E_EXCEPTION) {
		ATLTRACE("*CallInvoke(): Exception: %ws\n", excepinfo.bstrDescription);
        return excepinfo.bstrDescription;
	}

    if (hr == DISP_E_TYPEMISMATCH) {
		ATLTRACE("*CallInvoke(): Type Mismatch on method call.\n");
		return L"Parameter type mismatch error on method call to internal object";
    }

    if (hr == DISP_E_BADPARAMCOUNT) {
		ATLTRACE("*CallInvoke(): Invalid number of parameters on method call.\n");
		return L"Invalid number of arguments error on method call to internal object";
    }

    if (FAILED(hr)) {
		ATLTRACE("*CallInvoke(): Error on method call: 0x%X!!!\n\n\n", hr);
		return L"Unexpected error on method call to internal object";
    }

    return NULL;  // everything went ok
}

HRESULT DispatchInvoke(IDispatch *obj, DISPID dispid, VARIANTARG *args,
                  int nArg, VARIANT *Result, EXCEPINFO *pExceptInfo)
{
	DISPPARAMS disp = { args, NULL, nArg, 0};
	unsigned int nArgError;
    HRESULT hresult;

    if (Result != NULL && Result->vt != VT_EMPTY)
        VariantInit(Result);

	hresult = obj->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
		        DISPATCH_METHOD, &disp, Result, pExceptInfo, &nArgError);

    if (FAILED(hresult))
        return hresult;

     // Give Java time to send events before we return.
    ::Sleep(1);

    if (Result == NULL)
        return hresult;

    // The beans bridge wants VT_NULL for null pointer input parameters,
    // but for null objects it outputs VT_EMPTY, VT_NULL with a bogus pointer
    // and sometimes VT_DISPATCH with a null pointer.
    // We want the bridge output to match the correct input
    // so we can hand a variant back to the bridge without conversion.
    if ((Result->vt == VT_EMPTY) ||
        (Result->vt == VT_NULL) ||
        (Result->vt == VT_DISPATCH && Result->pdispVal == NULL))
    {
        // make sure every thing is properly cleared out
        Result->vt = VT_NULL;
        Result->pdispVal = NULL;
        return hresult;
    }

    return hresult;
}
