
/*----------------------------------------------------------------------
CLASS
    Synchronize

KEYWORDS
    Mutex

AUTHOR
    Dave Westen Allan Scott

DESCRIPTION
    A convenience class for  creating a synchronized block.

    The mutex passed to it is locked in the constructor and
    then  is unlocked in the destructor.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_SYNCHRONIZE_H
#define _CPP_LINK_SYNCHRONIZE_H

#include "Mutex.h"


namespace CppLink
{

class API Synchronize
{
public:
  Synchronize(Mutex *pMutex);
  ~Synchronize();
private:
  Mutex *mMutex;
};
}

#endif // ifndef _CPP_LINK_SYNCHRONIZE_H