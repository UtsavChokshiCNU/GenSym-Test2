/* The prototypes for DLL interoperability in KB language
 * Subsystem: EXT.Subsystems.Interop
 * Tags:
 *  - A shared header to use in the rest of the application
 *
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */
#ifndef DLLLINK_H
#define DLLLINK_H

#include "common_config.h"

#ifdef __cplusplus
	extern "C" { 
#endif /* __cplusplus */

#ifdef Platform_Windows
	int XANALYS_API g2ext_load_dynamic_library(wchar_t*);
#else
	int XANALYS_API g2ext_load_dynamic_library();
#endif

#ifdef __cplusplus
	} // extern "C"
#endif /* __cplusplus */

#endif /* DLLLINK_H */
