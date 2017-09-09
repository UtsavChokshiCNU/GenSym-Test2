! $Revision: 10168 $ $Date: 2009-07-09 16:31:20 -0700 (Thu, 09 Jul 2009) $
! Copyright (c) Bullseye Testing Technology
! This source file contains confidential proprietary information.

! References:
!   The SPARC Architecture Manual Version 8, 1992
!   SYSTEM V APPLICATION BINARY INTERFACE,
!     SPARC Processor Supplement, Third Edition, 1996
!   Sun SPARC Assembly Language Reference Manual, May 2002
! Parameters in o0-o5, return value in o0

	.section ".text"

! int cov_atomic_tryLock(cov_atomic_t* p)
	.global cov_atomic_tryLock
	.type cov_atomic_tryLock,#function
cov_atomic_tryLock:
	membar #LoadLoad | #LoadStore | #StoreLoad | #StoreStore
	mov  %o0,%o1    ! p -> o1
	clr  %o0        ! 0 -> o0
	retl
	swap [%o1],%o0  ! (in delay slot)
	.size cov_atomic_tryLock,(.-cov_atomic_tryLock)
