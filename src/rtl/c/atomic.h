/*
 * atomic.h -  Chestnut Run-Time Library entry for atomic functions
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  4 Apr 2010
 * Update :  22 April 2014
 *
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *
 */

#ifndef SI_ATOMIC_DOT_H
#define SI_ATOMIC_DOT_H

#if SI_SUPPORT_THREAD

#if SI_USE_PROTOTYPES

extern Object atomic_exchange_symval(Object, Object);
extern Object atomic_incff_car(Object, Object);
extern Object atomic_incff_cdr(Object, Object);
extern Object atomic_incff_symval(Object, Object);
extern Object atomic_incff_svslot(Object, Object, Object);
extern Object compare_and_swap_car(Object, Object, Object);
extern Object compare_and_swap_cdr(Object, Object, Object);
extern Object compare_and_swap_symval(Object, Object, Object);
extern Object compare_and_swap_svslot(Object, SI_Long, Object, Object);

#else

extern Object atomic_exchange_symval();
extern Object atomic_incff_car();
extern Object atomic_incff_cdr();
extern Object atomic_incff_symval();
extern Object atomic_incff_svslot();
extern Object compare_and_swap_car();
extern Object compare_and_swap_cdr();
extern Object compare_and_swap_symval();
extern Object compare_and_swap_svslot();

#endif

#endif /* SI_SUPPORT_THREAD */
#endif /* SI_ATOMIC_DOT_H */
