/*
 *
 *
 * markgc.c - mark+sweep garbage collector
 *
 * J. O'Toole
 * Copyright (c) 1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"

#if !SI_COPYING_COLLECTOR

#include "gc.h"

/* Include object reference mapping operations and area iterators. */
#include "gcobjmap.h"




/*
 * Mark+sweep GC, compaction phase depends on knowing relocatable objects.
 */
#if SI_DYNAMICNESS_LABELED

#if SI_STATIC_RELOCATION_WORDS

#define should_copy(o)  \
  (is_pointer(o) && (relocated_position(o) != SI_NONRELOCATABLE_MARKER))

#else /* use bit in header */

#define should_copy(o)  \
  (is_pointer(o) && (SI_STORED_OBJECT_FIELD(o, SI_Header, gcrelocatable) \
		       != SI_GC_NONRELOCATABLE))

#endif /* SI_STATIC_RELOCATION_WORDS */

#else

static Object *from_bottom, *from_top;

#define in_target_area(p)  (((Object *)p >= from_bottom) \
			    && ((Object *)p <= from_top))
#define should_copy(p)  (is_pointer(p) && in_target_area(p))

#endif /* SI_DYNAMICNESS_LABELED */

/* global temps -- record post-compaction phase frontier information */
static SI_Segment *copyseg;
static Object *copyptr, *copylimit;

#define SETUP_COPYPTR() \
  { SI_Segment *seg;  \
    for (seg = Dynamic_area.first_segment; seg; seg = seg->next) \
      seg->gc_temp = seg->start; \
    } \
  copyseg = Dynamic_area.first_segment; \
  copyptr = (Object *)copyseg->gc_temp; \
  copylimit = (Object *)copyseg->limit;

#define FLUSH_COPYPTR() \
    (copyseg->gc_temp = (void *)copyptr)


#if !EVERYTHING_ALIGNED

#define CHECK_FOR_SPACE(ptr, gclen) \
    while (copyptr + gclen + 2 > copylimit) { \
        if (!((needs_alignment(ptr)) && (not_aligned(copyptr+1)) \
	      || (copyptr + gclen + 1 > copylimit))) \
	    break; /* fits anyway, because no alignment */ \
	FLUSH_COPYPTR(); \
	copyseg = copyseg->next; \
	if (!copyseg) error(1, "heap corrupted"); \
	copyptr = (Object *)copyseg->start; \
        copylimit = (Object *)copyseg->limit; \
    }

#define ALIGN_COPYPTR(o)   \
{ if ((needs_alignment(o)) && (not_aligned(copyptr))) {  \
    copyptr++; \
  } \
}

#else

#define CHECK_FOR_SPACE(ptr, gclen) \
    while (copyptr + gclen + 1 > copylimit) { \
	FLUSH_COPYPTR(); \
	copyseg = copyseg->next; \
	if (!copyseg) error(1, "heap corrupted"); \
	copyptr = (Object *)copyseg->start; \
        copylimit = (Object *)copyseg->limit; \
    }

#define ALIGN_COPYPTR(o)   /* none */

#endif

#if !SI_VISIT_EXACTLY_ONCE

/* compute_sneaky_bit, maybe_update_ref and fixup_ref use these */
static Object *top_unused, *bottom_unused;

#define in_unused_area(p)  (((Object *)p >= bottom_unused) \
			    && ((Object *)p <= top_unused))

/* kludge to avoid updating the same object ref twice */
#define SLOP   256
extern end; /* linker must provide info about end of address range */
static int sneaky_extra_bit;

/*
 * This procedure is somewhat kludgy.
 *
 * The mark+sweep collector does not use semispaces, and is intended
 * to be used when virtual memory is scarce.  However, the mark+sweep
 * algorithm does need a way to indicate that a pointer has been
 * updated.  This is necessary because of the existence of Object
 * pointers which are stored outside of the heap.  A copying collector
 * effectively marks such pointers as updated by making them point to
 * the TO-space.
 *
 * This is achieved in the mark+sweep collector by locating an unused
 * address range which would be sufficient to hold a semispace.  Then,
 * pointers to the Dynamic_area which have been updated are displaced
 * to the imaginary semispace, and are displaced back after the updates
 * have been completed.
 *
 * The methods used to locate the unused address range are ad hoc.
 * This code will fail if the layout of the address space is changed
 * much.  For example, it assumes that C data lies in a stack at the
 * top of the address space and in data/bss areas at the bottom of
 * the address space.
 */
static void
compute_sneaky_bit ()
{
    Object local_dummy_var; /* for determining the stack pointer */
    SI_Segment *seg;
    unsigned int gap_required;
    Object *least_dynamic_address, *greatest_dynamic_address;

    least_dynamic_address = Dynamic_area.first_segment->start;
    greatest_dynamic_address = Dynamic_area.first_segment->limit;

#define raise_bottom(x)  (bottom_unused = MAX(bottom_unused, (Object *)x))

    /* initialize gap estimates */
    top_unused = &local_dummy_var;
    bottom_unused = (Object *)&end;
    raise_bottom(&sneaky_extra_bit);

    /* move bottom up according to various address ranges of objects */
    raise_bottom(Lisp_stack);
    raise_bottom(Stack);
    for (seg = Static_area.first_segment; seg; seg = seg->next) {
	raise_bottom(seg->start);
	raise_bottom(seg->limit);
    }
    for (seg = Dynamic_area.first_segment; seg; seg = seg->next) {
	raise_bottom(seg->start);
	least_dynamic_address =
	  MIN(least_dynamic_address, (Object *)seg->start);
	raise_bottom(seg->limit);
	greatest_dynamic_address =
	  MAX(greatest_dynamic_address, (Object *)seg->limit);
    }
    for (seg = Local_area.first_segment; seg; seg = seg->next) {
	raise_bottom(seg->start);
	raise_bottom(seg->limit);
    }

#define universal_align(x) (((unsigned) x) & ~(GC_UNIVERSAL_ALIGNMENT))
    /* be paranoid */
    top_unused -= SLOP;
    top_unused = (Object *)universal_align(top_unused);
    bottom_unused += SLOP;
    bottom_unused = (Object *)universal_align(bottom_unused);

    gap_required = greatest_dynamic_address - least_dynamic_address;
    gap_required += SLOP;

    if ((top_unused > bottom_unused)
	&& ((top_unused - bottom_unused) > gap_required)) {
	sneaky_extra_bit = bottom_unused - (Object *)least_dynamic_address;
	sneaky_extra_bit *= sizeof(Object);
    } else {
	error(1, "mark+sweep gc: unable to locate unused address range");
	return;
    }
}
#endif /* !SI_VISIT_EXACTLY_ONCE */

#define IGNORE(x,y,z)     /* ignore */

static inline void
ignore(a, b, c)
     Object *a, b, c;
{
  IGNORE(a, b, c);
  return;
}

/* mark_node - mark arg and anything it points to as not free. */
/* This is the GC inner loop -- speed is of the essence! */
static void
mark_node (ptrp)
    Object *ptrp;
{
    register Object ptr = *ptrp;
    register Object *mp;

    if (should_copy(ptr)) {
	if (relocated_position(ptr) == SI_FORWARDING_MARKER) {
	    relocated_position(ptr) = SI_UNINITIALIZED_MARKER; /* marked */

	    /* recurse */
	    mp = object_to_ptr(ptr);
	    MAP_ONTO_POINTERS(mark_node, mark_node, IGNORE, mp);
	}
    }
}


/*
 * Marking from a space using the mark_node/ignore operations is the
 * core of the mark+sweep collection algorithm.  The reason it looks
 * so simple is that the gcobjmap.h macros provide extensive
 * support for mapping such operations sequentially over objects
 * in an area and interobject references within each object.
 *
 * Hopefully, clever use of macros provides adequate performance
 * even in this somewhat abstract presentation of the algorithm.
 */
static void
mark_this_space (space)
     SI_Area space;
{
  area_object_refs(space, mark_node, mark_node, ignore);
}

static void
mark_from_roots ()
{
  mark_this_space(Static_area);
  nonheap_object_refs(mark_node);
#if SI_SCAN_LOCAL_AREA
  mark_this_space(Local_area);
#endif /* SI_SCAN_LOCAL_AREA */
}

/*
 * This operation is used to sweep through all relocatable objects.
 * If the object has been marked as live, then the new position of
 * the object is calculated and recorded in the relocation word.
 */
/* Object ptr; */
/* int gclen; */
#define RECORD_RELOCATION(ptr, gclen)                                      \
    if (relocated_position(ptr) == SI_UNINITIALIZED_MARKER) {              \
	/* object is live */                                               \
	CHECK_FOR_SPACE(ptr, gclen);                                       \
	copyptr++; /* leave space for relocation word */                   \
	ALIGN_COPYPTR(ptr);                                                \
	relocated_position(ptr) = SI_TAG_STORED(copyptr, SI_TAG_OF(ptr));  \
	copyptr += gclen;                                                  \
    }

static inline void
record_relocation (ptr, gclen)
     Object ptr;
     int gclen;
{
    RECORD_RELOCATION(ptr, gclen);
}

static void
record_relocation_info ()
{
  /**** OPTIMIZATION --- modify lead dead object of a consecutive
    stretch of dead objects to encompass them all, so that later
    scans go faster ****/
  SETUP_COPYPTR();
  AREA_OBJECTS(Dynamic_area, RECORD_RELOCATION, FLUSH_NONE);
  FLUSH_COPYPTR();
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

#if SI_VISIT_EXACTLY_ONCE

/*
 * This operation is used to update an inter-object reference.
 * It is NOT used in this collector, because of the existence of inter-object
 * references which go indirect via off-heap data.  I am conservatively
 * assuming that the same inter-object reference might be visited twice
 * during the update phase (empirical data supports this assumption).
 * Therefore, the operations MAYBE_UPDATE_REF and FIXUP_REF are used.
 * The effect of one-or-more invocations of MAYBE_UPDATE_REF, followed by
 * one-or-more invocations of FIXUP_REF, should be identical to a single
 * invocation of update_ref.
 */
/* Object *ptrp; */
#define UPDATE_REF(ptrp)                    \
{                                           \
    register Object ptr = *ptrp;            \
                                            \
    if (should_copy(ptr))                   \
	*ptrp = relocated_position(ptr);    \
}

static inline void
update_ref (ptrp)
     Object *ptrp;
{
    UPDATE_REF(ptrp);
}

static void
update_space (space)
     SI_Area space;
{
  AREA_OBJECT_REFS(space, UPDATE_REF, update_ref, ADJUST, FLUSH_NONE);
}

#else /* !SI_VISIT_EXACTLY_ONCE */

/*
 * This operation does what UPDATE_REF does, but then displaces the resulting
 * pointer into the unused portion of the address space, so that repeated
 * invocations of this operation will have no bad effect.
 */
/* Object *ptrp; */
#define MAYBE_UPDATE_REF(ptrp)                                                \
{                                                                             \
    register Object ptr = *ptrp;                                              \
                                                                              \
    if (!in_unused_area(ptr) && should_copy(ptr))                             \
      *ptrp = (Object)((SI_Ulong)relocated_position(ptr) + sneaky_extra_bit); \
}

static inline void
maybe_update_ref (ptrp)
     Object *ptrp;
{
    MAYBE_UPDATE_REF(ptrp);
}

static void
maybe_update_space (space)
     SI_Area space;
{
  AREA_OBJECT_REFS(space, MAYBE_UPDATE_REF,maybe_update_ref,ADJUST, FLUSH_NONE);
}

/*
 * This operation cleans up after the MAYBE_UPDATE_REF operation, by
 * removing the offset from any inter-object refs which have been displaced
 * to point into the unused portion of the address space.
 */
/* Object *ptrp; */
#define FIXUP_REF(ptrp)                                             \
{                                                                   \
    register Object ptr = *ptrp;                                    \
                                                                    \
    if (is_pointer(ptr) && in_unused_area(ptr))                     \
	*ptrp = (Object)((SI_Ulong)ptr - sneaky_extra_bit);         \
}

static inline void
fixup_ref (ptrp)
     Object *ptrp;
{
    FIXUP_REF(ptrp);
}

static void
fixup_space (space)
     SI_Area space;
{
  AREA_OBJECT_REFS(space, FIXUP_REF, fixup_ref, ADJUST, FLUSH_NONE);
}

#endif /* !SI_VISIT_EXACTLY_ONCE */

static void
update_refs ()
{
#if SI_VISIT_EXACTLY_ONCE

  /* Each of these three calls should apply update_ref to separate
     parts of the memory system.  Update_ref must never be applied
     to the same object reference twice.  It must to applied to
     every object reference exactly once. */
  update_space(Static_area);
  nonheap_object_refs(update_ref);
#if SI_SCAN_LOCAL_AREA
  update_space(Local_area);
#endif /* SI_SCAN_LOCAL_AREA */
  update_space(Dynamic_area);

#else /* !SI_VISIT_EXACTLY_ONCE */

  /* Every pointer into Dynamic_area must be updated exactly once. */
  /* NOTE --- VALUE_CELL_LOCATION case will produce double updates
     from scanning areas, so code below only is careful for both
     nonheap data and heap data, at great expense. */
  maybe_update_space(Static_area);
  nonheap_object_refs(maybe_update_ref);
#if SI_SCAN_LOCAL_AREA
  maybe_update_space(Local_area);
#endif /* SI_SCAN_LOCAL_AREA */
  maybe_update_space(Dynamic_area);

  /* fixup */
  fixup_space(Static_area);
  nonheap_object_refs(fixup_ref);
#if SI_SCAN_LOCAL_AREA
  fixup_space(Local_area);
#endif /* SI_SCAN_LOCAL_AREA */
  fixup_space(Dynamic_area);

#endif /* !SI_VISIT_EXACTLY_ONCE */
}

/*
 * This operation relocates an individual live object.
 * It recomputes the correct new position for the object, even though the
 * position should be already recorded in the relocation word.  The reason
 * for this is that this is the easiest way to be sure to get the alignment
 * and relocation words positioned and initialized correctly.
 */
#define RELOCATE_IF_LIVE(ptr, gclen)                                      \
{                                                                         \
    register Object newptr = relocated_position(ptr);                     \
                                                                          \
    if (is_pointer(newptr)) { /* object is live */                        \
	CHECK_FOR_SPACE(ptr, gclen);                                      \
	*copyptr = SI_ALIGNMENT_MARKER;                                   \
	copyptr++; /* leave space for relocation word */                  \
	ALIGN_COPYPTR(ptr);                                               \
	BCOPY(SI_UNTAG_STORED(ptr, char), SI_UNTAG_STORED(newptr, char),  \
	      gclen * sizeof(Object));                                    \
	relocated_position(newptr) = SI_FORWARDING_MARKER; /* unmarked */    \
	copyptr += gclen;                                                 \
    }                                                                     \
}

static inline void
relocate_if_live (ptr, gclen)
     Object ptr;
     int gclen;
{
    RELOCATE_IF_LIVE(ptr, gclen);
}

static void
relocate_live_data ()
{
  SI_Segment *seg;

  SETUP_COPYPTR();
  AREA_OBJECTS(Dynamic_area, RELOCATE_IF_LIVE, FLUSH_NONE);
  FLUSH_COPYPTR();
  
  /* update all segment frontiers */
  for (seg = Dynamic_area.first_segment; seg; seg = seg->next)
      seg->frontier = seg->gc_temp;
  /* update current_segment; go to first_segment, to be space frugal */
  Dynamic_area.current_segment = Dynamic_area.first_segment;
}

/*
 * This is used for non-local transfer of control after gc,
 * if RTL was performing a gc unsafe operation.
 */

extern int SI_gc_unsafe;
extern jmp_buf SI_restart_unsafe;

/*
 * This is the only entry point into the garbage collector proper from
 * the runtime system.
 *
 * It invokes, in proper sequence, each phase of the collection algorithm.
 */
SI_garbage_collect ()
{
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

#if !SI_DYNAMICNESS_LABELED
    /* setup global variables describing area being collected */
    from_bottom = (Object *)Dynamic_area.current_segment->start;
    from_top = (Object *)Dynamic_area.current_segment->limit;
#endif /* !SI_DYNAMICNESS_LABELED */

#if !SI_VISIT_EXACTLY_ONCE
    compute_sneaky_bit();
#endif /* !SI_VISIT_EXACTLY_ONCE */

    mark_from_roots();
    record_relocation_info();
    update_refs();
    relocate_live_data();

    if (Current_area == &Dynamic_area)
      SI_RELOAD_ALLOC_CACHE();

    Gc_inhibit = TRUEP(save) ? T : NIL;
    if(Gc_silence == NIL)gcwarn("done.\n");

    /* If RTL was doing unsafe operations, provide non-local exit. */
    if (SI_gc_unsafe != 0)
	longjmp(SI_restart_unsafe, 1);
}

#endif /* !SI_COPYING_COLLECTOR */
