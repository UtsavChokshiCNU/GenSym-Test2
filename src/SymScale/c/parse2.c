/* parse2.c
 * Input file:  parse2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "parse2.h"


Object Cache_of_regular_expressions = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_state_stack, Qcurrent_state_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Current_token_stack, Qcurrent_token_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Current_input_stack, Qcurrent_input_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Current_lr_states, Qcurrent_lr_states);

DEFINE_VARIABLE_WITH_SYMBOL(Current_nonterminals, Qcurrent_nonterminals);

DEFINE_VARIABLE_WITH_SYMBOL(Current_parse_table, Qcurrent_parse_table);

DEFINE_VARIABLE_WITH_SYMBOL(Current_productions, Qcurrent_productions);

DEFINE_VARIABLE_WITH_SYMBOL(Current_terminals, Qcurrent_terminals);

DEFINE_VARIABLE_WITH_SYMBOL(Lr0_follow, Qlr0_follow);

DEFINE_VARIABLE_WITH_SYMBOL(Preprocessor_errors_qm, Qpreprocessor_errors_qm);

Object The_type_description_of_production = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_productions, Qchain_of_available_productions);

DEFINE_VARIABLE_WITH_SYMBOL(Production_count, Qproduction_count);

Object Chain_of_available_productions_vector = UNBOUND;

/* PRODUCTION-STRUCTURE-MEMORY-USAGE */
Object production_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,0);
    temp = Production_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PRODUCTION-COUNT */
Object outstanding_production_count()
{
    Object def_structure_production_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,1);
    gensymed_symbol = IFIX(Production_count);
    def_structure_production_variable = Chain_of_available_productions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_production_variable))
	goto end_loop;
    def_structure_production_variable = 
	    ISVREF(def_structure_production_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PRODUCTION-1 */
Object reclaim_production_1(production)
    Object production;
{
    Object temp, svref_arg_2;

    x_note_fn_call(78,2);
    inline_note_reclaim_cons(production,Nil);
    temp = ISVREF(Chain_of_available_productions_vector,
	    IFIX(Current_thread_index));
    SVREF(production,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_productions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = production;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PRODUCTION */
Object reclaim_structure_for_production(production)
    Object production;
{
    x_note_fn_call(78,3);
    return reclaim_production_1(production);
}

static Object Qg2_defstruct_structure_name_production_g2_struct;  /* g2-defstruct-structure-name::production-g2-struct */

/* MAKE-PERMANENT-PRODUCTION-STRUCTURE-INTERNAL */
Object make_permanent_production_structure_internal()
{
    Object def_structure_production_variable, defstruct_g2_production_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,4);
    def_structure_production_variable = Nil;
    atomic_incff_symval(Qproduction_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_production_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_production_variable = the_array;
	SVREF(defstruct_g2_production_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_production_g2_struct;
	def_structure_production_variable = defstruct_g2_production_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_production_variable);
}

/* MAKE-PRODUCTION-1 */
Object make_production_1()
{
    Object def_structure_production_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(78,5);
    def_structure_production_variable = 
	    ISVREF(Chain_of_available_productions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_production_variable) {
	svref_arg_1 = Chain_of_available_productions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_production_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_production_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_production_g2_struct;
    }
    else
	def_structure_production_variable = 
		make_permanent_production_structure_internal();
    inline_note_allocate_cons(def_structure_production_variable,Nil);
    return VALUES_1(def_structure_production_variable);
}

Object The_type_description_of_possible_phrase = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_possible_phrases, Qchain_of_available_possible_phrases);

DEFINE_VARIABLE_WITH_SYMBOL(Possible_phrase_count, Qpossible_phrase_count);

Object Chain_of_available_possible_phrases_vector = UNBOUND;

/* POSSIBLE-PHRASE-STRUCTURE-MEMORY-USAGE */
Object possible_phrase_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,6);
    temp = Possible_phrase_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-POSSIBLE-PHRASE-COUNT */
Object outstanding_possible_phrase_count()
{
    Object def_structure_possible_phrase_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,7);
    gensymed_symbol = IFIX(Possible_phrase_count);
    def_structure_possible_phrase_variable = 
	    Chain_of_available_possible_phrases;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_possible_phrase_variable))
	goto end_loop;
    def_structure_possible_phrase_variable = 
	    ISVREF(def_structure_possible_phrase_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-POSSIBLE-PHRASE-1 */
Object reclaim_possible_phrase_1(possible_phrase)
    Object possible_phrase;
{
    Object temp, svref_arg_2;

    x_note_fn_call(78,8);
    inline_note_reclaim_cons(possible_phrase,Nil);
    temp = ISVREF(Chain_of_available_possible_phrases_vector,
	    IFIX(Current_thread_index));
    SVREF(possible_phrase,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_possible_phrases_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = possible_phrase;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-POSSIBLE-PHRASE */
Object reclaim_structure_for_possible_phrase(possible_phrase)
    Object possible_phrase;
{
    x_note_fn_call(78,9);
    return reclaim_possible_phrase_1(possible_phrase);
}

static Object Qg2_defstruct_structure_name_possible_phrase_g2_struct;  /* g2-defstruct-structure-name::possible-phrase-g2-struct */

/* MAKE-PERMANENT-POSSIBLE-PHRASE-STRUCTURE-INTERNAL */
Object make_permanent_possible_phrase_structure_internal()
{
    Object def_structure_possible_phrase_variable;
    Object defstruct_g2_possible_phrase_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,10);
    def_structure_possible_phrase_variable = Nil;
    atomic_incff_symval(Qpossible_phrase_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_possible_phrase_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_possible_phrase_variable = the_array;
	SVREF(defstruct_g2_possible_phrase_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_possible_phrase_g2_struct;
	def_structure_possible_phrase_variable = 
		defstruct_g2_possible_phrase_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_possible_phrase_variable);
}

/* MAKE-POSSIBLE-PHRASE-1 */
Object make_possible_phrase_1()
{
    Object def_structure_possible_phrase_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(78,11);
    def_structure_possible_phrase_variable = 
	    ISVREF(Chain_of_available_possible_phrases_vector,
	    IFIX(Current_thread_index));
    if (def_structure_possible_phrase_variable) {
	svref_arg_1 = Chain_of_available_possible_phrases_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_possible_phrase_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_possible_phrase_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_possible_phrase_g2_struct;
    }
    else
	def_structure_possible_phrase_variable = 
		make_permanent_possible_phrase_structure_internal();
    inline_note_allocate_cons(def_structure_possible_phrase_variable,Nil);
    return VALUES_1(def_structure_possible_phrase_variable);
}

Object The_type_description_of_set_of_possible_phrases = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_set_of_possible_phrasess, Qchain_of_available_set_of_possible_phrasess);

DEFINE_VARIABLE_WITH_SYMBOL(Set_of_possible_phrases_count, Qset_of_possible_phrases_count);

Object Chain_of_available_set_of_possible_phrasess_vector = UNBOUND;

/* SET-OF-POSSIBLE-PHRASES-STRUCTURE-MEMORY-USAGE */
Object set_of_possible_phrases_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,12);
    temp = Set_of_possible_phrases_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SET-OF-POSSIBLE-PHRASES-COUNT */
Object outstanding_set_of_possible_phrases_count()
{
    Object def_structure_set_of_possible_phrases_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,13);
    gensymed_symbol = IFIX(Set_of_possible_phrases_count);
    def_structure_set_of_possible_phrases_variable = 
	    Chain_of_available_set_of_possible_phrasess;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_set_of_possible_phrases_variable))
	goto end_loop;
    def_structure_set_of_possible_phrases_variable = 
	    ISVREF(def_structure_set_of_possible_phrases_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SET-OF-POSSIBLE-PHRASES-1 */
Object reclaim_set_of_possible_phrases_1(set_of_possible_phrases)
    Object set_of_possible_phrases;
{
    Object temp, svref_arg_2;

    x_note_fn_call(78,14);
    inline_note_reclaim_cons(set_of_possible_phrases,Nil);
    temp = ISVREF(Chain_of_available_set_of_possible_phrasess_vector,
	    IFIX(Current_thread_index));
    SVREF(set_of_possible_phrases,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_set_of_possible_phrasess_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = set_of_possible_phrases;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SET-OF-POSSIBLE-PHRASES */
Object reclaim_structure_for_set_of_possible_phrases(set_of_possible_phrases)
    Object set_of_possible_phrases;
{
    x_note_fn_call(78,15);
    return reclaim_set_of_possible_phrases_1(set_of_possible_phrases);
}

static Object Qg2_defstruct_structure_name_set_of_possible_phrases_g2_struct;  /* g2-defstruct-structure-name::set-of-possible-phrases-g2-struct */

/* MAKE-PERMANENT-SET-OF-POSSIBLE-PHRASES-STRUCTURE-INTERNAL */
Object make_permanent_set_of_possible_phrases_structure_internal()
{
    Object def_structure_set_of_possible_phrases_variable;
    Object defstruct_g2_set_of_possible_phrases_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,16);
    def_structure_set_of_possible_phrases_variable = Nil;
    atomic_incff_symval(Qset_of_possible_phrases_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_set_of_possible_phrases_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_set_of_possible_phrases_variable = the_array;
	SVREF(defstruct_g2_set_of_possible_phrases_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_set_of_possible_phrases_g2_struct;
	def_structure_set_of_possible_phrases_variable = 
		defstruct_g2_set_of_possible_phrases_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_set_of_possible_phrases_variable);
}

/* MAKE-SET-OF-POSSIBLE-PHRASES-1 */
Object make_set_of_possible_phrases_1()
{
    Object def_structure_set_of_possible_phrases_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(78,17);
    def_structure_set_of_possible_phrases_variable = 
	    ISVREF(Chain_of_available_set_of_possible_phrasess_vector,
	    IFIX(Current_thread_index));
    if (def_structure_set_of_possible_phrases_variable) {
	svref_arg_1 = Chain_of_available_set_of_possible_phrasess_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_set_of_possible_phrases_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_set_of_possible_phrases_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_set_of_possible_phrases_g2_struct;
    }
    else
	def_structure_set_of_possible_phrases_variable = 
		make_permanent_set_of_possible_phrases_structure_internal();
    inline_note_allocate_cons(def_structure_set_of_possible_phrases_variable,
	    Nil);
    SVREF(def_structure_set_of_possible_phrases_variable,FIX((SI_Long)2L)) 
	    = Nil;
    SVREF(def_structure_set_of_possible_phrases_variable,FIX((SI_Long)3L)) 
	    = Nil;
    return VALUES_1(def_structure_set_of_possible_phrases_variable);
}

Object The_type_description_of_parse_table = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_parse_tables, Qchain_of_available_parse_tables);

DEFINE_VARIABLE_WITH_SYMBOL(Parse_table_count, Qparse_table_count);

Object Chain_of_available_parse_tables_vector = UNBOUND;

/* PARSE-TABLE-STRUCTURE-MEMORY-USAGE */
Object parse_table_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,18);
    temp = Parse_table_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PARSE-TABLE-COUNT */
Object outstanding_parse_table_count()
{
    Object def_structure_parse_table_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,19);
    gensymed_symbol = IFIX(Parse_table_count);
    def_structure_parse_table_variable = Chain_of_available_parse_tables;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_parse_table_variable))
	goto end_loop;
    def_structure_parse_table_variable = 
	    ISVREF(def_structure_parse_table_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PARSE-TABLE-1 */
Object reclaim_parse_table_1(parse_table)
    Object parse_table;
{
    Object temp, svref_arg_2;

    x_note_fn_call(78,20);
    inline_note_reclaim_cons(parse_table,Nil);
    temp = ISVREF(Chain_of_available_parse_tables_vector,
	    IFIX(Current_thread_index));
    SVREF(parse_table,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_parse_tables_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = parse_table;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PARSE-TABLE */
Object reclaim_structure_for_parse_table(parse_table)
    Object parse_table;
{
    x_note_fn_call(78,21);
    return reclaim_parse_table_1(parse_table);
}

static Object Qg2_defstruct_structure_name_parse_table_g2_struct;  /* g2-defstruct-structure-name::parse-table-g2-struct */

/* MAKE-PERMANENT-PARSE-TABLE-STRUCTURE-INTERNAL */
Object make_permanent_parse_table_structure_internal()
{
    Object def_structure_parse_table_variable;
    Object defstruct_g2_parse_table_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,22);
    def_structure_parse_table_variable = Nil;
    atomic_incff_symval(Qparse_table_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_parse_table_variable = Nil;
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
	defstruct_g2_parse_table_variable = the_array;
	SVREF(defstruct_g2_parse_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parse_table_g2_struct;
	def_structure_parse_table_variable = defstruct_g2_parse_table_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_parse_table_variable);
}

/* MAKE-PARSE-TABLE-1 */
Object make_parse_table_1()
{
    Object def_structure_parse_table_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(78,23);
    def_structure_parse_table_variable = 
	    ISVREF(Chain_of_available_parse_tables_vector,
	    IFIX(Current_thread_index));
    if (def_structure_parse_table_variable) {
	svref_arg_1 = Chain_of_available_parse_tables_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_parse_table_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_parse_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parse_table_g2_struct;
    }
    else
	def_structure_parse_table_variable = 
		make_permanent_parse_table_structure_internal();
    inline_note_allocate_cons(def_structure_parse_table_variable,Nil);
    return VALUES_1(def_structure_parse_table_variable);
}

/* CREATE-POSSIBLE-PHRASE */
Object create_possible_phrase(prod,pos)
    Object prod, pos;
{
    Object new_possible_phrase;

    x_note_fn_call(78,24);
    new_possible_phrase = make_possible_phrase_1();
    SVREF(new_possible_phrase,FIX((SI_Long)1L)) = prod;
    SVREF(new_possible_phrase,FIX((SI_Long)2L)) = pos;
    return VALUES_1(new_possible_phrase);
}

/* CREATE-PARSE-TABLE */
Object create_parse_table(nonterminals,terminals,productions,lr_states)
    Object nonterminals, terminals, productions, lr_states;
{
    Object new_parse_table;

    x_note_fn_call(78,25);
    new_parse_table = make_parse_table_1();
    SVREF(new_parse_table,FIX((SI_Long)1L)) = nonterminals;
    SVREF(new_parse_table,FIX((SI_Long)2L)) = terminals;
    SVREF(new_parse_table,FIX((SI_Long)3L)) = productions;
    SVREF(new_parse_table,FIX((SI_Long)4L)) = lr_states;
    return VALUES_1(new_parse_table);
}

/* EPSILON-PRODUCTION-P */
Object epsilon_production_p(symbol)
    Object symbol;
{
    Object prod, temp;
    SI_Long ab_loop_bind_, i;

    x_note_fn_call(78,26);
    ab_loop_bind_ = IFIX(length(Current_productions));
    i = (SI_Long)0L;
    prod = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    prod = ISVREF(Current_productions,i);
    if ( !TRUEP(ISVREF(prod,(SI_Long)2L)) && EQ(symbol,ISVREF(prod,
	    (SI_Long)1L))) {
	temp = T;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SYMBOL-AFTER */
Object symbol_after(symb,rhs)
    Object symb, rhs;
{
    Object temp;

    x_note_fn_call(78,27);
    if ( !TRUEP(rhs))
	temp = Nil;
    else if (EQ(symb,CAR(rhs)))
	temp = CADR(rhs);
    else
	temp = symbol_after(symb,CDR(rhs));
    return VALUES_1(temp);
}

/* SYMBOLS-APPEARING-IN-SOME-PRODUCTION-FOLLOWING */
Object symbols_appearing_in_some_production_following(nonterm)
    Object nonterm;
{
    Object prod, answer, next_symbol, gensymed_symbol, temp_1;
    SI_Long ab_loop_bind_, i;
    char temp;

    x_note_fn_call(78,28);
    ab_loop_bind_ = IFIX(length(Current_productions));
    i = (SI_Long)0L;
    prod = Nil;
    answer = Qnil;
    next_symbol = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    prod = ISVREF(Current_productions,i);
    next_symbol = symbol_after(nonterm,ISVREF(prod,(SI_Long)2L));
    if (next_symbol) {
	gensymed_symbol = answer;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	if (EQ(M_CAR(gensymed_symbol),next_symbol)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	answer = temp ? answer : token_cons_1(next_symbol,answer);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = answer;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* FIRST-CAN-BE */
Object first_can_be(symbol,list_1)
    Object symbol, list_1;
{
    Object temp;

    x_note_fn_call(78,29);
    temp = EQ(symbol,CAR(list_1)) ? T : epsilon_production_p(CAR(list_1)) ?
	     first_can_be(symbol,CDR(list_1)) : Nil;
    return VALUES_1(temp);
}

/* CAN-THIS-PRODUCTION-END-WITH */
Object can_this_production_end_with(nonterm,prod)
    Object nonterm, prod;
{
    Object reversed_rhs, answer;

    x_note_fn_call(78,30);
    reversed_rhs = token_reverse(ISVREF(prod,(SI_Long)2L));
    answer = first_can_be(nonterm,reversed_rhs) ? ISVREF(prod,(SI_Long)1L) 
	    : Nil;
    reclaim_token_list_1(reversed_rhs);
    return VALUES_1(answer);
}

/* NONTERMS-WHICH-HAVE-PRODUCTIONS-WHICH-MAY-END-WITH */
Object nonterms_which_have_productions_which_may_end_with(nonterm)
    Object nonterm;
{
    Object prod, answer, whatever, token_modify_macro_using_test_arg_1, car_1;
    Object cdr_1, key_result, x_element, ab_loop_list_, ab_loop_it_, temp_1;
    SI_Long ab_loop_bind_, i;
    char temp;

    x_note_fn_call(78,31);
    ab_loop_bind_ = IFIX(length(Current_productions));
    i = (SI_Long)0L;
    prod = Nil;
    answer = Qnil;
    whatever = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    prod = ISVREF(Current_productions,i);
    whatever = can_this_production_end_with(nonterm,prod);
    if (whatever) {
	if ( !EQ(whatever,nonterm)) {
	    token_modify_macro_using_test_arg_1 = whatever;
	    car_1 = token_modify_macro_using_test_arg_1;
	    cdr_1 = answer;
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list_ = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    x_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_1:;
	    answer = temp ? cdr_1 : token_cons_1(car_1,cdr_1);
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = answer;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* SYMBOLS-WHICH-CAN-BEGIN-RHS */
Object symbols_which_can_begin_rhs(rhs,omit)
    Object rhs, omit;
{
    Object temp, yn_1, answer, done_qm, gensymed_symbol, new_omit;
    char temp_1;

    x_note_fn_call(78,32);
    if ( !TRUEP(rhs))
	temp = Nil;
    else {
	yn_1 = CAR(rhs);
	answer = Qnil;
	done_qm = memq_function(yn_1,omit);
      next_loop:
	if (done_qm)
	    goto end_loop;
	if ( !TRUEP(yn_1))
	    done_qm = T;
	else if (memq_function(yn_1,Current_terminals)) {
	    gensymed_symbol = answer;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    if (EQ(M_CAR(gensymed_symbol),yn_1)) {
		temp_1 = TRUEP(gensymed_symbol);
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	    answer = temp_1 ? answer : token_cons_1(yn_1,answer);
	    done_qm = T;
	}
	else if (epsilon_production_p(yn_1)) {
	    new_omit = token_cons_1(yn_1,copy_list_using_token_conses_1(omit));
	    answer = lr_first(yn_1);
	    yn_1 = CAR(rhs);
	    rhs = CDR(rhs);
	    done_qm = memq_function(yn_1,new_omit);
	    reclaim_token_list_1(new_omit);
	}
	else {
	    answer = lr_first(yn_1);
	    done_qm = T;
	}
	goto next_loop;
      end_loop:
	temp = answer;
    }
    return VALUES_1(temp);
}

static Object Qtoken;              /* token */

/* LR-FIRST-OF-NONTERMINAL */
Object lr_first_of_nonterminal(symb,omit)
    Object symb, omit;
{
    Object real_omit, prod, answer, lhs, rhs, first_of_rhs, token_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2;
    Object token_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_, temp_2;
    SI_Long ab_loop_bind_, i, ab_loop_bind__1, i_1;
    char temp_1;

    x_note_fn_call(78,33);
    real_omit = token_cons_1(symb,copy_list_using_token_conses_1(omit));
    ab_loop_bind_ = IFIX(length(Current_productions));
    i = (SI_Long)0L;
    prod = Nil;
    answer = Qnil;
    lhs = Nil;
    rhs = Nil;
    first_of_rhs = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    prod = ISVREF(Current_productions,i);
    lhs = ISVREF(prod,(SI_Long)1L);
    rhs = EQ(lhs,symb) ? ISVREF(prod,(SI_Long)2L) : Nil;
    first_of_rhs = symbols_which_can_begin_rhs(rhs,real_omit);
    if (first_of_rhs) {
	ab_loop_bind__1 = IFIX(length(first_of_rhs));
	i_1 = (SI_Long)0L;
      next_loop_1:
	if (i_1 >= ab_loop_bind__1)
	    goto end_loop_1;
	token_pop_store = Nil;
	cons_1 = first_of_rhs;
	if (cons_1) {
	    token_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qtoken);
	    if (ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	first_of_rhs = next_cons;
	token_modify_macro_using_test_arg_1 = token_pop_store;
	car_1 = token_modify_macro_using_test_arg_1;
	cdr_1 = answer;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list_ = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	x_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp_1 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	temp_1 = TRUEP(Qnil);
      end_1:;
	answer = temp_1 ? cdr_1 : token_cons_1(car_1,cdr_1);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	goto end_2;
      end_2:;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_token_list_1(real_omit);
    temp_2 = answer;
    goto end_3;
    temp_2 = Qnil;
  end_3:;
    return VALUES_1(temp_2);
}

/* LR-FIRST */
Object lr_first(symb)
    Object symb;
{
    Object temp, stupid_tmp_list, lr_first_symb;

    x_note_fn_call(78,34);
    if ( !TRUEP(symb))
	temp = Nil;
    else if (memq_function(symb,Current_terminals))
	temp = token_cons_1(symb,Nil);
    else {
	stupid_tmp_list = token_cons_1(symb,Nil);
	lr_first_symb = lr_first_of_nonterminal(symb,stupid_tmp_list);
	reclaim_token_list_1(stupid_tmp_list);
	temp = lr_first_symb;
    }
    return VALUES_1(temp);
}

/* DETERMINE-FOLLOW-OF-NONTERMINAL-WITH-OMISSIONS */
Object determine_follow_of_nonterminal_with_omissions(nonterm,omit)
    Object nonterm, omit;
{
    Object answer, nonterms_which_have_productions_which_may_end_with_nonterm;
    Object lhs, ab_loop_list_, computed_already_qm, follow_nonterm, temp;
    Object new_omit, follow_lhs, token_pop_store, cons_1, next_cons, temp_1;
    Object svref_arg_2, token_modify_macro_using_test_arg_1, car_1, cdr_1;
    Object key_result, x_element, ab_loop_list__1, ab_loop_it_;
    SI_Long ab_loop_bind_, i;
    char temp_2;

    x_note_fn_call(78,35);
    answer = Qnil;
    nonterms_which_have_productions_which_may_end_with_nonterm = 
	    nonterms_which_have_productions_which_may_end_with(nonterm);
    lhs = Nil;
    ab_loop_list_ = nonterms_which_have_productions_which_may_end_with_nonterm;
    computed_already_qm = Nil;
    follow_nonterm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    lhs = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = assoc_eql(lhs,Lr0_follow);
    computed_already_qm = CDR(temp);
    if ( !TRUEP(lhs))
	follow_nonterm = Nil;
    else if (computed_already_qm)
	follow_nonterm = copy_list_using_token_conses_1(computed_already_qm);
    else if (memq_function(lhs,omit))
	follow_nonterm = lbreak((SI_Long)1L,"Cannot handle this.~%");
    else {
	new_omit = token_cons_1(lhs,copy_list_using_token_conses_1(omit));
	follow_lhs = follow_1(lhs,new_omit);
	reclaim_token_list_1(new_omit);
	follow_nonterm = follow_lhs;
    }
    ab_loop_bind_ = IFIX(length(follow_nonterm));
    i = (SI_Long)0L;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    token_pop_store = Nil;
    cons_1 = follow_nonterm;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    follow_nonterm = next_cons;
    token_modify_macro_using_test_arg_1 = token_pop_store;
    car_1 = token_modify_macro_using_test_arg_1;
    cdr_1 = answer;
    key_result = car_1;
    x_element = Nil;
    ab_loop_list__1 = cdr_1;
    ab_loop_it_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    x_element = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp_2 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_2;
  end_loop_2:
    temp_2 = TRUEP(Qnil);
  end_1:;
    answer = temp_2 ? cdr_1 : token_cons_1(car_1,cdr_1);
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
  end_2:;
    goto next_loop;
  end_loop:
    reclaim_token_list_1(nonterms_which_have_productions_which_may_end_with_nonterm);
    return VALUES_1(answer);
}

/* FOLLOW-1 */
Object follow_1(nonterm,omit)
    Object nonterm, omit;
{
    Object follow, all_betas, beta, ab_loop_list_, first_beta, token_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2;
    Object token_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__1, ab_loop_it_, follow_nonterm;
    SI_Long ab_loop_bind_, i;
    char temp_1;

    x_note_fn_call(78,36);
    follow = Qnil;
    if (EQ(nonterm,ISVREF(ISVREF(Current_productions,(SI_Long)0L),
	    (SI_Long)1L)))
	follow = token_cons_1(Nil,follow);
    all_betas = symbols_appearing_in_some_production_following(nonterm);
    beta = Nil;
    ab_loop_list_ = all_betas;
    first_beta = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    beta = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    first_beta = lr_first(beta);
    ab_loop_bind_ = IFIX(length(first_beta));
    i = (SI_Long)0L;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    token_pop_store = Nil;
    cons_1 = first_beta;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    first_beta = next_cons;
    token_modify_macro_using_test_arg_1 = token_pop_store;
    car_1 = token_modify_macro_using_test_arg_1;
    cdr_1 = follow;
    key_result = car_1;
    x_element = Nil;
    ab_loop_list__1 = cdr_1;
    ab_loop_it_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    x_element = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_2;
  end_loop_2:
    temp_1 = TRUEP(Qnil);
  end_1:;
    follow = temp_1 ? cdr_1 : token_cons_1(car_1,cdr_1);
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
  end_2:;
    goto next_loop;
  end_loop:
    reclaim_token_list_1(all_betas);
    follow_nonterm = 
	    determine_follow_of_nonterminal_with_omissions(nonterm,omit);
    ab_loop_bind_ = IFIX(length(follow_nonterm));
    i = (SI_Long)0L;
  next_loop_3:
    if (i >= ab_loop_bind_)
	goto end_loop_3;
    token_pop_store = Nil;
    cons_1 = follow_nonterm;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    follow_nonterm = next_cons;
    token_modify_macro_using_test_arg_1 = token_pop_store;
    car_1 = token_modify_macro_using_test_arg_1;
    cdr_1 = follow;
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_3;
    }
    goto next_loop_4;
  end_loop_4:
    temp_1 = TRUEP(Qnil);
  end_3:;
    follow = temp_1 ? cdr_1 : token_cons_1(car_1,cdr_1);
    i = i + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:
    goto end_4;
  end_4:;
    return VALUES_1(follow);
}

/* CREATE-FOLLOW-A-LIST */
Object create_follow_a_list()
{
    Object nonterminal, ab_loop_list_, nonterm_follow;

    x_note_fn_call(78,37);
    if (Lr0_follow)
	Lr0_follow = Nil;
    nonterminal = Nil;
    ab_loop_list_ = Current_nonterminals;
    nonterm_follow = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    nonterminal = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    nonterm_follow = follow_1(nonterminal,Nil);
    Lr0_follow = token_cons_1(token_cons_1(nonterminal,nonterm_follow),
	    Lr0_follow);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* LR-FOLLOW-FOR-POSSIBLE-PHRASE */
Object lr_follow_for_possible_phrase(possible_phrase)
    Object possible_phrase;
{
    Object nonterm, temp;

    x_note_fn_call(78,38);
    nonterm = ISVREF(ISVREF(possible_phrase,(SI_Long)1L),(SI_Long)1L);
    temp = assoc_eql(nonterm,Lr0_follow);
    return VALUES_1(CDR(temp));
}

/* SYMBOL-AFTER-DOT */
Object symbol_after_dot(possible_phrase)
    Object possible_phrase;
{
    Object temp;

    x_note_fn_call(78,39);
    temp = nth(ISVREF(possible_phrase,(SI_Long)2L),
	    ISVREF(ISVREF(possible_phrase,(SI_Long)1L),(SI_Long)2L));
    return VALUES_1(temp);
}

/* COLLECT-NONTERMINALS */
Object collect_nonterminals()
{
    Object last_1, prod, lhs, nonterms, temp;
    SI_Long i;

    x_note_fn_call(78,40);
    last_1 = FIXNUM_SUB1(length(Current_productions));
    i = IFIX(last_1);
    prod = Nil;
    lhs = Nil;
    nonterms = Nil;
  next_loop:
    if (i < (SI_Long)0L)
	goto end_loop;
    prod = ISVREF(Current_productions,i);
    lhs = ISVREF(prod,(SI_Long)1L);
    if ( !TRUEP(memq_function(lhs,nonterms)))
	nonterms = token_cons_1(lhs,nonterms);
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = nonterms;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SYMBOLS-IN-GRAMMAR-WHICH-ARE-NOT-NONTERMINALS */
Object symbols_in_grammar_which_are_not_nonterminals(nonterms)
    Object nonterms;
{
    Object prod, rhs, termls, symb, ab_loop_list_, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(78,41);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Current_productions));
    prod = Nil;
    rhs = Nil;
    termls = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    prod = ISVREF(Current_productions,i);
    rhs = ISVREF(prod,(SI_Long)2L);
    symb = Nil;
    ab_loop_list_ = rhs;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    symb = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(memq_function(symb,nonterms) || memq_function(symb,termls)))
	termls = token_cons_1(symb,termls);
    goto next_loop_1;
  end_loop_1:;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = termls;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* PRODUCTION-MEMBER-OF-POSSIBLE-PHRASES-P */
Object production_member_of_possible_phrases_p(production,possible_phrases)
    Object production, possible_phrases;
{
    Object possible_phrase, ab_loop_list_, temp;

    x_note_fn_call(78,42);
    possible_phrase = Nil;
    ab_loop_list_ = possible_phrases;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    possible_phrase = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(production,ISVREF(possible_phrase,(SI_Long)1L)) && (SI_Long)0L 
	    == IFIX(ISVREF(possible_phrase,(SI_Long)2L))) {
	temp = T;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* UNREPRESENTED-NONKERNEL-POSSIBLE-PHRASES */
Object unrepresented_nonkernel_possible_phrases(nonterminal,
	    possible_phrases_list)
    Object nonterminal, possible_phrases_list;
{
    Object answer, prod, new_possible_phrase, temp;
    SI_Long production_num, ab_loop_bind_;

    x_note_fn_call(78,43);
    answer = Qnil;
    production_num = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Current_productions));
    prod = Nil;
  next_loop:
    if (production_num >= ab_loop_bind_)
	goto end_loop;
    prod = ISVREF(Current_productions,production_num);
    if (EQ(nonterminal,ISVREF(prod,(SI_Long)1L))) {
	if ( !TRUEP(production_member_of_possible_phrases_p(prod,
		possible_phrases_list))) {
	    new_possible_phrase = create_possible_phrase(prod,
		    FIX((SI_Long)0L));
	    answer = token_cons_1(new_possible_phrase,answer);
	}
    }
    production_num = production_num + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = answer;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* LR-CLOSURE */
Object lr_closure(initial_possible_phrase_or_phrases)
    Object initial_possible_phrase_or_phrases;
{
    Object done_qm, answer, possible_phrase, ab_loop_list_, next_symbol;
    Object new_possible_phrases, item, ab_loop_list__1;

    x_note_fn_call(78,44);
    done_qm = Nil;
    answer = LISTP(initial_possible_phrase_or_phrases) ? 
	    copy_list_using_token_conses_1(initial_possible_phrase_or_phrases) 
	    : token_cons_1(initial_possible_phrase_or_phrases,Nil);
  next_loop:
    if (done_qm)
	goto end_loop;
    done_qm = T;
    possible_phrase = Nil;
    ab_loop_list_ = answer;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    possible_phrase = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    next_symbol = symbol_after_dot(possible_phrase);
    if (memq_function(next_symbol,Current_nonterminals)) {
	new_possible_phrases = 
		unrepresented_nonkernel_possible_phrases(next_symbol,answer);
	item = Nil;
	ab_loop_list__1 = new_possible_phrases;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	item = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	answer = token_cons_1(item,answer);
	done_qm = Nil;
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    return VALUES_1(answer);
}

/* FIND-TRANSITIONS */
Object find_transitions(set_of_possible_phrases,gram_sym)
    Object set_of_possible_phrases, gram_sym;
{
    Object list_of_possible_phrases, temp, unclosed, possible_phrase;
    Object ab_loop_list_, new_possible_phrase, answer;

    x_note_fn_call(78,45);
    list_of_possible_phrases = ISVREF(set_of_possible_phrases,(SI_Long)1L);
    if ( !TRUEP(list_of_possible_phrases))
	temp = Nil;
    else if (ATOM(list_of_possible_phrases))
	temp = error((SI_Long)2L,
		"ERROR: non-cons as the represents of: ~s~%",
		set_of_possible_phrases);
    else {
	unclosed = Nil;
	possible_phrase = Nil;
	ab_loop_list_ = list_of_possible_phrases;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	possible_phrase = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(gram_sym,symbol_after_dot(possible_phrase))) {
	    new_possible_phrase = 
		    create_possible_phrase(ISVREF(possible_phrase,
		    (SI_Long)1L),FIXNUM_ADD1(ISVREF(possible_phrase,
		    (SI_Long)2L)));
	    unclosed = token_cons_1(new_possible_phrase,unclosed);
	}
	goto next_loop;
      end_loop:;
	answer = lr_closure(unclosed);
	temp = answer;
    }
    return VALUES_1(temp);
}

/* POSSIBLE-PHRASE-EQL */
Object possible_phrase_eql(possible_phrase1,possible_phrase2)
    Object possible_phrase1, possible_phrase2;
{
    Object temp;

    x_note_fn_call(78,46);
    temp = EQ(ISVREF(possible_phrase1,(SI_Long)1L),ISVREF(possible_phrase2,
	    (SI_Long)1L)) ? (FIXNUM_EQ(ISVREF(possible_phrase1,
	    (SI_Long)2L),ISVREF(possible_phrase2,(SI_Long)2L)) ? T : Nil) :
	     Qnil;
    return VALUES_1(temp);
}

/* POSSIBLE-PHRASE-MEMBER */
Object possible_phrase_member(possible_phrase,list_1)
    Object possible_phrase, list_1;
{
    Object old_possible_phrase, ab_loop_list_, temp;

    x_note_fn_call(78,47);
    old_possible_phrase = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    old_possible_phrase = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (possible_phrase_eql(possible_phrase,old_possible_phrase)) {
	temp = T;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SAME-POSSIBLE-PHRASES-P */
Object same_possible_phrases_p(possible_phrase_list1,possible_phrase_list2)
    Object possible_phrase_list1, possible_phrase_list2;
{
    Object same, possible_phrase, ab_loop_list_;

    x_note_fn_call(78,48);
    same = T;
    possible_phrase = Nil;
    ab_loop_list_ = possible_phrase_list2;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    possible_phrase = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(same))
	goto end_loop;
    if ( !TRUEP(possible_phrase_member(possible_phrase,possible_phrase_list1)))
	same = Nil;
    goto next_loop;
  end_loop:;
    possible_phrase = Nil;
    ab_loop_list_ = possible_phrase_list1;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    possible_phrase = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(same))
	goto end_loop_1;
    if ( !TRUEP(possible_phrase_member(possible_phrase,possible_phrase_list2)))
	same = Nil;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(same);
}

/* POSSIBLE-PHRASES-REPRESENTED-IN-LIST? */
Object possible_phrases_represented_in_list_qm(list_of_poss_phrases,closure)
    Object list_of_poss_phrases, closure;
{
    Object temp, possible_phrases_set, ab_loop_list_;

    x_note_fn_call(78,49);
    if ( !TRUEP(list_of_poss_phrases))
	temp = Nil;
    else {
	possible_phrases_set = Nil;
	ab_loop_list_ = closure;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	possible_phrases_set = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (same_possible_phrases_p(ISVREF(possible_phrases_set,
		(SI_Long)1L),list_of_poss_phrases)) {
	    temp = possible_phrases_set;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* POSSIBLE-PHRASES-REPRESENTED-IN-ARRAY? */
Object possible_phrases_represented_in_array_qm(list_of_poss_phrases)
    Object list_of_poss_phrases;
{
    Object temp, possible_phrases_set;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(78,50);
    if ( !TRUEP(list_of_poss_phrases))
	temp = Nil;
    else {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(Current_lr_states));
	possible_phrases_set = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	possible_phrases_set = ISVREF(Current_lr_states,i);
	if (same_possible_phrases_p(ISVREF(possible_phrases_set,
		(SI_Long)1L),list_of_poss_phrases)) {
	    temp = possible_phrases_set;
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* FIND-DESTINATION-OF-TRANSITIONS */
Object find_destination_of_transitions(current_set,gram_sym)
    Object current_set, gram_sym;
{
    Object list_of_shift_state, shift_state, token_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2;
    SI_Long ab_loop_bind_, i;

    x_note_fn_call(78,51);
    list_of_shift_state = find_transitions(current_set,gram_sym);
    shift_state = 
	    possible_phrases_represented_in_array_qm(list_of_shift_state);
    ab_loop_bind_ = IFIX(length(list_of_shift_state));
    i = (SI_Long)0L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    token_pop_store = Nil;
    cons_1 = list_of_shift_state;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_of_shift_state = next_cons;
    reclaim_possible_phrase_1(token_pop_store);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(shift_state);
}

/* CREATE-LR-STATES */
Object create_lr_states()
{
    Object current_set, all_sets, closure, to_be_processed;
    Object initial_possible_phrase, temp, gram_sym, ab_loop_list_, new_set;
    Object new_list, duplicate_set, token_pop_store, cons_1, next_cons;
    Object svref_arg_2, token_push_modify_macro_arg, car_1, cdr_1;
    Object closure_length, array_version, each_set, ab_loop_iter_flag_, temp_1;
    SI_Long ab_loop_bind_, i;

    x_note_fn_call(78,52);
    current_set = make_set_of_possible_phrases_1();
    all_sets = token_cons_1(current_set,Nil);
    closure = token_cons_1(current_set,Nil);
    to_be_processed = Qnil;
    initial_possible_phrase = 
	    create_possible_phrase(ISVREF(Current_productions,(SI_Long)0L),
	    FIX((SI_Long)0L));
    temp = lr_closure(initial_possible_phrase);
    SVREF(current_set,FIX((SI_Long)1L)) = temp;
  next_loop:
    if ( !TRUEP(current_set))
	goto end_loop;
    gram_sym = Nil;
    ab_loop_list_ = Current_terminals;
    new_set = Nil;
    new_list = Nil;
    duplicate_set = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    gram_sym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_list = find_transitions(current_set,gram_sym);
    duplicate_set = possible_phrases_represented_in_list_qm(new_list,all_sets);
    if (new_list) {
	if (duplicate_set) {
	    ab_loop_bind_ = IFIX(length(new_list));
	    i = (SI_Long)0L;
	  next_loop_2:
	    if (i >= ab_loop_bind_)
		goto end_loop_2;
	    token_pop_store = Nil;
	    cons_1 = new_list;
	    if (cons_1) {
		token_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qtoken);
		if (ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_token_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_token_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_token_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_token_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    new_list = next_cons;
	    reclaim_possible_phrase_1(token_pop_store);
	    i = i + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:;
	}
	else {
	    new_set = make_set_of_possible_phrases_1();
	    SVREF(new_set,FIX((SI_Long)1L)) = new_list;
	    all_sets = token_cons_1(new_set,all_sets);
	    to_be_processed = token_cons_1(new_set,to_be_processed);
	}
    }
    goto next_loop_1;
  end_loop_1:;
    gram_sym = Nil;
    ab_loop_list_ = Current_nonterminals;
    new_set = Nil;
    new_list = Nil;
    duplicate_set = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    gram_sym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_list = find_transitions(current_set,gram_sym);
    duplicate_set = possible_phrases_represented_in_list_qm(new_list,all_sets);
    if (new_list) {
	if (duplicate_set) {
	    token_push_modify_macro_arg = token_list_2(gram_sym,duplicate_set);
	    car_1 = token_push_modify_macro_arg;
	    cdr_1 = ISVREF(current_set,(SI_Long)3L);
	    temp = token_cons_1(car_1,cdr_1);
	    SVREF(current_set,FIX((SI_Long)3L)) = temp;
	    ab_loop_bind_ = IFIX(length(new_list));
	    i = (SI_Long)0L;
	  next_loop_4:
	    if (i >= ab_loop_bind_)
		goto end_loop_4;
	    token_pop_store = Nil;
	    cons_1 = new_list;
	    if (cons_1) {
		token_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qtoken);
		if (ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_token_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_token_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_token_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_token_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    new_list = next_cons;
	    reclaim_possible_phrase_1(token_pop_store);
	    i = i + (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:;
	}
	else {
	    new_set = make_set_of_possible_phrases_1();
	    SVREF(new_set,FIX((SI_Long)1L)) = new_list;
	    token_push_modify_macro_arg = token_list_2(gram_sym,new_set);
	    car_1 = token_push_modify_macro_arg;
	    cdr_1 = ISVREF(current_set,(SI_Long)3L);
	    temp = token_cons_1(car_1,cdr_1);
	    SVREF(current_set,FIX((SI_Long)3L)) = temp;
	    all_sets = token_cons_1(new_set,all_sets);
	    to_be_processed = token_cons_1(new_set,to_be_processed);
	}
    }
    goto next_loop_3;
  end_loop_3:;
    if (to_be_processed) {
	token_pop_store = Nil;
	cons_1 = to_be_processed;
	if (cons_1) {
	    token_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qtoken);
	    if (ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	to_be_processed = next_cons;
	current_set = token_pop_store;
	closure = token_cons_1(current_set,closure);
    }
    else
	current_set = Nil;
    goto next_loop;
  end_loop:
    closure_length = length(closure);
    array_version = make_array(1,closure_length);
    each_set = Nil;
    ab_loop_list_ = closure;
    i = IFIX(FIXNUM_SUB1(closure_length));
    ab_loop_iter_flag_ = T;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    each_set = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i - (SI_Long)1L;
    ISVREF(array_version,i) = each_set;
    ab_loop_iter_flag_ = Nil;
    goto next_loop_5;
  end_loop_5:;
    temp_1 = array_version;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* CREATE-AUGMENTED-GRAMMAR */
Object create_augmented_grammar(list_of_productions)
    Object list_of_productions;
{
    Object num_productions, array_of_productions, top_production;
    Object svref_new_value, lhs, rhs, reduction, ab_loop_list_, new_production;
    Object ab_loop_iter_flag_, ab_loop_desetq_, temp;
    SI_Long i;

    x_note_fn_call(78,53);
    num_productions = FIXNUM_ADD1(length(list_of_productions));
    array_of_productions = make_array(1,num_productions);
    top_production = make_production_1();
    svref_new_value = ab_gensym(0);
    SVREF(top_production,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = token_cons_1(CAAR(list_of_productions),Nil);
    SVREF(top_production,FIX((SI_Long)2L)) = svref_new_value;
    SVREF(top_production,FIX((SI_Long)3L)) = Default_reduction;
    SVREF(array_of_productions,FIX((SI_Long)0L)) = top_production;
    lhs = Nil;
    rhs = Nil;
    reduction = Nil;
    ab_loop_list_ = list_of_productions;
    i = (SI_Long)1L;
    new_production = Nil;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    lhs = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    rhs = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    reduction = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    new_production = make_production_1();
    SVREF(new_production,FIX((SI_Long)1L)) = lhs;
    svref_new_value = LISTP(rhs) ? rhs : gensym_cons_1(rhs,Nil);
    SVREF(new_production,FIX((SI_Long)2L)) = svref_new_value;
    if ( !TRUEP(reduction))
	SVREF(new_production,FIX((SI_Long)3L)) = Default_reduction;
    else
	SVREF(new_production,FIX((SI_Long)3L)) = reduction;
    ISVREF(array_of_productions,i) = new_production;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(array_of_productions);
}

static Object Qshift;              /* shift */

static Object Qaccept;             /* accept */

static Object Qab_reduce;          /* reduce */

/* CREATE-ACTION-TRANSITIONS */
Object create_action_transitions()
{
    Object current_set, top_production, possible_phrase, ab_loop_list_;
    Object next_sym, shift_state, token_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value, follw, production, term, ab_loop_list__1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(78,54);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Current_lr_states));
    current_set = Nil;
    top_production = ISVREF(Current_productions,(SI_Long)0L);
    create_follow_a_list();
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    current_set = ISVREF(Current_lr_states,i);
    possible_phrase = Nil;
    ab_loop_list_ = ISVREF(current_set,(SI_Long)1L);
    next_sym = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    possible_phrase = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    next_sym = symbol_after_dot(possible_phrase);
    if (memq_function(next_sym,Current_terminals)) {
	shift_state = find_destination_of_transitions(current_set,next_sym);
	if ( ! !TRUEP(shift_state)) {
	    token_push_modify_macro_arg = token_list_2(next_sym,
		    token_list_2(Qshift,shift_state));
	    car_1 = token_push_modify_macro_arg;
	    cdr_1 = ISVREF(current_set,(SI_Long)2L);
	    svref_new_value = token_cons_1(car_1,cdr_1);
	    SVREF(current_set,FIX((SI_Long)2L)) = svref_new_value;
	}
    }
    else if (next_sym);
    else if (EQ(ISVREF(possible_phrase,(SI_Long)1L),top_production)) {
	token_push_modify_macro_arg = token_list_2(Nil,
		token_cons_1(Qaccept,Nil));
	car_1 = token_push_modify_macro_arg;
	cdr_1 = ISVREF(current_set,(SI_Long)2L);
	svref_new_value = token_cons_1(car_1,cdr_1);
	SVREF(current_set,FIX((SI_Long)2L)) = svref_new_value;
    }
    else {
	follw = lr_follow_for_possible_phrase(possible_phrase);
	production = ISVREF(possible_phrase,(SI_Long)1L);
	term = Nil;
	ab_loop_list__1 = follw;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	term = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	token_push_modify_macro_arg = token_list_2(term,
		token_list_2(Qab_reduce,production));
	car_1 = token_push_modify_macro_arg;
	cdr_1 = ISVREF(current_set,(SI_Long)2L);
	svref_new_value = token_cons_1(car_1,cdr_1);
	SVREF(current_set,FIX((SI_Long)2L)) = svref_new_value;
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_token_tree_1(Lr0_follow);
    Lr0_follow = Nil;
    return VALUES_1(Nil);
}

/* COMPILE-PARSING-TABLE */
Object compile_parsing_table(productions)
    Object productions;
{
    Object lr0_follow, current_productions, current_nonterminals;
    Object current_terminals, current_lr_states, temp;
    Declare_special(5);

    x_note_fn_call(78,55);
    lr0_follow = Qnil;
    PUSH_SPECIAL_WITH_SYMBOL(Lr0_follow,Qlr0_follow,lr0_follow,4);
      current_productions = create_augmented_grammar(CDR(productions));
      PUSH_SPECIAL_WITH_SYMBOL(Current_productions,Qcurrent_productions,current_productions,
	      3);
	current_nonterminals = collect_nonterminals();
	PUSH_SPECIAL_WITH_SYMBOL(Current_nonterminals,Qcurrent_nonterminals,current_nonterminals,
		2);
	  current_terminals = 
		  symbols_in_grammar_which_are_not_nonterminals(Current_nonterminals);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_terminals,Qcurrent_terminals,current_terminals,
		  1);
	    current_lr_states = create_lr_states();
	    PUSH_SPECIAL_WITH_SYMBOL(Current_lr_states,Qcurrent_lr_states,current_lr_states,
		    0);
	      create_action_transitions();
	      temp = create_parse_table(Current_nonterminals,
		      Current_terminals,Current_productions,Current_lr_states);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* LR-SHIFT */
Object lr_shift(new_state,new_token)
    Object new_state, new_token;
{
    Object token_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(78,56);
    Current_token_stack = token_cons_1(new_token,Current_token_stack);
    Current_state_stack = token_cons_1(new_state,Current_state_stack);
    token_pop_store = Nil;
    cons_1 = Current_input_stack;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Current_input_stack = next_cons;
    return VALUES_1(Nil);
}

/* LR-GOTO */
Object lr_goto(state_1,symbol)
    Object state_1, symbol;
{
    Object temp;

    x_note_fn_call(78,57);
    temp = assq_function(symbol,ISVREF(state_1,(SI_Long)3L));
    return VALUES_1(CADR(temp));
}

/* LR-REDUCE */
Object lr_reduce(production_struct)
    Object production_struct;
{
    Object number_of_constituents, last_constituent_index;
    Object thing_on_top_of_stack, value_on_top_of_stack, token_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2, gensymed_symbol;
    Object gensymed_symbol_1, current_edit_state, temp_1;
    Object transformed_reduction, non_terminal, next_state, new_parse_object;
    SI_Long i;
    Declare_special(1);

    x_note_fn_call(78,58);
    number_of_constituents = length(ISVREF(production_struct,(SI_Long)2L));
    last_constituent_index = FIXNUM_SUB1(number_of_constituents);
    ensure_transform_constituent_array(number_of_constituents);
    i = IFIX(last_constituent_index);
    thing_on_top_of_stack = Nil;
    value_on_top_of_stack = Nil;
  next_loop:
    if (i < (SI_Long)0L)
	goto end_loop;
    token_pop_store = Nil;
    cons_1 = Current_token_stack;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Current_token_stack = next_cons;
    thing_on_top_of_stack = token_pop_store;
    value_on_top_of_stack = ISVREF(thing_on_top_of_stack,(SI_Long)4L);
    reclaim_parse_object_1(thing_on_top_of_stack);
    token_pop_store = Nil;
    cons_1 = Current_state_stack;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Current_state_stack = next_cons;
    temp = Current_transform_constituent_array;
    ISVREF(temp,i) = value_on_top_of_stack;
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    gensymed_symbol = Current_edit_state;
    if (Generate_source_annotation_info) {
	gensymed_symbol_1 = Current_edit_state ? 
		get_current_sexp_annotation_hash() : Nil;
	if (gensymed_symbol_1);
	else
	    gensymed_symbol_1 = make_sexp_annotation_hash();
    }
    else
	gensymed_symbol_1 = Nil;
    current_edit_state = make_edit_state_1();
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      temp = Current_edit_state;
      SVREF(temp,FIX((SI_Long)90L)) = gensymed_symbol_1;
      temp_1 = 
	      copy_tree_using_token_conses_1(transform_by_template(ISVREF(production_struct,
	      (SI_Long)3L)));
      if (gensymed_symbol) {
	  temp = Current_edit_state;
	  SVREF(temp,FIX((SI_Long)90L)) = Nil;
      }
      reclaim_edit_state_1(Current_edit_state);
      transformed_reduction = temp_1;
    POP_SPECIAL();
    non_terminal = ISVREF(production_struct,(SI_Long)1L);
    next_state = lr_goto(CAR(Current_state_stack),non_terminal);
    new_parse_object = create_parse_object(non_terminal,transformed_reduction);
    if ( !TRUEP(next_state))
	error((SI_Long)1L,"Error in LR parsing table.");
    Current_token_stack = token_cons_1(new_parse_object,Current_token_stack);
    i = IFIX(last_constituent_index);
  next_loop_1:
    if (i < (SI_Long)0L)
	goto end_loop_1;
    reclaim_token_tree_1(ISVREF(Current_transform_constituent_array,i));
    i = i - (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    Current_state_stack = token_cons_1(next_state,Current_state_stack);
    return VALUES_1(Nil);
}

/* LR-ACTION */
Object lr_action(state_1,symbol)
    Object state_1, symbol;
{
    Object temp;

    x_note_fn_call(78,59);
    temp = assq_function(symbol,ISVREF(state_1,(SI_Long)2L));
    return VALUES_1(CADR(temp));
}

/* LR-PARSE-1 */
Object lr_parse_1(input_stack)
    Object input_stack;
{
    Object current_input_stack, current_state_stack, current_token_stack;
    Object return_value, top_token, ip, action, temp, token_pop_store, cons_1;
    Object next_cons, temp_1, svref_arg_2, answer_token;
    Declare_special(3);

    x_note_fn_call(78,60);
    current_input_stack = token_reverse(input_stack);
    PUSH_SPECIAL_WITH_SYMBOL(Current_input_stack,Qcurrent_input_stack,current_input_stack,
	    2);
      current_state_stack = token_cons_1(ISVREF(Current_lr_states,
	      (SI_Long)0L),Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Current_state_stack,Qcurrent_state_stack,current_state_stack,
	      1);
	current_token_stack = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_token_stack,Qcurrent_token_stack,current_token_stack,
		0);
	  return_value = Nil;
	  top_token = Nil;
	  ip = Nil;
	  action = Nil;
	next_loop:
	  top_token = CAR(Current_input_stack);
	  ip = top_token ? ISVREF(top_token,(SI_Long)1L) : Qnil;
	  action = lr_action(CAR(Current_state_stack),ip);
	  temp = CAR(action);
	  if (EQ(temp,Qaccept)) {
	      token_pop_store = Nil;
	      cons_1 = Current_token_stack;
	      if (cons_1) {
		  token_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qtoken);
		  if (ISVREF(Available_token_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_1 = ISVREF(Available_token_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_1) = cons_1;
		      temp_1 = Available_token_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = cons_1;
		  }
		  else {
		      temp_1 = Available_token_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = cons_1;
		      temp_1 = Available_token_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Current_token_stack = next_cons;
	      answer_token = token_pop_store;
	      return_value = ISVREF(answer_token,(SI_Long)4L);
	      reclaim_parse_object_1(answer_token);
	      reclaim_token_list_1(Current_state_stack);
	      reclaim_token_list_1(Current_token_stack);
	      reclaim_token_list_1(Current_input_stack);
	      temp = return_value;
	      goto end_1;
	  }
	  else if (EQ(temp,Qshift))
	      lr_shift(CADR(action),top_token);
	  else if (EQ(temp,Qab_reduce))
	      lr_reduce(CADR(action));
	  else {
	      reclaim_token_list_1(Current_state_stack);
	      reclaim_token_list_1(Current_token_stack);
	      reclaim_token_list_1(Current_input_stack);
	      temp = Nil;
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp = Qnil;
	end_1:;
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Regexp_preprocessing_parser, Qregexp_preprocessing_parser);

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

/* TWRITE-REPLACEMENT-FOR-TOKENIZER-VARIABLE */
Object twrite_replacement_for_tokenizer_variable(source_string,
	    start_position,end_position)
    Object source_string, start_position, end_position;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object end_1, temp, char_1, char_to_write_qm, temp_1, code, temp_2;
    Object aref_arg_2_1, variable_name, replacement_for_pattern;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    Declare_special(5);

    x_note_fn_call(78,61);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      end_1 = end_position;
	      if (end_1);
	      else {
		  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_string));
		  end_1 = FIX(UBYTE_16_ISAREF_1(source_string,length_1 - 
			  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(source_string,
			  length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			  (SI_Long)16L));
	      }
	      temp = start_position;
	      if (temp);
	      else
		  temp = FIX((SI_Long)0L);
	      i = IFIX(temp);
	      char_1 = Nil;
	      char_to_write_qm = Nil;
	    next_loop:
	      if ( !(i < IFIX(end_1)))
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(source_string,i));
	      if (IFIX(char_1) == (SI_Long)64L) {
		  i = i + (SI_Long)1L;
		  temp_1 = FIX(i);
		  temp = end_position;
		  if (temp);
		  else {
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_string));
		      temp = FIX(UBYTE_16_ISAREF_1(source_string,length_1 
			      - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(source_string,length_1 - 
			      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  }
		  char_to_write_qm =  !NUM_EQ(temp_1,temp) ? 
			  FIX(UBYTE_16_ISAREF_1(source_string,i)) : Nil;
	      }
	      else {
		  code = char_1;
		  if (IFIX(code) < (SI_Long)127L)
		      char_to_write_qm = (SI_Long)97L <= IFIX(code) && 
			      IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) 
			      + (SI_Long)-32L) : code;
		  else {
		      temp = unicode_uppercase_if_lowercase(code);
		      if (temp);
		      else
			  temp = code;
		      char_to_write_qm = temp;
		  }
	      }
	      if (char_to_write_qm) {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			  Total_length_of_current_wide_string))
		      extend_current_wide_string(Fill_pointer_for_current_wide_string);
		  temp_2 = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),
			  IFIX(char_to_write_qm));
		  temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		  Fill_pointer_for_current_wide_string = temp_2;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    variable_name = intern_wide_string(1,temp);
    temp = assq_function(variable_name,Current_lexing_strings);
    replacement_for_pattern = CDR(temp);
    if ( !TRUEP(replacement_for_pattern)) {
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
	Preprocessor_errors_qm = token_cons_1(token_list_2(variable_name,
		Qvariable),Preprocessor_errors_qm);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp_2 = Current_wide_string;
	aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),(SI_Long)40L);
	temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp_2;
	twrite(replacement_for_pattern);
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp_2 = Current_wide_string;
	aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),(SI_Long)41L);
	temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp_2;
    }
    return VALUES_1(Nil);
}

static Object Qbuilt_in;           /* built-in */

/* TWRITE-REPLACEMENT-FOR-BUILT-IN-CHARACTER-CLASS */
Object twrite_replacement_for_built_in_character_class(source_string,
	    start_position,end_position)
    Object source_string, start_position, end_position;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object end_1, temp, char_1, char_to_write_qm, temp_1, code, temp_2;
    Object aref_arg_2_1, class_name, replacement_for_pattern;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    Declare_special(5);

    x_note_fn_call(78,62);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      end_1 = end_position;
	      if (end_1);
	      else {
		  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_string));
		  end_1 = FIX(UBYTE_16_ISAREF_1(source_string,length_1 - 
			  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(source_string,
			  length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			  (SI_Long)16L));
	      }
	      temp = start_position;
	      if (temp);
	      else
		  temp = FIX((SI_Long)0L);
	      i = IFIX(temp);
	      char_1 = Nil;
	      char_to_write_qm = Nil;
	    next_loop:
	      if ( !(i < IFIX(end_1)))
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(source_string,i));
	      if (IFIX(char_1) == (SI_Long)64L) {
		  i = i + (SI_Long)1L;
		  temp_1 = FIX(i);
		  temp = end_position;
		  if (temp);
		  else {
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_string));
		      temp = FIX(UBYTE_16_ISAREF_1(source_string,length_1 
			      - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(source_string,length_1 - 
			      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  }
		  char_to_write_qm =  !NUM_EQ(temp_1,temp) ? 
			  FIX(UBYTE_16_ISAREF_1(source_string,i)) : Nil;
	      }
	      else {
		  code = char_1;
		  if (IFIX(code) < (SI_Long)127L)
		      char_to_write_qm = (SI_Long)97L <= IFIX(code) && 
			      IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) 
			      + (SI_Long)-32L) : code;
		  else {
		      temp = unicode_uppercase_if_lowercase(code);
		      if (temp);
		      else
			  temp = code;
		      char_to_write_qm = temp;
		  }
	      }
	      if (char_to_write_qm) {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			  Total_length_of_current_wide_string))
		      extend_current_wide_string(Fill_pointer_for_current_wide_string);
		  temp_2 = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),
			  IFIX(char_to_write_qm));
		  temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		  Fill_pointer_for_current_wide_string = temp_2;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    class_name = intern_wide_string(1,temp);
    temp = assq_function(class_name,Built_in_character_codes);
    replacement_for_pattern = CDR(temp);
    if ( !TRUEP(replacement_for_pattern)) {
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
	Preprocessor_errors_qm = token_cons_1(token_list_2(class_name,
		Qbuilt_in),Preprocessor_errors_qm);
    }
    else
	twrite(replacement_for_pattern);
    return VALUES_1(Nil);
}

static Object Qcharacter_class;    /* character-class */

/* REGEXP-STRING-PREPROCESSOR-ERRORS? */
Object regexp_string_preprocessor_errors_qm(source_string,include_variables_p)
    Object source_string, include_variables_p;
{
    Object source_index, preprocessor_errors_qm, next_token, end_position;
    Object start_position, token_first_char, temp;
    SI_Long length_1;
    Declare_special(1);

    x_note_fn_call(78,63);
    source_index = FIX((SI_Long)0L);
    preprocessor_errors_qm = Qnil;
    PUSH_SPECIAL_WITH_SYMBOL(Preprocessor_errors_qm,Qpreprocessor_errors_qm,preprocessor_errors_qm,
	    0);
      next_token = Nil;
      end_position = Nil;
      start_position = Nil;
      token_first_char = Nil;
    next_loop:
      next_token = INLINE_UNSIGNED_BYTE_16_VECTOR_P(source_string) != 
	      (SI_Long)0L ? 
	      get_next_token_from_text_string_1(source_string,source_index,
	      Nil) : Qnil;
      end_position = ISVREF(next_token,(SI_Long)3L);
      if (FIXNUM_EQ(No_tokenizer_match_end_index,end_position))
	  goto end_loop;
      start_position = ISVREF(next_token,(SI_Long)2L);
      token_first_char = FIX(UBYTE_16_ISAREF_1(source_string,
	      IFIX(source_index)));
      twrite_portion_of_wide_string_unparsably_to_current_wide_string(source_string,
	      source_index,start_position);
      temp = ISVREF(next_token,(SI_Long)1L);
      if (EQ(temp,Qvariable)) {
	  if (include_variables_p)
	      twrite_replacement_for_tokenizer_variable(source_string,
		      FIX((SI_Long)2L + IFIX(start_position)),
		      FIXNUM_SUB1(end_position));
	  else
	      twrite_portion_of_wide_string_unparsably_to_current_wide_string(source_string,
		      start_position,end_position);
      }
      else if (EQ(temp,Qbuilt_in))
	  twrite_replacement_for_built_in_character_class(source_string,
		  FIXNUM_ADD1(start_position),FIXNUM_SUB1(end_position));
      else if (EQ(temp,Qcharacter_class))
	  twrite_portion_of_wide_string_unparsably_to_current_wide_string(source_string,
		  start_position,end_position);
      else
	  twrite_portion_of_wide_string_unparsably_to_current_wide_string(source_string,
		  start_position,end_position);
      reclaim_parse_object_1(next_token);
      source_index = end_position;
      goto next_loop;
    end_loop:
      reclaim_parse_object_1(next_token);
      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_string));
      twrite_portion_of_wide_string_unparsably_to_current_wide_string(source_string,
	      source_index,FIX(UBYTE_16_ISAREF_1(source_string,length_1 - 
	      (SI_Long)2L) + ((UBYTE_16_ISAREF_1(source_string,length_1 - 
	      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)));
      temp = Preprocessor_errors_qm;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* PREPROCESS-REGEXP-STRING */
Object preprocess_regexp_string(source_string,include_variables_p)
    Object source_string, include_variables_p;
{
    Object current_tokenizer, current_start_state, current_anchor_p, errors_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object preprocessed_string, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(9);

    x_note_fn_call(78,64);
    current_tokenizer = Preprocessing_tokenizer;
    PUSH_SPECIAL_WITH_SYMBOL(Current_tokenizer,Qcurrent_tokenizer,current_tokenizer,
	    8);
      current_start_state = ISVREF(Current_tokenizer,(SI_Long)1L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_start_state,Qcurrent_start_state,current_start_state,
	      7);
	current_anchor_p = ISVREF(Current_tokenizer,(SI_Long)3L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_anchor_p,Qcurrent_anchor_p,current_anchor_p,
		6);
	  current_anchor_p = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_anchor_p,Qcurrent_anchor_p,current_anchor_p,
		  5);
	    errors_qm = Nil;
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
		      (SI_Long)3L));
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	      current_wide_string = wide_string_bv16;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		      3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      errors_qm = 
			      regexp_string_preprocessor_errors_qm(source_string,
			      include_variables_p);
		      preprocessed_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    if ( !TRUEP(errors_qm))
		temp = preprocessed_string;
	    else {
		reclaim_wide_string(preprocessed_string);
		temp = nreverse(errors_qm);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* MOVE-TO-TOP-OF-REGEXP-CACHE */
Object move_to_top_of_regexp_cache(item)
    Object item;
{
    Object pointer, temp, svref_arg_1, temp_1;
    SI_Long index_1;

    x_note_fn_call(78,65);
    index_1 = (SI_Long)0L;
    pointer = ISVREF(Cache_of_regular_expressions,index_1);
  next_loop:
    if ( !TRUEP(pointer) || string_eq_w(CAR(pointer),item))
	goto end_loop;
    if (index_1 < IFIX(Max_number_of_regexps_to_cache)) {
	temp = ISVREF(Cache_of_regular_expressions,index_1);
	svref_arg_1 = Cache_of_regular_expressions;
	ISVREF(svref_arg_1,index_1) = pointer;
	pointer = temp;
    }
    else {
	reclaim_wide_string(CAR(pointer));
	reclaim_token_tree_1(pointer);
	pointer = Nil;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    svref_arg_1 = Cache_of_regular_expressions;
    SVREF(svref_arg_1,FIX((SI_Long)0L)) = pointer;
    temp_1 = pointer;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_lexing_tables_in_cache, Qnumber_of_lexing_tables_in_cache);

Object Tail_of_lexing_table_cache_marker = UNBOUND;

Object Cache_of_lexing_tables = UNBOUND;

/* CLEAR-LEXING-TABLE-CACHE */
Object clear_lexing_table_cache()
{
    Object i, ab_loop_list_;

    x_note_fn_call(78,66);
    i = Nil;
    ab_loop_list_ = Cache_of_lexing_tables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    i = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(i,Tail_of_lexing_table_cache_marker))
	goto end_loop;
    reclaim_wide_string(M_CAR(i));
    reclaim_dfa(M_CDR(i));
    reclaim_token_cons_1(i);
    goto next_loop;
  end_loop:
    Number_of_lexing_tables_in_cache = FIX((SI_Long)0L);
    reclaim_token_list_1(Cache_of_lexing_tables);
    Cache_of_lexing_tables = 
	    token_cons_1(Tail_of_lexing_table_cache_marker,Nil);
    return VALUES_1(Nil);
}

/* GET-LEXING-TABLE-FROM-CACHE */
Object get_lexing_table_from_cache(text_string)
    Object text_string;
{
    Object pointer, ab_loop_list_, temp;

    x_note_fn_call(78,67);
    pointer = Nil;
    ab_loop_list_ = Cache_of_lexing_tables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pointer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(pointer,Tail_of_lexing_table_cache_marker) || 
	    string_eq_w(M_CAR(pointer),text_string))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp = M_CDR(pointer);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* ADD-LEXING-TABLE-TO-CACHE */
Object add_lexing_table_to_cache(text_string,lexing_table)
    Object text_string, lexing_table;
{
    Object temp, number_of_lexing_tables_in_cache_new_value;

    x_note_fn_call(78,68);
    if (FIXNUM_GE(Number_of_lexing_tables_in_cache,
	    Max_number_of_lexing_tables_to_cache))
	clear_lexing_table_cache();
    temp = token_cons_1(copy_text_string(text_string),lexing_table);
    Cache_of_lexing_tables = token_cons_1(temp,Cache_of_lexing_tables);
    number_of_lexing_tables_in_cache_new_value = 
	    FIXNUM_ADD1(Number_of_lexing_tables_in_cache);
    Number_of_lexing_tables_in_cache = 
	    number_of_lexing_tables_in_cache_new_value;
    return VALUES_1(lexing_table);
}

static Object Qgoal;               /* goal */

/* GET-LEXING-TABLE-FOR-REGEXP */
Object get_lexing_table_for_regexp(search_pattern)
    Object search_pattern;
{
    Object temp, preprocessed_string_or_errors, regexp_parse;
    Object tokenizer_definition, lexing_table_for_regexp;

    x_note_fn_call(78,69);
    temp = get_lexing_table_from_cache(search_pattern);
    if (temp);
    else {
	preprocessed_string_or_errors = 
		preprocess_regexp_string(search_pattern,Nil);
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(preprocessed_string_or_errors) 
		!= (SI_Long)0L) {
	    temp = parse_regexp_string(preprocessed_string_or_errors);
	    reclaim_wide_string(preprocessed_string_or_errors);
	    preprocessed_string_or_errors = Nil;
	    regexp_parse = temp;
	}
	else
	    regexp_parse = Nil;
	if (regexp_parse) {
	    tokenizer_definition = token_list_2(Nil,token_list_2(Qgoal,
		    regexp_parse));
	    lexing_table_for_regexp = 
		    compile_lexing_table(tokenizer_definition);
	    reclaim_token_cons_1(CDADR(tokenizer_definition));
	    reclaim_token_cons_1(M_CAR(CDR(tokenizer_definition)));
	    reclaim_token_cons_1(CDR(tokenizer_definition));
	    reclaim_token_cons_1(tokenizer_definition);
	    temp = add_lexing_table_to_cache(search_pattern,
		    lexing_table_for_regexp);
	}
	else
	    temp = preprocessed_string_or_errors;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Regular_expression_parser, Qregular_expression_parser);

/* STACK-OF-REGEXP-TOKENS */
Object stack_of_regexp_tokens(string_1)
    Object string_1;
{
    Object stack, current_index_qm, next_token, next_lexeme, temp;

    x_note_fn_call(78,70);
    stack = Qnil;
    current_index_qm = FIX((SI_Long)0L);
    next_token = Nil;
    next_lexeme = Nil;
  next_loop:
    if ( !TRUEP(current_index_qm))
	goto end_loop;
    next_token = INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L 
	    ? get_next_token_from_text_string_1(string_1,current_index_qm,
	    Nil) : Qnil;
    next_lexeme = regular_expression_lexeme(string_1,next_token);
    if (next_lexeme) {
	SVREF(next_token,FIX((SI_Long)4L)) = next_lexeme;
	current_index_qm = ISVREF(next_token,(SI_Long)3L);
	stack = token_cons_1(next_token,stack);
    }
    else {
	reclaim_parse_object_1(next_token);
	current_index_qm = Nil;
    }
    goto next_loop;
  end_loop:
    temp = stack;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* PARSE-UNKNOWN-REGEXP-STRING */
Object parse_unknown_regexp_string(expression)
    Object expression;
{
    Object current_productions, current_lr_states, current_nonterminals;
    Object current_terminals, current_parse_table, stack_of_tokens;
    Object stack_of_tokens_1, result_1, temp;
    Declare_special(5);

    x_note_fn_call(78,71);
    current_productions = ISVREF(Regular_expression_parser,(SI_Long)3L);
    current_lr_states = ISVREF(Regular_expression_parser,(SI_Long)4L);
    current_nonterminals = ISVREF(Regular_expression_parser,(SI_Long)1L);
    current_terminals = ISVREF(Regular_expression_parser,(SI_Long)2L);
    current_parse_table = Regular_expression_parser;
    PUSH_SPECIAL_WITH_SYMBOL(Current_parse_table,Qcurrent_parse_table,current_parse_table,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Current_terminals,Qcurrent_terminals,current_terminals,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Current_nonterminals,Qcurrent_nonterminals,current_nonterminals,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_lr_states,Qcurrent_lr_states,current_lr_states,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_productions,Qcurrent_productions,current_productions,
		    0);
	      stack_of_tokens = stack_of_regexp_tokens(expression);
	      stack_of_tokens_1 = stack_of_tokens;
	      result_1 =  !TRUEP(stack_of_tokens_1) ? Nil : 
		      lr_parse_1(stack_of_tokens_1);
	      reclaim_token_tree_1(stack_of_tokens);
	      temp = result_1;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* PARSE-REGEXP-STRING */
Object parse_regexp_string(wide_string)
    Object wide_string;
{
    Object lookup, new_string, parsed_string, svref_arg_1;

    x_note_fn_call(78,72);
    lookup = move_to_top_of_regexp_cache(wide_string);
    if ( !TRUEP(lookup)) {
	new_string = copy_wide_string(wide_string);
	parsed_string = parse_unknown_regexp_string(wide_string);
	lookup = token_list_2(new_string,parsed_string);
	svref_arg_1 = Cache_of_regular_expressions;
	SVREF(svref_arg_1,FIX((SI_Long)0L)) = lookup;
    }
    return VALUES_1(CADR(lookup));
}

static Object Qself_terminating_punctuation_mark;  /* self-terminating-punctuation-mark */

static Object Qpunctuation_mark;   /* punctuation-mark */

static Object Qdo_nothing;         /* do-nothing */

/* PARTIAL-TOKENS-FOR-STATE */
Object partial_tokens_for_state(associated_rules_on_last_state)
    Object associated_rules_on_last_state;
{
    Object token_number, ab_loop_list_, probably_token_symbol, token_symbol;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(78,73);
    token_number = Nil;
    ab_loop_list_ = associated_rules_on_last_state;
    probably_token_symbol = Nil;
    token_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    token_number = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    probably_token_symbol = ISVREF(ISVREF(ISVREF(Current_tokenizer,
	    (SI_Long)2L),IFIX(token_number)),(SI_Long)1L);
    token_symbol = EQ(probably_token_symbol,
	    Qself_terminating_punctuation_mark) ? Qpunctuation_mark : 
	    probably_token_symbol;
    if ( !EQ(token_symbol,Qdo_nothing)) {
	ab_loopvar__2 = phrase_cons(token_symbol,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* G2-USE-TOKENIZER-INTERNAL */
Object g2_use_tokenizer_internal(type)
    Object type;
{
    SI_Long a, b, c;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(78,74);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	a = (SI_Long)12L;
	b = (SI_Long)14L;
	c = (SI_Long)10L;
	result = l_round(divide(ltimes(FIX(a),FIX(b)),FIX(c)),_);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

void parse2_INIT()
{
    Object gensymed_symbol, the_array, temp;
    Object reclaim_structure_for_production_1;
    Object reclaim_structure_for_possible_phrase_1;
    Object reclaim_structure_for_set_of_possible_phrases_1;
    Object reclaim_structure_for_parse_table_1;
    SI_Long i, ab_loop_bind_;
    Object Qg2_use_tokenizer_internal;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object list_constant_108, list_constant_107, list_constant_106;
    Object list_constant_105, list_constant_104, list_constant_103;
    Object list_constant_102, list_constant_101, list_constant_100;
    Object list_constant_99, list_constant_98, list_constant_97;
    Object list_constant_96, list_constant_95, list_constant_94;
    Object list_constant_93, list_constant_92, list_constant_91;
    Object list_constant_90, list_constant_89, list_constant_88;
    Object list_constant_87, list_constant_86, list_constant_85;
    Object list_constant_84, list_constant_83, list_constant_82;
    Object list_constant_81, list_constant_80, list_constant_79;
    Object list_constant_78, Qchar_sequence, list_constant_61, Qhyphen;
    Object Qregexp_character, list_constant_62, Qrange_element;
    Object list_constant_77, list_constant_6, list_constant_76, Qrange;
    Object list_constant_3, list_constant_75, list_constant_74;
    Object list_constant_73, list_constant_47, Qinverted_class;
    Object list_constant_69, Qcaret, Qleft_curly_brace, list_constant_42;
    Object list_constant_72, list_constant_64, list_constant_71;
    Object list_constant_70, list_constant_16, list_constant_68;
    Object Qbasic_regexp_block, Qnon_range_standard_character;
    Object list_constant_67, Qab_dot, list_constant_66, list_constant_9;
    Object list_constant_65, list_constant_12, Qexpression, Qleft_paren;
    Object Qright_curly_brace, list_constant_63, list_constant_60;
    Object list_constant_59, Qkleened_basic_block, list_constant_2, Qmaybe;
    Object Qquestion_mark, list_constant_58, list_constant_57, Qab_plus;
    Object list_constant_56, list_constant_55, Qkleene, Qkleene_star;
    Object list_constant_54, Qpossibly_kleened_basic_block, list_constant_53;
    Object list_constant_52, Qregexp_sequence, list_constant_51;
    Object list_constant_50, Qseq, list_constant_1, Qalternatives;
    Object list_constant_49, list_constant_48, Qeither, list_constant_46;
    Object Qalternative, list_constant_45, list_constant_44;
    Object Qregexp_expression, Qanchor, list_constant_43, Qright_paren;
    Object list_constant_41, list_constant_40, list_constant_39;
    Object list_constant_38, list_constant_37, list_constant_36;
    Object list_constant_35, list_constant_34, list_constant_33;
    Object list_constant_32, list_constant_31, list_constant_30;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18, Qdollar_sign;
    Object list_constant_8, Qless_than, list_constant_7, list_constant;
    Object list_constant_17, Qcharacters, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_11, list_constant_10;
    Object Qab_built_in_class, Qgreater_than, Qbasic_block, Qother_character;
    Object list_constant_5, list_constant_4, Qpreprocessed_string;
    Object Qparse_table, Qreclaim_structure, Qoutstanding_parse_table_count;
    Object Qparse_table_structure_memory_usage, Qutilities2, string_constant_7;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_6, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qset_of_possible_phrases;
    Object Qoutstanding_set_of_possible_phrases_count;
    Object Qset_of_possible_phrases_structure_memory_usage, string_constant_5;
    Object string_constant_4, Qpossible_phrase;
    Object Qoutstanding_possible_phrase_count;
    Object Qpossible_phrase_structure_memory_usage, string_constant_3;
    Object string_constant_2, Qproduction, Qoutstanding_production_count;
    Object Qproduction_structure_memory_usage, string_constant_1;
    Object string_constant;

    x_note_fn_call(78,75);
    SET_PACKAGE("AB");
    gensymed_symbol = Max_number_of_regexps_to_cache;
    the_array = make_array(1,gensymed_symbol);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(gensymed_symbol);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ISVREF(the_array,i) = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    Cache_of_regular_expressions = the_array;
    if (Current_state_stack == UNBOUND)
	Current_state_stack = Qnil;
    if (Current_token_stack == UNBOUND)
	Current_token_stack = Qnil;
    if (Current_input_stack == UNBOUND)
	Current_input_stack = Qnil;
    if (Current_lr_states == UNBOUND)
	Current_lr_states = Nil;
    if (Current_nonterminals == UNBOUND)
	Current_nonterminals = Qnil;
    if (Current_parse_table == UNBOUND)
	Current_parse_table = Nil;
    if (Current_productions == UNBOUND)
	Current_productions = Nil;
    if (Current_terminals == UNBOUND)
	Current_terminals = Qnil;
    if (Lr0_follow == UNBOUND)
	Lr0_follow = Qnil;
    if (Preprocessor_errors_qm == UNBOUND)
	Preprocessor_errors_qm = Qnil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_production_g2_struct = 
	    STATIC_SYMBOL("PRODUCTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qproduction = STATIC_SYMBOL("PRODUCTION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_production_g2_struct,
	    Qproduction,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qproduction,
	    Qg2_defstruct_structure_name_production_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_production == UNBOUND)
	The_type_description_of_production = Nil;
    string_constant = STATIC_STRING("43Dy8m83lky1n83lky8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_production;
    The_type_description_of_production = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_production_g2_struct,
	    The_type_description_of_production,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qproduction,The_type_description_of_production,
	    Qtype_description_of_type);
    Qoutstanding_production_count = 
	    STATIC_SYMBOL("OUTSTANDING-PRODUCTION-COUNT",AB_package);
    Qproduction_structure_memory_usage = 
	    STATIC_SYMBOL("PRODUCTION-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_1 = STATIC_STRING("1q83lky8s83-kVy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_production_count);
    push_optimized_constant(Qproduction_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_productions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PRODUCTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_productions,
	    Chain_of_available_productions);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_productions,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qproduction_count = STATIC_SYMBOL("PRODUCTION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qproduction_count,Production_count);
    record_system_variable(Qproduction_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_productions_vector == UNBOUND)
	Chain_of_available_productions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qproduction_structure_memory_usage,
	    STATIC_FUNCTION(production_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_production_count,
	    STATIC_FUNCTION(outstanding_production_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_production_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_production,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qproduction,
	    reclaim_structure_for_production_1);
    Qg2_defstruct_structure_name_possible_phrase_g2_struct = 
	    STATIC_SYMBOL("POSSIBLE-PHRASE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpossible_phrase = STATIC_SYMBOL("POSSIBLE-PHRASE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_possible_phrase_g2_struct,
	    Qpossible_phrase,Qab_name_of_unique_structure_type);
    mutate_global_property(Qpossible_phrase,
	    Qg2_defstruct_structure_name_possible_phrase_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_possible_phrase == UNBOUND)
	The_type_description_of_possible_phrase = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8m83ley1n83ley8n8k1l8n0000000knk0k0");
    temp = The_type_description_of_possible_phrase;
    The_type_description_of_possible_phrase = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_2));
    mutate_global_property(Qg2_defstruct_structure_name_possible_phrase_g2_struct,
	    The_type_description_of_possible_phrase,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qpossible_phrase,
	    The_type_description_of_possible_phrase,Qtype_description_of_type);
    Qoutstanding_possible_phrase_count = 
	    STATIC_SYMBOL("OUTSTANDING-POSSIBLE-PHRASE-COUNT",AB_package);
    Qpossible_phrase_structure_memory_usage = 
	    STATIC_SYMBOL("POSSIBLE-PHRASE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_3 = STATIC_STRING("1q83ley8s83-jTy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_possible_phrase_count);
    push_optimized_constant(Qpossible_phrase_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_possible_phrases = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-POSSIBLE-PHRASES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_possible_phrases,
	    Chain_of_available_possible_phrases);
    record_system_variable(Qchain_of_available_possible_phrases,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qpossible_phrase_count = STATIC_SYMBOL("POSSIBLE-PHRASE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpossible_phrase_count,Possible_phrase_count);
    record_system_variable(Qpossible_phrase_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_possible_phrases_vector == UNBOUND)
	Chain_of_available_possible_phrases_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qpossible_phrase_structure_memory_usage,
	    STATIC_FUNCTION(possible_phrase_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_possible_phrase_count,
	    STATIC_FUNCTION(outstanding_possible_phrase_count,NIL,FALSE,0,0));
    reclaim_structure_for_possible_phrase_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_possible_phrase,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qpossible_phrase,
	    reclaim_structure_for_possible_phrase_1);
    Qg2_defstruct_structure_name_set_of_possible_phrases_g2_struct = 
	    STATIC_SYMBOL("SET-OF-POSSIBLE-PHRASES-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qset_of_possible_phrases = STATIC_SYMBOL("SET-OF-POSSIBLE-PHRASES",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_set_of_possible_phrases_g2_struct,
	    Qset_of_possible_phrases,Qab_name_of_unique_structure_type);
    mutate_global_property(Qset_of_possible_phrases,
	    Qg2_defstruct_structure_name_set_of_possible_phrases_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_set_of_possible_phrases == UNBOUND)
	The_type_description_of_set_of_possible_phrases = Nil;
    string_constant_4 = 
	    STATIC_STRING("43Dy8m83mmy1n83mmy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_set_of_possible_phrases;
    The_type_description_of_set_of_possible_phrases = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_4));
    mutate_global_property(Qg2_defstruct_structure_name_set_of_possible_phrases_g2_struct,
	    The_type_description_of_set_of_possible_phrases,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qset_of_possible_phrases,
	    The_type_description_of_set_of_possible_phrases,
	    Qtype_description_of_type);
    Qoutstanding_set_of_possible_phrases_count = 
	    STATIC_SYMBOL("OUTSTANDING-SET-OF-POSSIBLE-PHRASES-COUNT",
	    AB_package);
    Qset_of_possible_phrases_structure_memory_usage = 
	    STATIC_SYMBOL("SET-OF-POSSIBLE-PHRASES-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_5 = STATIC_STRING("1q83mmy8s83-oSy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_set_of_possible_phrases_count);
    push_optimized_constant(Qset_of_possible_phrases_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
    Qchain_of_available_set_of_possible_phrasess = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SET-OF-POSSIBLE-PHRASESS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_set_of_possible_phrasess,
	    Chain_of_available_set_of_possible_phrasess);
    record_system_variable(Qchain_of_available_set_of_possible_phrasess,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qset_of_possible_phrases_count = 
	    STATIC_SYMBOL("SET-OF-POSSIBLE-PHRASES-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qset_of_possible_phrases_count,
	    Set_of_possible_phrases_count);
    record_system_variable(Qset_of_possible_phrases_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_set_of_possible_phrasess_vector == UNBOUND)
	Chain_of_available_set_of_possible_phrasess_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qset_of_possible_phrases_structure_memory_usage,
	    STATIC_FUNCTION(set_of_possible_phrases_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_set_of_possible_phrases_count,
	    STATIC_FUNCTION(outstanding_set_of_possible_phrases_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_set_of_possible_phrases_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_set_of_possible_phrases,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qset_of_possible_phrases,
	    reclaim_structure_for_set_of_possible_phrases_1);
    Qg2_defstruct_structure_name_parse_table_g2_struct = 
	    STATIC_SYMBOL("PARSE-TABLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qparse_table = STATIC_SYMBOL("PARSE-TABLE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_parse_table_g2_struct,
	    Qparse_table,Qab_name_of_unique_structure_type);
    mutate_global_property(Qparse_table,
	    Qg2_defstruct_structure_name_parse_table_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_parse_table == UNBOUND)
	The_type_description_of_parse_table = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8m83lOy1n83lOy8n8k1l8n0000000kpk0k0");
    temp = The_type_description_of_parse_table;
    The_type_description_of_parse_table = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
    mutate_global_property(Qg2_defstruct_structure_name_parse_table_g2_struct,
	    The_type_description_of_parse_table,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qparse_table,
	    The_type_description_of_parse_table,Qtype_description_of_type);
    Qoutstanding_parse_table_count = 
	    STATIC_SYMBOL("OUTSTANDING-PARSE-TABLE-COUNT",AB_package);
    Qparse_table_structure_memory_usage = 
	    STATIC_SYMBOL("PARSE-TABLE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_7 = STATIC_STRING("1q83lOy8s83-iMy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_parse_table_count);
    push_optimized_constant(Qparse_table_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
    Qchain_of_available_parse_tables = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PARSE-TABLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_parse_tables,
	    Chain_of_available_parse_tables);
    record_system_variable(Qchain_of_available_parse_tables,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qparse_table_count = STATIC_SYMBOL("PARSE-TABLE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qparse_table_count,Parse_table_count);
    record_system_variable(Qparse_table_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_parse_tables_vector == UNBOUND)
	Chain_of_available_parse_tables_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qparse_table_structure_memory_usage,
	    STATIC_FUNCTION(parse_table_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_parse_table_count,
	    STATIC_FUNCTION(outstanding_parse_table_count,NIL,FALSE,0,0));
    reclaim_structure_for_parse_table_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_parse_table,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qparse_table,
	    reclaim_structure_for_parse_table_1);
    Qtoken = STATIC_SYMBOL("TOKEN",AB_package);
    Qshift = STATIC_SYMBOL("SHIFT",AB_package);
    Qaccept = STATIC_SYMBOL("ACCEPT",AB_package);
    Qab_reduce = STATIC_SYMBOL("REDUCE",AB_package);
    Preprocessing_tokenizer = 
	    compile_permanent_lexing_table(Regexp_macro_tokens);
    Qleft_curly_brace = STATIC_SYMBOL("LEFT-CURLY-BRACE",AB_package);
    Qright_curly_brace = STATIC_SYMBOL("RIGHT-CURLY-BRACE",AB_package);
    Qleft_paren = STATIC_SYMBOL("LEFT-PAREN",AB_package);
    Qright_paren = STATIC_SYMBOL("RIGHT-PAREN",AB_package);
    Qdollar_sign = STATIC_SYMBOL("DOLLAR-SIGN",AB_package);
    Qgreater_than = STATIC_SYMBOL("GREATER-THAN",AB_package);
    Qless_than = STATIC_SYMBOL("LESS-THAN",AB_package);
    Qother_character = STATIC_SYMBOL("OTHER-CHARACTER",AB_package);
    list_constant = STATIC_CONS(Qsymbol,Qnil);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)9L,Qleft_curly_brace,
	    Qright_curly_brace,Qleft_paren,Qright_paren,Qdollar_sign,
	    Qgreater_than,Qless_than,Qother_character,list_constant);
    Qpreprocessed_string = STATIC_SYMBOL("PREPROCESSED-STRING",AB_package);
    Qregexp_sequence = STATIC_SYMBOL("REGEXP-SEQUENCE",AB_package);
    list_constant_1 = STATIC_CONS(Qregexp_sequence,Qnil);
    list_constant_19 = STATIC_CONS(Qpreprocessed_string,list_constant_1);
    Qbasic_block = STATIC_SYMBOL("BASIC-BLOCK",AB_package);
    list_constant_2 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_3 = STATIC_CONS(list_constant_2,Qnil);
    list_constant_20 = STATIC_LIST_STAR((SI_Long)3L,Qregexp_sequence,
	    Qbasic_block,list_constant_3);
    list_constant_5 = STATIC_CONS(Qbasic_block,list_constant_1);
    list_constant_4 = STATIC_CONS(FIX((SI_Long)1L),FIX((SI_Long)2L));
    list_constant_6 = STATIC_CONS(list_constant_4,Qnil);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)3L,Qregexp_sequence,
	    list_constant_5,list_constant_6);
    Qab_built_in_class = STATIC_SYMBOL("BUILT-IN-CLASS",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qbasic_block,
	    Qab_built_in_class);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qbasic_block,Qvariable);
    Qcharacter_class = STATIC_SYMBOL("CHARACTER-CLASS",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qbasic_block,Qcharacter_class);
    list_constant_25 = STATIC_CONS(Qbasic_block,list_constant);
    list_constant_7 = STATIC_CONS(Qother_character,Qnil);
    list_constant_26 = STATIC_CONS(Qbasic_block,list_constant_7);
    list_constant_8 = STATIC_CONS(Qgreater_than,Qnil);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)3L,Qless_than,Qsymbol,
	    list_constant_8);
    Qbuilt_in = STATIC_SYMBOL("BUILT-IN",AB_package);
    list_constant_9 = STATIC_CONS(FIX((SI_Long)2L),Qnil);
    list_constant_11 = STATIC_CONS(Qbuilt_in,list_constant_9);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qab_built_in_class,
	    list_constant_10,list_constant_11);
    list_constant_12 = STATIC_CONS(Qright_paren,Qnil);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)4L,Qdollar_sign,
	    Qleft_paren,Qsymbol,list_constant_12);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qvariable,FIX((SI_Long)3L));
    list_constant_28 = STATIC_LIST((SI_Long)3L,Qvariable,list_constant_13,
	    list_constant_14);
    Qcharacters = STATIC_SYMBOL("CHARACTERS",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qleft_curly_brace,
	    Qcharacters,Qright_curly_brace);
    list_constant_16 = STATIC_CONS(Qcharacter_class,list_constant_9);
    list_constant_29 = STATIC_LIST((SI_Long)3L,Qcharacter_class,
	    list_constant_15,list_constant_16);
    list_constant_30 = STATIC_LIST_STAR((SI_Long)3L,Qcharacters,Qcharacter,
	    list_constant_3);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qcharacter,Qcharacters);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)3L,Qcharacters,
	    list_constant_17,list_constant_6);
    list_constant_32 = STATIC_CONS(Qcharacter,list_constant);
    list_constant_33 = STATIC_CONS(Qcharacter,list_constant_7);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qcharacter,Qless_than);
    list_constant_35 = STATIC_CONS(Qcharacter,list_constant_8);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qcharacter,Qleft_paren);
    list_constant_37 = STATIC_CONS(Qcharacter,list_constant_12);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qcharacter,Qleft_curly_brace);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qcharacter,Qdollar_sign);
    list_constant_40 = STATIC_LIST((SI_Long)22L,list_constant_18,
	    list_constant_19,list_constant_20,list_constant_21,
	    list_constant_22,list_constant_23,list_constant_24,
	    list_constant_25,list_constant_26,list_constant_27,
	    list_constant_28,list_constant_29,list_constant_30,
	    list_constant_31,list_constant_32,list_constant_33,
	    list_constant_34,list_constant_35,list_constant_36,
	    list_constant_37,list_constant_38,list_constant_39);
    Regexp_preprocessing_parser = compile_parsing_table(list_constant_40);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_41,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    if (Number_of_lexing_tables_in_cache == UNBOUND)
	Number_of_lexing_tables_in_cache = FIX((SI_Long)0L);
    list_constant_42 = STATIC_CONS(Qnil,Qnil);
    Tail_of_lexing_table_cache_marker = list_constant_42;
    Cache_of_lexing_tables = 
	    token_cons_1(Tail_of_lexing_table_cache_marker,Nil);
    Qgoal = STATIC_SYMBOL("GOAL",AB_package);
    Qregexp_character = STATIC_SYMBOL("REGEXP-CHARACTER",AB_package);
    Qhyphen = STATIC_SYMBOL("HYPHEN",AB_package);
    Qab_dot = STATIC_SYMBOL("DOT",AB_package);
    Qquestion_mark = STATIC_SYMBOL("QUESTION-MARK",AB_package);
    Qab_plus = STATIC_SYMBOL("PLUS",AB_package);
    Qkleene_star = STATIC_SYMBOL("KLEENE-STAR",AB_package);
    Qalternative = STATIC_SYMBOL("ALTERNATIVE",AB_package);
    Qcaret = STATIC_SYMBOL("CARET",AB_package);
    list_constant_80 = STATIC_LIST((SI_Long)12L,Qregexp_character,Qhyphen,
	    Qright_curly_brace,Qleft_curly_brace,Qab_dot,Qright_paren,
	    Qleft_paren,Qquestion_mark,Qab_plus,Qkleene_star,Qalternative,
	    Qcaret);
    Qregexp_expression = STATIC_SYMBOL("REGEXP-EXPRESSION",AB_package);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    list_constant_43 = STATIC_CONS(Qexpression,Qnil);
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qregexp_expression,
	    list_constant_43);
    list_constant_44 = STATIC_CONS(Qcaret,list_constant_43);
    Qanchor = STATIC_SYMBOL("ANCHOR",AB_package);
    list_constant_45 = STATIC_CONS(Qanchor,list_constant_9);
    list_constant_82 = STATIC_LIST((SI_Long)3L,Qregexp_expression,
	    list_constant_44,list_constant_45);
    Qalternatives = STATIC_SYMBOL("ALTERNATIVES",AB_package);
    list_constant_46 = STATIC_CONS(Qalternatives,Qnil);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qexpression,list_constant_46);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)3L,Qregexp_sequence,
	    Qalternative,list_constant_46);
    Qeither = STATIC_SYMBOL("EITHER",AB_package);
    list_constant_47 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)3L,Qeither,
	    FIX((SI_Long)1L),list_constant_47);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qalternatives,
	    list_constant_48,list_constant_49);
    list_constant_85 = STATIC_LIST((SI_Long)2L,Qalternatives,list_constant_1);
    Qpossibly_kleened_basic_block = 
	    STATIC_SYMBOL("POSSIBLY-KLEENED-BASIC-BLOCK",AB_package);
    list_constant_50 = STATIC_CONS(Qpossibly_kleened_basic_block,
	    list_constant_1);
    Qseq = STATIC_SYMBOL("SEQ",AB_package);
    list_constant_51 = STATIC_LIST_STAR((SI_Long)3L,Qseq,FIX((SI_Long)1L),
	    list_constant_9);
    list_constant_86 = STATIC_LIST((SI_Long)3L,Qregexp_sequence,
	    list_constant_50,list_constant_51);
    list_constant_52 = STATIC_CONS(Qpossibly_kleened_basic_block,Qnil);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Qregexp_sequence,
	    list_constant_52);
    Qbasic_regexp_block = STATIC_SYMBOL("BASIC-REGEXP-BLOCK",AB_package);
    list_constant_53 = STATIC_CONS(Qbasic_regexp_block,Qnil);
    list_constant_88 = STATIC_LIST((SI_Long)2L,
	    Qpossibly_kleened_basic_block,list_constant_53);
    Qkleened_basic_block = STATIC_SYMBOL("KLEENED-BASIC-BLOCK",AB_package);
    list_constant_54 = STATIC_CONS(Qkleened_basic_block,Qnil);
    list_constant_89 = STATIC_LIST((SI_Long)2L,
	    Qpossibly_kleened_basic_block,list_constant_54);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qbasic_regexp_block,
	    Qkleene_star);
    Qkleene = STATIC_SYMBOL("KLEENE",AB_package);
    list_constant_56 = STATIC_CONS(Qkleene,list_constant_2);
    list_constant_90 = STATIC_LIST((SI_Long)3L,Qkleened_basic_block,
	    list_constant_55,list_constant_56);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qbasic_regexp_block,Qab_plus);
    list_constant_58 = STATIC_CONS(Qab_plus,list_constant_2);
    list_constant_91 = STATIC_LIST((SI_Long)3L,Qkleened_basic_block,
	    list_constant_57,list_constant_58);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qbasic_regexp_block,
	    Qquestion_mark);
    Qmaybe = STATIC_SYMBOL("MAYBE",AB_package);
    list_constant_60 = STATIC_CONS(Qmaybe,list_constant_2);
    list_constant_92 = STATIC_LIST((SI_Long)3L,Qkleened_basic_block,
	    list_constant_59,list_constant_60);
    Qnon_range_standard_character = 
	    STATIC_SYMBOL("NON-RANGE-STANDARD-CHARACTER",AB_package);
    list_constant_61 = STATIC_CONS(Qregexp_character,Qnil);
    list_constant_62 = STATIC_CONS(list_constant_61,Qnil);
    list_constant_93 = STATIC_CONS(Qnon_range_standard_character,
	    list_constant_62);
    list_constant_63 = STATIC_CONS(Qhyphen,Qnil);
    list_constant_94 = STATIC_LIST((SI_Long)2L,
	    Qnon_range_standard_character,list_constant_63);
    list_constant_64 = STATIC_CONS(Qright_curly_brace,Qnil);
    list_constant_95 = STATIC_LIST((SI_Long)2L,
	    Qnon_range_standard_character,list_constant_64);
    list_constant_65 = STATIC_LIST_STAR((SI_Long)3L,Qleft_paren,
	    Qexpression,list_constant_12);
    list_constant_96 = STATIC_LIST_STAR((SI_Long)3L,Qbasic_regexp_block,
	    list_constant_65,list_constant_9);
    list_constant_66 = STATIC_CONS(Qcharacter_class,Qnil);
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qbasic_regexp_block,
	    list_constant_66);
    list_constant_67 = STATIC_CONS(Qab_dot,Qnil);
    list_constant_98 = STATIC_LIST((SI_Long)3L,Qbasic_regexp_block,
	    list_constant_67,list_constant_67);
    list_constant_68 = STATIC_CONS(Qnon_range_standard_character,Qnil);
    list_constant_99 = STATIC_LIST((SI_Long)2L,Qbasic_regexp_block,
	    list_constant_68);
    Qrange = STATIC_SYMBOL("RANGE",AB_package);
    list_constant_69 = STATIC_CONS(Qrange,list_constant_64);
    list_constant_70 = STATIC_CONS(Qleft_curly_brace,list_constant_69);
    list_constant_71 = STATIC_CONS(list_constant_16,Qnil);
    list_constant_100 = STATIC_LIST_STAR((SI_Long)3L,Qcharacter_class,
	    list_constant_70,list_constant_71);
    list_constant_72 = STATIC_CONS(Qleft_curly_brace,list_constant_64);
    list_constant_101 = STATIC_LIST((SI_Long)3L,Qcharacter_class,
	    list_constant_72,list_constant_42);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)3L,Qleft_curly_brace,
	    Qcaret,list_constant_69);
    Qinverted_class = STATIC_SYMBOL("INVERTED-CLASS",AB_package);
    list_constant_74 = STATIC_CONS(Qinverted_class,list_constant_47);
    list_constant_102 = STATIC_LIST((SI_Long)3L,Qcharacter_class,
	    list_constant_73,list_constant_74);
    Qrange_element = STATIC_SYMBOL("RANGE-ELEMENT",AB_package);
    list_constant_75 = STATIC_CONS(Qrange_element,Qnil);
    list_constant_103 = STATIC_LIST_STAR((SI_Long)3L,Qrange,
	    list_constant_75,list_constant_3);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qrange_element,Qrange);
    list_constant_104 = STATIC_LIST_STAR((SI_Long)3L,Qrange,
	    list_constant_76,list_constant_6);
    Qchar_sequence = STATIC_SYMBOL("CHAR-SEQUENCE",AB_package);
    list_constant_77 = STATIC_CONS(Qchar_sequence,Qnil);
    list_constant_105 = STATIC_LIST((SI_Long)2L,Qrange_element,
	    list_constant_77);
    list_constant_106 = STATIC_CONS(Qrange_element,list_constant_62);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)3L,Qregexp_character,
	    Qhyphen,list_constant_61);
    list_constant_79 = STATIC_CONS(FIX((SI_Long)1L),FIX((SI_Long)3L));
    list_constant_107 = STATIC_LIST((SI_Long)3L,Qchar_sequence,
	    list_constant_78,list_constant_79);
    list_constant_108 = STATIC_LIST((SI_Long)28L,list_constant_80,
	    list_constant_81,list_constant_82,list_constant_83,
	    list_constant_84,list_constant_85,list_constant_86,
	    list_constant_87,list_constant_88,list_constant_89,
	    list_constant_90,list_constant_91,list_constant_92,
	    list_constant_93,list_constant_94,list_constant_95,
	    list_constant_96,list_constant_97,list_constant_98,
	    list_constant_99,list_constant_100,list_constant_101,
	    list_constant_102,list_constant_103,list_constant_104,
	    list_constant_105,list_constant_106,list_constant_107);
    Regular_expression_parser = compile_parsing_table(list_constant_108);
    Qself_terminating_punctuation_mark = 
	    STATIC_SYMBOL("SELF-TERMINATING-PUNCTUATION-MARK",AB_package);
    Qpunctuation_mark = STATIC_SYMBOL("PUNCTUATION-MARK",AB_package);
    Qdo_nothing = STATIC_SYMBOL("DO-NOTHING",AB_package);
    Qg2_use_tokenizer_internal = STATIC_SYMBOL("G2-USE-TOKENIZER-INTERNAL",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_use_tokenizer_internal,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_use_tokenizer_internal,
	    STATIC_FUNCTION(g2_use_tokenizer_internal,NIL,FALSE,1,1));
}
