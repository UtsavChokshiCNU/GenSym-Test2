# $Revision: 10168 $ $Date: 2009-07-09 16:31:20 -0700 (Thu, 09 Jul 2009) $
# Copyright (c) Bullseye Testing Technology
# This source file contains confidential proprietary information.

# References:
#   PowerPC Microprocessor Family:
#     The Programming Environments for 32-Bit Microprocessors, 02/21/2000
#   PowerPC Microprocessor Family: The Programmer's Reference Guide, 10/95
#   IBM AIX Assembler Language Reference, April 2001
# Parameters in r3-r5, return value in r3.
#   Determined from compiler output.

	.csect .text[PR]

# int cov_atomic_tryLock(cov_atomic_t* p)
	.globl .cov_atomic_tryLock
.cov_atomic_tryLock:
	li     4,0      # r4 <- 0
	sync
L1:	lwarx  5,0,3    # Load Word and Reserve Indexed
	                # r5 <- *p
	stwcx. 4,0,3    # Store Word Conditional Indexed
	                # r4 -> *p
	bne-   L1       # branch if store failed
	mr     3,5      # r3 <- r5
	blr
