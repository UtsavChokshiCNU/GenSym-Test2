// CtrlPanel.cpp : Implementation of CCtrlPanel
#include "stdafx.h"
#include "CtrlPanel.h"

/////////////////////////////////////////////////////////////////////////////
// CCtrlPanel

long CCtrlPanel::radioButtons[] = {IDC_TL0, IDC_TL1, IDC_TL2, IDC_TL3, IDC_TL4} ;

LRESULT CCtrlPanel::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
        g_dlg_open = true ;

        //CheckRadioButton(IDC_TL0, IDC_TL4, 3) ;
        if (g_traceLevel >= TL_FATAL_ONLY && g_traceLevel <= TL_INFO)
            CheckDlgButton(radioButtons[g_traceLevel], BST_CHECKED) ;

        // Initialize the controls
        // -----------------------
        CheckDlgButton(IDC_LOG_TO_G2,       g_logToG2?BST_CHECKED:BST_UNCHECKED) ;
        CheckDlgButton(IDC_LOG_TO_SCREEN,   g_logToStdout?BST_CHECKED:BST_UNCHECKED) ;
        CheckDlgButton(IDC_ARCHIVE_LOG,     g_archvLastLog?BST_CHECKED:BST_UNCHECKED) ;
        CheckDlgButton(IDC_LOGGING_ENABLED, g_traceOn?BST_CHECKED:BST_UNCHECKED) ;
        CheckDlgButton(IDC_CHK_SRVR_STAT,   g_chkServerStatus?BST_CHECKED:BST_UNCHECKED) ;
        CheckDlgButton(IDC_USE_G2_TIMESTAMP,g_useG2TimeStamp?BST_CHECKED:BST_UNCHECKED) ;


        // Set the current quality filter setting
        // --------------------------------------
        wchar_t qf[4] ;

        qf[0] = g_lev1_good      ? (unsigned short)'1' : (unsigned short)'0' ;
        qf[1] = g_lev1_bad       ? (unsigned short)'1' : (unsigned short)'0' ;
        qf[2] = g_lev1_uncertain ? (unsigned short)'1' : (unsigned short)'0' ;
        qf[3] = 0 ;
        SetDlgItemText(IDC_QUALITY_FILTER, qf) ;

        if (g_srvrCheckFreq <= 0)
            g_srvrCheckFreq = 15 ;
        SetDlgItemInt(IDC_SRVR_CHK_FREQ,g_srvrCheckFreq, FALSE) ;


		return 1;  // Let the system set the focus
	}

#define UPDATE_PANEL_BOOL_VALUE(id,place,section,key) \
  { \
    bool new_bool = (IsDlgButtonChecked(id) == BST_CHECKED); \
    if (new_bool != place) { \
      place = new_bool; \
      OpcUtils::UpdateBooleanToIniFile(INI_FILE,section,key,place); \
    } \
  }
#define UPDATE_PANEL_INT_VALUE(value,place,section,key) \
  { \
    int new_int = value; \
    if (new_int != place) { \
      place = new_int; \
      OpcUtils::UpdateIntToIniFile(INI_FILE,section,key,place); \
    } \
  }
  
LRESULT CCtrlPanel::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    BOOL    okFlag ;
    BSTR    bstrQF = NULL ;
    bool    l_lev1_good      = g_lev1_good ;
    bool    l_lev1_bad       = g_lev1_bad ;
    bool    l_lev1_uncertain = g_lev1_uncertain ;
    bool    errFlg           = false ;
    int     traceLevel = 0 ;
    long    lngX, offset ;
    LPWSTR  errMsg = NULL ;
    UINT    chked, chkFreq ;



    // Determine the Trace Level
    // -------------------------
    for (int i = 0 ; i < 5 ; i++)
        if ((chked=IsDlgButtonChecked(radioButtons[i])) == BST_CHECKED)
        {
            traceLevel = i ;
            break ;
        }

    // Get & Validate the Quality Filter
    // ---------------------------------
    chkFreq = GetDlgItemInt(IDC_SRVR_CHK_FREQ, &okFlag, FALSE) ;
    if (!okFlag || chkFreq == 0)
    {
        errFlg = true ;
        errMsg = L"Invalid Server Status Check Frequency" ;
        MessageBox(errMsg, L"Validation Error") ;
        return 1 ;
    }

    GetDlgItemText(IDC_QUALITY_FILTER, bstrQF) ;
    lngX = SysStringLen(bstrQF) ;
    if (lngX > 3)
        errFlg = true ;
    else
    {
        offset = 3 - lngX ;
        for (int i = 0 ; i < lngX ; i++)
            if (bstrQF[i] != (unsigned short)'0' && bstrQF[i] != (unsigned short)'1')
            {
                errFlg = true ;
                break ;
            }
        if (!errFlg)
        {
            if (lngX==3)
                l_lev1_good = (bstrQF[0] == (unsigned short)'1') ;
            if (lngX >= 2)
                l_lev1_bad = (bstrQF[1-offset] == (unsigned short)'1') ;
            if (lngX >= 1)
                l_lev1_uncertain = (bstrQF[2-offset] == (unsigned short)'1') ;
        }
    }
    if (errFlg)
    {
        MessageBox(L"Invalid Quality Filter", L"Validation Error") ;
        return 1 ;
    }

    // If everything is OK, update the global flags & values
    // -----------------------------------------------------
    if (!errFlg)
    {
        UPDATE_PANEL_BOOL_VALUE(IDC_LOG_TO_G2,g_logToG2,INI_SEC_LOG,INI_LOG_TO_G2);
        UPDATE_PANEL_BOOL_VALUE(IDC_LOG_TO_SCREEN,g_logToStdout,INI_SEC_LOG,INI_LOG_TO_SCREEN);
        UPDATE_PANEL_BOOL_VALUE(IDC_ARCHIVE_LOG,g_archvLastLog,INI_SEC_LOG,INI_LOG_ARCHIVE_LAST);

        g_lev1_good      = l_lev1_good ;
        g_lev1_bad       = l_lev1_bad ;
        g_lev1_uncertain = l_lev1_uncertain ;
        UPDATE_PANEL_INT_VALUE(g_lev1_good*100 + g_lev1_bad*10 + g_lev1_uncertain,
                               g_defaultQualityFilter,INI_SEC_QUALITY,INI_QUALITY_FILTER);
        UPDATE_PANEL_BOOL_VALUE(IDC_LOGGING_ENABLED,g_traceOn,INI_SEC_LOG,INI_LOG_SWITCH);
        UPDATE_PANEL_BOOL_VALUE(IDC_CHK_SRVR_STAT,g_chkServerStatus,
                                INI_SEC_SERVERSTATUS, INI_SERVERSTATUS_CHECKSTATUS);
        UPDATE_PANEL_BOOL_VALUE(IDC_USE_G2_TIMESTAMP,g_useG2TimeStamp,
                                INI_SEC_SERVERSTATUS,INI_SERVERSTATUS_USEG2TIMESTAMP);
        UPDATE_PANEL_INT_VALUE(traceLevel, g_traceLevel,INI_SEC_LOG,INI_LOG_LEVEL);
        UPDATE_PANEL_INT_VALUE(chkFreq, g_srvrCheckFreq,INI_SEC_SERVERSTATUS,INI_SERVERSTATUS_CHECKFREQUENCY);

        EndDialog(wID);
        g_dlg_open = false ;
    }
	return 0;
}