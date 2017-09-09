#if !defined(_Subscription_h_)
#define _Subscription_h_

class G2OrbContained ;
class G2Item ;

class Subscription : public G2OrbContained
{
public:
    gsi_int             m_handle ;
    g2SubscriptionType  m_subscrType ;
    CComBSTR            m_attrName ;
    class CG2Item       *mp_Item ;
    virtual gsi_int GetHash(void) { return m_handle; } ;
    virtual TCHAR *GetKey(void) 
    {
        USES_CONVERSION;
        return OLE2T(m_attrName.m_str) ;
    }
    Subscription(gsi_int hv, g2SubscriptionType subtyp, BSTR tc , CG2Item *p) : 
            m_handle(hv), m_subscrType(subtyp), mp_Item(p)
    { 
        if (NULL == tc)
            m_attrName = "" ;
        else
            m_attrName = tc ;
    } 
} ;
#endif