// GsiWrapper.cpp: implementation of the GsiWrapper class.
//
// This class provides a object wrapper around GSI.  This GSI wrapper
// enforces thread locking so that only one thread may touch GSI
// routines at a time.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GsiWrapper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
// #define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


GsiWrapper::GsiWrapper()
{
    InitializeCriticalSection(&mAccessControlCritSection);
    count = 0;
}

GsiWrapper::~GsiWrapper()
{
    DeleteCriticalSection(&mAccessControlCritSection);
}
