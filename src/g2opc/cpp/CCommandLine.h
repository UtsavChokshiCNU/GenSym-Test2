#pragma once

class CCommandLine
{
public:
    CCommandLine(LPSTR lpCmdLine);
    ~CCommandLine(void);
    bool    Ready()   { return m_Ready ; }
    int     NrArgs()  { return m_nrArgs; }
    char    **argv()  { return m_Ready ? m_ppArg : NULL; }
    wchar_t *argW(int idx) ;
private:
    bool    m_Ready ;
    int     m_nrArgs;
    char**  m_ppArg;
};
