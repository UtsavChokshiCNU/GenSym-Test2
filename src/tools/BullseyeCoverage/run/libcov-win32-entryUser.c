/* $Revision: 7929 $ $Date: 2007-05-25 14:20:07 -0700 (Fri, 25 May 2007) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 */

// Do not include windows.h due to complicated macros and warnings

#if __cplusplus
extern "C"
#endif
int (__stdcall* cov_DllMain_user)(void*, unsigned, void*) = 0;
