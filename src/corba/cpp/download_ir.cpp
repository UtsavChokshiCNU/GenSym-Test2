//
// Download IR rpc routine
//
//
// This module receives the rpc call from G2 that passes the array of IR objects from G2.
//

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
#include "gsi_misc_cpp.h"
#include "orbtype.h"

//
// release memory used by IR objects
void deep_gsi_release(gsi_item &ptr)

{
	if (!ptr) return;
	gsirtl_free_i_or_v_contents(ptr);
}

void deep_reclaim_items(gsi_item *ptr, int n) {
	if (!ptr) return;
	for (int i = 0; i < n; i++) deep_gsi_release(ptr[i]);
	gsi_reclaim_items(ptr);
}


//
// Utility function to fetch an attribute by name
//

gsi_item get_attr_by_name(gsi_item ptr, char *name)

{
	gsi_item ptr1 = gsi_attr_by_name(ptr, name);
	if (!ptr1) {
		cout << "Error! Unable to find " << name << " in object!" << endl;
	}
	return ptr1;
}

//
// Utility function to find a IR object by id and context
//
G2IRObject *get_ir_object(G2OrbContext *cObj, char *ID)

{
	G2IRObject *irObj = (G2IRObject *) cObj->IRobjs.FindObj(ID);
	if (!irObj) {
		cout << "Error!  Unable to find ID " << ID << endl;
	}
	return irObj;
}

//
// Remove any existing objects from memory.
//
void download_ir_clear_context(G2OrbContext &cObj)

{
	// run through the list of ir object and remove each one
	cout << "Removing old IR..." << flush;

	cObj.IRobjs.Empty();  // clear all of the ir objects
	cObj.orbtypes.Empty();
	cObj.remoteDefs.Empty();
	cObj.KindMap.Empty();

	// Add primitive types
	orbtype *prim;
	prim = (orbtype *) new orbtype_any;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_char;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_double;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_float;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_long;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_octet;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_principal;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_short;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_string;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_typecode;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_ulong;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_ushort;
	cObj.orbtypes.Add((G2OrbContained *) prim);
    prim = (orbtype *) new orbtype_ullong ;
    cObj.orbtypes.Add((G2OrbContained *) prim) ;
    prim = (orbtype *) new orbtype_llong ;
    cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_void;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_boolean;
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_objref(NULL, "objref"); // Base object type
	cObj.orbtypes.Add((G2OrbContained *) prim);
	prim = (orbtype *) new orbtype_g2item;
	cObj.orbtypes.Add((G2OrbContained *) prim);

	cObj.interfaces.Empty(); // remove interfaces
	deep_reclaim_items(cObj.RepositoryHead, 1);
	cout << "done" << endl;
}

//
// Create a orbtype object based on a gsi ir object
//
orbtype *download_ir_create_orbtype(gsi_item itm, G2OrbContext *cObj)

{
	gsi_item el = get_attr_by_name(itm, "G2ORB-UUID");
	if (!el) return NULL;
	char *gsi_id = gsi_str_of(el);			// Grab uuid

	char *class_name = gsi_class_name_of(itm);

	if (!strcmp(class_name, "G2ORB-STRUCTDEF")) {
		orbtype_struct *tObj = new orbtype_struct(itm, gsi_id);
		return tObj;
	} else if (!strcmp(class_name, "G2ORB-UNIONDEF")) {
		orbtype_union *tObj = new orbtype_union(itm, gsi_id);
		return tObj;
	} else if (!strcmp(class_name, "G2ORB-ENUMDEF")) {
		orbtype_enum *tObj = new orbtype_enum(itm, gsi_id);
		return tObj;
	} else if (!strcmp(class_name, "G2ORB-ALIASDEF")) {
		orbtype_alias *tObj = new orbtype_alias(itm, gsi_id, cObj);
		return tObj;
	} else if (!strcmp(class_name, "G2ORB-ARRAYDEF")) {
		orbtype_array *tObj = new orbtype_array(itm, gsi_id);
		return tObj;
	} else if (!strcmp(class_name, "G2ORB-SEQUENCEDEF")) {
		orbtype_sequence *tObj = new orbtype_sequence(itm, gsi_id);
		return tObj;
	} else if (!strcmp(class_name, "G2ORB-STRINGDEF")) {
		orbtype_stringdef *tObj = new orbtype_stringdef(itm, gsi_id);
		return tObj;
	} else if (!strcmp(class_name, "G2ORB-INTERFACEDEF")) {
		orbtype_objref *tObj = new orbtype_objref(itm, gsi_id);
		return tObj;
	} else return NULL;
}

//
// Add IR object to data structure
//

unsigned char download_ir_add_item_to_context(gsi_item itm, G2OrbContext *cObj)

{
	//  add each one to the set of IR objects for this context
	gsi_item el = get_attr_by_name(itm, "G2ORB-UUID");
	if (!el) return 1;
	char *gsi_id = gsi_str_of(el);			// Grab uuid
	G2IRObject *irObj = new G2IRObject;
	irObj->ID = gsi_id;
	irObj->ref = itm;
	cObj->IRobjs.Add(irObj);

	// Now check the type and add type definitions

	orbtype *tObj = download_ir_create_orbtype(itm, cObj);
	if (tObj) cObj->orbtypes.Add(tObj);

	return 0;
}

//
// This finds a orbtype by name.  This follows alias, if any
//
orbtype *getTrueObj(char *optype, G2OrbContext *cObj)

{
	orbtype *tObj = (orbtype *) cObj->orbtypes.FindObj(optype);
	if (!tObj) return NULL;
	tObj = tObj->getTrueType();
	return tObj;
}

//
// Determine if the type indicated by a parm or attribute is complex
//
int check_type_for_complex(gsi_item parm, G2OrbContext *cObj)

{
	gsi_item el;
	char *classname = gsi_class_name_of(parm);
	if (!strcmp(classname, "G2ORB-OPERATIONDEF")) {
		el = get_attr_by_name(parm, "G2ORB-RESULT");
	} else if (!strcmp(classname, "G2ORB-UNIONDEF")) {
		el = get_attr_by_name(parm, "G2ORB-DISCRIMINATOR-TYPE");
	} else if (!strcmp(classname, "G2ORB-ARRAYDEF")) {
		el = get_attr_by_name(parm, "G2ORB-ELEMENT-TYPE");
	} else if (!strcmp(classname, "G2ORB-SEQUENCEDEF")) {
		el = get_attr_by_name(parm, "G2ORB-ELEMENT-TYPE");
	} else {
		el = get_attr_by_name(parm, "G2ORB-TYPE");
	}
		
	if (!el) return -1;
	char *optype = gsi_str_of(el);

	orbtype *tObj = (orbtype *) cObj->orbtypes.FindObj(optype);
	if (!tObj) return -1;

	int flag = tObj->ItemType();
	return flag;
}

//
// This creates a object that holds a pointer to a orbtype.  This points to a true type and
// follows aliass, if any.
//

orbtypePtr *download_ir_create_orbtypePtr(gsi_item itm, G2OrbContext *cObj)

{
	gsi_item el;
	char *classname = gsi_class_name_of(itm);
	if (!strcmp(classname, "G2ORB-OPERATIONDEF")) {
		el = get_attr_by_name(itm, "G2ORB-RESULT");
	} else if (!strcmp(classname, "G2ORB-UNIONDEF")) {
		el = get_attr_by_name(itm, "G2ORB-DISCRIMINATOR-TYPE");
	} else if (!strcmp(classname, "G2ORB-ARRAYDEF")) {
		el = get_attr_by_name(itm, "G2ORB-ELEMENT-TYPE");
	} else if (!strcmp(classname, "G2ORB-SEQUENCEDEF")) {
		el = get_attr_by_name(itm, "G2ORB-ELEMENT-TYPE");
	} else {
		el = get_attr_by_name(itm, "G2ORB-TYPE");
	}

	if (!el) return NULL;
	orbtype *tObj = (orbtype *) getTrueObj(gsi_str_of(el), cObj);
	if (!tObj) return NULL;

	orbtypePtr *pObj = new orbtypePtr(tObj);
	return pObj;
}

//
// Find the number of in and out parms for both val and item types.  This is used 
// to build the NVList and return arrays.
//
// We are passed a gsi item for the operation object and a pointer to the operation object
//
// This also populates the inOrbTypes and outOrbTypes member of
// of the operation.  This is a performance enhancement that 
// eliminates the need to look at the IR objects at run time for
// simple operations. 
//
unsigned char find_total_parm_counts(gsi_item op, G2Operation *oObj, G2OrbContext *cObj) {

	oObj->in_values = 0;
	oObj->out_values = 0;

	int flag = check_type_for_complex(op, cObj); // result
	if (flag != 2) { // result code void?
		oObj->out_values++;
		orbtypePtr *tObj = download_ir_create_orbtypePtr(op, cObj);
		if (!tObj) return 1;
		oObj->outOrbTypes.Add(tObj);
	}
	gsi_item el = get_attr_by_name(op, "G2ORB-PARMS");
	if (!el) return 1;
	char **list = gsi_str_array_of(el); // array of object id's
	int n = gsi_element_count_of(el);
	for (int i = 0; i < n; i++) {
		G2IRObject *irObj = get_ir_object(cObj, list[i]); // get parm
		if (!irObj) return 1;
		el = get_attr_by_name(irObj->ref, "G2ORB-MODE"); // mode
		if (!el) return 1;
		char *parmdir = gsi_sym_of(el);
		flag = check_type_for_complex(irObj->ref,cObj); // parm
		if (flag == -1) return 1;
		if (flag == 2) return 1;
		if (!strcmp(parmdir, "PARAM-OUT")) {
			oObj->out_values++;
			orbtypePtr *tObj = download_ir_create_orbtypePtr(irObj->ref, cObj);
			if (!tObj) return 1;
			oObj->outOrbTypes.Add(tObj);
		} else if (!strcmp(parmdir, "PARAM-IN")) {
			oObj->in_values++;
			orbtypePtr *tObj = download_ir_create_orbtypePtr(irObj->ref, cObj);
			if (!tObj) return 1;
			oObj->inOrbTypes.Add(tObj);
		} else {
			oObj->in_values++;
			oObj->out_values++;
			orbtypePtr *tObj = download_ir_create_orbtypePtr(irObj->ref, cObj);
			if (!tObj) return 1;
			oObj->outOrbTypes.Add(tObj);
			tObj = download_ir_create_orbtypePtr(irObj->ref, cObj);
			oObj->inOrbTypes.Add(tObj);
		}
	}
	cout << "Counts:" << oObj->in_values << ":" << oObj->out_values << endl;
	return 0;
}

//
// Add ir interface to context
//
unsigned char download_ir_add_interface_to_context(gsi_item &itm, G2OrbContext *cObj)

{
	// At this point, we have a interface def.

	gsi_item el = get_attr_by_name(itm, "G2ORB-UUID");
	if (!el) return 1;
	char *gsi_id = gsi_str_of(el);
	el = get_attr_by_name(itm, "G2ORB-ABSOLUTE-NAME");
	if (!el) return 1;
	char *absname = gsi_sym_of(el);
	el = get_attr_by_name(itm, "G2ORB-ABS-NAME");
	if (!el) return 1;
	char *kind = gsi_str_of(el);
	el = get_attr_by_name(itm, "G2ORB-PROXY-NAME");
	if (!el) return 1;
	char *proxyName = gsi_sym_of(el);

    cout << "Adding Interface:" << absname << endl;

    // convert the kind field.  We throw out the version number and uppercase 
	// everthing to make the match as liberal as possible.
	char buf[4096];
	g2orb_simplify_idl_kind(buf, kind);
	G2KindMap *kmap = new G2KindMap;  // add map object
	kmap->kind = buf;
	if (proxyName) kmap->objectClass = proxyName; else kmap->objectClass = "G2ORB-PROXY";
	cObj->KindMap.Add(kmap);

	G2Interface *iObj = new G2Interface;
	iObj->interface_name = absname;
	iObj->kind = kind;		// IDL type
	iObj->IRObj = gsi_id;
	cObj->interfaces.Add(iObj);  // add to list

	
	// Each interface has a set of attributes and operations.
	// we need to run through the list and add them to the data structure

	el = get_attr_by_name(itm, "G2ORB-OPERATIONS");
	if (!el) return 1;
	char **list = gsi_str_array_of(el);
	int n = gsi_element_count_of(el);
	int i;

	for (i = 0; i < n; i++) {
		// build operation object
		G2IRObject *irObj = get_ir_object(cObj, list[i]);
		if (!irObj) return 1;
		el = get_attr_by_name(irObj->ref, "G2ORB-NAME"); // operation name
		if (!el) return 1;
		char *gsi_name = gsi_str_of(el);
		cout << "Added operation:" << gsi_name << endl;
		G2Operation *oObj = new G2Operation;
		oObj->IRObj = list[i];
		oObj->operation_name = gsi_name;
		oObj->kind = 1;
		el = get_attr_by_name(irObj->ref, "G2ORB-MODE"); // oneway?
		if (!el) return 1;
		if (!strcmp(gsi_sym_of(el),"OP-NORMAL")) oObj->isoneway = 0; else oObj->isoneway = 1;
		if (find_total_parm_counts(irObj->ref, oObj, cObj)) return 1; 
		iObj->operations.Add(oObj);  // add it to list
	}

	// now do all of the attributes and do the _get_ and _set_ operations

	el = get_attr_by_name(itm, "G2ORB-ATTRIBUTES");
	if (!el) return 1;
	list = gsi_str_array_of(el);
	n = gsi_element_count_of(el);
	for (i = 0; i < n; i++) {
		G2IRObject *irObj = get_ir_object(cObj, list[i]);
		if (!irObj) return 1;
		el = get_attr_by_name(irObj->ref, "G2ORB-NAME"); // operation name
		if (!el) return 1;
		char *gsi_name = gsi_str_of(el);
		cout << "Added attribute:" << gsi_name << endl;
		
		// add _get_A method
		char *name = new char[strlen("_get_")+strlen(gsi_name)+1];
		strcpy(name,"_get_"); strcat(name, gsi_name);
		int flag = check_type_for_complex(irObj->ref,cObj); // get
		if (flag == -1) return 1;
		G2Operation *oObj = new G2Operation;
		oObj->out_values = 1;
		oObj->in_values = 0;
		oObj->isoneway = 0;

		orbtypePtr *tObj = download_ir_create_orbtypePtr(irObj->ref, cObj);
		if (!tObj) return 1;
		oObj->outOrbTypes.Add(tObj);

		oObj->IRObj = list[i];
		oObj->operation_name = name;
		oObj->kind = 2;
		iObj->operations.Add(oObj);
		delete name;  // free memory used for building name

		// add _set_A method
		// not if readonly 
		el = get_attr_by_name(irObj->ref, "G2ORB-MODE");
		if (!strcmp(gsi_sym_of(el),"ATTR-NORMAL")) {
			name = new char[strlen("_set_")+strlen(gsi_name)+1];
			strcpy(name,"_set_"); strcat(name, gsi_name);
			flag = check_type_for_complex(irObj->ref,cObj);  // set
			if (flag == -1) return 1;
			oObj = new G2Operation;
			oObj->out_values = 0;
			oObj->in_values = 1;
			oObj->isoneway = 0;

			orbtypePtr *tObj = download_ir_create_orbtypePtr(irObj->ref, cObj);
			if (!tObj) return 1;
			oObj->inOrbTypes.Add(tObj);

			oObj->IRObj = list[i];
			oObj->operation_name = name;
			oObj->kind = 3;
			iObj->operations.Add(oObj);
			delete name;
		}
	}

	// Now run though all of the base interfaces
	el = get_attr_by_name(itm, "G2ORB-BASE-INTERFACES");
	if (!el) return 1;
	list = gsi_str_array_of(el);
	n = gsi_element_count_of(el);
	for (i = 0; i < n; i++) {
		// We get the id of each base interface and convert
		// it to an absolute interface name for this context
		G2IRObject *irObj = get_ir_object(cObj, list[i]);
		if (!irObj) return 1;
		el = get_attr_by_name(irObj->ref, "G2ORB-ABSOLUTE-NAME");
		if (!el) return 1;
		char *basename = gsi_sym_of(el);
		cout << "Adding base class:" << basename << endl;
		G2BaseInterface *base = new G2BaseInterface;
		base->Interface = basename;
		iObj->base_interfaces.Add(base);
	}

	return 0;
}



void g2orb_download_ir(void *proc_data, gsi_item args[], gsi_int count, void *call_index )     
{
  gsi_int thisContext = gsi_current_context();

	cout << "Got download ir" << endl;

	if (count != 2 || gsi_type_of(args[0]) != GSI_SYMBOL_TAG ||
		gsi_type_of(args[1]) != GSI_ITEM_LIST_TAG) { // types ok

		g2orb_return_symbol_error("INVALID-ARGS", call_index, thisContext);
		cout << "Invalid arguments to download IR objects" << endl;
		return;
	}

	//
	// Make deep copy of array;
	//
	gsi_item *ptr = gsi_make_items(1);
	gsirtl_copy_item_or_value(args[1], ptr[0]);

	cout << "done." << endl;

	//
	// Now, we need to run through each Ir object that was downloaded and update
	// the internal data structures.
	//

	// Find the context object.
	G2OrbContext *cObj;
	cObj = (G2OrbContext *) ContextObjs.FindObj(thisContext);
	if (!cObj) {
		g2orb_return_symbol_error("ERROR", call_index, thisContext);
		cout << "Unable to find context object:" << thisContext << endl;
		return;
	}

	char *G2Interface = gsi_sym_of(args[0]);
	cObj->G2Interface = G2Interface;
	download_ir_clear_context(*cObj);
	cObj->RepositoryHead = ptr; // save pointer to main array
	int n = gsi_element_count_of(ptr[0]);
	cout << "Adding " << n << " IR Blocks..." << flush;
	gsi_item *els = gsi_elements_of(ptr[0]);

	int i;
	for (i = 0; i < n; i++) { // loop over each object
		if (download_ir_add_item_to_context(els[i], cObj)) {
			g2orb_return_symbol_error("ERROR", call_index, thisContext);
			return;
		}
	}
	cout << "done." << endl;
	//
	// Now that we have a quick way to find a item given its UUID,
	// lets run through and find all of the interfaces
	//

	cout << "building interfaces...";
	for (i = 0; i < n; i++) {
		if (!strcmp(gsi_class_name_of(els[i]),"G2ORB-INTERFACEDEF")) {
			if (download_ir_add_interface_to_context(els[i], cObj)) {
				g2orb_return_symbol_error("ERROR", call_index, thisContext);
				return;
			}
		}
	}
	cout << "done." << endl;
	g2orb_return_symbol_error("SUCCESS", call_index, thisContext);
}

