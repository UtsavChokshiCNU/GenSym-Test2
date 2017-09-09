#include "Thread.h"
#include <process.h>

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Thread constructor
	//
Thread::Thread()
{
}

  ///////////////////////////////////////////
	//
	//  Thread destructor
	//

Thread::~Thread()
{
}


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

void ThreadRoutine(void *val)
{
  ((Thread *) val)->run();
} 

void Thread::start()
{
  mStopFlag = false;

#ifdef WIN32  
  _beginthread(ThreadRoutine, 0, this);
#else 
  // FIND ME  POSIX thread code here
#endif
}

void Thread::stop()
{
    mStopFlag = true;
}

void Thread::kill()
{
#ifdef WIN32
    _endthread();
#else 
  // FIND ME  POSIX thread code here
#endif
}

}
