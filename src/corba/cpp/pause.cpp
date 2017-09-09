//
// Handle pause on context
//


#include <iostream_ver.h>
#include "gsi_main_cpp.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "corba_main.h"

void gsi_pause_context()
{
    printf ("gsi_pause_context in context %d\n",gsi_current_context());
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (cObj) cObj->paused = 1;
}

void gsi_resume_context()
{
    printf ("gsi_resume_context in context %d\n",gsi_current_context());
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (cObj) cObj->paused = 0;
}

