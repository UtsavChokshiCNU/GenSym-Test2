/* $Revision: 10757 $ $Date: 2010-01-13 15:27:04 -0800 (Wed, 13 Jan 2010) $
 * Copyright (c) Bullseye Testing Technology
 */

#define pthread_t Libcov_pthread_t
typedef int pthread_t;

#define pthread_atfork Libcov_pthread_atfork
static int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
	prepare = prepare;
	parent = parent;
	child = child;
	return ENOSYS;
}

#define pthread_create Libcov_pthread_create
static int pthread_create(pthread_t* thread, const void* attr, void* (* start_routine)(void*), void* arg)
{
	thread = thread;
	attr = attr;
	start_routine = start_routine;
	arg = arg;
	return ENOSYS;
}

#define pthread_exit Libcov_pthread_exit
static void pthread_exit(void* value_ptr)
{
	value_ptr = value_ptr;
}

#define pthread_join Libcov_pthread_join
static int pthread_join(pthread_t thread, void** value_ptr)
{
	thread = thread;
	value_ptr = value_ptr;
	return ENOSYS;
}
