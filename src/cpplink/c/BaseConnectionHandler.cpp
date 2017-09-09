#include "ConnectionCallback.h"
#include <string.h>

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  BaseConnectionHandler constructor
	//
BaseConnectionHandler::BaseConnectionHandler()
{
}

  ///////////////////////////////////////////
	//
	//  BaseConnectionHandler destructor
	//
BaseConnectionHandler::~BaseConnectionHandler()
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
	//  contextStarted
	//
void BaseConnectionHandler::contextStarted(Connection& pConnection)
{

}

  ///////////////////////////////////////////
	//
	//  contextPaused
	//
void BaseConnectionHandler::contextPaused(Connection& pConnection)
{

}

  ///////////////////////////////////////////
	//
	//  contextResumed
	//
void BaseConnectionHandler::contextResumed(Connection& pConnection)
{

}


  ///////////////////////////////////////////
	//
	//  contextReset
	//
void BaseConnectionHandler::contextReset(Connection& pConnection)
{


}

  ///////////////////////////////////////////
	//
	//  contextShutdown
	//
void BaseConnectionHandler::contextShutdown(Connection& pConnection)
{

}


  ///////////////////////////////////////////
	//
	//  call
	//  
void BaseConnectionHandler::call(ItemArray& pArgs, void *pCallId)
{

}

  ///////////////////////////////////////////
	//
	//  start
	//  
void BaseConnectionHandler::start(ItemArray &pArgs, void *pCallId)
{


}

  ///////////////////////////////////////////
	//
	//  message
	//  
void BaseConnectionHandler::message(char *message, int pLength)
{

}

  ///////////////////////////////////////////
	//
	//  error
	//  
void BaseConnectionHandler::error(int pCode, char *pMessage)
{

}
}