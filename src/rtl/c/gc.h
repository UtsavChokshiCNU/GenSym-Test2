/*
 * gc.h - macros and declarations for garbage collector
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

/* This is an internal configuration option which controls the treatment
   of the local area during a garbage collection.  In the past, the
   local area has been ignored during gc because users of the
   local area disabled garbage collection.  Now, for safety, the
   default behavior is to scan the local area (as if it is part of
   static space). */
#ifndef SI_SCAN_LOCAL_AREA
#define SI_SCAN_LOCAL_AREA     1
#endif

/* both are declared static in heap.c, */
#if 0 && !DEBUG  && !defined(__ZTC__)
extern int GC_Phase;
extern Object watch_node;
#endif

#if ALIGNMENT > 3
#define WORD_ALIGNMENT 3
#else
#define WORD_ALIGNMENT ALIGNMENT
#endif

/*
 * external root list
 */
#define GCRLIM      50
typedef struct Root_items_struct {
  struct Root_items_struct *next;
  long count;
  Object *roots[GCRLIM];
} Root_items;

extern Root_items *SI_Gc_external_roots;
extern void (*SI_garbage_collect_fptr)();

#if SI_COPYING_COLLECTOR
extern SI_Area Dynamic_area_copy;
#endif

/*****
 ***** These kinds of macros probably belong in object.h
 *****/
#if !SI_CONSES_HAVE_HEADERS

#define HEADERLESS_LENGTH 2L
#define HDRSIZE   sizeof(SI_Header)

#endif /* !SI_CONSES_HAVE_HEADERS */

#if SI_TAG_WIDTH == 3
#define GC_UNIVERSAL_ALIGNMENT     ((1<<SI_TAG_WIDTH)-1)
#define GC_SPORADIC_ALIGNMENT      GC_UNIVERSAL_ALIGNMENT
#define EVERYTHING_ALIGNED         1
#else /* variable alignment */
#define GC_UNIVERSAL_ALIGNMENT     (sizeof(Object) - 1L)
#define GC_SPORADIC_ALIGNMENT      (2*sizeof(Object) - 1L)
#define EVERYTHING_ALIGNED         0
#endif /* variable alignment */

#define is_pointer(o)  (SI_STORED_OBJECT_P(o))
#define object_to_header(o)  (*SI_UNTAG_STORED(o, SI_Header))
#define object_to_ptr(o)  (SI_UNTAG_STORED(o, Object))
#define ptr_to_object(p)  SI_TAG_STORED(p, SI_STORED_TAG_VALUE)
#define is_header(h) ((h).tag == SI_HEADER_TAG)
#define hdr_lc_easylength(h)  (SI_ENUM_LE((h).length_status,SI_NORMAL))
#define hdr_lc_easy_boring(h)  ((h).length_status == (unsigned)SI_BORING)
#define hdr_lc_hard_boring(h)  (SI_ENUM_GT((h).length_status,A_T))
#define hdr_lc_easy_normal(h)  ((h).length_status == (unsigned)SI_NORMAL)
#define hdr_lc_easy_typecode(h)   ((enum SI_type)(h).type)
#define easy_gc_length(h) ((h).gclength)
#define hard_gc_length(h,p) (calc_vector_size((enum SI_etype)((h).length_status), SI_PRIMITIVE_VECTOR_LENGTH(p)))
#define FORWARDING_MARKER  SI_MAKE_TOKEN(SI_TOKEN_ID_GC_FORWARDING)
#define align_size(bytes)  (((bytes + GC_UNIVERSAL_ALIGNMENT)&(~GC_UNIVERSAL_ALIGNMENT))/sizeof(Object))
#define not_aligned(p)  ((unsigned)p & GC_SPORADIC_ALIGNMENT)
#define easy_aligned(h)  ((h).gcaligned == (unsigned)SI_GC_ALIGNED)
#define hard_aligned(h)  ((h).length_status == (unsigned)A_DOUBLE_FLOAT) /** BUG **/

#if SI_CONSES_HAVE_HEADERS
#define needs_alignment(ptr)    \
     (hdr_lc_easylength(object_to_header(ptr)) ? \
         easy_aligned(object_to_header(ptr)) \
      :  hard_aligned(object_to_header(ptr)))
#else
#define needs_alignment(ptr)    \
     (is_header(object_to_header(ptr)) \
      && (hdr_lc_easylength(object_to_header(ptr)) ? \
             easy_aligned(object_to_header(ptr)) \
          :  hard_aligned(object_to_header(ptr))))
#endif /* SI_CONSES_HAVE_HEADERS */

#if !SI_COPYING_COLLECTOR
#define relocated_position(ptr)  (object_to_ptr(ptr)[-1])
#endif

#define inline /* */

/* difficult length calculation */
static inline long /* length in BYTES */
calc_vector_size(etype, size)
     enum SI_etype etype;
     SI_Long size;
{
  long size_in_bytes;
  Object result = NULL; /* used only for length computation macro */

    switch (etype) {
#define DO_IT(t) \
	size_in_bytes = (long)(\
	    (char *) &SI_PRIMITIVE_VECTOR_CONTENTS(result, t)[size] - \
		SI_UNTAG_STORED(result, char)); \
        break;
    case A_T:
	DO_IT(SI_PVT_Object);
    case A_STRING_CHAR:
	++size;   /* size doesn't include the terminating null char. */
	DO_IT(SI_PVT_Char);
    case A_SINGLE_FLOAT:
	DO_IT(SI_PVT_Float);
    case A_DOUBLE_FLOAT:
	DO_IT(SI_PVT_Double);
    case A_BIT:
	size = ((size + SI_BITS_TYPE_MASK) >> SI_BITS_TYPE_SHIFT);
	DO_IT(SI_PVT_Bits);
    case A_BYTE_8:
	DO_IT(SI_PVT_Char);
    case A_BYTE_16:
	DO_IT(SI_PVT_Short);
    case A_BYTE_32:
	DO_IT(SI_PVT_Long);
    case A_BYTE_64:
	DO_IT(SI_PVT_Long64);
    case A_UNSIGNED_BYTE_8:
	DO_IT(SI_PVT_Uchar);
    case A_UNSIGNED_BYTE_16:
	DO_IT(SI_PVT_Ushort);
    case A_UNSIGNED_BYTE_32:
	DO_IT(SI_PVT_Ulong);
    case A_UNSIGNED_BYTE_64:
	DO_IT(SI_PVT_Ulong64);
    default:
	error(1,"calc_vector_length: unknown element type");
    }
  return(size_in_bytes);
#undef DO_IT
}
    

/* Use this instead of warn, to avoid inconsistency problems. */
#define gcwarn(s)    { fputs(s, stdout); fflush(stdout); }

