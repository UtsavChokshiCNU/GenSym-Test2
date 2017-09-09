/*----------------------------------------------------------------------
CLASS
    ActionCallback

KEYWORDS
    Action

AUTHOR
    Allan Scott

DESCRIPTION
    Users implement the ActionCallback interface when they wish to
    be notified when an Action has either completed or failed.  For 
    this to work they must register an instance which implements this
    callback interface by calling the setCallback() method on the action
    they are interested in.

    In the case that an Action has failed the actionFailed() method
    is called and getErrorCode() and getErrorString() on the Action
    can be used to retrieve the cause of the error.

    In the case that an Action has completed successfully the user
    can retrieve additional data from the action, depending upon the
    specific action.   For example the Call Action has a getReturnValues()
    method that will return the ItemArray of return values from the Call.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ACTION_CALLBACK_H
#define _CPP_LINK_ACTION_CALLBACK_H

#include "api.h"

namespace CppLink
{

class Action;
class Connect;
class Disconnect;
class Start;
class Call;
class ReturnValues;

class API ActionCallback
{  
 public:
  virtual void actionCompleted(Action& pAction) = 0;
  virtual void actionFailed(Action& pAction) = 0;
};


/*----------------------------------------------------------------------
CLASS
    BaseActionHandler

KEYWORDS

AUTHOR
   
DESCRIPTION
  
LAST MODIFIED
    
----------------------------------------------------------------------*/
class API BaseActionHandler: public ActionCallback
{
  public:
    BaseActionHandler();
    ~BaseActionHandler();
    virtual void actionCompleted(Action& pAction);
    virtual void actionFailed(Action& pAction);
    virtual void actionFailed(Connect& pAction);
    virtual void actionFailed(Disconnect& pAction);
    virtual void actionFailed(Start& pAction);
    virtual void actionFailed(Call& pAction);
    virtual void actionFailed(ReturnValues& pAction);
};

}

#endif // ifndef _CPP_LINK_ACTION_CALLBACK_H
