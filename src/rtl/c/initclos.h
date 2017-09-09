/* initclos.h -- internal slot indexes and access macros
 * Generated on 05 Jan 1994  13:27:16
 * Copyright (C) 1993 Chestnut Software, Inc.  All Rights Reserved.
 */

#define SI_CLASS_DEFAULT_INITARGS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qinitargs,SI_Sinitargs)

#define SI_CLASS_DEFAULT_INITARGS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qinitargs,SI_Sinitargs)

#define SI_SET_CLASS_DEFAULT_INITARGS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qinitargs,v,SI_Sinitargs)

#define SI_CLASS_DIRECT_SUBCLASSES(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qdirect_subclasses,SI_Sdirect_subclasses)

#define SI_CLASS_DIRECT_SUBCLASSES_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qdirect_subclasses,SI_Sdirect_subclasses)

#define SI_SET_CLASS_DIRECT_SUBCLASSES(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qdirect_subclasses,v,SI_Sdirect_subclasses)

#define SI_CLASS_PRECEDENCE_LIST(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qprecedence_list,SI_Sprecedence_list)

#define SI_CLASS_PRECEDENCE_LIST_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qprecedence_list,SI_Sprecedence_list)

#define SI_SET_CLASS_PRECEDENCE_LIST(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qprecedence_list,v,SI_Sprecedence_list)

#define SI_CLASS_PROTOTYPE(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qprototype,SI_Sprototype)

#define SI_CLASS_PROTOTYPE_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qprototype,SI_Sprototype)

#define SI_SET_CLASS_PROTOTYPE(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qprototype,v,SI_Sprototype)

#define SI_CLASS_SHARED_SLOT_LOCATIONS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qshared_slot_locations,SI_Sshared_slot_locations)

#define SI_CLASS_SHARED_SLOT_LOCATIONS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qshared_slot_locations,SI_Sshared_slot_locations)

#define SI_SET_CLASS_SHARED_SLOT_LOCATIONS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qshared_slot_locations,v,SI_Sshared_slot_locations)

#define SI_CLASS_SLOTS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qslots,SI_Sslots)

#define SI_CLASS_SLOTS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qslots,SI_Sslots)

#define SI_SET_CLASS_SLOTS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qslots,v,SI_Sslots)

#define SI_CLASS_SLOTS_ALIST(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qslots_alist,SI_Sslots_alist)

#define SI_CLASS_SLOTS_ALIST_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qslots_alist,SI_Sslots_alist)

#define SI_SET_CLASS_SLOTS_ALIST(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qslots_alist,v,SI_Sslots_alist)

#define SI_CLASS_WRAPPER(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qwrapper,SI_Swrapper)

#define SI_CLASS_WRAPPER_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qwrapper,SI_Swrapper)

#define SI_SET_CLASS_WRAPPER(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qwrapper,v,SI_Swrapper)

#define SI_ENCODED_LAMBDA_LIST(o) \
    SI_SLOT_VALUE_INDEXED(o,Qencoded_lambda_list,SI_Sencoded_lambda_list)

#define SI_ENCODED_LAMBDA_LIST_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,Qencoded_lambda_list,SI_Sencoded_lambda_list)

#define SI_SET_ENCODED_LAMBDA_LIST(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,Qencoded_lambda_list,v,SI_Sencoded_lambda_list)

#define SI_GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qargument_precedence_map,SI_Sargument_precedence_map)

#define SI_GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qargument_precedence_map,SI_Sargument_precedence_map)

#define SI_SET_GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qargument_precedence_map,v,SI_Sargument_precedence_map)

#define SI_GENERIC_FUNCTION_CRITICAL_METHODS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qcritical_methods,SI_Scritical_methods)

#define SI_GENERIC_FUNCTION_CRITICAL_METHODS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qcritical_methods,SI_Scritical_methods)

#define SI_SET_GENERIC_FUNCTION_CRITICAL_METHODS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qcritical_methods,v,SI_Scritical_methods)

#define SI_GENERIC_FUNCTION_EFFECTIVE_METHODS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qeffective_methods,SI_Seffective_methods)

#define SI_GENERIC_FUNCTION_EFFECTIVE_METHODS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qeffective_methods,SI_Seffective_methods)

#define SI_SET_GENERIC_FUNCTION_EFFECTIVE_METHODS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qeffective_methods,v,SI_Seffective_methods)

#define SI_GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qeql_specialized_methods,SI_Seql_specialized_methods)

#define SI_GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qeql_specialized_methods,SI_Seql_specialized_methods)

#define SI_SET_GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qeql_specialized_methods,v,SI_Seql_specialized_methods)

#define SI_GENERIC_FUNCTION_INITIAL_METHODS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qinitial_methods,SI_Sinitial_methods)

#define SI_GENERIC_FUNCTION_INITIAL_METHODS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qinitial_methods,SI_Sinitial_methods)

#define SI_SET_GENERIC_FUNCTION_INITIAL_METHODS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qinitial_methods,v,SI_Sinitial_methods)

#define SI_GENERIC_FUNCTION_METHODS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qmethods,SI_Smethods)

#define SI_GENERIC_FUNCTION_METHODS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qmethods,SI_Smethods)

#define SI_SET_GENERIC_FUNCTION_METHODS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qmethods,v,SI_Smethods)

#define SI_GENERIC_FUNCTION_SPECIALIZED_POSITIONS(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qspecialized_positions,SI_Sspecialized_positions)

#define SI_GENERIC_FUNCTION_SPECIALIZED_POSITIONS_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qspecialized_positions,SI_Sspecialized_positions)

#define SI_SET_GENERIC_FUNCTION_SPECIALIZED_POSITIONS(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qspecialized_positions,v,SI_Sspecialized_positions)

#define SI_METHOD_GENERIC_FUNCTION(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qgeneric_function,SI_Sgeneric_function)

#define SI_METHOD_GENERIC_FUNCTION_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qgeneric_function,SI_Sgeneric_function)

#define SI_SET_METHOD_GENERIC_FUNCTION(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qgeneric_function,v,SI_Sgeneric_function)

#define SI_METHOD_KEYWORD_PARAMETER_MAP(o) \
    SI_SLOT_VALUE_INDEXED(o,SI_Qkeyword_parameter_map,SI_Skeyword_parameter_map)

#define SI_METHOD_KEYWORD_PARAMETER_MAP_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,SI_Qkeyword_parameter_map,SI_Skeyword_parameter_map)

#define SI_SET_METHOD_KEYWORD_PARAMETER_MAP(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,SI_Qkeyword_parameter_map,v,SI_Skeyword_parameter_map)

#define SI_SLOT_DEFINITION_CONSTANT_INITFORM_P(o) \
    SI_SLOT_VALUE_INDEXED(o,Qconstant_initform_p,SI_Sconstant_initform_p)

#define SI_SLOT_DEFINITION_CONSTANT_INITFORM_P_BOUNDP(o) \
    SI_SLOT_BOUNDP_INDEXED(o,Qconstant_initform_p,SI_Sconstant_initform_p)

#define SI_SET_SLOT_DEFINITION_CONSTANT_INITFORM_P(o,v) \
    SI_SET_SLOT_VALUE_INDEXED(o,Qconstant_initform_p,v,SI_Sconstant_initform_p)


extern Object SI_Sallocation;
extern Object SI_Sargument_precedence_map;
extern Object SI_Sargument_precedence_order;
extern Object SI_Sconstant_initform_p;
extern Object SI_Scritical_methods;
extern Object SI_Sdeclarations;
extern Object SI_Sdirect_default_initargs;
extern Object SI_Sdirect_slots;
extern Object SI_Sdirect_subclasses;
extern Object SI_Sdirect_superclasses;
extern Object SI_Sdoc_string;
extern Object SI_Seffective_methods;
extern Object SI_Sencoded_lambda_list;
extern Object SI_Seql_specialized_methods;
extern Object SI_Sgeneric_function;
extern Object SI_Sinitargs;
extern Object SI_Sinitform;
extern Object SI_Sinitfunction;
extern Object SI_Sinitial_methods;
extern Object SI_Skeyword_parameter_map;
extern Object SI_Slambda_list;
extern Object SI_Slocation;
extern Object SI_Smethod_class;
extern Object SI_Smethod_combination;
extern Object SI_Smethods;
extern Object SI_Sname;
extern Object SI_Sprecedence_list;
extern Object SI_Sprototype;
extern Object SI_Squalifiers;
extern Object SI_Sreaders;
extern Object SI_Sshared_slot_locations;
extern Object SI_Sslot_name;
extern Object SI_Sslot_type;
extern Object SI_Sslots;
extern Object SI_Sslots_alist;
extern Object SI_Sspecialized_positions;
extern Object SI_Sspecializers;
extern Object SI_Sstatus_bits;
extern Object SI_Svalid_change_class_initargs;
extern Object SI_Svalid_creation_initargs;
extern Object SI_Svalid_reinitialization_initargs;
extern Object SI_Swrapper;
extern Object SI_Swriters;

extern Object SI_Slot_index_min, SI_Slot_index_max;
