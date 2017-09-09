/*----------------------------------------------------------------------
CLASS
    Hashtable

KEYWORDS

AUTHOR
    Allan Scott

DESCRIPTION
    An abstract base class of all hashtables that are used in CppLink,
    for example LongHashtable and StringHashtable.

    This Hashtable class is a thread safe datastructure.
LOG
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_HASHTABLE_H
#define _CPP_LINK_HASHTABLE_H

#include "api.h"
#include "hashtable-impl.h"
#include "Mutex.h"

namespace CppLink
{

class API Hashtable
{
public:
  Hashtable();
  virtual ~Hashtable();
  virtual int initialize(long pInitialSize) = 0;
  int add(void* key, void* value);
  void *get(void *key);
  void remove(void *key);
  void clear(); 
protected:
  struct hashtable mTable;
  Mutex *mMutex;
};

}

#endif // ifndef _CPP_LINK_HASHTABLE_H
