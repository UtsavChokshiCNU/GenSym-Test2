/*
 * lock.c -  Chestnut Run-Time Library entry for multi-thread API
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  26 Jul 2009
 *
 * Copyright (c) 2009 Versata Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include <time.h>

extern Object Klock;
extern Object Kname;

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, int align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (int n, char *lstr, ...);
extern Object (*SI_warn_fptr) (int n, char *lstr, ...);
extern Object SI_obtain_rest_list(int rest_position, int arg_position, int nargs, va_list *ap);
extern Object SI_internal_make_condition_variable(Object lock);
static Object SI_internal_make_lock(Object name, int recursive_p);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object string(Object);

#else

extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();
extern Object SI_obtain_rest_list();
extern Object SI_internal_make_condition_variable();
static Object SI_internal_make_lock();
extern Object SI_symbol_field();
extern Object string();

#endif

#if SI_SUPPORT_THREAD

/*
 * Lock functions
 */

#if defined(_WIN32)
#include <windows.h>
#include <process.h>
typedef unsigned (__stdcall *PTHREAD_START) (void *);

static CRITICAL_SECTION cs;

#define SI_ENTER_CRITICAL_SECTION() EnterCriticalSection(&cs)
#define SI_LEAVE_CRITICAL_SECTION() LeaveCriticalSection(&cs)
#define SI_INIT_CRITICAL_SECTION() \
    InitializeCriticalSectionAndSpinCount(&cs, 4000) /* Used in init_heaps() */

#else

#include <pthread.h>
#include <signal.h>
static pthread_mutex_t cs;

#define SI_ENTER_CRITICAL_SECTION() \
	if(pthread_mutex_lock(&cs)) { \
		perror("Error while obtaining cs lock"); \
		fflush(stdout); \
		raise(SIGTERM); \
	}
#define SI_LEAVE_CRITICAL_SECTION() \
	if(pthread_mutex_unlock(&cs)) { \
		perror("Error while releasing cs lock"); \
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
		if(pthread_mutex_init(&cs, &attr)) { \
			perror("Error while initializing cs_thread lock"); \
			fflush(stdout); \
			raise(SIGTERM); \
		} \
	} while(0)

#endif /* defined(_WIN32) */

static TLS char error_buffer[256];

Object make_lock varargs_1(int, n) /* (&key name) */
{
    XDeclare_varargs;
    Object name, result;

    BEGIN_ARGS(n);
        KEYWORD_ARGS_1(Kname, name);
    END_ARGS();

    if (UNSUPPLIED_P(name))
        name = NIL;

    result = SI_internal_make_lock(name, 0);

    return VALUES_1(result);
}

Object make_recursive_lock varargs_1(int, n) /* (&key name) */
{
    XDeclare_varargs;
    Object name, result;

    BEGIN_ARGS(n);
        KEYWORD_ARGS_1(Kname, name);
    END_ARGS();

    if (UNSUPPLIED_P(name))
        name = NIL;

    result = SI_internal_make_lock(name, 1);

    return VALUES_1(result);
}

Object make_condition_variable varargs_1(int, n)
  /* (&rest initargs &key (class 'condition-variable) &allow-other-keys) */
{
    XDeclare_varargs;
    Object lock, result;

    BEGIN_ARGS(n);
        KEYWORD_ARGS_1(Klock, lock);
    END_ARGS();

    if (UNSUPPLIED_P(lock))
        lock = SI_internal_make_lock(NIL, 0);

    result = SI_internal_make_condition_variable(lock);

    return VALUES_1(result);
}

Object condition_variable_wait(condition_variable)
  Object condition_variable;
{
    Object lock;
    int status;

    if (!SI_CONDP(condition_variable))
        return VALUES_1(NIL);

    lock = SI_COND_LOCK(condition_variable);
    status = pthread_cond_wait(&SI_COND_ID(condition_variable), &SI_LOCK_ID(lock));

    return VALUES_1(lock);
}

Object condition_variable_wait_with_timeout(condition_variable, seconds)
  Object condition_variable, seconds;
{
    Object lock;
    struct timespec timeout;
    int status;

    if (!SI_CONDP(condition_variable))
        return VALUES_1(NIL);

    lock = SI_COND_LOCK(condition_variable);
    timeout.tv_sec = (long) time(NULL) + IFIX(seconds);
    timeout.tv_nsec = 0;
    status = pthread_cond_timedwait(&SI_COND_ID(condition_variable), &SI_LOCK_ID(lock), &timeout);

    return VALUES_1(lock);
}

Object condition_variable_signal(condition_variable)
  Object condition_variable;
{
    int status;

    if (!SI_CONDP(condition_variable))
        return VALUES_1(NIL);

    status = pthread_cond_signal(&SI_COND_ID(condition_variable));

    return VALUES_1(T);
}

Object condition_variable_broadcast(condition_variable)
  Object condition_variable;
{
    int status;

    if (!SI_CONDP(condition_variable))
        return VALUES_1(NIL);

    status = pthread_cond_broadcast(&SI_COND_ID(condition_variable));

    return VALUES_1(T);
}

/* * * * * *
 * Internal Lock Functions -- binghe, 2009/7/29
 * Updated on 2014/12/12 (recursive lock)
 */

static Object SI_internal_make_lock(name, recursive_p)
  Object name;
  int recursive_p;
{
    Object result;
    Declare_stack_pointer;
    int status;
    pthread_mutexattr_t Attr;

  SI_ENTER_CRITICAL_SECTION();
  SAVE_STACK();
  PROTECT_1(name);
  PROTECTI_1(result);

  result = SI_ALLOC(SI_Lock, SI_LOCK_TYPE, SI_INSTANCE_TAG, SI_NORMAL);

  SI_SET_WRAPPER(result, SI_WRAPPER_lock);
  SI_LOCK_NAME(result) = name;

  if (recursive_p) {
    pthread_mutexattr_init(&Attr);
    pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);
    status = pthread_mutex_init(&SI_LOCK_ID(result), &Attr);
    pthread_mutexattr_destroy(&Attr);
  } else
    status = pthread_mutex_init(&SI_LOCK_ID(result), NULL);

  RESTORE_STACK();
  SI_LEAVE_CRITICAL_SECTION();
  return result;
}

Object SI_lock(lock)
  Object lock;
{
    int status;

    if (!SI_LOCKP(lock))
        return NIL;

    status = pthread_mutex_lock(&SI_LOCK_ID(lock));

    return status ? NIL : T;
}

Object SI_trylock(lock)
  Object lock;
{
    int status;

    if (!SI_LOCKP(lock))
        return NIL;

    status = pthread_mutex_trylock(&SI_LOCK_ID(lock));

    return status ? NIL : T;
}

Object SI_unlock(lock)
  Object lock;
{
    int status;

    if (!SI_LOCKP(lock))
        return NIL;

    status = pthread_mutex_unlock(&SI_LOCK_ID(lock));

    return status ? NIL : T;
}

Object SI_internal_make_condition_variable(lock)
  Object lock;
{
    Object result;
    Declare_stack_pointer;
    int status;

    SI_ENTER_CRITICAL_SECTION();
    SAVE_STACK();
    PROTECT_1(lock);
    PROTECTI_1(result);

    result = SI_ALLOC(SI_Condition_variable, SI_COND_TYPE, SI_INSTANCE_TAG, SI_NORMAL);

    SI_SET_WRAPPER(result, SI_WRAPPER_condition_variable);
    SI_COND_LOCK(result) = lock;

    status = pthread_cond_init(&SI_COND_ID(result), NULL);

    RESTORE_STACK();
    SI_LEAVE_CRITICAL_SECTION();
    return result;
}

void SI_init_lock()
{
    SI_INIT_CRITICAL_SECTION();
}

#endif /* SI_SUPPORT_THREAD */
