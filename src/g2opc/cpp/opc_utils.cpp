#include "stdafx.h"
#include <wchar.h>


// ========================================================================== //
//                                                                            //
//             Return a textual description of the Variant Type.              //
//            Client is responsible for freeing the returned BSTR.            //
//                                                                            //
// ========================================================================== //
BSTR OpcUtils::ConvertVariantTypeToText(VARTYPE vtin)
{
    wchar_t buffer[80] ; // large enough to hold largest possible string
    struct lups {   VARTYPE vt ;
                    LPWSTR  desc ;} lup_tab[] = { { VT_EMPTY, L"VT_EMPTY" },
                                                  { VT_NULL, L"VT_NULL" },
                                                  { VT_I2, L"VT_I2" },
                                                  { VT_I4, L"VT_I4" },
                                                  { VT_R4, L"VT_R4" },
                                                  { VT_R8, L"VT_R8" },
                                                  { VT_CY, L"VT_CY" },
                                                  { VT_DATE, L"VT_DATE" },
                                                  { VT_BSTR, L"VT_BSTR" },
                                                  { VT_DISPATCH, L"VT_DISPATCH" },
                                                  { VT_ERROR, L"VT_ERROR" },
                                                  { VT_BOOL, L"VT_BOOL" },
                                                  { VT_VARIANT, L"VT_VARIANT" },
                                                  { VT_UNKNOWN, L"VT_UNKNOWN" },
                                                  { VT_DECIMAL, L"VT_DECIMAL" },
                                                  { VT_I1, L"VT_I1" },
                                                  { VT_UI1, L"VT_UI1" },
                                                  { VT_UI2, L"VT_UI2" },
                                                  { VT_UI4, L"VT_UI4" },
                                                  { VT_I8, L"VT_I8" },
                                                  { VT_UI8, L"VT_UI8" },
                                                  { VT_INT, L"VT_INT" },
                                                  { VT_UINT, L"VT_UINT" },
                                                  { VT_VOID, L"VT_VOID" },
                                                  { VT_HRESULT, L"VT_HRESULT" },
                                                  { VT_PTR, L"VT_PTR" },
                                                  { VT_SAFEARRAY, L"VT_SAFEARRAY" },
                                                  { VT_CARRAY, L"VT_CARRAY" },
                                                  { VT_USERDEFINED, L"VT_USERDEFINED" },
                                                  { VT_LPSTR, L"VT_LPSTR" },
                                                  { VT_LPWSTR, L"VT_LPWSTR" },
                                                  { VT_RECORD, L"VT_RECORD" },
                                                  { VT_FILETIME, L"VT_FILETIME" },
                                                  { VT_BLOB, L"VT_BLOB" },
                                                  { VT_STREAM, L"VT_STREAM" },
                                                  { VT_STORAGE, L"VT_STORAGE" },
                                                  { VT_STREAMED_OBJECT, L"VT_STREAMED_OBJECT" },
                                                  { VT_STORED_OBJECT, L"VT_STORED_OBJECT" },
                                                  { VT_BLOB_OBJECT, L"VT_BLOB_OBJECT" },
                                                  { VT_CF, L"VT_CF" },
                                                  { VT_CLSID, L"VT_CLSID" } } ;

    const int nr_var_types = sizeof(lup_tab)/sizeof(lups) ;
    bool    append_flag = false ;

    if (vtin & VT_RESERVED)
    {
        wcscpy(buffer, L"VT_RESERVED") ;
        append_flag = true ;
    }
    if (vtin & VT_BYREF)
    {
        if (append_flag)
            wcscat(buffer, L" | VT_BYREF") ;
        else
            wcscpy(buffer, L"VT_BYREF") ;
        append_flag = true ;
    }
    if (vtin & VT_ARRAY)
    {
        if (append_flag)
            wcscat(buffer, L" | VT_ARRAY") ;
        else
            wcscpy(buffer, L"VT_ARRAY") ;
        append_flag = true ;
    }
    if (vtin & VT_VECTOR)
    {
        if (append_flag)
            wcscat(buffer, L" | VT_VECTOR") ;
        else
            wcscpy(buffer, L"VT_VECTOR") ;
        append_flag = true ;
    }
    
    VARTYPE core = vtin & VT_TYPEMASK ;
    for (int i = 0 ; i < nr_var_types ; i++)
    {
        if (core == lup_tab[i].vt)
        {
            if (append_flag)
            {
                wcscat(buffer, L" | ");
                wcscat(buffer, lup_tab[i].desc) ;
            }
            else
                wcscpy(buffer, lup_tab[i].desc) ;
            break ;
        }
    }
    if (i == nr_var_types)
        if (append_flag)
            wcscat(buffer, L" | UNKNOWN");
        else
            wcscpy(buffer, L"UNKNOWN") ;
        
    return SysAllocString(buffer) ;
}


// ========================================================================== //
//                                                                            //
//                Return the value of the Variant as a string.                //
//            Client is responsible for freeing the returned BSTR.            //
//                                                                            //
// ========================================================================== //
BSTR OpcUtils::CStr(VARIANT vx)
{
    BSTR        retval = NULL ;

    SYSTEMTIME  st ;
    wchar_t buffer[64] ;

    switch (vx.vt)
    {
    case VT_I2:     wsprintf(buffer, L"%d",vx.iVal) ;
                    break ;
    case VT_I4:     wsprintf(buffer, L"%ld", vx.lVal) ;
                    break ;
    case VT_R4:     swprintf(buffer, L"%g", (double)vx.fltVal) ;
                    break ;
    case VT_R8:     swprintf(buffer, L"%g", vx.dblVal) ;
                    break ;
    case VT_BSTR:   retval = SysAllocString(vx.bstrVal) ;
                    return retval ;
    case VT_DATE:   if (VariantTimeToSystemTime(vx.date, &st))
                    {
                        wsprintf(buffer,L"%02d.%02d.%02d %02d:%02d:%02d",st.wMonth,st.wDay,st.wYear,st.wHour,st.wMinute,st.wSecond) ;
                    }
                    else
                        wcscpy(buffer, L"* date conversion failed *") ;
                    break ;
    default:        wcscpy(buffer, L"* unsupported type *") ;
                    break ;
    }
    retval = SysAllocString(buffer) ;
    return retval ;
}


// Note: Client is responsible for freeing array of pointers to arguments
// -----------------------------------------------------------------------------
HRESULT OpcUtils::WinCmdLineToC(LPSTR lpCmdLine, char ***pppArg, int *pNrArgs)
{
    char        *p = lpCmdLine ;
    char        **ppc ;
    HRESULT     hr = E_FAIL ;
    int         nrArgs = 0 ;
    int         sz = 0 ;

    *pppArg = NULL ;
    *pNrArgs = 0 ;
    if (!lpCmdLine)
        return E_POINTER ;

    // First count the number of arguments
    // -----------------------------------
    while (*p)
    {
        // Scan ahead to first non-space character
        // ---------------------------------------
        while (*p == ' ')
            p++ ;
        if (*p==0)
            break ;

        // Count this argument & move to the end of it
        // -------------------------------------------
        nrArgs++ ;

        if (*p == '"')
        {
            while (*++p != '"')
                if (!*p)
                    break ;
            if (*p == '"')
                p++ ;
            continue ;
        }

        while(*++p != ' ')
            if (!*p)
                break ;
    }

    // Now allocate an array of pointers to strings
    // --------------------------------------------
    if (nrArgs)
        ppc = new char*[nrArgs] ;
    if (!nrArgs || !ppc)
    {
        *pNrArgs = 0 ;
        *pppArg = NULL ;
        return nrArgs ? S_OK : E_OUTOFMEMORY ;
    }




    *pNrArgs = nrArgs ;


    return hr ;
}

void OpcUtils::GetWindowsErrorMsg(TCHAR *lpBuffer, int nBufferSize) {
  DWORD dwLastError = GetLastError();
  ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
                  MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
                  lpBuffer, nBufferSize-1, NULL);
}

/* ========================================================================== */
/*                                                                            */
/*      Configure this program based on the settings in "configfile.ini"      */
/*                                                                            */
/* ========================================================================== */
HRESULT OpcUtils::InitializeFromIniFile(LPWSTR szIniFileName)
{
    LPWSTR logFileName = NULL;
	struct keyInfo	{	LPWSTR	keyName ;
						VARTYPE	keyType ;
						void*	ptrGlobal ; } ;
	keyInfo	logKeys[]	= {	{ INI_LOG_FILENAME,    VT_BSTR, &logFileName },
							{ INI_LOG_FILE_MAX_SIZE, VT_I4,   &g_logFileMaxSize },
							{ INI_LOG_LEVEL,       VT_I2,   &g_traceLevel },
							{ INI_LOG_SWITCH,        VT_BOOL, &g_traceOn },
							{ INI_LOG_TO_G2,        VT_BOOL, &g_logToG2 },
							{ INI_LOG_ARCHIVE_LAST, VT_BOOL, &g_archvLastLog },
							{ INI_LOG_TO_SCREEN,    VT_BOOL, &g_logToStdout} } ;
	keyInfo qltyKeys[]  = { { INI_QUALITY_FILTER,  VT_I2,   &g_defaultQualityFilter} } ;
	keyInfo srvStKeys[] = { { INI_SERVERSTATUS_CHECKSTATUS,    VT_BOOL, &g_chkServerStatus},
							{ INI_SERVERSTATUS_CHECKFREQUENCY, VT_I4,   &g_srvrCheckFreq},
							{ INI_SERVERSTATUS_USEG2TIMESTAMP, VT_BOOL, &g_useG2TimeStamp},
							{ INI_SERVERSTATUS_INITSECURITY,   VT_BOOL, &g_initSecurity} } ;


	struct secKeyMap {	LPWSTR	sectionName ;
						short	nrKeys ;
						keyInfo	*keyInfoList ; } ;
	secKeyMap sectionTable[] = 				
						 {  {INI_SEC_LOG,   sizeof(logKeys)/sizeof(keyInfo),   logKeys },
							{INI_SEC_QUALITY,      sizeof(qltyKeys)/sizeof(keyInfo),  qltyKeys },
							{INI_SEC_SERVERSTATUS, sizeof(srvStKeys)/sizeof(keyInfo), srvStKeys} } ;
	const int nrSections = sizeof(sectionTable)/sizeof(secKeyMap) ;
    const long bufferSize = 256 ;
    wchar_t buffer[bufferSize], buffer2[bufferSize] ;

    // Build Qualifed Name of Ini File
    // -------------------------------
    long        iniFileNameSize = wcslen(szIniFileName) ;
    DWORD       pathLen = GetModuleFileName(NULL,buffer,bufferSize) ;
    if (pathLen)
    {
        wchar_t *p = buffer + --pathLen ;
        while (p >= buffer && *p != '\\')
            p-- ;
        if (p - buffer + iniFileNameSize + 1 < bufferSize)
            wcscpy(++p, szIniFileName) ;
        else
        {
            log_message(TL_ERRORS, L"* Qualified path to ini file overflows buffer.",-1) ;
            return E_FAIL ;
        }
    }   
    else if (bufferSize > iniFileNameSize)
        wcscpy(buffer, szIniFileName) ;
    else
    {
        log_message(TL_ERRORS, L"* Internal error: size of ini file name is greater than buffer size.", -1) ;
        return E_FAIL ;
    }

    // See if Ini File exists and if we can read it
    // --------------------------------------------
	DWORD nrChars = GetPrivateProfileSectionNames(buffer2, bufferSize, buffer) ;
	if (nrChars)
	{
        int qfin = g_defaultQualityFilter ;
		for (int secNr = 0 ; secNr < nrSections ; secNr++)
		{
			secKeyMap*	ptrSecEntry = sectionTable + secNr ;
			for (int keyNr = 0 ; keyNr < ptrSecEntry->nrKeys ; keyNr++)
			{
                keyInfo*    ptrKeyEntry = ptrSecEntry->keyInfoList + keyNr ;
				switch(ptrKeyEntry->keyType)
				{
				case VT_I2:
                case VT_I4:
                                {
                                    long n = GetPrivateProfileInt(ptrSecEntry->sectionName, ptrKeyEntry->keyName,
                                                     *(long*)ptrKeyEntry->ptrGlobal, buffer) ;
                                    if (ptrKeyEntry->keyType == VT_I2)
                                        *(short*)ptrKeyEntry->ptrGlobal = (short)n ;
                                    else
                                        *(int*)ptrKeyEntry->ptrGlobal = (int)n ;
                                    break ;
                                }

                case VT_BOOL:   GetPrivateProfileString(ptrSecEntry->sectionName, ptrKeyEntry->keyName, 
                                            (*(bool*)ptrKeyEntry->ptrGlobal)==true? L"TRUE" : L"FALSE",
                                            buffer2, bufferSize, buffer) ;
                                *(bool*)ptrKeyEntry->ptrGlobal = (buffer2[0] == 't' || buffer2[0] == 'T') ;
                                break ;

                case VT_BSTR:   {   bool newStr = false ;

                                    GetPrivateProfileString(ptrSecEntry->sectionName, ptrKeyEntry->keyName, 
                                            *(wchar_t**)ptrKeyEntry->ptrGlobal==NULL? L"" : (wchar_t*)ptrKeyEntry->ptrGlobal,
                                            buffer2, bufferSize, buffer) ;
                                    if (*((wchar_t*)ptrKeyEntry->ptrGlobal))
                                    {
                                        if (wcscmp(*(wchar_t**)ptrKeyEntry->ptrGlobal,buffer2))
                                        {
                                            delete [] *(wchar_t**)ptrKeyEntry->ptrGlobal ;
                                            newStr = true ;
                                        }
                                    }
                                    else
                                        newStr = true ;
                                    if (newStr)
                                    {
                                        *(wchar_t**)ptrKeyEntry->ptrGlobal = new wchar_t [wcslen(buffer2)+1] ;
                                        wcscpy(*(wchar_t**)ptrKeyEntry->ptrGlobal,buffer2) ;
                                    }
                                    break ;
                                }
                default:        log_message(TL_ERRORS, L"* Internal error: unknown ini file key type.",-1) ;
				}
			}
        }

        // Validate the settings
        // ---------------------
        if ((nullptr == logFileName) || (logFileName && (0 == wcscmp(logFileName, L"")))) {
            g_logToFile = false ;
	}
	else {
	    SetLogFileName(logFileName);
	}

        if (g_logFileMaxSize < 1024)
            g_logFileMaxSize = 1024 ;
        if (g_traceLevel < 0 || g_traceLevel > 4)
            g_traceLevel = 3 ;


        if (qfin != g_defaultQualityFilter)
        {
            int quo ;

            g_lev1_uncertain = g_defaultQualityFilter % 10 ? true : false ;
            quo = g_defaultQualityFilter / 10 ;
            g_lev1_bad = quo % 10 ? true : false ;
            quo = quo / 10 ;
            g_lev1_good = quo % 10 ? true : false ;
        }
	}
	else
		log_message(TL_WARNINGS,L"Unable to initialize from ini file",-1) ;
	return S_OK ;
}
BOOL OpcUtils::UpdateBooleanToIniFile(LPCTSTR szIniFileName,LPCTSTR sectionName,LPCTSTR name, bool value)
{
  TCHAR szDir[MAX_PATH],szPath[MAX_PATH];
  GetModuleFileName(NULL,szDir,MAX_PATH);
  PathRemoveFileSpec(szDir); 
  _stprintf(szPath,_T("%s\\%s"),szDir,szIniFileName);
  BOOL result = WritePrivateProfileString(sectionName,name,value?L"TRUE":L"FALSE",szPath);
  if (!result) {
    time_t      ltime;
    struct  tm  *ts;
    TCHAR szErr[MAX_PATH];
    GetWindowsErrorMsg(szErr,MAX_PATH);
    time(&ltime) ;
    ts = localtime(&ltime);
    _tprintf(_T("[%4d-%02d-%02d %02d:%02d:%02d] Failed to write %s to file %s: %s\n"),
             ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec,
             name,szIniFileName, szErr);
  }
  return result;
}

BOOL OpcUtils::UpdateIntToIniFile(LPCTSTR szIniFileName,LPCTSTR sectionName,LPCTSTR name, int value)
{
  TCHAR szDir[MAX_PATH],szPath[MAX_PATH];
  TCHAR szBuf[100];
  GetModuleFileName(NULL,szDir,MAX_PATH);
  PathRemoveFileSpec(szDir); 
  _stprintf(szPath,_T("%s\\%s"),szDir,szIniFileName);

  wsprintf(szBuf,_T("%d"),value);

  BOOL result = WritePrivateProfileString(sectionName,name,szBuf,szPath);
  if (!result) {
    time_t      ltime;
    struct  tm  *ts;
    TCHAR szErr[MAX_PATH];
    GetWindowsErrorMsg(szErr,MAX_PATH);
    time(&ltime) ;
    ts = localtime(&ltime);
    _tprintf(_T("[%4d-%02d-%02d %02d:%02d:%02d] Failed to write %s to file %s: %s\n"),
             ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec,
             name,szIniFileName, szErr);
  }
  return result;
}


/* ========================================================================== */
/*                                                                            */
/*   We just shutdown a context.  Manage the copy of its OPC Server pointer   */
/*   in the Server pointer table.                                             */
/*                                                                            */
/* ========================================================================== */
void OpcUtils::ServerReleased(CLSID clsid)
{
    int     iX, nr_servers ;
    CServer *pCServer ;
    CGroup  *pGrp ;
    

    for (iX=0, nr_servers=0, pCServer=g_servers ; 
            nr_servers < g_nr_servers && iX < MAX_GDB_CONTEXTS ; iX++,pCServer++)
        if (pCServer->m_pOPCServer)  // does this slot contain an active server?
        {
            nr_servers++ ;
            if (clsid == pCServer->m_clsid)
            {
                // If this was the last one, release the pointers,
                // (except for the one to the shutdown object)
                // and mark the CServer as unused.
                // ---------------------------------------------
                if (--g_servers[iX].m_nr_ctxs_using == 0)
                {
                    CServer *p = &g_servers[iX] ;
                   
                    memset(&p->m_clsid,0,sizeof(CLSID)) ;

                    while (pGrp = p->m_pGroups)
                    {
                        p->m_pGroups = p->m_pGroups->mp_Next ;
                        delete pGrp ;
                    }
                       
                    long dbg=p->m_pOPCServer->Release() ;
                    if (!dbg)
                        p->m_pOPCServer = NULL ;            
                    g_nr_servers-- ;
                }
                break ;
            }
        }
}


/* ========================================================================== */
/*                                                                            */
/*           Translate an OPC quality code to a Gensym quality code           */
/*                                                                            */
/* ========================================================================== */
long OpcUtils::OPCq2G2q(long OPCq)
{
    long    qtype = OPCq & OPC_QUALITY_MASK ;
    long    qstat = OPCq & OPC_STATUS_MASK ;

    struct lup { long opcq ;
                 long g2q ; };
                 lup lupt[] = { {OPC_QUALITY_GOOD,                      OPC_GOOD_NONSPEC},
                                {OPC_QUALITY_BAD,                       OPC_BAD_NONSPEC},
                                {OPC_QUALITY_UNCERTAIN,                 OPC_UNC_NONSPEC},
                                {OPC_QUALITY_CONFIG_ERROR,              OPC_BAD_CONFIG_ERROR },
                                {OPC_QUALITY_NOT_CONNECTED,             OPC_BAD_NOT_CONNECTED},
                                {OPC_QUALITY_DEVICE_FAILURE,            OPC_BAD_DEVICE_FAILURE},
                                {OPC_QUALITY_SENSOR_FAILURE,            OPC_BAD_SENSOR_FAILURE},
                                {OPC_QUALITY_LAST_KNOWN,                OPC_BAD_LAST_KNOWN_VAL},
                                {OPC_QUALITY_COMM_FAILURE,              OPC_BAD_COMM_FAILURE},
                                {OPC_QUALITY_OUT_OF_SERVICE,            OPC_BAD_OUT_OF_SERVICE},
                                {OPC_QUALITY_WAITING_FOR_INITIAL_DATA,  OPC_BAD_NOT_INITIALIZED},
                                {OPC_QUALITY_LAST_USABLE,               OPC_UNC_LAST_USABLE_VAL},
                                {OPC_QUALITY_SENSOR_CAL,                OPC_UNC_SENSOR_NOT_ACCUR},
                                {OPC_QUALITY_EGU_EXCEEDED,              OPC_UNC_EGU_EXCEEDED},
                                {OPC_QUALITY_SUB_NORMAL,                OPC_UNC_SUB_NORMAL},
                                {OPC_QUALITY_LOCAL_OVERRIDE,            OPC_GOOD_LOCAL_OVERRIDE} };
const int nrPredefinedQualities = sizeof(lupt)/sizeof lup ;
    
    for (int i = 0 ; i < nrPredefinedQualities ; i++)
        if (qstat == lupt[i].opcq)
            return lupt[i].g2q ;
    if (qtype == OPC_QUALITY_GOOD)
        return OPC_GOOD_INVALID_QUALITY ;
    if (qtype == OPC_QUALITY_UNCERTAIN)
        return OPC_UNC_INVALID_QUALITY ;
    if (qtype == OPC_QUALITY_BAD)
        return OPC_BAD_INVALID_QUALITY ;
    return OPC_INVALID_QUALITY ;
}



/* ========================================================================== */
/*                                                                            */
/*                  Determine whether specified quality code                  */
/*                    passes this context's quality filter                    */
/*                                                                            */
/* ========================================================================== */
bool OpcUtils::QualityPasses(long quality_code, gsi_int ctx_nr)
{
    if (quality_code == 0 || quality_code == 404 || quality_code == 405)
        return true ;
    if (quality_code < 300 || quality_code == 333 || quality_code == 444 || quality_code >= 555)
        return false ;
    if (quality_code == 506)
        return g_lev1_good ;
    if (quality_code >= 300 && quality_code <= 308)
        return g_lev1_bad ;
    if (quality_code == 400 || quality_code == 404 || quality_code == 405)
        return g_lev1_uncertain ;
    return false ;
}


/* ========================================================================== */
/*                                                                            */
/*   Determine the VARIANT type that should be returned by the OPC Server     */
/*       given the type of the GSI variable that will hold the result.        */
/*                                                                            */
/* ========================================================================== */
VARTYPE OpcUtils::GsiType2VT(gsi_int GsiType)
{
    switch(GsiType)
    {
        case GSI_NULL_TAG:      return VT_NULL ;

        case GSI_INTEGER_TAG :  return VT_I4 ;

        case GSI_FLOAT64_TAG:   return VT_R8 ;

        case GSI_LOGICAL_TAG:   return VT_BOOL ;

        case GSI_STRING_TAG:    
        case GSI_SYMBOL_TAG:    return VT_BSTR ;
    }
    return VT_EMPTY ;
}


/* ========================================================================== */
/*                                                                            */
/*      Add the client and server handles for an item to the context's        */
/*                            table of items.                                 */
/*                                                                            */
/* ========================================================================== */
HRESULT OpcUtils::AddItemHdl2Ctx(OPCHANDLE hdlC, OPCHANDLE hdlS, gsi_int ctx_nr) 
{
    bool            found ;
    context_info    *pCtx = &context[ctx_nr] ;
    HRESULT         hr = S_OK ;
    item_values_ptr *pOld, *pNew ;
    long            lngNewSize, lngOldByteSize ;
    long            lngNewLoc, lngNr2Move ;

    EnterCriticalSection(&crtsec_items) ;
    while(1)  // provides easy way to jump out of block
    {
        if (pCtx->nrItems >= pCtx->table_size)
        {
            if (pCtx->table_size == 0)
            {
                pCtx->pItemTable = new item_values_ptr[starting_table_size] ;
                if (pCtx->pItemTable == NULL)
                {
                    hr = E_OUTOFMEMORY ;
                    break ;
                }
                pCtx->table_size = starting_table_size ;
                pCtx->pItemTable[0].hItem = hdlC ;
                pCtx->pItemTable[0].hItemS = hdlS ;
                pCtx->pItemTable[0].pVals = NULL ;
                pCtx->nrItems++ ;
                break ;
            }
            pOld = pCtx->pItemTable ;
            lngNewSize = pCtx->table_size << 1 ;
            pNew = new item_values_ptr[lngNewSize] ;
            if (pNew == NULL)
            {
                hr = E_OUTOFMEMORY ;
                break ;
            }
            lngOldByteSize = pCtx->table_size * sizeof(item_values_ptr) ;
            memcpy(pNew, pOld, lngOldByteSize) ;
            memset(pNew+pCtx->table_size, 0, lngOldByteSize) ;
            pCtx->pItemTable = pNew ;
            pCtx->table_size = lngNewSize ;
            delete [] pOld ;
        }
        lngNewLoc = FindItemHdl(hdlC, ctx_nr, &found) ;
        if (found)
        {
            hr = E_FAIL ;
            break ;
        }
        lngNr2Move = pCtx->nrItems - lngNewLoc ;
        if (lngNr2Move)
            memmove(pCtx->pItemTable+lngNewLoc+1, pCtx->pItemTable+lngNewLoc, lngNr2Move * sizeof(item_values_ptr)) ;
        pCtx->pItemTable[lngNewLoc].hItem = hdlC ;
        pCtx->pItemTable[lngNewLoc].hItemS= hdlS ;
        pCtx->pItemTable[lngNewLoc].pVals = NULL ;
        pCtx->nrItems++ ;
        break ;
    }
    LeaveCriticalSection(&crtsec_items) ;
    return S_OK ;
}

/* ========================================================================== */
/*                                                                            */
/*   Look for the specified client handle in the context's table of items.    */
/*   If found, set "found" to true and return its location in the table.      */
/*   If not found, set "found" to false and return the location where it      */
/*   should be inserted to keep the table in order.                           */
/*                                                                            */
/* ========================================================================== */
long OpcUtils::FindItemHdl(OPCHANDLE hdl, gsi_int ctx_nr, bool *found)
{
    context_info    *pCtx = &context[ctx_nr] ;
    long            lngRetLoc ;
    OPCHANDLE       hndlX ;

    *found = false ;
    if (pCtx->table_size == 0)
        return -1 ;

    // This probably should be rewritten as a binary chop
    // --------------------------------------------------
    EnterCriticalSection(&crtsec_items) ;
    for (lngRetLoc=0 ; lngRetLoc < pCtx->nrItems ; lngRetLoc++)
    {
        hndlX = pCtx->pItemTable[lngRetLoc].hItem ;
        if (hndlX == hdl)
            *found = TRUE ;
        if (hndlX >= hdl)
            break ;
    }
    LeaveCriticalSection(&crtsec_items) ;
    return lngRetLoc ;
}


/* ========================================================================== */
/*                                                                            */
/* This function takes a win32 FILETIME structures, returns the equivalent    */
/* time_t value.                                                              */
/*                                                                            */
/* NOTE: a 32-bit time_t is only capable of representing dates between        */
/* 13 December 1901 and 19 January 2038. This function will calculate the     */
/* number of seconds (positive or negative) since the Unix epoch, however if  */
/* this value is outside of the range of 32-bit numbers, the result will be   */
/* truncated on systems with a 32-bit time_t.                                 */
/*                                                                            */
/* ========================================================================== */
time_t OpcUtils::FileTimeToUnixTime(FILETIME FileTime)
{
    static const __int64 SECS_BETWEEN_EPOCHS = 11644473600;
    static const __int64 SECS_TO_100NS = 10000000; /* 10^7 */

    __int64 UnixTime;

    /* get the full win32 value, in 100ns */
    UnixTime = ((__int64)FileTime.dwHighDateTime << 32) + FileTime.dwLowDateTime;

    /* convert to the Unix epoch */
    UnixTime -= (SECS_BETWEEN_EPOCHS * SECS_TO_100NS);
    UnixTime /= SECS_TO_100NS; /* now convert to seconds */

    if ( (time_t)UnixTime != UnixTime )
    {
     // WARN("Resulting value is too big for a time_t value\n");
     // *** TO DO:  Log error
    }

    /* printf("Win32 FILETIME = [%#x:%#x] converts to Unix time = [%ld.%09ld]\n", 
       FileTime.dwHighDateTime, FileTime.dwLowDateTime ,(long) UnixTime,
       nsec?*nsec:0L); */

    return (time_t)UnixTime;
}
