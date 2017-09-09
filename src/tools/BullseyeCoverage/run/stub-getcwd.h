/* $Revision: 9747 $ $Date: 2009-02-06 18:09:16 -0800 (Fri, 06 Feb 2009) $
 * Copyright (c) Bullseye Testing Technology
 */

#define getcwd Libcov_getcwd
static char* getcwd(char* buf, unsigned size)
{
	buf = buf;
	size = size;
	errno = ENOSYS;
	return NULL;
}
