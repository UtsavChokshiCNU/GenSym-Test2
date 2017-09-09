/* $Revision: 10914 $ $Date: 2010-03-02 15:08:54 -0800 (Tue, 02 Mar 2010) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for ARC MetaWare C/C++
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define ENOSYS 100
#define PATH_MAX 512
#define S_IRUSR 0x0100
#define S_IWUSR 0x0080

#pragma BSS(".covbss")
#pragma Data(".covdata")

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-fcntl.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"

#pragma BSS()
#pragma Data()
