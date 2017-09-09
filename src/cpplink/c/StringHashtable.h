/*----------------------------------------------------------------------
CLASS
    StringHashtable

KEYWORDS
     Hashtable

AUTHOR
     Allan Scott

DESCRIPTION
	   A hashtable that uses strings for the key
     
LOG
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_STRING_HASHTABLE_H
#define _CPP_LINK_STRING_HASHTABLE_H

#include "api.h"
#include "Hashtable.h"

namespace CppLink
{

class API StringHashtable : public Hashtable
{
public:
  virtual ~StringHashtable();
  virtual int initialize(long pInitialSize);
  int addKey(char *pKey, void *pValue); 
};

}


#endif // ifndef _CPP_LINK_STRING_HASHTABLE_H