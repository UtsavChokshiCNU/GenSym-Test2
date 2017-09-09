/*
 * send_req.c - Code to send a request to Orbix.
 */
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
#include "gsi_misc_cpp.h"
#include "corba_main.h"

NoHashContainer PurgeObjects;  // list of objects to be purged after decoding
bool decode_top_level = true;
//
//
// Return error condition.
// This creates an system exception object and returns it.  
// 
void g2orb_send_rpc_return_se(char *kind, gsi_int minor, gsi_int comp_status, void *call_handle, gsi_int context_number)

{
	// First create the exception object
	gsi_item *Except = gsi_make_items(1);  // Create exception object
	gsi_set_class_name(Except[0],"G2ORB-SYSTEM-EXCEPTION");
	gsi_attr *ExceptAttrs = gsi_make_attrs_with_items(4);
	gsi_set_attr_name(ExceptAttrs[0],"G2ORB-EXCEPTION-KIND");
	gsi_set_sym(ExceptAttrs[0],kind);
	gsi_set_attr_name(ExceptAttrs[1], "G2ORB-MINOR");
	gsi_set_int(ExceptAttrs[1], minor);
	gsi_set_attr_name(ExceptAttrs[2], "G2ORB-COMPLETION-STATUS");
	switch (comp_status) {
	case 0:  gsi_set_sym(ExceptAttrs[2], "COMPLETED-YES");
		     break;
	case 1:  gsi_set_sym(ExceptAttrs[2], "COMPLETED-NO");
		     break;
	case 2:  
	default: gsi_set_sym(ExceptAttrs[2], "COMPLETED-MAYBE");
		     break;
	}
	gsi_set_attr_name(ExceptAttrs[3], "ERROR-DESCRIPTION");
	gsi_set_str(ExceptAttrs[3], kind);
	gsi_set_attrs(Except[0], ExceptAttrs, 4);

	gsi_rpc_return_error_values(Except, 1, call_handle, context_number);
	deep_reclaim_items(Except,1);
}


//
 // Add an Any object to a named list
//
// We are passed a pointer to the gsi attribute or parm. 
unsigned char build_Any_from_gsi(gsi_item gsiItem, gsi_item *args, 
								 int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	// Get the typecode of object
	char *class_name = gsi_class_name_of(gsiItem);
	gsi_item defobj;
	if (!strcmp(class_name, "G2ORB-OPERATIONDEF")) {
		defobj = get_attr_by_name(gsiItem, "G2ORB-RESULT");
		if (!defobj) return 1;
	} else if (!strcmp(class_name, "G2ORB-UNIONDEF")) {
		defobj = get_attr_by_name(gsiItem, "G2ORB-DISCRIMINATOR-TYPE");
		if (!defobj) return 1;
	} else if (!strcmp(class_name, "G2ORB-ALIASDEF")) {
		defobj = get_attr_by_name(gsiItem, "G2ORB-ORIGINAL-TYPE");
		if (!defobj) return 1;
	} else if (!strcmp(class_name, "G2ORB-ARRAYDEF")) {
		defobj = get_attr_by_name(gsiItem, "G2ORB-ELEMENT-TYPE");
		if (!defobj) return 1;
	} else if (!strcmp(class_name, "G2ORB-SEQUENCEDEF")) {
		defobj = get_attr_by_name(gsiItem, "G2ORB-ELEMENT-TYPE");
		if (!defobj) return 1;
	} else {
		defobj = get_attr_by_name(gsiItem, "G2ORB-TYPE");
		if (!defobj) return 1;
	}
	char *optype = gsi_str_of(defobj);

	orbtype *tObj = (orbtype *) cObj->orbtypes.FindObj(optype);
	if (!tObj) {
		cout << "Unable to find definition for type:" << optype << " in " << class_name << endl;
		return 1;
	}

	tObj = tObj->getTrueType(); // follow alias, if any
	if (truetype) (*truetype) = (char *) tObj->key; // grab type, if needed

	decode_top_level = false; // no longer at top level
	int temp = tObj->build_encodeable_object(args, argIndex,
								 cObj,
								 arglist,
								 direction);
	return (unsigned char) temp;
}

//
// This will build a named value list from a operation name, context object and arrays of
// gsi values and items.
//
// direction is:
//   1 for request outgoing
//   2 for request reply incoming
//   3 for request incoming
//   4 for request reply outgoing
//
// The arglist is a collection of encodeable objects.  We assocate each
// encodeable object with a gsi item.  We only include the encodeable objects
// that we need to send, that is out and inout's  These are similar to the 
// NVList specified in CORBA.
//
// This uses a set of prebuilt orbtypes that where generated when 
// the ir object was downloaded. This minimizes the need to look
// at actual gsi ir objects.
//
unsigned char build_NVList_from_gsi(G2OrbContainer &arglist,
									G2Interface *iObj,
									G2Operation *oObj,
									G2OrbContext *cObj,
									gsi_item *Args,
									int direction) {


	int argIndex = 0;
	orbtypePtr *pObj;

	if (direction == 2 || direction == 4) { // out
		for (pObj = (orbtypePtr *) oObj->outOrbTypes.GetFirst();
			pObj; pObj = (orbtypePtr *) pObj->GetNext()) {
			decode_top_level = true;
				// now, for each orbtype, call the construtorint 
			if (!pObj->m_tObj) { cout << "Null type pointer!" << endl; continue;}
			if (pObj->m_tObj->build_encodeable_object(Args, argIndex, cObj, arglist, direction)) return 1;
		}
	} else { // in
		for (pObj = (orbtypePtr *) oObj->inOrbTypes.GetFirst();
			pObj; pObj = (orbtypePtr *) pObj->GetNext()) {

			decode_top_level = true;
			if (!pObj->m_tObj) { cout << "Null type pointer!" << endl; continue;}
			if (pObj->m_tObj->build_encodeable_object(Args, argIndex, cObj, arglist, direction)) return 1;
		}
	}
	return 0;
}



//
// Encode message header
//
void encode_mesg_header(iiop *ptr, int mesg_type, int flag)
{
	ptr->encode_oct('G',flag);	// magic
	ptr->encode_oct('I',flag);
	ptr->encode_oct('O',flag);
	ptr->encode_oct('P',flag);
	ptr->encode_oct(1,flag);	// version
	ptr->encode_oct(0,flag);
	ptr->encode_oct(NATURAL_CODING,flag);  // byte order
	ptr->encode_oct((char) mesg_type, flag); // message type
	ptr->encode_ulong(0,flag);  // we do not have the size yet
}

//
// Update the size field
//
void update_mesg_header_size(iiop *ptr)

{
	unsigned long old_index = ptr->index;
	ptr->index = 8;
	ptr->encode_ulong(ptr->len - 12, 1); // actual size
	ptr->index = old_index;
}

//
// Encode the request header
//
void encode_req_header(iiop *ptr, G2CRequest *retobj, int flag,
                       char* principal)

{
	ptr->encode_ulong(0,flag);  // null context list
	ptr->encode_ulong(retobj->request_id, flag); 
	ptr->encode_oct(retobj->response_expected, flag);
	iiop temp_iiop;
	temp_iiop.data_ptr =retobj->object_key.buf;
	temp_iiop.len = retobj->object_key.buf_len;
	temp_iiop.owns_data = 0;
	ptr->encode_encap_sequence(&temp_iiop, flag);
	ptr->encode_string((char *) retobj->operation, flag);

    if (principal == NULL)
	    ptr->encode_string("", flag);
    else
	    ptr->encode_string(principal, flag);
}


//
// This builds the actual request body. 
// We first need to find out how much memory we need.
// We run through the encodeable objects and first estimate the packet size.  Then we
// allocate the memory and encode the object
//

iiop *build_request_body(G2OrbContainer &arglist, G2CRequest *retobj,
                         char* principal)

{
	iiop *ptr = new iiop;
	encodeable_object *eo;

	relations_flag = 0;  // make sure this flag is reset
	encode_mesg_header(ptr, 0, 0); // Build req header
	encode_req_header(ptr, retobj, 0, principal);
	for (eo = (encodeable_object *) arglist.GetFirst();
		eo; eo = (encodeable_object *) eo->GetNext()) {
			if (eo->encode(ptr, 0)) return NULL;
	}
	ptr->alloc_mem();
	encode_mesg_header(ptr, 0, 1);
	encode_req_header(ptr, retobj, 1, principal);
	for (eo = (encodeable_object *) arglist.GetFirst();
		eo; eo = (encodeable_object *) eo->GetNext()) {
			if (eo->encode(ptr, 1)) return NULL;
	}
	update_mesg_header_size(ptr);
	return ptr;
}

//
// Decode the body of a request
//
int decode_request_body(G2OrbContainer &arglist, iiop *iiopObj, int context_num)

{
	decoding_context = context_num;
	g2item_level_deep = 0;
	for (encodeable_object *eo = (encodeable_object *) arglist.GetFirst();
		eo; eo = (encodeable_object *) eo->GetNext()) {
			if (eo->decode(iiopObj)) return 1;
			//if (debug_mode) gsirtl_display_item_or_value(eo->itm, 1, 1);
	}
	return 0;
}



unsigned long get_request_id(void)

{
	static unsigned long next_request_id = 0;
	return next_request_id++;
}



//
// Build request for ORB
//
// This is called when there is a client request for a remot
// ORB.  
// 
// The Arguments are:
//    Object handle
//    Op name
//    sequence of arguments or symbol none
//
void build_orb_request(gsi_item args[], int count, void *call_index)

{
	G2CRequest *retobj = new G2CRequest;
	// Check argument types
	if (count != 3 || (gsi_type_of(args[0]) != GSI_HANDLE_TAG) ||
		 (gsi_type_of(args[1]) != GSI_STRING_TAG) ||
	     (gsi_type_of(args[2]) != GSI_SEQUENCE_TAG && gsi_type_of(args[2]) != GSI_SYMBOL_TAG)) {
		
		g2orb_send_rpc_return_se("BAD-PARM", 0, 1, call_index, current_context);
		delete retobj;
		return; // fail
	}

	retobj->CallIndex = call_index;
	retobj->Context = current_context;
	if (!client_timeout) retobj->timeout_time = 0;
	else retobj->timeout_time = g_current_time + client_timeout;

	// Find the context object.
	gsi_int handle = gsi_handle_of(args[0]);
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (!cObj) {
		g2orb_send_rpc_return_se("INTERNAL", 0, 1, call_index, current_context);
		cout << "Unable to find context object" << endl;
		delete retobj;
		return;
	}
	// Find the proxy object
	G2CObject *pObj = (G2CObject *) cObj->proxies.FindObj(handle);
	if (!pObj) { // Not registered
		gsi_item *Rets = gsi_make_items(1);  // Create return array
		gsi_set_sym(Rets[0], "NOT-REGISTERED");
		gsi_rpc_return_values(Rets, 1, call_index, current_context);
		gsi_reclaim_items(Rets);
		cout << "Proxy object not registered" << endl;
		delete retobj;
		return;
	}
	
	// Now, we need to check for a forwarded message.
	unsigned char use_forward = 0;
	if (pObj->forwarded_object_key.buf_len) { // Object has been forwarded
		// is the connection still there?
		if (pObj->connection_id) { // we have a connection already
			socket_data *sdata = (socket_data *) Sockets.FindObj(pObj->connection_id); 
			if (sdata) use_forward = 1; // yes
		}
	}
	if (use_forward) retobj->object_key = pObj->forwarded_object_key;
	else retobj->object_key = pObj->object_key; // copy object key
	retobj->ObjHandle = handle;  // save handle so we can find the proxy object if we need to forward it

	// Find the interface object
	retobj->Interface = pObj->Interface;
	G2Interface *iObj = (G2Interface *) cObj->interfaces.FindObj(pObj->Interface);
	if (!iObj) {
		g2orb_send_rpc_return_se("BAD-OPERATION", 0, 1, call_index,current_context);
		cout << "Unable to find interface object" << endl;
		delete retobj;
		return;
	}
	// Find the operation object
	char *operation = gsi_str_of(args[1]);
	retobj->operation = operation;
	G2Operation *oObj = got_server_find_operation(operation, iObj, cObj) ;
	if (!oObj) {
		g2orb_send_rpc_return_se("BAD-OPERATION", 0, 1, call_index, current_context);
		cout << "Unable to find operation object" << endl;
		delete retobj;
		return;
	}
	G2OrbContainer arglist(0);

	if (oObj->in_values) {
		if (gsi_type_of(args[2]) != GSI_SEQUENCE_TAG) {
			g2orb_send_rpc_return_se("MARSHAL", 0, 1, call_index, current_context);
			delete retobj;
			return;
		}
		if ((unsigned) gsi_element_count_of(args[2]) != oObj->in_values) {
			cout << "Got " << gsi_element_count_of(args[3]) << " value arguments for operation and expected " << oObj->in_values << endl;
			g2orb_send_rpc_return_se("MARSHAL", 0, 1, call_index, current_context);
			delete retobj;
			return;
		}
	}

	if (build_NVList_from_gsi(arglist, iObj, oObj, cObj, (oObj->in_values) ? gsi_elements_of(args[2]) : (gsi_item*)NULL, 1)) {
		g2orb_send_rpc_return_se("MARSHAL", 0, 1, call_index, current_context);
		delete retobj;
		return;
	}
	// At this point, we should have the constructed list of primitive values.
	retobj->request_id = get_request_id();
	retobj->is_request = 1;
	if (oObj->isoneway) retobj->response_expected = 0; else retobj->response_expected = 1;
	// Now build the request body
	iiop *iiopptr = build_request_body(arglist, retobj, (char*)cObj->principal);
	if (!iiopptr) {
		g2orb_send_rpc_return_se("MARSHAL", 0, 1, call_index, current_context);
		delete retobj;
		return;
	}

  if (debug_mode) {
    printf(">>Built a %s request for interface %s with ID: %d\n",
      (char*)retobj->operation, (char*)retobj->Interface, retobj->request_id);
  }

	RequestObjs.Add(retobj);
	new Write_buffer(iiopptr, pObj, retobj);
	return;
}

//
// Fail a request
//
void request_failed(G2CRequest *rObj, char *code) {


	// How we fail a request depends on if this is a locate request or a operation request

	if (rObj->is_request) g2orb_send_rpc_return_se(code, 0, 1, rObj->CallIndex, rObj->Context);
	else g2orb_return_symbol_error(code, rObj->CallIndex, rObj->Context);
	RequestObjs.Remove(rObj);
}

//
// Request was written
//
void request_sent(G2CRequest *rObj)

{
	// if this was a oneway, then return the rpc and remove the req
	// First create the exception object
	if (rObj->response_expected) return;
	
	// This was a oneway

	// Return the request to G2.
	gsi_item *Rets = gsi_make_items(1);
	gsi_set_sym(Rets[0], "NONE");
	gsi_rpc_return_values(Rets, 1, rObj->CallIndex, rObj->Context);
	gsi_reclaim_items(Rets);
	RequestObjs.Remove(rObj);
}



/*
 * g2orb_send_req()
 *
 * This is called by the KB to dispatch an operation to the ORB.  All operations are funneled
 * through this single procedure.  
 *
 * Input Arguments:
 *    Proxy Object as handle
 *    Name of operation.
 *	  Sequence of arguments or the symbol none
 *
 * Return Values:
 *    value: sequence of return values or symbol not-registered or location-forward or none
 *    
 * This operation is non blocking.  It will either send a oneway,
 * send defered, or return an error.
 */
void g2orb_send_req(void *proc_data, gsi_item args[], gsi_int count, void *call_index )     

{	
	if (debug_mode) printf("In Send req:\n");

	build_orb_request(args, count, call_index);
}

//
// Decode User Exception
//
int got_reply_user_exception(G2CRequest *rObj, iiop *iiopObj,
						 G2OrbContext *cObj, G2Operation *oObj) {

	char *except_name = iiopObj->decode_string();
	if (iiopObj->overrun_detected) return 1;

	G2IRObject *irObj = get_ir_object(cObj, (char *) oObj->IRObj);
	if (!irObj) return 1;
	gsi_item el = get_attr_by_name(irObj->ref, "G2ORB-EXCEPTIONS");
	if (!el) return 1;
	char **list = gsi_str_array_of(el);
	int n = gsi_element_count_of(el);
	for (int i = 0; i < n; i++) {
		G2IRObject *irObj = get_ir_object(cObj, list[i]);
		if (!irObj) return 1;
		el = get_attr_by_name(irObj->ref, "G2ORB-ABS-NAME");
		if (!el) return 1;
		char *ln = gsi_str_of(el);
		if (strcmp(ln, except_name)) continue;

		gsi_item *Itms = gsi_make_items(1);
		encodeable_exception *oAny = new encodeable_exception(Itms[0], cObj, irObj->ref, 2);

		int temp = oAny->decode(iiopObj);
		if (temp || iiopObj->overrun_detected) return 1;
		
		delete oAny;

		gsi_rpc_return_error_values(Itms, 1, rObj->CallIndex, rObj->Context);
		deep_reclaim_items(Itms,1);
		return 0;
	}
	cout << "Unknown exception: "<< except_name << " received." << endl;
	return 1;
}


//
// Got a location forward reply message
//


int got_forward_reply(G2OrbContext *cObj, G2CRequest *rObj, iiop *iiopObj)

{
	// When we get a location forward reply, we need to decode a object reference from the message
	// This works in much the same way as receiving a object reference as an argument.  However,
	// We need to update the proxy object informaion and may need to create a new connection.
	//
	// The new connection is used for all future requests.  But, if the connection is broken, then
	// future connections should be made to the original location.  This logic is done when the 
	// message is sent.


	// Find the proxy object from the handle 
	G2CObject *pObj = (G2CObject *) cObj->proxies.FindObj(rObj->ObjHandle);
	if (!pObj) return 1; 

	// Now, decode the new object reference

	// First get a binary objref
	iiop objref;
	int oldindex = iiopObj->index;
	if (do_decode_objref(&objref, iiopObj, 0)) return 1;
	iiopObj->index = oldindex;
	objref.alloc_mem();
	if (do_decode_objref(&objref, iiopObj, 1)) return 1;

	// now convert it to a string
	objref.reset();
	G2String decodedIOR;
	int type = binior2objref(objref, cObj->context_number, decodedIOR);
	if (type == -1) return 1; // error

	// Ok, we now have a text ior, we can decode the things that we need
	G2String Host;
	unsigned port_number;
	pObj->connection_id = 0; // dont use the old one anymore
	if (decodeobjref((char *) decodedIOR, Host, port_number, pObj->forwarded_object_key)) return 1;

	// Ok, now we have a new place to create a connection to, lets open up the connection
	// and be done.

	char buf[1024];
	socket_data *sdata = NULL;
	sprintf(buf, "%s:%d", (char *) Host, port_number); // there may already be a connection for this location
	socket_map *smap = (socket_map *) SocketMaps.FindObj(buf);
	if (smap) { // yep, is the socket still there?
		sdata = (socket_data *) Sockets.FindObj(smap->socket_id);
	}
	if (!sdata) { // no, we need to create a new one
		sdata = create_connection((char *) Host, port_number);
		if (!sdata) return 1; // failed
	}
	pObj->connection_id = sdata->socket_id;  // Use this connection in the future
	if (!smap) {
		smap = new socket_map; // create a new map object
		smap->target_system = buf;
		SocketMaps.Add(smap);
	}
	smap->socket_id = sdata->socket_id; // update map
	return 0; // done, ok
}



//
// Got a reply 
//
void got_request_reply(G2CRequest *rObj, iiop *iiopObj, 
					   unsigned char reply_status)

{
  if (debug_mode) {
    printf("  Interface: %s\n", (char*)rObj->Interface);
    printf("  Operation: %s\n", (char*)rObj->operation);
  }

  //  The first thing we need to do is locate the operation object.
	// We can get that from the context object to the interface object to the operation object

	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(rObj->Context);
	if (!cObj) {
		g2orb_send_rpc_return_se("INTERNAL", 0, 0, rObj->CallIndex, rObj->Context);
		cout << "Unable to find context object on operation return" << endl;
		RequestObjs.Remove(rObj);  // no longer pending.
		return;
	}
	// Find the Interface
	G2Interface *iObj = (G2Interface *) cObj->interfaces.FindObj(rObj->Interface);
	if (!iObj) {
		g2orb_send_rpc_return_se("INTERNAL", 0, 0, rObj->CallIndex, rObj->Context);
		cout << "Unable to find interface object on operation return" << endl;
		RequestObjs.Remove(rObj);  // no longer pending.
		return;
	}
	// Find the operation object
	G2Operation *oObj = got_server_find_operation((char *) rObj->operation, iObj, cObj);
	if (!oObj) {
		g2orb_send_rpc_return_se("INTERNAL", 0, 0, rObj->CallIndex, rObj->Context);
		cout << "Unable to find operation object on operation return" << endl;
		RequestObjs.Remove(rObj);  // no longer pending.
		return;
	}

	switch (reply_status) {
	case 0: {// no exception

		// Since we now use direct dispatch, we can just
		// return the values to the caller or the symbol none
		// if there are no value
		G2OrbContainer arglist(0);
		gsi_item *Rets = gsi_make_items(1);
		if (!oObj->out_values) {  // no return values
			gsi_set_sym(Rets[0], "NONE");
			gsi_rpc_return_values(Rets, 1, rObj->CallIndex, rObj->Context);
			gsi_reclaim_items(Rets);			
			RequestObjs.Remove(rObj);  // no longer pending.
			return;
		}
		gsi_item *Args = gsi_make_items(oObj->out_values);
		gsi_set_elements(Rets[0], Args, oObj->out_values, GSI_SEQUENCE_TAG);
		if (build_NVList_from_gsi(arglist, iObj, oObj, cObj, Args, 2)) {
			g2orb_send_rpc_return_se("MARSHAL",0,0, rObj->CallIndex, rObj->Context);
			cout << "Unable to parse return results" << endl;
			RequestObjs.Remove(rObj);  // no longer pending.
			deep_reclaim_items(Rets, 1);
			return;
		}
		int temp = decode_request_body(arglist, iiopObj, rObj->Context); // populate return arrays
		if (temp || iiopObj->overrun_detected) { 
			g2orb_send_rpc_return_se("MARSHAL", 0, 0, rObj->CallIndex, rObj->Context);
			cout << "Unable to parse return results" << endl;
			RequestObjs.Remove(rObj);  // no longer pending.
			deep_reclaim_items(Rets, 1);
			return;
		}
		gsi_rpc_return_values(Rets, 1, rObj->CallIndex, rObj->Context);
		deep_reclaim_items(Rets, 1);
		RequestObjs.Remove(rObj);
		break;
			}
	case 1: {// user exception
		if (got_reply_user_exception(rObj, iiopObj, cObj, oObj)) {
			g2orb_send_rpc_return_se("MARSHAL", 0, 2, rObj->CallIndex, rObj->Context);
			cout << "Unable to parse user exception" << endl;
		}
		RequestObjs.Remove(rObj);
		return;
		break;
			}
	case 2: {// system exception
		char *except_name = iiopObj->decode_string();
		convert_to_g2_symbol_string(except_name);
		unsigned long minor_code = iiopObj->decode_ulong();
		unsigned long comp_status = iiopObj->decode_ulong();
		if (iiopObj->overrun_detected) { 
			g2orb_send_rpc_return_se("MARSHAL", 0, 2, rObj->CallIndex, rObj->Context);
			cout << "Unable to parse return results" << endl;
			RequestObjs.Remove(rObj);  // no longer pending.
			return;
		}
		g2orb_send_rpc_return_se(except_name, minor_code, comp_status, rObj->CallIndex, rObj->Context);
		RequestObjs.Remove(rObj);  // no longer pending.
		cout << "System exception found in request reply: " << except_name <<
			" Code:" << minor_code << ",status:" << comp_status << endl;
		break;
			}
	case 3: {// location forward
		if (got_forward_reply(cObj, rObj, iiopObj)) {
			g2orb_send_rpc_return_se("MARSHAL", 0, 1, rObj->CallIndex, rObj->Context);
			cout << "Unable to process object forward message" << endl;
			RequestObjs.Remove(rObj);
		} else {	
			gsi_item *Itms = gsi_make_items(1);  // Create return array
			gsi_set_sym(Itms[0], "LOCATION-FORWARD");
			gsi_rpc_return_values(Itms, 1, rObj->CallIndex, rObj->Context);
			gsi_reclaim_items(Itms);
			RequestObjs.Remove(rObj);
			if (debug_mode) cout << "Got object forward" << endl;
		}
		break;
			}
	}
}

//
// This times out client requests
//


void timeout_client_req(void)

{
	for (;1;) {
		G2CRequest *rObj = (G2CRequest *) RequestObjs.GetFirst();
		if (rObj) {
			if (rObj->timeout_time) {
				if (g_current_time >= rObj->timeout_time) {
					request_failed(rObj, "NO-RESPONSE");
					cout << "Client request timed out with no response from server" << endl;
					continue; // get next one
				}
			}
		}
		break;  // if we get this far, then we are done
	}
}



