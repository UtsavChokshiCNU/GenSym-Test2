/*
 * thread.h -  Chestnut Run-Time Library entry for multi-thread API
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  13 Apr 2009
 *
 * Copyright (c) 2009 Versata Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *
 */

#ifndef SI_THREAD_DOT_H
#define SI_THREAD_DOT_H

#if SI_SUPPORT_THREAD

/* Structure SI_Thread */
typedef struct {
    Structure_object included_fields;
    Object name;
    unsigned index;
    pthread_t id;
} SI_Thread;

#define SI_THREADP(o)		SI_INSTANCE_PRED(o, SI_THREAD_TYPE)
#define SI_TAG_THREAD(u)	SI_TAG_INSTANCE(u)
#define SI_THREAD_NAME(o)	SI_INSTANCE_FIELD(o,SI_Thread,name)
#define SI_THREAD_ID(o)		SI_INSTANCE_FIELD(o,SI_Thread,id)
#define SI_THREAD_INDEX(o)      SI_INSTANCE_FIELD(o,SI_Thread,index)
#define SI_THREAD_STUFF(o)	SI_INSTANCE_FIELD(o,SI_Header,stuff)

/* SI_current_thread() will be called by other internal functions which need to
   get current thread index from current thread object.
   Previously, we don't have this macro, and internal functions (include
   POP_SPECIAL()) just use current_thread(), and the VALUES_1() in public
   interface broke multiple values in user code (GENSYM-46968).
   
   This make us remember one important rule: internal function should always
   call internal functions but public functions because later will reset
   Values_count and make user code broken.  -- Chun Tian (binghe), 2010/1/2 */

extern TLS Object SI_current_thread_object;
#define SI_current_thread()     (SI_current_thread_object)

#if SI_USE_PROTOTYPES

extern Object all_threads(void);
extern Object current_thread(void);
extern Object kill_thread(Object);
extern Object spawn_thread varargs_1(int, n);
extern Object threadp(Object);
extern Object thread_alive_p(Object);
extern Object thread_name(Object);
extern Object thread_yield(void);
extern Object SETF_thread_name(Object, Object);
extern void SI_init_thread(void);

#else

extern Object all_threads();
extern Object current_thread();
extern Object kill_thread();
extern Object spawn_thread();
extern Object threadp();
extern Object thread_alive_p();
extern Object thread_name();
extern Object thread_yield();
extern Object SETF_thread_name();
extern void SI_init_thread();

#endif /* SI_USE_PROTOTYPES */

#define SI_INIT_THREAD() SI_init_thread()

#else /* SI_SUPPORT_THREAD */

#define SI_INIT_THREAD() do {} while(0)

#endif /* SI_SUPPORT_THREAD */
#endif /* SI_THREAD_DOT_H */
