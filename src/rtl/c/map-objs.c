/*
 *
 *
 * Copyright (c) 1993 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area_copy;
extern SI_Area Dynamic_area;
extern Object Gc_inhibit;
extern SI_Stack_item *Lisp_stack;
extern Object List_of_packages;
extern SI_Area Local_area;
extern TLS Object SI_Called_function;
extern TLS SI_Catch_frame *SI_Catch_stack;
extern TLS SI_Special_frame *SI_Special_stack;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object SI_cons_with_gc(Object x, Object y);
extern Object cons(Object x, Object y);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern long ilength(Object sequence);
extern Object istring_to_string(char *istring);
extern Object list(long,...);
extern Object make_vector(Object size, Object initial_element);
extern Object ncons(Object a);

#else

extern void SI_add_external_root();
extern Object SI_cons_with_gc();
extern Object cons();
extern Object (*SI_error_fptr) ();
extern long ilength();
extern Object istring_to_string();
extern Object list();
extern Object make_vector();
extern Object ncons();

#endif

#include "gc.h"
#include "gcobjmap.h"

typedef Object *Object_pointer;

static Object (*map_function_fn)();
static Object map_function;
static unsigned long *map_objects_map;
static unsigned long *map_objects_others;
static unsigned long map_objects_others_count = 0;
static int map_objects_others_overflow_p = 0;
#define map_objects_others_limit 20
static unsigned long min_area_address;
static unsigned long max_area_address;

static void map_root_objects ();
static void map_objects_this_space ();
static void ignore ();
static Object_pointer map_object_pointer ();
static long symbol_internal_plist_info ();

static void 
map_objects_this_space(ar)
     SI_Area ar;
{
  /* Only one line prevents us from using area_object_refs. */
  SI_Segment *seg; 
  long donescanning;
 
  for (seg = ar.first_segment; seg != NULL; seg = seg->next) 
    seg->gc_maptemp = seg->start; /* initialize per-segment scanptrs */ 
  donescanning = 0; /* indicate whether all objects have been examined */ 
  while (!donescanning) { 
    donescanning = 1;		/* assume one pass will get them all */ 
    for (seg = ar.first_segment; seg != NULL; seg = seg->next) { 
      Object *scanptr = (Object *)seg->gc_maptemp; 
      Object *scanlimit = (Object *)seg->frontier; 
   
      /*** Must do this on a per-segment basis ***/ 
      while ((scanptr < scanlimit) 
	     /* just in case segment is growing, refresh scanlimit */ 
	     || ((scanlimit = (Object *)seg->frontier), 
		 (scanptr < scanlimit))) { 
	SKIP_ALIGNMENT_WORDS(scanptr, 
	   { SKIP_RELOCATION_WORD(scanptr);
	     scanptr = map_object_pointer((Object *)&scanptr);
	     donescanning = 0;	/* outside call may add objects, recheck */ 
	   } ); 
      } 
      seg->gc_maptemp = (void *)scanptr; /* save scanptr for scan restart */ 
    } 
  } 
} 


static void
map_root_objects()
{
  map_objects_this_space(Static_area);
#if SI_SCAN_LOCAL_AREA
  map_objects_this_space(Local_area);
#endif 
  {/* external roots */
    register Root_items *temp;
    register long i;

    for(temp = SI_Gc_external_roots; temp != NULL; temp = temp->next)
      for(i=0; i < temp->count; i++) 
	map_object_pointer(temp->roots[i]);
  }
  {/* Preserve Lisp Stack */
    Stack_item *temp, item;
    long indirect = FALSE;
    for (temp = Lisp_stack; temp != Stack; temp++) {
      item = *temp;
      if (item.object == PROTECT_MARKER) /* start/end of indirect nodes */
	indirect = ~indirect;
      else if (indirect)
	map_object_pointer(item.location);
      else
	map_object_pointer(&(temp->object));
    }
  }
  {/* Preserve special variable stack */
    register SI_Special_frame *temp = SI_Special_stack;
    for(temp = SI_Special_stack; temp != NULL; temp = temp->link)
      map_object_pointer(&(temp->saved_value));
  }
  {/* Preserve catch frame stack */
    register SI_Catch_frame *temp = SI_Catch_stack;
    for(temp = SI_Catch_stack; temp != NULL; temp = temp->link)
      map_object_pointer(&(temp->tag));
  }
  {/* Preserve Values array */
    register long i;
#ifdef RETURN_MULTIPLE_VALUES
    for (i = 0; i+1 < Values_count; ++i)
#else
    for (i = 0; i+1 < MAXARGS; ++i)
#endif
      map_object_pointer(&(Values[i]));
  }
}

#define IGNORE(x,y,z)

static inline void
ignore(a, b, c)
     Object *a, b, c;
{
  IGNORE(a, b, c);
  return;
}

#define TOKENP(o) \
    (((SI_Long)(o) & ((1 << SI_CHAR_SHIFT) - 1)) == SI_TOKEN_TAG)

static Object_pointer 
map_object_pointer (ptrp)
    Object_pointer ptrp;
{
  register Object ptr = *ptrp;
  register Object_pointer mp;
  register unsigned long up;
  unsigned long bit_index,word_index,mask;
  long i,dynamic_p,len;

#ifdef DEBUG_MAP_OBJECTS
  printf("%x %x\n",(long)ptrp,(long)ptr);
#endif
  if (!is_pointer(ptr))
    {
      long code;
      
      if (ptr == NIL)
	return (Object_pointer)0; /* was: code = 0; */
      else if (FIXNUMP(ptr))
	code = 1L;
      else if (CHARACTERP(ptr))
	code = 2L;
      else if (TOKENP(ptr))
	code = ICHAR_INT(ptr)+3L;
      else /* Header.  Need to fix MAP_ONTO_POINTERS to avoid this case. */
	return (Object_pointer)0;
      SI_Called_function = map_function;
      (*map_function_fn)(ptr,FIX(0),FIX(-code));
      return (Object_pointer)0;
    }
  mp = object_to_ptr(ptr);
  up = (unsigned long)mp;
  len = GC_LENGTH(ptr);
  if((up >= min_area_address) &&
     (up < max_area_address)) {
    bit_index = (up - min_area_address) >> 2;
    word_index = bit_index >> 5;
    mask = (1 << (bit_index & 63));
#ifdef DEBUG_MAP_OBJECTS
    printf("%x  %x %x  %x\n",bit_index,word_index,mask,
	   map_objects_map[word_index]);
#endif
    if(map_objects_map[word_index] & mask)
      return mp+len;
    map_objects_map[word_index] |= mask;
    {
      SI_Segment *seg;
      dynamic_p = 1;
      for (seg = Static_area.first_segment; seg != NULL; seg = seg->next)
	if ((SI_Ulong)(seg->start)<=up && up<(SI_Ulong)(seg->limit)) {
	  dynamic_p = 0;
	  break;
	}
    }
  }
  else {
    dynamic_p = 0;
    for(i=0; i<map_objects_others_count; i++)
      if(map_objects_others[i]==up)
	return mp+len;
    if(i==map_objects_others_limit) {
      if(!map_objects_others_overflow_p) {
	map_objects_others_overflow_p = 1;
	gcwarn("map_objects_others_limit is too small.\n");
      }
      return mp+len;
    }
    map_objects_others[map_objects_others_count++]=up;
  }
  {
    long code = (long)SI_STORED_OBJECT_TYPE(ptr);
    code |= dynamic_p << SI_TYPE_WIDTH;
    if(SYMBOLP(ptr))
      code |= symbol_internal_plist_info(ptr) << (1+SI_TYPE_WIDTH);
    SI_Called_function = map_function;
    (*map_function_fn)(ptr,
		       FIX(len),
		       FIX(code));
  }
  MAP_ONTO_POINTERS(map_object_pointer, map_object_pointer, IGNORE, mp);
  return mp;
}

#define VALUE_INDICATOR	     	SI_MAKE_TOKEN(SI_TOKEN_ID_VALUE)
#define FUNCTION_INDICATOR     	SI_MAKE_TOKEN(SI_TOKEN_ID_FUNCTION)
#define SETF_FUNCTION_INDICATOR SI_MAKE_TOKEN(SI_TOKEN_ID_SETF_FUNCTION)
#define NAME_INDICATOR		SI_MAKE_TOKEN(SI_TOKEN_ID_NAME)

static long symbol_internal_plist_info (symbol)
     Object symbol;
{
  Object tail,key;
  long code = 0;

  for (tail = SI_SYMBOL_PLIST(symbol); CONSP(tail); tail = M_CDDR(tail)) {
    key = M_CAR(tail);
    if (key == NAME_INDICATOR)
      code |= 16L;
    else if (key == VALUE_INDICATOR)
      code |= 8L;
    else if (key == FUNCTION_INDICATOR)
      code |= 4L;
    else if (key == SETF_FUNCTION_INDICATOR)
      code |= 2L;
    else
      break;
  }
  if (tail != NIL)
    code |= 1L;
  return code;  
}

static void
check_area_addresses(ar)
     SI_Area  ar;
{
  SI_Segment *seg;
  
  for (seg = ar.first_segment; seg != NULL; seg = seg->next) {
    if (min_area_address > (SI_Ulong)(seg->start))
      min_area_address = (SI_Ulong)(seg->start);
    if (max_area_address < (SI_Ulong)(seg->limit))
      max_area_address = (SI_Ulong)(seg->limit);
  }
}

Object
map_objects (map_fn)
  Object map_fn;
{
  Object save = Gc_inhibit;
  unsigned long others[map_objects_others_limit];
  unsigned long bytes_in_map;

  Gc_inhibit = T;
  if (!(SI_FUNCTIONP(map_fn)&&
	SI_FUNCTION_SIMPLE_P(map_fn)&&
	SI_FUNCTION_NARGS(map_fn)==3))
    error(2,"~S is not a simple function taking 3 arguments",map_fn);
  map_function = map_fn;
  map_function_fn = SI_FUNCTION_ENTRY(map_fn);
	  
  if (Current_area == &Dynamic_area)
    SI_FLUSH_ALLOC_CACHE();

  min_area_address = ~(unsigned long)0;
  max_area_address = 0;

  check_area_addresses(Static_area);
  check_area_addresses(Dynamic_area);
#if SI_COPYING_COLLECTOR
  check_area_addresses(Dynamic_area_copy);
#endif
#if SI_SCAN_LOCAL_AREA
  check_area_addresses(Local_area);
#endif

  bytes_in_map = (1+((max_area_address-min_area_address)>>7)) << 2;
  map_objects_map = (unsigned long *)malloc(bytes_in_map);

  {
    unsigned long i, limit=(max_area_address-min_area_address)>>7;
    for(i=0; i<limit; i++)
      map_objects_map[i]=0;
  }

  map_objects_others = others;
  map_objects_others_count = 0;

  map_root_objects();

  free((void *)map_objects_map);

  Gc_inhibit = TRUEP(save) ? T : NIL;

  if (Current_area == &Dynamic_area)
    SI_RELOAD_ALLOC_CACHE();

  return VALUES_1(NIL);
}

static char *
si_immediate_object_names[]={
  "NIL","FIXNUM","CHARACTER",
  "UNSUPPLIED_TOKEN","UNBOUND_TOKEN",
  "PROTECT_TOKEN","UNWIND_PROTECT_TOKEN",
  "NO_APPLICABLE_METHOD_TOKEN",
  "UNINITIALIZED_TOKEN",
  "GC_LIVE_TOKEN","GC_FORWARDING_TOKEN",
  "GC_ALIGNING_TOKEN","GC_NONRELOCATABLE_TOKEN",
  "VALUE_TOKEN","FUNCTION_TOKEN","SETF_FUNCTION_TOKEN","NAME_TOKEN",
  "DOT_TOKEN","EOF_TOKEN","MACRO_TOKEN",
  (char *)0
};

static char *
si_type_names[]={
  "UNUSED",			/* for "redundancy", avoid using zero */

  /* Ordering of number type is used to determine coercions and contagion. */
  "FIXNUM",			/* used only internally in numbers.c */
  "OBIGNUM",			/* obsolescent */
  "BIGNUM",
  "RATIO",
  "DOUBLE",
  "COMPLEX",

  "INDIRECT",			/* must precede symbol types */
  "SYMBOL",			/* non-external initial symbol */
  "MSYMBOL",			/* non-external non-initial symbol */
  "USYMBOL",			/* uninterned symbol */

  "ESYMBOL",			/* external initial symbol */
  "EMSYMBOL",			/* external non-initial symbol */
  "KEYWORD",			/* initial keyword */
  "MKEYWORD",			/* non-initial keyword */
  "NIL",			/* ? */
  "EINDIRECT",			/* must follow symbol types */

  "CONS",
  "GENERAL_ARRAY",
  "PRIMITIVE_VECTOR",

  "VALUE_CELL",			/* holds pointer to Object-type C var */
  "WINDOW",

  "STRUCTURE",

  "COBJECT",
  "HASH_TABLE",
  "PACKAGE",
  "PATHNAME",
  "RANDOM_STATE",
  "READTABLE",
  "STREAM",

#if SI_SUPPORT_CLOS

  "CLASS_WRAPPER",
  "EFFECTIVE_METHOD",
  "METHOD_COMBINATION",

  "STANDARD_INSTANCE",
  "METHOD",

#endif /* SI_SUPPORT_CLOS */

  "FUNCTION",
  (char *)0
};

static char *
si_area_names[]={
  "Static","Dynamic",
  (char *)0
};

/* corresponds to the order used by symbol_internal_plist_info */
static char *
si_symbol_field_names[]={
  "PLIST","SETF_FUNCTION","FUNCTION","VALUE","NAME",
  (char *)0
};

static int si_immediate_object_names_length;
static int si_type_names_length;
static int si_area_names_length;
static int si_symbol_field_names_length;
static int si_symbol_field_set_names_length;

static Object SI_immediate_object_names = UNBOUND;
static Object SI_type_names = UNBOUND;
static Object SI_area_names = UNBOUND;
static Object SI_symbol_field_names = UNBOUND;
static Object SI_symbol_field_set_names = UNBOUND;

static Object
make_string_vector(string_array)
     char **string_array;
{
  long size,i;
  Object result;
  Declare_area(a);

  SAVE_CURRENT_AREA(a);
  SET_CURRENT_AREA(Static_area);
  for(size=0; string_array[size]!=(char *)0; size++);
  result = make_vector(FIX(size),NIL);
  for(i=0; i<size; i++)
    ISVREF(result,i) = istring_to_string(string_array[i]);
  RESTORE_CURRENT_AREA(a);
  return result;
}

static int name_lists_initialized_p = 0;

static void
initialize_name_lists ()
{
  SI_immediate_object_names = make_string_vector(si_immediate_object_names);
  PROTECT_GLOBAL(SI_immediate_object_names);
  si_immediate_object_names_length = ilength(SI_immediate_object_names);
  SI_type_names = make_string_vector(si_type_names);
  PROTECT_GLOBAL(SI_type_names);
  si_type_names_length = ilength(SI_type_names);
  SI_area_names = make_string_vector(si_area_names);
  PROTECT_GLOBAL(SI_area_names);
  si_area_names_length = ilength(SI_area_names);
  SI_symbol_field_names = make_string_vector(si_symbol_field_names);
  PROTECT_GLOBAL(SI_symbol_field_names);
  si_symbol_field_names_length = ilength(SI_symbol_field_names);
  {
    int icode,ic,j,set_size = 1 << ilength(SI_symbol_field_names);
    Object result = UNBOUND;
    Declare_stack_pointer;

    SI_symbol_field_set_names = make_vector(FIX(set_size),NIL);
    PROTECT_GLOBAL(SI_symbol_field_set_names);
    si_symbol_field_set_names_length = set_size;
    SAVE_STACK();
    PROTECT_1(result);
    for(icode=0; icode<set_size; icode++) {
      result = NIL;
      for (j=0,ic=icode; ic != 0; ic >>= 1, j++) {
	if (ic & 1) 
	  result = (Object)CONS(ISVREF(SI_symbol_field_names,j),result);
      }
      ISVREF(SI_symbol_field_set_names,icode) = result;
    }
    RESTORE_STACK();
  }
  name_lists_initialized_p = 1;
}

Object
map_objects_code_limits()
{
  long ion_size,sfn_size;

  for(ion_size=0; si_immediate_object_names[ion_size]!=(char *)0; ion_size++);
  for(sfn_size=0; si_symbol_field_names[sfn_size]!=(char *)0; sfn_size++);
  return VALUES_2(FIX(1L-ion_size),
		  FIX((1L << (SI_TYPE_WIDTH+1+sfn_size))-1L));
}

Object
decode_map_objects_code(code)
     Object code;
{
  long icode = IFIX(code);
  long type,area;
  Object otype,oarea,osymset;

  if(!name_lists_initialized_p)
    initialize_name_lists();
  if (icode <= 0)
    return LIST_1((-icode<si_immediate_object_names_length)?
		  ISVREF(SI_immediate_object_names,-icode):NIL);
  type = icode & ((1L<<SI_TYPE_WIDTH)-1L);
  area = (icode & (1L<<SI_TYPE_WIDTH)) >> SI_TYPE_WIDTH;
  icode = icode >> (1L+SI_TYPE_WIDTH);
  otype = (type<si_type_names_length)?ISVREF(SI_type_names,type):NIL;
  oarea = (area<si_area_names_length)?ISVREF(SI_area_names,area):NIL;
  if ((long)SI_LEAST_SYMBOL_TYPE <= type &&
      type <= (long)SI_GREATEST_SYMBOL_TYPE) {
    osymset = ((icode<si_symbol_field_set_names_length)?
	       ISVREF(SI_symbol_field_set_names,icode):NIL);      
    return LIST_3(otype,oarea,osymset);
  }
  else
    return LIST_2(otype,oarea);
}
