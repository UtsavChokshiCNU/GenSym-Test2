/* -*- Mode: C -*-
 *
 * Filename:      g2ptrs.c
 *
 * Gensym module: ext/c
 *
 * File Summmary: routines to map a C pointer or long into a g2pointer
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 *            All Rights Reserved.
 *
 * Ong, Peng Tsin
 *
 * This file contains the routines to map a C pointer or long into a
 * g2pointer (which is an int less than the smallest most-positive-fixnum
 * on all implementations of Lisp used by G2.
 *
 * Assumptions:
 * 1. We're going to run out of memory long before we'll run out of g2pointer
 *    values less than the most-positive-fixnum.  Hence we won't bother
 *    checking if the g2pointer is less than most-positive-fixnum.
 * 2. All g2pointers handed to this facility are legal g2pointers allocated
 *    by this facility.  (If this is not the case, a bombout will occur.)
 *
 * The six functions that are to be used to hook into this facility are:
 *	void	  g2ext_initialize_g2pointers()
 *	Cpointer  g2ext_map_g2pointer_to_cpointer(g2pointer)
 *	G2pointer g2ext_cache_cpointer(cpointer)
 *	G2pointer g2ext_copy_g2pointer(g2pointer)
 *      long      g2ext_cpointer_of_g2pointer_is_null(g2pointer)
 *      long      g2ext_cpointers_of_g2pointers_eq(g2pointer_1, g2pointer2);
 *	void	  g2ext_decache_g2pointer(g2pointer)
 */


/****************************
 * DEFINITIONS OF CONSTANTS *
 ****************************/

#include <stdlib.h>

#define IN_G2POINTERS_MODULE
#include "cprim.h"


#ifdef CHECK_MEMORY
#include <signal.h>
#define MAXIMUM_NUMBER_OF_G2POINTERS_CHECKED 20000L
#endif


/*
 * The constant `SIZE_OF_OVERFLOW_SPACE_SEGMENT' ...
 */

#define SIZE_OF_OVERFLOW_SPACE_SEGMENT	512L


#define MAP_G2POINTER(G2PTR) \
	( \
	(G2PTR < MAXIMUM_NUMBER_OF_FAST_G2PTRS) \
	? g2ext_g2pointer_to_cpointer_array[G2PTR] \
	: g2ext_get_cptr_from_overflow_space((G2pointer) G2PTR) \
	)


/*
 * Locking macros
 */

#ifdef MTG2
#include <pthread.h>
#include <signal.h>
#define OBTAIN_CPOINTER_WRITE_LOCK() \
	if(pthread_rwlock_wrlock(&cpointer_lock)) { \
		perror("Error while obtaining Cpointer write lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#define OBTAIN_CPOINTER_READ_LOCK() \
	if(pthread_rwlock_rdlock(&cpointer_lock)) { \
		perror("Error while obtaining Cpointer read lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#define RELEASE_CPOINTER_LOCK() \
	if(pthread_rwlock_unlock(&cpointer_lock)) { \
		perror("Error while releasing Cpointer lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#else
#define OBTAIN_CPOINTER_WRITE_LOCK() {}
#define OBTAIN_CPOINTER_READ_LOCK() {}
#define RELEASE_CPOINTER_LOCK() {}
#endif



/************************
 * DEFINITIONS OF TYPES *
 ************************/


/*
 * free_g2pointer_list_node
 */

struct free_g2pointer_list_node_struct
{
  struct free_g2pointer_list_node_struct	*next_node;
  G2pointer					g2pointer;
  Cpointer					*cpointer_ptr;
} ;

typedef struct free_g2pointer_list_node_struct	free_g2pointer_list_node;
typedef free_g2pointer_list_node		*free_g2pointer_list_node_ptr;







/*
 * There are two ways considerred for handling overflows of the main
 * g2ext_g2pointer_to_cpointer_array[]:  with a list of small arrays, or with
 * a binary tree.
 */





/*
 * overflow_array_node
 */

typedef Cpointer	overflow_array_node[SIZE_OF_OVERFLOW_SPACE_SEGMENT];

typedef Cpointer *Cpointer_ptr;




/*
 * overflow_array_list
 */

struct overflow_array_list_node_struct
{
  struct overflow_array_list_node_struct	*next_node;
  overflow_array_node				overflow_array;
};

typedef struct overflow_array_list_node_struct	overflow_array_list_node;
typedef overflow_array_list_node		*overflow_array_list_node_ptr;





/*
 * binary_tree_node
 */

struct binary_tree_node_struct
{
  Cpointer				cpointer;
  struct binary_tree_node_struct	*left_child;
  struct binary_tree_node_struct	*right_child;
};

typedef struct binary_tree_node_struct	binary_tree_node;
typedef binary_tree_node	*binary_tree_node_ptr;










/**************************
 * GLOBAL DATA STRUCTURES *
 **************************/

/*
 * read-write lock
 * protects g2ext_g2pointer_to_cpointer_array, 
 * largest_possible_g2ptr_so_far, head_of_free_g2pointer_list 
 * and other globals of this facility
 */

#ifdef MTG2
pthread_rwlock_t  cpointer_lock = PTHREAD_RWLOCK_INITIALIZER;
#endif


/*
 * g2ext_g2pointer_to_cpointer_array[]
 */
 Cpointer g2ext_g2pointer_to_cpointer_array[MAXIMUM_NUMBER_OF_FAST_G2PTRS];


/*
 * largest_possible_g2ptr_so_far
 */
static G2pointer largest_possible_g2ptr_so_far;



/*
 * head_of_free_g2pointer_list is a pointer to the head of the
 * free g2pointer list.
 */
static free_g2pointer_list_node_ptr	head_of_free_g2pointer_list;




/*
 * tail_of_free_g2pointer_list is a pointer to the tail of the
 * free g2pointer list.
 */
static free_g2pointer_list_node_ptr	tail_of_free_g2pointer_list;




/*
 * head_reclaim_free_g2ptr_list
 */
static free_g2pointer_list_node_ptr 
  head_reclaim_free_g2ptr_list;



/*
 * g2pointer_to_cpointer_tree_root is a pointer to the root of the binary
 * tree which is used to cache the g2pointers that are overflowed from the 
 * g2ext_g2pointer_to_cpointer_array[].
 */
/* static binary_tree_node_ptr		g2ptr_to_cptr_overflow_space; */


/*
 * overflow_array_list_node_ptr is a pointer ...
 */
static overflow_array_list_node_ptr	g2ptr_to_cptr_overflow_space;

/*
 * tail_of_overflow_space is ...
 */
static overflow_array_list_node_ptr	tail_of_overflow_space;




/******************************
 * THE CHECK_MEMORY FUNCTIONS *
 ******************************/

#ifdef CHECK_MEMORY
static long legal_g2pointer[MAXIMUM_NUMBER_OF_G2POINTERS_CHECKED];
#endif


#ifdef USE_G2_MALLOC_P
void *g2_malloc(long size)
{
  long *return_ptr;

  return_ptr = (long *)malloc(size);
  if (return_ptr)
    {
      return((void *)return_ptr);
    }
  else
    {
      int pid = getpid();

      printf("\nMalloc error in g2_malloc(%ld), interrupting lisp(pid %d)...\n",
	     size, pid);
      fflush(stdout);
      kill(pid, SIGINT);
      printf("\nContinuing in g2_malloc, returning ... \n");
      printf("An error will probably result.\n");
      fflush(stdout);
      return(0);
    }
}
#endif



/***************************************
 * THE INTERNALLY REFERENCED FUNCTIONS *
 ***************************************/

/*
 * METHOD 1 FOR HANDLING OVERFLOW:
 *
 * The function `retrieve_cpointer_from_tree' ...
 * Returns the cpointer corresponding to the g2pointer it is given.
 *
 * The tree looks like:
 *				root
 *				 |
 *				 1  ( = offset_g2pointer )
 *				/ \
 *			      2     3
 *			    /  \   /  \
 *			   4    5 6    7
 *
 * where offset_g2pointer = g2pointer - MAXIMUM_NUMBER_OF_FAST_G2PTRS
 *
 * So the depth of a node with offset_g2pointer n is floor(log2(n)).
 */

	/* Traverse tree here */
	
	/* Algorithm:
	 * started_traversing_p = 0;
	 * current_ptr = root_ptr;
	 * bits = g2pointer;
	 * Do m times ( m = length of a g2pointer in bits )
	 * {	if (started_traversing_p)
	 *	{	if (most_significant_bit(bits) == 1)
	 *		{	current_ptr = current_ptr->right_child; }
	 *		else
	 *		{	current_ptr = current_ptr->left_child;  }
	 *	}
	 *	else
	 *	{	started_traversing_p = most_significant_bit(bits);
	 *	}
	 * }
	 * return( current_ptr->cpointer );
	 */


/*
 * METHOD 2 FOR HANDLING OVERFLOW:
 *
 * Allocate an overflow array each time overflow occurs, and
 * maintain all the overflow arrays.
 */




/*
 * The function `g2ext_make_list_of_free_g2ptr_nodes' ...
 */
free_g2pointer_list_node_ptr g2ext_make_list_of_free_g2ptr_nodes
  (G2pointer first_g2pointer_value, long number_of_nodes, Cpointer_ptr start_address_of_array)
{
  G2pointer index;
  G2pointer actual_g2pointer = first_g2pointer_value;
  Cpointer_ptr  cpointer_ptr = start_address_of_array;
  G2pointer limit = number_of_nodes - 1;
  free_g2pointer_list_node_ptr head_of_list;
  head_of_list
    = (free_g2pointer_list_node_ptr)
      G2MALLOC((unsigned)sizeof(free_g2pointer_list_node) * (int)number_of_nodes);

  for (index=0; index<limit; index++)
    {
      head_of_list[index].next_node = &(head_of_list[index + 1]);

      head_of_list[index].g2pointer = actual_g2pointer;
      actual_g2pointer++;
      head_of_list[index].cpointer_ptr = cpointer_ptr;
      cpointer_ptr++;
    }

  head_of_list[limit].next_node = (free_g2pointer_list_node_ptr)NULL;
  head_of_list[limit].g2pointer = actual_g2pointer;
  head_of_list[limit].cpointer_ptr = cpointer_ptr;
  return(head_of_list);
}




/*
 * The function `g2ext_get_cptr_from_overflow_space' ...
 */

Cpointer g2ext_get_cptr_from_overflow_space(G2pointer g2pointer)
{
  G2pointer current_maximum
    = MAXIMUM_NUMBER_OF_FAST_G2PTRS + SIZE_OF_OVERFLOW_SPACE_SEGMENT;
  overflow_array_list_node_ptr 
    current_overflow_array_node_ptr = g2ptr_to_cptr_overflow_space;

  while ( g2pointer >= current_maximum )
    {
      current_overflow_array_node_ptr
	= current_overflow_array_node_ptr->next_node;
      current_maximum += SIZE_OF_OVERFLOW_SPACE_SEGMENT;
    }
  return(current_overflow_array_node_ptr->overflow_array
	 [g2pointer + SIZE_OF_OVERFLOW_SPACE_SEGMENT - current_maximum]);
}





/*
 * The function `g2ext_put_cptr_in_new_overflow_space' ...
 * This function should only be called when head_of_free_g2pointer_list is
 * NULL.
 */
G2pointer  g2ext_put_cptr_in_new_overflow_space(Cpointer cpointer)
{
  G2pointer g2pointer_to_return;

  if (tail_of_overflow_space)
    {
      tail_of_overflow_space->next_node
	= (overflow_array_list_node_ptr)
	  G2MALLOC((unsigned)sizeof(overflow_array_list_node));
      tail_of_overflow_space = tail_of_overflow_space->next_node;
    }
  else
    {
      g2ptr_to_cptr_overflow_space
	= tail_of_overflow_space
	  = (overflow_array_list_node_ptr)
	    G2MALLOC((unsigned)sizeof(overflow_array_list_node));
    }

  tail_of_overflow_space->overflow_array[0] = cpointer;

  g2pointer_to_return = largest_possible_g2ptr_so_far + 1;
  largest_possible_g2ptr_so_far += SIZE_OF_OVERFLOW_SPACE_SEGMENT;

  head_of_free_g2pointer_list
    = g2ext_make_list_of_free_g2ptr_nodes
      ((G2pointer) g2pointer_to_return+1,
       (long) (SIZE_OF_OVERFLOW_SPACE_SEGMENT-1),
       (Cpointer_ptr) &(tail_of_overflow_space->overflow_array[1]));
  tail_of_free_g2pointer_list
    = &(head_of_free_g2pointer_list
	[SIZE_OF_OVERFLOW_SPACE_SEGMENT - 2]);

  return(g2pointer_to_return);
}





free_g2pointer_list_node_ptr g2ext_make_free_g2pointer_list_node()
{
	if (head_reclaim_free_g2ptr_list)
	{
		free_g2pointer_list_node_ptr	new_node_ptr
			= head_reclaim_free_g2ptr_list;
		head_reclaim_free_g2ptr_list
			= new_node_ptr->next_node;
		return(new_node_ptr);
	}
	else
	{
		return(	(free_g2pointer_list_node_ptr)
			G2MALLOC( (unsigned)sizeof(free_g2pointer_list_node) ) );
	}
}



void g2ext_reclaim_free_g2ptr_list_node(free_g2pointer_list_node_ptr reclaim_free_g2ptrlist_node_ptr)
{
	reclaim_free_g2ptrlist_node_ptr->next_node
		= head_reclaim_free_g2ptr_list;

	head_reclaim_free_g2ptr_list
		= reclaim_free_g2ptrlist_node_ptr;
}


/***************************************
 * THE EXTERNALLY REFERENCED FUNCTIONS *
 ***************************************/

/*
 * The function `g2ext_initialize_g2pointers' ...
 * Initializes the free pointer list.
 * Returns non-zero if the initialization failed, and 0 if it was successful.
 *
 * jv, 12/13/02 -- we "always" checked for g2PointersInitialized being set,
 * but never set it.  I'm not sure what should happen if this function is
 * called twice.  I think it's better if the function sticks to the contract
 * it implies by having the variable in the first place, so I'm setting
 * g2PointersInitialized to 1 when this function is run.
 */

static int g2PointersInitialized = 0;

void g2ext_initialize_g2pointers()
{
#ifdef VERBOSE
  printf("In init_ptrs...");
  fflush(stdout);
#endif
  if (g2PointersInitialized == 1) 
	  return;

  g2PointersInitialized = 1;
  g2ptr_to_cptr_overflow_space = NULL;
  tail_of_overflow_space = NULL;

#ifdef CHECK_MEMORY
  {
    int index;
    for (index=0; index < MAXIMUM_NUMBER_OF_G2POINTERS_CHECKED; index++)
      {
	legal_g2pointer[index] = FALSE;
      }
  }
#endif

  head_reclaim_free_g2ptr_list = NULL;

  /* create the free g2pointer list here:  one free pointer
   * for each slot in the g2ext_g2pointer_to_cpointer_array[]
   */

  /* set tail_of_free_g2pointer_list and head_of_free_g2pointer_list */
  head_of_free_g2pointer_list
    = g2ext_make_list_of_free_g2ptr_nodes
      ((G2pointer) 0L,
       (long) MAXIMUM_NUMBER_OF_FAST_G2PTRS,
       (Cpointer_ptr) g2ext_g2pointer_to_cpointer_array);
  tail_of_free_g2pointer_list
    = &(head_of_free_g2pointer_list
	[MAXIMUM_NUMBER_OF_FAST_G2PTRS - 1]);
  largest_possible_g2ptr_so_far = MAXIMUM_NUMBER_OF_FAST_G2PTRS - 1;
#ifdef VERBOSE
  printf("Init_Ptrs done!\n");
  fflush(stdout);
#endif
}



/*
 * The function `g2ext_map_g2pointer_to_cpointer' ...
 * Retrieves a cpointer given a g2pointer.
 */
Cpointer	g2ext_map_g2pointer_to_cpointer(G2pointer g2pointer)
{
  Cpointer cpointer;
  OBTAIN_CPOINTER_READ_LOCK();
#ifdef CHECK_MEMORY
  {
    /* Check for illegal pointer here */
    /* legal_g2pointer[MAXIMUM_NUMBER_OF_G2POINTERS_CHECKED]; */
    if (g2pointer >= MAXIMUM_NUMBER_OF_G2POINTERS_CHECKED)
      {
	printf("\nCan't check G2pointer %ld, too large.\n", g2pointer);
	fflush(stdout);
      }
    else
      {
	if (!(legal_g2pointer[g2pointer]))
	  {
	    int pid = getpid();

	    printf("\nIllegal G2pointer(%ld) in g2ext_map_g2pointer_to_cpointer, ",
		   g2pointer);
	    printf("interrupting lisp(pid %d)...\n", pid);
	    fflush(stdout);
	    kill(pid, SIGINT);
	    printf("\nContinuing in g2ext_map_g2pointer_to_cpointer ... \n");
	    printf("An error will probably result.\n");
	    fflush(stdout);
	    RELEASE_CPOINTER_LOCK();
	    return(-1);
	  }
      }
#ifdef VERBOSE
    if (g2pointer< MAXIMUM_NUMBER_OF_FAST_G2PTRS) 
	printf("map_g2ptr_to_Cptr: getting (%d)  out of array as %x.\n",
	       g2pointer, MAP_G2POINTER(g2pointer));
    else
	printf("map_g2ptr_to_Cptr: getting (%d) from overflow space as %x.\n",
	       g2pointer, MAP_G2POINTER(g2pointer));
    fflush(stdout);
#endif /* VERBOSE */
    cpointer = MAP_G2POINTER(g2pointer);
    RELEASE_CPOINTER_LOCK();
    return(cpointer);
  }
#else
#ifdef VERBOSE
    if (g2pointer< MAXIMUM_NUMBER_OF_FAST_G2PTRS) 
	printf("map_g2ptr_to_Cptr: getting (%d)  out of array as %x.\n",
	       g2pointer, MAP_G2POINTER(g2pointer));
    else
	printf("map_g2ptr_to_Cptr: getting (%d) from overflow space as %x.\n",
	       g2pointer, MAP_G2POINTER(g2pointer));
    fflush(stdout);
#endif /* VERBOSE */
  cpointer = MAP_G2POINTER(g2pointer);
  RELEASE_CPOINTER_LOCK();
  return(cpointer);
#endif
}






/*
 * The function `g2ext_cache_cpointer' ...
 */
G2pointer	g2ext_cache_cpointer(Cpointer cpointer)
{
#ifdef CHECK_MEMORY
  G2pointer g2pointer_to_return;
#endif

  OBTAIN_CPOINTER_WRITE_LOCK();
  
  if(!g2PointersInitialized)
    g2ext_initialize_g2pointers();

  if (head_of_free_g2pointer_list) /* if no overflow */
    {
      free_g2pointer_list_node_ptr	node_to_be_used
	= head_of_free_g2pointer_list;
      G2pointer g2pointer = head_of_free_g2pointer_list->g2pointer;
      Cpointer_ptr address_of_cpointer;

#ifdef VERBOSE
      printf("cache_pointer: No Overflow...\n");
      fflush(stdout);
#endif /* VERBOSE */
      address_of_cpointer = node_to_be_used->cpointer_ptr;
      head_of_free_g2pointer_list
	= node_to_be_used->next_node;
      *address_of_cpointer = cpointer;
      g2ext_reclaim_free_g2ptr_list_node(node_to_be_used);
#ifdef CHECK_MEMORY
      g2pointer_to_return = g2pointer;
      printf("Caching %x as %d.\n", cpointer, g2pointer_to_return);
      fflush(stdout);
#else
      RELEASE_CPOINTER_LOCK();
      return(g2pointer);
#endif
    }
  else
    {
      G2pointer temp_g2ptr;
#ifdef VERBOSE
      printf("cache_pointer: Putting in overflow space...\n");
      fflush(stdout);
#endif /* VERBOSE */
#ifdef CHECK_MEMORY
      g2pointer_to_return = g2ext_put_cptr_in_new_overflow_space((Cpointer) cpointer);
#  ifdef VERBOSE
      printf("Caching %x as %d.\n", cpointer, g2pointer_to_return);
      fflush(stdout);
#  endif /* VERBOSE */
#else
      temp_g2ptr = g2ext_put_cptr_in_new_overflow_space((Cpointer) cpointer);
      RELEASE_CPOINTER_LOCK();
      return(temp_g2ptr);
#endif
    }
#ifdef CHECK_MEMORY
  /* Allow caching of NULL pointer.  Just because the cpointer is zero doesn't
   * mean that this is not a legally cached G2 pointer.  - jv, 12/13/02
   */
  legal_g2pointer[g2pointer_to_return] = TRUE;
  RELEASE_CPOINTER_LOCK();
  return(g2pointer_to_return);
#endif
}


/*
 * jh, 3/18/96.  The function `g2ext_copy_g2pointer' exists so that Lisp can acquire a
 * new G2pointer from a dynamic extent where the old G2pointer is destined to be
 * destroyed automatically.  This is useful for the OLE infrastructure project.
 */
G2pointer	g2ext_copy_g2pointer(G2pointer g2pointer) /* Unused? */
{
 return g2ext_cache_cpointer(g2ext_map_g2pointer_to_cpointer(g2pointer));
}

/*
 * jh, 3/18/96.  The function `g2ext_cpointer_of_g2pointer_is_null' exists so that
 * Lisp can tell if it has successfully acquired a valid pointer.  This is
 * useful for the OLE infrastructure project.
 */
long	g2ext_cpointer_of_g2pointer_is_null(G2pointer g2pointer) /* Unused? */
{
 return g2ext_map_g2pointer_to_cpointer(g2pointer) == 0;
}

/*
 * jh, 5/5/96.  The function `g2ext_cpointers_of_g2pointers_eq' tests that the
 * referent of two G2pointers is identical.  This is useful for the OLE
 * infrastructure project.
 */
long	g2ext_cpointers_of_g2pointers_eq(G2pointer g2pointer_1, G2pointer g2pointer_2) /* Unused? */
{
 Cpointer   cpointer_1, cpointer_2;

 cpointer_1 = g2ext_map_g2pointer_to_cpointer(g2pointer_1);
 cpointer_2 = g2ext_map_g2pointer_to_cpointer(g2pointer_2);

 return (cpointer_1 == cpointer_2);
}




/*
 * The function `g2ext_decache_g2pointer' ...
 */
void g2ext_decache_g2pointer(G2pointer g2pointer)
{
  free_g2pointer_list_node_ptr	new_free_node_ptr;

  OBTAIN_CPOINTER_WRITE_LOCK();
  
  new_free_node_ptr  = g2ext_make_free_g2pointer_list_node();

#ifdef CHECK_MEMORY
  if (g2pointer >= MAXIMUM_NUMBER_OF_G2POINTERS_CHECKED)
    {
      printf("\nCan't check reclamation of G2pointer %ld, too large.\n",
	     g2pointer);
      fflush(stdout);
    }
  else
    {
      if (legal_g2pointer[g2pointer])
	{
	  legal_g2pointer[g2pointer] = FALSE;
	}
      else
	{
	  int pid = getpid();

	  printf("\nError: decaching illegal G2pointer(%ld); interrupt lisp(pid %d)...\n",
		 g2pointer, pid);
	  fflush(stdout);
	  kill(pid, SIGINT);
	  printf("\nContinuing g2ext_decache_g2pointer ... \n");
	  printf("An error will probably result.\n");
	  fflush(stdout);
	}
    }

#endif


  new_free_node_ptr->g2pointer = g2pointer;

  if (g2pointer < MAXIMUM_NUMBER_OF_FAST_G2PTRS)
    {
      /* So that the fast g2pointers are reused first */
      new_free_node_ptr->cpointer_ptr
	= (Cpointer_ptr)(&(g2ext_g2pointer_to_cpointer_array[g2pointer]));
	  g2ext_g2pointer_to_cpointer_array[g2pointer] = (Cpointer) NULL;
      new_free_node_ptr->next_node = head_of_free_g2pointer_list;
      head_of_free_g2pointer_list = new_free_node_ptr;
    }
  else
    {
      {	/* Get address of cpointer location */
	G2pointer current_maximum 
	  = MAXIMUM_NUMBER_OF_FAST_G2PTRS + SIZE_OF_OVERFLOW_SPACE_SEGMENT;
	overflow_array_list_node_ptr 
	  current_overflow_array_node_ptr = g2ptr_to_cptr_overflow_space;
	while ( g2pointer >= current_maximum )
	  {
	    current_overflow_array_node_ptr
	      = current_overflow_array_node_ptr->next_node;
	    current_maximum += SIZE_OF_OVERFLOW_SPACE_SEGMENT;
	  }
	new_free_node_ptr->cpointer_ptr
	  = (Cpointer_ptr)
	    &(current_overflow_array_node_ptr->overflow_array
	      [g2pointer+SIZE_OF_OVERFLOW_SPACE_SEGMENT-current_maximum]);
	current_overflow_array_node_ptr->overflow_array
	  [g2pointer+SIZE_OF_OVERFLOW_SPACE_SEGMENT-current_maximum]= (Cpointer) NULL;
      }
      new_free_node_ptr->next_node = NULL;
      tail_of_free_g2pointer_list->next_node = new_free_node_ptr;
      tail_of_free_g2pointer_list = new_free_node_ptr;
    }
  RELEASE_CPOINTER_LOCK();
}

#ifdef _IBMR2
g2_init_g2pointers()
{
	return(0);
}
#endif

/* To be taken out with the great cleanup vkp 1/25/96 */
long g2ext_get_add_cache_pointer()
{

  G2pointer (*pfn)(Cpointer /*cpointer*/) = g2ext_cache_cpointer;

  printf("Address of g2ext_cache_cpointer in C is %x\n", (unsigned int) pfn);
  fflush(stdout);
  return (long)pfn;
}
