/*
**  Dependencies:
**  gsi.lib
*/
#include <iostream_ver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gsi_main_cpp.h"
#include "gsi_misc_cpp.h"
#include "corba_main.h"

#include "code_tokens.h"

//void gsi_set_sym( gsi_item, char* );

//
// These routines build G2 objects to pass up to G2.
//

void token_create_array(gsi_item itm, int count, 
						gsi_item **pitm, gsi_item **pval)

{
	gsi_set_class_name(itm, "G2IDL-G2-ARRAY");
	gsi_attr *attrs = gsi_make_attrs_with_items(2);
	gsi_set_attr_name(attrs[0], "ITMS");
	gsi_set_attr_name(attrs[1], "VALS");
	gsi_item *itms = gsi_make_items(count);
	gsi_item *vals = gsi_make_items(count);
	for (int i = 0; i < count; i++) {
		gsi_set_sym(vals[i], "NO-VALUE");
	}; // we need init values or GSI will bomb
	gsi_set_class_name(attrs[0], "ITEM-ARRAY");
	gsi_set_class_name(attrs[1], "VALUE-ARRAY");
	gsi_set_elements(attrs[0], itms, count, GSI_ITEM_ARRAY_TAG);
	gsi_set_elements(attrs[1], vals, count, GSI_VALUE_ARRAY_TAG);
	gsi_set_attrs(itm, attrs, 2);
	if (pitm) *pitm = itms;
	if (pval) *pval = vals;
}

void token_create_text_array(gsi_item itm, G2OrbContainer& texts,
							 char *sym)

{
	gsi_item *itms;
	gsi_item *vals;
	int i = 0;
	int n = texts.Count;
	if (sym) n++;
	token_create_array(itm, n, &itms, &vals);
	if (sym) gsi_set_sym(vals[i++], sym);
	for (g2_gsi_string_constant_token *ptr = (g2_gsi_string_constant_token *) texts.GetFirst();
		ptr; ptr = (g2_gsi_string_constant_token *) ptr->GetNext()) {
			gsi_set_str(vals[i++], (char *) ptr->m_name);
	}
}

//
// Build the G2 array for a file token with contents
//

void g2_file_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 2 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "FILE");
	gsi_set_str(vals[1], (char *) m_name);
	int i = 2;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_module_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 2 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "MODULE");
	gsi_set_str(vals[1], (char *) m_name);
	int i = 2;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_inheritance_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 1 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "INHERITANCE");
	int i = 1;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_scoped_name_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 1 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "SCOPED-NAME");
	int i = 1;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_global_scoped_name_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 1 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "GLOBAL-SCOPED-NAME");
	int i = 1;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}


//////////////////rjf
void g2_gsi_char_constant_token::build_gsi_object(gsi_item itm, gsi_item val) {

  char tmp[2];
  sprintf(tmp,"%c",m_namex);
  m_name = tmp; 
	gsi_set_str(val, (char *) m_name);
}

void g2_gsi_string_constant_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_set_str(val, (char *) m_name);
}

void g2_gsi_integer_constant_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_set_int(val, m_name);
}

void g2_gsi_float_constant_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_set_flt(val, m_name);
}

void g2_gsi_symbol_constant_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_set_sym(val, (char *) m_name);
}


void g2_array_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 2 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "ARRAY");
	gsi_set_str(vals[1], (char *) m_name);
	int i = 2;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i], vals[i]);
			i++;
	}
}

void g2_union_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 2 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "UNION");
	gsi_set_str(vals[1], (char *) m_name);
	int i = 2;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_union_case_token::build_gsi_object(gsi_item itm, gsi_item val) {

	// This is a different case, since the case object is a sub array
	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 3, &itms, &vals);
	gsi_item *sitms;
	gsi_item *svals;
	token_create_array(itms[0], 1 + m_val.Count, &sitms, &svals);
	gsi_set_sym(svals[0], "CASE");
	int i = 1;
	for (g2_token_object *ptr = (g2_token_object *) m_val.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(sitms[i], svals[i]);
			i++;
	}

	m_type.build_gsi_object(itms[1],vals[1]);
	m_name.build_gsi_object(itms[2],vals[2]);
}

void g2_union_switch_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 2, &itms, &vals);
	gsi_set_sym(vals[0], "SWITCH");
	m_type.build_gsi_object(itms[1],vals[1]);
}

void g2_math_op_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 3, &itms, &vals);
	gsi_set_sym(vals[0], (char *) m_name);
	val1.build_gsi_object(itms[1],vals[1]);
	val2.build_gsi_object(itms[2],vals[2]);
}


void g2_interface_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 2 + m_contents.Count;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "INTERFACE");
	gsi_set_str(vals[1], (char *) m_name);
	int i = 2;
	for (g2_token_object *ptr = (g2_token_object *) m_contents.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_attribute_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 2 + m_names.Count;
	if (m_readonly) n++;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "ATTRIBUTE");
	m_type.build_gsi_object(itms[1], vals[1]);
	token_create_text_array(itms[2], m_names, NULL);
	if (m_readonly) gsi_set_sym(vals[n-1], "READONLY");
}

void g2_operation_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 4;
	if (m_oneway) n++;
	if (m_exceptions.Count) n++;
	if (m_contexts.Count) n++;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "OPERATION");
	m_type.build_gsi_object(itms[1], vals[1]);
	gsi_set_str(vals[2], (char *) m_name);

	// now build the parm array
	gsi_item *pitms;
	gsi_item *pvals;
	int i = 0;
	token_create_array(itms[3], m_parms.Count, &pitms, &pvals);
	for (g2_token_object *ptr = (g2_token_object *) m_parms.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(pitms[i],pvals[i]);
			i++;
	}

	// now handle the optional arrays
	i = 4;
	if (m_oneway) gsi_set_sym(vals[i++], "ONEWAY");
	if (m_exceptions.Count) {  // create exception sub array
		gsi_item *eitms;
		gsi_item *evals;
		token_create_array(itms[i++], m_exceptions.Count + 1, &eitms, &evals);
		int j = 1;
		gsi_set_sym(evals[0], "RAISES");
		for (g2_token_object *ptr = (g2_token_object *) m_exceptions.GetFirst();
			ptr; ptr = (g2_token_object *) ptr->GetNext()) {
				ptr->build_gsi_object(eitms[j], evals[j]);
				j++;
		}
	}
	if (m_contexts.Count) {
		token_create_text_array(itms[i++], m_contexts, "CONTEXT");
	}
}

void g2_parm_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 3, &itms, &vals);
	switch (m_direction) {
	case 1:	gsi_set_sym(vals[0], "IN");
			break;
	case 2:	gsi_set_sym(vals[0], "OUT");
			break;
	case 3:	gsi_set_sym(vals[0], "INOUT");
			break;
	}
	m_type.build_gsi_object(itms[1], vals[1]);
	gsi_set_str(vals[2], (char *) m_name);
}

void g2_enum_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 3, &itms, &vals);
	gsi_set_sym(vals[0], "ENUM");
	gsi_set_str(vals[1], (char *) m_name);
	token_create_text_array(itms[2], m_values, NULL);
}

void g2_except_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 2 + m_members.Count, &itms, &vals);
	gsi_set_sym(vals[0], "EXCEPTION");
	gsi_set_str(vals[1], (char *) m_name);
	int i = 2;
	for (g2_token_object *ptr = (g2_token_object *) m_members.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_struct_mem_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 1 + m_name.Count, &itms, &vals);
	m_type.build_gsi_object(itms[0], vals[0]);
	int i = 1;
	for (g2_token_object *ptr = (g2_token_object *) m_name.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i], vals[i]);
			i++;
	}
}

void g2_typedef_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 2 + m_names.Count, &itms, &vals);
	gsi_set_sym(vals[0], "TYPEDEF");
	m_type.build_gsi_object(itms[1], vals[1]);
	int i = 2;
	for (g2_string_token *ptr = (g2_string_token *) m_names.GetFirst();
		ptr; ptr = (g2_string_token *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i], vals[i]);
			i++;
	}
}

void g2_struct_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 2 + m_members.Count, &itms, &vals);
	gsi_set_sym(vals[0], "STRUCT");
	gsi_set_str(vals[1], (char *) m_name);
	int i = 2;
	for (g2_token_object *ptr = (g2_token_object *) m_members.GetFirst();
		ptr; ptr = (g2_token_object *) ptr->GetNext()) {
			ptr->build_gsi_object(itms[i],vals[i]);
			i++;
	}
}

void g2_const_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	token_create_array(itm, 4, &itms, &vals);
	gsi_set_sym(vals[0], "CONST");
	gsi_set_str(vals[1], (char *) m_name);
	m_type.build_gsi_object(itms[2], vals[2]);
	m_value.build_gsi_object(itms[3], vals[3]);
}



void g2_type_holder::build_gsi_object(gsi_item itm, gsi_item val) {
	if (!m_type) {
		cout << "Error! attempt to convert a nonexistant type object to a gsi object!" << endl;
		return;
	}

	m_type->build_gsi_object(itm, val);
}

void g2_prim_type_token::build_gsi_object(gsi_item itm, gsi_item val) {
	gsi_set_sym(val, (char *) m_name);
}

void g2_string_type_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 1;
	if (m_bound.m_type) n++;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "STRING");
	if (m_bound.m_type) m_bound.build_gsi_object(itms[1],vals[1]);
}

void g2_seq_type_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_item *itms;
	gsi_item *vals;
	int n = 2;
	if (m_bound.m_type) n++;
	token_create_array(itm, n, &itms, &vals);
	gsi_set_sym(vals[0], "SEQUENCE");
	this->m_type.build_gsi_object(itms[1], vals[1]);
	if (m_bound.m_type) m_bound.build_gsi_object(itms[2],vals[2]);
}

void g2_ident_type_token::build_gsi_object(gsi_item itm, gsi_item val) {

	gsi_set_str(val, (char *) m_name);
}


/*
 * SuperClass Constructor
 */
SuperClass::SuperClass()
{

	//cout << "Inside SuperClass Constructor" << endl;

	return;

}

/*
 * SuperClass Destructor
 */
SuperClass::~SuperClass()
{

	//cout << "Inside SuperClass Destructor" << endl;

	return;
}

