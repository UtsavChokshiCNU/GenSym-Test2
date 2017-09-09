/*----------------------------------------------------------------------
CLASS
    LinkCallback

KEYWORDS
    Link

AUTHOR
    Allan Scott

DESCRIPTION
    A callback interface for events that happen to the singleon Link 
    object.
	
LOG
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_LINK_CALLBACK_H
#define _CPP_LINK_LINK_CALLBACK_H

#include "api.h"
#include "Link.h"

namespace CppLink 
{

class Link;

class API LinkCallback
{
public:
  virtual void containerKilled(Link& pLink) = 0;
};

}

#endif // ifndef _CPP_LINK_LINK_CALLBACK_H