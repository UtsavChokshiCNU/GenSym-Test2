// helpers.h
#ifndef _HELPERS_H
#define _HELPERS_H

class SmartVariant: public CComVariant
{
public:
	SmartVariant& operator=(const SmartVariant& varSrc)
	{
		InternalCopy(&varSrc);
		return *this;
	}

    SmartVariant& operator=(const CComVariant& varSrc)
	{
		InternalCopy(&varSrc);
		return *this;
	}

    SmartVariant& operator=(const VARIANT& varSrc)
	{
		InternalCopy(&varSrc);
		return *this;
	}

	SmartVariant& operator=(BSTR bstrSrc)
	{
		InternalClear();
		vt = VT_BSTR;
		bstrVal = ::SysAllocString(bstrSrc);
		if (bstrVal == NULL && bstrSrc != NULL)
		{
			vt = VT_ERROR;
			scode = E_OUTOFMEMORY;
		}
		return *this;
	}

	SmartVariant& operator=(LPCOLESTR lpszSrc)
	{
		InternalClear();
		vt = VT_BSTR;
		bstrVal = ::SysAllocString(lpszSrc);

		if (bstrVal == NULL && lpszSrc != NULL)
		{
			vt = VT_ERROR;
			scode = E_OUTOFMEMORY;
		}
		return *this;
	}

	#ifndef OLE2ANSI
	SmartVariant& operator=(LPCSTR lpszSrc)
	{
		USES_CONVERSION;
		InternalClear();
		vt = VT_BSTR;
		bstrVal = ::SysAllocString(A2COLE(lpszSrc));

		if (bstrVal == NULL && lpszSrc != NULL)
		{
			vt = VT_ERROR;
			scode = E_OUTOFMEMORY;
		}
		return *this;
	}
	#endif

	SmartVariant& operator=(bool bSrc)
	{
		if (vt != VT_BOOL)
		{
			InternalClear();
			vt = VT_BOOL;
		}
	#pragma warning(disable: 4310) // cast truncates constant value
		boolVal = bSrc ? VARIANT_TRUE : VARIANT_FALSE;
	#pragma warning(default: 4310) // cast truncates constant value
		return *this;
	}

	SmartVariant& operator=(int nSrc)
	{
		if (vt != VT_I4)
		{
			InternalClear();
			vt = VT_I4;
		}
		lVal = nSrc;

		return *this;
	}

	SmartVariant& operator=(BYTE nSrc)
	{
		if (vt != VT_UI1)
		{
			InternalClear();
			vt = VT_UI1;
		}
		bVal = nSrc;
		return *this;
	}

	SmartVariant& operator=(short nSrc)
	{
		if (vt != VT_I2)
		{
			InternalClear();
			vt = VT_I2;
		}
		iVal = nSrc;
		return *this;
	}

	SmartVariant& operator=(long nSrc)
	{
		if (vt != VT_I4)
		{
			InternalClear();
			vt = VT_I4;
		}
		lVal = nSrc;
		return *this;
	}

	SmartVariant& operator=(float fltSrc)
	{
		if (vt != VT_R4)
		{
			InternalClear();
			vt = VT_R4;
		}
		fltVal = fltSrc;
		return *this;
	}

	SmartVariant& operator=(double dblSrc)
	{
		if (vt != VT_R8)
		{
			InternalClear();
			vt = VT_R8;
		}
		dblVal = dblSrc;
		return *this;
	}

	SmartVariant& operator=(CY cySrc)
	{
		if (vt != VT_CY)
		{
			InternalClear();
			vt = VT_CY;
		}
		cyVal.Hi = cySrc.Hi;
		cyVal.Lo = cySrc.Lo;
		return *this;
	}

	SmartVariant& operator=(IDispatch* pSrc)
	{
		InternalClear();
		vt = VT_DISPATCH;
		pdispVal = pSrc;
		// Need to AddRef as VariantClear will Release
		if (pdispVal != NULL)
			pdispVal->AddRef();
		return *this;
	}

	SmartVariant& operator=(IUnknown* pSrc)
	{
		InternalClear();
		vt = VT_UNKNOWN;
		punkVal = pSrc;

		// Need to AddRef as VariantClear will Release
		if (punkVal != NULL)
			punkVal->AddRef();
		return *this;
	}

	void AttachString(BSTR bstr)
	{
		InternalClear();
		bstrVal = bstr;
		vt = VT_BSTR;
	}

    // this is useful when we calling methods that return arrays that do not
    //  need conversion
    SAFEARRAY *DetachArray(void)
    {
        SAFEARRAY *result = NULL;

        if (vt & VT_ARRAY)
        {
            if (vt & VT_BYREF)
                result = *pparray;
            else
                result = parray;
        }

        vt = VT_EMPTY;
        return result;
    }

    // this is useful when we calling methods that return objects that do not
    //  need conversion, we do not have to call AddRef
    IDispatch *DetachObject(void)
    {
        IDispatch *result = NULL;

        if (vt & VT_DISPATCH)
        {
            if (vt & VT_BYREF)
                result = *ppdispVal;
            else
                result = pdispVal;
        }

        vt = VT_EMPTY;
        return result;
    }

    // this is useful when we calling methods that return strings that are
    //  passed up to our caller.
    //  we avoid calling SysAllocString and check it for errors
    BSTR DetachString(void)
    {
        BSTR result = NULL;

        if (vt & VT_BSTR)
        {
            if (vt & VT_BYREF)
                result = *pbstrVal;
            else
                result = bstrVal;
        }

        vt = VT_EMPTY;
        return result;
    }

    bool IsBoolean(void)
    {
        return vt == VT_BOOL;
    }

    bool IsDouble(void)
    {
        return vt == VT_R8;
    }

    bool IsEmpty(void)
    {
        return vt == VT_EMPTY;
    }

    bool IsInteger(void)
    {
        return vt == VT_I4;
    }

    bool IsNull(void)
    {
        return vt == VT_NULL;
    }

    bool IsObject(void)
    {
        return vt == VT_DISPATCH;
    }

    bool IsObjectArray(void)
    {
        return vt == (VT_DISPATCH | VT_ARRAY);
    }

    bool IsString(void)
    {
        return vt == VT_BSTR;
    }

    bool IsStringArray(void)
    {
        return vt == (VT_BSTR | VT_ARRAY);
    }

    bool IsVariantArray(void)
    {
        return vt == (VT_VARIANT | VT_ARRAY);
    }

    void SetToNull(void)
	{
		InternalClear();
		pdispVal = NULL;
		vt = VT_NULL;
	}
};

template <class T>
class _NoAddRefReleaseOnSmartComPtr : public T
{
	private:
		STDMETHOD_(ULONG, AddRef)()=0;
		STDMETHOD_(ULONG, Release)()=0;
};

template <class T>
class SmartComPtr
{
public:
	typedef T _PtrClass;
	SmartComPtr()
	{
		p=NULL;
	}
	SmartComPtr(T* lp)
	{
		if ((p = lp) != NULL)
			p->AddRef();
	}
	SmartComPtr(const SmartComPtr<T>& lp)
	{
		if ((p = lp.p) != NULL)
			p->AddRef();
	}
	~SmartComPtr()
	{
		if (p)
			p->Release();
	}
	void Release()
	{
		IUnknown* pTemp = p;
		if (pTemp)
		{
			p = NULL;
			pTemp->Release();
		}
	}
	operator T*() const
	{
		return (T*)p;
	}
	T& operator*() const
	{
		return *p;
	}
	T** operator&()
	{
		return &p;
	}
	_NoAddRefReleaseOnSmartComPtr<T>* operator->() const
	{
		return (_NoAddRefReleaseOnSmartComPtr<T>*)p;
	}
	T* operator=(T* lp)
	{
		return (T*)AtlComPtrAssign((IUnknown**)&p, lp);
	}
	T* operator=(const SmartComPtr<T>& lp)
	{
		return (T*)AtlComPtrAssign((IUnknown**)&p, lp.p);
	}
	bool operator!() const
	{
		return (p == NULL);
	}
	bool operator<(T* pT) const
	{
		return p < pT;
	}
	bool operator==(T* pT) const
	{
		return p == pT;
	}
	// Compare two objects for equivalence
	bool IsEqualObject(IUnknown* pOther)
	{
		if (p == NULL && pOther == NULL)
			return true; // They are both NULL objects

		if (p == NULL || pOther == NULL)
			return false; // One is NULL the other is not

		SmartComPtr<IUnknown> punk1;
		SmartComPtr<IUnknown> punk2;
		p->QueryInterface(IID_IUnknown, (void**)&punk1);
		pOther->QueryInterface(IID_IUnknown, (void**)&punk2);
		return punk1 == punk2;
	}
	void Attach(T* p2)
	{
		if (p)
			p->Release();
		p = p2;
	}
	T* Detach()
	{
		T* pt = p;
		p = NULL;
		return pt;
	}
	HRESULT CopyTo(T** ppT)
	{
		if (ppT == NULL)
			return E_POINTER;
		*ppT = p;
		if (p)
			p->AddRef();
		return S_OK;
	}
	T* p;
};

#endif // _HELPERS_H
