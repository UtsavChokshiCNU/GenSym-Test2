/ $Revision: 5049 $ $Date: 2004-11-18 13:47:54 -0800 (Thu, 18 Nov 2004) $
/ Copyright (c) Bullseye Testing Technology
/ This source file contains confidential proprietary information.

	.section .text

	.type cov_atomic_tryLock,@function
	.globl cov_atomic_tryLock
	.align 4

/ int cov_atomic_tryLock(cov_atomic_t* p)
cov_atomic_tryLock:
	movl  4(%esp),%edx  / p -> edx
	subl  %eax,%eax     / 0 -> eax
	xchgl %eax,(%edx)
	ret
	.size cov_atomic_tryLock,.-cov_atomic_tryLock
