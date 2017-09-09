// ServerList.cpp : Implementation of CServerList
#include "stdafx.h"
#include "ServerList.h"

/////////////////////////////////////////////////////////////////////////////
// CServerList

bool    CServerList::m_opc1 ;
bool    CServerList::m_opc2 ;
bool    CServerList::m_opc3 ;

LRESULT CServerList::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        g_dlg_open = true ;
        CheckDlgButton(IDC_OPC1,m_opc1 ? BST_CHECKED:BST_UNCHECKED) ;
        CheckDlgButton(IDC_OPC2,m_opc2 ? BST_CHECKED:BST_UNCHECKED) ;
        CheckDlgButton(IDC_OPC3,m_opc3 ? BST_CHECKED:BST_UNCHECKED) ;
        return 1;  // Let the system set the focus
    }


/* ========================================================================== */
/* ========================================================================== */
LRESULT CServerList::OnFindServers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        CATID               catid[3] ;
        CLSID               ClsID;
        ICatInformation*    pICatInformation = NULL ;
        IEnumGUID*          pIEnumGUID = 0;
        HRESULT             hr ;
        HWND                hndl = GetDlgItem(IDC_SERVERS) ;
        int                 nrTypes = 0 ;
        LPOLESTR            lpClsIDString = NULL;
        LPOLESTR            progID = NULL ;
        ULONG               lFetched = 0 ;

        // Empty the list box
        // ------------------
        if (!hndl)
            return 0 ;
        SendMessage(hndl, LB_RESETCONTENT, 0, 0) ;

        // Determine which OPC types we should find
        // ----------------------------------------
        m_opc1 = (IsDlgButtonChecked(IDC_OPC1) == BST_CHECKED) ;
        m_opc2 = (IsDlgButtonChecked(IDC_OPC2) == BST_CHECKED) ;
        m_opc3 = (IsDlgButtonChecked(IDC_OPC3) == BST_CHECKED) ;

        if (m_opc1)
            catid[nrTypes++] = IID_CATID_OPCDAServer10 ;
        if (m_opc2) 
            catid[nrTypes++] = IID_CATID_OPCDAServer20 ;
        if (m_opc3) 
            catid[nrTypes++] = IID_CATID_OPCDAServer30 ;

        // Return if no types were requested
        // ---------------------------------
        if (!nrTypes)
        {
            bHandled = TRUE ;
            return 0 ;
        }

//      SendMessage(hndl, LB_ADDSTRING, 0, (LPARAM)L"To be implemented") ;

        // Get the enumerator of the servers
        // ---------------------------------
        hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,NULL, CLSCTX_INPROC_SERVER, IID_ICatInformation, (void**) &pICatInformation) ;
        if ( SUCCEEDED(hr) )
        {
            HRESULT hr = pICatInformation->EnumClassesOfCategories( nrTypes, catid, 0, 0, &pIEnumGUID ) ;
            if ( SUCCEEDED(hr) )
            {
                pIEnumGUID->Reset();           
                while ( S_OK == pIEnumGUID->Next( 1, &ClsID, &lFetched ) )
                {
                    if ( S_OK == StringFromIID( ClsID, &lpClsIDString ) )
                    {
                        ProgIDFromCLSID( ClsID, &progID );
                        SendMessage(hndl, LB_ADDSTRING, 0, (LPARAM)progID) ;
                        CoTaskMemFree( lpClsIDString );
//                      CoTaskMemFree( progID );
                    }
                }
                pIEnumGUID->Release() ;
            }
        }
        bHandled = TRUE ;          
        return 0;
    }

LRESULT CServerList::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        EndDialog(wID);
        g_dlg_open = false ;
        return 0;
    }
