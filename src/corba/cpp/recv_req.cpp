//
// This file contains the code to receive a server request
//
#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"
#include "G2CorbaContainer.h"
#include "encoding.h"
#include "gsi_misc_cpp.h"

void convert_to_g2_symbol_string(char *ptr)

{
	for (char *ptr1 = ptr; *ptr1; ptr1++) {
		if (*ptr1 == ' ') *ptr1 = '-';
		if (*ptr1 == '_') *ptr1 = '-';
	}
}

void convert_from_g2_symbol_string(char *ptr)

{
	for (char *ptr1 = ptr; *ptr1; ptr1++) {
		if (*ptr1 == '-') *ptr1 = '_';
	}
}


//
// Code the reply header
//
void encode_reply_header(iiop *ptr, G2SRequest *srObj, int flag)

{
	ptr->encode_ulong(0,flag);  // null context list
	ptr->encode_ulong(srObj->request_id, flag); 
	ptr->encode_ulong(srObj->reply_status, flag);
}

//
// Send a list of objects to G2 that need to be purged
//
void purge_objects(G2OrbContext *cObj)

{
	int n = PurgeObjects.Count;
	if (!n) return;  // nothing to do

	gsi_item *attrs = gsi_make_items(n);
	int i = 0;
	for (HandleHolder *hObj = (HandleHolder *) PurgeObjects.GetFirst(); hObj; hObj = (HandleHolder *) hObj->GetNext()) {
		gsi_set_handle(attrs[i], hObj->handle);
		i++;
	}
	gsi_item *Rets = gsi_make_items(1);
	gsi_set_elements(Rets[0], attrs, n, GSI_SEQUENCE_TAG);

	gsi_rpc_start(cObj->rpc_purge_handle, Rets, cObj->context_number);
	deep_reclaim_items(Rets, 1);
}


//
// Encode the request reply
//

iiop *build_request_reply_body(G2OrbContainer &arglist, G2SRequest *srObj)

{
	iiop *ptr = new iiop;
	encodeable_object *eo;

	relations_flag = 0;  // make sure this flag is reset
	encode_mesg_header(ptr, 1, 0); // Build req header
	encode_reply_header(ptr, srObj, 0);
	for (eo = (encodeable_object *) arglist.GetFirst();
		eo; eo = (encodeable_object *) eo->GetNext()) {
			if (eo->encode(ptr, 0)) return NULL;
	}
	ptr->alloc_mem();
	encode_mesg_header(ptr, 1, 1);
	encode_reply_header(ptr, srObj, 1);
	for (eo = (encodeable_object *) arglist.GetFirst();
		eo; eo = (encodeable_object *) eo->GetNext()) {
			if (eo->encode(ptr, 1)) return NULL;
	}
	update_mesg_header_size(ptr);
	return ptr;
}

//
// Build reply packet with system exception
//
iiop *build_request_reply_se(G2SRequest *srObj, char *exception, gsi_int minor, gsi_int comp_status) {

	iiop *ptr = new iiop;
	char buf[1024];


	// Build exception name
	strcpy(buf, "IDL:omg.org/CORBA/");
	strcat(buf, exception);
	srObj->reply_status = 2;  // system exception

	encode_mesg_header(ptr, 1, 0);
	encode_reply_header(ptr, srObj, 0); // system exception
	ptr->encode_string(buf, 0);
	ptr->encode_ulong(minor, 0);
	ptr->encode_ulong(comp_status, 0);

	ptr->alloc_mem();

	encode_mesg_header(ptr, 1, 1);
	encode_reply_header(ptr, srObj, 1);
	ptr->encode_string(exception, 1);
	ptr->encode_ulong(minor, 1);
	ptr->encode_ulong(comp_status, 1);

	update_mesg_header_size(ptr);
	return ptr;
}


//
// Return System exception to the client
//
void g2orb_return_server_se(G2SRequest *srObj, char *exception,
								  gsi_int minor, gsi_int comp_status)

{
	char buf[1024];  // temp string buffer
	strcpy(buf, exception);
	convert_from_g2_symbol_string(buf);
	iiop *iiopptr = build_request_reply_se(srObj, buf, minor, comp_status);
	new Write_buffer(iiopptr, srObj->connection_id);
}

void g2orb_return_server_mesg_excep(socket_data *sdata, unsigned long reqnum,
									 char *exception, gsi_int minor, gsi_int comp_status)

{
	G2SRequest srObj;
	srObj.connection_id = sdata->socket_id;
	srObj.Context = -1;
	srObj.request_id = reqnum;
	srObj.reply_status = 2;
	g2orb_return_server_se(&srObj, exception, minor, comp_status);
}
	
void g2orb_return_isa(socket_data *sdata, unsigned long reqnum, unsigned char val)

{
	iiop *ptr = new iiop;


	encode_mesg_header(ptr, 1, 0); // Build req header
	ptr->encode_ulong(0,0);  // null context list
	ptr->encode_ulong(reqnum, 0); 
	ptr->encode_ulong(0, 0);   // ok status
	ptr->encode_oct(val, 0); // return value

	ptr->alloc_mem();

	encode_mesg_header(ptr, 1, 1);
	ptr->encode_ulong(0,1);
	ptr->encode_ulong(reqnum, 1);
	ptr->encode_ulong(0, 1);
	ptr->encode_oct(val, 1);

	update_mesg_header_size(ptr);
	new Write_buffer(ptr, sdata->socket_id);
}


//
// Return a user exception
//
int return_user_exception(gsi_item ue, G2SRequest *srObj) {
	
	gsi_item el = get_attr_by_name(ue,"G2ORB-EXCEPTION-KIND");
	if (!el) return 1;
	char *except = gsi_str_of(el);
	// We have the exception name, now we need to find the exception def
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(srObj->Context);
	if (!cObj) return 1;
	// Get Interface Object
	G2Interface *iObj = (G2Interface *) cObj->interfaces.FindObj(srObj->Interface);
	if (!iObj) return 1;

	G2Operation *oObj = (G2Operation *) iObj->operations.FindObj(srObj->opname);
	if (!oObj) return 1;

	G2IRObject *irObj = get_ir_object(cObj, (char *) oObj->IRObj);
	if (!irObj) return 1;
	el = get_attr_by_name(irObj->ref, "G2ORB-EXCEPTIONS");
	if (!el) return 1;
	char **list = gsi_str_array_of(el);
	int n = gsi_element_count_of(el);
	for (int i = 0; i < n; i++) {
		G2IRObject *irObj = get_ir_object(cObj, list[i]);
		if (!irObj) return 1;
		el = get_attr_by_name(irObj->ref, "G2ORB-ABS-NAME"); // exception kind
		if (!el) return 1;
		char *ln = gsi_str_of(el);
		if (strcmp(ln, except)) continue;

		// Have definition of exception. 
		encodeable_exception *oAny = new encodeable_exception(ue, cObj, irObj->ref, 4);
		
		//  now encode it
		
		iiop *iiopptr = new iiop;
		srObj->reply_status = 1;  // user exception

		// find name for exception
		el = get_attr_by_name(irObj->ref, "G2ORB-ABS-NAME"); // full scoped name
		if (!el) return 1;
		char *full_name = gsi_str_of(el);

		encode_mesg_header(iiopptr, 1, 0);
		encode_reply_header(iiopptr, srObj, 0); 
		iiopptr->encode_string(full_name, 0);
		if (oAny->encode(iiopptr, 0)) return 1;

		iiopptr->alloc_mem();

		encode_mesg_header(iiopptr, 1, 1);
		encode_reply_header(iiopptr, srObj, 1);
		iiopptr->encode_string(full_name, 1);
		if (oAny->encode(iiopptr, 1)) return 1;

		update_mesg_header_size(iiopptr);

		new Write_buffer(iiopptr, srObj->connection_id);

		delete oAny;

		return 0;
	} // for each exception type
	return 1;  // Could not find our exception type
}


//
// Send back a system exception
//
int return_system_exception(gsi_item se, G2SRequest *srObj) {

	gsi_item el = get_attr_by_name(se,"G2ORB-EXCEPTION-KIND");
	if (!el) return 1;
	char *except = gsi_sym_of(el);

	el = get_attr_by_name(se,"G2ORB-MINOR");
	if (!el) return 1;
	gsi_int minor = gsi_int_of(el);

	el = get_attr_by_name(se, "G2ORB-COMPLETION-STATUS");
	if (!el) return 1;
	char *comp_status = gsi_sym_of(el);
	int comp_stat = 2;
	if (!strcmp(comp_status, "COMPLETED-YES")) comp_stat = 0;
	else if (!strcmp(comp_status, "COMPLETED-NO")) comp_stat = 1;
	g2orb_return_server_se(srObj, except, minor, comp_stat);
	return 0;
}


//
// Find a operation in a interface.  This will also search base interfaces.
// Returns null if not found
//

G2Operation *got_server_find_operation(char *opname, G2Interface *iObj, G2OrbContext *cObj) 

{
	G2Operation *oObj = (G2Operation *) iObj->operations.FindObj(opname);
	if (oObj) return oObj;

	// Now look in the base interfaces

	for (G2BaseInterface *base = (G2BaseInterface *) iObj->base_interfaces.GetFirst();
		base; base = (G2BaseInterface *) base->GetNext()) {
			iObj = (G2Interface *) cObj->interfaces.FindObj(base->Interface);
			if (!iObj) {
				cout << "Unable to find base interface:" << (char *) base->Interface << endl;
				return NULL;
			}
			oObj = got_server_find_operation(opname, iObj, cObj);
			return oObj;
	}
	return NULL; 
}


//
// Checks to see if the object implements a interface
//

unsigned char do_isa_test(char *test_inter, G2Interface *iObj, G2OrbContext *cObj)

{
	char *kind = (char *) iObj->kind;
	if (debug_mode) cout << "  Checking interface:" << kind << endl; 
	if (!strcmp(kind, (char *) iObj->kind)) return 1;

	// now look in base classes

	for (G2BaseInterface *base = (G2BaseInterface *) iObj->base_interfaces.GetFirst();
		base; base = (G2BaseInterface *) base->GetNext()) {
			iObj = (G2Interface *) cObj->interfaces.FindObj(base->Interface);
			if (!iObj) break;
	}
	if (debug_mode) cout <<"Isa test failed" << endl;
	return 0;
}

//
// Error handler for server functions that are called from iiop
//
void rpc_req_recv_error(void * user_data,
							   gsi_item *ErrorArgs,
							   gsi_int nArgCount,
							   void *call_identifier)

{
	cout << "Got error callback" << endl;

	// First, find the server request object


	G2SRequest *srObj = (G2SRequest *) ServReqObjs.FindObj((intptr_t) call_identifier);
	if (!srObj) {
		cout << "Unable to find Server Request Object" << endl;
		return;
	}

	if (!srObj->response_expected) {
		ServReqObjs.Remove(srObj);
		return; // nothing expected
	}

	if (nArgCount == 2) {
		cout << gsi_sym_of(ErrorArgs[0]) << ":" << gsi_str_of(ErrorArgs[1]) << endl;
		g2orb_return_server_se(srObj, "INTERNAL", 0, 0);
	} else if (nArgCount == 1) {
		char *ErrorClass = gsi_class_name_of(ErrorArgs[0]);
		if (!strcmp(ErrorClass, "G2ORB-SYSTEM-EXCEPTION")) {
			return_system_exception(ErrorArgs[0], srObj);
		} else return_user_exception(ErrorArgs[0], srObj);
	} else g2orb_return_server_se(srObj, "INTERNAL", 0, 0);
	
	ServReqObjs.Remove(srObj);
}

//
// Receiver function for returns from server routines
//
// We use direct dispatch now.  So, the return arguments
// should just be the return arguments.  There is no longer
// a need to send status informaion with it.
//

void rpc_req_recv(void *proc_data, gsi_item args[], gsi_int count, void *callindex)  

{
	if (debug_mode) cout << "Got request rpc return" << endl;

	//
	// Get hold of the server request
	//
	G2SRequest *srObj = (G2SRequest *) ServReqObjs.FindObj((intptr_t) callindex);
	if (!srObj) {
		cout << "Unable to find Server Request Object" << endl;
		return;
	}

	if (!srObj->response_expected) {
		ServReqObjs.Remove(srObj);
		return; // nothing expected
	}

	srObj->reply_status = 0; // Ok

    // Get Context Object
	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(srObj->Context);
	if (!cObj) {
		cout << "Unable to find context" << endl;
		g2orb_return_server_se(srObj, "INTERNAL", 0, 0);
		ServReqObjs.Remove(srObj);
		return;
	}

	// Get Interface Object
	G2Interface *iObj = (G2Interface *) cObj->interfaces.FindObj(srObj->Interface);
	if (!iObj) {
		cout << "Unable to find interface " << (char *) srObj->Interface << endl;
		g2orb_return_server_se(srObj, "INTERNAL", 0, 0);
		ServReqObjs.Remove(srObj);
		return;
	}

    // Get operation object
	G2Operation *oObj = got_server_find_operation((char *) srObj->opname, iObj, cObj);
	if (!oObj) {
		cout << "Unable to find operation " << (char *) srObj->opname << " in interface "
			<< (char *) srObj->Interface << endl;
		g2orb_return_server_se(srObj, "INTERNAL", 0, 0);
		ServReqObjs.Remove(srObj);
		return;
	}
	//
	// Ok, now build the gsi objects to send to G2.
	//
	PurgeObjects.Empty();
	G2OrbContainer arglist(0);
	if (build_NVList_from_gsi(arglist, iObj, oObj, cObj, args, 4)) {
		g2orb_return_server_se(srObj, "MARSHAL", 0, 0);
		cout << "Unable to parse request results" << endl;
		ServReqObjs.Remove(srObj);
		return;
	}
	iiop *iiopptr = build_request_reply_body(arglist, srObj);
	if (!iiopptr) {
		g2orb_return_server_se(srObj, "MARSHAL", 0, 0);
		cout << "Unable to parse request results" << endl;
		ServReqObjs.Remove(srObj);
		return;
	}
	purge_objects(cObj);
	new Write_buffer(iiopptr, srObj->connection_id);
	ServReqObjs.Remove(srObj);
}

#ifdef nothing
//
// gsi_simple_content_copy() does not seem to work.
// nor does gsi_misc do what I need.
// This is a simple hack to fix it
//

void copy_gsi_item(gsi_item dest, gsi_item source)

{
	gsi_clear_item(dest);	
	
	char *classname = gsi_class_name_of(source);  // fix classname
	if (classname) gsi_set_class_name(dest, classname);

	int itemType = gsi_type_of(source);
	gsi_set_type(dest, itemType);  // make the type right

	gsi_item *els = gsi_attrs_of(source);    // attributes if any
	if (els) gsi_set_attrs(dest, els, gsi_attr_count_of(source));

	char *itemname = gsi_name_of(source);
	if (itemname) gsi_set_name(dest, itemname);

	// values are a little harder, we will have a switch for each

	switch (itemType) {
	case GSI_NULL_TAG: break;
	case GSI_INTEGER_TAG: gsi_set_int(dest, gsi_int_of(source)); break;
	case GSI_SYMBOL_TAG: gsi_set_sym(dest, gsi_sym_of(source)); break;
	case GSI_STRING_TAG: gsi_set_str(dest, gsi_str_of(source)); break;
	case GSI_LOGICAL_TAG: gsi_set_log(dest, gsi_log_of(source)); break;
	case GSI_FLOAT64_TAG: gsi_set_flt(dest, gsi_flt_of(source)); break;
	case GSI_ITEM_TAG: break;
	case GSI_VALUE_TAG: break;
	case GSI_HANDLE_TAG: break;
	case GSI_QUANTITY_TAG: break;
	case GSI_UNSIGNED_SHORT_VECTOR_TAG: gsi_set_usv(dest, gsi_usv_of(source), gsi_usv_length_of(source)); break;
	case GSI_INTEGER_ARRAY_TAG: gsi_set_int_array(dest, gsi_int_array_of(source), gsi_element_count_of(source)); break;
	case GSI_SYMBOL_ARRAY_TAG: gsi_set_sym_array(dest, gsi_sym_array_of(source), gsi_element_count_of(source)); break;
	case GSI_STRING_ARRAY_TAG: gsi_set_str_array(dest, gsi_str_array_of(source), gsi_element_count_of(source)); break;
	case GSI_LOGICAL_ARRAY_TAG: gsi_set_log_array(dest, gsi_log_array_of(source), gsi_element_count_of(source)); break;
	case GSI_FLOAT64_ARRAY_TAG: gsi_set_flt_array(dest, gsi_flt_array_of(source), gsi_element_count_of(source)); break;
	case GSI_ITEM_ARRAY_TAG: 
	case GSI_VALUE_ARRAY_TAG: 
	case GSI_ITEM_OR_VALUE_ARRAY_TAG: 
	case GSI_QUANTITY_ARRAY_TAG: 
	case GSI_SEQUENCE_TAG:
	case GSI_ITEM_LIST_TAG:
	case GSI_VALUE_LIST_TAG:
	case GSI_ITEM_OR_VALUE_LIST_TAG:
	case GSI_QUANTITY_LIST_TAG:
		gsi_set_elements(dest, gsi_elements_of(source), gsi_element_count_of(source), itemType); break;
	case GSI_INTEGER_LIST_TAG: gsi_set_int_list(dest, gsi_int_list_of(source), gsi_element_count_of(source)); break;
	case GSI_SYMBOL_LIST_TAG: gsi_set_sym_list(dest, gsi_sym_list_of(source), gsi_element_count_of(source)); break;
	case GSI_STRING_LIST_TAG: gsi_set_str_list(dest, gsi_str_list_of(source), gsi_element_count_of(source)); break;
	case GSI_LOGICAL_LIST_TAG: gsi_set_log_list(dest, gsi_log_list_of(source), gsi_element_count_of(source)); break;
	case GSI_FLOAT64_LIST_TAG: gsi_set_flt_list(dest, gsi_flt_list_of(source), gsi_element_count_of(source)); break;
	case GSI_STRUCTURE_TAG: break;
	default: cout << "Unknown tag:" << itemType << endl;
	}
}

//
// Perform a update on a object.  We have to demrashal
// the arguments.  The signature is:
//   void g2_update_object(in string object_id, in g2item obj);
//
int do_system_update_object(iiop *iiopObj, unsigned long requestid, unsigned char resp_expected, socket_data *sdata)

{
	if (debug_mode) cout << "Performing update in place\n" << endl;
	gsi_item *itms = gsi_make_items(2);
	encodeable_object *eo1 = new encodeable_string(itms[0]);
	encodeable_object *eo2 = new encodeable_g2item(itms[1]);
	if (eo1->decode(iiopObj)) {deep_reclaim_items(itms,2); return -1;}
	if (eo2->decode(iiopObj)) {deep_reclaim_items(itms,2); return -1;}

	// We still need to find a object to find the context
	G2SObject *sObj = (G2SObject *) Objects.FindObj(gsi_str_of(itms[0]));
	if (!sObj) {deep_reclaim_items(itms,2); return -2;}

	gsi_set_item_reference_flag(itms[1], TRUE);
	if (debug_mode) gsirtl_display_item_or_value(itms[1], 1, 1);
	gsi_return_values(&itms[1], 1, sObj->Context);
	deep_reclaim_items(itms,2);


#ifdef nothing

	// We have the decoded data, we need the object handle
	// lets assume that the object has already been registered

	G2SObject *sObj = (G2SObject *) Objects.FindObj(gsi_str_of(itms[0]));
	if (!sObj) {gsi_reclaim_items(itms); return -2;} // cant find object handle

	// We now have a context, and object handle

	gsi_registered_item *ri = gsi_make_registered_items(1);
    gsi_item itm = gsi_item_of_registered_item(ri[0]);
	gsi_set_handle(ri[0], sObj->ObjHandle);

	copy_gsi_item(itm, itms[1]);  // copy it 

	gsi_return_values(ri, 1, sObj->Context); // send it back
	deep_reclaim_items(itms, 2); // clean up
	gsi_reclaim_registered_items(ri);
#endif

	// The update is complete.  Now return a response
	// back to the requester

	if (resp_expected) {
		G2OrbContainer arglist(0);
		G2SRequest srObj;
		srObj.request_id = requestid;
		srObj.reply_status = 0;
		iiop *iiopptr = build_request_reply_body(arglist, &srObj);
		if (!iiopptr) return -1;
		new Write_buffer(iiopptr, sdata->socket_id);
	}
	return 0;
}
#endif


//
// Convert a iiop operation name to a G2 method name
//
void convertNameToG2(char *remote_name, char *opname)
{
	if (!strncmp(opname, "_get_", 5)) {
		strcpy(remote_name, "GET-ORB-");
		strcat(remote_name, &opname[5]);
	} else if (!strncmp(opname, "_set_", 5)) {
		strcpy(remote_name, "SET-ORB-");
		strcat(remote_name, &opname[5]);
	} else {
		strcpy(remote_name, "ORB-");
		strcat(remote_name, opname);
	}
	for (char *ptr = remote_name; *ptr; ptr++) *ptr = toupper(*ptr);
}

//
// Ok, we have a request.  We need to find the target object
// and send it to G2.
//
void got_server_request(iiop *iiopObj, unsigned long requestid, 
						unsigned char resp_expected, 
						char *objectkey, char *opname, 
						char *principal, socket_data *sdata)
{

#ifdef nothing
	// Check for special G2 System object
	if (!strcmp(objectkey, "G2-System")) {
		if (!strcmp(opname, "g2_update_object")) {
			if (do_system_update_object(iiopObj, requestid, resp_expected, sdata)) {
				g2orb_return_server_mesg_excep(sdata, requestid, "INTERNAL", 0, 1);
			}
			return;
		} else {
			g2orb_return_server_mesg_excep(sdata, requestid, "INTERNAL", 0, 1);
			return;
		}
	}
#endif

	G2SObject *sObj = (G2SObject *) Objects.FindObj(objectkey);  
	if (!sObj) {  // cant find the object, invoke the locator
		if (debug_mode) cout << "Request for unknown object:" << objectkey << endl;
		call_locator(iiopObj, requestid, resp_expected, objectkey, opname, principal, sdata);
		return;
	}

	if (!(sObj->is_valid_for_connection(sdata->socket_id))) { // request came over wrong connection
		if (debug_mode) cout << "Request for private object over wrong connection:" << objectkey << endl;
		call_locator(iiopObj, requestid, resp_expected, objectkey, opname, principal, sdata);
		return;
	}

	// now that we have the server object, we can get the context
	int context = sObj->Context;
	if (debug_mode) 
		cout << "Got server object: " << sObj->ObjHandle << " Context: " << context << endl;

	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(context);
	if (!cObj) {
		cout << "Unable to find context" << endl;
		g2orb_return_server_mesg_excep(sdata, requestid, "INTERNAL", 0, 1);
		return;
	}

	if (cObj->paused) {
		cout << "Request received for paused context" << endl;
		g2orb_return_server_mesg_excep(sdata, requestid, "TRANSIENT", 0, 1);
		return;
	}
	// Get Interface Object
	G2Interface *iObj = (G2Interface *) cObj->interfaces.FindObj(sObj->Interface);
	if (!iObj) {
		cout << "Unable to find interface " << (char *) sObj->Interface
			<< " in context" << endl;
		g2orb_return_server_mesg_excep(sdata, requestid, "INTERNAL", 0, 1);
		return;
	}

	// Check for _is_a
	if (!strcmp(opname, "_is_a")) {
		char *test_inter = iiopObj->decode_string();
		if (debug_mode) cout << "Isa test for " << test_inter << endl;
		unsigned char ret = do_isa_test(test_inter, iObj, cObj);
        g2orb_return_isa(sdata, requestid, ret);
		return;
	}
		
	G2Operation *oObj = got_server_find_operation(opname, iObj, cObj);
	if (!oObj) {
		cout << "Unable to find operation " << (char *) opname << " in interface "
		<< (char *) sObj->Interface << endl;
		g2orb_return_server_mesg_excep(sdata, requestid, "INTERNAL", 0, 1);
		return;
	}

	// Special check. getIOR_ operation (get the string ior by name).
        // This method is from our corblink_daemon.idl
	// We do not look up a G2 procedure for this operation.
	// The operation is all done in the bridge.
        // Note for later: since the code is here after the object key
        // lookup. There must be a register corbalink_daemon object
        // registered. but this is the only function needed. So if we
        // automatically add a fake object at bridge init with a well known
        // object key, we can avoid the need for customer to create and
        // regisger a G2 server object.
        // (see the function getIOR_G2SO for more information)
 	if (!strcmp(opname, "getIOR_")) {
	    if (debug_mode) cout << "Intercepted getIOR request!" << endl;

	    char *g2orb_objname;
		// Get the g2orb object name of the G2 server object to look-up
		g2orb_objname = iiopObj->decode_string();

	    // Build the server request object
	    G2SRequest *srObj = new G2SRequest;
	    srObj->Context = sObj->Context;
	    srObj->request_id = requestid;
	    srObj->response_expected = resp_expected;
	    if (!server_timeout) srObj->timeout_time = 0;
	    else srObj->timeout_time = g_current_time + server_timeout;
	    srObj->Interface = sObj->Interface;
	    srObj->opname = opname;
	    srObj->connection_id = sdata->socket_id;
	    static int next_req_callindex = 1;
	    srObj->CallIndex = next_req_callindex++;
	    ServReqObjs.Add(srObj);

        // Perform the getIOR_ operation
	    getIOR_G2SO( g2orb_objname, srObj, iObj, oObj, cObj );
	}

	else {

        // No special operation
        // Ok, now build the gsi objects to send to G2.
	    // We do a direct dispatch on the method.  So, first check
	    // to see if it has already been declared
	    char remote_name[1024];
	    convertNameToG2(remote_name, opname);
        RemoteDef *dObj = (RemoteDef *) cObj->remoteDefs.FindObj(remote_name);
	    if (!dObj) {
		    dObj = new RemoteDef;
		    dObj->opName = remote_name;
		    gsi_rpc_declare_remote_with_error_handler_and_user_data(&(dObj->handle), remote_name,
			    &rpc_req_recv, &rpc_req_recv_error, NULL, oObj->in_values + 1, oObj->out_values, cObj->context_number);
		    cObj->remoteDefs.Add(dObj);
        }

	    // Do the actual argument decode
	    G2OrbContainer arglist(0);
	    gsi_item *Args = gsi_make_items(oObj->in_values + 1);
	    gsi_set_handle(Args[0], sObj->ObjHandle);
	    if (build_NVList_from_gsi(arglist, iObj, oObj, cObj, (oObj->in_values) ? (&Args[1]) : (gsi_item*)NULL, 3)) {
		    g2orb_return_server_mesg_excep(sdata, requestid, "MARSHAL", 0, 1);
		    cout << "Unable to parse request results" << endl;
		    deep_reclaim_items(Args, oObj->in_values+1);
		    return;
        }

        int  temp=0;
	    // populate return arrays
	    temp = decode_request_body(arglist, iiopObj, sObj->Context); 

	    if (temp || iiopObj->overrun_detected) {
		    g2orb_return_server_mesg_excep(sdata, requestid, "MARSHAL", 0, 1);
		    cout << "Unable to parse request results" << endl;
		    deep_reclaim_items(Args, oObj->in_values+1);
		    return;
        }

	    // Build the server request object
	    G2SRequest *srObj = new G2SRequest;
	    srObj->Context = sObj->Context;
	    srObj->request_id = requestid;
	    srObj->response_expected = resp_expected;
	    if (!server_timeout) srObj->timeout_time = 0;
	    else srObj->timeout_time = g_current_time + server_timeout;
	    srObj->Interface = sObj->Interface;
	    srObj->opname = opname;
	    srObj->connection_id = sdata->socket_id;
	    static int next_req_callindex = 1;
	    srObj->CallIndex = next_req_callindex++;
	    ServReqObjs.Add(srObj);

        // Make the remote call to G2
	    gsi_rpc_call(dObj->handle, Args, (void *) srObj->CallIndex, srObj->Context); 
	
	    deep_reclaim_items(Args, oObj->in_values + 1);
    }
}

// 
// A server request timed out.  Return an exception to the client
//

void timeout_serv_req(void)

{
	for (;1;) {
		G2SRequest *srObj = (G2SRequest *) ServReqObjs.GetFirst();
		if (srObj) {
			if (srObj->timeout_time) {
				if (g_current_time >= srObj->timeout_time) {
					g2orb_return_server_se(srObj, "NO-RESPONSE", 0, 2);
					ServReqObjs.Remove(srObj);
					cout << "Server request timed out with no response from G2" << endl;
					continue; // get next one
				}
			}
		}
		break;  // if we get this far, then we are done
	}

	for (;1;) { // now do locate requests
		G2LRequest *lObj = (G2LRequest *) LocateReqObjs.GetFirst();
		if (lObj) {
			if (lObj->timeout_time) {
				if (g_current_time >= lObj->timeout_time) {
					loc_reject_request(lObj, "NO-RESPONSE");
					LocateReqObjs.Remove(lObj);
					cout << "Locate request timed out with no response from G2" << endl;
					continue; // get next one
				}
			}
		}
		break;  // we if we this far, we are done
	}
}


/*
**  Function: getIOR_G2SO
**
**  This is a special function that is called when the client is trying to
**  get the IOR of a G2 Server object.  They call the "getIOR_" method on a
**  Corbalink_Daemon object to get the stringified IOR (In text format) of a
**  G2ORB-SERVER object by its G2ORB-OBJECT-NAME.
**  To use this function the client must compile corbalink_daemon.idl
**  and call the getIOR method in the corblink_daemon interface.
**
**  As of 4/21/2000 this mini name service feature is only experiment for
**  the 1.0 rev 2 and is not known to customers.
**
**  Although there is a standard CORBA object by naming interface it takes
**  and returns object references at this time. Because of a bug in Orbix
**  marshalling code that checks the object key in object reference passed as
**  parameters or return values for their format. But according to the CORBA
**  spec the object is opaque and only has meaning to the host ORB. Since our
**  object key does not match to Orbix format, an exception is thrown
**  whenever we pass one of our objects to be registered. So the normal
**  naming service will not work. But we know that if we pass a stringified
**  object reference the Orbix client, it can call a function to convert the
**  string into a usable object reference. So we invented this mini service
**  that gives out strings.
*/
void getIOR_G2SO( char         *g2orb_objname, //g2orb_objname attribute of the server object
                  G2SRequest   *srObj,
                  G2Interface  *iObj,    // Interface object for Corbalink_Daemon
                  G2Operation  *oObj,    // Operation object for Corbalink_Daemon
                  G2OrbContext *cObj )   // Context object for Corbalink_Daemon
{
char *result_ior;

    if (debug_mode) cout << "In getIOR_G2SO" << endl;

    // Find the G2 server object
    G2SObject *sObj = (G2SObject *) Objects.FindObj( g2orb_objname );  

    if ( sObj ) {
        // Get the Context object for it
        G2OrbContext *G2S_cObj = (G2OrbContext *) ContextObjs.FindObj(sObj->Context);
        if (!G2S_cObj) {
            cout << "Unable to find context" << endl;
            g2orb_return_server_se(srObj, "INTERNAL", 0, 0);
            ServReqObjs.Remove(srObj);
            return;
        }

        // Get Interface Object
        G2Interface *G2S_iObj = (G2Interface *) G2S_cObj->interfaces.FindObj(sObj->Interface);
        if (!G2S_iObj) {
            cout << "Unable to find interface " << (char *) srObj->Interface << endl;
            g2orb_return_server_se(srObj, "INTERNAL", 0, 0);
            ServReqObjs.Remove(srObj);
            return;
        }

        // Generate an IOR for the object
        G2String objectref;
        iiop ior;
        G2OctSeq obj_key;
        obj_key.set_buf(g2orb_objname, strlen(g2orb_objname)+1);
        genbinior( ior, (char *) G2S_iObj->kind, (char *) hostname, hostport, obj_key, 
                   (char *) G2S_cObj->hostname, G2S_cObj->g2_port, 1 );

        // Convert it to text.
        ior.index = 0; // start at begining
        int kind = binior2objref(ior, current_context, objectref);
        if (kind == -1) {
            cout << "Unable to generate object ref" << endl;
            ServReqObjs.Remove(srObj);
            return;
        }
        if (debug_mode) cout << "IOR = " << objectref.str << endl;
    
        // Prepend "IOR:" to the text string and remove from the comma ',' back
        int olen = strlen( objectref.str );
        result_ior = (char *)malloc( olen + 5 );
        char *tptr;
        tptr = result_ior;
        *tptr++ = 'I';
        *tptr++ = 'O';
        *tptr++ = 'R';
        *tptr++ = ':';

        int i = 4;
        char *srcptr;
        for ( srcptr = objectref.str; (*srcptr != ',') && (i<olen) ; srcptr++, i++ ) {
            *tptr++ = *srcptr;
        }
        *tptr = 0;
    }
    else {
        // The G2 server object was not found, set IOR to empty
        if (debug_mode) 
            cout << "Server Object: " << g2orb_objname << " not found" << endl;
        result_ior = 0;
    }

    // Build the return argument list and populate it
    PurgeObjects.Empty();
    G2OrbContainer arglist(0);

    // Take the Stringified IOR and put it into args
    gsi_item *args = gsi_make_items(1);
    gsi_set_str( args[0], result_ior );

    if (build_NVList_from_gsi(arglist, iObj, oObj, cObj, args, 4)) {
        g2orb_return_server_se(srObj, "MARSHAL", 0, 0);
        cout << "Unable to parse request results" << endl;
        ServReqObjs.Remove(srObj);
        free( result_ior );
        gsi_reclaim_items( args );
        return;
    }

    // Put arglist into the iiop
    iiop *iiopptr = build_request_reply_body(arglist, srObj);
    if (!iiopptr) {
        g2orb_return_server_se(srObj, "MARSHAL", 0, 0);
        cout << "Unable to parse request results" << endl;
        ServReqObjs.Remove(srObj);
        free( result_ior );
        gsi_reclaim_items( args );
        return;
    }

    // Write out the iiop string 
    purge_objects(cObj);
    new Write_buffer(iiopptr, srObj->connection_id);
    ServReqObjs.Remove(srObj);
    free( result_ior );
    gsi_reclaim_items( args );

    return;
}



