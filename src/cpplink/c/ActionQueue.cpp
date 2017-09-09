#include "ActionQueue.h"
#include "Synchronize.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  ActionQueue constructor
	//
ActionQueue::ActionQueue():
    mFirst(NULL),
    mLast(NULL)
{
  mMutex = new Mutex();
}

  ///////////////////////////////////////////
  //
	//  ActionQueue destructor
	//
ActionQueue::~ActionQueue()
{
    Synchronize sync = Synchronize(mMutex);
    // Iterate over all remaining actions and then work on 
    // removing them all.
    
    mFirst = NULL;
    mLast = NULL;

    delete mMutex;
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
  //
	//  queue
	//
void ActionQueue::queue(Action *pAction)
{
    Synchronize sync = Synchronize(mMutex);
    
    // Need to check for a maximum queue count here - to make sure
    // we do not go over a maximum queue size.
    
    ActionQueueElement *element = new ActionQueueElement();
    element->mNext = NULL;
    element->mAction = pAction;
    // The queue is currently empty
    if (mLast == NULL) {
        mLast = element;
        mFirst = element;
    }
    // Put on the end of the queue
    else { 
        mLast->mNext = element;
        mLast = element; 
    }
    
    pAction->setStatus(ACTION_QUEUED);
}

  ///////////////////////////////////////////
  //
	//  dequeue
	//
Action *ActionQueue::dequeue()
{
    Synchronize sync = Synchronize(mMutex);
    Action *result;
    ActionQueueElement *temp;
    
    if (mFirst == NULL) {
        return NULL;
    }

    temp = mFirst;
    mFirst = temp->mNext;

    result = temp->mAction;
    temp->mAction = NULL;
    if (temp == mLast) {
      mLast = NULL;
    }

    delete temp;
    
    return result;
}

}