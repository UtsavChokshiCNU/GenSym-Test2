/************************************************************************************/
/* Shutdown context code																*/
/*																					*/
/* This file contains code to handle context shutdown						*/
/************************************************************************************/
#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"
#include "G2CorbaContainer.h"
	
void gsi_shutdown_context()
{
  gsi_int thisContext = gsi_current_context();

    printf ("\ngsi_shutdown_context in context %d\n",thisContext);

	G2OrbContext *ContextObj;
	ContextObj = (G2OrbContext *) ContextObjs.FindObj(thisContext);
	if (!ContextObj) {
		cout << "Unable to find context object for " << thisContext << endl;
	} else {
		deep_reclaim_items(ContextObj->RepositoryHead, 1);
		ContextObjs.Remove(ContextObj);
	}



	// We have to remember to remove any pending request and server objects

	G2SObject *sptr, *snext;
	for (sptr = (G2SObject *) Objects.GetFirst(); sptr; sptr = snext) {
		snext = (G2SObject *) sptr->GetNext();
		if (sptr->Context == thisContext) {
			Objects.Remove(sptr);
		}
	}
	
	G2CRequest *rptr, *rnext;
	for (rptr = (G2CRequest *) RequestObjs.GetFirst(); rptr; rptr = rnext) {
		rnext = (G2CRequest *) rptr->GetNext();
		if (rptr->Context == thisContext) {
			RequestObjs.Remove(rptr);
		}
	}	

	G2SRequest *srptr, *nsrptr;
	for (srptr = (G2SRequest *) ServReqObjs.GetFirst(); srptr; srptr = nsrptr) {
		nsrptr = (G2SRequest *) srptr->GetNext();
		if (srptr->Context == thisContext) {
			ServReqObjs.Remove(srptr);
		}
	}

}
