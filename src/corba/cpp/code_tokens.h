
#ifndef CODE_TOKENS_H
#define CODE_TOKENS_H

#include "G2ContainerClass.h"
#include "g2string.h"

//
// This header files contains the definitions for objects that code 
// tokens for their trip to G2.
//

/*
 * SuperClass - base class which is used for argument passing and parameter return in the
 *				parse tree to GSI object model mapping.
 */
class SuperClass
	{			
	private:
		//-None-

	protected:	
		//-None-

	public:
		SuperClass();
		virtual	~SuperClass();
	};

class g2_token_object : public G2OrbContained, public SuperClass {
public:
	virtual void build_gsi_object(gsi_item itm, gsi_item val) = 0;

};

 
class g2_type_holder : public SuperClass {
public:
	g2_token_object *m_type;
	g2_type_holder(void) {m_type = NULL;};
	~g2_type_holder() {if (m_type) delete m_type;};
//	g2_type_token* operator=(g2_type_token *RHS) {m_type = RHS;};
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_prim_type_token : public g2_token_object {
public:
	G2String m_name; // symbol name 
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_string_type_token : public g2_token_object {
public:
	g2_type_holder m_bound; // 0 if unbounded;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_seq_type_token : public g2_token_object {
public:
	g2_type_holder m_type;
	g2_type_holder m_bound;; // 0 if unbounded;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_ident_type_token : public g2_token_object  {
public:
	G2String m_name; // name of identifier
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_file_token : public g2_token_object {
public:
	G2String m_name;
	NoHashContainer m_contents;  // token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_interface_token : public g2_token_object {
public:
	G2String m_name;
	NoHashContainer m_contents;  // token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};


class g2_attribute_token : public g2_token_object {
public:
	g2_type_holder m_type;
	NoHashContainer m_names;  // g2_string_token objects
	int m_readonly; // 1 if readonly, 0 if normal 
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_operation_token : public g2_token_object {
public:
	g2_type_holder m_type;
	G2String m_name;
	NoHashContainer m_parms; // g2_parm_token objects
	int m_oneway; // 1 if oneway, 0 if normal
	NoHashContainer m_exceptions; // g2_string_token objects
	NoHashContainer m_contexts;  // g2_string_token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_parm_token : public g2_token_object {
public:
	int m_direction; // 1 = in, 2 = out, 3 = inout;
	g2_type_holder m_type;
	G2String m_name;
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_enum_token : public g2_token_object {
public:
	G2String m_name;
	NoHashContainer m_values;  // g2_string_token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_except_token : public g2_token_object {
public:
	G2String m_name;
	NoHashContainer m_members;  // g2_struct_mem_token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_struct_mem_token : public g2_token_object {
public:
	g2_type_holder m_type;
	NoHashContainer m_name;	  //Make this a NoHashContainer ro hold multiple vales, perhaps.
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_typedef_token : public g2_token_object {
public:
	g2_type_holder m_type;
	NoHashContainer m_names;  // g2_string_token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_struct_token : public g2_token_object {
public:
	G2String m_name;
	NoHashContainer m_members; // g2_struct_mem_token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_const_token : public g2_token_object {
public:
	G2String m_name;
	g2_type_holder m_type;
	g2_type_holder m_value;
	virtual void build_gsi_object(gsi_item itm, gsi_item val); 
};

class g2_module_token : public g2_token_object {
public:
	G2String m_name;
	NoHashContainer m_contents; // set of things in moudle
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_inheritance_token : public g2_token_object {
public:
	NoHashContainer m_contents;  // holds g2_scoped_name_token or g2_string_token objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_scoped_name_token : public g2_token_object {
public:
	NoHashContainer m_contents;  // holds set of strings, use g2_string_token for strings
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_global_scoped_name_token : public g2_token_object {
public:
	NoHashContainer m_contents;  // holds set of strings, use g2_string_token for strings
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

//
// This set of constant objects are used to place a simple constant in the gsi output array
// This is done as a object, so these may be used anywhere a g2_token_object is 
//
class g2_gsi_constant_token : public g2_token_object {
public:
	virtual void build_gsi_object(gsi_item itm, gsi_item val) = 0;
};

class g2_gsi_integer_constant_token : public g2_gsi_constant_token {
public:
	gsi_int m_name;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

///////////////////////////rjf
class g2_gsi_char_constant_token : public g2_gsi_constant_token {
public:
  char     m_namex;
	G2String m_name;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_gsi_string_constant_token : public g2_gsi_constant_token {
public:
	G2String m_name;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_string_token: public g2_gsi_string_constant_token {
};  // for compatability with early version

class g2_gsi_float_constant_token : public g2_gsi_constant_token {
public:
	double m_name;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_gsi_symbol_constant_token : public g2_gsi_constant_token {
public:
	G2String m_name;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};


// Array

class g2_array_token : public g2_token_object {
public:
	G2String m_name;			// array name
	NoHashContainer m_contents; // dimentions of array
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

// Union

class g2_union_token : public g2_token_object {
public:
	G2String m_name;
	NoHashContainer m_contents; // case and switch objects
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_union_case_token : public g2_token_object {
public:
	NoHashContainer m_val;
	g2_type_holder m_type;		//element_spec: type_spec
	g2_type_holder m_name;		//element_spec: declarator
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};

class g2_union_switch_token : public g2_token_object {
public:
	g2_type_holder m_type;
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};


// Math Operation class

class g2_math_op_token : public g2_token_object {
public:
	G2String m_name;	   //operator as string
	g2_type_holder val1;   //left operand
	g2_type_holder val2;   //right operand
	virtual void build_gsi_object(gsi_item itm, gsi_item val);
};


void token_create_array(gsi_item itm, int count, 
						gsi_item **pitm, gsi_item **pval);
#endif
