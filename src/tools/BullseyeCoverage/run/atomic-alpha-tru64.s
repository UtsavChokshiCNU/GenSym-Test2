 # $Revision: 10168 $ $Date: 2009-07-09 16:31:20 -0700 (Thu, 09 Jul 2009) $
 # Copyright (c) Bullseye Testing Technology
 # This source file contains confidential proprietary information.

 # References:
 #   Alpha AXP Architecture Handbook October 1994.
 #   Tru64 Assembly Language Programmer's Guide August 2000
 #     http://www.tru64unix.compaq.com/docs/base_doc/DOCUMENTATION/V51_HTML/ARH9LBTE/BTCHPTRX.HTM
 # Parameters in r16-r21, return value in r0, r1-r8 temps.
 #   Parameters, return value, function entry and exit determined from
 #   Assembly Language Programmer's Guide.

	.text

 # int cov_atomic_tryLock(cov_atomic_t* p)
	.globl cov_atomic_tryLock
	.ent cov_atomic_tryLock
cov_atomic_tryLock:
	.frame $sp,0,$26
	mb
1:	ldl_l $0,0($16)     # Load Sign-Extended Longword Locked
	                    # r0 <- *p; lock_flag <- 1
	mov   $31,$1        # 0 -> r1
	stl_c $1,0($16)     # Store Longword Conditional
	                    # if lock_flag == 1 r1 -> *p; r1 <- lock_flag
	beq   $1,2f         # branch if r1 == 0
	ret   $31,($26),1
 # Alpha predicts backward branches will be taken,
 #  this avoids near-certain mis-prediction of beq above.
2:	br    1b
	.end cov_atomic_tryLock
