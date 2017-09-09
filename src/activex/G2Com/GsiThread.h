// GsiThread.h: interface for the GsiThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSITHREAD_H__A503D2A3_417E_11D1_B155_00609703E682__INCLUDED_)
#define AFX_GSITHREAD_H__A503D2A3_417E_11D1_B155_00609703E682__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "G2Container.h"

struct IG2Gateway;

const long  NO_WAKEUP_PAUSE = 5 ;
const long  WAKEUP_PAUSE = 1000 ;

class GsiThread
{
private:
    long        mRefCount;
    int         mLocalPort;
    int         mListenSocket;
    int         mIn;
    int         mOut;
    sockaddr_in mAddrIn;
    int         mCount;
    char        mBuffer[100];
    long        mPauseTimeout ;
public:
    CRITICAL_SECTION    m_NoVanishingReqs ;
    G2OrbContainer      m_OrphanedReqs ;
    static long         sNumFds ;

    GsiThread();
    virtual     ~GsiThread();
    void        RunThread(void);
    void        start() ;
    void        addRef(void);
    void        delRef(void);
    void        postRelease(IG2Gateway *ptr);
    void        RequestTimeoutOrDelete(void);
    void        wakePauseUp() ;
    void        retrieveData() ;
    int         getWakeupFd() ;
    long        getPauseTimeout() ;
};

extern GsiThread *GsiThreadObj;
extern HINSTANCE hGlobalInstance;  // save window handle from dllMain
extern G2OrbContainer Queue ;


#endif // !defined(AFX_GSITHREAD_H__A503D2A3_417E_11D1_B155_00609703E682__INCLUDED_)
