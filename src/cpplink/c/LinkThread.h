
/*----------------------------------------------------------------------
CLASS
    LinkThread

KEYWORDS
    Link ActionQueue Action

AUTHOR
    Allan Scott
   
DESCRIPTION
    There is one LinkThread associated with the singleon Link object.

    The LinkThread is the single thread in which all of the GSI API
    calls are made in CppLink.

    The LinkThread is also the thread that receives al the callbacks
    from GSI.

    The LinkThread is responsible for performing all the actions on
    the ActionQueue by retrieving the next action from the queue and
    then calling the doAction() method on the action.

      
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_LINK_THREAD_H
#define _CPP_LINK_LINK_THREAD_H

#include "Thread.h"
#include "Link.h"
#include "ActionQueue.h"
#include "Tickle.h"

namespace CppLink
{

class LinkThread : public Thread
{  
 public:
  LinkThread();
  ~LinkThread();
  
  void init(Link *pContainer, 
            ActionQueue *pActionQueue);
  void run();
  void tickle();
  int getTickleFd();
  static int sNumFds;
 private:
  Link *mLink;
  ActionQueue *mActionQueue;
  bool mStopFlag;
  Tickle mTickle;
};

}

#endif // ifndef _CPP_LINK_LINK_THREAD_H