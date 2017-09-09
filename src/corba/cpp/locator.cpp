//
// This file contains code for the locator
//
#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>
#include <time.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"
#include "G2CorbaContainer.h"
#include "encoding.h"
#include "gsi_misc_cpp.h"

//
// Find context for locator call
//
G2OrbContext * find_locator_context()

{
	// we do this on a round robin basis
	static int last_g2_context = -1;
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(last_g2_context);
	if (!cObj) cObj = (G2OrbContext *) ContextObjs.GetFirst();
	if (cObj) {
		G2OrbContext *fObj = cObj;
		for (;1;) {
			cObj = (G2OrbContext *) cObj->GetNext();
			if (!cObj) cObj = (G2OrbContext *) ContextObjs.GetFirst(); // wrap to first
			if (cObj == fObj) break; // wraped all the way around
			if (cObj->has_locator == 0) continue;  // no locator
			if (cObj->paused) continue; // paused
			break;  // we got this far, ok 
		}
	}
	if (cObj) if (cObj->has_locator == 0) cObj = NULL; // no locator
	if (cObj) if (cObj->paused) cObj = NULL; // we could not find an active G2
	if (!cObj) { // we could not find an active G2
		last_g2_context = -1;
		cout << "Unable to find context for locate request" << endl;
		return NULL;
	}
	last_g2_context = cObj->context_number;
	if (debug_mode) cout << "Sending locate request to context:" << cObj->context_number << endl;
	return cObj; // ok, done
}

//
// Make the actual locator call to G2
//

void loc_do_call_locator(G2LRequest *lObj, G2OrbContext *cObj)

{
	if (!server_timeout) lObj->timeout_time = 0;
	else lObj->timeout_time = g_current_time + server_timeout;

	static int call_index = 1;
	lObj->CallIndex = call_index++;
	LocateReqObjs.Add(lObj);

	// Now send the request to G2
	gsi_item *Rets = gsi_make_items(4);
	gsi_set_str(Rets[0], (char *) lObj->objectkey);
	gsi_set_int(Rets[1], lObj->socket_id);
	gsi_set_sym(Rets[2], (char *) cObj->G2Interface);
	gsi_set_int(Rets[3], lObj->CallIndex);
	gsi_rpc_call(cObj->rpc_locate_handle, Rets, NULL, cObj->context_number);
	gsi_reclaim_items(Rets);
}

//
// We have a request for a object that we do not know about, 
// call the locator in G2.
//

void call_locator(iiop *iiopObj, unsigned long requestid,
				  unsigned char resp_expected,
				  char *objectkey, char *opname,
				  char *principal, socket_data *sdata) {


	// First, find a G2 to work with

	G2OrbContext *cObj = find_locator_context();
	if (!cObj) {
		cout << "Unable to find server object or locator:" << objectkey << endl;
		g2orb_return_server_mesg_excep(sdata, requestid, "OBJECT_NOT_EXIST", 0, 1);
		return ;
	}
	// Found g2 to talk to, create new request object

	G2LRequest *lObj = new G2LRequest;
	// Steal the iiop data
	lObj->iiopObj = iiopObj;
	lObj->requestid = requestid;
	lObj->resp_expected = resp_expected;
	lObj->objectkey = objectkey;
	lObj->opname = opname;
	lObj->principal = principal;
	lObj->socket_id = sdata->socket_id;
	lObj->is_request = 1;

	loc_do_call_locator(lObj, cObj);
}



//
// Generate a locate reply message
//

void loc_gen_message(iiop *ptr, G2LRequest *lObj, int stat, encodeable_object *eo, int flag)

{
	encode_mesg_header(ptr, 4, flag); // message header
	ptr->encode_ulong(lObj->requestid, flag); 
	ptr->encode_ulong(stat, flag); // reply status

	// we are done unless the message is a location forward

	if (eo) eo->encode(ptr, flag);
}


//
// Return a locate reply message
//

void loc_return_message(G2LRequest *lObj, int stat, encodeable_object *ref)

{
	iiop *ptr = new iiop;
	loc_gen_message(ptr, lObj, stat, ref, 0); // generate iiop message
	ptr->alloc_mem();
	loc_gen_message(ptr, lObj, stat, ref, 1);
	update_mesg_header_size(ptr);
	new Write_buffer(ptr, lObj->socket_id);
}


void loc_reject_request(G2LRequest *lObj, char *reason) {

	// if this is a request, then return a exception.  
	// If this is a locate, then return object not found


	if (lObj->is_request) {	// find socket
		socket_data *sdata = (socket_data *) Sockets.FindObj(lObj->socket_id);
		if (!sdata) return;  // no more socket, not much we can do
		g2orb_return_server_mesg_excep(sdata, lObj->requestid, "OBJECT_NOT_EXIST", 0, 1);
	} else {
		// return object not here 
		loc_return_message(lObj, 0, NULL);  // unknown object
	}
}

void loc_continue_request(G2LRequest *lObj) {

	// The object is now registered.  If this is a request, then continue
	// the request, if this is a locate, then return object here

	if (lObj->is_request) {	// find socket
		socket_data *sdata = (socket_data *) Sockets.FindObj(lObj->socket_id);
		if (!sdata) return;  // no more socket, not much we can do
		got_server_request(&lObj->iiopObj, lObj->requestid, lObj->resp_expected,
			(char *) lObj->objectkey, (char *) lObj->opname, 
			(char *) lObj->principal, sdata); // continue the request
	} else {
		// return object here
		loc_return_message(lObj, 1, NULL); // object here
	}
}

void loc_forward_request(G2LRequest *lObj, gsi_item ref) {

	encodeable_objref eo(ref, (G2OrbContext*)NULL, NULL);

	if (lObj->is_request) {	
		
		iiop *ret_mesg = new iiop;

		encode_mesg_header(ret_mesg, 1, 0); // build repy message
		ret_mesg->encode_ulong(0, 0); // no context
		ret_mesg->encode_ulong(lObj->requestid, 0);
		ret_mesg->encode_ulong(3, 0); // forward
		eo.encode(ret_mesg, 0); 

		ret_mesg->alloc_mem();	
		
		encode_mesg_header(ret_mesg, 1, 1); // build repy message
		ret_mesg->encode_ulong(0, 1); // no context
		ret_mesg->encode_ulong(lObj->requestid, 1);
		ret_mesg->encode_ulong(3, 1); // forward
		eo.encode(ret_mesg, 1); 

		update_mesg_header_size(ret_mesg);
		new Write_buffer(ret_mesg, lObj->socket_id);
	} else {
		// return object forward
		loc_return_message(lObj, 2, &eo); // object forward
	}
}





//
// This is the receiver function for the locator
//

void rpc_loc_recv(void *proc_data, gsi_item args[], gsi_int count, void *callIndex)

{	
	if (debug_mode) cout << "Got locate rpc return" << endl;
	if (count != 3 || gsi_type_of(args[0]) != GSI_SYMBOL_TAG
		|| gsi_type_of(args[1]) != GSI_STRING_TAG
		|| gsi_type_of(args[2]) != GSI_INTEGER_TAG) {
		cout << "Invalid arguments to rpc reply" << endl;
		return;
	}

	char *stat = gsi_sym_of(args[0]);
	int call_index = gsi_int_of(args[2]);

	// First, find the locate request object
	if (debug_mode) cout << "Got Locate Response:" << stat << endl;

	G2LRequest *lObj = (G2LRequest *) LocateReqObjs.FindObj(call_index);
	if (!lObj) {
		cout << "Unable to find locate request" << call_index << endl;
	}
	if (!strcmp(stat, "NEW-OBJECT") || !strcmp(stat, "PRIVATE-OBJECT")) {
		// continue request
		loc_continue_request(lObj);
	} else if (!strcmp(stat, "REJECT")) {
		loc_reject_request(lObj, "OBJECT_NOT_EXIST");
	} else if (!strcmp(stat, "FORWARD")) {
		loc_forward_request(lObj, args[1]);
	} else loc_reject_request(lObj, "OBJECT_NOT_EXIST");

	LocateReqObjs.Remove(lObj);
}

//
// Call the locator for a locate request
//
void loc_call_locator(G2LRequest *lObj)

{
	if (debug_mode) {
		cout << "Calling G2 locator for locate request" << endl;
	};
	
	G2OrbContext *cObj = find_locator_context();
	if (!cObj) {
		cout << "Unable to find server object or locator for locate message" << endl;
		loc_reject_request(lObj, "");
		return ;
	}

	loc_do_call_locator(lObj, cObj);
}


//
// This routine handles locate requests from remote ORB's
//

void got_locate_request(char *objectkey, unsigned long requestid, socket_data *sdata)

{

	// Generate a locate request object
	G2LRequest *lObj = new G2LRequest;
	lObj->requestid = requestid;
	lObj->resp_expected = 1;
	lObj->objectkey = objectkey;
	lObj->socket_id = sdata->socket_id;
	lObj->is_request = 0;

#ifdef nothing
	if (!strcmp(objectkey, "G2-System")) {
		loc_continue_request(lObj); // The system object is always here
		delete lObj;
		return;
	}
#endif
	// determine if the object is registered
	G2SObject *sObj = (G2SObject *) Objects.FindObj(objectkey);
	if (!sObj) {
		loc_call_locator(lObj);
		return;
	}

	// We found a object, is it available for this connection?
	if (!(sObj->is_valid_for_connection(sdata->socket_id))) {
		loc_call_locator(lObj);
		return;
	}

	// Ok, the object is valid
	loc_continue_request(lObj);
	delete lObj;  // new the request
}

//
// Build the locate request message
//
iiop *build_locate_request_body(G2CRequest *retobj)

{
	iiop *ptr = new iiop;

	iiop temp_iiop;    // get the object key
	temp_iiop.data_ptr = retobj->object_key.buf;
	temp_iiop.len = retobj->object_key.buf_len;
	temp_iiop.owns_data = 0;

	encode_mesg_header(ptr, 3, 0);
	ptr->encode_ulong(retobj->request_id, 0); 
	ptr->encode_encap_sequence(&temp_iiop, 0);

	ptr->alloc_mem();
	encode_mesg_header(ptr, 3, 1);
	ptr->encode_ulong(retobj->request_id, 1);
	ptr->encode_encap_sequence(&temp_iiop, 1);
	
	update_mesg_header_size(ptr);
	return ptr;
}


//
// g2orb-ping:  This is a rpc called from g2 to issue a locate request
//
// Input arguments: proxy Object as handle
// Output values: symbol: success or failure
//

void g2orb_ping_rpc(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{

	if (debug_mode) cout << "Pinging object" << endl;
	// Check args
	if (count != 1 || gsi_type_of(args[0]) != GSI_HANDLE_TAG) {
		g2orb_return_symbol_error("INVALID-ARGS", call_index, current_context);
		return;
	}

  G2CRequest *retobj = new G2CRequest;
	retobj->is_request = 0;  // locate request
	retobj->CallIndex = call_index;
	retobj->Context = current_context;
	retobj->response_expected = 1;  // expect return
	if (!client_timeout) retobj->timeout_time = 0;
	else retobj->timeout_time = g_current_time + client_timeout;

	// Find context object
	gsi_int handle = gsi_handle_of(args[0]);
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (!cObj) {
		g2orb_return_symbol_error("INTERNAL", call_index, current_context);
		delete retobj;
		return;
	}

	// Find proxy object
	G2CObject *pObj = (G2CObject *) cObj->proxies.FindObj(handle);
	if (!pObj) { // not registered
		g2orb_return_symbol_error("NOT-REGISTERED", call_index, current_context);
		delete retobj;
		return;
	}

	// is the object forwarded?
	unsigned char use_forward = 0;
	if (pObj->forwarded_object_key.buf_len) { // object forwarded
		// is the connection still there?
		if (pObj->connection_id) { // connection already there
			socket_data *sdata = (socket_data *) Sockets.FindObj(pObj->connection_id);
			if (sdata) use_forward = 1; // yes
		}
	}
	if (use_forward) retobj->object_key = pObj->forwarded_object_key;
	else retobj->object_key = pObj->object_key; // copy object key
	retobj->ObjHandle = handle; 
	retobj->request_id = get_request_id(); // get unqiue id
	iiop *iiopPtr = build_locate_request_body(retobj);
	if (!iiopPtr) {
		g2orb_return_symbol_error("MARSHAL", call_index, current_context);
		delete retobj;
		return;
	}
	RequestObjs.Add(retobj);

  if (debug_mode) {
    printf(">>Built a Locate request message with ID %d\n", retobj->request_id);
  }

	new Write_buffer(iiopPtr, pObj, retobj);
}


//
// Got the locate request reply
//

void got_locate_request_reply(G2CRequest *rObj, iiop *iiopObj, unsigned char reply_status)

{
	switch (reply_status) {
	case 0: { // unknown object
		g2orb_return_symbol_error("UNKNOWN-OBJECT", rObj->CallIndex, rObj->Context);
		break;
			}
	case 1: { // object here
		g2orb_return_symbol_error("SUCCESS", rObj->CallIndex, rObj->Context);
		break;
			}
	case 2: { // object forward
		// This is the hard one since we have to recover the forwarded object id, and 
		// and create a connection to the new location

		G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(rObj->Context);
		if (!cObj) {
			g2orb_return_symbol_error("INTERNAL", rObj->CallIndex, rObj->Context);
			break;
		}
		if (got_forward_reply(cObj, rObj, iiopObj)) {
			g2orb_return_symbol_error("MARSHAL", rObj->CallIndex, rObj->Context);
		} else {
			g2orb_return_symbol_error("OBJECT-FORWARDED", rObj->CallIndex, rObj->Context);
		}
		break;
			}
	default: break;
	}
	RequestObjs.Remove(rObj);
}


