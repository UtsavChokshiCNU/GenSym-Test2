/*
 *
 *
 * copygc.c - garbage collector
 *
 * J. O'Toole
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area_copy;
extern SI_Area Dynamic_area;
extern Object Gc_inhibit;
extern Object Gc_silence;
extern SI_Stack_item *Lisp_stack;
extern Object List_of_packages;
extern SI_Area Local_area;
extern TLS SI_Catch_frame *SI_Catch_stack;
extern TLS SI_Special_frame *SI_Special_stack;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern long SI_gc_count;
extern Object SI_gc_genobj;
extern SI_Area Static_area;
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif



#if SI_COPYING_COLLECTOR

#include "gc.h"

/* Include object reference mapping operations and area iterators. */
#include "gcobjmap.h"



#ifdef DEBUG
/* 
   stop in note_event
   set watch_node = 0x1f4468
 */
static Object watch_node;
static note_event (s) char *s; {
    fprintf(stderr, "Attention - %s\n", s);
}
#endif

/*
 * Copying GC must be able to determine membership in target area
 */
#if SI_SEGMENTED_DYNAMIC_AREA

/* If the dynamic area is segmented, the collector relies on labels
   which appear in the header words of stored objects.
   */
#if !(SI_VISIT_EXACTLY_ONCE && SI_CONSES_HAVE_HEADERS)
/* Note: it is Impossible configuration for copying collector,
 * but because customers who are willing to provide explicit 
 * memory management and compact list representation might
 * prefer this configuration, we allow it to be 
 * linked with no-collecting applications only as defined in 
 * uconfig.h (with US_ENSURE__GC == 0). For extra protection,
 * error reporting copy primitives provided
 */
#define is_relocatable(o)  \
       (error(1,"Can not relocate data, wrong configuration"))
#define should_copy(o) is_relocatable(o)
#else

#if SI_DYNAMICNESS_LABELED

/* The invariant used with the dynamicness labels is that objects outside
   of the Dynamic areas always have their labels set to SI_GC_NONRELOCATABLE.
   Even though objects which have been copied to TO space appear to be
   relocatable, the garbage collector will not relocate them again because
   SI_VISIT_EXACTLY_ONCE ensures that the collector will never revisit
   an object reference which has already been updated to point to TO space.
   */

#define is_relocatable(o)  \
   SI_ENUM_NE(SI_STORED_OBJECT_FIELD(o, SI_Header, gcrelocatable), \
	      SI_GC_NONRELOCATABLE)
#define should_copy(o)    (is_pointer(o) && is_relocatable(o))

#else
#include "Impossible configuration for copying collector."
#endif /* SI_DYNAMICNESS_LABELED */
#endif /* (SI_VISIT_EXACTLY_ONCE && SI_CONSES_HAVE_HEADERS) */
#else /* !SI_SEGMENTED_DYNAMIC_AREA */

/* With a single segment, the collector uses a quick address range test. */
static Object *from_bottom, *from_top;

#define should_copy(o)  (is_pointer(o) \
			 && (object_to_ptr(o) >= from_bottom) \
			 && (object_to_ptr(o) <= from_top))

#endif /* !SI_SEGMENTED_DYNAMIC_AREA */

/* Copying collector uses globals to track new frontier in TO space. */
static SI_Segment *copyseg;
static Object *copyptr, *copylimit;

#define SETUP_COPYPTR() \
  { SI_Segment *seg;  \
    for (seg = Dynamic_area_copy.first_segment; seg; seg = seg->next) \
      seg->frontier = seg->start; \
    } \
  copyseg = Dynamic_area_copy.first_segment; \
  copyptr = (Object *)copyseg->frontier; \
  copylimit = (Object *)copyseg->limit;

#define FLUSH_COPYPTR() \
    (copyseg->frontier = (void *)copyptr)

#if !EVERYTHING_ALIGNED
#define CHECK_FOR_SPACE(ptr, gclen) \
    while (copyptr + gclen + 1 > copylimit) { \
        if (!((needs_alignment(ptr)) && (not_aligned(copyptr)) \
	      || (copyptr + gclen > copylimit))) \
	    break; /* fits anyway, because no alignment */ \
	FLUSH_COPYPTR(); \
	copyseg = copyseg->next; \
        /* Due to reordering, Objects might pack more loosely, and we lose */ \
        /* if (!copyseg) error(1, "heap corrupted"); */ \
	if (!copyseg) copyseg = Dynamic_area_copy.first_segment; \
	copyptr = (Object *)copyseg->frontier; \
        copylimit = (Object *)copyseg->limit; \
    }

#define ALIGN_COPYPTR(o)   \
{ if ((needs_alignment(o)) && (not_aligned(copyptr))) {  \
    *copyptr = SI_ALIGNMENT_MARKER; \
    copyptr++; \
  } \
}

#else

#define CHECK_FOR_SPACE(ptr, gclen) \
    while (copyptr + gclen > copylimit) { \
	FLUSH_COPYPTR(); \
	copyseg = copyseg->next; \
        /* Due to reordering, Objects might pack more loosely, and we lose */ \
        /* if (!copyseg) error(1, "heap corrupted"); */ \
	if (!copyseg) copyseg = Dynamic_area_copy.first_segment; \
	copyptr = (Object *)copyseg->frontier; \
        copylimit = (Object *)copyseg->limit; \
    }

#define ALIGN_COPYPTR(o)   /* none */

#endif /* EVERYTHING_ALIGNED */

#define COPY(result, ptr)    \
{ \
  register int len; \
 \
  len = GC_LENGTH(ptr); \
  CHECK_FOR_SPACE(ptr, len); \
  ALIGN_COPYPTR(ptr); \
  BCOPY((char *)object_to_ptr(ptr), (char *)copyptr, len * sizeof(Object)); \
  result = SI_TAG_STORED(copyptr, SI_TAG_OF(ptr)); \
  copyptr += len; \
  /* return(result) */; \
}

/*
 * The basic copying collector operation for preserving live data.
 * The should_copy test is done first on single-segment heap because
 * it might save a page fault.  The fwded test is done first on multi-segment
 * heaps because a forwarded object appears non-relocatable, due to the
 * header word being overwritten.
 */
#if SI_SEGMENTED_DYNAMIC_AREA

/* Object *ptrp; */
#define COLLECT(ptrp)				\
{ \
  register Object ptr, newptr; \
 \
  ptr = *ptrp; \
 \
  /* if this is a valid pointer into from space, then copy+forward */ \
  if (is_pointer(ptr)) { \
    if (fwded(ptr)) { \
      *ptrp = fwded_target(ptr); \
    } else { \
      if (is_relocatable(ptr)) { \
        COPY(newptr, ptr); \
        forward(ptr, newptr); \
        *ptrp = newptr; \
      } \
    } \
  } \
}

#else /* !SI_SEGMENTED_DYNAMIC_AREA */

/* Object *ptrp; */
#define COLLECT(ptrp)				\
{ \
  register Object ptr, newptr; \
 \
  ptr = *ptrp; \
 \
  /* if this is a valid pointer into from space, then copy+forward */ \
  if (should_copy(ptr)) { \
    if (fwded(ptr)) { \
      *ptrp = fwded_target(ptr); \
    } else { \
      COPY(newptr, ptr); \
      forward(ptr, newptr); \
      *ptrp = newptr; \
    } \
  } \
}

#endif /* !SI_SEGMENTED_DYNAMIC_AREA */

static inline void
collect (ptrp)
     Object *ptrp;
{
  COLLECT(ptrp);
}


/*
 * The adjustment operation, used for derived pointers, which appear
 * in a few very ugly objects.
 */
#define ADJUST(ptrp, newptr, oldptr)       \
{*ptrp = (Object)((SI_Ulong)*ptrp + (SI_Ulong)newptr - (SI_Ulong)oldptr);}

static inline void
adjust (ptrp, newptr, oldptr)
     Object *ptrp;
     Object newptr;
     Object oldptr;
{
  ADJUST(ptrp, newptr, oldptr);
}

/*
 * Flipping takes place immediately after each copying collection.
 */
static void
flip ()
{
  SI_Area tmp;

  /* Finished copying, so done with variables controlling copy destination. */
  FLUSH_COPYPTR();

  /* swap areas */
  tmp = Dynamic_area;
  Dynamic_area = Dynamic_area_copy;
  Dynamic_area_copy = tmp;
}

/*
 * Scanning a space using the collect/adjust operations is the
 * core of the copying collection algorithm.  The reason it looks
 * so simple is that the gcobjmap.h macros provide extensive
 * support for mapping such operations sequentially over objects
 * in an area and interobject references within each object.
 *
 * Hopefully, clever use of macros provides adequate performance
 * even in this somewhat abstract presentation of the algorithm.
 */
static void
scan_space (space)
     SI_Area space;
{
  AREA_OBJECT_REFS(space, COLLECT, collect, ADJUST, FLUSH_COPYPTR);
}

/*
 * Collecting the roots of the heap requires an examination of all
 * locations outside of the heap which may contain references into
 * the heap.  This includes the so-called Static_area, which contains
 * data in heap representation, but which is not worth attempting to
 * collect, as well as any object references which appear in non-heap
 * data, such as in C variables.
 */
static void
collect_roots ()
{
  scan_space(Static_area);
  nonheap_object_refs(collect);
#if SI_SCAN_LOCAL_AREA
  scan_space(Local_area);
#endif /* SI_SCAN_LOCAL_AREA */
}

/*
 * This is used for non-local transfer of control after gc,
 * if RTL was performing a gc unsafe operation.
 */

extern long SI_gc_unsafe;
extern jmp_buf SI_restart_unsafe;

/*
 * This is the only entry point into the garbage collector proper from
 * the runtime system.
 *
 * It invokes, in proper sequence, each phase of the copying collection
 * algorithm.
 */
extern int /* should be void BUG */
SI_garbage_collect ()
{
#if !SI_SEGMENTED_DYNAMIC_AREA
    SI_Segment *seg;
#endif

    Object save = Gc_inhibit;

    if (Current_area == &Dynamic_area)
      SI_FLUSH_ALLOC_CACHE();

    /* record that another garbage collection was triggered */
    SI_gc_count++;
    SI_gc_genobj = FIX(0);

    if (TRUEP(Gc_inhibit))
	gcwarn("GC called while Gc_inhibit is non-NIL\n");
    Gc_inhibit = T;
    if(Gc_silence == NIL)gcwarn("Garbage collecting...");

    /* setup global variables controlling copying destination */
    SETUP_COPYPTR();

#if !SI_SEGMENTED_DYNAMIC_AREA
    /* setup global variables describing area being collected */
    seg = Dynamic_area.current_segment;
    from_bottom = (Object *)seg->start;
    from_top = (Object *)seg->limit;
#endif /* !SI_SEGMENTED_DYNAMIC_AREA */

    /* iterate over protection entries in stack and static space */
    collect_roots();

    /* make scanptr meet copyptr */
    scan_space(Dynamic_area_copy);

    /* rearrange spaces */
    flip();

    if (Current_area == &Dynamic_area)
      SI_RELOAD_ALLOC_CACHE();

    Gc_inhibit = TRUEP(save) ? T : NIL;
    if(Gc_silence == NIL)gcwarn("done.\n");

    /* If RTL was doing unsafe operations, provide non-local exit. */
    if (SI_gc_unsafe != 0)
	longjmp(SI_restart_unsafe, 1);
}


#endif /* SI_COPYING_COLLECTOR */
