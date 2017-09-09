/*----------------------------------------------------------------------
CLASS
   Link

KEYWORDS
   Action ActionQueue OptionsArray StartArgsArray

AUTHOR
   Allan Scott
   
DESCRIPTION
   The Link class is the main entry point into the
   CppLink library.

   The Link class is a singleton.  There will only
   ever be one instance of a Link object created in 
   any process at any time.

   Users retrieve the Link object by calling the getInstance()
   method.

   Users can configure the Link object by setting options using
   the setOptions() method.

   Users can configure how GSI is started up by setting the
   start arguments  using the setStartArgs() method.

   A Link can be started by calling the start() method.

   A running link may be stopped by calling the kill() method.

   Internally the Link object manages a queue of Actions to be
   peformed.  The Actions are stored in an ActionQueue object.

   Internally the Link object creates a LinkThread which is 
   responsible for making all GSI calls and performing all actions
   in that thread.
	
LINK STATUS
   The enumeration defines the different statuses that a Link
   can be in. These are:

   LINK_NEW - The Link object has been created but not started
   LINK_RUNNING - The Link object has been started and is running
   LINK_KILLED - The Link object was running but it has been killed


LAST MODIFIED
     
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_LINK_H
#define _CPP_LINK_LINK_H

#include "api.h"
#include "CppLink.h"
#include "ActionQueue.h"
#include "OptionsArray.h"
#include "StartArgsArray.h"

namespace CppLink 
{

  // forward reference
class LinkThread;
class LinkCallback;

enum API LinkStatus {
    LINK_NEW,
    LINK_RUNNING,
    LINK_KILLED
};

class API Link
{
 public:
  Link();
  ~Link();
  static Link *getInstance();
  void setPauseTimeout(int pPauseTimeout);
  int getPauseTimeout();
  void setTcpPort(int pTcpPort);
  int getTcpPort();
  void setOptions(OptionsArray* pOptions);
  OptionsArray *getOptions();
  void setStartArgs(StartArgsArray *pStartArgsArray);
  StartArgsArray *getStartArgs();
  void setLocalCallRPCName(char *pName);
  char *getLocalCallRPCName();
  void setLocalStartRPCName(char *pName);
  char *getLocalStartRPCName();
  LinkStatus getStatus();
  void start();
  void kill();
  void tickle();
  int getWatchFd();
  void setCallback(LinkCallback* pCallback);
  void queueAction(Action *pAction);
 private: 
  static Link* sInstance;
  static Mutex *sGlobalLinkLock;
  LinkThread *mThread;
  ActionQueue *mActionQueue;
  int mTcpPort;
  int mPauseTimeout;
  OptionsArray* mOptions;
  StartArgsArray* mStartArgs;
  volatile LinkStatus mStatus;
  LinkCallback *mCallback;
 
  char *mLocalCallRPCName;
  char *mLocalStartRPCName;
};


}


#endif // ifndef _CPP_LINK_LINK_H