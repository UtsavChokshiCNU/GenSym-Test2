/*----------------------------------------------------------------------
CLASS
    Mutex

KEYWORDS
    Synchronize

AUTHOR
    Allan Scott
   
DESCRIPTION
    An implementation of a simple Mutex.
  
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_MUTEX_H
#define _CPP_LINK_MUTEX_H

#include "api.h"

namespace CppLink
{

class API Mutex
{
 public:
   Mutex();
   ~Mutex();
   void lock();
   void unlock();
 private:
#ifdef WIN32
   CRITICAL_SECTION mCritSection;
#else 
 
#endif 

};

}

#endif // ifndef _CPP_LINK_MUTEX_H