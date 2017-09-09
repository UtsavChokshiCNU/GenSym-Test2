/* pthnms.c
 * Input file:  pathnames.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pthnms.h"


static Object Qg2int_unix;         /* unix */

static Object Qg2int_vms;          /* vms */

static Object Qg2int_dos;          /* dos */

static Object Qg2int_win32;        /* win32 */

/* INITIALIZE-LOCAL-FILE-SYSTEM */
Object g2int_initialize_local_file_system()
{
    x_note_fn_call(32,0);
    if (EQ(G2int_g2_operating_system,Qg2int_unix))
	return VALUES_1(Qg2int_unix);
    else if (EQ(G2int_g2_operating_system,Qg2int_vms))
	return VALUES_1(Qg2int_vms);
    else if (EQ(G2int_g2_operating_system,Qg2int_dos))
	return VALUES_1(Qg2int_dos);
    else if (EQ(G2int_g2_operating_system,Qg2int_win32))
	return VALUES_1(Qg2int_win32);
    else
	return VALUES_1(Qg2int_unix);
}

Object G2int_local_file_system = UNBOUND;

static Object Qg2int_parse_unix_filename;  /* parse-unix-filename */

static Object Qg2int_parse_vms_filename;  /* parse-vms-filename */

static Object Qg2int_parse_dos_filename;  /* parse-dos-filename */

static Object Qg2int_parse_win32_filename;  /* parse-win32-filename */

/* INITIALIZE-LOCAL-FILENAME-PARSER */
Object g2int_initialize_local_filename_parser()
{
    x_note_fn_call(32,1);
    if (EQ(G2int_g2_operating_system,Qg2int_unix))
	return VALUES_1(Qg2int_parse_unix_filename);
    else if (EQ(G2int_g2_operating_system,Qg2int_vms))
	return VALUES_1(Qg2int_parse_vms_filename);
    else if (EQ(G2int_g2_operating_system,Qg2int_dos))
	return VALUES_1(Qg2int_parse_dos_filename);
    else if (EQ(G2int_g2_operating_system,Qg2int_win32))
	return VALUES_1(Qg2int_parse_win32_filename);
    else
	return VALUES_1(Qg2int_parse_unix_filename);
}

Object G2int_local_filename_parser = UNBOUND;

static Object Qg2int_generate_unix_namestring;  /* generate-unix-namestring */

static Object Qg2int_generate_vms_namestring;  /* generate-vms-namestring */

static Object Qg2int_generate_dos_namestring;  /* generate-dos-namestring */

static Object Qg2int_generate_win32_namestring;  /* generate-win32-namestring */

/* INITIALIZE-LOCAL-NAMESTRING-GENERATOR */
Object g2int_initialize_local_namestring_generator()
{
    x_note_fn_call(32,2);
    if (EQ(G2int_g2_operating_system,Qg2int_unix))
	return VALUES_1(Qg2int_generate_unix_namestring);
    else if (EQ(G2int_g2_operating_system,Qg2int_vms))
	return VALUES_1(Qg2int_generate_vms_namestring);
    else if (EQ(G2int_g2_operating_system,Qg2int_dos))
	return VALUES_1(Qg2int_generate_dos_namestring);
    else if (EQ(G2int_g2_operating_system,Qg2int_win32))
	return VALUES_1(Qg2int_generate_win32_namestring);
    else
	return VALUES_1(Qg2int_generate_unix_namestring);
}

Object G2int_local_namestring_generator = UNBOUND;

Object G2int_convert_file_strings_to_uppercase_p_prop = UNBOUND;

/* INITIALIZE-CONVERT-FILE-STRINGS-TO-UPPERCASE-P */
Object g2int_initialize_convert_file_strings_to_uppercase_p()
{
    x_note_fn_call(32,3);
    if (EQ(G2int_local_file_system,Qg2int_unix))
	return VALUES_1(Nil);
    else if (EQ(G2int_local_file_system,Qg2int_vms))
	return VALUES_1(T);
    else if (EQ(G2int_local_file_system,Qg2int_dos))
	return VALUES_1(T);
    else if (EQ(G2int_local_file_system,Qg2int_win32))
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

Object G2int_convert_file_strings_to_uppercase_p = UNBOUND;

Object G2int_the_type_description_of_gensym_pathname = UNBOUND;

Object G2int_chain_of_available_gensym_pathnames = UNBOUND;

Object G2int_gensym_pathname_count = UNBOUND;

/* RECLAIM-GENSYM-PATHNAME-STRUCTURE-MACRO-1 */
Object g2int_reclaim_gensym_pathname_structure_macro_1(gensym_pathname)
    Object gensym_pathname;
{
    Object svref_new_value;

    x_note_fn_call(32,4);
    inline_note_reclaim_cons(gensym_pathname,Nil);
    svref_new_value = G2int_chain_of_available_gensym_pathnames;
    SVREF(gensym_pathname,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gensym_pathnames = gensym_pathname;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-PATHNAME */
Object g2int_reclaim_structure_for_gensym_pathname(gensym_pathname)
    Object gensym_pathname;
{
    x_note_fn_call(32,5);
    return g2int_reclaim_gensym_pathname_structure_macro_1(gensym_pathname);
}

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* MAKE-PERMANENT-GENSYM-PATHNAME-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gensym_pathname_structure_internal()
{
    Object def_structure_gensym_pathname_variable;
    Object gensym_pathname_count_new_value;
    Object defstruct_g2_gensym_pathname_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(32,6);
    def_structure_gensym_pathname_variable = Nil;
    gensym_pathname_count_new_value = FIXNUM_ADD1(G2int_gensym_pathname_count);
    G2int_gensym_pathname_count = gensym_pathname_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gensym_pathname_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_gensym_pathname_variable = the_array;
	SVREF(defstruct_g2_gensym_pathname_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct;
	def_structure_gensym_pathname_variable = 
		defstruct_g2_gensym_pathname_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gensym_pathname_variable);
}

/* MAKE-GENSYM-PATHNAME-STRUCTURE-MACRO-1 */
Object g2int_make_gensym_pathname_structure_macro_1(gensym_pathname_host,
	    gensym_pathname_device,gensym_pathname_directory,
	    gensym_pathname_name,gensym_pathname_type,gensym_pathname_version)
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version;
{
    Object def_structure_gensym_pathname_variable, svref_new_value;

    x_note_fn_call(32,7);
    def_structure_gensym_pathname_variable = 
	    G2int_chain_of_available_gensym_pathnames;
    if (def_structure_gensym_pathname_variable) {
	G2int_chain_of_available_gensym_pathnames = 
		ISVREF(def_structure_gensym_pathname_variable,(SI_Long)0L);
	SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct;
    }
    else
	def_structure_gensym_pathname_variable = 
		g2int_make_permanent_gensym_pathname_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_pathname_variable,Nil);
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)1L)) = 
	    gensym_pathname_host;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)2L)) = 
	    gensym_pathname_device;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)3L)) = 
	    gensym_pathname_directory;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)4L)) = 
	    gensym_pathname_name;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)5L)) = 
	    gensym_pathname_type;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)6L)) = 
	    gensym_pathname_version;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)7L)) = Nil;
    svref_new_value = G2int_local_file_system;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)8L)) = 
	    svref_new_value;
    svref_new_value = G2int_local_filename_parser;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)9L)) = 
	    svref_new_value;
    svref_new_value = G2int_local_namestring_generator;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)10L)) = 
	    svref_new_value;
    return VALUES_1(def_structure_gensym_pathname_variable);
}

/* MAKE-GENSYM-PATHNAME-STRUCTURE-FUNCTION */
Object g2int_make_gensym_pathname_structure_function(gensym_pathname_host,
	    gensym_pathname_device,gensym_pathname_directory,
	    gensym_pathname_name,gensym_pathname_type,gensym_pathname_version)
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version;
{
    x_note_fn_call(32,8);
    return g2int_make_gensym_pathname_structure_macro_1(gensym_pathname_host,
	    gensym_pathname_device,gensym_pathname_directory,
	    gensym_pathname_name,gensym_pathname_type,gensym_pathname_version);
}

/* MAKE-EMPTY-GENSYM-PATHNAME */
Object g2int_make_empty_gensym_pathname()
{
    Object temp;

    x_note_fn_call(32,9);
    temp = g2int_make_gensym_pathname_structure_macro_1(Nil,Nil,Nil,Nil,
	    Nil,Nil);
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

/* INITIALIZE-DEFAULT-GENSYM-PATHNAME-DEFAULTS */
Object g2int_initialize_default_gensym_pathname_defaults()
{
    Object defaults, svref_new_value;

    x_note_fn_call(32,10);
    defaults = g2int_make_gensym_pathname_structure_function(Nil,Nil,
	    list_constant,Nil,Nil,Knewest);
    svref_new_value = G2int_local_file_system;
    SVREF(defaults,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = G2int_local_filename_parser;
    SVREF(defaults,FIX((SI_Long)9L)) = svref_new_value;
    svref_new_value = G2int_local_namestring_generator;
    SVREF(defaults,FIX((SI_Long)10L)) = svref_new_value;
    return VALUES_1(defaults);
}

Object G2int_gensym_default_pathname_defaults = UNBOUND;

/* RECLAIM-PATHNAME-OR-STRING */
Object g2int_reclaim_pathname_or_string(pathname_var)
    Object pathname_var;
{
    x_note_fn_call(32,11);
    if ( !TRUEP(pathname_var))
	return VALUES_1(Nil);
    else if (SIMPLE_VECTOR_P(pathname_var) && EQ(ISVREF(pathname_var,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	return g2int_reclaim_gensym_pathname(pathname_var);
    else if (g2int_text_string_p(pathname_var))
	return g2int_reclaim_text_string(pathname_var);
    else
	return VALUES_1(Qnil);
}

static Object string_constant;     /* "RclmGsmPthnm" */

/* RECLAIM-GENSYM-PATHNAME */
Object g2int_reclaim_gensym_pathname(pathname_1)
    Object pathname_1;
{
    Object current_custom_reclamation_stamp_qm, gensym_pathname_host;
    Object gensym_pathname_device, gensym_pathname_directory;
    Object gensym_pathname_name, gensym_pathname_type, gensym_pathname_version;
    Object directory_component, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,12);
    current_custom_reclamation_stamp_qm = string_constant;
    PUSH_SPECIAL(G2int_current_custom_reclamation_stampqm,current_custom_reclamation_stamp_qm,
	    0);
      gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
      gensym_pathname_device = ISVREF(pathname_1,(SI_Long)2L);
      gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
      gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
      gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
      gensym_pathname_version = ISVREF(pathname_1,(SI_Long)6L);
      if (g2int_text_string_p(gensym_pathname_host))
	  g2int_reclaim_text_string(gensym_pathname_host);
      if (g2int_text_string_p(gensym_pathname_device))
	  g2int_reclaim_text_string(gensym_pathname_device);
      if (CONSP(gensym_pathname_directory)) {
	  directory_component = Nil;
	  ab_loop_list_ = gensym_pathname_directory;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  directory_component = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (g2int_text_string_p(directory_component))
	      g2int_reclaim_text_string(directory_component);
	  goto next_loop;
	end_loop:
	  g2int_reclaim_gensym_list_1(gensym_pathname_directory);
      }
      if (g2int_text_string_p(gensym_pathname_name))
	  g2int_reclaim_text_string(gensym_pathname_name);
      if (g2int_text_string_p(gensym_pathname_type))
	  g2int_reclaim_text_string(gensym_pathname_type);
      if (g2int_text_string_p(gensym_pathname_version))
	  g2int_reclaim_text_string(gensym_pathname_version);
      result = g2int_reclaim_gensym_pathname_structure_macro_1(pathname_1);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-IF-GENSYM-PATHNAME */
Object g2int_reclaim_if_gensym_pathname(pathname_qm)
    Object pathname_qm;
{
    Object temp;

    x_note_fn_call(32,13);
    temp = pathname_qm ? g2int_reclaim_gensym_pathname(pathname_qm) : Nil;
    return VALUES_1(temp);
}

/* RECLAIM-PATHNAME-COMPONENTS */
Object g2int_reclaim_pathname_components varargs_1(int, n)
{
    Object host, device, directory_1, name, type, version, directory_item;
    Object ab_loop_list_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,14);
    INIT_ARGS_nonrelocating();
    host = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    device = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    directory_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    name = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    type = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    version = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (g2int_text_string_p(host))
	g2int_reclaim_text_string(host);
    if (g2int_text_string_p(device))
	g2int_reclaim_text_string(device);
    directory_item = Nil;
    ab_loop_list_ = directory_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (g2int_text_string_p(directory_item))
	g2int_reclaim_text_string(directory_item);
    goto next_loop;
  end_loop:
    g2int_reclaim_gensym_list_1(directory_1);
    if (g2int_text_string_p(name))
	g2int_reclaim_text_string(name);
    if (g2int_text_string_p(type))
	g2int_reclaim_text_string(type);
    if (g2int_text_string_p(version))
	return g2int_reclaim_text_string(version);
    else
	return VALUES_1(Nil);
}

/* PRINT-GENSYM-PATHNAME */
Object g2int_print_gensym_pathname(pathname_qm)
    Object pathname_qm;
{
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version;

    x_note_fn_call(32,15);
    if (SIMPLE_VECTOR_P(pathname_qm) && EQ(ISVREF(pathname_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	format((SI_Long)3L,T,"~&~a pathname -~%",ISVREF(pathname_qm,
		(SI_Long)8L));
	format((SI_Long)3L,T,"~&     host: ~s~%",gensym_pathname_host);
	format((SI_Long)3L,T,"~&   device: ~s~%",gensym_pathname_device);
	format((SI_Long)3L,T,"~&directory: ~s~%",gensym_pathname_directory);
	format((SI_Long)3L,T,"~&     name: ~s~%",gensym_pathname_name);
	format((SI_Long)3L,T,"~&     type: ~s~%",gensym_pathname_type);
	return format((SI_Long)3L,T,"~&  version: ~s~%",
		gensym_pathname_version);
    }
    else
	return format((SI_Long)3L,T,"~&not a gensym-pathname: ~s~%",
		pathname_qm);
}

Object G2int_file_systems_which_distinguish_by_version = UNBOUND;

/* PATHNAME-DISTINGUISHED-BY-VERSION-P */
Object g2int_pathname_distinguished_by_version_p(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(32,16);
    if (SIMPLE_VECTOR_P(pathname_1) && EQ(ISVREF(pathname_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	if (g2int_memq_function(ISVREF(pathname_1,(SI_Long)8L),
		G2int_file_systems_which_distinguish_by_version))
	    return VALUES_2(T,T);
	else
	    return VALUES_2(Nil,T);
    }
    else
	return VALUES_2(Nil,Nil);
}

Object G2int_file_systems_which_store_device_names = UNBOUND;

/* PATHNAME-CAN-CONTAIN-DEVICE-P */
Object g2int_pathname_can_contain_device_p(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(32,17);
    if (SIMPLE_VECTOR_P(pathname_1) && EQ(ISVREF(pathname_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	if (g2int_memq_function(ISVREF(pathname_1,(SI_Long)8L),
		G2int_file_systems_which_store_device_names))
	    return VALUES_2(T,T);
	else
	    return VALUES_2(Nil,T);
    }
    else
	return VALUES_2(Nil,Nil);
}

/* GET-DEFAULT-FILE-SYSTEM-INFO */
Object g2int_get_default_file_system_info()
{
    x_note_fn_call(32,18);
    return VALUES_3(G2int_local_filename_parser,
	    G2int_local_namestring_generator,G2int_local_file_system);
}

/* GENSYM-MAKE-PATHNAME-WITHOUT-COPYING */
Object g2int_gensym_make_pathname_without_copying varargs_1(int, n)
{
    Object host, device, directory_1, name, type, version;
    Object defaults, undefaulted_pathname, temp, temp_1, temp_2;
    Object filename_parser, namestring_generator, file_system;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(32,19);
    INIT_ARGS_nonrelocating();
    host = REQUIRED_ARG_nonrelocating();
    device = REQUIRED_ARG_nonrelocating();
    directory_1 = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    version = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    undefaulted_pathname = 
	    g2int_make_gensym_pathname_structure_function(host,device,
	    directory_1,name,type,version);
    if (host && g2int_text_string_p(host))
	result = g2int_get_parser_from_namestring(host);
    else if (defaults && SIMPLE_VECTOR_P(defaults) && EQ(ISVREF(defaults,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	temp = ISVREF(defaults,(SI_Long)9L);
	temp_1 = ISVREF(defaults,(SI_Long)10L);
	temp_2 = ISVREF(defaults,(SI_Long)8L);
	result = VALUES_3(temp,temp_1,temp_2);
    }
    else if (defaults && g2int_text_string_p(defaults))
	result = g2int_get_parser_from_namestring(defaults);
    else
	result = g2int_get_default_file_system_info();
    MVS_3(result,filename_parser,namestring_generator,file_system);
    SVREF(undefaulted_pathname,FIX((SI_Long)9L)) = filename_parser;
    SVREF(undefaulted_pathname,FIX((SI_Long)10L)) = namestring_generator;
    SVREF(undefaulted_pathname,FIX((SI_Long)8L)) = file_system;
    if (defaults) {
	temp_2 = 
		g2int_gensym_merge_pathnames_function(undefaulted_pathname,
		defaults,Nil);
	g2int_reclaim_gensym_pathname(undefaulted_pathname);
	return VALUES_1(temp_2);
    }
    else
	return VALUES_1(undefaulted_pathname);
}

/* COPY-DIRECTORY-COMPONENTS-FROM-DIRECTORY-STRING */
Object g2int_copy_directory_components_from_directory_string(directory_string)
    Object directory_string;
{
    Object raw_directory_pathname_qm, directory_pathname_qm;
    Object directory_component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(32,20);
    raw_directory_pathname_qm = g2int_gensym_pathname(directory_string);
    if ( !TRUEP(raw_directory_pathname_qm))
	return VALUES_1(Nil);
    else if (ISVREF(raw_directory_pathname_qm,(SI_Long)4L)) {
	directory_pathname_qm = 
		g2int_gensym_file_as_directory(raw_directory_pathname_qm);
	if (directory_pathname_qm) {
	    directory_component = Nil;
	    ab_loop_list_ = ISVREF(directory_pathname_qm,(SI_Long)3L);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    directory_component = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    g2int_gensym_cons_1(g2int_copy_pathname_contents(directory_component),
		    Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    g2int_reclaim_gensym_pathname(directory_pathname_qm);
	    g2int_reclaim_gensym_pathname(raw_directory_pathname_qm);
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
	else {
	    directory_component = Nil;
	    ab_loop_list_ = ISVREF(raw_directory_pathname_qm,(SI_Long)3L);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    directory_component = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    g2int_gensym_cons_1(g2int_copy_pathname_contents(directory_component),
		    Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    g2int_reclaim_gensym_pathname(raw_directory_pathname_qm);
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
    }
    else {
	directory_component = Nil;
	ab_loop_list_ = ISVREF(raw_directory_pathname_qm,(SI_Long)3L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	directory_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		g2int_gensym_cons_1(g2int_copy_pathname_contents(directory_component),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	g2int_reclaim_gensym_pathname(raw_directory_pathname_qm);
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

static Object Qg2int_convert_file_strings_to_uppercase_p;  /* convert-file-strings-to-uppercase-p */

/* GENSYM-MAKE-PATHNAME-WITH-COPIED-COMPONENTS */
Object g2int_gensym_make_pathname_with_copied_components(host,device,
	    directory_1,name,type,version,defaults)
    Object host, device, directory_1, name, type, version, defaults;
{
    Object gensymed_symbol, convert_file_strings_to_uppercase_p;
    Object directory_component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,21);
    if (host && g2int_text_string_p(host)) {
	result = g2int_get_parser_from_namestring(host);
	gensymed_symbol = NTH_VALUE((SI_Long)2L, result);
	convert_file_strings_to_uppercase_p = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_convert_file_strings_to_uppercase_p);
    }
    else if (defaults && SIMPLE_VECTOR_P(defaults) && EQ(ISVREF(defaults,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	gensymed_symbol = ISVREF(defaults,(SI_Long)8L);
	convert_file_strings_to_uppercase_p = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_convert_file_strings_to_uppercase_p);
    }
    else if (defaults && g2int_text_string_p(defaults)) {
	result = g2int_get_parser_from_namestring(defaults);
	gensymed_symbol = NTH_VALUE((SI_Long)2L, result);
	convert_file_strings_to_uppercase_p = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_convert_file_strings_to_uppercase_p);
    }
    else
	convert_file_strings_to_uppercase_p = Nil;
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      host = g2int_copy_pathname_contents(host);
      device = g2int_copy_pathname_contents(device);
      if (CONSP(directory_1)) {
	  directory_component = Nil;
	  ab_loop_list_ = directory_1;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  directory_component = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loopvar__2 = 
		  g2int_gensym_cons_1(g2int_copy_pathname_contents(directory_component),
		  Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop;
	end_loop:
	  directory_1 = ab_loopvar_;
	  goto end;
	  directory_1 = Qnil;
	end:;
      }
      else if (g2int_text_string_p(directory_1))
	  directory_1 = 
		  g2int_copy_directory_components_from_directory_string(directory_1);
      else
	  directory_1 = g2int_copy_pathname_contents(directory_1);
      name = g2int_copy_pathname_contents(name);
      type = g2int_copy_pathname_contents(type);
      version = g2int_copy_pathname_contents(version);
      result = g2int_gensym_make_pathname_without_copying(7,host,device,
	      directory_1,name,type,version,defaults);
    POP_SPECIAL();
    return result;
}

/* GENSYM-MAKE-PATHNAME-FUNCTION */
Object g2int_gensym_make_pathname_function varargs_1(int, n)
{
    Object host, device, directory_1, name, type, version;
    Object defaults;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,22);
    INIT_ARGS_nonrelocating();
    host = REQUIRED_ARG_nonrelocating();
    device = REQUIRED_ARG_nonrelocating();
    directory_1 = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    version = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return g2int_gensym_make_pathname_with_copied_components(host,device,
	    directory_1,name,type,version,defaults);
}

/* COPY-PATHNAME-CONTENTS */
Object g2int_copy_pathname_contents(old_contents)
    Object old_contents;
{
    Object mutable_string_from_symbol;

    x_note_fn_call(32,23);
    if ( !TRUEP(old_contents))
	return VALUES_1(old_contents);
    else if (g2int_text_string_p(old_contents) && 
	    G2int_convert_file_strings_to_uppercase_p)
	return g2int_nstring_upcasew(g2int_copy_text_string(old_contents));
    else if (g2int_text_string_p(old_contents))
	return g2int_copy_text_string(old_contents);
    else if (SYMBOLP(old_contents) && KEYWORDP(old_contents))
	return VALUES_1(old_contents);
    else if (SYMBOLP(old_contents)) {
	mutable_string_from_symbol = 
		g2int_copy_text_string(g2int_symbol_name_text_string(old_contents));
	if (G2int_convert_file_strings_to_uppercase_p)
	    return VALUES_1(mutable_string_from_symbol);
	else
	    return g2int_nstring_downcasew(mutable_string_from_symbol);
    }
    else if (STRINGP(old_contents))
	return g2int_copy_text_string(old_contents);
    else
	return VALUES_1(old_contents);
}

/* COPY-DIRECTORY-CONTENTS */
Object g2int_copy_directory_contents(directory_to_copy)
    Object directory_to_copy;
{
    Object directory_component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(32,24);
    directory_component = Nil;
    ab_loop_list_ = directory_to_copy;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    g2int_gensym_cons_1(g2int_copy_pathname_contents(directory_component),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* COPY-GENSYM-PATHNAME */
Object g2int_copy_gensym_pathname(old_pathname)
    Object old_pathname;
{
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version, new_pathname;
    Object gensymed_symbol, convert_file_strings_to_uppercase_p;
    Object svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,25);
    if ( !TRUEP(old_pathname))
	return VALUES_1(Nil);
    gensym_pathname_host = ISVREF(old_pathname,(SI_Long)1L);
    gensym_pathname_device = ISVREF(old_pathname,(SI_Long)2L);
    gensym_pathname_directory = ISVREF(old_pathname,(SI_Long)3L);
    gensym_pathname_name = ISVREF(old_pathname,(SI_Long)4L);
    gensym_pathname_type = ISVREF(old_pathname,(SI_Long)5L);
    gensym_pathname_version = ISVREF(old_pathname,(SI_Long)6L);
    new_pathname = g2int_make_gensym_pathname_structure_function(Nil,Nil,
	    Nil,Nil,Nil,Nil);
    gensymed_symbol = ISVREF(old_pathname,(SI_Long)8L);
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      svref_new_value = g2int_copy_pathname_contents(gensym_pathname_host);
      SVREF(new_pathname,FIX((SI_Long)1L)) = svref_new_value;
      svref_new_value = g2int_copy_pathname_contents(gensym_pathname_device);
      SVREF(new_pathname,FIX((SI_Long)2L)) = svref_new_value;
      svref_new_value = CONSP(gensym_pathname_directory) ? 
	      g2int_copy_directory_contents(gensym_pathname_directory) : 
	      g2int_copy_pathname_contents(gensym_pathname_directory);
      SVREF(new_pathname,FIX((SI_Long)3L)) = svref_new_value;
      svref_new_value = g2int_copy_pathname_contents(gensym_pathname_name);
      SVREF(new_pathname,FIX((SI_Long)4L)) = svref_new_value;
      svref_new_value = g2int_copy_pathname_contents(gensym_pathname_type);
      SVREF(new_pathname,FIX((SI_Long)5L)) = svref_new_value;
      svref_new_value = g2int_copy_pathname_contents(gensym_pathname_version);
      SVREF(new_pathname,FIX((SI_Long)6L)) = svref_new_value;
      svref_new_value = ISVREF(old_pathname,(SI_Long)8L);
      SVREF(new_pathname,FIX((SI_Long)8L)) = svref_new_value;
      svref_new_value = ISVREF(old_pathname,(SI_Long)9L);
      SVREF(new_pathname,FIX((SI_Long)9L)) = svref_new_value;
      svref_new_value = ISVREF(old_pathname,(SI_Long)10L);
      SVREF(new_pathname,FIX((SI_Long)10L)) = svref_new_value;
      result = VALUES_1(new_pathname);
    POP_SPECIAL();
    return result;
}

/* GENSYM-PATHNAME-CONTENTS-EQUAL-P */
Object g2int_gensym_pathname_contents_equal_p(contents1,contents2)
    Object contents1, contents2;
{
    x_note_fn_call(32,26);
    if (g2int_text_string_p(contents1) && g2int_text_string_p(contents2) 
	    && G2int_convert_file_strings_to_uppercase_p)
	return g2int_string_equalw(contents1,contents2);
    else if (g2int_text_string_p(contents1) && g2int_text_string_p(contents2))
	return g2int_stringeqw(contents1,contents2);
    else
	return VALUES_1(EQL(contents1,contents2) ? T : Nil);
}

/* GENSYM-PATHNAMES-EQUAL-P */
Object g2int_gensym_pathnames_equal_p(pathname1,pathname2)
    Object pathname1, pathname2;
{
    Object file_system1, file_system2, convert_file_strings_to_uppercase_p;
    Object gensym_pathname_host1, gensym_pathname_device1;
    Object gensym_pathname_directory1, gensym_pathname_name1;
    Object gensym_pathname_type1, gensym_pathname_version1;
    Object gensym_pathname_host2, gensym_pathname_device2;
    Object gensym_pathname_directory2, gensym_pathname_name2;
    Object gensym_pathname_type2, gensym_pathname_version2, component1;
    Object ab_loop_list_, component2, ab_loop_list__1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,27);
    if (SIMPLE_VECTOR_P(pathname1) && EQ(ISVREF(pathname1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) && 
	    SIMPLE_VECTOR_P(pathname2) && EQ(ISVREF(pathname2,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	file_system1 = ISVREF(pathname1,(SI_Long)8L);
	file_system2 = ISVREF(pathname2,(SI_Long)8L);
	if (EQ(file_system1,file_system2)) {
	    convert_file_strings_to_uppercase_p = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(file_system1),
		    Qg2int_convert_file_strings_to_uppercase_p);
	    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		    0);
	      gensym_pathname_host1 = ISVREF(pathname1,(SI_Long)1L);
	      gensym_pathname_device1 = ISVREF(pathname1,(SI_Long)2L);
	      gensym_pathname_directory1 = ISVREF(pathname1,(SI_Long)3L);
	      gensym_pathname_name1 = ISVREF(pathname1,(SI_Long)4L);
	      gensym_pathname_type1 = ISVREF(pathname1,(SI_Long)5L);
	      gensym_pathname_version1 = ISVREF(pathname1,(SI_Long)6L);
	      gensym_pathname_host2 = ISVREF(pathname2,(SI_Long)1L);
	      gensym_pathname_device2 = ISVREF(pathname2,(SI_Long)2L);
	      gensym_pathname_directory2 = ISVREF(pathname2,(SI_Long)3L);
	      gensym_pathname_name2 = ISVREF(pathname2,(SI_Long)4L);
	      gensym_pathname_type2 = ISVREF(pathname2,(SI_Long)5L);
	      gensym_pathname_version2 = ISVREF(pathname2,(SI_Long)6L);
	      if (g2int_gensym_pathname_contents_equal_p(gensym_pathname_host1,
		      gensym_pathname_host2) && 
		      g2int_gensym_pathname_contents_equal_p(gensym_pathname_device1,
		      gensym_pathname_device2)) {
		  if (CONSP(gensym_pathname_directory1) && 
			  CONSP(gensym_pathname_directory2)) {
		      if (FIXNUM_EQ(length(gensym_pathname_directory1),
			      length(gensym_pathname_directory2))) {
			  component1 = Nil;
			  ab_loop_list_ = gensym_pathname_directory1;
			  component2 = Nil;
			  ab_loop_list__1 = gensym_pathname_directory2;
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  component1 = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop;
			  component2 = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  if ( 
				  !TRUEP(g2int_gensym_pathname_contents_equal_p(component1,
				  component2))) {
			      temp = TRUEP(Nil);
			      goto end;
			  }
			  goto next_loop;
			end_loop:
			  temp = TRUEP(T);
			  goto end;
			  temp = TRUEP(Qnil);
			end:;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = 
			      TRUEP(g2int_gensym_pathname_contents_equal_p(gensym_pathname_directory1,
			      gensym_pathname_directory2));
	      }
	      else
		  temp = TRUEP(Nil);
	      if ((temp ? 
		      TRUEP(g2int_gensym_pathname_contents_equal_p(gensym_pathname_name1,
		      gensym_pathname_name2)) : TRUEP(Nil)) ? 
		      TRUEP(g2int_gensym_pathname_contents_equal_p(gensym_pathname_type1,
		      gensym_pathname_type2)) : TRUEP(Nil))
		  result = g2int_gensym_pathname_contents_equal_p(gensym_pathname_version1,
			  gensym_pathname_version2);
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GENSYM-PATHNAMES-EQUAL-ENOUGH-P */
Object g2int_gensym_pathnames_equal_enough_p(pathname1,pathname2)
    Object pathname1, pathname2;
{
    Object file_system1, file_system2, convert_file_strings_to_uppercase_p;
    Object gensym_pathname_host1, gensym_pathname_device1;
    Object gensym_pathname_directory1, gensym_pathname_name1;
    Object gensym_pathname_type1, gensym_pathname_version1;
    Object gensym_pathname_host2, gensym_pathname_device2;
    Object gensym_pathname_directory2, gensym_pathname_name2;
    Object gensym_pathname_type2, gensym_pathname_version2, component1;
    Object ab_loop_list_, component2, ab_loop_list__1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,28);
    if (SIMPLE_VECTOR_P(pathname1) && EQ(ISVREF(pathname1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) && 
	    SIMPLE_VECTOR_P(pathname2) && EQ(ISVREF(pathname2,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	file_system1 = ISVREF(pathname1,(SI_Long)8L);
	file_system2 = ISVREF(pathname2,(SI_Long)8L);
	if (EQ(file_system1,file_system2)) {
	    convert_file_strings_to_uppercase_p = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(file_system1),
		    Qg2int_convert_file_strings_to_uppercase_p);
	    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		    0);
	      gensym_pathname_host1 = ISVREF(pathname1,(SI_Long)1L);
	      gensym_pathname_device1 = ISVREF(pathname1,(SI_Long)2L);
	      gensym_pathname_directory1 = ISVREF(pathname1,(SI_Long)3L);
	      gensym_pathname_name1 = ISVREF(pathname1,(SI_Long)4L);
	      gensym_pathname_type1 = ISVREF(pathname1,(SI_Long)5L);
	      gensym_pathname_version1 = ISVREF(pathname1,(SI_Long)6L);
	      gensym_pathname_host2 = ISVREF(pathname2,(SI_Long)1L);
	      gensym_pathname_device2 = ISVREF(pathname2,(SI_Long)2L);
	      gensym_pathname_directory2 = ISVREF(pathname2,(SI_Long)3L);
	      gensym_pathname_name2 = ISVREF(pathname2,(SI_Long)4L);
	      gensym_pathname_type2 = ISVREF(pathname2,(SI_Long)5L);
	      gensym_pathname_version2 = ISVREF(pathname2,(SI_Long)6L);
	      if (g2int_gensym_pathname_contents_equal_p(gensym_pathname_host1,
		      gensym_pathname_host2) && 
		      g2int_gensym_pathname_contents_equal_p(gensym_pathname_device1,
		      gensym_pathname_device2)) {
		  if (CONSP(gensym_pathname_directory1) && 
			  CONSP(gensym_pathname_directory2)) {
		      if (FIXNUM_EQ(length(gensym_pathname_directory1),
			      length(gensym_pathname_directory2))) {
			  component1 = Nil;
			  ab_loop_list_ = gensym_pathname_directory1;
			  component2 = Nil;
			  ab_loop_list__1 = gensym_pathname_directory2;
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  component1 = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop;
			  component2 = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  if ( 
				  !TRUEP(g2int_gensym_pathname_contents_equal_p(component1,
				  component2))) {
			      temp = TRUEP(Nil);
			      goto end;
			  }
			  goto next_loop;
			end_loop:
			  temp = TRUEP(T);
			  goto end;
			  temp = TRUEP(Qnil);
			end:;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = 
			      TRUEP(g2int_gensym_pathname_contents_equal_p(gensym_pathname_directory1,
			      gensym_pathname_directory2));
	      }
	      else
		  temp = TRUEP(Nil);
	      if ((temp ? 
		      TRUEP(g2int_gensym_pathname_contents_equal_p(gensym_pathname_name1,
		      gensym_pathname_name2)) : TRUEP(Nil)) ? 
		      TRUEP(g2int_gensym_pathname_contents_equal_p(gensym_pathname_type1,
		      gensym_pathname_type2)) : TRUEP(Nil)) {
		  if (EQ(gensym_pathname_version1,Knewest) &&  
			  !TRUEP(gensym_pathname_version2))
		      result = VALUES_1(T);
		  else if ( !TRUEP(gensym_pathname_version1) && 
			  EQ(gensym_pathname_version2,Knewest))
		      result = VALUES_1(T);
		  else
		      result = g2int_gensym_pathname_contents_equal_p(gensym_pathname_version1,
			      gensym_pathname_version2);
	      }
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_1;   /* "~a" */

/* FILE-SYSTEM-HOST-AS-TEXT-STRING */
Object g2int_file_system_host_as_text_string(lisp_pathname_host)
    Object lisp_pathname_host;
{
    x_note_fn_call(32,29);
    if (g2int_text_string_p(lisp_pathname_host))
	return g2int_tformat_text_string(2,string_constant_1,
		lisp_pathname_host);
    else if ( !TRUEP(lisp_pathname_host))
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* CONVERT-NAMESTRING-TO-GENSYM-PATHNAME-WITH-KNOWN-PARSER */
Object g2int_convert_namestring_to_gensym_pathname_with_known_parser(namestring_1,
	    filename_parser,namestring_generator)
    Object namestring_1, filename_parser, namestring_generator;
{
    Object temp, pathname_qm;

    x_note_fn_call(32,30);
    temp = SYMBOL_FUNCTION(filename_parser);
    pathname_qm = FUNCALL_1(temp,namestring_1);
    if (pathname_qm) {
	SVREF(pathname_qm,FIX((SI_Long)9L)) = filename_parser;
	SVREF(pathname_qm,FIX((SI_Long)10L)) = namestring_generator;
	return VALUES_1(pathname_qm);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-G2-STREAM-TO-GENSYM-PATHNAME */
Object g2int_convert_g2_stream_to_gensym_pathname(g2_stream)
    Object g2_stream;
{
    x_note_fn_call(32,31);
    return VALUES_1(g2_stream);
}

/* CONVERT-TO-GENSYM-PATHNAME-WITH-KNOWN-PARSER */
Object g2int_convert_to_gensym_pathname_with_known_parser(thing,
	    filename_parser,namestring_generator)
    Object thing, filename_parser, namestring_generator;
{
    x_note_fn_call(32,32);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	return g2int_copy_gensym_pathname(thing);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	return g2int_convert_namestring_to_gensym_pathname_with_known_parser(thing,
		filename_parser,namestring_generator);
    else if (STRINGP(thing))
	return g2int_convert_namestring_to_gensym_pathname_with_known_parser(thing,
		filename_parser,namestring_generator);
    else if (SYMBOLP(thing))
	return g2int_convert_namestring_to_gensym_pathname_with_known_parser(g2int_symbol_name_text_string(thing),
		filename_parser,namestring_generator);
    else if (g2int_g2_stream_p(thing))
	return g2int_convert_g2_stream_to_gensym_pathname(thing);
    else
	return g2int_make_empty_gensym_pathname();
}

/* CONVERT-TO-GENSYM-PATHNAME */
Object g2int_convert_to_gensym_pathname(thing,default_filename_parser,
	    default_namestring_generator)
    Object thing, default_filename_parser, default_namestring_generator;
{
    x_note_fn_call(32,33);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	return g2int_copy_gensym_pathname(thing);
    else if (g2int_text_string_p(thing))
	return g2int_convert_to_gensym_pathname_with_known_parser(thing,
		default_filename_parser,default_namestring_generator);
    else if (STRINGP(thing))
	return g2int_convert_to_gensym_pathname_with_known_parser(thing,
		default_filename_parser,default_namestring_generator);
    else if (SYMBOLP(thing))
	return g2int_convert_to_gensym_pathname_with_known_parser(g2int_symbol_name_text_string(thing),
		default_filename_parser,default_namestring_generator);
    else if (g2int_g2_stream_p(thing))
	return g2int_convert_g2_stream_to_gensym_pathname(thing);
    else
	return g2int_make_empty_gensym_pathname();
}

static Object Krelative;           /* :relative */

static Object Qg2int_gensym;       /* gensym */

/* COALESCE-DIRECTORY-COMPONENTS */
Object g2int_coalesce_directory_components(directory_list)
    Object directory_list;
{
    Object directory_component, ab_loop_list_, result_directory_list;
    Object retain_relative_marker_p, retain_up_marker_p, ab_loop_iter_flag_;
    Object gensym_pop_store, cons_1, next_cons, cdr_new_value;
    Object discarded_component;

    x_note_fn_call(32,34);
    directory_component = Nil;
    ab_loop_list_ = directory_list;
    result_directory_list = Nil;
    retain_relative_marker_p = EQ(CAR(directory_list),Krelative) ? T : Nil;
    retain_up_marker_p = EQ(CAR(directory_list),Kup) ? T : Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_)) {
	retain_relative_marker_p = Nil;
	retain_up_marker_p = retain_up_marker_p ? (EQ(directory_component,
		Kup) ? T : Nil) : Qnil;
    }
    if (EQ(directory_component,Krelative)) {
	if (retain_relative_marker_p)
	    result_directory_list = 
		    g2int_gensym_cons_1(directory_component,
		    result_directory_list);
    }
    else if (EQ(directory_component,Kup)) {
	if (retain_up_marker_p)
	    result_directory_list = 
		    g2int_gensym_cons_1(directory_component,
		    result_directory_list);
	else {
	    gensym_pop_store = Nil;
	    cons_1 = result_directory_list;
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qg2int_gensym);
		cdr_new_value = G2int_available_gensym_conses;
		M_CDR(cons_1) = cdr_new_value;
		G2int_available_gensym_conses = cons_1;
	    }
	    else
		next_cons = Nil;
	    result_directory_list = next_cons;
	    discarded_component = gensym_pop_store;
	    if (g2int_text_string_p(discarded_component))
		g2int_reclaim_text_string(discarded_component);
	}
    }
    else
	result_directory_list = g2int_gensym_cons_1(directory_component,
		result_directory_list);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    g2int_reclaim_gensym_list_1(directory_list);
    return nreverse(result_directory_list);
    return VALUES_1(Qnil);
}

/* CANONICIZE-HOST-NAME-FROM-FILE-SYSTEM */
Object g2int_canonicize_host_name_from_file_system(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(32,35);
    return VALUES_1(pathname_1);
}

static Object Qg2int_unbound_in_protected_let;  /* unbound-in-protected-let */

static Object array_constant;      /* # */

static Object string_constant_2;   /* "~A/" */

/* SUPPLY-HOME-TO-UNIX-PATHNAME */
Object g2int_supply_home_to_unix_pathname(pathname_1)
    Object pathname_1;
{
    volatile Object home_directory_string_qm;
    Object directory_length;
    volatile Object already_terminated_p;
    volatile Object terminated_home_directory_string;
    volatile Object home_directory_pathname;
    Object gensym_pop_store, cons_1, next_cons, temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(32,36);
    SAVE_STACK();
    home_directory_string_qm = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(1)) {
	home_directory_string_qm = 
		g2int_get_gensym_environment_variable(array_constant);
	if (home_directory_string_qm) {
	    directory_length = g2int_lengthw(home_directory_string_qm);
	    if (IFIX(directory_length) > (SI_Long)0L) {
		already_terminated_p = Qg2int_unbound_in_protected_let;
		terminated_home_directory_string = 
			Qg2int_unbound_in_protected_let;
		home_directory_pathname = Qg2int_unbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    already_terminated_p = (SI_Long)47L == 
			    UBYTE_16_ISAREF_1(home_directory_string_qm,
			    IFIX(FIXNUM_SUB1(directory_length))) ? T : Nil;
		    terminated_home_directory_string = 
			    already_terminated_p ? 
			    home_directory_string_qm : 
			    g2int_tformat_text_string(2,string_constant_2,
			    home_directory_string_qm);
		    home_directory_pathname = 
			    g2int_gensym_pathname(terminated_home_directory_string);
		    gensym_pop_store = Nil;
		    cons_1 = ISVREF(pathname_1,(SI_Long)3L);
		    if (cons_1) {
			gensym_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qg2int_gensym);
			temp = G2int_available_gensym_conses;
			M_CDR(cons_1) = temp;
			G2int_available_gensym_conses = cons_1;
		    }
		    else
			next_cons = Nil;
		    SVREF(pathname_1,FIX((SI_Long)3L)) = next_cons;
		    temp = nconc2(ISVREF(home_directory_pathname,
			    (SI_Long)3L),ISVREF(pathname_1,(SI_Long)3L));
		    SVREF(pathname_1,FIX((SI_Long)3L)) = temp;
		    SAVE_VALUES(VALUES_1(SVREF(home_directory_pathname,
			    FIX((SI_Long)3L)) = Nil));
		}
		POP_UNWIND_PROTECT(0);
		if (home_directory_pathname) {
		    if ( !EQ(home_directory_pathname,
			    Qg2int_unbound_in_protected_let))
			g2int_reclaim_gensym_pathname(home_directory_pathname);
		}
		if (terminated_home_directory_string) {
		    if ( !EQ(terminated_home_directory_string,
			    Qg2int_unbound_in_protected_let)) {
			if ( !TRUEP(already_terminated_p))
			    g2int_reclaim_text_string(terminated_home_directory_string);
		    }
		}
		CONTINUE_UNWINDING(0);
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(1);
    if (home_directory_string_qm) {
	if ( !EQ(home_directory_string_qm,Qg2int_unbound_in_protected_let))
	    g2int_reclaim_text_string(home_directory_string_qm);
    }
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Khome;               /* :home */

/* MAYBE-SUPPLY-HOME-TO-POSSIBLE-UNIX-PATHNAME */
Object g2int_maybe_supply_home_to_possible_unix_pathname(pathname_1)
    Object pathname_1;
{
    Object temp;
    char temp_1;

    x_note_fn_call(32,37);
    if (EQ(ISVREF(pathname_1,(SI_Long)8L),Qg2int_unix)) {
	temp = ISVREF(pathname_1,(SI_Long)3L);
	temp_1 = EQ(FIRST(temp),Khome);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	g2int_supply_home_to_unix_pathname(pathname_1);
    return VALUES_1(pathname_1);
}

Object G2int_inside_handling_gensym_file_errors_scope_p = UNBOUND;

Object G2int_gensym_file_error_occurred_p = UNBOUND;

static Object Qg2int_gensym_file_error_catch_tag;  /* gensym-file-error-catch-tag */

static Object Qg2int_tformat_text_string;  /* tformat-text-string */

/* SIGNAL-GENSYM-FILE-ERROR */
Object g2int_signal_gensym_file_error(file_error_string,arguments_list)
    Object file_error_string, arguments_list;
{
    Object temp, report_string, error_arg, ab_loop_list_;
    Object result;

    x_note_fn_call(32,38);
    if (G2int_inside_handling_gensym_file_errors_scope_p) {
	G2int_gensym_file_error_occurred_p = T;
	result = g2int_gensym_cons_1(file_error_string,arguments_list);
	THROW(Qg2int_gensym_file_error_catch_tag,result);
    }
    else {
	temp = SYMBOL_FUNCTION(Qg2int_tformat_text_string);
	report_string = APPLY_2(temp,file_error_string,arguments_list);
	g2int_notify_user_at_console(2,string_constant_1,report_string);
	g2int_reclaim_text_string(report_string);
	if (arguments_list) {
	    error_arg = Nil;
	    ab_loop_list_ = arguments_list;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    error_arg = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (g2int_text_string_p(error_arg))
		g2int_reclaim_text_string(error_arg);
	    goto next_loop;
	  end_loop:
	    g2int_reclaim_gensym_list_1(arguments_list);
	}
	return g2int_abort(0);
    }
}

Object G2int_report_filename_parsing_errors_in_development_p = UNBOUND;

/* VALID-PATHNAME-P */
Object g2int_valid_pathname_p(convertible_thing)
    Object convertible_thing;
{
    Object report_filename_parsing_errors_in_development_p;
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(32,39);
    report_filename_parsing_errors_in_development_p = Nil;
    PUSH_SPECIAL(G2int_report_filename_parsing_errors_in_development_p,report_filename_parsing_errors_in_development_p,
	    1);
      if (EQUAL(convertible_thing,Nil))
	  result = VALUES_1(Nil);
      else {
	  current_local_filename_parser = G2int_local_filename_parser;
	  current_local_namestring_generator = 
		  G2int_local_namestring_generator;
	  convert_file_strings_to_uppercase_p = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		  Qg2int_convert_file_strings_to_uppercase_p);
	  PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		  0);
	    pathname_qm = 
		    g2int_convert_to_gensym_pathname(convertible_thing,
		    current_local_filename_parser,
		    current_local_namestring_generator);
	    if (pathname_qm) {
		g2int_reclaim_gensym_pathname(pathname_qm);
		result = VALUES_1(T);
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return result;
}

static Object array_constant_1;    /* # */

static Object Qg2int_generalized_dos;  /* generalized-dos */

/* VALID-DIRECTORY-P */
Object g2int_valid_directory_p(convertible_thing)
    Object convertible_thing;
{
    Object report_filename_parsing_errors_in_development_p;
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(32,40);
    SAVE_STACK();
    report_filename_parsing_errors_in_development_p = Nil;
    PUSH_SPECIAL(G2int_report_filename_parsing_errors_in_development_p,report_filename_parsing_errors_in_development_p,
	    1);
      current_local_filename_parser = G2int_local_filename_parser;
      current_local_namestring_generator = G2int_local_namestring_generator;
      convert_file_strings_to_uppercase_p = 
	      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	      Qg2int_convert_file_strings_to_uppercase_p);
      PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	      0);
	pathname_qm = Qg2int_unbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    pathname_qm = 
		    g2int_convert_to_gensym_pathname(convertible_thing,
		    current_local_filename_parser,
		    current_local_namestring_generator);
	    if (pathname_qm) {
		temp = ISVREF(pathname_qm,(SI_Long)8L);
		if (EQ(temp,Qg2int_unix))
		    temp = ISVREF(pathname_qm,(SI_Long)4L);
		else if (EQ(temp,Qg2int_vms))
		    temp = ISVREF(pathname_qm,(SI_Long)4L) ? 
			    g2int_string_equalw(ISVREF(pathname_qm,
			    (SI_Long)5L),array_constant_1) : Qnil;
		else if (EQ(temp,Qg2int_dos) || EQ(temp,Qg2int_win32) || 
			EQ(temp,Qg2int_generalized_dos))
		    temp = ISVREF(pathname_qm,(SI_Long)4L);
		else
		    temp = Nil;
		if (temp)
		    SAVE_VALUES(VALUES_1(T));
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	POP_UNWIND_PROTECT(0);
	if (pathname_qm) {
	    if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
		if (pathname_qm)
		    g2int_reclaim_gensym_pathname(pathname_qm);
	    }
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-WILD-PATHNAME-P */
Object g2int_gensym_wild_pathname_p(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object contents, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,41);
    SAVE_STACK();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      contents = ISVREF(pathname_qm,(SI_Long)4L);
	      temp = g2int_text_string_p(contents) ? 
		      g2int_wild_regular_expression_string_p(contents) : 
		      EQ(Kwild,contents) ? T : Nil;
	      if (temp);
	      else {
		  contents = ISVREF(pathname_qm,(SI_Long)5L);
		  temp = g2int_text_string_p(contents) ? 
			  g2int_wild_regular_expression_string_p(contents) 
			  : EQ(Kwild,contents) ? T : Nil;
	      }
	      if (temp)
		  SAVE_VALUES(VALUES_1(temp));
	      else {
		  contents = ISVREF(pathname_qm,(SI_Long)6L);
		  if (g2int_text_string_p(contents))
		      SAVE_VALUES(g2int_wild_regular_expression_string_p(contents));
		  else
		      SAVE_VALUES(VALUES_1(EQ(Kwild,contents) ? T : Nil));
	      }
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
      }
      POP_UNWIND_PROTECT(0);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object array_constant_2;    /* # */

/* GENSYM-NAMESTRING */
Object g2int_gensym_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object gensymed_symbol, component, ab_loop_list_, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,42);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
	      if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		      Qg2int_convert_file_strings_to_uppercase_p) ? 
		      TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		  component = ISVREF(pathname_qm,(SI_Long)1L);
		  if (g2int_text_string_p(component)) {
		      if ( 
			      !TRUEP(g2int_wild_regular_expression_string_p(component)))
			  g2int_nstring_downcasew(component);
		  }
		  component = ISVREF(pathname_qm,(SI_Long)2L);
		  if (g2int_text_string_p(component)) {
		      if ( 
			      !TRUEP(g2int_wild_regular_expression_string_p(component)))
			  g2int_nstring_downcasew(component);
		  }
		  component = Nil;
		  ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  component = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (g2int_text_string_p(component)) {
		      if ( 
			      !TRUEP(g2int_wild_regular_expression_string_p(component)))
			  g2int_nstring_downcasew(component);
		  }
		  goto next_loop;
		end_loop:;
		  component = ISVREF(pathname_qm,(SI_Long)4L);
		  if (g2int_text_string_p(component)) {
		      if ( 
			      !TRUEP(g2int_wild_regular_expression_string_p(component)))
			  g2int_nstring_downcasew(component);
		  }
		  component = ISVREF(pathname_qm,(SI_Long)5L);
		  if (g2int_text_string_p(component)) {
		      if ( 
			      !TRUEP(g2int_wild_regular_expression_string_p(component)))
			  g2int_nstring_downcasew(component);
		  }
		  component = ISVREF(pathname_qm,(SI_Long)6L);
		  if (g2int_text_string_p(component)) {
		      if ( 
			      !TRUEP(g2int_wild_regular_expression_string_p(component)))
			  g2int_nstring_downcasew(component);
		  }
	      }
	      temp = ISVREF(pathname_qm,(SI_Long)10L);
	      internal_namestring = FUNCALL_1(temp,pathname_qm);
	      SAVE_VALUES(VALUES_1(internal_namestring));
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(0);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-NAMESTRING-AS-TEXT-STRING */
Object g2int_gensym_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,43);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = g2int_gensym_namestring(2,convertible_thing,
	    prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

static Object Qg2int_namestring_as_gensym_string;  /* namestring-as-gensym-string */

/* NAMESTRING-AS-GENSYM-STRING */
Object g2int_namestring_as_gensym_string(pathname_1)
    Object pathname_1;
{
    Object namestring_1, gensym_string;

    x_note_fn_call(32,44);
    namestring_1 = g2int_gensym_namestring(1,pathname_1);
    gensym_string = g2int_export_text_string(2,namestring_1,
	    Qg2int_namestring_as_gensym_string);
    g2int_reclaim_wide_string(namestring_1);
    return VALUES_1(gensym_string);
}

/* GENSYM-FILE-NAMESTRING */
Object g2int_gensym_file_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,45);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)4L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)5L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)6L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-FILE-NAMESTRING-AS-TEXT-STRING */
Object g2int_gensym_file_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,46);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = g2int_gensym_file_namestring(2,convertible_thing,
	    prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

/* GENSYM-HOST-NAMESTRING */
Object g2int_gensym_host_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_directory;
    Object old_gensym_pathname_device, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,47);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)1L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DEVICE-NAMESTRING */
Object g2int_gensym_device_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_directory;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,48);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)2L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-NAMESTRING */
Object g2int_gensym_directory_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, ab_loop_list_;
    Object temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,49);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-NAMESTRING-AS-TEXT-STRING */
Object g2int_gensym_directory_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,50);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = g2int_gensym_directory_namestring(2,convertible_thing,
	    prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

/* GENSYM-BASE-NAMESTRING */
Object g2int_gensym_base_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,51);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)4L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-TYPE-NAMESTRING */
Object g2int_gensym_type_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_name;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,52);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)5L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-VERSION-NAMESTRING */
Object g2int_gensym_version_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_type, old_gensym_pathname_name;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,53);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)6L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-NAMESTRING-OF-DIRECTORY-AS-FILE */
Object g2int_gensym_namestring_of_directory_as_file(pathname_1)
    Object pathname_1;
{
    Object directory_1;
    volatile Object all_but_last_of_directory;
    volatile Object pathname_of_directory_as_file;
    Object len, dn, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_iter_flag_, temp, temp_1, temp_2, temp_3;
    SI_Long i;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(32,54);
    SAVE_STACK();
    directory_1 = Qg2int_unbound_in_protected_let;
    all_but_last_of_directory = Qg2int_unbound_in_protected_let;
    pathname_of_directory_as_file = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	directory_1 = ISVREF(pathname_1,(SI_Long)3L);
	if (LISTP(directory_1)) {
	    len = Nil;
	    dn = Nil;
	    ab_loop_list_ = directory_1;
	    i = (SI_Long)1L;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    len = length(directory_1);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    dn = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		i = i + (SI_Long)1L;
	    if ( !(i == IFIX(len))) {
		ab_loopvar__2 = g2int_gensym_cons_1(dn,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    all_but_last_of_directory = ab_loopvar_;
	    goto end;
	    all_but_last_of_directory = Qnil;
	  end:;
	}
	else
	    all_but_last_of_directory = directory_1;
	temp = ISVREF(pathname_1,(SI_Long)1L);
	temp_1 = ISVREF(pathname_1,(SI_Long)2L);
	temp_2 = all_but_last_of_directory;
	if (CONSP(directory_1)) {
	    temp_3 = last(directory_1,_);
	    temp_3 = CAR(temp_3);
	}
	else
	    temp_3 = Nil;
	pathname_of_directory_as_file = 
		g2int_gensym_make_pathname_with_copied_components(temp,
		temp_1,temp_2,temp_3,Nil,Nil,Nil);
	SAVE_VALUES(g2int_gensym_namestring(1,pathname_of_directory_as_file));
    }
    POP_UNWIND_PROTECT(0);
    if (pathname_of_directory_as_file) {
	if ( !EQ(pathname_of_directory_as_file,
		Qg2int_unbound_in_protected_let))
	    g2int_reclaim_gensym_pathname(pathname_of_directory_as_file);
    }
    if (all_but_last_of_directory) {
	if ( !EQ(all_but_last_of_directory,Qg2int_unbound_in_protected_let)) {
	    if (CONSP(all_but_last_of_directory))
		g2int_reclaim_gensym_list_1(all_but_last_of_directory);
	}
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* GENSYM-HOST-AND-DIRECTORY-NAMESTRING */
Object g2int_gensym_host_and_directory_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_device;
    Object gensymed_symbol, component, ab_loop_list_, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,55);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)1L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_3;   /* "~a*.*" */

/* GENSYM-DIRECTORY-AND-WILDCARD-FILE-NAMESTRING */
Object g2int_gensym_directory_and_wildcard_file_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, host_and_directory_namestring, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,56);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    host_and_directory_namestring = 
	    g2int_gensym_host_and_directory_namestring(2,convertible_thing,
	    prefer_lowercase_p);
    temp = g2int_tformat_text_string(2,string_constant_3,
	    host_and_directory_namestring);
    g2int_reclaim_text_string(host_and_directory_namestring);
    return VALUES_1(temp);
}

/* GENSYM-DEVICE-AND-DIRECTORY-NAMESTRING */
Object g2int_gensym_device_and_directory_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_host, gensymed_symbol;
    Object component, ab_loop_list_, temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,57);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)2L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-AND-ABOVE-NAMESTRING */
Object g2int_gensym_directory_and_above_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, gensymed_symbol, component, ab_loop_list_;
    Object temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,58);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)1L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)2L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-AND-ABOVE-NAMESTRING-AS-TEXT-STRING */
Object g2int_gensym_directory_and_above_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,59);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = g2int_gensym_directory_and_above_namestring(2,
	    convertible_thing,prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

/* GENSYM-NAME-AND-TYPE-NAMESTRING */
Object g2int_gensym_name_and_type_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_directory;
    Object old_gensym_pathname_device, old_gensym_pathname_host;
    Object gensymed_symbol, component, temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,60);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_convert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)4L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)5L);
		      if (g2int_text_string_p(component)) {
			  if ( 
				  !TRUEP(g2int_wild_regular_expression_string_p(component)))
			      g2int_nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(g2int_copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (pathname_qm)
		  g2int_reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qg2int_gensym_enough_namestring;  /* gensym-enough-namestring */

static Object Kabsolute;           /* :absolute */

static Object string_constant_4;   /* "" */

/* GENSYM-ENOUGH-NAMESTRING */
Object g2int_gensym_enough_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object default_1, tag_temp, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    volatile Object default_pathname_qm;
    Object file_system, temp, gensym_pathname_host1, gensym_pathname_device1;
    Object gensym_pathname_directory1, gensym_pathname_name1;
    Object gensym_pathname_type1, gensym_pathname_version1;
    Object gensym_pathname_host2, gensym_pathname_device2;
    Object gensym_pathname_directory2, gensym_pathname_name2;
    Object gensym_pathname_type2, gensym_pathname_version2;
    Object first_directory_component1, absolute_marker_to_restore_qm;
    Object component_1_qm, component_2_qm, reclaimable_components;
    Object gensym_pathname_directory1_old_value, temp_1;
    Object gensym_pathname_directory2_old_value, remaining_directory_qm;
    Object reclaimable_component, ab_loop_list_, gensym_pop_store, cons_1;
    Object next_cons, car_1, cdr_1;
    SI_Long number_of_components_dropped, count_1, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(32,61);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : 
	    G2int_gensym_default_pathname_defaults;
    END_ARGS_nonrelocating();
    tag_temp = UNIQUE_TAG(Qg2int_gensym_enough_namestring);
    if (PUSH_CATCH(tag_temp,1)) {
	current_local_filename_parser = G2int_local_filename_parser;
	current_local_namestring_generator = G2int_local_namestring_generator;
	convert_file_strings_to_uppercase_p = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		Qg2int_convert_file_strings_to_uppercase_p);
	PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		1);
	  pathname_qm = Qg2int_unbound_in_protected_let;
	  default_pathname_qm = Qg2int_unbound_in_protected_let;
	  if (PUSH_UNWIND_PROTECT(0)) {
	      pathname_qm = 
		      g2int_convert_to_gensym_pathname(convertible_thing,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      default_pathname_qm = 
		      g2int_convert_to_gensym_pathname(default_1,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      file_system = pathname_qm ? ISVREF(pathname_qm,(SI_Long)8L) :
		       Qnil;
	      if (pathname_qm && default_pathname_qm && EQ(file_system,
		      ISVREF(default_pathname_qm,(SI_Long)8L))) {
		  convert_file_strings_to_uppercase_p = 
			  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(file_system),
			  Qg2int_convert_file_strings_to_uppercase_p);
		  PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
			  0);
		    temp = 
			    g2int_coalesce_directory_components(ISVREF(pathname_qm,
			    (SI_Long)3L));
		    SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
		    temp = 
			    g2int_coalesce_directory_components(ISVREF(default_pathname_qm,
			    (SI_Long)3L));
		    SVREF(default_pathname_qm,FIX((SI_Long)3L)) = temp;
		    gensym_pathname_host1 = ISVREF(pathname_qm,(SI_Long)1L);
		    gensym_pathname_device1 = ISVREF(pathname_qm,(SI_Long)2L);
		    gensym_pathname_directory1 = ISVREF(pathname_qm,
			    (SI_Long)3L);
		    gensym_pathname_name1 = ISVREF(pathname_qm,(SI_Long)4L);
		    gensym_pathname_type1 = ISVREF(pathname_qm,(SI_Long)5L);
		    gensym_pathname_version1 = ISVREF(pathname_qm,(SI_Long)6L);
		    gensym_pathname_host2 = ISVREF(default_pathname_qm,
			    (SI_Long)1L);
		    gensym_pathname_device2 = ISVREF(default_pathname_qm,
			    (SI_Long)2L);
		    gensym_pathname_directory2 = 
			    ISVREF(default_pathname_qm,(SI_Long)3L);
		    gensym_pathname_name2 = ISVREF(default_pathname_qm,
			    (SI_Long)4L);
		    gensym_pathname_type2 = ISVREF(default_pathname_qm,
			    (SI_Long)5L);
		    gensym_pathname_version2 = ISVREF(default_pathname_qm,
			    (SI_Long)6L);
		    if (g2int_gensym_pathname_contents_equal_p(gensym_pathname_host1,
			    gensym_pathname_host2)) {
			if (g2int_text_string_p(gensym_pathname_host1))
			    g2int_reclaim_text_string(gensym_pathname_host1);
			SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		    }
		    else if ( !TRUEP(Nil))
			goto provide_namestring;
		    if (g2int_gensym_pathname_contents_equal_p(gensym_pathname_device1,
			    gensym_pathname_device2)) {
			if (g2int_text_string_p(gensym_pathname_device1))
			    g2int_reclaim_text_string(gensym_pathname_device1);
			SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		    }
		    else if ( !TRUEP(Nil))
			goto provide_namestring;
		    first_directory_component1 = 
			    FIRST(gensym_pathname_directory1);
		    absolute_marker_to_restore_qm = 
			    EQ(first_directory_component1,Kabsolute) && 
			    EQ(first_directory_component1,
			    FIRST(gensym_pathname_directory2)) ? 
			    first_directory_component1 : Qnil;
		    component_1_qm = Nil;
		    component_2_qm = Nil;
		    number_of_components_dropped = (SI_Long)0L;
		    reclaimable_components = Nil;
		    component_1_qm = CAR(gensym_pathname_directory1);
		    component_2_qm = CAR(gensym_pathname_directory2);
		  next_loop:
		    if ( !((component_1_qm || component_2_qm) && 
			    g2int_gensym_pathname_contents_equal_p(component_1_qm,
			    component_2_qm)))
			goto end_loop;
		    gensym_pathname_directory1_old_value = 
			    gensym_pathname_directory1;
		    temp_1 = FIRST(gensym_pathname_directory1_old_value);
		    gensym_pathname_directory1 = 
			    REST(gensym_pathname_directory1_old_value);
		    reclaimable_components = g2int_gensym_cons_1(temp_1,
			    reclaimable_components);
		    gensym_pathname_directory2_old_value = 
			    gensym_pathname_directory2;
		    gensym_pathname_directory2 = 
			    REST(gensym_pathname_directory2_old_value);
		    component_1_qm = CAR(gensym_pathname_directory1);
		    component_2_qm = CAR(gensym_pathname_directory2);
		    number_of_components_dropped = 
			    number_of_components_dropped + (SI_Long)1L;
		    goto next_loop;
		  end_loop:
		    remaining_directory_qm = 
			    g2int_copy_list_using_gensym_conses_1(gensym_pathname_directory1);
		    reclaimable_component = Nil;
		    ab_loop_list_ = reclaimable_components;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    reclaimable_component = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (g2int_text_string_p(reclaimable_component))
			g2int_reclaim_text_string(reclaimable_component);
		    goto next_loop_1;
		  end_loop_1:
		    g2int_reclaim_gensym_list_1(reclaimable_components);
		    g2int_reclaim_gensym_list_1(ISVREF(pathname_qm,
			    (SI_Long)3L));
		  next_loop_2:
		    if ( !EQ(CAR(remaining_directory_qm),Krelative))
			goto end_loop_2;
		    gensym_pop_store = Nil;
		    cons_1 = remaining_directory_qm;
		    if (cons_1) {
			gensym_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qg2int_gensym);
			temp = G2int_available_gensym_conses;
			M_CDR(cons_1) = temp;
			G2int_available_gensym_conses = cons_1;
		    }
		    else
			next_cons = Nil;
		    remaining_directory_qm = next_cons;
		    goto next_loop_2;
		  end_loop_2:
		    SVREF(pathname_qm,FIX((SI_Long)3L)) = 
			    remaining_directory_qm;
		    if (remaining_directory_qm) {
			if (absolute_marker_to_restore_qm && 
				number_of_components_dropped <= (SI_Long)1L) {
			    car_1 = Kabsolute;
			    cdr_1 = ISVREF(pathname_qm,(SI_Long)3L);
			    temp = g2int_gensym_cons_1(car_1,cdr_1);
			    SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
			}
			if (EQ(ISVREF(pathname_qm,(SI_Long)8L),Qg2int_vms) 
				&& number_of_components_dropped >= 
				    (SI_Long)1L) {
			    car_1 = Krelative;
			    cdr_1 = ISVREF(pathname_qm,(SI_Long)3L);
			    temp = g2int_gensym_cons_1(car_1,cdr_1);
			    SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
			}
		    }
		    else {
			count_1 = (SI_Long)1L;
			ab_loop_bind_ = 
				IFIX(length(gensym_pathname_directory2));
		      next_loop_3:
			if (count_1 > ab_loop_bind_)
			    goto end_loop_3;
			car_1 = Kup;
			cdr_1 = ISVREF(pathname_qm,(SI_Long)3L);
			temp = g2int_gensym_cons_1(car_1,cdr_1);
			SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
			count_1 = count_1 + (SI_Long)1L;
			goto next_loop_3;
		      end_loop_3:;
		    }
		    if (g2int_gensym_pathname_contents_equal_p(gensym_pathname_name1,
			    gensym_pathname_name2)) {
			if (g2int_text_string_p(gensym_pathname_name1))
			    g2int_reclaim_text_string(gensym_pathname_name1);
			SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		    }
		    else if ( !TRUEP(T))
			goto provide_namestring;
		    if (g2int_gensym_pathname_contents_equal_p(gensym_pathname_type1,
			    gensym_pathname_type2)) {
			if (g2int_text_string_p(gensym_pathname_type1))
			    g2int_reclaim_text_string(gensym_pathname_type1);
			SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		    }
		    else if ( !TRUEP(T))
			goto provide_namestring;
		    if (g2int_gensym_pathname_contents_equal_p(gensym_pathname_version1,
			    gensym_pathname_version2)) {
			if (g2int_text_string_p(gensym_pathname_version1))
			    g2int_reclaim_text_string(gensym_pathname_version1);
			SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		    }
		    else if ( !TRUEP(T))
			goto provide_namestring;
		  provide_namestring:
		    result = g2int_gensym_namestring(1,pathname_qm);
		    THROW(tag_temp,result);
		    SAVE_VALUES(VALUES_1(Qnil));
		  POP_SPECIAL();
	      }
	      else
		  SAVE_VALUES(VALUES_1(string_constant_4));
	  }
	  POP_UNWIND_PROTECT(0);
	  if (default_pathname_qm) {
	      if ( !EQ(default_pathname_qm,Qg2int_unbound_in_protected_let)) {
		  if (default_pathname_qm)
		      g2int_reclaim_gensym_pathname(default_pathname_qm);
	      }
	  }
	  if (pathname_qm) {
	      if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
		  if (pathname_qm)
		      g2int_reclaim_gensym_pathname(pathname_qm);
	      }
	  }
	  CONTINUE_UNWINDING(0);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

/* GENSYM-ENOUGH-NAMESTRING-AS-TEXT-STRING */
Object g2int_gensym_enough_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object default_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,62);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : 
	    G2int_gensym_default_pathname_defaults;
    END_ARGS_nonrelocating();
    return g2int_gensym_enough_namestring(2,convertible_thing,default_1);
}

/* GENSYM-PATHNAME-VERSION-EMPTY-P */
Object g2int_gensym_pathname_version_empty_p(pathname_1)
    Object pathname_1;
{
    Object version, temp;

    x_note_fn_call(32,63);
    version = ISVREF(pathname_1,(SI_Long)6L);
    temp =  !TRUEP(version) ? T : Nil;
    if (temp);
    else
	temp = EQ(version,Kunspecific) ? T : Nil;
    return VALUES_1(temp);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* GENSYM-DIRECTORY-AS-FILE */
Object g2int_gensym_directory_as_file(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm;
    Object directory_subcomponents, svref_new_value, subcomponent_cons;
    Object pointer_to_last_subcomponent, last_subcomponent, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,64);
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
	      current_local_filename_parser,
	      current_local_namestring_generator);
      if (pathname_qm) {
	  if (ISVREF(pathname_qm,(SI_Long)4L) || ISVREF(pathname_qm,
		  (SI_Long)5L) || ISVREF(pathname_qm,(SI_Long)6L)) {
	      g2int_reclaim_gensym_pathname(pathname_qm);
	      pathname_qm = Nil;
	  }
	  else {
	      directory_subcomponents = ISVREF(pathname_qm,(SI_Long)3L);
	      if ( !TRUEP(directory_subcomponents)) {
		  svref_new_value = g2int_gensym_cons_1(Kabsolute,Nil);
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = svref_new_value;
	      }
	      else if (EQUAL(directory_subcomponents,list_constant_1));
	      else if (EQUAL(directory_subcomponents,list_constant)) {
		  g2int_reclaim_gensym_pathname(pathname_qm);
		  pathname_qm = Nil;
	      }
	      else {
		  if ( 
			  !TRUEP(g2int_memq_function(CAR(directory_subcomponents),
			  list_constant_2)))
		      directory_subcomponents = 
			      g2int_gensym_cons_1(Krelative,
			      directory_subcomponents);
		  subcomponent_cons = directory_subcomponents;
		next_loop:
		  if ( !TRUEP(subcomponent_cons))
		      goto end_loop;
		  if ( !TRUEP(CDDR(subcomponent_cons))) {
		      pointer_to_last_subcomponent = subcomponent_cons;
		      goto end;
		  }
		  subcomponent_cons = M_CDR(subcomponent_cons);
		  goto next_loop;
		end_loop:
		  pointer_to_last_subcomponent = Qnil;
		end:;
		  last_subcomponent = CADR(pointer_to_last_subcomponent);
		  M_CDR(pointer_to_last_subcomponent) = Nil;
		  temp = ISVREF(pathname_qm,(SI_Long)8L);
		  if (EQ(temp,Qg2int_unix))
		      SVREF(pathname_qm,FIX((SI_Long)4L)) = last_subcomponent;
		  else if (EQ(temp,Qg2int_vms)) {
		      SVREF(pathname_qm,FIX((SI_Long)4L)) = last_subcomponent;
		      svref_new_value = 
			      g2int_copy_constant_wide_string_given_length(array_constant_1,
			      FIX((SI_Long)3L));
		      SVREF(pathname_qm,FIX((SI_Long)5L)) = svref_new_value;
		  }
		  else if (EQ(temp,Qg2int_dos) || EQ(temp,Qg2int_win32) || 
			  EQ(temp,Qg2int_generalized_dos))
		      SVREF(pathname_qm,FIX((SI_Long)4L)) = last_subcomponent;
		  else {
		      g2int_reclaim_gensym_pathname(pathname_qm);
		      pathname_qm = Nil;
		  }
	      }
	  }
      }
      result = VALUES_1(pathname_qm);
    POP_SPECIAL();
    return result;
}

/* GENSYM-FILE-AS-DIRECTORY */
Object g2int_gensym_file_as_directory(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm, temp;
    Object final_directory_component, svref_new_value, pathname_name_1;
    Object pathname_type_1, pathname_version_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,65);
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
	      current_local_filename_parser,
	      current_local_namestring_generator);
      if (pathname_qm) {
	  if (g2int_valid_directory_p(pathname_qm)) {
	      temp = ISVREF(pathname_qm,(SI_Long)8L);
	      final_directory_component = EQ(temp,Qg2int_unix) || EQ(temp,
		      Qg2int_win32) || EQ(temp,Qg2int_dos) ? 
		      g2int_gensym_file_namestring(1,pathname_qm) : 
		      g2int_copy_text_string(ISVREF(pathname_qm,(SI_Long)4L));
	      svref_new_value = nconc2(ISVREF(pathname_qm,(SI_Long)3L),
		      g2int_gensym_cons_1(final_directory_component,Nil));
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = svref_new_value;
	      pathname_name_1 = ISVREF(pathname_qm,(SI_Long)4L);
	      if (g2int_text_string_p(pathname_name_1))
		  g2int_reclaim_text_string(pathname_name_1);
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
	      pathname_type_1 = ISVREF(pathname_qm,(SI_Long)5L);
	      if (g2int_text_string_p(pathname_type_1))
		  g2int_reclaim_text_string(pathname_type_1);
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
	      pathname_version_1 = ISVREF(pathname_qm,(SI_Long)6L);
	      if (g2int_text_string_p(pathname_version_1))
		  g2int_reclaim_text_string(pathname_version_1);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
	      result = VALUES_1(pathname_qm);
	  }
	  else {
	      g2int_reclaim_gensym_pathname(pathname_qm);
	      result = VALUES_1(Nil);
	  }
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* GET-NEW-DIRECTORY-PATHNAME-DWIM */
Object g2int_get_new_directory_pathname_dwim(new_directory_string)
    Object new_directory_string;
{
    Object raw_pathname_qm, raw_pathname_name, raw_pathname_type, temp;
    Object raw_pathname_version;

    x_note_fn_call(32,66);
    raw_pathname_qm = g2int_gensym_pathname(new_directory_string);
    if (raw_pathname_qm) {
	raw_pathname_name = ISVREF(raw_pathname_qm,(SI_Long)4L);
	raw_pathname_type = ISVREF(raw_pathname_qm,(SI_Long)5L);
	if ( !TRUEP(raw_pathname_name) &&  !TRUEP(raw_pathname_type) && 
		g2int_gensym_pathname_version_empty_p(raw_pathname_qm))
	    return VALUES_1(raw_pathname_qm);
	else if (g2int_g2_stream_directory_p(new_directory_string)) {
	    temp = g2int_gensym_file_as_directory(raw_pathname_qm);
	    g2int_reclaim_gensym_pathname(raw_pathname_qm);
	    return VALUES_1(temp);
	}
	else {
	    raw_pathname_version = ISVREF(raw_pathname_qm,(SI_Long)6L);
	    if (g2int_text_string_p(raw_pathname_name))
		g2int_reclaim_text_string(raw_pathname_name);
	    SVREF(raw_pathname_qm,FIX((SI_Long)4L)) = Nil;
	    if (g2int_text_string_p(raw_pathname_type))
		g2int_reclaim_text_string(raw_pathname_type);
	    SVREF(raw_pathname_qm,FIX((SI_Long)5L)) = Nil;
	    if (g2int_text_string_p(raw_pathname_version))
		g2int_reclaim_text_string(raw_pathname_version);
	    SVREF(raw_pathname_qm,FIX((SI_Long)6L)) = Nil;
	    return VALUES_1(raw_pathname_qm);
	}
    }
    else
	return VALUES_1(Nil);
}

/* GENSYM-PATHNAME */
Object g2int_gensym_pathname(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,67);
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
	      current_local_filename_parser,
	      current_local_namestring_generator);
      temp = pathname_qm;
      if (temp)
	  result = VALUES_1(temp);
      else
	  result = g2int_make_empty_gensym_pathname();
    POP_SPECIAL();
    return result;
}

/* GET-PARSER-FROM-HOST */
Object g2int_get_parser_from_host(host)
    Object host;
{
    x_note_fn_call(32,68);
    return g2int_get_default_file_system_info();
}

/* GET-PARSER-FROM-NAMESTRING */
Object g2int_get_parser_from_namestring(namestring_1)
    Object namestring_1;
{
    x_note_fn_call(32,69);
    return g2int_get_default_file_system_info();
}

/* PARSER-IN-NAMESTRING-P */
Object g2int_parser_in_namestring_p(namestring_1)
    Object namestring_1;
{
    x_note_fn_call(32,70);
    return VALUES_1(Nil);
}

/* GENSYM-PARSE-NAMESTRING-FUNCTION */
Object g2int_gensym_parse_namestring_function(convertible_thing,host,default_1)
    Object convertible_thing, host, default_1;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object default_pathname_qm;
    Object host_for_conversion, filename_parser, namestring_generator;
    Object pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,71);
    SAVE_STACK();
    current_local_filename_parser = G2int_local_filename_parser;
    current_local_namestring_generator = G2int_local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      default_pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  default_pathname_qm = g2int_convert_to_gensym_pathname(default_1,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  host_for_conversion = host;
	  if (host_for_conversion);
	  else
	      host_for_conversion = default_pathname_qm ? 
		      ISVREF(default_pathname_qm,(SI_Long)1L) : Qnil;
	  result = g2int_get_parser_from_host(host_for_conversion);
	  MVS_2(result,filename_parser,namestring_generator);
	  if ( !TRUEP(filename_parser)) {
	      filename_parser = G2int_local_filename_parser;
	      namestring_generator = G2int_local_namestring_generator;
	  }
	  pathname_qm = g2int_convert_to_gensym_pathname(convertible_thing,
		  filename_parser,namestring_generator);
	  if (pathname_qm) {
	      SVREF(pathname_qm,FIX((SI_Long)9L)) = filename_parser;
	      SVREF(pathname_qm,FIX((SI_Long)10L)) = namestring_generator;
	      SAVE_VALUES(VALUES_1(pathname_qm));
	  }
	  else
	      SAVE_VALUES(g2int_make_empty_gensym_pathname());
      }
      POP_UNWIND_PROTECT(0);
      if (default_pathname_qm) {
	  if ( !EQ(default_pathname_qm,Qg2int_unbound_in_protected_let)) {
	      if (default_pathname_qm)
		  g2int_reclaim_gensym_pathname(default_pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_5;   /* "GENSYM-TRUENAME: Cannot get pathname from stream ~a" */

static Object string_constant_6;   /* "GENSYM-TRUENAME: Cannot access file ~a" */

static Object string_constant_7;   /* "GENSYM-TRUENAME: Cannot obtain pathname for ~a" */

/* GENSYM-TRUENAME */
Object g2int_gensym_truename(convertible_thing)
    Object convertible_thing;
{
    Object pathname_from_stream_qm, temp, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object probed_pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,72);
    SAVE_STACK();
    if (g2int_g2_stream_p(convertible_thing)) {
	pathname_from_stream_qm = g2int_gensym_probe_file(convertible_thing);
	temp = pathname_from_stream_qm;
	if (temp) {
	    RESTORE_STACK();
	    return VALUES_1(temp);
	}
	else {
	    result = g2int_signal_gensym_file_error(string_constant_5,
		    g2int_gensym_cons_1(convertible_thing,Nil));
	    RESTORE_STACK();
	    return result;
	}
    }
    else {
	current_local_filename_parser = G2int_local_filename_parser;
	current_local_namestring_generator = G2int_local_namestring_generator;
	convert_file_strings_to_uppercase_p = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		Qg2int_convert_file_strings_to_uppercase_p);
	PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		0);
	  pathname_qm = Qg2int_unbound_in_protected_let;
	  if (PUSH_UNWIND_PROTECT(0)) {
	      pathname_qm = 
		      g2int_convert_to_gensym_pathname(convertible_thing,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      if (pathname_qm) {
		  probed_pathname_qm = g2int_gensym_probe_file(pathname_qm);
		  temp = probed_pathname_qm;
		  if (temp)
		      SAVE_VALUES(VALUES_1(temp));
		  else
		      SAVE_VALUES(g2int_signal_gensym_file_error(string_constant_6,
			      g2int_gensym_cons_1(convertible_thing,Nil)));
	      }
	      else
		  SAVE_VALUES(g2int_signal_gensym_file_error(string_constant_7,
			  g2int_gensym_cons_1(convertible_thing,Nil)));
	  }
	  POP_UNWIND_PROTECT(0);
	  if (pathname_qm) {
	      if ( !EQ(pathname_qm,Qg2int_unbound_in_protected_let)) {
		  if (pathname_qm)
		      g2int_reclaim_gensym_pathname(pathname_qm);
	      }
	  }
	  CONTINUE_UNWINDING(0);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

Object G2int_merge_pathnames_rules = UNBOUND;

Object G2int_merge_pathnames_rules_sorted_p = UNBOUND;

/* TRANSFER-GENSYM-PATHNAME-CONTENTS */
Object g2int_transfer_gensym_pathname_contents(old_contents,new_contents)
    Object old_contents, new_contents;
{
    Object old_component, ab_loop_list_, new_component, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(32,73);
    if (CONSP(old_contents)) {
	old_component = Nil;
	ab_loop_list_ = old_contents;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	old_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (g2int_text_string_p(old_component))
	    g2int_reclaim_text_string(old_component);
	goto next_loop;
      end_loop:
	g2int_reclaim_gensym_list_1(old_contents);
    }
    else if (g2int_text_string_p(old_contents))
	g2int_reclaim_text_string(old_contents);
    if (CONSP(new_contents)) {
	new_component = Nil;
	ab_loop_list_ = new_contents;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	new_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		g2int_gensym_cons_1(g2int_text_string_p(new_component) ? 
		g2int_copy_text_string(new_component) : new_component,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else if (g2int_text_string_p(new_contents))
	return g2int_copy_text_string(new_contents);
    else
	return VALUES_1(new_contents);
}

/* GET-DEFAULT-FILE-DEVICE-FROM-HOST */
Object g2int_get_default_file_device_from_host(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(32,74);
    return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-DEVICE-DEFAULT-RULE */
Object g2int_merge_pathnames_device_default_rule varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,75);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (ISVREF(original_pathname,(SI_Long)1L) &&  
	    !TRUEP(ISVREF(original_pathname,(SI_Long)2L)) && 
	    g2int_stringeqw(ISVREF(original_pathname,(SI_Long)1L),
	    ISVREF(defaults,(SI_Long)1L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)2L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)2L));
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)2L)) = svref_new_value);
    }
    else if (ISVREF(original_pathname,(SI_Long)1L) &&  
	    !TRUEP(ISVREF(original_pathname,(SI_Long)2L))) {
	if ( !EQ(ISVREF(original_pathname,(SI_Long)2L),Kunspecific)) {
	    old_contents = ISVREF(pathname_1,(SI_Long)2L);
	    svref_new_value = 
		    g2int_transfer_gensym_pathname_contents(old_contents,
		    g2int_get_default_file_device_from_host(original_pathname));
	    return VALUES_1(SVREF(pathname_1,FIX((SI_Long)2L)) = 
		    svref_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-PROPAGATE-FILE-SYSTEM */
Object g2int_merge_pathnames_propagate_file_system varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,76);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)1L))) {
	svref_new_value = ISVREF(defaults,(SI_Long)8L);
	SVREF(pathname_1,FIX((SI_Long)8L)) = svref_new_value;
	svref_new_value = ISVREF(defaults,(SI_Long)9L);
	SVREF(pathname_1,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = ISVREF(defaults,(SI_Long)10L);
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)10L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-REPLACE-UNSPECIFIC-HOST */
Object g2int_merge_pathnames_replace_unspecific_host varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,77);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(ISVREF(original_pathname,(SI_Long)1L),Kunspecific) &&  ! 
	    !TRUEP(ISVREF(defaults,(SI_Long)1L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)1L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)1L));
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)1L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-REPLACE-EMPTY-COMPONENTS */
Object g2int_merge_pathnames_replace_empty_components varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,78);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)1L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)1L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)1L));
	SVREF(pathname_1,FIX((SI_Long)1L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)2L)) &&  
	    !(ISVREF(original_pathname,(SI_Long)1L) || 
	    EQ(ISVREF(pathname_1,(SI_Long)8L),Qg2int_vms) && 
	    ISVREF(original_pathname,(SI_Long)3L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)2L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)2L));
	SVREF(pathname_1,FIX((SI_Long)2L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)3L)) &&  
	    !(EQ(ISVREF(pathname_1,(SI_Long)8L),Qg2int_vms) && 
	    ISVREF(original_pathname,(SI_Long)2L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)3L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)3L));
	SVREF(pathname_1,FIX((SI_Long)3L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)4L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)4L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)4L));
	SVREF(pathname_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)5L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)5L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)5L));
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)5L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-VERSION-DEFAULT-RULE */
Object g2int_merge_pathnames_version_default_rule varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, default_version, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,79);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    default_version = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)6L)) &&  
	    !TRUEP(ISVREF(original_pathname,(SI_Long)4L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)6L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)6L));
	SVREF(pathname_1,FIX((SI_Long)6L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(pathname_1,(SI_Long)6L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)6L);
	svref_new_value = 
		g2int_transfer_gensym_pathname_contents(old_contents,
		default_version);
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)6L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* ELIDE-DIRECTORY-CONTAINING-UP-WITH-DEFAULT-DIRECTORY */
Object g2int_elide_directory_containing_up_with_default_directory(directory_containing_up,
	    default_directory)
    Object directory_containing_up, default_directory;
{
    Object reversed_copy_of_default_directory_qm, directory_component;
    Object ab_loop_list_, gensym_pop_store, cons_1, next_cons, cdr_new_value;
    Object temp;

    x_note_fn_call(32,80);
    reversed_copy_of_default_directory_qm = 
	    nreverse(g2int_copy_directory_contents(default_directory));
    directory_component = Nil;
    ab_loop_list_ = directory_containing_up;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(EQ(directory_component,Kup) && 
	    reversed_copy_of_default_directory_qm && 
	    g2int_text_string_p(CAR(reversed_copy_of_default_directory_qm))))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = directory_containing_up;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	G2int_available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    directory_containing_up = next_cons;
    gensym_pop_store = Nil;
    cons_1 = reversed_copy_of_default_directory_qm;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	G2int_available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    reversed_copy_of_default_directory_qm = next_cons;
    g2int_reclaim_text_string(gensym_pop_store);
    goto next_loop;
  end_loop:
    temp = nreverse(reversed_copy_of_default_directory_qm);
    return VALUES_1(nconc2(temp,directory_containing_up));
    return VALUES_1(Qnil);
}

static Object list_constant_3;     /* # */

/* MERGE-PATHNAMES-MERGE-STRUCTURED-DIRECTORIES */
Object g2int_merge_pathnames_merge_structured_directories varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, temp, directory_so_far, default_directory_qm;
    Object gensymed_symbol, first_component, second_component;
    Object gensym_pop_store, cons_1, next_cons, temp_2;
    Object default_directory_section_to_merge;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,81);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (ISVREF(original_pathname,(SI_Long)3L)) {
	temp = ISVREF(pathname_1,(SI_Long)3L);
	temp_1 = TRUEP(g2int_memq_function(CAR(temp),list_constant_3));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	directory_so_far = ISVREF(pathname_1,(SI_Long)3L);
	default_directory_qm = ISVREF(defaults,(SI_Long)3L);
	if (default_directory_qm) {
	    gensymed_symbol = directory_so_far;
	    first_component = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    second_component = CAR(gensymed_symbol);
	    if (EQ(first_component,Krelative) && EQ(second_component,Kup)) {
		gensym_pop_store = Nil;
		cons_1 = directory_so_far;
		if (cons_1) {
		    gensym_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
		    temp_2 = G2int_available_gensym_conses;
		    M_CDR(cons_1) = temp_2;
		    G2int_available_gensym_conses = cons_1;
		}
		else
		    next_cons = Nil;
		directory_so_far = next_cons;
		temp_2 = 
			g2int_elide_directory_containing_up_with_default_directory(directory_so_far,
			default_directory_qm);
		return VALUES_1(SVREF(pathname_1,FIX((SI_Long)3L)) = temp_2);
	    }
	    else if (EQ(first_component,Kup)) {
		temp_2 = 
			g2int_elide_directory_containing_up_with_default_directory(directory_so_far,
			default_directory_qm);
		return VALUES_1(SVREF(pathname_1,FIX((SI_Long)3L)) = temp_2);
	    }
	    else if (EQ(first_component,Krelative)) {
		gensym_pop_store = Nil;
		cons_1 = directory_so_far;
		if (cons_1) {
		    gensym_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
		    temp_2 = G2int_available_gensym_conses;
		    M_CDR(cons_1) = temp_2;
		    G2int_available_gensym_conses = cons_1;
		}
		else
		    next_cons = Nil;
		directory_so_far = next_cons;
		default_directory_section_to_merge = 
			g2int_copy_directory_contents(default_directory_qm);
		temp_2 = nconc2(default_directory_section_to_merge,
			directory_so_far);
		return VALUES_1(SVREF(pathname_1,FIX((SI_Long)3L)) = temp_2);
	    }
	    else
		return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GENSYM-MERGE-PATHNAMES-AFTER-CONVERSION */
Object g2int_gensym_merge_pathnames_after_conversion varargs_1(int, n)
{
    Object pathname_1;
    Object defaults, default_version, convert_file_strings_to_uppercase_p;
    Object original_pathname, merge_pathnames_rule, ab_loop_list_;
    Object ab_loop_desetq_, temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,82);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    default_version = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    convert_file_strings_to_uppercase_p = Nil;
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      original_pathname = g2int_copy_gensym_pathname(pathname_1);
      merge_pathnames_rule = Nil;
      ab_loop_list_ = G2int_merge_pathnames_rules;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      merge_pathnames_rule = CDR(ab_loop_desetq_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      temp = SYMBOL_FUNCTION(merge_pathnames_rule);
      FUNCALL_4(temp,original_pathname,pathname_1,defaults,default_version);
      goto next_loop;
    end_loop:;
      g2int_reclaim_gensym_pathname(original_pathname);
      result = VALUES_1(pathname_1);
    POP_SPECIAL();
    return result;
}

/* GENSYM-MERGE-PATHNAMES-FUNCTION */
Object g2int_gensym_merge_pathnames_function(convertible_thing,default_1,
	    default_version)
    Object convertible_thing, default_1, default_version;
{
    Object filename_parser, namestring_generator, default_filename_parser;
    Object default_namestring_generator, convert_file_strings_to_uppercase_p;
    Object pathname_qm;
    volatile Object default_pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(32,83);
    SAVE_STACK();
    filename_parser = Nil;
    namestring_generator = Nil;
    default_filename_parser = Nil;
    default_namestring_generator = Nil;
    if (SIMPLE_VECTOR_P(convertible_thing) && EQ(ISVREF(convertible_thing,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	filename_parser = ISVREF(convertible_thing,(SI_Long)9L);
	namestring_generator = ISVREF(convertible_thing,(SI_Long)10L);
    }
    else if (g2int_text_string_p(convertible_thing) && 
	    g2int_parser_in_namestring_p(convertible_thing)) {
	result = g2int_get_parser_from_namestring(convertible_thing);
	MVS_2(result,filename_parser,namestring_generator);
    }
    else if (SIMPLE_VECTOR_P(default_1) && EQ(ISVREF(default_1,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	filename_parser = ISVREF(default_1,(SI_Long)9L);
	namestring_generator = ISVREF(default_1,(SI_Long)10L);
    }
    else if (g2int_text_string_p(default_1) && 
	    g2int_parser_in_namestring_p(default_1)) {
	result = g2int_get_parser_from_namestring(default_1);
	MVS_2(result,filename_parser,namestring_generator);
    }
    else {
	filename_parser = G2int_local_filename_parser;
	namestring_generator = G2int_local_namestring_generator;
    }
    if (SIMPLE_VECTOR_P(default_1) && EQ(ISVREF(default_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	default_filename_parser = ISVREF(default_1,(SI_Long)9L);
	default_namestring_generator = ISVREF(default_1,(SI_Long)10L);
    }
    else if (g2int_text_string_p(default_1) && 
	    g2int_parser_in_namestring_p(default_1)) {
	result = g2int_get_parser_from_namestring(default_1);
	MVS_2(result,default_filename_parser,default_namestring_generator);
    }
    else {
	default_filename_parser = filename_parser;
	default_namestring_generator = namestring_generator;
    }
    convert_file_strings_to_uppercase_p = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(filename_parser),
	    Qg2int_convert_file_strings_to_uppercase_p);
    PUSH_SPECIAL(G2int_convert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = 
	      g2int_convert_to_gensym_pathname_with_known_parser(convertible_thing,
	      filename_parser,namestring_generator);
      default_pathname_qm = Qg2int_unbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  default_pathname_qm = 
		  g2int_convert_to_gensym_pathname_with_known_parser(default_1,
		  default_filename_parser,default_namestring_generator);
	  if (pathname_qm && default_pathname_qm)
	      SAVE_VALUES(g2int_gensym_merge_pathnames_after_conversion(3,
		      pathname_qm,default_pathname_qm,default_version));
	  else if (pathname_qm)
	      SAVE_VALUES(g2int_gensym_merge_pathnames_after_conversion(3,
		      pathname_qm,G2int_gensym_default_pathname_defaults,
		      default_version));
	  else
	      SAVE_VALUES(g2int_make_empty_gensym_pathname());
      }
      POP_UNWIND_PROTECT(0);
      if (default_pathname_qm) {
	  if ( !EQ(default_pathname_qm,Qg2int_unbound_in_protected_let))
	      g2int_reclaim_gensym_pathname(default_pathname_qm);
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* MAKE-ABSOLUTE-PATHNAME-IF-POSSIBLE */
Object g2int_make_absolute_pathname_if_possible(filename)
    Object filename;
{
    x_note_fn_call(32,84);
    return VALUES_1(Nil);
}

/* MAKE-WILD-NAME-AND-TYPE-PATHNAME */
Object g2int_make_wild_name_and_type_pathname(default_pathname)
    Object default_pathname;
{
    Object temp;

    x_note_fn_call(32,85);
    temp = ISVREF(default_pathname,(SI_Long)8L);
    if (EQ(temp,Qg2int_unix))
	return g2int_gensym_make_pathname_with_copied_components(Nil,Nil,
		Nil,Kwild,Nil,Nil,Nil);
    else if (EQ(temp,Qg2int_win32) || EQ(temp,Qg2int_dos) || EQ(temp,
	    Qg2int_generalized_dos))
	return g2int_gensym_make_pathname_with_copied_components(Nil,Nil,
		Nil,Kwild,Nil,Nil,Nil);
    else
	return g2int_gensym_make_pathname_with_copied_components(Nil,Nil,
		Nil,Kwild,Kwild,Nil,Nil);
}

/* MAKE-CANONICAL-WILD-DIRECTORY-PATHNAME-IF-POSSIBLE */
Object g2int_make_canonical_wild_directory_pathname_if_possible(directory_pathname,
	    directory_string)
    Object directory_pathname, directory_string;
{
    volatile Object wild_pathname;
    volatile Object canonical_directory_pathname_qm;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(32,86);
    SAVE_STACK();
    if ( !TRUEP(ISVREF(directory_pathname,(SI_Long)4L)) &&  
	    !TRUEP(ISVREF(directory_pathname,(SI_Long)5L)) && 
	    g2int_gensym_pathname_version_empty_p(directory_pathname)) {
	wild_pathname = Qg2int_unbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    wild_pathname = 
		    g2int_make_wild_name_and_type_pathname(directory_pathname);
	    SAVE_VALUES(g2int_gensym_merge_pathnames_function(directory_pathname,
		    wild_pathname,Nil));
	}
	POP_UNWIND_PROTECT(0);
	if (wild_pathname) {
	    if ( !EQ(wild_pathname,Qg2int_unbound_in_protected_let))
		g2int_reclaim_gensym_pathname(wild_pathname);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else if (g2int_g2_stream_directory_p(directory_string)) {
	canonical_directory_pathname_qm = Qg2int_unbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(1)) {
	    canonical_directory_pathname_qm = 
		    g2int_gensym_file_as_directory(directory_pathname);
	    if (canonical_directory_pathname_qm) {
		wild_pathname = Qg2int_unbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    wild_pathname = 
			    g2int_make_wild_name_and_type_pathname(canonical_directory_pathname_qm);
		    SAVE_VALUES(g2int_gensym_merge_pathnames_function(canonical_directory_pathname_qm,
			    wild_pathname,Nil));
		}
		POP_UNWIND_PROTECT(0);
		if (wild_pathname) {
		    if ( !EQ(wild_pathname,Qg2int_unbound_in_protected_let))
			g2int_reclaim_gensym_pathname(wild_pathname);
		}
		CONTINUE_UNWINDING(0);
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	POP_UNWIND_PROTECT(1);
	if (canonical_directory_pathname_qm) {
	    if ( !EQ(canonical_directory_pathname_qm,
		    Qg2int_unbound_in_protected_let))
		g2int_reclaim_gensym_pathname(canonical_directory_pathname_qm);
	}
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* GET-LESS-CASE-SENSITIVE-GENSYM-PATHNAME-GIVEN-DIRECTORY */
Object g2int_get_less_case_sensitive_gensym_pathname_given_directory(gensym_pathname,
	    directory_1)
    Object gensym_pathname, directory_1;
{
    Object name, type, version, truename_1, ab_loop_list_, ab_loop_it_;
    Object truename_version;

    x_note_fn_call(32,87);
    name = ISVREF(gensym_pathname,(SI_Long)4L);
    type = ISVREF(gensym_pathname,(SI_Long)5L);
    version = ISVREF(gensym_pathname,(SI_Long)6L);
    truename_1 = Nil;
    ab_loop_list_ = directory_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    truename_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (name && ISVREF(truename_1,(SI_Long)4L) && 
	    g2int_string_equalw(ISVREF(truename_1,(SI_Long)4L),name) && 
	    type && ISVREF(truename_1,(SI_Long)5L) && 
	    g2int_string_equalw(ISVREF(truename_1,(SI_Long)5L),type)) {
	truename_version = ISVREF(truename_1,(SI_Long)6L);
	ab_loop_it_ = EQL(version,truename_version) || (EQ(version,Qnil) 
		|| EQ(version,Knewest) || EQ(version,Kunspecific)) && 
		(EQ(truename_version,Qnil) || EQ(truename_version,Knewest) 
		|| EQ(truename_version,Kunspecific)) ? 
		g2int_copy_gensym_pathname(truename_1) : Qnil;
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MAKE-MODULE-NAME-FROM-KB-PATHNAME */
Object g2int_make_module_name_from_kb_pathname(kb_pathname)
    Object kb_pathname;
{
    x_note_fn_call(32,88);
    return g2int_intern_text_string(1,
	    g2int_nstring_upcasew(g2int_copy_text_string(ISVREF(kb_pathname,
	    (SI_Long)4L))));
}

/* MERGE-SERIES-OF-PATHNAMES */
Object g2int_merge_series_of_pathnames(series_of_pathnames)
    Object series_of_pathnames;
{
    Object pathname_qm, result_so_far, series_of_pathnames_old_value, temp;

    x_note_fn_call(32,89);
    pathname_qm = Nil;
    result_so_far = g2int_gensym_make_pathname_with_copied_components(Nil,
	    Nil,Nil,Nil,Nil,Nil,Nil);
  next_loop:
    if ( !TRUEP(series_of_pathnames))
	goto end_loop;
    series_of_pathnames_old_value = series_of_pathnames;
    temp = FIRST(series_of_pathnames_old_value);
    series_of_pathnames = REST(series_of_pathnames_old_value);
    pathname_qm = temp;
    if (pathname_qm) {
	temp = g2int_gensym_merge_pathnames_function(result_so_far,
		pathname_qm,Nil);
	g2int_reclaim_gensym_pathname(result_so_far);
	result_so_far = temp;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(result_so_far);
    return VALUES_1(Qnil);
}

Object G2int_object_file_pathname_for_machine = UNBOUND;

Object G2int_g2_machine_type_string = UNBOUND;

static Object Kappend_to_directory;  /* :append-to-directory */

static Object Kappend_to_name;     /* :append-to-name */

static Object string_constant_8;   /* "~A-~A" */

/* MAKE-OBJECT-FILE-PATHNAME */
Object g2int_make_object_file_pathname(pathname_1,type)
    Object pathname_1, type;
{
    Object directory_1, obj_file_dir, name, obj_file_name, temp;

    x_note_fn_call(32,90);
    directory_1 = ISVREF(pathname_1,(SI_Long)3L);
    obj_file_dir = EQ(G2int_object_file_pathname_for_machine,
	    Kappend_to_directory) && CONSP(directory_1) ? 
	    nconc2(g2int_copy_list_using_gensym_conses_1(directory_1),
	    g2int_gensym_cons_1(G2int_g2_machine_type_string,Nil)) : 
	    directory_1;
    name = ISVREF(pathname_1,(SI_Long)4L);
    obj_file_name = EQ(G2int_object_file_pathname_for_machine,
	    Kappend_to_name) ? g2int_tformat_text_string(3,
	    string_constant_8,name,G2int_g2_machine_type_string) : name;
    temp = g2int_gensym_make_pathname_with_copied_components(Nil,Nil,
	    obj_file_dir,obj_file_name,type,Nil,pathname_1);
    if (EQ(G2int_object_file_pathname_for_machine,Kappend_to_directory) && 
	    CONSP(directory_1))
	g2int_reclaim_gensym_list_1(obj_file_dir);
    if (EQ(G2int_object_file_pathname_for_machine,Kappend_to_name))
	g2int_reclaim_text_string(obj_file_name);
    return VALUES_1(temp);
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* PATHNAME->SHARED-FILE-PATHNAME */
Object g2int_pathname_gtshared_file_pathname(pathname_1)
    Object pathname_1;
{
    Object temp;

    x_note_fn_call(32,91);
    if (T) {
	if (EQ(G2int_local_file_system,Qg2int_unix))
	    temp = array_constant_3;
	else if (EQ(G2int_local_file_system,Qg2int_vms))
	    temp = array_constant_4;
	else if (EQ(G2int_local_file_system,Qg2int_win32))
	    temp = array_constant_5;
	else
	    temp = array_constant_5;
    }
    else
	temp = Nil;
    temp = g2int_make_object_file_pathname(pathname_1,temp);
    return VALUES_1(temp);
}

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* GET-OBJECT-FILE-SUFFIX-FOR-THIS-OS */
Object g2int_get_object_file_suffix_for_this_os()
{
    x_note_fn_call(32,92);
    return VALUES_1(EQ(G2int_local_file_system,Qg2int_unix) ? 
	    array_constant_6 : array_constant_7);
}

static Object Qg2int_do_not_use;   /* do-not-use */

static Object Qg2int_wide_string;  /* wide-string */

/* KB-NAME->SHARED-OBJECT-FILENAME */
Object g2int_kb_name_gtshared_object_filename(kb_filename)
    Object kb_filename;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, temp, aref_arg_2_1, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(32,93);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(g2int_text_string_length(kb_filename));
	      c = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      c = FIX(UBYTE_16_ISAREF_1(kb_filename,i));
	      if ((SI_Long)46L == IFIX(c))
		  goto end_loop;
	      if ( !FIXNUM_LT(G2int_fill_pointer_for_current_wide_string,
		      G2int_total_length_of_current_wide_string))
		  g2int_extend_current_wide_string(G2int_fill_pointer_for_current_wide_string);
	      temp = G2int_current_wide_string;
	      aref_arg_2_1 = G2int_fill_pointer_for_current_wide_string;
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),IFIX(c));
	      temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
	      G2int_fill_pointer_for_current_wide_string = temp;
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      if ( !FIXNUM_LT(G2int_fill_pointer_for_current_wide_string,
		      G2int_total_length_of_current_wide_string))
		  g2int_extend_current_wide_string(G2int_fill_pointer_for_current_wide_string);
	      temp = G2int_current_wide_string;
	      aref_arg_2_1 = G2int_fill_pointer_for_current_wide_string;
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)45L);
	      temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
	      G2int_fill_pointer_for_current_wide_string = temp;
	      g2int_twrite_general_string(G2int_g2_machine_type_string);
	      if ( !FIXNUM_LT(G2int_fill_pointer_for_current_wide_string,
		      G2int_total_length_of_current_wide_string))
		  g2int_extend_current_wide_string(G2int_fill_pointer_for_current_wide_string);
	      temp = G2int_current_wide_string;
	      aref_arg_2_1 = G2int_fill_pointer_for_current_wide_string;
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)46L);
	      temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
	      G2int_fill_pointer_for_current_wide_string = temp;
	      if (EQ(G2int_local_file_system,Qg2int_unix))
		  g2int_twrite_beginning_of_wide_string(array_constant_3,
			  FIX((SI_Long)2L));
	      else if (EQ(G2int_local_file_system,Qg2int_vms))
		  g2int_twrite_beginning_of_wide_string(array_constant_4,
			  FIX((SI_Long)3L));
	      else if (EQ(G2int_local_file_system,Qg2int_win32))
		  g2int_twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)3L));
	      else
		  g2int_twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)3L));
	      temp_1 = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* C-USER-NAME */
Object g2int_c_user_name(buff)
    Object buff;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(32,94);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_get_user_name(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* FOREIGN-GET-USER-NAME */
Object g2int_foreign_get_user_name()
{
    Object result_code;

    x_note_fn_call(32,95);
    result_code = g2int_c_user_name(G2int_gensym_environment_variable_buffer);
    if ( !(FIXNUMP(result_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    result_code) && FIXNUM_LE(result_code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(result_code)) {
	  case 0:
	    return g2int_copy_null_terminated_string_as_text_string(G2int_gensym_environment_variable_buffer);
	  case -1:
	    return VALUES_1(Nil);
	  default:
	    return VALUES_1(Nil);
	}
}

void pathnames_INIT()
{
    Object temp, reclaim_structure_for_gensym_pathname, pushnew_arg_1;
    Object pushnew_arg_3, pushnew_arg_5, merge_pathnames_rules_new_value;
    Object AB_package, list_constant_7;
    Object Qg2int_merge_pathnames_merge_structured_directories;
    Object Qg2int_merge_pathnames_version_default_rule;
    Object Qg2int_merge_pathnames_replace_empty_components;
    Object Qg2int_merge_pathnames_replace_unspecific_host;
    Object Qg2int_merge_pathnames_propagate_file_system;
    Object Qg2int_merge_pathnames_device_default_rule, Qg2int_gensym_pathname;
    Object list_constant_6, Qg2int_file_systems_which_store_device_names;
    Object Qg2int_coral, list_constant_5;
    Object Qg2int_file_systems_which_distinguish_by_version, list_constant_4;
    Object Qg2int_pathnames, Qg2int_gensym_default_pathname_defaults;
    Object Qg2int_initialize_default_gensym_pathname_defaults, Kfuncall;
    Object Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_gensym_pathname_count;
    Object Qg2int_chain_of_available_gensym_pathnames;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_9, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(32,96);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_unix = STATIC_SYMBOL("UNIX",AB_package);
    Qg2int_vms = STATIC_SYMBOL("VMS",AB_package);
    Qg2int_dos = STATIC_SYMBOL("DOS",AB_package);
    Qg2int_win32 = STATIC_SYMBOL("WIN32",AB_package);
    if (G2int_local_file_system == UNBOUND)
	G2int_local_file_system = g2int_initialize_local_file_system();
    Qg2int_parse_unix_filename = STATIC_SYMBOL("PARSE-UNIX-FILENAME",
	    AB_package);
    Qg2int_parse_vms_filename = STATIC_SYMBOL("PARSE-VMS-FILENAME",AB_package);
    Qg2int_parse_dos_filename = STATIC_SYMBOL("PARSE-DOS-FILENAME",AB_package);
    Qg2int_parse_win32_filename = STATIC_SYMBOL("PARSE-WIN32-FILENAME",
	    AB_package);
    if (G2int_local_filename_parser == UNBOUND)
	G2int_local_filename_parser = g2int_initialize_local_filename_parser();
    Qg2int_generate_unix_namestring = 
	    STATIC_SYMBOL("GENERATE-UNIX-NAMESTRING",AB_package);
    Qg2int_generate_vms_namestring = 
	    STATIC_SYMBOL("GENERATE-VMS-NAMESTRING",AB_package);
    Qg2int_generate_dos_namestring = 
	    STATIC_SYMBOL("GENERATE-DOS-NAMESTRING",AB_package);
    Qg2int_generate_win32_namestring = 
	    STATIC_SYMBOL("GENERATE-WIN32-NAMESTRING",AB_package);
    if (G2int_local_namestring_generator == UNBOUND)
	G2int_local_namestring_generator = 
		g2int_initialize_local_namestring_generator();
    Qg2int_convert_file_strings_to_uppercase_p = 
	    STATIC_SYMBOL("CONVERT-FILE-STRINGS-TO-UPPERCASE-P",AB_package);
    G2int_convert_file_strings_to_uppercase_p_prop = 
	    Qg2int_convert_file_strings_to_uppercase_p;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_convert_file_strings_to_uppercase_p,
	    G2int_convert_file_strings_to_uppercase_p);
    if (G2int_convert_file_strings_to_uppercase_p == UNBOUND)
	G2int_convert_file_strings_to_uppercase_p = 
		g2int_initialize_convert_file_strings_to_uppercase_p();
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gensym_pathname = STATIC_SYMBOL("GENSYM-PATHNAME",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gensym_pathname_g2_struct,
	    Qg2int_gensym_pathname,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_gensym_pathname,
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gensym_pathname == UNBOUND)
	G2int_the_type_description_of_gensym_pathname = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8l9k1n9k8m8k1l8m0000001m1n8n83*py1q83-7y83-5y83-6y83-8y83-9y83-Ay1m8p830Aykvk0k0");
    temp = G2int_the_type_description_of_gensym_pathname;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qg2int_gensym_pathname);
    G2int_the_type_description_of_gensym_pathname = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_9));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gensym_pathname_g2_struct,
	    G2int_the_type_description_of_gensym_pathname,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_gensym_pathname,
	    G2int_the_type_description_of_gensym_pathname,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gensym_pathnames = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-PATHNAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gensym_pathnames,
	    G2int_chain_of_available_gensym_pathnames);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_gensym_pathnames,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym_pathname_count = STATIC_SYMBOL("GENSYM-PATHNAME-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_pathname_count,
	    G2int_gensym_pathname_count);
    g2int_record_system_variable(Qg2int_gensym_pathname_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gensym_pathname = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gensym_pathname,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gensym_pathname,reclaim_structure_for_gensym_pathname);
    Krelative = STATIC_SYMBOL("RELATIVE",Pkeyword);
    list_constant = STATIC_CONS(Krelative,Qnil);
    Qg2int_gensym_default_pathname_defaults = 
	    STATIC_SYMBOL("GENSYM-DEFAULT-PATHNAME-DEFAULTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_default_pathname_defaults,
	    G2int_gensym_default_pathname_defaults);
    Qg2int_pathnames = STATIC_SYMBOL("PATHNAMES",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_initialize_default_gensym_pathname_defaults = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-GENSYM-PATHNAME-DEFAULTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_initialize_default_gensym_pathname_defaults,
	    STATIC_FUNCTION(g2int_initialize_default_gensym_pathname_defaults,
	    NIL,FALSE,0,0));
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_initialize_default_gensym_pathname_defaults);
    g2int_record_system_variable(Qg2int_gensym_default_pathname_defaults,
	    Qg2int_pathnames,list_constant_4,Qnil,Qt,Qnil,Qnil);
    string_constant = STATIC_STRING("RclmGsmPthnm");
    Qg2int_file_systems_which_distinguish_by_version = 
	    STATIC_SYMBOL("FILE-SYSTEMS-WHICH-DISTINGUISH-BY-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_file_systems_which_distinguish_by_version,
	    G2int_file_systems_which_distinguish_by_version);
    list_constant_5 = STATIC_CONS(Qg2int_vms,Qnil);
    SET_SYMBOL_VALUE(Qg2int_file_systems_which_distinguish_by_version,
	    list_constant_5);
    Qg2int_file_systems_which_store_device_names = 
	    STATIC_SYMBOL("FILE-SYSTEMS-WHICH-STORE-DEVICE-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_file_systems_which_store_device_names,
	    G2int_file_systems_which_store_device_names);
    Qg2int_coral = STATIC_SYMBOL("CORAL",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qg2int_vms,Qg2int_coral);
    SET_SYMBOL_VALUE(Qg2int_file_systems_which_store_device_names,
	    list_constant_6);
    string_constant_1 = STATIC_STRING("~a");
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_unbound_in_protected_let = 
	    STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING("~A/");
    Khome = STATIC_SYMBOL("HOME",Pkeyword);
    if (G2int_inside_handling_gensym_file_errors_scope_p == UNBOUND)
	G2int_inside_handling_gensym_file_errors_scope_p = Nil;
    if (G2int_gensym_file_error_occurred_p == UNBOUND)
	G2int_gensym_file_error_occurred_p = Nil;
    Qg2int_gensym_file_error_catch_tag = 
	    STATIC_SYMBOL("GENSYM-FILE-ERROR-CATCH-TAG",AB_package);
    Qg2int_tformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_tformat_text_string,
	    STATIC_FUNCTION(g2int_tformat_text_string,NIL,TRUE,1,10));
    if (G2int_report_filename_parsing_errors_in_development_p == UNBOUND)
	G2int_report_filename_parsing_errors_in_development_p = Nil;
    array_constant_1 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_generalized_dos = STATIC_SYMBOL("GENERALIZED-DOS",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_namestring_as_gensym_string = 
	    STATIC_SYMBOL("NAMESTRING-AS-GENSYM-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_namestring_as_gensym_string,
	    STATIC_FUNCTION(g2int_namestring_as_gensym_string,NIL,FALSE,1,1));
    string_constant_3 = STATIC_STRING("~a*.*");
    Qg2int_gensym_enough_namestring = 
	    STATIC_SYMBOL("GENSYM-ENOUGH-NAMESTRING",AB_package);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    string_constant_4 = STATIC_STRING("");
    SET_SYMBOL_FUNCTION(Qg2int_gensym_enough_namestring,
	    STATIC_FUNCTION(g2int_gensym_enough_namestring,NIL,TRUE,1,2));
    list_constant_1 = STATIC_CONS(Kabsolute,Qnil);
    list_constant_2 = STATIC_CONS(Kabsolute,list_constant);
    SET_SYMBOL_FUNCTION(Qg2int_gensym_pathname,
	    STATIC_FUNCTION(g2int_gensym_pathname,NIL,FALSE,1,1));
    string_constant_5 = 
	    STATIC_STRING("GENSYM-TRUENAME: Cannot get pathname from stream ~a");
    string_constant_6 = 
	    STATIC_STRING("GENSYM-TRUENAME: Cannot access file ~a");
    string_constant_7 = 
	    STATIC_STRING("GENSYM-TRUENAME: Cannot obtain pathname for ~a");
    if (G2int_merge_pathnames_rules == UNBOUND)
	G2int_merge_pathnames_rules = Nil;
    if (G2int_merge_pathnames_rules_sorted_p == UNBOUND)
	G2int_merge_pathnames_rules_sorted_p = Nil;
    Qg2int_merge_pathnames_device_default_rule = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-DEVICE-DEFAULT-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_merge_pathnames_device_default_rule,
	    STATIC_FUNCTION(g2int_merge_pathnames_device_default_rule,NIL,
	    TRUE,2,4));
    temp = FIX((SI_Long)0L);
    pushnew_arg_1 = CONS(temp,Qg2int_merge_pathnames_device_default_rule);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    G2int_merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    G2int_merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qg2int_merge_pathnames_propagate_file_system = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-PROPAGATE-FILE-SYSTEM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_merge_pathnames_propagate_file_system,
	    STATIC_FUNCTION(g2int_merge_pathnames_propagate_file_system,
	    NIL,TRUE,2,4));
    temp = FIX((SI_Long)1L);
    pushnew_arg_1 = CONS(temp,Qg2int_merge_pathnames_propagate_file_system);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    G2int_merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    G2int_merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qg2int_merge_pathnames_replace_unspecific_host = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-REPLACE-UNSPECIFIC-HOST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_merge_pathnames_replace_unspecific_host,
	    STATIC_FUNCTION(g2int_merge_pathnames_replace_unspecific_host,
	    NIL,TRUE,2,4));
    temp = FIX((SI_Long)2L);
    pushnew_arg_1 = CONS(temp,Qg2int_merge_pathnames_replace_unspecific_host);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    G2int_merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    G2int_merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qg2int_merge_pathnames_replace_empty_components = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-REPLACE-EMPTY-COMPONENTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_merge_pathnames_replace_empty_components,
	    STATIC_FUNCTION(g2int_merge_pathnames_replace_empty_components,
	    NIL,TRUE,2,4));
    temp = FIX((SI_Long)3L);
    pushnew_arg_1 = CONS(temp,Qg2int_merge_pathnames_replace_empty_components);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    G2int_merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    G2int_merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qg2int_merge_pathnames_version_default_rule = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-VERSION-DEFAULT-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_merge_pathnames_version_default_rule,
	    STATIC_FUNCTION(g2int_merge_pathnames_version_default_rule,NIL,
	    TRUE,2,4));
    temp = FIX((SI_Long)4L);
    pushnew_arg_1 = CONS(temp,Qg2int_merge_pathnames_version_default_rule);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    G2int_merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    G2int_merge_pathnames_rules = merge_pathnames_rules_new_value;
    list_constant_3 = STATIC_CONS(Kup,list_constant);
    Qg2int_merge_pathnames_merge_structured_directories = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-MERGE-STRUCTURED-DIRECTORIES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_merge_pathnames_merge_structured_directories,
	    STATIC_FUNCTION(g2int_merge_pathnames_merge_structured_directories,
	    NIL,TRUE,2,4));
    temp = FIX((SI_Long)5L);
    pushnew_arg_1 = CONS(temp,
	    Qg2int_merge_pathnames_merge_structured_directories);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    G2int_merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,
	    pushnew_arg_5);
    G2int_merge_pathnames_rules = merge_pathnames_rules_new_value;
    G2int_merge_pathnames_rules = sort(4,G2int_merge_pathnames_rules,
	    SYMBOL_FUNCTION(Qnum_lt),Kkey,SYMBOL_FUNCTION(Qcar));
    G2int_merge_pathnames_rules_sorted_p = T;
    Kappend_to_name = STATIC_SYMBOL("APPEND-TO-NAME",Pkeyword);
    if (G2int_object_file_pathname_for_machine == UNBOUND)
	G2int_object_file_pathname_for_machine = Kappend_to_name;
    G2int_g2_machine_type_string = 
	    g2int_gensym_string_to_wide_string(string_downcase(1,
	    SYMBOL_NAME(G2int_g2_machine_type)));
    Kappend_to_directory = STATIC_SYMBOL("APPEND-TO-DIRECTORY",Pkeyword);
    string_constant_8 = STATIC_STRING("~A-~A");
    array_constant_3 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
}
