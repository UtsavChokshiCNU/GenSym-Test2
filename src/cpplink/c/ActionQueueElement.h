/*----------------------------------------------------------------------
CLASS
    ActionQueueElement

KEYWORDS
    ActionQueue

AUTHOR
    Allan Scott

DESCRIPTION  
	  The ActionQueueElement class is used to wrap an individual Action
    in the ActionQueue.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ACTION_QUEUE_ELEMENT_H
#define _CPP_LINK_ACTION_QUEUE_ELEMENT_H

#include "Action.h"

namespace CppLink
{

class ActionQueueElement
{
public:
  ActionQueueElement(); 
  ~ActionQueueElement();
  Action *mAction;
  ActionQueueElement *mNext;
  long mCount;
};

}

#endif // ifndef _CPP_LINK_ACTION_QUEUE_ELEMENT_H

