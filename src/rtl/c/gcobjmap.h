/*
 *
 *
 * gcobjmap.h
 *
 * J. O'Toole
 * (c) Copyright 1991 Chestnut Software, Inc.
 *
 * GC Interface to object contents and area iteration.
 */


/* This macro is for dealing with COPYING_COLLECTOR conditionalization. */
#if SI_COPYING_COLLECTOR
#define SKIP_RELOCATION_WORD(sp)
#else
#define SKIP_RELOCATION_WORD(sp)   (sp++)
#endif

/* This macro is for dealing with VISIT_EXACTLY_ONCE conditionalization. */
#if SI_VISIT_EXACTLY_ONCE
#define DO_VALUE_CELL_CASE(p, c_none, c_many, c_one, one, one_proc, adjust) \
	  c_one(p, len, VALUE_CELL_LOCATION(p)); break
#else
#define DO_VALUE_CELL_CASE(p, c_none, c_many, c_one, one, one_proc, adjust) \
          c_none(p, len) /* BORING, FALL THROUGH */ 
#endif

/* These macros are for dealing with CLOS conditionalization. */
#if SI_SUPPORT_CLOS

#define DO_OPTIONAL_SI_METHOD_TYPE() \
   case SI_METHOD_TYPE: 

#define DO_OPTIONAL_SOME_OR_NONE(p,c_none,c_many,c_one,one,one_proc,adjust) \
	case SI_STANDARD_INSTANCE_TYPE: \
	  { \
	    register Object oldptr = SI_STANDARD_OBJECT_SLOT_VECTOR(p); \
	    one(&(SI_STANDARD_OBJECT_SLOT_VECTOR(p))); \
	    adjust(&(SI_STANDARD_OBJECT_SLOTS(p)), SI_STANDARD_OBJECT_SLOT_VECTOR(p), oldptr); \
	    }; \
	  c_one(p, len, &(INSTANCE_WRAPPER(p))); \
 \
	case SI_CLASS_WRAPPER_TYPE: \
	      /* assume wrapper, readpair, writepair, ...normal */ \
	  one(&(INSTANCE_WRAPPER(p))); \
	  { \
	    register Object oldptr = SI_WRAPPER_READ_TABLE_BASE(p); \
	    one(&(SI_WRAPPER_READ_TABLE_BASE(p))); \
	    adjust(&(SI_WRAPPER_READ_TABLE(p)), SI_WRAPPER_READ_TABLE_BASE(p), oldptr); \
	    }; \
	  { \
	    register Object oldptr = SI_WRAPPER_WRITE_TABLE_BASE(p); \
	    one(&(SI_WRAPPER_WRITE_TABLE_BASE(p))); \
	    adjust(&(SI_WRAPPER_WRITE_TABLE(p)), SI_WRAPPER_WRITE_TABLE_BASE(p), oldptr); \
	    }; \
	  /* continue with rest of object, since it is normal */ \
	  c_many(p, (p + len - &SI_WRAPPER_CLASS(p)), &SI_WRAPPER_CLASS(p))

#define DO_OPTIONAL_EFF_METHOD_COMBINATION() \
      case SI_EFFECTIVE_METHOD_TYPE:   \
      case SI_METHOD_COMBINATION_TYPE: 

#define DO_OPTIONAL_CLOS_WRAPPER(p, one)  one(&(INSTANCE_WRAPPER(p)))

#else /* !SI_SUPPORT_CLOS */

#define DO_OPTIONAL_SI_METHOD_TYPE() 
#define DO_OPTIONAL_SOME_OR_NONE(p,c_none,c_many,c_one,one,one_proc,adjust) \
         c_none(p, len)  
#define DO_OPTIONAL_EFF_METHOD_COMBINATION() 
#define DO_OPTIONAL_CLOS_WRAPPER(p, one)  

#endif /* !SI_SUPPORT_CLOS */


#if SI_CONSES_HAVE_HEADERS

/* Object ptr; */
/* true length in words, including header */
#define GC_LENGTH(ptr)				\
     (hdr_lc_easylength(object_to_header(ptr)) ? \
         easy_gc_length(object_to_header(ptr)) \
      :  align_size(hard_gc_length(object_to_header(ptr), ptr)))

#else /* !SI_CONSES_HAVE_HEADERS */

/* Object ptr; */
/* true length in words, including header */
#define GC_LENGTH(ptr)				\
  (is_header(object_to_header(ptr)) ? \
     (hdr_lc_easylength(object_to_header(ptr)) ? \
         easy_gc_length(object_to_header(ptr)) \
      :  align_size(hard_gc_length(object_to_header(ptr), ptr))) \
    : HEADERLESS_LENGTH)

#endif /* !SI_CONSES_HAVE_HEADERS */

static inline long
gc_length(ptr)
Object ptr;
{
  register long len;
  /* register */ SI_Header w;    /* *** SLOW *** */

  w = object_to_header(ptr);

#if !SI_CONSES_HAVE_HEADERS
  if (is_header(w)) {
#endif /* !SI_CONSES_HAVE_HEADERS */

    if (hdr_lc_easylength(w)) {
      len = easy_gc_length(w);
    } else {
      len = align_size(hard_gc_length(w, ptr));
    }

#if !SI_CONSES_HAVE_HEADERS
  } else {
    len = HEADERLESS_LENGTH;
  }
#endif /* !SI_CONSES_HAVE_HEADERS */

  return(len);
}

static preserve_package();

static void
nonheap_object_refs(preserve)
     void (*preserve)();
{
  register long i;

  Object node;
  Stack_item *temp, item;
  long indirect = FALSE;
  extern Object SI_Initial_packages;

  /* Preserve external roots */
  { Root_items *temp = SI_Gc_external_roots;

    while (temp != NULL) {
      register long i = 0;

      while (i < temp->count) {
	preserve(temp->roots[i]);
	i++;
      }
      temp = temp->next;
    }
  }

  /* Preserve initial packages (others will be found in static area) */
  if (SI_Initial_packages == UNBOUND)
    SI_Initial_packages = List_of_packages;

  /* This code assumes that these cons cells are not in dynamic space! */
  for (node = SI_Initial_packages; node != NIL; node = M_CDR(node))
    preserve_package(M_CAR(node), preserve);

  /* Preserve Lisp Stack */
  for (temp = Lisp_stack; temp != Stack; temp++) {
    item = *temp;
    if (item.object == PROTECT_MARKER)  /* start/end of indirect nodes */
      indirect = ~indirect;
    else if (indirect)
      preserve(item.location);
    else
      preserve(&(temp->object));
  }
  
  /* Preserve special variable stack */
  { register SI_Special_frame *temp = SI_Special_stack;
    while (temp != NULL) {
      if (temp->location == NULL)   /* Temp hack for old special bindings */
          preserve(&(temp->symbol));
      preserve(&(temp->saved_value));
      temp = temp->link;
    }
  }
  /* Preserve catch frame stack */
  { register SI_Catch_frame *temp = SI_Catch_stack;
    while (temp != NULL) {
      preserve(&(temp->tag));
      temp = temp->link;
    }
  }

  /* Preserve Values array */
#ifdef RETURN_MULTIPLE_VALUES
  for (i = 0; i+1 < Values_count; ++i)
    preserve(&(Values[i]));
#else
  for (i = 0; i+1 < MAXARGS; ++i)
    preserve(&(Values[i]));
#endif
}

/*
 * utility for dealing with package objects
 */
static preserve_package(obj, preserve)
     Object obj;
     void (*preserve)();
{
    register long i, count;
    SYMBOL_NODE *symtab;
    Object sym;

    DO_OPTIONAL_CLOS_WRAPPER(obj, preserve);

    preserve(&(PACKAGE_NICKNAMES(obj)));
    preserve(&(PACKAGE_USE_LIST(obj)));
    preserve(&(PACKAGE_USED_BY_LIST(obj)));
    preserve(&(PACKAGE_SHADOWING_SYMBOLS(obj)));

    /* trace array of initial symbols and imports */
    symtab = PACKAGE_SYMTAB(obj);
    if (symtab != NULL) {
	count = PACKAGE_SYMBOL_COUNT(obj);
	for (i = 1; i <= count; i++) {
	    sym = TAG_ISYMBOL(symtab, i);
	    switch (ISYMBOL_TYPE(sym)) {
	    case SYMBOL_TYPE:		/* Initial symbol */
	    case ESYMBOL_TYPE:		/* External initial symbol */
	    case KEYWORD_TYPE:		/* Initial keyword symbol */
		preserve(&(ISYMBOL_PLIST(sym)));
		break;
	    case INDIRECT_TYPE:
	    case EINDIRECT_TYPE:
		/* Necessarily points to an initial symbol, which will be
		   encountered on scanning another package. */
		/* Dmitry and Kim claim this might not point to an
		   initial symbol, so... */
		preserve(&(INDIRECT_SYMBOL(sym))); /* really plist! */
		break;
	    default:
		gcwarn("unexpected object found in initial package ");
		gcwarn(PACKAGE_NAME(obj));
		gcwarn("\n");
	    }
	}
    }
}

/*
 * Primary dispatch for all objects.
 * This code knows how to find all the pointers inside of any object,
 * but all it does is use the operations passed in to "follow" them.
 * The operations are merely various ways of encoding information about
 * the length and pointer-contents of the object.
 */
#ifdef undef
static void
lc_interpret(p, c_none, c_many, c_one, one, p_one, adjust)
     Object *p;
     void (*c_none)();
     void (*c_many)();
     void (*c_one)();
     void (*one)();
     void (*p_one)();
     void (*adjust)();
#else /* undef */
/* Object *p; */ 
#endif /* undef */

/* The PREAMBLE and POSTAMBLE are for headerless conses. */
#define LC_INTERP_CH_PREAMBLE(p,w)  /*** Don't use a semicolon! ***/ \
  if (is_header(w)) {
#define LC_INTERP_CH_POSTAMBLE(p,w,c_many) /*** Don't use a semicolon! ***/ \
  } else { /* headerless */ \
    c_many(p, 2, p); \
  }

#define LC_INTERPRET(p, c_none, c_many, c_one, one, one_proc, adjust)      \
{ \
  /* register */ SI_Header w; \
  register long len; \
 \
  w = object_to_header((Object)p); \
  LC_INTERP_CH_PREAMBLE(p,w) \
    if (hdr_lc_easylength(w)) { \
      len = easy_gc_length(w); \
      if (hdr_lc_easy_boring(w)) { \
	c_none(p, len); \
      } else if (hdr_lc_easy_normal(w)) { \
	c_many(p, len, p); \
      } else {  /* ugly */ \
	switch (hdr_lc_easy_typecode(w)) { \
	case COBJECT_TYPE:	/* Pointer to C object - don't disturb */ \
	  DO_OPTIONAL_CLOS_WRAPPER(p, one); \
	  c_one(p, len, &(COBJECT_NAME(p))); \
	case HASH_TABLE_TYPE: \
	  DO_OPTIONAL_CLOS_WRAPPER(p, one); \
	  c_one(p, len, &(HASH_ARRAY(p))); \
 \
	  /* other */ \
	case PACKAGE_TYPE: \
	  preserve_package((Object)p, one_proc); \
	  c_none(p, len); \
	  break; \
	case MSYMBOL_TYPE: \
	case EMSYMBOL_TYPE: \
	  one(&(MSYMBOL_NEXT(p))); \
	  /* FALLTHROUGH */ \
	case MKEYWORD_TYPE: \
	case SYMBOL_TYPE: \
	case ESYMBOL_TYPE: \
	case KEYWORD_TYPE: \
	case INDIRECT_TYPE: \
	case EINDIRECT_TYPE: \
	  c_one(p, len, &(SI_SYMBOL_PLIST(p))); \
	  break; \
 \
	case VALUE_CELL_TYPE: \
          DO_VALUE_CELL_CASE(p,c_none,c_many,c_one,one,one_proc,adjust); \
 \
	case STREAM_TYPE: \
	  DO_OPTIONAL_CLOS_WRAPPER(p, one); \
	  c_one(p, len, &(STREAM_OBJ(p))); \
	  break; \
	   \
        DO_OPTIONAL_SI_METHOD_TYPE(); \
	case SI_FUNCTION_TYPE: \
	  one(&(SI_FUNCTION_ENV(p))); \
	  /* FALLTHROUGH */ \
 \
        DO_OPTIONAL_SOME_OR_NONE(p, c_none, c_many, c_one, one, one_proc, adjust); \
	  /* These should be in the SI_BORING category of length_status */ \
	case RANDOM_STATE_TYPE: \
	  DO_OPTIONAL_CLOS_WRAPPER(p, one); \
          /* FALL THROUGH */ \
	case FIXNUM_TYPE: /* SHOULD NEVER OCCUR */ \
	case OBIGNUM_TYPE: /* BORING */ \
	case DOUBLE_TYPE: /* BORING */ \
	case WINDOW_TYPE: /* BORING */ \
	  c_none(p, len); \
	  /* These should be in the SI_NORMAL category of length_status */ \
	case READTABLE_TYPE: /* NORMAL */  \
	  DO_OPTIONAL_CLOS_WRAPPER(p, one); \
	  c_one(p, len, &(READTABLE_ENTRIES(p))); \
	  break; \
        case BIGNUM_TYPE: \
        case RATIO_TYPE: \
        case CONS_TYPE: \
        case COMPLEX_TYPE: \
        case USYMBOL_TYPE: \
        case PATHNAME_TYPE: \
        case SI_GENERAL_ARRAY_TYPE: \
        case SI_STRUCTURE_TYPE: \
        DO_OPTIONAL_EFF_METHOD_COMBINATION(); \
	  c_many(p, len, p); \
 \
	default: \
	  /* shouldn't happen -- no unknown ugly objects allowed! */ \
	  error(1,"gc dispatch: unknown object type (BUG)"); \
	} \
      } \
    } else {  /* more expensive length calculation for simple vectors */ \
      len = align_size(hard_gc_length(w, p)); \
 \
      if (hdr_lc_hard_boring(w)) { \
	c_none(p, len); \
      } else { \
	c_many(p, (p + len - SI_PRIMITIVE_VECTOR_CONTENTS(p, SI_PVT_Object)), SI_PRIMITIVE_VECTOR_CONTENTS(p, SI_PVT_Object)); \
      } \
    } \
  LC_INTERP_CH_POSTAMBLE(p,w,c_many) \
}

/* macros for processing pointers */
#define do_skip(p, howfar)       { p += howfar; goto done; }
#define do_many(p, howfar, start) { p = start; \
				 limit = p + howfar; \
				 goto many_loop; }
#define do_one(p, howfar, spot) { aptr = spot; \
			       p = p + howfar; \
			       goto just_one_spot; }

/* efficiently process pointers in an object */
/* p is positioned after the object when done */
#define MAP_ONTO_POINTERS(follow, p_follow, adjust, p)     \
{ \
    register Object *limit; \
    register Object *aptr; \
 \
LC_INTERPRET(p, do_skip, do_many, do_one, follow, p_follow, adjust); \
  \
many_loop: \
     while (p < limit) { follow(p); p++; }; \
     goto done; \
just_one_spot: \
     follow(aptr); \
done: \
  /* null stmt */; \
  }

#ifdef undef
static void
map_onto_pointers(follow, p_follow, adjust, p)
     void (*follow)();
     void (*p_follow)();
     void (*adjust)();
     Object *p;
{
  MAP_ONTO_POINTERS(follow, p_follow, adjust, p);
}
#endif /* undef */


/**
 ** Forwarding -- must be unambigous with normal object reps.
 **/
#define FWDED(obj)    (object_to_ptr(obj)[0] == SI_FORWARDING_MARKER)

#if UNMACROIZE_GC_MACROS
static inline int
fwded(obj)
     Object obj;
{
  /* check whether this object has already been forwarded */
  return(FWDED(obj));
}
#else /* not UNMACROIZE_GC_MACROS */
#define fwded(obj)	FWDED(obj)
#endif /* not UNMACROIZE_GC_MACROS */


#define FWDED_TARGET(obj)	(object_to_ptr(obj)[1])

#if UNMACROIZE_GC_MACROS
static inline Object
fwded_target(obj)
     Object obj;
{
  /* obtain the new address of this object, assuming it is forwarded */
  return(FWDED_TARGET(obj);
}
#else /* not UNMACROIZE_GC_MACROS */
#define fwded_target(obj)	FWDED_TARGET(obj)
#endif /* not UNMACROIZE_GC_MACROS */


/* mark this object as forwarded */
#define FORWARD(obj, target)       { \
  object_to_ptr(obj)[0] = SI_FORWARDING_MARKER; \
  object_to_ptr(obj)[1] = target; \
  }

#if UNMACROIZE_GC_MACROS
static inline void
forward(obj, target)
     Object obj;
     Object target;
{
  FORWARD(obj, target);
}
#else /* not UNMACROIZE_GC_MACROS */
#define forward(obj, target)	FORWARD(obj, target)
#endif /* not UNMACROIZE_GC_MACROS */


/*
 * deal with possible gaps due to alignment
 *    and due to vector shortening
 */
#if !EVERYTHING_ALIGNED
#define SKIP_ALIGNMENT_WORDS(sp, BODY)   \
{ if (*sp == SI_ALIGNMENT_MARKER) { \
      sp++; \
  } else { \
      BODY; \
  } \
}
#else
#define SKIP_ALIGNMENT_WORDS(sp, body)   /* no alignment words */ body
#endif

#define FLUSH_NONE()    /* nothing to flush */ 0

/*
 * area_object_refs
 *
 * This iterates over the inter-object references appearing in
 * any object in any segment of this area.
 */
#define AREA_OBJECT_REFS(ar, preserve,p_preserve,preserve_derived,refresh) \
{ \
  SI_Segment *seg; \
  long donescanning; \
 \
  for (seg = ar.first_segment; seg != NULL; seg = seg->next) \
    seg->gc_maptemp = seg->start; /* initialize per-segment scanptrs */ \
  donescanning = 0; /* indicate whether all objects have been examined */ \
  while (!donescanning) { \
    donescanning = 1; /* assume one pass will get them all */ \
    for (seg = ar.first_segment; seg != NULL; seg = seg->next) { \
      register Object *scanptr = (Object *)seg->gc_maptemp; \
      register Object *scanlimit = (Object *)seg->frontier; \
   \
    /*** Must do this on a per-segment basis ***/ \
      while ((scanptr < scanlimit) \
	     /* just in case segment is growing, refresh scanlimit */ \
	     || ((refresh()) /* Uncache anything growing area! */, \
		 (scanlimit = (Object *)seg->frontier) /* assignment! */, \
		 (scanptr < scanlimit))) { \
	SKIP_ALIGNMENT_WORDS(scanptr, \
	 { SKIP_RELOCATION_WORD(scanptr); \
	   MAP_ONTO_POINTERS(preserve,p_preserve, preserve_derived, scanptr); \
           donescanning = 0; /* outside call may add objects, must recheck */ \
	   } ); \
      } \
      seg->gc_maptemp = (void *)scanptr; /* save scanptr for scan restart */ \
    } \
  } \
} 


static void
area_object_refs(ar, preserve, p_preserve, preserve_derived)
     SI_Area ar;
     void (*preserve)();
     void (*p_preserve)();
     void (*preserve_derived)();
{
  AREA_OBJECT_REFS(ar, preserve, p_preserve, preserve_derived, FLUSH_NONE);
}

/*
 * area_objects
 *
 * This iterates over the objects appearing in any segment of this area.
 */
#define AREA_OBJECTS(ar, preserve, refresh)       \
{ \
  SI_Segment *seg; \
  long donescanning; \
 \
  for (seg = ar.first_segment; seg != NULL; seg = seg->next) \
    seg->gc_maptemp = seg->start; /* initialize per-segment scanptrs */ \
  donescanning = 0; /* indicate whether all objects have been examined */ \
  while (!donescanning) { \
    donescanning = 1; /* assume one pass will get them all */ \
    for (seg = ar.first_segment; seg != NULL; seg = seg->next) { \
      register Object *scanptr = (Object *)seg->gc_maptemp; \
      register Object *scanlimit = (Object *)seg->frontier; \
   \
    /*** Must do this on a per-segment basis ***/ \
      while ((scanptr < scanlimit) \
	     /* just in case segment is growing, refresh scanlimit */ \
	     || ((refresh()) /* Uncache anything growing area! */, \
		 (scanlimit = (Object *)seg->frontier) /* assignment! */, \
		 (scanptr < scanlimit))) { \
	register long len; \
   \
	SKIP_ALIGNMENT_WORDS(scanptr, \
	  { SKIP_RELOCATION_WORD(scanptr); \
	    len = GC_LENGTH(ptr_to_object(scanptr)); \
	    preserve(ptr_to_object(scanptr), len); \
	    donescanning = 0; /* outside call may add objects, must recheck */ \
	    scanptr += len; \
	    } ); \
      } \
      seg->gc_maptemp = (void *)scanptr; /* save scanptr for scan restart */ \
    } \
  } \
} 


static void
area_objects(ar, preserve)
     SI_Area ar;
     void (*preserve)();
{
  AREA_OBJECTS(ar, preserve, FLUSH_NONE);
}

