//
// Routines to create encodeable objects.  These map the g2orb-type-key field in a type code
// to a encodeable object
//

#include <iostream_ver.h>
#include "gsi_main_cpp.h"
#include "corba_main.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "encoding.h"
#include "orbtype.h"


int orbtype_boolean::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_boolean *oAny = new encodeable_boolean(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_short::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_short *oAny = new encodeable_short(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}


int orbtype_long::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_long *oAny = new encodeable_long(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_llong::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_llong *oAny = new encodeable_llong(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_ushort::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_ushort *oAny = new encodeable_ushort(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}


int orbtype_ulong::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_ulong *oAny = new encodeable_ulong(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_ullong::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_ullong *oAny = new encodeable_ullong(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}


int orbtype_float::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_float *oAny = new encodeable_float(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}


int orbtype_double::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_double *oAny = new encodeable_double(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}



int orbtype_char::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_char *oAny = new encodeable_char(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}


int orbtype_octet::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_octet *oAny = new encodeable_octet(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_any::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	cout << "Type Any is not yet supported" << endl;
	return 1;
}



int orbtype_typecode::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	cout << "Type typecode is not yet supported" << endl;
	return 1;
}


int orbtype_principal::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	cout << "Type principal is not yet supported" << endl;
	return 1;
}


int orbtype_objref::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_objref *oAny = new encodeable_objref(args[argIndex++],cObj, m_def);
	arglist.Add((G2OrbContained *) oAny);
	// On the server side, if we return a object, make 
	// sure that we purge it.  Otherwise, a memory leak
	// will ocurr.
	if (direction == 4) oAny->m_purge = true;
	return 0;
}



int orbtype_struct::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {
	
		encodeable_struct *oAny = new encodeable_struct(args[argIndex++], cObj, m_def, direction);
		arglist.Add((G2OrbContained *) oAny);
		return 0;
}



int orbtype_union::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {
	
		gsi_item el;

		gsi_item userunion = args[argIndex++]; // rpc object
		encodeable_union *oAny = new encodeable_union(userunion,
				cObj, m_def, direction);
		arglist.Add((G2OrbContained *) oAny);
		if (direction == 2 || direction == 3) { // incoming
			// build union object
			gsi_attr *userunionattrs = gsi_make_attrs_with_items(3);
			gsi_set_attrs(userunion, userunionattrs, 3);
			gsi_set_type(userunion, GSI_STRUCTURE_TAG);
			gsi_set_attr_name(userunionattrs[0], "G2ORB-DISCRIMINATOR");
			gsi_set_attr_name(userunionattrs[1], "G2ORB-VALUE");
			gsi_set_sym(userunionattrs[1], "NO-VALUE");
			gsi_set_attr_name(userunionattrs[2], "G2ORB-TYPE");
			// Ok, we are ready to place the discriminator
			int dummy_count = 0;
			if (build_Any_from_gsi(m_def, &userunionattrs[0], 
				dummy_count, cObj, oAny->members, direction)) return 1; 
			// Since we do not know what type to build or even
			// if we need a value or an item until we decode
			// the discrimint, then we are done for now.
		} else { // outgoing
			el = get_attr_by_name(userunion, "G2ORB-DISCRIMINATOR"); 
			if (!el) return 1;
			int dummy_count = 0;
			if (build_Any_from_gsi(m_def,&el, 
				dummy_count, cObj, oAny->members, direction)) return 1;
		}	
		return 0;
}



int orbtype_enum::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {
	
		encodeable_enum *oAny = 
			new encodeable_enum(args[argIndex++],m_def);
		arglist.Add((G2OrbContained *) oAny);
		return 0;
}


int orbtype_sequence::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_sequence *oAny = new encodeable_sequence(args[argIndex++], cObj, m_def, direction);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}


int orbtype_array::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {


	encodeable_array *oAny = new encodeable_array(args[argIndex++], cObj, m_def, direction);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_string::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_string *oAny = new encodeable_string(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_stringdef::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_stringdef *oAny = new encodeable_stringdef(args[argIndex++], m_def);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}

int orbtype_g2item::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	encodeable_g2item *oAny = new encodeable_g2item(args[argIndex++]);
	arglist.Add((G2OrbContained *) oAny);
	return 0;
}


int orbtype_alias::build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype) {

	int temp = build_Any_from_gsi(m_def, args, argIndex,
								 cObj,
								 arglist,
								 direction, truetype);
	return temp;
}

int orbtype_alias::ItemType(void) {
	
	// Get the typecode of object
	gsi_item defobj;
	defobj = get_attr_by_name(m_def, "G2ORB-ORIGINAL-TYPE");
	if (!defobj) return -1;
	char *optype = gsi_str_of(defobj);

	orbtype *tObj = (orbtype *) m_cObj->orbtypes.FindObj(optype);
	if (!tObj) {
		cout << "Unable to find definition for type:" << optype << endl;
		return 1;
	}
	
	int temp = tObj->ItemType();
	return temp;
}

orbtype* orbtype_alias::getTrueType(void) {
	// follow the alias

	gsi_item defobj;
	defobj = get_attr_by_name(m_def, "G2ORB-ORIGINAL-TYPE");
	if (!defobj) return NULL;
	char *optype = gsi_str_of(defobj);

	orbtype *tObj = (orbtype *) m_cObj->orbtypes.FindObj(optype);
	if (!tObj) {
		cout << "Unable to find definition for type:" << optype << endl;
		return NULL;
	}

	tObj = tObj->getTrueType();
	return tObj;
}


