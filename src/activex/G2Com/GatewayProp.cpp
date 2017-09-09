// GatewayProp.cpp : Implementation of CGatewayProp
#include "stdafx.h"
#include "GatewayProp.h"
#include <atlstr.h>

/////////////////////////////////////////////////////////////////////////////
// CGatewayProp


HRESULT CGatewayProp::Apply(void)
{
    CComBSTR        sHost;
    CComBSTR        sInterfaceClass;
    CComBSTR        sRPIS;
    CSimpleString   sSimple(&g_strmgr);
    LONG            lCallTimeout;
    int             iG2Syms ;
    int             iDiscOnReset ;

    
    USES_CONVERSION;
    if (m_bDirty == FALSE)
        return S_OK;
    ATLTRACE2(atrAxlMethodCalls,3,_T("CGatewayProp::Apply\n"));
    for (UINT i = 0; i < m_nObjects; i++)
    {
        CComQIPtr<IG2Gateway4, &IID_IG2Gateway4> pGateway(m_ppUnk[i]);
#if _MSC_VER == 1200 //VC++6.0
        GetDlgItemText(IDC_HOST, (unsigned short *&) sHost);
#elif _MSC_VER >=1300  //VC++7.O OR MORE
        GetDlgItemText(IDC_HOST, sSimple);
#endif
        sHost = sSimple.GetBuffer();
        if FAILED(pGateway->put_G2Location(sHost))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        lCallTimeout = (long) GetDlgItemInt(IDC_TIMEOUT);
        if FAILED(pGateway->put_CallTimeout(lCallTimeout))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
#if _MSC_VER == 1200  //VC++6.0
        GetDlgItemText(IDC_INTERFACECLASS, (unsigned short *&) sInterfaceClass);
#elif _MSC_VER >= 1300  //VC++7.0 OR MORE
        GetDlgItemText(IDC_INTERFACECLASS, sSimple);
#endif
        sInterfaceClass = sSimple.GetBuffer();
        if FAILED(pGateway->put_InterfaceClass(sInterfaceClass))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
#if _MSC_VER == 1200  //VC++6.0
        GetDlgItemText(IDC_RPIS, (unsigned short *&) sRPIS);
#elif _MSC_VER >= 1300  //VC++7.0 OR MORE
        GetDlgItemText(IDC_RPIS, sSimple);
#endif
        sRPIS = sSimple.GetBuffer();
        if FAILED(pGateway->put_RemoteInitializationString(sRPIS))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        iG2Syms = (int)SendMessage(GetDlgItem(IDC_G2SYMBOLS), BM_GETCHECK, 0, 0) ;
        if FAILED(pGateway->put_G2Symbols(iG2Syms ? VARIANT_TRUE : VARIANT_FALSE))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        iDiscOnReset = (int)SendMessage(GetDlgItem(IDC_DISCON_ON_RESET), BM_GETCHECK, 0, 0) ;
        if FAILED(pGateway->put_DisconnectOnReset(iDiscOnReset ? VARIANT_TRUE : VARIANT_FALSE))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        //    UpdateWindow();
    }
    SetDirty(FALSE);
    return S_OK;
}

LRESULT CGatewayProp:: OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    CComBSTR        sHost;
    CComBSTR        sInterfaceClass;
    CComBSTR        sRPIS;
    LONG            lCallTimeout;
    VARIANT_BOOL    MyBool;
    VARIANT_BOOL    vbG2Syms ;
    VARIANT_BOOL    vbDiscOnReset ;

    USES_CONVERSION;
    ATLTRACE2(atrAxlMethodCalls,3,_T("CGatewayProp::OnInitDialog\n"));
    for (UINT i = 0; i < m_nObjects; i++)
    {
        CComQIPtr<IG2Gateway4, &IID_IG2Gateway4> pGateway(m_ppUnk[i]);
        if FAILED(pGateway->get_G2Location(&sHost))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        if FAILED(pGateway->get_CallTimeout(&lCallTimeout))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        if FAILED(pGateway->get_InterfaceClass(&sInterfaceClass))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        if FAILED(pGateway->get_RemoteInitializationString(&sRPIS))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        if FAILED(pGateway->get_G2Symbols(&vbG2Syms))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        if FAILED(pGateway->get_DisconnectOnReset(&vbDiscOnReset))
        {
            CComPtr<IErrorInfo> pError;
            CComBSTR            strError;
            GetErrorInfo(0, &pError);
            pError->GetDescription(&strError);
            MessageBox(OLE2T(strError), _T("Property Page Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }

        SetDlgItemText(IDC_HOST, OLE2T(sHost));
        SetDlgItemInt(IDC_TIMEOUT, (UINT) lCallTimeout);
        SetDlgItemText(IDC_INTERFACECLASS, OLE2T(sInterfaceClass));
        SetDlgItemText(IDC_RPIS, OLE2T(sRPIS));
        SendMessage(GetDlgItem(IDC_G2SYMBOLS), BM_SETCHECK, 
                            (VARIANT_FALSE == vbG2Syms) ? 0 : -1, 0) ;
        SendMessage(GetDlgItem(IDC_DISCON_ON_RESET), BM_SETCHECK, 
                            (VARIANT_FALSE == vbDiscOnReset) ? 0 : -1, 0) ;

        // Set Connection Established status in dialog box.
        pGateway->get_IsG2Connected(&MyBool);

        if (MyBool)
            SetDlgItemText(IDC_G2CONNECT, _T("Yes") );
        else
            SetDlgItemText(IDC_G2CONNECT, _T("No") );

        // Set G2 KB Start status field in dialog box.
        pGateway->get_IsG2Running(&MyBool);

        if (MyBool)
            SetDlgItemText(IDC_KBSTART, _T("Yes") );
        else
            SetDlgItemText(IDC_KBSTART, _T("No") );

    }
    SetDirty(FALSE);
    return 1;
}

LRESULT CGatewayProp::OnHostChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
    SetDirty(TRUE);
    return 0;
}
