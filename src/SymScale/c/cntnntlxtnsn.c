/* cntnntlxtnsn.c
 * Input file:  continentalextension.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cntnntlxtnsn.h"


/* KB-G2NKE-HISTORICAL-MEAN */
Object kb_g2nke_historical_mean(history,window_size,start_index)
    Object history, window_size, start_index;
{
    x_note_fn_call(238,0);
    return make_evaluation_quantity(g2nke_historical_mean(history,
	    window_size,start_index));
}

/* KB-G2NKE-HISTORICAL-VARIANCE */
Object kb_g2nke_historical_variance(history,window_size,start_index)
    Object history, window_size, start_index;
{
    x_note_fn_call(238,1);
    return make_evaluation_quantity(g2nke_historical_variance(history,
	    window_size,start_index));
}

void continentalextension_INIT()
{
    Object gensymed_symbol;
    Object Qkb_g2nke_historical_variance;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qkb_g2nke_historical_mean;

    x_note_fn_call(238,2);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qkb_g2nke_historical_mean = STATIC_SYMBOL("KB-G2NKE-HISTORICAL-MEAN",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2nke_historical_mean,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2nke_historical_mean,
	    STATIC_FUNCTION(kb_g2nke_historical_mean,NIL,FALSE,3,3));
    Qkb_g2nke_historical_variance = 
	    STATIC_SYMBOL("KB-G2NKE-HISTORICAL-VARIANCE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2nke_historical_variance,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2nke_historical_variance,
	    STATIC_FUNCTION(kb_g2nke_historical_variance,NIL,FALSE,3,3));
}
