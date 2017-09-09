/*
 * lock.h -  Chestnut Run-Time Library entry for multi-thread API
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  26 Jul 2009
 *
 * Copyright (c) 2009 Versata Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *
 */

#ifndef SI_LOCK_DOT_H
#define SI_LOCK_DOT_H

#if SI_SUPPORT_THREAD

/* Structure LOCK */

typedef struct {
    Structure_object included_fields;
    Object name;
    pthread_mutex_t id;
} SI_Lock;

#define SI_LOCKP(o)		SI_INSTANCE_PRED(o, SI_LOCK_TYPE)
#define SI_TAG_LOCK(u)	        SI_TAG_INSTANCE(u)
#define SI_LOCK_NAME(o) 	SI_INSTANCE_FIELD(o,SI_Lock,name)
#define SI_LOCK_ID(o)           SI_INSTANCE_FIELD(o,SI_Lock,id)
#define SI_LOCK_STUFF(o)	SI_INSTANCE_FIELD(o,SI_Header,stuff)

typedef struct {
    Structure_object included_fields;
    Object lock;
    pthread_cond_t id;
} SI_Condition_variable;

#define SI_CONDP(o)             SI_INSTANCE_PRED(o, SI_COND_TYPE)
#define SI_TAG_COND(u)          SI_TAG_INSTANCE(u)
#define SI_COND_LOCK(o)         SI_INSTANCE_FIELD(o,SI_Condition_variable,lock)
#define SI_COND_ID(o)           SI_INSTANCE_FIELD(o,SI_Condition_variable,id)
#define SI_COND_STUFF(o)	SI_INSTANCE_FIELD(o,SI_Header,stuff)

#if SI_USE_PROTOTYPES

extern Object condition_variable_broadcast(Object);
extern Object condition_variable_signal(Object);
extern Object condition_variable_wait(Object);
extern Object condition_variable_wait_with_timeout(Object, Object);
extern Object make_condition_variable varargs_1(int, n);
extern Object make_lock varargs_1(int, n);
extern Object make_recursive_lock varargs_1(int, n);
extern Object SI_lock(Object);
extern Object SI_trylock(Object);
extern Object SI_unlock(Object);
extern void SI_init_lock(void);

#else

extern Object condition_variable_broadcast();
extern Object condition_variable_signal();
extern Object condition_variable_wait();
extern Object condition_variable_wait_with_timeout();
extern Object make_condition_variable();
extern Object make_lock();
extern Object make_recursive_lock();
extern Object SI_lock();
extern Object SI_trylock();
extern Object SI_unlock();
extern void SI_init_lock();

#endif /* SI_USE_PROTOTYPES */

/* Locking functions as macro */
#define LOCK(o)    SI_lock(o)
#define TRYLOCK(o) SI_trylock(o)
#define UNLOCK(o)  SI_unlock(o)

#define SI_INIT_LOCK() SI_init_lock()

#else /* SI_SUPPORT_THREAD */

#define SI_INIT_LOCK() do {} while(0)

#endif /* SI_SUPPORT_THREAD */
#endif /* SI_LOCK_DOT_H */
