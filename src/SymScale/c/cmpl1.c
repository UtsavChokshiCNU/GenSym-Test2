/* cmpl1.c
 * Input file:  compile1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cmpl1.h"


Object The_type_description_of_expression_for_compilation = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_expression_for_compilations, Qchain_of_available_expression_for_compilations);

DEFINE_VARIABLE_WITH_SYMBOL(Expression_for_compilation_count, Qexpression_for_compilation_count);

Object Chain_of_available_expression_for_compilations_vector = UNBOUND;

/* EXPRESSION-FOR-COMPILATION-STRUCTURE-MEMORY-USAGE */
Object expression_for_compilation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(140,0);
    temp = Expression_for_compilation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EXPRESSION-FOR-COMPILATION-COUNT */
Object outstanding_expression_for_compilation_count()
{
    Object def_structure_expression_for_compilation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(140,1);
    gensymed_symbol = IFIX(Expression_for_compilation_count);
    def_structure_expression_for_compilation_variable = 
	    Chain_of_available_expression_for_compilations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_expression_for_compilation_variable))
	goto end_loop;
    def_structure_expression_for_compilation_variable = 
	    ISVREF(def_structure_expression_for_compilation_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EXPRESSION-FOR-COMPILATION-1 */
Object reclaim_expression_for_compilation_1(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp, svref_arg_2;

    x_note_fn_call(140,2);
    inline_note_reclaim_cons(expression_for_compilation,Nil);
    temp = ISVREF(Chain_of_available_expression_for_compilations_vector,
	    IFIX(Current_thread_index));
    SVREF(expression_for_compilation,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_expression_for_compilations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = expression_for_compilation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EXPRESSION-FOR-COMPILATION */
Object reclaim_structure_for_expression_for_compilation(expression_for_compilation)
    Object expression_for_compilation;
{
    x_note_fn_call(140,3);
    return reclaim_expression_for_compilation_1(expression_for_compilation);
}

static Object Qg2_defstruct_structure_name_expression_for_compilation_g2_struct;  /* g2-defstruct-structure-name::expression-for-compilation-g2-struct */

/* MAKE-PERMANENT-EXPRESSION-FOR-COMPILATION-STRUCTURE-INTERNAL */
Object make_permanent_expression_for_compilation_structure_internal()
{
    Object def_structure_expression_for_compilation_variable;
    Object defstruct_g2_expression_for_compilation_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(140,4);
    def_structure_expression_for_compilation_variable = Nil;
    atomic_incff_symval(Qexpression_for_compilation_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_expression_for_compilation_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_expression_for_compilation_variable = the_array;
	SVREF(defstruct_g2_expression_for_compilation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_expression_for_compilation_g2_struct;
	def_structure_expression_for_compilation_variable = 
		defstruct_g2_expression_for_compilation_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_expression_for_compilation_variable);
}

/* MAKE-EXPRESSION-FOR-COMPILATION-1 */
Object make_expression_for_compilation_1()
{
    Object def_structure_expression_for_compilation_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(140,5);
    def_structure_expression_for_compilation_variable = 
	    ISVREF(Chain_of_available_expression_for_compilations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_expression_for_compilation_variable) {
	svref_arg_1 = Chain_of_available_expression_for_compilations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_expression_for_compilation_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_expression_for_compilation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_expression_for_compilation_g2_struct;
    }
    else
	def_structure_expression_for_compilation_variable = 
		make_permanent_expression_for_compilation_structure_internal();
    inline_note_allocate_cons(def_structure_expression_for_compilation_variable,
	    Nil);
    SVREF(def_structure_expression_for_compilation_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_expression_for_compilation_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_expression_for_compilation_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_expression_for_compilation_variable,
	    FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_expression_for_compilation_variable);
}

/* PRINT-EXPRESSION-FOR-COMPILATION-STRUCTURE */
Object print_expression_for_compilation_structure(expression_for_compilation,
	    stream,depth)
    Object expression_for_compilation, stream, depth;
{
    Object dot_object_dot, dot_stream_dot;

    x_note_fn_call(140,6);
    dot_object_dot = expression_for_compilation;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    format((SI_Long)3L,stream,"expression-for-compilation ~S",
	    ISVREF(expression_for_compilation,(SI_Long)1L));
    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
}

Object The_type_description_of_for_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_for_structures, Qchain_of_available_for_structures);

DEFINE_VARIABLE_WITH_SYMBOL(For_structure_count, Qfor_structure_count);

Object Chain_of_available_for_structures_vector = UNBOUND;

/* FOR-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object for_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(140,7);
    temp = For_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FOR-STRUCTURE-COUNT */
Object outstanding_for_structure_count()
{
    Object def_structure_for_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(140,8);
    gensymed_symbol = IFIX(For_structure_count);
    def_structure_for_structure_variable = Chain_of_available_for_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_for_structure_variable))
	goto end_loop;
    def_structure_for_structure_variable = 
	    ISVREF(def_structure_for_structure_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-FOR-STRUCTURE-1 */
Object reclaim_for_structure_1(for_structure)
    Object for_structure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(140,9);
    inline_note_reclaim_cons(for_structure,Nil);
    temp = ISVREF(Chain_of_available_for_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(for_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_for_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = for_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FOR-STRUCTURE */
Object reclaim_structure_for_for_structure(for_structure)
    Object for_structure;
{
    x_note_fn_call(140,10);
    return reclaim_for_structure_1(for_structure);
}

static Object Qg2_defstruct_structure_name_for_structure_g2_struct;  /* g2-defstruct-structure-name::for-structure-g2-struct */

/* MAKE-PERMANENT-FOR-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_for_structure_structure_internal()
{
    Object def_structure_for_structure_variable;
    Object defstruct_g2_for_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(140,11);
    def_structure_for_structure_variable = Nil;
    atomic_incff_symval(Qfor_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_for_structure_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_for_structure_variable = the_array;
	SVREF(defstruct_g2_for_structure_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_for_structure_g2_struct;
	def_structure_for_structure_variable = 
		defstruct_g2_for_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_for_structure_variable);
}

/* MAKE-FOR-STRUCTURE-1 */
Object make_for_structure_1()
{
    Object def_structure_for_structure_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(140,12);
    def_structure_for_structure_variable = 
	    ISVREF(Chain_of_available_for_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_for_structure_variable) {
	svref_arg_1 = Chain_of_available_for_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_for_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_for_structure_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_for_structure_g2_struct;
    }
    else
	def_structure_for_structure_variable = 
		make_permanent_for_structure_structure_internal();
    inline_note_allocate_cons(def_structure_for_structure_variable,Nil);
    SVREF(def_structure_for_structure_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_for_structure_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_for_structure_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_for_structure_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_for_structure_variable);
}

Object The_type_description_of_reference_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_reference_structures, Qchain_of_available_reference_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Reference_structure_count, Qreference_structure_count);

Object Chain_of_available_reference_structures_vector = UNBOUND;

/* REFERENCE-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object reference_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(140,13);
    temp = Reference_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-REFERENCE-STRUCTURE-COUNT */
Object outstanding_reference_structure_count()
{
    Object def_structure_reference_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(140,14);
    gensymed_symbol = IFIX(Reference_structure_count);
    def_structure_reference_structure_variable = 
	    Chain_of_available_reference_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_reference_structure_variable))
	goto end_loop;
    def_structure_reference_structure_variable = 
	    ISVREF(def_structure_reference_structure_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-REFERENCE-STRUCTURE-1 */
Object reclaim_reference_structure_1(reference_structure)
    Object reference_structure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(140,15);
    inline_note_reclaim_cons(reference_structure,Nil);
    temp = ISVREF(Chain_of_available_reference_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(reference_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_reference_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = reference_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REFERENCE-STRUCTURE */
Object reclaim_structure_for_reference_structure(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(140,16);
    return reclaim_reference_structure_1(reference_structure);
}

static Object Qg2_defstruct_structure_name_reference_structure_g2_struct;  /* g2-defstruct-structure-name::reference-structure-g2-struct */

/* MAKE-PERMANENT-REFERENCE-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_reference_structure_structure_internal()
{
    Object def_structure_reference_structure_variable;
    Object defstruct_g2_reference_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(140,17);
    def_structure_reference_structure_variable = Nil;
    atomic_incff_symval(Qreference_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_reference_structure_variable = Nil;
	gensymed_symbol = (SI_Long)13L;
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
	defstruct_g2_reference_structure_variable = the_array;
	SVREF(defstruct_g2_reference_structure_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_reference_structure_g2_struct;
	def_structure_reference_structure_variable = 
		defstruct_g2_reference_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_reference_structure_variable);
}

/* MAKE-REFERENCE-STRUCTURE-1 */
Object make_reference_structure_1()
{
    Object def_structure_reference_structure_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(140,18);
    def_structure_reference_structure_variable = 
	    ISVREF(Chain_of_available_reference_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_reference_structure_variable) {
	svref_arg_1 = Chain_of_available_reference_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_reference_structure_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_reference_structure_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_reference_structure_g2_struct;
    }
    else
	def_structure_reference_structure_variable = 
		make_permanent_reference_structure_structure_internal();
    inline_note_allocate_cons(def_structure_reference_structure_variable,Nil);
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_reference_structure_variable,FIX((SI_Long)12L)) = Nil;
    return VALUES_1(def_structure_reference_structure_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_antecedent_1, Qcompiled_antecedent_1);

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_consequent_1, Qcompiled_consequent_1);

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_consequent_2, Qcompiled_consequent_2);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_expressions_for_compilation, Qlist_of_expressions_for_compilation);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_for_structures, Qlist_of_for_structures);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_reference_structures, Qlist_of_reference_structures);

/* MAKE-COMPILATION-RECLAIMABLE-EXPRESSION-FOR-COMPILATION */
Object make_compilation_reclaimable_expression_for_compilation()
{
    Object new_expression_for_compilation;

    x_note_fn_call(140,19);
    new_expression_for_compilation = make_expression_for_compilation_1();
    List_of_expressions_for_compilation = 
	    phrase_cons(new_expression_for_compilation,
	    List_of_expressions_for_compilation);
    return VALUES_1(new_expression_for_compilation);
}

/* MAKE-COMPILATION-RECLAIMABLE-FOR-STRUCTURE */
Object make_compilation_reclaimable_for_structure()
{
    Object new_for_structure;

    x_note_fn_call(140,20);
    new_for_structure = make_for_structure_1();
    List_of_for_structures = phrase_cons(new_for_structure,
	    List_of_for_structures);
    return VALUES_1(new_for_structure);
}

/* MAKE-COMPILATION-RECLAIMABLE-REFERENCE-STRUCTURE */
Object make_compilation_reclaimable_reference_structure()
{
    Object new_reference_structure;

    x_note_fn_call(140,21);
    new_reference_structure = make_reference_structure_1();
    List_of_reference_structures = phrase_cons(new_reference_structure,
	    List_of_reference_structures);
    return VALUES_1(new_reference_structure);
}

/* RECLAIM-ALL-COMPILATION-STRUCTURES */
Object reclaim_all_compilation_structures()
{
    Object expression_for_compilation, ab_loop_list_, for_structure;
    Object reference_structure;

    x_note_fn_call(140,22);
    expression_for_compilation = Nil;
    ab_loop_list_ = List_of_expressions_for_compilation;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression_for_compilation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_expression_for_compilation_1(expression_for_compilation);
    goto next_loop;
  end_loop:;
    List_of_expressions_for_compilation = Nil;
    for_structure = Nil;
    ab_loop_list_ = List_of_for_structures;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    for_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_for_structure_1(for_structure);
    goto next_loop_1;
  end_loop_1:;
    List_of_for_structures = Nil;
    reference_structure = Nil;
    ab_loop_list_ = List_of_reference_structures;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_reference_structure_1(reference_structure);
    goto next_loop_2;
  end_loop_2:;
    List_of_reference_structures = Nil;
    return VALUES_1(List_of_reference_structures);
}

static Object list_constant;       /* # */

/* DESIGNATION-OPERATOR-P */
Object designation_operator_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,23);
    temp = memq_function(operator_1,list_constant);
    return VALUES_1(temp);
}

static Object Qgiver_of_value;     /* giver-of-value */

/* DESIGNATION-OPERATOR-OR-GIVER-OF-VALUE-P */
Object designation_operator_or_giver_of_value_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,24);
    temp = designation_operator_p(operator_1);
    if (temp);
    else
	temp = EQ(operator_1,Qgiver_of_value) ? T : Nil;
    return VALUES_1(temp);
}

static Object list_constant_1;     /* # */

/* IMPLICIT-ITERATOR-P */
Object implicit_iterator_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,25);
    temp = memq_function(operator_1,list_constant_1);
    return VALUES_1(temp);
}

/* QUANTIFIER-REQUIRES-PREVIOUS-REFERENCE-P */
Object quantifier_requires_previous_reference_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,26);
    temp = EQ(operator_1,Qthe) ? T : Nil;
    return VALUES_1(temp);
}

/* QUANTIFIER-OR-AGGREGATOR-P */
Object quantifier_or_aggregator_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,27);
    temp = quantifier_p(operator_1);
    if (temp);
    else
	temp = aggregator_p(operator_1);
    return VALUES_1(temp);
}

static Object list_constant_2;     /* # */

/* QUANTIFIER-P */
Object quantifier_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,28);
    temp = memq_function(operator_1,list_constant_2);
    return VALUES_1(temp);
}

static Object list_constant_3;     /* # */

/* AGGREGATOR-P */
Object aggregator_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,29);
    temp = memq_function(operator_1,list_constant_3);
    return VALUES_1(temp);
}

static Object list_constant_4;     /* # */

/* LOGICAL-OPERATOR-P */
Object logical_operator_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,30);
    temp = memq_function(operator_1,list_constant_4);
    return VALUES_1(temp);
}

static Object list_constant_5;     /* # */

/* IF-OPERATOR-P */
Object if_operator_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,31);
    temp = memq_function(operator_1,list_constant_5);
    return VALUES_1(temp);
}

Object Function_definition_kbprop = UNBOUND;

/* OPERATOR-DOES-NOT-REQUIRE-REFERENCES-P */
Object operator_does_not_require_references_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(140,32);
    temp = memq_function(operator_1,Qnil);
    return VALUES_1(temp);
}

/* SIMPLE-ROLE-P */
Object simple_role_p(role)
    Object role;
{
    Object temp, cdr_1;

    x_note_fn_call(140,33);
    temp = SYMBOLP(role) ? T : Nil;
    if (temp);
    else {
	cdr_1 = CDR(role);
	temp =  !(cdr_1 && SYMBOLP(cdr_1)) ? T : Nil;
    }
    return VALUES_1(temp);
}

/* GET-NAME-PROVIDED-BY-ROLE */
Object get_name_provided_by_role(role)
    Object role;
{
    Object temp;

    x_note_fn_call(140,34);
    temp =  !TRUEP(simple_role_p(role)) ? M_CDR(role) : 
	    atomic_naming_element_of_simple_role(role);
    return VALUES_1(temp);
}

/* SIMPLE-ROLE-OF-ROLE */
Object simple_role_of_role(role)
    Object role;
{
    x_note_fn_call(140,35);
    return VALUES_1(simple_role_p(role) ? role : M_CAR(role));
}

/* GET-EXPLICITLY-SPECIFIED-LOCAL-NAME-OF-ROLE-IF-ANY */
Object get_explicitly_specified_local_name_of_role_if_any(role)
    Object role;
{
    x_note_fn_call(140,36);
    return VALUES_1( !TRUEP(simple_role_p(role)) ? M_CDR(role) : Nil);
}

static Object Qrole_server;        /* role-server */

/* ROLE-NAME-OF-ROLE */
Object role_name_of_role(role)
    Object role;
{
    Object temp, role_1, role_car;

    x_note_fn_call(140,37);
    if (SYMBOLP(role))
	temp = role;
    else {
	role_1 = role;
	role_car = M_CAR(role_1);
	temp = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) : role_car;
    }
    return VALUES_1(temp);
}

/* DESIGNATION-P-FUNCTION */
Object designation_p_function(form)
    Object form;
{
    Object temp;

    x_note_fn_call(140,38);
    temp = ATOM(form) ? (form ? (SYMBOLP(form) ? T : Nil) : Qnil) : 
	    designation_operator_or_giver_of_value_p(CAR(form));
    return VALUES_1(temp);
}

/* ROLE-OF-DESIGNATION */
Object role_of_designation(designation)
    Object designation;
{
    x_note_fn_call(140,39);
    return VALUES_1(ATOM(designation) ? Nil : SECOND(designation));
}

/* DOMAIN-OF-DESIGNATION */
Object domain_of_designation(designation)
    Object designation;
{
    x_note_fn_call(140,40);
    return VALUES_1(CONSP(designation) && CDDR(designation) ? 
	    THIRD(designation) : Nil);
}

/* DOMAIN-LIST-OF-DESIGNATION */
Object domain_list_of_designation(designation)
    Object designation;
{
    x_note_fn_call(140,41);
    return VALUES_1(CONSP(designation) ? CDDR(designation) : Nil);
}

/* NAME-ROOTED-ATTRIBUTE-ONLY-DESIGNATION-P */
Object name_rooted_attribute_only_designation_p(designation)
    Object designation;
{
    Object temp;
    char temp_1;

    x_note_fn_call(140,42);
    temp = SYMBOLP(designation) ? T : Nil;
    if (temp);
    else {
	if (CONSP(designation) && IFIX(length(designation)) == (SI_Long)3L 
		&& EQ(CAR(designation),Qthe)) {
	    temp = SECOND(designation);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? 
		name_rooted_attribute_only_designation_p(THIRD(designation)) 
		: Nil;
    }
    return VALUES_1(temp);
}

/* DESIGNATION-REQUIRES-PREVIOUS-REFERENCE-P */
Object designation_requires_previous_reference_p(designation)
    Object designation;
{
    Object temp;

    x_note_fn_call(140,43);
    if (CONSP(designation) &&  !TRUEP(CDDR(designation)) && 
	    EQ(FIRST(designation),Qthe)) {
	temp = role_of_designation(designation);
	temp = SYMBOLP(temp) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Focus_range, Qfocus_range);

DEFINE_VARIABLE_WITH_SYMBOL(Needed_domain, Qneeded_domain);

DEFINE_VARIABLE_WITH_SYMBOL(Global_domain, Qglobal_domain);

DEFINE_VARIABLE_WITH_SYMBOL(Expression_list_indicator, Qexpression_list_indicator);

DEFINE_VARIABLE_WITH_SYMBOL(Color_change_indicator, Qcolor_change_indicator);

DEFINE_VARIABLE_WITH_SYMBOL(Color_changes_indicator, Qcolor_changes_indicator);

DEFINE_VARIABLE_WITH_SYMBOL(Nil_indicator, Qnil_indicator);

DEFINE_VARIABLE_WITH_SYMBOL(Local_names_not_associated_with_roles, Qlocal_names_not_associated_with_roles);

/* REFERENCE-STRUCTURE-FOR-GLOBAL-SYMBOL-P */
Object reference_structure_for_global_symbol_p(reference_structure)
    Object reference_structure;
{
    Object role_and_local_name;

    x_note_fn_call(140,44);
    role_and_local_name = ISVREF(reference_structure,(SI_Long)3L);
    if (EQ(ISVREF(reference_structure,(SI_Long)1L),Global_domain) && 
	    EQ(ISVREF(reference_structure,(SI_Long)6L),Qthe) && 
	    SYMBOLP(role_and_local_name))
	return VALUES_1( !TRUEP(memq_function(role_and_local_name,
		Local_names_not_associated_with_roles)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* INVERSE-REFERENCE-STRUCTURE-FOR-GLOBAL-SYMBOL-P */
Object inverse_reference_structure_for_global_symbol_p(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(140,45);
    if (EQ(ISVREF(reference_structure,(SI_Long)1L),Global_domain))
	return VALUES_1(EQ(ISVREF(reference_structure,(SI_Long)7L),Qthe) ? 
		T : Nil);
    else
	return VALUES_1(Nil);
}

/* RS-FOR-TWO-ELEMENT-DESIGNATION-WITH-NON-ATOMIC-ROLE-P */
Object rs_for_two_element_designation_with_non_atomic_role_p(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(140,46);
    if (EQ(ISVREF(reference_structure,(SI_Long)1L),Global_domain))
	return VALUES_1( 
		!TRUEP(reference_structure_for_global_symbol_p(reference_structure)) 
		? T : Nil);
    else
	return VALUES_1(Nil);
}

/* ATOMIC-NAMING-ELEMENT-OF-ROLE */
Object atomic_naming_element_of_role(role)
    Object role;
{
    Object temp;

    x_note_fn_call(140,47);
    temp = atomic_naming_element_of_simple_role(simple_role_of_role(role));
    return VALUES_1(temp);
}

static Object Qab_structure;       /* structure */

/* ATOMIC-NAMING-ELEMENT-OF-SIMPLE-ROLE */
Object atomic_naming_element_of_simple_role(role)
    Object role;
{
    Object temp, result_1;

    x_note_fn_call(140,48);
    if (SYMBOLP(role))
	temp = role;
    else {
	temp = last(role,_);
	result_1 = CAR(temp);
	temp = CONSP(result_1) && (EQ(CAR(result_1),Qsequence) || 
		EQ(CAR(result_1),Qab_structure)) ? CAR(result_1) : result_1;
    }
    return VALUES_1(temp);
}

/* ATOMIC-CLASS-ELEMENT-OF-ROLE */
Object atomic_class_element_of_role(role)
    Object role;
{
    Object simple_role, temp;

    x_note_fn_call(140,49);
    simple_role = simple_role_of_role(role);
    if (SYMBOLP(simple_role))
	temp = simple_role;
    else if (EQ(CAR(simple_role),Qrole_server))
	temp = THIRD(simple_role);
    else {
	temp = last(simple_role,_);
	temp = CAR(temp);
    }
    return VALUES_1(temp);
}

/* ATOMIC-CLASS-ELEMENT-OF-SIMPLE-ROLE */
Object atomic_class_element_of_simple_role(role)
    Object role;
{
    Object temp;

    x_note_fn_call(140,50);
    if (SYMBOLP(role))
	temp = role;
    else if (EQ(CAR(role),Qrole_server))
	temp = THIRD(role);
    else {
	temp = last(role,_);
	temp = CAR(temp);
    }
    return VALUES_1(temp);
}

/* ATOMIC-NAMING-ELEMENT-OF-DESIGNATION */
Object atomic_naming_element_of_designation(designation)
    Object designation;
{
    Object temp;

    x_note_fn_call(140,51);
    temp = atomic_naming_element_of_role(role_of_designation(designation));
    return VALUES_1(temp);
}

/* ATOMIC-CLASS-ELEMENT-OF-DESIGNATION */
Object atomic_class_element_of_designation(designation)
    Object designation;
{
    Object temp;

    x_note_fn_call(140,52);
    temp = atomic_class_element_of_role(role_of_designation(designation));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compilation_local_name_symbol_counter, Qcompilation_local_name_symbol_counter);

DEFINE_VARIABLE_WITH_SYMBOL(Compilation_local_name_listed_next_symbol, Qcompilation_local_name_listed_next_symbol);

DEFINE_VARIABLE_WITH_SYMBOL(Compilation_local_name_symbol_supply, Qcompilation_local_name_symbol_supply);

static Object string_constant;     /* "COMPILATION-LOCAL-NAME" */

/* INTERNED-COMPILATION-LOCAL-NAME-SYMBOL */
Object interned_compilation_local_name_symbol()
{
    Object temp, cdr_arg, cdr_new_value;
    XDeclare_area(1);

    x_note_fn_call(140,53);
    if (ATOM(Compilation_local_name_listed_next_symbol)) {
	atomic_incff_symval(Qcompilation_local_name_symbol_counter,
		FIX((SI_Long)1L));
	if (PUSH_AREA(Dynamic_area,0))
	    Compilation_local_name_listed_next_symbol = 
		    LIST_1(intern(format((SI_Long)4L,Nil,"~A-~D",
		    string_constant,Compilation_local_name_symbol_counter),_));
	POP_AREA(0);
    }
    if (CDR(Compilation_local_name_listed_next_symbol)) {
	temp = CAR(Compilation_local_name_listed_next_symbol);
	atomic_incff_symval(Qcompilation_local_name_symbol_counter,
		FIX((SI_Long)1L));
	Compilation_local_name_listed_next_symbol = 
		CDR(Compilation_local_name_listed_next_symbol);
	return VALUES_1(temp);
    }
    else {
	temp = CAR(Compilation_local_name_listed_next_symbol);
	atomic_incff_symval(Qcompilation_local_name_symbol_counter,
		FIX((SI_Long)1L));
	cdr_arg = Compilation_local_name_listed_next_symbol;
	if (PUSH_AREA(Dynamic_area,0))
	    cdr_new_value = LIST_1(intern(format((SI_Long)4L,Nil,"~A-~D",
		    string_constant,Compilation_local_name_symbol_counter),_));
	POP_AREA(0);
	M_CDR(cdr_arg) = cdr_new_value;
	Compilation_local_name_listed_next_symbol = 
		CDR(Compilation_local_name_listed_next_symbol);
	return VALUES_1(temp);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Bad_rule, Qbad_rule);

DEFINE_VARIABLE_WITH_SYMBOL(Focus_name_for_rule_or_formula_compilation, Qfocus_name_for_rule_or_formula_compilation);

DEFINE_VARIABLE_WITH_SYMBOL(Focus_too_narrow_qm, Qfocus_too_narrow_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Fatal_focus_error_info_qm, Qfatal_focus_error_info_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Fatal_focus_error_info_for_all_compilations, Qfatal_focus_error_info_for_all_compilations);

DEFINE_VARIABLE_WITH_SYMBOL(Focus_local_name_for_rule_compilation_qm, Qfocus_local_name_for_rule_compilation_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Compiling_antecedent_p, Qcompiling_antecedent_p);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_known_names, Qlist_of_known_names);

DEFINE_VARIABLE_WITH_SYMBOL(Alist_of_local_names_and_role_names, Qalist_of_local_names_and_role_names);

DEFINE_VARIABLE_WITH_SYMBOL(Names_used_for_more_than_one_item, Qnames_used_for_more_than_one_item);

DEFINE_VARIABLE_WITH_SYMBOL(Role_names_and_local_names_for_runtime_items, Qrole_names_and_local_names_for_runtime_items);

DEFINE_VARIABLE_WITH_SYMBOL(Focus_local_names_for_focus_role_name, Qfocus_local_names_for_focus_role_name);

DEFINE_VARIABLE_WITH_SYMBOL(Local_name_errors, Qlocal_name_errors);

DEFINE_VARIABLE_WITH_SYMBOL(Inside_action_iteration_p, Qinside_action_iteration_p);

DEFINE_VARIABLE_WITH_SYMBOL(Top_level_reference_tree, Qtop_level_reference_tree);

DEFINE_VARIABLE_WITH_SYMBOL(Pattern_checking_inverse_references, Qpattern_checking_inverse_references);

DEFINE_VARIABLE_WITH_SYMBOL(Wrapper_references_for_left_side_of_formula_qm, Qwrapper_references_for_left_side_of_formula_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Designations_from_explicit_iteration_forms, Qdesignations_from_explicit_iteration_forms);

DEFINE_VARIABLE_WITH_SYMBOL(Source_designations_from_explicit_iteration_forms, Qsource_designations_from_explicit_iteration_forms);

DEFINE_VARIABLE_WITH_SYMBOL(Compiling_rule_p, Qcompiling_rule_p);

DEFINE_VARIABLE_WITH_SYMBOL(Compiling_expression_p, Qcompiling_expression_p);

DEFINE_VARIABLE_WITH_SYMBOL(Context_iteration_forms, Qcontext_iteration_forms);

DEFINE_VARIABLE_WITH_SYMBOL(Non_context_top_level_binding_forms, Qnon_context_top_level_binding_forms);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_no_binds, Qnumber_of_no_binds);

DEFINE_VARIABLE_WITH_SYMBOL(Assignment_section_forms, Qassignment_section_forms);

DEFINE_VARIABLE_WITH_SYMBOL(Post_compiler_warning_note_qm, Qpost_compiler_warning_note_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Attribute_name_errors, Qattribute_name_errors);

DEFINE_VARIABLE_WITH_SYMBOL(Allow_in_line_designations_qm, Qallow_in_line_designations_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Reference_structures_originating_from_within_existence_predicate, Qreference_structures_originating_from_within_existence_predicate);

DEFINE_VARIABLE_WITH_SYMBOL(Local_iteration_forms, Qlocal_iteration_forms);

DEFINE_VARIABLE_WITH_SYMBOL(Local_insertion_location, Qlocal_insertion_location);

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qframe_flags;        /* frame-flags */

static Object Quniversal_compilation;  /* universal-compilation */

static Object Qcompile2_action;    /* compile2-action */

/* COMPILE-RULE */
Object compile_rule(rule_translation,focus_name_qm,
	    context_for_general_compilation,using_section)
    Object rule_translation, focus_name_qm, context_for_general_compilation;
    Object using_section;
{
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object compilation_local_name_symbol_counter;
    Object compilation_local_name_listed_next_symbol;
    Object list_of_expressions_for_compilation, list_of_for_structures;
    Object list_of_reference_structures;
    Object focus_name_for_rule_or_formula_compilation, list_of_known_names;
    Object names_used_for_more_than_one_item;
    Object role_names_and_local_names_for_runtime_items;
    Object alist_of_local_names_and_role_names;
    Object local_names_not_associated_with_roles, top_level_reference_tree;
    Object local_name_errors, focus_local_names_for_focus_role_name;
    Object non_context_top_level_binding_forms, attribute_name_errors;
    Object reference_structures_originating_from_within_existence_predicate;
    Object local_iteration_forms, local_insertion_location, rule;
    Object designations_from_explicit_iteration_forms;
    Object source_designations_from_explicit_iteration_forms, rule_keyword;
    Object antecedent_expression, consequent_expression;
    Object compiling_antecedent_p, inside_action_iteration_p;
    Object pattern_checking_inverse_references, chaining_category_qm;
    Object focus_local_name_for_rule_compilation_qm, focus_too_narrow_qm;
    Object fatal_focus_error_info_qm;
    Object fatal_focus_error_info_for_all_compilations, compiling_rule_p;
    Object context_iteration_forms, compiled_antecedent_1;
    Object compiled_consequent_1, compiled_antecedent_2, compiled_consequent_2;
    Object number_of_no_binds, context_for_this_focus_local_name, body_of_rule;
    Object focus_local_name_continuation_qm, multiple_context_compilations;
    Object temp_1, only_multiple_compilation, focus_spec;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_3;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(36);
    Object result;

    x_note_fn_call(140,54);
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(Current_computation_frame,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = 
		nconc2(stack_change_list_2(Current_computation_frame,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	temp = Current_computation_frame;
	M_CAR(gensymed_symbol_1) = temp;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    35);
      compilation_local_name_symbol_counter = FIX((SI_Long)1L);
      compilation_local_name_listed_next_symbol = 
	      Compilation_local_name_symbol_supply;
      PUSH_SPECIAL_WITH_SYMBOL(Compilation_local_name_listed_next_symbol,Qcompilation_local_name_listed_next_symbol,compilation_local_name_listed_next_symbol,
	      34);
	PUSH_SPECIAL_WITH_SYMBOL(Compilation_local_name_symbol_counter,Qcompilation_local_name_symbol_counter,compilation_local_name_symbol_counter,
		33);
	  list_of_expressions_for_compilation = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(List_of_expressions_for_compilation,Qlist_of_expressions_for_compilation,list_of_expressions_for_compilation,
		  32);
	    list_of_for_structures = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(List_of_for_structures,Qlist_of_for_structures,list_of_for_structures,
		    31);
	      list_of_reference_structures = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(List_of_reference_structures,Qlist_of_reference_structures,list_of_reference_structures,
		      30);
		focus_name_for_rule_or_formula_compilation = focus_name_qm;
		PUSH_SPECIAL_WITH_SYMBOL(Focus_name_for_rule_or_formula_compilation,Qfocus_name_for_rule_or_formula_compilation,focus_name_for_rule_or_formula_compilation,
			29);
		  list_of_known_names = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(List_of_known_names,Qlist_of_known_names,list_of_known_names,
			  28);
		    names_used_for_more_than_one_item = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Names_used_for_more_than_one_item,Qnames_used_for_more_than_one_item,names_used_for_more_than_one_item,
			    27);
		      role_names_and_local_names_for_runtime_items = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Role_names_and_local_names_for_runtime_items,Qrole_names_and_local_names_for_runtime_items,role_names_and_local_names_for_runtime_items,
			      26);
			alist_of_local_names_and_role_names = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Alist_of_local_names_and_role_names,Qalist_of_local_names_and_role_names,alist_of_local_names_and_role_names,
				25);
			  local_names_not_associated_with_roles = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Local_names_not_associated_with_roles,Qlocal_names_not_associated_with_roles,local_names_not_associated_with_roles,
				  24);
			    top_level_reference_tree = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Top_level_reference_tree,Qtop_level_reference_tree,top_level_reference_tree,
				    23);
			      local_name_errors = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Local_name_errors,Qlocal_name_errors,local_name_errors,
				      22);
				focus_local_names_for_focus_role_name = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Focus_local_names_for_focus_role_name,Qfocus_local_names_for_focus_role_name,focus_local_names_for_focus_role_name,
					21);
				  non_context_top_level_binding_forms = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Non_context_top_level_binding_forms,Qnon_context_top_level_binding_forms,non_context_top_level_binding_forms,
					  20);
				    attribute_name_errors = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Attribute_name_errors,Qattribute_name_errors,attribute_name_errors,
					    19);
				      reference_structures_originating_from_within_existence_predicate 
					      = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Reference_structures_originating_from_within_existence_predicate,Qreference_structures_originating_from_within_existence_predicate,reference_structures_originating_from_within_existence_predicate,
					      18);
					local_iteration_forms = Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Local_iteration_forms,Qlocal_iteration_forms,local_iteration_forms,
						17);
					  local_insertion_location = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Local_insertion_location,Qlocal_insertion_location,local_insertion_location,
						  16);
					    rule = Current_computation_frame;
					    designations_from_explicit_iteration_forms 
						    = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Designations_from_explicit_iteration_forms,Qdesignations_from_explicit_iteration_forms,designations_from_explicit_iteration_forms,
						    15);
					      source_designations_from_explicit_iteration_forms 
						      = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Source_designations_from_explicit_iteration_forms,Qsource_designations_from_explicit_iteration_forms,source_designations_from_explicit_iteration_forms,
						      14);
						rule_translation = 
							filter_explicit_iteration_forms(rule_translation);
						rule_keyword = 
							FIRST(rule_translation);
						antecedent_expression = 
							SECOND(rule_translation);
						consequent_expression = 
							THIRD(rule_translation);
						compiling_antecedent_p = Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Compiling_antecedent_p,Qcompiling_antecedent_p,compiling_antecedent_p,
							13);
						  inside_action_iteration_p 
							  = Nil;
						  PUSH_SPECIAL_WITH_SYMBOL(Inside_action_iteration_p,Qinside_action_iteration_p,inside_action_iteration_p,
							  12);
						    pattern_checking_inverse_references 
							    = Nil;
						    PUSH_SPECIAL_WITH_SYMBOL(Pattern_checking_inverse_references,Qpattern_checking_inverse_references,pattern_checking_inverse_references,
							    11);
						      chaining_category_qm 
							      = Nil;
						      focus_local_name_for_rule_compilation_qm 
							      = Nil;
						      PUSH_SPECIAL_WITH_SYMBOL(Focus_local_name_for_rule_compilation_qm,Qfocus_local_name_for_rule_compilation_qm,focus_local_name_for_rule_compilation_qm,
							      10);
							focus_too_narrow_qm 
								= Nil;
							PUSH_SPECIAL_WITH_SYMBOL(Focus_too_narrow_qm,Qfocus_too_narrow_qm,focus_too_narrow_qm,
								9);
							  fatal_focus_error_info_qm 
								  = Nil;
							  PUSH_SPECIAL_WITH_SYMBOL(Fatal_focus_error_info_qm,Qfatal_focus_error_info_qm,fatal_focus_error_info_qm,
								  8);
							    fatal_focus_error_info_for_all_compilations 
								    = Nil;
							    PUSH_SPECIAL_WITH_SYMBOL(Fatal_focus_error_info_for_all_compilations,Qfatal_focus_error_info_for_all_compilations,fatal_focus_error_info_for_all_compilations,
								    7);
							      compiling_rule_p 
								      = T;
							      PUSH_SPECIAL_WITH_SYMBOL(Compiling_rule_p,Qcompiling_rule_p,compiling_rule_p,
								      6);
								context_iteration_forms 
									= Nil;
								PUSH_SPECIAL_WITH_SYMBOL(Context_iteration_forms,Qcontext_iteration_forms,context_iteration_forms,
									5);
								  compiled_antecedent_1 
									  = 
									  Nil;
								  PUSH_SPECIAL_WITH_SYMBOL(Compiled_antecedent_1,Qcompiled_antecedent_1,compiled_antecedent_1,
									  4);
								    compiled_consequent_1 
									    = 
									    Nil;
								    PUSH_SPECIAL_WITH_SYMBOL(Compiled_consequent_1,Qcompiled_consequent_1,compiled_consequent_1,
									    3);
								      compiled_antecedent_2 
									      = 
									      Nil;
								      compiled_consequent_2 
									      = 
									      Nil;
								      PUSH_SPECIAL_WITH_SYMBOL(Compiled_consequent_2,Qcompiled_consequent_2,compiled_consequent_2,
									      2);
									number_of_no_binds 
										= 
										FIX((SI_Long)0L);
									PUSH_SPECIAL_WITH_SYMBOL(Number_of_no_binds,Qnumber_of_no_binds,number_of_no_binds,
										1);
									  context_for_this_focus_local_name 
										  = 
										  Nil;
									  body_of_rule 
										  = 
										  Nil;
									  if ( 
										  !TRUEP(focus_name_qm)) 
										      {
									      if (Noting_changes_to_kb_p)
										  note_change_to_block_1(rule,
											  Qframe_flags);
									      svref_new_value_1 
										      = 
										      IFIX(ISVREF(rule,
										      (SI_Long)4L)) 
										      & 
										       
										      ~
										      (SI_Long)16384L;
									      ISVREF(rule,
										      (SI_Long)4L) 
										      = 
										      FIX(svref_new_value_1);
									      delete_all_frame_notes_for_rule_or_expression(Nil);
									  }
									  else
									      delete_compiler_frame_notes_for_role(focus_name_qm);
									  focus_local_name_continuation_qm 
										  = 
										  Nil;
									  multiple_context_compilations 
										  = 
										  Nil;
									next_loop:
									  result = compile1_expression_top(antecedent_expression,
										  consequent_expression,
										  Nil,
										  phrase_cons(focus_name_qm,
										  Nil),
										  focus_local_name_continuation_qm);
									  MVS_5(result,
										  Compiled_antecedent_1,
										  Compiled_consequent_1,
										  chaining_category_qm,
										  Focus_local_name_for_rule_compilation_qm,
										  focus_local_name_continuation_qm);
									  if (first_pass_problems_with_rule_compile_qm(focus_name_qm))
									      result = VALUES_2(Bad_rule,
										      Nil);
									  else if (focus_name_qm 
										  && 
										   
										  !TRUEP(Pattern_checking_inverse_references))
									      result = VALUES_2(Quniversal_compilation,
										      Nil);
									  else if ( 
										  !TRUEP(focus_name_qm) 
										  && 
										   
										  !TRUEP(reference_paths_generic_p(Top_level_reference_tree)) 
										  && 
										   
										  !TRUEP(expression_has_inverse_references_beyond_focus_p(Compiled_antecedent_1)) 
										  && 
										   
										  !TRUEP(Local_names_not_associated_with_roles)) 
										      {
									      temp_1 
										      = 
										      phrase_list_3(rule_keyword,
										      antecedent_expression,
										      consequent_expression);
									      result = VALUES_2(Nil,
										      temp_1);
									  }
									  else if (Focus_too_narrow_qm)
									      result = VALUES_2(CDR(context_for_general_compilation),
										      T);
									  else {
									      Compiled_consequent_2 
										      = 
										      compile_consequent(Compiled_consequent_1,
										      Qcompile2_action);
									      compile2_designations_from_explicit_iteration_forms();
									      compiling_antecedent_p 
										      = 
										      T;
									      PUSH_SPECIAL_WITH_SYMBOL(Compiling_antecedent_p,Qcompiling_antecedent_p,compiling_antecedent_p,
										      0);
										compiled_antecedent_2 
											= 
											compile2_expression_top(Compiled_antecedent_1);
									      POP_SPECIAL();
									      result = compile3_rule(compiled_antecedent_2,
										      Compiled_consequent_2,
										      focus_name_qm,
										      rule_keyword);
									  }
									  MVS_2(result,
										  context_for_this_focus_local_name,
										  body_of_rule);
									  if ( 
										  !EQ(context_for_this_focus_local_name,
										  Bad_rule))
									      multiple_context_compilations 
										      = 
										      nconc2(multiple_context_compilations,
										      phrase_cons(phrase_cons( 
										      !TRUEP(chaining_category_qm) 
										      ?
										       
										      focus_name_qm 
										      :
										       
										      EQ(focus_name_qm,
										      Focus_local_name_for_rule_compilation_qm) 
										      ?
										       
										      focus_name_qm 
										      :
										       
										      phrase_list_2(focus_name_qm,
										      Focus_local_name_for_rule_compilation_qm),
										      context_for_this_focus_local_name),
										      Nil));
									  reset_compilation_state();
									  if ( 
										  !TRUEP(focus_local_name_continuation_qm))
									      goto end_loop;
									  goto next_loop;
									end_loop:
									  reclaim_all_compilation_structures();
									  if (multiple_context_compilations) 
										      {
									      if ( 
										      !TRUEP(CDR(multiple_context_compilations))) 
											  {
										  only_multiple_compilation 
											  = 
											  CAR(multiple_context_compilations);
										  focus_spec 
											  = 
											  CAR(only_multiple_compilation);
										  if (CONSP(focus_spec)) 
											      {
										      if (EQ(FIRST(focus_spec),
											      THIRD(focus_spec))) 
												  {
											  temp 
												  = 
												  FIRST(focus_spec);
											  M_CAR(only_multiple_compilation) 
												  = 
												  temp;
										      }
										  }
									      }
									      else {
										  if (Noting_changes_to_kb_p)
										      note_change_to_block_1(rule,
											      Qframe_flags);
										  svref_new_value_1 
											  = 
											  IFIX(ISVREF(rule,
											  (SI_Long)4L)) 
											  | 
											  (SI_Long)16384L;
										  ISVREF(rule,
											  (SI_Long)4L) 
											  = 
											  FIX(svref_new_value_1);
									      }
									  }
									  if ( 
										  !TRUEP(multiple_context_compilations) 
										  && 
										   
										  !TRUEP(body_of_rule)) 
										      {
									      post_compiler_warning_note();
									      if (Fatal_focus_error_info_for_all_compilations)
										  handle_fatal_focus_errors(focus_name_qm);
									      temp_1 
										      = 
										      Nil;
									  }
									  else if ( 
										  !TRUEP(focus_name_qm))
									      temp_1 
										      = 
										      phrase_list_2(body_of_rule,
										      CAR(multiple_context_compilations));
									  else {
									      temp_1 
										      = 
										      multiple_context_compilations;
									      if (temp_1);
									      else
										  temp_1 
											  = 
											  phrase_cons(Nil,
											  Nil);
									  }
									  goto end_1;
									  temp_1 
										  = 
										  Qnil;
									end_1:;
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							POP_SPECIAL();
						      POP_SPECIAL();
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_2);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop_1;
	  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_2);
	  else {
	      temp_3 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_3) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(Current_computation_frame,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_2 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(Current_computation_frame,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(Current_computation_frame);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp_3 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_3);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
      result = VALUES_1(temp_1);
    POP_SPECIAL();
    return result;
}

/* RESET-COMPILATION-STATE */
Object reset_compilation_state()
{
    x_note_fn_call(140,55);
    List_of_known_names = Nil;
    Names_used_for_more_than_one_item = Nil;
    Focus_local_names_for_focus_role_name = Nil;
    Local_name_errors = Nil;
    Attribute_name_errors = Nil;
    Top_level_reference_tree = Nil;
    Pattern_checking_inverse_references = Nil;
    Fatal_focus_error_info_qm = Nil;
    Context_iteration_forms = Nil;
    Non_context_top_level_binding_forms = Nil;
    Role_names_and_local_names_for_runtime_items = Nil;
    Alist_of_local_names_and_role_names = Nil;
    Local_names_not_associated_with_roles = Nil;
    Compilation_local_name_symbol_counter = FIX((SI_Long)1L);
    Compilation_local_name_listed_next_symbol = 
	    Compilation_local_name_symbol_supply;
    Number_of_no_binds = FIX((SI_Long)0L);
    return reclaim_all_compilation_structures();
}

/* COMPILE-CONSEQUENT */
Object compile_consequent(consequent_expression,compile_function)
    Object consequent_expression, compile_function;
{
    Object temp, expression, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1;

    x_note_fn_call(140,56);
    temp = CAR(consequent_expression);
    expression = Nil;
    ab_loop_list_ = CDR(consequent_expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = SYMBOL_FUNCTION(compile_function);
    ab_loopvar__2 = phrase_cons(FUNCALL_1(temp_1,expression),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return phrase_cons(temp,temp_1);
}

static Object Qfor;                /* for */

/* FILTER-EXPLICIT-ITERATION-FORMS */
Object filter_explicit_iteration_forms(rule_translation)
    Object rule_translation;
{
    x_note_fn_call(140,57);
    if (CONSP(rule_translation) && EQ(FIRST(rule_translation),Qfor)) {
	Source_designations_from_explicit_iteration_forms = 
		nconc2(Source_designations_from_explicit_iteration_forms,
		phrase_cons(SECOND(rule_translation),Nil));
	return filter_explicit_iteration_forms(THIRD(rule_translation));
    }
    else
	return VALUES_1(rule_translation);
}

/* INVERSE-REFERENCE-STRUCTURE-IS-GLOBAL-END? */
Object inverse_reference_structure_is_global_end_qm(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(140,58);
    return VALUES_1(EQ(ISVREF(reference_structure,(SI_Long)1L),
	    Global_domain) ? T : Nil);
}

/* INSERT-WRAPPER-REFERENCES-FOR-LEFT-SIDE-OF-FORMULA */
Object insert_wrapper_references_for_left_side_of_formula(expression)
    Object expression;
{
    Object root_reference_is_global_symbol_qm, temp;
    Object wrapper_references_to_use_qm, for_structure, svref_new_value;

    x_note_fn_call(140,59);
    root_reference_is_global_symbol_qm = 
	    reference_structure_for_global_symbol_p(Wrapper_references_for_left_side_of_formula_qm);
    if (root_reference_is_global_symbol_qm) {
	temp = ISVREF(Wrapper_references_for_left_side_of_formula_qm,
		(SI_Long)5L);
	wrapper_references_to_use_qm = CAR(temp);
    }
    else
	wrapper_references_to_use_qm = 
		Wrapper_references_for_left_side_of_formula_qm;
    if (wrapper_references_to_use_qm) {
	if (reference_structure_provides_external_references_qm(wrapper_references_to_use_qm))
	    insert_forward_wrapper_references(expression,
		    wrapper_references_to_use_qm);
	if ( !TRUEP(root_reference_is_global_symbol_qm) &&  
		!EQ(ISVREF(wrapper_references_to_use_qm,(SI_Long)1L),
		Focus_name_for_rule_or_formula_compilation)) {
	    for_structure = make_compilation_reclaimable_for_structure();
	    svref_new_value = phrase_cons(Nil,
		    phrase_cons(ISVREF(wrapper_references_to_use_qm,
		    (SI_Long)1L),
		    phrase_cons(Focus_name_for_rule_or_formula_compilation,
		    Nil)));
	    SVREF(for_structure,FIX((SI_Long)1L)) = svref_new_value;
	    svref_new_value = ISVREF(expression,(SI_Long)1L);
	    SVREF(for_structure,FIX((SI_Long)2L)) = svref_new_value;
	    return VALUES_1(SVREF(expression,FIX((SI_Long)1L)) = 
		    for_structure);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INSERT-FORWARD-WRAPPER-REFERENCES */
Object insert_forward_wrapper_references(expression,wrapper_reference)
    Object expression, wrapper_reference;
{
    Object next_reference_structure, previous_for_structure;
    Object outermost_for_structure, first_time_qm, new_for_structure, temp;
    Object iteration_forms_to_be_inserted, innermost_iteration_form;
    Object svref_new_value;
    Object result;

    x_note_fn_call(140,60);
    next_reference_structure = wrapper_reference;
    previous_for_structure = Nil;
    outermost_for_structure = Nil;
    first_time_qm = T;
    new_for_structure = Nil;
  next_loop:
    new_for_structure = 
	    make_for_structure_given_reference_structure(next_reference_structure);
    if (first_time_qm && new_for_structure) {
	outermost_for_structure = new_for_structure;
	first_time_qm = Nil;
    }
    if (previous_for_structure)
	SVREF(previous_for_structure,FIX((SI_Long)2L)) = new_for_structure;
    if ( !TRUEP(ISVREF(next_reference_structure,(SI_Long)5L))) {
	result = VALUES_2(outermost_for_structure,new_for_structure);
	goto end_1;
    }
    previous_for_structure = new_for_structure;
    temp = ISVREF(next_reference_structure,(SI_Long)5L);
    next_reference_structure = CAR(temp);
    if ( 
	    !TRUEP(reference_structure_provides_external_references_qm(next_reference_structure))) 
		{
	result = VALUES_2(outermost_for_structure,new_for_structure);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    result = VALUES_1(Qnil);
  end_1:;
    MVS_2(result,iteration_forms_to_be_inserted,innermost_iteration_form);
    if (innermost_iteration_form) {
	svref_new_value = ISVREF(expression,(SI_Long)1L);
	SVREF(innermost_iteration_form,FIX((SI_Long)2L)) = svref_new_value;
	return VALUES_1(SVREF(expression,FIX((SI_Long)1L)) = 
		iteration_forms_to_be_inserted);
    }
    else
	return VALUES_1(Nil);
}

/* COMPILE-EXPRESSION */
Object compile_expression(expression,left_side_of_formula_qm,focus_names)
    Object expression, left_side_of_formula_qm, focus_names;
{
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object compilation_local_name_symbol_counter;
    Object compilation_local_name_listed_next_symbol, compiler_errors;
    Object compiler_warnings, list_of_expressions_for_compilation;
    Object list_of_for_structures, list_of_reference_structures;
    Object focus_name_for_rule_or_formula_compilation, list_of_known_names;
    Object names_used_for_more_than_one_item;
    Object role_names_and_local_names_for_runtime_items;
    Object alist_of_local_names_and_role_names;
    Object local_names_not_associated_with_roles, top_level_reference_tree;
    Object local_name_errors, focus_local_names_for_focus_role_name;
    Object non_context_top_level_binding_forms, attribute_name_errors;
    Object reference_structures_originating_from_within_existence_predicate;
    Object local_iteration_forms, local_insertion_location;
    Object compiled_expression_1, compiled_expression_2, compiled_expression_3;
    Object wrapper_references_for_left_side_of_formula_qm;
    Object compiling_expression_p, temp_1, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, temp_3, stack_change_pop_store, cons_1;
    Object next_cons;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(24);
    Object result;

    x_note_fn_call(140,61);
    SAVE_STACK();
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(Current_computation_frame,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = 
		nconc2(stack_change_list_2(Current_computation_frame,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	temp = Current_computation_frame;
	M_CAR(gensymed_symbol_1) = temp;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    23);
      compilation_local_name_symbol_counter = FIX((SI_Long)1L);
      compilation_local_name_listed_next_symbol = 
	      Compilation_local_name_symbol_supply;
      PUSH_SPECIAL_WITH_SYMBOL(Compilation_local_name_listed_next_symbol,Qcompilation_local_name_listed_next_symbol,compilation_local_name_listed_next_symbol,
	      22);
	PUSH_SPECIAL_WITH_SYMBOL(Compilation_local_name_symbol_counter,Qcompilation_local_name_symbol_counter,compilation_local_name_symbol_counter,
		21);
	  compiler_errors = Nil;
	  compiler_warnings = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Compiler_warnings,Qcompiler_warnings,compiler_warnings,
		  20);
	    PUSH_SPECIAL_WITH_SYMBOL(Compiler_errors,Qcompiler_errors,compiler_errors,
		    19);
	      remove_compiler_error_and_warning_frame_notes();
	      if (PUSH_UNWIND_PROTECT(0)) {
		  list_of_expressions_for_compilation = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(List_of_expressions_for_compilation,Qlist_of_expressions_for_compilation,list_of_expressions_for_compilation,
			  18);
		    list_of_for_structures = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(List_of_for_structures,Qlist_of_for_structures,list_of_for_structures,
			    17);
		      list_of_reference_structures = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(List_of_reference_structures,Qlist_of_reference_structures,list_of_reference_structures,
			      16);
			focus_name_for_rule_or_formula_compilation = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Focus_name_for_rule_or_formula_compilation,Qfocus_name_for_rule_or_formula_compilation,focus_name_for_rule_or_formula_compilation,
				15);
			  list_of_known_names = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(List_of_known_names,Qlist_of_known_names,list_of_known_names,
				  14);
			    names_used_for_more_than_one_item = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Names_used_for_more_than_one_item,Qnames_used_for_more_than_one_item,names_used_for_more_than_one_item,
				    13);
			      role_names_and_local_names_for_runtime_items 
				      = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Role_names_and_local_names_for_runtime_items,Qrole_names_and_local_names_for_runtime_items,role_names_and_local_names_for_runtime_items,
				      12);
				alist_of_local_names_and_role_names = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Alist_of_local_names_and_role_names,Qalist_of_local_names_and_role_names,alist_of_local_names_and_role_names,
					11);
				  local_names_not_associated_with_roles = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Local_names_not_associated_with_roles,Qlocal_names_not_associated_with_roles,local_names_not_associated_with_roles,
					  10);
				    top_level_reference_tree = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Top_level_reference_tree,Qtop_level_reference_tree,top_level_reference_tree,
					    9);
				      local_name_errors = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Local_name_errors,Qlocal_name_errors,local_name_errors,
					      8);
					focus_local_names_for_focus_role_name 
						= Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Focus_local_names_for_focus_role_name,Qfocus_local_names_for_focus_role_name,focus_local_names_for_focus_role_name,
						7);
					  non_context_top_level_binding_forms 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Non_context_top_level_binding_forms,Qnon_context_top_level_binding_forms,non_context_top_level_binding_forms,
						  6);
					    attribute_name_errors = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Attribute_name_errors,Qattribute_name_errors,attribute_name_errors,
						    5);
					      reference_structures_originating_from_within_existence_predicate 
						      = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Reference_structures_originating_from_within_existence_predicate,Qreference_structures_originating_from_within_existence_predicate,reference_structures_originating_from_within_existence_predicate,
						      4);
						local_iteration_forms = Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Local_iteration_forms,Qlocal_iteration_forms,local_iteration_forms,
							3);
						  local_insertion_location 
							  = Nil;
						  PUSH_SPECIAL_WITH_SYMBOL(Local_insertion_location,Qlocal_insertion_location,local_insertion_location,
							  2);
						    compiled_expression_1 
							    = Nil;
						    compiled_expression_2 
							    = Nil;
						    compiled_expression_3 
							    = Nil;
						    wrapper_references_for_left_side_of_formula_qm 
							    = Nil;
						    PUSH_SPECIAL_WITH_SYMBOL(Wrapper_references_for_left_side_of_formula_qm,Qwrapper_references_for_left_side_of_formula_qm,wrapper_references_for_left_side_of_formula_qm,
							    1);
						      compiling_expression_p 
							      = T;
						      PUSH_SPECIAL_WITH_SYMBOL(Compiling_expression_p,Qcompiling_expression_p,compiling_expression_p,
							      0);
							delete_all_frame_notes_for_rule_or_expression(Nil);
							if (left_side_of_formula_qm)
							    Focus_name_for_rule_or_formula_compilation 
								    = 
								    CAR(focus_names);
							compiled_expression_1 
								= 
								compile1_expression_top(expression,
								Nil,
								left_side_of_formula_qm,
								focus_names,
								Nil);
							if (first_pass_problems_with_expression_compile_qm(compiled_expression_1)) 
								    {
							    post_compiler_warning_note();
							    temp_1 = Nil;
							}
							else if ( 
								!TRUEP(focus_names) 
								&&  
								!TRUEP(reference_paths_generic_p(Top_level_reference_tree)))
							    temp_1 = 
								    expression;
							else {
							    compiled_expression_2 
								    = 
								    compile2_expression_top(compiled_expression_1);
							    if ( 
								    !TRUEP(Compiler_errors)) 
									{
								compiled_expression_3 
									= 
									compile3_expression_top(compiled_expression_2);
								temp_1 = 
									compiled_expression_3;
							    }
							    else
								temp_1 = Nil;
							}
							reclaim_all_compilation_structures();
							reclaim_gensym_list_1(focus_names);
						      POP_SPECIAL();
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  SAVE_VALUES(VALUES_1(temp_1));
	      }
	      POP_UNWIND_PROTECT(0);
	      add_compiler_error_and_warning_frame_notes();
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	      temp_1 = result;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_2);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop;
	  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_2);
	  else {
	      temp_3 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_3) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(Current_computation_frame,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_2 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(Current_computation_frame,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(Current_computation_frame);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp_3 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_3);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
      result = VALUES_1(temp_1);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(List_of_compiler_frame_note_types, Qlist_of_compiler_frame_note_types);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_bad_status_compiler_frame_note_types, Qlist_of_bad_status_compiler_frame_note_types);

static Object array_constant;      /* # */

static Object string_constant_1;   /* " is a G2 internal attribute which may not be referenced directly " */

static Object string_constant_2;   /* " are G2 internal attributes which may not be referenced directly " */

static Object string_constant_3;   /* ", " */

static Object string_constant_4;   /* ", and " */

static Object string_constant_5;   /* " and " */

/* WRITE-ILLEGAL-ATTRIBUTE-NOTE */
Object write_illegal_attribute_note(particulars,frame)
    Object particulars, frame;
{
    Object ab_loop_destructure_, attribute, rest_of_illegal_attributes, temp;

    x_note_fn_call(140,62);
    ab_loop_destructure_ = particulars;
    attribute = Nil;
    rest_of_illegal_attributes = Nil;
    attribute = CAR(ab_loop_destructure_);
    rest_of_illegal_attributes = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)14L));
    twrite(attribute);
    if ( !TRUEP(rest_of_illegal_attributes)) {
	temp = twrite_general_string( !TRUEP(CDR(particulars)) ? 
		string_constant_1 : string_constant_2);
	goto end_1;
    }
    if (CDR(rest_of_illegal_attributes))
	temp = string_constant_3;
    else if (CDDR(particulars))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    attribute = CAR(rest_of_illegal_attributes);
    rest_of_illegal_attributes = CDR(rest_of_illegal_attributes);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* WRITE-ROOT-REFERENCE-ROLE-NAME-SAME-AS-PREVIOUSLY-SPECIFIED-LOCAL-NAME-NOTE */
Object write_root_reference_role_name_same_as_previously_specified_local_name_note(particulars,
	    frame)
    Object particulars, frame;
{
    Object ab_loop_destructure_, local_name, rest_of_local_names, temp;

    x_note_fn_call(140,63);
    ab_loop_destructure_ = particulars;
    local_name = Nil;
    rest_of_local_names = Nil;
    local_name = CAR(ab_loop_destructure_);
    rest_of_local_names = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)15L));
    twrite(local_name);
    if ( !TRUEP(rest_of_local_names)) {
	temp = twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)39L));
	goto end_1;
    }
    if (CDR(rest_of_local_names))
	temp = string_constant_3;
    else if (CDDR(particulars))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    local_name = CAR(rest_of_local_names);
    rest_of_local_names = CDR(rest_of_local_names);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_6;   /* " refers to more than one runtime item" */

static Object string_constant_7;   /* " refer to more than one runtime item" */

/* WRITE-EXPLICITLY-SPECIFIED-LOCAL-NAME-REFERS-TO-MORE-THAN-ONE-ITEM-NOTE */
Object write_explicitly_specified_local_name_refers_to_more_than_one_item_note(particulars,
	    frame)
    Object particulars, frame;
{
    Object ab_loop_destructure_, local_name, rest_of_local_names, temp;

    x_note_fn_call(140,64);
    ab_loop_destructure_ = particulars;
    local_name = Nil;
    rest_of_local_names = Nil;
    local_name = CAR(ab_loop_destructure_);
    rest_of_local_names = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)15L));
    twrite(local_name);
    if ( !TRUEP(rest_of_local_names)) {
	temp = twrite_general_string( !TRUEP(CDR(particulars)) ? 
		string_constant_6 : string_constant_7);
	goto end_1;
    }
    if (CDR(rest_of_local_names))
	temp = string_constant_3;
    else if (CDDR(particulars))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    local_name = CAR(rest_of_local_names);
    rest_of_local_names = CDR(rest_of_local_names);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object string_constant_8;   /* "them " */

static Object string_constant_9;   /* "it " */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* WRITE-AMBIGUOUS-REFERENCE-NOTE */
Object write_ambiguous_reference_note(particulars,frame)
    Object particulars, frame;
{
    Object ab_loop_destructure_, role_name, rest_of_role_names, temp;

    x_note_fn_call(140,65);
    ab_loop_destructure_ = particulars;
    role_name = Nil;
    rest_of_role_names = Nil;
    role_name = CAR(ab_loop_destructure_);
    rest_of_role_names = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)14L));
    twrite(role_name);
    if ( !TRUEP(rest_of_role_names)) {
	twrite_general_string( !TRUEP(CDR(particulars)) ? 
		string_constant_6 : string_constant_7);
	goto end_1;
    }
    if (CDR(rest_of_role_names))
	temp = string_constant_3;
    else if (CDDR(particulars))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    role_name = CAR(rest_of_role_names);
    rest_of_role_names = CDR(rest_of_role_names);
    goto next_loop;
  end_loop:
  end_1:;
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)18L));
    twrite(CDR(particulars) ? string_constant_8 : string_constant_9);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)14L));
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)82L));
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_7,
	    FIX((SI_Long)40L)));
    return VALUES_1(Nil);
}

static Object array_constant_8;    /* # */

static Object string_constant_10;  /* " is used to name both a role and a kb object" */

static Object string_constant_11;  /* " are used to name both roles and kb objects" */

static Object array_constant_9;    /* # */

/* WRITE-ROLE-AND-KB-OBJECT-NAMESPACE-CONFUSION-NOTE */
Object write_role_and_kb_object_namespace_confusion_note(particulars,frame)
    Object particulars, frame;
{
    Object ab_loop_destructure_, name, rest_of_names, temp;

    x_note_fn_call(140,66);
    ab_loop_destructure_ = particulars;
    name = Nil;
    rest_of_names = Nil;
    name = CAR(ab_loop_destructure_);
    rest_of_names = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)9L));
    twrite(name);
    if ( !TRUEP(rest_of_names)) {
	twrite_general_string( !TRUEP(CDR(particulars)) ? 
		string_constant_10 : string_constant_11);
	goto end_1;
    }
    if (CDR(rest_of_names))
	temp = string_constant_3;
    else if (CDDR(particulars))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    name = CAR(rest_of_names);
    rest_of_names = CDR(rest_of_names);
    goto next_loop;
  end_loop:
  end_1:;
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_9,
	    FIX((SI_Long)42L)));
    return VALUES_1(Nil);
}

static Object string_constant_12;  /* " is used to name a role, but is a reserved word" */

static Object string_constant_13;  /* " are used to name roles, but are reserved words" */

static Object array_constant_10;   /* # */

/* WRITE-LOCAL-NAME-AND-INTERNAL-TYPE-NAMESPACE-CONFUSION-NOTE */
Object write_local_name_and_internal_type_namespace_confusion_note(particulars,
	    frame)
    Object particulars, frame;
{
    Object ab_loop_destructure_, name, rest_of_names, temp;

    x_note_fn_call(140,67);
    ab_loop_destructure_ = particulars;
    name = Nil;
    rest_of_names = Nil;
    name = CAR(ab_loop_destructure_);
    rest_of_names = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)9L));
    twrite(name);
    if ( !TRUEP(rest_of_names)) {
	twrite_general_string( !TRUEP(CDR(particulars)) ? 
		string_constant_12 : string_constant_13);
	goto end_1;
    }
    if (CDR(rest_of_names))
	temp = string_constant_3;
    else if (CDDR(particulars))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    name = CAR(rest_of_names);
    rest_of_names = CDR(rest_of_names);
    goto next_loop;
  end_loop:
  end_1:;
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_10,
	    FIX((SI_Long)25L)));
    return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

/* WRITE-ILLEGAL-REFERENCE-FROM-AN-EVERY-QUANTIFIER-NOTE */
Object write_illegal_reference_from_an_every_quantifier_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,68);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_11,
	    FIX((SI_Long)101L)));
    return VALUES_1(Nil);
}

static Object array_constant_12;   /* # */

/* WRITE-ILLEGAL-QUANTIFIER-IN-RULE-CONSEQUENT-NOTE */
Object write_illegal_quantifier_in_rule_consequent_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,69);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_12,
	    FIX((SI_Long)67L)));
    return VALUES_1(Nil);
}

static Object array_constant_13;   /* # */

/* WRITE-ILLEGAL-REFERENCE-OUTSIDE-ACTION-NOTE */
Object write_illegal_reference_outside_action_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,70);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_13,
	    FIX((SI_Long)74L)));
    return VALUES_1(Nil);
}

static Object array_constant_14;   /* # */

/* WRITE-ILLEGAL-REFERENCE-OUTSIDE-CREATE-ACTION-NOTE */
Object write_illegal_reference_outside_create_action_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,71);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_14,
	    FIX((SI_Long)104L)));
    return VALUES_1(Nil);
}

static Object array_constant_15;   /* # */

/* WRITE-TOO-MANY-DELETE-ACTIONS-NOTE */
Object write_too_many_delete_actions_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,72);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_15,
	    FIX((SI_Long)65L)));
    return VALUES_1(Nil);
}

static Object array_constant_16;   /* # */

/* WRITE-ILLEGAL-REFERENCE-OUTSIDE-NOT-NOTE */
Object write_illegal_reference_outside_not_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,73);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_16,
	    FIX((SI_Long)78L)));
    return VALUES_1(Nil);
}

static Object Qa;                  /* a */

static Object Qquantifier;         /* quantifier */

static Object Qaggregator;         /* aggregator */

static Object Qthere_exists_literal;  /* there-exists-literal */

static Object Qthere_exists;       /* there-exists */

static Object Qfor_every_literal;  /* for-every-literal */

static Object Qfor_every;          /* for-every */

static Object Qaggregated_average;  /* aggregated-average */

static Object Qaverage;            /* average */

static Object Qan;                 /* an */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

static Object array_constant_21;   /* # */

/* WRITE-ILLEGAL-REFERENCE-OUTSIDE-EXPRESSION-NOTE */
Object write_illegal_reference_outside_expression_note(particulars,frame)
    Object particulars, frame;
{
    Object operator_1, ab_loop_list_, indefinite_article;
    Object quantifier_or_aggregator_qm;

    x_note_fn_call(140,74);
    operator_1 = Nil;
    ab_loop_list_ = particulars;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    operator_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    indefinite_article = Qa;
    if (quantifier_p(operator_1))
	quantifier_or_aggregator_qm = Qquantifier;
    else if (aggregator_p(operator_1))
	quantifier_or_aggregator_qm = Qaggregator;
    else
	quantifier_or_aggregator_qm = Qnil;
    if (EQ(operator_1,Qthere_exists_literal))
	operator_1 = Qthere_exists;
    else if (EQ(operator_1,Qfor_every_literal))
	operator_1 = Qfor_every;
    else if (EQ(operator_1,Qaggregated_average)) {
	operator_1 = Qaverage;
	indefinite_article = Qan;
    }
    twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)20L));
    twrite(indefinite_article);
    twrite_beginning_of_wide_string(array_constant_18,FIX((SI_Long)1L));
    twrite(operator_1);
    if (EQ(quantifier_or_aggregator_qm,Qquantifier))
	twrite_beginning_of_wide_string(array_constant_19,FIX((SI_Long)60L));
    else if (EQ(quantifier_or_aggregator_qm,Qaggregator))
	twrite_beginning_of_wide_string(array_constant_20,FIX((SI_Long)60L));
    else
	twrite_beginning_of_wide_string(array_constant_21,FIX((SI_Long)60L));
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object array_constant_22;   /* # */

/* WRITE-ILLEGAL-REFERENCE-OUTSIDE-THERE-EXISTS-NOTE */
Object write_illegal_reference_outside_there_exists_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,75);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_22,
	    FIX((SI_Long)120L)));
    return VALUES_1(Nil);
}

static Object Qif_expression;      /* if-expression */

static Object Qab_if;              /* if */

static Object Qab_or;              /* or */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

/* WRITE-ILLEGAL-REFERENCE-OUTSIDE-SUB-EXPRESSION-OF-EXPRESSION-NOTE */
Object write_illegal_reference_outside_sub_expression_of_expression_note(particulars,
	    frame)
    Object particulars, frame;
{
    Object operator_1, ab_loop_list_;

    x_note_fn_call(140,76);
    operator_1 = Nil;
    ab_loop_list_ = particulars;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    operator_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(operator_1,Qif_expression))
	operator_1 = Qab_if;
    else if (EQ(operator_1,Qab_or))
	operator_1 = Qab_or;
    twrite_beginning_of_wide_string(array_constant_23,FIX((SI_Long)42L));
    twrite(operator_1);
    twrite_beginning_of_wide_string(array_constant_24,FIX((SI_Long)64L));
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

/* WRITE-ILLEGAL-REFERENCE-OUTSIDE-ANTECEDENT-CLAUSE-NOTE */
Object write_illegal_reference_outside_antecedent_clause_note(particulars,
	    frame)
    Object particulars, frame;
{
    x_note_fn_call(140,77);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

static Object array_constant_27;   /* # */

/* WRITE-FATAL-FOCUS-ERROR-NOTE */
Object write_fatal_focus_error_note(particulars,frame)
    Object particulars, frame;
{
    Object rest_of_role_names_and_fatal_focus_errors;
    Object role_name_and_fatal_focus_error, role_name_qm, fatal_focus_error;
    Object last_time_qm;

    x_note_fn_call(140,78);
    rest_of_role_names_and_fatal_focus_errors = particulars;
    role_name_and_fatal_focus_error = Nil;
    role_name_qm = Nil;
    fatal_focus_error = Nil;
    last_time_qm = Nil;
  next_loop:
    if ( !TRUEP(rest_of_role_names_and_fatal_focus_errors))
	goto end_loop;
    role_name_and_fatal_focus_error = 
	    CAR(rest_of_role_names_and_fatal_focus_errors);
    role_name_qm = CAR(role_name_and_fatal_focus_error);
    fatal_focus_error = SECOND(role_name_and_fatal_focus_error);
    last_time_qm =  !TRUEP(CDR(rest_of_role_names_and_fatal_focus_errors)) 
	    ? T : Nil;
    twrite_beginning_of_wide_string(array_constant_25,FIX((SI_Long)8L));
    twrite(role_name_qm);
    write_fatal_focus_error(fatal_focus_error);
    twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)36L));
    if ( !TRUEP(last_time_qm))
	twrite_beginning_of_wide_string(array_constant_27,FIX((SI_Long)3L));
    rest_of_role_names_and_fatal_focus_errors = 
	    M_CDR(rest_of_role_names_and_fatal_focus_errors);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object array_constant_28;   /* # */

static Object list_constant_6;     /* # */

static Object array_constant_29;   /* # */

static Object array_constant_30;   /* # */

static Object list_constant_7;     /* # */

static Object array_constant_31;   /* # */

static Object array_constant_32;   /* # */

static Object Qinvoke;             /* invoke */

static Object Qinform;             /* inform */

static Object Qactivate;           /* activate */

static Object array_constant_33;   /* # */

static Object Qset_position;       /* set-position */

static Object array_constant_34;   /* # */

static Object Qset_heading;        /* set-heading */

static Object array_constant_35;   /* # */

static Object Qnon_invertible_role;  /* non-invertible-role */

static Object array_constant_36;   /* # */

static Object array_constant_37;   /* # */

static Object array_constant_38;   /* # */

/* WRITE-FATAL-FOCUS-ERROR */
Object write_fatal_focus_error(fatal_focus_error)
    Object fatal_focus_error;
{
    x_note_fn_call(140,79);
    if (SYMBOLP(fatal_focus_error)) {
	twrite_beginning_of_wide_string(array_constant_28,FIX((SI_Long)11L));
	if (member_eql(fatal_focus_error,list_constant_6)) {
	    twrite_beginning_of_wide_string(array_constant_29,
		    FIX((SI_Long)2L));
	    twrite(fatal_focus_error);
	    return twrite_beginning_of_wide_string(array_constant_30,
		    FIX((SI_Long)8L));
	}
	else if (member_eql(fatal_focus_error,list_constant_7)) {
	    twrite_beginning_of_wide_string(array_constant_31,
		    FIX((SI_Long)20L));
	    return twrite_beginning_of_wide_string(array_constant_32,
		    FIX((SI_Long)17L));
	}
	else if (EQ(fatal_focus_error,Qinvoke) || EQ(fatal_focus_error,
		Qinform) || EQ(fatal_focus_error,Qactivate)) {
	    twrite_beginning_of_wide_string(array_constant_33,
		    FIX((SI_Long)3L));
	    twrite(fatal_focus_error);
	    return twrite_beginning_of_wide_string(array_constant_30,
		    FIX((SI_Long)8L));
	}
	else if (EQ(fatal_focus_error,Qset_position))
	    return twrite_beginning_of_wide_string(array_constant_34,
		    FIX((SI_Long)14L));
	else if (EQ(fatal_focus_error,Qset_heading))
	    return twrite_beginning_of_wide_string(array_constant_35,
		    FIX((SI_Long)16L));
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(CAR(fatal_focus_error),Qnon_invertible_role)) {
	twrite_beginning_of_wide_string(array_constant_36,FIX((SI_Long)12L));
	twrite_beginning_of_wide_string(array_constant_37,FIX((SI_Long)31L));
	if (THIRD(fatal_focus_error))
	    print_role_or_role_and_designation(SECOND(fatal_focus_error),
		    Nil,CDDR(fatal_focus_error));
	else
	    print_role(SECOND(fatal_focus_error));
	return twrite_beginning_of_wide_string(array_constant_38,
		FIX((SI_Long)1L));
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_14;  /* "the focal class~a " */

static Object string_constant_15;  /* "es" */

static Object string_constant_16;  /* "" */

static Object string_constant_17;  /* "and" */

static Object string_constant_18;  /* " could not be compiled, since ~a not mentioned in the rule" */

static Object string_constant_19;  /* "they are" */

static Object string_constant_20;  /* "it is" */

/* WRITE-FOCUS-CLASS-COMPILATION-FAILED-NOTE */
Object write_focus_class_compilation_failed_note(particulars,frame)
    Object particulars, frame;
{
    x_note_fn_call(140,80);
    tformat(2,string_constant_14,CDR(particulars) ? string_constant_15 : 
	    string_constant_16);
    write_list_in_chicago_style(2,particulars,string_constant_17);
    GENSYM_RETURN_ONE(tformat(2,string_constant_18,CDR(particulars) ? 
	    string_constant_19 : string_constant_20));
    return VALUES_1(Nil);
}

static Object array_constant_39;   /* # */

static Object array_constant_40;   /* # */

/* WRITE-ILLEGAL-QUANTIFIER-WITHIN-NTH-ELEMENT-ROLE-NOTE */
Object write_illegal_quantifier_within_nth_element_role_note(particulars,frame)
    Object particulars, frame;
{
    Object rest_of_roles_and_nth_element_expressions, role, nth_element_role;
    Object domain_list, last_time_qm, temp;

    x_note_fn_call(140,81);
    rest_of_roles_and_nth_element_expressions = particulars;
    role = Nil;
    nth_element_role = Nil;
    domain_list = Nil;
    last_time_qm = Nil;
  next_loop:
    if ( !TRUEP(rest_of_roles_and_nth_element_expressions))
	goto end_loop;
    temp = CAR(rest_of_roles_and_nth_element_expressions);
    role = CAR(temp);
    temp = CAR(rest_of_roles_and_nth_element_expressions);
    temp = CDR(temp);
    nth_element_role = CAR(temp);
    temp = CAR(rest_of_roles_and_nth_element_expressions);
    temp = CDR(temp);
    domain_list = CDR(temp);
    last_time_qm =  !TRUEP(CDR(rest_of_roles_and_nth_element_expressions)) 
	    ? T : Nil;
    twrite_beginning_of_wide_string(array_constant_39,FIX((SI_Long)44L));
    print_role(role);
    twrite_beginning_of_wide_string(array_constant_40,FIX((SI_Long)67L));
    print_role_or_role_and_designation(nth_element_role,Nil,domain_list);
    twrite_beginning_of_wide_string(array_constant_38,FIX((SI_Long)1L));
    if ( !TRUEP(last_time_qm))
	twrite_beginning_of_wide_string(array_constant_27,FIX((SI_Long)3L));
    rest_of_roles_and_nth_element_expressions = 
	    M_CDR(rest_of_roles_and_nth_element_expressions);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object string_constant_21;  /* "the reference to \"~a\" in the expression \" " */

static Object array_constant_41;   /* # */

static Object array_constant_42;   /* # */

/* WRITE-CIRCULARITY-IN-NTH-ELEMENT-INDEX-NOTE */
Object write_circularity_in_nth_element_index_note(particulars,frame)
    Object particulars, frame;
{
    Object rest_of_info, role, nth_element_role, domain_list, last_time_qm;
    Object temp;

    x_note_fn_call(140,82);
    rest_of_info = particulars;
    role = Nil;
    nth_element_role = Nil;
    domain_list = Nil;
    last_time_qm = Nil;
  next_loop:
    if ( !TRUEP(rest_of_info))
	goto end_loop;
    temp = CAR(rest_of_info);
    role = CAR(temp);
    temp = CAR(rest_of_info);
    temp = CDR(temp);
    nth_element_role = CAR(temp);
    temp = CAR(rest_of_info);
    temp = CDR(temp);
    domain_list = CDR(temp);
    last_time_qm =  !TRUEP(CDR(rest_of_info)) ? T : Nil;
    tformat(2,string_constant_21,role);
    print_role_or_role_and_designation(nth_element_role,Nil,domain_list);
    twrite_beginning_of_wide_string(array_constant_41,FIX((SI_Long)55L));
    print_role_or_role_and_designation(nth_element_role,Nil,domain_list);
    twrite_beginning_of_wide_string(array_constant_42,FIX((SI_Long)22L));
    if ( !TRUEP(last_time_qm))
	twrite_beginning_of_wide_string(array_constant_27,FIX((SI_Long)3L));
    rest_of_info = M_CDR(rest_of_info);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Unknown_references, Qunknown_references);

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object array_constant_43;   /* # */

static Object array_constant_44;   /* # */

static Object array_constant_45;   /* # */

/* WRITE-UNKNOWN-REFERENCES-NOTE */
Object write_unknown_references_note(particulars,frame)
    Object particulars, frame;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    Object rest_of_role_names_and_unknown_references;
    Object role_name_and_unknown_references, role_name_qm, unknown_references;
    Object last_time_qm, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(140,83);
    if (SIMPLE_VECTOR_P(frame) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(frame,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	rest_of_role_names_and_unknown_references = particulars;
	role_name_and_unknown_references = Nil;
	role_name_qm = Nil;
	unknown_references = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Unknown_references,Qunknown_references,unknown_references,
		0);
	  last_time_qm = Nil;
	next_loop:
	  if ( !TRUEP(rest_of_role_names_and_unknown_references))
	      goto end_loop;
	  role_name_and_unknown_references = 
		  CAR(rest_of_role_names_and_unknown_references);
	  role_name_qm = CAR(role_name_and_unknown_references);
	  Unknown_references = SECOND(role_name_and_unknown_references);
	  last_time_qm =  
		  !TRUEP(CDR(rest_of_role_names_and_unknown_references)) ? 
		  T : Nil;
	  if ( !TRUEP(role_name_qm))
	      twrite_beginning_of_wide_string(array_constant_43,
		      FIX((SI_Long)29L));
	  else {
	      twrite_beginning_of_wide_string(array_constant_44,
		      FIX((SI_Long)30L));
	      twrite(role_name_qm);
	      twrite_beginning_of_wide_string(array_constant_45,
		      FIX((SI_Long)2L));
	  }
	  write_unknown_references(Unknown_references);
	  if ( !TRUEP(last_time_qm))
	      twrite_beginning_of_wide_string(array_constant_27,
		      FIX((SI_Long)3L));
	  rest_of_role_names_and_unknown_references = 
		  M_CDR(rest_of_role_names_and_unknown_references);
	  goto next_loop;
	end_loop:
	  temp_1 = Qnil;
	POP_SPECIAL();
    }
    else {
	temp_1 = CAR(particulars);
	temp_1 = write_unknown_references(SECOND(temp_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

static Object array_constant_46;   /* # */

static Object string_constant_22;  /* " is unknown" */

static Object string_constant_23;  /* " are unknown" */

/* WRITE-UNKNOWN-REFERENCES */
Object write_unknown_references(list_of_unknown_references)
    Object list_of_unknown_references;
{
    Object ab_loop_destructure_, unknown_reference, rest_of_unknown_references;
    Object temp;

    x_note_fn_call(140,84);
    ab_loop_destructure_ = list_of_unknown_references;
    unknown_reference = Nil;
    rest_of_unknown_references = Nil;
    unknown_reference = CAR(ab_loop_destructure_);
    rest_of_unknown_references = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant_46,FIX((SI_Long)14L));
    twrite(unknown_reference);
    if ( !TRUEP(rest_of_unknown_references))
	return twrite_general_string( 
		!TRUEP(CDR(list_of_unknown_references)) ? 
		string_constant_22 : string_constant_23);
    if (CDR(rest_of_unknown_references))
	temp = string_constant_3;
    else if (CDDR(list_of_unknown_references))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    unknown_reference = CAR(rest_of_unknown_references);
    rest_of_unknown_references = CDR(rest_of_unknown_references);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REFERENCE-PATHS-GENERIC-P */
Object reference_paths_generic_p(reference_tree)
    Object reference_tree;
{
    Object reference_structure, ab_loop_list_, needing_reference_structures;
    Object role_name, local_name;

    x_note_fn_call(140,85);
    reference_structure = Nil;
    ab_loop_list_ = reference_tree;
    needing_reference_structures = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    needing_reference_structures = ISVREF(reference_structure,(SI_Long)5L);
    role_name = atomic_naming_element_of_role(ISVREF(reference_structure,
	    (SI_Long)3L));
    local_name = ISVREF(reference_structure,(SI_Long)2L);
    if (implicit_iterator_p(ISVREF(reference_structure,(SI_Long)6L)) || 
	    EQ(ISVREF(reference_structure,(SI_Long)6L),Qquantifier) || 
	    CDR(needing_reference_structures) || 
	    EQ(ISVREF(reference_structure,(SI_Long)1L),Needed_domain) ||  
	    !EQ(role_name,local_name))
	return VALUES_1(T);
    else if (reference_paths_generic_p(needing_reference_structures))
	return VALUES_1(T);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* EXPRESSION-HAS-INVERSE-REFERENCES-BEYOND-FOCUS-P */
Object expression_has_inverse_references_beyond_focus_p(expression_for_compilation_qm)
    Object expression_for_compilation_qm;
{
    x_note_fn_call(140,86);
    return VALUES_1(Nil);
}

/* FIRST-PASS-PROBLEMS-WITH-RULE-COMPILE? */
Object first_pass_problems_with_rule_compile_qm(focus_name_qm)
    Object focus_name_qm;
{
    Object problem_qm, temp;

    x_note_fn_call(140,87);
    problem_qm = Nil;
    if ( !TRUEP(focus_name_qm)) {
	problem_qm = Nil;
	temp = illegal_attribute_qm();
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
	temp = local_name_error_qm();
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
	temp = evaluation_value_type_used_to_name_kb_object_qm();
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
	temp = role_name_used_to_name_kb_object_qm();
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
	temp = unknown_references_qm(Top_level_reference_tree,focus_name_qm);
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
	temp = illegal_references_in_rule_qm();
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
	temp = illegal_quantifier_in_rule_consequent_qm();
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
	temp = illegal_quantifier_within_nth_element_role_qm();
	if (temp);
	else
	    temp = problem_qm;
	problem_qm = temp;
    }
    temp = check_for_fatal_focus_error(focus_name_qm);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    return VALUES_1(problem_qm);
}

/* FIRST-PASS-PROBLEMS-WITH-EXPRESSION-COMPILE? */
Object first_pass_problems_with_expression_compile_qm(compiled_expression_1)
    Object compiled_expression_1;
{
    Object problem_qm, temp;

    x_note_fn_call(140,88);
    problem_qm = Nil;
    temp = illegal_attribute_qm();
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = local_name_error_qm();
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = evaluation_value_type_used_to_name_kb_object_qm();
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = role_name_used_to_name_kb_object_qm();
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = SIMPLE_VECTOR_P(compiled_expression_1) && 
	    EQ(ISVREF(compiled_expression_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    && ISVREF(compiled_expression_1,(SI_Long)3L) ? 
	    unknown_references_qm(Top_level_reference_tree,Nil) : Nil;
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = 
	    expression_has_inverse_references_beyond_focus_p(compiled_expression_1);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = illegal_references_in_expression_qm(compiled_expression_1);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    return VALUES_1(problem_qm);
}

/* ILLEGAL-ATTRIBUTE? */
Object illegal_attribute_qm()
{
    x_note_fn_call(140,89);
    return VALUES_1(Nil);
}

/* LOCAL-NAME-ERROR? */
Object local_name_error_qm()
{
    Object error_entry, ab_loop_list_;

    x_note_fn_call(140,90);
    error_entry = Nil;
    ab_loop_list_ = Local_name_errors;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    error_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_to_frame_note_particulars_list_if_necessary(CDR(error_entry),
	    CAR(error_entry),Current_computation_frame);
    goto next_loop;
  end_loop:;
    return VALUES_1(Local_name_errors);
}

static Object Qlocal_name_and_internal_type_namespace_confusion;  /* local-name-and-internal-type-namespace-confusion */

/* EVALUATION-VALUE-TYPE-USED-TO-NAME-KB-OBJECT? */
Object evaluation_value_type_used_to_name_kb_object_qm()
{
    Object problem_qm, name, ignore, ab_loop_list_, ab_loop_desetq_, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(140,91);
    problem_qm = Nil;
    name = Nil;
    ignore = Nil;
    ab_loop_list_ = Alist_of_local_names_and_role_names;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    ignore = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    skip_list = CDR(Defined_evaluation_value_types);
    key_value = name;
    key_hash_value = SXHASH_SYMBOL_1(name) & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)31L;
    ab_loop_bind_ = bottom_level;
  next_loop_1:
    if (level < ab_loop_bind_)
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_2:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_3:
    if ( !TRUEP(marked))
	goto end_loop_2;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_3;
  end_loop_2:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_1;
    goto next_loop_2;
  end_loop_3:
  end_1:
    level = level - (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? (EQ(key_value,
	    ISVREF(curr,(SI_Long)2L)) ? TRUEP(ISVREF(curr,(SI_Long)3L)) : 
	    TRUEP(Nil)) : TRUEP(Nil)) {
	add_to_frame_note_particulars_list_if_necessary(name,
		Qlocal_name_and_internal_type_namespace_confusion,
		Current_computation_frame);
	problem_qm = T;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(problem_qm);
    return VALUES_1(Qnil);
}

static Object Qrole_and_kb_object_namespace_confusion;  /* role-and-kb-object-namespace-confusion */

/* ROLE-NAME-USED-TO-NAME-KB-OBJECT? */
Object role_name_used_to_name_kb_object_qm()
{
    Object kb_object_name, problem_qm, reference_structure, ab_loop_list_;
    Object role_and_local_name_entry_qm;
    char temp;

    x_note_fn_call(140,92);
    kb_object_name = Nil;
    problem_qm = Nil;
    reference_structure = Nil;
    ab_loop_list_ = Top_level_reference_tree;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (reference_structure_for_global_symbol_p(reference_structure)) {
	kb_object_name = ISVREF(reference_structure,(SI_Long)2L);
	role_and_local_name_entry_qm = assq_function(kb_object_name,
		Role_names_and_local_names_for_runtime_items);
	temp = role_and_local_name_entry_qm ? 
		EQ(CAR(role_and_local_name_entry_qm),
		CDR(role_and_local_name_entry_qm)) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	add_to_frame_note_particulars_list_if_necessary(kb_object_name,
		Qrole_and_kb_object_namespace_confusion,
		Current_computation_frame);
	problem_qm = T;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(problem_qm);
    return VALUES_1(Qnil);
}

/* CHECK-FOR-FATAL-FOCUS-ERROR */
Object check_for_fatal_focus_error(focus_name_qm)
    Object focus_name_qm;
{
    Object problem_qm, temp;

    x_note_fn_call(140,93);
    problem_qm = Nil;
    temp = check_for_focus_inside_invertible_roles(focus_name_qm);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    if (Fatal_focus_error_info_qm) {
	Fatal_focus_error_info_for_all_compilations = 
		nconc2(Fatal_focus_error_info_for_all_compilations,
		phrase_cons(Fatal_focus_error_info_qm,Nil));
	temp = Fatal_focus_error_info_for_all_compilations;
    }
    else
	temp = Nil;
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    return VALUES_1(problem_qm);
}

/* CHECK-FOR-FOCUS-INSIDE-INVERTIBLE-ROLES */
Object check_for_focus_inside_invertible_roles(focus_name_qm)
    Object focus_name_qm;
{
    Object problem_qm, temp, reference_structure, next_reference_structure;
    Object role, temp_1, embedded_expression_qm;

    x_note_fn_call(140,94);
    problem_qm = Nil;
    if (Pattern_checking_inverse_references) {
	temp = ISVREF(Pattern_checking_inverse_references,(SI_Long)5L);
	reference_structure = CAR(temp);
    }
    else
	reference_structure = Nil;
    next_reference_structure = Nil;
    role = Nil;
  next_loop:
    if ( !TRUEP(reference_structure) || 
	    inverse_reference_structure_is_global_end_qm(reference_structure))
	goto end_loop;
    temp = ISVREF(reference_structure,(SI_Long)5L);
    next_reference_structure = CAR(temp);
    role = simple_role_of_role(ISVREF(reference_structure,(SI_Long)3L));
    if ( !TRUEP(invertible_role_p(role))) {
	temp_1 = Fatal_focus_error_info_for_all_compilations;
	temp = phrase_list_2(Qnon_invertible_role,SYMBOLP(role) ? role : 
		copy_list_using_phrase_conses(role));
	embedded_expression_qm = ISVREF(reference_structure,(SI_Long)12L);
	Fatal_focus_error_info_for_all_compilations = nconc2(temp_1,
		phrase_cons(nconc2(temp,embedded_expression_qm ? 
		phrase_list_2(ISVREF(reference_structure,(SI_Long)1L),
		embedded_expression_qm) : Nil),Nil));
	problem_qm = T;
    }
    reference_structure = next_reference_structure;
    goto next_loop;
  end_loop:
    return VALUES_1(problem_qm);
    return VALUES_1(Qnil);
}

static Object Qfatal_focus_error;  /* fatal-focus-error */

/* HANDLE-FATAL-FOCUS-ERRORS */
Object handle_fatal_focus_errors(focus_name_qm)
    Object focus_name_qm;
{
    Object error_info, ab_loop_list_;

    x_note_fn_call(140,95);
    error_info = Nil;
    ab_loop_list_ = Fatal_focus_error_info_for_all_compilations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    error_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_to_frame_note_particulars_list_if_necessary(slot_value_list_2(focus_name_qm,
	    SYMBOLP(error_info) ? error_info : 
	    copy_for_slot_value(error_info)),Qfatal_focus_error,
	    Current_computation_frame);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Special_globally_known_references, Qspecial_globally_known_references);

static Object Qreference_to_item_or_datum_qm;  /* reference-to-item-or-datum? */

/* UNKNOWN-REFERENCES? */
Object unknown_references_qm(reference_tree,focus_name_qm)
    Object reference_tree, focus_name_qm;
{
    Object unknown_references, root_reference_structure, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(140,96);
    unknown_references = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Unknown_references,Qunknown_references,unknown_references,
	    0);
      check_for_problem_in_tree(reference_tree,Qreference_to_item_or_datum_qm);
      root_reference_structure = Nil;
      ab_loop_list_ = reference_tree;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      root_reference_structure = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (EQ(ISVREF(root_reference_structure,(SI_Long)1L),Needed_domain) 
	      &&  !TRUEP(memq_function(ISVREF(root_reference_structure,
	      (SI_Long)2L),Special_globally_known_references)))
	  Unknown_references = nconc2(Unknown_references,
		  slot_value_cons_1(ISVREF(root_reference_structure,
		  (SI_Long)2L),Nil));
      goto next_loop;
    end_loop:
      if (Unknown_references) {
	  add_to_frame_note_particulars_list_if_necessary(slot_value_list_2(focus_name_qm,
		  Unknown_references),Qunknown_references,
		  Current_computation_frame);
	  result = VALUES_1(Unknown_references);
	  goto end_1;
      }
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object Qnth_element;        /* nth-element */

/* REFERENCE-TO-ITEM-OR-DATUM? */
Object reference_to_item_or_datum_qm(reference_structure)
    Object reference_structure;
{
    Object role, temp;
    char temp_1;

    x_note_fn_call(140,97);
    role = simple_role_of_role(ISVREF(reference_structure,(SI_Long)3L));
    if (CONSP(role) && EQ(CAR(role),Qnth_element)) {
	temp = ISVREF(reference_structure,(SI_Long)5L);
	temp_1 = TRUEP(CDR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	Unknown_references = nconc2(Unknown_references,
		slot_value_cons_1(ISVREF(reference_structure,(SI_Long)2L),
		Nil));
	return VALUES_1(Unknown_references);
    }
    else
	return check_for_problem_in_tree(reference_structure,
		Qreference_to_item_or_datum_qm);
}

static Object Qillegal_quantifier_in_rule_consequent;  /* illegal-quantifier-in-rule-consequent */

/* ILLEGAL-QUANTIFIER-IN-RULE-CONSEQUENT? */
Object illegal_quantifier_in_rule_consequent_qm()
{
    Object consequent_action, ab_loop_list_, ab_loop_it_;
    char temp;

    x_note_fn_call(140,98);
    consequent_action = Nil;
    ab_loop_list_ = CDR(Compiled_consequent_1);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    consequent_action = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = illegal_quantifier_in_action_qm(consequent_action);
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp)
	return add_frame_note(5,Qillegal_quantifier_in_rule_consequent,
		Current_computation_frame,Nil,T,Nil);
    else
	return VALUES_1(Nil);
}

/* ILLEGAL-QUANTIFIER-IN-ACTION? */
Object illegal_quantifier_in_action_qm(action)
    Object action;
{
    Object compiled_specific_expression, temp, designation;

    x_note_fn_call(140,99);
    if (SIMPLE_VECTOR_P(action) && EQ(ISVREF(action,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	compiled_specific_expression = ISVREF(action,(SI_Long)1L);
	temp = CAR(compiled_specific_expression);
	if (EQ(temp,Qinvoke) || EQ(temp,Qbreak))
	    return VALUES_1(Nil);
	else {
	    designation = SECOND(compiled_specific_expression);
	    if (SIMPLE_VECTOR_P(designation) && EQ(ISVREF(designation,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
		    && ISVREF(designation,(SI_Long)3L)) {
		temp = ISVREF(designation,(SI_Long)3L);
		return illegal_any_quantifier_in_tree_qm(CAR(temp));
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qillegal_quantifier_within_nth_element_role_1;  /* illegal-quantifier-within-nth-element-role-1 */

/* ILLEGAL-QUANTIFIER-WITHIN-NTH-ELEMENT-ROLE? */
Object illegal_quantifier_within_nth_element_role_qm()
{
    x_note_fn_call(140,100);
    return check_for_problem_in_tree(Top_level_reference_tree,
	    Qillegal_quantifier_within_nth_element_role_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Role_and_domains_for_nth_element_expression, Qrole_and_domains_for_nth_element_expression);

/* ILLEGAL-QUANTIFIER-WITHIN-NTH-ELEMENT-ROLE-1 */
Object illegal_quantifier_within_nth_element_role_1(reference_structure)
    Object reference_structure;
{
    Object simple_role, temp, role_and_domains_for_nth_element_expression;
    Declare_special(1);
    Object result;

    x_note_fn_call(140,101);
    simple_role = simple_role_of_role(ISVREF(reference_structure,(SI_Long)3L));
    if (CONSP(simple_role) && EQ(CAR(simple_role),Qnth_element)) {
	temp = simple_role_of_role(ISVREF(reference_structure,(SI_Long)3L));
	role_and_domains_for_nth_element_expression = phrase_list_3(temp,
		ISVREF(reference_structure,(SI_Long)1L),
		ISVREF(reference_structure,(SI_Long)12L));
	PUSH_SPECIAL_WITH_SYMBOL(Role_and_domains_for_nth_element_expression,Qrole_and_domains_for_nth_element_expression,role_and_domains_for_nth_element_expression,
		0);
	  result = illegal_any_quantifier_in_tree_qm(reference_structure);
	POP_SPECIAL();
	return result;
    }
    else
	return check_for_problem_in_tree(reference_structure,
		Qillegal_quantifier_within_nth_element_role_1);
}

static Object Qany;                /* any */

static Object Qillegal_quantifier_within_nth_element_role;  /* illegal-quantifier-within-nth-element-role */

static Object Qillegal_any_quantifier_in_tree_qm;  /* illegal-any-quantifier-in-tree? */

/* ILLEGAL-ANY-QUANTIFIER-IN-TREE? */
Object illegal_any_quantifier_in_tree_qm(reference_structure)
    Object reference_structure;
{
    Object temp;

    x_note_fn_call(140,102);
    if (EQ(ISVREF(reference_structure,(SI_Long)6L),Qany)) {
	temp = 
		copy_for_slot_value(simple_role_of_role(ISVREF(reference_structure,
		(SI_Long)3L)));
	return add_to_frame_note_particulars_list_if_necessary(slot_value_cons_1(temp,
		copy_for_slot_value(Role_and_domains_for_nth_element_expression)),
		Qillegal_quantifier_within_nth_element_role,
		Current_computation_frame);
    }
    else
	return check_for_problem_in_tree(reference_structure,
		Qillegal_any_quantifier_in_tree_qm);
}

/* CHECK-FOR-PROBLEM-IN-TREE */
Object check_for_problem_in_tree(reference_structure_or_tree,
	    function_to_do_check)
    Object reference_structure_or_tree, function_to_do_check;
{
    Object problem_qm, reference_structure, ab_loop_list_, temp;

    x_note_fn_call(140,103);
    problem_qm = Nil;
    reference_structure = Nil;
    ab_loop_list_ = SIMPLE_VECTOR_P(reference_structure_or_tree) && 
	    EQ(ISVREF(reference_structure_or_tree,(SI_Long)0L),
	    Qg2_defstruct_structure_name_reference_structure_g2_struct) ? 
	    ISVREF(reference_structure_or_tree,(SI_Long)5L) : 
	    reference_structure_or_tree;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = FUNCALL_1(function_to_do_check,reference_structure);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    goto next_loop;
  end_loop:
    return VALUES_1(problem_qm);
    return VALUES_1(Qnil);
}

static Object Qcircularity_in_nth_element_index;  /* circularity-in-nth-element-index */

/* CIRCULARITY-IN-NTH-ELEMENT-INDEX? */
Object circularity_in_nth_element_index_qm(compiled_expression_1)
    Object compiled_expression_1;
{
    Object problem_qm, designation, ab_loop_list_, temp, reference_structure;
    Object ab_loop_list__1, embedded_expression_qm;
    Object reference_structure_in_embedded_expression, ab_loop_list__2;
    Object reference_structure_for_nth_element_role, temp_1;

    x_note_fn_call(140,104);
    if (SIMPLE_VECTOR_P(compiled_expression_1) && 
	    EQ(ISVREF(compiled_expression_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	problem_qm = Nil;
	designation = Nil;
	ab_loop_list_ = ISVREF(compiled_expression_1,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	designation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = ISVREF(designation,(SI_Long)2L);
	if (CDR(temp)) {
	    reference_structure = Nil;
	    ab_loop_list__1 = ISVREF(designation,(SI_Long)3L);
	    embedded_expression_qm = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    reference_structure = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    embedded_expression_qm = ISVREF(reference_structure,(SI_Long)11L);
	    if (SIMPLE_VECTOR_P(embedded_expression_qm) && 
		    EQ(ISVREF(embedded_expression_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_reference_structure_g2_struct)) 
			{
		reference_structure_in_embedded_expression = Nil;
		ab_loop_list__2 = ISVREF(embedded_expression_qm,(SI_Long)3L);
	      next_loop_2:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_2;
		reference_structure_in_embedded_expression = 
			M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		if (ISVREF(get_copy_of_reference_structure_in_highest_level_reference_tree(reference_structure_in_embedded_expression),
			(SI_Long)4L)) {
		    temp = ISVREF(reference_structure,(SI_Long)5L);
		    reference_structure_for_nth_element_role = CAR(temp);
		    temp = 
			    ISVREF(reference_structure_in_embedded_expression,
			    (SI_Long)2L);
		    temp_1 = 
			    simple_role_of_role(ISVREF(reference_structure_for_nth_element_role,
			    (SI_Long)3L));
		    add_to_frame_note_particulars_list_if_necessary(copy_for_slot_value(phrase_list_4(temp,
			    temp_1,ISVREF(reference_structure,(SI_Long)2L),
			    ISVREF(reference_structure_for_nth_element_role,
			    (SI_Long)12L))),
			    Qcircularity_in_nth_element_index,
			    Current_computation_frame);
		    problem_qm = T;
		}
		goto next_loop_2;
	      end_loop_2:;
	    }
	    goto next_loop_1;
	  end_loop_1:;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(problem_qm);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* ILLEGAL-REFERENCES-IN-RULE? */
Object illegal_references_in_rule_qm()
{
    Object problem_qm, temp;

    x_note_fn_call(140,105);
    problem_qm = Nil;
    temp = illegal_references_in_rule_antecedent_qm(Compiled_antecedent_1);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = illegal_references_in_rule_consequent_qm(Compiled_consequent_1);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    return VALUES_1(problem_qm);
}

/* ILLEGAL-REFERENCES-IN-RULE-ANTECEDENT? */
Object illegal_references_in_rule_antecedent_qm(compiled_antecedent_1)
    Object compiled_antecedent_1;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(140,106);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_antecedent_1,Qcompiled_antecedent_1,compiled_antecedent_1,
	    0);
      result = illegal_references_in_expression_qm(Compiled_antecedent_1);
    POP_SPECIAL();
    return result;
}

static Object Qsimultaneously;     /* simultaneously */

/* ILLEGAL-REFERENCES-IN-RULE-CONSEQUENT? */
Object illegal_references_in_rule_consequent_qm(compiled_consequent_1)
    Object compiled_consequent_1;
{
    Object problem_qm, temp, problem_qm_1, consequent_expression;
    Object ab_loop_list_, problem_qm_2;
    char simultaneous_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(140,107);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_consequent_1,Qcompiled_consequent_1,compiled_consequent_1,
	    0);
      simultaneous_qm = EQ(CAR(Compiled_consequent_1),Qsimultaneously);
      problem_qm = Nil;
      temp = simultaneous_qm ? 
	      more_than_one_delete_action_qm(Compiled_consequent_1) : Nil;
      if (temp);
      else
	  temp = problem_qm;
      problem_qm = temp;
      problem_qm_1 = Nil;
      consequent_expression = Nil;
      ab_loop_list_ = CDR(Compiled_consequent_1);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      consequent_expression = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      problem_qm_2 = Nil;
      temp = illegal_references_in_expression_qm(consequent_expression);
      if (temp);
      else
	  temp = problem_qm_2;
      problem_qm_2 = temp;
      temp = illegal_reference_outside_action_qm(consequent_expression,
	      simultaneous_qm ? T : Nil);
      if (temp);
      else
	  temp = problem_qm_2;
      problem_qm_2 = temp;
      temp = problem_qm_2;
      if (temp);
      else
	  temp = problem_qm_1;
      problem_qm_1 = temp;
      goto next_loop;
    end_loop:
      temp = problem_qm_1;
      goto end_1;
      temp = Qnil;
    end_1:;
      if (temp);
      else
	  temp = problem_qm;
      problem_qm = temp;
      result = VALUES_1(problem_qm);
    POP_SPECIAL();
    return result;
}

static Object Qtoo_many_delete_actions;  /* too-many-delete-actions */

/* MORE-THAN-ONE-DELETE-ACTION? */
Object more_than_one_delete_action_qm(compiled_consequent_1)
    Object compiled_consequent_1;
{
    Object delete_action_count, consequent_expression, ab_loop_list_, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(140,108);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_consequent_1,Qcompiled_consequent_1,compiled_consequent_1,
	    0);
      delete_action_count = FIX((SI_Long)0L);
      consequent_expression = Nil;
      ab_loop_list_ = CDR(Compiled_consequent_1);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      consequent_expression = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      gensymed_symbol = IFIX(delete_action_count);
      temp = ISVREF(consequent_expression,(SI_Long)1L);
      gensymed_symbol_1 = EQ(CAR(temp),Qdelete) ? (SI_Long)1L : (SI_Long)0L;
      delete_action_count = FIX(gensymed_symbol + gensymed_symbol_1);
      if (IFIX(delete_action_count) > (SI_Long)1L) {
	  add_frame_note(5,Qtoo_many_delete_actions,
		  Current_computation_frame,Nil,T,Nil);
	  result = VALUES_1(T);
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* ILLEGAL-REFERENCES-IN-EXPRESSION? */
Object illegal_references_in_expression_qm(compiled_expression_1)
    Object compiled_expression_1;
{
    Object problem_qm, temp;

    x_note_fn_call(140,109);
    problem_qm = Nil;
    temp = 
	    illegal_reference_from_an_every_quantifier_qm(compiled_expression_1);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = illegal_reference_outside_expression_qm(compiled_expression_1);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    temp = circularity_in_nth_element_index_qm(compiled_expression_1);
    if (temp);
    else
	temp = problem_qm;
    problem_qm = temp;
    return VALUES_1(problem_qm);
}

static Object Qillegal_reference_from_an_every_quantifier;  /* illegal-reference-from-an-every-quantifier */

/* ILLEGAL-REFERENCE-FROM-AN-EVERY-QUANTIFIER? */
Object illegal_reference_from_an_every_quantifier_qm(expression)
    Object expression;
{
    Object compiled_specific_expression_qm, root_reference_structure;
    Object ab_loop_list_, ab_loop_it_;
    char temp;

    x_note_fn_call(140,110);
    compiled_specific_expression_qm = SIMPLE_VECTOR_P(expression) && 
	    EQ(ISVREF(expression,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    ? ISVREF(expression,(SI_Long)1L) : Nil;
    if (compiled_specific_expression_qm) {
	root_reference_structure = Nil;
	ab_loop_list_ = ISVREF(expression,(SI_Long)3L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	root_reference_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = 
		illegal_every_quantifier_in_reference_tree_qm(root_reference_structure);
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	add_frame_note(5,Qillegal_reference_from_an_every_quantifier,
		Current_computation_frame,Nil,T,Nil);
	return VALUES_1(T);
    }
    else
	return illegal_reference_from_an_every_quantifier_rec_qm(expression);
}

/* ILLEGAL-REFERENCE-FROM-AN-EVERY-QUANTIFIER-REC? */
Object illegal_reference_from_an_every_quantifier_rec_qm(expression)
    Object expression;
{
    Object compiled_specific_expression_to_investigate_qm, sub_expression;
    Object ab_loop_list_, ab_loop_it_;
    Object compiled_specific_expression_for_sub_expression;
    Object root_reference_structure, ab_loop_list__1;
    char temp;

    x_note_fn_call(140,111);
    compiled_specific_expression_to_investigate_qm = 
	    SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    ? ISVREF(expression,(SI_Long)1L) : Nil;
    if (compiled_specific_expression_to_investigate_qm && 
	    CONSP(compiled_specific_expression_to_investigate_qm) && 
	    logical_operator_p(CAR(compiled_specific_expression_to_investigate_qm))) 
		{
	sub_expression = Nil;
	ab_loop_list_ = CDR(compiled_specific_expression_to_investigate_qm);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sub_expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	compiled_specific_expression_for_sub_expression = 
		SIMPLE_VECTOR_P(sub_expression) && 
		EQ(ISVREF(sub_expression,(SI_Long)0L),
		Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
		? ISVREF(sub_expression,(SI_Long)1L) : Nil;
	if (compiled_specific_expression_for_sub_expression) {
	    if (ATOM(compiled_specific_expression_for_sub_expression) ||  
		    !TRUEP(logical_operator_p(CAR(compiled_specific_expression_for_sub_expression)))) 
			{
		root_reference_structure = Nil;
		ab_loop_list__1 = ISVREF(sub_expression,(SI_Long)3L);
		ab_loop_it_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		root_reference_structure = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		ab_loop_it_ = 
			illegal_every_quantifier_in_reference_tree_qm(root_reference_structure);
		if (ab_loop_it_)
		    goto end_1;
		goto next_loop_1;
	      end_loop_1:
		ab_loop_it_ = Qnil;
	      end_1:;
	    }
	    else
		ab_loop_it_ = 
			illegal_reference_from_an_every_quantifier_rec_qm(sub_expression);
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_2:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	add_frame_note(5,Qillegal_reference_from_an_every_quantifier,
		Current_computation_frame,Nil,T,Nil);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qillegal_every_quantifier_in_reference_tree_qm;  /* illegal-every-quantifier-in-reference-tree? */

/* ILLEGAL-EVERY-QUANTIFIER-IN-REFERENCE-TREE? */
Object illegal_every_quantifier_in_reference_tree_qm(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(140,112);
    if (EQ(ISVREF(reference_structure,(SI_Long)6L),Qevery))
	return reference_structure_provides_external_references_qm(reference_structure);
    else
	return check_for_problem_in_tree(reference_structure,
		Qillegal_every_quantifier_in_reference_tree_qm);
}

/* OPERATOR-TO-CHECK-FOR-ILLEGAL-REFERENCE-P */
Object operator_to_check_for_illegal_reference_p(operator_1)
    Object operator_1;
{
    x_note_fn_call(140,113);
    return quantifier_or_aggregator_p(operator_1);
}

static Object Qillegal_reference_outside_there_exists;  /* illegal-reference-outside-there-exists */

static Object Qillegal_reference_outside_expression;  /* illegal-reference-outside-expression */

/* ILLEGAL-REFERENCE-OUTSIDE-EXPRESSION? */
Object illegal_reference_outside_expression_qm(expression)
    Object expression;
{
    Object compiled_specific_expression_to_investigate_qm, operator_1;
    Object sub_expression, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(140,114);
    compiled_specific_expression_to_investigate_qm = 
	    SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    ? ISVREF(expression,(SI_Long)1L) : Nil;
    if (compiled_specific_expression_to_investigate_qm && 
	    CONSP(compiled_specific_expression_to_investigate_qm)) {
	operator_1 = CAR(compiled_specific_expression_to_investigate_qm);
	if (operator_to_check_for_illegal_reference_p(operator_1)) {
	    if (EQ(operator_1,Qthere_exists_literal)) {
		if (expression_provides_external_references_qm(THIRD(compiled_specific_expression_to_investigate_qm))) 
			    {
		    add_frame_note(5,
			    Qillegal_reference_outside_there_exists,
			    Current_computation_frame,Nil,T,Nil);
		    return VALUES_1(T);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else if (expression_provides_external_references_qm(expression)) {
		add_to_frame_note_particulars_list_if_necessary(operator_1,
			Qillegal_reference_outside_expression,
			Current_computation_frame);
		return VALUES_1(T);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    sub_expression = Nil;
	    ab_loop_list_ = 
		    CDR(compiled_specific_expression_to_investigate_qm);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    sub_expression = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = 
		    illegal_reference_outside_expression_qm(sub_expression);
	    if (ab_loop_it_)
		return VALUES_1(ab_loop_it_);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qcreate;             /* create */

static Object Qcreate_by_cloning;  /* create-by-cloning */

static Object Qcreate_connection;  /* create-connection */

static Object Qcreate_explanation;  /* create-explanation */

static Object Qillegal_reference_outside_create_action;  /* illegal-reference-outside-create-action */

static Object Qcall_assignment_action;  /* call-assignment-action */

static Object Qillegal_reference_outside_action;  /* illegal-reference-outside-action */

/* ILLEGAL-REFERENCE-OUTSIDE-ACTION? */
Object illegal_reference_outside_action_qm(action,simultaneous_qm)
    Object action, simultaneous_qm;
{
    Object compiled_specific_expression, temp, root_reference_structure;
    Object ab_loop_list_, sub_root_reference_structure, ab_loop_list__1;
    Object ab_loop_it_;

    x_note_fn_call(140,115);
    if (SIMPLE_VECTOR_P(action) && EQ(ISVREF(action,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	compiled_specific_expression = ISVREF(action,(SI_Long)1L);
	if (compiled_specific_expression && 
		CONSP(compiled_specific_expression)) {
	    temp = CAR(compiled_specific_expression);
	    if (EQ(temp,Qcreate) || EQ(temp,Qcreate_by_cloning) || EQ(temp,
		    Qcreate_connection) || EQ(temp,Qcreate_explanation)) {
		if (simultaneous_qm && 
			expression_provides_external_references_qm(THIRD(compiled_specific_expression))) 
			    {
		    add_frame_note(5,
			    Qillegal_reference_outside_create_action,
			    Current_computation_frame,Nil,T,Nil);
		    return VALUES_1(T);
		}
		else
		    temp = 
			    expression_provides_external_references_qm(SECOND(compiled_specific_expression));
	    }
	    else if (EQ(temp,Qcall_assignment_action)) {
		if (simultaneous_qm && 
			expression_provides_external_references_qm(SECOND(compiled_specific_expression))) 
			    {
		    add_frame_note(5,
			    Qillegal_reference_outside_create_action,
			    Current_computation_frame,Nil,T,Nil);
		    return VALUES_1(T);
		}
		else
		    temp = 
			    expression_provides_external_references_qm(FOURTH(compiled_specific_expression));
	    }
	    else {
		root_reference_structure = Nil;
		ab_loop_list_ = ISVREF(action,(SI_Long)3L);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		root_reference_structure = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (EQ(ISVREF(root_reference_structure,(SI_Long)2L),
			Focus_range) || EQ(ISVREF(root_reference_structure,
			(SI_Long)1L),Needed_domain)) {
		    sub_root_reference_structure = Nil;
		    ab_loop_list__1 = ISVREF(root_reference_structure,
			    (SI_Long)5L);
		    ab_loop_it_ = Nil;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_1;
		    sub_root_reference_structure = M_CAR(ab_loop_list__1);
		    ab_loop_list__1 = M_CDR(ab_loop_list__1);
		    ab_loop_it_ = 
			    reference_structure_provides_external_references_qm(sub_root_reference_structure);
		    if (ab_loop_it_)
			goto end_1;
		    goto next_loop_1;
		  end_loop_1:
		  end_1:;
		}
		else if (reference_structure_provides_external_references_qm(root_reference_structure)) 
			    {
		    temp = T;
		    goto end_2;
		}
		goto next_loop;
	      end_loop:
		temp = Qnil;
	      end_2:;
	    }
	    if (temp) {
		add_frame_note(5,Qillegal_reference_outside_action,
			Current_computation_frame,Nil,T,Nil);
		return VALUES_1(T);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* EXPRESSION-PROVIDES-EXTERNAL-REFERENCES? */
Object expression_provides_external_references_qm(expression)
    Object expression;
{
    Object root_reference_structure, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(140,116);
    if (SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	root_reference_structure = Nil;
	ab_loop_list_ = ISVREF(expression,(SI_Long)3L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	root_reference_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = 
		reference_structure_provides_external_references_qm(root_reference_structure);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* REFERENCE-STRUCTURE-PROVIDES-EXTERNAL-REFERENCES? */
Object reference_structure_provides_external_references_qm(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(140,117);
    return VALUES_1( 
	    !TRUEP(reference_structures_equivalent_qm(reference_structure,
	    get_copy_of_reference_structure_in_highest_level_reference_tree(reference_structure))) 
	    ? T : Nil);
}

/* REFERENCE-STRUCTURES-EQUIVALENT? */
Object reference_structures_equivalent_qm(reference_structure_1,
	    reference_structure_2)
    Object reference_structure_1, reference_structure_2;
{
    Object rest_of_sub_reference_structures_1;
    Object rest_of_sub_reference_structures_2, sub_reference_structure_1;
    Object sub_reference_structure_2;

    x_note_fn_call(140,118);
    if (EQ(ISVREF(reference_structure_1,(SI_Long)1L),
	    ISVREF(reference_structure_2,(SI_Long)1L)) && 
	    EQ(ISVREF(reference_structure_1,(SI_Long)2L),
	    ISVREF(reference_structure_2,(SI_Long)2L)) && 
	    EQ(ISVREF(reference_structure_1,(SI_Long)3L),
	    ISVREF(reference_structure_2,(SI_Long)3L)) && 
	    EQ(ISVREF(reference_structure_1,(SI_Long)6L),
	    ISVREF(reference_structure_2,(SI_Long)6L))) {
	rest_of_sub_reference_structures_1 = ISVREF(reference_structure_1,
		(SI_Long)5L);
	rest_of_sub_reference_structures_2 = ISVREF(reference_structure_2,
		(SI_Long)5L);
	sub_reference_structure_1 = Nil;
	sub_reference_structure_2 = Nil;
      next_loop:
	sub_reference_structure_1 = CAR(rest_of_sub_reference_structures_1);
	sub_reference_structure_2 = CAR(rest_of_sub_reference_structures_2);
	if ( !(rest_of_sub_reference_structures_1 && 
		rest_of_sub_reference_structures_2))
	    goto end_loop;
	if ( 
		!TRUEP(reference_structures_equivalent_qm(sub_reference_structure_1,
		sub_reference_structure_2)))
	    return VALUES_1(Nil);
	rest_of_sub_reference_structures_1 = 
		CDR(rest_of_sub_reference_structures_1);
	rest_of_sub_reference_structures_2 = 
		CDR(rest_of_sub_reference_structures_2);
	goto next_loop;
      end_loop:
	return VALUES_1( !(rest_of_sub_reference_structures_1 || 
		rest_of_sub_reference_structures_2) ? T : Nil);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-ALL-FRAME-NOTES-FOR-RULE-OR-EXPRESSION */
Object delete_all_frame_notes_for_rule_or_expression(delete_only_from_component_particulars_qm)
    Object delete_only_from_component_particulars_qm;
{
    Object notes_to_delete;

    x_note_fn_call(140,119);
    notes_to_delete = gensym_cons_1(Qcompiler_errors,
	    List_of_compiler_frame_note_types);
    delete_frame_notes_of_types_in_list(Current_computation_frame,
	    notes_to_delete,delete_only_from_component_particulars_qm);
    reclaim_gensym_cons_1(notes_to_delete);
    return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

/* DELETE-COMPILER-FRAME-NOTES-FOR-ROLE */
Object delete_compiler_frame_notes_for_role(role_name)
    Object role_name;
{
    Object type_of_note, ab_loop_list_, frame_note_particulars;
    Object particular_to_delete, temp;

    x_note_fn_call(140,120);
    type_of_note = Nil;
    ab_loop_list_ = list_constant_8;
    frame_note_particulars = Nil;
    particular_to_delete = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    type_of_note = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (Current_computation_component_particulars)
	frame_note_particulars = 
		get_particulars_of_frame_note_from_component_particulars(type_of_note,
		Current_computation_frame,
		Current_computation_component_particulars);
    else {
	temp = ISVREF(Current_computation_frame,(SI_Long)8L);
	frame_note_particulars = getfq_function_no_default(CDR(temp),
		type_of_note);
    }
    particular_to_delete = assq_function(role_name,frame_note_particulars);
    delete_from_frame_note_particulars_list(particular_to_delete,
	    type_of_note,Current_computation_frame);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* BAD-STATUS-COMPILER-FRAME-NOTES? */
Object bad_status_compiler_frame_notes_qm varargs_1(int, n)
{
    Object frame, temp, current_computation_frame;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(140,121);
    INIT_ARGS_nonrelocating();
    frame = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    temp = frame;
    if (temp);
    else
	temp = Current_computation_frame;
    current_computation_frame = temp;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      if (Current_computation_component_particulars)
	  result = bad_status_compiler_frame_notes_for_component_particulars_qm(Current_computation_frame,
		  Current_computation_component_particulars);
      else {
	  temp = ISVREF(Current_computation_frame,(SI_Long)8L);
	  result = bad_status_compiler_frame_notes_1_qm(CDR(temp));
      }
    POP_SPECIAL();
    return result;
}

/* BAD-STATUS-COMPILER-FRAME-NOTES-1? */
Object bad_status_compiler_frame_notes_1_qm(frame_notes)
    Object frame_notes;
{
    Object ab_loop_destructure_, type_of_note, rest_of_plist, temp;

    x_note_fn_call(140,122);
    ab_loop_destructure_ = frame_notes;
    type_of_note = Nil;
    rest_of_plist = Nil;
    type_of_note = CAR(ab_loop_destructure_);
    temp = CDR(ab_loop_destructure_);
    rest_of_plist = CDR(temp);
  next_loop:
    if (memq_function(type_of_note,
	    List_of_bad_status_compiler_frame_note_types))
	return VALUES_1(T);
    if ( !TRUEP(rest_of_plist))
	goto end_loop;
    type_of_note = CAR(rest_of_plist);
    temp = CDR(rest_of_plist);
    rest_of_plist = CDR(temp);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* BAD-STATUS-COMPILER-FRAME-NOTES-FOR-COMPONENT-PARTICULARS? */
Object bad_status_compiler_frame_notes_for_component_particulars_qm(frame,
	    component_particulars)
    Object frame, component_particulars;
{
    Object temp;

    x_note_fn_call(140,123);
    temp = get_entry_for_component_particulars(component_particulars,frame);
    temp = SECOND(temp);
    return bad_status_compiler_frame_notes_1_qm(CDR(temp));
}

/* COMPILE-GENERIC-SIMULATION-FORMULA */
Object compile_generic_simulation_formula(expression,focus_name,
	    left_side_of_formula,generic_simulation_formula,
	    compiling_initialization_form_qm)
    Object expression, focus_name, left_side_of_formula;
    Object generic_simulation_formula, compiling_initialization_form_qm;
{
    Object allow_in_line_designations_qm, current_computation_frame;
    Declare_special(2);
    Object result;

    x_note_fn_call(140,124);
    allow_in_line_designations_qm = T;
    current_computation_frame = generic_simulation_formula;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Allow_in_line_designations_qm,Qallow_in_line_designations_qm,allow_in_line_designations_qm,
	      0);
	if ( !TRUEP(compiling_initialization_form_qm))
	    Allow_in_line_designations_qm = Nil;
	result = compile_expression(expression,left_side_of_formula,
		gensym_cons_1(atomic_naming_element_of_role(focus_name),Nil));
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMPILE-GENERIC-FORMULA */
Object compile_generic_formula(expression,focus_name,attribute_name,
	    generic_formula)
    Object expression, focus_name, attribute_name, generic_formula;
{
    Object current_computation_frame, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(140,125);
    current_computation_frame = generic_formula;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      temp = phrase_list_3(Qthe,attribute_name,phrase_list_2(Qany,focus_name));
      result = compile_expression(expression,temp,
	      gensym_cons_1(atomic_naming_element_of_role(focus_name),Nil));
    POP_SPECIAL();
    return result;
}

void compile1_INIT()
{
    Object temp, reclaim_structure_for_expression_for_compilation_1;
    Object reclaim_structure_for_for_structure_1;
    Object reclaim_structure_for_reference_structure_1, temp_1;
    Object write_illegal_attribute_note_1;
    Object write_root_reference_role_name_same_as_previously_specified_local_name_note_1;
    Object write_explicitly_specified_local_name_refers_to_more_than_one_item_note_1;
    Object write_ambiguous_reference_note_1;
    Object write_role_and_kb_object_namespace_confusion_note_1;
    Object write_local_name_and_internal_type_namespace_confusion_note_1;
    Object write_illegal_reference_from_an_every_quantifier_note_1;
    Object write_illegal_quantifier_in_rule_consequent_note_1;
    Object write_illegal_reference_outside_action_note_1;
    Object write_illegal_reference_outside_create_action_note_1;
    Object write_too_many_delete_actions_note_1;
    Object write_illegal_reference_outside_not_note_1;
    Object write_illegal_reference_outside_expression_note_1;
    Object write_illegal_reference_outside_there_exists_note_1;
    Object write_illegal_reference_outside_sub_expression_of_expression_note_1;
    Object write_illegal_reference_outside_antecedent_clause_note_1;
    Object write_fatal_focus_error_note_1;
    Object write_focus_class_compilation_failed_note_1;
    Object write_illegal_quantifier_within_nth_element_role_note_1;
    Object write_circularity_in_nth_element_index_note_1;
    Object write_unknown_references_note_1;
    Object AB_package, list_constant_20, Qcompile1, list_constant_19;
    Object Qoperator, list_constant_18, Qframe_note_writer_1;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qfocus_class_compilation_failed, Qchange_icon_color;
    Object Qconclude_has_no_value, Qconclude_has_no_current_value;
    Object Qconclude_not, Qconclude, Qrotate, Qmove, Qdeactivate, Qfocus;
    Object Qillegal_reference_outside_antecedent_clause;
    Object Qillegal_reference_outside_sub_expression_of_expression;
    Object Qillegal_reference_outside_not, Qambiguous_reference;
    Object Qexplicitly_specified_local_name_refers_to_more_than_one_item;
    Object Qroot_reference_role_name_same_as_previously_specified_local_name;
    Object Qillegal_attribute, list_constant_17, string_constant_37, Kfuncall;
    Object list_constant_16, Qutilities3, Qcompilation_local_name_1;
    Object list_constant_15, string_constant_36, list_constant_14;
    Object string_constant_35, list_constant_13, string_constant_34;
    Object list_constant_12, string_constant_33, list_constant_11;
    Object string_constant_32, list_constant_10, string_constant_31;
    Object list_constant_9, string_constant_30, Qfunction_definition;
    Object Qdo_not_carry_global_property_value_into_kbs_qm, Qwhen_star;
    Object Qif_star, Qminimum, Qmaximum, Qproduct, Qsum, Qreference_structure;
    Object Qreclaim_structure, Qoutstanding_reference_structure_count;
    Object Qreference_structure_structure_memory_usage, Qutilities2;
    Object string_constant_29, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_28, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qfor_structure;
    Object Qoutstanding_for_structure_count;
    Object Qfor_structure_structure_memory_usage, string_constant_27;
    Object string_constant_26, Qexpression_for_compilation;
    Object Qoutstanding_expression_for_compilation_count;
    Object Qexpression_for_compilation_structure_memory_usage;
    Object string_constant_25, string_constant_24;

    x_note_fn_call(140,126);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct = 
	    STATIC_SYMBOL("EXPRESSION-FOR-COMPILATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qexpression_for_compilation = 
	    STATIC_SYMBOL("EXPRESSION-FOR-COMPILATION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_expression_for_compilation_g2_struct,
	    Qexpression_for_compilation,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qexpression_for_compilation,
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_expression_for_compilation == UNBOUND)
	The_type_description_of_expression_for_compilation = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8m83hAy1n83hAy8n8k1l8n0000000kpk0k0");
    temp = The_type_description_of_expression_for_compilation;
    The_type_description_of_expression_for_compilation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_24));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_expression_for_compilation_g2_struct,
	    The_type_description_of_expression_for_compilation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qexpression_for_compilation,
	    The_type_description_of_expression_for_compilation,
	    Qtype_description_of_type);
    Qoutstanding_expression_for_compilation_count = 
	    STATIC_SYMBOL("OUTSTANDING-EXPRESSION-FOR-COMPILATION-COUNT",
	    AB_package);
    Qexpression_for_compilation_structure_memory_usage = 
	    STATIC_SYMBOL("EXPRESSION-FOR-COMPILATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_25 = STATIC_STRING("1q83hAy8s83-TOy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_expression_for_compilation_count);
    push_optimized_constant(Qexpression_for_compilation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_25));
    Qchain_of_available_expression_for_compilations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EXPRESSION-FOR-COMPILATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_expression_for_compilations,
	    Chain_of_available_expression_for_compilations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_expression_for_compilations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qexpression_for_compilation_count = 
	    STATIC_SYMBOL("EXPRESSION-FOR-COMPILATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexpression_for_compilation_count,
	    Expression_for_compilation_count);
    record_system_variable(Qexpression_for_compilation_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_expression_for_compilations_vector == UNBOUND)
	Chain_of_available_expression_for_compilations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qexpression_for_compilation_structure_memory_usage,
	    STATIC_FUNCTION(expression_for_compilation_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_expression_for_compilation_count,
	    STATIC_FUNCTION(outstanding_expression_for_compilation_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_expression_for_compilation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_expression_for_compilation,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qexpression_for_compilation,
	    reclaim_structure_for_expression_for_compilation_1);
    Qg2_defstruct_structure_name_for_structure_g2_struct = 
	    STATIC_SYMBOL("FOR-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qfor_structure = STATIC_SYMBOL("FOR-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_for_structure_g2_struct,
	    Qfor_structure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qfor_structure,
	    Qg2_defstruct_structure_name_for_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_for_structure == UNBOUND)
	The_type_description_of_for_structure = Nil;
    string_constant_26 = 
	    STATIC_STRING("43Dy8m83hLy1n83hLy8n8k1l8n0000000kpk0k0");
    temp = The_type_description_of_for_structure;
    The_type_description_of_for_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_26));
    mutate_global_property(Qg2_defstruct_structure_name_for_structure_g2_struct,
	    The_type_description_of_for_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qfor_structure,
	    The_type_description_of_for_structure,Qtype_description_of_type);
    Qoutstanding_for_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-FOR-STRUCTURE-COUNT",AB_package);
    Qfor_structure_structure_memory_usage = 
	    STATIC_SYMBOL("FOR-STRUCTURE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_27 = STATIC_STRING("1q83hLy8s83-UXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_for_structure_count);
    push_optimized_constant(Qfor_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_27));
    Qchain_of_available_for_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FOR-STRUCTURES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_for_structures,
	    Chain_of_available_for_structures);
    record_system_variable(Qchain_of_available_for_structures,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qfor_structure_count = STATIC_SYMBOL("FOR-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfor_structure_count,For_structure_count);
    record_system_variable(Qfor_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_for_structures_vector == UNBOUND)
	Chain_of_available_for_structures_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qfor_structure_structure_memory_usage,
	    STATIC_FUNCTION(for_structure_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_for_structure_count,
	    STATIC_FUNCTION(outstanding_for_structure_count,NIL,FALSE,0,0));
    reclaim_structure_for_for_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_for_structure,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qfor_structure,
	    reclaim_structure_for_for_structure_1);
    Qg2_defstruct_structure_name_reference_structure_g2_struct = 
	    STATIC_SYMBOL("REFERENCE-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreference_structure = STATIC_SYMBOL("REFERENCE-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_reference_structure_g2_struct,
	    Qreference_structure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qreference_structure,
	    Qg2_defstruct_structure_name_reference_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_reference_structure == UNBOUND)
	The_type_description_of_reference_structure = Nil;
    string_constant_28 = 
	    STATIC_STRING("43Dy8m83m5y1n83m5y8n8k1l8n0000000kxk0k0");
    temp = The_type_description_of_reference_structure;
    The_type_description_of_reference_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_28));
    mutate_global_property(Qg2_defstruct_structure_name_reference_structure_g2_struct,
	    The_type_description_of_reference_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qreference_structure,
	    The_type_description_of_reference_structure,
	    Qtype_description_of_type);
    Qoutstanding_reference_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-REFERENCE-STRUCTURE-COUNT",AB_package);
    Qreference_structure_structure_memory_usage = 
	    STATIC_SYMBOL("REFERENCE-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_29 = STATIC_STRING("1q83m5y8s83-lPy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_reference_structure_count);
    push_optimized_constant(Qreference_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qchain_of_available_reference_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REFERENCE-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_reference_structures,
	    Chain_of_available_reference_structures);
    record_system_variable(Qchain_of_available_reference_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qreference_structure_count = STATIC_SYMBOL("REFERENCE-STRUCTURE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreference_structure_count,
	    Reference_structure_count);
    record_system_variable(Qreference_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_reference_structures_vector == UNBOUND)
	Chain_of_available_reference_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qreference_structure_structure_memory_usage,
	    STATIC_FUNCTION(reference_structure_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_reference_structure_count,
	    STATIC_FUNCTION(outstanding_reference_structure_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_reference_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_reference_structure,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qreference_structure,
	    reclaim_structure_for_reference_structure_1);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qany,Qevery,Qthe);
    Qgiver_of_value = STATIC_SYMBOL("GIVER-OF-VALUE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qany,Qevery);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    Qfor_every_literal = STATIC_SYMBOL("FOR-EVERY-LITERAL",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qthere_exists_literal,
	    Qfor_every_literal);
    Qsum = STATIC_SYMBOL("SUM",AB_package);
    Qproduct = STATIC_SYMBOL("PRODUCT",AB_package);
    Qmaximum = STATIC_SYMBOL("MAXIMUM",AB_package);
    Qminimum = STATIC_SYMBOL("MINIMUM",AB_package);
    Qaggregated_average = STATIC_SYMBOL("AGGREGATED-AVERAGE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)6L,Qsum,Qproduct,Qmaximum,
	    Qminimum,Qaggregated_average,Qcount);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)4L,Qand,Qab_or,Qnot,Qwhen);
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    Qif_star = STATIC_SYMBOL("IF*",AB_package);
    Qwhen_star = STATIC_SYMBOL("WHEN*",AB_package);
    Qif_expression = STATIC_SYMBOL("IF-EXPRESSION",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)5L,Qab_if,Qwhen,Qif_star,
	    Qwhen_star,Qif_expression);
    Qfunction_definition = STATIC_SYMBOL("FUNCTION-DEFINITION",AB_package);
    Kb_specific_property_names = CONS(Qfunction_definition,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qfunction_definition,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Function_definition_kbprop = Qfunction_definition;
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qfocus_range = STATIC_SYMBOL("FOCUS-RANGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfocus_range,Focus_range);
    Qcompile1 = STATIC_SYMBOL("COMPILE1",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    string_constant_30 = STATIC_STRING("focus");
    list_constant_9 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_30);
    record_system_variable(Qfocus_range,Qcompile1,list_constant_9,Qnil,
	    Qnil,Qnil,Qnil);
    Qneeded_domain = STATIC_SYMBOL("NEEDED-DOMAIN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qneeded_domain,Needed_domain);
    string_constant_31 = STATIC_STRING("needed");
    list_constant_10 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_31);
    record_system_variable(Qneeded_domain,Qcompile1,list_constant_10,Qnil,
	    Qnil,Qnil,Qnil);
    Qglobal_domain = STATIC_SYMBOL("GLOBAL-DOMAIN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qglobal_domain,Global_domain);
    string_constant_32 = STATIC_STRING("global");
    list_constant_11 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_32);
    record_system_variable(Qglobal_domain,Qcompile1,list_constant_11,Qnil,
	    Qnil,Qnil,Qnil);
    Qexpression_list_indicator = STATIC_SYMBOL("EXPRESSION-LIST-INDICATOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexpression_list_indicator,
	    Expression_list_indicator);
    string_constant_33 = STATIC_STRING("expression-list");
    list_constant_12 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_33);
    record_system_variable(Qexpression_list_indicator,Qcompile1,
	    list_constant_12,Qnil,Qnil,Qnil,Qnil);
    Qcolor_change_indicator = STATIC_SYMBOL("COLOR-CHANGE-INDICATOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolor_change_indicator,Color_change_indicator);
    string_constant_34 = STATIC_STRING("color-change");
    list_constant_13 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_34);
    record_system_variable(Qcolor_change_indicator,Qcompile1,
	    list_constant_13,Qnil,Qnil,Qnil,Qnil);
    Qcolor_changes_indicator = STATIC_SYMBOL("COLOR-CHANGES-INDICATOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolor_changes_indicator,
	    Color_changes_indicator);
    string_constant_35 = STATIC_STRING("color-changes");
    list_constant_14 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_35);
    record_system_variable(Qcolor_changes_indicator,Qcompile1,
	    list_constant_14,Qnil,Qnil,Qnil,Qnil);
    Qnil_indicator = STATIC_SYMBOL("NIL-INDICATOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnil_indicator,Nil_indicator);
    string_constant_36 = STATIC_STRING("nil-indicator");
    list_constant_15 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_36);
    record_system_variable(Qnil_indicator,Qcompile1,list_constant_15,Qnil,
	    Qnil,Qnil,Qnil);
    Qlocal_names_not_associated_with_roles = 
	    STATIC_SYMBOL("LOCAL-NAMES-NOT-ASSOCIATED-WITH-ROLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocal_names_not_associated_with_roles,
	    Local_names_not_associated_with_roles);
    record_system_variable(Qlocal_names_not_associated_with_roles,
	    Qcompile1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qcompilation_local_name_symbol_supply = 
	    STATIC_SYMBOL("COMPILATION-LOCAL-NAME-SYMBOL-SUPPLY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompilation_local_name_symbol_supply,
	    Compilation_local_name_symbol_supply);
    Qutilities3 = STATIC_SYMBOL("UTILITIES3",AB_package);
    Qcompilation_local_name_1 = STATIC_SYMBOL("COMPILATION-LOCAL-NAME-1",
	    AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Kfuncall,Qlist,
	    Qcompilation_local_name_1);
    record_system_variable(Qcompilation_local_name_symbol_supply,
	    Qutilities3,list_constant_16,Qnil,Qt,Qnil,Qnil);
    Qcompilation_local_name_symbol_counter = 
	    STATIC_SYMBOL("COMPILATION-LOCAL-NAME-SYMBOL-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompilation_local_name_symbol_counter,
	    Compilation_local_name_symbol_counter);
    string_constant = STATIC_STRING("COMPILATION-LOCAL-NAME");
    Qbad_rule = STATIC_SYMBOL("BAD-RULE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbad_rule,Bad_rule);
    string_constant_37 = STATIC_STRING("bad-rule");
    list_constant_17 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_37);
    record_system_variable(Qbad_rule,Qcompile1,list_constant_17,Qnil,Qnil,
	    Qnil,Qnil);
    Qfocus_too_narrow_qm = STATIC_SYMBOL("FOCUS-TOO-NARROW\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfocus_too_narrow_qm,Focus_too_narrow_qm);
    record_system_variable(Qfocus_too_narrow_qm,Qcompile1,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qfatal_focus_error_info_qm = STATIC_SYMBOL("FATAL-FOCUS-ERROR-INFO\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfatal_focus_error_info_qm,
	    Fatal_focus_error_info_qm);
    record_system_variable(Qfatal_focus_error_info_qm,Qcompile1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qfatal_focus_error_info_for_all_compilations = 
	    STATIC_SYMBOL("FATAL-FOCUS-ERROR-INFO-FOR-ALL-COMPILATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfatal_focus_error_info_for_all_compilations,
	    Fatal_focus_error_info_for_all_compilations);
    record_system_variable(Qfatal_focus_error_info_for_all_compilations,
	    Qcompile1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qfocus_local_name_for_rule_compilation_qm = 
	    STATIC_SYMBOL("FOCUS-LOCAL-NAME-FOR-RULE-COMPILATION\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfocus_local_name_for_rule_compilation_qm,
	    Focus_local_name_for_rule_compilation_qm);
    record_system_variable(Qfocus_local_name_for_rule_compilation_qm,
	    Qcompile1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcompiling_antecedent_p = STATIC_SYMBOL("COMPILING-ANTECEDENT-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiling_antecedent_p,Compiling_antecedent_p);
    record_system_variable(Qcompiling_antecedent_p,Qcompile1,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qinside_action_iteration_p = STATIC_SYMBOL("INSIDE-ACTION-ITERATION-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinside_action_iteration_p,
	    Inside_action_iteration_p);
    record_system_variable(Qinside_action_iteration_p,Qcompile1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qpattern_checking_inverse_references = 
	    STATIC_SYMBOL("PATTERN-CHECKING-INVERSE-REFERENCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpattern_checking_inverse_references,
	    Pattern_checking_inverse_references);
    record_system_variable(Qpattern_checking_inverse_references,Qcompile1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qwrapper_references_for_left_side_of_formula_qm = 
	    STATIC_SYMBOL("WRAPPER-REFERENCES-FOR-LEFT-SIDE-OF-FORMULA\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwrapper_references_for_left_side_of_formula_qm,
	    Wrapper_references_for_left_side_of_formula_qm);
    record_system_variable(Qwrapper_references_for_left_side_of_formula_qm,
	    Qcompile1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qdesignations_from_explicit_iteration_forms = 
	    STATIC_SYMBOL("DESIGNATIONS-FROM-EXPLICIT-ITERATION-FORMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesignations_from_explicit_iteration_forms,
	    Designations_from_explicit_iteration_forms);
    record_system_variable(Qdesignations_from_explicit_iteration_forms,
	    Qcompile1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qsource_designations_from_explicit_iteration_forms = 
	    STATIC_SYMBOL("SOURCE-DESIGNATIONS-FROM-EXPLICIT-ITERATION-FORMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsource_designations_from_explicit_iteration_forms,
	    Source_designations_from_explicit_iteration_forms);
    record_system_variable(Qsource_designations_from_explicit_iteration_forms,
	    Qcompile1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcompiling_rule_p = STATIC_SYMBOL("COMPILING-RULE-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiling_rule_p,Compiling_rule_p);
    record_system_variable(Qcompiling_rule_p,Qcompile1,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qcompiling_expression_p = STATIC_SYMBOL("COMPILING-EXPRESSION-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiling_expression_p,Compiling_expression_p);
    record_system_variable(Qcompiling_expression_p,Qcompile1,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    if (Assignment_section_forms == UNBOUND)
	Assignment_section_forms = Nil;
    if (Post_compiler_warning_note_qm == UNBOUND)
	Post_compiler_warning_note_qm = T;
    Qallow_in_line_designations_qm = 
	    STATIC_SYMBOL("ALLOW-IN-LINE-DESIGNATIONS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qallow_in_line_designations_qm,
	    Allow_in_line_designations_qm);
    record_system_variable(Qallow_in_line_designations_qm,Qcompile1,T,Qnil,
	    Qnil,Qnil,Qnil);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Quniversal_compilation = STATIC_SYMBOL("UNIVERSAL-COMPILATION",AB_package);
    Qcompile2_action = STATIC_SYMBOL("COMPILE2-ACTION",AB_package);
    Qfor = STATIC_SYMBOL("FOR",AB_package);
    if (List_of_compiler_frame_note_types == UNBOUND)
	List_of_compiler_frame_note_types = Nil;
    if (List_of_bad_status_compiler_frame_note_types == UNBOUND)
	List_of_bad_status_compiler_frame_note_types = Nil;
    Qillegal_attribute = STATIC_SYMBOL("ILLEGAL-ATTRIBUTE",AB_package);
    temp_1 = adjoin(2,Qillegal_attribute,List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_attribute,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    string_constant_1 = 
	    STATIC_STRING(" is a G2 internal attribute which may not be referenced directly ");
    string_constant_2 = 
	    STATIC_STRING(" are G2 internal attributes which may not be referenced directly ");
    string_constant_3 = STATIC_STRING(", ");
    string_constant_4 = STATIC_STRING(", and ");
    string_constant_5 = STATIC_STRING(" and ");
    write_illegal_attribute_note_1 = 
	    STATIC_FUNCTION(write_illegal_attribute_note,NIL,FALSE,2,2);
    mutate_global_property(Qillegal_attribute,
	    write_illegal_attribute_note_1,Qframe_note_writer_1);
    Qroot_reference_role_name_same_as_previously_specified_local_name = 
	    STATIC_SYMBOL("ROOT-REFERENCE-ROLE-NAME-SAME-AS-PREVIOUSLY-SPECIFIED-LOCAL-NAME",
	    AB_package);
    temp_1 = adjoin(2,
	    Qroot_reference_role_name_same_as_previously_specified_local_name,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,
	    Qroot_reference_role_name_same_as_previously_specified_local_name,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_1 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)57344L);
    write_root_reference_role_name_same_as_previously_specified_local_name_note_1 
	    = 
	    STATIC_FUNCTION(write_root_reference_role_name_same_as_previously_specified_local_name_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qroot_reference_role_name_same_as_previously_specified_local_name,
	    write_root_reference_role_name_same_as_previously_specified_local_name_note_1,
	    Qframe_note_writer_1);
    Qexplicitly_specified_local_name_refers_to_more_than_one_item = 
	    STATIC_SYMBOL("EXPLICITLY-SPECIFIED-LOCAL-NAME-REFERS-TO-MORE-THAN-ONE-ITEM",
	    AB_package);
    temp_1 = adjoin(2,
	    Qexplicitly_specified_local_name_refers_to_more_than_one_item,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,
	    Qexplicitly_specified_local_name_refers_to_more_than_one_item,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    string_constant_6 = STATIC_STRING(" refers to more than one runtime item");
    string_constant_7 = STATIC_STRING(" refer to more than one runtime item");
    write_explicitly_specified_local_name_refers_to_more_than_one_item_note_1 
	    = 
	    STATIC_FUNCTION(write_explicitly_specified_local_name_refers_to_more_than_one_item_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qexplicitly_specified_local_name_refers_to_more_than_one_item,
	    write_explicitly_specified_local_name_refers_to_more_than_one_item_note_1,
	    Qframe_note_writer_1);
    Qambiguous_reference = STATIC_SYMBOL("AMBIGUOUS-REFERENCE",AB_package);
    temp_1 = adjoin(2,Qambiguous_reference,List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qambiguous_reference,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_3 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING("them ");
    string_constant_9 = STATIC_STRING("it ");
    array_constant_5 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)96L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)36L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)42L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)45L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)46L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)47L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)48L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)49L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)50L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)51L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)52L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)53L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)55L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)56L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)57L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)58L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)59L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)60L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)61L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)62L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)63L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)64L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)65L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)66L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)67L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)68L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)69L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)70L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)71L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)72L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)73L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)74L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)75L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)76L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)77L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)78L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)79L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)80L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)81L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)94L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)95L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)57344L);
    write_ambiguous_reference_note_1 = 
	    STATIC_FUNCTION(write_ambiguous_reference_note,NIL,FALSE,2,2);
    mutate_global_property(Qambiguous_reference,
	    write_ambiguous_reference_note_1,Qframe_note_writer_1);
    Qrole_and_kb_object_namespace_confusion = 
	    STATIC_SYMBOL("ROLE-AND-KB-OBJECT-NAMESPACE-CONFUSION",AB_package);
    temp_1 = adjoin(2,Qrole_and_kb_object_namespace_confusion,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qrole_and_kb_object_namespace_confusion,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_8 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    string_constant_10 = 
	    STATIC_STRING(" is used to name both a role and a kb object");
    string_constant_11 = 
	    STATIC_STRING(" are used to name both roles and kb objects");
    array_constant_9 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)39L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)41L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)57344L);
    write_role_and_kb_object_namespace_confusion_note_1 = 
	    STATIC_FUNCTION(write_role_and_kb_object_namespace_confusion_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qrole_and_kb_object_namespace_confusion,
	    write_role_and_kb_object_namespace_confusion_note_1,
	    Qframe_note_writer_1);
    Qlocal_name_and_internal_type_namespace_confusion = 
	    STATIC_SYMBOL("LOCAL-NAME-AND-INTERNAL-TYPE-NAMESPACE-CONFUSION",
	    AB_package);
    temp_1 = adjoin(2,Qlocal_name_and_internal_type_namespace_confusion,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qlocal_name_and_internal_type_namespace_confusion,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    string_constant_12 = 
	    STATIC_STRING(" is used to name a role, but is a reserved word");
    string_constant_13 = 
	    STATIC_STRING(" are used to name roles, but are reserved words");
    array_constant_10 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    write_local_name_and_internal_type_namespace_confusion_note_1 = 
	    STATIC_FUNCTION(write_local_name_and_internal_type_namespace_confusion_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qlocal_name_and_internal_type_namespace_confusion,
	    write_local_name_and_internal_type_namespace_confusion_note_1,
	    Qframe_note_writer_1);
    Qillegal_reference_from_an_every_quantifier = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-FROM-AN-EVERY-QUANTIFIER",
	    AB_package);
    temp_1 = adjoin(2,Qillegal_reference_from_an_every_quantifier,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_reference_from_an_every_quantifier,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_11 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)112L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)40L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)42L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)44L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)45L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)49L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)50L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)51L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)52L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)54L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)57L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)58L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)59L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)60L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)61L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)62L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)63L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)64L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)65L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)66L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)67L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)68L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)69L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)70L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)71L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)72L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)73L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)74L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)75L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)76L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)77L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)78L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)79L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)80L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)81L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)82L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)83L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)84L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)85L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)86L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)87L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)88L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)89L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)90L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)91L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)92L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)93L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)94L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)95L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)96L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)97L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)98L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)99L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)100L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)110L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)111L,(SI_Long)57344L);
    write_illegal_reference_from_an_every_quantifier_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_from_an_every_quantifier_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_reference_from_an_every_quantifier,
	    write_illegal_reference_from_an_every_quantifier_note_1,
	    Qframe_note_writer_1);
    Qillegal_quantifier_in_rule_consequent = 
	    STATIC_SYMBOL("ILLEGAL-QUANTIFIER-IN-RULE-CONSEQUENT",AB_package);
    temp_1 = adjoin(2,Qillegal_quantifier_in_rule_consequent,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_quantifier_in_rule_consequent,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_12 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)32L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)34L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)36L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)39L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)40L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)43L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)46L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)47L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)48L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)49L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)50L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)52L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)53L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)55L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)56L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)57L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)58L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)59L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)60L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)61L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)62L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)63L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)64L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)65L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)66L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)78L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)79L,(SI_Long)57344L);
    write_illegal_quantifier_in_rule_consequent_note_1 = 
	    STATIC_FUNCTION(write_illegal_quantifier_in_rule_consequent_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_quantifier_in_rule_consequent,
	    write_illegal_quantifier_in_rule_consequent_note_1,
	    Qframe_note_writer_1);
    Qillegal_reference_outside_action = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-OUTSIDE-ACTION",AB_package);
    temp_1 = adjoin(2,Qillegal_reference_outside_action,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_reference_outside_action,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_13 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)35L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)40L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)41L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)42L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)43L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)45L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)46L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)47L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)49L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)50L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)51L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)52L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)54L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)55L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)56L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)57L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)58L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)59L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)60L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)61L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)62L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)63L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)64L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)65L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)66L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)67L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)68L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)69L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)70L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)71L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)72L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)73L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)78L,(SI_Long)74L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)79L,(SI_Long)57344L);
    write_illegal_reference_outside_action_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_outside_action_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_reference_outside_action,
	    write_illegal_reference_outside_action_note_1,
	    Qframe_note_writer_1);
    Qillegal_reference_outside_create_action = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-OUTSIDE-CREATE-ACTION",
	    AB_package);
    temp_1 = adjoin(2,Qillegal_reference_outside_create_action,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_reference_outside_create_action,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_14 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)112L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)36L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)38L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)39L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)42L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)45L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)46L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)47L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)49L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)50L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)51L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)52L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)54L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)55L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)56L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)57L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)58L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)59L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)60L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)61L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)62L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)63L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)64L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)65L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)66L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)67L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)68L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)69L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)70L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)71L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)72L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)73L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)74L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)75L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)76L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)77L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)78L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)79L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)80L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)81L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)82L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)83L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)84L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)85L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)86L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)87L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)88L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)89L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)90L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)91L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)92L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)93L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)94L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)95L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)96L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)97L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)98L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)99L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)100L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)101L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)102L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)103L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)110L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)111L,(SI_Long)57344L);
    write_illegal_reference_outside_create_action_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_outside_create_action_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_reference_outside_create_action,
	    write_illegal_reference_outside_create_action_note_1,
	    Qframe_note_writer_1);
    Qtoo_many_delete_actions = STATIC_SYMBOL("TOO-MANY-DELETE-ACTIONS",
	    AB_package);
    temp_1 = adjoin(2,Qtoo_many_delete_actions,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qtoo_many_delete_actions,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_15 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)30L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)32L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)35L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)37L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)38L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)41L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)42L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)43L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)45L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)46L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)47L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)49L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)50L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)51L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)52L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)53L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)54L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)55L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)56L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)57L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)58L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)59L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)60L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)61L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)62L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)63L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)64L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)78L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)79L,(SI_Long)57344L);
    write_too_many_delete_actions_note_1 = 
	    STATIC_FUNCTION(write_too_many_delete_actions_note,NIL,FALSE,2,2);
    mutate_global_property(Qtoo_many_delete_actions,
	    write_too_many_delete_actions_note_1,Qframe_note_writer_1);
    Qillegal_reference_outside_not = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-OUTSIDE-NOT",AB_package);
    temp_1 = adjoin(2,Qillegal_reference_outside_not,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_reference_outside_not,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_16 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)96L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)27L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)28L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)37L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)39L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)42L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)43L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)46L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)47L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)48L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)49L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)50L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)51L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)52L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)54L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)56L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)57L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)58L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)59L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)60L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)61L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)62L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)63L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)64L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)65L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)66L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)67L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)68L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)69L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)70L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)71L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)72L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)73L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)74L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)75L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)76L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)77L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)94L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)95L,(SI_Long)57344L);
    write_illegal_reference_outside_not_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_outside_not_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qillegal_reference_outside_not,
	    write_illegal_reference_outside_not_note_1,Qframe_note_writer_1);
    Qillegal_reference_outside_expression = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-OUTSIDE-EXPRESSION",AB_package);
    temp_1 = adjoin(2,Qillegal_reference_outside_expression,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_reference_outside_expression,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    Qa = STATIC_SYMBOL("A",AB_package);
    Qquantifier = STATIC_SYMBOL("QUANTIFIER",AB_package);
    Qaggregator = STATIC_SYMBOL("AGGREGATOR",AB_package);
    Qthere_exists = STATIC_SYMBOL("THERE-EXISTS",AB_package);
    Qfor_every = STATIC_SYMBOL("FOR-EVERY",AB_package);
    Qaverage = STATIC_SYMBOL("AVERAGE",AB_package);
    Qan = STATIC_SYMBOL("AN",AB_package);
    array_constant_17 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)25L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)43L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)46L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)47L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)50L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)51L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)52L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)53L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)55L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)56L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)57L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)58L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)59L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)62L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)63L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)22L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)25L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)43L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)46L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)47L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)50L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)51L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)52L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)53L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)54L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)55L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)56L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)57L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)58L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)59L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)62L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)63L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)22L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)25L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)43L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)46L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)47L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)50L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)51L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)52L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)53L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)54L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)55L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)56L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)57L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)58L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)59L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)62L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)63L,(SI_Long)57344L);
    write_illegal_reference_outside_expression_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_outside_expression_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_reference_outside_expression,
	    write_illegal_reference_outside_expression_note_1,
	    Qframe_note_writer_1);
    Qillegal_reference_outside_there_exists = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-OUTSIDE-THERE-EXISTS",AB_package);
    temp_1 = adjoin(2,Qillegal_reference_outside_there_exists,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_reference_outside_there_exists,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_22 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)128L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)21L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)26L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)29L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)33L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)34L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)35L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)37L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)39L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)43L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)44L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)48L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)49L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)50L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)51L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)52L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)53L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)54L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)55L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)56L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)57L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)58L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)59L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)60L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)61L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)62L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)63L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)64L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)65L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)66L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)67L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)68L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)69L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)70L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)71L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)72L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)73L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)74L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)75L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)76L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)77L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)78L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)79L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)80L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)81L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)82L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)83L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)84L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)85L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)86L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)87L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)88L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)89L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)90L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)91L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)92L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)93L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)94L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)95L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)96L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)97L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)98L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)99L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)100L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)101L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)102L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)103L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)104L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)105L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)106L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)107L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)108L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)109L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)110L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)111L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)112L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)113L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)114L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)115L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)116L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)117L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)118L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)119L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)126L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)127L,(SI_Long)57344L);
    write_illegal_reference_outside_there_exists_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_outside_there_exists_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_reference_outside_there_exists,
	    write_illegal_reference_outside_there_exists_note_1,
	    Qframe_note_writer_1);
    Qillegal_reference_outside_sub_expression_of_expression = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-OUTSIDE-SUB-EXPRESSION-OF-EXPRESSION",
	    AB_package);
    temp_1 = adjoin(2,
	    Qillegal_reference_outside_sub_expression_of_expression,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,
	    Qillegal_reference_outside_sub_expression_of_expression,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_23 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)25L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)26L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)37L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)40L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)47L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)22L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)25L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)43L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)46L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)47L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)50L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)51L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)52L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)53L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)54L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)55L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)56L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)57L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)58L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)59L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)60L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)61L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)62L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)63L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)78L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)79L,(SI_Long)57344L);
    write_illegal_reference_outside_sub_expression_of_expression_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_outside_sub_expression_of_expression_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_reference_outside_sub_expression_of_expression,
	    write_illegal_reference_outside_sub_expression_of_expression_note_1,
	    Qframe_note_writer_1);
    Qillegal_reference_outside_antecedent_clause = 
	    STATIC_SYMBOL("ILLEGAL-REFERENCE-OUTSIDE-ANTECEDENT-CLAUSE",
	    AB_package);
    temp_1 = adjoin(2,Qillegal_reference_outside_antecedent_clause,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_reference_outside_antecedent_clause,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    write_illegal_reference_outside_antecedent_clause_note_1 = 
	    STATIC_FUNCTION(write_illegal_reference_outside_antecedent_clause_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_reference_outside_antecedent_clause,
	    write_illegal_reference_outside_antecedent_clause_note_1,
	    Qframe_note_writer_1);
    Qfatal_focus_error = STATIC_SYMBOL("FATAL-FOCUS-ERROR",AB_package);
    temp_1 = adjoin(2,Qfatal_focus_error,List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qfatal_focus_error,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_25 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)25L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)31L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)32L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)33L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)35L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)39L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)57344L);
    write_fatal_focus_error_note_1 = 
	    STATIC_FUNCTION(write_fatal_focus_error_note,NIL,FALSE,2,2);
    mutate_global_property(Qfatal_focus_error,
	    write_fatal_focus_error_note_1,Qframe_note_writer_1);
    array_constant_28 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)57344L);
    Qfocus = STATIC_SYMBOL("FOCUS",AB_package);
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    Qrotate = STATIC_SYMBOL("ROTATE",AB_package);
    Qcreate = STATIC_SYMBOL("CREATE",AB_package);
    Qcreate_explanation = STATIC_SYMBOL("CREATE-EXPLANATION",AB_package);
    Qcreate_connection = STATIC_SYMBOL("CREATE-CONNECTION",AB_package);
    Qcreate_by_cloning = STATIC_SYMBOL("CREATE-BY-CLONING",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)11L,Qbreak,Qfocus,Qdeactivate,
	    Qset,Qmove,Qrotate,Qcreate,Qdelete,Qcreate_explanation,
	    Qcreate_connection,Qcreate_by_cloning);
    array_constant_29 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qconclude_not = STATIC_SYMBOL("CONCLUDE-NOT",AB_package);
    Qconclude_has_no_current_value = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-CURRENT-VALUE",AB_package);
    Qconclude_has_no_value = STATIC_SYMBOL("CONCLUDE-HAS-NO-VALUE",AB_package);
    Qchange_icon_color = STATIC_SYMBOL("CHANGE-ICON-COLOR",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)5L,Qconclude,Qconclude_not,
	    Qconclude_has_no_current_value,Qconclude_has_no_value,
	    Qchange_icon_color);
    array_constant_31 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)23L,(SI_Long)57344L);
    array_constant_32 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)23L,(SI_Long)57344L);
    Qinvoke = STATIC_SYMBOL("INVOKE",AB_package);
    Qinform = STATIC_SYMBOL("INFORM",AB_package);
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    array_constant_33 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)57344L);
    Qset_position = STATIC_SYMBOL("SET-POSITION",AB_package);
    array_constant_34 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)23L,(SI_Long)57344L);
    Qset_heading = STATIC_SYMBOL("SET-HEADING",AB_package);
    array_constant_35 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)23L,(SI_Long)57344L);
    Qnon_invertible_role = STATIC_SYMBOL("NON-INVERTIBLE-ROLE",AB_package);
    array_constant_36 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)57344L);
    array_constant_37 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)20L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)30L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)39L,(SI_Long)57344L);
    array_constant_38 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)57344L);
    Qfocus_class_compilation_failed = 
	    STATIC_SYMBOL("FOCUS-CLASS-COMPILATION-FAILED",AB_package);
    temp_1 = adjoin(2,Qfocus_class_compilation_failed,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qfocus_class_compilation_failed,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    string_constant_14 = STATIC_STRING("the focal class~a ");
    string_constant_15 = STATIC_STRING("es");
    string_constant_16 = STATIC_STRING("");
    string_constant_17 = STATIC_STRING("and");
    string_constant_18 = 
	    STATIC_STRING(" could not be compiled, since ~a not mentioned in the rule");
    string_constant_19 = STATIC_STRING("they are");
    string_constant_20 = STATIC_STRING("it is");
    write_focus_class_compilation_failed_note_1 = 
	    STATIC_FUNCTION(write_focus_class_compilation_failed_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qfocus_class_compilation_failed,
	    write_focus_class_compilation_failed_note_1,Qframe_note_writer_1);
    Qillegal_quantifier_within_nth_element_role = 
	    STATIC_SYMBOL("ILLEGAL-QUANTIFIER-WITHIN-NTH-ELEMENT-ROLE",
	    AB_package);
    temp_1 = adjoin(2,Qillegal_quantifier_within_nth_element_role,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qillegal_quantifier_within_nth_element_role,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    array_constant_39 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)15L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)18L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)19L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)29L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)30L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)39L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)40L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)42L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)46L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)47L,(SI_Long)57344L);
    array_constant_40 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)13L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)17L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)28L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)30L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)39L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)40L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)44L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)45L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)46L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)47L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)48L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)49L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)50L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)51L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)52L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)53L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)56L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)57L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)58L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)59L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)60L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)61L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)62L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)63L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)64L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)65L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)66L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)78L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)79L,(SI_Long)57344L);
    write_illegal_quantifier_within_nth_element_role_note_1 = 
	    STATIC_FUNCTION(write_illegal_quantifier_within_nth_element_role_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qillegal_quantifier_within_nth_element_role,
	    write_illegal_quantifier_within_nth_element_role_note_1,
	    Qframe_note_writer_1);
    Qcircularity_in_nth_element_index = 
	    STATIC_SYMBOL("CIRCULARITY-IN-NTH-ELEMENT-INDEX",AB_package);
    temp_1 = adjoin(2,Qcircularity_in_nth_element_index,
	    List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qcircularity_in_nth_element_index,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    string_constant_21 = 
	    STATIC_STRING("the reference to \"~a\" in the expression \" ");
    array_constant_41 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)13L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)17L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)28L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)30L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)39L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)40L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)43L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)46L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)47L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)48L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)51L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)52L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)53L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)62L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)63L,(SI_Long)57344L);
    array_constant_42 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)18L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)31L,(SI_Long)57344L);
    write_circularity_in_nth_element_index_note_1 = 
	    STATIC_FUNCTION(write_circularity_in_nth_element_index_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qcircularity_in_nth_element_index,
	    write_circularity_in_nth_element_index_note_1,
	    Qframe_note_writer_1);
    Qunknown_references = STATIC_SYMBOL("UNKNOWN-REFERENCES",AB_package);
    temp_1 = adjoin(2,Qunknown_references,List_of_compiler_frame_note_types);
    List_of_compiler_frame_note_types = temp_1;
    temp_1 = adjoin(2,Qunknown_references,
	    List_of_bad_status_compiler_frame_note_types);
    List_of_bad_status_compiler_frame_note_types = temp_1;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_43 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)19L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)27L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)31L,(SI_Long)57344L);
    array_constant_44 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)19L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)24L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)39L,(SI_Long)57344L);
    array_constant_45 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_VALUE_LOCATION(Qunknown_references,Unknown_references);
    write_unknown_references_note_1 = 
	    STATIC_FUNCTION(write_unknown_references_note,NIL,FALSE,2,2);
    mutate_global_property(Qunknown_references,
	    write_unknown_references_note_1,Qframe_note_writer_1);
    array_constant_46 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)23L,(SI_Long)57344L);
    string_constant_22 = STATIC_STRING(" is unknown");
    string_constant_23 = STATIC_STRING(" are unknown");
    Qspecial_globally_known_references = 
	    STATIC_SYMBOL("SPECIAL-GLOBALLY-KNOWN-REFERENCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qspecial_globally_known_references,
	    Special_globally_known_references);
    Qoperator = STATIC_SYMBOL("OPERATOR",AB_package);
    list_constant_19 = STATIC_CONS(Qoperator,Qnil);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_19);
    record_system_variable(Qspecial_globally_known_references,Qcompile1,
	    list_constant_20,Qnil,Qnil,Qnil,Qnil);
    Qreference_to_item_or_datum_qm = 
	    STATIC_SYMBOL("REFERENCE-TO-ITEM-OR-DATUM\?",AB_package);
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qreference_to_item_or_datum_qm,
	    STATIC_FUNCTION(reference_to_item_or_datum_qm,NIL,FALSE,1,1));
    Qillegal_quantifier_within_nth_element_role_1 = 
	    STATIC_SYMBOL("ILLEGAL-QUANTIFIER-WITHIN-NTH-ELEMENT-ROLE-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qillegal_quantifier_within_nth_element_role_1,
	    STATIC_FUNCTION(illegal_quantifier_within_nth_element_role_1,
	    NIL,FALSE,1,1));
    Qillegal_any_quantifier_in_tree_qm = 
	    STATIC_SYMBOL("ILLEGAL-ANY-QUANTIFIER-IN-TREE\?",AB_package);
    SET_SYMBOL_FUNCTION(Qillegal_any_quantifier_in_tree_qm,
	    STATIC_FUNCTION(illegal_any_quantifier_in_tree_qm,NIL,FALSE,1,1));
    Qsimultaneously = STATIC_SYMBOL("SIMULTANEOUSLY",AB_package);
    Qillegal_every_quantifier_in_reference_tree_qm = 
	    STATIC_SYMBOL("ILLEGAL-EVERY-QUANTIFIER-IN-REFERENCE-TREE\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qillegal_every_quantifier_in_reference_tree_qm,
	    STATIC_FUNCTION(illegal_every_quantifier_in_reference_tree_qm,
	    NIL,FALSE,1,1));
    Qcall_assignment_action = STATIC_SYMBOL("CALL-ASSIGNMENT-ACTION",
	    AB_package);
    Qcompiler_errors = STATIC_SYMBOL("COMPILER-ERRORS",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qunknown_references,
	    Qfatal_focus_error);
}
