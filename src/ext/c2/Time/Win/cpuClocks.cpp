/* Windows-specific code for CPU clock measurements
 * Subsystem: EXT.Subsystems.Time
 * Tags:
 * Used In:
 *   - G2 & TWNG performance measurements
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */
#include "common_config.h"
#ifndef Platform_Windows
#error You are trying to compile a windows-specific source in a non-Windows environment
#else // ONLY windows-specific code in this file

#include <windows.h>
#include "g2ss/Time/cpuClocks.h"

cltInt64 g2ext_get_process_cpu_cycles() {
	cltInt64 ans;
	ULONG64 cycleTime;
	HANDLE hProcess = GetCurrentProcess(); //REPERR: error-reporting
	BOOL bOk = QueryProcessCycleTime(hProcess, &cycleTime); //REPERR: error-reporting
	ans = cycleTime;
	return ans;
}


#endif /* Platform_Windows */
