
#include <iostream_ver.h>
#include <fstream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>
#include <time.h>
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "iiop.h"
#include "connections.h"
#include "encoding.h"
#include "orbtype.h"

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"

// G2CorbaContainer classes


// Private Server Objects

//
// Checks to see if the object is valid on a given connection
//

unsigned char G2PSObject::is_valid_for_connection(int C)

{
	if (C == -1) return 0; // no for the any connection

	socket_data *sdata = (socket_data *) Sockets.FindObj(C);
	if (!sdata) return 0; // unable to find connection


	G2SubString *substr = (G2SubString *) sdata->private_ids.FindObj((char *) Marker);
	if (!substr) return 0; // not valid for this connection

	return 1;  // ok
}

//
// We have to be careful with the ref counts.  The ref count is set to 0 by 
// the constructor and incrmented each time we add a private connection.
// and decrmented each time we remove one.
//
// We dont want to call the finalize method if a privite connection is removed
// becuase the object is deregistered.  But, we do if it is becuase 
// a socket went away.  
//

unsigned char G2PSObject::add_private_connection(int C)

{
	if (C == -1) return 0; // ok

	socket_data *sdata = (socket_data *) Sockets.FindObj(C);
	if (!sdata) return 1;  // error

	G2SubString *subStr = new G2SubString((char *) Marker);
	sdata->private_ids.Add(subStr);  // make it ok to use on this connection
	ref_count++; 
	return 0; // ok
}

void G2PSObject::remove_private_connection()

{
	if (ref_count) ref_count--;
}


//
// Make sure there are no hanging private references
//

G2PSObject::~G2PSObject()

{
	char *id = (char *) Marker;

	for (socket_data *sdata = (socket_data *) Sockets.GetFirst(); sdata;
		sdata = (socket_data *) sdata->GetNext()) {

		G2SubString *substr = (G2SubString *) sdata->private_ids.FindObj(id);
		if (substr) sdata->private_ids.Remove(substr);
		
	}
}

		
//
// This is called when a socket is destroyed.  Lets make sure that we find any issoloated
// private connections and call the finalize methods.
//


G2SubString::~G2SubString()

{
	G2SObject *sObj = (G2SObject *) Objects.FindObj((char *) str);
	if (sObj) {
		sObj->remove_private_connection();
		if (sObj->can_finalize()) {
			G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(sObj->Context);
			if (cObj) {
				// send rpc message to G2
				gsi_item *Rets = gsi_make_items(2);
				gsi_set_handle(Rets[0], sObj->ObjHandle);
				gsi_set_sym(Rets[1], (char *) cObj->G2Interface);
				gsi_rpc_start(cObj->rpc_finalize_handle, Rets, sObj->Context); // send to G2
				gsi_reclaim_items(Rets);
			}
			Objects.Remove(sObj); // remove object
		}
	}
}


