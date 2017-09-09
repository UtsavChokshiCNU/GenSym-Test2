#pragma once

class ProgramVersion
{
public:
    ProgramVersion(void);
    ~ProgramVersion(void);
    // Has Version Info Been Successfully Attached?
    bool Ready(void);
    HRESULT GetVersion(UINT &MajorVer, UINT &MinorVer, UINT &TypeCode, UINT &RevNum);
    HRESULT GetBuildCode(TCHAR* pBuildCode, UINT kBufferSize);
private:
    bool                m_booHaveInfo;
    LPTSTR              m_lpVI ; // pointer to Version Info
    WORD*               m_pLangInfo ;
};
