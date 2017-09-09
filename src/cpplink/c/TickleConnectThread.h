/*----------------------------------------------------------------------
CLASS
    TickleConnectThread

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

#ifndef _CPP_LINK_TICKLE_CONNECT_THREAD_H
#define _CPP_LINK_TICKLE_CONNECT_THREAD_H

#include "Thread.h"

namespace CppLink
{

class Tickle;
class TickleConnectThread : public Thread
{
public:
  TickleConnectThread();
  ~TickleConnectThread();
  void initialize(Tickle *pTickle);
  virtual void run();
private:
  Tickle *mTickle;
};

}

#endif // ifndef _CPP_LINK_TICKLE_CONNECT_THREAD_H