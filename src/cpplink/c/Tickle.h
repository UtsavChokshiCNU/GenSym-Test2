/*----------------------------------------------------------------------
CLASS
    Tickle

KEYWORDS
    ActionQueue

AUTHOR
    Judy Anderson Allan Scott

DESCRIPTION
	  Adapted from Java Link the Tickle feature causes GSI to watch 
    an additional file descriptor when determining when to wake up
    from a pause state.

LOG
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_TICKLE_H
#define _CPP_LINK_TICKLE_H

#include "TickleConnectThread.h"
#include "Mutex.h"

#ifdef WIN32
#include "windows.h"
#else
// POSIX case
#endif

namespace CppLink
{
class TickleConnectThread;

class Tickle
{
  public:
    Tickle();
    ~Tickle() {
    }
    int initialize();
    int finalize();
    int connectTickle();
    int tickle();
    void suckData();
    int getTickleFd();
  private:
    int mLocalPort;
    int mListenSocket;
    int mIn;
    int mOut;
    struct sockaddr_in mAddrIn;
    Mutex mMutex;
    int mCount;
    char mBuffer[100];
    TickleConnectThread mThread;
};
}

#endif // ifndef _CPP_LINK_TICKLE_H