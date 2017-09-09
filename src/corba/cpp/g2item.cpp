//
// This file contains the code for the G2Item object
// Since support for this type is complex, it is placed in its 
// own file rather than with the other encodeable objects
//

#include <iostream_ver.h>
#include <string.h>
#include "iiop.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "corba_main.h"
#include "encoding.h"
#include "typecodes.h"
#include "gsi_misc_cpp.h"


unsigned char relations_flag = 0;
int decoding_context = -1;
int g2item_level_deep = 0;

//
// There is a bug in gsi that reports the type of a item as 0
// This is a wrapper fuction that works around this problem
//

int get_type_of(gsi_item itm) {
	int code = gsi_type_of(itm);
	if (!code && gsi_class_name_of(itm)) code = GSI_ITEM_TAG;
	return code;
}

encodeable_g2item::encodeable_g2item(gsi_item ittm):encodeable_g2typecode(ittm)  {
}


int encodeable_g2item::encode_typecode(iiop *ptr, int flag) {
	encode_item_tk(ptr, flag);
	return 0;
}

int encodeable_g2item::decode_typecode(iiop *ptr) {
	return decode_item_tk(ptr);
}

int encodeable_g2item::encode(iiop *ptr, int flag) {
	// First, encode the class name
	char * className = gsi_class_name_of(itm);
	ptr->encode_string(className, flag);

	if (!flag) { // first time only
        if (debug_mode) {
            puts("Encoding item:");
            gsirtl_display_item_or_value(itm, 0, 1);
        }

		if (gsi_name_of(itm)) { // the object has a name
			encodeable_g2itemname *itemname = new encodeable_g2itemname(itm);
			members.Add(itemname);
		}

//		if (gsi_history_count_of(itm)) {
//			encodeable_g2history *history = new encodeable_g2history(itm);
//			members.Add(history);
//		}

		if ((gsi_type_of(itm) != GSI_NULL_TAG) ||
            (gsi_history_type_of(itm) != GSI_NULL_TAG)) { // variable or parm
			encodeable_g2itemval *itemval = new encodeable_g2itemval(itm);
			members.Add(itemval);
		}
		
		// Ok, now get each attribute
		int n = gsi_attr_count_of(itm);
		gsi_attr *attrs = gsi_attrs_of(itm);

		for (int i = 0; i < n; i++) {
			encodeable_g2attribute *attr = new encodeable_g2attribute(attrs[i]);
			members.Add(attr);
		}
	}

	// now we have all of the attributes, call the encode methods

	ptr->encode_ulong(members.Count, flag);
	for (encodeable_object *eo = (encodeable_object *) members.GetFirst();
	eo; eo = (encodeable_object *) eo->GetNext()) {
		int temp = eo->encode(ptr, flag);
		if (temp) return temp;
	}
	return 0; // ok
}


int encodeable_g2item::decode(iiop *ptr) {

	// At this point, we can decode a g2item structure
	// One catch is that we do not know how many attributes to allocate
	// But, we do know that if there are special fields, then
	// they will be first

	char *ClassName = ptr->decode_string();
	gsi_set_class_name(itm, ClassName);

	int seqCount = ptr->decode_ulong(); // number of elements in seq
	if (ptr->overrun_detected) return 1;

	encodeable_object *eo;
	int temp;
	gsi_attr *attrs = NULL;
	int num_attrs = 0;

	bool has_uuid = false;
	for (int i = 0; i < seqCount; i++) {
		char *slotName = ptr->decode_string(); // get slot name
		if (slotName[0] == '&') { // special slot
			if (slotName[1] == 'N') { // name
				eo = new encodeable_g2itemname(itm);
			} else if (slotName[1] == 'H') { // history
				eo = new encodeable_g2history(itm);
			} else if (slotName[1] == 'V') { // value
				eo = new encodeable_g2itemval(itm);
			}
		} else {
			// if we got this far, then we have a real attribute
			// if we have a real attribute, then we know that the 
			// rest of the slots will also be attributes
			// we need to allocate memory here

			if (!attrs) {
				num_attrs = seqCount - i;
				attrs = gsi_make_attrs_with_items(num_attrs);
				gsi_set_attrs(itm, attrs, num_attrs);
			}
			int index = num_attrs - seqCount + i;
			gsi_set_attr_name(attrs[index], slotName);
			if (!strcmp(slotName, "UUID")) {  // make the uuid identifiying
			    gsi_set_attr_is_identifying(attrs[index], TRUE);
				has_uuid = true;
				g2item_level_deep++;
			}
			eo = new encodeable_g2attribute(attrs[index]);
		}
		temp = eo->decode(ptr);
		delete eo;
		if (temp) return 1;
    }  // for loop

    if (!attrs) { // never had any attrs
		attrs = gsi_make_attrs_with_items(0);
		gsi_set_attrs(itm, attrs, 0);
	}

	if (has_uuid) {
		g2item_level_deep--;

        gsi_set_item_reference_flag(itm, TRUE);

        if (debug_mode) {
            printf("Decoded the following object on level: %d\n",
                g2item_level_deep);
            gsirtl_display_item_or_value(itm, 0, 1);
        }

        // gsi does not traverse references we must return each
        // embedded item that has a reference as we decode it.
        gsi_return_values(&itm, 1, decoding_context);
	}

	return 0; // ok
}


//
// Name slot
//

encodeable_g2itemname::encodeable_g2itemname(gsi_item ittm):encodeable_object(ittm) {
}

//
// The slot name is encoded here, but decoded in the g2 encodeable item 

int encodeable_g2itemname::encode(iiop *ptr, int flag) {

	ptr->encode_string("&N", flag);  // Slot name

	// Now, encode the typecode of the slot

	ptr->encode_long(3, flag);  // symbol
	ptr->encode_ulong(18, flag);  // string
	ptr->encode_ulong(0, flag);  // now bound

	// and the value
	char *itemname = gsi_name_of(itm);
	ptr->encode_string(itemname, flag);
	return 0;
}

int encodeable_g2itemname::decode(iiop *ptr) {

	// slot already decoded

	// Get typecode for unbounded string
	int code = ptr->decode_long();
	if (!code) { // null name
		gsi_set_name(itm, "");
		if (ptr->decode_long() != 3) return 1; // suck down extra word.
		ptr->decode_long();   // junk data
		return 0;
	}
	if (code != 3) return 1;
	if (ptr->decode_ulong() != 18) return 1;
	if (ptr->decode_ulong()) return 1;

	char *itemname = ptr->decode_string();
	if (ptr->overrun_detected) return 1;
	gsi_set_name(itm, itemname);  // name it

    if (debug_mode) {
        printf("Decoded the following item name: %s\n", itemname);
    }

	return 0; // ok
}

//
// Value of passed item
//
encodeable_g2itemval::encodeable_g2itemval(gsi_item ittm):encodeable_object(ittm) { eo = NULL; }

encodeable_g2itemval::~encodeable_g2itemval() {
	if (eo) delete eo;
}

int encodeable_g2itemval::encode(iiop *ptr, int flag) {
	ptr->encode_string("&V", flag);
	long code = gsi_type_of(itm);
	ptr->encode_long(code, flag);
	if (!flag) eo = new encodeable_g2any(itm, code);
	int temp = eo->encode(ptr, flag);
	return temp;
}

int encodeable_g2itemval::decode(iiop *ptr) {

	// The name is already fetched

	long code = ptr->decode_ulong();
	eo = new encodeable_g2any(itm, code);
	int temp = eo->decode(ptr);
	return temp;
}


//
// History
//

encodeable_g2history::encodeable_g2history(gsi_item ittm):encodeable_object(ittm) {
}

int encodeable_g2history::encode(iiop *ptr, int flag) {
	return 1; // fail, not implemented
}

int encodeable_g2history::decode(iiop *ptr) {
	return 1;  // fail,  not implemented
}

//
// Attribute
//

encodeable_g2attribute::encodeable_g2attribute(gsi_attr attr):
   encodeable_object((gsi_item)attr) {
	eo = NULL;
}


encodeable_g2attribute::~encodeable_g2attribute() {
	if (eo) delete eo;
}


int encodeable_g2attribute::encode(iiop *ptr, int flag) {

    // note: the member itm is really an attribute

	// attributes have a name and a any slot value

	// first, encode the name

	char *attrName = gsi_attr_name_of(itm);
	ptr->encode_string(attrName, flag);

	unsigned char first_relation = 0;

	long code = get_type_of(itm);
	if (gsi_class_name_of(itm)) code = GSI_ITEM_TAG; // if it has a class name, it is a item

	// if we are already in a relationship, do not continue on, instead generate a null relationship
	if (!strcmp(attrName, "RELATIONSHIPS")) {
		if (relations_flag) code = GSI_NULL_RELATION_TAG;
		else {
			relations_flag = 1;
			first_relation = 1;
		}
	}

	ptr->encode_long(code, flag);
    // when creating an encodeable item we must pass the item of
    //   attribute
	if (!flag) eo = new encodeable_g2any(gsi_item_of_attr(itm), code);
	int temp = eo->encode(ptr, flag);

	if (first_relation) relations_flag = 0;  // top of tree, reset flag
	return temp;
}

int encodeable_g2attribute::decode(iiop *ptr) {

    // note: the member itm is really an attribute

    // The name is already fetched

	long code = ptr->decode_ulong();
    // when creating an encodeable item we must pass the item of
    //   attribute
	eo = new encodeable_g2any(gsi_item_of_attr(itm), code);
	int temp = eo->decode(ptr);
	return temp;
}


//
// G2any's  These are a subset of any objects 
//


//
// Create a g2 encodable type based on a typecode
//
encodeable_g2typecode * encodeable_g2any::make_g2encodeable_from_type(int code) {

	encodeable_g2typecode *eo = NULL;

	switch (code) {
		case GSI_NULL_TAG: eo = new encodeable_g2null(itm); break;
		case GSI_INTEGER_TAG: eo = new encodeable_g2integer(itm); break;
		case GSI_SYMBOL_TAG: eo = new encodeable_g2symbol(itm); break;
		case GSI_STRING_TAG: eo = new encodeable_g2string(itm); break;
		case GSI_LOGICAL_TAG: eo = new encodeable_g2logical(itm); break;
		case GSI_FLOAT64_TAG: eo = new encodeable_g2float(itm); break;
		case GSI_ITEM_TAG: eo = new encodeable_g2item(itm); break;
		case GSI_INTEGER_ARRAY_TAG: eo = new encodeable_g2integerarray(itm); break;
		case GSI_SYMBOL_ARRAY_TAG: eo = new encodeable_g2symbolarray(itm); break;
		case GSI_STRING_ARRAY_TAG: eo = new encodeable_g2stringarray(itm); break;
		case GSI_LOGICAL_ARRAY_TAG: eo = new encodeable_g2logicalarray(itm); break;
		case GSI_FLOAT64_ARRAY_TAG: eo = new encodeable_g2floatarray(itm); break;
		case GSI_ITEM_ARRAY_TAG: eo = new encodeable_g2itemarray(itm); break;
		case GSI_VALUE_ARRAY_TAG: eo = new encodeable_g2valuearray(itm); break;
		case GSI_ITEM_OR_VALUE_ARRAY_TAG: eo = new encodeable_g2itemorvaluearray(itm); break;
		case GSI_QUANTITY_ARRAY_TAG: eo = new encodeable_g2quantityarray(itm); break;
		case GSI_INTEGER_LIST_TAG: eo = new encodeable_g2integerlist(itm); break;
		case GSI_SYMBOL_LIST_TAG: eo = new encodeable_g2symbollist(itm); break;
		case GSI_STRING_LIST_TAG: eo = new encodeable_g2stringlist(itm); break;
		case GSI_LOGICAL_LIST_TAG: eo = new encodeable_g2logicallist(itm); break;
		case GSI_FLOAT64_LIST_TAG: eo = new encodeable_g2floatlist(itm); break;
		case GSI_ITEM_LIST_TAG: eo = new encodeable_g2itemlist(itm); break;
		case GSI_VALUE_LIST_TAG: eo = new encodeable_g2valuelist(itm); break;
		case GSI_ITEM_OR_VALUE_LIST_TAG: eo = new encodeable_g2itemorvaluelist(itm); break;
		case GSI_QUANTITY_LIST_TAG: eo = new encodeable_g2quantitylist(itm); break;
		case GSI_SEQUENCE_TAG: eo = new encodeable_g2sequence(itm); break;
		case GSI_STRUCTURE_TAG: eo = new encodeable_g2structure(itm); break;
		case GSI_UNSIGNED_SHORT_VECTOR_TAG: eo = new encodeable_g2usv(itm); break;
		case GSI_NULL_RELATION_TAG: eo = new encodeable_g2nullrelation(itm); break;
		default:
			cout << "Unable to build encodeable object for type:" << code << endl;
	} // case
	return eo;
}

encodeable_g2any::encodeable_g2any(gsi_item ittm, long code):encodeable_object(ittm) {
	eo = NULL;
	mCode = code;
    eo = make_g2encodeable_from_type(code);
}

encodeable_g2any::~encodeable_g2any() {
	if (eo) delete eo;
}

//
// These methods send the typecode for each G2 type
//

//
// This routine consumes an alias if any
//
int encodeable_g2typecode::fetch_tk(iiop *ptr) {
	if (ptr->overrun_detected) return -1;
	long code = ptr->decode_long();
	if (code == TK_ALIAS) {
		iiop tk;
		if (fetch_encap(ptr, tk)) return -1;
		tk.decode_string();  // repository id
		tk.decode_string();  // name
		code = fetch_tk(&tk);
	}
	return code;
}

int encodeable_g2typecode::fetch_encap(iiop *ptr, iiop &tk) {

	ptr->decode_encap_sequence(tk);
	if (ptr->overrun_detected) return 1;
	tk.little_endian = (tk.decode_oct() & 1);

  if (debug_mode) {
    printf("  Decoded %s typecode encapsulation of %d bytes\n",
       tk.little_endian ? "little endian" : "big endian", tk.len);
  }

	return 0;
}

void encodeable_g2typecode::encode_integer_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_LONG, flag);  // long
}

int encodeable_g2typecode::decode_integer_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_LONG) return 1;
	return 0;
}


void encodeable_g2typecode::encode_symbol_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_STRING, flag);  // string
	ptr->encode_long(64, flag);  // bounded
}

int encodeable_g2typecode::decode_symbol_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_STRING) return 1;
	ptr->decode_long();
	return 0;
}


void encodeable_g2typecode::encode_string_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_STRING, flag);
	ptr->encode_long(0, flag); // no bound
}

int encodeable_g2typecode::decode_string_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_STRING) return 1;
	ptr->decode_long();
	return 0;
}

void encodeable_g2typecode::encode_logical_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_BOOLEAN, flag);
}

int encodeable_g2typecode::decode_logical_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_BOOLEAN) return 1;
	return 0;
}

void encodeable_g2typecode::encode_float_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_DOUBLE, flag);
}

int encodeable_g2typecode::decode_float_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_DOUBLE) return 1;
	return 0;
}

void encodeable_g2typecode::encode_item_tk(iiop *ptr, int flag) {  // 100 
	ptr->encode_long(TK_STRUCT, flag);
	long indexLen = ptr->pre_encode_len(flag);
	//ptr->encode_long(92, flag);
	ptr->encode_oct(ptr->little_endian, flag);
	ptr->encode_string("IDL:G2/G2Item:1.0", flag);   // repository ID
	ptr->encode_string("G2Item", flag);   // name
	ptr->encode_ulong(2, flag); // two members

	ptr->encode_string("ClassName", flag); // Class name
	ptr->encode_ulong(TK_STRING, flag); 
	ptr->encode_ulong(0, flag);  // unbounded string

	ptr->encode_string("Attributes", flag);  // attributes
	ptr->encode_ulong(TK_SEQUENCE, flag); 
	long lenIndex2 = ptr->pre_encode_len(flag);
	ptr->encode_oct(ptr->little_endian, flag);
	encode_g2attribute_tk(ptr, flag);	// 52
	ptr->encode_ulong(0, flag);  // no bound to sequence
	ptr->post_encode_len(lenIndex2, flag);
	ptr->post_encode_len(indexLen, flag);
}

int encodeable_g2typecode::decode_item_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_STRUCT) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	tk.decode_string(); // rep id
	tk.decode_string(); // name
	if (tk.decode_long() != 2) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_STRING) return 1;
	if (tk.decode_long() != 0) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_SEQUENCE) return 1;
	iiop tk2;
	if (fetch_encap(&tk, tk2)) return 1;
	if (decode_g2attribute_tk(&tk2)) return 1;
	tk2.decode_long();
#endif

    return 0;
}


void encodeable_g2typecode::encode_integer_seq_tk(iiop *ptr, int flag) {
	  ptr->encode_long(TK_SEQUENCE, flag);
	  ptr->encode_long(12, flag);  // 12 byte encap
	  ptr->encode_oct(ptr->little_endian, flag);
	  ptr->encode_long(TK_LONG, flag);
	  ptr->encode_long(0, flag);
}

int encodeable_g2typecode::decode_integer_seq_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (fetch_encap(ptr, tk)) return 1;
	if (fetch_tk(&tk) != TK_LONG) return 1;
	tk.decode_long();
#endif
    
    return 0;
}

void encodeable_g2typecode::encode_symbol_seq_tk(iiop *ptr, int flag) {
	  ptr->encode_long(TK_SEQUENCE, flag);
	  ptr->encode_long(16, flag);  // 12 byte encap
	  ptr->encode_oct(ptr->little_endian, flag);
	  ptr->encode_long(TK_STRING, flag);
	  ptr->encode_long(64, flag);
	  ptr->encode_long(0, flag);
}

int encodeable_g2typecode::decode_symbol_seq_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (fetch_tk(&tk) != TK_STRING) return 1;
	tk.decode_long();
	tk.decode_long();
#endif

	return 0;
}

void encodeable_g2typecode::encode_string_seq_tk(iiop *ptr, int flag) {
	  ptr->encode_long(TK_SEQUENCE, flag);
	  ptr->encode_long(16, flag);  // 12 byte encap
	  ptr->encode_oct(ptr->little_endian, flag);
	  ptr->encode_long(TK_STRING, flag);
	  ptr->encode_long(0, flag);
	  ptr->encode_long(0, flag);
}

int encodeable_g2typecode::decode_string_seq_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (fetch_tk(&tk) != TK_STRING) return 1;
	tk.decode_long();
	tk.decode_long();
#endif
    
    return 0;
}

void encodeable_g2typecode::encode_logical_seq_tk(iiop *ptr, int flag) {
	  ptr->encode_long(TK_SEQUENCE, flag);
	  ptr->encode_long(12, flag);  // 12 byte encap
	  ptr->encode_oct(ptr->little_endian, flag);
	  ptr->encode_long(TK_BOOLEAN, flag);
	  ptr->encode_long(0, flag);
}

int encodeable_g2typecode::decode_logical_seq_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (fetch_tk(&tk) != TK_BOOLEAN) return 1;
	tk.decode_long();
#endif
    
    return 0;
}


void encodeable_g2typecode::encode_float_seq_tk(iiop *ptr, int flag) {
	  ptr->encode_long(TK_SEQUENCE, flag);
	  ptr->encode_long(12, flag);  // 12 byte encap
	  ptr->encode_oct(ptr->little_endian, flag);
	  ptr->encode_long(TK_DOUBLE, flag);
	  ptr->encode_long(0, flag);
}

int encodeable_g2typecode::decode_float_seq_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (fetch_tk(&tk) != TK_DOUBLE) return 1;
	tk.decode_long();
#endif
    
    return 0;
}

void encodeable_g2typecode::encode_item_seq_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_SEQUENCE, flag);
	long lenIndex = ptr->pre_encode_len(flag);
	// ptr->encode_long(108, flag); 
	ptr->encode_oct(ptr->little_endian, flag);
	encode_item_tk(ptr, flag);
	ptr->encode_long(0, flag);
	ptr->post_encode_len(lenIndex, flag);
}

int encodeable_g2typecode::decode_item_seq_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (decode_item_tk(&tk)) return 1;
	tk.decode_long();
#endif
    
    return 0;
}

void encodeable_g2typecode::encode_seq_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_SEQUENCE, flag);
	long lenIndex = ptr->pre_encode_len(flag);
//	ptr->encode_long(48, flag);  
	ptr->encode_oct(ptr->little_endian, flag);
	encode_g2sequencemember_tk(ptr, flag);
	ptr->encode_long(0, flag);
	ptr->post_encode_len(lenIndex, flag);
}

int encodeable_g2typecode::decode_seq_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (decode_g2sequencemember_tk(&tk)) return 1;
    tk.decode_long();
#endif

    return 0;
}

void encodeable_g2typecode::encode_structure_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_SEQUENCE, flag);
	long lenIndex = ptr->pre_encode_len(flag);
	// ptr->encode_long(60, flag); 
	ptr->encode_oct(ptr->little_endian, flag);
	encode_g2structuremember_tk(ptr, flag);
	ptr->encode_long(0, flag);
	ptr->post_encode_len(lenIndex, flag);
}

int encodeable_g2typecode::decode_structure_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (decode_g2structuremember_tk(&tk)) return 1;
	tk.decode_long();
#endif

    return 0;
}

void encodeable_g2typecode::encode_usv_tk(iiop *ptr, int flag) {
	ptr->encode_long(TK_SEQUENCE, flag);
	ptr->encode_long(12, flag);  // 12 byte encap
	ptr->encode_oct(ptr->little_endian, flag);
	ptr->encode_long(TK_SHORT, flag);
	ptr->encode_long(0, flag);
}

int encodeable_g2typecode::decode_usv_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_SEQUENCE) return 1;

	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	if (fetch_tk(&tk) != TK_SHORT) return 1;
	tk.decode_long();
#endif
    
    return 0;
}
	
void encodeable_g2typecode::encode_g2attribute_tk(iiop *ptr, int flag) { // 52
	
	ptr->encode_ulong(TK_STRUCT, flag);  // g2 attribute structure
	long lenIndex = ptr->pre_encode_len(flag);
	ptr->encode_oct(ptr->little_endian, flag);

	ptr->encode_string("IDL:G2/G2Attribute:1.0", flag); // repository ID
	ptr->encode_string("G2Attribute", flag); // name
	ptr->encode_ulong(3, flag);  // three members

	ptr->encode_string("AttributeName", flag); // attribute name
	ptr->encode_ulong(TK_STRING, flag); 
	ptr->encode_ulong(0, flag); // unbounded string

	ptr->encode_string("TagValue", flag); // tag value
	ptr->encode_ulong(TK_LONG, flag); 

	ptr->encode_string("AttributeValue", flag); // attribute value
	ptr->encode_ulong(TK_ANY, flag);
	ptr->post_encode_len(lenIndex, flag);
}

int encodeable_g2typecode::decode_g2attribute_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_STRUCT) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1; 

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	tk.decode_string();
	tk.decode_string();
	if (tk.decode_long() != 3) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_STRING) return 1;
	tk.decode_long();

	tk.decode_string();
	if (fetch_tk(&tk) != TK_LONG) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_ANY) return 1;
#endif
    
    return 0;
}


void encodeable_g2typecode::encode_g2structuremember_tk(iiop *ptr, int flag) {  // 52

	ptr->encode_ulong(TK_STRUCT, flag);
	long lenIndex = ptr->pre_encode_len(flag);
	//ptr->encode_long(44, flag);
	ptr->encode_oct(ptr->little_endian, flag);
	ptr->encode_string("IDL:G2/G2StructureMember:1.0", flag); // repository ID
	ptr->encode_string("G2StructureMember", flag); // name
	ptr->encode_ulong(3, flag);  // three members

	ptr->encode_string("MemberName", flag); // member name
	ptr->encode_ulong(TK_STRING, flag);
	ptr->encode_ulong(0, flag); // unbounded string

	ptr->encode_string("TagValue", flag); // tag value
	ptr->encode_ulong(TK_LONG, flag); 

	ptr->encode_string("MemberValue", flag); // attribute value
	ptr->encode_ulong(TK_ANY, flag);
	ptr->post_encode_len(lenIndex, flag);
}

int encodeable_g2typecode::decode_g2structuremember_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_STRUCT) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	tk.decode_string();
	tk.decode_string();
	if (tk.decode_long() != 3) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_STRING) return 1;
	tk.decode_long();

	tk.decode_string();
	if (fetch_tk(&tk) != TK_LONG) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_ANY) return 1;
#endif

	return 0;
}

void encodeable_g2typecode::encode_g2sequencemember_tk(iiop *ptr, int flag) { // 40

	ptr->encode_ulong(TK_STRUCT, flag);
	long indexLen = ptr->pre_encode_len(flag);
	//ptr->encode_long(32, flag);
	ptr->encode_oct(ptr->little_endian, flag);
	ptr->encode_string("IDL:G2/G2SequenceMember:1.0", flag); // repository ID
	ptr->encode_string("G2SequenceMember", flag); // name
	ptr->encode_ulong(2, flag);  // three members

	ptr->encode_string("TagValue", flag); // tag value
	ptr->encode_ulong(TK_LONG, flag); 

	ptr->encode_string("SequenceValue", flag); // attribute value
	ptr->encode_ulong(TK_ANY, flag);
	ptr->post_encode_len(indexLen, flag);
}

int encodeable_g2typecode::decode_g2sequencemember_tk(iiop *ptr) {
	if (fetch_tk(ptr) != TK_STRUCT) return 1;
	iiop tk;
	if (fetch_encap(ptr, tk)) return 1;

#ifdef revert // to avoid messy indirection code we will not do any
              //  extra checking
	tk.decode_string();
	tk.decode_string();
	if (tk.decode_long() != 2) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_LONG) return 1;

	tk.decode_string();
	if (fetch_tk(&tk) != TK_ANY) return 1;
#endif
    
    return 0;
}

//
// This takes a type that has elements and builds a sequence to be coded.

void encodeable_g2typecode::build_sequence_from_elements(void) {
	int n = gsi_element_count_of(itm);
	gsi_item *els = gsi_elements_of(itm);
	for (int i = 0; i < n; i++) {
		encodeable_g2any *eo = new encodeable_g2any(els[i], get_type_of(els[i]));
		members.Add(eo);
	}
}

void encodeable_g2typecode::encode_members(iiop *ptr, int flag) {

	encodeable_g2any *eo;

	ptr->encode_ulong(members.Count, flag);
	for (eo = (encodeable_g2any *) members.GetFirst(); eo; eo = (encodeable_g2any *) eo->GetNext()) {

		ptr->encode_ulong(eo->mCode, flag);
		eo->encode(ptr, flag);
	}
}



int encodeable_g2any::encode(iiop *ptr, int flag) {

	int temp;
	
	temp = eo->encode_typecode(ptr, flag);  // send typecode
	if (temp) return temp;
	temp = eo->encode(ptr, flag); // do the actual code
	return temp;
}

int encodeable_g2any::decode(iiop *ptr) {

	int temp = eo->decode_typecode(ptr);
	if (temp) {
		cout << "Unexpected or invalid typecode received" << endl;
		return 1;
	}
	if (ptr->overrun_detected) return 1;
	temp = eo->decode(ptr);  // get the actual value
	return temp;
}


//
// Individual classes for g2 objects
//

// Null

encodeable_g2null::encodeable_g2null(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2null::encode_typecode(iiop *ptr, int flag) {
	encode_integer_tk(ptr, flag);
	return 0;
}

int encodeable_g2null::decode_typecode(iiop *ptr) {
	return decode_integer_tk(ptr);
}

int encodeable_g2null::encode(iiop *ptr, int flag) {
	if (gsi_is_item(itm)) {
		ptr->encode_long(gsi_history_type_of(itm), flag);
	} else {
		ptr->encode_long(0, flag);
	}
	return 0;
}

int encodeable_g2null::decode(iiop *ptr) {
    ptr->decode_long();

    if (debug_mode) {
        printf("Decoded a g2 null\n");
    }

	return 0;
}




// Integer
encodeable_g2integer::encodeable_g2integer(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2integer::encode_typecode(iiop *ptr, int flag) {
	encode_integer_tk(ptr, flag);
	return 0;
}

int encodeable_g2integer::decode_typecode(iiop *ptr) {
	return decode_integer_tk(ptr);
}

int encodeable_g2integer::encode(iiop *ptr, int flag) {
	ptr->encode_long(gsi_int_of(itm), flag);
	return 0;
}

int encodeable_g2integer::decode(iiop *ptr) {
    long value;

    value = ptr->decode_long();
	gsi_set_int(itm, value);

    if (debug_mode) {
        printf("Decoded a g2 integer: %ld\n", value);
    }

	return 0;
}



// Symbol
encodeable_g2symbol::encodeable_g2symbol(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2symbol::encode_typecode(iiop *ptr, int flag) {
	encode_symbol_tk(ptr, flag);
	return 0;
}

int encodeable_g2symbol::decode_typecode(iiop *ptr) {
	return decode_symbol_tk(ptr);
}

int encodeable_g2symbol::encode(iiop *ptr, int flag) {
	ptr->encode_string(gsi_sym_of(itm),flag);
	return 0;
}

int encodeable_g2symbol::decode(iiop *ptr) {
    char* value;

    value =  ptr->decode_string();

    gsi_set_sym(itm, value);

    if (debug_mode) {
        printf("Decoded a g2 symbol: %s\n", value);
    }

	return 0;
}

// null relationship used to stop recursion in relations
// this just sends the symbol none

encodeable_g2nullrelation::encodeable_g2nullrelation(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2nullrelation::encode_typecode(iiop *ptr, int flag) {
	encode_symbol_tk(ptr, flag);
	return 0;
}

int encodeable_g2nullrelation::decode_typecode(iiop *ptr) {
	return decode_symbol_tk(ptr);
}

int encodeable_g2nullrelation::encode(iiop *ptr, int flag) {
	ptr->encode_string("NONE",flag);
	return 0;
}

int encodeable_g2nullrelation::decode(iiop *ptr) {  // should never be called
    char* value;

    value = ptr->decode_string();
	gsi_set_sym(itm, value);

    if (debug_mode) {
        printf("Decoded a g2 null relation: %s\n", value);
    }

	return 0;
}



// String
encodeable_g2string::encodeable_g2string(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2string::encode_typecode(iiop *ptr, int flag) {
	encode_string_tk(ptr, flag);
	return 0;
}

int encodeable_g2string::decode_typecode(iiop *ptr) {
	return decode_string_tk(ptr);
}

int encodeable_g2string::encode(iiop *ptr, int flag) {
	ptr->encode_string(gsi_str_of(itm), flag);
	return 0;
}

int encodeable_g2string::decode(iiop *ptr) {
    char* value;

    value = ptr->decode_string();
	gsi_set_str(itm, value);

    if (debug_mode) {
        printf("Decoded a g2 string: %s\n", value);
    }

    return 0;
}

// Logical
encodeable_g2logical::encodeable_g2logical(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2logical::encode_typecode(iiop *ptr, int flag) {
	encode_logical_tk(ptr, flag);
	return 0;
}

int encodeable_g2logical::decode_typecode(iiop *ptr) {
	return decode_logical_tk(ptr);
}

int encodeable_g2logical::encode(iiop *ptr, int flag) {
	ptr->encode_oct((gsi_log_of(itm) >= 0) ? 1 : 0, flag);
	return 0;
}

int encodeable_g2logical::decode(iiop *ptr) {
    long value;

    value = (ptr->decode_oct() & 1) ? 1000 : -1000;
	gsi_set_log(itm, value);

    if (debug_mode) {
        printf("Decoded a g2 logical: %ld\n", value);
    }

	return 0;
}


// Float
encodeable_g2float::encodeable_g2float(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2float::encode_typecode(iiop *ptr, int flag) {
	encode_float_tk(ptr, flag);
	return 0;
}

int encodeable_g2float::decode_typecode(iiop *ptr) {
	return decode_float_tk(ptr);
}

int encodeable_g2float::encode(iiop *ptr, int flag) {
	ptr->encode_double(gsi_flt_of(itm), flag);
	return 0;
}

int encodeable_g2float::decode(iiop *ptr) {
    double value;

    value = ptr->decode_double();
	gsi_set_flt(itm, value);

    if (debug_mode) {
        printf("Decoded a g2 float: %f\n", value);
    }

	return 0;
}


// Value
encodeable_g2value::encodeable_g2value(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2value::encode_typecode(iiop *ptr, int flag) {
	cout << "Unable to encode value typecode!" << endl;
	return 1;
}

int encodeable_g2value::decode_typecode(iiop *ptr) {
	cout << "Unable to decode value typecode!" << endl;
	return 1;
}

int encodeable_g2value::encode(iiop *ptr, int flag) {
	cout << "Unable to encode value type!" << endl;
	return 1;
}

int encodeable_g2value::decode(iiop *ptr) {
	cout << "Unable to decode value type!" << endl;
	return 1;
}


// Quantity
encodeable_g2quantity::encodeable_g2quantity(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2quantity::encode_typecode(iiop *ptr, int flag) {
	cout << "Unable to encode quantity typecode!" << endl;
	return 1;
}

int encodeable_g2quantity::decode_typecode(iiop *ptr) {
	cout << "Unable to decode value typecode!" << endl;
	return 1;
}

int encodeable_g2quantity::encode(iiop *ptr, int flag) {
	cout << "Unable to encode quantity type!" << endl;
	return 1;
}

int encodeable_g2quantity::decode(iiop *ptr) {
	cout << "Unable to decode quantity type!" << endl;
	return 1;
}


// integer array
encodeable_g2integerarray::encodeable_g2integerarray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2integerarray::encode_typecode(iiop *ptr, int flag) {
	encode_integer_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2integerarray::decode_typecode(iiop *ptr) {
	return decode_integer_seq_tk(ptr);
}

int encodeable_g2integerarray::encode(iiop *ptr, int flag) {

	int count = gsi_element_count_of(itm);
	gsi_int *els = gsi_int_array_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_long(els[i], flag);
	}
	return 0;
}

int encodeable_g2integerarray::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	long *attrs = new long[count];
	for (int i = 0; i < count; i++) {
		attrs[i] = ptr->decode_long();
	}
	if (!count) gsi_set_int_array(itm, NULL, 0);
	else gsi_set_int_array(itm, attrs, count);
	delete [] attrs;

    if (debug_mode) {
        printf("Decoded a g2 array of %d integers\n", count);
    }

	return 0;
}


// symbol array
encodeable_g2symbolarray::encodeable_g2symbolarray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2symbolarray::encode_typecode(iiop *ptr, int flag) {
	encode_symbol_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2symbolarray::decode_typecode(iiop *ptr) {
	return decode_symbol_seq_tk(ptr);
}

int encodeable_g2symbolarray::encode(iiop *ptr, int flag) {	
	
	int count = gsi_element_count_of(itm);
	char **els = gsi_sym_array_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_string(els[i], flag);
	}
	return 0;
}

int encodeable_g2symbolarray::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	char **attrs = new (char *[count]);
	for (int i = 0; i < count; i++) {
		attrs[i] = ptr->decode_string();
	}
	gsi_set_sym_array(itm, attrs, count);
	delete [] attrs;

    if (debug_mode) {
        printf("Decoded a g2 array of %d symbols\n", count);
    }

	return 0;
}


// string array
encodeable_g2stringarray::encodeable_g2stringarray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2stringarray::encode_typecode(iiop *ptr, int flag) {
	encode_string_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2stringarray::decode_typecode(iiop *ptr) {
	return decode_string_seq_tk(ptr);
}

int encodeable_g2stringarray::encode(iiop *ptr, int flag) {	
	
	int count = gsi_element_count_of(itm);
	char **els = gsi_str_array_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_string(els[i], flag);
	}
	return 0;
}

int encodeable_g2stringarray::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	char **attrs = new (char *[count]);
	for (int i = 0; i < count; i++) {
		attrs[i] = ptr->decode_string();
	}
	gsi_set_str_array(itm, attrs, count);
	delete [] attrs;

    if (debug_mode) {
        printf("Decoded a g2 array of %d strings\n", count);
    }

	return 0;
}


// logical array
encodeable_g2logicalarray::encodeable_g2logicalarray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2logicalarray::encode_typecode(iiop *ptr, int flag) {
	encode_logical_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2logicalarray::decode_typecode(iiop *ptr) {
	return decode_logical_seq_tk(ptr);
}

int encodeable_g2logicalarray::encode(iiop *ptr, int flag) {
		
	int count = gsi_element_count_of(itm);
	long *els = gsi_log_array_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_oct((els[i] > 0) ? 1 : 0, flag);
	}
	return 0;
}

int encodeable_g2logicalarray::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	long *els = new long[count];
	for (int i = 0; i < count; i++) {
		els[i] = (ptr->decode_oct() & 1) ? 1000 : -1000;
	}
	gsi_set_log_array(itm, els, count);
	delete [] els;

    if (debug_mode) {
        printf("Decoded a g2 array of %d logicals\n", count);
    }

	return 0;
}


// float array
encodeable_g2floatarray::encodeable_g2floatarray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2floatarray::encode_typecode(iiop *ptr, int flag) {
	encode_float_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2floatarray::decode_typecode(iiop *ptr) {
	return decode_float_seq_tk(ptr);
}

int encodeable_g2floatarray::encode(iiop *ptr, int flag) {
		
	int count = gsi_element_count_of(itm);
	double *els = gsi_flt_array_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_double(els[i], flag);
	}
	return 0;
}

int encodeable_g2floatarray::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	double *attrs = new double[count];
	for (int i = 0; i < count; i++) {
		attrs[i] = ptr->decode_double();
	}
	gsi_set_flt_array(itm, attrs, count);
	delete [] attrs;

    if (debug_mode) {
        printf("Decoded a g2 array of %d floats\n", count);
    }

	return 0;
}


// item array
encodeable_g2itemarray::encodeable_g2itemarray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2itemarray::encode_typecode(iiop *ptr, int flag) {
	encode_item_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2itemarray::decode_typecode(iiop *ptr) {
	return decode_item_seq_tk(ptr);
}

int encodeable_g2itemarray::encode(iiop *ptr, int flag) {
	
	encodeable_object *eo;

	int count = gsi_element_count_of(itm);
	gsi_item *els = gsi_elements_of(itm);
	ptr->encode_ulong(count, flag);
	if (!flag) { // create sub objects
		for (int i = 0; i < count; i++) {
			eo = new encodeable_g2item(els[i]);
			members.Add(eo);
		}
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo; eo = (encodeable_object *) eo->GetNext()) {
		eo->encode(ptr, flag);
	}
	return 0;
}

int encodeable_g2itemarray::decode(iiop *ptr) {

	encodeable_object *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		eo = new encodeable_g2item(attrs[i]);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_ITEM_ARRAY_TAG);

    if (debug_mode) {
        printf("Decoded a g2 array of %d items\n", count);
    }

	return 0;
}

// value array
encodeable_g2valuearray::encodeable_g2valuearray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2valuearray::encode_typecode(iiop *ptr, int flag) {
	encode_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2valuearray::decode_typecode(iiop *ptr) {
	return decode_seq_tk(ptr);
}

int encodeable_g2valuearray::encode(iiop *ptr, int flag) {
	if (!flag) build_sequence_from_elements();
	encode_members(ptr, flag);
	return 0;
}

int encodeable_g2valuearray::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_VALUE_ARRAY_TAG);

    if (debug_mode) {
        printf("Decoded a g2 array of %d values\n", count);
    }

	return 0;
}


// item or value array
encodeable_g2itemorvaluearray::encodeable_g2itemorvaluearray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2itemorvaluearray::encode_typecode(iiop *ptr, int flag) {
	encode_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2itemorvaluearray::decode_typecode(iiop *ptr) {
	return decode_seq_tk(ptr);
}

int encodeable_g2itemorvaluearray::encode(iiop *ptr, int flag) {
	if (!flag) build_sequence_from_elements();
	encode_members(ptr, flag);
	return 0;
}

int encodeable_g2itemorvaluearray::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_ITEM_OR_VALUE_ARRAY_TAG);

    if (debug_mode) {
        printf("Decoded a g2 array of %d items or values\n", count);
    }

	return 0;
}


// quantity array
encodeable_g2quantityarray::encodeable_g2quantityarray(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2quantityarray::encode_typecode(iiop *ptr, int flag) {
	encode_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2quantityarray::decode_typecode(iiop *ptr) {
	return decode_seq_tk(ptr);
}

int encodeable_g2quantityarray::encode(iiop *ptr, int flag) {
	if (!flag) build_sequence_from_elements();
	encode_members(ptr, flag);
	return 0;
}

int encodeable_g2quantityarray::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_QUANTITY_ARRAY_TAG);

    if (debug_mode) {
        printf("Decoded a g2 array of %d quantities\n", count);
    }

	return 0;
}


// integer list
encodeable_g2integerlist::encodeable_g2integerlist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2integerlist::encode_typecode(iiop *ptr, int flag) {
	encode_integer_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2integerlist::decode_typecode(iiop *ptr) {
	return decode_integer_seq_tk(ptr);
}

int encodeable_g2integerlist::encode(iiop *ptr, int flag) {
	int count = gsi_element_count_of(itm);
	long *els = gsi_int_list_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_long(els[i], flag);
	}
	return 0;
}

int encodeable_g2integerlist::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	long *els = new long[count];
	for (int i = 0; i < count; i++) {
		els[i] = ptr->decode_long();
	}
	gsi_set_int_list(itm, els, count);
	delete [] els;

    if (debug_mode) {
        printf("Decoded a g2 list of %d integers\n", count);
    }

	return 0;
}


// symbol list
encodeable_g2symbollist::encodeable_g2symbollist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2symbollist::encode_typecode(iiop *ptr, int flag) {
	encode_symbol_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2symbollist::decode_typecode(iiop *ptr) {
	return decode_symbol_seq_tk(ptr);
}

int encodeable_g2symbollist::encode(iiop *ptr, int flag) {
	int count = gsi_element_count_of(itm);
	char **els = gsi_sym_list_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_string(els[i], flag);
	}
	return 0;
}

int encodeable_g2symbollist::decode(iiop *ptr) {	
	
	long count = ptr->decode_ulong();
	char **els = new (char *[count]);
	for (int i = 0; i < count; i++) {
		els[i] = ptr->decode_string();
	}
	gsi_set_sym_list(itm, els, count);
	delete [] els;

    if (debug_mode) {
        printf("Decoded a g2 list of %d symbols\n", count);
    }

	return 0;
}


// string list
encodeable_g2stringlist::encodeable_g2stringlist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2stringlist::encode_typecode(iiop *ptr, int flag) {
	encode_string_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2stringlist::decode_typecode(iiop *ptr) {
	return decode_string_seq_tk(ptr);
}

int encodeable_g2stringlist::encode(iiop *ptr, int flag) {

	int count = gsi_element_count_of(itm);
	char **els = gsi_str_list_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_string(els[i], flag);
	}
	return 0;
}

int encodeable_g2stringlist::decode(iiop *ptr) {	
	
	long count = ptr->decode_ulong();
	char **attrs = new (char *[count]);
	for (int i = 0; i < count; i++) {
		attrs[i] = ptr->decode_string();
	}
	gsi_set_str_list(itm, attrs, count);
	delete [] attrs;

    if (debug_mode) {
        printf("Decoded a g2 list of %d strings\n", count);
    }

	return 0;
}


// logical list
encodeable_g2logicallist::encodeable_g2logicallist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2logicallist::encode_typecode(iiop *ptr, int flag) {
	encode_logical_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2logicallist::decode_typecode(iiop *ptr) {
	return decode_logical_seq_tk(ptr);
}

int encodeable_g2logicallist::encode(iiop *ptr, int flag) {
	int count = gsi_element_count_of(itm);

	long *els = gsi_log_list_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_oct((els[i] >= 0) ? 1 : 0, flag);
	}
	return 0;
}

int encodeable_g2logicallist::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	long *attrs = new long[count];
	for (int i = 0; i < count; i++) {
		attrs[i] = (ptr->decode_oct() & 1) ? 1000 : -1000;
	}
	gsi_set_log_list(itm, attrs, count);
	delete [] attrs;

    if (debug_mode) {
        printf("Decoded a g2 list of %d logicals\n", count);
    }

	return 0;
}


// float list
encodeable_g2floatlist::encodeable_g2floatlist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2floatlist::encode_typecode(iiop *ptr, int flag) {
	encode_float_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2floatlist::decode_typecode(iiop *ptr) {
	return decode_float_seq_tk(ptr);
}

int encodeable_g2floatlist::encode(iiop *ptr, int flag) {
	int count = gsi_element_count_of(itm);
	double *els = gsi_flt_list_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_double(els[i], flag);
	}
	return 0;
}

int encodeable_g2floatlist::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	double *attrs = new double[count];
	for (int i = 0; i < count; i++) {
		attrs[i] = ptr->decode_double();
	}
	gsi_set_flt_list(itm, attrs, count);
	delete [] attrs;

    if (debug_mode) {
        printf("Decoded a g2 list of %d floats\n", count);
    }

	return 0;
}



// item list
encodeable_g2itemlist::encodeable_g2itemlist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2itemlist::encode_typecode(iiop *ptr, int flag) {
	encode_item_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2itemlist::decode_typecode(iiop *ptr) {
	return decode_item_seq_tk(ptr);
}

int encodeable_g2itemlist::encode(iiop *ptr, int flag) {
	
	encodeable_object *eo;

	int count = gsi_element_count_of(itm);
	gsi_item *els = gsi_elements_of(itm);
	ptr->encode_ulong(count, flag);
	if (!flag) { // create sub objects
		for (int i = 0; i < count; i++) {
			eo = new encodeable_g2item(els[i]);
			members.Add(eo);
		}
	}

	for (eo = (encodeable_object *) members.GetFirst(); eo; eo = (encodeable_object *) eo->GetNext()) {
		eo->encode(ptr, flag);
	}
	return 0;
}

int encodeable_g2itemlist::decode(iiop *ptr) {

	encodeable_object *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		eo = new encodeable_g2item(attrs[i]);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_ITEM_LIST_TAG);

    if (debug_mode) {
        printf("Decoded a g2 list of %d items\n", count);
    }

	return 0;
}


// value list
encodeable_g2valuelist::encodeable_g2valuelist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2valuelist::encode_typecode(iiop *ptr, int flag) {
	encode_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2valuelist::decode_typecode(iiop *ptr) {
	return decode_seq_tk(ptr);
}

int encodeable_g2valuelist::encode(iiop *ptr, int flag) {
	if (!flag) build_sequence_from_elements();
	encode_members(ptr, flag);
	return 0;
}

int encodeable_g2valuelist::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_VALUE_LIST_TAG);

    if (debug_mode) {
        printf("Decoded a g2 list of %d values\n", count);
    }

	return 0;
}


// item or value list
encodeable_g2itemorvaluelist::encodeable_g2itemorvaluelist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2itemorvaluelist::encode_typecode(iiop *ptr, int flag) {
	encode_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2itemorvaluelist::decode_typecode(iiop *ptr) {
	return decode_seq_tk(ptr);
}

int encodeable_g2itemorvaluelist::encode(iiop *ptr, int flag) {
	if (!flag) build_sequence_from_elements();
	encode_members(ptr, flag);
	return 0;
}

int encodeable_g2itemorvaluelist::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_ITEM_OR_VALUE_LIST_TAG);

    if (debug_mode) {
        printf("Decoded a g2 list of %d items or values\n", count);
    }

	return 0;
}



// sequence
encodeable_g2sequence::encodeable_g2sequence(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2sequence::encode_typecode(iiop *ptr, int flag) {
	encode_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2sequence::decode_typecode(iiop *ptr) {
	return decode_seq_tk(ptr);
}

int encodeable_g2sequence::encode(iiop *ptr, int flag) {
	if (!flag) build_sequence_from_elements();
	encode_members(ptr, flag);
	return 0;
}

int encodeable_g2sequence::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_SEQUENCE_TAG);

    if (debug_mode) {
        printf("Decoded a g2 sequence of %d items\n", count);
    }

	return 0;
}



// structure
encodeable_g2structure::encodeable_g2structure(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2structure::encode_typecode(iiop *ptr, int flag) {
	encode_structure_tk(ptr, flag);
	return 0;
}

int encodeable_g2structure::decode_typecode(iiop *ptr) {
	return decode_structure_tk(ptr);
}

int encodeable_g2structure::encode(iiop *ptr, int flag) {

	encodeable_g2any *eo;

	if (!flag) {
		int n = gsi_attr_count_of(itm);
		gsi_item *attrs = gsi_attrs_of(itm);
		for (int i = 0; i < n; i++) {
			eo = new encodeable_g2any(attrs[i], get_type_of(attrs[i]));
			members.Add(eo);
		}
	}

	ptr->encode_ulong(members.Count, flag);
	for (eo = (encodeable_g2any *) members.GetFirst(); eo; eo = (encodeable_g2any *) eo->GetNext()) {
		char *attrName = gsi_attr_name_of(eo->itm);
		ptr->encode_string(attrName, flag);
		ptr->encode_ulong(eo->mCode, flag);
		eo->encode(ptr, flag);
	}

	return 0;
}

int encodeable_g2structure::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_attrs_with_items(count);
	for (int i = 0; i < count; i++) {
		char *AttrName = ptr->decode_string();
		gsi_set_attr_name(attrs[i], AttrName);
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_type(itm, GSI_STRUCTURE_TAG);
	gsi_set_attrs(itm, attrs, count);

    if (debug_mode) {
        printf("Decoded a g2 structure with %d members\n", count);
    }

	return 0;
}



// quantity list
encodeable_g2quantitylist::encodeable_g2quantitylist(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2quantitylist::encode_typecode(iiop *ptr, int flag) {
	encode_seq_tk(ptr, flag);
	return 0;
}

int encodeable_g2quantitylist::decode_typecode(iiop *ptr) {
	return decode_seq_tk(ptr);
}

int encodeable_g2quantitylist::encode(iiop *ptr, int flag) {
	if (!flag) build_sequence_from_elements();
	encode_members(ptr, flag);
	return 0;
}

int encodeable_g2quantitylist::decode(iiop *ptr) {

	encodeable_g2any *eo;

	long count = ptr->decode_ulong();
	gsi_item *attrs = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		long code = ptr->decode_ulong();
		eo = new encodeable_g2any(attrs[i], code);
		if (eo->decode(ptr)) return 1;
		delete eo;
	}
	gsi_set_elements(itm, attrs, count, GSI_QUANTITY_LIST_TAG);

    if (debug_mode) {
        printf("Decoded a g2 list of %d quantities\n", count);
    }

	return 0;
}


// Unsigned short vector
encodeable_g2usv::encodeable_g2usv(gsi_item ittm):encodeable_g2typecode(ittm) {
}

int encodeable_g2usv::encode_typecode(iiop *ptr, int flag) {
	encode_usv_tk(ptr, flag);
	return 0;
}

int encodeable_g2usv::decode_typecode(iiop *ptr) {
	return decode_usv_tk(ptr);
}

int encodeable_g2usv::encode(iiop *ptr, int flag) {
	int count = gsi_usv_length_of(itm);
	unsigned short *els = gsi_usv_of(itm);
	ptr->encode_ulong(count, flag);
	for (int i = 0; i < count; i++) {
		ptr->encode_short(els[i], flag);
	}
	return 0;
}

int encodeable_g2usv::decode(iiop *ptr) {

	long count = ptr->decode_ulong();
	unsigned short *attrs = new unsigned short[count];

    if (debug_mode) {
        printf("Decoded an unsigned short vector: \"");
    }

	for (int i = 0; i < count; i++) {
		attrs[i] = ptr->decode_short();
        if (debug_mode) {
            printf("%4.4x", attrs[i]);
        }
	}

    if (debug_mode) {
        printf("\"\n");
    }

    gsi_set_usv(itm, attrs, count);
	delete [] attrs;

	return 0;
}


