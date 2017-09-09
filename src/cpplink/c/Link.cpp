#include "Link.h"
#include "LinkThread.h"
#include "Synchronize.h"

namespace CppLink
{
/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Link constructor
	//
Link::Link() :
  mStartArgs(NULL),
  mOptions(NULL),
  mTcpPort(20040),
  mPauseTimeout(10),
  mCallback(NULL),
  mStatus(LINK_NEW)
{  
    mActionQueue = new ActionQueue();
    
    Connection::initialize();
    Connect::initialize();
    
    mThread = new LinkThread();
    mThread->init(this, mActionQueue);
}


	///////////////////////////////////////////
	//
	//  Link destructor
	//

/** Link Destructor **/
Link::~Link()
{
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  sInstance
	//
Link *Link::sInstance = NULL;

	///////////////////////////////////////////
	//
	//  sGlobalLinkLock
	//
Mutex *Link::sGlobalLinkLock = new Mutex();

	///////////////////////////////////////////
	//
	//  getInstance
	//
Link *Link::getInstance()
{
    Synchronize sync = Synchronize(sGlobalLinkLock);
    if (sInstance == NULL) {
        sInstance = new Link(); 
    }
    return sInstance;
}


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  setPauseTimeout
	//
void Link::setPauseTimeout(int pPauseTimeout)
{
  mPauseTimeout = pPauseTimeout;
}

	///////////////////////////////////////////
	//
	//  getPauseTimeout
	//
int Link::getPauseTimeout()
{
  return mPauseTimeout;
}

	///////////////////////////////////////////
	//
	//  setTcpPort
	//
void Link::setTcpPort(int pTcpPort)
{
  mTcpPort = pTcpPort;
}

	///////////////////////////////////////////
	//
	//  getTcpPort
	//
int Link::getTcpPort()
{
  return mTcpPort;
}

	///////////////////////////////////////////
	//
	//  setOptions
	//
void Link::setOptions(OptionsArray *pOptions)
{
  mOptions = pOptions;
}

	///////////////////////////////////////////
	//
	//  getOptions
	//
OptionsArray *Link::getOptions()
{
  return mOptions;
}

	///////////////////////////////////////////
	// 
	//  setStartArgs
	//
void Link::setStartArgs(StartArgsArray *pStartArgs)
{
  mStartArgs = pStartArgs;
}

	///////////////////////////////////////////
	//
	//  getStartArgs
	//
StartArgsArray *Link::getStartArgs()
{
  return mStartArgs;
}

	///////////////////////////////////////////
	//
	//  setLocalCallRPCName
	//
void Link::setLocalCallRPCName(char *pName)
{
  mLocalCallRPCName = pName;
}

	///////////////////////////////////////////
	//
	//  getLocalCallRPCName
	//
char *Link::getLocalCallRPCName()
{
  return mLocalCallRPCName;
}

	///////////////////////////////////////////
	//
	//  setLocalStartRPCName
	//
void Link::setLocalStartRPCName(char *pName)
{
  mLocalStartRPCName = pName;
}

	///////////////////////////////////////////
	//
	//  getLocalStartRPCName
	//
char *Link::getLocalStartRPCName()
{
  return mLocalStartRPCName;
}

	///////////////////////////////////////////
	//
	//  getStatus
	//
LinkStatus Link::getStatus()
{
  return mStatus;
}

	///////////////////////////////////////////
	//
	//  registerCallback
	//
void Link::setCallback(LinkCallback *pCallback)
{
  mCallback = pCallback;
}

	///////////////////////////////////////////
	//
	//  queueAction
	//
void Link::queueAction(Action *pAction)
{
    Synchronize sync = Synchronize(sGlobalLinkLock);
    mActionQueue->queue(pAction);
    mThread->tickle();
}

	///////////////////////////////////////////
	//
	//  start
	//
void Link::start()
{
    Synchronize sync = Synchronize(sGlobalLinkLock);
    
    if (mStatus != LINK_RUNNING) {
        mThread->start();
        mStatus = LINK_RUNNING;
    }
}

	///////////////////////////////////////////
	//
	//  kill
	//
void Link::kill()
{
    Synchronize sync = Synchronize(sGlobalLinkLock);
    
    mThread->stop();
    if (mCallback) {
        mCallback->containerKilled(*this);
    }
}

	///////////////////////////////////////////
	//
	//  tickle
	//
void Link::tickle()
{    
    mThread->tickle();
}

	///////////////////////////////////////////
	//
	//  getWatchFd
	//
int Link::getWatchFd()
{
  return mThread->getTickleFd();
}

}
