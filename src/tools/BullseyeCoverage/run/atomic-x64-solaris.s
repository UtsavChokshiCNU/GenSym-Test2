/ $Revision: 10168 $ $Date: 2009-07-09 16:31:20 -0700 (Thu, 09 Jul 2009) $
/ Copyright (c) Bullseye Testing Technology
/ This source file contains confidential proprietary information.

	.section .text

	.type cov_atomic_tryLock,@function
	.globl cov_atomic_tryLock
	.align 16

/ int cov_atomic_tryLock(cov_atomic_t* p)
cov_atomic_tryLock:
	mfence
	subl  %eax,%eax
	xchgl %eax,(%rdi)
	ret
	.size cov_atomic_tryLock,.-cov_atomic_tryLock
