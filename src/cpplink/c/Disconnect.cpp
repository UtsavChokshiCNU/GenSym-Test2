#include "Disconnect.h"
#include "Connection.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Disconnect constructor
	//
Disconnect::Disconnect(Connection& pConnection) :
ConnectionAction(pConnection)
{
}

	///////////////////////////////////////////
	//
	//  Disconnect destructor
	//
Disconnect::~Disconnect()
{
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  doAction
	//
void Disconnect::doAction()
{  
  ConnectionAction::doAction();
  if (mStatus == ACTION_FAILED) {
    notify();
    if (mDeleteAfterCallback)
      delete this;
    return;
  }
  
  // The shutdown flag prevents any other actions taking place on the
  // context.
  mConnection->setShutdown(true);
  
  mStatus = ACTION_RUNNING;
  gsi_kill_context(mConnection->getContextId());
  
  mStatus = ACTION_COMPLETE;
  notify();
  if (mDeleteAfterCallback)
    delete this;
} 

}