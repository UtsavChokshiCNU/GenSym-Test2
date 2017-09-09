//
// Encoding routines
//
#include <iostream_ver.h>
#include <string.h>
#include "iiop.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "corba_main.h"
#include "encoding.h"


//
// The encode routines add the encoded object to the iiop packet
//

encodeable_object::encodeable_object(gsi_item ittm) {
	itm = ittm;
}


// Short
encodeable_short::encodeable_short(gsi_item ittm):encodeable_object(ittm){
}

int encodeable_short::encode(iiop *ptr, int flag) {
	short val = 0;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_INTEGER_TAG) {
			cout << "ERROR! Expected short, but got type: " << t << endl;
			return 1;
		}
		val = (short) gsi_int_of(itm);
	}
	ptr->encode_short(val, flag);
	return 0;
}

int encodeable_short::decode(iiop *ptr) {
	short val = ptr->decode_short();
	if (ptr->overrun_detected) return 1;
	gsi_set_int(itm, (gsi_int) val);
	return 0;
}

// Unsigned Short
encodeable_ushort::encodeable_ushort(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_ushort::encode(iiop *ptr, int flag) {
	unsigned short val = 0;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_INTEGER_TAG) {
			cout << "ERROR! Expected unsigned short, but got type: " << t << endl;
			return 1;
		}
		val = (unsigned short) gsi_int_of(itm);
	}
	ptr->encode_ushort(val, flag);
	return 0;
}

int encodeable_ushort::decode(iiop *ptr) {
	unsigned short val = ptr->decode_ushort();
	if (ptr->overrun_detected) return 1;
	gsi_set_int(itm, (gsi_int) val);
	return 0;
}

// Long
encodeable_long::encodeable_long(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_long::encode(iiop *ptr, int flag) {
	long val = 0;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t == GSI_INTEGER_TAG) {
			val = (long) gsi_int_of(itm);
		} else if (t == GSI_FLOAT64_TAG) {
			val = (long) gsi_flt_of(itm);
		} else {
			cout << "ERROR! Expected long, but got type " << t << endl;
			return 1;
		}
	}
	ptr->encode_long(val, flag);
	return 0;
}

int encodeable_long::decode(iiop *ptr) {
	long val = ptr->decode_long();
	if (ptr->overrun_detected) return 1;
	if (val > MAX_G2_INTEGER || val < MIN_G2_INTEGER) {
		gsi_set_flt(itm, (double) val);
	} else 	gsi_set_int(itm, (gsi_int) val);
	return 0;
}

// Unsigned Long
encodeable_ulong::encodeable_ulong(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_ulong::encode(iiop *ptr, int flag) {
	unsigned long val = 0;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t == GSI_INTEGER_TAG) val = (unsigned long) gsi_int_of(itm);
	    else if (t == GSI_FLOAT64_TAG) val = (unsigned long) gsi_flt_of(itm);
		else {
			cout << "ERROR! Expected unsigned long, but got type " << t << endl;
			return 1;
		}
	}
	ptr->encode_ulong(val, flag);
	return 0;
}

int encodeable_ulong::decode(iiop *ptr) {
	unsigned long val = ptr->decode_ulong();
	if (ptr->overrun_detected) return 1;
	if (val > MAX_G2_INTEGER) gsi_set_flt(itm, (double) val);
	else gsi_set_int(itm, (gsi_int) val);
	return 0;
}


// Long Long
// ---------

// ==================
// Unsigned Long Long
// ==================

// Constructor
// -----------
encodeable_ullong::encodeable_ullong(gsi_item ittm):encodeable_object(ittm)
{ }

// Pack G2's representation of unsigned long long into transmission buffer
// -----------------------------------------------------------------------
int encodeable_ullong::encode(iiop *ptr, int flag)
{
    unsigned short val[4] = {0, 0, 0, 0} ;

	if (flag) 
    {
        // Array of integers?
        // ------------------
		int t = gsi_type_of(itm);
        if (t != GSI_SEQUENCE_TAG)
        {
			cout << "ERROR! Expected sequence of 4 integers (representing an unsigned long long) but got type " << t << endl;
			return 1;
        }

        // Four elements?
        // --------------
        gsi_int ct = gsi_element_count_of(itm) ;
        if (ct != 4)
        {
			cout << "ERROR! Sequence representing an unsigned long long should have 4 elements but had " << ct << " elements." << endl;
			return 1;
        }

        // Each one an integer <= 65,535?
        // ------------------------------
        gsi_item *pVal = gsi_elements_of(itm) ;

        for (int i = 0 ; i < 4 ; i++)
            if (gsi_type_of(pVal[i]) != GSI_INTEGER_TAG)
            {
                cout << "ERROR! Sequence representing an unsigned long long should consist of 4 integer.  Found type " << gsi_type_of(pVal[i]) << "." << endl ;
                return 1 ;
            }
            else if (gsi_int_of(pVal[i]) >= 65536)
            {
			    cout << "ERROR! Each element of array representing unsigned long long must be less than 65,536 (2**16)." << endl;
			    return 1;
            }
            else
                val[(ptr->little_endian)? i : (3-i)] = (unsigned short)gsi_int_of(pVal[i]) ;
	}

    // Pack the values
    // ---------------
	ptr->encode_ullong(val, flag);

	return 0;
}

// Decode the unsigned long long in the input buffer and pack it into GSI structures
// ---------------------------------------------------------------------------------
int encodeable_ullong::decode(iiop *ptr) 
{
	unsigned int val[4];

    ptr->decode_ullong(val);
	if (ptr->overrun_detected) return 1;

    // Create elements to hold each of the integers, fill them in, and link them to itm
    // --------------------------------------------------------------------------------
    gsi_item *pEl = gsi_make_items(4) ;
    for (int i=0 ; i < 4 ; i++)
        gsi_set_int(pEl[i], val[i] ) ;
    gsi_set_elements(itm, pEl, 4, GSI_SEQUENCE_TAG) ;
	return 0;
}

// =========
// Long Long
// =========

// Constructor
// -----------
encodeable_llong::encodeable_llong(gsi_item ittm):encodeable_ullong(ittm)
{ }


// Float
encodeable_float::encodeable_float(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_float::encode(iiop *ptr, int flag) {
	float val = (float) 0.0;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_FLOAT64_TAG) {
			cout << "ERROR! Expected float, but got type " << t << endl;
			return 1;
		}
		val = (float) gsi_flt_of(itm);
	}	
	ptr->encode_float(val, flag);
	return 0;
}

int encodeable_float::decode(iiop *ptr) {
	float val = ptr->decode_float();
	if (ptr->overrun_detected) return 1;
	gsi_set_flt(itm, (double) val);
	return 0;
}


// Double
encodeable_double::encodeable_double(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_double::encode(iiop *ptr, int flag) {
	double val = 0.0;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_FLOAT64_TAG) {
			cout << "ERROR! Expected type double, but got type " << t << endl;
			return 1;
		}
		val = gsi_flt_of(itm);
	}
	ptr->encode_double(val, flag);
	return 0;
}

int encodeable_double::decode(iiop *ptr) {
	double val = ptr->decode_double();
	if (ptr->overrun_detected) return 1;
	gsi_set_flt(itm, val);
	return 0;
}

// Boolean
encodeable_boolean::encodeable_boolean(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_boolean::encode(iiop *ptr, int flag) {
	gsi_int val = 0;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_LOGICAL_TAG) {
			cout << "ERROR! Expected type boolean, but got type " << t << endl;
			return 1;
		}
		val = gsi_log_of(itm);
	}
	if (val > 0) ptr->encode_oct(1, flag); // true
	else ptr->encode_oct(0,flag);	// false
	return 0;
}

int encodeable_boolean::decode(iiop *ptr) {
	unsigned char val = ptr->decode_oct();
	if (ptr->overrun_detected) return 1;
	if (val & 1) gsi_set_log(itm, 1000);  // true
	else gsi_set_log(itm, -1000);	// false
	return 0;
}


// Char
encodeable_char::encodeable_char(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_char::encode(iiop *ptr, int flag) {
	char *val = "";
	if (flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_STRING_TAG) {
			cout << "ERROR! Expected char, but got type " << t << endl;
			return 1;
		}
		val = gsi_str_of(itm);
	}
	ptr->encode_oct(val[0], flag);
	return 0;
}

int encodeable_char::decode(iiop *ptr) {
	char val[2] = "A";
	val[0] = ptr->decode_oct();
	if (ptr->overrun_detected) return 1;
	gsi_set_str(itm, val);
	return 0;
}


// Octet
encodeable_octet::encodeable_octet(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_octet::encode(iiop *ptr, int flag) {
	gsi_int val;
	if (flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_INTEGER_TAG) {
			cout << "ERROR! Expected octet, but got type " << t << endl;
			return 1;
		}
		val = gsi_int_of(itm);
	}
	ptr->encode_oct((unsigned char) val, flag);
	return 0;
}

int encodeable_octet::decode(iiop *ptr) {
	gsi_int val;
	val = ptr->decode_oct();
	if (ptr->overrun_detected) return 1;
	gsi_set_int(itm, val);
	return 0;
}



// String
encodeable_string::encodeable_string(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_string::encode(iiop *ptr, int flag) {
	char *val;
	if (!flag && gsi_type_of(itm) != GSI_STRING_TAG) {
		cout << "ERROR! Expected string, but got type " << gsi_type_of(itm) << endl;
		return 1;
	}
	val = gsi_str_of(itm);
	ptr->encode_string(val, flag);
	return 0;
}

int encodeable_string::decode(iiop *ptr) {
	char *val;
	val = ptr->decode_string();
	if (ptr->overrun_detected) return 1;
	gsi_set_str(itm, val);
	return 0;
}


// Bounded String
encodeable_stringdef::encodeable_stringdef(gsi_item ittm, gsi_item ir):encodeable_object(ittm) {
	m_def = ir;
} 


int encodeable_stringdef::encode(iiop *ptr, int flag) {

	if (!flag) {
		gsi_item el = get_attr_by_name(m_def, "G2ORB-BOUND");
		if (!el) return 1;
		int bound = gsi_int_of(el);  // get max length
		if (gsi_type_of(itm) != GSI_STRING_TAG) {
			cout << "ERROR! Expected string, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}
		m_val = gsi_str_of(itm);
		int len = strlen((char *) m_val);
		if (len > bound && bound) {
			((char *) m_val)[bound] = 0;  // truncate string
		};
	}
	ptr->encode_string((char *) m_val, flag);
	return 0;
}

int encodeable_stringdef::decode(iiop *ptr) {
	char *val;
	val = ptr->decode_string();
	if (ptr->overrun_detected) return 1;
	gsi_set_str(itm, val);
	return 0;
}


//
// Structs are implemented as a sequence of encodable objects
//
encodeable_struct::encodeable_struct(gsi_item ittm, G2OrbContext *cObj, 
									 gsi_item ir, int direction):encodeable_object(ittm) {
	m_def = ir;
	m_direction = direction;
	m_cObj = cObj;
}


int encodeable_struct::encode(iiop *ptr, int flag) {

	encodeable_object *eo;
	int temp;

	if (!flag) {
		if (gsi_type_of(itm) != GSI_STRUCTURE_TAG) {
			cout << "ERROR!  Expected structure, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}

		gsi_item el = get_attr_by_name(m_def, "G2ORB-MEMBERS");
		if (!el) return 1;
		char **list = gsi_str_array_of(el);
		int n = gsi_element_count_of(el);
		for (int i = 0; i < n; i++) {
			G2IRObject *irObj = get_ir_object(m_cObj, list[i]);
			if (!irObj) return 1;
			el = get_attr_by_name(irObj->ref, "G2ORB-ABSOLUTE-NAME");
			if (!el) return 1;
			char *member_name = gsi_sym_of(el);
			gsi_item user_attr = get_attr_by_name(itm, member_name);
			if (!user_attr) return 1;
			int dummy_count = 0;
			if (build_Any_from_gsi(irObj->ref, (void **) &user_attr,
				dummy_count, m_cObj,
				members, m_direction)) return 1;
		}
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo;
				eo = (encodeable_object *) eo->GetNext()) {
		temp = eo->encode(ptr, flag);
		if (temp) return temp;
	}
	return 0;
}


int encodeable_struct::decode(iiop *ptr) {

	encodeable_object *eo;
	int temp;

	gsi_attr el = get_attr_by_name(m_def, "G2ORB-MEMBERS");
	if (!el) return 1;
	char **list = gsi_str_array_of(el);
	int n = gsi_element_count_of(el);
	gsi_attr *userattrs = gsi_make_attrs_with_items(n);
	gsi_set_attrs(itm, userattrs, n);
	gsi_set_type(itm, GSI_STRUCTURE_TAG);

	int dummy_count = 0;
	for (int i = 0; i < n; i++) {
		G2IRObject *irObj = get_ir_object(m_cObj, list[i]);
		if (!irObj) return 1;

		el = get_attr_by_name(irObj->ref, "G2ORB-ABSOLUTE-NAME");
		if (!el) return 1;
		char *member_name = gsi_sym_of(el);
		gsi_set_attr_name(userattrs[dummy_count], member_name);

		if (build_Any_from_gsi(irObj->ref, userattrs, dummy_count, 
				m_cObj, members, m_direction)) return 1;
	}


	for (eo = (encodeable_object *) members.GetFirst(); eo;
		eo = (encodeable_object *) eo->GetNext()) {
			temp = eo->decode(ptr);
			if (temp) return temp;
	}
	return 0;
}

//
// Exceptions work the same way as structs

encodeable_exception::encodeable_exception(gsi_item ittm, 
		G2OrbContext *cObj, gsi_item ir, 
		int direction):encodeable_object(ittm) {
	m_def = ir;
	m_direction = direction;
	m_cObj = cObj;
}


int encodeable_exception::encode(iiop *ptr, int flag) {

	encodeable_object *eo;
	int temp;

	if (!flag) {

		if (gsi_type_of(itm) != 0) {
			cout << "ERROR!  Expected exception, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}

		gsi_item el = get_attr_by_name(m_def, "G2ORB-MEMBERS");
		if (!el) return 1;
		char **list = gsi_str_array_of(el);
		int n = gsi_element_count_of(el);
		for (int i = 0; i < n; i++) {
			G2IRObject *irObj = get_ir_object(m_cObj, list[i]);
			if (!irObj) return 1;
			el = get_attr_by_name(irObj->ref, "G2ORB-ABSOLUTE-NAME");
			if (!el) return 1;
			char *member_name = gsi_sym_of(el);
			gsi_item user_attr = get_attr_by_name(itm, member_name);
			if (!user_attr) return 1;
			int dummy_count = 0;
			if (build_Any_from_gsi(irObj->ref, (void **) &user_attr,
				dummy_count, m_cObj,
				members, m_direction)) return 1;
		}
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo;
				eo = (encodeable_object *) eo->GetNext()) {
		temp = eo->encode(ptr, flag);
		if (temp) return temp;
	}
	return 0;
}


int encodeable_exception::decode(iiop *ptr) {

	encodeable_object *eo;
	int temp;

	gsi_item el = get_attr_by_name(m_def, "G2ORB-ABSOLUTE-NAME");
	if (!el) return 1;
	char *class_name = gsi_sym_of(el);
	gsi_set_class_name(itm, class_name);

	el = get_attr_by_name(m_def, "G2ORB-MEMBERS");
	if (!el) return 1;
	char **list = gsi_str_array_of(el);
	int n = gsi_element_count_of(el);
	gsi_attr *userattrs = gsi_make_attrs_with_items(n+2);
	gsi_set_attrs(itm, userattrs, n+2);

	el = get_attr_by_name(m_def, "G2ORB-NAME");
	if (!el) return 1;
	char *except_name = gsi_str_of(el);
	gsi_set_attr_name(userattrs[0], "G2ORB-EXCEPTION-KIND");
	gsi_set_str(userattrs[0], except_name);

	gsi_set_attr_name(userattrs[1], "ERROR-DESCRIPTION");
	gsi_set_str(userattrs[1], except_name);

	int dummy_count = 2;
	for (int i = 0; i < n; i++) {
		G2IRObject *irObj = get_ir_object(m_cObj, list[i]);
		if (!irObj) return 1;
	
		el = get_attr_by_name(irObj->ref, "G2ORB-ABSOLUTE-NAME");
		if (!el) return 1;
		char *member_name = gsi_sym_of(el);
		gsi_set_attr_name(userattrs[dummy_count], member_name);
		
		if (build_Any_from_gsi(irObj->ref, userattrs,
			dummy_count, m_cObj,
			members, m_direction)) return 1;
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo;
			eo = (encodeable_object *) eo->GetNext()) {
		temp = eo->decode(ptr);
		if (temp) return temp;
	}
	return 0;
}


//
// Enums are coded by sending a ulong.  We implement the encodable objects
// by passing a reference to the defining object, We can then pull in the 
// value and find the position.
//

encodeable_enum::encodeable_enum(gsi_item ittm, gsi_item deff):encodeable_object(ittm) {
	m_def = deff;
}

// To encode, we have a symbol and we want to find the long value
int encodeable_enum::encode(iiop *ptr, int flag) {

	unsigned long val = 0;
	int i = 0;
	if (flag) {
		if (gsi_type_of(itm) != GSI_SYMBOL_TAG) {
			cout << "ERROR!  Expected enumerated symbol, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}

		char *sym = gsi_sym_of(itm);  // value we are looking for
		gsi_item el = gsi_attr_by_name(m_def, "G2ORB-MEMBERS"); // symbol array
		if (!el) return 1;
 		char **list = gsi_str_array_of(el);
		int n = gsi_element_count_of(el); 
		for (i = 0; i < n; i++) {
			if (!strcmp(list[i], sym)) break;
		}
		if (i == n) {
			cout << "Unable to find symbol " << sym << " in enumerated type" << endl;
			return 1;
		}
	}
	val = i;
	ptr->encode_ulong(val,flag);
	return 0;
}

int encodeable_enum::decode(iiop *ptr) {
	unsigned long val;
	val = ptr->decode_ulong();
	if (ptr->overrun_detected) return 1;
	gsi_item el = gsi_attr_by_name(m_def, "G2ORB-MEMBERS");
	if (!el) return 1;
	char **list = gsi_str_array_of(el);
	unsigned long n = gsi_element_count_of(el);
	if (val >= n) {
		cout << "Received invalid enumerated value" << endl;
		return 1;
	}
	gsi_set_sym(itm, list[val]);
	return 0;
}



//
// Unions are implemented as the descriminator and the coresponding value
//
encodeable_union::encodeable_union(gsi_item ittm, G2OrbContext *cObj,
								   gsi_item ir, int direction):encodeable_object(ittm) {
	m_cObj = cObj;
	m_ir = ir;
	m_direction = direction;
}

gsi_item encodeable_union::find_matching_union_member(gsi_item target) {

	gsi_item el = get_attr_by_name(m_ir, "G2ORB-MEMBERS");
	if (!el) return NULL;
	char **list = gsi_str_array_of(el);
	int n = gsi_element_count_of(el);
	gsi_item default_case = NULL;

	gsi_int intval = 0;
	char *strval = NULL;
	int target_type = gsi_type_of(target);
	switch (target_type) {
	case GSI_INTEGER_TAG: intval = gsi_int_of(target); break;
	case GSI_FLOAT64_TAG: intval = (gsi_int) gsi_flt_of(target); break;
	case GSI_SYMBOL_TAG:  strval = gsi_sym_of(target); break;
	case GSI_STRING_TAG:  strval = gsi_str_of(target); break; // char 
	case GSI_LOGICAL_TAG:   intval = (gsi_log_of(target) > 0); break;
	default: cout << "Invalid union switch type:" << target_type << endl;
		     return NULL;
			 break;
	}
	for (int i = 0; i < n; i++) {
		G2IRObject *irObj = get_ir_object(m_cObj, list[i]);
		if (!irObj) return NULL;
		el = get_attr_by_name(irObj->ref, "G2ORB-LABEL");
		if (!el) return NULL;
		target_type = gsi_type_of(el);
		switch (target_type) {
		case GSI_INTEGER_TAG: if (gsi_int_of(el) == intval) return irObj->ref;
							  break;
		case GSI_FLOAT64_TAG: if (((gsi_int) gsi_flt_of(el)) == intval) return irObj->ref;
							  break;
		case GSI_SYMBOL_TAG:  if (!strcmp(strval, gsi_sym_of(el))) return irObj->ref;
							  break;
		case GSI_STRING_TAG:  if (!strcmp("DEFAULT", gsi_str_of(el))) {
								default_case = irObj->ref;
								break;
							  }
							  if (!strcmp(strval, gsi_str_of(el))) return irObj->ref;
							  break;
		case GSI_LOGICAL_TAG: if (gsi_log_of(el) > 0) {
								if (intval) return irObj->ref;
							  } else {
								  if (!intval) return irObj->ref;
							  }
							  break;
		default:	  cout << "Invalid union switch type" << endl;
			          return NULL;
					  break;
		} // case
	} // for
	// if we got this far, we could not find the matching case, use the default if defined
	if (default_case) return default_case;
	return NULL;  // could not find matching union
}
		

int encodeable_union::encode(iiop *ptr, int flag) {

	encodeable_object *eo;
	int temp;
	
	// On the first pass, we need to find the matching
	// member def for the discriminant

	eo = (encodeable_object *) members.GetFirst();
	temp = eo->encode(ptr, flag);
	if (temp) return temp;

	if (!flag) {
		if (gsi_type_of(itm) != GSI_STRUCTURE_TAG) {
			cout << "ERROR!  Expected union, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}

		// Find the matching member
		gsi_item unionmemdef = find_matching_union_member(eo->itm);
		if (!unionmemdef) return 1;  // not found
		// Now find the target values
		gsi_item userval = get_attr_by_name(itm, "G2ORB-VALUE");
		if (!userval) {
			cout << "ERROR!  Unable to find value of union object." << endl;
			return 1;
		}
		int dummy_count = 0;
		if (build_Any_from_gsi(unionmemdef, &userval,  
			dummy_count, m_cObj, members, m_direction)) return 1; 
	}

	eo = (encodeable_object *) eo->GetNext();
	if (!eo) return 1;
	temp = eo->encode(ptr,flag);
	if (temp) return temp;
	return 0;
}


//
// In order to decode, we must first decode the discriminator,
// then match it to one of the union cases.  Then, we create a 
// new encodeable object to decode it.
//
int encodeable_union::decode(iiop *ptr) {

	encodeable_object *eo;
	int temp;
	
	eo = (encodeable_object *) members.GetFirst();
	temp = eo->decode(ptr);
	if (temp) return temp;
	// Ok, now it has been decoded, lets find the matching member
	gsi_item unionmemdef = find_matching_union_member(eo->itm);
	if (!unionmemdef) return 1;  // not found
	// Now find the target values
	gsi_item userval = get_attr_by_name(itm, "G2ORB-VALUE");
	if (!userval) return 1;

	int dummy_count = 0;
	G2String truetype;
	if (build_Any_from_gsi(unionmemdef, &userval,
		dummy_count, m_cObj, members, m_direction, &truetype)) return 1; 
	gsi_item member_type = get_attr_by_name(itm, "G2ORB-TYPE");
	if (!member_type) return 1;
	if (debug_mode) cout << "True type for union: " << (char *) truetype << endl;
	gsi_set_str(member_type, (char *) truetype);

	eo = (encodeable_object *) eo->GetNext();
	if (!eo) return 1;
	temp = eo->decode(ptr);
	if (temp) return temp;
	return 0;
}

//
// Object references are passed to G2 as a text object reference
//


encodeable_objref::encodeable_objref(gsi_item ittm,
                                     G2OrbContext *cObj,
                                     gsi_item ir):encodeable_object(ittm) {
	m_def = ir;
	m_cObj = cObj;
	m_purge = false;
	m_isItem = decode_top_level;  // map to item proxy or string?
}

int encodeable_objref::encode(iiop *ptr, int flag) {
	//
	// On the first pass, we parse the object reference and 
	// extract the host name, port and object key.
	//

    if (!flag) {
		
		int type = gsi_type_of(itm);
		if (type == GSI_STRING_TAG) {
			char *ior = gsi_str_of(itm);
			if (objref2binior(ior, m_objref)) return 1;
		} else if (type == GSI_NULL_TAG) {
			gsi_attr attr = gsi_attr_by_name(itm, "G2ORB-OBJECT-REF");
			if (!attr) {
				cout <<"ERROR! unable to find object reference" << endl;
				return 1;
			}
			if (gsi_type_of(attr) != GSI_STRING_TAG) {
				cout << "ERROR! Unable to decode object reference" << endl;
				return 1;
			}
			char *ior = gsi_str_of(attr);
			if (objref2binior(ior, m_objref)) return 1;

			// if this is the server side and we get a object
			// purge it

			if (m_purge) {
				HandleHolder *hObj = new HandleHolder;
				hObj->handle = gsi_handle_of(itm);
				PurgeObjects.Add(hObj);
			}


		} else {
			cout << "ERROR!  Expected object ref, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}
	}

    // g2 passes null object references as empty strings
    // so we must build one, they consist of an empty string for a type and
    // sequence of zero profiles
    if (m_objref.len == 0) {
		m_objref.index = 0; // start over
		m_objref.little_endian = 0;
		ptr->encode_string("", flag);
		ptr->encode_ulong(0, flag);
        return 0;
	}

	iiop profile;

	m_objref.index = 0; // start over
	int dir = m_objref.decode_oct(); // get direction flag
	m_objref.little_endian = dir & 1;
	char *kind = m_objref.decode_string();
	ptr->encode_string(kind, flag);
	int numprof = m_objref.decode_ulong();
	ptr->encode_ulong(numprof, flag);
	for (int i = 0;i < numprof;i++) {
		unsigned long tag = m_objref.decode_ulong();
		ptr->encode_ulong(tag, flag);
		m_objref.decode_encap_sequence(profile);
		ptr->encode_encap_sequence(&profile, flag);
	}
	return 0;
}

//
//
//
int do_decode_objref(iiop *objref, iiop *ptr, int flag)

{
	iiop profile;

	objref->encode_oct(objref->little_endian, flag);
	char *kind = ptr->decode_string();
	if (ptr->overrun_detected) return 1;
	objref->encode_string(kind, flag);
	unsigned long nprof = ptr->decode_ulong();
	if (ptr->overrun_detected) return 1;
	objref->encode_ulong(nprof, flag);
	for (unsigned i = 0; i < nprof; i++) {
		unsigned long tag = ptr->decode_ulong();
		objref->encode_ulong(tag, flag);
		ptr->decode_encap_sequence(profile);
		objref->encode_encap_sequence(&profile, flag);
		if (ptr->overrun_detected) return 1;
	}
	if (ptr->overrun_detected) return 1;
	return 0;
}



int encodeable_objref::decode(iiop *ptr) {

	iiop objref;
	char *p_iiop_host = 0;
	unsigned iiop_port = 0;
	unsigned char* p_object_key;
    int object_key_len = 0;
	char *p_object_kind = 0;

	int oldindex = ptr->index;
	if (do_decode_objref(&objref, ptr, 0)) return 1;
	ptr->index = oldindex;
	objref.alloc_mem();
	if (do_decode_objref(&objref, ptr, 1)) return 1;

	objref.reset();
	G2String decodedIOR;
	int type = binior2objrefEx(objref, m_cObj->context_number, decodedIOR,
				   &p_iiop_host, &iiop_port, &p_object_key, &object_key_len,
                   &p_object_kind);
	if (type == -1) return 1; // cant decode

	// Build a item object proxy if we are at the top level
	// otherwise, generate text.
	if (m_isItem) { // build item reference or proxy
		bool is_local = false;

		if (!strcmp(p_iiop_host, (char *) hostname) &&
			iiop_port == hostport) { 
			// object reference for this orb.  Is it this g2?
			if (object_key_len != 0) {
                //
                // NOTE: the cast to char * in the following should be replaced
                //       by modifying the 'FindObj' method
                //
				G2SObject *sObj = 
                    (G2SObject *) Objects.FindObj((char *)p_object_key);
				if (sObj) {
					if (sObj->Context == m_cObj->context_number) {
						is_local = true; // local object
					}
				}
			}
		}

		if (is_local) { // bind to a local object
			gsi_item *Attrs = gsi_make_attrs_with_items(1);
			gsi_set_class_name(itm, "G2ORB-SERVER");
			gsi_set_attr_name(Attrs[0], "G2ORB-OBJECT-NAME");
			gsi_set_str(Attrs[0], (char *) p_object_key);
			gsi_set_attr_is_identifying(Attrs[0], 1);
			gsi_set_attrs(itm, Attrs, 1);
 			gsi_set_item_reference_flag(itm, 1);
		} else {  // build the proxy object
			gsi_item *Attrs = gsi_make_attrs_with_items(2);

			// decide what the proxy class should be
			char *class_name = "G2ORB-PROXY";
			if (p_object_kind) { // try to narrow the proxy class to something useable
				char buf[4096];
				g2orb_simplify_idl_kind(buf, p_object_kind);
				G2KindMap *kmap = (G2KindMap *) m_cObj->KindMap.FindObj(buf);
				if (kmap) class_name = (char *) kmap->objectClass;
			}
			gsi_set_class_name(itm, class_name);

			gsi_set_attr_name(Attrs[0], "G2ORB-OBJECT-REF");
			gsi_set_str(Attrs[0], (char *) decodedIOR);

			gsi_set_attr_name(Attrs[1], "_G2ORB-ORB-NAME");
			gsi_set_sym(Attrs[1], (char *) m_cObj->G2Interface);

			gsi_set_attrs(itm, Attrs, 2);
		} 
	} else {    // value mapping
		gsi_set_str(itm, (char *) decodedIOR);
	}

	if (debug_mode) {
		printf("Decoded an object reference\n");
	}

    return 0;
}

encodeable_array::encodeable_array(gsi_item ittm, G2OrbContext *cObj, 
									 gsi_item ir, int direction):encodeable_object(ittm) {
	m_def = ir;
	m_direction = direction;
	m_cObj = cObj;
}


int encodeable_array::encode(iiop *ptr, int flag) {

	encodeable_object *eo;
	int temp;

	if (!flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_SEQUENCE_TAG) {
			cout << "ERROR!  Expected sequence, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}
		gsi_item el = get_attr_by_name(m_def, "G2ORB-LENGTH");
		if (!el) return 1;
		gsi_int n = gsi_int_of(el); // number of elements
		gsi_item *arr = gsi_elements_of(itm);
		if (!arr) return 1; 
		for (int i = 0; i < n; i++) {
			// add a bunch of elements to the members list
			int dummy_count = i;
			if (build_Any_from_gsi(m_def, arr,
				dummy_count, m_cObj,
				members, m_direction)) return 1;
		}
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo;
				eo = (encodeable_object *) eo->GetNext()) {
		temp = eo->encode(ptr, flag);
		if (temp) return temp;
	}
	return 0;
}


int encodeable_array::decode(iiop *ptr) {

	encodeable_object *eo;
	int temp;

	gsi_item el = get_attr_by_name(m_def, "G2ORB-LENGTH");
	if (!el) return 1;
	gsi_int n = gsi_int_of(el); // number of elements

	gsi_attr *arr = gsi_make_items(n);
	gsi_set_elements(itm, arr, n, GSI_SEQUENCE_TAG);

	for (int i = 0; i < n; i++) {
		// add a bunch of elements to the members list
		int dummy_count = i;
		if (build_Any_from_gsi(m_def, arr, 
			dummy_count, m_cObj,
			members, m_direction)) return 1;
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo;
		eo = (encodeable_object *) eo->GetNext()) {
			temp = eo->decode(ptr);
			if (temp) return temp;
	}
	return 0;
}


encodeable_sequence::encodeable_sequence(gsi_item ittm, G2OrbContext *cObj, 
									 gsi_item ir, int direction):encodeable_object(ittm) {
	m_def = ir;
	m_direction = direction;
	m_cObj = cObj;
	m_count = 0;
}


int encodeable_sequence::encode(iiop *ptr, int flag) {

	encodeable_object *eo;
	int temp;

	if (!flag) {
		int t = gsi_type_of(itm);
		if (t != GSI_SEQUENCE_TAG) {
			cout << "ERROR!  Expected sequence, but got type " << gsi_type_of(itm) << endl;
			return 1;
		}
		m_count = gsi_element_count_of(itm); // number of elements
		gsi_item el = get_attr_by_name(m_def, "G2ORB-BOUND");
		if (!el) return 1;
		gsi_int n = gsi_int_of(el);
		if (n && n < m_count) m_count = n;  // upper bound

		gsi_item *arr = gsi_elements_of(itm);
    	if (!arr && m_count) return 1;   
		for (int i = 0; i < m_count; i++) {
			// add a bunch of elements to the members list
			int dummy_count = i;
			if (build_Any_from_gsi(m_def, arr,
				dummy_count, m_cObj,
				members, m_direction)) return 1;
		}
	}
	ptr->encode_ulong(m_count, flag);  // number of elements

	for (eo = (encodeable_object *) members.GetFirst(); eo;
				eo = (encodeable_object *) eo->GetNext()) {
		temp = eo->encode(ptr, flag);
		if (temp) return temp;
	}
	return 0;
}


int encodeable_sequence::decode(iiop *ptr) {

	encodeable_object *eo;
	int temp;

	m_count = ptr->decode_ulong();		// number of elements
	if (ptr->overrun_detected) return 1;
	gsi_item el = get_attr_by_name(m_def, "G2ORB-BOUND");
	if (!el) return 1;
	gsi_int n = gsi_int_of(el);
	if (n && n < m_count) m_count = n;

	gsi_attr *arr = gsi_make_items(m_count);
	gsi_set_elements(itm, arr, m_count, GSI_SEQUENCE_TAG);

	for (int i = 0; i < m_count; i++) {
		// add a bunch of elements to the members list
		int dummy_count = i;
		if (build_Any_from_gsi(m_def, arr,
			dummy_count, m_cObj,
			members, m_direction)) return 1;
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo;
		eo = (encodeable_object *) eo->GetNext()) {
			temp = eo->decode(ptr);
			if (temp) return temp;
	}
	return 0;
}

