#include "Mutex.h"

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Mutex constructor
	//
Mutex::Mutex()
{
#ifdef WIN32
    InitializeCriticalSection(&mCritSection);
#else
    // FIND ME. Add POSIX impl here
#endif
}

  ///////////////////////////////////////////
	//
	//  Mutex destructor
	//
Mutex::~Mutex()
{
#ifdef WIN32
    DeleteCriticalSection(&mCritSection);
#else
// FIND ME. Add POSIX impl here
#endif
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  lock
	//
void Mutex::lock()
{
#ifdef WIN32
    EnterCriticalSection(&mCritSection);
#else
// FIND ME. Add POSIX impl here 
#endif
}

	///////////////////////////////////////////
	//
	//  unlock
	//
void Mutex::unlock()
{
#ifdef WIN32
    LeaveCriticalSection(&mCritSection);
#else
// FIND ME. Add POSIX impl here
#endif
}

}