/*----------------------------------------------------------------------
CLASS
    LongHashtable

KEYWORDS
    Hashtable

AUTHOR
    Allan Scott
   
DESCRIPTION
    A Hashtable that takes keys of type long
	
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_LONG_HASHTABLE_H
#define _CPP_LINK_LONG_HASHTABLE_H

#include "Hashtable.h"

namespace CppLink
{

class API LongHashtable : public Hashtable
{
public:
  virtual int initialize(long pInitialSize);
};

}

#endif // ifndef _CPP_LINK_LONG_HASHTABLE_H