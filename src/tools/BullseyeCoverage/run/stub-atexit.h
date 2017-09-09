/* $Revision: 9747 $ $Date: 2009-02-06 18:09:16 -0800 (Fri, 06 Feb 2009) $
 * Copyright (c) Bullseye Testing Technology
 */

#define atexit Libcov_atexit
static int atexit(void (Libcov_cdecl* function)(void))
{
	function = function;
	errno = ENOSYS;
	return 1;
}
