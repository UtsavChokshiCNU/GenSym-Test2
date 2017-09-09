// GsiWrapper.h: interface for the GsiWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSIWRAPPER_H__BFB70ACE_3FF2_11D1_B155_00609703E682__INCLUDED_)
#define AFX_GSIWRAPPER_H__BFB70ACE_3FF2_11D1_B155_00609703E682__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define GSI_USE_USER_DATA_FOR_RPC_CALLS
#define GSI_USE_DLL
#include "gsi_main_cpp.h"
#include "g2container.h"


typedef gsi_item GsiItem;
typedef gsi_item GsiAttr;


//
// This is a wrapper around gsi to make sure that it is thread safe
// There is one critical section that is shared by the object.
//
// This critical section guards the object model of the entire project.  Only one thread at a time
// may access the data model.  We obtain a lock by creating a LockObj.  This lock is automaticly released
// when it is destructed.
//
// Since gsi is only called from within one of our locks, it is also protected, along with our object model.
//

class GsiWrapper
{
public:
    GsiWrapper();
    virtual ~GsiWrapper();

    // Lock and unlock are inlined for speed
    inline void Lock(const char *Id)
    {
#ifdef _DEBUG
        ATLTRACE2(atrLockHistory,4,">> CS: %04X: RQST> \"%s\" requests lock.\n", GetCurrentThreadId(), Id);
#endif

        EnterCriticalSection(&mAccessControlCritSection);

#ifdef _DEBUG

        static long ThreadOwner = 0;

        long newId = GetCurrentThreadId();
        if (newId != ThreadOwner)
        {
            ATLTRACE2(atrLockHistory,4,">> CS: %04X: TAKE> \"%s\" took lock (Prior=%04x).\n", newId, Id, ThreadOwner);
            count = 1;
            ThreadOwner = newId;
        }
        else
        {
            ATLTRACE2(atrLockHistory,4,">> CS: %04X: =++=> %s.  Lock count changed to %ld.\n", newId, Id, ++count);
        }
#endif
    };
    inline void Unlock(const char *Id)
    {
        // The following line is necessary because when the callback function
        // gsi_run_state_change is first installed, it will result in one or more
        // calls to Unlock for which there never was a corresponding call to Lock.
        // If the OwningThread value is 0, the lock has already been released.
        // ----------------------------------------------------------------------
        if (mAccessControlCritSection.OwningThread == 0)
            return ;
#ifdef _DEBUG

        count-- ;
        ATLTRACE2(atrLockHistory,4,">> CS: %04X: %s> \"%s\" Count:%d\n", GetCurrentThreadId(), (!count ? "0REL" : "=--="), Id, count);
#endif

        LeaveCriticalSection(&mAccessControlCritSection);
    };


private:
    CRITICAL_SECTION mAccessControlCritSection;
    long count;
};

extern GsiWrapper GsiObj;
//
// This is a lock object, the constructor obtains a lock on gsi, the destructor frees it.  This simplfies the lock/unlock
// code with a object wrapper that isures that the lock will be released.  There is also a Lock() method
// that allows the lock to be released prior to the destructor call.

class LockObj
{
    unsigned char isLocked;
    const char *mId;
public:
    inline LockObj(const char *Id)
    {
        mId = Id;
        GsiObj.Lock(mId);
        isLocked = 1;
    }
    inline LockObj()
    {
        mId = "Default label";
        GsiObj.Lock(mId);
        isLocked = 1;
    }
    inline ~LockObj()
    {
        while (isLocked)
        {
            GsiObj.Unlock(mId);
            isLocked--;
        }
    }
    inline void Lock(void)
    {
        GsiObj.Lock(mId);
        isLocked++;
    }
    inline void Unlock(void)
    {
        GsiObj.Unlock(mId);
        isLocked--;
    }
};


#endif // !defined(AFX_GSIWRAPPER_H__BFB70ACE_3FF2_11D1_B155_00609703E682__INCLUDED_)
