
/************************************************************************************/
/* Init Context																	    */
/*																					*/
/* This file contains the init context event 							            */
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
	

gsi_int gsi_initialize_context( char *remote_process_init_string, gsi_int length)
{
  gsi_int thisContext = gsi_current_context();
//	printf( "Inside gsi_initialize_context() - Context %d\n", current_context );    
//	printf("%s\n",remote_process_init_string);

	// Create a new context object
	G2OrbContext *ContextObj = new G2OrbContext;
	ContextObj->context_number = thisContext;
	gsi_rpc_declare_remote(&ContextObj->rpc_locate_handle, "_G2ORB-LOCATE-RPC", rpc_loc_recv, NULL, 4, 3, thisContext);
	gsi_rpc_declare_remote(&ContextObj->rpc_finalize_handle, "_G2ORB-FINALIZE-RPC", NULL, NULL, 2, 0, thisContext);
	gsi_rpc_declare_remote(&ContextObj->rpc_purge_handle, "_G2ORB-PURGE-RPC", NULL, NULL, 1, 0, thisContext);
	gsi_rpc_declare_remote(&ContextObj->rpc_get_vers, "_G2ORB-VERCHK", NULL, NULL, 0, 0, thisContext) ;
	ContextObjs.Add(ContextObj);

	gsi_rpc_start(ContextObj->rpc_get_vers, NULL, ContextObj->context_number) ;

	cout << "Context init complete (" << thisContext << ")" << endl;

  return( GSI_ACCEPT );
}


