/* initvars.h -- initial variables/constants for translator runtime
 *
 * Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
 *
 *
 * This file contains extern declarations for all the global variables provided
 * initially provided by Lisp, including any Chestnut extensions.  Variables
 * are annotated with the location of their initialization code.
 */

/* Initialization function declarations. */
#ifdef SI_RUNTIME_INTERNAL
extern void SI_INIT_evals();		/* evals.c */
extern void SI_INIT_format();		/* format.c */
extern void SI_INIT_filesys();		/* filesys.c */
extern void SI_INIT_io();		/* io.c */
extern void SI_INIT_misc();		/* misc.c */
extern void SI_INIT_numbers();		/* numbers.c */
extern void SI_INIT_packages_1();	/* packages.c */
extern void SI_INIT_packages_2();	/* packages.c */
extern void SI_INIT_streams();		/* streams.c */
#endif

/* *** CL package *** */

/* SI_INIT_evals() */
extern Object Star;			/* "*" */
extern Object Star_star;		/* "**" */
extern Object Star_star_star;		/* "***" */

extern Object Break_on_signals; 	/* not yet initialized */

/* SI_INIT_filesys() in filesys.c: */
DECLARE_VARIABLE(Load_pathname);
DECLARE_VARIABLE(Load_print);
DECLARE_VARIABLE(Load_truename);
DECLARE_VARIABLE(Load_verbose);
extern Object Compile_file_pathname;
extern Object Compile_print; 
extern Object Compile_file_truename; 
extern Object Compile_verbose; 
extern Object Default_pathname_defaults; 

DECLARE_VARIABLE(Debug_io);	/* SI_INIT_streams() */
extern Object Qdebug_io;	/* SI_INIT_streams() */

extern Object Debugger_hook; 

DECLARE_VARIABLE(Error_output);	/* SI_INIT_streams() */
extern Object Qerror_output;	/* SI_INIT_streams() */

extern Object Features;                 /* SI_INIT_misc() */

extern Object Gensym_counter; 

/* macros.c */
extern Object Macroexpand_hook; 

DECLARE_VARIABLE(Package);      /* SI_INIT_packages() */
extern Object Qpackage_variable;      /* SI_INIT_packages() */

/* SI_INIT_format() */
DECLARE_VARIABLE(Print_array);
extern Object Qprint_array;
DECLARE_VARIABLE(Print_base);
extern Object Qprint_base;
DECLARE_VARIABLE(Print_case);
extern Object Qprint_case;
DECLARE_VARIABLE(Print_circle);
extern Object Qprint_circle;
DECLARE_VARIABLE(Print_escape);
DECLARE_VARIABLE(Print_gensym);
DECLARE_VARIABLE(Print_length);
extern Object Qprint_length;
DECLARE_VARIABLE(Print_level);
DECLARE_VARIABLE(Print_lines);
DECLARE_VARIABLE(Print_miser_width);
DECLARE_VARIABLE(Print_pprint_dispatch);
DECLARE_VARIABLE(Print_pretty);
DECLARE_VARIABLE(Print_radix);
DECLARE_VARIABLE(Print_readably);
DECLARE_VARIABLE(Print_right_margin);

extern Object Query_io; 		/* SI_INIT_streams() */

extern Object Random_state; 

/* SI_INIT_io() in io.c */
DECLARE_VARIABLE(Read_base);
extern Object Qread_base;
DECLARE_VARIABLE(Read_default_float_format);
extern Object Qread_default_float_format;
extern Object Read_eval; 
extern Object Read_suppress; 

extern Object Readtable;                /* init.c */

/* SI_INIT_streams() */
DECLARE_VARIABLE(Standard_input);
extern Object Qstandard_input;
DECLARE_VARIABLE(Standard_output);
extern Object Qstandard_output;
DECLARE_VARIABLE(Terminal_io);
extern Object Qterminal_io;
extern Object Trace_output;

/* SI_INIT_evals() */
extern Object Plus;			/* "+" */
extern Object Plus_plus;		/* "++" */
extern Object Plus_plus_plus;		/* "+++" */
extern Object Us;			/* "-" */
extern Object Sl;			/* "/" */
extern Object Sl_sl;			/* "//" */
extern Object Sl_sl_sl;			/* "///" */

/* Array_dimension_limit */ 
/* Array_rank_limit */ 
/* Array_total_size_limit */ 
/* Boole_1 */ 
/* Boole_2 */ 
/* Boole_and */ 
/* Boole_andc1 */ 
/* Boole_andc2 */ 
/* Boole_c1 */ 
/* Boole_c2 */ 
/* Boole_clr */ 
/* Boole_eqv */ 
/* Boole_ior */ 
/* Boole_nand */ 
/* Boole_nor */ 
/* Boole_orc1 */ 
/* Boole_orc2 */ 
/* Boole_set */ 
/* Boole_xor */ 
/* Call_arguments_limit */ 
/* Char_code_limit */ 

/* All of the following floating point constants are initialized by
 * SI_INIT_numbers(), in numbers.c. */
extern Object Double_float_epsilon; 
extern Object Double_float_negative_epsilon; 

extern Object Internal_time_units_per_second;	/* SI_INIT_misc() */

extern Object Lambda_list_keywords;	/* SI_INIT_evals() */

/* Lambda_parameters_limit */

/* All of the following floating point constants are initialized by
 * SI_INIT_numbers(), in numbers.c. */
extern Object Least_negative_double_float;
extern Object Least_negative_long_float;
extern Object Least_negative_normalized_double_float;
extern Object Least_negative_normalized_long_float;
extern Object Least_negative_normalized_short_float;
extern Object Least_negative_normalized_single_float;
extern Object Least_negative_short_float;
extern Object Least_negative_single_float;
extern Object Least_positive_double_float;
extern Object Least_positive_long_float;
extern Object Least_positive_normalized_double_float;
extern Object Least_positive_normalized_long_float;
extern Object Least_positive_normalized_short_float;
extern Object Least_positive_normalized_single_float;
extern Object Least_positive_short_float;
extern Object Least_positive_single_float;
extern Object Long_float_epsilon;
extern Object Long_float_negative_epsilon;
extern Object Most_negative_double_float;

/* Most_negative_fixnum */

/* All of the following floating point constants are initialized by
 * SI_INIT_numbers(), in numbers.c. */
extern Object Most_negative_long_float;
extern Object Most_negative_short_float;
extern Object Most_negative_single_float;
extern Object Most_positive_double_float;

/* Most_positive_fixnum */

/* All of the following floating point constants are initialized by
 * SI_INIT_numbers(), in numbers.c. */
extern Object Most_positive_long_float;
extern Object Most_positive_short_float;
extern Object Most_positive_single_float;

/* Multiple_values_limit */

extern Object Pi; 		/* SI_INIT_numbers() (numbers.c) */

/* All of the following floating point constants are initialized by
 * SI_INIT_numbers(), in numbers.c. */
extern Object Short_float_epsilon;
extern Object Short_float_negative_epsilon;
extern Object Single_float_epsilon;
extern Object Single_float_negative_epsilon;

/* *** RUN package *** */

extern Object Break_function;
extern Object Gc_inhibit; 
extern Object Gc_silence; 
extern long SI_gc_silence_init;

/* Used by the corresponding functions.
 * Partially initialized by SI_INIT_misc(), but not to a useful value.
 */
extern Object Long_site_name_string;
extern Object Short_site_name_string;

/* _				"TRUN:%UNSUPPLIED_MARKER" (object.h) */

/* *** CLOS-RUN package *** */

#if SI_SUPPORT_CLOS

/* Initialized by SI_INIT_method_combination() (methcomb.c) */
extern Object Generic_function_for_method_combination_errors; 
extern Object Method_combination_effective_method; 
extern Object Method_combination_for_method_combination_errors; 

#endif
