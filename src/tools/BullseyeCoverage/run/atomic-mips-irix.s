/* $Revision: 10415 $ $Date: 2009-09-22 14:16:28 -0700 (Tue, 22 Sep 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * References:
 *   MIPS IV Instruction Set, Revision 3.2, September 1995
 *   MIPSpro Assembly Language Programmer's Guide, March 1999
 * Parameters in r4-r7, return value in r2, r2-r3 temps,
 *   determined from Assembly Language Programmer's Guide.
 */

/* int cov_atomic_tryLock(cov_atomic_t* p) */
	.ent cov_atomic_tryLock
	.globl cov_atomic_tryLock
	.frame $sp,0,$31
cov_atomic_tryLock:
	sync
L1:	ll   $2,($4)        # Load Linked
	                    # r2 <- *p
	li   $3,0           # r3 <- 0
	sc   $3,($4)        # Store Conditional
	                    # r3 -> *p
	beqz $3,L1          # branch if store failed
	nop                 # delay slot
	jr   $31
	nop                 # delay slot
	.end cov_atomic_tryLock
