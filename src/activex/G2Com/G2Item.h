
// G2Item.h : Declaration of the CG2Item

#ifndef __G2ITEM_H_
#define __G2ITEM_H_


#include "resource.h"       // main symbols
#include <vector>
#include "BRPCReq.h"
#include "Datum.h"
#include "GsiContext.h"


// Forward reference
class CG2Item ;
class G2ItemPtr ;


/////////////////////////////////////////////////////////////////////////////
// CG2Item
class ATL_NO_VTABLE CG2Item : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CG2Item, &CLSID_G2Item>,
    public ISupportErrorInfo,
    public IDispatchImpl<IG2Item4, &IID_IG2Item4, &LIBID_GensymAxl, 2, 0>
{
friend class CG2Workspace ;
friend class CG2Window ;
public:
    CG2Item() : m_g2syms(false), m_Port(0), m_Host(OLESTR(""))
    { 
        ATLTRACE2 (atrG2ObjLife, 4, "##> G2Item at %08x created.\n", this);
    }

    ~CG2Item()
    {
    }
    HRESULT CG2Item::FinalConstruct() ;
    void CG2Item::FinalRelease() ;

DECLARE_REGISTRY_RESOURCEID(IDR_G2ITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CG2Item)
    COM_INTERFACE_ENTRY(IG2Item4)
    COM_INTERFACE_ENTRY(IG2Item3)
    COM_INTERFACE_ENTRY(IG2Item2)
    COM_INTERFACE_ENTRY(IG2Item)
    COM_INTERFACE_ENTRY(G2ComObject)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CG2Item)
END_CONNECTION_POINT_MAP()

private:
    bool            m_g2syms ;
    Datum*          mp_Datum ;
    bool            m_linked ;
    CComBSTR        m_Host;
    int             m_Port;
    long            mp_ctx;
    unsigned short  m_compressedUUID[8] ;

    void            copyMassagedItem(Datum *pNewItem);
    bool            SameClass(IG2Item4 *pOther);
    std::vector< IDispatch* >   m_vecG2Attributes ;
    STDMETHOD(getAttrPtrWithLongIdx)(long idx, Attribute** ppAttr);
    STDMETHOD(getAttrPtrWithStrIdx)(BSTR BSTRidx, Attribute** ppAttr);
    STDMETHOD(InternalUnsubscribe)(VARIANT varFromWhat, int G2Required, int subset) ;
    STDMETHOD(UnsubscribeFromOneEvent)(long subHdl, g2SubscriptionType subType, bool tellG2) ;
    STDMETHOD(FindSubHdlsFor)(BSTR cbName, long **pHdlList, g2SubscriptionType **pTypList, long *lNrHdls) ;
    STDMETHOD(CommonSubscribe)(g2SubscriptionType subtyp, VARIANT userData, VARIANT *subHdl) ;
	STDMETHOD(InternalCall)(BRPCReq *req, long *pNrRetVars) ;
	STDMETHOD(InternalCall)(BRPCReq *req, VARIANT **ppRetVars, long *pNrRetVars) ;
    STDMETHOD(refreshWithDatum)(Datum *pNewDatum) ;
 
public:
	STDMETHOD(Unhandle)();
    int AutoConnect(long pCtx) ;
    G2ItemPtr       *mp_pG2Item ;
    G2OrbContainer  m_subscriptions ;
    STDMETHOD(InternalUnsubscribeAll)(bool tellG2) ;
    void UnlinkOnly();

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// G2ComObject
    STDMETHOD(get_WhatAmI)(/*[out]*/ BSTR *g2Type);
    STDMETHOD(Duplicate)(/*[out,retval]*/IUnknown** pNewObj);

// IG2Item
    STDMETHOD(get_ClassName)(/*[out,retval]*/ BSTR *pClassName) ;
    STDMETHOD(put_ClassName)(/*[in]*/ BSTR bstrClassName) ;
    STDMETHOD(get_Name)(/*[out,retval]*/ BSTR *pItemName) ;
    STDMETHOD(put_Name)(/*[in]*/ BSTR ItemName) ;
    STDMETHOD(get_Type)(/*[out,retval]*/ G2Type *pGsiType) ;
    STDMETHOD(put_Type)(/*[in]*/ G2Type GsiType) ;
    STDMETHOD(get_Value)(/*[out,retval]*/ VARIANT *pVal) ;
    STDMETHOD(put_Value)(/*[in]*/ VARIANT Val) ;
    STDMETHOD(get_Item)(/*[in]*/ VARIANT Idx, /*[out, retval]*/ VARIANT* pItem);
    STDMETHOD(put_Item)(/*[in]*/ VARIANT Idx, /*[in]*/ VARIANT value);
    STDMETHOD(get_Count)(/*[out,retval]*/ long *pVal) ;
    STDMETHOD(Add)(/*[in]*/ BSTR atName, /*[in]*/ VARIANT atVal) ;
    STDMETHOD(Remove)(/*[in]*/ VARIANT varIdx) ;
    STDMETHOD(get__NewEnum)(/*[out,retval]*/ LPUNKNOWN *pVal) ;
    STDMETHOD(get_AttrNames) (/*[out, retval]*/ SAFEARRAY **pNames);
    STDMETHOD(get_AttrValues)(/*[out, retval]*/ SAFEARRAY **pValues);
    STDMETHOD(get_AttrTypes) (/*[out, retval]*/ SAFEARRAY **pValues);
    STDMETHOD(Init)(/*[in]*/ long pItem) ;      // obsolete
    STDMETHOD(Git)(/*[out]*/ long *pGsiItem) ;  // obsolete
    STDMETHOD(Symbolize)(VARIANT idx, VARIANT_BOOL flgSym);

//IG2Item2
    STDMETHOD(Inix)(/*[in]*/ long pItem, /*[in]*/ IG2ItemRef *pRef) ;  // obsolete
    STDMETHOD(Update)();
    STDMETHOD(Refresh)();
    STDMETHOD(Delete)();
    STDMETHOD(Create)(/*[in]*/ LPDISPATCH pAxL);
    STDMETHOD(get_Linked)(/*[out, retva]*/ VARIANT_BOOL *pflgLinked);
    STDMETHOD(Link)(/*[in]*/ IG2ItemRef *pItemRef);
    STDMETHOD(Unlink)();
    STDMETHOD(get_Reference)(/*[out, retval]*/ IG2ItemRef **pVal);
    STDMETHOD(get_AttrType)(/*[in]*/ VARIANT idx, /*[out, retval]*/ G2Type *pVal);
    STDMETHOD(SubscribeToAttributeModification)(/*[in]*/ VARIANT AttrName, /*[in]*/ VARIANT tag, /*[out, retval]*/ VARIANT * SubscripHndls);
    STDMETHOD(SubscribeToDeletion)(/*[in]*/ VARIANT tag, /*[out, retval]*/ VARIANT * SubscripHndl);
    STDMETHOD(SubscribeToIconColorChange)(/*[in]*/ VARIANT tag, /*[out, retval]*/ VARIANT * SubscripHndls);
    STDMETHOD(SubscribeToCustomEvent)(/*[in]*/ BSTR EventName, /*[in]*/ VARIANT UserData,/*[out, retval]*/ VARIANT * SubscripHndl);
	STDMETHOD(SubscribeToValueChange)(/*[in]*/ VARIANT userData, /*[out]*/ VARIANT *subHndl);
    STDMETHOD(UnsubscribeFromAttributeModification)(/*[in]*/ VARIANT varToWhat);
	STDMETHOD(UnsubscribeFromDeletion)();
    STDMETHOD(UnsubscribeFromIconColorChange)() ;
	STDMETHOD(UnsubscribeFromCustomEvent)(/*[in]*/ VARIANT EventNames);
	STDMETHOD(UnsubscribeFromAll)();
	STDMETHOD(UnsubscribeFromValueChange)();
    STDMETHOD(Subscriptions)(/*[out,retval]*/ VARIANT *ArrayOfSubscriptions);

//IG2Item3
    STDMETHOD(get_Icon)(/*[in]*/ long bkgrCor, /*[out, retval]*/ LPDISPATCH *pVal);

//IG2Item4
    STDMETHOD(Init2)(/*[in]*/ long pDatum) ;
    STDMETHOD(Init3)(/*[in]*/ long pDatum, IG2ItemRef *pRef) ;
    STDMETHOD(Git2)(/*[out]*/ long *ppDatum) ;
};


class G2ItemPtr : public G2OrbContained
{
public:
    CG2Item     *mp_G2Item ;
    ~G2ItemPtr()
    {
        if (mp_G2Item)
            mp_G2Item->UnlinkOnly() ;
    }
};


#endif //__G2ITEM_H_
