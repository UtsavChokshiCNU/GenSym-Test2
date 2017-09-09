/*
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 */

/* in instance.h

 #define FOREIGN_POINTER_TYPE(o) COBJECT_NAME(o)
 #define FOREIGN_POINTER_ADDRESS(o) COBJECT_OBJ(o)
 #define FOREIGN_POINTER_TYPE_P(o) COBJECTP(o)
 #define FOREIGN_POINTER_P(o) \
   (FOREIGN_POINTER_TYPE_P(o) && \
    POINTER_FOREIGN_TYPE_P(FOREIGN_POINTER_TYPE(o)))

 #define MAKE_FOREIGN_POINTER(result,address,type) \
  {result=SI_ALLOC(SI_Cobject,COBJECT_TYPE,SI_INSTANCE_TAG,SI_UGLY); \
   SI_SET_WRAPPER(result,SI_WRAPPER_foreign_pointer); \
   FOREIGN_POINTER_ADDRESS(result) = address; \
   FOREIGN_POINTER_TYPE(result) = type;}

 */

/* in inline.h

 #define FOREIGN_TYPE2(o,e) (FOREIGN_TYPE_P(o) ? o : get_foreign_type(o,e))
 #define FOREIGN_TYPE(o) (FOREIGN_TYPE_P(o) ? o : get_foreign_type(o))

 */

/* Structure FOREIGN-TYPE */

typedef struct {
    Structure_object included_fields;
    Object name;
    Object pointer_type;
    Object info;
    /*
    Object size;
    Object modulus;
    Object remainder;
    Object reader;
    Object writer;
    */
} SI_Foreign_type;

#define FOREIGN_TYPE_P(o) (STRUCTURE_OBJECT_P(o) &&  \
	STRUCTURE_OBJECT_TYPEP(o,2,Qforeign_type))

#define FOREIGN_TYPE_NAME(o) STRUCTURE_FIELD(o,SI_Foreign_type,name)
#define FOREIGN_TYPE_POINTER_TYPE(o) \
  STRUCTURE_FIELD(o,SI_Foreign_type,pointer_type)
#define SI_FOREIGN_TYPE_INFO(o,i) \
  UBYTE_32_ISAREF_1(STRUCTURE_FIELD(o,SI_Foreign_type,info),i)
#define SI_INITIALIZE_FOREIGN_TYPE_INFO(o) \
  STRUCTURE_FIELD(o,SI_Foreign_type,info) = \
  SI_alloc_primitive_vector(5,A_UNSIGNED_BYTE_32)

#define FOREIGN_TYPE_SIZE(o) SI_FOREIGN_TYPE_INFO(o,0)
#define FOREIGN_TYPE_MODULUS(o) SI_FOREIGN_TYPE_INFO(o,1)
#define FOREIGN_TYPE_REMAINDER(o) SI_FOREIGN_TYPE_INFO(o,2)
#define FOREIGN_TYPE_READER(o) (Object(*)())SI_FOREIGN_TYPE_INFO(o,3)
#define FOREIGN_TYPE_WRITER(o) (Object(*)())SI_FOREIGN_TYPE_INFO(o,4)
#define SET_FOREIGN_TYPE_READER(o,v) \
  SI_FOREIGN_TYPE_INFO(o,3)=(unsigned long)(v)
#define SET_FOREIGN_TYPE_WRITER(o,v) \
  SI_FOREIGN_TYPE_INFO(o,4)=(unsigned long)(v)

/* Structure PRIMITIVE-FOREIGN-TYPE */

typedef struct {
    SI_Foreign_type included_fields;
} SI_Primitive_foreign_type;

#define PRIMITIVE_FOREIGN_TYPE_P(o) (STRUCTURE_OBJECT_P(o) &&  \
	STRUCTURE_OBJECT_TYPEP(o,3,Qprimitive_foreign_type))

/* Structure POINTER-FOREIGN-TYPE */

typedef struct {
    SI_Foreign_type included_fields;
    Object to_type;
} SI_Pointer_foreign_type;

#define POINTER_FOREIGN_TYPE_P(o) (STRUCTURE_OBJECT_P(o) &&  \
	STRUCTURE_OBJECT_TYPEP(o,3,Qpointer_foreign_type))

#define POINTER_FOREIGN_TYPE_TO_TYPE(o) STRUCTURE_FIELD(o, \
	SI_Pointer_foreign_type,to_type)

/* Structure ARRAY-FOREIGN-TYPE */

typedef struct {
    SI_Foreign_type included_fields;
    Object etype;
    Object dimensions;
    Object row_major_p;
} SI_Array_foreign_type;

#define ARRAY_FOREIGN_TYPE_P(o) (STRUCTURE_OBJECT_P(o) &&  \
	STRUCTURE_OBJECT_TYPEP(o,3,Qarray_foreign_type))

#define ARRAY_FOREIGN_TYPE_ETYPE(o) STRUCTURE_FIELD(o, \
	SI_Array_foreign_type,etype)
#define ARRAY_FOREIGN_TYPE_DIMENSIONS(o) STRUCTURE_FIELD(o, \
	SI_Array_foreign_type,dimensions)
#define ARRAY_FOREIGN_TYPE_ROW_MAJOR_P(o) STRUCTURE_FIELD(o, \
	SI_Array_foreign_type,row_major_p)

/* Structure STRUCTURE-FOREIGN-TYPE */

typedef struct {
    SI_Foreign_type included_fields;
} SI_Structure_foreign_type;

#define STRUCTURE_FOREIGN_TYPE_P(o) (STRUCTURE_OBJECT_P(o) &&  \
	STRUCTURE_OBJECT_TYPEP(o,3,Qstructure_foreign_type))

