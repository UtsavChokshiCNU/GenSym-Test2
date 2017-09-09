#include "Action.h"
#include "Synchronize.h"
#include <string.h>


namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Action constructor
	//
Action::Action() :
 mStatus(ACTION_CREATED),
 mErrorCode(0),
 mCallback(NULL),
 mErrorString(NULL),
 mDeleteAfterCallback(true),
 mTimeout(-1)
{
}

	///////////////////////////////////////////
	//
	//  Action destructor
	//
Action::~Action() 
{
  if (mErrorString) {
    delete[] mErrorString;
  }
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  copyErrorString
	//
char * Action::copyErrorString(const char * const pError)
{
  char *result = new char[strlen(pError) + 1];
  strcpy(result, pError);
  return result;
}

/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  setCallback
	//
void Action::setCallback(ActionCallback *pCallback)
{ 
  mCallback = pCallback;
}

	///////////////////////////////////////////
	//
	//  getCallback
	//
ActionCallback *Action::getCallback()
{
  return mCallback;
}

	///////////////////////////////////////////
	//
	//  getStatus
	//
ActionStatusFlag Action::getStatus()
{    
  return mStatus;
}

	///////////////////////////////////////////
	//
	//  setStatus
	//
void Action::setStatus(ActionStatusFlag pStatus)
{
  mStatus = pStatus;
}


	///////////////////////////////////////////
	//
	//  getErrorString
	//
char * Action::getErrorString()
{
  return mErrorString;
}

	///////////////////////////////////////////
	//
	//  setErrorString
	//
void Action::setErrorString(char *pErrorString)
{
  mErrorString = pErrorString;
}


	///////////////////////////////////////////
	//
	//  getErrorCode
	//
int Action::getErrorCode()
{
  return mErrorCode;
}


	///////////////////////////////////////////
	//
	//  setErrorCode
	//
void Action::setErrorCode(int pErrorCode)
{
  mErrorCode = pErrorCode;
}


	///////////////////////////////////////////
	//
	//  setDeleteAfterCallback
	//
void Action::setDeleteAfterCallback(bool pDeleteAfterCallback)
{ 
  mDeleteAfterCallback = pDeleteAfterCallback;
}


	///////////////////////////////////////////
	//
	//  getDeleteAfterCallback
	//
bool Action::getDeleteAfterCallback()
{ 
  return mDeleteAfterCallback;
}


	///////////////////////////////////////////
	//
	//  setTimeout
	//
void Action::setTimeout(long pTimeout)
{ 
  mTimeout = pTimeout;
}


	///////////////////////////////////////////
	//
	//  getTimeout
	//
long Action::getTimeout()
{ 
  return mTimeout;
}


	///////////////////////////////////////////
	//
	//  notify
	//
void Action::notify()
{
 
}

	///////////////////////////////////////////
	//
	//  waitFor
	//
void Action::waitFor()
{
  // FIND ME.  Need to implement blocking more
  // efficiently here.
  while(mStatus == ACTION_CREATED || 
        mStatus == ACTION_RUNNING ||
        mStatus == ACTION_QUEUED) {
     Sleep(50);
  }

}

}



