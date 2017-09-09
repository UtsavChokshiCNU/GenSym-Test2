#include "TickleConnectThread.h"
#include "Tickle.h"
#include "Utils.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  TickleConnectThread constructor
  //
TickleConnectThread::TickleConnectThread()
{
}

  ///////////////////////////////////////////
	//
	//  TickleConnectThread destructor
  //
TickleConnectThread::~TickleConnectThread()
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
	//  initialize
  //
void TickleConnectThread::initialize(Tickle *pTickle)
{
    mTickle = pTickle;
}

	///////////////////////////////////////////
	//
	//  run
  //
void TickleConnectThread::run()
{ 
  int result = 1;
  int tries = 0;

  Utils::debugLogException(0, "Got here\n");    
  while (result = mTickle->connectTickle()) {
    Sleep(10);
    if (tries ++ > 25) {
      Utils::debugLogException(result, "Failed to connect to Tickle socket after 25 tries");
       break;
    }
  }

  kill();
}

}