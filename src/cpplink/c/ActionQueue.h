/*----------------------------------------------------------------------
CLASS
    ActionQueue

KEYWORDS
    Action LinkThread Link

AUTHOR
    Allan Scott

DESCRIPTION 
    A queue of actions to be performed by CppLink.
    
    Currently there is a single action queue that is associated
    with the singleton Link object.

    The Link object queues actions on the ActionQueue.

    The LinkThread is responsible for getting the next action
    to run from the ActionQueue and performing it.

    The ActionQueue is currently a simple FIFO queue.

    There are no timeouts implemented yet for actions in theA
    ActionQueue.  This is expected in future versions.

LAST MODIFIED

    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ACTION_QUEUE_H
#define _CPP_LINK_ACTION_QUEUE_H

#include "Action.h"
#include "ActionQueueElement.h"
#include "Mutex.h"


namespace CppLink
{

class ActionQueue
{
 public:
  ActionQueue();
  ~ActionQueue();
  void queue(Action *pAction);
  Action *dequeue();
  bool hasActions();
  void clear();

 private:
  ActionQueueElement *mFirst;
  ActionQueueElement *mLast;
  Mutex *mMutex;

  // FIND ME.  Need to implement timeout behavior
  // for actions in the queue.
};


}
#endif // ifndef _CPP_LINK_ACTION_CALLBACK_H