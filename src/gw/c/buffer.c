/* buffer.c
 * Input file:  buffer.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "buffer.h"


Object G2int_binding_cliches_prop = UNBOUND;

Object G2int_prefered_line_terminator = UNBOUND;

Object G2int_default_fragment_max = UNBOUND;

Object G2int_default_fragment_bit_size = UNBOUND;

Object G2int_the_type_description_of_rb_mark = UNBOUND;

Object G2int_chain_of_available_rb_marks = UNBOUND;

Object G2int_rb_mark_count = UNBOUND;

/* RECLAIM-RB-MARK-1 */
Object g2int_reclaim_rb_mark_1(rb_mark)
    Object rb_mark;
{
    Object svref_new_value;

    x_note_fn_call(54,0);
    inline_note_reclaim_cons(rb_mark,Nil);
    svref_new_value = G2int_chain_of_available_rb_marks;
    SVREF(rb_mark,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_rb_marks = rb_mark;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RB-MARK */
Object g2int_reclaim_structure_for_rb_mark(rb_mark)
    Object rb_mark;
{
    x_note_fn_call(54,1);
    return g2int_reclaim_rb_mark_1(rb_mark);
}

static Object Qg2_defstruct_structure_name_rb_mark_g2_struct;  /* g2-defstruct-structure-name::rb-mark-g2-struct */

/* MAKE-PERMANENT-RB-MARK-STRUCTURE-INTERNAL */
Object g2int_make_permanent_rb_mark_structure_internal()
{
    Object def_structure_rb_mark_variable, rb_mark_count_new_value;
    Object defstruct_g2_rb_mark_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(54,2);
    def_structure_rb_mark_variable = Nil;
    rb_mark_count_new_value = FIXNUM_ADD1(G2int_rb_mark_count);
    G2int_rb_mark_count = rb_mark_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_rb_mark_variable = Nil;
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
	defstruct_g2_rb_mark_variable = the_array;
	SVREF(defstruct_g2_rb_mark_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rb_mark_g2_struct;
	def_structure_rb_mark_variable = defstruct_g2_rb_mark_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_rb_mark_variable);
}

static Object Kforward;            /* :forward */

/* MAKE-RB-MARK-1 */
Object g2int_make_rb_mark_1()
{
    Object def_structure_rb_mark_variable;

    x_note_fn_call(54,3);
    def_structure_rb_mark_variable = G2int_chain_of_available_rb_marks;
    if (def_structure_rb_mark_variable) {
	G2int_chain_of_available_rb_marks = 
		ISVREF(def_structure_rb_mark_variable,(SI_Long)0L);
	SVREF(def_structure_rb_mark_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rb_mark_g2_struct;
    }
    else
	def_structure_rb_mark_variable = 
		g2int_make_permanent_rb_mark_structure_internal();
    inline_note_allocate_cons(def_structure_rb_mark_variable,Nil);
    SVREF(def_structure_rb_mark_variable,FIX((SI_Long)2L)) = Kforward;
    ISVREF(def_structure_rb_mark_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_rb_mark_variable);
}

Object G2int_the_type_description_of_rb_fragment = UNBOUND;

Object G2int_chain_of_available_rb_fragments = UNBOUND;

Object G2int_rb_fragment_count = UNBOUND;

/* RECLAIM-RB-FRAGMENT-1 */
Object g2int_reclaim_rb_fragment_1(rb_fragment)
    Object rb_fragment;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(54,4);
    inline_note_reclaim_cons(rb_fragment,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = rb_fragment;
    g2int_reclaim_rb_fragment_if_any(ISVREF(rb_fragment,(SI_Long)1L));
    SVREF(rb_fragment,FIX((SI_Long)1L)) = Nil;
    g2int_reclaim_gensym_string(ISVREF(rb_fragment,(SI_Long)2L));
    SVREF(rb_fragment,FIX((SI_Long)2L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_rb_fragments;
    SVREF(rb_fragment,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_rb_fragments = rb_fragment;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RB-FRAGMENT */
Object g2int_reclaim_structure_for_rb_fragment(rb_fragment)
    Object rb_fragment;
{
    x_note_fn_call(54,5);
    return g2int_reclaim_rb_fragment_1(rb_fragment);
}

static Object Qg2_defstruct_structure_name_rb_fragment_g2_struct;  /* g2-defstruct-structure-name::rb-fragment-g2-struct */

/* MAKE-PERMANENT-RB-FRAGMENT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_rb_fragment_structure_internal()
{
    Object def_structure_rb_fragment_variable, rb_fragment_count_new_value;
    Object defstruct_g2_rb_fragment_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(54,6);
    def_structure_rb_fragment_variable = Nil;
    rb_fragment_count_new_value = FIXNUM_ADD1(G2int_rb_fragment_count);
    G2int_rb_fragment_count = rb_fragment_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_rb_fragment_variable = Nil;
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
	defstruct_g2_rb_fragment_variable = the_array;
	SVREF(defstruct_g2_rb_fragment_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rb_fragment_g2_struct;
	def_structure_rb_fragment_variable = defstruct_g2_rb_fragment_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_rb_fragment_variable);
}

/* MAKE-RB-FRAGMENT-1 */
Object g2int_make_rb_fragment_1()
{
    Object def_structure_rb_fragment_variable, svref_new_value;

    x_note_fn_call(54,7);
    def_structure_rb_fragment_variable = G2int_chain_of_available_rb_fragments;
    if (def_structure_rb_fragment_variable) {
	G2int_chain_of_available_rb_fragments = 
		ISVREF(def_structure_rb_fragment_variable,(SI_Long)0L);
	SVREF(def_structure_rb_fragment_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rb_fragment_g2_struct;
    }
    else
	def_structure_rb_fragment_variable = 
		g2int_make_permanent_rb_fragment_structure_internal();
    inline_note_allocate_cons(def_structure_rb_fragment_variable,Nil);
    SVREF(def_structure_rb_fragment_variable,FIX((SI_Long)1L)) = Nil;
    svref_new_value = 
	    g2int_obtain_simple_gensym_string(G2int_default_fragment_max);
    SVREF(def_structure_rb_fragment_variable,FIX((SI_Long)2L)) = 
	    svref_new_value;
    ISVREF(def_structure_rb_fragment_variable,(SI_Long)3L) = FIX((SI_Long)0L);
    ISVREF(def_structure_rb_fragment_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_rb_fragment_variable);
}

Object G2int_the_type_description_of_r_buffer = UNBOUND;

Object G2int_chain_of_available_r_buffers = UNBOUND;

Object G2int_r_buffer_count = UNBOUND;

/* RECLAIM-R-BUFFER-1 */
Object g2int_reclaim_r_buffer_1(r_buffer)
    Object r_buffer;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(54,8);
    inline_note_reclaim_cons(r_buffer,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = r_buffer;
    g2int_reclaim_rb_fragment_1(ISVREF(r_buffer,(SI_Long)1L));
    SVREF(r_buffer,FIX((SI_Long)1L)) = Nil;
    g2int_reclaim_list_of_marks_1(ISVREF(r_buffer,(SI_Long)2L));
    SVREF(r_buffer,FIX((SI_Long)2L)) = Nil;
    g2int_reclaim_plist_of_resource_buffer(ISVREF(r_buffer,(SI_Long)3L));
    SVREF(r_buffer,FIX((SI_Long)3L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_r_buffers;
    SVREF(r_buffer,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_r_buffers = r_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-R-BUFFER */
Object g2int_reclaim_structure_for_r_buffer(r_buffer)
    Object r_buffer;
{
    x_note_fn_call(54,9);
    return g2int_reclaim_r_buffer_1(r_buffer);
}

static Object Qg2_defstruct_structure_name_r_buffer_g2_struct;  /* g2-defstruct-structure-name::r-buffer-g2-struct */

/* MAKE-PERMANENT-R-BUFFER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_r_buffer_structure_internal()
{
    Object def_structure_r_buffer_variable, r_buffer_count_new_value;
    Object defstruct_g2_r_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(54,10);
    def_structure_r_buffer_variable = Nil;
    r_buffer_count_new_value = FIXNUM_ADD1(G2int_r_buffer_count);
    G2int_r_buffer_count = r_buffer_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_r_buffer_variable = Nil;
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
	defstruct_g2_r_buffer_variable = the_array;
	SVREF(defstruct_g2_r_buffer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_r_buffer_g2_struct;
	def_structure_r_buffer_variable = defstruct_g2_r_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_r_buffer_variable);
}

/* MAKE-R-BUFFER-1 */
Object g2int_make_r_buffer_1()
{
    Object def_structure_r_buffer_variable;

    x_note_fn_call(54,11);
    def_structure_r_buffer_variable = G2int_chain_of_available_r_buffers;
    if (def_structure_r_buffer_variable) {
	G2int_chain_of_available_r_buffers = 
		ISVREF(def_structure_r_buffer_variable,(SI_Long)0L);
	SVREF(def_structure_r_buffer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_r_buffer_g2_struct;
    }
    else
	def_structure_r_buffer_variable = 
		g2int_make_permanent_r_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_r_buffer_variable,Nil);
    SVREF(def_structure_r_buffer_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_r_buffer_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_r_buffer_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_r_buffer_variable);
}

/* RECLAIM-RB-FRAGMENT-IF-ANY */
Object g2int_reclaim_rb_fragment_if_any(fragment_qm)
    Object fragment_qm;
{
    x_note_fn_call(54,12);
    if (fragment_qm)
	return g2int_reclaim_rb_fragment_1(fragment_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-LIST-OF-MARKS-1 */
Object g2int_reclaim_list_of_marks_1(marks)
    Object marks;
{
    Object mark, ab_loop_list_;

    x_note_fn_call(54,13);
    mark = Nil;
    ab_loop_list_ = marks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mark = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_reclaim_rb_mark_1(mark);
    goto next_loop;
  end_loop:;
    g2int_reclaim_gensym_list_1(marks);
    return VALUES_1(Nil);
}

/* RECLAIM-RESOURCE-BUFFER-OF-MARK */
Object g2int_reclaim_resource_buffer_of_mark(mark)
    Object mark;
{
    x_note_fn_call(54,14);
    g2int_reclaim_r_buffer_1(ISVREF(mark,(SI_Long)1L));
    return VALUES_1(Nil);
}

/* MAKE-MARK-INTO-NEW-EMPTY-RESOURCE-BUFFER */
Object g2int_make_mark_into_new_empty_resource_buffer()
{
    Object resource_buffer, fragment;

    x_note_fn_call(54,15);
    resource_buffer = g2int_make_r_buffer_1();
    fragment = g2int_make_rb_fragment_1();
    SVREF(resource_buffer,FIX((SI_Long)1L)) = fragment;
    return g2int_make_mark_at_start(resource_buffer);
}

/* MAKE-MARK-AT-START */
Object g2int_make_mark_at_start(resource_buffer)
    Object resource_buffer;
{
    Object mark, svref_new_value, gensym_push_modify_macro_arg, car_1, cdr_1;

    x_note_fn_call(54,16);
    mark = g2int_make_rb_mark_1();
    SVREF(mark,FIX((SI_Long)1L)) = resource_buffer;
    svref_new_value = ISVREF(resource_buffer,(SI_Long)1L);
    SVREF(mark,FIX((SI_Long)3L)) = svref_new_value;
    gensym_push_modify_macro_arg = mark;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(resource_buffer,(SI_Long)2L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(resource_buffer,FIX((SI_Long)2L)) = svref_new_value;
    return VALUES_1(mark);
}

/* MARK-COPY */
Object g2int_mark_copy(mark)
    Object mark;
{
    Object new_mark, svref_new_value;

    x_note_fn_call(54,17);
    new_mark = g2int_make_mark_at_start(ISVREF(mark,(SI_Long)1L));
    svref_new_value = ISVREF(mark,(SI_Long)4L);
    SVREF(new_mark,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = ISVREF(mark,(SI_Long)3L);
    SVREF(new_mark,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(new_mark);
}

/* MARK-SET */
Object g2int_mark_set(mark_to_set,mark_to_copy)
    Object mark_to_set, mark_to_copy;
{
    Object svref_new_value;

    x_note_fn_call(54,18);
    svref_new_value = ISVREF(mark_to_copy,(SI_Long)3L);
    SVREF(mark_to_set,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = ISVREF(mark_to_copy,(SI_Long)4L);
    return VALUES_1(SVREF(mark_to_set,FIX((SI_Long)4L)) = svref_new_value);
}

/* MARK-EQ */
Object g2int_mark_eq(mark_a,mark_b)
    Object mark_a, mark_b;
{
    Object ia, ib, fb, fa;

    x_note_fn_call(54,19);
    ia = ISVREF(mark_a,(SI_Long)4L);
    ib = ISVREF(mark_b,(SI_Long)4L);
    if (EQ(ISVREF(mark_a,(SI_Long)3L),ISVREF(mark_b,(SI_Long)3L)))
	return VALUES_1(EQ(ia,ib) ? T : Nil);
    else if ((SI_Long)0L == IFIX(ia)) {
	fb = ISVREF(mark_b,(SI_Long)3L);
	if (EQ(ISVREF(fb,(SI_Long)4L),ib))
	    return VALUES_1(EQ(ISVREF(fb,(SI_Long)1L),ISVREF(mark_b,
		    (SI_Long)3L)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if ((SI_Long)0L == IFIX(ib)) {
	fa = ISVREF(mark_a,(SI_Long)3L);
	if (EQ(ISVREF(fa,(SI_Long)4L),ia))
	    return VALUES_1(EQ(ISVREF(fa,(SI_Long)1L),ISVREF(mark_a,
		    (SI_Long)3L)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* MARK-KILL */
Object g2int_mark_kill(mark)
    Object mark;
{
    Object resource_buffer, svref_new_value;

    x_note_fn_call(54,20);
    resource_buffer = ISVREF(mark,(SI_Long)1L);
    svref_new_value = g2int_delete_gensym_element_1(mark,
	    ISVREF(resource_buffer,(SI_Long)2L));
    SVREF(resource_buffer,FIX((SI_Long)2L)) = svref_new_value;
    g2int_reclaim_rb_mark_1(mark);
    return VALUES_1(Nil);
}

/* MARK-DIRECTION */
Object g2int_mark_direction(mark,new_direction)
    Object mark, new_direction;
{
    x_note_fn_call(54,21);
    SVREF(mark,FIX((SI_Long)2L)) = new_direction;
    return VALUES_1(mark);
}

/* SET-PROPERTY-OF-BUFFER */
Object g2int_set_property_of_buffer(mark,property_1,value)
    Object mark, property_1, value;
{
    Object resource_buffer, buffer_plist, key, value_cons, ab_loop_list_;
    Object svref_new_value;

    x_note_fn_call(54,22);
    resource_buffer = ISVREF(mark,(SI_Long)1L);
    buffer_plist = ISVREF(resource_buffer,(SI_Long)3L);
    key = Nil;
    value_cons = Nil;
    ab_loop_list_ = buffer_plist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    key = CAR(ab_loop_list_);
    value_cons = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(key,property_1)) {
	M_CAR(value_cons) = value;
	goto end;
    }
    goto next_loop;
  end_loop:
    svref_new_value = g2int_gensym_cons_1(property_1,
	    g2int_gensym_cons_1(value,buffer_plist));
    SVREF(resource_buffer,FIX((SI_Long)3L)) = svref_new_value;
  end:;
    return VALUES_1(value);
}

/* GET-PROPERTY-OF-BUFFER */
Object g2int_get_property_of_buffer(mark,property_1)
    Object mark, property_1;
{
    Object resource_buffer, buffer_plist, key, value, ab_loop_list_, temp;

    x_note_fn_call(54,23);
    resource_buffer = ISVREF(mark,(SI_Long)1L);
    buffer_plist = ISVREF(resource_buffer,(SI_Long)3L);
    key = Nil;
    value = Nil;
    ab_loop_list_ = buffer_plist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    key = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(key,property_1))
	return VALUES_1(value);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-PLIST-OF-RESOURCE-BUFFER */
Object g2int_reclaim_plist_of_resource_buffer(plist)
    Object plist;
{
    x_note_fn_call(54,24);
    return g2int_reclaim_plist_tree_of_resource_buffer(plist);
}

/* RECLAIM-PLIST-TREE-OF-RESOURCE-BUFFER */
Object g2int_reclaim_plist_tree_of_resource_buffer(tree)
    Object tree;
{
    x_note_fn_call(54,25);
    if (CONSP(tree)) {
	g2int_reclaim_plist_tree_of_resource_buffer(CAR(tree));
	g2int_reclaim_plist_tree_of_resource_buffer(CDR(tree));
	return g2int_reclaim_gensym_cons_1(tree);
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(tree) != (SI_Long)0L)
	return g2int_reclaim_wide_string(tree);
    else if (STRINGP(tree))
	return g2int_reclaim_gensym_string(tree);
    else
	return VALUES_1(Qnil);
}

/* COPY-RESOURCE-PLIST-VALUE */
Object g2int_copy_resource_plist_value(value)
    Object value;
{
    Object temp;

    x_note_fn_call(54,26);
    if (CONSP(value)) {
	temp = g2int_copy_resource_plist_value(CAR(value));
	return g2int_gensym_cons_1(temp,
		g2int_copy_resource_plist_value(CDR(value)));
    }
    else if (STRINGP(value))
	return g2int_copy_text_string(value);
    else
	return VALUES_1(value);
}

/* POINT-MIN */
Object g2int_point_min(mark_for_buffer)
    Object mark_for_buffer;
{
    x_note_fn_call(54,27);
    return VALUES_1(FIX((SI_Long)0L));
}

/* POINT-MAX */
Object g2int_point_max(mark)
    Object mark;
{
    Object resource_buffer, fragment, next_fragment_qm;

    x_note_fn_call(54,28);
    resource_buffer = ISVREF(mark,(SI_Long)1L);
    fragment = ISVREF(resource_buffer,(SI_Long)1L);
    next_fragment_qm = Nil;
  next_loop:
    next_fragment_qm = ISVREF(fragment,(SI_Long)1L);
    if ( !TRUEP(next_fragment_qm))
	return VALUES_1(FIXNUM_ADD(ISVREF(fragment,(SI_Long)3L),
		ISVREF(fragment,(SI_Long)4L)));
    fragment = next_fragment_qm;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MARK-TAB */
Object g2int_mark_tab(mark,position_1)
    Object mark, position_1;
{
    Object resource_buffer, fragments_of_resource_buffer, fragment;
    Object start_position_of_fragment, length_of_fragment;
    Object end_position_of_fragment, svref_new_value, next_fragment_qm;
    char temp;

    x_note_fn_call(54,29);
    if (IFIX(position_1) < (SI_Long)0L)
	position_1 = FIX((SI_Long)0L);
    resource_buffer = ISVREF(mark,(SI_Long)1L);
    fragments_of_resource_buffer = ISVREF(resource_buffer,(SI_Long)1L);
    fragment = ISVREF(mark,(SI_Long)3L);
    start_position_of_fragment = ISVREF(fragment,(SI_Long)3L);
    if (FIXNUM_LE(start_position_of_fragment,position_1)) {
	length_of_fragment = ISVREF(fragment,(SI_Long)4L);
	end_position_of_fragment = FIXNUM_ADD(start_position_of_fragment,
		length_of_fragment);
	temp = FIXNUM_LT(position_1,end_position_of_fragment);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	svref_new_value = FIXNUM_MINUS(position_1,ISVREF(fragment,
		(SI_Long)3L));
	SVREF(mark,FIX((SI_Long)4L)) = svref_new_value;
	return VALUES_1(mark);
    }
    else {
	fragment = fragments_of_resource_buffer;
	next_fragment_qm = Nil;
      next_loop:
	next_fragment_qm = ISVREF(fragment,(SI_Long)1L);
	start_position_of_fragment = ISVREF(fragment,(SI_Long)3L);
	length_of_fragment = ISVREF(fragment,(SI_Long)4L);
	end_position_of_fragment = FIXNUM_ADD(start_position_of_fragment,
		length_of_fragment);
	if (FIXNUM_LE(start_position_of_fragment,position_1) && 
		FIXNUM_LT(position_1,end_position_of_fragment)) {
	    SVREF(mark,FIX((SI_Long)3L)) = fragment;
	    svref_new_value = FIXNUM_MINUS(position_1,
		    start_position_of_fragment);
	    SVREF(mark,FIX((SI_Long)4L)) = svref_new_value;
	    return VALUES_1(mark);
	}
	if ( !TRUEP(next_fragment_qm)) {
	    SVREF(mark,FIX((SI_Long)3L)) = fragment;
	    SVREF(mark,FIX((SI_Long)4L)) = length_of_fragment;
	    return VALUES_1(mark);
	}
	fragment = next_fragment_qm;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* MARK-MOVE */
Object g2int_mark_move(mark,delta)
    Object mark, delta;
{
    Object fragment, position_of_mark;

    x_note_fn_call(54,30);
    fragment = ISVREF(mark,(SI_Long)3L);
    position_of_mark = FIXNUM_ADD(ISVREF(fragment,(SI_Long)3L),ISVREF(mark,
	    (SI_Long)4L));
    return g2int_mark_tab(mark,FIXNUM_ADD(position_of_mark,delta));
}

/* MARK-MOVE-TO-END */
Object g2int_mark_move_to_end(mark)
    Object mark;
{
    x_note_fn_call(54,31);
    return g2int_mark_tab(mark,Most_positive_fixnum);
}

/* MARK-PEEK-CHARACTER */
Object g2int_mark_peek_character(mark)
    Object mark;
{
    Object fragment, index_of_mark, text_of_fragment, length_of_fragment;
    Object possible_fragment_qm;

    x_note_fn_call(54,32);
    fragment = ISVREF(mark,(SI_Long)3L);
    index_of_mark = ISVREF(mark,(SI_Long)4L);
    text_of_fragment = ISVREF(fragment,(SI_Long)2L);
    length_of_fragment = ISVREF(fragment,(SI_Long)4L);
    if (FIXNUM_LT(index_of_mark,length_of_fragment))
	return VALUES_1(CHAR(text_of_fragment,index_of_mark));
    possible_fragment_qm = ISVREF(fragment,(SI_Long)1L);
  next_loop:
    if ( !TRUEP(possible_fragment_qm))
	return VALUES_1(Nil);
    if ((SI_Long)0L < IFIX(ISVREF(possible_fragment_qm,(SI_Long)4L)))
	return VALUES_1(CHAR(ISVREF(possible_fragment_qm,(SI_Long)2L),
		FIX((SI_Long)0L)));
    possible_fragment_qm = ISVREF(possible_fragment_qm,(SI_Long)1L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MARK-GET-CHARACTER */
Object g2int_mark_get_character(mark)
    Object mark;
{
    Object temp;

    x_note_fn_call(54,33);
    temp = g2int_mark_peek_character(mark);
    g2int_mark_move(mark,FIX((SI_Long)1L));
    return VALUES_1(temp);
}

/* MARK-PEEK-BYTE */
Object g2int_mark_peek_byte(mark)
    Object mark;
{
    x_note_fn_call(54,34);
    return VALUES_1(CHAR_CODE(g2int_mark_peek_character(mark)));
}

/* MARK-GET-BYTE */
Object g2int_mark_get_byte(mark)
    Object mark;
{
    x_note_fn_call(54,35);
    return VALUES_1(CHAR_CODE(g2int_mark_get_character(mark)));
}

/* N-CHARACTERS-AVAILABLE? */
Object g2int_n_characters_availableqm(n_1,left_mark,right_mark)
    Object n_1, left_mark, right_mark;
{
    Object temp;

    x_note_fn_call(54,36);
    temp = g2int_position_of_mark(right_mark);
    return VALUES_1(FIXNUM_LE(n_1,FIXNUM_MINUS(temp,
	    g2int_position_of_mark(left_mark))) ? T : Nil);
}

/* POSITION-OF-MARK */
Object g2int_position_of_mark(mark)
    Object mark;
{
    Object fragment, position_of_mark;

    x_note_fn_call(54,37);
    fragment = ISVREF(mark,(SI_Long)3L);
    position_of_mark = FIXNUM_ADD(ISVREF(fragment,(SI_Long)3L),ISVREF(mark,
	    (SI_Long)4L));
    return VALUES_1(position_of_mark);
}

/* COPY-TEXT-BETWEEN-MARKS */
Object g2int_copy_text_between_marks(from_mark,to_mark)
    Object from_mark, to_mark;
{
    Object position_from, position_to, length_1, result_1, mark;
    Object char_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(54,38);
    position_from = g2int_position_of_mark(from_mark);
    position_to = g2int_position_of_mark(to_mark);
    length_1 = FIXNUM_MINUS(position_to,position_from);
    result_1 = g2int_obtain_simple_gensym_string(length_1);
    mark = g2int_mark_copy(from_mark);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_new_value = g2int_mark_get_character(mark);
    SET_ICHAR(result_1,i,ICHAR_CODE(char_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    g2int_mark_kill(mark);
    return VALUES_1(result_1);
}

/* INSERT-SUBTEXT-INTO-ROOMY-FRAGMENT */
Object g2int_insert_subtext_into_roomy_fragment(mark,text,start,end)
    Object mark, text, start, end;
{
    Object index_of_mark, fragment, text_of_fragment, length_of_fragment;
    Object resource_buffer, length_of_insert, old_length_of_fragment;
    Object count_in_front_of_mark, new_length_of_fragment, ab_loop_iter_flag_;
    Object next_fragment, incf_arg, svref_new_value, a_mark, ab_loop_list_;
    Object index_of_a_mark;
    SI_Long ab_loop_repeat_, from_i, to_i, i, ab_loop_bind_, j;
    char char_new_value;

    x_note_fn_call(54,39);
    index_of_mark = ISVREF(mark,(SI_Long)4L);
    fragment = ISVREF(mark,(SI_Long)3L);
    text_of_fragment = ISVREF(fragment,(SI_Long)2L);
    length_of_fragment = ISVREF(fragment,(SI_Long)4L);
    resource_buffer = ISVREF(mark,(SI_Long)1L);
    length_of_insert = FIXNUM_MINUS(end,start);
    old_length_of_fragment = length_of_fragment;
    count_in_front_of_mark = FIXNUM_MINUS(old_length_of_fragment,
	    index_of_mark);
    new_length_of_fragment = FIXNUM_ADD(old_length_of_fragment,
	    length_of_insert);
    if ((SI_Long)0L < IFIX(count_in_front_of_mark)) {
	ab_loop_repeat_ = IFIX(count_in_front_of_mark);
	from_i = IFIX(sub1(old_length_of_fragment));
	to_i = IFIX(FIXNUM_SUB1(new_length_of_fragment));
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_)) {
	    from_i = from_i - (SI_Long)1L;
	    to_i = to_i - (SI_Long)1L;
	}
	char_new_value = ICHAR(text_of_fragment,from_i);
	SET_ICHAR(text_of_fragment,to_i,char_new_value);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    SVREF(fragment,FIX((SI_Long)4L)) = new_length_of_fragment;
    i = IFIX(start);
    ab_loop_bind_ = IFIX(end);
    j = IFIX(index_of_mark);
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    if ( !TRUEP(ab_loop_iter_flag_))
	j = j + (SI_Long)1L;
    char_new_value = ICHAR(text,i);
    SET_ICHAR(text_of_fragment,j,char_new_value);
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    next_fragment = ISVREF(fragment,(SI_Long)1L);
  next_loop_2:
    if ( !TRUEP(next_fragment))
	goto end_loop_2;
    incf_arg = length_of_insert;
    svref_new_value = add(ISVREF(next_fragment,(SI_Long)3L),incf_arg);
    SVREF(next_fragment,FIX((SI_Long)3L)) = svref_new_value;
    next_fragment = ISVREF(next_fragment,(SI_Long)1L);
    goto next_loop_2;
  end_loop_2:;
    a_mark = Nil;
    ab_loop_list_ = ISVREF(resource_buffer,(SI_Long)2L);
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    a_mark = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(a_mark,(SI_Long)3L),fragment)) {
	index_of_a_mark = ISVREF(a_mark,(SI_Long)4L);
	if (FIXNUM_LT(index_of_mark,index_of_a_mark) || 
		NUM_EQ(index_of_mark,index_of_a_mark) && EQ(Kforward,
		ISVREF(a_mark,(SI_Long)2L))) {
	    incf_arg = length_of_insert;
	    svref_new_value = add(ISVREF(a_mark,(SI_Long)4L),incf_arg);
	    SVREF(a_mark,FIX((SI_Long)4L)) = svref_new_value;
	}
    }
    goto next_loop_3;
  end_loop_3:;
    return VALUES_1(mark);
}

/* INSERT-TEXT-AT-MARK */
Object g2int_insert_text_at_mark(mark,text)
    Object mark, text;
{
    x_note_fn_call(54,40);
    return g2int_insert_subtext_at_mark(mark,text,FIX((SI_Long)0L),
	    length(text));
}

/* INSERT-SUBTEXT-AT-MARK */
Object g2int_insert_subtext_at_mark(mark,text,start,end)
    Object mark, text, start, end;
{
    Object fragment, text_of_fragment, length_of_fragment, max_of_fragment;
    Object length_of_insert;

    x_note_fn_call(54,41);
    fragment = ISVREF(mark,(SI_Long)3L);
    text_of_fragment = ISVREF(fragment,(SI_Long)2L);
    length_of_fragment = ISVREF(fragment,(SI_Long)4L);
    max_of_fragment = length(text_of_fragment);
    length_of_insert = FIXNUM_MINUS(end,start);
    if (FIXNUM_LT(FIXNUM_ADD(length_of_insert,length_of_fragment),
	    max_of_fragment))
	g2int_insert_subtext_into_roomy_fragment(mark,text,
		FIX((SI_Long)0L),length_of_insert);
    else
	g2int_insert_subtext_by_spliting_fragment(mark,text,start,end);
    return VALUES_1(mark);
}

/* SPLIT-FRAGMENT */
Object g2int_split_fragment(mark)
    Object mark;
{
    Object fragment, next_fragment_qm, index_of_mark, length_of_fragment;
    Object text_of_fragment, new_fragment, svref_new_value;
    Object text_of_new_fragment, ab_loop_iter_flag_;
    SI_Long src, ab_loop_bind_, dst;
    char char_new_value;

    x_note_fn_call(54,42);
    fragment = ISVREF(mark,(SI_Long)3L);
    next_fragment_qm = ISVREF(fragment,(SI_Long)1L);
    index_of_mark = ISVREF(mark,(SI_Long)4L);
    length_of_fragment = ISVREF(fragment,(SI_Long)4L);
    text_of_fragment = ISVREF(fragment,(SI_Long)2L);
    new_fragment = g2int_make_rb_fragment_1();
    SVREF(new_fragment,FIX((SI_Long)1L)) = next_fragment_qm;
    SVREF(fragment,FIX((SI_Long)1L)) = new_fragment;
    svref_new_value = FIXNUM_MINUS(length_of_fragment,index_of_mark);
    SVREF(new_fragment,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = FIXNUM_ADD(ISVREF(fragment,(SI_Long)3L),index_of_mark);
    SVREF(new_fragment,FIX((SI_Long)3L)) = svref_new_value;
    SVREF(fragment,FIX((SI_Long)4L)) = index_of_mark;
    text_of_new_fragment = ISVREF(new_fragment,(SI_Long)2L);
    src = IFIX(index_of_mark);
    ab_loop_bind_ = IFIX(length_of_fragment);
    dst = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (src >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	dst = dst + (SI_Long)1L;
    char_new_value = ICHAR(text_of_fragment,src);
    SET_ICHAR(text_of_new_fragment,dst,char_new_value);
    ab_loop_iter_flag_ = Nil;
    src = src + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(fragment);
}

/* INSERT-SUBTEXT-BY-SPLITING-FRAGMENT */
Object g2int_insert_subtext_by_spliting_fragment(mark,text,start,end)
    Object mark, text, start, end;
{
    Object left_fragment, right_fragment, length_of_insert;
    Object first_of_inserted_fragments, last_of_inserted_fragments;
    Object position_so_far, start_of_bit, end_of_bit, length_of_bit, incf_arg;
    Object dst_text, ab_loop_iter_flag_, temp, next_fragment_qm;
    Object index_of_split, a_mark, ab_loop_list_, fragment_of_mark, a_index;
    SI_Long src_i, ab_loop_bind_, dst_i;
    char char_new_value;

    x_note_fn_call(54,43);
    left_fragment = g2int_split_fragment(mark);
    right_fragment = ISVREF(left_fragment,(SI_Long)1L);
    length_of_insert = FIXNUM_MINUS(end,start);
    first_of_inserted_fragments = g2int_make_rb_fragment_1();
    last_of_inserted_fragments = first_of_inserted_fragments;
    position_so_far = ISVREF(right_fragment,(SI_Long)3L);
    start_of_bit = start;
    end_of_bit = Nil;
    length_of_bit = Nil;
  next_loop:
    end_of_bit = lmin(FIXNUM_ADD(start_of_bit,
	    G2int_default_fragment_bit_size),end);
    length_of_bit = FIXNUM_MINUS(end_of_bit,start_of_bit);
    SVREF(last_of_inserted_fragments,FIX((SI_Long)4L)) = length_of_bit;
    SVREF(last_of_inserted_fragments,FIX((SI_Long)3L)) = position_so_far;
    incf_arg = length_of_bit;
    position_so_far = add(position_so_far,incf_arg);
    dst_text = ISVREF(last_of_inserted_fragments,(SI_Long)2L);
    src_i = IFIX(start_of_bit);
    ab_loop_bind_ = IFIX(end_of_bit);
    dst_i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if (src_i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	dst_i = dst_i + (SI_Long)1L;
    char_new_value = ICHAR(text,src_i);
    SET_ICHAR(dst_text,dst_i,char_new_value);
    ab_loop_iter_flag_ = Nil;
    src_i = src_i + (SI_Long)1L;
    goto next_loop_1;
  end_loop:;
    if (NUM_EQ(end_of_bit,end))
	goto end_1;
    temp = last_of_inserted_fragments;
    last_of_inserted_fragments = g2int_make_rb_fragment_1();
    SVREF(temp,FIX((SI_Long)1L)) = last_of_inserted_fragments;
    start_of_bit = end_of_bit;
    goto next_loop;
  end_loop_1:
  end_1:;
    SVREF(left_fragment,FIX((SI_Long)1L)) = first_of_inserted_fragments;
    SVREF(last_of_inserted_fragments,FIX((SI_Long)1L)) = right_fragment;
    next_fragment_qm = ISVREF(last_of_inserted_fragments,(SI_Long)1L);
  next_loop_2:
    if ( !TRUEP(next_fragment_qm))
	goto end_loop_2;
    incf_arg = length_of_insert;
    temp = add(ISVREF(next_fragment_qm,(SI_Long)3L),incf_arg);
    SVREF(next_fragment_qm,FIX((SI_Long)3L)) = temp;
    next_fragment_qm = ISVREF(next_fragment_qm,(SI_Long)1L);
    goto next_loop_2;
  end_loop_2:;
    index_of_split = ISVREF(left_fragment,(SI_Long)4L);
    a_mark = Nil;
    ab_loop_list_ = ISVREF(ISVREF(mark,(SI_Long)1L),(SI_Long)2L);
    fragment_of_mark = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    a_mark = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    fragment_of_mark = ISVREF(a_mark,(SI_Long)3L);
    if (EQ(fragment_of_mark,left_fragment)) {
	a_index = ISVREF(a_mark,(SI_Long)4L);
	if (FIXNUM_LT(index_of_split,a_index) || FIXNUM_EQ(index_of_split,
		a_index) && EQ(Kforward,ISVREF(a_mark,(SI_Long)2L)))
	    g2int_mark_move(a_mark,length_of_insert);
    }
    goto next_loop_3;
  end_loop_3:;
    return VALUES_1(mark);
}

/* INSERT-CHARACTER-AT-MARK */
Object g2int_insert_character_at_mark(mark,character_1)
    Object mark, character_1;
{
    Object hack;

    x_note_fn_call(54,44);
    hack = g2int_obtain_simple_gensym_string(FIX((SI_Long)1L));
    SET_CHAR(hack,FIX((SI_Long)0L),character_1);
    g2int_insert_text_at_mark(mark,hack);
    g2int_reclaim_gensym_string(hack);
    return VALUES_1(Nil);
}

Object G2int_current_right_of_parsing = UNBOUND;

/* CHARACTERS-AVAILABLE-FOR-PARSING */
Object g2int_characters_available_for_parsing()
{
    Object mark, fragment, position_of_mark, resource_buffer;
    Object fragments_of_resource_buffer, f, end_position_of_buffer;

    x_note_fn_call(54,45);
    mark = G2int_current_right_of_parsing;
    fragment = ISVREF(mark,(SI_Long)3L);
    position_of_mark = FIXNUM_ADD(ISVREF(fragment,(SI_Long)3L),ISVREF(mark,
	    (SI_Long)4L));
    resource_buffer = ISVREF(mark,(SI_Long)1L);
    fragments_of_resource_buffer = ISVREF(resource_buffer,(SI_Long)1L);
    f = fragments_of_resource_buffer;
  next_loop:
    if ( !TRUEP(ISVREF(f,(SI_Long)1L)))
	goto end_loop;
    f = ISVREF(f,(SI_Long)1L);
    goto next_loop;
  end_loop:
    end_position_of_buffer = FIXNUM_ADD(ISVREF(f,(SI_Long)3L),ISVREF(f,
	    (SI_Long)4L));
    goto end;
    end_position_of_buffer = Qnil;
  end:;
    return VALUES_1(FIXNUM_MINUS(end_position_of_buffer,position_of_mark));
}

Object G2int_current_left_of_parsing = UNBOUND;

/* GET-SIMPLE-TEXT-FROM-LAST-SCAN */
Object g2int_get_simple_text_from_last_scan()
{
    x_note_fn_call(54,46);
    return g2int_copy_text_between_marks(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
}

/* UNDO-LAST-SCAN */
Object g2int_undo_last_scan()
{
    x_note_fn_call(54,47);
    return g2int_mark_set(G2int_current_right_of_parsing,
	    G2int_current_left_of_parsing);
}

/* SCAN-MOVE */
Object g2int_scan_move(delta)
    Object delta;
{
    x_note_fn_call(54,48);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    return g2int_mark_move(G2int_current_right_of_parsing,delta);
}

/* SCAN-TEXT */
Object g2int_scan_text(text)
    Object text;
{
    Object temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(54,49);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(text));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    temp = CHR(ICHAR(text,i));
    if ( !EQ(temp,g2int_mark_get_character(G2int_current_right_of_parsing))) {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* SCAN-INTEGER */
Object g2int_scan_integer()
{
    Object result_qm, char_1, digit_qm;

    x_note_fn_call(54,50);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    result_qm = Nil;
    char_1 = Nil;
    digit_qm = Nil;
  next_loop:
    char_1 = g2int_mark_peek_character(G2int_current_right_of_parsing);
    digit_qm = char_1 ? digit_char_p(char_1,_) : Qnil;
    if ( !TRUEP(digit_qm)) {
	if (result_qm)
	    return VALUES_1(result_qm);
	else {
	    g2int_mark_set(G2int_current_right_of_parsing,
		    G2int_current_left_of_parsing);
	    return VALUES_1(Nil);
	}
    }
    else if (result_qm)
	result_qm = FIX((SI_Long)10L * IFIX(result_qm) + IFIX(digit_qm));
    else
	result_qm = digit_qm;
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SCAN-ZERO-OR-MORE-SPACES-AND-TABS */
Object g2int_scan_zero_or_more_spaces_and_tabs()
{
    Object char_1;

    x_note_fn_call(54,51);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    char_1 = Nil;
  next_loop:
    char_1 = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if ( !(EQ(char_1,CHR(' ')) || EQ(char_1,CHR('\t'))))
	goto end_loop;
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* SCAN-ONE-OR-MORE-SPACES-AND-TABS */
Object g2int_scan_one_or_more_spaces_and_tabs()
{
    Object result_1, char_1;

    x_note_fn_call(54,52);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    result_1 = Nil;
    char_1 = Nil;
  next_loop:
    char_1 = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if ( !(EQ(char_1,CHR(' ')) || EQ(char_1,CHR('\t'))))
	goto end_loop;
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    result_1 = T;
    goto next_loop;
  end_loop:
    if (result_1)
	return VALUES_1(result_1);
    else {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
    return VALUES_1(Qnil);
}

/* SCAN-TO-END-OF-LINE */
Object g2int_scan_to_end_of_line()
{
    Object result_1, char_1;

    x_note_fn_call(54,53);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    result_1 = Nil;
    char_1 = Nil;
  next_loop:
    char_1 = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if ( !TRUEP(char_1) || EQ(char_1,CHR('\r')) || EQ(char_1,CHR('\n')))
	return VALUES_1(T);
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    result_1 = T;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SCAN-LINE-TERMINATION */
Object g2int_scan_line_termination()
{
    Object line_terminator_qm;

    x_note_fn_call(54,54);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    line_terminator_qm = 
	    g2int_mark_peek_character(G2int_current_right_of_parsing);
    if (EQ(line_terminator_qm,CHR('\r'))) {
	g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
	if (EQ(g2int_mark_peek_character(G2int_current_right_of_parsing),
		CHR('\n')))
	    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
	return VALUES_1(T);
    }
    else {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
}

/* SCAN-TO-BEGINNING-OF-NEXT-LINE */
Object g2int_scan_to_beginning_of_next_line()
{
    Object line_terminator;

    x_note_fn_call(54,55);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    g2int_scan_to_end_of_line();
    line_terminator = 
	    g2int_mark_peek_character(G2int_current_right_of_parsing);
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    if (EQ(line_terminator,CHR('\r')) && 
	    EQ(g2int_mark_peek_character(G2int_current_right_of_parsing),
	    CHR('\n')))
	g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    if (g2int_mark_peek_character(G2int_current_right_of_parsing))
	return VALUES_1(T);
    else {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
}

/* SCAN-BLANK-LINE */
Object g2int_scan_blank_line()
{
    Object next_char;

    x_note_fn_call(54,56);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    next_char = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if (EQ(CHR('\r'),next_char) || EQ(CHR('\n'),next_char)) {
	g2int_scan_to_beginning_of_next_line();
	return VALUES_1(T);
    }
    else {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
}

/* SCAN-UPTO-CHARACTER */
Object g2int_scan_upto_character(character_1)
    Object character_1;
{
    Object c_qm;

    x_note_fn_call(54,57);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    c_qm = Nil;
  next_loop:
    c_qm = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if ( !TRUEP(c_qm)) {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
    if (EQ(c_qm,character_1))
	return VALUES_1(T);
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* STRING-MEMBER */
Object g2int_string_member(char_1,string_1)
    Object char_1, string_1;
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(54,58);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(string_1));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (CHAR_EQ(char_1,CHR(ICHAR(string_1,i))))
	return VALUES_1(T);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SCAN-UPTO-MEMBER-OF-BAG */
Object g2int_scan_upto_member_of_bag(bag)
    Object bag;
{
    Object c_qm;

    x_note_fn_call(54,59);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    c_qm = Nil;
  next_loop:
    c_qm = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if ( !TRUEP(c_qm)) {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
    if (g2int_string_member(c_qm,bag))
	return VALUES_1(c_qm);
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SCAN-UPTO-END */
Object g2int_scan_upto_end()
{
    x_note_fn_call(54,60);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
  next_loop:
    if ( !TRUEP(g2int_mark_peek_character(G2int_current_right_of_parsing)))
	goto end_loop;
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    return VALUES_1(T);
}

/* SCAN-SYMBOL */
Object g2int_scan_symbol()
{
    Object c_qm, text, result_1;

    x_note_fn_call(54,61);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    if ( !(g2int_mark_peek_character(G2int_current_right_of_parsing) && 
	    ALPHA_CHAR_P(g2int_mark_peek_character(G2int_current_right_of_parsing)))) 
		{
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
    c_qm = Nil;
  next_loop:
    c_qm = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if ( !TRUEP(c_qm))
	goto end_loop;
    if ( !(ALPHANUMERICP(c_qm) || EQ(c_qm,CHR('_')) || EQ(c_qm,CHR('-')))) {
	text = g2int_get_simple_text_from_last_scan();
	result_1 = g2int_gsi_web_intern(nstring_upcase(1,text));
	g2int_reclaim_gensym_string(text);
	return VALUES_1(result_1);
    }
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant;     /* "INTEGER" */

static Object string_constant_1;   /* "SYMBOL" */

static Object string_constant_2;   /* "STRING" */

/* GSI-WEB-INTERN */
Object g2int_gsi_web_intern(string_1)
    Object string_1;
{
    x_note_fn_call(54,62);
    if (string_eq(2,string_1,string_constant))
	return VALUES_1(Qinteger);
    else if (string_eq(2,string_1,string_constant_1))
	return VALUES_1(Qsymbol);
    else if (string_eq(2,string_1,string_constant_2))
	return VALUES_1(Qstring);
    else
	return intern(string_1,G2int_ab_package_1);
}

/* SCAN-OVER-FILENAME */
Object g2int_scan_over_filename()
{
    Object c_qm, temp;

    x_note_fn_call(54,63);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    c_qm = Nil;
  next_loop:
    c_qm = g2int_mark_peek_character(G2int_current_right_of_parsing);
    if ( !(c_qm &&  !EQ(c_qm,CHR('\t'))))
	goto end_loop;
    g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:;
    temp = g2int_position_of_mark(G2int_current_left_of_parsing);
    if ( !FIXNUM_EQ(temp,
	    g2int_position_of_mark(G2int_current_right_of_parsing))) {
	g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)-1L));
      next_loop_1:
	if ( !EQ(g2int_mark_peek_character(G2int_current_right_of_parsing),
		CHR(' ')))
	    goto end_loop_1;
	g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)-1L));
	goto next_loop_1;
      end_loop_1:
	g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
    }
    return VALUES_1(T);
}

void buffer_INIT()
{
    Object temp, reclaim_structure_for_rb_mark;
    Object reclaim_structure_for_rb_fragment, reclaim_structure_for_r_buffer;
    Object Qg2int_r_buffer, Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_r_buffer_count, AB_package;
    Object Qg2int_chain_of_available_r_buffers;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_5, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qg2int_rb_fragment;
    Object Qg2int_rb_fragment_count, Qg2int_chain_of_available_rb_fragments;
    Object string_constant_4, Qg2int_rb_mark, Qg2int_rb_mark_count;
    Object Qg2int_chain_of_available_rb_marks, string_constant_3;
    Object Qg2int_binding_cliches;

    x_note_fn_call(54,64);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_binding_cliches = STATIC_SYMBOL("BINDING-CLICHES",AB_package);
    G2int_binding_cliches_prop = Qg2int_binding_cliches;
    G2int_prefered_line_terminator = CHR('\n');
    G2int_default_fragment_max = FIX((SI_Long)2100L);
    G2int_default_fragment_bit_size = FIX((SI_Long)2000L);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_rb_mark_g2_struct = 
	    STATIC_SYMBOL("RB-MARK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_rb_mark = STATIC_SYMBOL("RB-MARK",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_rb_mark_g2_struct,
	    Qg2int_rb_mark,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_rb_mark,
	    Qg2_defstruct_structure_name_rb_mark_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_rb_mark == UNBOUND)
	G2int_the_type_description_of_rb_mark = Nil;
    string_constant_3 = 
	    STATIC_STRING("43Dy8l8303y1n8303y8m8k1l8m0000000kpk0k0");
    temp = G2int_the_type_description_of_rb_mark;
    G2int_the_type_description_of_rb_mark = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_3));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_rb_mark_g2_struct,
	    G2int_the_type_description_of_rb_mark,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_rb_mark,
	    G2int_the_type_description_of_rb_mark,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_rb_marks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RB-MARKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_rb_marks,
	    G2int_chain_of_available_rb_marks);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_rb_marks,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_rb_mark_count = STATIC_SYMBOL("RB-MARK-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_rb_mark_count,G2int_rb_mark_count);
    g2int_record_system_variable(Qg2int_rb_mark_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_rb_mark = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_rb_mark,NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_rb_mark,reclaim_structure_for_rb_mark);
    Kforward = STATIC_SYMBOL("FORWARD",Pkeyword);
    Qg2_defstruct_structure_name_rb_fragment_g2_struct = 
	    STATIC_SYMBOL("RB-FRAGMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_rb_fragment = STATIC_SYMBOL("RB-FRAGMENT",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_rb_fragment_g2_struct,
	    Qg2int_rb_fragment,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_rb_fragment,
	    Qg2_defstruct_structure_name_rb_fragment_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_rb_fragment == UNBOUND)
	G2int_the_type_description_of_rb_fragment = Nil;
    string_constant_4 = 
	    STATIC_STRING("43Dy8l8302y1n8302y8m8k1l8m0000000kpk0k0");
    temp = G2int_the_type_description_of_rb_fragment;
    G2int_the_type_description_of_rb_fragment = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_4));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_rb_fragment_g2_struct,
	    G2int_the_type_description_of_rb_fragment,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_rb_fragment,
	    G2int_the_type_description_of_rb_fragment,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_rb_fragments = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RB-FRAGMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_rb_fragments,
	    G2int_chain_of_available_rb_fragments);
    g2int_record_system_variable(Qg2int_chain_of_available_rb_fragments,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_rb_fragment_count = STATIC_SYMBOL("RB-FRAGMENT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_rb_fragment_count,
	    G2int_rb_fragment_count);
    g2int_record_system_variable(Qg2int_rb_fragment_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_rb_fragment = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_rb_fragment,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_rb_fragment,reclaim_structure_for_rb_fragment);
    Qg2_defstruct_structure_name_r_buffer_g2_struct = 
	    STATIC_SYMBOL("R-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_r_buffer = STATIC_SYMBOL("R-BUFFER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_r_buffer_g2_struct,
	    Qg2int_r_buffer,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_r_buffer,
	    Qg2_defstruct_structure_name_r_buffer_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_r_buffer == UNBOUND)
	G2int_the_type_description_of_r_buffer = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8l8301y1n8301y8m8k1l8m0000000kok0k0");
    temp = G2int_the_type_description_of_r_buffer;
    G2int_the_type_description_of_r_buffer = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_5));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_r_buffer_g2_struct,
	    G2int_the_type_description_of_r_buffer,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_r_buffer,
	    G2int_the_type_description_of_r_buffer,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_r_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-R-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_r_buffers,
	    G2int_chain_of_available_r_buffers);
    g2int_record_system_variable(Qg2int_chain_of_available_r_buffers,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_r_buffer_count = STATIC_SYMBOL("R-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_r_buffer_count,G2int_r_buffer_count);
    g2int_record_system_variable(Qg2int_r_buffer_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_r_buffer = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_r_buffer,NIL,FALSE,
	    1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_r_buffer,reclaim_structure_for_r_buffer);
    string_constant = STATIC_STRING("INTEGER");
    string_constant_1 = STATIC_STRING("SYMBOL");
    string_constant_2 = STATIC_STRING("STRING");
}
