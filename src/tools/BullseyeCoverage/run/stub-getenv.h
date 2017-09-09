/* $Revision: 9747 $ $Date: 2009-02-06 18:09:16 -0800 (Fri, 06 Feb 2009) $
 * Copyright (c) Bullseye Testing Technology
 */

#define getenv Libcov_getenv
static char* getenv(const char* name)
{
	return NULL;
}
