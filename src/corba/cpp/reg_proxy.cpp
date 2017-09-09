/*
 * reg_obj.c - Routine to register a object
 */

#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>
#include "G2ContainerClass.h"

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"


//
// Here we register a proxy object.  We pass the object and the stringifiled object reference.
// We use a stringified object reference since it may be either URL style or IOR.
//
//. Args:
//		Object handle
//		Object reference
//		Name of interface
//


void g2orb_reg_proxy(void *proc_data, gsi_item args[], gsi_int count, void *call_index )     
{
	cout << "Got register proxy" << endl;

	if (count != 3 || gsi_type_of(args[0]) != GSI_HANDLE_TAG ||
		gsi_type_of(args[1]) != GSI_STRING_TAG ||
		gsi_type_of(args[2]) != GSI_SYMBOL_TAG) {

		g2orb_return_symbol_error("INVALID-ARGS", call_index, current_context);
		cout << "Invalid arguments to register proxy" << endl;
		return;
	}
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (!cObj) {
		g2orb_return_symbol_error("ERROR", call_index, current_context);
		cout << "Unable to find context object" << endl;
		return;
	}

	char *interfacename = gsi_sym_of(args[2]);
	gsi_int handle = gsi_handle_of(args[0]);
	char *objref = gsi_str_of(args[1]);

	G2CObject *pObj = (G2CObject *) cObj->proxies.FindObj(handle);
	if (pObj) cObj->proxies.Remove(pObj);  // remove if already regged


	//
	// We have to be very carefull about the type info.
	// Proxies may be indicated in one of three ways: IOR, URL, Expanded IOR
	// The IOR forms have specific type info, but the URL does not, we can assume
	// that the URL has the most specific interface.in the class.
	// So, for kind info, we use the IOR if available, otherwise, we use the interface name
	// to find the kind.
	//
	pObj = new G2CObject;
	if (decodeobjref(objref, pObj->Host, pObj->port_number, pObj->object_key)) {
		g2orb_return_symbol_error("INVALID-OBJ-REF", call_index, current_context);
		delete pObj;
		cout << "Unable to decode object reference:" << objref << endl;
		return;
	}
	pObj->Interface = interfacename;
	pObj->ObjHandle = handle;
	pObj->connection_id = 0;
	cObj->proxies.Add(pObj);

	g2orb_return_symbol_error("SUCCESS", call_index, current_context);
	cout << "Added Proxy " << objref  << ":" << interfacename << ":" << (char *) pObj->Host <<
		":" << pObj->port_number << endl;
}


//
// Deregister a proxy object.  The object handle is passed
//

void g2orb_dereg_proxy(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{

	cout << "Deregister Proxy" << endl;
	if (count != 1 || gsi_type_of(args[0]) != GSI_HANDLE_TAG) {

		g2orb_return_symbol_error("INVALID-ARGS", call_index, current_context);
		cout << "Invalid arguments to register proxy" << endl;
		return;
	}
	gsi_int handle = gsi_handle_of(args[0]);
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (!cObj) {
		g2orb_return_symbol_error("ERROR", call_index, current_context);
		cout << "Unable to find context object" << endl;
		return;
	}
	G2CObject *pObj = (G2CObject *) cObj->proxies.FindObj(handle);
	if (!pObj) {
		g2orb_return_symbol_error("OBJ-NOT-FOUND", call_index, current_context);
		cout << "Unable to find proxy to deregister."  << endl;
		return;
	}

	// To Do:  Add Code to remote pending client requests
	g2orb_return_symbol_error("SUCCESS", call_index, current_context);
	if (debug_mode) cout << "Removed proxy object" << endl;
}
