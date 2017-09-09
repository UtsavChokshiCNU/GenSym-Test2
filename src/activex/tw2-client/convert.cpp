//
// This file provides a set of conversion routines
//

#include "stdafx.h"
#include "AXClient.h"
#include "convert.h"
#include "G2Symbol.h"
#include "G2Item.h"
#include "G2Structure.h"
#include "util.h"
#include "Container.h"
#include "helpers.h"

static HRESULT JavaArrayToComArray(VARTYPE javaType, SAFEARRAY* pJavaArray,
                                   VARTYPE comType, VARIANT* pComVariant);

static SmartComPtr<IDispatch> g_pScriptUtilities;

// don't release the static script utilities
static IDispatch* GetStaticScriptUtilities()
{
    if (!g_pScriptUtilities)
    {
        if (FAILED(CreateScriptUtilitiesInstance(&g_pScriptUtilities)))
            return NULL;
    }

    return g_pScriptUtilities;
}

//
// Simple conversion functions
//


//
// For performance reasons, it is good to cache symbol
// objects.  We want to avoid both creation of the script utility
// bean object each time we need a symbol and the creation 
// of a symbol object each time we need one as well.
// 

class SymbolEntry : public Contained
{
public:
	CComBSTR value;
	SmartComPtr<IDispatch> javaObject;
	WCHAR *GetKey() { return (BSTR) value;};
};


class SymbolCacheClass : public Container
{
public:
	BSTR GetSymbol(BSTR Name, IDispatch **ret);
	void RegisterSymbol(BSTR Name, IDispatch *javaObject);
private:
	void CreateEntry(BSTR Name, IDispatch *javaObject);
	SmartComPtr<IDispatch> subPtr;
};

SymbolCacheClass SymbolCache;   // Global object for central cache

BSTR SymbolCacheClass::GetSymbol(BSTR Name, IDispatch **ret)
{
	WCHAR Buf[1024];
	SmartVariant pvars[1];
    SmartVariant varResult;

    UpperCase(Name, Buf);	
	CComBSTR UpperName = Buf;

    ATLTRACE("Getting Symbol for %ws\n", (BSTR) UpperName);

    // first look in the cache.  If we find it there, we are done
	SymbolEntry *se = (SymbolEntry *) FindObj((BSTR) UpperName);
	if (se != NULL)
    {
		*ret = se->javaObject;
		(*ret)->AddRef();
		ATLTRACE("Found %ws in Cache\n", (BSTR) UpperName);
		return NULL;
	}

	// now check to see if we have a bean object
	if (!subPtr)
    { // nope, create one	
        if (FAILED(CreateScriptUtilitiesInstance(&subPtr)))
            return L"Can't create symbol factory.";
	}

	// create the new symbol object
	pvars[0] = (BSTR) UpperName;
    BSTR error_msg = CallDispatch(subPtr, L"internSymbol", pvars, 1, &varResult);
	if (error_msg != NULL)
        return error_msg;

	// we now have a symbol object from Java.  Add it to the cache
    CreateEntry(UpperName, varResult.pdispVal);

    *ret = varResult.DetachObject();
	return NULL;
}

// This will add a symbol received from Java to our local cache
// This would avoid the overhead of creating a new object
// if Java passes one to us.
void SymbolCacheClass::RegisterSymbol(BSTR Name, IDispatch *javaObject) 
{
	SymbolEntry *se = (SymbolEntry *) FindObj(Name);
	if (se)
        return;  // already in the cache, done

    CreateEntry(Name, javaObject);
}

void SymbolCacheClass::CreateEntry(BSTR Name, IDispatch *javaObject) 
{
	SymbolEntry *se = new SymbolEntry;

    // se->javaObject is a smart pointer, no AddRef() needed
	se->javaObject = javaObject;
	se->value = Name;
	Add(se);
	ATLTRACE("Added %ws to symbol cache\n", Name);
}



// Convert a ActiveX SafeArray to a Sequence
// This works around a problem with the bean bridge and arrays
// This also converts types back and forth.

HRESULT ArrayToSequence(SAFEARRAY *arr, IDispatch **Sequence)

{
	HRESULT hr;
    IDispatch *seq;
	OLECHAR *methodName;
	long LBound, UBound;
    int num_vars;

    // First, create a new object
    hr = CreateJavaObject(L"com.gensym.util.Sequence", &seq);
	if (FAILED(hr))
        return hr;

	// The result should hold the constructed result
	// We now have a Java sequence object.  We want to copy the data from
	// the SAFEARRAY to the object.  We need to be careful in the way that we
	// create the objects.  

	// First make sure that we have a good SAFEARRAY
	if (SafeArrayGetDim(arr) != 1)
        return E_FAIL;

	hr = SafeArrayGetLBound(arr, 1, &LBound);
	if (FAILED(hr))
        return hr;

	hr = SafeArrayGetUBound(arr, 1, &UBound);
	if (FAILED(hr))
        return hr;

	// We want to copy each non-null element
    for (long i = LBound; i <= UBound; i++)
    {
    	SmartVariant varCom;
	    SmartVariant varJava;

		SafeArrayGetElement(arr, &i, &varCom);
		if (varCom.vt == VT_EMPTY)
            continue;

        hr = ComVariantToJavaVariant(varCom, &varJava);
        if (FAILED(hr))
            break;

        num_vars = 1;
        switch (varJava.vt)
        {
        case VT_I2:
            varJava = (long)varJava.iVal;
        case VT_I4:
            methodName = L"addIntElement";
            break;
            
        case VT_BSTR:
            if (varJava.bstrVal != NULL && varJava.bstrVal[0] == 0)
            {
                // this method does not have args
                methodName = L"addEmptyStringElement";
                num_vars = 0;
                break;
            }

            methodName = L"addStringElement";
            break;
            
        case VT_R4:
            varJava = (double)varJava.fltVal;
        case VT_R8:
            methodName = L"addDoubleElement";
            break;
            
        case VT_BOOL:
            // 9/3/98 there is a bug using booleans with the Bean bridge
            // methodName = L"addBooleanElement";
            
            varJava = (long)varJava.boolVal;
            methodName = L"addPseudoBooleanElement";
            break;
            
        default:
            methodName = L"addElement";
        }
        
        // ok, we have a valid element, add it to the sequence
        hr = InvokeMethod(seq, methodName, &varJava, num_vars, NULL);
        if (FAILED(hr))
            break;
	}

    *Sequence = seq;

#ifdef _DEBUG
    {
        SmartVariant var;

        CComBSTR error_msg = CallDispatch(seq, L"toString", NULL, 0, &var);
        if (error_msg == (BSTR)NULL && var.vt == VT_BSTR)
            ATLTRACE("sequence = %ws\n",var.bstrVal);
    }
#endif

    return S_OK;
}


// Convert a ActiveX SafeArray to a sequence in a variant

HRESULT ArrayToVariant(SAFEARRAY *arr, VARIANT *pvar)
{
    HRESULT hresult;

    hresult = ArrayToSequence(arr, &(pvar->pdispVal));
    if (SUCCEEDED(hresult))
        pvar->vt = VT_DISPATCH;

    return hresult;
}

// Convert a sequnce object to a equivlement safearray

HRESULT SequenceToArray(IDispatch *Sequence, SAFEARRAY **arr, int lowerBound, bool colapseSymbols)
{
    HRESULT hr;
	SmartVariant varResultSize;
	long size;
	OLECHAR *methodName;
    DISPID dispid;
	SmartVariant pvars[1];
	SAFEARRAY *sa;
	DISPPARAMS disp = {pvars, NULL, 1, 0};
    long i;
    long offset;

    // ok, we want to create a safe array of the right size and shape
	// First, find out how many elements are in the sequence
    hr = InvokeMethod(Sequence, L"size", NULL, 0, &varResultSize);
    if (FAILED(hr))
        return hr;

	size = varResultSize.lVal; 

	// Get the disp id of the array access operation
	// Also set up the call to Java to save time

	methodName = L"elementAt";
	hr = Sequence->GetIDsOfNames(IID_NULL, &methodName,1,LOCALE_SYSTEM_DEFAULT,&dispid);
    if (FAILED(hr))
        return hr;

	// ok, now create a safe array
	sa = SafeArrayCreateVector(VT_VARIANT, lowerBound, (unsigned int)size); 
    if (sa == NULL)
        return E_OUTOFMEMORY;

	for (i = 0; i < size; i++)
    {
    	SmartVariant varResult;

		// get the element
		pvars[0] = i;
		hr = Sequence->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
             DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
        if (FAILED(hr))
            return hr;

		offset = i + lowerBound;
		if (varResult.IsObject())
        {
        	SmartVariant varDest;

			JavaToCom(varResult.pdispVal, &varDest, colapseSymbols);
			SafeArrayPutElement(sa, &offset, &varDest);
        }
        else
        {
            SafeArrayPutElement(sa, &offset, &varResult);
        }
	}

    *arr = sa;

    return S_OK;
}

HRESULT SequenceToVariant(IDispatch *Sequence, VARIANT *varResult, int lowerBound, bool colapseSymbols)
{
    HRESULT hresult;

    hresult = SequenceToArray(Sequence, &(varResult->parray), lowerBound,
               colapseSymbols);
    if (SUCCEEDED(hresult))
        varResult->vt = VT_ARRAY | VT_VARIANT;

    return hresult;
}
// Ok, map a COM object to a VB object.  If we get one of our object, get the internal
// object.  This will take one IDispatch and produce another

HRESULT ComToJava(IDispatch *ComObject, IDispatch **JavaObject)
{
	SmartComPtr<IG2Symbol> symPtr;
	HRESULT hr = ComObject->QueryInterface(IID_IG2Symbol,
                  (void **) &symPtr);
	if (SUCCEEDED(hr))
    { // got symbol object
		hr = symPtr->_subObject(JavaObject);
		if (SUCCEEDED(hr))
            return S_OK;

        return E_FAIL;
	}

	SmartComPtr<IG2Structure> structPtr;
	hr = ComObject->QueryInterface(IID_IG2Structure,
          (void **) &structPtr);
	if (SUCCEEDED(hr))
    { // got structure object
		hr = structPtr->_subObject(JavaObject);
		if (SUCCEEDED(hr))
            return S_OK;

        return E_FAIL;
	}

	SmartComPtr<IG2Item> itemPtr;
    hr = ComObject->QueryInterface(IID_IG2Item, (void **) &itemPtr);
	if (SUCCEEDED(hr))
    { // item object
		hr = itemPtr->_subObject(JavaObject);
		if (SUCCEEDED(hr))
            return S_OK;

        return E_FAIL;
	}

	// cant find the object, just pass it through
	*JavaObject = ComObject;
	ComObject->AddRef();  // we just copied the pointer, make sure that we bump the count
	return S_OK;
}

//
// This will convert one of the general Java objects to one of our interfaces

// The steps to follow are:
//    Get class object of the object to convert
//    get class name
//    check for symbol, struct
//    get class item for item
//    check to see if it is assignable to item

HRESULT JavaToCom(IDispatch *JavaObject, VARIANT *ComObject, bool colapseSymbols)

{
	SmartVariant varResult;
	SmartComPtr<IDispatch> ClassObject;

    if (JavaObject == NULL)
    {
        ComObject->pdispVal = NULL;
        return S_OK;
    }

    // First get the class object
	HRESULT hresult = InvokeMethod(JavaObject, L"getClass", NULL, 0, &varResult);
	if (FAILED(hresult)) return hresult;

	// Now get the name of the class 
	ClassObject.Attach(varResult.DetachObject());
	hresult = InvokeMethod(ClassObject, L"getName", NULL, 0, &varResult);
	if (FAILED(hresult)) return hresult;

    ATLTRACE("Java Class:%ws\n",varResult.bstrVal);

	if (!wcscmp(varResult.bstrVal, L"com.gensym.util.Symbol")) {
		// Construct Symbol object here
		ATLTRACE("Got Symbol\n");
		if (colapseSymbols) {
			ComObject->vt = VT_BSTR;
			hresult = JavaToBSTR(JavaObject, &(ComObject->bstrVal));
		} else {
            // create symbol object
			ComObject->vt = VT_DISPATCH;
            hresult = JavaToSymbol(JavaObject, (IG2Symbol**)(&ComObject->pdispVal));
		}
	} else if (!wcscmp(varResult.bstrVal, JAVA_STRUCTURE_CLASS)) {
		// Construct Structure object here
		ATLTRACE("Got Structure\n");
		ComObject->vt = VT_DISPATCH;
        hresult = JavaToStructure(JavaObject,
            (IG2Structure**)(&ComObject->pdispVal));
	} else if (!wcscmp(varResult.bstrVal, L"com.gensym.util.Sequence")) {
		// construct Sequence object here
		ATLTRACE("Got Sequence\n");
        hresult = SequenceToVariant(JavaObject, ComObject, 0);
	} else if (!wcscmp(varResult.bstrVal, L"java.lang.Integer")) {
		// handle g2 integers here
		ATLTRACE("Got Integer Object\n");
	    hresult = InvokeMethod(JavaObject, L"intValue", NULL, 0, ComObject);
    } else if (!wcscmp(varResult.bstrVal, L"java.lang.String")) {
		// handle g2 texts here
		ATLTRACE("Got String Object\n");
	    hresult = InvokeMethod(JavaObject, L"toString", NULL, 0, ComObject);
    } else if (!wcscmp(varResult.bstrVal, L"java.lang.Double")) {
		// handle g2 floats here
		ATLTRACE("Got Double Object\n");
	    hresult = InvokeMethod(JavaObject, L"doubleValue", NULL, 0, ComObject);
    } else if (!wcscmp(varResult.bstrVal, L"java.lang.Boolean")) {
		// handle g2 true-values here
		ATLTRACE("Got Boolean Object\n");
	    hresult = InvokeMethod(JavaObject, L"booleanValue", NULL, 0, ComObject);
	} else {
        // the above classes are only base type objects that do
        // inherit from item, all other objects do, this could change in the
        // future
		ATLTRACE("Got Assumed Item\n");
		ComObject->vt = VT_DISPATCH;
        hresult = JavaToItem(JavaObject, (G2Item2**)(&ComObject->pdispVal));
	}

	return hresult;
}

// Convert a BSTR to a Java Symbol object
BSTR BSTRToJava(BSTR str, VARIANT *pvar)
{
	BSTR error_msg;

    error_msg = BSTRToJavaSymbolObject(str, &pvar->pdispVal);
    if (error_msg != NULL)
        return error_msg;

    pvar->vt = VT_DISPATCH;

    return NULL;
}

BSTR BSTRToJavaSymbolObject(BSTR str, IDispatch **ppObj)
{
	ATLTRACE("Converting %ws to Symbol\n", str);

    return SymbolCache.GetSymbol(str, ppObj);
}

BSTR OLECHARToJavaSymbol(OLECHAR *str, VARIANT *pvar)
{
    CComBSTR bstring(str);

    if (!bstring)
        return L"Out of Memory"; //E_OUTOFMEMORY

    return BSTRToJava(bstring, pvar);
}

HRESULT JavaToBSTR(IDispatch *JavaObject, BSTR *str)
{
	OLECHAR FAR* methodName = L"getPrintValue";
	DISPID dispid;
	HRESULT hr = JavaObject->GetIDsOfNames(IID_NULL,&methodName,1,LOCALE_SYSTEM_DEFAULT,&dispid);
	if (FAILED(hr)) return hr;

	DISPPARAMS disp = {NULL, NULL, 0, 0 };
	SmartVariant varResult;
	hr = JavaObject->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
	if (FAILED(hr))
        return hr;

    // The variant now contains the BSTR
	*str = varResult.DetachString();
	SymbolCache.RegisterSymbol(*str, JavaObject);
	ATLTRACE("Got Symbol:%ws\n", *str);

	return S_OK;
}

HRESULT JavaToItem(IDispatch *JavaObject, G2Item2 **ComObject)
{
    HRESULT hresult;
    SmartVariant itemString;
	CComObject<_CG2Item>* newItem;

    if (JavaObject == NULL)
    {
         *ComObject = NULL;
         return S_OK;
    }

    //Check to see if this is a valid Java Object
    hresult = InvokeMethod(JavaObject, L"toString", NULL, 0, &itemString);
    if (FAILED(hresult))
    {
        ATLTRACE("\nInvalid Java object passed into JavaToItem()\n\n");
        return hresult;
    }

    hresult = CComObject<_CG2Item>::CreateInstance(&newItem);
    if (FAILED(hresult))
        return hresult;

    // we are copying a pointer, make sure that we bump up the reference count
    ATLTRACE("\nAdding a new reference to the Java Object: %ws\n\n",
        itemString.bstrVal);
    JavaObject->AddRef();

    newItem->AddRef();
	newItem->subIDispatch = JavaObject;  // embedd internal java object
	newItem->subConstruct();

	*ComObject = (G2Item2*)newItem;
	return S_OK;
}


HRESULT JavaToSymbol(IDispatch *JavaObject, IG2Symbol **ComObject)
{
    CComBSTR SymbolName;
	CComObject<G2Symbol>* newSymbol;

    JavaToBSTR(JavaObject, &SymbolName);  // get the symbol name
    CComObject<G2Symbol>::CreateInstance(&newSymbol);
	newSymbol->AddRef();
	newSymbol->put_Value(SymbolName);
    *ComObject = (IG2Symbol*)newSymbol;
    return S_OK;
}

HRESULT JavaVariantToComVariant(VARIANT JavaVariant, VARIANT *ComVariant)
{
	switch (JavaVariant.vt)
    {
		case VT_DISPATCH:
            return JavaToCom(JavaVariant.pdispVal, ComVariant);

        case VT_BYREF | VT_VARIANT:
            // strip off the extra level of indirection
            return JavaVariantToComVariant(*JavaVariant.pvarVal, ComVariant);

        case VT_ARRAY | VT_VARIANT:
            return JavaVariantArrayToComVariant(JavaVariant.parray, ComVariant);

        case VT_ARRAY | VT_DISPATCH:
            return JavaObjectArrayToComVariant(JavaVariant.parray, ComVariant);
    }

    // default

    // The beans bridge wants VT_NULL for null pointer input parameters,
    // but for null objects it outputs VT_EMPTY, VT_NULL with a bogus pointer.
    // Sometimes it outputs VT_DISPATCH with a null pointer.
    // We want the output to match the input
    // so we can hand it back in without coversion.
    if ((JavaVariant.vt == VT_EMPTY) ||
        (JavaVariant.vt == VT_NULL) ||
        (JavaVariant.vt == VT_DISPATCH && JavaVariant.pdispVal == NULL))
    {
        ComVariant->vt = VT_NULL;
        ComVariant->pdispVal = NULL;
    }
    else
    {
        VariantInit(ComVariant);
        VariantCopy(ComVariant, &JavaVariant);
    }

    return S_OK;
}

HRESULT ComVariantToJavaVariant(VARIANT ComVariant, VARIANT *JavaVariant)
{
    HRESULT hresult;

	switch (ComVariant.vt)
    {
		case VT_DISPATCH:
            JavaVariant->vt = VT_DISPATCH;
            return ComToJava(ComVariant.pdispVal, &JavaVariant->pdispVal);

		case VT_BYREF | VT_DISPATCH:
            // strip off the extra level of indirection
            JavaVariant->vt = VT_DISPATCH;
            return ComToJava(*ComVariant.ppdispVal, &JavaVariant->pdispVal);

        case VT_BYREF | VT_VARIANT:
            // strip off the extra level of indirection
            return ComVariantToJavaVariant(*ComVariant.pvarVal, JavaVariant);

        case VT_ARRAY | VT_VARIANT:
            hresult = ArrayToSequence(ComVariant.parray, &JavaVariant->pdispVal);
            if (SUCCEEDED(hresult))
                JavaVariant->vt = VT_DISPATCH;

            return hresult;

        case VT_BYREF | VT_ARRAY | VT_VARIANT:
            // strip off the extra level of indirection
            hresult = ArrayToSequence(*ComVariant.pparray, &JavaVariant->pdispVal);
            if (SUCCEEDED(hresult))
                JavaVariant->vt = VT_DISPATCH;

            return hresult;

        case VT_I2:
            // we only send 32 bit integers to java
            ComVariant.lVal = (long)ComVariant.iVal;
            ComVariant.vt = VT_I4;
            break;
                
        case VT_R4:
            // we only send doubles to java
            ComVariant.dblVal = (double)ComVariant.fltVal;
            ComVariant.vt = VT_R8;
            break;
    }

    // default
    VariantInit(JavaVariant);
    VariantCopy(JavaVariant, &ComVariant);
    return S_OK;
}

HRESULT JavaToStructure(IDispatch *JavaObject, IG2Structure** ComObject)
{
	CComObject<_G2Structure>* newStructure;

    CComObject<_G2Structure>::CreateInstance(&newStructure);
	newStructure->AddRef();
	newStructure->subIDispatch = JavaObject;
	JavaObject->AddRef();
    newStructure->subConstruct();
    *ComObject = (IG2Structure*)newStructure;
    return S_OK;
}

HRESULT CreateStructure(CLSID clsid, SAFEARRAY *NameValuePairs,
                        IG2Structure **Structure)
{
    SAFEARRAY *psa;
    HRESULT hr;
    CComObject<G2Structure>* retval;
    long lLBound;
    long lUBound;
    long cArgs;
    long paircount;
    long i;
    long ix;

    // now lets look inside the passed array and pull out the data
    psa = NameValuePairs;
    if (SafeArrayGetDim(psa) != 1)
    {
        return AtlReportError(clsid,
            "There must be only one array dimension.", GUID_NULL, 0);
    }
    
    hr = SafeArrayGetLBound(psa, 1, &lLBound);
    if (FAILED(hr))
        return E_FAIL;

    hr = SafeArrayGetUBound(psa, 1, &lUBound);
    if (FAILED(hr))
        return E_FAIL;
    
    cArgs = (lUBound - lLBound) + 1;
    
    // ok, we should have a even number of elements
    if (cArgs & 1)
    {
        return AtlReportError(clsid,
            L"Either a name is missing a value or a value is missing a name.",
                GUID_NULL, 0);
    }
    
    hr = CComObject<G2Structure>::CreateInstance(&retval);
    if (FAILED(hr))
        return hr;

    retval->AddRef();
    
    paircount = cArgs / 2;
    for (i = 0; i < paircount; i++)
    {
        SmartVariant var;
        SmartVariant var2;

        ix = lLBound + (i * 2);
        SafeArrayGetElement(psa, &ix, &var);
        ix++;
        SafeArrayGetElement(psa, &ix, &var2);
        if (var.IsString())
            retval->put_Member(var.bstrVal, var2);
    }
    
    *Structure = (IG2Structure*)retval;
    return S_OK;
}

HRESULT CreateSymbol(BSTR SymbolName, IG2Symbol **Symbol)
{
    CComObject<G2Symbol>* newSymbol;

    CComObject<G2Symbol>::CreateInstance(&newSymbol);
    newSymbol->AddRef();
    newSymbol->put_Value(SymbolName);
    *Symbol = (IG2Symbol*)newSymbol;

	return S_OK;
}

// Convert a Bean Bridge SafeArray to a Sequence

HRESULT JavaArrayToSequence(SAFEARRAY *arr, IDispatch **Sequence)

{
	HRESULT hr;
    IDispatch *seq;
	long LBound, UBound;
	OLECHAR *methodName;
    void *pDummy;
    int num_vars;

    // First, create a new object
    hr = CreateJavaObject(L"com.gensym.util.Sequence", &seq);
	if (FAILED(hr))
        return hr;

	// The result should hold the constructed result
	// We now have a Java sequence object.  We want to copy the data from
	// the SAFEARRAY to the object.  We need to be careful in the way that we
	// create the objects.  

	// First make sure that we have a good SAFEARRAY
	if (SafeArrayGetDim(arr) != 1)
        return E_FAIL;

	hr = SafeArrayGetLBound(arr, 1, &LBound);
	if (FAILED(hr))
        return hr;

	hr = SafeArrayGetUBound(arr, 1, &UBound);
	if (FAILED(hr))
        return hr;

	hr = SafeArrayAccessData(arr, &pDummy);
	if (FAILED(hr))
        return hr;

	// We want to copy every element
    for (long i = LBound; i <= UBound; i++)
    {
    	SmartVariant var;

		SafeArrayGetElement(arr, &i, &var);

        // java safe arrays (vectors can have nulls) so do skip empty entries
        num_vars = 1;
        switch (var.vt)
        {
        case VT_I2:
            var = (long)var.iVal;
        case VT_I4:
            methodName = L"addIntElement";
            break;
            
        case VT_BSTR:
            if (var.bstrVal != NULL && var.bstrVal[0] == 0)
            {
                // this method does not have args
                methodName = L"addEmptyStringElement";
                num_vars = 0;
                break;
            }

            methodName = L"addStringElement";
            break;
            
        case VT_R4:
            var = (double)var.fltVal;
        case VT_R8:
            methodName = L"addDoubleElement";
            break;
            
        case VT_BOOL:
            // 9/3/98 there is a bug using booleans with the Bean bridge
            // methodName = L"addBooleanElement";

            var = (long)var.boolVal;
            methodName = L"addPseudoBooleanElement";
            break;
            
        default:
            methodName = L"addElement";
        }
            
        // ok, we have a valid element, add it to the sequence
        // void Sequence.addElement(Object)
        hr = InvokeMethod(seq, methodName, &var, num_vars, NULL);
        if (FAILED(hr))
            return hr;
	}

	*Sequence = seq;

#ifdef _DEBUG
    {
        SmartVariant var;

        CComBSTR error_msg = CallDispatch(seq, L"toString", NULL, 0, &var);
        if (error_msg == (BSTR)NULL && var.vt == VT_BSTR)
            ATLTRACE("sequence = %ws\n",var.bstrVal);
    }
#endif

    return S_OK;
}


// Since the some objects are not exported as a beans, we must bind to a another 
// non-bean object and call the "getNew" member to create a non-bean object
// the quickest object to get is the G2Symbol

// this now gets a symbol object from the cache for performance

HRESULT CreateJavaObject(OLECHAR *classname, IDispatch **Object)
{ 
    IDispatch* pSU;
	SmartVariant varResult;
	SmartVariant pvars[1];

    // don't release the static script utilities
    pSU = GetStaticScriptUtilities();
    if (pSU == NULL)
        return E_FAIL;

	pvars[0] = SysAllocString(classname);
    if (pvars[0].bstrVal == NULL)
        return E_FAIL;

	if (FAILED(InvokeMethod(pSU, L"makeInstance", pvars, 1, &varResult)))
        return E_FAIL;

	*Object = varResult.DetachObject();
    return S_OK;
}

HRESULT JavaVariantArrayToComVariant(SAFEARRAY* pJavaArray, VARIANT* pComVariant)
{
    return JavaArrayToComArray(VT_VARIANT, pJavaArray, VT_VARIANT, pComVariant);
}

HRESULT JavaObjectArrayToComVariant(SAFEARRAY* pJavaArray, VARIANT* pComVariant)
{
    return JavaArrayToComArray(VT_DISPATCH, pJavaArray, VT_VARIANT, pComVariant);
}

HRESULT JavaVariantArrayToItems(SAFEARRAY* pJavaArray, VARIANT* pComVariant)
{
    return JavaArrayToComArray(VT_VARIANT, pJavaArray, VT_DISPATCH, pComVariant);
}

static HRESULT JavaArrayToComArray(VARTYPE javaType, SAFEARRAY* pJavaArray,
                                   VARTYPE comType, VARIANT* pComVariant)
{
	HRESULT hresult;
    SAFEARRAY* pComArray;
	long i, LBound, UBound;
    VARIANT* pCurrentVariant;
    G2Item2** pCurrentItem;

	// First make sure that we have a good SAFEARRAY
	if (SafeArrayGetDim(pJavaArray) != 1)
        return E_FAIL;

	hresult = SafeArrayGetLBound(pJavaArray, 1, &LBound);
	if (FAILED(hresult))
        return hresult;

    hresult = SafeArrayGetUBound(pJavaArray, 1, &UBound);
	if (FAILED(hresult))
        return hresult;

    // create an empty copy of the Java array
    pComArray = SafeArrayCreate(comType, 1, pJavaArray->rgsabound);
	if (pComArray == NULL)
        return E_OUTOFMEMORY;

	// We want to convert every Java Variant to a COM Variant
    pCurrentVariant = (VARIANT*)pComArray->pvData;
    pCurrentItem = (G2Item2**)pComArray->pvData;
    for (i = LBound; i <= UBound; i++, pCurrentVariant++, pCurrentItem++)
    {
        SmartVariant JavaVariant;

        if (javaType == VT_DISPATCH)
        {
    		SafeArrayGetElement(pJavaArray, &i, &JavaVariant.pdispVal);
    		JavaVariant.vt = VT_DISPATCH;
        }
        else if (javaType == VT_VARIANT)
        {
		    SafeArrayGetElement(pJavaArray, &i, &JavaVariant);
        }
        else
        {
            ATLTRACE("Unexpected java type given to JavaArrayToComArray().\n");
            return E_FAIL;
        }

        if (comType == VT_DISPATCH)
        {
            hresult = JavaToItem(JavaVariant.pdispVal, pCurrentItem);
        }
        else if (javaType == VT_VARIANT)
        {
            hresult = JavaVariantToComVariant(JavaVariant, pCurrentVariant);
        }
        else
        {
            ATLTRACE("Unexpected com type given to JavaArrayToComArray().\n");
            return E_FAIL;
        }

        if (FAILED(hresult))
        {
            SafeArrayDestroy(pComArray);
            return hresult;
        }
    }

	pComVariant->parray = pComArray;
    pComVariant->vt = VT_ARRAY | comType;

    return S_OK;
}

// Convert the sequence of workspace elements to a safearray of
//          items using workspaceElement.getItem()
HRESULT WorkspaceElementsToItems(VARIANT varElements, SAFEARRAY** ppItems)
{
    IDispatch* Sequence;
	SmartVariant varResultSize;
    HRESULT hresult;
    long number_of_elements;
    OLECHAR *methodName;
    DISPID dispid;
	SmartVariant varArg;
    DISPPARAMS disp = {&varArg, NULL, 1, 0};
    long i;

    // First make sure that we have a good variant
    if (varElements.vt != VT_DISPATCH)
        return E_FAIL;

    Sequence = varElements.pdispVal;

    // ok, we want to create a safe array of the right size and shape
	// First, find out how many elements are in the sequence
    hresult = InvokeMethod(Sequence, L"size", NULL, 0, &varResultSize);
    if (FAILED(hresult))
        return hresult;

	number_of_elements = varResultSize.lVal;

	// Get the disp id of the array access operation
	// Also set up the call to Java to save time

	methodName = L"elementAt";
	hresult = Sequence->GetIDsOfNames(IID_NULL, &methodName, 1,
                LOCALE_SYSTEM_DEFAULT, &dispid);
    if (FAILED(hresult))
        return hresult;

	// ok, now create a safe array
	*ppItems = SafeArrayCreateVector(VT_DISPATCH, 0,
                   (unsigned int)number_of_elements); 
    if (*ppItems == NULL)
        return E_OUTOFMEMORY;

	for (i = 0; i < number_of_elements; i++)
    {
    	SmartVariant varWorkspaceElement;
    	SmartVariant varResult;
        SmartComPtr<G2Item2> Item;

        // get the element
        varArg = i;
		hresult = Sequence->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
                    DISPATCH_METHOD, &disp, &varWorkspaceElement, NULL, NULL);
        if (FAILED(hresult))
            break;

		if (!varWorkspaceElement.IsObject())
        {
            hresult = E_FAIL;
            break;
        }

        hresult = InvokeMethod(varWorkspaceElement.pdispVal, L"getItem", NULL,
                   0, &varResult);

        if (FAILED(hresult))
            break;

		if (!varResult.IsObject())
        {
            hresult = E_FAIL;
            break;
        }

        hresult = JavaToItem(varResult.pdispVal, &Item);

        SafeArrayPutElement(*ppItems, &i, (IDispatch*)Item);
	}

    return hresult;
}


// We honor the @ symbol in symbol conversion, but does not support the Gensym character set

void UpperCase(BSTR str, WCHAR *outstr)
{
	int i, j;

    j= 0;
	for (i = 0; str[i] != 0; i++) {
		if (str[i] == L'@') {
			i++; // skip escape char
        } else {
            outstr[j] = towupper(str[i]);
            j++;
        }
	}
	outstr[j] = 0;
}

HRESULT NewUpperCaseBSTR(BSTR str, VARIANT *pvar)
{
    if (str == NULL)
    {
        pvar->bstrVal = NULL;
        pvar->vt = VT_BSTR;
        return S_OK;
    }

    pvar->bstrVal = SysAllocString(str);
    if (pvar->bstrVal == NULL)
        return E_OUTOFMEMORY;

    pvar->vt = VT_BSTR;
    UpperCase(str, pvar->bstrVal);
    return S_OK;
}
