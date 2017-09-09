// G2Symbol.cpp : Implementation of CAXClientApp and DLL registration.

#include "G2Symbol.h"
#include "convert.h"
#include "util.h"

/////////////////////////////////////////////////////////////////////////////
//

G2Symbol::G2Symbol()
{
    // just a place holder for now
}

G2Symbol::~G2Symbol()
{
    // just a place holder for now
}

HRESULT G2Symbol::FinalConstruct()
{
    mValue = L"NONE";
    if (BSTRToJavaSymbolObject(mValue, &javaObject) != NULL)
        return E_CANT_CREATE_JAVA_OBJ;

    return S_OK;
}

STDMETHODIMP G2Symbol::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
    {
		&IID_IG2Symbol,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
		if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
	}

	return S_FALSE;
}

STDMETHODIMP G2Symbol::get_Value(BSTR * pVal)
{
	*pVal = SysAllocString(mValue.operator BSTR()); // alloc return string
	return S_OK;
}

// The putval method uses the internSymbol method of the ScriptUtilites bean to 
// create a new Java symbol object
STDMETHODIMP G2Symbol::put_Value(BSTR newVal)
{
    BSTR error_msg;
    SmartComPtr<IDispatch> pNewSymbol;
	SmartVariant pvars[1];

    error_msg = BSTRToJavaSymbolObject(newVal, &pNewSymbol);
    if (error_msg != NULL)
        return Error(error_msg);

    if (FAILED(NewUpperCaseBSTR(newVal, &pvars[0])))
        return Error("Invalid Symbol");

    javaObject = pNewSymbol;
	mValue = pvars[0].bstrVal;  // save local copy
	return S_OK;
}

STDMETHODIMP G2Symbol::_subObject(IDispatch **subObject)
{
    _SUBOBJECT_METHOD_IMPL(subObject, javaObject);
}

// 
// This is the defualt property.  This is called by VB if you do not use the "Set" keyword
//
STDMETHODIMP G2Symbol::get_Self(IG2Symbol **pVal) {
	*pVal = this;
	InternalAddRef();
	return S_OK;
}

STDMETHODIMP G2Symbol::String(BSTR *StringValue) {
	*StringValue = SysAllocString(mValue.operator BSTR()); // alloc return string
	return S_OK;
}
