/* ps.h -- Header File for ps.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

extern Object Pclos;
extern Object Pclos_run;
extern Object Pclosx;
extern Object Pcl;
extern Object Pcl_user;
extern Object Pkeyword;
extern Object Ptrun;
extern Object Ptx;

/* function declarations */

#ifdef USE_PROTOTYPES

extern Object emit_paper_tray(Object);
extern Object emit_postscript_prolog(Object,Object);
extern Object emit_postscript_reserve_space(Object,Object);
extern Object emit_printing_color_map(void);
extern Object g2_stream_terpri(Object);
extern Object g2_stream_write_char(Object,Object);
extern Object g2_stream_write_string(Object,Object);
extern Object memq_function(Object,Object);
extern Object pformat(int,...);
extern Object postscript_decode_text_into_gensym_stream(Object,Object);
extern Object postscript_decompress_header_token(Object);

#else

extern Object emit_paper_tray();
extern Object emit_postscript_prolog();
extern Object emit_postscript_reserve_space();
extern Object emit_printing_color_map();
extern Object g2_stream_terpri();
extern Object g2_stream_write_char();
extern Object g2_stream_write_string();
extern Object memq_function();
extern Object pformat();
extern Object postscript_decode_text_into_gensym_stream();
extern Object postscript_decompress_header_token();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Emit_postscript_line_length, Qemit_postscript_line_length);
extern Object Postscript_header_array;
extern Object Postscript_header_token_encodings;
extern Object Postscript_macro_function_prop;
extern Object Postscript_transparent_color_value;
DECLARE_VARIABLE_WITH_SYMBOL(Printing_stream, Qprinting_stream);
