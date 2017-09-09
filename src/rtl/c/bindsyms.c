
#include "runtime.h"

extern Object Compile_file_pathname;
extern Object Compile_file_truename;
extern Object Compile_print;
extern Object Compile_verbose;
DECLARE_VARIABLE(Debug_io);
extern Object Default_pathname_defaults;
extern Object Double_float_epsilon;
extern Object Double_float_negative_epsilon;
DECLARE_VARIABLE(Error_output);
extern Object Features;
extern Object Gc_inhibit;
extern Object Gc_silence;
extern Object Internal_time_units_per_second;
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
DECLARE_VARIABLE(Load_pathname);
DECLARE_VARIABLE(Load_print);
DECLARE_VARIABLE(Load_truename);
DECLARE_VARIABLE(Load_verbose);
extern Object Long_float_epsilon;
extern Object Long_float_negative_epsilon;
extern Object Modules;
extern Object Most_negative_double_float;
extern Object Most_negative_long_float;
extern Object Most_negative_short_float;
extern Object Most_negative_single_float;
extern Object Most_positive_double_float;
extern Object Most_positive_long_float;
extern Object Most_positive_short_float;
extern Object Most_positive_single_float;
DECLARE_VARIABLE(Package);
extern Object Pcl;
extern Object Pi;
DECLARE_VARIABLE(Print_array);
DECLARE_VARIABLE(Print_base);
DECLARE_VARIABLE(Print_case);
DECLARE_VARIABLE(Print_circle);
DECLARE_VARIABLE(Print_escape);
DECLARE_VARIABLE(Print_gensym);
DECLARE_VARIABLE(Print_length);
DECLARE_VARIABLE(Print_level);
DECLARE_VARIABLE(Print_lines);
DECLARE_VARIABLE(Print_miser_width);
DECLARE_VARIABLE(Print_pprint_dispatch);
DECLARE_VARIABLE(Print_pretty);
DECLARE_VARIABLE(Print_radix);
DECLARE_VARIABLE(Print_readably);
DECLARE_VARIABLE(Print_right_margin);
extern Object Ptrun;
extern Object Qcompile_file_pathname;
extern Object Qcompile_file_truename;
extern Object Qcompile_print;
extern Object Qcompile_verbose;
extern Object Qdebug_io;
extern Object Qdefault_pathname_defaults;
extern Object Qdouble_float_epsilon;
extern Object Qdouble_float_negative_epsilon;
extern Object Qerror_output;
extern Object Qfeatures;
extern Object Qgc_inhibit;
extern Object Qgc_silence;
extern Object Qinternal_time_units_per_second;
extern Object Qleast_negative_double_float;
extern Object Qleast_negative_long_float;
extern Object Qleast_negative_normalized_double_float;
extern Object Qleast_negative_normalized_long_float;
extern Object Qleast_negative_normalized_short_float;
extern Object Qleast_negative_normalized_single_float;
extern Object Qleast_negative_short_float;
extern Object Qleast_negative_single_float;
extern Object Qleast_positive_double_float;
extern Object Qleast_positive_long_float;
extern Object Qleast_positive_normalized_double_float;
extern Object Qleast_positive_normalized_long_float;
extern Object Qleast_positive_normalized_short_float;
extern Object Qleast_positive_normalized_single_float;
extern Object Qleast_positive_short_float;
extern Object Qleast_positive_single_float;
extern Object Qload_pathname;
extern Object Qload_print;
extern Object Qload_truename;
extern Object Qload_verbose;
extern Object Qlong_float_epsilon;
extern Object Qlong_float_negative_epsilon;
extern Object Qmodules;
extern Object Qmost_negative_double_float;
extern Object Qmost_negative_long_float;
extern Object Qmost_negative_short_float;
extern Object Qmost_negative_single_float;
extern Object Qmost_positive_double_float;
extern Object Qmost_positive_long_float;
extern Object Qmost_positive_short_float;
extern Object Qmost_positive_single_float;
extern Object Qpackage_variable;
extern Object Qpi;
extern Object Qprint_array;
extern Object Qprint_base;
extern Object Qprint_case;
extern Object Qprint_circle;
extern Object Qprint_escape;
extern Object Qprint_gensym;
extern Object Qprint_length;
extern Object Qprint_level;
extern Object Qprint_lines;
extern Object Qprint_miser_width;
extern Object Qprint_pprint_dispatch;
extern Object Qprint_pretty;
extern Object Qprint_radix;
extern Object Qprint_readably;
extern Object Qprint_right_margin;
extern Object Qquery_io;
extern Object Qread_base;
extern Object Qread_default_float_format;
extern Object Qread_eval;
extern Object Qread_suppress;
extern Object Qshort_float_epsilon;
extern Object Qshort_float_negative_epsilon;
extern Object Qsingle_float_epsilon;
extern Object Qsingle_float_negative_epsilon;
extern Object Qstandard_input;
extern Object Qstandard_output;
extern Object Qterminal_io;
extern Object Qtrace_output;
extern Object Query_io;
DECLARE_VARIABLE(Read_base);
DECLARE_VARIABLE(Read_default_float_format);
extern Object Read_eval;
extern Object Read_suppress;
extern Object Short_float_epsilon;
extern Object Short_float_negative_epsilon;
extern Object Single_float_epsilon;
extern Object Single_float_negative_epsilon;
DECLARE_VARIABLE(Standard_input);
DECLARE_VARIABLE(Standard_output);
DECLARE_VARIABLE(Terminal_io);
extern Object Trace_output;

#if SI_USE_PROTOTYPES

extern void SI_INIT_evals();
extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern void SI_set_symbol_value_location(Object symbol, Object *address);

#else

extern void SI_INIT_evals();
extern Object SI_set_symbol_field();
extern void SI_set_symbol_value_location();

#endif



extern Object Internal_time_units_per_second;
extern Object NEW_SYMBOL();

/* 
   Establish correspondence between CLtL symbols and value-holding
   RTL variables (locations). Derived from SI_initsyms()
   called by SI_INIT_packages()
   Some day might be generated automatically as the translator\'s
   perception of what is a value-location for what.

   Note that every location must be protected in the corresponding faset\'s 
   init-file with PROTECT_GLOBAL.
*/

void SI_bind_symbols() /*  must be invoked when Area == Static_area */
{
#undef INIT_CORE_SYMBOL
#define INIT_CORE_SYMBOL(sym, pkg, name, extern, location) \
    SET_SYMBOL_VALUE_LOCATION((sym)= NEW_SYMBOL(pkg, name, extern), (location))
    
    INIT_CORE_SYMBOL(Qgc_inhibit,Ptrun,"*GC-INHIBIT*",TRUE, Gc_inhibit);
    INIT_CORE_SYMBOL(Qgc_silence,Ptrun,"*GC-SILENCE*",TRUE, Gc_silence);

    /* streams */
     
    INIT_CORE_SYMBOL(Qterminal_io,Pcl,"*TERMINAL-IO*",TRUE, Terminal_io);
     
    INIT_CORE_SYMBOL
	(Qstandard_input,Pcl,"*STANDARD-INPUT*",TRUE,Standard_input);
     
    INIT_CORE_SYMBOL(Qquery_io,Pcl,"*QUERY-IO*",TRUE,Query_io);
     
    INIT_CORE_SYMBOL(Qdebug_io,Pcl,"*DEBUG-IO*",TRUE,Debug_io);
     
    INIT_CORE_SYMBOL
	(Qstandard_output,Pcl,"*STANDARD-OUTPUT*",TRUE,Standard_output);
     
    INIT_CORE_SYMBOL(Qerror_output,Pcl,"*ERROR-OUTPUT*",TRUE,Error_output);
     
    INIT_CORE_SYMBOL(Qtrace_output,Pcl,"*TRACE-OUTPUT*",TRUE,Trace_output);
    
    
    /* file system */
    INIT_CORE_SYMBOL(Qdefault_pathname_defaults, Pcl,
		     "*DEFAULT-PATHNAME-DEFAULTS*",TRUE,
		     Default_pathname_defaults);
     
    INIT_CORE_SYMBOL(Qload_pathname,Pcl,"*LOAD-PATHNAME*",TRUE,Load_pathname);
     
    INIT_CORE_SYMBOL(Qload_print,Pcl,"*LOAD-PRINT*",TRUE,Load_print);
     
    INIT_CORE_SYMBOL(Qload_truename,Pcl,"*LOAD-TRUENAME*",TRUE,Load_truename);
     
    INIT_CORE_SYMBOL(Qload_verbose,Pcl,"*LOAD-VERBOSE*",TRUE,Load_verbose);
    
     
    INIT_CORE_SYMBOL
	(Qcompile_file_pathname,Pcl,
	 "*COMPILE-FILE-PATHNAME*",TRUE,Compile_file_pathname);
     
    INIT_CORE_SYMBOL(Qcompile_print,Pcl,
	 "*COMPILE-PRINT*",TRUE,Compile_print);
     
    INIT_CORE_SYMBOL(Qcompile_file_truename,Pcl,
	 "*COMPILE-FILE-TRUENAME*",TRUE,Compile_file_truename);
     
    INIT_CORE_SYMBOL(Qcompile_verbose,Pcl,
	 "*COMPILE-VERBOSE*",TRUE,Compile_verbose);
    
    /* io system*/
    
    
     
    INIT_CORE_SYMBOL(Qread_base,Pcl,"*READ-BASE*",TRUE,Read_base);
     
    INIT_CORE_SYMBOL
	(Qread_default_float_format,Pcl,
	 "*READ-DEFAULT-FLOAT-FORMAT*",TRUE,Read_default_float_format);
    
     
    INIT_CORE_SYMBOL(Qread_eval,Pcl,"*READ-EVAL*",TRUE,Read_eval);
     
    INIT_CORE_SYMBOL(Qread_suppress,Pcl,"*READ-SUPPRESS*",TRUE,Read_suppress);
    
    /* numbers */
    
     
    INIT_CORE_SYMBOL(Qpi,Pcl,"PI",TRUE,Pi);
     
    INIT_CORE_SYMBOL(Qmost_positive_double_float,Pcl,"MOST-POSITIVE-DOUBLE-FLOAT",TRUE,Most_positive_double_float);
     
    INIT_CORE_SYMBOL
	(Qleast_positive_normalized_double_float,Pcl,
	 "LEAST-POSITIVE-NORMALIZED-DOUBLE-FLOAT",TRUE,Least_positive_normalized_double_float);
     
    INIT_CORE_SYMBOL
	(Qleast_positive_double_float,Pcl,
	 "LEAST-POSITIVE-DOUBLE-FLOAT",TRUE,Least_positive_double_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_double_float,Pcl,"LEAST-NEGATIVE-DOUBLE-FLOAT",TRUE,Least_negative_double_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_normalized_double_float,Pcl,"LEAST-NEGATIVE-NORMALIZED-DOUBLE-FLOAT",TRUE,Least_negative_normalized_double_float);
     
    INIT_CORE_SYMBOL(Qmost_negative_double_float,Pcl,"MOST-NEGATIVE-DOUBLE-FLOAT",TRUE,Most_negative_double_float);
     
    INIT_CORE_SYMBOL(Qdouble_float_epsilon,Pcl,"DOUBLE-FLOAT-EPSILON",TRUE,Double_float_epsilon);
     
    INIT_CORE_SYMBOL(Qdouble_float_negative_epsilon,Pcl,"DOUBLE-FLOAT-NEGATIVE-EPSILON",TRUE,Double_float_negative_epsilon);
     
    INIT_CORE_SYMBOL(Qmost_positive_short_float,Pcl,"MOST-POSITIVE-SHORT-FLOAT",TRUE,Most_positive_short_float);
     
    INIT_CORE_SYMBOL(Qleast_positive_normalized_short_float,Pcl,"LEAST-POSITIVE-NORMALIZED-SHORT-FLOAT",TRUE,Least_positive_normalized_short_float);
     
    INIT_CORE_SYMBOL(Qleast_positive_short_float,Pcl,"LEAST-POSITIVE-SHORT-FLOAT",TRUE,Least_positive_short_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_short_float,Pcl,"LEAST-NEGATIVE-SHORT-FLOAT",TRUE,Least_negative_short_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_normalized_short_float,Pcl,"LEAST-NEGATIVE-NORMALIZED-SHORT-FLOAT",TRUE,Least_negative_normalized_short_float);
     
    INIT_CORE_SYMBOL(Qmost_negative_short_float,Pcl,"MOST-NEGATIVE-SHORT-FLOAT",TRUE,Most_negative_short_float);
     
    INIT_CORE_SYMBOL(Qshort_float_epsilon,Pcl,"SHORT-FLOAT-EPSILON",TRUE,Short_float_epsilon);
     
    INIT_CORE_SYMBOL(Qshort_float_negative_epsilon,Pcl,"SHORT-FLOAT-NEGATIVE-EPSILON",TRUE,Short_float_negative_epsilon);
     
    INIT_CORE_SYMBOL(Qmost_positive_single_float,Pcl,"MOST-POSITIVE-SINGLE-FLOAT",TRUE,Most_positive_single_float);
     
    INIT_CORE_SYMBOL(Qleast_positive_normalized_single_float,Pcl,"LEAST-POSITIVE-NORMALIZED-SINGLE-FLOAT",TRUE,Least_positive_normalized_single_float);
     
    INIT_CORE_SYMBOL(Qleast_positive_single_float,Pcl,"LEAST-POSITIVE-SINGLE-FLOAT",TRUE,Least_positive_single_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_single_float,Pcl,"LEAST-NEGATIVE-SINGLE-FLOAT",TRUE,Least_negative_single_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_normalized_single_float,Pcl,"LEAST-NEGATIVE-NORMALIZED-SINGLE-FLOAT",TRUE,Least_negative_normalized_single_float);
     
    INIT_CORE_SYMBOL(Qmost_negative_single_float,Pcl,"MOST-NEGATIVE-SINGLE-FLOAT",TRUE,Most_negative_single_float);
     
    INIT_CORE_SYMBOL(Qsingle_float_epsilon,Pcl,"SINGLE-FLOAT-EPSILON",TRUE,Single_float_epsilon);
     
    INIT_CORE_SYMBOL(Qsingle_float_negative_epsilon,Pcl,"SINGLE-FLOAT-NEGATIVE-EPSILON",TRUE,Single_float_negative_epsilon);
     
    INIT_CORE_SYMBOL(Qmost_positive_long_float,Pcl,"MOST-POSITIVE-LONG-FLOAT",TRUE,Most_positive_long_float);
     
    INIT_CORE_SYMBOL(Qleast_positive_normalized_long_float,Pcl,"LEAST-POSITIVE-NORMALIZED-LONG-FLOAT",TRUE,Least_positive_normalized_long_float);
     
    INIT_CORE_SYMBOL(Qleast_positive_long_float,Pcl,"LEAST-POSITIVE-LONG-FLOAT",TRUE,Least_positive_long_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_long_float,Pcl,"LEAST-NEGATIVE-LONG-FLOAT",TRUE,Least_negative_long_float);
     
    INIT_CORE_SYMBOL(Qleast_negative_normalized_long_float,Pcl,"LEAST-NEGATIVE-NORMALIZED-LONG-FLOAT",TRUE,Least_negative_normalized_long_float);
     
    INIT_CORE_SYMBOL(Qmost_negative_long_float,Pcl,"MOST-NEGATIVE-LONG-FLOAT",TRUE,Most_negative_long_float);
     
    INIT_CORE_SYMBOL(Qlong_float_epsilon,Pcl,"LONG-FLOAT-EPSILON",TRUE,Long_float_epsilon);
     
    INIT_CORE_SYMBOL(Qlong_float_negative_epsilon,Pcl,"LONG-FLOAT-NEGATIVE-EPSILON",TRUE,Long_float_negative_epsilon);
    
    /* packages */
    
    INIT_CORE_SYMBOL(Qpackage_variable,Pcl,"*PACKAGE*",TRUE,Package); 
 
    INIT_CORE_SYMBOL(Qmodules,Pcl,"*MODULES*",TRUE,Modules);
    
    /* printer */
    
     
    INIT_CORE_SYMBOL( Qprint_array,Pcl,"*PRINT-ARRAY*",TRUE,Print_array);
     
    INIT_CORE_SYMBOL( Qprint_base,Pcl,"*PRINT-BASE*",TRUE,Print_base);
     
    INIT_CORE_SYMBOL( Qprint_case,Pcl,"*PRINT-CASE*",TRUE,Print_case);
     
    INIT_CORE_SYMBOL( Qprint_circle,Pcl,"*PRINT-CIRCLE*",TRUE,Print_circle);
     
    INIT_CORE_SYMBOL( Qprint_escape,Pcl,"*PRINT-ESCAPE*",TRUE,Print_escape);
     
    INIT_CORE_SYMBOL( Qprint_gensym,Pcl,"*PRINT-GENSYM*",TRUE,Print_gensym);
     
    INIT_CORE_SYMBOL( Qprint_length,Pcl,"*PRINT-LENGTH*",TRUE,Print_length);
     
    INIT_CORE_SYMBOL( Qprint_level,Pcl,"*PRINT-LEVEL*",TRUE,Print_level);
     
    INIT_CORE_SYMBOL( Qprint_lines,Pcl,"*PRINT-LINES*",TRUE,Print_lines);
     
    INIT_CORE_SYMBOL( Qprint_miser_width,Pcl,"*PRINT-MISER-WIDTH*",TRUE,Print_miser_width);
     
    INIT_CORE_SYMBOL( Qprint_pprint_dispatch,Pcl,"*PRINT-PPRINT-DISPATCH*",TRUE,Print_pprint_dispatch);
     
    INIT_CORE_SYMBOL( Qprint_pretty,Pcl,"*PRINT-PRETTY*",TRUE,Print_pretty);
     
    INIT_CORE_SYMBOL( Qprint_radix,Pcl,"*PRINT-RADIX*",TRUE,Print_radix);
     
    INIT_CORE_SYMBOL( Qprint_readably,Pcl,"*PRINT-READABLY*",TRUE,Print_readably);
     
    INIT_CORE_SYMBOL( Qprint_right_margin,Pcl,"*PRINT-RIGHT-MARGIN*",TRUE,Print_right_margin);
    
    /* misc */
    
     
    INIT_CORE_SYMBOL(Qfeatures,Pcl,"*FEATURES*",TRUE,Features);
    /* Constant, so don't need SET_SYMBOL_VALUE_LOCATION() */
    SET_SYMBOL_VALUE(Qinternal_time_units_per_second 
		      = NEW_SYMBOL(Pcl,"INTERNAL-TIME-UNITS-PER-SECOND",TRUE)
		     ,Internal_time_units_per_second);

    SI_INIT_evals();
}
