#include "Synchronize.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Synchronize constructor
	//
Synchronize::Synchronize(Mutex *pMutex) :
  mMutex(pMutex)
{ 
  mMutex->lock();
}

	///////////////////////////////////////////
	//
	//  Synchronize destructor
	//
Synchronize::~Synchronize()
{
  mMutex->unlock();
}

}