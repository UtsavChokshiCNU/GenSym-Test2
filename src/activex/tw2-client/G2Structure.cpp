// G2Structure.cpp : Implementation of CAXClientApp and DLL registration.

#include "G2Structure.h"
#include "Container.h"
#include "convert.h"
#include "util.h"

/////////////////////////////////////////////////////////////////////////////
//

G2Structure::G2Structure()
{
}

G2Structure::~G2Structure()
{
    subDestruct();
}

HRESULT G2Structure::FinalConstruct()
{
    // First create the sub object
    ATLTRACE("\n\nNewControl\n");
    HRESULT hr = CreateJavaObject(JAVA_STRUCTURE_CLASS, &subIDispatch);
    if (FAILED(hr))
        return hr;
    
    return subConstruct();
}

// set subIDispatch before calling this method
HRESULT G2Structure::subConstruct()
{
    // just a place holder for now
    return S_OK;
}

void G2Structure::subDestruct()
{
    // just a place holder for now
}

STDMETHODIMP G2Structure::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Structure,
	};

	for (int i = 0; i < sizeof (arr) / sizeof (arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}

    return S_FALSE;
}

class Name: public Contained
{
public:
    CComBSTR bstring;
};

STDMETHODIMP G2Structure::get_MemberNames(VARIANT *ListOfNames)
{
    SmartVariant varResult;
    SmartComPtr<IDispatch> pEnumeration;
    NoHashContainer names;
    Name* p_name;
	SAFEARRAYBOUND rgsabound[1];
    SAFEARRAY* psaNames;
    long i;

    // java.util.Enumeration = Structure.getAttributeNames()
	BSTR error_msg = CallDispatch(subIDispatch, L"getAttributeNames", NULL, 0,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (varResult.vt != VT_DISPATCH)
    {
        ATLTRACE("*get_MemberNames(): varResult.vt = 0x%X\n", varResult.vt);
        ATLTRACE("  getAttributeNames() did not return a enumeration\n");
        return E_FAIL;
    }

    pEnumeration.Attach(varResult.DetachObject());
    for (;;)
    {
        SmartComPtr<IDispatch> pSymbol;

    	error_msg = CallDispatch(pEnumeration, L"hasMoreElements", NULL, 0,
                        &varResult);
        if (error_msg != NULL)
            return Error(error_msg);

        if (!varResult.IsBoolean())
        {
            ATLTRACE("*get_MemberNames(): varResult.vt = 0x%X\n", varResult.vt);
            ATLTRACE("  hasMoreElements() did not return a boolean\n");
            return E_FAIL;
        }

        // no more elements
        if (!varResult.boolVal)
            break;

    	error_msg = CallDispatch(pEnumeration, L"nextElement", NULL, 0,
                        &varResult);
        if (error_msg != NULL)
            return Error(error_msg);

        if (!varResult.IsObject())
        {
            ATLTRACE("*get_MemberNames(): varResult.vt = 0x%X\n", varResult.vt);
            ATLTRACE("  nextElement() did not return a symbol\n");
            return E_FAIL;
        }

        pSymbol.Attach(varResult.DetachObject());
    	error_msg = CallDispatch(pSymbol, L"getPrintValue", NULL, 0, &varResult);
        if (error_msg != NULL)
            return Error(error_msg);

        if (!varResult.IsString())
        {
            ATLTRACE("*get_MemberNames(): varResult.vt = 0x%X\n", varResult.vt);
            ATLTRACE("  getPrintValue() did not return a string\n");
            return E_FAIL;
        }

        p_name = new Name;
        if (p_name == NULL)
            return E_OUTOFMEMORY;

        p_name->bstring.Attach(varResult.DetachString());
        names.Add((Contained*)p_name);
    }

    // make safe array
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = names.Count;
	psaNames = SafeArrayCreate(VT_BSTR, 1, rgsabound);
	if (psaNames == NULL)
        return E_OUTOFMEMORY;

    p_name = (Name*)names.GetFirst();
    for (i = 0; i < names.Count; i++)
    {
        SafeArrayPutElement(psaNames, &i, (void*)p_name->bstring);
        p_name = (Name*)p_name->GetNext();
    }

	ListOfNames->vt = VT_ARRAY | VT_BSTR;
	ListOfNames->parray = psaNames;
    return S_OK;
}


STDMETHODIMP G2Structure::get_Member(BSTR MemberName, VARIANT * pVal)
{
	SmartVariant pvars[1];
    SmartVariant varResult;

    BSTR error_msg = BSTRToJava(MemberName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

	error_msg = CallDispatch(subIDispatch, L"getAttributeValue", pvars, 1,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    JavaVariantToComVariant(varResult, pVal);
	return S_OK;
}

STDMETHODIMP G2Structure::put_Member(BSTR MemberName, VARIANT newVal)
{
	SmartVariant pvars[2];
    OLECHAR *method_name;
    int num_vars = 2;

    BSTR error_msg = BSTRToJava(MemberName, &pvars[1]);
    if (error_msg != NULL)
        return Error(error_msg);

    HRESULT hresult = ComVariantToJavaVariant(newVal, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

    switch (pvars[0].vt)
    {
    case VT_I2:
        pvars[0] = (long)pvars[0].iVal;
    case VT_I4:
        method_name = L"setIntAttributeValue";
        break;

    case VT_BSTR:
        if (pvars[0].bstrVal != NULL && pvars[0].bstrVal[0] == 0)
        {
            // this method only takes one parameter
            method_name = L"setEmptyStringAttributeValue";
            pvars[0] = pvars[1];
            num_vars = 1;
            break;
        }

        method_name = L"setStringAttributeValue";
        break;

    case VT_R4:
        pvars[0] = (double)pvars[0].fltVal;
    case VT_R8:
        method_name = L"setDoubleAttributeValue";
        break;

    case VT_BOOL:
        // 9/3/98 there is a bug using booleans with the Bean bridge
        // method_name = L"setBooleanAttributeValue";

        pvars[0] = (long)pvars[0].boolVal;
        method_name = L"setPseudoBooleanAttributeValue";
        break;

    default:
        method_name = L"setAttributeValue";
    }

    // void Structure.setAttributeValue(Symbol, Object)
	error_msg = CallDispatch(subIDispatch, method_name, pvars, num_vars,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP G2Structure::ClearMember(BSTR MemberName)
{
	SmartVariant pvars[1];

    BSTR error_msg = BSTRToJava(MemberName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    error_msg = CallDispatch(subIDispatch, L"deleteAttribute", pvars, 1,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

// This is the defualt proprty and is called by VB if the Set keyword is not used
STDMETHODIMP G2Structure::get_Self(IG2Structure **pVal)
{
	*pVal = this;
	InternalAddRef();
	return S_OK;
}

STDMETHODIMP G2Structure::_subObject(/*[out, retval]*/ IDispatch **subObject)
{
    _SUBOBJECT_METHOD_IMPL(subObject, subIDispatch);
}

STDMETHODIMP G2Structure::String(BSTR * StringValue)
{
	// call the toString method on the internal Java object
	
	SmartVariant retval;

    BSTR error_msg = CallDispatch(subIDispatch, L"toString", NULL, 0, &retval);
	if (error_msg)
        return Error(error_msg);

    if (!retval.IsString())
    {
        return Error("G2Structure.String(): The method of internal object did not "
            "return a value of type string.");
    }

    *StringValue = retval.DetachString();
	return S_OK;
}
