/*----------------------------------------------------------------------
CLASS
    Action

KEYWORDS
   ConnectionAction Connection Connect Disconnect Start Call ReturnValues
   Link RPCAction

AUTHOR
   Allan Scott

DESCRIPTION
  Actions are used in CppLink to represent all the GSI activities
  that CppLink supports.

  The Connect action is used to connect to G2.

  ConnectionActions are those actions that belong to a specific Connection

  Disconnect is a ConnectionAction which will disconnect a connection.

  ReturnValues is a ConnectionAction which is used to return values to
  G2 from an incoming remote procedure call.  

  RPCAction is a kind of a ConnectionAction that is used for performing
  remote procedure calls.

  Start is an RPCAction which will perform a remote procedure call
  start over a Connection.

  Call is an RPCAction which will peform a remote procedure call
  over a Connection.

  Actions are queued in the singleton Link object.  The success or failure
  of the action is communicated through the ActionCallback interface. The
  setCallback() method on Action is used to register an instance which
  implements the ActionCallback interface.

  Users that do no wish to work with Actions directly may use the Session
  clas which manages the creation and queueing of the Action objects 
  directly.


ACTION STATUSES
  The possible statuses of an action are defined by the 
  ActionStatusFlag enumeration.

  ACTION_CREATED - the action has been created but not queued 
  ACTION_QUEUED - the action is currently queued for execution
  ACTION_RUNNING - the action is currently executing
  ACTION_COMPLETE - the action has completed successfully
  ACTION_FAILED - a failure took place when executing the action

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_ACTION_H
#define _CPP_LINK_ACTION_H

#include "api.h"
#include "ActionCallback.h"
#include "Mutex.h"

namespace CppLink 
{

enum API ActionStatusFlag {
  ACTION_CREATED,
  ACTION_QUEUED,
  ACTION_RUNNING,    
  ACTION_COMPLETE,
  ACTION_FAILED
};  

class API Action
{
 friend class LinkThread;

 public:
  Action();
  virtual ~Action();
  void setCallback(ActionCallback *pCallback);
  ActionCallback *getCallback();
  ActionStatusFlag getStatus();
  void setStatus(ActionStatusFlag pStatus);
  char *getErrorString();
  void setErrorString(char *pErrorString);
  int getErrorCode();
  void setErrorCode(int pErrorCode);
  virtual void doAction() {}
  void waitFor();
  void notify();

  void setDeleteAfterCallback(bool pDeleteAfterCallback);
  bool getDeleteAfterCallback();
  void setTimeout(long pTimeout);
  long getTimeout();
 
 protected:
    volatile ActionStatusFlag mStatus;
    char *mErrorString;
    volatile int mErrorCode;
    ActionCallback *mCallback;    
    static char *copyErrorString(const char * const pError);
    bool mDeleteAfterCallback;
    long mTimeout;
};


#ifndef NULL
#define NULL 0
#endif // ifndef NULL

}


#endif // ifndef _CPP_LINK_ACTION_H