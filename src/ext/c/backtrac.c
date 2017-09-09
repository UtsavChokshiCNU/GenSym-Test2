/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module: backtrac.c
+ 
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):   Richard Harris
+
+ Description: This module contains primitives that are used for a symbolic C
+              backtrace.  This module is separate from trace.c because it 
+              must be compiled with GCC to be useful.
+              A custom makefile is used for this file.  See gen/mfiles/backtrace-make
+              The primary user of this facility is notify-console-of-internal-error.
+              in the lisp module OS-ERROR.   
+                
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Need to check this for each platform */
/*   Checked for: sun4                  */
#if defined(__x86_64__)
#  define VALID_RETURN_ADDRESS(x) ((unsigned long long)x>8192)
#else
#  define VALID_RETURN_ADDRESS(x) ((unsigned long)x>8192)
#endif

extern void *g2ext_pc_at_c_gensym_signal_handler;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

int g2ext_save_backtrace_into_array(
    void **backtrace_array,
    int backtrace_array_size,
    int frames_to_skip
    )
{
#ifdef _WIN32

    return CaptureStackBackTrace(frames_to_skip, backtrace_array_size, backtrace_array, NULL);

#else /* ifdef _WIN32 */
	
  int frame_count;
#if defined(__GNUC__)
  int index;
  void *return_address;
#endif

  g2ext_pc_at_c_gensym_signal_handler = 0;

#if defined(__GNUC__)

  index = 0;

#define get_return_addr(i) \
  if (!__builtin_frame_address(i) || index>=backtrace_array_size) { \
	frame_count = index; \
	goto end; \
  } \
  return_address = (void *)(__builtin_return_address(i)); \
  if (!VALID_RETURN_ADDRESS(return_address)) { \
    frame_count = index; \
	goto end; \
  } \
  if (i > frames_to_skip) \
    backtrace_array[index++] = return_address;

  get_return_addr(0);
  get_return_addr(1);
  get_return_addr(2);
  get_return_addr(3);
  get_return_addr(4);
  get_return_addr(5);
  get_return_addr(6);
  get_return_addr(7);
  get_return_addr(8);
  get_return_addr(9);
  get_return_addr(10);
  get_return_addr(11);
  get_return_addr(12);
  get_return_addr(13);
  get_return_addr(14);
  get_return_addr(15);
  get_return_addr(16);
  get_return_addr(17);
  get_return_addr(18);
  get_return_addr(19);
  get_return_addr(20);
  get_return_addr(21);
  get_return_addr(22);
  get_return_addr(23);
  get_return_addr(24);
  get_return_addr(25);
  get_return_addr(26);
  get_return_addr(27);
  get_return_addr(28);
  get_return_addr(29);
  get_return_addr(30);
  get_return_addr(31);
  get_return_addr(32);
  get_return_addr(33);
  get_return_addr(34);
  get_return_addr(35);
  get_return_addr(36);
  get_return_addr(37);
  get_return_addr(38);
  get_return_addr(39);
  frame_count = 39 - frames_to_skip;
end:

#else

  frame_count = 0;

#endif

  return frame_count;
  
#endif /* ifdef _WIN32 */

}
