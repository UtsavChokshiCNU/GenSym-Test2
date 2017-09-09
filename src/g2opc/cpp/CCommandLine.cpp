#include "stdafx.h"

CCommandLine::CCommandLine(LPSTR lpCmdLine): m_Ready(false), m_nrArgs(0), 
                                             m_ppArg(NULL)
{
    char        *p = lpCmdLine,
                *p2 ;
    int         nrArgs = 0 ;
    int         sz = 0 ;

    if (!lpCmdLine) return ;

    // ***** First count the number of arguments *****
    // -----------------------------------------------
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

        // Count anything within quotation marks as a single argument
        // ----------------------------------------------------------
        if (*p == '"')
        {
            while (*++p != '"')
                if (!*p)
                    break ;
            if (*p == '"')
                p++ ;
            continue ;
        }

        // Move to the end of this argument (not in quotation marks)
        // ---------------------------------------------------------
        while(*++p != ' ')
            if (!*p)
                break ;
    }

    //    ***** Allocate an array of pointers to strings *****
    // We need to allocate an extra slot for a dummy program name.
    // -----------------------------------------------------------
    m_ppArg = new char*[++nrArgs] ;
    if (m_ppArg)
    {
        memset(m_ppArg, 0, sizeof(char*)*nrArgs);
        int i = 1 ;
        m_ppArg[0] = new char[2] ;
        if (m_ppArg[0])
#ifdef VS2005
            strcpy_s(m_ppArg[0],2,"X") ;
#else
            strcpy(m_ppArg[0],"X") ;
#endif
        else
            nrArgs = i = 0 ;

        for (; i < nrArgs ; i++)
            m_ppArg[i] = NULL ;
    }
    if (!nrArgs || !m_ppArg)
    {
        m_nrArgs = 0 ;
        if (m_ppArg[0]){
            delete [] m_ppArg[0];
            m_ppArg[0] = NULL;
        }
        delete [] m_ppArg;
        m_ppArg = NULL ;
        return ;
    }

    // ***** Scan the command line again.  Make a copy of each argument. *****
    // -----------------------------------------------------------------------
    int idx = 0 ;

    p = lpCmdLine ;
    while (*p)
    {
        // Scan ahead to first non-space character
        // ---------------------------------------
        while (*p == ' ')
            p++ ;
        if (*p==0)
            break ;

        idx++ ;

        // Count anything within quotation marks as a single argument
        // ----------------------------------------------------------
        if (*p == '"')
        {
            sz = 0 ;
            p2 = ++p ;
            while (*p != '"')
                if (!*p++)
                {
                    p-- ;
                    break ;
                }
                else
                    sz++ ;
            if (*p == '"')
                p++ ;
            m_ppArg[idx] = new char[sz+1] ;
            if (m_ppArg[idx])
            {
#ifdef VS2005
                strncpy_s(m_ppArg[idx],sz+1,p2,sz) ;
#else
                strncpy(m_ppArg[idx],p2,sz) ;
#endif
                m_ppArg[idx][sz] = '\0' ;
                continue ;
            }
            else
                return ;
        }

        // Move to the end of this argument (not in quotation marks)
        // ---------------------------------------------------------
        sz = 1 ;
        p2 = p ;
        while(*++p != ' ')
            if (!*p)
                break ;
            else
                sz++ ;
            m_ppArg[idx] = new char[sz+1] ;
            if (m_ppArg[idx])
            {
#ifdef VS2005
                strncpy_s(m_ppArg[idx],sz+1,p2,sz) ;
#else
                strncpy(m_ppArg[idx],p2, sz) ;
#endif
                m_ppArg[idx][sz] = '\0' ;
                continue ;
            }
            else
                return ;
    }


    m_nrArgs = nrArgs ;
    m_Ready = true ;
    return  ;

}

CCommandLine::~CCommandLine(void)
{
    if (m_ppArg)
    {
        for (int i = 0 ; i < m_nrArgs ; i++)
            if (m_ppArg[i])
            {
                delete [] m_ppArg[i];
                m_ppArg[i] = NULL ;
            }
        delete [] m_ppArg ;
    }
}

// The Client is Responsible for Deleting the Returned String
// ----------------------------------------------------------
wchar_t* CCommandLine::argW(int idx)
{
    size_t  sz ;
    wchar_t *retVal ;

    if (idx >= m_nrArgs || m_ppArg[idx]==NULL)
        return NULL ;
    sz = strlen(m_ppArg[idx]) ;
    retVal = new wchar_t[sz+1] ;
#ifdef VS2005
    mbstowcs_s(&sz2, retVal, sz+1, m_ppArg[idx], sz) ;
#else
    mbstowcs(retVal, m_ppArg[idx], sz) ;
#endif 
    retVal[sz] = 0 ;
    return retVal ;
}

    
