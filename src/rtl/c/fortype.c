/*
 * fortype.c -  Chestnut Run-Time Library entry for function get_foreign_type
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Karray;
extern Object Kcharacter;
extern Object Kcolumn_major;
extern Object Kdouble_float;
extern Object Kpointer;
extern Object Ksigned_16bit;
extern Object Ksigned_32bit;
extern Object Ksigned_8bit;
extern Object Ksingle_float;
extern Object Kunsigned_16bit;
extern Object Kunsigned_32bit;
extern Object Kunsigned_8bit;
extern Object Qarray_foreign_type;
extern Object Qequal;
extern Object Qforeign_type;
extern Object Qpointer_foreign_type;
extern Object Qprimitive_foreign_type;
extern Object Qstructure_foreign_type;
extern Object Qstructure_object;
#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_make_structure(Object name, SI_Size_type size, long align);
extern Object cdouble_to_double(double a);
extern Object clong_to_bignum(SI_Long a);
extern Object gethash(Object,Object,Object);
extern SI_Long integer_to_long(Object n);
extern SI_Ulong integer_to_unsigned_long(Object n);
extern Object list(long,...);
extern Object make_hash_table(Object test, Object size, Object rehash_size, Object rehash_threshold);
extern Object make_structure_class(Object name, Object super, Object slots, Object printer, Object constructor, Object doc);
extern Object set_gethash(Object,Object,Object);
extern bignum_type unsigned_long_to_bignum (SI_Ulong);

#else

extern void SI_add_external_root();
extern Object SI_alloc_primitive_vector();
extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object SI_make_structure();
extern Object cdouble_to_double();
extern Object clong_to_bignum();
extern Object gethash();
extern SI_Long integer_to_long();
extern SI_Ulong integer_to_unsigned_long();
extern Object list();
extern Object make_hash_table();
extern Object make_structure_class();
extern Object set_gethash();
extern bignum_type unsigned_long_to_bignum ();

#endif



static Object get_foreign_type_table();
static Object make_array_foreign_type();
static Object get_pointer_type();

static long foreign_types_initialized_p = FALSE;
#define maybe_initialize_foreign_types() \
  if(!foreign_types_initialized_p)initialize_foreign_types()
#define make_simple_structure_class(name,super) \
  make_structure_class(name,super,NIL,NIL,NIL,NIL)

static void initialize_foreign_types()
{
  if(!foreign_types_initialized_p) {
    foreign_types_initialized_p = TRUE;
    make_simple_structure_class(Qforeign_type,Qstructure_object);
    make_simple_structure_class(Qprimitive_foreign_type,Qforeign_type);
    make_simple_structure_class(Qarray_foreign_type,Qforeign_type);
    make_simple_structure_class(Qpointer_foreign_type,Qforeign_type);
    make_simple_structure_class(Qstructure_foreign_type,Qforeign_type);
  }
}

Object 
get_foreign_type(foreign_type_name,error_if_not_found_p)
    Object foreign_type_name,error_if_not_found_p;
{
  Object foreign_type, etype = UNBOUND, dims = UNBOUND, to_type = UNBOUND;
  Object table;
  Declare_stack_pointer;

  if(FOREIGN_TYPE_P(foreign_type_name))
    return foreign_type_name;
  SAVE_STACK();
  PROTECT_6(foreign_type_name,error_if_not_found_p,
	    foreign_type,etype,dims,to_type);
  table = get_foreign_type_table();
  foreign_type = gethash(foreign_type_name,table,NIL);
  if(foreign_type == NIL && TRUEP(error_if_not_found_p)) {
    if(CONSP(foreign_type_name)) {
      if(Karray == M_CAR(foreign_type_name)) {
	  RESTORE_STACK();
	  return make_array_foreign_type(foreign_type_name);
	}
      else if(Kpointer == M_CAR(foreign_type_name)) {
	RESTORE_STACK();
	return get_pointer_type(FOREIGN_TYPE(M_CADR(foreign_type_name)));
      }
    }
    error(2,"There is no foreign-type named ~S",foreign_type_name);
  }
  RESTORE_STACK();
  return VALUES_1(foreign_type);
}

static void
make_primitive_foreign_type(name,size,modulus,remainder,reader,writer)
     Object name;
     long size,modulus,remainder;
     Object (*reader)(),(*writer)();
{
  Object ft = UNBOUND, table;
  Declare_stack_pointer;

  SAVE_STACK();
  PROTECT_2(name,ft);
  maybe_initialize_foreign_types();
  ft = MAKE_STRUCTURE(Qprimitive_foreign_type,SI_Primitive_foreign_type);
  FOREIGN_TYPE_NAME(ft) = name;
  FOREIGN_TYPE_POINTER_TYPE(ft) = NIL;
  SI_INITIALIZE_FOREIGN_TYPE_INFO(ft);
  FOREIGN_TYPE_SIZE(ft) = size;
  FOREIGN_TYPE_MODULUS(ft) = modulus;
  FOREIGN_TYPE_REMAINDER(ft) = remainder;
  SET_FOREIGN_TYPE_READER(ft,reader);
  SET_FOREIGN_TYPE_WRITER(ft,writer);
  table = get_foreign_type_table();
  set_gethash(name,table,ft);
  RESTORE_STACK();
}

static Object
non_primitive_read(type,address)
     Object type;
     char *address;
{
  Object result;
  Declare_stack_pointer;

  SAVE_STACK();
  PROTECT_1(type);
  type = get_pointer_type(type);
  MAKE_FOREIGN_POINTER(result,(unsigned long)address,type);
  RESTORE_STACK();
  return VALUES_1(result);
}

static Object
non_primitive_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  if(!(FOREIGN_POINTER_TYPE_P(new_value) &&
       FOREIGN_TYPE_POINTER_TYPE(type) == FOREIGN_POINTER_TYPE(new_value)))
    error(3,"~S is not a foreign-pointer of type (:POINTER ~S)",
	  new_value,FOREIGN_TYPE_NAME(type));
  MEMCPY(address,
	 (char *)FOREIGN_POINTER_ADDRESS(new_value),
	 FOREIGN_TYPE_SIZE(type));
  return VALUES_1(new_value);
}

static Object
make_array_foreign_type(name)
     Object name;
{
  Object ft = UNBOUND, etype = UNBOUND, dims = UNBOUND;
  Object dims_tail, table;
  Declare_stack_pointer;
  long nelems = 1;
  
  SAVE_STACK();
  PROTECT_4(name,etype,dims,ft);
  etype = FOREIGN_TYPE(M_CADR(name));
  dims_tail = dims = M_CADDR(name);
  while(CONSP(dims_tail)) {
    nelems *= IFIX(M_CAR(dims_tail));
    dims_tail = M_CDR(dims_tail);
  }
  maybe_initialize_foreign_types();
  ft = MAKE_STRUCTURE(Qarray_foreign_type,SI_Array_foreign_type);
  FOREIGN_TYPE_NAME(ft) = name;
  FOREIGN_TYPE_POINTER_TYPE(ft) = NIL;
  SI_INITIALIZE_FOREIGN_TYPE_INFO(ft);
  FOREIGN_TYPE_SIZE(ft) = nelems * FOREIGN_TYPE_SIZE(etype);
  FOREIGN_TYPE_MODULUS(ft) = FOREIGN_TYPE_MODULUS(etype);
  FOREIGN_TYPE_REMAINDER(ft) = 0;
  SET_FOREIGN_TYPE_READER(ft,non_primitive_read);
  SET_FOREIGN_TYPE_WRITER(ft,non_primitive_write);
  ARRAY_FOREIGN_TYPE_ETYPE(ft) = etype;
  ARRAY_FOREIGN_TYPE_DIMENSIONS(ft) = dims;
  ARRAY_FOREIGN_TYPE_ROW_MAJOR_P(ft) = 
    (CONSP(M_CDDDR(name)) && 
     (Kcolumn_major == M_CADDDR(name))) ? NIL : T;
  table = get_foreign_type_table();
  set_gethash(name,table,ft);
  RESTORE_STACK();
  return VALUES_1(ft);
}

static Object
pointer_read(type,address)
     Object type;
     char *address;
{
  Object result;
  Declare_stack_pointer;

  SAVE_STACK();
  PROTECT_1(type);
  MAKE_FOREIGN_POINTER(result,(unsigned long)*(char **)address,type);
  RESTORE_STACK();
  return VALUES_1(result);
}

static Object
pointer_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  if(!(FOREIGN_POINTER_TYPE_P(new_value) &&
       type == FOREIGN_POINTER_TYPE(new_value)))
    error(3,"~S is not a foreign-pointer of type ~S",
	  new_value,type);
  *(char **)address = (char *)FOREIGN_POINTER_ADDRESS(new_value);
  return VALUES_1(new_value);
}

static Object
get_pointer_type(foreign_type)
     Object foreign_type;
{
  Object pft, table;
  Declare_stack_pointer;

  if(TRUEP(pft = FOREIGN_TYPE_POINTER_TYPE(foreign_type)))
    return VALUES_1(pft);
    
  SAVE_STACK();
  PROTECT_2(foreign_type,pft);
  maybe_initialize_foreign_types();
  pft = MAKE_STRUCTURE(Qpointer_foreign_type,SI_Pointer_foreign_type);
  FOREIGN_TYPE_NAME(pft) = LIST_2(Kpointer,FOREIGN_TYPE_NAME(foreign_type));
  FOREIGN_TYPE_POINTER_TYPE(pft) = NIL;
  SI_INITIALIZE_FOREIGN_TYPE_INFO(pft);
  FOREIGN_TYPE_SIZE(pft) = sizeof(Object);
  FOREIGN_TYPE_MODULUS(pft) = sizeof(Object);
  FOREIGN_TYPE_REMAINDER(pft) = 0;
  SET_FOREIGN_TYPE_READER(pft,pointer_read);
  SET_FOREIGN_TYPE_WRITER(pft,pointer_write);
  POINTER_FOREIGN_TYPE_TO_TYPE(pft) = foreign_type;
  FOREIGN_TYPE_POINTER_TYPE(foreign_type) = pft;
  table = get_foreign_type_table();
  set_gethash(FOREIGN_TYPE_NAME(pft),table,pft);
  RESTORE_STACK();
  return VALUES_1(pft);
}


Object
make_struct_foreign_type(name,size,modulus,remainder)
     Object name,size,modulus,remainder;
{
  Object ft = UNBOUND, table;
  Declare_stack_pointer;

  SAVE_STACK();
  PROTECT_4(name,size,modulus,remainder);
  ft = get_foreign_type(name,NIL);
  if ( ft == NIL ) {
    ft = MAKE_STRUCTURE(Qstructure_foreign_type,SI_Structure_foreign_type);
    FOREIGN_TYPE_NAME(ft) = name;
    FOREIGN_TYPE_POINTER_TYPE(ft) = NIL;
    SI_INITIALIZE_FOREIGN_TYPE_INFO(ft);
    FOREIGN_TYPE_SIZE(ft) = IFIX(size);
    FOREIGN_TYPE_MODULUS(ft) = IFIX(modulus);
    FOREIGN_TYPE_REMAINDER(ft) = IFIX(remainder);
    SET_FOREIGN_TYPE_READER(ft,non_primitive_read);
    SET_FOREIGN_TYPE_WRITER(ft,non_primitive_write);
  }
  else if ( !(STRUCTURE_FOREIGN_TYPE_P(ft) &&
	      (FOREIGN_TYPE_SIZE(ft) == IFIX(size)) &&
	      (FOREIGN_TYPE_MODULUS(ft) == IFIX(modulus)) &&
	      (FOREIGN_TYPE_REMAINDER(ft) == IFIX(remainder))) )
    error(2,"The foreign-type named ~S is already defined",name);
  table = get_foreign_type_table();
  set_gethash(name,table,ft);
  RESTORE_STACK();
  return VALUES_1(ft);
}

Object
undefine_foreign_type(name)
     Object name;
{
  return set_gethash(name,get_foreign_type_table(),NIL);
}

Object
define_foreign_synonym_type(new_name,name)
     Object new_name,name;
{
  return set_gethash(new_name,get_foreign_type_table(),FOREIGN_TYPE(name));
}

static Object
character_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(CHAR_TO_CHARACTER(*address));
}

static Object
character_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *address = CHARACTER_TO_CHAR(new_value);
  return VALUES_1(new_value);
}

#ifdef __STDC__
#define signed_char signed char
#else
#define signed_char char
#endif

static Object
signed_8bit_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(FIX(*(signed_char *)address));
}

static Object
signed_8bit_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(signed_char *)address = (signed_char)IFIX(new_value);
  return VALUES_1(new_value);
}

static Object
unsigned_8bit_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(FIX(*(unsigned char *)address));
}

static Object
unsigned_8bit_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(unsigned char *)address = (unsigned char)IFIX(new_value);
  return VALUES_1(new_value);
}

static Object
signed_16bit_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(FIX(*(short *)address));
}

static Object
signed_16bit_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(short *)address = (short)IFIX(new_value);
  return VALUES_1(new_value);
}

static Object
unsigned_16bit_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(FIX(*(unsigned short *)address));
}

static Object
unsigned_16bit_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(unsigned short *)address = (unsigned short)IFIX(new_value);
  return VALUES_1(new_value);
}

static Object
signed_32bit_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(LONG_TO_INTEGER(*(long *)address));
}

static Object
signed_32bit_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(long *)address = INTEGER_TO_LONG(new_value);
  return VALUES_1(new_value);
}

static Object
unsigned_32bit_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(UNSIGNED_LONG_TO_INTEGER(*(unsigned long *)address));
}

static Object
unsigned_32bit_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(unsigned long *)address = INTEGER_TO_UNSIGNED_LONG(new_value);
  return VALUES_1(new_value);
}

static Object
single_float_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(FLOAT_TO_SINGLE_FLOAT(*(float *)address));
}

static Object
single_float_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(float *)address = SINGLE_FLOAT_TO_FLOAT(new_value);
  return VALUES_1(new_value);
}

static Object
double_float_read(type,address)
     Object type;
     char *address;
{
  return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(*(double *)address));
}

static Object
double_float_write(type,address,new_value)
     Object type,new_value;
     char *address;
{
  *(double *)address = DOUBLE_FLOAT_TO_DOUBLE(new_value);
  return VALUES_1(new_value);
}

static Object
foreign_type_table = UNBOUND;

static Object
get_foreign_type_table()
{
  if( foreign_type_table == UNBOUND )
    {
      foreign_type_table = make_hash_table(Qequal,_,_,_);
      PROTECT_GLOBAL(foreign_type_table);
      make_primitive_foreign_type(Kcharacter,1,1,0,
				  character_read,character_write);
      make_primitive_foreign_type(Ksigned_8bit,1,1,0,
				  signed_8bit_read,signed_8bit_write);
      make_primitive_foreign_type(Kunsigned_8bit,1,1,0,
				  unsigned_8bit_read,unsigned_8bit_write);
      make_primitive_foreign_type(Ksigned_16bit,2,2,0,
				  signed_16bit_read,signed_16bit_write);
      make_primitive_foreign_type(Kunsigned_16bit,2,2,0,
				  unsigned_16bit_read,unsigned_16bit_write);
      make_primitive_foreign_type(Ksigned_32bit,4,4,0,
				  signed_32bit_read,signed_32bit_write);
      make_primitive_foreign_type(Kunsigned_32bit,4,4,0,
				  unsigned_32bit_read,unsigned_32bit_write);
      make_primitive_foreign_type(Ksingle_float,4,4,0,
				  single_float_read,
				  single_float_write);
      make_primitive_foreign_type(Kdouble_float,8,8,0,
				  double_float_read,
				  double_float_write);
    }
  return foreign_type_table;
}
