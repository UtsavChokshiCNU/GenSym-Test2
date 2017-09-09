/*
 * Heap.c - Heap management functions
 *
 * J. O'Toole
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"

extern Object Break_on_signals;
extern Object Kdynamic;
extern Object Kstatic;
extern Object Macroexpand_hook;
extern Object Random_state;
DECLARE_VARIABLE(Read_base);
DECLARE_VARIABLE(Read_default_float_format);
extern Object Read_suppress;
extern Object Readtable;
extern TLS Object SI_Called_function;
extern TLS Object SI_First_value;
extern TLS Object T_temp;
extern TLS Object Temp1;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (int n, char *lstr, ...);
extern Object (*SI_warn_fptr) (int n, char *lstr, ...);
extern void SI_add_external_root (Object *p);
extern Object get_next_node (enum SI_type nodetype);
extern Object SI_alloc (SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern void g2ext_heap_command_line(int argc, char *argv[]);

#else

extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();
extern void SI_add_external_root ();
extern Object get_next_node ();
extern Object SI_alloc ();
extern void g2ext_heap_command_line();

#endif

#include "gc.h"

/*
 * signal heap configuration by defining SI_config_xxx symbols
 */
#if SI_CONSES_HAVE_HEADERS
CONFIG_PROVIDES(SI_config_conses_have_headers)
#else
CONFIG_PROVIDES(SI_config_not_conses_have_headers)
#endif

#if SI_NIL_IS_ZERO
CONFIG_PROVIDES(SI_config_nil_is_zero)
#else
CONFIG_PROVIDES(SI_config_not_nil_is_zero)
#endif

#if SI_TAG_WIDTH == 1L
CONFIG_PROVIDES(SI_config_1_tag_width)
#else
#if SI_TAG_WIDTH == 2
CONFIG_PROVIDES(SI_config_2_tag_width)
#else
#if SI_TAG_WIDTH == 3
CONFIG_PROVIDES(SI_config_3_tag_width)
#endif
#endif
#endif

#if SI_VISIT_EXACTLY_ONCE
CONFIG_PROVIDES(SI_config_exactly_once)
#else
CONFIG_PROVIDES(SI_config_not_exactly_once)
#endif

#if RTL_BIG_ENDIAN
CONFIG_PROVIDES(SI_config_big_endian)
#else
CONFIG_PROVIDES(SI_config_not_big_endian)
#endif

#if SI_SEGMENTED_DYNAMIC_AREA
CONFIG_PROVIDES(SI_config_segmented_dynamic_area)
#else
CONFIG_PROVIDES(SI_config_not_segmented_dynamic_area)
#endif

#if SI_SUPPORT_CLOS
CONFIG_PROVIDES(SI_config_support_clos)
#else
CONFIG_PROVIDES(SI_config_not_support_clos)
#endif

/* CRITICAL_SECTION are used for protection of heap */
#if SI_SUPPORT_THREAD

#if defined(_WIN32)

#include <windows.h>
static CRITICAL_SECTION cs_heap;

#define SI_ENTER_CRITICAL_SECTION() EnterCriticalSection(&cs_heap)
#define SI_LEAVE_CRITICAL_SECTION() LeaveCriticalSection(&cs_heap)
#define SI_INIT_CRITICAL_SECTION() \
    InitializeCriticalSectionAndSpinCount(&cs_heap, 4000)

#else

#include <pthread.h>
#include <signal.h>
static pthread_mutex_t cs_heap;

#define SI_ENTER_CRITICAL_SECTION() \
	if(pthread_mutex_lock(&cs_heap)) { \
		perror("Error while obtaining cs_heap lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#define SI_LEAVE_CRITICAL_SECTION() \
	if(pthread_mutex_unlock(&cs_heap)) { \
		perror("Error while releasing cs_heap lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#define SI_INIT_CRITICAL_SECTION() do { \
		pthread_mutexattr_t attr; \
		if(pthread_mutexattr_init(&attr)) { \
			perror("Error while initializing cs_thread lock attributes"); \
			fflush(stdout); \
			raise(SIGTERM); \
		} \
		if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) { \
			perror("Error while setting recursive type for cs_thread lock"); \
			fflush(stdout); \
			raise(SIGTERM); \
		} \
		if(pthread_mutex_init(&cs_heap, &attr)) { \
			perror("Error while initializing cs_thread lock"); \
			fflush(stdout); \
			raise(SIGTERM); \
		} \
	} while(0)

#endif /* defined(_WIN32) */

#else

#define SI_ENTER_CRITICAL_SECTION()
#define SI_LEAVE_CRITICAL_SECTION()
#define SI_INIT_CRITICAL_SECTION() 

#endif /* SI_SUPPORT_THREAD */

#define MULTIPLIER 2048		/* Formerly ARRAY_K */

#define GC_PERIOD	  /* Debugging feature.  Undefine this for speed. */

#ifdef GC_PERIOD
#define GC_DEBUGGING()  { \
    if (GC_Period > 0 && ++GC_Phase >= GC_Period && !TRUEP(Gc_inhibit)) { \
	GC_Phase = 0; \
	if (Current_area == &Dynamic_area) (*SI_garbage_collect_fptr)(); \
      } \
 }
#else /* !GC_PERIOD */
#define GC_DEBUGGING() /* none */
#endif /* !GC_PERIOD */

/* Random global state */

int SI_gc_count = 0;
Object SI_gc_genobj = FIX(0);
Object Gc_inhibit = SI_UNINITIALIZED_MARKER;
Object Gc_silence = SI_UNINITIALIZED_MARKER;
Object Area_overflow_function = SI_UNINITIALIZED_MARKER;

short Initialization = 1;
Stack_item *Lisp_stack;
TLS Stack_item *Stack;
Root_items *SI_Gc_external_roots = NULL;

/* These are purely for debugging the GC.  If GC_Period is positive then
   a GC is forced every time that many nodes are allocated. */
static int GC_Period = 0;
static int GC_Phase = -32768;

#ifdef DEBUG
static Object watch_node;
#endif

SI_Area Static_area
    = {NULL, NULL, 0,
	   (SI_Size_type)STATIC_SIZE*MULTIPLIER,
	   (SI_Size_type)STATIC_INCREMENT*MULTIPLIER,
	   (SI_Size_type)0};
SI_Area Dynamic_area
    = {NULL, NULL, 0,
	   (SI_Size_type)DYNAMIC_SIZE*MULTIPLIER,
	   (SI_Size_type)DYNAMIC_INCREMENT*MULTIPLIER,
	   (SI_Size_type)0};
#if SI_COPYING_COLLECTOR
SI_Area Dynamic_area_copy
    = {NULL, NULL, 0,
	   (SI_Size_type)DYNAMIC_SIZE*MULTIPLIER,
	   (SI_Size_type)DYNAMIC_INCREMENT*MULTIPLIER,
	   (SI_Size_type)0};
#endif /* SI_COPYING_COLLECTOR */
SI_Area Local_area
    = {NULL, NULL, 0,
	   (SI_Size_type)LOCAL_AREA_SIZE*MULTIPLIER,
	   (SI_Size_type)LOCAL_AREA_INCREMENT*MULTIPLIER,
	   (SI_Size_type)0};

SI_Size_type Emergency_threshold = (SI_Size_type)EMERGENCY_RESERVE*MULTIPLIER;

int SI_lisp_stack_size = LISP_STACK_SIZE;

/* GENSYM-46913 notes: (by Chun Tian (binghe))
 * Current_area should be thread-specific and initialized to &Dynamic_area when
   every new thread is created.
   
 * But SI_cached_frontier and SI_cached_limit shouldn't be declared as thread-specific,
   because it always point to latest available allocation point in current area, ...
   but how we handle SI_FLUSH_ALLOC_CACHE() and SI_RELOAD_ALLOC_CACHE() now, they updates
   these two variables for current area ... maybe they should be area-specific but
   thread-specific, or just should be removed (as a cache).
 */
TLS SI_Area *Current_area = &Static_area;
Object *SI_cached_frontier;
Object *SI_cached_limit;

static Object *get_space();
static Object *gc_and_get_space();
extern SI_Segment *alloc_segment();
extern SI_Size_type area_bytes_in_use(), area_total_size();
extern void (*SI_garbage_collect_fptr)();
extern void SI_no_gc();
long SI_gc_silence_init = FALSE;

/*
 * Initialization
 */

static void
init_area (ar)
SI_Area *ar;
{
    SI_Size_type size;
    SI_Segment *seg;

    /* include emergency reserve in initial allocation amount */
    size = ar->notify_threshold;

    if ((ar == &Dynamic_area)
#if SI_COPYING_COLLECTOR
	|| (ar == &Dynamic_area_copy)
#endif
	) {
#if SI_SEGMENTED_DYNAMIC_AREA
	size += ar->increment;
#else
	size += ar->target_size;
#endif /* SI_SEGMENTED_DYNAMIC_AREA */
    } else {
	size += ar->increment;
    }

    if (!(seg = alloc_segment(ar, size))) {
	fprintf(stdout, "Can't allocate %ld bytes for heap.\n",
		ar->target_size);
	exit(-1);
    } else {
	/* withhold emergency reserve from this first segment */
	seg->limit = (void *)((char *)seg->end - ar->notify_threshold);
    }
}

/* Gensym: We don't need no stinking extra argument line parsing.  Instead of
 * running their code, we will define our own version of heap_command_line which
 * usurps their call to this function.  -jra & jh 9/24/93
 */

void heap_command_line(argc, argv)
    int argc;
    char *argv[];
{
  g2ext_heap_command_line(argc, argv);
}

/*
void
g2rtl_heap_command_line (argc, argv)
    int argc;
    char **argv;
{
    int i, n;

    /# atoi returns an int, not necessarily a SI_Size_type #/

#   define GETFLAG(name, loc, mult) \
    if (!stricmp(argv[i], name)) {  \
	n = atoi(argv[++i]);	    \
	if (n <= 0)		    \
	    goto LOSSAGE;	    \
	loc = (SI_Size_type)n * mult; \
        argv[i-1] = argv[i] = "";   \
    }
    for (i = 1; i < argc; i++) {
	if (!stricmp(argv[i], "-gs"))
	  SI_gc_silence_init = TRUE;
	if ( (i+1) < argc ) {
	  GETFLAG("-sn",     Static_area.target_size,  MULTIPLIER);
	  GETFLAG("-si",     Static_area.increment,    MULTIPLIER);
	  GETFLAG("-dn",     Dynamic_area.target_size, MULTIPLIER);
	  GETFLAG("-di",     Dynamic_area.increment,   MULTIPLIER);
	  GETFLAG("-ln",     Local_area.target_size,   MULTIPLIER);
	  GETFLAG("-li",     Local_area.increment,     MULTIPLIER);
	  GETFLAG("-em",     Emergency_threshold,      MULTIPLIER);
	  GETFLAG("-period", GC_Period,		       1);
      }
    }
#if SI_COPYING_COLLECTOR
    Dynamic_area_copy = Dynamic_area;
#endif /# SI_COPYING_COLLECTOR *#
    return;

 LOSSAGE:
    fprintf(stderr, "Invalid argument: %s %s\n", argv[i-1], argv[i]);
    (void)exit(1);
#   undef GETFLAG
}
*/

long SI_in_gsi_p = FALSE;

void gsi_initialize_region_increments()
{
  SI_in_gsi_p = TRUE;
  /* SI_gc_silence_init = TRUE; */
  /* Emergency_threshold = 0; */
  Static_area.target_size = 150000;
  Dynamic_area.target_size = 150000;
  /* Later in the initialization process (adjust_area_target_sizes, in load_INIT),
   * these increments are reduced to 16 * 1024 */
  Static_area.increment = Static_area.target_size;
  Dynamic_area.increment = Dynamic_area.target_size;
  Local_area.increment = 16 * 1024;
  SI_lisp_stack_size = 2;
}

/* (void *) halloc(number_of_items, size_of_an_item)
   long number_of_items;
   int size_of_an_item;  [?]
   size_of_an_item must be less than 65536. */

FORWARD_STATIC void init_stack_vector_header();
FORWARD_STATIC void protect_standard_specials();

/*
 * Gensym addition (jh, 9/23/93).  We need a way to size the static area before
 * userinit() is called, since we allocate many more symbols than the default.
 * (Symbols are allocated `way before the usual memory setup machinery can
 * work.)  Furthermore, we allocate a different number of symbols in different
 * products, so we can't simply adjust the default in config.h.  Finally, there
 * is no easy way to exploit heap_command_line() for our purposes.  Hence we
 * define the function adjust_static_area_target_size(), which should be called
 * before any symbols are allocated, i.e., first thing in the top-level function
 * for the first file in the loading sequence of all our products, namely LOAD. 
 *
 * jh, 10/6/93.  Changed adjust_static_area_target_size() to
 * adjust_area_target_sizes() because we need to change both static and dynamic
 * areas at load time for images translated by the new Chestnut rev
 *
 * jh, 4/29/94.  Added local word_size_factor to adjust_area_target_sizes().
 * This is initialized differently depending on the word size of the platform
 * running the code.  Currently, all platforms except the AlphaOSF have 32-bit
 * words.  The AlphaOSF has a 64-bit word.  The preprocessor token __osf__ was
 * obtained from cc_get_platform_code() in /bt/<spin>/ext/c/cprim.c, which is
 * the canonical place for getting the platform type.  I made sure that this
 * token was supplied to the run time library compile -- this particular token
 * is "hardwired" into the AlphaOSF preprocessor rather than supplied by Gensym
 * by a -D directive in the cc command line.
 */
int g2rtl_current_system_is_g2 = FALSE;

Object
adjust_area_target_sizes(static_target_in_kbytes, dynamic_target_in_kbytes, system_name)
  Object static_target_in_kbytes, dynamic_target_in_kbytes;
  char *system_name;
{
#    ifdef Platform_64bit
 long     word_size_factor = 2;
#    else
 long     word_size_factor = 1;
#    endif

 Static_area.target_size 
   = IFIX(static_target_in_kbytes) * MULTIPLIER * word_size_factor;
 Dynamic_area.target_size 
   = IFIX(dynamic_target_in_kbytes) * MULTIPLIER * word_size_factor;
 if (SI_in_gsi_p) {
   Static_area.increment = 16 * 1024;
   Dynamic_area.increment = 16 * 1024;
 }
 g2rtl_current_system_is_g2 = (0 == strcmp("AB",system_name));
 return FIX(0);
}

#ifdef USE_BITMAP_FOR_CONS_TRACING
extern void *g2ext_cons_checking_region_start;
extern int *consing_bitmap;
#define CONS_CHECKING_REGION_SIZE (256*1024*1024)
#define CONS_CHECKING_BITMAP_SIZE (CONS_CHECKING_REGION_SIZE>>8)
#endif

void init_heaps ()
{
#ifdef HUGE_MSDOS
    Lisp_stack = (Stack_item *) halloc((SI_Size_type) SI_lisp_stack_size,
				       MULTIPLIER * sizeof(Stack_item));
#else  /* not HUGE_MSDOS */
    Lisp_stack = (Stack_item *) malloc((SI_Size_type) SI_lisp_stack_size*MULTIPLIER
				       * sizeof(Stack_item));
#endif /* not HUGE_MSDOS */
    if (!Lisp_stack) {
	fprintf(stdout, "init_heaps: not enough memory for Lisp_stack\n");
	(void)exit(1);
    }
    Stack = Lisp_stack;
#ifdef USE_BITMAP_FOR_CONS_TRACING
    g2ext_cons_checking_region_start = (void *)((long)Lisp_stack & ~15L);
    consing_bitmap = (int *)calloc(CONS_CHECKING_BITMAP_SIZE,sizeof(int));
#endif
    init_stack_vector_header();
    protect_standard_specials();

    /* setup notification thresholds */
    Dynamic_area.notify_threshold = Emergency_threshold;
#if SI_COPYING_COLLECTOR
    Dynamic_area_copy.notify_threshold = Emergency_threshold;
#endif /* SI_COPYING_COLLECTOR */

    init_area(&Static_area);
    SET_CURRENT_AREA(Static_area);
    init_area(&Dynamic_area);
#if SI_COPYING_COLLECTOR
    /* avoid allocating the second semispace if GC is not intended */
    if(SI_garbage_collect_fptr !=  SI_no_gc)
	init_area(&Dynamic_area_copy);
#endif /* SI_COPYING_COLLECTOR */
    init_area(&Local_area);
    SI_INIT_CRITICAL_SECTION();
}

void SI_INIT_dynamic_heaps ()
{
    SET_CURRENT_AREA(Dynamic_area);
    if (Area_overflow_function == SI_UNINITIALIZED_MARKER)
	Area_overflow_function = NIL;
    GC_Phase = 0;
}

static void protect_standard_specials ()
{
    /* extern Object Arglist_stack; */
    PROTECT_GLOBAL_2(Temp1,Macroexpand_hook);
    PROTECT_GLOBAL_2(T_temp,Random_state);
    PROTECT_GLOBAL_3(Read_base,Read_suppress,Readtable);
    PROTECT_GLOBAL_2(Read_default_float_format,Break_on_signals);
#if SI_SUPPORT_SF
    PROTECT_GLOBAL_2(SI_Called_function, SI_First_value);
#endif
    /* PROTECT_GLOBAL_2(Eval_situation, Arglist_stack); */
}

/*
 * Procedure for adding an external gc root.
 */
void
SI_add_external_root (p)
     Object *p;
{

  /* if the condition in the following line is false, there is no GC */
#if !SI_COPYING_COLLECTOR || !SI_SEGMENTED_DYNAMIC_AREA || (SI_VISIT_EXACTLY_ONCE && SI_CONSES_HAVE_HEADERS)

#if SI_VISIT_EXACTLY_ONCE

    /* Make sure there is at least one block */
    if (SI_Gc_external_roots == NULL) {
	/* allocate */
	SI_Gc_external_roots = (Root_items *)malloc(sizeof(Root_items));
	if (SI_Gc_external_roots == NULL) {
	    error(1,"SI_add_external_root: can't malloc space"); /* fail */
	    return;
	}
	SI_Gc_external_roots->next = 0;
	SI_Gc_external_roots->count = 0;
    }

    { register Root_items *block;
      
      /* Locate block which should contain the new root */
      for (block = SI_Gc_external_roots; block->next; block = block->next)
	  if (block->next->roots[0] > p)
	      break;
      if ((block->next != NULL)
	  && (p > block->roots[block->count - 1]) /* p is in gap */
	  && (block->count > block->next->count)) /* more space in next */
	  block = block->next; /* use next block */

      /* this root belongs in this block */
      if (block->count == GCRLIM) {  /* this block is full, must split */
	  register Root_items *temp;
	  register int i;

	  /* strategy: always split in half */
	  temp = (Root_items *)malloc(sizeof(Root_items));
	  if (temp == NULL) {
	      error(1,"SI_add_external_root: can't malloc space"); /* fail */
	      return;
	  }

	  /* link into chain */
	  temp->next = block->next;
	  block->next = temp;

	  /* copy second half of block into temp */
	  for (i = GCRLIM/2; i < GCRLIM; i++)
	      temp->roots[i - GCRLIM/2] = block->roots[i];

	  /* adjust counts in temp and block */
	  block->count = GCRLIM/2;
	  temp->count = GCRLIM - GCRLIM/2;

	  /* pick which block to insert new root */
	  if (p >= temp->roots[0])
	      block = temp;
      }

      /* put new root in this block */
      {
	  register int i, pos;

	  /* locate position within block */
	  for (pos = block->count - 1; pos >= 0; pos--)
	      if (p >= block->roots[pos])
		  break;
	  if ((pos < 0) || (p > block->roots[pos])) {
	      pos++;
	      /* new root is not a duplicate, so insert here */
	      for (i = block->count - 1; i >= pos; i--)
		  /* shift up other larger roots */
		  block->roots[i+1] = block->roots[i];

	      block->roots[pos] = p; /* add new root */
	      block->count++;
	  }
      }
  }

#else /* !SI_VISIT_EXACTLY_ONCE */

  /* Make sure we have space for one more external root. */
  if ((SI_Gc_external_roots == NULL) || (SI_Gc_external_roots->count == GCRLIM)) {
    Root_items *temp;

    temp = (Root_items *)malloc(sizeof(Root_items)); /* allocate */
    if (temp == NULL) {
      error(1,"SI_add_external_root: out of space"); /* fail */
      return;
    }
    temp->next = SI_Gc_external_roots;  /* link at front */
    SI_Gc_external_roots = temp;
    SI_Gc_external_roots->count = 0;  /* initialize counter */
  }

#if SI_VISIT_EXACTLY_ONCE
  /***** Yes, this code is not in use, because the above code
   ***** for duplicate elimination is faster.
   *****/
  /* Eliminate possible duplicate protection of globals. */
  { register int i;
    register Root_items *temp;

    for (temp = SI_Gc_external_roots; temp; temp = temp->next)
      for (i = temp->count; i > 0;)
	if (temp->roots[--i] == p)
	  return; /* already protected, don't protect again */
  }
#endif /* SI_VISIT_EXACTLY_ONCE */

  /* Add this external root to protected list. */
  SI_Gc_external_roots->roots[SI_Gc_external_roots->count++] = p;

#endif /* !SI_VISIT_EXACTLY_ONCE */

#endif

  return;
}

/*
 * Basic method for getting space.
 */
#ifdef DEBUG
#define watch_debug() {if (new == watch_node) \
			 note_event("Allocating watch_node");}
#else /* not DEBUG */
#define watch_debug() {/* none */;}
#endif

#if SI_COPYING_COLLECTOR
#define ALLOC_RELOCATION_WORD(n,s)  /* no relocation word needed */
#define INIT_RELOCATION_WORD(o)  /* no relocation word needed */
#else
#define ALLOC_RELOCATION_WORD(n,s)  \
  { if (n < s->limit) { \
        *n = SI_ALIGNMENT_MARKER; \
        n++; \
    } \
  }
#if SI_DYNAMICNESS_LABELED
#define INIT_RELOCATION_WORD(o) \
   relocated_position(o) = (Current_area == &Dynamic_area) ? \
                           SI_FORWARDING_MARKER : SI_NONRELOCATABLE_MARKER;
#else
#define INIT_RELOCATION_WORD(o) \
   relocated_position(o) = SI_FORWARDING_MARKER;
#endif /* SI_DYNAMICNESS_LABELED */
#endif /* SI_COPYING_COLLECTOR */

#define get_some_space(new, size, alignp)       \
{ \
SI_Area *area; \
SI_Segment *seg; \
void *new_frontier; \
 \
 SI_ENTER_CRITICAL_SECTION(); \
 SI_FLUSH_ALLOC_CACHE(); \
 RETRY: \
    area = Current_area; \
    seg = area->current_segment; \
    new = (Object *)seg->frontier; \
    ALLOC_RELOCATION_WORD(new, seg); \
    if (alignp && not_aligned(new) && (new < (Object *)seg->limit)) { \
      *new = SI_ALIGNMENT_MARKER; \
      new++; \
    } \
    new_frontier = (void *)((char *)new + size); \
    if (new_frontier >= (void*)seg->limit) { \
	new = get_space(area, size, alignp); \
	if (new == NULL) goto RETRY; \
    } \
    else \
	seg->frontier = new_frontier; \
    INIT_RELOCATION_WORD(new); \
    SI_RELOAD_ALLOC_CACHE(); \
    watch_debug(); \
 SI_LEAVE_CRITICAL_SECTION(); \
}


/*
 * Allocators:
 *   SI_cons -- cons cells, initialized by caller
 *   SI_alloc_primitive_vector -- primitive vector with length encodings
 *   SI_alloc -- most objects
 *   SI_copy_object -- for copying results of SI_alloc only
 */

struct node {SI_Header h; Object x, y; };

#define SI_NODE_SIZE		sizeof(struct node)

Object get_next_node (nodetype)  /* BUG BUG this should be obsolete */
    enum SI_type nodetype;
{
  Object newnode;

    GC_DEBUGGING();

  newnode = SI_ALLOC(struct node, nodetype, SI_INSTANCE_TAG, SI_UGLY);

  M_CAR(newnode) = SI_UNINITIALIZED_MARKER; /* Paranoia */
  M_CDR(newnode) = SI_UNINITIALIZED_MARKER; /* Paranoia */

  return newnode;
}

/*
 * jh, 4/21/94.  Folded warn_gensym_area_violation() back into SI_cons() and
 * SI_alloc(), with a more informative message.
 */
void warn_gensym_area_violation(str)
     char * str;
{
  char message[200];
  extern long g2ext_write_string_to_console();
  extern void g2ext_print_backtrace();

  sprintf(message,"%s\nPlease call Gensym customer support.\n\n",str);
  g2ext_write_string_to_console(message);
  g2ext_print_backtrace();
}

#ifdef DEBUG
static int note_event(); /* get_some_space */
#endif

extern Object
SI_cons ()
{
    register Object *new;
    register SI_Size_type gcsize = align_size(sizeof(SI_Cons));
    Object result;

    GC_DEBUGGING();

    /* Gensym modification */
    if (Current_area == &Local_area)
      warn_gensym_area_violation("Memory inconsistency (type 1) detected.");

    get_some_space(new, gcsize * sizeof(Object), 0);

    /* init possible extra alignment word */
    new[gcsize-1] = SI_UNINITIALIZED_MARKER;

    result = SI_SET_TAG(new, SI_CONS_TAG);

#if SI_CONSES_HAVE_HEADERS
    SI_INIT_HEADER(result, CONS_TYPE, gcsize, SI_NORMAL, SI_GC_UNALIGNED);
#endif

    return(result);
}

long notify_type_2_error = 1; /* Gensym modification */

/*ARGSUSED*/
extern Object
SI_alloc (size, align, type, tag, gcls)
     SI_Size_type size;       /* size in bytes, including header word */
     long align;
     enum SI_type type;
     enum SI_tag tag;
     enum SI_gcls gcls;
{
    register SI_Size_type gcsize = align_size(size); /* shouldn't be needed */
    register Object *new;
    Object result = NULL;

    GC_DEBUGGING();

    /* Gensym modification */
    if ((Current_area == &Local_area) &&
	((type != DOUBLE_TYPE) && (type != BIGNUM_TYPE) && (type != LONG64_TYPE)) &&
        notify_type_2_error)
      warn_gensym_area_violation("Memory inconsistency (type 2) detected.");

    align = (align > sizeof(Object));  /* convert to flag */

    get_some_space(new, gcsize * sizeof(Object), align);

    /* init possible extra alignment word */
    new[gcsize-1] = SI_UNINITIALIZED_MARKER;

    result = SI_SET_TAG(new, tag);

    SI_INIT_HEADER(result, type, gcsize, gcls,
		   align ? SI_GC_ALIGNED : SI_GC_UNALIGNED);

    return result;
}

/*
 * jh, 4/22/94.  Added check for improper allocation inside a temporary area to
 * SI_alloc_primitive_vector().  The only allocation allowed is bignums,
 * signified by an etype (element type tag) of A_BYTE_32 passed by
 * SI_allocate_bignum().  The problem is, other data types use A_BYTE_32, so we
 * clone SI_alloc_primitive_vector() into SI_alloc_bignum_vector().  For further
 * details, see comment above the latter function, below.
 */
extern Object 
SI_alloc_primitive_vector (numelems, etype)
    SI_Dimension numelems;
    enum SI_etype etype;
{
    Object result = NULL;
    register SI_Size_type size_in_bytes = calc_vector_size(etype, numelems);
    register SI_Size_type gcsize = align_size(size_in_bytes);
    int align = (etype == A_DOUBLE_FLOAT || etype == A_BYTE_64 || etype == A_UNSIGNED_BYTE_64);
    register Object *new;

    GC_DEBUGGING();

    /* Gensym modification */
    if (Current_area == &Local_area)
      warn_gensym_area_violation("Memory inconsistency (type 3) detected.");

    get_some_space(new, gcsize * sizeof(Object), align);

    result = SI_SET_TAG(new, SI_ARRAY_TAG);

    /* init possible extra alignment word */
    new[gcsize-1] = SI_UNINITIALIZED_MARKER;

    /** SI_INIT_PRIMITIVE_VECTOR(new, numelems, etype); ***/
    SI_INIT_HEADER(result, SI_PRIMITIVE_VECTOR_TYPE, gcsize, etype,
       align ? SI_GC_ALIGNED : SI_GC_UNALIGNED);
    SI_INIT_PRIMITIVE_VECTOR(result, etype);
    SI_SET_PRIMITIVE_VECTOR_LENGTH(result, numelems);

    if (etype == A_STRING_CHAR)
	SI_ISCHAR(result, numelems) = '\0';

    return result;
}

/* SI_malloc_primitive_vector is like SI_alloc_primitive_vector, except
 * that it explicitly mallocs the space, padding as needed for alignment,
 * and recording the amount of padding in the byte immediately before
 * the object (the last byte of the padding), so that it can be
 * freed with SI_free_primitive_vector.
 */

extern Object 
SI_malloc_primitive_vector (numelems, etype)
    SI_Dimension numelems;
    enum SI_etype etype;
{
    Object arr = NULL;
    register SI_Size_type size_in_bytes = calc_vector_size(etype, numelems);
    register SI_Size_type gcsize = align_size(size_in_bytes);
    /*  array has to be offset from malloc'ed chunk to guarantee alignment.
     *  We have to be able to recover malloc'ed chunk from the array,
     *  so we store the amount of offset immediately before the array.
     *  we store it as a single byte to minimize padding overhead.
     */
    char offset;
    char *new;
    register Object *aligned_new;

    
    /* for alignment; probably unnecessary, but here in slavish imitation of
     * SI_alloc_primitive_vector to be safe
     */
    size_in_bytes = (size_in_bytes + 1) & (~1);

    new = malloc(size_in_bytes + 4);
    /*
    fprintf(stderr, "SI_malloc_primitive_vector called on argument %ld: malloc returned %lx\n", (long)numelems, (long)new);
    */
    offset = (char)(4 - ((long)new % 4));
    new[offset - 1] = offset;
    aligned_new = (Object *)(new + offset);

    arr = SI_SET_TAG(aligned_new, SI_ARRAY_TAG);

    SI_INIT_HEADER(arr, SI_PRIMITIVE_VECTOR_TYPE,
		   gcsize,
		   etype,
		   SI_GC_UNALIGNED);

    SI_INIT_PRIMITIVE_VECTOR(arr, etype);
    SI_SET_PRIMITIVE_VECTOR_LENGTH(arr, numelems);
    if (etype == A_STRING_CHAR)
	SI_ISCHAR(arr, numelems) = '\0';
    return(arr);
}

extern void free_malloced_array_internal(arr)
    Object arr;
{
  char *buffer = (char *)arr;
  char offset = *(buffer - 1);
  /*
  fprintf(stderr, "free_malloced_array called on %x\n", buffer);
  */
  if ((offset > 4) || (offset <= 0)) {
    fprintf(stderr, "bad offset %i in free_malloced_array\n", (int)offset);
  }
  buffer -= offset;
  /*
  fprintf(stderr, "about to free malloced_array %x\n", buffer);
  */
  free(buffer); /* should check return value here, or possibly return it to lisp */
}

/*
 * jh, 4/22/94.  Note that the function SI_alloc_bignum_vector() below is
 * identical to the function SI_alloc_primitive_vector() immediately above,
 * except that it omits the check for (Current_area == &Local_area).  We do this
 * so we can check for improper temporary area allocation for all data types
 * other than bignum, without risky, far-reaching edits to every runtime library
 * function that calls SI_alloc_primitive_vector().  Such edits would be a pain
 * to incorporate into the next rtl rev we take, too.
 */
/* Gensym addition */
extern Object 
SI_alloc_bignum_vector (numelems, etype)
    SI_Dimension numelems;
    enum SI_etype etype;
{
    Object result = NULL;
    register SI_Size_type size_in_bytes = calc_vector_size(etype, numelems);
    register SI_Size_type gcsize = align_size(size_in_bytes);
    long align = (etype == A_DOUBLE_FLOAT);
    register Object *new;

    GC_DEBUGGING();

    get_some_space(new, gcsize * sizeof(Object), align);

    result = SI_SET_TAG(new, SI_ARRAY_TAG);

    /* init possible extra alignment word */
    new[gcsize-1] = SI_UNINITIALIZED_MARKER;

    /** SI_INIT_PRIMITIVE_VECTOR(new, numelems, etype); ***/
    SI_INIT_HEADER(result, SI_PRIMITIVE_VECTOR_TYPE, gcsize, etype,
       align ? SI_GC_ALIGNED : SI_GC_UNALIGNED);
    SI_INIT_PRIMITIVE_VECTOR(result, etype);
    SI_SET_PRIMITIVE_VECTOR_LENGTH(result, numelems);

    if (etype == A_STRING_CHAR)
	SI_ISCHAR(result, numelems) = '\0';

    return result;
}

/* SI_Stack_vector_header is used by SI_INIT_OBJECT_VECTOR_HEADER() to
 * initialize the header portion of a stack allocated simple-vector by using
 * structure assignment.  The main point of this is to put the code that knows
 * about the detailed format of the header textually near other code which has
 * similar knowledge, to reduce maintenance costs.  (The performance difference
 * between using structure assignment from a global compared to computing the
 * constant header words and directly bashing them in is negligable).
 * Unfortunately, we've still got some abstraction violations here.  However,
 * they are (we hope) less likely to be overlooked now if any changes need to
 * be made.
 *
 * void init_stack_vector_header()
 *   This function is called during the startup to initialize the header
 *   structure.  We could instead use SI_STATIC_HEADER_FOR_PRIMITIVE_VECTOR()
 *   except that macro isn't permitted when SI_OBJECT_INITIALIZERS_WORK is
 *   false.  Rather than conditionalizing on that flag, we just have a single
 *   mechanism here.
 */

SI_Primitive_vector_constant SI_Stack_vector_header;

static void init_stack_vector_header()
{
#if SI_STATIC_RELOCATION_WORDS
  SI_Stack_vector_header.relocation_word = SI_NONRELOCATABLE_MARKER;
#endif

  /* BUG: This needs to be maintained in parallel with SI_INIT_HEADER(). */
  SI_Stack_vector_header.h.tag = (unsigned)SI_HEADER_TAG;
  SI_Stack_vector_header.h.length_status = (unsigned)(A_T);
  SI_Stack_vector_header.h.type = (unsigned)SI_PRIMITIVE_VECTOR_TYPE;
  SI_Stack_vector_header.h.gcaligned = (unsigned)SI_GC_UNALIGNED;
  SI_Stack_vector_header.h.gcrelocatable = (unsigned)SI_GC_NONRELOCATABLE;
  SI_Stack_vector_header.h.gclength = (unsigned)0; /* not used! */
  SI_Stack_vector_header.h.stuff = 0;

  /* BUG: This needs to be maintained in parallel with
   * SI_INIT_PRIMITIVE_VECTOR(). */
  SI_Stack_vector_header.h.stuff = (int)(A_T);

  /* BUG: This needs to be maintained in parallel with
   * SI_SET_PRIMITIVE_VECTOR_LENGTH(). */
  SI_Stack_vector_header.length = ZERO;
}

/*
 * This clever procedure shortens primitive vectors.
 * If the copying collector is in use, it is easy.
 * If the mark+sweep collector is in use, then the ugly gap
 * left as a result of shortening the vector must be spackled.
 * The spackling technique is tricky, and involves either making
 * the gap into an alignment word for the following object, or
 * making it into a new boring object.
 */
extern void
SI_shorten_primitive_vector (pv, len)
    Object pv;
    long len;
{
    if (SI_STORED_OBJECT_P(pv) && SI_VECTOR_PRIMITIVE_P(pv)) {
	if (SI_PRIMITIVE_VECTOR_LENGTH(pv) < len) {
	    error(1,"SI_shorten_primitive_vector: can't lengthen vectors");
	} else {

#if SI_COPYING_COLLECTOR

	    /* first, shorten the vector */
	    SI_SET_PRIMITIVE_VECTOR_LENGTH(pv, len);
	    /* second, ignore gap because copying gc never examines it */

#else /* !SI_COPYING_COLLECTOR */

	    int oldlen = SI_PRIMITIVE_VECTOR_LENGTH(pv);
	    enum SI_etype etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);
	    SI_Size_type oldsize_in_bytes = calc_vector_size(etype, oldlen);
	    SI_Size_type newsize_in_bytes = calc_vector_size(etype, len);
	    SI_Size_type oldgcsize = align_size(oldsize_in_bytes);
	    SI_Size_type newgcsize = align_size(newsize_in_bytes);
	    int gapsize = (oldgcsize - newgcsize);
	    Object *gapaddr = &(SI_UNTAG_STORED(pv, Object)[newgcsize]);

	    /* first, shorten the vector */
	    SI_SET_PRIMITIVE_VECTOR_LENGTH(pv, len);

	    /* second, make gap safe for gc scanning -- complicated */
	    
	    /* if there is no gap, we are done */
	    if (gapsize == 0)
		return;

#if !EVERYTHING_ALIGNED

	    /* possible alignment word */

/* if every object is aligned, alignment words are not allowed,
   but in that case we assume the primitive vector must shrink
   by at least two words */
/* so if the gapsize is 1, we use an alignment word */

	    if (gapsize == 1) {
		gapaddr[0] = SI_ALIGNMENT_MARKER;
		return;
	    }   

#endif /* !EVERYTHING_ALIGNED */

#define SI_INIT_BORING_HEADER(where, gclen)                     \
	    SI_INIT_HEADER(SI_SET_TAG(&(where), SI_NUMBER_TAG), \
			   COMPLEX_TYPE, /* ugh! */             \
			   gclen,                               \
			   SI_BORING,                           \
			   SI_GC_UNALIGNED)

	    /* plenty of space, make boring object */
	    if (gapsize > 1) {
		gapaddr[0] = SI_FORWARDING_MARKER;
		SI_INIT_BORING_HEADER(gapaddr[1], (gapsize-1));
                SI_STORED_OBJECT_FIELD(&gapaddr[1], SI_Header, gcrelocatable) =
		  SI_STORED_OBJECT_FIELD(pv, SI_Header, gcrelocatable);
	    } else {
		/* given that everything is aligned, the gc length of
		   the original vector should never shrink by only one word */
		error(1,"SI_shorten_primitive_vector: BUG -- can't happen");
	    }

#endif /* !SI_COPYING_COLLECTOR */

	}
    }
    else {
	error(1,"SI_shorten_primitive_vector: arg not a primitive vector");
    }
}

extern Object
SI_copy_object (p)
    Object p;
{
    /* register */ SI_Header hdr;
    register SI_Size_type gcsize;
    register Object *new;
    register Object result;

    GC_DEBUGGING();

    hdr = object_to_header(p);
    gcsize = easy_gc_length(hdr);

    get_some_space(new, gcsize * sizeof(Object), easy_aligned(hdr));

    BCOPY(SI_UNTAG_STORED(p, char), (char *)new, gcsize * sizeof(Object));

    result = SI_SET_TAG(new, SI_TAG_OF(p));
    SI_INIT_DYNAMICNESS_LABEL(result);

    return result;
}



/* Careful -- this typedef was copied from bignmint.h */
typedef long bignum_digit_type;

/* To do: change representation of bignums to
     typedef struct {
         SI_Header h;
	 Object digit_vector;
	 } ALIGNEDTYPE SI_Bignum;
   Update macros in object.h and runint.h accordingly.
   (Move the SI_UNTAG_BIGNUM macro to runint.h, or flush in favor of
   SI_STORED_OBJECT_FIELD.)
 */


void *SI_get_foreign_space (align, size)
    SI_Long align, size;
{
    char *mem_ptr;

    mem_ptr = malloc(size + align);
    mem_ptr += align;
    mem_ptr = (char *) (((SI_Long)mem_ptr) & ~(align - 1L));
    return ((void *)mem_ptr);
}

/* Structures (for untyped DEFSTRUCT)
 *
 * There are two versions of the constructor, one for v2 and one for v3.
 * The v2 constructor passes all the initial slot values to the constructor in
 * the order in which they are to be placed in the structure.
 * The v3 constructor simply allocates storage, with the caller being
 * responsible for initializing fields.  For GC safety though, all fields get
 * initialized to UNBOUND.
 *
 * In either case, the header returned by SI_find_structure_header() contains
 * information about the structure type.
 */

/* BUG BUG (abstraction violation) */
#define STRUCTURE_SIZE(o) \
    (SI_INSTANCE_FIELD(o,SI_Header,gclength) \
      - (sizeof(SI_Type_for_structure(1)) - sizeof(Object))/sizeof(Object))

extern Object (*SI_find_structure_header_fptr)(/*Object name*/);

/* v3 constructor -- see also MAKE_STRUCTURE(). */
Object SI_make_structure (name, size, align)
  Object name;
  SI_Size_type size;
  long align;
{
    Declare_local_temp;
  Declare_protect(1);
  Object header, res;
  Object *elem;
  SI_Dimension i;

  PROTECT_LOCALS();
  PROTECTI_1(header);

  header = (*SI_find_structure_header_fptr)(name);
  res = SI_alloc(size, align, SI_STRUCTURE_TYPE, SI_INSTANCE_TAG, SI_NORMAL);
  SI_STRUCTURE_HEADER(res) = header;
  SI_INIT_DYNAMICNESS_LABEL(res);
  /* You would think that C would have a fill function for this, but the
   * nearest thing to such appears to be memset, which only does char filling.
   * A static array of UNBOUND markers could be allocated for block copying
   * here, but it's not clear that its really worth the effort.
   */
  elem = &STRUCTURE_ELEMENT(res, 0);
  for (i = STRUCTURE_SIZE(res); i-- > 0; ) *elem++ = UNBOUND;
  UNPROTECT_LOCALS();
  return VALUES_1(res);
}

/* n is the number of slots in the structure.
 * This assumes that the slots are layed out as an array of Object.
 */
#define ALLOC_STRUCT_N(n) \
    SI_alloc((SI_Size_type) \
		(sizeof(SI_Type_for_structure(1))+(n-1)*sizeof(Object)), \
	     SI_ALIGNMENT_FOR(SI_Type_for_structure(1)), \
	     SI_STRUCTURE_TYPE, SI_INSTANCE_TAG, SI_NORMAL)

#if (SI_SUPPORT_MF && !SI_SUPPORT_CLOS)

/* v2 constructor -- see also make_structure().
 * n is total number of other arguments passed in, including type name.
 */ 
Object make_structure varargs_1(int, n)
{
    Declare_local_temp;
  Object	res, header;
  Object	*rest;
  Declare_stack_pointer;

  SAVE_STACK();
  SETUP_REST(n, rest);
  PROTECTI_1(res);
  PROTECTI_1(header);

  header = (*SI_find_structure_header_fptr)(*rest++);
  n--;
  res = ALLOC_STRUCT_N(n);
  SI_STRUCTURE_HEADER(res) = header;
  SI_INIT_DYNAMICNESS_LABEL(res);
  /* Block copy the slot values from the stack. */
  (void)MEMCPY((char *)&STRUCTURE_ELEMENT(res, 0),
	       (char *)rest,
	       n * sizeof(Object));
  RESTORE_STACK();
  return VALUES_1(res);
}
#endif  

Object copy_structure (s)
  Object	s;
{
    Declare_local_temp;
  Declare_protect(1);
  Object	copy;
  SI_Dimension	n;

  PROTECT_LOCALS();
  PROTECT_1(s);

  n = STRUCTURE_SIZE(s);	/* compute number of slots. */
  copy = ALLOC_STRUCT_N(n);	/* allocate space for object. */
  SI_STRUCTURE_HEADER(copy) = SI_STRUCTURE_HEADER(s);
  SI_INIT_DYNAMICNESS_LABEL(copy);
  /* Block copy the slot values. */
  (void)MEMCPY((char *)&STRUCTURE_ELEMENT(copy, 0),
	       (char *)&STRUCTURE_ELEMENT(s, 0),
	       n * sizeof(Object));
  UNPROTECT_LOCALS();
  return VALUES_1(copy);
}

/* bignum_reduce_length */

/* bignum_deallocate */


/*
 * Either switch segments, allocate another segment, or GC, as appropriate.
 */

typedef void (*FUNCTION_RETURNING_VOID)();
#define SI_DIRECT_FUNCALL_0(f) \
    (SI_FUNCTIONP(f) ? \
      (*((FUNCTION_RETURNING_VOID)SI_FUNCTION_ENTRY(f)))() \
      : SI_undefined_function_error(f))

#define SI_EMERGENCY_FUNCALL_0(f) \
      (*((FUNCTION_RETURNING_VOID)SI_FUNCTION_ENTRY(f)))()

static Object *
get_space (area, size, alignp)
    SI_Area *area;
    SI_Size_type size;
    long alignp;
{
    Object *new;
    void *new_frontier;
    SI_Segment *seg;

    /* switch to next segment if possible */
    if ((area->current_segment != NULL)
        && (area->current_segment->next != NULL)) {
      area->current_segment = area->current_segment->next;
      if (area == Current_area)
	SI_RELOAD_ALLOC_CACHE();   /* being careful */
      return((Object *)NULL);
    }

    if (area_total_size(area) >= area->target_size) {
	if (new = gc_and_get_space(area, size, alignp))
	    return new;
	seg = alloc_segment(area, MAX(area->increment,size+2*sizeof(Object)));
	if (seg == NULL)
	    goto LOSING;
    }
    else {
	seg = alloc_segment(area,MAX(area->increment, size+2*sizeof(Object)));
	if (seg == NULL) {
	    if (new = gc_and_get_space(area, size, alignp))
		return new;
	    goto LOSING;
	}
    }
    new = (Object *)seg->frontier;
    ALLOC_RELOCATION_WORD(new, seg);
    if (alignp && not_aligned(new) && (new < (Object *)seg->limit)) {
      *new = SI_ALIGNMENT_MARKER;
      new++;
    }
    new_frontier = (void *)((char *)new + size);
    if (new_frontier > seg->limit)
	error(1, "This shouldn't happen");
    seg->frontier = new_frontier;
    return new;

 LOSING:
    if ((Current_area->notify_threshold == 0)
      || (Area_overflow_function == NIL)) {
	fprintf(stdout, "Error:  memory exhausted\n");
	fflush(stdout);
	(void)exit(1);
    }
    /* Give up entire emergency reserve, notify, and try again. */
    Current_area->notify_threshold = (SI_Size_type)0;
    for (seg = Current_area->first_segment; seg; seg = seg->next) {
	if (seg->limit != seg->end) {
	    seg->limit = seg->end;
	    Current_area->current_segment = seg;
	    SI_RELOAD_ALLOC_CACHE();
	}
    }
    /* if segment usage is changed, must avoid restore_frontier dangers */
    SI_gc_count++;
    /* SI_gc_genobj = FIX(0);    Objects did not move, don't bother. */

    /* provide notification --- this will probably destroy VALUES count */
    if (TRUEP(Area_overflow_function))
	(void)SI_EMERGENCY_FUNCALL_0(Area_overflow_function);
    return NULL;		/* Retry */
}

static Object *
gc_and_get_space (area, size, alignp)
    SI_Area *area;
    SI_Size_type size;
    long alignp;
{
    Object *new;
    void *new_frontier;
    SI_Segment *seg;

    if (!(Current_area == &Dynamic_area) || TRUEP(Gc_inhibit))
	return NULL;
    (*SI_garbage_collect_fptr)();
    for (seg = area->first_segment; seg != NULL; seg = seg->next) {
	new = (Object *)seg->frontier;
	ALLOC_RELOCATION_WORD(new, seg);
        if (alignp && not_aligned(new) && (new < (Object *)seg->limit)) {
          *new = SI_ALIGNMENT_MARKER;
          new++;
        }
	new_frontier = (void *)((char *)new + size);
	if (new_frontier <= seg->limit) {
	    seg->frontier = new_frontier;
	    area->current_segment = seg;
	    if (area == Current_area)
	      SI_RELOAD_ALLOC_CACHE();
	    return new;
	}
    }
    return NULL;
}

static SI_Size_type
space_above_threshold (area)
    SI_Area *area;
{
    SI_Size_type result = 0;

    result = area_total_size(area) - area_bytes_in_use(area);
    if (result > area->notify_threshold)
	result -= area->notify_threshold;
    else
	result = (SI_Size_type)0;

    return result;
}

SI_Size_type
area_total_size (area)
    SI_Area *area;
{
    SI_Size_type result = 0;
    SI_Segment *seg;

    for (seg = area->first_segment; seg; seg = seg->next)
	result += (char *)seg->end - (char *)seg->start;
    return result;
}

SI_Size_type
area_bytes_in_use (area)
    SI_Area *area;
{
    SI_Size_type result = 0;
    SI_Segment *seg;

    if (area == Current_area)
      SI_FLUSH_ALLOC_CACHE();
    for (seg = area->first_segment; seg; seg = seg->next)
	result += (char *)seg->frontier - (char *)seg->start;
    return result;
}

/* Returns nonzero on success */

int alloc_memory_to_target (area)
    SI_Area *area;
{
    SI_Size_type want = area->target_size,
	         have = area_total_size(area);
    SI_Segment *current = area->current_segment;

    if (want <= have)
      return 1;
    if (alloc_segment(area, want - have) == NULL) {
      gcwarn("Unable to obtain more memory.\n");
      return 0;
    }

    /* The old current_segment is still useful, so restore it. */
    if (area == Current_area)
      SI_FLUSH_ALLOC_CACHE();
    area->current_segment = current;
    if (area == Current_area)
      SI_RELOAD_ALLOC_CACHE();
    
    return 1;
}

/*
 * Enlarge an area.
 * Returns segment on success, NULL otherwise.
 */

int simulate_out_of_memory = 0;

/*
 * Gensym modification (jh, 9/28/93).  Brought forward from
 * /bt/ab/runtime/c/heap.c the modification to alloc_segment() that provides a
 * more informative "obtaining more memory" message.  Replaced the "then" clause
 * of the "if TRUEP(Gc_inhibit)" statement below (between "start Gensym
 * replacement" and "end Gensym replacement).
 */

/* static */ SI_Segment *
alloc_segment (area, size)
    SI_Area *area;
    SI_Size_type size;
{
    SI_Segment *current, *new;

#if !(SI_SEGMENTED_DYNAMIC_AREA)
    if ((area == &Dynamic_area

#if SI_COPYING_COLLECTOR
         || area == &Dynamic_area_copy
#endif

        ) && area->first_segment != NULL) {
      gcwarn("garbage collector supports contiguous dynamic heap only\n");
      gcwarn("you should increase dynamic heap size using -dn switch.\n");
      return((SI_Segment *)NULL);
    }
#endif /* !SI_SEGMENTED_DYNAMIC_AREA */

    if (simulate_out_of_memory ||
	!(new = (SI_Segment *)malloc((SI_Size_type)sizeof(*new))) ||
	!(new->start = (void *)malloc(size))
	)
	return NULL;

    new->end = new->limit = (void *)((char *)new->start + size);
    new->frontier = new->start;
    new->gc_temp = new->gc_maptemp = new->start;

    /* Link it into area's list of segments */
    if (current = area->current_segment) {
	new->next  = current->next;
	current->next = new;
    } else
	new->next = NULL;

    if (area->first_segment == NULL) {
      area->first_segment = new;
      area->current_segment = new;
      if (area == Current_area)
	SI_RELOAD_ALLOC_CACHE();    /* cache new current segment frontier */
    } else {
      if (area == Current_area)
	SI_FLUSH_ALLOC_CACHE();     /* update old current segment frontier */
      
      area->current_segment = new;

      if (area == Current_area)
	SI_RELOAD_ALLOC_CACHE();    /* cache new current segment frontier */
    }

#if SI_COPYING_COLLECTOR
  if (area != &Dynamic_area_copy) {
#endif
   {
    SI_Size_type     measured_size;

    if (((measured_size = area_total_size(area)) > 
        area->target_size + area->notify_threshold) &&
	(Gc_silence == NIL)) {
	if (TRUEP(Gc_inhibit)) {
	   /* start Gensym replacement */
	   char     warn_string[100];
	   char    *region_name;
	   extern long g2ext_write_string_to_console();

           if (area == &Static_area)
	     region_name = "region 2";
           else if (area == &Dynamic_area) 
	     region_name = "region 1";
	   else 
	     region_name = "other region";
	   sprintf(warn_string, 
		   "Obtaining more memory (%s at %ld)\n",
		   region_name,
		   measured_size);
	   g2ext_write_string_to_console(warn_string);
	/* end Gensym replacement */
        } else if (Current_area != &Dynamic_area) {
	    gcwarn("Obtaining more memory (non-dynamic allocation)\n");
	} else {
	    gcwarn("Obtaining more memory\n");
	}
    }
   }
#if SI_COPYING_COLLECTOR
  }
  if ((area == &Dynamic_area) && 
      (area->first_segment != new) && 
      (SI_garbage_collect_fptr !=  SI_no_gc)) {
    /* Duplicate allocation in Dynamic_area_copy if this isn't init segment */
    if (alloc_segment(&Dynamic_area_copy, size) == NULL)
	gcwarn("Unable to obtain more memory for semispace, continuing.\n");
  }
#endif
    return(new);
}

extern void
restore_frontier (seg, frontier)
    SI_Segment *seg;
    void *frontier;
{
    SI_Area *a = Current_area;
    SI_Segment *s, *current = a->current_segment;

    /* Consistency check */
    if (seg == current) {
	gcwarn("restore_frontier: probable bug in RESTORE_FRONTIER macro\n");
    } else
	for (s = a->first_segment; s != seg; s = s->next)
	    if (s == NULL) {
		gcwarn("restore_frontier: unrecognized segment\n");
		return;
	    } else if (s == current) {
		gcwarn("restore_frontier: segments out of order\n");
		return;
	    }

    /* have verified that new frontier segment comes before current segment */
    seg->frontier = frontier;  /* restore frontier of new frontier segment */
    for (s = seg->next; s != current; s = s->next) {
	if (s == NULL) {
	    gcwarn("restore_frontier: ran off end of segment list\n");
	    return;
	}
	s->frontier = s->start;/* restore frontiers of intervening segments */
    }
    s->frontier = s->start;     /* restore frontier of old current segment */
    a->current_segment = seg;   /* move back in segment list */
    SI_RELOAD_ALLOC_CACHE();    /* cache new current segment frontier */
}

/*
 * Lisp-callable
 */

extern Object
force_gc ()
{
    Declare_local_temp;
    (*SI_garbage_collect_fptr)();
    return VALUES_1(NIL);
}

extern Object
allow_gc (normal_bytes_needed, array_bytes_needed)
    Object normal_bytes_needed;
    Object array_bytes_needed;
{
    Declare_local_temp;
    SI_Long need, have;
    need = IFIX(normal_bytes_needed) + IFIX(array_bytes_needed);
    have = space_above_threshold(&Dynamic_area);

    if (have < need) {
	(*SI_garbage_collect_fptr)();
	have = space_above_threshold(&Dynamic_area);
        if (have < need) {
	    warn(1,"allow_gc: ~D bytes requested, ~D btyes remaining",
		 FIX(need), FIX(have));
	    return VALUES_1(NIL);
	}
    }
    /* I\'d like this file not to use symbol T at all (D.N.) */
    return VALUES_1(FIX(1));
}

#ifdef DEBUG
/* 
   E.g., in dbx:
     stop in note_event
     set watch_node = 0x1f4468
 */
static int note_event(s) char *s; {
    fprintf(stderr, "Attention - %s\n", s);
    return 0;
}
#endif

/* GC Interface Abstraction Violation; only functions internal to
   the GC should know about these:
*/
extern SI_Area Static_area, Dynamic_area;

SI_Area *SI_area_name_to_area(area_name)
    Object area_name;
{
    SI_Area *area;

    if (EQ(area_name,Kstatic))
	area = &Static_area;
    else if (EQ(area_name,Kdynamic))
	area = &Dynamic_area;
    /* Add other areas (emergency, local, ...) here */
    else
	area = NULL;
    return area;
}
