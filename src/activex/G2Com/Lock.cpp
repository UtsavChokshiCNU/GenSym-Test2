// Lock.cpp: 
//
// In earlier versions of ActiveXLink, this routine used was called
// GsiWrapper.  It included extraneous information for logging its
// behavior due to the difficulty of preventing multiple threads from
// accessing GSI simultaneously.
// 
// Now that only one thread may access GSI, this routine was rewritten
// to simplify it.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lock.h"

// Implementation of the methods of Lock.
// --------------------------------------
Lock::Lock()
{
    InitializeCriticalSection(&m_CriticalSection);
}

Lock::~Lock()
{
    DeleteCriticalSection(&m_CriticalSection);
}

void Lock::enter()
{
    EnterCriticalSection(&m_CriticalSection);
    ATLTRACE2 (atrLockHistory, 4, "%% Locked: %08x.\n", GetCurrentThreadId()) ;
}

void Lock::leave()
{
    LeaveCriticalSection(&m_CriticalSection);
    ATLTRACE2 (atrLockHistory, 4, "%% Unlocked: %08x.\n", GetCurrentThreadId()) ;
}



// The Gatekeeper will only let you pass if the Lock
// is open.  Otherwise you wait. Passing locks it.
// -------------------------------------------------
Gatekeeper::Gatekeeper(Lock* pLock)
{
      m_pLock = pLock ;
      m_pLock->enter() ;
}


// The lock is opened by destroying the Gatekeeper
// -----------------------------------------------
Gatekeeper::~Gatekeeper()
{
    if (m_pLock)
        m_pLock->leave() ;
}


// This method lets you unlock a thread before
// finishing the method that contains the Gatekeeper
// -------------------------------------------------
void Gatekeeper::unLock()
{
    if (m_pLock)
    {
        m_pLock->leave() ;
        m_pLock = NULL ;
    }
}

