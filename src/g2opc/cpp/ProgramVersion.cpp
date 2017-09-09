#include "stdafx.h"
#include "ProgramVersion.h"

// Constructor: Attach the Resources Version Information
// =====================================================
ProgramVersion::ProgramVersion(void)
                 : m_booHaveInfo(false), m_lpVI(NULL), m_pLangInfo(NULL)
{
    const int           MAX_FN_LEN = 500 ;
    DWORD               dwX, dwZ ;
    UINT                uiX ;
    TCHAR               progName[MAX_FN_LEN] ;

    // Determine the program name
    // --------------------------
    dwX = GetModuleFileName(NULL,progName,MAX_FN_LEN-1) ;
    if (!dwX || dwX >= MAX_FN_LEN-1)
        return ;
    progName[dwX] = _T('\0') ;

    // Get the size of the version info area
    // -------------------------------------
    dwX = GetFileVersionInfoSize(progName, &dwZ);
    if (!dwX)
        return ;

    // Allocate a buffer for the version info area
    // -------------------------------------------
    m_lpVI = (LPTSTR)calloc(dwX,1) ;
    if (!m_lpVI)
        return ;

    // Get the version info
    // --------------------
    if (!GetFileVersionInfo(progName,NULL,dwX,m_lpVI))
    {
        free(m_lpVI) ;
        m_lpVI = NULL ;
    }
    else
        m_booHaveInfo = true ;

    // Store away a pointer to the language info
    // -----------------------------------------
    VerQueryValue(m_lpVI, _T("\\VarFileInfo\\Translation"),
                            (LPVOID*)&m_pLangInfo, &uiX);
}

// Destructor: Free the Allocated Memory
// =====================================
ProgramVersion::~ProgramVersion(void)
{
    // Release the version info buffer memory
    // --------------------------------------
    if (m_booHaveInfo)
        free(m_lpVI) ;
}

// Has Version Info Been Successfully Attached?
// ============================================
bool ProgramVersion::Ready(void)
{
    return m_booHaveInfo;
}

// Return the Program Version as 4 Numbers
HRESULT ProgramVersion::GetVersion(UINT &MajorVer, UINT &MinorVer, UINT &TypeCode, UINT &RevNum)
{
    DWORD               dwX ;
    VS_FIXEDFILEINFO    *ffi;

    if (m_booHaveInfo && VerQueryValue(m_lpVI,_T("\\"), (LPVOID*)&ffi, (UINT *) &dwX))
    {
        MajorVer = HIWORD(ffi->dwFileVersionMS);
        MinorVer = LOWORD(ffi->dwFileVersionMS) ;
        TypeCode = HIWORD(ffi->dwFileVersionLS),
        RevNum   = LOWORD(ffi->dwFileVersionLS);
        return S_OK ;
    }
    return E_FAIL;
}


// Copy the Build Code into the User-Supplied Buffer
// -------------------------------------------------
HRESULT ProgramVersion::GetBuildCode(TCHAR* pBuildCode, UINT kBufferSize)
{
    UINT    uiX ;
    LPVOID  lpt;
    TCHAR   tszVerStrName[64];

    if (!m_booHaveInfo || !m_pLangInfo)
        return E_FAIL ;
    wsprintf(tszVerStrName, _T("\\StringFileInfo\\%04x%04x\\%s"),
                 m_pLangInfo[0], m_pLangInfo[1], _T("Build ID"));
    if (VerQueryValue(m_lpVI, tszVerStrName, &lpt, &uiX) && (uiX <= kBufferSize))
    {
#ifdef VS2005
        _tcscpy_s(pBuildCode,uiX,(TCHAR*)lpt) ;
#else
        _tcscpy(pBuildCode,(TCHAR*)lpt) ;
#endif
        return S_OK ;
    }
    return E_FAIL;
}
