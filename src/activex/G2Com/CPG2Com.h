//////////////////////////////////////////////////////////////////////////////
// CProxy_G2Events
template <class T>
class CProxy_G2Events : public IConnectionPointImpl<T, &DIID__G2Events, CComDynamicUnkArray>
{
public:
    //methods:
    //_G2Events : IDispatch
public:
    void Fire_RpcStarted(
        BSTR ProcedureName,
        VARIANT * InputArguments)
    {
        VARIANTARG* pvars = new VARIANTARG[2];
        for (int i = 0; i < 2; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[1].vt = VT_BSTR;
                pvars[1].bstrVal= ProcedureName;
                pvars[0].vt = VT_VARIANT | VT_BYREF;
                pvars[0].byref= InputArguments;
                DISPPARAMS disp = { pvars, NULL, 2, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete[] pvars;
    }
    void Fire_G2Paused()
    {
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                DISPPARAMS disp = { NULL, NULL, 0, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
    }
    void Fire_G2Resumed()
    {
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                DISPPARAMS disp = { NULL, NULL, 0, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
    }
    void Fire_G2Connected()
    {
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                DISPPARAMS disp = { NULL, NULL, 0, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
    }
    void Fire_G2Disconnected()
    {
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                DISPPARAMS disp = { NULL, NULL, 0, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
    }
    void Fire_RpcCalled(
        BSTR ProcedureName,
        VARIANT * InputArguments,
        VARIANT * ReturnArguments)
    {
        VARIANTARG* pvars = new VARIANTARG[3];
        for (int i = 0; i < 3; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[2].vt = VT_BSTR;
                pvars[2].bstrVal= ProcedureName;
                pvars[1].vt = VT_VARIANT | VT_BYREF;
                pvars[1].byref= InputArguments;
                pvars[0].vt = VT_VARIANT | VT_BYREF;
                pvars[0].byref= ReturnArguments;
                DISPPARAMS disp = { pvars, NULL, 3, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete[] pvars;
    }
    void Fire_RpcReturned(
        BSTR ProcedureName,
        VARIANT * ReturnArguments,
        VARIANT * DeferredCallIdentifier)
    {
        VARIANTARG* pvars = new VARIANTARG[3];
        for (int i = 0; i < 3; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[2].vt = VT_BSTR;
                pvars[2].bstrVal= ProcedureName;
                pvars[1].vt = VT_VARIANT | VT_BYREF;
                pvars[1].byref= ReturnArguments;
                pvars[0].vt = VT_VARIANT | VT_BYREF;
                pvars[0].byref= DeferredCallIdentifier;
                DISPPARAMS disp = { pvars, NULL, 3, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete[] pvars;
    }
    void Fire_Error(
        BSTR ErrorMessage,
        long ErrorCode,
        VARIANT * DeferredCallIdentifier)
    {
        VARIANTARG* pvars = new VARIANTARG[3];
        for (int i = 0; i < 3; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[2].vt = VT_BSTR;
                pvars[2].bstrVal= ErrorMessage;
                pvars[1].vt = VT_I4;
                pvars[1].lVal= ErrorCode;
                pvars[0].vt = VT_VARIANT | VT_BYREF;
                pvars[0].byref= DeferredCallIdentifier;
                DISPPARAMS disp = { pvars, NULL, 3, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete[] pvars;
    }
    void Fire_GotMessage(
        BSTR Message)
    {
        VARIANTARG* pvars = new VARIANTARG[1];
        for (int i = 0; i < 1; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[0].vt = VT_BSTR;
                pvars[0].bstrVal= Message;
                DISPPARAMS disp = { pvars, NULL, 1, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete[] pvars;
    }
    void Fire_G2Reset()
    {
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                DISPPARAMS disp = { NULL, NULL, 0, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0xA, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
    }
    void Fire_G2Started()
    {
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                DISPPARAMS disp = { NULL, NULL, 0, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0xB, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
    }
    void Fire_G2RunStateKnown()
    {
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                DISPPARAMS disp = { NULL, NULL, 0, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x0C, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
    }
    void Fire_ItemDeleted(IDispatch *pItem, long itemHandle, VARIANT userData)
    {
        VARIANTARG* pvars = new VARIANTARG[3];
        for (int i = 0; i < 3; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[2].vt = VT_DISPATCH | VT_BYREF ;
                pvars[2].ppdispVal = &pItem;
                pvars[1].vt = VT_I4;
                pvars[1].lVal = itemHandle ;
                VariantCopy(pvars, &userData) ;
                DISPPARAMS disp = { pvars, NULL, 3, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x0D, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete [] pvars ;

        if (pItem)
            ((CG2Item*)pItem)->InternalUnsubscribeAll(false) ;
    }
    void Fire_ItemModified(IDispatch *pItem, long itemHandle, BSTR attrName, VARIANT newVal, VARIANT userData)
    {
        VARIANTARG* pvars = new VARIANTARG[5];
        for (int i = 0; i < 5; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[4].vt = VT_DISPATCH | VT_BYREF ;
                pvars[4].ppdispVal = &pItem;
                pvars[3].vt = VT_BSTR ;
                pvars[3].bstrVal = attrName ;
                VariantCopy(pvars+2, &newVal) ;
                pvars[1].vt = VT_I4;
                pvars[1].lVal = itemHandle ;
                VariantCopy(pvars, &userData) ;
                DISPPARAMS disp = { pvars, NULL, 5, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x0E, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete [] pvars ;
    }
    void Fire_IconColorChg(IDispatch *pItem, long itemHandle, VARIANT chgStruct, VARIANT userData)
    {
        VARIANTARG* pvars = new VARIANTARG[4];
        for (int i = 0; i < 4; i++)
            VariantInit(&pvars[i]);
       T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[3].vt = VT_DISPATCH | VT_BYREF ;
                pvars[3].ppdispVal = &pItem;
                pvars[2].vt = VT_I4;
                pvars[2].lVal = itemHandle ;
                VariantCopy(pvars+1, &chgStruct) ;
                VariantCopy(pvars, &userData) ;
                DISPPARAMS disp = { pvars, NULL, 4, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x0F, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete [] pvars ;
    }
    void Fire_CustomEvent(IDispatch *pItem, BSTR EventName, VARIANT newValue, long itemHandle, VARIANT userData)
    {
        VARIANTARG* pvars = new VARIANTARG[5];
        for (int i = 0; i < 5; i++)
            VariantInit(&pvars[i]);
       T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[4].vt = VT_DISPATCH | VT_BYREF ;
                pvars[4].ppdispVal = &pItem;

                pvars[3].vt = VT_BSTR ;
                pvars[3].bstrVal = EventName ;

                VariantCopy(pvars+2, &newValue) ;

                pvars[1].vt = VT_I4;
                pvars[1].lVal = itemHandle ;

                VariantCopy(pvars, &userData) ;
                DISPPARAMS disp = { pvars, NULL, 5, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x10, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete [] pvars ;
    }
    void Fire_ItemAddedOrDeletedWorkspace(IDispatch *pItem, long itemHandle, VARIANT userData, short evc)
    {
        long    dispcode = (evc==20 ? 0x11 : 0x12) ;  /* 20 = G2_WKSPCADD_EVENT*/
        VARIANTARG* pvars = new VARIANTARG[3];
        for (int i = 0; i < 3; i++)
            VariantInit(&pvars[i]);
       T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[2].vt = VT_DISPATCH | VT_BYREF ;
                pvars[2].ppdispVal = &pItem;
                pvars[1].vt = VT_I4;
                pvars[1].lVal = itemHandle ;
                VariantCopy(pvars, &userData) ;
                DISPPARAMS disp = { pvars, NULL, 3, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(dispcode, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete [] pvars ;
    }
    void Fire_ValueChg(IDispatch *pItem, VARIANT newValue, long itemHandle, VARIANT userData)
    {
        VARIANTARG* pvars = new VARIANTARG[4];
        for (int i = 0; i < 4; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[3].vt = VT_DISPATCH | VT_BYREF ;
                pvars[3].ppdispVal = &pItem;

                VariantInit(pvars+2);
                VariantCopy(pvars+2, &newValue) ;

                pvars[1].vt = VT_I4;
                pvars[1].lVal = itemHandle ;

                VariantInit(pvars);
                VariantCopy(pvars, &userData) ;
                DISPPARAMS disp = { pvars, NULL, 4, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x13, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
                VariantClear(pvars);
                VariantClear(pvars+2);
            }
            pp++;
        }
        pT->Unlock();
        delete [] pvars ;
    }

    void Fire_ItemSelected(IDispatch *pItem, long itemHandle, VARIANT userData)
    {
        VARIANTARG* pvars = new VARIANTARG[3];
        for (int i = 0; i < 3; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[2].vt = VT_DISPATCH | VT_BYREF ;
                pvars[2].ppdispVal = &pItem;

                pvars[1].vt = VT_I4;
                pvars[1].lVal = itemHandle ;

                VariantCopy(pvars, &userData) ;
                DISPPARAMS disp = { pvars, NULL, 3, 0 };
                IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
                pDispatch->Invoke(0x14, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
            }
            pp++;
        }
        pT->Unlock();
        delete [] pvars ;
    }
};

