
/*----------------------------------------------------------------------
CLASS
    StartArgsArray

KEYWORDS
    Link

AUTHOR
    Allan Scott

DESCRIPTION
	  The StartArgsArray is used to represent the arguments that the
    singleton Link object will use to start up GSI.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_START_ARGS_ARRAY_H
#define _CPP_LINK_START_ARGS_ARRAY_H

#include "api.h"

namespace CppLink 
{

class API StartArgsArray
{
 public:
   StartArgsArray(char *pStartArgs[],
     long pSize);
                
   ~StartArgsArray();
  
   long getSize();
   char **getArgs();
   char *startArg(long pIndex);

   char *operator[](long pIndex);

 private:
   char **mArgs;
   long mSize;
};

}

#endif // ifndef _CPP_LINK_START_ARGS_ARRAY_H