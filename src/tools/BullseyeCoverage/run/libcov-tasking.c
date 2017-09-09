// $Revision: 10470 $ $Date: 2009-10-08 14:56:47 -0700 (Thu, 08 Oct 2009) $
// Copyright (c) Bullseye Testing Technology
// This source file contains confidential proprietary information.
//
// BullseyeCoverage run-time definitions for TASKING VX-toolset

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define ENOSYS (-2)
#define PATH_MAX 128
#define S_IRUSR _S_IREAD
#define S_IWUSR _S_IWRITE

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-fcntl.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"
