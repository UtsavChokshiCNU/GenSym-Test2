#include "ActionCallback.h"
#include "Connect.h"
#include "Disconnect.h"
#include "Start.h"
#include "Call.h"
#include "ReturnValues.h"
#include "Utils.h"
#include <string.h>
#include <stdio.h>


namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

  ///////////////////////////////////////////
	//
	//  BaseActionHandler constructor
	//
BaseActionHandler::BaseActionHandler()
{
}

	///////////////////////////////////////////
	//
	//  BaseActionHandler destructor
	//
BaseActionHandler::~BaseActionHandler()
{
}

/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

void BaseActionHandler::actionCompleted(Action& pAction)
{
}

void BaseActionHandler::actionFailed(Action& pAction)
{
  char *errorString = pAction.getErrorString();
  char * buffer = new char[strlen(errorString) + 1024];
    
  sprintf(buffer, 
    "Action failed, errorCode: %d, errorMessage %s",
    pAction.getErrorCode(),
    errorString);

  Utils::debugLogException(0, buffer);
  
  delete [] buffer;
}

void BaseActionHandler::actionFailed(Connect& pAction)
{
  char *errorString = pAction.getErrorString();
  char *buffer= new char[strlen(errorString) + 1024];
    
  sprintf(buffer, 
    "Connect failed, errorCode: %d, errorMessage %s",
    pAction.getErrorCode(),
    errorString);

  Utils::debugLogException(0, buffer);

  delete [] buffer;
}

void BaseActionHandler::actionFailed(Disconnect& pAction)
{
  char *errorString = pAction.getErrorString();
  char *buffer = new char [strlen(errorString) + 1024];
    
  sprintf(buffer, 
    "Disconnect failed, errorCode: %d, errorMessage %s",
    pAction.getErrorCode(),
    errorString);

  Utils::debugLogException(0, buffer);
  delete [] buffer;
}

void BaseActionHandler::actionFailed(Call& pAction)
{
  char *errorString = pAction.getErrorString();
  char *buffer =  new char[strlen(errorString) + 1024];
    
  sprintf(buffer, 
    "Call failed, errorCode: %d, errorMessage %s",
    pAction.getErrorCode(),
    errorString);

  Utils::debugLogException(0, buffer);

  delete [] buffer;
}

void BaseActionHandler::actionFailed(ReturnValues& pAction)
{
  char *errorString = pAction.getErrorString();
  char *buffer = new char[strlen(errorString) + 1024];
    
  sprintf(buffer, 
    "ReturnValues failed, errorCode: %d, errorMessage %s",
    pAction.getErrorCode(),
    errorString);

  Utils::debugLogException(0, buffer);

  delete [] buffer;
}

void BaseActionHandler::actionFailed(Start& pAction)
{
  char *errorString = pAction.getErrorString();
  char *buffer = new char[strlen(errorString) + 1024];
    
  sprintf(buffer, 
    "Start failed, errorCode: %d, errorMessage %s",
    pAction.getErrorCode(),
    errorString);

  Utils::debugLogException(0, buffer);

  delete [] buffer;
}

}