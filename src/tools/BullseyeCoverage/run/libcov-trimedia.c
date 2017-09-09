// $Revision: 9490 $ $Date: 2008-11-25 16:51:58 -0800 (Tue, 25 Nov 2008) $
// Copyright (c) Bullseye Testing Technology
// This source file contains confidential proprietary information.
//
// BullseyeCoverage run-time definitions for NXP TriMedia Compilation System

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntlcom.h>
#include <sys/syslimits.h>
#include <sys/stat.h>
#include <unistd.h>

#define open Libcov_open
int open(const char* path, int oflag, int mode)
{
	return _open(path, oflag | O_BINARY, mode);
}

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-fcntl.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"
