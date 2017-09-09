/* The prototypes for CPU clock measurements
 * Subsystem: EXT.Subsystems.Time
 * Tags:
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */
#ifndef CPUCLOCKS_H
#define CPUCLOCKS_H

#include "common_config.h"

// This function has platform-specific implementations, and follows
//   QueryProcessCycleTime specified in http://msdn.microsoft.com/en-us/library/ms684929(VS.85).aspx
cltInt64 g2ext_get_process_cpu_cycles();

#endif /* CPUCLOCKS_H */