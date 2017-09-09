/* lgsi_support.c */

/* Support routines in C for Bridge authors writing in Lisp, i.e. lgsi */
#include <stddef.h>
#include "gsi_main.h"

/* Lgsi_rpc_declare_remote_1 returns the handle used to call this later.
   It disregards any errors, but I don't see how any can occur.

   Note: the real version of this function is in gw/c/gw_main.c
 */

#if defined(XANALYS)

void lgsi_rpc_declare_remote_1(function_name, number_of_args, number_of_return_values)
	char * function_name;
	int number_of_args;
	int number_of_return_values;
{
	return;
}

#endif
