/*----------------------------------------------------------------------
CLASS
    Utils

KEYWORDS
    
AUTHOR
    John Valente Allan Scott   

DESCRIPTION
    Utilities that are used across the CppLink library.  

    Currently this includes logging and string manipulation utilities.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_UTILS_H
#define _CPP_LINK_UTILS_H

namespace CppLink
{
  class Utils
  { 
  public:
    static void debugLogException (int priority, char *message);
    static void toUpper(char *pString);
  };
}

#endif