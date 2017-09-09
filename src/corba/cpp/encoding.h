#ifndef ENCODING_H
#define ENCODING_H

#include "gsi_main_cpp.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "iiop.h"

//
// These objects are used to marshel values.  Each object has an 
// encode method.  These objects are organized in a collection.  
// Also, each object is passed a gsi_item that is set to the 
// needed value when it is created.
//
// The encode method has a flag argument.  It should be called with
// flag = 0 to calcualte the size needed for the object.  Then
// the iiop buffer can be allocated to the needed size.
//
// These routines call the primitive marshel methods of the iiop
// object.
// 

class encodeable_object:public G2OrbContained {
public:
	virtual int encode(iiop *ptr, int flag) = 0;  // abstract class
	virtual int decode(iiop *ptr) = 0; 
	encodeable_object(gsi_item);
	gsi_item itm;
};


class encodeable_short:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_short(gsi_item);
};

class encodeable_ushort:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);        
	encodeable_ushort(gsi_item);
};

class encodeable_long:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_long(gsi_item);
};

class encodeable_ulong:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_ulong(gsi_item);
};


class encodeable_ullong:public encodeable_object {
public:
    virtual int encode(iiop *ptr, int flag) ;
    virtual int decode(iiop *ptr) ;
    encodeable_ullong(gsi_item) ;
};

class encodeable_llong:public encodeable_ullong
{
public:
    encodeable_llong(gsi_item) ;
};

class encodeable_float:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_float(gsi_item);
};

class encodeable_double:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_double(gsi_item);
};

class encodeable_boolean:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_boolean(gsi_item);
};

class encodeable_char:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_char(gsi_item);
};

class encodeable_string:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_string(gsi_item);
};

class encodeable_octet:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_octet(gsi_item);
};

//
// The following types need informaion from the IR to encode/decode
//

class encodeable_enum:public encodeable_object {
public:
	gsi_item m_def;
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_enum(gsi_item, gsi_item ir);
};

class encodeable_struct:public encodeable_object {
public:
	gsi_item m_def;
	G2OrbContext *m_cObj;
	NoHashContainer members;
	int m_direction;
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_struct(gsi_item, G2OrbContext *cObj, gsi_item ir, int direction);
};

class encodeable_exception:public encodeable_object {
public:
	gsi_item m_def;
	G2OrbContext *m_cObj;
	NoHashContainer members;
	int m_direction;
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_exception(gsi_item, G2OrbContext *cObj, gsi_item ir, int direction);
};

class encodeable_union:public encodeable_object {
public:
	NoHashContainer members;
	G2OrbContext *m_cObj;
	gsi_item m_ir;
	int m_direction;
	gsi_item m_typecode;
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	//gsi_item encodeable_union::find_matching_union_member(gsi_item target);
	gsi_item find_matching_union_member(gsi_item target);
	encodeable_union(gsi_item, G2OrbContext *cObj, gsi_item ir, int direction);
};

class encodeable_array:public encodeable_object {
public:
	gsi_item m_def;
	G2OrbContext *m_cObj;
	NoHashContainer members;
	int m_direction;

	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_array(gsi_item, G2OrbContext *cObj, gsi_item ir, int direction);
};

class encodeable_sequence:public encodeable_object {
public:
	gsi_item m_def;
	G2OrbContext *m_cObj;
	NoHashContainer members;
	int m_direction;
	gsi_int m_count;

	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_sequence(gsi_item, G2OrbContext *cObj, gsi_item ir, int direction);
};


class encodeable_context:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_context(gsi_item, G2OrbContext *cObj, char *ir);
};

class encodeable_objref:public encodeable_object {
public:
	iiop m_objref;
	gsi_item m_def; // check for NULL before using
	G2OrbContext *m_cObj;
	bool m_purge;
	bool m_isItem;

	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_objref(gsi_item ittm, G2OrbContext *cObj, gsi_item ir);
};

class encodeable_stringdef:public encodeable_object {
public:
	gsi_item m_def;
	G2String m_val;

	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_stringdef(gsi_item, gsi_item ir);
};


class encodeable_g2history:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2history(gsi_item);
};

class encodeable_g2itemval:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2itemval(gsi_item);
	encodeable_object *eo;
	virtual ~encodeable_g2itemval();
};


class encodeable_g2typecode:public encodeable_object {
public:
	virtual int encode_typecode(iiop *ptr, int flag) = 0;
	virtual int decode_typecode(iiop *ptr) = 0;
	encodeable_g2typecode(gsi_item ittm):encodeable_object(ittm) {};

	void encode_integer_tk(iiop *ptr, int flag);
	void encode_symbol_tk(iiop *ptr, int flag);
	void encode_string_tk(iiop *ptr, int flag);
	void encode_logical_tk(iiop *ptr, int flag);
	void encode_float_tk(iiop *ptr, int flag);
	void encode_item_tk(iiop *ptr, int flag);
	void encode_integer_seq_tk(iiop *ptr, int flag);
	void encode_symbol_seq_tk(iiop *ptr, int flag);
	void encode_string_seq_tk(iiop *ptr, int flag);
	void encode_logical_seq_tk(iiop *ptr, int flag);
	void encode_float_seq_tk(iiop *ptr, int flag);
	void encode_item_seq_tk(iiop *ptr, int flag);
	void encode_seq_tk(iiop *ptr, int flag);
	void encode_structure_tk(iiop *ptr, int flag);
	void encode_g2attribute_tk(iiop *ptr, int flag);
	void encode_g2structuremember_tk(iiop *ptr, int flag);
	void encode_g2sequencemember_tk(iiop *ptr, int flag);
	void encode_usv_tk(iiop *ptr, int flag);

	int decode_integer_tk(iiop *ptr);
	int decode_symbol_tk(iiop *ptr);
	int decode_string_tk(iiop *ptr);
	int decode_logical_tk(iiop *ptr);
	int decode_float_tk(iiop *ptr);
	int decode_item_tk(iiop *ptr);
	int decode_integer_seq_tk(iiop *ptr);
	int decode_symbol_seq_tk(iiop *ptr);
	int decode_string_seq_tk(iiop *ptr);
	int decode_logical_seq_tk(iiop *ptr);
	int decode_float_seq_tk(iiop *ptr);
	int decode_item_seq_tk(iiop *ptr);
	int decode_seq_tk(iiop *ptr);
	int decode_structure_tk(iiop *ptr);
	int decode_g2attribute_tk(iiop *ptr);
	int decode_g2structuremember_tk(iiop *ptr);
	int decode_g2sequencemember_tk(iiop *ptr);
	int decode_usv_tk(iiop *ptr);

	int fetch_tk(iiop *ptr);
	void build_sequence_from_elements(void);
	int fetch_encap(iiop *ptr, iiop &tk);

	encodeable_g2typecode * make_g2encodeable_from_type(int code);
	void encode_members(iiop *ptr, int flag);
	NoHashContainer members;
};

class encodeable_g2item:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2item(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2any:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2any(gsi_item, long code);
	encodeable_g2typecode * make_g2encodeable_from_type(int code);
	virtual ~encodeable_g2any();
	encodeable_g2typecode *eo;
	long mCode;
};

class encodeable_g2null:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2null(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2integer:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2integer(gsi_item);	
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};	

class encodeable_g2symbol:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2symbol(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2string:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2string(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2logical:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2logical(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2float:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2float(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2value:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2value(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2quantity:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2quantity(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2integerarray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2integerarray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2symbolarray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2symbolarray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2stringarray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2stringarray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2logicalarray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2logicalarray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2floatarray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2floatarray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2itemarray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2itemarray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
	NoHashContainer members;
};

class encodeable_g2valuearray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2valuearray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2itemorvaluearray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2itemorvaluearray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2quantityarray:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2quantityarray(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2integerlist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2integerlist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2symbollist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2symbollist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2stringlist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2stringlist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2logicallist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2logicallist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2floatlist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2floatlist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2itemlist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2itemlist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2valuelist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2valuelist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2itemorvaluelist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2itemorvaluelist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};


class encodeable_g2sequence:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2sequence(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2structure:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2structure(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2quantitylist:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2quantitylist(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);
};

class encodeable_g2itemname:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2itemname(gsi_item);
};

class encodeable_g2attribute:public encodeable_object {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2attribute(gsi_attr);
	encodeable_object *eo;
	virtual ~encodeable_g2attribute();
};

class encodeable_g2usv:public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2usv(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);	
};

class encodeable_g2nullrelation: public encodeable_g2typecode {
public:
	virtual int encode(iiop *ptr, int flag);
	virtual int decode(iiop *ptr);
	encodeable_g2nullrelation(gsi_item);
	virtual int encode_typecode(iiop *ptr, int flag);
	virtual int decode_typecode(iiop *ptr);	
};


#endif

