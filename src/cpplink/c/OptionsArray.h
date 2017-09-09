
/*----------------------------------------------------------------------
CLASS
    OptionsArray

KEYWORDS
    Link
    
AUTHOR
    Allan Scott
   
DESCRIPTION
    The OptionsArray object is used to configure the singleton Link object 
    with the options that are available.
    
    The available options are a subset of those available in GSI
    and are defined by the Option enumeration.

LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_OPTIONS_ARRAY_H
#define _CPP_LINK_OPTIONS_ARRAY_H

#include "api.h"
#include "gsi_main_cpp.h"


namespace CppLink 
{

enum API Option
{
  OPTION_SUPPRESS_OUTPUT = GSI_SUPPRESS_OUTPUT,
  OPTION_STRING_CHECK = GSI_STRING_CHECK
};

class API OptionsArray
{
 public:
   OptionsArray(
     Option *pOptions,
     long pNumOptions);
                
   ~OptionsArray();
  
   long getSize();
   Option option(long pIndex);
   Option operator[](long pIndex);

 private:
   Option* mOptions;
   long mSize;
};

}

#endif // ifndef _CPP_LINK_OPTIONS_ARRAY_H