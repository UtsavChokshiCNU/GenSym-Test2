/* kybrds.h -- Header File for kybrds.c
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

extern Object assq_function(Object,Object);
extern Object convert_key_code_to_key_symbol(Object);
extern Object define_key_symbol_1(Object,Object,Object,Object,Object,Object,Object);
extern Object key_code_from_character(Object);
extern Object mutate_global_property(Object,Object,Object);

#else

extern Object assq_function();
extern Object convert_key_code_to_key_symbol();
extern Object define_key_symbol_1();
extern Object key_code_from_character();
extern Object mutate_global_property();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Bindable_keysyms, Qbindable_keysyms);
#define Illegal_key_code FIX((SI_Long)-1L)
extern Object Illegal_key_index;
extern Object Key_code_for_key_symbol_prop;
extern Object Key_index_bits;
DECLARE_VARIABLE_WITH_SYMBOL(Key_index_to_key_symbol_array, Qkey_index_to_key_symbol_array);
DECLARE_VARIABLE_WITH_SYMBOL(Key_index_to_lisp_character_array, Qkey_index_to_lisp_character_array);
DECLARE_VARIABLE_WITH_SYMBOL(Lisp_character_to_key_index_alist, Qlisp_character_to_key_index_alist);
DECLARE_VARIABLE_WITH_SYMBOL(Lisp_int_character_to_key_index_array, Qlisp_int_character_to_key_index_array);
#define Maximum_number_of_key_indexes FIX((SI_Long)2048L)
DECLARE_VARIABLE_WITH_SYMBOL(Pseudo_keysyms, Qpseudo_keysyms);
#define Unicode_bit FIX((SI_Long)16777216L)
extern Object Unicode_character_bits;
