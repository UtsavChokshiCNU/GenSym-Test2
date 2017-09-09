/*
 * thread.c -  Chestnut Run-Time Library entry for multi-thread API
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  06 Apr 2009
 * Update :  01 May 2012
 *
 * Copyright (c) 2009 Versata Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern SI_Area Dynamic_area;
extern TLS SI_Area *Current_area;
extern TLS Object SI_Called_function;

#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern void SI_add_external_root(Object *p);
extern Object SI_alloc(SI_Size_type size, int align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object SI_cons(void);
extern Object SI_internal_spawn_thread(Object name, Object original_function, int args_on_stack, Object arglist);
extern Object SI_internal_funcall(Object original_function, int args_on_stack, Object arglist);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object STATIC_STRING(char *s);

#else

extern Object cons();
extern void SI_add_external_root();
extern Object SI_alloc();
extern Object SI_cons();
extern Object SI_internal_spawn_thread();
extern Object SI_internal_funcall();
extern Object SI_symbol_field();
extern Object STATIC_STRING();

#endif

/*
 * Thread functions
 */

#if SI_SUPPORT_THREAD

#if defined(WIN32)
#include <windows.h>
#include <process.h>
#endif

/* GENSYM-46928: CURRENT-THREAD and ALL-THREADS support */

Object SI_all_threads;
Object SI_initial_thread;
TLS Object SI_current_thread_object;
static short SI_next_available_thread_index = 0;

/* CRITICAL_SECTION are used for protection of SI_all_threads when new threads are created */
#if defined(_WIN32)

static CRITICAL_SECTION cs_thread;

#define SI_ENTER_CRITICAL_SECTION() EnterCriticalSection(&cs_thread)
#define SI_LEAVE_CRITICAL_SECTION() LeaveCriticalSection(&cs_thread)
#define SI_INIT_CRITICAL_SECTION() \
    InitializeCriticalSectionAndSpinCount(&cs_thread, 4000)

#else

#include <pthread.h>
#include <signal.h>
static pthread_mutex_t cs_thread;

#define SI_ENTER_CRITICAL_SECTION() \
	if(pthread_mutex_lock(&cs_thread)) { \
		perror("Error while obtaining cs_thread lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#define SI_LEAVE_CRITICAL_SECTION() \
	if(pthread_mutex_unlock(&cs_thread)) { \
		perror("Error while releasing cs_thread lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#define SI_INIT_CRITICAL_SECTION() \
	do { \
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
		if(pthread_mutex_init(&cs_thread, &attr)) { \
			perror("Error while initializing cs_thread lock"); \
			fflush(stdout); \
			raise(SIGTERM); \
		} \
	} while(0)

#endif /* defined(_WIN32) */

/* Public API */

Object all_threads()
{
    return VALUES_1(SI_all_threads);
}

Object current_thread()
{
    return VALUES_1(SI_current_thread_object);
}

Object spawn_thread varargs_1(int, n) /* (name function &rest args) */
{
    int i;
    Object *sp;
    va_list ap;
    Object name, func, result;

    SI_va_start(ap,n);
    name = va_arg(ap, Object);
    --n;

    func = va_arg(ap, Object);
    --n;

    sp = (Object *)Stack;
    Stack += n;
    for(i = 0; i < n; ++i)
	*sp++ = va_arg(ap, Object);
    va_end(ap);

    result = SI_internal_spawn_thread(name, func, n, NIL);
    return VALUES_1(result);
}

Object kill_thread(thread)
  Object thread;
{
    pthread_t id;

    if (!SI_THREADP(thread))
        return VALUES_1(NIL);

    id = SI_THREAD_ID(thread);

    if (0 == pthread_cancel(id))
        return VALUES_1(T);
    else
        return VALUES_1(NIL);
}

Object threadp(thread)
  Object thread;
{
    if (SI_THREADP(thread))
        return VALUES_1(T);
    else
        return VALUES_1(NIL);
}

Object thread_alive_p(thread)
  Object thread;
{
    /* not implemented */
    return VALUES_1(T);
}

Object thread_name(thread)
  Object thread;
{
    return VALUES_1(SI_THREAD_NAME(thread));
}

Object SETF_thread_name(new_name, thread)
  Object new_name, thread;
{
    SI_THREAD_NAME(thread) = new_name;
    return VALUES_1(new_name);
}

Object thread_yield()
{
    return VALUES_1(sched_yield() ? T : NIL);
}

Object hibernate_thread(thread)
  Object thread;
{
    /* not implemented */
    return VALUES_1(NIL);
}

Object awaken_thread(thread)
  Object thread;
{
    /* not implemented */
    return VALUES_1(NIL);
}

/* * * * * *
 * Internal Thread Functions
 */

#define MAX_THREAD_ARGS 4 /* max number of args when calling spawn_thread(). See also spawn-thread-limit-number-of-args in Lisp */

typedef struct SI_Thread_args_struct {
    Object original_function, arglist;
    SI_Stack_item stack[MAX_THREAD_ARGS];
    int args_on_stack;
} SI_Thread_args;

#define THREAD_PUSH(s,a) ((s++)->object=(a))
#define THREAD_POP(s)    ((--s)->object)

static Object SI_internal_make_thread(name)
  Object name;
{
  Object result;
  Declare_stack_pointer;

  SAVE_STACK();
  PROTECT_1(name);
  PROTECTI_1(result);

  result = SI_ALLOC(SI_Thread, SI_THREAD_TYPE, SI_INSTANCE_TAG, SI_NORMAL);

  SI_SET_WRAPPER(result, SI_WRAPPER_thread);
  SI_THREAD_NAME(result) = name;

  RESTORE_STACK();
  return result;
}

#define MULTIPLIER 1024		/* Copied from heap.c */
extern int SI_lisp_stack_size;  /* Defined in heap.c */

static SI_Stack_item *SI_new_stack()
{
    SI_Stack_item *lisp_stack;

    /* Create a new Stack for the new created thread. */
#ifdef HUGE_MSDOS
    lisp_stack = (Stack_item *) halloc((SI_Size_type) SI_lisp_stack_size,
				       MULTIPLIER * sizeof(Stack_item));
#else  /* not HUGE_MSDOS */
    lisp_stack = (Stack_item *) malloc((SI_Size_type) SI_lisp_stack_size *
				       MULTIPLIER * sizeof(Stack_item));
#endif /* HUGE_MSDOS */

    if (!lisp_stack) {
	fprintf(stdout, "SI_new_stack: not enough memory for lisp_stack\n");
	(void)exit(1);
    }
    return lisp_stack;
}

/* A INIT function for every new created thread */
void *SI_thread_init(args)
  SI_Thread_args *args;
{
    Object original_function, arglist, thread, cons;
    SI_Stack_item *stack;
    int i, args_on_stack;
    pthread_t id;

    original_function = args->original_function;
    args_on_stack = args->args_on_stack;
    arglist = args->arglist;
    stack = args->stack + args_on_stack;

    /* Prepare stack (copy for caller thread) */
    Stack = SI_new_stack();
    for (i = 0; i < args_on_stack; i++)
        STACK_PUSH(THREAD_POP(stack));

#ifdef USE_BITMAP_FOR_CONS_TRACING
#include "thread.c won't support USE_BITMAP_FOR_CONS_TRACING"
#endif

    /* Init TLS Blocks (SI_Special_data & SI_Special_count) for current thread. */
    SI_INIT_TLS_BLOCK();

    /* GENSYM-46913: initialize current allocation area */
    Current_area = &Dynamic_area;

    /* GENSYM-46928: CURRENT-THREAD and ALL-THREADS support;
       GENSYM-47104: 3-threads SymScale crash, SI_current_thread not set correctly
                     if two new threads pushed into SI_all_threads so quickly
                     before the first new thread runs to here. */
    SI_ENTER_CRITICAL_SECTION();
    /* Search into SI_all_threads to find the thread object which maps to current
       thread, the method is to match the "thread_id" which returned by win32 API */

    id = pthread_self();
    for (cons = SI_all_threads; cons != NIL; cons = M_CDR(cons)) {
        thread = M_CAR(cons);
        if (pthread_equal(SI_THREAD_ID(thread), id)) {
            SI_current_thread_object = thread;
            break;
        }
    }
    SI_LEAVE_CRITICAL_SECTION();

    /* Finally we call the actual thread spawn function */
    SI_internal_funcall(original_function, args_on_stack, arglist);

    free(args); /* allocated in SI_internal_spawn_thread */
    return (unsigned)0;
}

#include "funcall.h"

Object SI_internal_spawn_thread(name, original_function, args_on_stack, arglist)
  Object name, original_function, arglist;
  int args_on_stack;
{
  Object thread, new_cons;
  SI_Thread_args *args = (SI_Thread_args*) malloc(sizeof(SI_Thread_args));
  SI_Stack_item *stack;
  int i, status;
  pthread_t thread_id;

  SI_ENTER_CRITICAL_SECTION();

  args->original_function = original_function;
  args->args_on_stack = args_on_stack;
  args->arglist = arglist;
  stack = args->stack;

  for(i = 0; i < args_on_stack; i++)
      THREAD_PUSH(stack, STACK_POP());

  status = pthread_create (&thread_id, NULL, (void* (*) (void *)) SI_thread_init, (void*)args);
  thread = SI_internal_make_thread(name);

  SI_THREAD_ID(thread) = thread_id;
  SI_THREAD_INDEX(thread) = SI_next_available_thread_index ++;

  new_cons = SI_CONS();
  M_CAR(new_cons) = thread;
  M_CDR(new_cons) = SI_all_threads;
  SI_all_threads = new_cons;

  SI_LEAVE_CRITICAL_SECTION();

  return thread;
}

void SI_init_thread()
{
    Object result;

    /* SI_initial_thread (main thread) initialization */
    result = SI_ALLOC(SI_Thread, SI_THREAD_TYPE, SI_INSTANCE_TAG, SI_NORMAL);
    SI_SET_WRAPPER(result, SI_WRAPPER_thread);

    SI_THREAD_NAME(result) = STATIC_STRING("Initial thread");
    SI_THREAD_INDEX(result) = SI_next_available_thread_index ++;
    SI_THREAD_ID(result) = pthread_self();

    SI_initial_thread = result;
    SI_current_thread_object = result;

    /* SI_all_threads initialization: (SETQ *all-threads* (CONS *initial-thread* NIL)) */
    result = SI_CONS();
    M_CAR(result) = SI_initial_thread;
    M_CDR(result) = NIL;
    SI_all_threads = result;

    PROTECT_GLOBAL_2(SI_all_threads, SI_initial_thread);
    SI_INIT_CRITICAL_SECTION();
}

#endif /* SI_SUPPORT_THREAD */
