/*
 * reg_obj.c - Routine to register a object
 */

#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"


// Return an error code to G2

void g2orb_return_symbol_error(char *code, void *call_index, gsi_int context_number)

{
	gsi_item *ret = gsi_make_items(1);
	gsi_set_sym(ret[0], code);
	gsi_rpc_return_values(ret, 1, call_index, context_number);
	deep_reclaim_items(ret, 1);
}


// Register an object to accept requests
// The first argument is the object handle
// The second argument is the marker
// Third argument is the interface name
// The Forth is the connection number if private, -1 if public
//
// If an object with the name already exists, and it is in the same context, then this will
// redefine the object and remove the old definition.  If it is already defined in a different
// context, then an error will be reported.
// A symbol error code is returned.  SUCCESS indicates operation completed ok.
//  we also return a coded object ref
//
// First, we find the interface in the registered interface set.

void g2orb_reg_obj(void *proc_data, gsi_item args[], gsi_int count, void *call_index )     
{
	if (count != 4 || gsi_type_of(args[0]) != GSI_HANDLE_TAG ||
		gsi_type_of(args[1]) != GSI_STRING_TAG ||
		gsi_type_of(args[2]) != GSI_SYMBOL_TAG ||
		gsi_type_of(args[3]) != GSI_INTEGER_TAG) { // types ok

		g2orb_return_symbol_string_error("INVALID-ARGS", "", call_index, current_context);
		cout << "Invalid arguments to register object" << endl;
		return;
	}

	gsi_int obj_handle = gsi_handle_of(args[0]);
	char *marker = gsi_str_of(args[1]);
	char *intname = gsi_sym_of(args[2]);
	gsi_int conn_number = gsi_int_of(args[3]);

	G2SObject *sObj = (G2SObject *) Objects.FindObj(marker);
	if (sObj) { // ID already defined.
		if (sObj->Context == current_context) { 
			Objects.Remove(sObj);  // nuke it
		} else { // different context
			g2orb_return_symbol_string_error("ID-IN-USE", "", call_index, current_context);
			cout << "Object ID " << marker << " is already in use in a different context" << endl;
			return;
		}
	}

	// Find context and interface

	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (!cObj) {
		g2orb_return_symbol_string_error("ERROR", "Unable to find context", call_index, current_context);
		cout << "Unable to find context object" << endl;
		return;
	}
	// Find the interface object
		
	G2Interface *iObj = (G2Interface *) cObj->interfaces.FindObj(intname);
	if (!iObj && strcmp(intname, "NONE")) {
		g2orb_return_symbol_string_error("ERROR", "Unable to find interface", call_index, current_context);
		cout << "Unable to find interface object" << endl;
		return;
	}

	// now build object ref

	G2String objectref;
	if (iObj) {
		iiop ior;
		G2OctSeq obj_key;
		obj_key.set_buf(marker, strlen(marker)+1);
		genbinior(ior, (char *) iObj->kind, (char *) hostname, hostport, obj_key, (char *) cObj->hostname, 
				cObj->g2_port, 1);

		// convert it to text.
		ior.index = 0; // start at begining
		int kind = binior2objref(ior, current_context, objectref);
		if (kind == -1) {
			g2orb_return_symbol_string_error("ERROR", "Unable to generate object ref", call_index, current_context);
			cout << "Unable to generate object ref" << endl;
			return;
		}
	}

	if (conn_number != -1) sObj = new G2PSObject; // private object
	else sObj = new G2SObject; // public object

	sObj->ObjHandle = obj_handle;
	sObj->Context = current_context;
	sObj->Marker = marker;
	sObj->Interface = intname;

	Objects.Add(sObj);

	if (conn_number != -1) {
		if (sObj->add_private_connection(conn_number)) {
			g2orb_return_symbol_string_error("ERROR", "Unable to add private connection", call_index, current_context);
			cout << "Unable to add private connection:" << conn_number << endl;
			return;
		}
	}

	g2orb_return_symbol_string_error("SUCCESS", (char *) objectref, call_index, current_context);
	cout << "Added Object " << marker  << ":" << intname <<  endl;
}

//
// This will deregister a server object.  The object marker is passed
//
void g2orb_dereg_obj(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	if (count != 1 || gsi_type_of(args[0]) != GSI_STRING_TAG) {
		g2orb_return_symbol_error("INVALID-ARGS", call_index, current_context);
		cout << "Invalid arguments to deregister object" << endl;
		return;
	}

	char *objid = gsi_str_of(args[0]);

	G2SObject *sObj = (G2SObject *) Objects.FindObj(objid);
	if (!sObj) {
		g2orb_return_symbol_error("OBJ-NOT-FOUND", call_index, current_context);
		cout << "Unable to find object to deregister. ID: " << objid << endl;
		return;
	}
	if (sObj->Context != current_context) {
		g2orb_return_symbol_error("WRONG-CONTEXT", call_index, current_context);
		cout << "Object registered to different context" << endl;
	}

	Objects.Remove(sObj);
	g2orb_return_symbol_error("SUCCESS", call_index, current_context);
	cout << "Removed Object " << objid << endl;

}

