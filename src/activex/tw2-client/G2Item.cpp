// G2Item.cpp : Implementation of CG2Item
#include "G2Item.h"
#include "util.h"
#include "convert.h"

/////////////////////////////////////////////////////////////////////////////
// CG2Item

CG2Item::CG2Item()
{
    init();
}

CG2Item::~CG2Item()
{
    subDestruct();
    ATLTRACE("G2Item Destroyed\n\n\n");
}

HRESULT CG2Item::FinalConstruct()
{
    ATLTRACE("G2Item Created\n\n");
    return subConstruct();
}

// set subIDispatch be for calling this method
HRESULT CG2Item::subConstruct()
{
    return S_OK;
}

void CG2Item::init()
{
    // Set up all of the defualt values
    m_call_timeout = 30;
}

void CG2Item::subDestruct()
{
    CComBSTR itemString;

    if (SUCCEEDED(String(&itemString)))
        ATLTRACE("\nReleasing Java Object: %ws\n\n", (BSTR)itemString);
    else
        ATLTRACE("\nReleasing a bad Java Object\n\n");
    
    init();
}

STDMETHODIMP CG2Item::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IG2Item,
	};

    for (int i = 0; i < sizeof (arr) / sizeof (arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CG2Item::get_Attribute(BSTR AttributeName, VARIANT * pVal)
{
	SmartVariant pvars[1];
    SmartVariant varResult;

    BSTR error_msg = BSTRToJava(AttributeName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

	error_msg = CallDispatch(subIDispatch, L"getPropertyValue", pvars, 1,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    HRESULT hresult  = JavaVariantToComVariant(varResult, pVal);
    if (FAILED(hresult))
        return Error("Received an invalid attribute from G2.");

	return S_OK;
}

STDMETHODIMP CG2Item::put_Attribute(BSTR AttributeName, VARIANT newVal)
{
	SmartVariant pvars[2];
    OLECHAR *method_name;
    int num_vars = 2;

	// convert input
    BSTR error_msg = BSTRToJava(AttributeName, &pvars[1]);
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
        method_name = L"setIntPropertyValue";
        break;

    case VT_BSTR:
        if (pvars[0].bstrVal != NULL && pvars[0].bstrVal[0] == 0)
        {
            // this method takes only one parameter
            method_name = L"setEmptyStringPropertyValue";
            pvars[0] = pvars[1];
            num_vars = 1;
            break;
        }

        method_name = L"setStringPropertyValue";
        break;

    case VT_R4:
        pvars[0] = (double)pvars[0].fltVal;
    case VT_R8:
        method_name = L"setDoublePropertyValue";
        break;

    case VT_BOOL:
        // 9/3/98 there is a bug using booleans with the Bean bridge
        //method_name = L"setBooleanPropertyValue";

        pvars[0] = (long)pvars[0].boolVal;
        method_name = L"setPseudoBooleanPropertyValue";
        break;

    default:
        method_name = L"setPropertyValue";
    }

    // void Item.setPropertyValue(Symbol, Object)
	error_msg = CallDispatch(subIDispatch, method_name, pvars, num_vars,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    // Give Java time to send events before we return.
    ::Sleep(1);
	return S_OK;
}

STDMETHODIMP CG2Item::get_AttributeNames(VARIANT *ListOfNames)
{
    long i;
	SmartVariant pvars[1];
    SmartVariant varResultAttributes;
    SAFEARRAY* pAttributeNameVariants;
    SAFEARRAY* pNames;

    BSTR error_msg = OLECHARToJavaSymbol(L"administrator", &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

    // sequence<structure> = item.getDescriptions
    error_msg = CallDispatch(subIDispatch, L"getVisibleAttributes", pvars, 1,
                        &varResultAttributes);
    if (error_msg != NULL)
        return Error(error_msg);

	HRESULT hresult = SequenceToArray(varResultAttributes.pdispVal,
                &pAttributeNameVariants, 0, true);
    if (FAILED(hresult))
        return hresult;

    if (!(pAttributeNameVariants->fFeatures & FADF_VARIANT))
    {
        SafeArrayDestroy(pAttributeNameVariants);
        return E_FAIL;
    }

    // variant array of must be converted to an array of BSTR's.
    long last_struct;

	hresult = SafeArrayGetUBound(pAttributeNameVariants, 1, &last_struct);
	if(FAILED(hresult))
    {
        SafeArrayDestroy(pAttributeNameVariants);
		return hresult;
    }

 	pNames = SafeArrayCreateVector(VT_BSTR, 0, last_struct + 1);
	if (pNames == NULL)
    {
        SafeArrayDestroy(pAttributeNameVariants);
        return E_OUTOFMEMORY;
    }

    for (i = 0; i <= last_struct; i++)
    {
        SmartVariant varResult;

        hresult = SafeArrayGetElement(pAttributeNameVariants, &i,
                    (void*)&varResult);
        if (FAILED(hresult))
            break;

        if (!varResult.IsString())
        {
            hresult = E_FAIL;
            break;
        }

        hresult = SafeArrayPutElement(pNames, &i, (void*)varResult.bstrVal);
        if (FAILED(hresult))
            break;
    }

    SafeArrayDestroy(pAttributeNameVariants);

    if (FAILED(hresult))
    {
        SafeArrayDestroy(pNames);
        return hresult;
    }

	ListOfNames->vt = VT_ARRAY | VT_BSTR;
	ListOfNames->parray = pNames;
	return S_OK;
}

STDMETHODIMP CG2Item::get_ElementCount(long * pVal)
{
    DISPID dispid;
    BSTR error_msg;
    SmartVariant varResult;
    SmartComPtr<IDispatch> Sequence;

    // count = ItemArray.getArrayLength()
    dispid = GetDispId(subIDispatch, L"getArrayLength");
	if (dispid != -1)
    {
        error_msg = CallInvoke(subIDispatch, dispid, NULL, 0, &varResult);
        if (error_msg != NULL)
            return Error(error_msg);

        *pVal = varResult.lVal;
        return S_OK;
    }

    // SequenceObject = ItemList.getG2ListSequence()
    dispid = GetDispId(subIDispatch, L"getG2ListSequence");
    if (dispid == -1)
    {
        ATLTRACE("*get_ElementCount(): Unable to find method\n");
	    return Error(L"This subclass of item does not support ElementCount.");
    }

    error_msg = CallInvoke(subIDispatch, dispid, NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    // count = sequence.size()
    Sequence.Attach(varResult.DetachObject());
    error_msg = CallDispatch(Sequence, L"size", NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    *pVal = varResult.lVal;
    return S_OK;
}

STDMETHODIMP CG2Item::get_ElementType(G2ElementType * pVal)
{
    DISPID dispid;
    BSTR error_msg;
    SmartVariant varResult;
    CComBSTR type;

    // Symbol = ItemArray.getElementType()
    //    or
    // Symbol = ItemList.getElementType()

    dispid = GetDispId(subIDispatch, L"getElementType");
    if (dispid == -1)
    {
        ATLTRACE("*get_ElementType(): Unable to find method\n");
	    return Error(L"This subclass of item does not support ElementType.");
    }

    error_msg = CallInvoke(subIDispatch, dispid, NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    // convert symbol to enum
    HRESULT hresult = JavaToBSTR(varResult.pdispVal, &type);
    if (FAILED(hresult))
        return hresult;

    hresult = S_OK;

    if (wcscmp(type, L"VALUE") == 0)
        *pVal = g2ValueType;
    else if (wcscmp(type, L"ITEM-OR-VALUE") == 0)
        *pVal = g2ItemOrValueType;
    else if (wcscmp(type, L"QUANTITY") == 0)
        *pVal = g2QuantityType;
    else if (wcscmp(type, L"TEXT") == 0)
        *pVal = g2TextType;
    else if (wcscmp(type, L"TRUTH-VALUE") == 0)
        *pVal = g2TruthValueType;
    else if (wcscmp(type, L"ITEM") == 0)
        *pVal = g2ItemType;
    else if (wcscmp(type, L"INTEGER") == 0)
        *pVal = g2IntegerType;
    else if (wcscmp(type, L"FLOAT") == 0)
        *pVal = g2FloatType;
    else if (wcscmp(type, L"SYMBOL") == 0)
        *pVal = g2SymbolType;
    else
        hresult = E_FAIL;

    return hresult;
}

STDMETHODIMP CG2Item::get_Element(long Index, VARIANT * pVal)
{
    DISPID dispid;
    BSTR error_msg;
    SmartVariant pvars[1];
    SmartVariant varResult;
    HRESULT hresult;
    SmartComPtr<IDispatch> Sequence;

    // SequenceObject = ItemArray.getG2ArraySequence()
    dispid = GetDispId(subIDispatch, L"getG2ArraySequence");
	if (dispid == -1)
    {
        //    or
        // SequenceObject = ItemList.getG2ListSequence()
        dispid = GetDispId(subIDispatch, L"getG2ListSequence");
        if (dispid == -1)
        {
            ATLTRACE("*get_ElementCount(): Unable to find method\n");
    	    return Error(L"This subclass of item does not support Element.");
        }
    }

    error_msg = CallInvoke(subIDispatch, dispid, NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return Error("Received an unexpected data type from G2.");

    Sequence.Attach(varResult.DetachObject());
    
    // Object = SequenceObject.elementAt(Index)
    pvars[0] = Index;
    error_msg = CallDispatch(Sequence, L"elementAt", pvars, 1, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    hresult = JavaVariantToComVariant(varResult, pVal);
    return hresult;
}

STDMETHODIMP CG2Item::put_Element(long Index, VARIANT newVal)
{
    DISPID dispid;
    BSTR error_msg;
    SmartVariant pvars[2];
    SmartVariant varResult;
    HRESULT hresult;
    OLECHAR *method_name;
    SmartComPtr<IDispatch> Sequence;
    int num_vars = 2;

    // SequenceObject = ItemArray.getG2ArraySequence()
    BOOL isArray = true;
    dispid = GetDispId(subIDispatch, L"getG2ArraySequence");
	if (dispid == -1)
    {
        //    or
        // SequenceObject = ItemList.getG2ListSequence()
        isArray = false;
        dispid = GetDispId(subIDispatch, L"getG2ListSequence");
        if (dispid == -1)
        {
            ATLTRACE("*get_ElementCount(): Unable to find method\n");
    	    return Error(L"This subclass of item does not support Element.");
        }

    }

    error_msg = CallInvoke(subIDispatch, dispid, NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsObject())
        return E_FAIL;

    Sequence.Attach(varResult.DetachObject());

    pvars[0] = Index;
    error_msg = CallDispatch(Sequence, L"removeElementAt", pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    pvars[0] = Index;
    hresult = ComVariantToJavaVariant(newVal, &pvars[1]);
    if (FAILED(hresult))
        return hresult;

    switch (pvars[1].vt)
    {
    case VT_I2:
        pvars[1] = (long)pvars[1].iVal;
    case VT_I4:
        method_name = L"insertIntegerElementAt";
        break;

    case VT_BSTR:
        if (pvars[1].bstrVal != NULL && pvars[1].bstrVal[0] == 0)
        {
            // this method take only one parameter
            method_name = L"insertEmptyStringElementAt";
            num_vars = 1;
            break;
        }

        method_name = L"insertStringElementAt";
        break;

    case VT_R4:
        pvars[1] = (double)pvars[1].fltVal;
    case VT_R8:
        method_name = L"insertDoubleElementAt";
        break;

    case VT_BOOL:
        // 9/3/98 there is a bug using booleans with the Bean bridge
        //method_name = L"insertBooleanElementAt";

        pvars[1] = (long)pvars[1].boolVal;
        method_name = L"insertPseudoBooleanElementAt";
        break;

    default:
        method_name = L"insertElementAt";
    }

    // void Sequence.insertElementAt(Object, int)
    error_msg = CallDispatch(Sequence, method_name, pvars, num_vars, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    if (isArray)
    {
        // ItemArray.setG2ArraySequence(SequenceObject)
        dispid = GetDispId(subIDispatch, L"setG2ArraySequence");
    }
    else
    {
        //    or
        // ItemList.setG2ListSequence(SequenceObject)
        dispid = GetDispId(subIDispatch, L"setG2ListSequence");
    }

    if (dispid == -1)
    {
        ATLTRACE("*get_ElementCount(): Unable to find method\n");
  	    return Error(L"This subclass of item does not support Element.");
    }

    pvars[0] = (IDispatch*)Sequence;

    error_msg = CallInvoke(subIDispatch, dispid, pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

    return S_OK;
}

STDMETHODIMP CG2Item::get_Elements(VARIANT * pVal)
{
    DISPID dispid;
    BSTR error_msg;
    SmartVariant varResult;

    // SequenceObject = ItemArray.getG2ArraySequence()
    dispid = GetDispId(subIDispatch, L"getG2ArraySequence");
	if (dispid == -1)
    {
        //    or
        // SequenceObject = ItemList.getG2ListSequence()
        dispid = GetDispId(subIDispatch, L"getG2ListSequence");
        if (dispid == -1)
        {
            ATLTRACE("*get_ElementCount(): Unable to find method\n");
    	    return Error(L"This subclass of item does not support Elements.");
        }
    }

    error_msg = CallInvoke(subIDispatch, dispid, NULL, 0, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    return SequenceToVariant(varResult.pdispVal, pVal, 0);
}

STDMETHODIMP CG2Item::put_Elements(VARIANT newVal)
{
    SmartVariant pvars[1];

    // ItemArray.setG2ArrayContents(SequenceObject)
    DISPID dispid = GetDispId(subIDispatch, L"setG2ArraySequence");
	if (dispid == -1)
    {
        //    or
        // ItemList.setListSequence(SequenceObject)
        dispid = GetDispId(subIDispatch, L"setG2ListSequence");
        if (dispid == -1)
        {
            ATLTRACE("*get_ElementCount(): Unable to find method\n");
    	    return Error(L"This subclass of item does not support Elements.");
        }
    }

    // make sure pVal is a safe array then convert to sequence
    if (!(newVal.vt & VT_ARRAY))
        return Error("Elements must be an array");

    HRESULT hresult = ArrayToVariant(newVal.parray, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

    BSTR error_msg = CallInvoke(subIDispatch, dispid, pvars, 1, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::CallMethod(BSTR MethodName, SAFEARRAY  **InputArguments, VARIANT * ReturnArguments)
{
	SmartVariant pvars[3];
    SmartVariant varResult;

    BSTR error_msg = BSTRToJava(MethodName, &pvars[2]);
    if (error_msg != NULL)
        return Error(error_msg);

    HRESULT hresult = ArrayToVariant(*InputArguments, &pvars[1]);
    if (FAILED(hresult))
        return hresult;

    pvars[0] = m_call_timeout * 1000;

    error_msg = CallDispatch(subIDispatch, L"callMethodForVB", pvars, 3,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    hresult = JavaVariantToComVariant(varResult, ReturnArguments);
    return hresult;
}

STDMETHODIMP CG2Item::StartMethod(BSTR MethodName, SAFEARRAY **Arguments)
{
	SmartVariant pvars[2];

    BSTR error_msg = BSTRToJava(MethodName, &pvars[1]);
    if (error_msg != NULL)
        return Error(error_msg);

    HRESULT hresult = ArrayToVariant(*Arguments, &pvars[0]);
    if (FAILED(hresult))
        return hresult;

	error_msg = CallDispatch(subIDispatch, L"startMethod", pvars, 2, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}


// This method creates a symbol object, populates the symbol state with the 
// passed value and returns it

STDMETHODIMP CG2Item::Symbol(BSTR SymbolName, IG2Symbol ** val)
{
    return CreateSymbol(SymbolName, val);
}

// Create a structure object

STDMETHODIMP CG2Item::Structure(SAFEARRAY **NameValuePairs, IG2Structure ** Structure)
{
    return CreateStructure(CLSID_G2Item, *NameValuePairs, Structure);
}

STDMETHODIMP CG2Item::get_CallTimeout(long *pVal)
{
    *pVal = m_call_timeout;
	return S_OK;
}

STDMETHODIMP CG2Item::put_CallTimeout(long newVal)
{
    m_call_timeout = newVal;
	return S_OK;
}

STDMETHODIMP CG2Item::get_Self(IG2Item **pVal)
{
	*pVal = this;
	InternalAddRef();
	return S_OK;
}

STDMETHODIMP CG2Item::_subObject(/*[out, retval]*/ IDispatch **subObject)
{
    _SUBOBJECT_METHOD_IMPL(subObject, subIDispatch);
}

STDMETHODIMP CG2Item::IsInstanceOfClass(BSTR ClassName, VARIANT_BOOL * Result)
{
	SmartVariant pvars[1];
    SmartVariant varResult;

    BSTR error_msg = BSTRToJava(ClassName, &pvars[0]);
    if (error_msg != NULL)
        return Error(error_msg);

	error_msg = CallDispatch(subIDispatch, L"isInstanceOfG2Class", pvars, 1,
                        &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    *Result = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2Item::String(BSTR *StringValue)
{
    SmartVariant varResult;

    // call the toString method on the internal Java object
    BSTR error_msg = CallDispatch(subIDispatch, L"toString", NULL, 0, &varResult);
	if (error_msg)
        return Error(error_msg);

    if (!varResult.IsString())
    {
        return Error(
            "G2Item.String(): The method of internal object did not return a "
            "value of type string.");
    }

    *StringValue = varResult.DetachString();
	return S_OK;
}

STDMETHODIMP CG2Item::Delete(VARIANT_BOOL WithPermanencyChecksDisabled,
    VARIANT_BOOL WithoutLeavingStubs)
{
	SmartVariant pvars[2];

	ATLTRACE("CG2Item::Delete()\n");

    pvars[1] = (long)WithPermanencyChecksDisabled;
    pvars[0] = (long)WithoutLeavingStubs;

    BSTR error_msg = CallDispatch(subIDispatch, L"deleteForVB", pvars, 2, NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::Disable()
{
    BSTR error_msg = CallDispatch(subIDispatch, L"disable", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::Enable()
{
    BSTR error_msg = CallDispatch(subIDispatch, L"enable", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::DropToBottom()
{
    BSTR error_msg = CallDispatch(subIDispatch, L"dropToBottom", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::LiftToTop()
{
    BSTR error_msg = CallDispatch(subIDispatch, L"liftToTop", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::G2Clone(IG2Item ** ReturnedItem)
{
	SmartVariant varResult;

	ATLTRACE("CG2Item::G2Clone()\n");

	BSTR error_msg = CallDispatch(subIDispatch, L"g2Clone", NULL,
                        0, &varResult);
	if (error_msg != NULL)
        return Error(error_msg);

	JavaToItem(varResult.pdispVal, (G2Item2**)ReturnedItem);
	return S_OK;
}

STDMETHODIMP CG2Item::MakeTransient()
{
    BSTR error_msg = CallDispatch(subIDispatch, L"makeTransient", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::MakePermanent()
{
    BSTR error_msg = CallDispatch(subIDispatch, L"makePermanent", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::MoveBy(long XDelta, long YDelta,
    VARIANT_BOOL EnlargeWorkspaceIfNecessary, VARIANT_BOOL * Successful)
{
	SmartVariant pvars[3];
	SmartVariant varResult;

	ATLTRACE("CG2Item::MoveBy()\n");

    pvars[2] = XDelta;
    pvars[1] = YDelta;
    pvars[0] = (long)EnlargeWorkspaceIfNecessary;

    BSTR error_msg = CallDispatch(subIDispatch, L"moveByForVB", pvars, 3,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*Successful = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2Item::Move(long X, long Y,
    VARIANT_BOOL EnlargeWorkspaceIfNecessary, VARIANT_BOOL * Successful)
{
	SmartVariant pvars[3];
	SmartVariant varResult;

	ATLTRACE("CG2Item::Move()\n");

    pvars[2] = X;
    pvars[1] = Y;
    pvars[0] = (long)EnlargeWorkspaceIfNecessary;

    BSTR error_msg = CallDispatch(subIDispatch, L"moveForVB", pvars, 3,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*Successful = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2Item::SetBounds(long Left, long Top, long Right, long Bottom)
{
	SmartVariant pvars[4];

	ATLTRACE("CG2Item::SetBounds()\n");

    pvars[3] = Left;
    pvars[2] = Top;
    pvars[1] = Right;
    pvars[0] = Bottom;

	BSTR error_msg = CallDispatch(subIDispatch, L"setBounds", pvars, 4, NULL);
	if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::TransferOff(VARIANT_BOOL * Successful)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subIDispatch, L"transferOff", NULL, 0,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*Successful = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2Item::TransferToItem(IG2Item * Item, BSTR AttributeName, BSTR ClassQualifier, VARIANT_BOOL * Successful)
{
	SmartVariant pvars[3];
	SmartVariant varResult;

	ATLTRACE("CG2Item::TransferToItem()\n");

	SUBOBJECT_AS_VARIANT(Item, &pvars[2]);

    BSTR error_msg = BSTRToJava(AttributeName, &pvars[1]);
    if (error_msg != NULL)
        return Error(error_msg);

    // the default value for class qualifier is a NULL symbol object
    if (ClassQualifier == NULL || ClassQualifier[0] == 0)
    {
        pvars[0].SetToNull();
    }
    else
    {
        error_msg = BSTRToJava(ClassQualifier, &pvars[0]);
        if (error_msg != NULL)
            return Error(error_msg);
    }

    error_msg = CallDispatch(subIDispatch, L"transferToItem", pvars, 3,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*Successful = varResult.boolVal;
	return S_OK;
}
STDMETHODIMP CG2Item::TransferToWorkspace(IG2Item * Workspace, long X, long Y,
    VARIANT_BOOL * Successful)
{
	SmartVariant pvars[3];
	SmartVariant varResult;

	ATLTRACE("CG2Item::TransferToWorkspace()\n");

	SUBOBJECT_AS_VARIANT(Workspace, &pvars[2]);
    pvars[1] = X;
    pvars[0] = Y;

    BSTR error_msg = CallDispatch(subIDispatch, L"transferToWorkspace", pvars, 3,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*Successful = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2Item::RestoreNormalSize()
{
    BSTR error_msg = CallDispatch(subIDispatch, L"restoreNormalSize", NULL, 0,
                        NULL);
    if (error_msg != NULL)
        return Error(error_msg);

	return S_OK;
}

STDMETHODIMP CG2Item::get_ManuallyDisabled(VARIANT_BOOL * pVal)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subIDispatch, L"getManuallyDisabled", NULL, 0,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*pVal = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2Item::get_Transient(VARIANT_BOOL * pVal)
{
	SmartVariant varResult;

    BSTR error_msg = CallDispatch(subIDispatch, L"getTransient", NULL, 0,
                    &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

   	*pVal = varResult.boolVal;
	return S_OK;
}

STDMETHODIMP CG2Item::Equals(IG2Item * Item, VARIANT_BOOL * pVal)
{
	SmartVariant pvars[1];
	SmartVariant varResult;

	SUBOBJECT_AS_VARIANT(Item, &pvars[0]);

    BSTR error_msg = CallDispatch(subIDispatch, L"equals", pvars, 1, &varResult);
    if (error_msg != NULL)
        return Error(error_msg);

    if (!varResult.IsBoolean())
    {
        return Error(
           "G2Item.Equals(): The method of the internal object did not return "
           "a value of type boolean.");
    }

    *pVal = varResult.boolVal;
	return S_OK;
}
