// GatewayProp.h : Declaration of the CGatewayProp

#ifndef __GATEWAYPROP_H_
#define __GATEWAYPROP_H_

#include "resource.h"       // main symbols
#include "G2Com.h"            // definition of IGateway

EXTERN_C const CLSID CLSID_GatewayProp;

/////////////////////////////////////////////////////////////////////////////
// CGatewayProp
class ATL_NO_VTABLE CGatewayProp :
            public CComObjectRootEx<CComSingleThreadModel>,
            public CComCoClass<CGatewayProp, &CLSID_GatewayProp>,
            public IPropertyPageImpl<CGatewayProp>,
            public CDialogImpl<CGatewayProp>
{
public:
    CGatewayProp()
    {
        m_dwTitleID = IDS_TITLEGatewayProp;
        m_dwHelpFileID = IDS_HELPFILEGatewayProp;
        m_dwDocStringID = IDS_DOCSTRINGGatewayProp;
    }

    enum {IDD = IDD_GATEWAYPROP};


    DECLARE_REGISTRY_RESOURCEID(IDR_GATEWAYPROP)

    BEGIN_COM_MAP(CGatewayProp)
    COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
    END_COM_MAP()

    BEGIN_MSG_MAP(CGatewayProp)
    COMMAND_HANDLER(IDC_HOST, EN_CHANGE, OnHostChange)
    COMMAND_HANDLER(IDC_TIMEOUT, EN_CHANGE, OnHostChange)
    COMMAND_HANDLER(IDC_INTERFACECLASS, EN_CHANGE, OnHostChange)
    COMMAND_HANDLER(IDC_RPIS, EN_CHANGE, OnHostChange)
    COMMAND_HANDLER(IDC_G2SYMBOLS, BN_CLICKED, OnHostChange)
    COMMAND_HANDLER(IDC_DISCON_ON_RESET, BN_CLICKED, OnHostChange)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    CHAIN_MSG_MAP(IPropertyPageImpl<CGatewayProp>)
    END_MSG_MAP()

    STDMETHOD(Apply)(void);
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnHostChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
};

#endif //__GATEWAYPROP_H_
