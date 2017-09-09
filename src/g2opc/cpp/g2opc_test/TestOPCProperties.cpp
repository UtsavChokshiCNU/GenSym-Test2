#include "stdafx.h"
#include "TestOPCProperties.h"


template <class Interface>
class IUnkImpl : public Interface
{
public:
	virtual ULONG STDMETHODCALLTYPE AddRef() {return 1;}
	virtual ULONG STDMETHODCALLTYPE Release() {return 1;}
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject)
	{
		HRESULT hr = E_NOINTERFACE;
		if (riid == IID_IUnknown)
		{
			hr = GetInterface(ppvObject);
		}

		return hr;
	}

	HRESULT GetInterface(void **ppvObject)
	{
		HRESULT hr = S_OK;
		if (ppvObject == NULL)
			hr = E_POINTER;
		else
			*ppvObject = this;

		return hr;
	}
};

// Items constants
#define ITEM_ID L"Test-Item-Id"
#define PROP_ID 10
#define PROP_TYPE VT_I4
#define PROP_VALUE 100
#define PROP_DESCRIPTION L"TEST-DESC"

// CTestOPCBrowse provides nesessary methods of IOPCBrowse
class CTestOPCBrowse : public IUnkImpl<IOPCBrowse>
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetProperties( 
		/* [in] */ DWORD dwItemCount,
		/* [size_is][string][in] */ LPWSTR *pszItemIDs,
		/* [in] */ BOOL bReturnPropertyValues,
		/* [in] */ DWORD dwPropertyCount,
		/* [size_is][in] */ DWORD *pdwPropertyIDs,
		/* [size_is][size_is][out] */ OPCITEMPROPERTIES **ppItemProperties)
	{
		CPPUNIT_ASSERT(dwItemCount == 1);
		CPPUNIT_ASSERT(dwPropertyCount == 0);
		CPPUNIT_ASSERT(pszItemIDs != NULL && (*pszItemIDs == ITEM_ID || wcscmp(*pszItemIDs, ITEM_ID) == 0));
		CPPUNIT_ASSERT(ppItemProperties != NULL);
		CPPUNIT_ASSERT(bReturnPropertyValues);

		// make result
		OPCITEMPROPERTIES* pItemProperties = (OPCITEMPROPERTIES*) CoTaskMemAlloc(sizeof(OPCITEMPROPERTIES));
		pItemProperties->hrErrorID = S_OK;
		pItemProperties->dwNumProperties = 1;
		pItemProperties->pItemProperties = (OPCITEMPROPERTY*) CoTaskMemAlloc(sizeof(OPCITEMPROPERTY));
		pItemProperties->pItemProperties->wReserved = 0;
		pItemProperties->pItemProperties->dwReserved = 0;
		pItemProperties->pItemProperties->vtDataType = PROP_TYPE;
		memset(&pItemProperties->pItemProperties->vValue, 0, sizeof(VARIANT));
		pItemProperties->pItemProperties->vValue.lVal = PROP_VALUE;
		pItemProperties->pItemProperties->vValue.vt = PROP_TYPE;
		pItemProperties->pItemProperties->szItemID = ITEM_ID;
		pItemProperties->pItemProperties->szDescription = PROP_DESCRIPTION;
		pItemProperties->pItemProperties->hrErrorID = S_OK;
		pItemProperties->pItemProperties->dwPropertyID = PROP_ID;

		*ppItemProperties = pItemProperties;

		return S_OK;
	}

    virtual HRESULT STDMETHODCALLTYPE Browse( 
        /* [string][in] */ LPWSTR szItemID,
        /* [string][out][in] */ LPWSTR *pszContinuationPoint,
        /* [in] */ DWORD dwMaxElementsReturned,
        /* [in] */ OPCBROWSEFILTER dwBrowseFilter,
        /* [string][in] */ LPWSTR szElementNameFilter,
        /* [string][in] */ LPWSTR szVendorFilter,
        /* [in] */ BOOL bReturnAllProperties,
        /* [in] */ BOOL bReturnPropertyValues,
        /* [in] */ DWORD dwPropertyCount,
        /* [size_is][in] */ DWORD *pdwPropertyIDs,
        /* [out] */ BOOL *pbMoreElements,
        /* [out] */ DWORD *pdwCount,
        /* [size_is][size_is][out] */ OPCBROWSEELEMENT **ppBrowseElements)
	{
		return E_NOTIMPL;
	}

};

class COPCItemProperties : public IUnkImpl<IOPCItemProperties>
{
public:
    virtual HRESULT STDMETHODCALLTYPE QueryAvailableProperties( 
        /* [in] */ LPWSTR szItemID,
        /* [out] */ DWORD *pdwCount,
        /* [size_is][size_is][out] */ DWORD **ppPropertyIDs,
        /* [size_is][size_is][out] */ LPWSTR **ppDescriptions,
        /* [size_is][size_is][out] */ VARTYPE **ppvtDataTypes)
	{
		CPPUNIT_ASSERT(szItemID == ITEM_ID || wcscmp(szItemID, ITEM_ID) == 0);
		CPPUNIT_ASSERT(pdwCount != NULL && ppPropertyIDs != NULL && ppDescriptions != NULL &&
			ppvtDataTypes != NULL);

		*pdwCount = 1;

		*ppPropertyIDs = (DWORD*) CoTaskMemAlloc(sizeof(DWORD));
		(*ppPropertyIDs)[0] = PROP_ID;

		*ppDescriptions = (LPWSTR*) CoTaskMemAlloc(sizeof(LPWSTR*));
		(*ppDescriptions)[0] = PROP_DESCRIPTION;

		*ppvtDataTypes = (VARTYPE*) CoTaskMemAlloc(sizeof(VARTYPE*));
		(*ppvtDataTypes)[0] = PROP_TYPE;

		return S_OK;
	}

    virtual HRESULT STDMETHODCALLTYPE GetItemProperties( 
        /* [in] */ LPWSTR szItemID,
        /* [in] */ DWORD dwCount,
        /* [size_is][in] */ DWORD *pdwPropertyIDs,
        /* [size_is][size_is][out] */ VARIANT **ppvData,
        /* [size_is][size_is][out] */ HRESULT **ppErrors)
	{
		CPPUNIT_ASSERT(szItemID == ITEM_ID || wcscmp(szItemID, ITEM_ID) == 0);

		CPPUNIT_ASSERT(pdwPropertyIDs != NULL);
		CPPUNIT_ASSERT(pdwPropertyIDs[0] == PROP_ID);

		CPPUNIT_ASSERT(dwCount == 1);
		CPPUNIT_ASSERT(ppvData != NULL && ppErrors != NULL);

		*ppvData = (VARIANT*) CoTaskMemAlloc(sizeof(VARIANT));
		memset(*ppvData, 0, sizeof(VARIANT));
		(*ppvData)[0].lVal = PROP_VALUE;
		(*ppvData)[0].vt = PROP_TYPE;

		return S_OK;
	}

    virtual HRESULT STDMETHODCALLTYPE LookupItemIDs( 
        /* [in] */ LPWSTR szItemID,
        /* [in] */ DWORD dwCount,
        /* [size_is][in] */ DWORD *pdwPropertyIDs,
        /* [size_is][size_is][string][out] */ LPWSTR **ppszNewItemIDs,
        /* [size_is][size_is][out] */ HRESULT **ppErrors)
	{
		return E_NOTIMPL;
	}


};

// CTestOPCServer provides nesessary methods of IOPCServer interface
class CTestOPCServer : public IUnkImpl<IOPCServer>
{
public:
	CTestOPCServer(bool bUseDAv3) : m_bUseDAv3(bUseDAv3) {}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject)
	{
		HRESULT hr = E_NOINTERFACE;
		if (riid == IID_IOPCBrowse && m_bUseDAv3)
		{
			static CTestOPCBrowse browse;
			hr = browse.GetInterface(ppvObject);
		}
		else if (riid == IID_IOPCItemProperties)
		{
			static COPCItemProperties properties;
			hr = properties.GetInterface(ppvObject);
		}
		else
		{
			hr = IUnkImpl<IOPCServer>::QueryInterface(riid, ppvObject);
		}

		return hr;
	}

        virtual HRESULT STDMETHODCALLTYPE AddGroup( 
            /* [string][in] */ LPCWSTR szName,
            /* [in] */ BOOL bActive,
            /* [in] */ DWORD dwRequestedUpdateRate,
            /* [in] */ OPCHANDLE hClientGroup,
            /* [in][unique] */ LONG *pTimeBias,
            /* [in][unique] */ FLOAT *pPercentDeadband,
            /* [in] */ DWORD dwLCID,
            /* [out] */ OPCHANDLE *phServerGroup,
            /* [out] */ DWORD *pRevisedUpdateRate,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ LPUNKNOWN *ppUnk)
		{
			return E_NOTIMPL;
		}
        
        virtual HRESULT STDMETHODCALLTYPE GetErrorString( 
            /* [in] */ HRESULT dwError,
            /* [in] */ LCID dwLocale,
            /* [string][out] */ LPWSTR *ppString)
		{
			return E_NOTIMPL;
		}
        
        virtual HRESULT STDMETHODCALLTYPE GetGroupByName( 
            /* [string][in] */ LPCWSTR szName,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ LPUNKNOWN *ppUnk)
		{
			return E_NOTIMPL;
		}
        
        virtual HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [out] */ OPCSERVERSTATUS **ppServerStatus)
		{
			return E_NOTIMPL;
		}
        
        virtual HRESULT STDMETHODCALLTYPE RemoveGroup( 
            /* [in] */ OPCHANDLE hServerGroup,
            /* [in] */ BOOL bForce)
		{
			return E_NOTIMPL;
		}
        
        virtual HRESULT STDMETHODCALLTYPE CreateGroupEnumerator( 
            /* [in] */ OPCENUMSCOPE dwScope,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ LPUNKNOWN *ppUnk)
		{
			return E_NOTIMPL;
		}

private:
	bool m_bUseDAv3;
};


////////////////////////////////////////////////////////////////////////////////////////
HRESULT GetItemProperties(IOPCServer* pOPCServer, gsi_char* pItemID, int& nr_props, gsi_item*& pPropIdArray,
                          gsi_char**& pPropDescArray, gsi_char**& pPropTypeArray, gsi_char**& pPropValArray,
                          LPWSTR& szMsg);

void CTestOPCProperties::testItemProperties(bool bUseDAv3)
{
	CTestOPCServer server(bUseDAv3);

	int nr_props = 0;
	gsi_item* pPropIdArray = NULL;
	gsi_char** pPropDescArray = NULL;
	gsi_char** pPropTypeArray = NULL;
	gsi_char** pPropValArray = NULL;
	LPWSTR szMsg = NULL;

	HRESULT hr = GetItemProperties(&server, ITEM_ID, nr_props, pPropIdArray, pPropDescArray,
		pPropTypeArray, pPropValArray, szMsg);

	CPPUNIT_ASSERT(SUCCEEDED(hr));
	CPPUNIT_ASSERT(szMsg == NULL);
	CPPUNIT_ASSERT(nr_props == 1);
	CPPUNIT_ASSERT(pPropIdArray != NULL && pPropDescArray != NULL &&
		pPropTypeArray != NULL && pPropValArray != NULL);

	double id = gsi_flt_of(pPropIdArray[0]);
	CPPUNIT_ASSERT((int) id == PROP_ID);

	gsi_reclaim_items(pPropIdArray);

	CPPUNIT_ASSERT(wcscmp(pPropDescArray[0], PROP_DESCRIPTION) == 0);
	SysFreeString(pPropDescArray[0]);
	delete[] pPropDescArray;

	BSTR strVarType = OpcUtils::ConvertVariantTypeToText(PROP_TYPE);
	CPPUNIT_ASSERT(wcscmp(pPropTypeArray[0], strVarType) == 0);

	SysFreeString(strVarType);
	SysFreeString(pPropTypeArray[0]);
	delete[] pPropTypeArray;

	VARIANT var;
	memset(&var, 0, sizeof(VARIANT));
	var.lVal = PROP_VALUE;
	var.vt = PROP_TYPE;
	BSTR strVar = OpcUtils::CStr(var);
	CPPUNIT_ASSERT(wcscmp(pPropValArray[0], strVar) == 0);

	SysFreeString(strVar);
	SysFreeString(pPropValArray[0]);
	delete[] pPropValArray;
}

void CTestOPCProperties::testUsingIOPCBrowse()
{
	testItemProperties(true);
}

void CTestOPCProperties::testUsingIOPCItemProperties()
{
	testItemProperties(false);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CTestOPCProperties);
