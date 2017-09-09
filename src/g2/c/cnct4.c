/* cnct4.c
 * Input file:  connect4.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cnct4.h"


/* CLONE-CONNECTIONS-FOR-BLOCK */
Object clone_connections_for_block(block,cloned_block,
	    plist_of_blocks_and_corresponding_clones)
    Object block, cloned_block, plist_of_blocks_and_corresponding_clones;
{
    Object gensymed_symbol, connection_table, cloned_connection_table;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_;
    Object block_connection, block_connection_item, block_at_other_end;
    Object cloned_block_at_other_end, temp, ab_less_than_branch_qm_;
    Object gensymed_symbol_1, gensymed_symbol_4, ab_node_stack__1;
    Object ab_current_node__1, ab_skip_list_p__1, ab_next_node__1;
    Object ab_tail_node__1, ab_current_alist__1, ab_connection__1;
    Object cloned_connection, cloned_connection_item, temp_2;
    Object cloned_block_connection, connection_table_at_other_end;
    Object connection_item_at_other_end, cloned_connection_table_at_other_end;
    Object cloned_connection_stub, cloned_connection_stub_connection_item;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(102,0);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    connection_table = gensymed_symbol;
    gensymed_symbol = ISVREF(cloned_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    cloned_connection_table = gensymed_symbol;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    block_connection = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,1);
      block_connection_item = Nil;
      block_at_other_end = Nil;
      cloned_block_at_other_end = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      block_connection = ab_connection_;
      gensymed_symbol = CDR(connection_table);
      gensymed_symbol_1 = block_connection;
      gensymed_symbol_2 = SXHASH_SYMBOL_1(block_connection) & 
	      IFIX(Most_positive_fixnum);
      gensymed_symbol_3 = (SI_Long)0L;
    next_loop_3:
      if ( !TRUEP(gensymed_symbol))
	  goto end_loop_3;
      gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
      if (gensymed_symbol_2 < gensymed_symbol_3)
	  gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
      else if (gensymed_symbol_2 > gensymed_symbol_3)
	  gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
      else {
	  gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	  gensymed_symbol_4 = Nil;
	next_loop_4:
	  if ( !TRUEP(gensymed_symbol))
	      goto end_loop_4;
	  gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	  if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	      block_connection_item = M_CDR(M_CAR(gensymed_symbol));
	      goto end_2;
	  }
	  gensymed_symbol = M_CDR(gensymed_symbol);
	  goto next_loop_4;
	end_loop_4:
	  block_connection_item = Qnil;
	end_2:;
	  goto end_3;
      }
      goto next_loop_3;
    end_loop_3:
      block_connection_item = Qnil;
    end_3:;
      block_at_other_end = 
	      get_block_at_other_end_of_connection(block_connection,block);
      cloned_block_at_other_end = 
	      getfq_function_no_default(plist_of_blocks_and_corresponding_clones,
	      block_at_other_end);
      if (cloned_block_at_other_end) {
	  scope_conses = Scope_conses;
	  ab_node_stack__1 = Nil;
	  ab_current_node__1 = Nil;
	  gensymed_symbol = ISVREF(cloned_block,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)6L) : Nil;
	  ab_skip_list_form_ = gensymed_symbol;
	  ab_skip_list_p__1 = Nil;
	  ab_next_node__1 = Nil;
	  ab_tail_node__1 = Nil;
	  ab_current_alist__1 = Nil;
	  ab_entry_cons_ = Nil;
	  ab_connection__1 = Nil;
	  ab_connection_item_ = Nil;
	  cloned_connection = Nil;
	  PUSH_SPECIAL(Scope_conses,scope_conses,0);
	    cloned_connection_item = Nil;
	    gensymed_symbol = CDR(ab_skip_list_form_);
	    if (CONSP(gensymed_symbol)) {
		temp = M_CAR(gensymed_symbol);
		temp_1 = SIMPLE_VECTOR_P(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = M_CDR(gensymed_symbol);
		ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp) ? T : Nil;
	    }
	    else
		ab_skip_list_p__1 = Nil;
	    if (ab_skip_list_p__1) {
		ab_next_node__1 = 
			ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L);
		ab_tail_node__1 = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node__1,ab_tail_node__1))
		    ab_next_node__1 = Nil;
	    }
	    else
		ab_next_node__1 = CDR(ab_skip_list_form_);
	  next_loop_5:
	  next_loop_6:
	    if (ab_current_alist__1) {
		ab_entry_cons_ = M_CAR(ab_current_alist__1);
		ab_connection__1 = M_CAR(ab_entry_cons_);
		ab_connection_item_ = M_CDR(ab_entry_cons_);
		ab_current_alist__1 = M_CDR(ab_current_alist__1);
	    }
	    else if (ab_skip_list_p__1) {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_next_node__1 = ISVREF(ISVREF(ab_current_node__1,
			    (SI_Long)0L),(SI_Long)0L);
		    if (EQ(ab_next_node__1,ab_tail_node__1))
			ab_next_node__1 = Nil;
		    ab_connection__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_connection_item_ = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		}
		else
		    ab_current_node__1 = Nil;
	    }
	    else {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_7:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node__1,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_5;
		    ab_node_stack__1 = scope_cons(ab_current_node__1,
			    ab_node_stack__1);
		    ab_current_node__1 = ab_less_than_branch_qm_;
		    goto next_loop_7;
		  end_loop_5:;
		}
		else if (ab_node_stack__1) {
		    ab_next_node__1 = ab_node_stack__1;
		    ab_current_node__1 = M_CAR(ab_node_stack__1);
		    ab_node_stack__1 = M_CDR(ab_node_stack__1);
		}
		else
		    ab_current_node__1 = Nil;
		if (ab_current_node__1) {
		    ab_next_node__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_current_alist__1 = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist__1);
		    ab_connection__1 = M_CAR(ab_entry_cons_);
		    ab_connection_item_ = M_CDR(ab_entry_cons_);
		    ab_current_alist__1 = M_CDR(ab_current_alist__1);
		}
	    }
	    if ( !TRUEP(ab_current_node__1) || ab_current_node__1 && 
		    ab_connection__1 && EQ(ISVREF(ab_connection__1,
		    (SI_Long)3L),cloned_block))
		goto end_4;
	    goto next_loop_6;
	  end_loop_6:
	  end_4:
	    if ( !TRUEP(ab_current_node__1))
		goto end_loop_7;
	    cloned_connection = ab_connection__1;
	    gensymed_symbol = CDR(cloned_connection_table);
	    gensymed_symbol_1 = cloned_connection;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(cloned_connection) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_8:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_8;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_9:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_9;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    cloned_connection_item = M_CDR(M_CAR(gensymed_symbol));
		    goto end_5;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_9;
	      end_loop_9:
		cloned_connection_item = Qnil;
	      end_5:;
		goto end_6;
	    }
	    goto next_loop_8;
	  end_loop_8:
	    cloned_connection_item = Qnil;
	  end_6:;
	    if ( !TRUEP(ISVREF(cloned_connection_item,(SI_Long)4L))) {
		temp_2 = ISVREF(cloned_connection_item,(SI_Long)1L);
		temp = ISVREF(block_connection_item,(SI_Long)1L);
		temp_1 = EQUAL(temp_2,temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? FIXNUM_EQ(ISVREF(cloned_connection,(SI_Long)5L),
		    ISVREF(block_connection,(SI_Long)5L)) : TRUEP(Nil)) {
		cloned_block_connection = cloned_connection;
		goto end_7;
	    }
	    goto next_loop_5;
	  end_loop_7:
	    cloned_block_connection = Qnil;
	  end_7:;
	  POP_SPECIAL();
	  gensymed_symbol = ISVREF(block_at_other_end,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)6L) : Nil;
	  connection_table_at_other_end = gensymed_symbol;
	  gensymed_symbol = CDR(connection_table_at_other_end);
	  gensymed_symbol_1 = block_connection;
	  gensymed_symbol_2 = SXHASH_SYMBOL_1(block_connection) & 
		  IFIX(Most_positive_fixnum);
	  gensymed_symbol_3 = (SI_Long)0L;
	next_loop_10:
	  if ( !TRUEP(gensymed_symbol))
	      goto end_loop_10;
	  gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	  if (gensymed_symbol_2 < gensymed_symbol_3)
	      gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	  else if (gensymed_symbol_2 > gensymed_symbol_3)
	      gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	  else {
	      gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	      gensymed_symbol_4 = Nil;
	    next_loop_11:
	      if ( !TRUEP(gensymed_symbol))
		  goto end_loop_11;
	      gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	      if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		  connection_item_at_other_end = M_CDR(M_CAR(gensymed_symbol));
		  goto end_8;
	      }
	      gensymed_symbol = M_CDR(gensymed_symbol);
	      goto next_loop_11;
	    end_loop_11:
	      connection_item_at_other_end = Qnil;
	    end_8:;
	      goto end_9;
	  }
	  goto next_loop_10;
	end_loop_10:
	  connection_item_at_other_end = Qnil;
	end_9:;
	  gensymed_symbol = ISVREF(cloned_block_at_other_end,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)6L) : Nil;
	  cloned_connection_table_at_other_end = gensymed_symbol;
	  scope_conses = Scope_conses;
	  ab_node_stack__1 = Nil;
	  ab_current_node__1 = Nil;
	  gensymed_symbol = ISVREF(cloned_block_at_other_end,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)6L) : Nil;
	  ab_skip_list_form_ = gensymed_symbol;
	  ab_skip_list_p__1 = Nil;
	  ab_next_node__1 = Nil;
	  ab_tail_node__1 = Nil;
	  ab_current_alist__1 = Nil;
	  ab_entry_cons_ = Nil;
	  ab_connection__1 = Nil;
	  ab_connection_item_ = Nil;
	  cloned_connection = Nil;
	  PUSH_SPECIAL(Scope_conses,scope_conses,0);
	    cloned_connection_item = Nil;
	    gensymed_symbol = CDR(ab_skip_list_form_);
	    if (CONSP(gensymed_symbol)) {
		temp = M_CAR(gensymed_symbol);
		temp_1 = SIMPLE_VECTOR_P(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = M_CDR(gensymed_symbol);
		ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp) ? T : Nil;
	    }
	    else
		ab_skip_list_p__1 = Nil;
	    if (ab_skip_list_p__1) {
		ab_next_node__1 = 
			ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L);
		ab_tail_node__1 = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node__1,ab_tail_node__1))
		    ab_next_node__1 = Nil;
	    }
	    else
		ab_next_node__1 = CDR(ab_skip_list_form_);
	  next_loop_12:
	  next_loop_13:
	    if (ab_current_alist__1) {
		ab_entry_cons_ = M_CAR(ab_current_alist__1);
		ab_connection__1 = M_CAR(ab_entry_cons_);
		ab_connection_item_ = M_CDR(ab_entry_cons_);
		ab_current_alist__1 = M_CDR(ab_current_alist__1);
	    }
	    else if (ab_skip_list_p__1) {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_next_node__1 = ISVREF(ISVREF(ab_current_node__1,
			    (SI_Long)0L),(SI_Long)0L);
		    if (EQ(ab_next_node__1,ab_tail_node__1))
			ab_next_node__1 = Nil;
		    ab_connection__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_connection_item_ = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		}
		else
		    ab_current_node__1 = Nil;
	    }
	    else {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_14:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node__1,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_12;
		    ab_node_stack__1 = scope_cons(ab_current_node__1,
			    ab_node_stack__1);
		    ab_current_node__1 = ab_less_than_branch_qm_;
		    goto next_loop_14;
		  end_loop_12:;
		}
		else if (ab_node_stack__1) {
		    ab_next_node__1 = ab_node_stack__1;
		    ab_current_node__1 = M_CAR(ab_node_stack__1);
		    ab_node_stack__1 = M_CDR(ab_node_stack__1);
		}
		else
		    ab_current_node__1 = Nil;
		if (ab_current_node__1) {
		    ab_next_node__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_current_alist__1 = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist__1);
		    ab_connection__1 = M_CAR(ab_entry_cons_);
		    ab_connection_item_ = M_CDR(ab_entry_cons_);
		    ab_current_alist__1 = M_CDR(ab_current_alist__1);
		}
	    }
	    if ( !TRUEP(ab_current_node__1) || ab_current_node__1 && 
		    ab_connection__1 && EQ(ISVREF(ab_connection__1,
		    (SI_Long)2L),cloned_block_at_other_end))
		goto end_10;
	    goto next_loop_13;
	  end_loop_13:
	  end_10:
	    if ( !TRUEP(ab_current_node__1))
		goto end_loop_14;
	    cloned_connection = ab_connection__1;
	    gensymed_symbol = CDR(cloned_connection_table_at_other_end);
	    gensymed_symbol_1 = cloned_connection;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(cloned_connection) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_15:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_15;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_16:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_16;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    cloned_connection_item = M_CDR(M_CAR(gensymed_symbol));
		    goto end_11;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_16;
	      end_loop_16:
		cloned_connection_item = Qnil;
	      end_11:;
		goto end_12;
	    }
	    goto next_loop_15;
	  end_loop_15:
	    cloned_connection_item = Qnil;
	  end_12:;
	    if ( !TRUEP(ISVREF(cloned_connection_item,(SI_Long)5L))) {
		temp_2 = ISVREF(cloned_connection_item,(SI_Long)2L);
		temp = ISVREF(connection_item_at_other_end,(SI_Long)2L);
		temp_1 = EQUAL(temp_2,temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? FIXNUM_EQ(ISVREF(cloned_connection,(SI_Long)4L),
		    ISVREF(block_connection,(SI_Long)4L)) : TRUEP(Nil)) {
		SVREF(cloned_connection_item,FIX((SI_Long)5L)) = T;
		cloned_connection_stub = cloned_connection;
		goto end_13;
	    }
	    goto next_loop_12;
	  end_loop_14:
	    cloned_connection_stub = Qnil;
	  end_13:;
	  POP_SPECIAL();
	  make_cloned_connection_stub_be_copy_of_connection(cloned_block_connection,
		  cloned_connection_stub,block_connection,cloned_block,
		  cloned_block_at_other_end);
	  gensymed_symbol = CDR(cloned_connection_table);
	  gensymed_symbol_1 = cloned_connection_stub;
	  gensymed_symbol_2 = SXHASH_SYMBOL_1(cloned_connection_stub) & 
		  IFIX(Most_positive_fixnum);
	  gensymed_symbol_3 = (SI_Long)0L;
	next_loop_17:
	  if ( !TRUEP(gensymed_symbol))
	      goto end_loop_17;
	  gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	  if (gensymed_symbol_2 < gensymed_symbol_3)
	      gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	  else if (gensymed_symbol_2 > gensymed_symbol_3)
	      gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	  else {
	      gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	      gensymed_symbol_4 = Nil;
	    next_loop_18:
	      if ( !TRUEP(gensymed_symbol))
		  goto end_loop_18;
	      gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	      if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		  cloned_connection_stub_connection_item = 
			  M_CDR(M_CAR(gensymed_symbol));
		  goto end_14;
	      }
	      gensymed_symbol = M_CDR(gensymed_symbol);
	      goto next_loop_18;
	    end_loop_18:
	      cloned_connection_stub_connection_item = Qnil;
	    end_14:;
	      goto end_15;
	  }
	  goto next_loop_17;
	end_loop_17:
	  cloned_connection_stub_connection_item = Qnil;
	end_15:;
	  SVREF(cloned_connection_stub_connection_item,FIX((SI_Long)4L)) = T;
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qconnection_item_table;  /* connection-item-table */

static Object Qab_gensym;          /* gensym */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* CLONE-CONNECTIONS-SLOT */
Object clone_connections_slot(old_slot_value,old_frame,new_frame,
	    blocks_in_bounding_box_qm)
    Object old_slot_value, old_frame, new_frame, blocks_in_bounding_box_qm;
{
    Object new_cons, gensymed_symbol, new_connection_table, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_next_node_qm_;
    Object ab_current_alist_, ab_entry_cons_, connection, connection_item;
    Object new_connection, new_connection_item, ab_less_than_branch_qm_, temp;
    Object extra_connection, extra_connection_item, temp_1, gensymed_symbol_1;
    Object slot_group_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(102,1);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qconnection_item_table;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    new_connection_table = gensymed_symbol;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_next_node_qm_ = old_slot_value;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    connection = Nil;
    connection_item = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      new_connection = Nil;
      new_connection_item = Nil;
      ab_next_node_qm_ = M_CDR(ab_next_node_qm_);
    next_loop:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else {
	  if (ab_next_node_qm_) {
	      ab_current_node_ = ab_next_node_qm_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_1:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_1;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_qm_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_qm_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_1;
      connection = CAR(ab_entry_cons_);
      connection_item = CDR(ab_entry_cons_);
      new_connection = clone_stub_for_connection(Nil,connection,old_frame,
	      new_frame);
      new_connection_item = make_connection_item_1(new_connection);
      gensymed_symbol = new_connection;
      temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	      IFIX(Most_positive_fixnum));
      set_balanced_binary_tree_entry(new_connection_table,Qeq,Nil,T,
	      gensymed_symbol,temp,new_connection_item);
      if (ISVREF(connection_item,(SI_Long)3L)) {
	  extra_connection = clone_stub_for_connection(connection,
		  connection,old_frame,new_frame);
	  extra_connection_item = make_connection_item_1(extra_connection);
	  gensymed_symbol = extra_connection;
	  set_balanced_binary_tree_entry(new_connection_table,Qeq,Nil,T,
		  gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		  IFIX(Most_positive_fixnum)),extra_connection_item);
	  temp_1 = copy_list_using_gensym_conses_1(ISVREF(connection_item,
		  (SI_Long)1L));
	  SVREF(new_connection_item,FIX((SI_Long)1L)) = temp_1;
	  temp_1 = copy_list_using_gensym_conses_1(ISVREF(connection_item,
		  (SI_Long)2L));
	  SVREF(extra_connection_item,FIX((SI_Long)2L)) = temp_1;
      }
      else {
	  temp_1 = copy_list_using_gensym_conses_1(ISVREF(connection_item,
		  (SI_Long)1L));
	  SVREF(new_connection_item,FIX((SI_Long)1L)) = temp_1;
	  temp_1 = copy_list_using_gensym_conses_1(ISVREF(connection_item,
		  (SI_Long)2L));
	  SVREF(new_connection_item,FIX((SI_Long)2L)) = temp_1;
      }
      goto next_loop;
    end_loop_1:
      gensymed_symbol = new_frame;
      gensymed_symbol_1 = Nil;
      slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
      gensymed_symbol_1 = new_connection_table;
      if (slot_group_qm)
	  SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_1;
      else if ( !EQ(gensymed_symbol_1,Qnil)) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	  temp_1 = make_icon_slot_group_1();
	  SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
	  temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
	  SVREF(temp_1,FIX((SI_Long)6L)) = gensymed_symbol_1;
      }
      result = VALUES_1(Nil);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* MAKE-CLONED-CONNECTION-STUB-BE-COPY-OF-CONNECTION */
Object make_cloned_connection_stub_be_copy_of_connection(cloned_block_connection,
	    cloned_connection_stub,connection,cloned_block,
	    cloned_block_at_other_end)
    Object cloned_block_connection, cloned_connection_stub, connection;
    Object cloned_block, cloned_block_at_other_end;
{
    Object gensymed_symbol, cloned_block_connection_table, gensymed_symbol_1;
    Object gensymed_symbol_4, cloned_block_connection_item;
    Object cloned_connection_stub_item, svref_new_value, output_loose_end;
    Object input_loose_end;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char same_cloned_block_qm, temp;

    x_note_fn_call(102,2);
    same_cloned_block_qm = EQ(cloned_block,cloned_block_at_other_end);
    gensymed_symbol = ISVREF(cloned_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    cloned_block_connection_table = gensymed_symbol;
    gensymed_symbol = CDR(cloned_block_connection_table);
    gensymed_symbol_1 = cloned_block_connection;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(cloned_block_connection) & 
	    IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    cloned_block_connection_item = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	cloned_block_connection_item = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    cloned_block_connection_item = Qnil;
  end_2:;
    gensymed_symbol = cloned_block_connection;
    set_balanced_binary_tree_entry(cloned_block_connection_table,Qeq,Nil,T,
	    gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Nil);
    delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
	    cloned_block_connection,cloned_block_connection_table,
	    FIX(SXHASH_SYMBOL_1(cloned_block_connection) & 
	    IFIX(Most_positive_fixnum)));
    if (same_cloned_block_qm) {
	gensymed_symbol = CDR(cloned_block_connection_table);
	gensymed_symbol_1 = cloned_connection_stub;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(cloned_connection_stub) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_3:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_3;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		cloned_connection_stub_item = M_CDR(M_CAR(gensymed_symbol));
		goto end_3;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	    cloned_connection_stub_item = Qnil;
	  end_3:;
	    goto end_4;
	}
	goto next_loop_2;
      end_loop_2:
	cloned_connection_stub_item = Qnil;
      end_4:;
	svref_new_value = ISVREF(cloned_block_connection_item,(SI_Long)1L);
	SVREF(cloned_connection_stub_item,FIX((SI_Long)1L)) = svref_new_value;
	reclaim_connection_item_1(cloned_block_connection_item);
	SVREF(cloned_connection_stub_item,FIX((SI_Long)3L)) = T;
    }
    else {
	SVREF(cloned_block_connection_item,FIX((SI_Long)0L)) = 
		cloned_connection_stub;
	gensymed_symbol = cloned_connection_stub;
	set_balanced_binary_tree_entry(cloned_block_connection_table,Qeq,
		Nil,T,gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
		& IFIX(Most_positive_fixnum)),cloned_block_connection_item);
    }
    delete_connection(3,cloned_block_connection,Nil,cloned_block);
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol_2 = IFIX(ISVREF(cloned_connection_stub,
		(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol_2) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(cloned_connection_stub);
    svref_new_value = copy_list_using_gensym_conses_1(ISVREF(connection,
	    (SI_Long)6L));
    SVREF(cloned_connection_stub,FIX((SI_Long)6L)) = svref_new_value;
    output_loose_end = ISVREF(cloned_connection_stub,(SI_Long)2L);
    input_loose_end = ISVREF(cloned_connection_stub,(SI_Long)3L);
    if (EQ(output_loose_end,cloned_block_at_other_end)) {
	delete_connection_in_block(input_loose_end,cloned_connection_stub,Nil);
	delete_frame(input_loose_end);
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_2 = IFIX(ISVREF(cloned_connection_stub,
		    (SI_Long)7L)) & (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_2) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(cloned_connection_stub);
	SVREF(cloned_connection_stub,FIX((SI_Long)3L)) = cloned_block;
    }
    else if (EQ(input_loose_end,cloned_block_at_other_end)) {
	delete_connection_in_block(output_loose_end,cloned_connection_stub,
		Nil);
	delete_frame(output_loose_end);
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_2 = IFIX(ISVREF(cloned_connection_stub,
		    (SI_Long)7L)) & (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_2) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(cloned_connection_stub);
	SVREF(cloned_connection_stub,FIX((SI_Long)2L)) = cloned_block;
    }
    else;
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol_2 = IFIX(ISVREF(cloned_connection_stub,
		(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol_2) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(cloned_connection_stub);
    svref_new_value = ISVREF(connection,(SI_Long)5L);
    SVREF(cloned_connection_stub,FIX((SI_Long)5L)) = svref_new_value;
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol_2 = IFIX(ISVREF(cloned_connection_stub,
		(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol_2) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(cloned_connection_stub);
    svref_new_value = ISVREF(connection,(SI_Long)4L);
    SVREF(cloned_connection_stub,FIX((SI_Long)4L)) = svref_new_value;
    determine_subworkspace_connection_posts_for_object(cloned_connection_stub,
	    ISVREF(cloned_connection_stub,(SI_Long)2L));
    return determine_subworkspace_connection_posts_for_object(cloned_connection_stub,
	    ISVREF(cloned_connection_stub,(SI_Long)3L));
}

static Object Qsuperior_connection;  /* superior-connection */

/* PUT-SUPERIOR-CONNECTION */
Object put_superior_connection(connection_post,
	    superior_connection_designation,initializing_qm)
    Object connection_post, superior_connection_designation, initializing_qm;
{
    Object old_translation_qm, gensymed_symbol, superblock_qm;
    Object sub_class_bit_vector, superior_block_qm;
    Object old_designated_connection_qm, new_designated_connection_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(102,3);
    if (Loading_kb_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(connection_post,Qsuperior_connection);
	return set_lookup_slot_value_1(connection_post,
		Qsuperior_connection,superior_connection_designation);
    }
    else {
	old_translation_qm =  !TRUEP(initializing_qm) ? 
		get_lookup_slot_value_given_default(connection_post,
		Qsuperior_connection,Nil) : Nil;
	gensymed_symbol = ISVREF(connection_post,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)5L) : Nil;
	superblock_qm = gensymed_symbol;
	if (superblock_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(superblock_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	superior_block_qm = temp ? ISVREF(superblock_qm,(SI_Long)18L) : Nil;
	old_designated_connection_qm = superior_block_qm ? 
		get_connection_given_stub_designation(superior_block_qm,
		old_translation_qm) : Nil;
	new_designated_connection_qm = superior_block_qm ? 
		get_connection_given_stub_designation(superior_block_qm,
		superior_connection_designation) : Nil;
	if (old_designated_connection_qm)
	    remove_subworkspace_connection_post_from_connection(old_designated_connection_qm,
		    connection_post,EQ(ISVREF(old_designated_connection_qm,
		    (SI_Long)3L),superior_block_qm) ? T : Nil,Nil);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(connection_post,Qsuperior_connection);
	set_lookup_slot_value_1(connection_post,Qsuperior_connection,
		superior_connection_designation);
	if (new_designated_connection_qm)
	    add_subworkspace_connection_post_to_connection(new_designated_connection_qm,
		    connection_post,EQ(ISVREF(new_designated_connection_qm,
		    (SI_Long)3L),superior_block_qm) ? T : Nil);
	return VALUES_1(superior_connection_designation);
    }
}

/* HANDLE-CONNECTION-POST-ADDITION-OR-REMOVAL-AS-SUBBLOCK */
Object handle_connection_post_addition_or_removal_as_subblock(item,removal_qm)
    Object item, removal_qm;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(102,4);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Connection_post_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return handle_connection_post_addition_or_removal_as_subblock_1(item,
		removal_qm);
    else
	return VALUES_1(Nil);
}

/* HANDLE-CONNECTION-POST-ADDITION-OR-REMOVAL-AS-SUBBLOCK-1 */
Object handle_connection_post_addition_or_removal_as_subblock_1(connection_post,
	    removal_qm)
    Object connection_post, removal_qm;
{
    Object superior_connection_designation, gensymed_symbol, superblock_qm;
    Object sub_class_bit_vector, superior_block_qm, designated_connection_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(102,5);
    superior_connection_designation = 
	    get_lookup_slot_value_given_default(connection_post,
	    Qsuperior_connection,Nil);
    gensymed_symbol = ISVREF(connection_post,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)5L) : Nil;
    superblock_qm = gensymed_symbol;
    if (superblock_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(superblock_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
    superior_block_qm = temp ? ISVREF(superblock_qm,(SI_Long)18L) : Nil;
    designated_connection_qm = superior_block_qm ? 
	    get_connection_given_stub_designation(superior_block_qm,
	    superior_connection_designation) : Nil;
    if (designated_connection_qm) {
	if (removal_qm) {
	    if (EQ(ISVREF(designated_connection_qm,(SI_Long)3L),
		    ISVREF(designated_connection_qm,(SI_Long)2L))) {
		remove_subworkspace_connection_post_from_connection(designated_connection_qm,
			connection_post,T,Nil);
		return remove_subworkspace_connection_post_from_connection(designated_connection_qm,
			connection_post,Nil,Nil);
	    }
	    else
		return remove_subworkspace_connection_post_from_connection(designated_connection_qm,
			connection_post,EQ(ISVREF(designated_connection_qm,
			(SI_Long)3L),superior_block_qm) ? T : Nil,Nil);
	}
	else
	    return add_subworkspace_connection_post_to_connection(designated_connection_qm,
		    connection_post,EQ(ISVREF(designated_connection_qm,
		    (SI_Long)3L),superior_block_qm) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DETERMINE-SUBWORKSPACE-CONNECTION-POSTS */
Object determine_subworkspace_connection_posts(object)
    Object object;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(102,6);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      determine_subworkspace_connection_posts_for_object(connection,object);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* DETERMINE-SUBWORKSPACE-CONNECTION-POSTS-FOR-OBJECT */
Object determine_subworkspace_connection_posts_for_object(connection,object)
    Object connection, object;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, subworkspace;
    Object ab_loop_list_, ab_queue_form_, ab_next_queue_element_, block;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(102,7);
    if (SIMPLE_VECTOR_P(object) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(object,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(object,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Object_class_description,
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
	subworkspace = Nil;
	ab_loop_list_ = ISVREF(object,(SI_Long)18L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subworkspace = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)4L) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	block = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
      next_loop_1:
	if (EQ(ab_next_queue_element_,ab_queue_form_))
	    goto end_loop_1;
	block = ISVREF(ab_next_queue_element_,(SI_Long)2L);
	ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_post_class_description,(SI_Long)18L));
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
	if (temp ? EQ(get_connection_given_stub_designation(object,
		get_lookup_slot_value_given_default(block,
		Qsuperior_connection,Nil)),connection) : TRUEP(Nil))
	    add_subworkspace_connection_post_to_connection(connection,
		    block,EQ(ISVREF(connection,(SI_Long)3L),object) ? T : Nil);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* FLUSH-ALL-SUBWORKSPACE-CONNECTION-POSTS-FOR-OBJECT */
Object flush_all_subworkspace_connection_posts_for_object(object,
	    delete_dangling_connection_posts_qm)
    Object object, delete_dangling_connection_posts_qm;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(102,8);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      flush_subworkspace_connection_posts_for_object(connection,object,
	      delete_dangling_connection_posts_qm);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qinput;              /* input */

static Object Qoutput;             /* output */

/* FLUSH-SUBWORKSPACE-CONNECTION-POSTS-FOR-OBJECT */
Object flush_subworkspace_connection_posts_for_object(connection,object,
	    delete_dangling_connection_posts_qm)
    Object connection, object, delete_dangling_connection_posts_qm;
{
    x_note_fn_call(102,9);
    if (EQ(ISVREF(connection,(SI_Long)3L),object))
	return flush_subworkspace_connection_posts(connection,Qinput,
		delete_dangling_connection_posts_qm);
    else
	return flush_subworkspace_connection_posts(connection,Qoutput,
		delete_dangling_connection_posts_qm);
}

static Object Qinput_end_subworkspace_connection_posts;  /* input-end-subworkspace-connection-posts */

static Object Qoutput_end_subworkspace_connection_posts;  /* output-end-subworkspace-connection-posts */

/* FLUSH-SUBWORKSPACE-CONNECTION-POSTS */
Object flush_subworkspace_connection_posts(connection,input_or_output_qm,
	    delete_dangling_connection_posts_qm)
    Object connection, input_or_output_qm, delete_dangling_connection_posts_qm;
{
    x_note_fn_call(102,10);
    if (EQ(input_or_output_qm,Qinput))
	return flush_subworkspace_connection_post_set(connection,
		getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
		Qinput_end_subworkspace_connection_posts),T,
		delete_dangling_connection_posts_qm);
    else if (EQ(input_or_output_qm,Qoutput))
	return flush_subworkspace_connection_post_set(connection,
		getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
		Qoutput_end_subworkspace_connection_posts),Nil,
		delete_dangling_connection_posts_qm);
    else {
	flush_subworkspace_connection_post_set(connection,
		getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
		Qinput_end_subworkspace_connection_posts),T,
		delete_dangling_connection_posts_qm);
	return flush_subworkspace_connection_post_set(connection,
		getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
		Qoutput_end_subworkspace_connection_posts),Nil,
		delete_dangling_connection_posts_qm);
    }
}

/* FLUSH-SUBWORKSPACE-CONNECTION-POST-SET */
Object flush_subworkspace_connection_post_set(connection,
	    connection_post_set,input_end_qm,
	    delete_dangling_connection_posts_qm)
    Object connection, connection_post_set, input_end_qm;
    Object delete_dangling_connection_posts_qm;
{
    Object copy_of_connection_post_set, connection_post, ab_loop_list_;

    x_note_fn_call(102,11);
    copy_of_connection_post_set = 
	    copy_list_using_gensym_conses_1(connection_post_set);
    connection_post = Nil;
    ab_loop_list_ = copy_of_connection_post_set;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connection_post = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    remove_subworkspace_connection_post_from_connection(connection,
	    connection_post,input_end_qm,delete_dangling_connection_posts_qm);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(copy_of_connection_post_set);
}

/* ADD-SUBWORKSPACE-CONNECTION-POST-TO-CONNECTION */
Object add_subworkspace_connection_post_to_connection(connection,
	    connection_post,input_end_qm)
    Object connection, connection_post, input_end_qm;
{
    x_note_fn_call(102,12);
    decache_roles_for_connection_post(connection_post);
    return add_or_delete_subworkspace_connection_post_from_connection(connection,
	    connection_post,input_end_qm,Nil,Nil);
}

/* REMOVE-SUBWORKSPACE-CONNECTION-POST-FROM-CONNECTION */
Object remove_subworkspace_connection_post_from_connection(connection,
	    connection_post,input_end_qm,delete_dangling_connection_posts_qm)
    Object connection, connection_post, input_end_qm;
    Object delete_dangling_connection_posts_qm;
{
    x_note_fn_call(102,13);
    decache_roles_for_connection_post(connection_post);
    return add_or_delete_subworkspace_connection_post_from_connection(connection,
	    connection_post,input_end_qm,T,
	    delete_dangling_connection_posts_qm);
}

static Object Qsuperior_connection_cache;  /* superior-connection-cache */

/* DELETE-SUBWORKSPACE-CONNECTION-POST-IF-SUPERFLUOUS */
Object delete_subworkspace_connection_post_if_superfluous(connection_post)
    Object connection_post;
{
    Object gensymed_symbol;
    char temp;

    x_note_fn_call(102,14);
    if (get_lookup_slot_value_given_default(connection_post,
	    Qsuperior_connection,Nil) &&  
	    !TRUEP(get_lookup_slot_value_given_default(connection_post,
	    Qsuperior_connection_cache,Nil))) {
	gensymed_symbol = ISVREF(connection_post,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)6L) : Nil;
	temp =  !TRUEP(gensymed_symbol);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return delete_frame(connection_post);
    else
	return VALUES_1(Nil);
}

/* ADD-OR-DELETE-SUBWORKSPACE-CONNECTION-POST-FROM-CONNECTION */
Object add_or_delete_subworkspace_connection_post_from_connection(connection,
	    connection_post,input_end_qm,delete_instead_qm,
	    delete_dangling_connection_posts_qm)
    Object connection, connection_post, input_end_qm, delete_instead_qm;
    Object delete_dangling_connection_posts_qm;
{
    x_note_fn_call(102,15);
    decache_roles_for_entities_related_to_this_connection(connection);
    if (input_end_qm) {
	change_connection_attribute(connection,
		Qinput_end_subworkspace_connection_posts,
		add_or_delete_subworkspace_connection_post(copy_list_using_gensym_conses_1(getfq_function_no_default(ISVREF(connection,
		(SI_Long)9L),Qinput_end_subworkspace_connection_posts)),
		connection_post,delete_instead_qm));
	change_connection_post_connection_cache(connection_post,connection,
		input_end_qm,delete_instead_qm);
    }
    else {
	change_connection_attribute(connection,
		Qoutput_end_subworkspace_connection_posts,
		add_or_delete_subworkspace_connection_post(copy_list_using_gensym_conses_1(getfq_function_no_default(ISVREF(connection,
		(SI_Long)9L),Qoutput_end_subworkspace_connection_posts)),
		connection_post,delete_instead_qm));
	change_connection_post_connection_cache(connection_post,connection,
		input_end_qm,delete_instead_qm);
    }
    if (delete_instead_qm && delete_dangling_connection_posts_qm)
	return delete_subworkspace_connection_post_if_superfluous(connection_post);
    else
	return VALUES_1(Nil);
}

/* CHANGE-CONNECTION-POST-CONNECTION-CACHE */
Object change_connection_post_connection_cache(connection_post,connection,
	    input_end_qm,delete_instead_qm)
    Object connection_post, connection, input_end_qm, delete_instead_qm;
{
    x_note_fn_call(102,16);
    return change_slot_value(3,connection_post,Qsuperior_connection_cache,
	    delete_instead_qm ? Nil : gensym_cons_1(input_end_qm ? Qinput :
	     Qoutput,connection));
}

Object Savable_connection_attributes = UNBOUND;

/* GET-SAVABLE-CONNECTION-ATTRIBUTES-PLIST */
Object get_savable_connection_attributes_plist(connection_attributes_plist)
    Object connection_attributes_plist;
{
    Object attribute, ab_loop_list_, value_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(102,17);
    attribute = Nil;
    ab_loop_list_ = Savable_connection_attributes;
    value_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    value_qm = getfq_function_no_default(connection_attributes_plist,
	    attribute);
    if (value_qm) {
	ab_loopvar__2 = gensym_cons_1(attribute,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = gensym_cons_1(value_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* ADD-SUBWORKSPACE-CONNECTION-POSTS */
Object add_subworkspace_connection_posts(subworkspace,object)
    Object subworkspace, object;
{
    Object gensymed_symbol, connection_table, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection, connection_item;
    Object port_name_qm, temp, ab_less_than_branch_qm_, gensymed_symbol_1;
    Object gensymed_symbol_4;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(102,18);
    gensymed_symbol = ISVREF(object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    connection_table = gensymed_symbol;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      connection_item = Nil;
      port_name_qm = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      gensymed_symbol = CDR(connection_table);
      gensymed_symbol_1 = connection;
      gensymed_symbol_2 = SXHASH_SYMBOL_1(connection) & 
	      IFIX(Most_positive_fixnum);
      gensymed_symbol_3 = (SI_Long)0L;
    next_loop_3:
      if ( !TRUEP(gensymed_symbol))
	  goto end_loop_3;
      gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
      if (gensymed_symbol_2 < gensymed_symbol_3)
	  gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
      else if (gensymed_symbol_2 > gensymed_symbol_3)
	  gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
      else {
	  gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	  gensymed_symbol_4 = Nil;
	next_loop_4:
	  if ( !TRUEP(gensymed_symbol))
	      goto end_loop_4;
	  gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	  if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	      connection_item = M_CDR(M_CAR(gensymed_symbol));
	      goto end_2;
	  }
	  gensymed_symbol = M_CDR(gensymed_symbol);
	  goto next_loop_4;
	end_loop_4:
	  connection_item = Qnil;
	end_2:;
	  goto end_3;
      }
      goto next_loop_3;
    end_loop_3:
      connection_item = Qnil;
    end_3:;
      temp = ISVREF(connection_item,(SI_Long)1L);
      if (temp);
      else
	  temp = ISVREF(connection_item,(SI_Long)2L);
      port_name_qm = CAR(temp);
      add_subworkspace_connection_post(connection,port_name_qm,object,
	      subworkspace);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

Object Disable_stack_error = UNBOUND;

static Object array_constant;      /* # */

static Object Qconnection_post;    /* connection-post */

/* ADD-SUBWORKSPACE-CONNECTION-POST */
Object add_subworkspace_connection_post(connection,port_name_qm,object,
	    subworkspace)
    Object connection, port_name_qm, object, subworkspace;
{
    Object original_end_position, new_side, connection_post_position_on_side;
    Object new_connection_post, connection_post_x, connection_post_y;
    Object disable_stack_error, gensymed_symbol_1, temp;
    SI_Long original_end_position_on_side, gensymed_symbol, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(102,19);
    original_end_position = EQ(ISVREF(connection,(SI_Long)3L),object) ? 
	    ISVREF(connection,(SI_Long)5L) : ISVREF(connection,(SI_Long)4L);
    original_end_position_on_side = IFIX(original_end_position) >>  -  - 
	    (SI_Long)2L;
    new_side = ISVREF(array_constant,IFIX(original_end_position) & 
	    (SI_Long)3L);
    connection_post_position_on_side = 
	    scale_subworkspace_connection_post_position(subworkspace,
	    object,FIX(original_end_position_on_side),new_side);
    new_connection_post = make_entity(1,Qconnection_post);
    connection_post_x = Nil;
    connection_post_y = Nil;
    result = connection_post_x_and_y_given_position_and_side(new_side,
	    connection_post_position_on_side,subworkspace);
    MVS_2(result,connection_post_x,connection_post_y);
    disable_stack_error = T;
    PUSH_SPECIAL(Disable_stack_error,disable_stack_error,0);
      gensymed_symbol = IFIX(connection_post_x);
      gensymed_symbol_1 = ISVREF(subworkspace,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)2L) : FIX((SI_Long)0L);
      gensymed_symbol_2 = IFIX(gensymed_symbol_1);
      gensymed_symbol_1 = ISVREF(subworkspace,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      gensymed_symbol_3 = IFIX(gensymed_symbol_1);
      gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
      gensymed_symbol_3 = (SI_Long)1L;
      gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
      temp = FIX(gensymed_symbol - gensymed_symbol_2);
      gensymed_symbol_1 = ISVREF(subworkspace,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)3L) : FIX((SI_Long)0L);
      gensymed_symbol = IFIX(gensymed_symbol_1);
      gensymed_symbol_1 = ISVREF(subworkspace,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      gensymed_symbol_2 = IFIX(gensymed_symbol_1);
      gensymed_symbol = gensymed_symbol - gensymed_symbol_2;
      gensymed_symbol_2 = (SI_Long)1L;
      gensymed_symbol = gensymed_symbol >>  -  - gensymed_symbol_2;
      gensymed_symbol_2 = IFIX(connection_post_y);
      transfer_blocks_with_their_external_connections(new_connection_post,
	      subworkspace,temp,FIX(gensymed_symbol - gensymed_symbol_2),Nil);
    POP_SPECIAL();
    temp = port_name_qm;
    if (temp);
    else
	temp = gensym_list_2(new_side,FIX(original_end_position_on_side));
    return change_slot_value(3,new_connection_post,Qsuperior_connection,temp);
}

static Object Qleft;               /* left */

static Object Qright;              /* right */

static Object float_constant;      /* 0.0 */

/* SCALE-SUBWORKSPACE-CONNECTION-POST-POSITION */
Object scale_subworkspace_connection_post_position(subworkspace,object,
	    position_on_object,side)
    Object subworkspace, object, position_on_object, side;
{
    Object temp, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    double temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(102,20);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (EQ(side,Qleft) || EQ(side,Qright)) {
	    temp = lfloat(position_on_object,float_constant);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_1 = temp_1 * (double)(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol = ISVREF(object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = DOUBLE_TO_DOUBLE_FLOAT(temp_1 / 
		    (double)(gensymed_symbol_1 - gensymed_symbol_2));
	}
	else {
	    temp = lfloat(position_on_object,float_constant);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_1 = temp_1 * (double)(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol = ISVREF(object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = DOUBLE_TO_DOUBLE_FLOAT(temp_1 / 
		    (double)(gensymed_symbol_1 - gensymed_symbol_2));
	}
	result = l_round(temp,_);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

Object Connection_post_indentation = UNBOUND;

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

/* CONNECTION-POST-X-AND-Y-GIVEN-POSITION-AND-SIDE */
Object connection_post_x_and_y_given_position_and_side(side,
	    position_on_side,subworkspace)
    Object side, position_on_side, subworkspace;
{
    Object x, y, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(102,21);
    x = Nil;
    y = Nil;
    if (EQ(side,Qleft)) {
	x = Connection_post_indentation;
	y = position_on_side;
    }
    else if (EQ(side,Qtop)) {
	y = Connection_post_indentation;
	x = position_on_side;
    }
    else if (EQ(side,Qright)) {
	gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(Connection_post_indentation);
	x = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	y = position_on_side;
    }
    else if (EQ(side,Qbottom)) {
	gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(subworkspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(Connection_post_indentation);
	y = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	x = position_on_side;
    }
    return VALUES_2(x,y);
}

void connect4_INIT()
{
    Object AB_package, list_constant, Qsavable_connection_attributes;
    Object Qconnection_arrows, Qline_pattern, Qconnection_style;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qslot_putter;
    Object Qput_superior_connection;

    x_note_fn_call(102,22);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qsuperior_connection = STATIC_SYMBOL("SUPERIOR-CONNECTION",AB_package);
    Qput_superior_connection = STATIC_SYMBOL("PUT-SUPERIOR-CONNECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_superior_connection,
	    STATIC_FUNCTION(put_superior_connection,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qsuperior_connection,
	    SYMBOL_FUNCTION(Qput_superior_connection),Qslot_putter);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qinput_end_subworkspace_connection_posts = 
	    STATIC_SYMBOL("INPUT-END-SUBWORKSPACE-CONNECTION-POSTS",
	    AB_package);
    Qoutput_end_subworkspace_connection_posts = 
	    STATIC_SYMBOL("OUTPUT-END-SUBWORKSPACE-CONNECTION-POSTS",
	    AB_package);
    Qsuperior_connection_cache = STATIC_SYMBOL("SUPERIOR-CONNECTION-CACHE",
	    AB_package);
    Qsavable_connection_attributes = 
	    STATIC_SYMBOL("SAVABLE-CONNECTION-ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsavable_connection_attributes,
	    Savable_connection_attributes);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    Qconnection_arrows = STATIC_SYMBOL("CONNECTION-ARROWS",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qconnection_style,
	    Qline_pattern,Qconnection_arrows);
    SET_SYMBOL_VALUE(Qsavable_connection_attributes,list_constant);
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    ISASET_1(array_constant,(SI_Long)0L,Qtop);
    ISASET_1(array_constant,(SI_Long)1L,Qleft);
    ISASET_1(array_constant,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant,(SI_Long)3L,Qright);
    Qconnection_post = STATIC_SYMBOL("CONNECTION-POST",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Connection_post_indentation = FIX((SI_Long)10L);
}
