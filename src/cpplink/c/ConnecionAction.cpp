#include "ConnectionAction.h"
#include "Connection.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  ConnectionAction constructor
	//
ConnectionAction::ConnectionAction(Connection& pConnection) : 
 Action(),
 mConnection(&pConnection)
{
 
}

	///////////////////////////////////////////
	//
	//  ConnectionAction destructor
	//
ConnectionAction::~ConnectionAction() 
{
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

const char * const ConnectionAction::sConnectionShutdown = 
   "Attempt to run action after connection is shutdown";

/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	// 
	//  getConnection 
	//
Connection& ConnectionAction::getConnection() 
{
  return *mConnection;
}

	///////////////////////////////////////////
	// 
	//  doAction
	//
void ConnectionAction::doAction()
{
  if (mConnection->isShutdown()) {
    mErrorString = copyErrorString(sConnectionShutdown);
    mErrorCode = 1;
    mStatus = ACTION_FAILED;
    
    if (mCallback) {
      mCallback->actionFailed(*this);
    }
  }
}

}
