

#include "stdafx.h"
#include "g2string.h"
#include <string.h>
#include <ctype.h>


// String routines

const G2String& G2String::operator=(const G2String& RHS) // Assignment

{
    if (str)
        delete str;  // free up old memory
    if (RHS.str)
    {
        str = new TCHAR[_tcslen(RHS.str)+1];
        _tcscpy(str, RHS.str);
    }
    else
        str = NULL;
    return *this;
}
const G2String& G2String::operator=(const TCHAR *RHS)

{
    if (str)
        delete str;
    if (RHS)
    {
        str = new TCHAR[_tcslen(RHS)+1];
        _tcscpy(str, RHS);
    }
    else
        str = NULL;
    return *this;
}

void G2String::toupper(void)
{

    TCHAR *ptr;

    for (ptr = str; *ptr; ptr++)
    {
        if (_istlower(*ptr))
            *ptr = ::_totupper(*ptr);
    }
}

// A case-insensitive check for equality of BSTRs //
// ---------------------------------------------- //
bool G2String::bstrGleich(BSTR bstr1, BSTR bstr2)
{
    unsigned long   len  = ::SysStringLen(bstr1);
    unsigned long   len2 = ::SysStringLen(bstr2) ;

    if (len2 != len)
        return false ;

#if defined(_WIN32) && !defined(OLE2ANSI)
    return (!wcsnicmp(bstr1, bstr2, len));
#else
    return (!stricmp(bstr1, bstr2)) ;
#endif
}

G2String::G2String(const TCHAR *ptr)

{
    str = new TCHAR[_tcslen(ptr)+1];
    _tcscpy(str,ptr);
}

G2String::G2String(const G2String& RHS)

{
    str = new TCHAR[_tcslen(RHS.str)+1];
    _tcscpy(str, RHS.str);
}



//
// These are routines that work binary sequences
//

const G2OctSeq& G2OctSeq::operator=(const G2OctSeq& RHS) // Assignment

{
    if (buf)
        delete buf;  // free up old memory
    buf_len = RHS.buf_len;
    buf = new char[buf_len];
    memcpy(buf,RHS.buf,buf_len);
    return *this;
}

G2OctSeq::~G2OctSeq()
{
    if (buf)
        delete buf;
}

void G2OctSeq::set_buf(void *ptr, int len)
{
    if (buf)
        delete buf;
    buf = new unsigned char[len];
    memcpy(buf, ptr, len);
    buf_len = len;
}

G2OctSeq::G2OctSeq()
{
    buf_len = 0;
    buf = NULL;
}



